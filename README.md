# 1. Overview
utilx9 是一個集合常用的 Open-source 而後衍生出來的 library.

主要訴求是 -
  應用簡單化！
  強化常用、有用的功能！

大家都知道 Open-source 功能強大，貢獻非凡！提供前所未有的視野，讓開發者們省去大半的研究時間，開發更有效率嗎？也因此我們不是要深究 Open-source 是如此高深，而是要知悉如何應用。

經過多年的工作經驗，心想只是為了糊口飯吃，為什麼還要浪費在這些 Open-source 的文件裏打轉，於是一點一滴才整理出這些.

It is hard to read any usages of Open-source. They are lengthy. 
utilx9 is the utility api. 
Here giving small api packages and easily to use. We can also get  the ideals from the demo programs

# 2. Depend on
- curl (PJ_HAS_CURL) - https://curl.haxx.se
- list (UTIL_EX_CLIST) & Crc16 - http://www.contiki-os.org
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
- libyuarel (PJ_HAS_LIBYUAREL / UTIL_EX_YUAREL) - https://github.com/jacketizer/libyuarel
- mosquitto (PJ_HAS_MOSQUITTO) - https://mosquitto.org
- mxml (PJ_HAS_MXML / UTIL_EX_MXML) - https://www.msweet.org/mxml/ (need to patch, please check patches/mxml-2.11)
- openssl (PJ_HAS_OPENSSL) - https://www.openssl.org
- ~~swconfig (PJ_HAS_SWCONFIG) - openwrt/package/network/config/swconfig~~
- ubus (PJ_HAS_UBUS) - https://openwrt.org/docs/techref/ubus
- uci (PJ_HAS_UCI) - https://openwrt.org/docs/techref/uci


# 3. Current Status
因為這是多年工作下的成果，一定還有發展空間.如果有 bug 請多多包函.


# 4. Build
```bash
$ . confs/github.conf
$ . confs/customer2def.sh
# to create
# include/customer_def.h
# include/config_customer
# include/config_customer.export
# include/meson_options.txt
$ make
```
## 4.1. environment (without libmxml and libyuarel)
```bash
$ sudo apt-get --yes install libjansson-dev
$ sudo apt-get --yes install libuv1-dev

$ sudo apt-get --yes install libdbus-1-dev
#or
$ sudo apt-get --yes install libdbus-dev

$ cd /usr/include
$ sudo ln dbus-1.0/dbus/ -s dbus
$ cd /usr/include/dbus
$ sudo cp /usr/lib/x86_64-linux-gnu/dbus-1.0/include/dbus/dbus-arch-deps.h ./

$ sudo apt-get --yes install libwebsockets-dev

$ sudo apt-get --yes install libusb-dev
$ sudo apt-get --yes install libusb-1.0-0-dev

$ sudo apt-get --yes install libmosquitto-dev
$ sudo apt-get --yes install libjson-c-dev

```

## 4.2. libmxml

```bash
$ vi conf/github.conf
export PJ_HAS_MXML=yes

$ vi utilx9.h
#define UTIL_EX_MXML

#please patch mxml-2.11 with patches/mxml-2.11
```

## 4.3. libyuarel

```bash
$ vi conf/github.conf
export PJ_HAS_LIBYUAREL=yes

$ vi utilx9.h
#define UTIL_EX_YUAREL

```

# 5. Example or Usage

- chainX_123 - socket example. use chainX_api.c.
- client_123 - socket client. use chainX_api.c.
- clist_123 - link list example. use clist_api.c , use contiki\core\lib\list.*.
- cronx_123 - parse crontab string ("minute" "hour" "day of month" "month" "day of week" "year, 2020+"), similar to crontab, to use cronx_api.c
- dbusx_456 - dbus example.
- demo_000 - c template.
- demo_123 - a example.
- http_client_123 - http client example. use curl.
- jqx - it is similar to jq. jqx only support reads from pipe. 
- json_123 - json example.
- led_123 - led controller example.
- lws_123 - a websocket example.
- mqtt_123 - a mqtt example.
- multicast_cli & multicast_srv - multicast example.
- ~~nlink_123 & nlink_456 - netlink example. got from internet.~~
- nlink_789 netlink example. use chainX_api.c (CHAINX_MODE_ID_NETLINK).
- onvif_client_123 - onvif client example.
- ping_123 - ping example.
- proc_list_123 & proc_watch - a system and proc information example.
- queuex_123 - a queue example.
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
- ~~gbusx_123 - a  example. use gbusx_api.c.~~


# 6. License
utilx9 is under the New BSD License (BSD-3-Clause).


# 7. Documentation
Run an example and read it.
