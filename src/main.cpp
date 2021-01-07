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

#include "mgos.h"
#include "mgos_rpc.h"
#include "mgos_wifi.h"
#include "mgos_http_server.h"
#include "mgos_dns_sd.h"
#include "WString.h"
#include "ACS71020.h"

#define LED_PIN 2
//longtermdata trimmer variable
#define UPPER_LIMIT_SIZE 12000
#define LOWER_LIMIT_SIZE 10000
#define TRIMMER_INTERVAL 3600
//housekeeping variable
#define THISDAY_INTERVAL 60 //(in seconds)
#define THISWEEK_INTERVAL 300
#define THISMONTH_INTERVAL 600
#define LONGTERM_INTERVAL 1800

bool colen[13];
float column[20];
bool rc_1970day = 0, rc_thisday = 0;
int header_size = 0;
int logColumn = 13 ;
String use_contain PROGMEM = "";
String use_header PROGMEM = "";
String header_file PROGMEM = "epoch;column1;column2;column3;column4;column5;column6;column7;column8;column9;column10;column11;column12;column13;column14;column15;column16;column17;column18;column19;column20\r\n";

long offline_epoch  = 0;
long online_epoch = 0;
bool NTPflag = false;
bool NTPflag_z = false;

//function prototype
void appendFile(const char* path, const char* message); //append message to a file (tested)
long getEpoch(const char* data_in); //get epoch value from csv row string (tested)
String getHeader_file(int desiredCol); //get header string based on desired column and calculate header size including epoch column (tested)
long read_epoch_last_entry(const char* path); //read last entry of file and return the epoch (tested)
int getColumnNum(const char* path); //get column number in file read path including epoch
String getColumnVal(int column, String data_in); //get column value of selected column from a string, first column is 0 (tested)
long read_epoch_first_entry(const char* path); //read first entry of file and then return the first epoch (tested)
bool exists(const char* path); //check if file exists or not (tested)
void migrate(const char* original, const char* destination, int interval, long difference, bool migrate2new);//migrate to destination, keep difference range in origin (tested)
void move_old2new(const char* origin, const char* destination, long time_difference);//copy content to destination with epoch offset (tested)
void manageOffline_files();//function that moves old files to current files with automated time difference (tested);
void contain_logging(int desired);//function that modify use_contain variable based on desired column (tested)
void header_column_logging(int desired);//function that ajusting file column number and header string (picked from last version)
void trimfile(const char* path);//function that trims file when reaching upper limit size to lower limit size (tested)
void online_HouseKeeping();//(picked from last version)
void offline_HouseKeeping();//(picked from last version)
void oldcheck_onboot();//check old files adjusts offline epoch (picked from last version)
//function prototype
static void setting_modifier(struct mg_rpc_request_info *ri, void *cb_arg, struct mg_rpc_frame_info *fi, struct mg_str args);
static void getTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void checkJSONsetting();
void requestDel(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
void pushTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args);
//function prototype

static void timer_cb(void *arg) {
	time_t now;
	time(&now);
	if(now > 946684800){
		online_epoch = now;
		NTPflag = true;
	}else{
		online_epoch++;
	}
	offline_epoch++;
#ifdef LED_PIN
  mgos_gpio_toggle(LED_PIN);
#endif
  (void) arg;
}
static void logging_cb(void *arg){
	column[1] = rand() % 3;
    column[2] = rand() % 3;
    column[3] = 20.00;
    column[4] = 300.1;
    column[5] = 1;
    column[6] = (float)(rand() % 3001) * 0.01;
    column[7] = (float)(rand() % 3001) * 0.01;
    column[8] = (float)(rand() % 3001) * 0.01;
    column[9] = (float)(rand() % 3001) * 0.01;
    column[10] = (float)(rand() % 3001) * 0.01;
    column[11] = (float)(rand() % 3001) * 0.01;
    column[12] = (float)(rand() % 3001) * 0.01;
    column[13] = (float)(rand() % 3001) * 0.01;
    contain_logging(logColumn);
    LOG(LL_INFO, ("%s", use_contain.c_str()));
    LOG(LL_WARN, ("free heap size %ld", (unsigned long) mgos_get_heap_size()));
    if(NTPflag){
    	if(NTPflag == true && NTPflag_z == false){
    		manageOffline_files();
		}
    	online_HouseKeeping();
    
	}else{
		offline_HouseKeeping();

	}

	NTPflag_z = NTPflag;
}


enum mgos_app_init_result mgos_app_init(void) {
#ifdef LED_PIN
  mgos_gpio_setup_output(LED_PIN, 0);
#endif
	//file system initiation
	header_column_logging(logColumn);
  	oldcheck_onboot();
  	
	if(exists("setting.json")){
		LOG(LL_INFO, ("json checking"));
		checkJSONsetting();
  	}	
 	mgos_set_timer(1000 /* ms */, MGOS_TIMER_REPEAT, timer_cb, NULL);
  	mgos_set_timer(10000 /* ms */, MGOS_TIMER_REPEAT, logging_cb, NULL);
  	//RPC handler function
	mg_rpc_add_handler(mgos_rpc_get_global(), "setting"
  	,"{col1_en: %B, col2_en: %B, col3_en: %B, col4_en: %B, col5_en: %B, col6_en: %B, col7_en: %B,  col8_en: %B, col9_en: %B, col10_en: %B, col11_en: %B, col12_en: %B, col13_en: %B, rc_1970day: %B, rc_thisday: %B}"
  	, setting_modifier, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "getTime", "", getTime, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "delReq", "{comm:%Q}", requestDel, NULL);
  	mg_rpc_add_handler(mgos_rpc_get_global(), "pushTime", "{epoch:%ld}", pushTime, NULL);
	LOG(LL_WARN, ("DNS %s", mgos_dns_sd_get_host_name()));
  	return MGOS_APP_INIT_SUCCESS;
}

void appendFile(const char* path, const char* message){ //append message to a file (tested)
	FILE * file = fopen(path, "a");
	fprintf(file, "%s", message);
	fclose(file);
}
long getEpoch(const char* data_in){//get epoch value from csv row string (tested)
	char* buff= (char*)malloc(11);
	char *pos = buff;
	while (*data_in != ';'){
		*buff++ = *data_in;
		data_in++;
	}
	//reset pointer position to initial
	buff = pos;
    long i = atoi (buff);
    free(buff);
    return i;
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
String getHeader_file(int desiredCol){//get header string based on desired column and calculate header size including epoch column (tested)
  int index = 0;
  int semicol = 0;
  while(desiredCol != 0){
    char a = header_file[index];
    //stop
    if(a == '\n'){
      break;
    }
    // check semicolon
    if( a == ';'){
      desiredCol--;
      if(desiredCol == 0){
        semicol = index;
        header_size = index +2;
        break;
      }
    }
    index++;
  }//while
  if(desiredCol != 0){
    header_size = index+1;
    return header_file;;
  }

  String ret = header_file.substring(0, semicol) + "\r\n";
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
String getColumnVal(int column, String data_in){ //get column value of selected column from a string, first column is 0 (tested)
  int a = 0;
  int a_z = 0;
  String ret = "";
  int something = data_in.indexOf('\r');
  if(something == -1){
    something = data_in.indexOf('\n');
  }
  data_in = data_in.substring(0,something);
  while(column != -1){
    a = data_in.indexOf(';', a_z); 
    ret = data_in.substring(a_z, a);
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
	char* buff = (char*)malloc(11);
	char* pos = buff;
	while(c != ';'){
		*buff++ = c;
		c = fgetc(file);
	}
	fclose(file);
	buff = pos;
	long ret = atol(buff);
	free(buff);
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
		return;
	}	//failed to open origin file
	
	//proceed to open destination file
	FILE * file_dest = fopen(destination, "a");
	if(file_dest == NULL){
		return;
	}   //failed to open destined file
	
	//proceed to create buffer file
	FILE * file_buff = fopen("/buffer.csv", "a");
	if(file_buff == NULL){
		return;
	}   //failed to create buffer file
	fprintf(file_buff, "%s", use_header.c_str());
	char* buff_ori = (char*)malloc(256);
    fseek(file_ori, header_size, SEEK_SET);
    
	while (fgets(buff_ori, 256, file_ori)){//read file line by line offset with header
		//scanning string line 
		int col_scan_index = 0;
		while(col_scan_index < logColumn){
			String col_val = getColumnVal(col_scan_index+1, buff_ori);
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
	rename("/buffer.csv", original);
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
		
		String s = buff_ori;
		int aaaa = s.indexOf(";");
		fprintf(file_dest, "%s", s.substring(aaaa).c_str());
	}
	free(buff_ori);
	fclose(file_ori);
	fclose(file_dest);
  
}
void manageOffline_files(){ //function that moves old files to current files with automated time difference (tested);
      long hour_last_entry = read_epoch_last_entry("/1970Hour.csv");
      long time_difference = online_epoch - offline_epoch;
      if(hour_last_entry > -1){
        if(hour_last_entry > offline_epoch){
          time_difference = online_epoch - hour_last_entry;
        }
      }
      //reset offline epoch value
      offline_epoch = 0;
	  ////////////////////////////////////////////////////////////////////////////////////////
      if (read_epoch_first_entry("/1970Hour.csv") > -1) { //not empty
        move_old2new("/1970Hour.csv", "/thisHour.csv", time_difference);
        remove("/1970Hour.csv");
      }
      /////////////////////////////////////////////////////////////////////////////////////
}
void contain_logging(int desired){//function that modify use_contain variable based on desired column (tested)
   	char buff[255];
 	if(NTPflag){
    	sprintf(buff, "%ld", online_epoch);
  	}else{
    	sprintf(buff, "%ld", offline_epoch);
  	}
  	int index = 1;
  	while (desired != 0){
		strcat(buff, ";");
    	if(colen[index-1] == 1){
      	//storage system
      		char num[20];
      		sprintf(num, "%.2f", column[index]);
      		strcat(buff, num);
    	}
    index++;
    desired--;
  }
  strcat(buff, "\n");
  use_contain = buff;
}
void header_column_logging(int desired){//function that ajusting file column number and header string (picked from last version)
	desired++;
	use_header = getHeader_file(desired);
	if(exists("/thisHour.csv") ){
		bool thishour_col = (getColumnNum("/thisHour.csv") != desired);
		if(thishour_col){
			//restart file
			remove("/thisHour.csv");
			appendFile("/thisHour.csv", use_header.c_str());
		}
	}
	if(exists("/thisDay.csv")){
		bool thisday_col = (getColumnNum("/thisDay.csv") != desired);
		if(thisday_col){
			remove("/thisDay.csv");
			appendFile("/thisDay.csv", use_header.c_str());
		}
	}
	if(exists("/thisWeek.csv") ){
		bool thisweek_col = (getColumnNum("/thisWeek.csv") != desired);
		if(thisweek_col){
			remove("/thisWeek.csv");
			appendFile("/thisWeek.csv", use_header.c_str());
		}
	}
	if(exists("/thisMonth.csv")){
		bool thismonth_col = (getColumnNum("/thisMonth.csv") != desired);
		if(thismonth_col){
			remove("/thisMonth.csv");
			appendFile("/thisMonth.csv", use_header.c_str());
		}
	}	
	if(exists("/longTermData.csv")){
		bool longterm_col = (getColumnNum("/longTermData.csv") != desired);
		if(longterm_col){
			remove("/longTermData.csv");
			appendFile("/longTermData.csv", use_header.c_str());
		}
	}
	////////////////////////offline//////////////////////////////////////////////
	if(exists("/1970Hour.csv")){
		bool oldhour_col = (getColumnNum("/1970Hour.csv") != desired);
		if(oldhour_col){
			//restart file
			remove("/1970Hour.csv");
			appendFile("/1970Hour.csv", use_header.c_str());
		}
	}
	if(exists("/1970Day.csv")){
		bool oldday_col = (getColumnNum("/1970Day.csv") != desired);
		if(oldday_col){
			remove("/1970Day.csv");
			appendFile("/1970Day.csv", use_header.c_str());
		}
	}
	if(exists("/1970Week.csv")){
		bool oldweek_col = (getColumnNum("/1970Week.csv") != desired);
		if(oldweek_col){
			remove("/1970Week.csv");
			appendFile("/1970Week.csv", use_header.c_str());
		}
	}
	if(exists("/1970Month.csv")){
		bool oldmonth_col = (getColumnNum("/1970Month.csv") != desired);
		if(oldmonth_col){
			remove("/1970Month.csv");
			appendFile("/1970Month.csv", use_header.c_str());
		}
	}	
	if(exists("/1970longTermData.csv") ){
		bool oldlongterm_col = (getColumnNum("/1970longTermData.csv") != desired);
		if(oldlongterm_col){
			remove("/1970longTermData.csv");
			appendFile("/1970longTermData.csv", use_header.c_str());
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
		FILE * file_dest = fopen("buffer.csv", "w");
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
      rename("buffer.csv", path);
    }
}
void online_HouseKeeping(){ //(picked from last version)
 	//read and store data every 10 secs
	///////////////////////////////////////////longTermData trimmer /////////////////////////////////////////////////
	static int timer = 10;
	if(timer>= TRIMMER_INTERVAL+10){
		if(!exists("/longTermData.csv")){ //if longTermData doesn't exist, create new one
		  appendFile("/longTermData.csv", use_header.c_str());
		}else{
		   trimfile("/longTermData.csv");
		}    
		timer = 0;
	}
	timer+=10;
	///////////////////////////////////////////longTermData trimmer /////////////////////////////////////////////////
	////////////////////////////////////////////thisMonth///////////////////////////////////////////////////////////
	if(!exists("/thisMonth.csv")){ //if thisMonth doesn't exist (just deleted) make a new file
		appendFile("/thisMonth.csv", use_header.c_str());
	}
	long thisMonth_first = read_epoch_first_entry("/thisMonth.csv");
	long thisMonth_last = read_epoch_last_entry("/thisMonth.csv");
    if(thisMonth_last - thisMonth_first > 2629743 ){ //not a new file
		//already pass 1 Month
		//move thisMonth to longTermData with 30mins interval
		migrate("/thisMonth.csv", "/longTermData.csv", LONGTERM_INTERVAL, 2160000, rc_thisday); //30mins interval, keep first 25 days, migrate the rest
    }
  	////////////////////////////////////////////thisMonth///////////////////////////////////////////////////////////
	////////////////////////////////////////////thisWeek///////////////////////////////////////////////////////////
	if(!exists("/thisWeek.csv")){ //if thisweek doesn't exist (just deleted) make a new file
		appendFile("/thisWeek.csv", use_header.c_str());
	}
	long thisWeek_first = read_epoch_first_entry("/thisWeek.csv");
	long thisWeek_last = read_epoch_last_entry("/thisWeek.csv");
    if(thisWeek_last - thisWeek_first > 604800){ //not a new file
		//already pass 1 week
		//move thisWeek to thisMonth with 10mins interval
		migrate("/thisWeek.csv", "/thisMonth.csv", THISMONTH_INTERVAL, 432000, rc_thisday); //10mins interval, keep last 5 days, migrate the rest
    }
  	////////////////////////////////////////////thisWeek///////////////////////////////////////////////////////////
  	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
	if(!exists("/thisDay.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/thisDay.csv", use_header.c_str());
	}
	long thisDay_first = read_epoch_first_entry("/thisDay.csv");
	long thisDay_last = read_epoch_last_entry("/thisDay.csv");
    if(thisDay_last - thisDay_first > 86400){ //already pass 1 day
		//move thisDay to thisWeek, with 5 mins interval
		migrate("/thisDay.csv", "/thisWeek.csv", THISWEEK_INTERVAL, 72000, rc_thisday); //5mins interval, keep last 20 hours, migrate the rest  
    }
	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
	/////////////////////////////////////////////thisHour////////////////////////////////////////////////////////////////////
	if(!exists("/thisHour.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/thisHour.csv", use_header.c_str());
	}
	if(read_epoch_first_entry("/thisHour.csv")  <= -1){
		//fresh file, append immediatelly
		appendFile("/thisHour.csv", use_contain.c_str());  
	}else{ // no fresh file
		if(online_epoch - read_epoch_first_entry("/thisHour.csv") <= 3600){ //not 1 hour yet, append file
		  //append file
		
		    appendFile("/thisHour.csv", use_contain.c_str());  
		}else{ //passed 1 hour
		  //migrate thisHour to thisDay with 1 mins interval 
		  // add current data
		    appendFile("/thisHour.csv", use_contain.c_str()); 
		    migrate("/thisHour.csv", "/thisDay.csv", THISDAY_INTERVAL, 2700, rc_thisday); //interval 60 secs, keep last 45 mins, migrate the rest
		}

  }//end of "no fresh file"
  ////////////////////////////////////////////////////thisHour//////////////////////////////////////////////////////////////////
}
void offline_HouseKeeping(){ //(picked from last version)
	//read and store data every 10 secs if offline
	///////////////////////////////////////////1970 longTermData trimmer /////////////////////////////////////////////////
	static int timer =10;
	if(timer>= TRIMMER_INTERVAL+10){
		if(!exists("/1970longTermData.csv")){ //if 1970longTermData doesn't exist, create new one
			appendFile("/1970longTermData.csv", use_header.c_str());
		}else{
			trimfile("/1970longTermData.csv");
		}
		timer = 0;
	}
	timer+=10;
  	///////////////////////////////////////////1970 longTermData trimmer /////////////////////////////////////////////////
  
  	////////////////////////////////////////////1970Month///////////////////////////////////////////////////////////
  	if(!exists("/1970Month.csv")){ //if 1970Month doesn't exist (just deleted) make a new file
    	appendFile("/1970Month.csv", use_header.c_str());
  	}
  	long thisMonth_first = read_epoch_first_entry("/1970Month.csv");
  	long thisMonth_last = read_epoch_last_entry("/1970Month.csv");
  	if(thisMonth_last - thisMonth_first > 2629743 ){
    	//move thisMonth to longTermData with 30mins interval
      	migrate("/1970Month.csv", "/1970longTermData.csv", LONGTERM_INTERVAL,2160000 , rc_1970day); //30mins interval, keep first 25 days, migrate the rest
    } 
 	////////////////////////////////////////////1970Month///////////////////////////////////////////////////////////
  
  	////////////////////////////////////////////1970Week///////////////////////////////////////////////////////////
  	if(!exists("/1970Week.csv")){ //if 1970week doesn't exist (just deleted) make a new file
    	appendFile("/1970Week.csv", use_header.c_str());
  	}
	long thisWeek_first = read_epoch_first_entry("/1970Week.csv");
	long thisWeek_last = read_epoch_last_entry("/1970Week.csv");
    if(thisWeek_last - thisWeek_first > 604800){ //not a new file
		//already pass 1 week
		//move thisWeek to thisMonth with 10mins interval
		migrate("/1970Week.csv", "/1970Month.csv", THISMONTH_INTERVAL, 432000, rc_1970day); //10mins interval, keep first 5 days, migrate the rest
    }
  	////////////////////////////////////////////thisWeek///////////////////////////////////////////////////////////
  
  	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
	if(!exists("/1970Day.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/1970Day.csv", use_header.c_str());
	}
	long thisDay_first = read_epoch_first_entry("/1970Day.csv");
	long thisDay_last = read_epoch_last_entry("/1970Day.csv");
    if(thisDay_last - thisDay_first > 86400){ //not a new file
		//already pass 1 day
		//move thisDay to thisWeek, with 5 mins interval
		migrate("/1970Day.csv", "/1970Week.csv", THISWEEK_INTERVAL,72000, rc_1970day); //5mins interval, keep first 20 hours, migrate the rest
    }
  	////////////////////////////////////////////thisDay///////////////////////////////////////////////////////////
  
  	//////////////////////////////////////////////thisHour///////////////////////////////////////////////////////////////////
  	if(!exists("/1970Hour.csv")){ //if thisDay doesn't exist (just deleted) make a new file
		appendFile("/1970Hour.csv", use_header.c_str());
	}
	if(read_epoch_first_entry("/1970Hour.csv") <= -1){
    	//fresh file, append immediatelly
    	appendFile("/1970Hour.csv", use_contain.c_str());  
  	}else{ // no fresh file
		if(offline_epoch - read_epoch_first_entry("/1970Hour.csv") <= 3600){ //not 1 hour yet, append file
      	//append file
        appendFile( "/1970Hour.csv", use_contain.c_str());  
      
    }else{ //passed 1 hour
        appendFile("/1970Hour.csv", use_contain.c_str());
        //migrate thisHour to thisDay with 1 mins interval 
        migrate("/1970Hour.csv", "/1970Day.csv", THISDAY_INTERVAL,2700, rc_1970day); //interval 60 secs, keep first 45 mins, migrate the rest
    }

  }//end of "no fresh file"
  /////////////////////////////////////////////thisHour/////////////////////////////////////////////////////////////////////////

}
void oldcheck_onboot() { //check old files adjusts offline epoch (picked from last version)
  long year = -1;
  long year2 = -1;
  long hour_1970_epoch = read_epoch_last_entry("/1970Hour.csv");
  if (hour_1970_epoch != -1) {
    //find year in 1970 Hour
    year = hour_1970_epoch / (long)31556926;
  }
  long day_1970_epoch = read_epoch_last_entry("/1970Day.csv");
  if (day_1970_epoch != -1) {
    year2 = day_1970_epoch /(long) 31556926;
    if(year2 != year) {
      remove( "/1970Hour.csv");
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
static void setting_modifier(struct mg_rpc_request_info *ri, void *cb_arg, struct mg_rpc_frame_info *fi, struct mg_str args) {
  if (json_scanf(args.p, args.len, ri->args_fmt, &colen[0], &colen[1], &colen[2], &colen[3], &colen[4], &colen[5], &colen[6], &colen[7], &colen[8], &colen[9], &colen[10], &colen[11], &colen[12], &rc_1970day, &rc_thisday) == 15) {
    mg_rpc_send_responsef(ri, "OK");
	LOG(LL_WARN, ("setting json file received"));
	json_fprintf("setting.json", "{col1_en: %B, col2_en: %B, col3_en: %B, col4_en: %B, col5_en: %B, col6_en: %B, col7_en: %B, col8_en: %B, col9_en: %B, col10_en: %B, col11_en: %B, col12_en: %B, col13_en: %B, rc_1970day: %B, rc_thisday: %B}", colen[0], colen[1], colen[2], colen[3], colen[4], colen[5], colen[6], colen[7], colen[8], colen[9], colen[10], colen[11], colen[12], rc_1970day, rc_thisday);
  } else {
    mg_rpc_send_errorf(ri, -1, "Bad request");
  }
  
  (void) cb_arg;
  (void) fi;
}
static void getTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args) {
 	long ret = (NTPflag == true) ? online_epoch : offline_epoch;
	mg_rpc_send_responsef(ri, "%ld", ret);
	(void) cb_arg;
	(void) fi;
}
void checkJSONsetting(){
	char* buff = json_fread("setting.json");
	json_scanf(buff, strlen(buff), "{col1_en: %B, col2_en: %B, col3_en: %B, col4_en: %B, col5_en: %B, col6_en: %B, col7_en: %B, col8_en: %B, col9_en: %B, col10_en: %B, col11_en: %B, col12_en: %B, col13_en: %B, rc_1970day: %B, rc_thisday: %B}"
	,&colen[0], &colen[1], &colen[2], &colen[3], &colen[4], &colen[5], &colen[6], &colen[7], &colen[8], &colen[9], &colen[10], &colen[11], &colen[12], &rc_1970day, &rc_thisday);
}
void requestDel(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	char *command = (char*)malloc(11);
	if (json_scanf(args.p, args.len, ri->args_fmt, &command) == 1) {
    	mg_rpc_send_responsef(ri, "OK");
		LOG(LL_WARN, ("%s delete file requested", command));
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	return;
  	}
  	if(command[0] == '1'){
      //delete longtermdata
      remove("1970longTermData.csv");
    }
    if(command[1] == '1'){
      //delete thismonth
      remove("1970Month.csv");
    }
    if(command[2] == '1'){
      //delete thisweek
      remove("1970Week.csv");
    }
    if(command[3] == '1'){
      //delete thisDay
      remove("1970Day.csv");
    }
    if(command[4] == '1'){
      //delete thishour
      remove("1970Hour.csv");
    }
  if(command[5] == '1'){
      //delete longtermdata
      remove("longTermData.csv");
    }
    if(command[6] == '1'){
      //delete thismonth
      remove("thisMonth.csv");
    }
    if(command[7] == '1'){
      //delete thisweek
      remove("thisWeek.csv");
    }
    if(command[8] == '1'){
      //delete thisDay
      remove("thisDay.csv");
    }
    if(command[9] == '1'){
      //delete thishour
      remove("thisHour.csv");
    }
}
void pushTime(struct mg_rpc_request_info *ri, void *cb_arg,struct mg_rpc_frame_info *fi, struct mg_str args){
	if (json_scanf(args.p, args.len, ri->args_fmt, &online_epoch) == 1) {
    	mg_rpc_send_responsef(ri, "OK");
		LOG(LL_WARN, ("push time requested"));
  	} else {
    	mg_rpc_send_errorf(ri, -1, "Bad request");
    	return;
  	}
  	NTPflag = true;
}

