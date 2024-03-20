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

- [curl](https://curl.haxx.se) (PJ_HAS_CURL)

- [dbus](https://www.freedesktop.org/wiki/Software/dbus/) (PJ_HAS_DBUS)

- [fcgi2](http://fastcgi-archives.github.io/fcgi2/doc/fcgi-devel-kit.htm) (PJ_HAS_FASTCGI)

- [jansson](https://github.com/akheron/jansson) (PJ_HAS_JANSSON)

- [json-c](https://github.com/json-c/json-c) (PJ_HAS_JSONC)

- [libbacktrace](https://github.com/ianlancetaylor/libbacktrace) (PJ_HAS_LIBBACKTRACE)

- [libnl-tiny](https://git.openwrt.org/project/libnl-tiny.git) (PJ_HAS_LIBNL_TINY)

- [libssh](http://www.libssh.org) (PJ_HAS_LIBSSH)

- [libubox](https://openwrt.org/docs/techref/libubox) (PJ_HAS_LIBUBOX)

- [libusb](https://github.com/libusb/libusb) (PJ_HAS_LIBUSB)

- [libuv](https://github.com/libuv/libuv) (PJ_HAS_LIBUV) 

- [libwebsockets](https://libwebsockets.org) (PJ_HAS_LIBWEBSOCKETS)

- [libyuarel](https://github.com/jacketizer/libyuarel) (PJ_HAS_LIBYUAREL / UTIL_EX_YUAREL)

- [mosquitto](https://mosquitto.org) (PJ_HAS_MOSQUITTO)

- [mxml](https://www.msweet.org/mxml/) (PJ_HAS_MXML / UTIL_EX_MXML)
> (need to patch, please check patches/mxml-2.11)

- [openssl](https://www.openssl.org) (PJ_HAS_OPENSSL)

- ~~swconfig (PJ_HAS_SWCONFIG) - openwrt/package/network/config/swconfig~~

- [ubus](https://openwrt.org/docs/techref/ubus) (PJ_HAS_UBUS)

- [uci](https://openwrt.org/docs/techref/uci) (PJ_HAS_UCI)

## 2.2. Internet Notes

- internet-collect.c - [Hex Encode and Decode in C](https://nachtimwald.com/2017/09/24/hex-encode-and-decode-in-c/)
- internet-collect.c - [Linux C语言实现urlencode和urldecode](https://ivanzz1001.github.io/records/post/cplusplus/2018/03/13/cpluscplus_urlencode)
- internet-collect.c - [Howto base64 encode and decode with C and OpenSSL](https://devenix.wordpress.com/2008/01/18/howto-base64-encode-and-decode-with-c-and-openssl-2/)
- internet-collect.c - [34.1 Backtraces](https://www.gnu.org/software/libc/manual/html_node/Backtraces.html)
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
$ . confs/simple_x86.conf
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

## 4.2. Other Libraries

#### A. libmxml

```bash
$ vi conf/simple_x86.conf
export PJ_HAS_MXML=yes

$ vi utilx9.h
#define UTIL_EX_MXML

#please patch mxml-2.11 with patches/mxml-2.11
```

#### B. libyuarel

```bash
$ vi conf/simple_x86.conf
export PJ_HAS_LIBYUAREL=yes

$ vi utilx9.h
#define UTIL_EX_YUAREL
```

#### C. libbacktrace

```bash
$ vi conf/simple_x86.conf
export PJ_HAS_LIBBACKTRACE=yes

$ vi utilx9.h
#define UTIL_EX_BACKTRACE
```

# 5. Example or Usage

#### - backtrace_123 - backtrace example.

```bash
$ ./backtrace_123
*** stack smashing detected ***: terminated
[20143/20143] app_signal_handler:88 - (signum: 6)
[20143/20143] backtrace_alert:373 - ===== Obtained 10 stack frames =====
/work/codebase/lankahsu520/utilx9/libutilx9.so.3(backtrace_alert+0x2e) [0x7f24e60030ce]
/lib/x86_64-linux-gnu/libc.so.6(+0x43090) [0x7f24e5c88090]
/lib/x86_64-linux-gnu/libc.so.6(gsignal+0xcb) [0x7f24e5c8800b]
/lib/x86_64-linux-gnu/libc.so.6(abort+0x12b) [0x7f24e5c67859]
/lib/x86_64-linux-gnu/libc.so.6(+0x8d26e) [0x7f24e5cd226e]
/lib/x86_64-linux-gnu/libc.so.6(__fortify_fail+0x2a) [0x7f24e5d74cda]
/lib/x86_64-linux-gnu/libc.so.6(+0x12fca6) [0x7f24e5d74ca6]
./backtrace_123(+0x16a8) [0x5562fcd6e6a8]
./backtrace_123(+0x12e5) [0x5562fcd6e2e5]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7f24e5c69083]
[20143/20143] backtrace_alert:380 - ====================================
Aborted (core dumped)

$ addr2line -Cfie backtrace_123 +0x16a8
function_deep_2
/work/codebase/lankahsu520/utilx9/backtrace_123.c:62

$ addr2line -Cfie backtrace_123 +0x12e5
main
/work/codebase/lankahsu520/utilx9/backtrace_123.c:187
```

#### - backtrace_456 - libbacktrace example.

>export PJ_HAS_LIBBACKTRACE=yes, use backtrace_api.c.

```bash
$ ./backtrace_456
*** stack smashing detected ***: terminated
[37049/37049] app_signal_handler:88 - (signum: 6)
0x7ff0d25ee7b0 backtraceX_alert
        /work/codebase/lankahsu520/utilx9/backtrace_api.c:69
0x7ff0d224d08f ???
        /build/glibc-wuryBv/glibc-2.31/signal/../sysdeps/unix/sysv/linux/x86_64/sigaction.c:0
0x7ff0d224d00b __GI_raise
        ../sysdeps/unix/sysv/linux/raise.c:51
0x7ff0d222c858 __GI_abort
        /build/glibc-wuryBv/glibc-2.31/stdlib/abort.c:79
0x7ff0d229726d __libc_message
        ../sysdeps/posix/libc_fatal.c:155
0x7ff0d2339cd9 __GI___fortify_fail
        /build/glibc-wuryBv/glibc-2.31/debug/fortify_fail.c:26
0x7ff0d2339ca5 __stack_chk_fail
        /build/glibc-wuryBv/glibc-2.31/debug/stack_chk_fail.c:24
0x55d40d6ed6c7 function_deep_2
        /work/codebase/lankahsu520/utilx9/backtrace_456.c:62
0x55d40d6ed30e app_loop
        /work/codebase/lankahsu520/utilx9/backtrace_456.c:71
0x55d40d6ed30e main
        /work/codebase/lankahsu520/utilx9/backtrace_456.c:187
0x7ff0d222e082 __libc_start_main
        ../csu/libc-start.c:308
0x55d40d6ed3fd ???
        ???:0
0xffffffffffffffff ???
        ???:0
7ff0d224d08f ?? ??:0
7ff0d224d00b __GI_raise ../sysdeps/unix/sysv/linux/raise.c:51
7ff0d222c858 __GI_abort /build/glibc-wuryBv/glibc-2.31/stdlib/abort.c:79
7ff0d229726d __libc_message ../sysdeps/posix/libc_fatal.c:155
7ff0d2339cd9 __GI___fortify_fail /build/glibc-wuryBv/glibc-2.31/debug/fortify_fail.c:26
7ff0d2339ca5 __stack_chk_fail /build/glibc-wuryBv/glibc-2.31/debug/stack_chk_fail.c:24
55d40d6ed6c7 function_deep_2 /work/codebase/lankahsu520/utilx9/backtrace_456.c:62
55d40d6ed30e app_loop /work/codebase/lankahsu520/utilx9/backtrace_456.c:71
55d40d6ed30e main /work/codebase/lankahsu520/utilx9/backtrace_456.c:187
7ff0d222e082 __libc_start_main ../csu/libc-start.c:308
55d40d6ed3fd _start ??:0
ffffffffffffffff ?? ??:0
Aborted (core dumped)
```

#### - chainX_123 - socket example.

> use chainX_api.c.

#### - client_123 - socket client.
> use chainX_api.c.
```bash
$ ./chainX_123
[40677/40677] main:131 - dns: 127.0.0.53
[40677/40677] chainX_if_list:364 - (name: lo, flags: 0x10049, family: 2, host: 127.0.0.1, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s3, flags: 0x11043, family: 2, host: 10.0.2.15, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s8, flags: 0x11043, family: 2, host: 192.168.50.52, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s9, flags: 0x11043, family: 2, host: 192.168.56.104, netmask: )
[40677/40677] chainX_if_list:364 - (name: docker0, flags: 0x1003, family: 2, host: 172.17.0.1, netmask: )
[40677/40677] chainX_if_list:364 - (name: lo, flags: 0x10049, family: 10, host: ::1, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s3, flags: 0x11043, family: 10, host: fe80::7549:bd5f:d0ed:32cf%enp0s3, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s8, flags: 0x11043, family: 10, host: fd69:1ac8:5719:2e98:ca8d:19d4:cc66:458f, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s8, flags: 0x11043, family: 10, host: fd69:1ac8:5719:2e98:634d:a07f:2840:758d, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s8, flags: 0x11043, family: 10, host: fe80::d49:8acb:9f1b:c4cf%enp0s8, netmask: )
[40677/40677] chainX_if_list:364 - (name: enp0s9, flags: 0x11043, family: 10, host: fe80::e6d1:c758:6c5c:4cbd%enp0s9, netmask: )

[40677/40677] main:145 - **************************************************
[40677/40677] main:146 - ** enp0s3 **
[40677/40677] main:150 - ip: 10.0.2.15
[40677/40677] main:154 - netmask: 255.255.255.0
[40677/40677] main:158 - broadcast: 10.0.2.255
[40677/40677] main:162 - gateway: 10.0.2.2
[40677/40677] main:166 - ethmac: 08:00:27:33:73:52
[40677/40677] main:169 - ethmac: 080027337352
[40677/40677] main:174 - **************************************************
[40677/40677] main:175 - ** ra0 **
[40677/40677] main:179 - ip:
[40677/40677] main:183 - netmask:
[40677/40677] main:187 - broadcast:
[40677/40677] main:191 - gateway:
[40677/40677] main:195 - ethmac:
[40677/40677] main:198 - ethmac:
[40677/40677] main:202 - ssid:
```

#### - clist_123 - link list example.
> use clist_api.c , use contiki\core\lib\list.*.

```bash
$ ./clist_123
[8338/8338] main:42 - clist_add ~~~ (num: 0)
[8338/8338] main:47 - clist_push ~~~ (num: 1)
[8338/8338] main:47 - clist_push ~~~ (num: 2)
[8338/8338] main:47 - clist_push ~~~ (num: 3)
[8338/8338] main:42 - clist_add ~~~ (num: 4)
[8338/8338] main:47 - clist_push ~~~ (num: 5)
[8338/8338] main:47 - clist_push ~~~ (num: 6)
[8338/8338] main:47 - clist_push ~~~ (num: 7)
[8338/8338] main:42 - clist_add ~~~ (num: 8)
[8338/8338] main:47 - clist_push ~~~ (num: 9)
[8338/8338] main:55 - clist_pop ~~~ (num: 8)
[8338/8338] main:55 - clist_pop ~~~ (num: 4)
[8338/8338] main:55 - clist_pop ~~~ (num: 0)
[8338/8338] main:55 - clist_pop ~~~ (num: 1)
[8338/8338] main:55 - clist_pop ~~~ (num: 2)
[8338/8338] main:55 - clist_pop ~~~ (num: 3)
[8338/8338] main:55 - clist_pop ~~~ (num: 5)
[8338/8338] main:55 - clist_pop ~~~ (num: 6)
[8338/8338] main:55 - clist_pop ~~~ (num: 7)
[8338/8338] main:55 - clist_pop ~~~ (num: 9)
```

#### - cronx_123 - crontab example.

> parse crontab string ("minute" "hour" "day of month" "month" "day of week" "year, 2020+"), similar to crontab, to use cronx_api.c

```bash
$ ./cronx_123 -a "*/1 * * * * 2024 " -d 3
[8985/8985] app_loop:164 - Run loop ... (clock_alarm: [*/1 * * * * 2024 ])
[8985/8985] timer_1sec_loop:51 - (09:30:56)
[8985/8985] timer_1sec_loop:51 - (09:30:57)
[8985/8985] timer_1sec_loop:51 - (09:30:58)
[8985/8985] timer_1sec_loop:51 - (09:30:59)
[8985/8985] timer_1sec_loop:51 - (09:31:00)
[8985/8985] cronx_validate:98 - (cron_txt: [*/1 * * * * 2024 ], [31 9 14 2 4 2024])
[8985/8985] cronx_validate:218 - Got !!! (cron_txt: [*/1 * * * * 2024 ], [31 9 14 2 4 4], fit: 6)
[8985/8985] timer_1sec_loop:65 - Alarm !!! (*/1 * * * * 2024 )
[8985/8985] timer_1sec_loop:51 - (09:31:01)
[8985/8985] timer_1sec_loop:51 - (09:31:02)
^C[8985/8985] app_signal_handler:212 - (signum: 2)
[8985/8985] app_stop:158 - Bye-Bye !!! (cronx_123)
[8985/8985] async_loop:128 - __________ Enter __________
[8985/8985] main:310 - Bye-Bye !!!
```

#### - dbusx_456 - dbus example.

> export PJ_HAS_DBUS=yes, use dbusx_api.c.
>
> pleae make sure [dbusX.conf](https://github.com/lankahsu520/HelperX/blob/master/DBus/dbusX.conf) in /etc/dbus-1/system.d

```bash
$ ./dbusx_456 -s &
[30642/30643] dbusx_thread_handler:516 - dbus listen ...
$ ./dbusx_456 -e 123
[3003/3004] demo_signal_name_cb:113 - Got !!! (signal_name: command, reqStr: 123)
[3005/3005] app_loop:150 - (retStr: 123)
[3005/3005] main:284 - Bye-Bye !!!
[3003/3004] demo_signal_name_cb:113 - Got !!! (signal_name: DBUS_TYPE_INT16, reqStr: 16)
[3003/3004] demo_signal_name_cb:113 - Got !!! (signal_name: DBUS_TYPE_INT32, reqStr: 32)
[3003/3004] demo_signal_name_cb:113 - Got !!! (signal_name: DBUS_TYPE_INT64, reqStr: 64)
```

#### - demo_000 - c template.

```bash
$ ./demo_000
[3011/3011] app_loop:46 - (pid: 3011)
[3011/3011] app_loop:50 - (cksum: 1398)
[3011/3011] app_loop:52 - (cksum: 22044)
[3011/3011] main:156 - Bye-Bye !!!
```
#### - demo_123 - a example.
```bash
$ ./demo_123
[3013/3013] main:44 - String testing ...
[3013/3013] main:45 - (1<<3: 0x00000008, 1<<14: 0x00004000, 1<<15: 0x00008000, 1<<16: 0x00010000, 1<<17: 0x00020000)
[3013/3013] main:48 - (hello org: Hello World !!!    )
[3013/3013] main:50 - (hello_trim: Hello World !!!)
[3013/3013] main:58 - SAFE_STRCAT_EX - lankahsu520/1234

[3013/3013] main:83 - BASE64, abc -> abc_enc -> abc_dec
[3013/3013] main:87 - (sec_base64_enc: cnRzcDovLzE5Mi4xNjguNTAuMjM4OjU1NC9saXZlMS5zZHA=)
[3013/3013] main:90 - (sec_base64_dec: rtsp://192.168.50.238:554/live1.sdp)

[3013/3013] main:111 - aes_128_cbc, intlen: 15, plaintext: 123456789012345 -> plaintext_enc -> plaintext_dec
[3013/3013] main:112 - (evp_key: 1234567890abcdef, iv_key: 1234567890abcdef)
[3013/3013] main:117 - sec_aes_cbc_enc - plaintext_enc: {
    93 EE E4 5D 7F 89 2D 25 CE 24 F1 BD 78 40 67 62
}
▒7▒#x/30▒▒p▒=S▒"▒▒w▒▒#x(▒▒p▒=S▒"▒▒w▒▒#x ▒▒p▒=S▒"▒▒w▒▒#x:▒▒p▒=S▒"▒▒w▒▒#x5▒▒p▒=S▒"▒▒w▒▒#x ▒▒p▒=S▒"▒▒w▒▒)

[3013/3013] main:127 - sec_aes_cbc_encX - enc_len: 16, plaintext_enc: {
    93 EE E4 5D 7F 89 2D 25 CE 24 F1 BD 78 40 67 62
}
[3013/3013] main:129 - (sec_aes_cbc_decX - dec_len: 15, plaintext_dec: 123456789012345)

[3013/3013] main:147 - hostname ...
[3013/3013] main:150 - (gethostname: build20-vbx)
[3013/3013] main:154 - (getdomainname: (none), res: 0)

[3013/3013] main:189 - datetime ...
[3013/3013] main:190 - (time_now_full: 2024-03-14 09:43:34)
```
#### - http_client_123 - http client example.
>export PJ_HAS_CURL=yes, use curl_api.c.
#### - jqx - it is similar to jq.
> jqx only support reads from pipe. 

```bash
# please download Music.json (https://github.com/lankahsu520/HelperX/blob/master/AWS/Music.json)
$ cat Music.json | ./jqx .Items[3].Sponsor.L[].S
"dog"
"cat"
"mouse"
"stoat"
"snake"
```

#### - json_123 - json example.

> export PJ_HAS_JANSSON=yes, use json_api.c.

```bash
$ ./json_123
[3032/3032] main:32 - enter
[3032/3032] uuid_test:21 - (guid: 7CE07D29-CFA5-417B-a4BF-51AD96BFCB3C)
[3032/3032] uuid_test:24 - (guid: 059D6F66-9537-4B6E-bCD7-48B204C59381)
[3032/3032] uuid_test:27 - (guid: 6E632715-5EEE-449E-8CB4-8049F0856661)
[3032/3032] json_dump_simple:22 - (jroot: {"j1":{"j2":{"j3":{"logo":"helloworld!!!"}}}})
[3032/3032] main:52 - >> update j4->j1
[3032/3032] json_dump_simple:22 - (jroot: {"j1":{"j4":"child !!!"}})
[3032/3032] json_dump_simple:22 - (jroot: {"j1":{"j4":"child !!!"},"jA":[{"name":"A1","val":1},{"name":"A2","val":2},{"name":"A3","val":3}]})
[3032/3032] main:95 - >> (jA: 0x55a05def06e0, jA_new: 0x55a05def06e0)
[3032/3032] main:102 - >> update jB1->jA1
[3032/3032] json_dump_simple:22 - (jroot: {"j1":{"j4":"child !!!"},"jA":[{"name":"A1","nameB":"B4","val":1,"valB":4},{"name":"A2","val":2},{"name":"A3","val":3}]})
[3032/3032] json_dump_simple:22 - (jroot: {"demo":"HelloWorld 1 !!!","j1":{"j4":"child !!!"},"jA":[{"name":"A1","nameB":"B4","val":1,"valB":4},{"name":"A2","val":2},{"name":"A3","val":3}]})
[3032/3032] main:120 - >> set demo as jdemo1 (jdemo1: 0x55a05def04c0, refcount: 1)
[3032/3032] json_dump_simple:22 - (jroot: {"demo":"HelloWorld 2 !!!","j1":{"j4":"child !!!"},"jA":[{"name":"A1","nameB":"B4","val":1,"valB":4},{"name":"A2","val":2},{"name":"A3","val":3}]})
[3032/3032] main:125 - >> set demo as jdemo2; jdemo1 will be free and we can't access jdemo1 !!! !!! (jdemo2: 0x55a05def0860, refcount: 1)
[3032/3032] json_dump_simple:22 - (jroot: {"demo":"HelloWorld 2 !!!","j1":{"j4":"child !!!"},"jA":[{"name":"A1","nameB":"B4","val":1,"valB":4},{"name":"A2","val":2},{"name":"A3","val":3}]})
[3032/3032] main:135 - (idx: 2)
[3032/3032] json_dump_simple:26 - (Not Found - j1/j2/j4: (nil))
[3032/3032] json_dump_simple:22 - (APPEND - j1/j2/j4: {})
[3032/3032] json_dump_simple:26 - (DEL - j1/j2/j3: (nil))
[3032/3032] json_dump_simple:22 - (j1/j2: {"j4":{}})
[3032/3032] main:208 - (sunrise: 3:22:56 AM)
[3032/3032] main:209 - (sunset: 5:10:20 PM)
[3032/3032] main:210 - (utc: 1652853043)
[3032/3032] main:228 - (cJson: {"sunrise":"3:22:56 AM","sunset":"5:10:20 PM","time_utc":1652853043})
```

#### - led_123 - led controller example.
#### - lws_123 - a websocket example.

> export PJ_HAS_LIBWEBSOCKETS=yes, use lws_api.c.

#### - mqtt_123 - a mqtt example.

> export PJ_HAS_MOSQUITTO=yes, use mqtt_api.c.

#### - multicast_cli & multicast_srv - multicast example.

> use multicast_api.c.

```bash
$ ./multicast_srv
listen ... (239.255.255.250:3618)
setsockopt IP_ADD_MEMBERSHIP
10.0.2.15 - 0
10.0.2.15 - 1
10.0.2.15 - 2
10.0.2.15 - 3
10.0.2.15 - 4
```

```bash
$ ./multicast_cli
link ... (239.255.255.250:3618, argc: 1)
sendto (buff: 0)
sendto (buff: 1)
sendto (buff: 2)
sendto (buff: 3)
sendto (buff: 4)
```

#### - ~~nlink_123 & nlink_456 - netlink example. got from internet.~~
#### - nlink_789 netlink example
> use chainX_api.c (CHAINX_MODE_ID_NETLINK).

#### - onvif_client_123 - onvif client example.

> export PJ_HAS_MXML=yes, use onvif_api.c.

#### - ping_123 - ping example.

>use chainX_api.c.

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

#### - proc_list_123 & proc_watch - a system and proc information example.
#### - queuex_123 - a queue example.

> use queuex_api.c.

```bash
$ ./queuex_123
[8651/8651] test_push:62 - (idx: 0)
[8651/8651] queuex_push:311 - (name: test, length: 0/30, ishold: 0, isloop: 1)
[8651/8651] test_push:62 - (idx: 1)
[8651/8651] queuex_push:311 - (name: test, length: 1/30, ishold: 0, isloop: 1)
[8651/8651] test_push:62 - (idx: 2)
[8651/8651] queuex_push:311 - (name: test, length: 2/30, ishold: 0, isloop: 1)
[8651/8651] test_push:62 - (idx: 3)
[8651/8651] queuex_push:311 - (name: test, length: 3/30, ishold: 0, isloop: 1)
[8651/8651] test_push:62 - (idx: 4)
[8651/8651] queuex_push:311 - (name: test, length: 4/30, ishold: 0, isloop: 1)
[8651/8652] test_q_exec_cb:38 - (data_pop->idx: 0)
[8651/8652] test_q_exec_cb:38 - (data_pop->idx: 1)
[8651/8652] test_q_exec_cb:38 - (data_pop->idx: 2)
[8651/8652] test_q_exec_cb:38 - (data_pop->idx: 3)
[8651/8652] test_q_exec_cb:38 - (data_pop->idx: 4)
```

#### - sshX_123 - ssh example.

> export PJ_HAS_LIBSSH=yes, use ssh_api.c.

#### - statex_123 - state machine example.
> use statex_api.c.
#### - ~~swlink_123 - swconfig example. (depend on linux kernel)~~
#### - thread_123 - thread example.

> use thread_api.c.

```bash
$ ./thread_123
[8935/8936] thread_handler:27 - Run loop ... (name: thread_A, count: 0)
[8935/8936] thread_handler:33 - (name: thread_A, count: 0)
[8935/8936] thread_handler:33 - (name: thread_A, count: 1)
[8935/8936] thread_handler:33 - (name: thread_A, count: 2)
[8935/8936] thread_handler:36 - wait 3 seconds ...
[8935/8937] thread_handler:27 - Run loop ... (name: thread_B, count: 0)
[8935/8937] thread_handler:33 - (name: thread_B, count: 0)
[8935/8937] thread_handler:33 - (name: thread_B, count: 1)
[8935/8937] thread_handler:33 - (name: thread_B, count: 2)
[8935/8937] thread_handler:36 - wait 3 seconds ...
[8935/8936] thread_handler:33 - (name: thread_A, count: 3)
[8935/8936] thread_handler:33 - (name: thread_A, count: 4)
[8935/8936] thread_handler:33 - (name: thread_A, count: 5)
[8935/8936] thread_handler:36 - wait 3 seconds ...
```

#### - tty_123 - a tty example. 
> use chainX_api.c.
#### - tunnel_123 - ssh tunnel example.

> export PJ_HAS_LIBSSH=yes, use ssh_api.c.

#### - ubox_123 - ubox example.

> export PJ_HAS_LIBUBOX=yes,.

#### - ubus_123 - ubus example.

> export PJ_HAS_UBUS=yes, use ubus_api.c.

#### - uci_123 - uci example.

> export PJ_HAS_UCI=yes, use uci_api.c.

#### - usb_123 - usb example.

> export PJ_HAS_LIBUSB=yes, use usbX_api.c.

#### - util_123 - example.

```bash
$ ./util_123
[8946/8946] main:23 - (Version: 0x03000000, 2922, 1710208772, lanka, 1710379668)
[8946/8946] main:26 - (Debug LVL: 2, Expiration: 1861919999=20290101 075959, Time Diff: 1753.94)
[8946/8946] main:27 - (Toolchain: , Path: , Build Path: /work/codebase/lankahsu520/utilx9)
[8946/8946] main:28 - (Name: github, Platform: linux, Save: /work/IoT, Work: /tmp/IoT)
[8946/8946] main:29 - (ICLOUD: 192.168.50.148:9000-0, IFACE: enp0s8)
[8946/8946] main:30 - (MCTT: 229.255.255.250:6288)
[8946/8946] main:34 - BIT_SET(num,0) (num: 0x00000001)
[8946/8946] main:36 - BIT_SET(num,2) (num: 0x00000005)
[8946/8946] main:38 - BIT_SET(num,4) (num: 0x00000015)
[8946/8946] main:40 - BIT_SET(num,6) (num: 0x00000055)
[8946/8946] main:42 - BIT_SET(num,8) (num: 0x00000155)
[8946/8946] main:44 - BIT_INVERSE(num,3) (num: 0x0000015D, num.bit2: 1, num.bit3: 1)
```

#### - uv_000 - uv template.

> export PJ_HAS_LIBUV=yes, use uv_api.c.

```bash
$ ./uv_000
[8948/8948] timer_1sec_loop:40 - kick async every 1 second. (countdown: 2)
[8948/8948] async_loop:98 - __________ Enter __________
[8948/8948] async_loop:104 - (*data: 1)
[8948/8948] timer_1sec_loop:40 - kick async every 1 second. (countdown: 1)
[8948/8948] async_loop:98 - __________ Enter __________
[8948/8948] async_loop:104 - (*data: 2)
[8948/8948] timer_1sec_loop:40 - kick async every 1 second. (countdown: 0)
[8948/8948] main:255 - Bye-Bye !!!
```

#### - uv_123 - uv example.

> export PJ_HAS_LIBUV=yes, use uv_api.c.

```bash
$ ./uv_123
[3334/3335] queue_work_handler:119 - (id: 1, count: 1)
[3334/3335] queue_work_handler:119 - (id: 4, count: 1)
[3334/3335] queue_work_handler:119 - (id: 5, count: 1)
[3334/3335] queue_work_handler:119 - (id: 6, count: 1)
[3334/3335] queue_work_handler:119 - (id: 7, count: 1)
[3334/3336] queue_work_handler:119 - (id: 2, count: 1)
[3334/3336] queue_work_handler:119 - (id: 10, count: 1)
[3334/3337] queue_work_handler:119 - (id: 3, count: 1)
[3334/3335] queue_work_handler:119 - (id: 8, count: 1)
[3334/3338] queue_work_handler:119 - (id: 9, count: 1)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 1, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 4, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 5, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 6, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 7, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 2, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 10, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 3, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 8, status: 0)
[3334/3334] queue_work_finisher:109 - Bye-Bye !!! (id: 9, status: 0)
[3334/3334] timer_1_loop:49 - (count: 1)
[3334/3334] timer_1_loop:55 - Bye-Bye !!!
[3334/3334] timer_2_loop:63 - (count: 1)
[3334/3334] timer_2_loop:68 - Bye-Bye !!!

^C[3334/3334] app_signal_handler:409 - (signum: 2)
[3334/3334] async_loop:300 - (percentage: 0)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 0)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 1)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 2)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 3)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 4)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 5)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 6)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 7)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 8)
[3334/3334] app_stop_uv:259 - (SAFE_UV_CANCEL: 9)
[3334/3334] uv_event_close_ex:249 - Bye-Bye !!! (uv_123)
[3334/3334] main:510 - Bye-Bye !!!
```

#### - uv_spawn_123 - uv spawn example.

> export PJ_HAS_LIBUV=yes, use uv_api.c.

```bash
$ ./uv_spawn_123
[5051/5051] timer_1sec_loop:94 - (count: 1)
[5051/5051] timer_1sec_loop:94 - (count: 2)
[5051/5051] uv_spawn_open_ex:163 - Launch a new thread !!! (spawn_req: 0x55d43bc5c0e0, pid: 5052)
[5051/5051] uv_spawn_pipe_stdout_cb:119 - (buf->base: PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_seq=1 ttl=113 time=5.19 ms
)
[5051/5051] timer_1sec_loop:94 - (count: 3)
[5051/5051] uv_spawn_simple_detached:210 - uv_spawn error !!! (no such file or directory, file: /work/rootfs/sbin/iot_kvsWebrtc.sh)
[5051/5051] uv_spawn_simple_detached:210 - uv_spawn error !!! (no such file or directory, file: /work/rootfs/sbin/baresip_123.sh)
[5051/5051] uv_spawn_pipe_stdout_cb:119 - (buf->base: 64 bytes from 8.8.8.8: icmp_seq=2 ttl=113 time=4.86 ms
)
[5051/5051] timer_1sec_loop:94 - (count: 4)
[5051/5051] uv_spawn_pipe_stdout_cb:119 - (buf->base: 64 bytes from 8.8.8.8: icmp_seq=3 ttl=113 time=4.68 ms
)
^C[5051/5051] app_signal_handler:239 - (signum: 2)
[5051/5051] uv_spawn_pipe_stdout_cb:119 - (buf->base:
--- 8.8.8.8 ping statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2002ms
rtt min/avg/max/mdev = 4.679/4.910/5.187/0.209 ms
)
[5051/5051] async_loop:176 - (async_count: 1)
[5051/5051] app_stop_uv:142 - call SAFE_UV_TIMER_CLOSE ~~~
[5051/5051] app_stop_uv:147 - call uv_spawn_close_ex ~~~
[5051/5051] app_stop_uv:152 - call SAFE_UV_CLOSE ~~~
[5051/5051] app_stop_uv:158 - call SAFE_UV_LOOP_CLOSE ~~~
[5051/5051] app_stop_uv:165 - exit
[5051/5051] uv_spawn_exit_cb:79 - Bye-Bye !!! (ping)
[5051/5051] main:326 - Bye-Bye !!!
```

#### - wsdiscovery_123 - WS-Discovery example.

> export PJ_HAS_MXML=yes, use wsdiscovery_api.c.

#### - ~~gbusx_123 - a  example.~~
> use gbusx_api.c.


# 6. License
> utilx9 is under the New BSD License (BSD-3-Clause).


# 7. Documentation
> Run an example and read it.
