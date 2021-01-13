# VersionJ_Mongoose

GUIDE
1. you need to build the firmware "mos build"
2. you need to flash the device "mos flash"
3. you must put file in data folder to mnt foler (in device) with this command: "mos put data/webstyle.css mnt/webstyle.css", do that to all files
4. restart the device.
5. good to go

Files: (just library)
mos put data/chart.js@2.8.0.js mnt/chart.js@2.8.0.js
mos put data/d3-dsv.v1.min.js mnt/d3-dsv.v1.min.js
mos put data/d3-fetch.v1.min.js mnt/d3-fetch.v1.min.js

1. WiFi:
mos wifi WIFI_NETWORK_NAME WIFI_PASSWORD
mos wifi DODO-A609 C7LWMPVNCP
mos config-set wifi.sta.enable=false

2. ethernet:
mos config-set eth.enable=true

DNS server
1. change host name in mos.yml file line 32

CONVERSION FLOW
1. webserver
In arduino we were using asyncwebserver library as the responder of HTTP request (GET and POST method).
after that, we must include in the code, what kind of replies must be sent after request, using server.on() function.
In mongoose OS, we don't need to do that. Just include library link in mos.yml file 
(- origin: https://github.com/mongoose-os-libs/http-server) and we are good to go.
With this library we just need to put web files in fs folder and then compile and then flash it to the device.

a. RPC (Remote procedure Call)
Mongoose OS uses RPC as an interaction function between user and the device. We use RPC function to respond many requests,
like (a) delete file request (b) time get request (c) csv file request (d) json setting file request (e) push time request

mongoose os code initiation example
mg_rpc_add_handler(mgos_rpc_get_global(), "getTime", "", getTime, NULL);
mg_rpc_add_handler(mgos_rpc_get_global(), "delReq", "{comm:%Q}", requestDel, NULL);
mg_rpc_add_handler(mgos_rpc_get_global(), "pushTime", "{epoch:%ld}", pushTime, NULL);

We can use RPC function call from http request using POST and GET method (in javascript). Basically, just same with arduino version with
POST method addition.

2. file management system
In arduino IDE, we can use SPIFFS library which gives ease in accessing file using file.open, file.close etc.
In mongoose OS we need to use file management function in C++ in this reference.
http://www.cplusplus.com/reference/cstdio/fopen/
the housekeeping function is the same in arduino version but using C++ file function.

We are also using extra file system partition because mongoose os only provides fs with 256K. The size is not enough for our libs.
so Extra partition is needed. We includes the partition settings in mos.yml file

  - origin: https://github.com/mongoose-os-libs/fstab
  
  - origin: https://github.com/mongoose-os-libs/vfs-fs-lfs

build_vars:
  
   ESP_IDF_EXTRA_PARTITION: data,data,spiffs,,256K


3. DNS setting
 DNS can be implemented using config scheme in mos.yml file
  - ["dns_sd.enable", true]
  
  - ["dns_sd.host_name", "esp32-mos"]
and library includes
  - origin: https://github.com/mongoose-os-libs/dns-sd

4. sNTP
- origin: https://github.com/mongoose-os-libs/sntp
include this library in mos.yml and add some config scheme 
  - ["sntp.retry_min", "i", 10, {title: "Minimum retry interval"}]
 
  - ["sntp.retry_max", "i", 30, {title: "Maximum retry interval"}]
  
  - ["sntp.update_interval", "i", 3600, {title: "Update interval. If 0, performs a one-off sync"}]
done!

5. ethernet
Using this config scheme
  - ["eth.clk_mode", "i", 3, {title: "50 MHz clock source: 0 in <- GPIO0, 1 out -> GPIO0, 2 out -> GPIO16, 3 out -> GPIO17 (inverted)"}]

  - ["eth.mdc_gpio", "i", 23, {title: "GPIO to use for RMII MDC signal"}]

  - ["eth.mdio_gpio", "i", 18, {title: "GPIO to use for RMII MDIO signal"}]

  - ["eth.phy_pwr_gpio", "i", 5, {title: "GPIO to use for PHY PWR control signal"}]

  - ["eth.phy_addr", "i", 0, {title: "PHY address"}]

and add library
  - origin: https://github.com/mongoose-os-libs/ethernet
done!
