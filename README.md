# 1. Overview
> utilx9 是一個集合常用的 Open-source 而後衍生出來的 library.
>
> 主要訴求是 -
>   應用簡單化！
>   強化常用、有用的功能！
>
> 大家都知道 Open-source 功能強大，貢獻非凡！提供前所未有的視野，讓開發者們省去大半的研究時間，開發更有效率嗎？也因此我們不是要深究 Open-source 是如此高深，而是要知悉如何應用。
>
> 經過多年的工作經驗，心想只是為了糊口飯吃，為什麼還要浪費在這些 Open-source 的文件裏打轉，於是一點一滴才整理出這些.
>
> It is hard to read any usages of Open-source. They are lengthy. 
> utilx9 is the utility api. 
> Here giving small api packages and easily to use. We can also get  the ideals from the demo programs

# 2. Depend on

## 2.1. Open-source

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

- libyuarel (PJ_HAS_LIBYUAREL / UTIL_EX_YUAREL) - https://github.com/jacketizer/libyuarel

- mosquitto (PJ_HAS_MOSQUITTO) - https://mosquitto.org

- mxml (PJ_HAS_MXML / UTIL_EX_MXML) - https://www.msweet.org/mxml/ (need to patch, please check patches/mxml-2.11)

- openssl (PJ_HAS_OPENSSL) - https://www.openssl.org

- ~~swconfig (PJ_HAS_SWCONFIG) - openwrt/package/network/config/swconfig~~

- ubus (PJ_HAS_UBUS) - https://openwrt.org/docs/techref/ubus

- uci (PJ_HAS_UCI) - https://openwrt.org/docs/techref/uci

## 2.2. Internet Notes

- internet-collect.c - [Hex Encode and Decode in C](https://nachtimwald.com/2017/09/24/hex-encode-and-decode-in-c/)
- internet-collect.c - [Linux C语言实现urlencode和urldecode](https://ivanzz1001.github.io/records/post/cplusplus/2018/03/13/cpluscplus_urlencode)
- internet-collect.c - [Howto base64 encode and decode with C and OpenSSL](https://devenix.wordpress.com/2008/01/18/howto-base64-encode-and-decode-with-c-and-openssl-2/)
- clist_api.c - http://www.contiki-os.org
- crc16.c - http://www.contiki-os.org
- crc32alg.c - CRC32 code derived from work by Gary S. Brown.
- chainX_api.c - [Linux RS-232 程式設計](http://shyuanliang.blogspot.com/2010/09/linux-rs-232.html)
- lws_123.c - [simple-libwebsockets-example](https://github.com/iamscottmoyers/simple-libwebsockets-example)
- lws_api.c - [multithread call lws_callback_on_writable to send data ASAP](https://codesti.com/issue/warmcat/libwebsockets/2358)
- nlink_123.c - [Monitoring Linux networking state using netlink](https://olegkutkov.me/2018/02/14/monitoring-linux-networking-state-using-netlink/)
- nlink_456.c - [Port status polling via swconfig kernel module](http://centaur.sch.bme.hu/~leait/projects/openwrt/)
- utilx9.h - [解读 /proc/$PID/status 中各种参数](https://my.oschina.net/aiguozhe/blog/125477)
- utilx9.h - [RTP Library in C](https://sourceforge.net/projects/rtp-lib/)

# 3. Current Status

> 因為這是多年工作下的成果，一定還有發展空間.如果有 bug 請多多包函.


# 4. Build
```bash
$ . confs/github.conf
#$ . confs/sh/customer2def.sh
# to create
# include/customer_def.h
# include/config_customer
# include/config_customer.export
# include/meson_options.txt
$ make
$ make install
# will be installed ${SDK_ROOT_DIR} - ./install/github_
$ make romfs
# will be installed ${HOMEX_ROOT_DIR} - ./install/github_rootfs
$ make target_install 
# will be installed ${PJ_INSTALL_TARGET} - /work/rootfs

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

```bash
$ ./clist_123
[30864/30864] main:53 - (num: 8)
[30864/30864] main:53 - (num: 4)
[30864/30864] main:53 - (num: 0)
[30864/30864] main:53 - (num: 1)
[30864/30864] main:53 - (num: 2)
[30864/30864] main:53 - (num: 3)
[30864/30864] main:53 - (num: 5)
[30864/30864] main:53 - (num: 6)
[30864/30864] main:53 - (num: 7)
[30864/30864] main:53 - (num: 9)
```

- cronx_123 - parse crontab string ("minute" "hour" "day of month" "month" "day of week" "year, 2020+"), similar to crontab, to use cronx_api.c

```bash
$ cronx_123 -a "*/1 * * * * 2022 " -d 2
[30859/30859] app_loop:164 - Run loop ... (clock_alarm: [*/1 * * * * 2022 ])
[30859/30859] timer_1sec_loop:51 - (21:31:58)
[30859/30859] timer_1sec_loop:51 - (21:31:59)
[30859/30859] timer_1sec_loop:51 - (21:32:00)
[30859/30859] cronx_validate:98 - (cron_txt: [*/1 * * * * 2022 ], [32 21 26 10 6 2022])
[30859/30859] cronx_validate:218 - Got !!! (cron_txt: [*/1 * * * * 2022 ], [32 21 26 10 6 2], fit: 6)
[30859/30859] timer_1sec_loop:65 - Alarm !!! (*/1 * * * * 2022 )
[30859/30859] timer_1sec_loop:51 - (21:32:01)
```

- dbusx_456 - dbus example.

```bash
$ ./dbusx_456 -s &
[30642/30643] dbusx_thread_handler:516 - dbus listen ...
$ ./dbusx_456 -e 123
[30644/30644] app_loop:124 - (retStr: 123)
[30644/30644] main:244 - Bye-Bye !!!
```

- demo_000 - c template.

```bash
$ ./demo_000
[30636/30636] app_loop:46 - (pid: 30636)
[30636/30636] app_loop:50 - (cksum: 1398)
[30636/30636] app_loop:52 - (cksum: 22044)
[30636/30636] main:156 - Bye-Bye !!!
```
- demo_123 - a example.
```bash
$ ./demo_123
[30635/30635] main:41 - (1<<3: 0x00000008, 1<<14: 0x00004000, 1<<15: 0x00008000, 1<<16: 0x00010000, 1<<17: 0x00020000)
[30635/30635] main:44 - (hello_trim: Hello World !!!    )
[30635/30635] main:47 - (hello_trim: Hello World !!!)
[30635/30635] main:55 - SAFE_STRCAT_EX - lankahsu520/1234

[30635/30635] main:152 - (mode: 4)
[30635/30635] main:153 - (curl: 8)
[30635/30635] main:154 - (url: 2048)
[30635/30635] main:155 - (port: 4)
[30635/30635] main:156 - (user: 8)
[30635/30635] main:157 - (log: 3072)
[30635/30635] main:159 - ------------
[30635/30635] main:160 - (res_size: 8)
[30635/30635] main:161 - (response: 8)
[30635/30635] main:162 - (method: 4)
[30635/30635] main:163 - (curl_slist: 8)
[30635/30635] main:165 - ------------
[30635/30635] main:166 - (max_size: 8)
[30635/30635] main:167 - (filename: 1024)
[30635/30635] main:168 - (fp: 8)
[30635/30635] main:169 - (qbuf: 24)
[30635/30635] main:170 - (boundary: 32)
[30635/30635] main:171 - (state: 4)
[30635/30635] main:173 - ------------
[30635/30635] main:175 - (track: 64)
[30635/30635] main:176 - (track[0]: 32)
```
- http_client_123 - http client example. use curl.
- jqx - it is similar to jq. jqx only support reads from pipe. 

```bash
# please download Music.json (https://github.com/lankahsu520/HelperX/blob/master/AWS/Music.json)
$ cat Music.json | ./jqx .Items[3].Sponsor.L[].S
"dog"
"cat"
"mouse"
"stoat"
"snake"

```

- json_123 - json example.

```bash
./json_123
[30867/30867] main:26 - enter
[30867/30867] uuid_test:21 - (guid: 72594E89-CFC6-4B86-b25F-AAE48DDCF1BD)
[30867/30867] main:59 - (jdemo1: 0x55d4cd20c7a0, refcount: 1)
[30867/30867] main:61 - (jdemo2: 0x55d4cd20c810, refcount: 1)
[30867/30867] main:62 - (jdemo1: 0x55d4cd20c7a0, refcount: 94372462784528)
[30867/30867] json_dump_simple:22 - (jroot: {"demo":"HelloWorld 1 !!!","j1":{"j2":{"j3":{"logo":"helloworld!!!"}}},"jA":[{"name":"A1","val":1},{"name":"A2","val":2},{"name":"A3","val":3}]})
[30867/30867] main:69 - (idx: 2)
[30867/30867] main:79 - (logo: helloworld!!!)
[30867/30867] json_dump_simple:26 - (Not Found - j1/j2/j4: (nil))
[30867/30867] json_dump_simple:22 - (APPEND - j1/j2/j4: {})
[30867/30867] json_dump_simple:26 - (DEL - j1/j2/j3: (nil))
[30867/30867] json_dump_simple:22 - (j1/j2: {"j4":{}})
[30867/30867] main:140 - (sunrise: 3:22:56 AM)
[30867/30867] main:141 - (sunset: 5:10:20 PM)
[30867/30867] main:142 - (utc: 1652853043)
[30867/30867] main:160 - (cJson: {"sunrise":"3:22:56 AM","sunset":"5:10:20 PM","time_utc":1652853043})

```

- led_123 - led controller example.
- lws_123 - a websocket example.
- mqtt_123 - a mqtt example.
- multicast_cli & multicast_srv - multicast example.
- ~~nlink_123 & nlink_456 - netlink example. got from internet.~~
- nlink_789 netlink example. use chainX_api.c (CHAINX_MODE_ID_NETLINK).
- onvif_client_123 - onvif client example.
- ping_123 - ping example.

```bash
$ ./ping_123 -i 1 -c 3 google.com
[35736/35736] chainX_ping:3691 - sockfd error !!! (errno: 1 Operation not permitted)
[35736/35736] main:109 - (count: 0/3)

$ sudo ./ping_123 -i 1 -c 3 google.com
[sudo] password for lanka:
[35735/35735] chainX_icmp:3560 - PING google.com (): 64 bytes of data
[35735/35735] chainX_icmp:3633 - 64 bytes from tsa01s11-in-f14.1e100.net (): icmp_seq=1 ttl=64 time=13.98 ms
[35735/35735] chainX_icmp:3633 - 64 bytes from tsa01s11-in-f14.1e100.net (): icmp_seq=2 ttl=64 time=9.32 ms
[35735/35735] chainX_icmp:3633 - 64 bytes from tsa01s11-in-f14.1e100.net (): icmp_seq=3 ttl=64 time=9.45 ms
[35735/35735] chainX_icmp:3668 - --- google.com ping statistics ---
[35735/35735] chainX_icmp:3669 - 3 packets transmitted, 3 received, 0% packet loss, time: 33 ms.
[35735/35735] main:109 - (count: 3/3)
```

- proc_list_123 & proc_watch - a system and proc information example.
- queuex_123 - a queue example.

```bash
$ ./queuex_123
[12746/12747] queue_pop:325 - (name: test, length: 0/30, ishold: 0, isloop: 1)
[12746/12746] queuex_push:287 - (name: test, length: 0/30, ishold: 0, isloop: 1)
[12746/12746] queuex_push:287 - (name: test, length: 1/30, ishold: 0, isloop: 1)
[12746/12746] queuex_push:287 - (name: test, length: 2/30, ishold: 0, isloop: 1)
[12746/12746] queuex_push:287 - (name: test, length: 3/30, ishold: 0, isloop: 1)
[12746/12746] queuex_push:287 - (name: test, length: 4/30, ishold: 0, isloop: 1)
[12746/12747] queue_pop:325 - (name: test, length: 5/30, ishold: 0, isloop: 1)
[12746/12747] test_q_exec_cb:38 - (data_pop->idx: 0)
[12746/12747] queue_pop:325 - (name: test, length: 4/30, ishold: 0, isloop: 1)
[12746/12747] test_q_exec_cb:38 - (data_pop->idx: 1)
[12746/12747] queue_pop:325 - (name: test, length: 3/30, ishold: 0, isloop: 1)
[12746/12747] test_q_exec_cb:38 - (data_pop->idx: 2)
[12746/12747] queue_pop:325 - (name: test, length: 2/30, ishold: 0, isloop: 1)
[12746/12747] test_q_exec_cb:38 - (data_pop->idx: 3)
[12746/12747] queue_pop:325 - (name: test, length: 1/30, ishold: 0, isloop: 1)
[12746/12747] test_q_exec_cb:38 - (data_pop->idx: 4)
[12746/12747] queue_pop:325 - (name: test, length: 0/30, ishold: 0, isloop: 1)
```

- sshX_123 - ssh example.
- statex_123 - state machine example. use statex_api.c.
- ~~swlink_123 - swconfig example. (depend on linux kernel)~~
- thread_123 - thread example.

```bash
$ ./thread_123
[16594/16595] thread_handler:27 - (count: 0)
[16594/16595] thread_handler:33 - (name: thread_A, count: 1)
[16594/16595] thread_handler:33 - (name: thread_A, count: 2)
[16594/16595] thread_handler:36 - wait 3 seconds ...
[16594/16596] thread_handler:27 - (count: 0)
[16594/16596] thread_handler:33 - (name: thread_B, count: 1)
[16594/16596] thread_handler:33 - (name: thread_B, count: 2)
[16594/16596] thread_handler:36 - wait 3 seconds ...
[16594/16595] thread_handler:33 - (name: thread_A, count: 3)
[16594/16595] thread_handler:33 - (name: thread_A, count: 4)
[16594/16595] thread_handler:33 - (name: thread_A, count: 5)
[16594/16595] thread_handler:36 - wait 3 seconds ...
[16594/16596] thread_handler:33 - (name: thread_B, count: 3)
[16594/16596] thread_handler:33 - (name: thread_B, count: 4)
[16594/16596] thread_handler:33 - (name: thread_B, count: 5)
[16594/16596] thread_handler:36 - wait 3 seconds ...
```

- tty_123 - a tty example. use chainX_api.c.
- tunnel_123 - ssh tunnel example.
- ubox_123 - ubox example.
- ubus_123 - ubus example.
- uci_123 - uci example.
- usb_123 - usb example.
- util_123 - example.
- uv_000 - uv template.

```bash
$ ./uv_000
[20044/20044] timer_1sec_loop:37 - kick async every 1 second.
[20044/20044] async_loop:79 - __________ Enter __________
[20044/20044] timer_1sec_loop:37 - kick async every 1 second.
[20044/20044] async_loop:79 - __________ Enter __________
[20044/20044] timer_1sec_loop:37 - kick async every 1 second.
[20044/20044] async_loop:79 - __________ Enter __________
[20044/20044] timer_1sec_loop:37 - kick async every 1 second.
[20044/20044] async_loop:79 - __________ Enter __________
```

- uv_123 - uv example.

```bash
$ ./uv_123
[30884/30885] queue_work_handler:114 - (id: 2, count: 1)
[30884/30888] queue_work_handler:114 - (id: 1, count: 1)
[30884/30887] queue_work_handler:114 - (id: 3, count: 1)
[30884/30886] queue_work_handler:114 - (id: 4, count: 1)
[30884/30884] timer_1_loop:44 - (count: 1)
[30884/30884] timer_1_loop:50 - Bye-Bye !!! (uv_123)
[30884/30884] timer_2_loop:58 - (count: 1)
[30884/30884] timer_2_loop:63 - Bye-Bye !!! (uv_123)
[30884/30886] queue_work_handler:114 - (id: 5, count: 1)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 4, status: 0)
[30884/30887] queue_work_handler:114 - (id: 6, count: 1)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 3, status: 0)
[30884/30885] queue_work_handler:114 - (id: 7, count: 1)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 2, status: 0)
[30884/30888] queue_work_handler:114 - (id: 8, count: 1)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 1, status: 0)
[30884/30887] queue_work_handler:114 - (id: 9, count: 1)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 6, status: 0)
[30884/30886] queue_work_handler:114 - (id: 10, count: 1)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 5, status: 0)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 8, status: 0)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 7, status: 0)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 10, status: 0)
[30884/30884] queue_work_finisher:104 - Bye-Bye !!! (uv_123, id: 9, status: 0)
```

- uv_spawn_123 - uv spawn example.
- wsdiscovery_123 - WS-Discovery example.
- ~~gbusx_123 - a  example. use gbusx_api.c.~~


# 6. License
> utilx9 is under the New BSD License (BSD-3-Clause).


# 7. Documentation
> Run an example and read it.
