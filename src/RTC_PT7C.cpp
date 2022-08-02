#include "RTC_PT7C.h"


//constructor
RTC_PT7C::RTC_PT7C(){

}


//bcd decimal conversion function
int RTC_PT7C::_bcd2dec(int value){
	int ones = value & 0x0f; //masking 4 least bits, convert to int
	int tens = (value & 0xf0)>>4;  //masking upper 4 bits, convert to int
	int result = ones +tens*10;
	
	return result & 0xff;   //masking 8 bits
}

//decimal bcd conversion function
int RTC_PT7C::_dec2bcd (int value){// e.g   47, bin2 = 4, bin1 = 7, convert to binary
	int bin2 =  (int)(value *0.1);
	int bin1 = value - bin2*10;
	int result = (bin2 << 4) + bin1;
	
	return result & 0xff;   //masking 8bits
	
}

bool RTC_PT7C::begin(unsigned char i2c_address){ //initiate begin function
	_dev_addr = i2c_address;
	
	Wire.begin();
  
  //upon begin, check if RTC oscilator is enable
  Wire.beginTransmission(_dev_addr);
  Wire.write(0x0E); // 0x0E is control register
                    // 0x0F is status register

  Wire.endTransmission();
  //restart transmission
  //request 2 byte data
  Wire.requestFrom(_dev_addr, (unsigned char) 2);

  unsigned char CR_buffer = Wire.read();      //reading control register
  unsigned char SR_buffer = Wire.read();      //reading status register
    
  if((SR_buffer & 0x80)>>7 == 1){     //check if osf stop
                   //modify control register to start oscillator
  }

  delay(1);
  //initate writing control register
  Wire.beginTransmission(_dev_addr);
  Wire.write(0x0E);
  Wire.write(CR_buffer);

  if(Wire.endTransmission() !=0){
    return false;
  }
  
	return true;
  
}


//write second value to RTC
bool RTC_PT7C::write_sec(int second){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x00); 			// 0x00 is second address, request write
	unsigned char dsec = _dec2bcd(second); 	// RTC using bcd, convert first
	Wire.write(dsec);     		// write bcd data to rtc sec register
	
	if(Wire.endTransmission() ==0){//if transmission succeed return true
		return true;
	}
	return false;
	
}

//write minute value to RTC
bool RTC_PT7C::write_min(int minute){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x01); 			//0x01 is minute address, request write
	unsigned char dmin = _dec2bcd(minute); 	// RTC using bcd, convert first
	Wire.write(dmin);			// write bcd data to rtc min register
	if(Wire.endTransmission() ==0){//if transmission succeed return true
		return true;
	}
	return false;
}


//write hour value to RTC
bool RTC_PT7C::write_hour(int hour, int format, int mode){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x02); 			//0x02 is hours address, request write
	unsigned char dhour = _dec2bcd(hour); 	// RTC using bcd, convert first
	
	if(format == FRMT_12H){ //if using 12H format, change am pm accordingly
		dhour = dhour | (mode << 5);
		dhour = dhour | (format << 6);
		//RTC have 2 format for hours, 24H, or 12H
	}
	
	Wire.write(dhour);				// write bcd data to rtc min register
	  if(Wire.endTransmission() ==0){	//if transmission succeed return true
		return true;
	}
	return false;
}


//write day value to RTC
bool RTC_PT7C::write_day(int day){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x03);				//0x03 is day address, request write;
	
	unsigned char dday = _dec2bcd(day);   //RTC using BCD, convert first
	Wire.write(dday);				//write bcd data to rtc day register
	
	if(Wire.endTransmission() == 0){//if transmission succeed return true
		return true;
	}
	return false;
}


//write date value to RTC
bool RTC_PT7C::write_date(int date){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x04);						//0x04 is date address, request write
	
	unsigned char ddate = _dec2bcd(date);			//RTC using BCD, convert first
	Wire.write(ddate);						//write bcd data to rtc date register
	
	if(Wire.endTransmission() == 0){		//if transmission succeed return true
		return true;
	}
	
	return false;
}




//write month value to RTC
bool RTC_PT7C::write_month(int month){
	Wire.beginTransmission(_dev_addr);	//0x05 is month address, request write
	Wire.write(0x05);						
	
	unsigned char dmonth = _dec2bcd(month);		//RTC using BCD, convert first
	Wire.write(dmonth);						//write bcd data to rtc month register
	
	if(Wire.endTransmission() == 0){		//if transmission succeed return true
		return true;
	}
	return false;
}

//write year value to RTC
bool RTC_PT7C::write_year(int year){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x06);						//0x06 is year address, request write
	
	unsigned char dyear = _dec2bcd(year);			//RTC using BCD, convert first
	Wire.write(dyear);						//write bcd data to rtc year register
	
	if(Wire.endTransmission() == 0){
		return true;						//if transmission succeed return true
	}
	return false;
}


//read second value from RTC
int RTC_PT7C::read_sec(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x00);  //0x00 is second register addr

  Wire.endTransmission();
	//restart transmission 1byte data request
	Wire.requestFrom(_dev_addr,(unsigned char)1);
	unsigned char buffer = Wire.read();
		
	int second = _bcd2dec(buffer);
	return second;
	
}

//read minute value from RTC
int RTC_PT7C::read_min(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x01); //0x01 is minute register addr

  Wire.endTransmission();
	//restart transmission, 1 byte data request
	Wire.requestFrom(_dev_addr, (unsigned char) 1);
	
	unsigned char buffer = Wire.read();

	int minute = _bcd2dec(buffer);
	return minute;
}

//read hour value from RTC
int RTC_PT7C::read_hour(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x02); // 0x02 is hour register addr
	
	Wire.endTransmission();
	//restart transmission, 1 byte data request
	Wire.requestFrom(_dev_addr,(unsigned char) 1);
	
	unsigned char buffer = Wire.read();
	
	//find format
	int format = (buffer>>6) & 0x01;
	int hour;
	
	if(format == FRMT_12H){
		hour = _bcd2dec(buffer & 0x1f);  //obtain hour in am/pm
	}else{
		hour = _bcd2dec(buffer);         //convert directly
	}	

  return hour;
}

//read am/pm
int RTC_PT7C::readAMPM(){
  Wire.beginTransmission(_dev_addr);
  Wire.write(0x02);
 
  Wire.endTransmission();
  //restart transmission, 1 byte data request
  Wire.requestFrom(_dev_addr,(unsigned char) 1);
  
  unsigned char buffer = Wire.read();

  //find am/pm
  int mode = (buffer>>5) & 0x01;

  return mode;  //  1 -> PM /// 0 -> AM
}

//read day value from RTC
int RTC_PT7C::read_day(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x03);						//0x03 is day register addr
	
	Wire.endTransmission();
	//restart transmission
	Wire.requestFrom(_dev_addr, (unsigned char) 1);
	
	unsigned char buffer = Wire.read();

	int day = _dec2bcd(buffer);
	
	return day;
}



//read date value from RTC
int RTC_PT7C::read_date(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x04);							//0x04 is date register

  Wire.endTransmission();
	//restart transmission, request 1 byte data
	Wire.requestFrom(_dev_addr, (unsigned char) 1);
	
	unsigned char buffer = Wire.read();
	int date = _dec2bcd(buffer);					//convert bcd to decimal
	
	return date;
}


//read month value from RTC
int RTC_PT7C::read_month(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x05);							//0x05 is month register

  Wire.endTransmission();
	//restart transmission
	Wire.requestFrom(_dev_addr, (unsigned char) 1);
	
	unsigned char buffer = Wire.read();
	
	int month = _dec2bcd(buffer);
	
	return month;	
}


//read year from RTC
int RTC_PT7C::read_year(){
	Wire.beginTransmission(_dev_addr);
	Wire.write(0x06);							//0x06 is year register


  Wire.endTransmission();
	//restart transmission
	Wire.requestFrom(_dev_addr, (unsigned char) 1);
	
	unsigned char buffer = Wire.read();
	
	int year = _dec2bcd(buffer);				//convert BCD to decimal
	
	return year;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//trickle charge enable function
bool RTC_PT7C::trickle_en(int diode_mode, int resistor_value){
  Wire.beginTransmission(_dev_addr);
  Wire.write(0x10);                   //0x10 is trickle charger control register
  
  unsigned char buffer = 0b10100000;    //1010 (MSB) is unique code to enable trickle charger
  buffer |= (unsigned char) diode_mode;

  buffer |= (unsigned char)resistor_value;

  Wire.write(buffer);
  
  if(Wire.endTransmission() == 0){  //if transmission succeed return true
    return true;
  }

  return false;
  
}


bool RTC_PT7C::trickle_dis(){
  Wire.beginTransmission(_dev_addr);
  Wire.write(0x10);  //0x10 is trickle charger control register
  Wire.write(0x00); //write anything to disable

  if(Wire.endTransmission() == 0){   //if transmission succeed return true
    return true;
  }
  return false;
}
