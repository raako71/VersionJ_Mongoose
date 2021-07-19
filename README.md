# VersionJ_Mongoose

Changelog:<br />
0..9.5.1: fix led red status in web page and seperated css file<br>
0.9.5: add export button and pb1 and pb2 <br>
0.9.3.2 Re-add Eth and LED brightness<br>
0.9.4: remove ethernet<br>
0.9.3: control page and program editor amendements<br>
0.9.2 : fix inversion remote led control, rl_led_en adjustment<br>
0.9.1 : completion of program edito feature, add light/dark theme setting<br>
0.9: add duty cycle as secondary for 1,2,3,4, and 8 main trigger option. add control remote push button algorithm (short push only)<br>
0.8: program calculation, IO integration with control page, brightness control <br>
0.7: check program state and program to output linker, slider range 0 to 100%, testing led 0.5Hz. <br>
0.6: program editor modify and control page<br>
0.5: program editor back-end<br/>
0.4: add advertise, program editor UI and front end <br/>
0.3: fix issue crash on migration <br/>
0.2: Issue with memory overflow resolved.<br />
0.1: Control Page beta finished.<br />

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
