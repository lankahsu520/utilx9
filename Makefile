PWD=$(shell pwd)
-include $(SDK_CONFIG_CONFIG)

#[major].[minor].[revision].[build]
VERSION_MAJOR = 1
VERSION_MINOR = 2
VERSION_REVISION = 1
VERSION_FULL = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)
LIBNAME = utilx9

LIBUTILX_API_VERSION="0x$(shell printf "%02X" $(VERSION_MAJOR))$(shell printf "%03X" $(VERSION_MINOR))$(shell printf "%03X" $(VERSION_REVISION))"

#** CFLAGS & LDFLAGS **
CFLAGS += $(CFLAGS_OTHERS) $(CFLAGS_CUSTOMER)

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
							queuex_api.o \
							multicast_api.o \
							statex_api.o \
							thread_api.o \
							cronx_api.o \
							utilx9.o

#** LIBXXX_yes **
#LIBXXX_A = lib$(LIBNAME).a
LIBXXX_SO = lib$(LIBNAME).so
#LIBXXXS_$(PJ_HAS_STATIC_LIB) += $(LIBXXX_A)
#LIBXXXS_$(PJ_HAS_SHARE_LIB) += -l$(LIBNAME)
LIBXXXS_yes += -l$(LIBNAME)

#** HEADER_FILES **
HEADER_FILES = \
							basic_def.h \
							ubus_ex.h \
							utilx9.h

#** librarys **
LIBS_yes = $(LIBXXXS_yes)
#** LIBS_yes, CLEAN_BINS, DUMMY_BINS  **
-include ./library.mk

LIBS += $(LIBS_yes)
#-lz -ldl -lpthread -lm

#** Clean **
CLEAN_OBJS = $(LIBXXX_OBJS)
CLEAN_LIBS = $(LIBXXX_A) $(LIBXXX_SO)

#** Target (CLEAN_BINS) **
CLEAN_BINS += \
						nlink_123 \
						nlink_456 \
						nlink_789 \
						proc_list_123 \
						proc_watch \
						queuex_123 \
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

#** Target (CONFS) **
CONFS = \
				$(wildcard conf/*.conf)

TO_FOLDER =

#** include *.mk **
-include define.mk

.DEFAULT_GOAL = all
.SUFFIXES: .c .o

.PHONY: all clean distclean install romfs
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
	$(PJ_SH_RM) Makefile.bak $(CLEAN_BINS) $(CLEAN_BINS:=.elf) $(CLEAN_BINS:=.gdb)
	$(PJ_SH_RM) .configured .patched $(addsuffix *, $(CLEAN_LIBS)) $(CLEAN_OBJS) $(CLEAN_OBJS:%.o=%.c.bak) $(CLEAN_OBJS:%.o=%.h.bak)
	$(PJ_SH_RM) util_expiration.h
	@for subbin in $(CLEAN_BINS); do \
		($(PJ_SH_RM) $(SDK_BIN_DIR)/$$subbin;); \
	done
	@for sublib in $(CLEAN_LIBS); do \
		($(PJ_SH_RM) $(SDK_LIB_DIR)/$$sublib*;); \
	done
	@for subheader in $(HEADER_FILES); do \
		($(PJ_SH_RM) $(SDK_INC_DIR)/$$subheader;); \
	done
	@for subshell in $(SHELL_SBINS); do \
		($(PJ_SH_RM) $(SDK_SBIN_DIR)/$$subshell;); \
	done
	@$(PJ_SH_RMDIR) build_xxx .meson_config build.meson meson_options.txt meson_public

distclean: clean

%.a: $(LIBXXX_OBJS)
	@echo 'Building lib (static): $@'
	$(AR) $(ARFLAGS) $@ $(LIBXXX_OBJS)
	@echo 'Finished building lib (static): $@'
	@echo ' '

%.so: $(LIBXXX_OBJS)
	@echo 'Building lib (shared): $@'
	$(CC) -shared $(LDFLAGS) -Wl,-soname,$@.$(VERSION_MAJOR) -o $@.$(VERSION_FULL) $(LIBXXX_OBJS)
	ln -sf $@.$(VERSION_FULL) $@.$(VERSION_MAJOR)
	ln -sf $@.$(VERSION_MAJOR) $@
	@echo 'Finished building lib (shared): $@'
	@echo ' '

install: all
	$(PJ_SH_MKDIR) $(SDK_BIN_DIR)
	@for subbin in $(CLEAN_BINS); do \
		$(PJ_SH_CP) $$subbin $(SDK_BIN_DIR); \
		$(STRIP) $(SDK_BIN_DIR)/`basename $$subbin`; \
	done
	$(PJ_SH_MKDIR) $(SDK_LIB_DIR)
	@for sublib in $(CLEAN_LIBS); do \
		$(PJ_SH_CP) $$sublib* $(SDK_LIB_DIR); \
		$(STRIP) $(SDK_LIB_DIR)/$$sublib.$(VERSION_FULL); \
	done
	$(PJ_SH_MKDIR) $(SDK_INC_DIR)
	@for subheader in $(HEADER_FILES); do \
		$(PJ_SH_CP) $$subheader $(SDK_INC_DIR); \
	done
	$(PJ_SH_MKDIR) $(SDK_SBIN_DIR)
	@for subshell in $(SHELL_SBINS); do \
		$(PJ_SH_CP) $$subshell $(SDK_SBIN_DIR); \
	done
	@for conf in $(CONFS); do \
		$(PJ_SH_MKDIR) $(SDK_IOT_DIR)/$(TO_FOLDER); \
		$(PJ_SH_CP) $$conf $(SDK_IOT_DIR)/$(TO_FOLDER); \
	done

romfs: install
ifneq ("$(HOMEX_ROOT_DIR)", "")
	$(PJ_SH_MKDIR) $(HOMEX_BIN_DIR)
	@for subbin in $(DUMMY_BINS); do \
		$(PJ_SH_CP) $$subbin $(HOMEX_BIN_DIR); \
		$(STRIP) $(HOMEX_BIN_DIR)/`basename $$subbin`; \
	done
	$(PJ_SH_MKDIR) $(HOMEX_LIB_DIR)
	@for sublib in $(CLEAN_LIBS); do \
		$(PJ_SH_CP) $$sublib* $(HOMEX_LIB_DIR); \
		$(STRIP) $(HOMEX_LIB_DIR)/$$sublib.$(VERSION_FULL); \
	done
	#$(PJ_SH_MKDIR) $(HOMEX_INC_DIR)
	#@for subheader in $(HEADER_FILES); do \
	#	$(PJ_SH_CP) $$subheader $(HOMEX_INC_DIR); \
	#done
	$(PJ_SH_MKDIR) $(HOMEX_SBIN_DIR)
	@for subshell in $(DUMMY_SBINS); do \
		$(PJ_SH_CP) $$subshell $(HOMEX_SBIN_DIR); \
	done
	@for conf in $(CONFS); do \
		$(PJ_SH_MKDIR) $(HOMEX_IOT_DIR)/$(TO_FOLDER); \
		$(PJ_SH_CP) $$conf $(HOMEX_IOT_DIR)/$(TO_FOLDER); \
	done
endif

