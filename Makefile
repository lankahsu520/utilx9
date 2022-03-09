-include $(SDK_CONFIG_CONFIG)

STRIP ?= $(PJ_STRIP)

#[major].[minor].[revision].[build]
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_REVISION = 0
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)
LIBNAME = utilx9

#** CFLAGS & LDFLAGS **
CFLAGS += $(CFLAGS_CUSTOMER)

CFLAGS += \
					-Wall -O2 \
					-I./
ifeq ("$(PJ_ARCH)", "x86")
CFLAGS += \
					-Wno-unused-value \
					-Wno-unused-result \
					-Wno-format-truncation
endif
LDFLAGS += \
					-L./
ARFLAGS = rcs

#** LIBXXX_OBJS **
LIBXXX_OBJS += \
							chainX_api.o \
							clist_api.o \
							led_api.o \
							proc_table_api.o \
							queue_api.o \
							multicast_api.o \
							statex_api.o \
							thread_api.o \
							cronx_api.o \
							utilx9.o

#** LIBXXX_yes **
#LIBXXX_A = lib$(LIBNAME).a
LIBXXX_SO = lib$(LIBNAME).so
LIBXXXS_$(PJ_HAS_STATIC_LIB) += $(LIBXXX_A)
LIBXXXS_$(PJ_HAS_SHARE_LIB) += -l$(LIBNAME)

#** HEADER_FILES **
HEADER_FILES = utilx9.h basic_def.h ubus_ex.h

LIBS_yes = $(LIBXXXS_yes)
-include ./library.mk

#** librarys **
LIBS += -lz
#-ldl -lpthread -lm

#** Clean **
#CLEAN_BINS =
CLEAN_OBJS = $(LIBXXX_OBJS)
CLEAN_LIBS = $(LIBXXX_A) $(LIBXXX_SO)

#** Target (CLEAN_BINS) **
CLEAN_BINS += \
						nlink_123 \
						nlink_456 \
						nlink_789 \
						proc_list_123 \
						proc_watch \
						queue_123 \
						demo_123 \
						demo_000

#** Target (DUMMY_BINS) **
DUMMY_BINS += \
						util_123

CLEAN_BINS += $(DUMMY_BINS)
CLEAN_OBJS += $(addsuffix .o, $(CLEAN_BINS))

#** Target (SHELL_SBINS) **
SHELL_SBINS = \
						proc_watch.sh

DUMMY_SBINS = $(SHELL_SBINS)

include define.mk

.SUFFIXES: .c .o

.PHONY: all clean distclean install romfs expired
all: .configured $(CLEAN_BINS) $(CLEAN_LIBS)

%.o: %.c $(HEADER_FILES)
	@echo 'Compiling file: $<'
	$(CC) $(CFLAGS) -c -o"$@" "$<"
	@echo 'Finished compiling: $<'
	@echo ' '

$(CLEAN_BINS): $(CLEAN_OBJS) $(CLEAN_LIBS)
	@echo 'Building target: $@'
	$(CC) -o $@ $@.o $(LDFLAGS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	rm -f Makefile.bak $(CLEAN_BINS) $(CLEAN_BINS:=.elf) $(CLEAN_BINS:=.gdb)
	rm -f $(addsuffix *, $(CLEAN_LIBS)) $(CLEAN_OBJS)
	rm -f $(CLEAN_OBJS:%.o=%.c.bak) $(CLEAN_OBJS:%.o=%.h.bak)
	rm -f util_expiration.h
	rm -f .configured
ifeq ("$(PJ_NAME)", "github")
	@[ -d $(PJ_NAME) ] && (rm -rf $(PJ_NAME);) || echo "skip !!! (PJ_NAME)" 
endif

	@for subbin in $(CLEAN_BINS); do \
		(rm -f $(SDK_BIN_DIR)/$$subbin;); \
	done
	@for sublib in $(CLEAN_LIBS); do \
		(rm -f $(SDK_LIB_DIR)/$$sublib*;); \
	done
	@for subheader in $(HEADER_FILES); do \
		(rm -f $(SDK_INC_DIR)/$$subheader;); \
	done
	@for subshell in $(SHELL_SBINS); do \
		(rm -f $(SDK_SBIN_DIR)/$$subshell;); \
	done

distclean: clean

%.a: $(LIBXXX_OBJS)
	@echo 'Building lib (static): $@'
	$(AR) $(ARFLAGS) $@ $(LIBXXX_OBJS)
	@echo 'Finished building lib (static): $@'
	@echo ' '

%.so: $(LIBXXX_OBJS)
	@echo 'Building lib (shared): $@'
	$(CC) -shared $(LDFLAGS) -Wl,-soname,$@.$(VERSION_MAJOR) -o $@.$(VERSION) $(LIBXXX_OBJS)
	ln -sf $@.$(VERSION) $@.$(VERSION_MAJOR)
	ln -sf $@.$(VERSION_MAJOR) $@
	@echo 'Finished building lib (shared): $@'
	@echo ' '

install: all
	mkdir -p $(SDK_BIN_DIR)
	@for subbin in $(CLEAN_BINS); do \
		$(PJ_CP) $$subbin $(SDK_BIN_DIR); \
		$(STRIP) $(SDK_BIN_DIR)/$$subbin; \
	done
	mkdir -p $(SDK_LIB_DIR)
	@for sublib in $(CLEAN_LIBS); do \
		$(PJ_CP) $$sublib* $(SDK_LIB_DIR); \
		$(STRIP) $(SDK_LIB_DIR)/$$sublib.$(VERSION); \
	done
	mkdir -p $(SDK_INC_DIR)
	@for subheader in $(HEADER_FILES); do \
		$(PJ_CP) $$subheader $(SDK_INC_DIR); \
	done
	mkdir -p $(SDK_SBIN_DIR)
	@for subshell in $(SHELL_SBINS); do \
		$(PJ_CP) $$subshell $(SDK_SBIN_DIR); \
	done

romfs: install
ifneq ("$(HOMEX_ROOT_DIR)", "")
	mkdir -p $(HOMEX_BIN_DIR)
	@for subbin in $(DUMMY_BINS); do \
		$(PJ_CP) $$subbin $(HOMEX_BIN_DIR); \
		$(STRIP) $(HOMEX_BIN_DIR)/$$subbin; \
	done
	mkdir -p $(HOMEX_LIB_DIR)
	@for sublib in $(CLEAN_LIBS); do \
		$(PJ_CP) $$sublib* $(HOMEX_LIB_DIR); \
		$(STRIP) $(HOMEX_LIB_DIR)/$$sublib.$(VERSION); \
	done
	#@for subheader in $(HEADER_FILES); do \
	#	$(PJ_CP) $$subheader $(HOMEX_INC_DIR); \
	#done
	mkdir -p $(HOMEX_SBIN_DIR)
	@for subshell in $(DUMMY_SBINS); do \
		$(PJ_CP) $$subshell $(HOMEX_SBIN_DIR); \
	done
endif

expired:
	$(call generate_expiration, $(shell date -d "+4 years" "+%s"))