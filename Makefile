include $(CONFIG_CONFIG)

#** CFLAGS & LDFLAGS **
CFLAGS += $(CFLAGS_CUSTOMER)

CFLAGS += \
					-Wall -O2 \
					-I./ -I$(SDK_INC_DIR)
ifeq ("$(PJ_ARCH)", "x86")
CFLAGS += \
					-Wno-unused-value \
					-Wno-unused-result \
					-Wno-format-truncation
endif
LDFLAGS += \
					-L./ \
					-L$(SDK_LIB_DIR) \
					-Wl,-rpath -Wl,$(SDK_LIB_DIR)
ARFLAGS = rcs

#** LIBXXX_OBJS **
LIBXXX_OBJS += \
							statex_api.o \
							led_api.o \
							chainX_api.o \
							clist_api.o \
							proc_table_api.o \
							queue_api.o \
							multicast_api.o \
							thread_api.o \
							utilx9.o

#** LIBXXX_yes **
#LIBXXX_A = libutilx9.a
LIBXXX_SO = libutilx9.so
LIBXXXS_$(PJ_HAS_STATIC_LIB) += $(LIBXXX_A)
LIBXXXS_$(PJ_HAS_SHARE_LIB) += -lutilx9

#** HEADER_FILES **
HEADER_FILES = utilx9.h basic_def.h ubus_ex.h

LIBS_yes = $(LIBXXXS_yes)
-include ./library.mk

#** librarys **
LIBS += -lz
#-ldl -lpthread -lm 

#** Clean **
CLEAN_BINS = 
CLEAN_OBJS = $(LIBXXX_OBJS)
CLEAN_LIBS = $(LIBXXX_A) $(LIBXXX_SO)

#** Target (CLEAN_BINS) **
CLEAN_BINS += \
						statex_123 \
						chainX_123 \
						led_123 \
						nlink_123 \
						nlink_456 \
						demo_123 \
						demo_000

ifeq ("$(PJ_HAS_LIBUSB)", "yes")
CLEAN_BINS += \
						usb_123
endif

ifeq ("$(PJ_HAS_LIBUV)", "yes")
CLEAN_BINS += \
						uv_000 \
						uv_spawn_123 \
						uv_123
endif

ifeq ("$(PJ_HAS_UBUS)", "yes")
CLEAN_BINS += \
						ubus_123
endif

ifeq ("$(PJ_HAS_UCI)", "yes")
CLEAN_BINS += \
						uci_123
endif

ifeq ("$(PJ_HAS_SWCONFIG)", "yes")
CLEAN_BINS += 	\
						swlink_123
endif

#** Target (DUMMY_BINS) **
DUMMY_BINS = \
						util_123 \
						proc_watch

CLEAN_BINS += $(DUMMY_BINS)
CLEAN_OBJS += $(addsuffix .o, $(CLEAN_BINS))

include define.mk

.SUFFIXES:
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
	rm -f $(CLEAN_LIBS) $(CLEAN_OBJS)
	@for sublib in $(CLEAN_LIBS); do \
		(cd $(SDK_LIB_DIR); rm -f $$sublib;); \
	done
	@for subbin in $(CLEAN_BINS); do \
		(cd $(SDK_LIB_DIR); rm -f $$subbin;); \
	done
	rm -f $(CLEAN_OBJS:%.o=%.c.bak) $(CLEAN_OBJS:%.o=%.h.bak)
	rm -f util_expiration.h
	rm -rf conf
	rm -f .configured

distclean: clean

%.a: $(LIBXXX_OBJS)
	@echo 'Building lib (static): $@'
	$(AR) $(ARFLAGS) $@ $(LIBXXX_OBJS)
	@echo 'Finished building lib (static): $@'
	@echo ' '

%.so: $(LIBXXX_OBJS)
	@echo 'Building lib (shared): $@'
	$(CC) -shared -o $@ $(LIBXXX_OBJS)
	@echo 'Finished building lib (shared): $@'
	@echo ' '

install: all
	@for subbin in $(CLEAN_BINS); do \
		cp -avf $$subbin $(SDK_BIN_DIR); \
		$(STRIP) $(SDK_BIN_DIR)/$$subbin; \
	done

	@for sublib in $(CLEAN_LIBS); do \
		cp -avf $$sublib $(SDK_LIB_DIR); \
		$(STRIP) $(SDK_LIB_DIR)/$$sublib; \
	done

	@for subheader in $(HEADER_FILES); do \
		cp -avf $$subheader $(SDK_INC_DIR); \
	done

romfs: install
ifneq ("$(HOMEX_ROOT_DIR)", "")
	@for subbin in $(DUMMY_BINS); do \
		cp -avf $$subbin $(HOMEX_BIN_DIR); \
		$(STRIP) $(HOMEX_BIN_DIR)/$$subbin; \
	done

	@for sublib in $(CLEAN_LIBS); do \
		cp -avf $$sublib $(HOMEX_LIB_DIR); \
		$(STRIP) $(HOMEX_LIB_DIR)/$$sublib; \
	done

	#@for subheader in $(HEADER_FILES); do \
	#	cp -avf $$subheader $(HOMEX_INC_DIR); \
	#done
endif

expired:
	$(call generate_expiration, $(shell date -d "+4 years" "+%s"))
