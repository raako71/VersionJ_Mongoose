var ctx = document.getElementById('main_chart').getContext('2d');
var chart_one = new Chart(ctx, {
// The type of chart we want to create
type: 'line',
// The data for our dataset
data: {
labels: [],
datasets: [{
label: 'Relay 1',
backgroundColor: 'rgb(255, 167, 0)',
borderColor: 'rgb(255, 167, 0)',
data: [],
spanGaps:true,
fill: false
},{
label: 'Relay 2',
backgroundColor: 'rgb(234, 1, 1)',
borderColor: 'rgb(234, 1, 1)',
data: [],
spanGaps:true,
fill: false
},{
label: 'Voltage',
backgroundColor: 'rgb(0, 39, 255)',
borderColor: 'rgb(0, 39, 255)',
data: [],
spanGaps:true,
fill: false
},{
label: 'Power',
backgroundColor: 'rgb(238, 255, 109)',
borderColor: 'rgb(238, 255, 109)',
data: [],
spanGaps:true,
fill: false
},
{
label: 'Current',
backgroundColor: 'rgb(173, 33, 171)',
borderColor: 'rgb(173, 33, 171)',
data: [],
spanGaps:true,
fill: false
}]
},

// Configuration options go here
options: {
scales: {
xAxes: [{
gridLines:{
color:'rgb(0, 255, 137)'
},
ticks:{
fontColor:'rgb(0, 255, 137)'
}
}],
yAxes: [{
gridLines:{
color:'rgb(0, 255, 137)'
},
ticks:{
fontColor:'rgb(0, 255, 137)'
}
}]
},
legend: {
labels: {
// This more specific font property overrides the global property
fontColor: 'rgb(0, 255, 137)'
}
}
}
});
var ctx1 = document.getElementById('sec_chart').getContext('2d');
var chart_two = new Chart(ctx1, {
// The type of chart we want to create
type: 'line',

// The data for our dataset
data: {
labels: [],
datasets: [{
label: 'S1 Temp',
backgroundColor: 'rgb(255, 167, 0)',
borderColor: 'rgb(255, 167, 0)',
data: [],
spanGaps:true,
fill: false
},{
label: 'S1 Hum',
backgroundColor: 'rgb(234, 1, 1)',
borderColor: 'rgb(234, 1, 1)',
data: [],
spanGaps:true,
fill: false
},{
label: 'S1 Press',
backgroundColor: 'rgb(0, 39, 255)',
borderColor: 'rgb(0, 39, 255)',
data: [],
spanGaps:true,
fill: false
},{
label: 'S1 light',
backgroundColor: 'rgb(238, 255, 109)',
borderColor: 'rgb(238, 255, 109)',
data: [],
spanGaps:true,
fill: false
}]
},

// Configuration options go here
options: {
scales: {
xAxes: [{
gridLines:{
color:'rgb(0, 255, 137)'
},
ticks:{
fontColor:'rgb(0, 255, 137)'
}
}],
yAxes: [{
gridLines:{
color:'rgb(0, 255, 137)'
},
ticks:{
fontColor:'rgb(0, 255, 137)'
}
}]

},
legend: {
labels: {
// This more specific font property overrides the global property
fontColor: 'rgb(0, 255, 137)'
}
}
}
});
var ctx2 = document.getElementById('trd_chart').getContext('2d');
var chart_three = new Chart(ctx2, {
// The type of chart we want to create
type: 'line',
// The data for our dataset
data: {
labels: [],
datasets: [{
label: 'S2 Temp',
backgroundColor: 'rgb(255, 167, 0)',
borderColor: 'rgb(255, 167, 0)',
data: [],
spanGaps: true,
fill: false
},{
label: 'S2 Hum',
backgroundColor: 'rgb(234, 1, 1)',
borderColor: 'rgb(234, 1, 1)',
data: [],
spanGaps:true,
fill: false
},{
label: 'S2 Press',
backgroundColor: 'rgb(0, 39, 255)',
borderColor: 'rgb(0, 39, 255)',
data: [],
spanGaps:true,
fill: false
},{
label: 'S2 light',
backgroundColor: 'rgb(238, 255, 109)',
borderColor: 'rgb(238, 255, 109)',
data: [],
spanGaps:true,
fill: false
}]
},
// Configuration options go here
options: {
scales: {
xAxes: [{
gridLines:{
color:'rgb(0, 255, 137)'
},
ticks:{
fontColor:'rgb(0, 255, 137)'
}
}],
yAxes: [{
gridLines:{
color:'rgb(0, 255, 137)'
},
ticks:{
fontColor:'rgb(0, 255, 137)'
}
}]
},
legend: {
labels: {
// This more specific font property overrides the global property
fontColor: 'rgb(0, 255, 137)'
}
}
}
});
function epochToJsDate(ts){
// ts = epoch timestamp
// returns date obj
var a = new Date(ts*1000);
var ret = (a.getHours() < 10 ? '0' + a.getHours() : a.getHours()) + ':' +(a.getMinutes() < 10 ? '0' + a.getMinutes() : a.getMinutes())  + ':' + (a.getSeconds() < 10 ? '0' + a.getSeconds() : a.getSeconds())  + ", ";
ret +=  a.getDate() + '/' + (a.getMonth() + 1) + '/' + a.getFullYear();
return ret; 
}
function addData(chart, label, data1, data2, data3,data4, data5) {
chart.data.labels =(label);
chart.data.datasets[0].data = data1;
chart.data.datasets[1].data = data2;
chart.data.datasets[2].data = data3;
chart.data.datasets[3].data = data4;
if (data5 != '-'){
chart.data.datasets[4].data = data5;
}
chart.update();
}
function check_global_setting(){
var col_bool;
fetch('mnt/setting.json')
.then(function (response){ return response.json();})
.then(function(data){
// Work with JSON data here
//console.log(data);
col_bool = data;
if(doc == "/thisHour.csv" || doc == "/1970Hour.csv"){
document.getElementById("col1_checkbox").checked = col_bool.col1_en;
document.getElementById("col2_checkbox").checked = col_bool.col2_en;
document.getElementById("col3_checkbox").checked = col_bool.col3_en;
document.getElementById("col4_checkbox").checked = col_bool.col4_en;
document.getElementById("col5_checkbox").checked = col_bool.col5_en;
document.getElementById("col6_checkbox").checked = col_bool.col6_en;
document.getElementById("col7_checkbox").checked = col_bool.col7_en;
document.getElementById("col8_checkbox").checked = col_bool.col8_en;
document.getElementById("col9_checkbox").checked = col_bool.col9_en;
document.getElementById("col10_checkbox").checked = col_bool.col10_en;
document.getElementById("col11_checkbox").checked = col_bool.col11_en;
document.getElementById("col12_checkbox").checked = col_bool.col12_en;
document.getElementById("col13_checkbox").checked = col_bool.col13_en;
}else if(doc == "/thisDay.csv"){
	document.getElementById("rec_online_checkbox").checked = col_bool.rc_thisday;	
}else if (doc == "/1970Day.csv"){
	document.getElementById("rec_online_checkbox").checked = col_bool.rc_1970day;	
}
});
}
function checkcol_func(){
var old_json;
fetch('mnt/setting.json')
.then(function (response){ return response.json();})
.then(function(data){
old_json = data;
old_json.col1_en = document.getElementById("col1_checkbox").checked;		
old_json.col2_en = document.getElementById("col2_checkbox").checked;			
old_json.col3_en = document.getElementById("col3_checkbox").checked;	
old_json.col4_en = document.getElementById("col4_checkbox").checked;	
old_json.col5_en = document.getElementById("col5_checkbox").checked;	
old_json.col6_en = document.getElementById("col6_checkbox").checked;		
old_json.col7_en = document.getElementById("col7_checkbox").checked;			
old_json.col8_en = document.getElementById("col8_checkbox").checked;	
old_json.col9_en = document.getElementById("col9_checkbox").checked;	
old_json.col10_en = document.getElementById("col10_checkbox").checked;	
old_json.col11_en = document.getElementById("col11_checkbox").checked;
old_json.col12_en = document.getElementById("col12_checkbox").checked;
old_json.col13_en = document.getElementById("col13_checkbox").checked;
var string = JSON.stringify(old_json);
var xhr = new XMLHttpRequest();
xhr.open("POST", "/rpc/setting", true);
xhr.setRequestHeader('Content-Type', 'application/json');
xhr.send(string);
});
}
function update_graph(){
d3.dsv(";", doc).then(function(mewmew){
var base = mewmew.map(function(e){
return e.epoch;
});
var converted_epoch = [];
function myFunction(value) {
ret = epochToJsDate(value);
converted_epoch.push(ret);
}
base.forEach(myFunction);
var mul50_result = [];
function mul50(value){
if(value == ''){
	ret = null;
}else{
	ret = value*50;
}
mul50_result.push(ret);

}	
var col1 = mewmew.map(function(e){
return e.column1;
})
col1.forEach(mul50);
var mul60_result = [];
function mul60(value){
if(value == ''){
	ret = null;
}else{
	ret = value*60;
}
mul60_result.push(ret);
}
var col2 = mewmew.map(function(e){
return e.column2;
});
col2.forEach(mul60);
var col3_conv_ret = [];
function col3_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col3_conv_ret.push(ret);
}
var col3 = mewmew.map(function(e){
return e.column3;
});
col3.forEach(col3_conv);
var col4_conv_ret = [];
function col4_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col4_conv_ret.push(ret);
}
var col4 = mewmew.map(function(e){
return e.column4;
});
col4.forEach(col4_conv);

var col5_conv_ret = [];
function col5_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col5_conv_ret.push(ret);
}
var col5 = mewmew.map(function(e){
return e.column5;
});
col5.forEach(col5_conv);
var col6_conv_ret = [];
function col6_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col6_conv_ret.push(ret);
}
var col6 = mewmew.map(function(e){
return e.column6;
});
col6.forEach(col6_conv);

var col7_conv_ret = [];
function col7_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col7_conv_ret.push(ret);
}
var col7 = mewmew.map(function(e){
return e.column7;
});
col7.forEach(col7_conv);
var col8_conv_ret = [];
function col8_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col8_conv_ret.push(ret);
}
var col8 = mewmew.map(function(e){
return e.column8;
});
col8.forEach(col8_conv);
var col9_conv_ret = [];
function col9_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col9_conv_ret.push(ret);
}
var col9 = mewmew.map(function(e){
return e.column9;
});
col9.forEach(col9_conv);
var col10_conv_ret = [];
function col10_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col10_conv_ret.push(ret);
}
var col10 = mewmew.map(function(e){
return e.column10;
});
col10.forEach(col10_conv);
var col11_conv_ret = [];
function col11_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col11_conv_ret.push(ret);
}
var col11 = mewmew.map(function(e){
return e.column11;
});
col11.forEach(col11_conv);

var col12_conv_ret = [];
function col12_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col12_conv_ret.push(ret);
}
var col12 = mewmew.map(function(e){
return e.column12;
});
col12.forEach(col12_conv);
var col13_conv_ret = [];
function col13_conv(value){
if(value == ''){
	ret = null;
}else{
	 ret = value;
}
col13_conv_ret.push(ret);
}
var col13 = mewmew.map(function(e){
return e.column13;
});
col13.forEach(col13_conv);
addData(chart_one, converted_epoch, mul50_result, mul60_result, col3_conv_ret,col4_conv_ret,col5_conv_ret);
addData(chart_two, converted_epoch, col6_conv_ret, col7_conv_ret, col8_conv_ret, col9_conv_ret, '-');
addData(chart_three, converted_epoch, col10_conv_ret, col11_conv_ret, col12_conv_ret, col13_conv_ret, '-');
})
}
function update_time(){
var xhr = new XMLHttpRequest();
xhr.onreadystatechange = function(){
if(xhr.readyState == 4){
var x = xhr.responseText;
var d = new Date();
var offset = d.getTimezoneOffset();
var pub_string = "Device Time: " + epochToJsDate(x)+  (offset < 0 ? " (+": " (-") + Math.abs(offset)/60 + ")";					
document.getElementById("hour_text").innerHTML = pub_string;
}
};
xhr.open("GET", "/rpc/getTime", true);
xhr.send();
}
function onLoad(event) { //function when dom is loaded
update_time();
check_global_setting();
//delay500ms to update graph on first load
setTimeout(update_graph(), 500);
}
window.addEventListener('load', onLoad);	
setInterval(function () {
update_graph();
}, 10000 ) ;
//update time
setInterval(function() {
update_time();
}, 1000);