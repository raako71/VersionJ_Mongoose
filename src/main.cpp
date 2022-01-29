/*
 * Copyright (c) 2014-2018 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <vector>
#include <string>
#include "mgos.h"
#include "mgos_rpc.h"
#include "mgos_wifi.h"
#include "mgos_http_server.h"
#include "mgos_dns_sd.h"
#include "mgos_pwm.h"
#include "ACS71020.h"
#include "mgos_bme280.h"
#include "MCP9600.h"
#include "mgos_sht31.h"
///#include "mgos_i2c.h"
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"
#include "mgos_adc.h"
#include "Wire.h"
//longtermdata trimmer variable
#define UPPER_LIMIT_SIZE 12000
#define LOWER_LIMIT_SIZE 10000
#define TRIMMER_INTERVAL 3600
//housekeeping variable
#define THISDAY_INTERVAL 60 //(in seconds)
#define THISWEEK_INTERVAL 300
#define THISMONTH_INTERVAL 600
#define LONGTERM_INTERVAL 1800

#define V2

#ifdef V1
#define WIFI_LED 4
#define WIFI_BTN 35
#define INPUT_A 34
#define INPUT_B 35
#define EN_I2C 13
#define OUTPUT_A 14
#define OUTPUT_B 12
#define LED_RED 16
#define RL_LED_EN 2	
#endif

#ifdef V2
#define WIFI_LED 16 //commented out in code due to short in hardware 
#define WIFI_BTN 36
#define INPUT_A 35
#define INPUT_B 39
#define INPUT_C 34
#define EN_I2C 13
#define OUTPUT_A 4
#define OUTPUT_B 12
#define OUTPUT_C 2
#define OUTPUT_D 14
#define RL_LED_EN 15
#endif

#ifdef V3
#define WIFI_BTN 13
#define WIFI_LED 14
#define INPUT_A 35
#define INPUT_B 39
#define INPUT_C 34
#define INPUT_D 36
#define OUTPUT_A 4
#define OUTPUT_B 12
#define OUTPUT_C 2
#define OUTPUT_D 16
#define EN_I2C 13
#define RL_LED_EN 15
#endif
bool colen[13];
float column[20];
bool rc_1970day = 0, rc_thisday = 0;
int header_size = 0;
int logColumn = 13;
int logging_indicator = 0;
std::string use_contain = "";
std::string use_header  = "";
std::string header_file  = "epoch;column1;column2;column3;column4;column5;column6;column7;column8;column9;column10;column11;column12;column13;column14;column15;column16;column17;column18;column19;column20\r\n";

long offline_epoch  = 0;
long online_epoch = 0;
bool NTPflag = false;
bool NTPflag_z = false;
long time_day_epoch;
int day_now;
//i2c and sensor
int enablei2c = 13;
int Vmax = 611;   //depend on Rsense, what maximum voltage that creates 275mV between the voltage input sensor
int Imax = 30;    //depend on IC specifications
ACS71020 mySensor{Vmax, Imax};
static struct mgos_bme280 *bme76 = NULL;
static struct mgos_bme280 *bme77 = NULL;
static struct mgos_sht31 *SHTx44 = NULL;
static struct mgos_sht31 *SHTx45 = NULL;
float sensor_value[4] = {0,0,0,0};
float gain = 0.25;
SparkFun_Ambient_Light light48(0x48);
SparkFun_Ambient_Light light10(0x10);
MCP9600 MCPx60;
MCP9600 MCPx67;

int time2 = 100;

unsigned int panel_brightness = 0;
unsigned int remote_brightness = 0;
bool IO14_en = false;
int LED_opt = 0;
int LED_prog = 0;

int input1_mode = 1;
bool input1_as_sens = false;
bool input1_as_ovr = false;
int input1_ovr_limit = 0; // 1-> always, 2 -> duration, 3 -> until
long input1_ovr_val = 0;
int input1_ovr_action = 0; // determine override action after triggered

int input2_mode = 1;
bool input2_as_sens = false;
bool input2_as_ovr = false;
int input2_ovr_limit = 0; // 1-> always, 2 -> duration, 3 -> until
long input2_ovr_val = 0;
int input2_ovr_action = 0; // determine override action after triggered

bool ovr_limit_A_en = 0; // flag to indicate that overriding is still due
bool ovr_limit_B_en = 0;
bool ovr_limit_C_en = 0;
bool ovr_limit_D_en = 0;

bool override_en_status_A = false; //flag to indicate ovr_limit_X_en status
bool override_en_status_B = false;
bool override_en_status_C = false;
bool override_en_status_D = false;

int input1_saved_state = -1;
int input2_saved_state = -1;
int input3_saved_state = -1;
int input4_saved_state = -1;

int input3_mode = 1;
bool input3_as_sens = false;
bool input3_as_ovr = false;
int input3_ovr_limit = 0; // 1-> always, 2 -> duration, 3 -> until
long input3_ovr_val = 0;
int input3_ovr_out = 0; // based on output id (1 to 4)
int input3_ovr_action = 0; // determine override action after triggered

int input4_mode = 1;
bool input4_as_sens = false;
bool input4_as_ovr = false;
int input4_ovr_limit = 0; // 1-> always, 2 -> duration, 3 -> until
long input4_ovr_val = 0;
int input4_ovr_out = 0; // based on output id (1 to 4)
int input4_ovr_action = 0; // determine override action after triggered

int en_ovr_output_A = -1; //flag to indicate that output is overriden
int override_pin_A = 0;
int en_ovr_output_B = -1; //flag to indicate that output is overriden
int override_pin_B = 1;
int en_ovr_output_C = -1; //flag to indicate that output is overriden
int override_pin_C = -1;
int en_ovr_output_D = -1; //flag to indicate that output is overriden
int override_pin_D = -1;

std::string override_out_status = "-1,-1";

///program backend variable
int prog_link_name[4] = {-1,-1,-1,-1}; //A, B, C, D -> detect lowest ID and enabled; and put program ID here
int prog_link_name_z[4] = {-1,-1,-1,-1}; //delayed
int prog_link_state[4] = {0,0,0,0}; //indicate program state -> based on date etc
const char* list_prog_name[10] = {"program1.json", "program2.json", "program3.json", "program4.json", "program5.json", "program6.json",
							  "program7.json", "program8.json", "program9.json", "program10.json"};
int prog_pin_state[4] = {0,0,0,0}; //A, B, C, D ->indicate pin output status
int prog_timer_state[4] = {0,0,0,0}; //indicate if timer is on or off or idle; 0 -> idle, 1-> on is working, 2 -> off is working
									 // 3 -> on is finished, 4-> off is finished

mgos_timer_id prog_timer_id[4];
mgos_timer_id prog_led_timer;
int ext_toggle_state[4] = {0,0,0,0};
int ext_PB_state[4] = {0,0,0,0};
int vt_PB_state[4] = {0,0,0,0};

/// sensors and logging variable
//char[7] sensor_addr_list = {0x10, 0x48, 0x60, 0x61, 0x67, 0x76, 0x77};
std::vector<char> sensor_addr_list;
std::vector<bool> sensor_ext;
std::vector<bool> sensor_online;
std::vector<std::string> sensor_name;
std::vector<bool> sensor_en;
std::vector<bool> sensor_init;

std::vector<std::string> sensor_name_log; //put sensor name specification as logging column name
std::vector<float> sensor_value_log; //keep sensor value based on sensor name
std::vector<bool> sensor_en_log; //indicate that column is logging enabled
std::vector<std::string> sensor_label_log;
int led_red_status = 0;
int dec_place_global;
bool dev_mode_global;
unsigned long current_ver_key = 0;
bool ap_button_mode = false;
//addition variable V2
char wifi_mode = 0; // 1 -> STA ; 2 -> AP; 3 -> OFF
void load_wifi_setting();
void fade_blink(int pin);

mgos_timer_id wifi_blink_timer;
struct mgos_config_wifi_sta cfg_sta;
struct mgos_config_wifi_ap cfg_ap;


static void wifi_led_ctrl(void *arg) {
	/*
   	if(wifi_mode == 2){
   		fade_blink(WIFI_LED);
	}else if(wifi_mode == 1){
		if(mgos_wifi_get_status() != 3){
			static int a = 0;
			if(a%2 == 0){
				mgos_pwm_set(WIFI_LED, 100, (float)panel_brightness/65535);	
			}else{
				//mgos_pwm_set(WIFI_LED, 100, 0);
				mgos_gpio_write(WIFI_LED, 0);
			}
			a++;
		}else{
	   		mgos_pwm_set(WIFI_LED, 100, (float)panel_brightness/65535);
	   		//mgos_gpio_write(WIFI_LED, 1);
		}
	}
    (void) arg;
	*/
}


//V2 ///////////////////////////////////////////////////////////////////

//function prototype
void appendFile(const char* path, const char* message); //append message to a file (tested)
long getEpoch(const char* data_in); //get epoch value from csv row string (tested)
std::string getHeader_file(); //get header string based on desired column and calculate header size including epoch column (tested)
long read_epoch_last_entry(const char* path); //read last entry of file and return the epoch (tested)
std::string file_get_header(const char* path);
int getColumnNum(const char* path); //get column number in file read path including epoch
std::string getColumnVal(int column, std::string data_in); //get column value of selected column from a string, first column is 0 (tested)
long read_epoch_first_entry(const char* path); //read first entry of file and then return the first epoch (tested)
bool exists(const char* path); //check if file exists or not (tested)
void migrate(const char* original, const char* destination, int interval, long difference, bool migrate2new);//migrate to destination, keep difference range in origin (tested)
void move_old2new(const char* origin, const char* destination, long time_difference);//copy content to destination with epoch offset (tested)
void manageOffline_files();//function that moves old files to current files with automated time difference (tested);
void contain_logging();//function that modify use_contain variable based on desired column (tested)
void header_column_logging();//function that ajusting file column number and header string (picked from last version)
void trimfile(const char* path);//function that trims file when reaching upper limit size to lower limit size (tested)
void online_HouseKeeping();//(picked from last version)
void offline_HouseKeeping();//(picked from last version)
void oldcheck_onboot();//check old files adjusts offline epoch (picked from last version)
void check_program_en(const char* file_read, bool& prog_en, int& control_opt); //tested -> read json file program.json
void check_program_name(); //tested -> retrive program en and output option from program json
int check_program_state(const char* file_read);  //tested
void adjust_prog_pin();
int pri_chk_cond(std::string input, float data_input); //tested
int sec_chk_cond(std::string input, float data_input, int& op);	
int check_program_output(const char* file_read); 
int pri_op_sec(int op, int pri_cond, int sec_cond); //tested
void setup_timer_program(int ctrl_pin, long value); //tested
void led_red_ctrl(unsigned int input);
int read_R1_button(int button);
int read_R2_button(int button);
int read_RPB_button(int button);
int read_R4_button(int button);
int read_R1_toggle(int input);
int read_R2_toggle(int input);
int read_R3_toggle(int input);
int read_R4_toggle(int input);
void check_override_func();
unsigned long randomGen();
void led_red_ctrl_asprog(void *arg);
void modify_program_en(const char* file_name, bool value);
void persistent_to_setting(){
	//read persistent
	char* buff = (char*)malloc(1024);
	long time_offset = 0;
	buff = json_fread("persistent_info.json");
	
	char* buff_b = (char*)malloc(512);
	json_scanf(buff, strlen(buff), "{wifi: %Q, timezone:%ld}", &buff_b, &time_offset);
	struct json_token t;
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",0, &t);
	int mode;
	char* ssid; char* pass;
	char* ssid1; char* pass1;
	char* ssid2; char* pass2; 
	
	json_scanf(buff_b, strlen(buff_b), "{mode: %d}", &mode);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass);
	
	//sta 1
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",1, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid1);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass1);
	
	//sta2
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",2, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid2);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass2);
	
	//modify setting
	const char *tmp_file_name = "tmp.json";
	char *content = (char*) malloc(1024);
	content = json_fread("setting.json");
	FILE *fp = fopen(tmp_file_name, "w");
	struct json_out out = JSON_OUT_FILE(fp);
	json_setf(content, strlen(content), &out, ".wifi", "{mode: %d,  cfg:[{ssid:%Q, pass:%Q}, {ssid:%Q, pass:%Q}, {ssid:%Q, pass:%Q}]}", mode,
	ssid, pass, ssid1, pass1, ssid2, pass2);
	//json_setf(content, strlen(content), &out, ".timezone", "%ld", time_offset);
	fclose(fp);
	remove("setting.json");
	rename(tmp_file_name, "setting.json");
	
	content = json_fread("setting.json");
	fp = fopen(tmp_file_name, "w");
	out = JSON_OUT_FILE(fp);
	json_setf(content, strlen(content), &out, ".timezone", "%ld", time_offset);
	fclose(fp);
	json_prettify_file(tmp_file_name);  // Optional
	remove("setting.json");
	rename(tmp_file_name, "setting.json");
	free(content);	free(buff); free(buff_b);
}
void setting_to_persistent(){
	//read setting
	char* buff = (char*)malloc(1024);
	long time_offset = 0;
	buff = json_fread("setting.json");
	
	char* buff_b = (char*)malloc(512);
	json_scanf(buff, strlen(buff), "{wifi: %Q, timezone:%ld}", &buff_b, &time_offset);
	
	struct json_token t;
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",0, &t);
	int mode;
	char* ssid; char* pass;
	char* ssid1; char* pass1;
	char* ssid2; char* pass2; 
	json_scanf(buff_b, strlen(buff_b), "{mode: %d}", &mode);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass);
	
	//sta 1
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",1, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid1);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass1);
	
	//sta2
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",2, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid2);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass2);
	//copy to persistent
	json_fprintf("persistent_info.json", "{wifi: {mode: %d,  cfg:[{ssid:%Q, pass:%Q}, {ssid:%Q, pass:%Q}, {ssid:%Q, pass:%Q}]}, timezone: %ld}", 
	mode, ssid, pass, ssid1, pass1, ssid2, pass2, time_offset);
	json_prettify_file("persistent_info.json");
	free(buff); free(buff_b);
}
void scan_sensor_at_boot();
bool check_sensor(char addr);
int get_index(std::vector<char> v, char K);
int get_index_name(std::vector<std::string> v, std::string K);
void init_sensor();
void update_sensor_logging(bool update = false);
void update_sensor_info();

//prog timer function ;
static void prog_timer1_cb (void *arg){
	mgos_clear_timer(prog_timer_id[0]);
	if(prog_timer_state[0] == 1){
		prog_timer_state[0] = 3;
	}else if(prog_timer_state[0] == 2){
		prog_timer_state[0] = 4;
	}
	(void) arg;
}
static void prog_timer2_cb (void *arg){
	mgos_clear_timer(prog_timer_id[1]);
	if(prog_timer_state[1] == 1){
		prog_timer_state[1] = 3;
	}else if(prog_timer_state[1] == 2){
		prog_timer_state[1] = 4;
	}
	(void) arg;
}
static void prog_timer3_cb (void *arg){
	mgos_clear_timer(prog_timer_id[2]);
	if(prog_timer_state[2] == 1){
		prog_timer_state[2] = 3;
	}else if(prog_timer_state[2] == 2){
		prog_timer_state[2] = 4;
	}
	(void) arg;
}
static void prog_timer4_cb (void *arg){
	mgos_clear_timer(prog_timer_id[3]);
	if(prog_timer_state[3] == 1){
		prog_timer_state[3] = 3;
	}else if(prog_timer_state[3] == 2){
		prog_timer_state[3] = 4;
	}
	(void) arg;
}
//function prototype
static void setting_modifier(struct mg_rpc_request_info *ri, void *cb_arg, struct mg_rpc_frame_info *fi, struct mg_str args);
static void getTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
static void sensor_log_change(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void checkJSONsetting();
void requestDel(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void pushTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void reset_timer(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void get_wifi_status(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void check_access_login(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void change_password(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void validate_cookie(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void request_widget_data(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void dns_advertise(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	//dns_advert = true;
	mg_rpc_send_responsef(ri, "OK");
	mgos_dns_sd_advertise();
}
void check_ap_mode(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	mg_rpc_send_responsef(ri, "{mode:%B, uptime:%f}", ap_button_mode, mgos_uptime());	
}
void virtual_pb_check(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void request_sensor_status(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void request_log_value(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
//function prototype
static void button_check_cb(void *arg){
	int input1 = mgos_adc_read(INPUT_A);
	int input2 = mgos_adc_read(INPUT_B);
	int input3 = 0;
	#ifdef INPUT_C
	input3 = mgos_adc_read(INPUT_C);
	#endif
	int input4 = 0;
	#ifdef INPUT_D
	input4 = mgos_adc_read(INPUT_D);
	#endif
	
	int a = read_R1_button(input1);
	int b = read_R2_button(input2);
	int c = read_RPB_button(input3);
	int d = read_R4_button(input4);
	ext_toggle_state[0] = read_R1_toggle(input1);
	ext_toggle_state[1] = read_R2_toggle(input2);
	ext_toggle_state[2] = read_R3_toggle(input3);
	ext_toggle_state[3] = read_R4_toggle(input4);
	if(ext_PB_state[0] == 0){ext_PB_state[0] = a;}
	if(ext_PB_state[1] == 0){ext_PB_state[1] = b;}
	if(ext_PB_state[2] == 0){ext_PB_state[2] = c;}
	if(ext_PB_state[3] == 0){ext_PB_state[3] = d;}
}
static void timer_cb(void *arg) {
	time_t now;
	time(&now);
	if(now > 946684800){
		online_epoch = now;
		NTPflag = true;
		time_t buff = online_epoch;
		tm *tm_gmt = gmtime(&buff);
		time_day_epoch = tm_gmt->tm_hour * (long)3600;
		time_day_epoch += tm_gmt->tm_min * (long)60;
		time_day_epoch += tm_gmt->tm_sec;
		day_now = tm_gmt->tm_wday;
	}else{
		online_epoch++;
		time_day_epoch = -1;
		day_now = -1;
	}
	//check override function
	check_override_func();
    check_program_name();
    adjust_prog_pin();
    //LOG(LL_WARN, ("day epoch: %ld", time_day_epoch));
    //LOG(LL_WARN, ("prog link : %d, %d, %d, %d", prog_link_name[0], prog_link_name[1], prog_link_name[2], prog_link_name[3]));
	//LOG(LL_WARN, ("prog state: %d, %d, %d, %d", prog_link_state[0], prog_link_state[1], prog_link_state[2], prog_link_state[3]));
	//LOG(LL_WARN, ("pin state: %d, %d, %d, %d", prog_pin_state[0], prog_pin_state[1], prog_pin_state[2], prog_pin_state[3]));
	offline_epoch++;
	//check override function
	ext_PB_state[0] = 0;
	ext_PB_state[1] = 0;
	ext_PB_state[2] = 0;
	ext_PB_state[3] = 0;
	mgos_pwm_set(RL_LED_EN, 333, (float)panel_brightness/65535);
	//mgos_gpio_write(RL_LED_EN, 1);
  (void) arg;
}

static void logging_cb(void *arg){
	//logging code
    update_sensor_info();
    init_sensor();
    for(int i = 0; i < sensor_addr_list.size(); i++){
    	char current_addr = sensor_addr_list.at(i);
    	
    	//sensor_online.at(i) = check_sensor(current_addr); //check sensor if online periodically
    	bool sense_available = sensor_en.at(i) == true && sensor_online.at(i) == true;
    	 //logging is enabled and sensor is online
    		//read actual sensors
    		if(current_addr == 0){
    			int a = get_index_name(sensor_name_log, "relay1");
    			sensor_value_log.at(a) = (sense_available)  ? mgos_gpio_read_out(OUTPUT_A) : -1;
    			sensor_value_log.at(a+1) = (sense_available) ?  mgos_gpio_read_out(OUTPUT_B) : -1;
			}else if(current_addr == 0x61){ //power sensor
    			int a = get_index_name(sensor_name_log, "P61-P");
    			sensor_value_log.at(a) = (sense_available) ? (float)mySensor.getPavg(ONE_SEC) * 0.01 : -1;
				sensor_value_log.at(a+1) = (sense_available)  ? (float)mySensor.getVrms()*0.1 : -1;
    			sensor_value_log.at(a+2) = (sense_available) ? (float)mySensor.getIavg(ONE_SEC) * 0.001 : -1;
    			sensor_en_log.at(a) = sensor_en.at(i);
				sensor_en_log.at(a+1) = sensor_en.at(i);
				sensor_en_log.at(a+2) = sensor_en.at(i);
			}else if(current_addr == 0x76){
				int a = get_index_name(sensor_name_log, "BMEx76-H");
				sensor_value_log.at(a) = (sense_available) ? mgos_bme280_read_humidity(bme76) : -1;
				sensor_value_log.at(a+1) = (sense_available) ?mgos_bme280_read_temperature(bme76) : -1;
				sensor_value_log.at(a+2) = (sense_available) ?mgos_bme280_read_pressure(bme76) : -1;
				sensor_en_log.at(a) = sensor_en.at(i);
				sensor_en_log.at(a+1) = sensor_en.at(i);
				sensor_en_log.at(a+2) = sensor_en.at(i);
			}else if(current_addr == 0x77){
				int a = get_index_name(sensor_name_log, "BMEx77-H");
				sensor_value_log.at(a) = (sense_available) ?mgos_bme280_read_humidity(bme77) : -1;
				sensor_value_log.at(a+1) = (sense_available) ?mgos_bme280_read_temperature(bme77) : -1;
				sensor_value_log.at(a+2) = (sense_available) ?mgos_bme280_read_pressure(bme77): -1;
				sensor_en_log.at(a) = sensor_en.at(i);
				sensor_en_log.at(a+1) = sensor_en.at(i);
				sensor_en_log.at(a+2) = sensor_en.at(i);
			}else if(current_addr == 0x10){
				int a = get_index_name(sensor_name_log, "L10");
				sensor_value_log.at(a) = (sense_available) ? light10.readLight() : (float)-1;
				sensor_en_log.at(a) = sensor_en.at(i);
			}else if(current_addr == 0x48){
				int a = get_index_name(sensor_name_log, "L48");
				sensor_value_log.at(a) = (sense_available) ? light48.readLight() : (float)-1;
				sensor_en_log.at(a) = sensor_en.at(i);
			}else if(current_addr == 0x44){
				int a = get_index_name(sensor_name_log, "SHTx44-T");
				sensor_value_log.at(a) = (sense_available) ? mgos_sht31_getTemperature(SHTx44) : -1;
				sensor_value_log.at(a+1) = (sense_available) ? mgos_sht31_getHumidity(SHTx44) : -1;
				sensor_en_log.at(a) = sensor_en.at(i); sensor_en_log.at(a+1) =sensor_en.at(i); 
			}else if(current_addr == 0x45){
				int a = get_index_name(sensor_name_log, "SHTx45-T");
				sensor_value_log.at(a) = (sense_available) ? mgos_sht31_getTemperature(SHTx45) : -1;
				sensor_value_log.at(a+1) = (sense_available) ? mgos_sht31_getHumidity(SHTx45) : -1;
				sensor_en_log.at(a) = sensor_en.at(i); sensor_en_log.at(a+1) = sensor_en.at(i);
			}else if(current_addr == 0x60){
				int a = get_index_name(sensor_name_log, "T60");
				sensor_value_log.at(a) = (sense_available) ? MCPx60.getThermocoupleTemp() : -1;
				sensor_en_log.at(a) = sensor_en.at(i);
			}else if(current_addr == 0x67){
				int a = get_index_name(sensor_name_log, "T67");
				sensor_value_log.at(a) = (sense_available) ? MCPx67.getThermocoupleTemp() : -1;
				sensor_en_log.at(a) = sensor_en.at(i);
			}	
	}
    contain_logging();
    
	if(NTPflag){
    	if(NTPflag == true && NTPflag_z == false){
    		manageOffline_files();
		}
    	if(logging_indicator != 0) online_HouseKeeping();
	}else{
		if(logging_indicator != 0) offline_HouseKeeping();

	}

	NTPflag_z = NTPflag;
}

enum mgos_app_init_result mgos_app_init(void) {
	//file system initiation
	
  	
  	if(!exists("persistent_info.json")){ //copy from setting to persistent
	  setting_to_persistent();
	}else{
		persistent_to_setting();
	}
	
	if(exists("setting.json")){
		checkJSONsetting();
  	}	
	//i2c and sensor
	Wire.begin();
	LOG(LL_WARN,("scan sensor_on_boot"));
	scan_sensor_at_boot();
	current_ver_key= randomGen();
	header_column_logging();
  	oldcheck_onboot();
  	
	//GPIO init
	mgos_gpio_setup_output(EN_I2C, 1);
  	mgos_gpio_setup_output(OUTPUT_A, 0);
  	mgos_gpio_setup_output(OUTPUT_B, 0);
  
  	#ifdef OUTPUT_C
	mgos_gpio_setup_output(OUTPUT_C,0);
	mgos_gpio_set_mode(OUTPUT_C, MGOS_GPIO_MODE_OUTPUT);
  	#endif
  	
	//mgos_gpio_setup_output(WIFI_LED, 0);
  	mgos_gpio_setup_output(RL_LED_EN, 0);
  	mgos_gpio_setup_input(WIFI_BTN, MGOS_GPIO_PULL_DOWN ); 

	#ifdef INPUT_C
	mgos_gpio_setup_input(INPUT_C, MGOS_GPIO_PULL_DOWN );
	mgos_gpio_set_mode(INPUT_C, MGOS_GPIO_MODE_INPUT);
	mgos_gpio_set_pull(INPUT_C, MGOS_GPIO_PULL_DOWN );
	mgos_adc_enable(INPUT_C);
	#endif
	#ifdef INPUT_D
	mgos_gpio_setup_input(INPUT_D, MGOS_GPIO_PULL_DOWN );
	mgos_gpio_set_mode(INPUT_D, MGOS_GPIO_MODE_INPUT);
	mgos_gpio_set_pull(INPUT_D, MGOS_GPIO_PULL_DOWN );
	mgos_adc_enable(INPUT_D);
	#endif
	
	mgos_gpio_setup_input(INPUT_A, MGOS_GPIO_PULL_DOWN );
	mgos_gpio_set_mode(INPUT_A, MGOS_GPIO_MODE_INPUT);
	mgos_gpio_set_pull(INPUT_A, MGOS_GPIO_PULL_DOWN );
	
	mgos_gpio_setup_input(INPUT_B, MGOS_GPIO_PULL_DOWN );	
	mgos_gpio_set_mode(INPUT_B, MGOS_GPIO_MODE_INPUT);
	mgos_gpio_set_pull(INPUT_B, MGOS_GPIO_PULL_DOWN );
	
	
	mgos_gpio_set_mode(OUTPUT_A, MGOS_GPIO_MODE_OUTPUT);
  	mgos_gpio_set_mode(OUTPUT_B, MGOS_GPIO_MODE_OUTPUT);
	mgos_gpio_set_mode(RL_LED_EN, MGOS_GPIO_MODE_OUTPUT);	
	
	//enabling adc
	mgos_adc_enable(INPUT_A);
	mgos_adc_enable(INPUT_B);
	LOG(LL_WARN,("initiating sensors"));
	init_sensor();
	
	//timer function
	mgos_set_timer(1000 /* ms */, MGOS_TIMER_REPEAT, timer_cb, NULL);
  	mgos_set_timer(10000 /* ms */, MGOS_TIMER_REPEAT, logging_cb, NULL);
   	mgos_set_timer(100, MGOS_TIMER_REPEAT, button_check_cb, NULL);
	//mgos_set_hw_timer(100000, MGOS_TIMER_REPEAT, button_check_cb, NULL);
  	
  	//RPC handler function
	mg_rpc_add_handler(mgos_rpc_get_global(), "setting","", setting_modifier, NULL);
	mg_rpc_add_handler(mgos_rpc_get_global(), "update_sensor_log","", sensor_log_change, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "getTime", "", getTime, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "delReq", "{comm:%Q}", requestDel, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "pushTime", "{epoch:%ld}", pushTime, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "dnsAdvertise", "", dns_advertise, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "req_widget", "", request_widget_data, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "reset_timer", "{file:%Q}", reset_timer, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "wifi.status", "", get_wifi_status, NULL);
	mg_rpc_add_handler(mgos_rpc_get_global(), "login", "{pass:%Q}", check_access_login, NULL);
	mg_rpc_add_handler(mgos_rpc_get_global(), "change_pass", "{old_pass:%Q, new_pass:%Q}", change_password, NULL);
	mg_rpc_add_handler(mgos_rpc_get_global(), "validate_key", "{key:%lu}", validate_cookie, NULL);	
	mg_rpc_add_handler(mgos_rpc_get_global(), "check_ap_mode", "", check_ap_mode, NULL);	
	mg_rpc_add_handler(mgos_rpc_get_global(), "VT.GPIO", "{pin:%d, val: %d}", virtual_pb_check, NULL);		
	mg_rpc_add_handler(mgos_rpc_get_global(), "req.sense_online", "", request_sensor_status, NULL);
	mg_rpc_add_handler(mgos_rpc_get_global(), "req.log_value", "", request_log_value, NULL);
	mgos_msleep(1000);
	LOG(LL_WARN,("wifi initiate"));
	load_wifi_setting();
	return MGOS_APP_INIT_SUCCESS;
}


void request_widget_data(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	char* prog_name_b = (char*)malloc(20);
	char* prog_state_b = (char*)malloc(9);
	char* pin_state_b = (char*)malloc(9);
	char* override_active_status = (char*)malloc(5);
	sprintf(override_active_status, "%d%d%d%d",0,0,0,0 );
	sprintf(prog_name_b, "%d,%d,%d,%d", prog_link_name[0], prog_link_name[1], prog_link_name[2], prog_link_name[3]);
	sprintf(prog_state_b, "%d%d%d%d", prog_link_state[0], prog_link_state[1], prog_link_state[2], prog_link_state[3]);
	sprintf(pin_state_b, "%d%d%d%d", prog_pin_state[0], prog_pin_state[1], led_red_status, prog_pin_state[3]);
	mg_rpc_send_responsef(ri, "{IO_info: {prog_name: %Q, prog_state: %Q, pin_state: %Q}, temp:%.1f, hump:%.1f, light:%.1f, power:%.1f, A:%d, B:%d, LED:%d, IO14:%d, ovr_out:%Q, ovr_en:%Q}",prog_name_b, prog_state_b, pin_state_b,sensor_value[0], sensor_value[1], sensor_value[2], sensor_value[3],prog_pin_state[0], prog_pin_state[1], led_red_status, prog_pin_state[3], override_out_status.c_str(), override_active_status);
	free(prog_name_b); free(prog_state_b); free(pin_state_b);
	(void) cb_arg;
	(void) fi;	
}
void get_wifi_status(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
int wifi_rssi = mgos_wifi_sta_get_rssi();
const char* ap_ip = mgos_sys_config_get_wifi_ap_ip();
const char* ap_ssid = mgos_sys_config_get_wifi_ap_ssid();
const char* ap_pass = mgos_sys_config_get_wifi_ap_pass();
bool ap_en = mgos_sys_config_get_wifi_ap_enable();
bool sta_en = mgos_sys_config_get_wifi_sta_enable();
sta_en |= mgos_sys_config_get_wifi_sta1_enable();
sta_en |= mgos_sys_config_get_wifi_sta2_enable();
mg_rpc_send_responsef(ri, "{ap_en: %B, sta_en: %B, sta_rssi: %d, ap_ip: %Q, ap_ssid: %Q, ap_pass: %Q}", ap_en, sta_en, wifi_rssi,ap_ip, ap_ssid, ap_pass);
//free(ap_ip); free(ap_ssid); free(ap_pass);
(void) cb_arg;
(void) fi;	
}
bool check_password(std::string input){
	char* buff = (char*)malloc(128); 
	//find out file size
	buff = json_fread("8f2js9ddfk.json"); //random file name for password file
	char* mystring = (char*)malloc(120);
	json_scanf(buff, strlen(buff), "{pass:%Q}", &mystring);
	if(strcmp(input.c_str(), mystring) == 0){
		free(mystring);
		return true;
	}else{
		free(mystring);
		return false;
	}
}
void validate_cookie(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	unsigned long ver_key_local;
	if (json_scanf(args.p, args.len, ri->args_fmt, &ver_key_local) == 1) {
		if(current_ver_key == ver_key_local){
			mg_rpc_send_responsef(ri, "{status: confirm}", current_ver_key);
		}else{
			mg_rpc_send_responsef(ri, "{status: illegal}", current_ver_key);
		}
	}
}
void check_access_login(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	char* pass_buff = (char*)malloc(64);
	if (json_scanf(args.p, args.len, ri->args_fmt, &pass_buff) == 1) {
   		if(check_password(pass_buff)){
   			current_ver_key = randomGen();
   			mg_rpc_send_responsef(ri, "{status: authorized, key:%lu}", current_ver_key);	
		}else{
			mg_rpc_send_responsef(ri, "{status: unauthorized}");
		}	
		free(pass_buff);
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	free(pass_buff);
    	return;
  	}
}
void change_password(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	char* pass_buff = (char*)malloc(64);
	char* new_pass = (char*)malloc(64);
	if (json_scanf(args.p, args.len, ri->args_fmt, &pass_buff, &new_pass) == 2) {
   		if(!check_password(pass_buff) && !(ap_button_mode && mgos_uptime() < 300.0)){
   			mg_rpc_send_responsef(ri, "{status: unauthorized}");
		}else{
			json_fprintf("8f2js9ddfk.json", "{pass: %Q}", new_pass);
			mg_rpc_send_responsef(ri, "{status: confirm}");
		}	
		free(pass_buff);
		free(new_pass);
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	free(new_pass);
		free(pass_buff);
    	return;
  	}
}
//V2////////////////////////////////////////////////////////////////////////////////////////

void load_wifi_setting(){
	struct json_token t;
  	//char* IP;char* SN;char* GW;
  	int mode;
  	char* ssid; char* pass;
	char* ssid1; char* pass1;
	char* ssid2; char* pass2;  	
  	//bool static_en = false;
	char* buff = (char*)malloc(1024);
	buff = json_fread("setting.json");
	char* buff_b = (char*)malloc(512);
	json_scanf(buff, strlen(buff), "{wifi: %Q}", &buff_b);
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",0, &t);
	//json_scanf_array_elem(buff, strlen(buff), ".static_IP_conf", 0, &t);
	//json_scanf(t.ptr, t.len, "{enable: %B}", &static_en);
	json_scanf(buff_b, strlen(buff_b), "{mode: %d}", &mode);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass);
	
	//sta 1
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",1, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid1);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass1);
	
	//sta2
	json_scanf_array_elem(buff_b, strlen(buff_b), ".cfg",2, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid2);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass2);
	
	int a = mgos_gpio_read(WIFI_BTN);
	free(buff);
	free(buff_b);
	
	if(a == 1){
		LOG(LL_WARN,("ap mode override"));
		ap_button_mode = true;
		wifi_mode = 2;
		mgos_sys_config_set_wifi_ap_enable(true);
		mgos_sys_config_set_wifi_sta_enable(false);
		mgos_sys_config_set_wifi_sta1_enable(false);
		mgos_sys_config_set_wifi_sta2_enable(false);
		mgos_wifi_setup((struct mgos_config_wifi *) mgos_sys_config_get_wifi());
		wifi_blink_timer = mgos_set_timer(10, MGOS_TIMER_REPEAT, wifi_led_ctrl, NULL);
		return;	
	}
	
	if(mode == 1 || mode == 4){
	
	    wifi_mode = 1;
	    if(mode == 4){
	    	mgos_sys_config_set_wifi_ap_enable(true);
		}else{
			mgos_sys_config_set_wifi_ap_enable(false);
		}
	    if(strcmp(ssid, "") != 0){
		mgos_sys_config_set_wifi_sta_ssid(ssid);
		mgos_sys_config_set_wifi_sta_pass(pass);
		mgos_sys_config_set_wifi_sta_enable(true);
		}else{
			mgos_sys_config_set_wifi_sta_enable(false);
		}
		if(strcmp(ssid1, "") != 0){
		mgos_sys_config_set_wifi_sta1_ssid(ssid1);
		mgos_sys_config_set_wifi_sta1_pass(pass1);
		mgos_sys_config_set_wifi_sta1_enable(true);
		}else{
			mgos_sys_config_set_wifi_sta1_enable(false);
		}
		if(strcmp(ssid2, "") != 0){
		mgos_sys_config_set_wifi_sta2_ssid(ssid2);
		mgos_sys_config_set_wifi_sta2_pass(pass2);
		mgos_sys_config_set_wifi_sta2_enable(true);
		}else{
			mgos_sys_config_set_wifi_sta2_enable(false);
		}
		mgos_wifi_setup((struct mgos_config_wifi *) mgos_sys_config_get_wifi());
		
		wifi_blink_timer = mgos_set_timer(100, MGOS_TIMER_REPEAT, wifi_led_ctrl, NULL);
		
		return;
	}else if(mode == 3){ ///both sta and AP off
		wifi_mode = 3;
		mgos_sys_config_set_wifi_ap_enable(false);
		mgos_sys_config_set_wifi_sta_enable(false);
		mgos_sys_config_set_wifi_sta1_enable(false);
		mgos_sys_config_set_wifi_sta2_enable(false);
		mgos_wifi_setup((struct mgos_config_wifi *) mgos_sys_config_get_wifi());
		//mgos_gpio_write(WIFI_LED, false);
	}else if(mode == 2){
		mgos_sys_config_set_wifi_ap_enable(true);
		mgos_sys_config_set_wifi_sta_enable(false);
		mgos_sys_config_set_wifi_sta1_enable(false);
		mgos_sys_config_set_wifi_sta2_enable(false);
		mgos_wifi_setup((struct mgos_config_wifi *) mgos_sys_config_get_wifi());
		wifi_blink_timer = mgos_set_timer(10, MGOS_TIMER_REPEAT, wifi_led_ctrl, NULL);
		wifi_mode = 2;
		return;
	}
}

void fade_blink_remote_led(){
	static unsigned int PWM_val = 0;
    static char index = 0;
    #ifdef OUTPUT_C
    mgos_pwm_set(OUTPUT_C, 1000, (float)PWM_val/65535);
    #endif
    if(index == 0){
      long buff = (long)PWM_val + (655);
      if(buff >= 65535){
        //no change value
        PWM_val = 65535;
        index = 1;
      }else{
        PWM_val = (unsigned int)buff;
      }
    }else{
      long buff = (long)PWM_val - (655);
      if(buff <= 0){
        PWM_val = 0;
        index = 0;
      }else{
        PWM_val = (unsigned int)buff;
      }
	    }
}


void fade_blink(int pin){
	static unsigned int PWM_val = 0;
    static char index = 0;
    mgos_pwm_set(pin, 1000, (float)PWM_val/65535);
    if(index == 0){
      long buff = (long)PWM_val + (655);
      if(buff >= 65535){
        //no change value
        PWM_val = 65535;
        index = 1;
      }else{
        PWM_val = (unsigned int)buff;
      }
    }else{
      long buff = (long)PWM_val - (655);
      if(buff <= 0){
        PWM_val = 0;
        index = 0;
      }else{
        PWM_val = (unsigned int)buff;
      }
    }
}
//V2////////////////////////////////////////////////////////////////////////////////////////

void appendFile(const char* path, const char* message){ //append message to a file (tested)
	FILE * file = fopen(path, "a");
	fprintf(file, "%s", message);
	fclose(file);
}
long getEpoch(const char* data_in){//get epoch value from csv row string (tested)
	std::string buff;
	buff = data_in;
	int a = buff.find(";");
	buff = buff.substr(0, a);
	long ret = std::stol(buff);
	return ret;
}
long read_epoch_last_entry(const char* path){//read last entry of file and return the epoch (tested)
	FILE * file = fopen(path, "r");
	if (file == NULL){
		fclose(file);
		return -1; //no file
	}
	fseek (file, 0, SEEK_END);  
	//find file size 
	long size = ftell(file);
	
	if(size <= header_size){//only contain header or empty
		fclose(file);
		return -1;
	}
	//file pointer at last line before \n
	fseek (file, -3, SEEK_END);  
	char c = fgetc(file);
	while(c != '\n'){
		fseek (file, -2, SEEK_CUR);
		c = fgetc(file);
	}
	char* buff = (char*)malloc(256);
	fgets(buff, 255, file);
	long a = getEpoch(buff);
	free(buff);
	fclose(file);
	return a;
}
std::string getHeader_file(){//get header string based on desired column and calculate header size including epoch column (tested)
  std::string ret = "epoch";
  for(int i = 0; i < sensor_name_log.size() ; i++){
  	//if(i == 0) ret += ";";
  	if(sensor_en_log.at(i)){
  		ret+=";";
  		ret+= sensor_name_log.at(i);
	}
	
  }
  ret += "\r\n";
  header_size = ret.size();
  return ret;
}

std::string file_get_header(const char* path){
	FILE * file = fopen(path, "r");
	if (file == NULL){
		fclose(file);
		return ""; //no file
	}
	char* buff_ori = (char*)malloc(256);
	fgets(buff_ori, 256, file);
	std::string ret = buff_ori;
	free(buff_ori);
	return ret;
}
int getColumnNum(const char* path){ //get column number in file read path including epoch (tested)
  FILE * file = fopen(path, "r");
  if(file == NULL){
  	fclose(file);
  	return 0;
  }
  int column = 0;
  char c = fgetc(file);
  while(c != '\n'){
    if( c == ';'){
      column++;
    }
    c = fgetc(file);
  }
  fclose(file);
  column++;
  return column;
}
std::string getColumnVal(int column, std::string data_in){ //get column value of selected column from a string, first column is 0 (tested)
  int a = 0;
  int a_z = 0;
  std::string ret = "";
  int something = data_in.find('\r');
  if(something == -1){
    something = data_in.find('\n');
  }
  data_in = data_in.substr(0,something);
  while(column != -1){
    a = data_in.find(';', a_z); 
    ret = data_in.substr(a_z, a-a_z);
	a_z = a+1;
    column--;
  }
  return ret;
}
long read_epoch_first_entry(const char* path){//read first entry of file and then return the first epoch (tested)
	FILE * file = fopen(path, "r");
	if (file == NULL){
		fclose(file);
		return -1; //no file
	}
	fseek (file, 0, SEEK_END);  
	//find file size 
	long size = ftell(file);
	
	if(size <= header_size){//only contain header or empty
		fclose(file);
		return -1;
	}
	//file pointer at beginning
	fseek (file, header_size, SEEK_SET);
	char c = fgetc(file);
	std::string buff;
	//char* pos = buff;
	while(c != ';'){
		buff+=c;
		c = fgetc(file);
	}
	fclose(file);
	//buff = pos;
	long ret = std::stol(buff);
	return ret;
}
bool exists(const char* path){ //check if file exists or not (tested)
	FILE * file = fopen(path, "r");
	if (file == NULL){
		fclose(file);
		return false;
	}else{
		fclose(file);
		return true;
	}

}
void migrate(const char* original, const char* destination, int interval, long difference, bool migrate2new){//migrate to destination, keep difference range in origin (tested)
	
	long epoch_z = 0;
	long last_epoch = read_epoch_last_entry(original);
	bool finish_move = false;
	int avg_index[20] = {};
	float avg_col[20] = {};
	
	bool firsttime = true;  //variable that indicates that destination file is only header or empty
	//proceed to check if destination exists or not
	if(!exists(destination)){
   		//still first time
   		appendFile(destination, use_header.c_str());
  	}else{
   		//already exists
    	epoch_z = read_epoch_last_entry(destination);
   		if(epoch_z > -1){
     		firsttime = false;
		}
	}
  
	//proceed to open origin file
	FILE * file_ori = fopen(original, "r");
	if(file_ori == NULL){
		fclose(file_ori);
		return;
	}	//failed to open origin file
	
	//proceed to open destination file
	FILE * file_dest = fopen(destination, "a");
	if(file_dest == NULL){
		fclose(file_dest);
		return;
	}   //failed to open destined file
	
	//proceed to create buffer file
	FILE * file_buff = fopen("/mnt/buffer.csv", "a");
	if(file_buff == NULL){
		fclose(file_buff);
		return;
	}   //failed to create buffer file
	fprintf(file_buff, "%s", use_header.c_str());
	char* buff_ori = (char*)malloc(256);
    fseek(file_ori, header_size, SEEK_SET);
    
	while (fgets(buff_ori, 256, file_ori)){//read file line by line offset with header
		//scanning string line 
		mgos_wdt_feed();
		int col_scan_index = 0;
		while(col_scan_index < logColumn){
			std::string col_val = getColumnVal(col_scan_index+1, buff_ori);
			if(col_val != ""){//not an empty column
				avg_col[col_scan_index] += atof(col_val.c_str());
				avg_index[col_scan_index]++;
			}
			col_scan_index++;
		}//Eo scanning string line
		
		//checking if file firsttime or not
		if(firsttime){
			epoch_z = getEpoch(buff_ori);
			//if not first time then print first line to destination file
			if(migrate2new){
				fprintf(file_dest, "%s", buff_ori);
			}
			//clearing array
			std::fill(avg_col,avg_col+20, 0);
			std::fill(avg_index,avg_index+20, 0);
			firsttime = false;
		}else{
			long epoch_now = getEpoch(buff_ori);
			if (!finish_move && epoch_now - epoch_z >= interval){
				if(last_epoch - epoch_now < difference){
					finish_move = true;
					fprintf(file_buff, "%s", buff_ori);
				}else if (last_epoch - epoch_now == difference){
					finish_move = true;
					int arr_index = 0;
					if(migrate2new){
						fprintf(file_dest, "%ld", epoch_now);
		            //itterate avg_index array --> averaging, put to string
					while(arr_index != logColumn){
		              	fprintf(file_dest, ";");
		              	if(avg_index[arr_index] == 0){ //array is null data
		                	//nothing to add
		              	}else{
		            		float a = avg_col[arr_index]/(float)avg_index[arr_index];    	
		              		fprintf(file_dest, "%.2f", a);
						}
		              arr_index++;
		            }
		            fprintf(file_dest, "\n");
		        	}//if migrate2new
		        	//clear avg_index array
		        	std::fill(avg_col,avg_col+20, 0);
					std::fill(avg_index,avg_index+20, 0);
					fprintf(file_buff, "%s", buff_ori);
				}else{
			
					//itterate avg_index array --> averaging, put to string
					int arr_index = 0;
					if(migrate2new){
						fprintf(file_dest, "%ld", epoch_now);
		            //itterate avg_index array --> averaging, put to string
					while(arr_index != logColumn){
		              	fprintf(file_dest, ";");
		              	if(avg_index[arr_index] == 0){ //array is null data
		                	//nothing to add
		              	}else{
		            		float a = avg_col[arr_index]/(float)avg_index[arr_index];    	
		              		fprintf(file_dest, "%.2f", a);
						}
		              arr_index++;
		            }
		            fprintf(file_dest, "\n");
		        	}//if migrate2new
		            //clear avg_index array
		        	std::fill(avg_col,avg_col+20, 0);
					std::fill(avg_index,avg_index+20, 0);	           
					epoch_z = epoch_now; 
				}
				
			}else if (finish_move){
				fprintf(file_buff, "%s", buff_ori);
			}
		}/*not first time branch*/
		
	}//read file line by line offset with header
	free(buff_ori);
	//closing file
	fclose(file_dest);
	fclose(file_ori);
	fclose(file_buff);
	
	//delete original file
	remove(original);
	rename("/mnt/buffer.csv", original);
}
void move_old2new(const char* origin, const char* destination, long time_difference){//copy content to destination with epoch offset (tested)
  	//proceed to move
	FILE * file_ori = fopen(origin, "r");
	fseek(file_ori, header_size, SEEK_SET);
	if(!exists(destination)){
		appendFile(destination, use_header.c_str());
	}
	FILE * file_dest = fopen(destination, "a");
	char* buff_ori = (char*)malloc(256);
	while (fgets(buff_ori, 256, file_ori)){//read file line by line offset with header
		long off_epoch = getEpoch(buff_ori);
		long new_epoch = off_epoch + time_difference;
		fprintf(file_dest, "%ld", new_epoch);
		
		std::string s = buff_ori;
		int aaaa = s.find(";");
		fprintf(file_dest, "%s", s.substr(aaaa).c_str());
	}
	free(buff_ori);
	fclose(file_ori);
	fclose(file_dest);
  
}
void manageOffline_files(){ //function that moves old files to current files with automated time difference (tested);
      long hour_last_entry = read_epoch_last_entry("/mnt/1970Hour.csv");
      long time_difference = online_epoch - offline_epoch;
      if(hour_last_entry > -1){
        if(hour_last_entry > offline_epoch){
          time_difference = online_epoch - hour_last_entry;
        }
      }
      //reset offline epoch value
      offline_epoch = 0;
	  ////////////////////////////////////////////////////////////////////////////////////////
      if (read_epoch_first_entry("/mnt/1970Hour.csv") > -1) { //not empty
        move_old2new("/mnt/1970Hour.csv", "/mnt/thisHour.csv", time_difference);
        remove("/mnt/1970Hour.csv");
      }
      /////////////////////////////////////////////////////////////////////////////////////
}
void contain_logging(){//function that modify use_contain variable based on desired column (tested)
   	//char buff[255];
	std::string buff = "";
 	if(NTPflag){
		buff = std::to_string(online_epoch);
  	}else{
		buff = std::to_string(offline_epoch);
  	}
	
	logging_indicator = 0;
	for(int i = 0; i < sensor_value_log.size() ; i++){
		//LOG(LL_WARN,("%s -> %.2f",sensor_label_log.at(i).c_str(), sensor_value_log.at(i)));
		if(sensor_en_log.at(i) == true){
			buff += ";";
		  	if(sensor_value_log.at(i) != -1){
				std::string num = std::to_string(sensor_value_log.at(i));
				num = (dec_place_global == 0) ? num.substr(0, num.find(",")) : num.substr(0, num.find(".") + dec_place_global + 1);
				buff.append(num);
				logging_indicator++;
			}	//else nothing to appended
		}
	}
	buff.append("\n");
	use_contain = buff;
	//char* load = (char*)malloc(1024);
	//load = json_fread("setting.json");
	//json_scanf(load, strlen(load), "{col3_en: %B, col4_en: %B, col5_en: %B}", &colen[2], &colen[3], &colen[4]);  
	//free(load);
}
void header_column_logging(){//function that ajusting file column number and header string (picked from last version)
	use_header = getHeader_file();
	if(exists("/mnt/thisHour.csv") ){
		bool thishour_col = (file_get_header("/mnt/thisHour.csv") != use_header);
		if(thishour_col){
			//restart file
			LOG(LL_WARN,("restart thishour"));
			remove("/mnt/thisHour.csv");
			appendFile("/mnt/thisHour.csv", use_header.c_str());
		}
	}
	if(exists("/mnt/thisDay.csv")){
		bool thisday_col = (file_get_header("/mnt/thisDay.csv") != use_header);
		if(thisday_col){
			remove("/mnt/thisDay.csv");
			appendFile("/mnt/thisDay.csv", use_header.c_str());
		}
	}
	if(exists("/mnt/thisWeek.csv") ){
		bool thisweek_col = (file_get_header("/mnt/thisWeek.csv") != use_header);
		if(thisweek_col){
			remove("/mnt/thisWeek.csv");
			appendFile("/mnt/thisWeek.csv", use_header.c_str());
		}
	}
	if(exists("/mnt/thisMonth.csv")){
		bool thismonth_col = (file_get_header("/mnt/thisMonth.csv") != use_header);
		if(thismonth_col){
			remove("/mnt/thisMonth.csv");
			appendFile("/mnt/thisMonth.csv", use_header.c_str());
		}
	}	
	if(exists("/mnt/longTermData.csv")){
		bool longterm_col = (file_get_header("/mnt/longTermData.csv") != use_header);
		if(longterm_col){
			remove("/mnt/longTermData.csv");
			appendFile("/mnt/longTermData.csv", use_header.c_str());
		}
	}
	////////////////////////offline//////////////////////////////////////////////
	if(exists("/mnt/1970Hour.csv")){
		bool oldhour_col = (file_get_header("/mnt/1970Hour.csv") != use_header);
		if(oldhour_col){
			//restart file
			remove("/mnt/1970Hour.csv");
			appendFile("/mnt/1970Hour.csv", use_header.c_str());
		}
	}
	if(exists("/mnt/1970Day.csv")){
		bool oldday_col = (file_get_header("/mnt/1970Day.csv") != use_header);
		if(oldday_col){
			remove("/mnt/1970Day.csv");
			appendFile("/mnt/1970Day.csv", use_header.c_str());
		}
	}
	if(exists("/mnt/1970Week.csv")){
		bool oldweek_col = (file_get_header("/mnt/1970Week.csv") != use_header);
		if(oldweek_col){
			remove("/mnt/1970Week.csv");
			appendFile("/mnt/1970Week.csv", use_header.c_str());
		}
	}
	if(exists("/mnt/1970Month.csv")){
		bool oldmonth_col = (file_get_header("/mnt/1970Month.csv") != use_header);
		if(oldmonth_col){
			remove("/mnt/1970Month.csv");
			appendFile("/mnt/1970Month.csv", use_header.c_str());
		}
	}	
	if(exists("/mnt/1970longTermData.csv") ){
		bool oldlongterm_col = (file_get_header("/mnt/1970longTermData.csv") != use_header);
		if(oldlongterm_col){
			remove("/mnt/1970longTermData.csv");
			appendFile("/mnt/1970longTermData.csv", use_header.c_str());
		}
	}
}
void trimfile(const char* path){ //function that trims file when reaching upper limit size to lower limit size (tested)
	FILE * file = fopen(path, "r");

	if(file == NULL){
		fclose(file);
		return;
	}
	fseek (file, 0, SEEK_END);  
	//find file size 
	long file_size = ftell(file);
    //move cursor to file core
    if(file_size >= UPPER_LIMIT_SIZE){
		//trim the file to LOWER_LIMIT_SIZE
		//make a new File First
		long left_size = file_size - LOWER_LIMIT_SIZE;
		fseek(file, header_size, SEEK_SET);		
		FILE * file_dest = fopen("/mnt/buffer.csv", "w");
		//make header
		fprintf(file_dest, "%s", use_header.c_str());
		//trim header size
		fseek(file, left_size, SEEK_CUR);
		char c = fgetc(file);
		while(c != '\n'){
			fseek (file, -2, SEEK_CUR);
			c = fgetc(file);
		}
		
		char* buff_ori = (char*)malloc(256);
		while (fgets(buff_ori, 256, file)){
			fprintf(file_dest, "%s", buff_ori);	
		}
      free(buff_ori);
	  fclose(file_dest);
	  fclose(file);
	  //finish moving
      //delete oldfile
      remove(path);
      //rename buffer
      rename("/mnt/buffer.csv", path);
    }
}
void online_HouseKeeping(){ //(picked from last version)
 	//read and store data every 10 secs
	///////////////////////////////////////////longTermData trimmer /////////////////////////////////////////////////
	static int timer = 10;
	if(timer>= TRIMMER_INTERVAL+10){
		if(!exists("/mnt/longTermData.csv")){ //if longTermData doesn't exist, create new one
		  appendFile("/mnt/longTermData.csv", use_header.c_str());
		}else{
		   trimfile("/mnt/longTermData.csv");
		}    
		timer = 0;
	}
	timer+=10;
	///////////////////////////////////////////longTermData trimmer /////////////////////////////////////////////////
	////////////////////////////////////////////thisMonth///////////////////////////////////////////////////////////
	if(!exists("/mnt/thisMonth.csv")){ //if thisMonth doesn't exist (just deleted) make a new file
		appendFile("/mnt/thisMonth.csv", use_header.c_str());
	}
	long thisMonth_first = read_epoch_first_entry("/mnt/thisMonth.csv");
	long thisMonth_last = read_epoch_last_entry("/mnt/thisMonth.csv");
    if(thisMonth_last - thisMonth_first > 2629743 ){ //not a new file
		//already pass 1 Month
		//move thisMonth to longTermData with 30mins interval
		migrate("/mnt/thisMonth.csv", "/mnt/longTermData.csv", LONGTERM_INTERVAL, 2160000, rc_thisday); //30mins interval, keep first 25 days, migrate the rest
    }
  	////////////////////////////////////////////thisMonth///////////////////////////////////////////////////////////
	////////////////////////////////////////////thisWeek///////////////////////////////////////////////////////////
	if(!exists("/mnt/thisWeek.csv")){ //if thisweek doesn't exist (just deleted) make a new file
		appendFile("/mnt/thisWeek.csv", use_header.c_str());
	}
	long thisWeek_first = read_epoch_first_entry("/mnt/thisWeek.csv");
	long thisWeek_last = read_epoch_last_entry("/mnt/thisWeek.csv");
    if(thisWeek_last - thisWeek_first > 604800){ //not a new file
		//already pass 1 week
		//move thisWeek to thisMonth with 10mins interval
		//LOG(LL_WARN, ("migrating this week"));
		migrate("/mnt/thisWeek.csv", "/mnt/thisMonth.csv", THISMONTH_INTERVAL, 432000, rc_thisday); //10mins interval, keep last 5 days, migrate the rest
    }
  	////////////////////////////////////////////thisWeek///////////////////////////////////////////////////////////
  	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
	if(!exists("/mnt/thisDay.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/mnt/thisDay.csv", use_header.c_str());
	}
	long thisDay_first = read_epoch_first_entry("/mnt/thisDay.csv");
	long thisDay_last = read_epoch_last_entry("/mnt/thisDay.csv");
    if(thisDay_last - thisDay_first > 86400){ //already pass 1 day
		//move thisDay to thisWeek, with 5 mins interval
		//LOG(LL_WARN, ("migrating this day"));
		migrate("/mnt/thisDay.csv", "/mnt/thisWeek.csv", THISWEEK_INTERVAL, 72000, rc_thisday); //5mins interval, keep last 20 hours, migrate the rest  
    }
	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
	/////////////////////////////////////////////thisHour////////////////////////////////////////////////////////////////////
	if(!exists("/mnt/thisHour.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/mnt/thisHour.csv", use_header.c_str());
	}
	if(read_epoch_first_entry("/mnt/thisHour.csv")  <= -1){
		//fresh file, append immediatelly
		appendFile("/mnt/thisHour.csv", use_contain.c_str());  
	}else{ // no fresh file
		if(online_epoch - read_epoch_first_entry("/mnt/thisHour.csv") <= 3600){ //not 1 hour yet, append file
		  //append file
		
		    appendFile("/mnt/thisHour.csv", use_contain.c_str());  
		}else{ //passed 1 hour
		  //migrate thisHour to thisDay with 1 mins interval 
		  // add current data
		    appendFile("/mnt/thisHour.csv", use_contain.c_str()); 
			//LOG(LL_WARN, ("migrating this hour"));
		    migrate("/mnt/thisHour.csv", "/mnt/thisDay.csv", THISDAY_INTERVAL, 2700, rc_thisday); //interval 60 secs, keep last 45 mins, migrate the rest
		}

  }//end of "no fresh file"
  ////////////////////////////////////////////////////thisHour//////////////////////////////////////////////////////////////////
}
void offline_HouseKeeping(){ //(picked from last version)
	//read and store data every 10 secs if offline
	///////////////////////////////////////////1970 longTermData trimmer /////////////////////////////////////////////////
	static int timer =10;
	if(timer>= TRIMMER_INTERVAL+10){
		if(!exists("/mnt/1970longTermData.csv")){ //if 1970longTermData doesn't exist, create new one
			appendFile("/mnt/1970longTermData.csv", use_header.c_str());
		}else{
			trimfile("/mnt/1970longTermData.csv");
		}
		timer = 0;
	}
	timer+=10;
  	///////////////////////////////////////////1970 longTermData trimmer /////////////////////////////////////////////////
  
  	////////////////////////////////////////////1970Month///////////////////////////////////////////////////////////
  	if(!exists("/mnt/1970Month.csv")){ //if 1970Month doesn't exist (just deleted) make a new file
    	appendFile("/mnt/1970Month.csv", use_header.c_str());
  	}
  	long thisMonth_first = read_epoch_first_entry("/mnt/1970Month.csv");
  	long thisMonth_last = read_epoch_last_entry("/mnt/1970Month.csv");
  	if(thisMonth_last - thisMonth_first > 2629743 ){
    	//move thisMonth to longTermData with 30mins interval
      	migrate("/mnt/1970Month.csv", "/mnt/1970longTermData.csv", LONGTERM_INTERVAL,2160000 , rc_1970day); //30mins interval, keep first 25 days, migrate the rest
    } 
 	////////////////////////////////////////////1970Month///////////////////////////////////////////////////////////
  
  	////////////////////////////////////////////1970Week///////////////////////////////////////////////////////////
  	if(!exists("/mnt/1970Week.csv")){ //if 1970week doesn't exist (just deleted) make a new file
    	appendFile("/mnt/1970Week.csv", use_header.c_str());
  	}
	long thisWeek_first = read_epoch_first_entry("/mnt/1970Week.csv");
	long thisWeek_last = read_epoch_last_entry("/mnt/1970Week.csv");
    if(thisWeek_last - thisWeek_first > 604800){ //not a new file
		//already pass 1 week
		//move thisWeek to thisMonth with 10mins interval
		migrate("/mnt/1970Week.csv", "/mnt/1970Month.csv", THISMONTH_INTERVAL, 432000, rc_1970day); //10mins interval, keep first 5 days, migrate the rest
    }
  	////////////////////////////////////////////thisWeek///////////////////////////////////////////////////////////
  
  	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
	if(!exists("/mnt/1970Day.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/mnt/1970Day.csv", use_header.c_str());
	}
	long thisDay_first = read_epoch_first_entry("/mnt/1970Day.csv");
	long thisDay_last = read_epoch_last_entry("/mnt/1970Day.csv");
    if(thisDay_last - thisDay_first > 86400){ //not a new file
		//already pass 1 day
		//move thisDay to thisWeek, with 5 mins interval
		migrate("/mnt/1970Day.csv", "/mnt/1970Week.csv", THISWEEK_INTERVAL,72000, rc_1970day); //5mins interval, keep first 20 hours, migrate the rest
    }
  	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
  
  	//////////////////////////////////////////////thisHour///////////////////////////////////////////////////////////////////
  	if(!exists("/mnt/1970Hour.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/mnt/1970Hour.csv", use_header.c_str());
	}
	if(read_epoch_first_entry("/mnt/1970Hour.csv") <= -1){
    	//fresh file, append immediatelly
    	appendFile("/mnt/1970Hour.csv", use_contain.c_str());  
  	}else{ // no fresh file
		if(offline_epoch - read_epoch_first_entry("/mnt/1970Hour.csv") <= 3600){ //not 1 hour yet, append file
      	//append file
        appendFile( "/mnt/1970Hour.csv", use_contain.c_str());  
      
    }else{ //passed 1 hour
        appendFile("/mnt/1970Hour.csv", use_contain.c_str());
        //migrate thisHour to thisDay with 1 mins interval 
        migrate("/mnt/1970Hour.csv", "/mnt/1970Day.csv", THISDAY_INTERVAL,2700, rc_1970day); //interval 60 secs, keep first 45 mins, migrate the rest
    }

  }//end of "no fresh file"
  /////////////////////////////////////////////thisHour/////////////////////////////////////////////////////////////////////////

}
void oldcheck_onboot() { //check old files adjusts offline epoch (picked from last version)
  long year = -1;
  long year2 = -1;
  long hour_1970_epoch = read_epoch_last_entry("/mnt/1970Hour.csv");
  if (hour_1970_epoch != -1) {
    //find year in 1970 Hour
    year = hour_1970_epoch / (long)31556926;
  }
  long day_1970_epoch = read_epoch_last_entry("/mnt/1970Day.csv");
  if (day_1970_epoch != -1) {
    year2 = day_1970_epoch /(long) 31556926;
    if(year2 != year) {
      remove( "/mnt/1970Hour.csv");
      year = year2;
    }
  }
  if (year == -1) { // no old files
    offline_epoch = 0;
  } else {
    if (year == 45) { //if year is 2015
      year = 65; //change to 2035
    } else {
      year += 1;
    }
    offline_epoch = year * 31556926;
  }
}
//function RPC function
static void sensor_log_change(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	mg_rpc_send_responsef(ri, "OK");
	sensor_en_log.clear();
	sensor_value_log.clear();
	sensor_name_log.clear();
	update_sensor_logging(true);
	header_column_logging();
	(void) cb_arg;
	(void) fi;
	
}
static void setting_modifier(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args) {
 	checkJSONsetting();
	(void) cb_arg;
	(void) fi;
	mg_rpc_send_responsef(ri, "OK");
}
static void getTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args) {
 	long ret = (NTPflag == true) ? online_epoch : offline_epoch;
	mg_rpc_send_responsef(ri, "%ld", ret);
	(void) cb_arg;
	(void) fi;
}
void checkJSONsetting(){
	char* buff = (char*)malloc(1024);
	buff = json_fread("setting.json");
	json_scanf(buff, strlen(buff), "{col1_en: %B, col2_en: %B, col3_en: %B, col4_en: %B, col5_en: %B, col6_en: %B, col7_en: %B, col8_en: %B, col9_en: %B, col10_en: %B, col11_en: %B, col12_en: %B, col13_en: %B, rc_1970day: %B, rc_thisday: %B}"
	,&colen[0], &colen[1], &colen[2], &colen[3], &colen[4], &colen[5], &colen[6], &colen[7], &colen[8], &colen[9], &colen[10], &colen[11], &colen[12], &rc_1970day, &rc_thisday);
	char* buff_b = (char*) malloc(512);
	json_scanf(buff, strlen(buff), "{ctrl_page: %Q}", &buff_b);
	json_scanf(buff_b, strlen(buff_b), "{LED: %d, LED_prog: %d, IO14: %B}", &LED_opt, &LED_prog, &IO14_en);
	
	struct json_token t;
	static bool first = true;
	
	if(!first){
	//setting to persistent
	long time_offset = 0;
	char* buff_x = (char*)malloc(512);
	json_scanf(buff, strlen(buff), "{wifi: %Q, timezone:%ld}", &buff_x, &time_offset);
	json_scanf_array_elem(buff_x, strlen(buff_x), ".cfg",0, &t);
	//LOG(LL_WARN,("%s %ld", buff_x, time_offset));
	int mode;
	char* ssid; char* pass;
	char* ssid1; char* pass1;
	char* ssid2; char* pass2; 
	json_scanf(buff_x, strlen(buff_x), "{mode: %d}", &mode);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass);
	
	//sta 1
	json_scanf_array_elem(buff_x, strlen(buff_x), ".cfg",1, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid1);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass1);
	
	//sta2
	json_scanf_array_elem(buff_x, strlen(buff_x), ".cfg",2, &t);
	json_scanf(t.ptr, t.len, "{ssid: %Q}", &ssid2);
	json_scanf(t.ptr, t.len, "{pass: %Q}", &pass2);
	//copy to persistent
	json_fprintf("persistent_info.json", "{wifi: {mode: %d,  cfg:[{ssid:%Q, pass:%Q}, {ssid:%Q, pass:%Q}, {ssid:%Q, pass:%Q}]}, timezone: %ld}", 
	mode, ssid, pass, ssid1, pass1, ssid2, pass2, time_offset);
	json_prettify_file("persistent_info.json");
	free(buff_x);
	}else{
		first = false;
	}

	//input 1 (PB1)
	json_scanf_array_elem(buff, strlen(buff), ".override",0, &t);
	json_scanf(t.ptr, t.len, "{mode: %d, sensor:%B, output_ovr:%B, ovr_limit: %d, ovr_val: %ld, ovr_act: %d}",
	           &input1_mode, &input1_as_sens, &input1_as_ovr, &input1_ovr_limit, &input1_ovr_val, &input1_ovr_action);
	//input 2 (PB2)
	json_scanf_array_elem(buff, strlen(buff), ".override",1, &t);
	json_scanf(t.ptr, t.len, "{mode: %d, sensor:%B, output_ovr:%B, ovr_limit: %d, ovr_val: %ld, ovr_act: %d}",
	           &input2_mode, &input2_as_sens, &input2_as_ovr, &input2_ovr_limit, &input2_ovr_val, &input2_ovr_action);
	//input 3 (RPB)
	json_scanf_array_elem(buff, strlen(buff), ".override",2, &t);
	json_scanf(t.ptr, t.len, "{mode: %d, sensor:%B, output_ovr:%B, ovr_limit: %d, ovr_val: %ld, output_opt: %d, ovr_act: %d}",
	           &input3_mode, &input3_as_sens, &input3_as_ovr, &input3_ovr_limit, &input3_ovr_val, &input3_ovr_out, &input3_ovr_action);
	//input 4 (RPB)
	json_scanf_array_elem(buff, strlen(buff), ".override",3, &t);
	json_scanf(t.ptr, t.len, "{mode: %d, sensor:%B, output_ovr:%B, ovr_limit: %d, ovr_val: %ld, output_opt: %d, ovr_act: %d}",
	           &input4_mode, &input4_as_sens, &input4_as_ovr, &input4_ovr_limit, &input4_ovr_val, &input4_ovr_out, &input4_ovr_action);
	           
	json_scanf(buff, strlen(buff), "{dec_place: %d, dev_mode: %B}",  &dec_place_global, &dev_mode_global);
	if(LED_opt == 2){
		mgos_clear_timer(prog_led_timer);
		prog_led_timer = mgos_set_timer(1000, MGOS_TIMER_REPEAT, led_red_ctrl_asprog, NULL);
	}else if(LED_opt == 3){
		mgos_clear_timer(prog_led_timer);
		prog_led_timer = mgos_set_timer(10, MGOS_TIMER_REPEAT, led_red_ctrl_asprog, NULL);
	}
	//processing option 
	//LOG(LL_WARN,("%ld", rpb_ovr_val));
	
	json_scanf_array_elem(buff, strlen(buff), ".brightness",0, &t);
	json_scanf(t.ptr, t.len, "{panel: %d, remote: %d}", &panel_brightness, &remote_brightness);
	panel_brightness = panel_brightness << 8;
	remote_brightness = remote_brightness << 8;
	if(!input1_as_ovr){
		if(en_ovr_output_A != -1){ //means override is working
			//return output A to saved state
			prog_pin_state[override_pin_A] = input1_saved_state;
		}
		input1_saved_state = -1;
		en_ovr_output_A = -1; //release override trigger
	}
	if(!input2_as_ovr){
		if(en_ovr_output_B != -1){ //means override is working
			//return output B to saved state
			prog_pin_state[override_pin_B] = input2_saved_state;
		}
		input2_saved_state = -1;
		en_ovr_output_B = -1; //release override trigger
	}
	if(!input3_as_ovr){
		if(en_ovr_output_C != -1){
			prog_pin_state[override_pin_C] = input3_saved_state; //return to saved state
		}
		input3_saved_state = -1;
		override_pin_C = -1;
		en_ovr_output_C = -1;//release override trigger
	}
	if(!input4_as_ovr){
		if(en_ovr_output_D != -1){
			prog_pin_state[override_pin_D] = input4_saved_state; //return to saved state
		}
		input4_saved_state = -1;
		override_pin_D = -1;
		en_ovr_output_D= -1;//release override trigger
	}

	free(buff); free(buff_b);
}
void requestDel(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	char *command = (char*)malloc(11);
	if (json_scanf(args.p, args.len, ri->args_fmt, &command) == 1) {
    	mg_rpc_send_responsef(ri, "OK");
		//LOG(LL_WARN, ("%s delete file requested", command));
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	free(command);
    	return;
  	}
  	if(command[0] == '1'){
      //delete longtermdata
      remove("/mnt/1970longTermData.csv");
    }
    if(command[1] == '1'){
      //delete thismonth
      remove("/mnt/1970Month.csv");
    }
    if(command[2] == '1'){
      //delete thisweek
      remove("/mnt/1970Week.csv");
    }
    if(command[3] == '1'){
      //delete thisDay
      remove("/mnt/1970Day.csv");
    }
    if(command[4] == '1'){
      //delete thishour
      remove("/mnt/1970Hour.csv");
    }
  if(command[5] == '1'){
      //delete longtermdata
      remove("/mnt/longTermData.csv");
    }
    if(command[6] == '1'){
      //delete thismonth
      remove("/mnt/thisMonth.csv");
    }
    if(command[7] == '1'){
      //delete thisweek
      remove("/mnt/thisWeek.csv");
    }
    if(command[8] == '1'){
      //delete thisDay
      remove("/mnt/thisDay.csv");
    }
    if(command[9] == '1'){
      //delete thishour
      remove("/mnt/thisHour.csv");
    }
    free(command);
}
void pushTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	if (json_scanf(args.p, args.len, ri->args_fmt, &online_epoch) == 1) {
    	mg_rpc_send_responsef(ri, "{status: %Q}", "New time is pushed!");
		//LOG(LL_WARN, ("push time requested"));
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	return;
  	}
  	NTPflag = true;
}
////////////////////////////////////////////////////////////////////////PROGRAM ROUTINE BACK END/////////////////////////////////////////////
void check_program_en(const char* file_read, bool& prog_en, int& control_opt){
	char* buff = (char*)malloc(1024);
	buff = json_fread(file_read);
	json_scanf(buff, strlen(buff), "{en: %B, control_opt: %d}", &prog_en, &control_opt); 	
	free(buff);
}

void check_override_func(){	
	static long input1_local_val = 0;
	static long input2_local_val = 0;
	static long input3_local_val = 0;
	static long input4_local_val = 0;
	//toggle mode
	if(ext_toggle_state[0] != 1 && input1_mode == 2 && input1_as_ovr){
		en_ovr_output_A = (ext_toggle_state[0] == 2) ? 0 : 1;
	}else if(ext_toggle_state[0] == 1 && input1_mode == 2 && input1_as_ovr){
		en_ovr_output_A = -1;
	}
	if(ext_toggle_state[1] != 1 && input2_mode == 2 && input2_as_ovr){
		en_ovr_output_B = (ext_toggle_state[1] == 2) ? 0 : 1;
	}else if(ext_toggle_state[1] == 1 && input2_mode == 2 && input2_as_ovr){
		en_ovr_output_B = -1;
	}
	if(ext_toggle_state[2] != 1 && input3_mode == 2 && input3_as_ovr){
		override_pin_C = input3_ovr_out-1;
		en_ovr_output_C = (ext_toggle_state[2] == 2) ? 0 : 1;
	}else if(ext_toggle_state[2] == 1 && input3_mode == 2 && input3_as_ovr){
		en_ovr_output_C = -1;
	}
	if(ext_toggle_state[3] != 1 && input4_mode == 2 && input4_as_ovr){
		override_pin_D = input4_ovr_out-1;
		en_ovr_output_D = (ext_toggle_state[3] == 2) ? 0 : 1;
	}else if(ext_toggle_state[3] == 1 && input4_mode == 2 && input4_as_ovr){
		en_ovr_output_D = -1;
	}
	
	//pb mode
	if((ext_PB_state[0] == 2 || vt_PB_state[0] == 2) && input1_as_ovr && input1_mode == 1){ //long push event// check override function (input1 / PB1)
		ext_PB_state[0] = 0;
		if(vt_PB_state[0] == 2) {vt_PB_state[0] = 0;}
		//check current program en value
		//int prog_en_local =-1; int buff =0;
	
		int pin_control = prog_pin_state[0];
		if(en_ovr_output_A == -1){
			input1_saved_state = pin_control;
			input1_local_val = input1_ovr_val; //reset timer
			LOG(LL_WARN,("trigger A (activate)"));
			if(input1_ovr_action == 2 && pin_control != -1){ //toggle output status
				if(en_ovr_output_A == -1){
					en_ovr_output_A = pin_control == 1 ? 0: 1;
				}else{
					en_ovr_output_A = (en_ovr_output_A == 1) ? 0 : 1;
				}
			}else if(input1_ovr_action == 3 && pin_control != -1){ //turn on output
				en_ovr_output_A  = 1;
			}else if(input1_ovr_action == 4 && pin_control != -1){ // turn off output
				en_ovr_output_A = 0;
			}
		}else{
			en_ovr_output_A = -1;
			LOG(LL_WARN,("trigger A (deactivate)"));
			prog_pin_state[override_pin_A] = input1_saved_state;
			input1_local_val = input1_ovr_val; //reset timer
		}
	}
	
	if((ext_PB_state[1] == 2 || vt_PB_state[1] == 2) && input2_as_ovr && input2_mode == 1){ //long push event// check override function (inputB / PB2)
		ext_PB_state[1] = 0;
		if(vt_PB_state[1] == 2) {vt_PB_state[1] = 0;}
		//check current program en value
		//int prog_en_local =-1; int buff =0;
	
		int pin_control = prog_pin_state[1];
		if(en_ovr_output_B == -1){ //override is inactive,
			LOG(LL_WARN,("trigger B (activate)"));
			input2_saved_state = pin_control; 
			input2_local_val = input2_ovr_val;
			if(input2_ovr_action == 2 && pin_control != -1){ //toggle output status
				if(en_ovr_output_B == -1){
					en_ovr_output_B = pin_control == 1 ? 0: 1;
				}else{
					en_ovr_output_B = (en_ovr_output_B == 1) ? 0 : 1;
				}
			}else if(input2_ovr_action == 3 && pin_control != -1){ //turn on output
				en_ovr_output_B  = 1;
			}else if(input2_ovr_action == 4 && pin_control != -1){ // turn off output
				en_ovr_output_B = 0;
			}
		}else{
			en_ovr_output_B = -1;
			LOG(LL_WARN,("trigger B (deactivate)"));
			prog_pin_state[override_pin_B] = input2_saved_state;
			input2_local_val = input2_ovr_val; //reset timer
		}
	}

	if((ext_PB_state[2] == 2 || vt_PB_state[2] == 2) && input3_as_ovr && input3_mode == 1){ //long push event// check override function (input3 / RPB)
		ext_PB_state[2] = 0;
		if(vt_PB_state[2] == 2) {vt_PB_state[2] = 0;}
		
		int pin_control = prog_pin_state[input3_ovr_out-1];
		override_pin_C = input3_ovr_out-1;
		if(en_ovr_output_C == -1){ //override is inactive
		LOG(LL_WARN,("trigger C (activate)"));
		if(input3_ovr_action == 2 && pin_control != -1){ //toggle output status
			input3_saved_state = pin_control; //saving state
			input3_local_val = input3_ovr_val; //and reset timer
			if(en_ovr_output_C == -1){
				en_ovr_output_C = pin_control == 1 ? 0: 1;
			}else{
				en_ovr_output_C = (en_ovr_output_C == 1) ? 0 : 1;
			}
		}else if(input3_ovr_action == 3 && pin_control != -1){ //turn on output
			en_ovr_output_C  = 1;
		}else if(input3_ovr_action == 4 && pin_control != -1){ // turn off output
			en_ovr_output_C = 0;
		}
		}else{ //override is active
			en_ovr_output_C = -1;
			LOG(LL_WARN,("trigger C (deactivate)"));
			prog_pin_state[override_pin_C] = input3_saved_state;
			input3_local_val = input3_ovr_val; //reset timer
		}
	}

	if((ext_PB_state[3] == 2 || vt_PB_state[3] == 2) && input4_as_ovr == 1 && input4_mode == 1){ //long push event// check override function (input3 / RPB)
		ext_PB_state[3] = 0;
		if(vt_PB_state[3] == 2) {vt_PB_state[3] = 0;}

		int pin_control = prog_pin_state[input4_ovr_out-1];
		override_pin_D = input4_ovr_out-1;
		if(en_ovr_output_D == -1){ //override is active
		LOG(LL_WARN,("trigger D (activate)"));
		input4_saved_state = pin_control; //saving state
		input4_local_val = input4_ovr_val; //and reset timer
		if(input4_ovr_action == 2 && pin_control != -1){ //toggle output status
			if(en_ovr_output_D == -1){
				en_ovr_output_D = pin_control == 1 ? 0: 1;
			}else{
				en_ovr_output_D = (en_ovr_output_D == 1) ? 0 : 1;
			}
		}else if(input4_ovr_action == 3 && pin_control != -1){ //turn on output
			en_ovr_output_D  = 1;
		}else if(input4_ovr_action == 4 && pin_control != -1){ // turn off output
			en_ovr_output_D = 0;
		}
		}else{
			LOG(LL_WARN,("trigger D (deactivate)"));
			en_ovr_output_D = -1;
			prog_pin_state[override_pin_D] = input4_saved_state;
			input4_local_val = input4_ovr_val; //reset timer
		}
	}
	//end of pb mode

	//check limit (pb only) //pb is triggered
	if(en_ovr_output_A != -1 && input1_mode == 1){
		if(input1_ovr_limit == 1){
			ovr_limit_A_en = true;	
		}else if(input1_ovr_limit == 2){ //for
			if(input1_local_val <= 1){
				ovr_limit_A_en = false;
				vt_PB_state[0] = 2;
			}else{
				ovr_limit_A_en = true;
				input1_local_val--;
			}
		}else if(input1_ovr_limit == 3){ //until
			if(time_day_epoch != -1){
				if(time_day_epoch <= input1_local_val){
					ovr_limit_A_en = true;
				}else{
					ovr_limit_A_en = false;
					vt_PB_state[0] = 2; // trigger to deactivate
				}
			}else{
				ovr_limit_A_en = false;
			}
		}
	}else{
		ovr_limit_A_en = false;
	}

	if(en_ovr_output_B != -1 && input2_mode == 1){
		if(input2_ovr_limit == 1){
			ovr_limit_B_en = true;	
		}else if(input2_ovr_limit == 2){ //for
			if(input2_local_val <= 1){
				ovr_limit_B_en = false;
				vt_PB_state[1] = 2; // trigger to deactivate
			}else{
				ovr_limit_B_en = true;
				input2_local_val--;
			}
		}else if(input2_ovr_limit == 3){ //until
			if(time_day_epoch != -1){
				if(time_day_epoch <= input2_local_val){
					ovr_limit_B_en = true;
				}else{
					ovr_limit_B_en = false;
					vt_PB_state[1] = 2; // trigger to deactivate
				}
			}else{
				ovr_limit_B_en = false;
			}
		}
	}else{
	ovr_limit_B_en = false;}

	if(en_ovr_output_C != -1 && input3_mode == 1){
		if(input3_ovr_limit == 1){
			ovr_limit_C_en = true;	
		}else if(input3_ovr_limit == 2){ //for
			if(input3_local_val <= 1){
				ovr_limit_C_en = false;
				vt_PB_state[2] = 2; // trigger to deactivate
			}else{
				ovr_limit_C_en = true;
				input3_local_val--;
			}
		}else if(input3_ovr_limit == 3){ //until
			if(time_day_epoch != -1){
				if(time_day_epoch <= input3_local_val){
					ovr_limit_C_en = true;
				}else{
					ovr_limit_C_en = false;
					vt_PB_state[2] = 2; // trigger to deactivate
				}
			}else{
				ovr_limit_C_en = false;
			}
		}
	}else{
	ovr_limit_C_en = false;}

	if(en_ovr_output_D != -1 && input4_mode == 1){
		if(input4_ovr_limit == 1){
			ovr_limit_D_en = true;	
		}else if(input4_ovr_limit == 2){ //for
			if(input4_local_val <= 1){
				ovr_limit_D_en = false;
				vt_PB_state[3] = 2; // trigger to deactivate
			}else{
				ovr_limit_D_en = true;
				input4_local_val--;
			}
		}else if(input4_ovr_limit == 3){ //until
			if(time_day_epoch != -1){
				if(time_day_epoch <= input4_local_val){
					ovr_limit_D_en = true;
				}else{
					vt_PB_state[3] = 2; // trigger to deactivate
					ovr_limit_D_en = false;
				}
			}else{
				ovr_limit_D_en = false;
			}
		}
	}else{
	ovr_limit_D_en = false;}
	
	int ovr_c_status = en_ovr_output_C != -1 && ((input3_ovr_out == 3 && LED_opt == 1) || (input3_ovr_out == 4 && IO14_en) || (input3_ovr_out < 3))? en_ovr_output_C :-1;
	int ovr_d_status = en_ovr_output_D != -1 && ((input4_ovr_out == 3 && LED_opt == 1) || (input4_ovr_out == 4 && IO14_en) || (input4_ovr_out < 3))? en_ovr_output_D :-1;
	override_out_status = std::to_string(en_ovr_output_A);
	override_out_status += ",";
	override_out_status += std::to_string(override_pin_A);
	override_out_status += "|";
	override_out_status += std::to_string(en_ovr_output_B);
	override_out_status += ",";
	override_out_status += std::to_string(override_pin_B);
	override_out_status += "|";
	override_out_status += std::to_string(ovr_c_status);
	override_out_status += ",";
	override_out_status += std::to_string(override_pin_C);
	override_out_status += "|";
	override_out_status += std::to_string(ovr_d_status);
	override_out_status += ",";
	override_out_status += std::to_string(override_pin_D);
}
void check_program_name(){ //check which output linked to program (id) and check its state
for (int i = 0; i < 10; i++){
	if(exists(list_prog_name[i])){
		//check if program enabled and output option
		bool prog_en;
		int prog_output;
		check_program_en(list_prog_name[i], prog_en, prog_output);
		//LOG(LL_WARN,("check name-> %s, prog en %d, output %d", list_prog_name[i], prog_en, prog_output));
		int x = check_program_state(list_prog_name[i]);
		bool run_prog = prog_en && x == 1;
		if(run_prog && prog_output != 5){ //program is enabled and output is not null
			//somehow user change the output option ->reset link with same output
			for(int j = 0; j < 4 ; j++){
				if(prog_link_name[j] == i+1){prog_link_name[j]=-1;} 
			}
			//normal operation
			if(prog_link_name[prog_output-1] == -1 || prog_link_name[prog_output-1] > i+1){ //priority check 
				if(prog_link_name[prog_output-1] > i+1 ){ //caused by activation of higher priority program
					prog_timer_state[prog_output-1] = 0; //reset timer
				}
				prog_link_name[prog_output-1] = i+1;
				if(prog_link_name[prog_output-1] != prog_link_name_z[prog_output-1]){ //different program controlling same pin // reset pin setting
					prog_pin_state[prog_output-1] = 0;
					prog_link_state[prog_output-1] =0;
					prog_timer_state[prog_output-1] = 0;
					mgos_clear_timer(prog_timer_id[prog_output-1]);
				}
				prog_link_name_z[prog_output-1] = prog_link_name[prog_output-1];
				//check program state
				prog_link_state[prog_output-1] = 1;
				
				/*if(prog_override == -1){
					prog_link_state[prog_output-1] = check_program_state(list_prog_name[i]);
				}else if(rpb_ovr_prog-1 == i){
					prog_link_state[prog_output-1] = prog_override;
				}*/
			
				//check if IO14 en or not
				if((prog_output == 4 && IO14_en == false) ){
					prog_link_state[prog_output-1] = 0;
					prog_pin_state[prog_output-1] = 0;
				}else if(prog_output == 3 && LED_opt != 1){
					prog_link_state[prog_output-1] = 0;
					prog_pin_state[prog_output-1] = 0;
				}
				
				if(prog_link_state[prog_output-1] == 1){ //if program is active
					int pin_res = check_program_output(list_prog_name[i]); //check output
					if(pin_res != -1){ //if not -1 change pin output
						prog_pin_state[prog_output-1] = pin_res;
					}
				}else{ //program is inactive
					prog_pin_state[prog_output-1] = 0;
				}
			}//end of normal operation	
		}//end if prog is enabled
		if(prog_output != -5){
			if(!run_prog && prog_link_name[prog_output-1] == i+1){ ///somehow program is disabled by user
				//LOG(LL_WARN,("disable program %d", (i+1)));
				prog_link_name[prog_output-1] = -1;
			}
		}
	}else{// program is somehow deleted, related output will be -1 (prog_link_name) (does not exist)
		for(int j = 0; j < 4 ; j++){
			if(prog_link_name[j] == i+1){prog_link_name[j]=-1;}
		}
	}
	
}
for(int x =0 ; x < 4 ; x++){ //reset program
	if(prog_link_name[x] == -1){ 
		prog_pin_state[x] = 0;
		prog_link_state[x] =0;
		prog_timer_state[x] = 0;
		mgos_clear_timer(prog_timer_id[x]);
	}
}
//OVERRIDING PROGRAM OUTPUT
if(en_ovr_output_C != -1  && ((ovr_limit_C_en && input3_mode == 1) || (input3_mode == 2))){
	prog_pin_state[override_pin_C] = en_ovr_output_C;
}
if(en_ovr_output_A != -1 && ((ovr_limit_A_en && input1_mode == 1) || (input1_mode == 2)) ){
	prog_pin_state[override_pin_A] = en_ovr_output_A;
}
if(en_ovr_output_B != -1  && ((ovr_limit_B_en && input2_mode == 1) || (input2_mode == 2))){
	prog_pin_state[override_pin_B] = en_ovr_output_B;
}
if(en_ovr_output_D != -1 && dev_mode_global == true  && ((ovr_limit_D_en && input4_mode == 1) || (input4_mode == 2))){
	prog_pin_state[override_pin_D] = en_ovr_output_D;
	//LOG(LL_WARN,("overriding (input D) output pin %d -> %d", (override_pin_D), en_ovr_output_D));
}

}//end of check_program_name() function

int check_program_state(const char* file_read){	
	unsigned long start_date; unsigned long end_date;
	std::string days;
	std::string on_time;
	std::string off_time;
	char* buff = (char*)malloc(1024);
	buff = json_fread(file_read);
	json_scanf(buff, strlen(buff), "{start_date: %ld, end_date: %ld, }", &start_date, &end_date);
	char* days_cr = NULL;
	char* on_time_cr = NULL;
	char* off_time_cr = NULL;
	json_scanf(buff, strlen(buff), "{days_active: %Q, on_time_global: %Q, off_time_global: %Q}", &days_cr, &on_time_cr, &off_time_cr); 	
	free(buff);
	days = days_cr; on_time = on_time_cr; off_time = off_time_cr;
	free(days_cr);free(on_time_cr); free(off_time_cr);
	
	int date_state = 0;
	if(start_date == 0 && end_date == 0){ //tested (both empty)
		date_state = 1;
	}else if(start_date == 0){  //tested (end date only)
		date_state = 1;
		if(online_epoch > end_date){date_state = 0;}
	}else if(end_date == 0){ ///tested (start date only)
		if(online_epoch >= start_date){date_state = 1;
		}else{date_state = 0; }
	}else if(online_epoch < start_date){
		date_state = 0;
	}else if(online_epoch >= start_date && online_epoch <= end_date){ //tested (both filled)
		date_state = 1;
	}
	if(online_epoch < 946684800){
		date_state = 0;	
	}
	
	int day_state = 0;

	if(days != "" && day_now != -1){ //all tested
		day_state = (days[day_now] == '1') ? 1 : 0;
	}else if(days == ""){ //day control is deactivated
		day_state = 1;
	}else if(day_now == -1){//offline 
		day_state = 0;
	}
	
	long on_conv = stol(on_time.substr(on_time.find("|")+1));
    long off_conv = stol(off_time.substr(off_time.find("|") + 1));
	int time_state =0;
	
	if(time_day_epoch != -1){ //if device is online already
	if(on_conv != -1 && off_conv != -1){ //both has time value
		if(on_conv > off_conv){ //off value less than on value
			if (time_day_epoch  >= on_conv) {
	          //activate
	          time_state = 1;
	        } else if (time_day_epoch <= off_conv) {
	          //still activate
	          time_state = 1;
	        } else if (time_day_epoch >= off_conv) {
	          //deactivate
	          time_state = 0;
	        }
		}else{//standard procedure
			time_state = (time_day_epoch >= on_conv && time_day_epoch < off_conv) ? 1 : 0;
		}		
	}else if(on_conv != -1){
		time_state = (time_day_epoch >= on_conv) ? 1 : 0;
	}else if (off_conv != -1){
		time_state = (time_day_epoch >= off_conv) ? 0 : 1;
		
	}else{
		time_state = 1;
	}
	
	}else{ //if device is offline
		time_state = 0;
	}
	
	int state = (date_state == 1 && day_state == 1 && time_state == 1) ? 1 : 0;
	return state;	
}


int check_program_output(const char* file_read){
//open the file
//get control option and control trigger
int pin_state = -1;
char* buff = (char*)malloc(1024);
buff = json_fread(file_read);
struct json_token t;
int ctrl_pin = 0;
json_scanf(buff, strlen(buff), "{control_opt: %d}", &ctrl_pin);
json_scanf_array_elem(buff, strlen(buff), ".control_trigger",0, &t);
int main_opt;
int sec_opt;
char* main_info_b = NULL; char* sec_info_b = NULL;
json_scanf(t.ptr, t.len, "{main_option: %d, sec_option: %d}", &main_opt, &sec_opt);
json_scanf(t.ptr, t.len, "{main_info: %Q, sec_info: %Q}", &main_info_b, &sec_info_b);
free(buff);
if(main_opt >= 1 && main_opt <= 20){ //tested well done
	char* pri_on_b = NULL; char* pri_off_b = NULL; 
	json_scanf(main_info_b, strlen(main_info_b), "{pri_on: %Q, pri_off: %Q}", &pri_on_b, &pri_off_b);
	std::string pri_on = pri_on_b; std::string pri_off = pri_off_b;  free(pri_on_b); free(pri_off_b); 
	//check if condition meet (for primary)
	int pri_op = 0; //operator value for on
	int sec_op = 0; //operator value for off
	int pri_cond_on = pri_chk_cond(pri_on, sensor_value_log.at(main_opt-1));
	int pri_cond_off = pri_chk_cond(pri_off, sensor_value_log.at(main_opt-1));
	int sec_cond_on = -1;
	int sec_cond_off = -1;
	if(sec_opt>= 1 && sec_opt <= 20){
		char* sec_on_b = NULL; char* sec_off_b = NULL;
		json_scanf(sec_info_b, strlen(sec_info_b), "{sec_on: %Q, sec_off: %Q}", &sec_on_b, &sec_off_b);
		std::string sec_on = sec_on_b; std::string sec_off = sec_off_b; free(sec_off_b); free(sec_on_b);
		sec_cond_on = sec_chk_cond(sec_on, sensor_value_log.at(sec_opt-1), pri_op);
		sec_cond_off = sec_chk_cond(sec_off, sensor_value_log.at(sec_opt-1), sec_op);
	}else if(sec_opt == 25){
		static int timer_mode = 0; // 0 -> timer off 1-> timer on
		pri_op = sec_info_b[0] - '0'; //and or relations
		sec_op = pri_op;
		char* time_val_b = NULL; char* init_n_loop = NULL;
		char* sec_dc_info = (char*)malloc(100);
		memcpy(sec_dc_info, &sec_info_b[2], strlen(sec_info_b) );
		json_scanf(sec_dc_info, strlen(sec_dc_info), "{value: %Q, sec: %Q}", &time_val_b, &init_n_loop);
		std::string time_val = time_val_b; free(time_val_b);
		
		//parse
		long on_timer = stol(time_val.substr(0, time_val.find(",")));
		long off_timer = stol(time_val.substr(time_val.find(",")+1));
	//	LOG(LL_WARN,("on time -> %ld, off time -> %ld", on_timer, off_timer));
		int init = init_n_loop[0] == '1'; // 1-> initial is high, 0-> initial is low
		int loop = init_n_loop[1] == '1'; // -> 0 -> loop, 1 -> run once
		free(init_n_loop);
	
		if(pri_cond_on == 1){
			timer_mode = 1;
		}else if(pri_cond_off == 1){
			timer_mode = 0;
		}
		//LOG(LL_WARN,("timer mode trigger 1 to 4: %d, timer state: %d", timer_mode,prog_timer_state[ctrl_pin-1]));
	
		if(timer_mode == 1){ //timer mode
		if(prog_timer_state[ctrl_pin-1] == 0){ // is idle
			if(on_timer != -1 && init == 1){
				//start on timer
			//	LOG(LL_WARN,("begin on timer %ld", on_timer));
				prog_timer_state[ctrl_pin-1] = 1; //on is working
				setup_timer_program(ctrl_pin, on_timer); //begin timer
			}else if(off_timer != -1 && init == 0){
			//	LOG(LL_WARN, ("begin off timer %ld", off_timer));
				prog_timer_state[ctrl_pin-1] = 2; // off is working
				setup_timer_program(ctrl_pin, off_timer); //begin timer to count down off time
			}
		}else if(prog_timer_state[ctrl_pin-1] == 3){ // on is finished
			if(off_timer != -1 && loop == 0){ //if looping and off timer exists
				prog_timer_state[ctrl_pin-1] = 2;
				setup_timer_program(ctrl_pin, off_timer);	
			//	LOG(LL_WARN,("restarting off timer"));
			}else if(loop == 1){ //no loop stop timer
				mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
				prog_timer_state[ctrl_pin-1] = -1;
			//	LOG(LL_WARN,("stop after on timer")); 
			}
		}else if(prog_timer_state[ctrl_pin-1] == 4){ //off is finished
			if(on_timer != -1 && loop == 0){ //if looping and on timer exists
				prog_timer_state[ctrl_pin-1] = 1;
				//LOG(LL_WARN,("restarting on timer"));
				setup_timer_program(ctrl_pin, on_timer);	 //start on timer
			}else if(loop == 1){ //no loop stop timer
				mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
				prog_timer_state[ctrl_pin-1] = -1; 
				//LOG(LL_WARN,("stop after off timer"));
			}
		}
		//////////////////////end of timer mode on
		
		}else if (timer_mode == 0){
			prog_timer_state[ctrl_pin-1]= 0;
			mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
		}
		////timer mode
		
		/////////////////// end logic result
		if(prog_timer_state[ctrl_pin-1] == 1){
			sec_cond_on = 1; sec_cond_off = 0;
		}else if(prog_timer_state[ctrl_pin-1] == 2){
			sec_cond_on = 0; sec_cond_off = 1;
		}else if(prog_timer_state[ctrl_pin-1] == 0 || prog_timer_state[ctrl_pin-1] == -1){
			sec_cond_on  = 0; sec_cond_off =1;
		}
	//	LOG(LL_WARN,("on %d off %d", sec_cond_on, sec_cond_off));
	}//end of sec_opt == 5
	else if(sec_opt >= 26 && sec_opt <= 29){
		char* sec_on_b = NULL; char* sec_off_b = NULL;
		json_scanf(sec_info_b, strlen(sec_info_b), "{sec_on: %Q, sec_off: %Q}", &sec_on_b, &sec_off_b);
		std::string sec_on = sec_on_b; std::string sec_off = sec_off_b; free(sec_off_b); free(sec_on_b);
		if(sec_on == ""){
			sec_cond_on = -1;
		}else{
			int opt_on_sec = sec_on[2] - '0';	
			pri_op = sec_on[0]- '0';
			if(opt_on_sec == 1)sec_cond_on = (prog_pin_state[sec_opt-26] == 1)? 1 : 0;
			if(opt_on_sec == 2)sec_cond_on = (prog_pin_state[sec_opt-26] == 0)? 1 : 0;
		}
		if(sec_off == ""){
			sec_cond_off = -1;
		}else{
			int opt_off_sec = sec_off[2] - '0';
			sec_op = sec_off[0] - '0';
			if(opt_off_sec == 1)sec_cond_off = (prog_pin_state[sec_opt-26] == 1)? 1 : 0;
			if(opt_off_sec == 2)sec_cond_off = (prog_pin_state[sec_opt-26] == 0)? 1 : 0;
		}
		//LOG(LL_WARN,("pri_cond_on -> %d, sec_cond_on -> %d, op -> %d", pri_cond_on, sec_cond_on, pri_op));
		//LOG(LL_WARN,("pri_cond_off -> %d, sec_cond_off -> %d, op -> %d", pri_cond_off, sec_cond_off, sec_op));
	}//end of sec_opt as output status
	int cond_on = pri_op_sec(pri_op, pri_cond_on, sec_cond_on);
	int cond_off = pri_op_sec(sec_op, pri_cond_off, sec_cond_off);
	//check triggering
	if(cond_on){
		//trigger on
		pin_state = 1;
	}else if(cond_off){
		//trigger off
		pin_state = 0;
	}
	
}// trig option 1 to 4
else if(main_opt == 26){ //timed cycle as primary
	char* time_val_b = NULL;
	json_scanf(main_info_b, strlen(main_info_b), "{value: %Q}", &time_val_b);
	std::string time_val = time_val_b; free(time_val_b);
	//parse
	long on_timer = stol(time_val.substr(0, time_val.find(",")));
	long off_timer = stol(time_val.substr(time_val.find(",")+1));
	
	char* init_n_loop = NULL;
	json_scanf(main_info_b, strlen(main_info_b), "{sec: %Q}", &init_n_loop);
	int init = init_n_loop[0] == '1'; // 1-> initial is high, 0-> initial is low
	int loop = init_n_loop[1] == '1'; // -> 0 -> loop, 1 -> run once
	free(init_n_loop);
	if(prog_timer_state[ctrl_pin-1] == 0){ // is idle
		if(on_timer != -1 && init == 1){
			//start on timer
			prog_timer_state[ctrl_pin-1] = 1; //on is working
			setup_timer_program(ctrl_pin, on_timer); //begin timer
			pin_state = 1; //return 1 to output
		}else if(off_timer != -1 && init == 0){
			prog_timer_state[ctrl_pin-1] = 2; // off is working
			setup_timer_program(ctrl_pin, off_timer); //begin timer to count down off time
			pin_state = 0;
		}
	}else if(prog_timer_state[ctrl_pin-1] == 3){ // on is finished
		if(off_timer != -1){
			if(init == 0 && loop == 1){ //start from low no loop -> timer stop
				mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
				prog_timer_state[ctrl_pin-1] = -1;
				pin_state = 0;
			}else{
				prog_timer_state[ctrl_pin-1] = 2;
				setup_timer_program(ctrl_pin, off_timer);
				pin_state = 0;	
			}
		}else{
			pin_state = 0;
		}
	}else if(prog_timer_state[ctrl_pin-1] == 4){ //off is finished
		if(on_timer != -1){
			if(init == 1 && loop == 1){ //start from on no loop -> timer stop
				prog_timer_state[ctrl_pin-1] = -1;
				mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
				pin_state = 0;
			}else{
				prog_timer_state[ctrl_pin-1] = 1;
				setup_timer_program(ctrl_pin, on_timer);
				pin_state = 1;	
			}
		}
	}
	
}
else if(main_opt == 27){ //manual operation
	std::string ti = main_info_b;
	pin_state = (ti == "1");
}
else if(main_opt == 28){ ///remote push button
	int rpb_pin = main_info_b[0] - '0';
	if(sec_opt == 1){ //standard
		if(prog_timer_state[ctrl_pin-1] == 0){
			int sec_info = sec_info_b[0] - '0';
			prog_timer_state[ctrl_pin-1] = 1;//this variable is used to indicate first time
			pin_state = 0;//sec_info;
			ext_PB_state[rpb_pin-1] = 0;
			//LOG(LL_WARN,("first time push button %d", pin_state));
		}else{
			if(ext_PB_state[rpb_pin-1] == 1 || vt_PB_state[rpb_pin-1] == 1){ //short push event
				if(vt_PB_state[rpb_pin-1] == 1 ){vt_PB_state[rpb_pin-1] = 0;}
				ext_PB_state[rpb_pin-1] = 0;
				if(rpb_pin == 3 && input3_as_sens){
					pin_state = !prog_pin_state[ctrl_pin-1];
				}else if(rpb_pin != 3){
					pin_state = !prog_pin_state[ctrl_pin-1];
				}
			}
		}
		
	}else if(sec_opt == 0){ ///with duty cycle
			//LOG(LL_WARN,("rpb with duty cycle"));
		char* sec_b = NULL; char* value_b = NULL;
		json_scanf(sec_info_b, strlen(sec_info_b), "{sec: %Q, value: %Q}", &sec_b, &value_b);
		std::string sec = sec_b; std::string value = value_b; free(sec_b); free(value_b);
		//check initial
		int init = sec[0] == '1'; // 1-> initial is high, 0-> initial is low
		int loop = sec[1] == '1'; // 0 -> is loop, 1 -> fired once
		long on_timer = stol(value.substr(0, value.find(",")));
		long off_timer = stol(value.substr(value.find(",")+1));
		int sec_info = sec_info_b[0] - '0';
		//determine initial
		if(prog_timer_state[ctrl_pin-1] == 0){
			prog_timer_state[ctrl_pin-1] = -1;//this variable is used to indicate first time //timer is idle
			//pin_state_local[rpb_pin-1] = init;
			ext_PB_state[rpb_pin-1] = 0;
			pin_state=0;
			//LOG(LL_WARN,("first time, timed cycle rpb"));
		}else{
			if(ext_PB_state[rpb_pin-1] == 1 || vt_PB_state[rpb_pin-1] == 1){ //short push event
				ext_PB_state[rpb_pin-1] = 0;
				if(vt_PB_state[rpb_pin-1] == 1 ){vt_PB_state[rpb_pin-1] = 0;}
			    if(rpb_pin != 3 || (rpb_pin == 3 && input3_as_sens)){
					if(loop == 1 && prog_timer_state[ctrl_pin-1] == 1){ //if no loop and on is working will shutdown timer
						//pin_state_local[rpb_pin-1] = 0;
						//reset timer
						prog_timer_state[ctrl_pin-1] = -1;
						mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
					//	LOG(LL_WARN,("timer stop no loop"));
						pin_state = 0;
					}else if(loop == 1 && prog_timer_state[ctrl_pin-1]== -1){ //if no loop and on is finished will reengage timer
						///pin_state_local[rpb_pin-1] = 0;
						//reset timer
						prog_timer_state[ctrl_pin-1] = -2;
					//	LOG(LL_WARN,("reengage timer no loop"));
						//pin_state = 1;
					}else if (loop == 0){
						if(prog_timer_state[ctrl_pin-1] != -1){//if loop and timer is working, will end timer
							prog_timer_state[ctrl_pin-1] = -1;
							mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
						//	LOG(LL_WARN,("timer stop with loop"));
							pin_state = 0;
						}else if(prog_timer_state[ctrl_pin-1] == -1){//if loop and timer is stopped will reengage timer
							prog_timer_state[ctrl_pin-1] = -2;
						///	LOG(LL_WARN,("reengage timer with loop"));
						}
					}
				}
			}//end of short push event
		}
		
		if(prog_timer_state[ctrl_pin-1] == -2){ // is idle
			if(on_timer != -1 && init == 1){
				//start on timer
				//LOG(LL_WARN,("starting on timer"));
				prog_timer_state[ctrl_pin-1] = 1; //on is working
				setup_timer_program(ctrl_pin, on_timer); //begin timer
				pin_state = 1; //return 1 to output
			}else if(off_timer != -1 && init == 0){
				//LOG(LL_WARN,("starting off timer"));
				prog_timer_state[ctrl_pin-1] = 2; // off is working
				setup_timer_program(ctrl_pin, off_timer); //begin timer to count down off time
				pin_state = 0;
			}
		}else if(prog_timer_state[ctrl_pin-1] == 3){ // on is finished
			if(loop == 1 || off_timer == -1){ //no loop or does not have off timer
				//will end timer
				mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
				prog_timer_state[ctrl_pin-1] = -1;
				pin_state = 0;				
			}else if(loop == 0 ){ //looping and have off timer
				prog_timer_state[ctrl_pin-1] = 2;
				setup_timer_program(ctrl_pin, off_timer);
				pin_state = 0;
			}
		}else if(prog_timer_state[ctrl_pin-1] == 4){ //off is finished
			if(on_timer != -1){ // has on timer, restarting on
				prog_timer_state[ctrl_pin-1] = 1;
				setup_timer_program(ctrl_pin, on_timer);
				pin_state = 1;	
			}else{ //no on timer, timer stop
				prog_timer_state[ctrl_pin-1] = -1;
				mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
				pin_state = 0;
			}
		}
	} //end of rpb with timed cycle
}
else if(main_opt == 29){//output status
	char* pri_on_b = NULL; char* pri_off_b = NULL; 
	json_scanf(main_info_b, strlen(main_info_b), "{pri_on: %Q, pri_off: %Q}", &pri_on_b, &pri_off_b);
	std::string pri_on = pri_on_b; std::string pri_off = pri_off_b;  free(pri_on_b); free(pri_off_b); 
	int pri_cond_on = -1; int pri_cond_off= -1;
	int pri_op; int sec_op;
	//primary condition
	if(pri_on == ""){
		pri_cond_on = -1;
	}else{
		int a = stoi(pri_on.substr(0, pri_on.find(","))); //output status trigger
		int b = stoi(pri_on.substr(pri_on.find(",")+1)); //what status is should be triggered
		a = a  - 25; //offset with addition sensor log
		if(b == 1){ // when on
			pri_cond_on = (prog_pin_state[a-1]== 1)? 1 : 0;
		}else if (b == 2){ //when off
			pri_cond_on = (prog_pin_state[a-1] == 0) ? 1 : 0;
		}
	}
	
	if(pri_off == ""){
		pri_cond_off = -1;
	}else{
		int a = stoi(pri_off.substr(0, pri_off.find(","))); //output status trigger
		int b = stoi(pri_off.substr(pri_off.find(",")+1)); //what status is should be triggered
		a = a- 25; //offset with addition sensor log
		if(b == 1){ // when on
			pri_cond_off = (prog_pin_state[a-1]== 1)? 1 : 0;
		}else if (b == 2){ //when off
			pri_cond_off = (prog_pin_state[a-1] == 0) ? 1 : 0;
		}
	}
	//end of primary condition
	//check secondary
	int sec_cond_on = -1;
	int sec_cond_off = -1;
	if(sec_opt != -1){
		char* sec_on_b = NULL; char* sec_off_b = NULL;
		json_scanf(sec_info_b, strlen(sec_info_b), "{sec_on: %Q, sec_off: %Q}", &sec_on_b, &sec_off_b);
		std::string sec_on = sec_on_b; std::string sec_off = sec_off_b; free(sec_off_b); free(sec_on_b);
		sec_cond_on = sec_chk_cond(sec_on, sensor_value_log.at(sec_opt-1), pri_op);
		sec_cond_off = sec_chk_cond(sec_off, sensor_value_log.at(sec_opt-1), sec_op);
	}
	//end of check secondary
	int cond_on = pri_op_sec(pri_op, pri_cond_on, sec_cond_on);
	int cond_off = pri_op_sec(sec_op, pri_cond_off, sec_cond_off);
	//check triggering
	if(cond_on){
		//trigger on
		pin_state = 1;
	}else if(cond_off){
		//trigger off
		pin_state = 0;
	}
}//end of main_opt == 9

free(main_info_b);
free(sec_info_b);
return pin_state; //-1 no change, 0 -> off, 1 -> on
}//end of function check program input

void adjust_prog_pin(){
	mgos_gpio_write(OUTPUT_A, prog_pin_state[0]);
	mgos_gpio_write(OUTPUT_B, prog_pin_state[1]);
	#ifdef OUTPUT_D
	mgos_gpio_write(OUTPUT_D, prog_pin_state[3]);
	#endif

	led_red_ctrl(prog_pin_state[2]);
}

int pri_chk_cond(std::string input, float data_input){//tested
	if(input == ""){
		return -1;
	}
	int a = input.find(",");
	int comp = stoi(input.substr(0,a));
	float val = stof(input.substr(a+1));
	int logic = 0;
	if(comp == 1){
		logic = (data_input > val) ? 1 : 0;
	}else if(comp == 2){
		logic = (data_input < val) ? 1 : 0;
	}
	return logic;
}

int sec_chk_cond(std::string input, float data_input, int& op){//tested
	if(input == ""){
		return -1;
	}
	int a = input.find(",");
	op = stoi(input.substr(0,a)); a++;
	int b = input.find(",", a);
	int comp = stoi(input.substr(a, b)); b++;
	float val = stof(input.substr(b));
	int logic = 0;
	if(comp == 1){
		logic = (data_input > val) ? 1 : 0;
	}else if(comp == 2){
		logic = (data_input < val) ? 1 : 0;
	}
	return logic;
}

int pri_op_sec(int op, int pri_cond, int sec_cond){ //tested
	int logic=0;
	if(pri_cond == -1 && sec_cond != -1){
		logic = sec_cond;
	}else if(sec_cond == -1 && pri_cond != -1){
		logic = pri_cond;
	}else if(sec_cond != -1 && pri_cond != -1){
		if(op == 1){
			logic = (pri_cond && sec_cond) ? 1 : 0;
		}else if(op == 2){
			logic = (pri_cond || sec_cond) ? 1 : 0;
		}
	}else{
		logic =0;
	}
	return logic;
}

void reset_timer(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	char *file_name = (char*)malloc(11);
	if (json_scanf(args.p, args.len, ri->args_fmt, &file_name) == 1) {
    	mg_rpc_send_responsef(ri, "OK");
    	char* buff = (char*)malloc(1024);
		buff = json_fread(file_name);
		int ctrl_pin;
		json_scanf(buff, strlen(buff), "{control_opt: %d}", &ctrl_pin); 	
		prog_timer_state[ctrl_pin-1]= 0;
		mgos_clear_timer(prog_timer_id[ctrl_pin-1]);
		free(buff);
		
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	return;
  	}
}

void led_red_ctrl(unsigned int value){ //as output
	if(LED_opt == 1){
		if(value == 1){
			#ifdef OUTPUT_C
			mgos_pwm_set(OUTPUT_C, 1000, (float)(65535-remote_brightness)/65535);
			#endif
			//mgos_gpio_write(LED_RED, 0);
			led_red_status = 1;
		}else{
			#ifdef OUTPUT_C
			mgos_pwm_set(OUTPUT_C, 1000, 1);
			#endif
			//mgos_gpio_write(LED_RED, 1);
			led_red_status = 0;
		}
	}else if(LED_opt == 0){
		led_red_status = 0;
		#ifdef OUTPUT_C
		mgos_pwm_set(OUTPUT_C, 1000, 1);
		#endif
	}
}

void led_red_ctrl_asprog(void *arg){
	if(LED_opt == 2){ //show output statuss
		for (int i = 0; i < 4;i++){ //blinking
			if(prog_link_name[i] == LED_prog){
				if(prog_pin_state[i] == 1){
					#ifdef OUTPUT_C
					mgos_pwm_set(OUTPUT_C, 1000, (float)(65535-remote_brightness)/65535);
					#endif
					//mgos_gpio_write(LED_RED, 0);
					led_red_status = 1;
				}else{
					#ifdef OUTPUT_C
					mgos_pwm_set(OUTPUT_C, 1000, 1);
					#endif
					//mgos_gpio_write(LED_RED, 1);
					led_red_status = 0;
				}
				break;
			}
		}
	}else if(LED_opt == 3){ //show program status
		for (int i = 0; i < 4;i++){ //fading
			if(prog_link_name[i] == LED_prog){
				if(prog_link_state[i] == 1 && prog_pin_state[i] == 1){
					#ifdef OUTPUT_C
					mgos_pwm_set(OUTPUT_C, 1000, (float)(65535-remote_brightness)/65535);
					#endif
					led_red_status = 1;
					break;
				}else if(prog_link_state[i] == 1 && prog_pin_state[i] == 0){ //scheduled is glowing
					fade_blink_remote_led();
					led_red_status = 2;
					break;
				}
			}else if (i == 3){
				led_red_status = 0;
				#ifdef OUTPUT_C
				mgos_pwm_set(OUTPUT_C, 1000, 1);
				#endif
			}
		}
	}
	(void) arg;
}

void setup_timer_program(int ctrl_pin, long value){
	value*= 1000;
	switch(ctrl_pin) {
	case 1:
		mgos_clear_timer(prog_timer_id[0]);
		prog_timer_id[0] = mgos_set_timer(value, MGOS_TIMER_REPEAT, prog_timer1_cb, NULL);
		break;
	case 2:
		mgos_clear_timer(prog_timer_id[1]);
		prog_timer_id[1] = mgos_set_timer(value, MGOS_TIMER_REPEAT, prog_timer2_cb, NULL);
		break;
	case 3:
		mgos_clear_timer(prog_timer_id[2]);
		prog_timer_id[2] = mgos_set_timer(value, MGOS_TIMER_REPEAT, prog_timer3_cb, NULL);
		break;
	case 4:
		mgos_clear_timer(prog_timer_id[3]);
		prog_timer_id[3] = mgos_set_timer(value, MGOS_TIMER_REPEAT, prog_timer4_cb, NULL);
		break;
	}
}

int read_R1_button(int button) { // read button if there is logic change
  static int state_button = 0; //0-> idle, 1 -> timer started (falling edge), 2-> hold detected
  static int button_z = 0;
  static int timer = 0;
  int result = 0;
  if (button - button_z >= 4000) { //rising edge
    state_button = 1;
  } else if (button_z - button >= 4000) { //falling edge
    if (state_button != 2) {
      if (timer >= 10) { //over 1sec
        result = 0;
      } else {
      	LOG(LL_WARN,("short push INPUT_A"));
      	button_z = 0;
        result = 1;
      }
    }
    state_button = 0;
    timer = 0;
  }
  
  if (timer >= 30) { //long press detection
    state_button = 2;
    timer = 0;
    button_z = 0;
    result = 2;
    LOG(LL_WARN,("long push INPUT_A"));
  }
  button_z = button;
  
  if (state_button == 1) {
    timer++;
  }
  return result;
}

int read_R2_button(int button) { // read button if there is logic change
  static int state_button = 0; //0-> idle, 1 -> timer started (falling edge), 2-> hold detected
  static int button_z = 0;
  static int timer = 0;
  int result = 0;
  if (button - button_z >= 4000) { //rising edge
    state_button = 1;
  } else if (button_z - button >= 4000) { //falling edge
    if (state_button != 2) {
      if (timer >= 10) { //over 1sec
        result = 0;
      } else {
      	//LOG(LL_WARN,("short push INPUT_B"));
      	button_z = 0;
        result = 1;
      }
    }
    state_button = 0;
    timer = 0;
  }

  if (timer >= 30) { //long press detection
    state_button = 2;
    timer = 0;
    button_z = 0;
    result = 2;
    //LOG(LL_WARN,("long push INPUT_B"));
  }
  button_z = button;
  if (state_button == 1) {
    timer++;
  }
  return result;
}

int read_RPB_button(int button) { // read button if there is logic change
  static int state_button = 0; //0-> idle, 1 -> timer started (falling edge), 2-> hold detected
  static int button_z = 0;
  static int timer = 0;
  int result = 0;
  if (button - button_z >= 4000/*button_z3 < 1000 && button > 3000*/) { //rising edge
    state_button = 1;
  } else if (button_z - button >= 4000 /*button_z3 > 3000 && button < 1000*/) { //falling edge
    if (state_button != 2) {
      if (timer >= 10) { //over 1sec
        result = 0;
      } else {
      	//LOG(LL_WARN,("short push INPUT_C"));
      	button_z = 0;
        result = 1;
      }
    }
    state_button = 0;
    timer = 0;
  }
  
  if (timer >= 30) { //long press detection
    state_button = 2;
    timer = 0;
    button_z = 0;
    result = 2;
    //LOG(LL_WARN,("long push INPUT_C"));
  }
  button_z = button;
  if (state_button == 1) {
    timer++;
  }
  return result;
}

int read_R4_button(int button) { // read button if there is logic change
  static int state_button = 0; //0-> idle, 1 -> timer started (falling edge), 2-> hold detected
  static int button_z = 0;
  static int timer = 0;
  int result = 0;
  if (button - button_z >= 4000) { //rising edge
    state_button = 1;
  } else if (button_z - button >= 4000) { //falling edge
    if (state_button != 2) {
      if (timer >= 10) { //over 1sec
        result = 0;
      } else {
      	//LOG(LL_WARN,("short push INPUT_D"));
      	button_z = 0;
        result = 1;
      }
    }
    state_button = 0;
    timer = 0;
  }
  
  if (timer >= 30) { //long press detection
    state_button = 2;
    timer = 0;
    button_z = 0;
    result = 2;
    //LOG(LL_WARN,("long push INPUT_D"));
  }
  button_z = button;
  if (state_button == 1) {
    timer++;
  }
  return result;
}

int read_R1_toggle(int input){
	static int timer = 0;
	static int area = 0; //indicate which part the adc read
	static int ret = 0;
	
	if(area == 0){ //determine initial
		if(input < 1365){
			ret = 1;
		}else if(input < 2731){
			ret = 2;
		}else{
			ret = 3;
		}
	}
	
	if(input < 1365){ //auto (do nothing)
		area = 1;
		timer = (area == 1 || area == 0) ? timer+1 : 0;
	}else if(input < 2731){ // override off
		area = 2;
		timer = (area == 2 || area == 0) ? timer+1 : 0;
	}else{ //override on
		area  =3;
		timer = (area == 3 || area == 0) ? timer+1 : 0;
	}
	
	if(timer >= 10){ret = area;}
	return ret;
}

int read_R2_toggle(int input){
	static int timer = 0;
	static int area = 0; //indicate which part the adc read
	static int ret = 0;
	
	if(area == 0){ //determine initial
		if(input < 1365){
			ret = 1;
		}else if(input < 2731){
			ret = 2;
		}else{
			ret = 3;
		}
	}
	
	if(input < 1365){ //auto (do nothing)
		area = 1;
		timer = (area == 1 || area == 0) ? timer+1 : 0;
	}else if(input < 2731){ // override off
		area = 2;
		timer = (area == 2 || area == 0) ? timer+1 : 0;
	}else{ //override on
		area  =3;
		timer = (area == 3 || area == 0) ? timer+1 : 0;
	}
	
	if(timer >= 10){ret = area;}
	return ret;
}

int read_R3_toggle(int input){	
	static int timer = 0;
	static int area = 0; //indicate which part the adc read
	static int ret = 0;
	
	if(area == 0){ //determine initial
		if(input < 1365){
			ret = 1;
		}else if(input < 2731){
			ret = 2;
		}else{
			ret = 3;
		}
	}
	
	if(input < 1365){ //auto (do nothing)
		area = 1;
		timer = (area == 1 || area == 0) ? timer+1 : 0;
	}else if(input < 2731){ // override off
		area = 2;
		timer = (area == 2 || area == 0) ? timer+1 : 0;
	}else{ //override on
		area  =3;
		timer = (area == 3 || area == 0) ? timer+1 : 0;
	}
	
	if(timer >= 10){ret = area;}
	return ret;
}

int read_R4_toggle(int input){
	static int timer = 0;
	static int area = 0; //indicate which part the adc read
	static int ret = 0;
	
	if(area == 0){ //determine initial
		if(input < 1365){
			ret = 1;
		}else if(input < 2731){
			ret = 2;
		}else{
			ret = 3;
		}
	}
	
	if(input < 1365){ //auto (do nothing)
		area = 1;
		timer = (area == 1 || area == 0) ? timer+1 : 0;
	}else if(input < 2731){ // override off
		area = 2;
		timer = (area == 2 || area == 0) ? timer+1 : 0;
	}else{ //override on
		area  =3;
		timer = (area == 3 || area == 0) ? timer+1 : 0;
	}
	
	if(timer >= 10){ret = area;}
	return ret;
}
unsigned long randomGen(){
	srand(time(NULL));
	return rand()*(rand()%222);
}


void modify_program_en(const char* file_name, bool value){
	const char *tmp_file_name = "tmp.json";
	char *content = (char*) malloc(1024);
	content = json_fread(file_name);
	FILE *fp = fopen(tmp_file_name, "w");
	struct json_out out = JSON_OUT_FILE(fp);
	json_setf(content, strlen(content), &out, ".en", "%B", value);
	fclose(fp);
	json_prettify_file(tmp_file_name);  // Optional
	remove(file_name);
	rename(tmp_file_name, file_name);
	free(content);
}

void virtual_pb_check(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	int pin = -1; int value = -1;
	if (json_scanf(args.p, args.len, ri->args_fmt, &pin, &value) == 2) {
    	mg_rpc_send_responsef(ri, "OK");
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	return;
  	}
  	if(pin != -1 && value != -1){
  		vt_PB_state[pin-1] = value;
	}
}

bool check_sensor(char addr){
	Wire.beginTransmission(addr);
	int error = Wire.endTransmission(true);
	if(error == 0){
		return true;
	}
	
	return false;
}
void update_sensor_info(){ //update online and exist	
	const char* tmp_name = "tmp.json";
	for(int i = 0; i < sensor_addr_list.size() ; i++){
		std::string a = ".sensors[" + std::to_string(i) + "].ext"; //exist
		bool ext = check_sensor(sensor_addr_list[i]);
		bool on = ext;
		//LOG(LL_WARN,("addr: %x -> %d", sensor_addr_list[i], on));
		ext = ext == true ? true : sensor_ext.at(i);
		if(on == true && sensor_ext.at(i) == false){
			char* buff = (char*)malloc(1024);
			buff = json_fread("sensors.json");
			FILE *fp = fopen(tmp_name, "w");
			struct json_out out = JSON_OUT_FILE(fp);
			json_setf(buff, strlen(buff), &out, a.c_str(), "%B", ext);
			fclose(fp);
			rename(tmp_name, "sensors.json");
			free(buff);	
		}
		sensor_ext.at(i) = ext;
		sensor_online.at(i) = on; //check if sensor online
		if(sensor_addr_list[i] == 0){
			sensor_online.at(i) = 1;
		}
		
	}
	
}

void update_sensor_logging(bool update){
	char* buff = (char*) malloc(1024);
	buff = json_fread("sensors.json");
	struct json_token t;
	int log_number = 0;
	for (int i = 0; json_scanf_array_elem(buff, strlen(buff), ".sensors", i, &t) > 0; i++) {
		char value = 0; bool ext = false;
		char* name; bool en = false;
		json_scanf(t.ptr, t.len, "{addr: %d, ext: %B, name: %Q, en:%B}", &value, &ext, &name, &en); 
		std::string name_x = name;
		if(!update){ //this information should not change
			sensor_ext.push_back(ext); 
			sensor_en.push_back(en);
			sensor_name.push_back(name_x);	
			sensor_online.push_back(false);
		  	sensor_addr_list.push_back(value);
		  	sensor_init.push_back(true);
		}else{
			//unless sensor enable
			sensor_en.at(get_index(sensor_addr_list, value)) = en;
		}
		if(name_x == "relay"){
			sensor_name_log.push_back("relay1");
			sensor_name_log.push_back("relay2");
			sensor_label_log.push_back("relay1");
			sensor_label_log.push_back("relay2");
			sensor_value_log.push_back(-1); sensor_value_log.push_back(-1);
			sensor_en_log.push_back(en); sensor_en_log.push_back(en);
			if(en) log_number += 2;
		}else if(name_x == "P61"){
		  	sensor_name_log.push_back("P61-P");
		  	sensor_name_log.push_back("P61-V");
		  	sensor_name_log.push_back("P61-I");
		  	sensor_label_log.push_back("Power x61");
		  	sensor_label_log.push_back("Voltage x61");
			sensor_label_log.push_back("Current x61");
			sensor_value_log.push_back(-1);	sensor_value_log.push_back(-1);	sensor_value_log.push_back(-1);
		  	sensor_en_log.push_back(en); sensor_en_log.push_back(en); sensor_en_log.push_back(en);
		  	if(en) log_number+= 3;
		}else if(name_x == "BMEx76"){
		  	sensor_name_log.push_back("BMEx76-H");
		  	sensor_name_log.push_back("BMEx76-T");
		  	sensor_name_log.push_back("BMEx76-P");
		  	sensor_label_log.push_back("Humidity x76");
		  	sensor_label_log.push_back("Temp x76");
			sensor_label_log.push_back("Pressure x76");
		  	sensor_value_log.push_back(-1);sensor_value_log.push_back(-1);sensor_value_log.push_back(-1);
		  	sensor_en_log.push_back(en);sensor_en_log.push_back(en);sensor_en_log.push_back(en);
		  	if(en) log_number += 3;
		}else if(name_x == "BMEx77"){
		  	sensor_name_log.push_back("BMEx77-H");
		  	sensor_name_log.push_back("BMEx77-T");
		  	sensor_name_log.push_back("BMEx77-P");
		  	sensor_value_log.push_back(-1);sensor_value_log.push_back(-1);sensor_value_log.push_back(-1);
		  	sensor_en_log.push_back(en);sensor_en_log.push_back(en);sensor_en_log.push_back(en);
		  	sensor_label_log.push_back("Humidity x77");
		  	sensor_label_log.push_back("Temp x77");
			sensor_label_log.push_back("Pressure x77");
		  	if(en) log_number += 3;
		}else if(name_x == "SHTx44"){
			sensor_name_log.push_back("SHTx44-T");
		  	sensor_name_log.push_back("SHTx44-H");
		  	sensor_label_log.push_back("Temp x44");
		  	sensor_label_log.push_back("Humidity x44");
		  	sensor_value_log.push_back(-1);sensor_value_log.push_back(-1);
		  	sensor_en_log.push_back(en);sensor_en_log.push_back(en);
		  	if(en) log_number+=2;
		}else if(name_x == "SHTx45"){
			sensor_name_log.push_back("SHTx45-T");
		  	sensor_name_log.push_back("SHTx45-H");
		  	sensor_label_log.push_back("Temp x45");
		  	sensor_label_log.push_back("Humidity x45");
		  	sensor_value_log.push_back(-1);sensor_value_log.push_back(-1);
		  	sensor_en_log.push_back(en);sensor_en_log.push_back(en);
		  	if(en) log_number+=2;
		}else if(name_x == "T60"){
			sensor_name_log.push_back(name_x);
			sensor_label_log.push_back("Temp x60");
			sensor_value_log.push_back(-1);
			sensor_en_log.push_back(en);
			if(en) log_number++;
		}else if(name_x == "T67"){
			sensor_name_log.push_back(name_x);
			sensor_label_log.push_back("Temp x67");
			sensor_value_log.push_back(-1);
			sensor_en_log.push_back(en);
			if(en) log_number++;
		}else if(name_x == "L10"){
			sensor_name_log.push_back(name_x);
			sensor_label_log.push_back("Light x10");
			sensor_value_log.push_back(-1);
			sensor_en_log.push_back(en);
			if(en) log_number++;
		}
		else if(name_x == "L48"){
			sensor_name_log.push_back(name_x);
			sensor_label_log.push_back("Light x48");
			sensor_value_log.push_back(-1);
			sensor_en_log.push_back(en);
			if(en) log_number++;
		}
    }
    logColumn =  log_number;
    free(buff);
}

void scan_sensor_at_boot(){
	update_sensor_logging();
	update_sensor_info();
}

void init_sensor(){ //based on online
	//ACS71020
	int sensor_exist = get_index(sensor_addr_list, 0x61);
	if(sensor_exist != -1){
	  	if(sensor_online.at(sensor_exist) == 1 && sensor_init.at(sensor_exist)){	
	    
		mySensor.begin(0x61);     //change according ic address
		//if (err == 1)LOG(LL_WARN, ("\nPower Sensor is online"));
		//else LOG(LL_WARN, ("\nPower Sensor is offline"));
		//delay(500);
		mySensor.custom_en(); //enable customer Mode (reset to disable)
		mySensor.shadow_currentSet(13, 229, 2, 1);
		//LOG(LL_WARN,("current setting error code: %d", err));
		// 0 means no error
		// 01 error detected and message corrected
		// 2 uncorrectable error
		// 3 no meaning
		mySensor.shadow_avgSelen(62, 60);
		sensor_init.at(sensor_exist) = false;
		}
	}
	
	//BME280
	sensor_exist = get_index(sensor_addr_list, 0x76);
	if(sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
			bme76 = mgos_bme280_i2c_create(0x76);
			sensor_init.at(sensor_exist) = false;
		}
	}
	
	sensor_exist = get_index(sensor_addr_list, 0x77);
	if (sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
			bme77 = mgos_bme280_i2c_create(0x77);
			sensor_init.at(sensor_exist) = false;
		}
	}
	
	//vmel6030
	sensor_exist = get_index(sensor_addr_list, 0x10);
	if(sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
		if (light10.begin(Wire)){
	    	//LOG(LL_WARN,("Ready to sense some light!"));
	    	light10.setGain(gain);
	 	 	light10.setIntegTime(time2);
	 	 	sensor_init.at(sensor_exist) = false;
	  	}
	  	}
  	}
  	sensor_exist = get_index(sensor_addr_list, 0x48);
  	if(sensor_exist != -1){
	  	if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
		if (light48.begin(Wire)){
	    	//LOG(LL_WARN,("Ready to sense some light!"));
	    	light48.setGain(gain);
	 	 	light48.setIntegTime(time2);
	 	 	sensor_init.at(sensor_exist) = false;
	  	}
	  	}
	}
	
	struct mgos_i2c *i2c;
	i2c = mgos_i2c_get_global();
	//SHT31
	sensor_exist = get_index(sensor_addr_list, 0x44);
	if(sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
			SHTx44=mgos_sht31_create(i2c, 0x44);
			sensor_init.at(sensor_exist) = false;
		}
	}
	sensor_exist = get_index(sensor_addr_list, 0x45);
	if(sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
			SHTx45 = mgos_sht31_create(i2c, 0x45);
			sensor_init.at(sensor_exist) = false;
		}
	}
	
	//MCP9600
	sensor_exist = get_index(sensor_addr_list, 0x60);
	if(sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
			MCPx60.begin(0x60,Wire);
			if(MCPx60.checkDeviceID()){
		    	sensor_init.at(sensor_exist) = false;
		    }
		}
	}
	sensor_exist = get_index(sensor_addr_list, 0x67);
	if(sensor_exist != -1){
		if(sensor_online.at(sensor_exist) && sensor_init.at(sensor_exist)){
			MCPx67.begin(0x67,Wire);
			if(MCPx67.checkDeviceID()){
		    	sensor_init.at(sensor_exist) = false;
		    }
		}
	}
}

std::string build_log_value_list(){
	std::string ret = "";
	for (int i = 0; i < sensor_value_log.size(); i++){
		std::string num = std::to_string(sensor_value_log.at(i));
		num = (dec_place_global == 0) ? num.substr(0, num.find(",")) : num.substr(0, num.find(".") + dec_place_global + 1);
		/*if(i > 10 ){
			ret += sensor_label_log.at(i) + "," +"1";
		}else{
			
		}*/
		ret += sensor_label_log.at(i) + "," +num;
		if(i != sensor_value_log.size() - 1){
			ret += "|";
		}
	}
	return ret;
}
void request_log_value(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	std::string x= build_log_value_list();
	mg_rpc_send_responsef(ri, "%Q", x.c_str());
	(void) cb_arg;
	(void) fi;
}

std::string build_online_sensor_list(){
	std::string ret = "";
	for(int i = 0; i < sensor_online.size() ; i++){
		ret += sensor_name.at(i) + "," +std::to_string(sensor_online.at(i));
		if(i != sensor_online.size() - 1){
			ret += "|";
		}
	}
	return ret;
}
void request_sensor_status(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	std::string x= build_online_sensor_list();
	mg_rpc_send_responsef(ri, "%Q", x.c_str());
	(void) cb_arg;
	(void) fi;	
}
int get_index_name(std::vector<std::string> v, std::string K){ //for sensor checking
    auto it = find(v.begin(), v.end(), K);
 	int ret;
    // If element was found
    if (it != v.end())
    {
        int index = it - v.begin();
        ret = index;
    }
    else{
       ret = -1;
    }
    return ret;
}
int get_index(std::vector<char> v, char K){ //for sensor checking
    auto it = find(v.begin(), v.end(), K);
 	int ret;
    // If element was found
    if (it != v.end())
    {
        int index = it - v.begin();
        ret = index;
    }
    else{
       ret = -1;
    }
    return ret;
}
