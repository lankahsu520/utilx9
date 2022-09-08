.DEFAULT_GOAL = all

.PHONY: meson meson_install meson_clean meson_distclean
.meson_config:
ifeq ("$(wildcard meson_public)","")
	ln -s $(PJ_MESON_BUILD_ROOT) meson_public
endif
	cp -av $(PJ_MESON_CROSS) ./build.meson \
	&& cp -av $(CONFIG_MESON) ./meson_options.txt \
	&& meson \
		--prefix $(SDK_ROOT_DIR) \
		--libdir $(SDK_LIB_DIR) \
		--pkg-config-path "$(PJ_PKG_CONFIG)" \
		--cross-file build.meson \
		build_xxx
	touch $@

meson: .meson_config
	cd build_xxx \
	&& ninja #-v

meson_install: meson
	cd build_xxx \
	&& ninja install

meson_clean:
	cd build_xxx \
	&& ninja clean

meson_distclean:
	[ -L meson_public ] && ($(PJ_SH_RMDIR) meson_public; ) || true
	[ -d ./subprojects ] && [ -f meson.build ] && (meson subprojects purge --confirm;) || true
	rm -rf build_xxx