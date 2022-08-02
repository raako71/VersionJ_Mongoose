//this library is provided to interact with I2C RTC PT7C4339WEX
// coded by: alif nabiel
// start code: 12th sep, 11.40
// finish: RTC time counter : 12th sep 23.37

#ifndef _RTC_PT7C_H_
#define _RTC_PT7C_H_

#define FRMT_12H 1
#define FRMT_24H 0

#define MODE_PM 1
#define MODE_AM 0

#define RES200 1
#define RES2K  2
#define RES4K  3

#define DIODE_OFF 1 << 2
#define DIODE_ON  1 << 3

#include "Wire.h"

class RTC_PT7C{ //class for RTC 
	private:
		unsigned char _dev_addr; // initiate _dev_addr variable
		
		int _bcd2dec(int value);
		int _dec2bcd(int value);
		
		
	public:
		RTC_PT7C(); //constructor
		bool begin(unsigned char i2c_address);
		
		//time counter function prototype
		
		//read function
		int read_sec();
		int read_min();
		int read_hour();
    int readAMPM();
		int read_day();
		int read_date();
		int read_month();
		int read_year();
		
		//write function
		bool write_sec(int second);
		bool write_min(int minute);
		bool write_hour(int hour, int format =0, int mode = 0);
		bool write_day (int day);
		bool write_date (int date);
		bool write_month(int month);
		bool write_year(int year);
		
		//trickle charger function
    bool trickle_en(int diode_mode, int resistor_value);
    
		
		bool trickle_dis();
		
		
};

#endif
