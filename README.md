---------------------------------------
# Overview
	utilx9 是一個集合常用的 Open-source 而後衍生出來的 library。

	主要訴求是 -
		應用簡單化！
		強化常用、有用的功能！

	大家都知道 Open-source 功能強大，貢獻非凡。提供前所未有的視野，讓開發者們省去大半的研究時間，開發更有效率？

	經過多年的工作經驗，心想只是為了糊口飯吃，為什麼還要浪費在這些 Open-source 的文件裏打轉，於是一點一滴才整理出這些。


---------------------------------------
# Depend on
	openssl (PJ_HAS_OPENSSL) - https://www.openssl.org
	jansson (PJ_HAS_JANSSON) - https://digip.org/jansson/
	curl (PJ_HAS_CURL) - https://curl.haxx.se
	minixml (PJ_HAS_MXML)- https://www.msweet.org/mxml
	libssh (PJ_HAS_LIBSSH) - http://www.libssh.org
	swconfig (PJ_HAS_SWCONFIG) - openwrt/package/network/config/swconfig
	libuv (PJ_HAS_LIBUV) - https://github.com/libuv/libuv
	dbus (PJ_HAS_DBUS) - https://www.freedesktop.org/wiki/Software/dbus/
	ubus (PJ_HAS_UBUS) - https://openwrt.org/docs/techref/ubus
	libusb (PJ_HAS_LIBUSB) - https://github.com/libusb/libusb
	uci (PJ_HAS_UCI) - https://openwrt.org/docs/techref/uci
	libubox (PJ_HAS_LIBUBOX) - https://openwrt.org/docs/techref/libubox
	fcgi2 (PJ_HAS_FASTCGI) - http://fastcgi-archives.github.io/fcgi2/doc/fcgi-devel-kit.htm
	libyuarel (PJ_HAS_LIBYUAREL) - https://github.com/jacketizer/libyuarel
	libwebsockets (PJ_HAS_LIBWEBSOCKETS) - https://libwebsockets.org

---------------------------------------
# Current Status
	因為這是多年工作下的成果，一定還有發展空間。如果有 bug 請多多包函。


---------------------------------------
# Build
> $ make

---------------------------------------
# Example or Usage


---------------------------------------
# License
	utilx9 is under the New BSD License (BSD-3-Clause)。


---------------------------------------
# Documentation
	簡單的範例程式就是最好的說明。
	chainX_123 - 常用 socket 範例程式。引用 chainX_api.c。
	client_123 - socket client 範例程式。引用 chainX_api.c。
	clist_123 - 簡單的link list。引用 clist_api.c 源自於 contiki\core\lib\list.*。
	dbus_456 - dbus 範例程式。
	demo_000 - 一個程式範本。讀取參數和抓取 signal 。
	demo_123 - 範例程式。
	http_client_123 - http client 範例程式。引用 curl。
	json_123 - json 範例程式。
	led_123 - led 操作的範例程式。
	multicast_cli & multicast_cli - multicast 範例程式。
	nlink_123 & nlink_456 - netlink 範例程式。非自製，源自於網路。
	onvif_client_123 - onvif client 範例程式。
	ping_123 - ping 範例程式。
	proc_list_123 & proc_watch - 抓取 /proc 相關訊息的範例程式。
	sshX_123 - ssh 範例程式。
	statex_123 - state machine 範例程式。引用 statex_api.c。
	swlink_123 - swconfig 範例程式。
	thread_123 - thread 範例程式。
	tty_123 - 操作 tty 的範例程式。引用 chainX_api.c。
	tunnel_123 - ssh tunnel 範例程式。
	ubox_123 - ubox 範例程式。
	ubus_123 - ubus 範例程式。
	uci_123 - uci 範例程式。
	usb_12 - usb 範例程式。
	util_123 - 範例程式。
	uv_000 - uv 程式範本。
	uv_123 - uv 範例程式。
