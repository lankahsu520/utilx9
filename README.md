# Overview
utilx9 是一個集合常用的 Open-source 而後衍生出來的 library.

主要訴求是 -
  應用簡單化！
  強化常用、有用的功能！

大家都知道 Open-source 功能強大，貢獻非凡.提供前所未有的視野，讓開發者們省去大半的研究時間，開發更有效率？

經過多年的工作經驗，心想只是為了糊口飯吃，為什麼還要浪費在這些 Open-source 的文件裏打轉，於是一點一滴才整理出這些.


# Depend on
- ubuntu_ - https://github.com/lankahsu520/ubuntu_
- curl (PJ_HAS_CURL) - https://curl.haxx.se
- dbus (PJ_HAS_DBUS) - https://www.freedesktop.org/wiki/Software/dbus/
- fcgi2 (PJ_HAS_FASTCGI) - http://fastcgi-archives.github.io/fcgi2/doc/fcgi-devel-kit.htm
- jansson (PJ_HAS_JANSSON) - https://digip.org/jansson/
- json-c (PJ_HAS_JSONC) - https://github.com/json-c/json-c
- libnl-tiny (PJ_HAS_LIBNL_TINY) - https://git.openwrt.org/project/libnl-tiny.git
- libssh (PJ_HAS_LIBSSH) - http://www.libssh.org
- libubox (PJ_HAS_LIBUBOX) - https://openwrt.org/docs/techref/libubox
- libusb (PJ_HAS_LIBUSB) - https://github.com/libusb/libusb
- libuv (PJ_HAS_LIBUV) - https://github.com/libuv/libuv
- libwebsockets (PJ_HAS_LIBWEBSOCKETS) - https://libwebsockets.org
- libyuarel (PJ_HAS_LIBYUAREL) - https://github.com/jacketizer/libyuarel
- minixml (PJ_HAS_MXML)- https://www.msweet.org/mxml
- mosquitto (PJ_HAS_MOSQUITTO) - https://mosquitto.org
- mxml (PJ_HAS_MXML) - https://www.msweet.org/mxml/
- openssl (PJ_HAS_OPENSSL) - https://www.openssl.org
- ~~swconfig (PJ_HAS_SWCONFIG) - openwrt/package/network/config/swconfig~~
- ubus (PJ_HAS_UBUS) - https://openwrt.org/docs/techref/ubus
- uci (PJ_HAS_UCI) - https://openwrt.org/docs/techref/uci


# Current Status
因為這是多年工作下的成果，一定還有發展空間.如果有 bug 請多多包函.


# Build
   ```
$ . conf/config_customer
	My prefix is /work/codebase/xbox/xbox_ubuntu/install/ubuntu_/.
	Please replace the string.
$ make
   ```

# Example or Usage
- chainX_123 - socket example. use chainX_api.c.
- client_123 - socket client. use chainX_api.c.
- clist_123 - link list example. use clist_api.c , use contiki\core\lib\list.*.
- dbus_456 - dbus example.
- demo_000 - c template.
- demo_123 - a example.
- http_client_123 - http client example. use curl.
- json_123 - json example.
- led_123 - led controller example.
- lws_123 - a websocket example.
- mqtt_123 - a mqtt example.
- multicast_cli & multicast_srv - multicast example.
- ~~nlink_123 & nlink_456 - netlink example. got from internet.~~
- onvif_client_123 - onvif client example.
- ping_123 - ping example.
- proc_list_123 & proc_watch - a system and proc information example.
- sshX_123 - ssh example.
- statex_123 - state machine example. use statex_api.c.
- ~~swlink_123 - swconfig example. (depend on linux kernel)~~
- thread_123 - thread example.
- tty_123 - a tty example. use chainX_api.c.
- tunnel_123 - ssh tunnel example.
- ubox_123 - ubox example.
- ubus_123 - ubus example.
- uci_123 - uci example.
- usb_12 - usb example.
- util_123 - example.
- uv_000 - uv template.
- uv_123 - uv example.
- uv_spawn_123 - uv spawn example.
- wsdiscovery_123 - WS-Discovery example.


# License
utilx9 is under the New BSD License (BSD-3-Clause).


# Documentation
Run an example and read it.
