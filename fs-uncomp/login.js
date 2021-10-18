var temp_unit_login;
var save_command = false;
var save_command_wifi = false;
var dev_offset = 0;
save_command_update = false;
check_ap_mode();
var theme_global;
var timeout_global = 5000; //default is 5secs
load_conf_login();
login_session_check();
var spinner_load= '<div id="circularG" style="margin-top:-5px"><div id="circularG_1" class="circularG"></div>';
spinner_load += '<div id="circularG_2" class="circularG"></div>';
spinner_load += '<div id="circularG_3" class="circularG"></div><div id="circularG_4" class="circularG"></div><div id="circularG_5" class="circularG"></div>';
spinner_load += '<div id="circularG_6" class="circularG"></div><div id="circularG_7" class="circularG"></div><div id="circularG_8" class="circularG"></div></div>';

var login_page = '<b>Login</b><br><div style="text-align:left;padding-left:10%; padding-right:10%;margin-top:10px">Password: <input type="password" style="width:75%; margin-bottom:5px" id="login_password"><br>';
login_page += '<div style="margin-top:10px"><input type="button" value="Change Password" onClick="change_password()"></div></div><span style="margin-top:10px;display:block;" id="login_warning"></span><div style="margin-top:10px">';
login_page += '<input type="button" style="margin:10px" onClick="confirm_password()" id="enter_password" value="OK"><input style="margin:10px" type="button" value="CANCEL" onClick="off_overlay_login()"></div>';

var time_page = '<div id="devtime_box"></div> <div style="margin-top:10px" id="timepanel_info"></div>';
time_page += '<div style="position:absolute;bottom:35%;width:100%"><input type="button" style="display:none" id="pulltime_btn" value="Pull time from browser" onClick="pushtime()"><br><br>';
time_page += '<input type="button" value="Pull timezone from browser"  onClick="change_offset()"></div>';
time_page += '<div style="position:absolute;bottom:10%;width:100%"><input type="button" value="CLOSE" onClick="off_overlay_login()"></div>';

function off_overlay_login(){
  document.getElementById("overlay_login").style.display = "none";
  document.getElementById("main_div").style.filter = "none";
  document.getElementById("multipurpose").innerHTML = "";
}
function on_overlay_login(input) {
  document.getElementById("overlay_login").style.display = "block";
  document.getElementById("main_div").style.filter = "blur(2px)";
  document.getElementById("overlay_login").style.filter = "none";
  if(input == 2){
  document.getElementById("multipurpose").innerHTML = login_page;
  document.getElementById("login_password").focus();
  document.getElementById("login_password").addEventListener("keyup", function (event){if(event.keyCode == 13){event.preventDefault();confirm_password();}});
  return;
  }
  if(input == 1){
  document.getElementById("multipurpose").innerHTML = time_page;
  return;
  } 
}
function change_pass_info(){
	var a = document.getElementById("old_password").value;
	var b = document.getElementById("new_pass1").value;
	var c = document.getElementById("new_pass2").value;
	var x = document.getElementById("change_pass_warning");
	if(b != c){
		x.innerHTML = "New Passwords are not same!";
		return;
	}
	x.innerHTML = spinner_load;
	xhr_send("change_pass", JSON.stringify({old_pass:a, new_pass:b}), function(i){
		if(i.status == "success"){
			var data = i.data;
			if(data.status == "unauthorized"){
				x.innerHTML = "incorrect password!";
			}else if(data.status == "confirm"){
				x.innerHTML = "Password changed!";
				document.getElementById("cancel_change_password").value = "OK";
				document.getElementById("confirm_change_password").style.display = "none";
			}
		}else{
			x.innerHTML = i.status;
		}
	});
}
function xhr_send(rpc, comm, callback){
	var xhr = new XMLHttpRequest();
	xhr.open("POST", "/rpc/"+rpc, true);
	xhr.setRequestHeader('Content-Type', 'application/json');
	xhr.send(comm);
	xhr.timeout = timeout_global;
	xhr.ontimeout = function (e) {
		callback({code:400, status:"No response from controller!"});
	};
	xhr.onreadystatechange = function() {
		if(xhr.readyState != 4){return;}
		if(xhr.status == 200){
			callback({code:200, status:"success", data: JSON.parse(xhr.responseText)});
		}else{
			callback({code: 408, status:"Request Failed!"});
		}
	}
}
function validate_cookie(callback){
	var ver_key = getCookie();
	ver_key = (ver_key == "") ? "0" : ver_key;
	xhr_send("validate_key", JSON.stringify({key:ver_key}), function(i){
		callback(i);
		if(i.code == 200){
			if(i.data.status == "illegal"){setCookie("");login_session_check();callback(i);}
		}
	});
}
function on_overlay_change_pass(){
	document.getElementById("overlay_change_pass").style.display = "block";
	document.getElementById("main_div").style.filter = "blur(2px)";
	document.getElementById("overlay_change_pass").style.filter = "none";
	document.getElementById("confirm_change_password").style.display = "inline";
	document.getElementById("cancel_change_password").value = "CANCEL";
	document.getElementById("change_pass_warning").innerHTML = "";
	document.getElementById("old_password").value = "";
	document.getElementById("new_pass1").value = "";
	document.getElementById("new_pass2").value ="";
}
function off_overlay_change_pass(){
  document.getElementById("overlay_change_pass").style.display = "none";
  document.getElementById("main_div").style.filter = "none";
}
function setCookie(cvalue) {	
  document.cookie = "verification=" + String(cvalue);
}
function change_password(){
var logged = check_password();
if(!logged){
on_overlay_change_pass();
}else{
document.getElementById("login_warning").innerHTML = "Please log out first to change password!";	
}
}
function confirm_password(){
	var x = document.getElementById("login_warning");
	var pass_local = document.getElementById("login_password").value;
	var logged = check_password();
	if(logged){	x.innerHTML = "Logged in already!";	return;}
	x.innerHTML = spinner_load;
	xhr_send("login", JSON.stringify({pass:pass_local}),  function(i){
	if(i.code == 200){
		if(i.data.status == "authorized"){
		x.innerHTML = "Login successful!";
		setCookie(i.data.key);
		login_session_check();
		off_overlay_login();
		if(save_command){save_conf();}
		if(save_command_update) {upload_fw();}
		if(save_command_wifi){connect_wifi();}
		}else if(i.data.status == "unauthorized"){x.innerHTML = "incorrect password!";return;}
	}else{
		x.innerHTML = i.status;
	}
	});
}
function login_confirm(input){
	if(input.innerHTML == "Login"){
	on_overlay_login(2);	
	}else if(input.innerHTML == "Logout"){
	setCookie("");
	login_session_check();
	}
}
function getCookie() {
	let name = "verification=";
	let ca = document.cookie.split(';');
	for(let i = 0; i < ca.length; i++) {
		let c = ca[i];
		while (c.charAt(0) == ' ') {
			c = c.substring(1);
		}
		if (c.indexOf(name) == 0) {
			return c.substring(name.length, c.length);
		}
	}
  return "";
}
function check_password(){
	var ver_key = getCookie();
	if(ver_key != ""){
		return true;
	}else{
		return false;
	}
}
function login_session_check(){
var logged = check_password();
document.getElementById("log_info").innerHTML = (logged)? "Logged In" : "Logged Out";
document.getElementById("log_button").innerHTML = (logged) ? "Logout" : "Login";	
}
function load_conf_login(){
var xhr = new XMLHttpRequest();
xhr.open("POST", "/rpc/FS.Get", true);
xhr.setRequestHeader('Content-Type', 'application/json');
var comm = {"filename": "setting.json"};
xhr.send(JSON.stringify(comm));
xhr.onload = function() {
var data = JSON.parse(this.responseText);
var old_json = JSON.parse(window.atob(data.data));
dev_offset = old_json.timezone;
temp_unit_login = old_json.temp_scale;
changetheme(old_json.theme);
timeout_global = old_json.webserver.timeout;
}
}
function changetheme(input){
var sheets = document.getElementsByTagName('link');
if(input == 1){
sheets[0].href = "light.css?" + Math.random() * Math.random();
theme_global = 1;
}else{
sheets[0].href = "dark.css?" + Math.random() * Math.random();
theme_global = 2;
}
}

var login_ap = setInterval(check_ap_mode, 5000);
function check_ap_mode(){
xhr_send("check_ap_mode", null, function(i){
	if(i.status == "success"){
		var a = i.data.mode;
		var b = i.data.uptime;
		if(a == true && b < 300){
			document.getElementById("old_password_holder").className = "disabled";
			document.getElementById("old_password").disabled = true;
		}else{
			document.getElementById("old_password_holder").classList.remove("disabled");
			document.getElementById("old_password").disabled = false;
			clearInterval(login_ap);
		}
	}
});	
}
function update_time(){
xhr_send("getTime", null, function(i){
	var x = i.data;
	if(i.code != 200){return;}
	var p = document.getElementById("pulltime_btn");
	if(p != null){ p.style.display = "none";}
	var d = new Date();
	var hour = Math.floor(Math.abs(dev_offset)/3600);hour = Math.abs(hour);
	var minute = Math.abs(dev_offset) - hour*3600; minute /= 60;
	var a = new Date();
	var pub_string = epochToJsDate(x);  var time_panel = "Device Time: "+pub_string;		
	var browser_time = Math.floor(Date.now() / 1000);
	if(a.getTimezoneOffset()*(-60) != dev_offset){
	pub_string += ' <a onClick="on_overlay_login(1)"  href="#" title="Timezone doesn\'t match browser!" style="text-decoration:none;color:red;">!!</a> ';
	}else if(Math.abs(browser_time - x) >= 10){
	pub_string += ' <a onClick="on_overlay_login(1)"  href="#" title="Device time doesn\'t match browser time!" style="text-decoration:none;color:red;">!!</a> ';
	}
	if(Math.abs(browser_time - x) >= 10){if(p != null){ p.style.display = "inline";}}
	var a = "&ensp;(GMT";
	a += (dev_offset >= 0 ? " +": " -") + hour +"." +minute + ") ";
	pub_string += a; time_panel += a;
	document.getElementById("clock_info").innerHTML = pub_string;
	if(document.getElementById("devtime_box") != null){document.getElementById("devtime_box").innerHTML = time_panel;}
});//end of gettime
}
function epochToJsDate(ts){
	var a = new Date();	var offset = a.getTimezoneOffset();a = new Date(ts* 1000 + (offset*60000) + dev_offset*1000);
	var ret = (a.getHours() < 10 ? '0' + a.getHours() : a.getHours()) + ':' +(a.getMinutes() < 10 ? '0' + a.getMinutes() : a.getMinutes())  + ':' + (a.getSeconds() < 10 ? '0' + a.getSeconds() : a.getSeconds())  + "&emsp; ";
	ret +=  a.getDate() + '/' + (a.getMonth() + 1) + '/' + a.getFullYear();	return ret; 
}
function change_offset(){
var a = new Date();
dev_offset = 	-1 * (a.getTimezoneOffset()) * 60;
var x = document.getElementById("timepanel_info");
x.innerHTML = spinner_load;
xhr_send("FS.get", JSON.stringify({filename:"setting.json"}), function(i){
	if(i.status != "success"){
	x.innerHTML = i.status;
	return;
	}
	old_json = JSON.parse(window.atob(i.data.data));
	old_json.timezone = dev_offset;
xhr_send("FS.put", JSON.stringify({filename:"setting.json", append:false, data: window.btoa(JSON.stringify(old_json))}), function(u){
	if(u.status != "success"){
		x.innerHTML = u.status;
		return;
	}
	x.innerHTML = "Device timezone updated!";
});	
});//end of fs.get
}
function pushtime(){
a = Math.floor(Date.now() / 1000); //recapture epoch
var jsonobj = {epoch: a};
var x = document.getElementById("timepanel_info");
x.innerHTML = spinner_load;
xhr_send("pushtime", JSON.stringify(jsonobj), function(i){
	if(i.code == 200){
		x.innerHTML = i.data.status;
	}else{
		x.innerHTML = i.status;
	}
});
}