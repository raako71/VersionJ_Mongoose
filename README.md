# VersionJ_Mongoose

Changelog:<br/>
0.9.7.9a: fix bug 12th milestone<br>
0.9.7.9: fix login (blank password) 5 mins free acess on ap button, validate cookie when saving<br>
0.9.7.8b: CSS changes<br>
0.9.7.8: fix login function add i2c enable<br>
0.9.7.7: revert CSS .section etc<br>
0.9.7.6: add login function<br>
0.9.7.5b->f: CSS changes<br>
0.9.7.5: CSS changes<br>
0.9.7.4: mobile html formatting<br>
0.9.7.2: add wifi sta+ap<br>
0.9.7.2: fix program editor bug<br>
0.9.7.1: match Harry push<br>
0.9.7.0: 12th milestone (wifi only), fix last version bug<br>
0.9.6.4c: CSS changes<br>
0.9.6.4a: Modify WiFi details and MDNS<br>
0.9.6.4: 11th milestone complete<br>
0.9.6.3: fix dev mode 2nd <br>
0.9.6.2: fix dev mode<br>
0.9.6.1: milestone 11 exclude OTA<br>
0.9.6.0: add web ota<br>
0.9.5.9: fix timed cycle init and output warning (page) <br>
0.9.5.8: fix some feature<br>
0.9.5.7: very minor changes to text<br>
0.9.5.6: fix bug for milestone 10, add spinner for setting and control page<br>
0.9.5.5: added general.css<br>
0.9.5.4: minor modifications to CSS for program editor<br>
0.9.5.3: fix timed cycle confirm, add spiner loader when saving, add import program<br>
0.9.5.2: fix program editor reload and rpb check<br>
0.9.5.1: fix led red status in web page and seperated css file<br>
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
