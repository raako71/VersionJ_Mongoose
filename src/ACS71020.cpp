#include "ACS71020.h"
#include "Wire.h"
//special constructor

ACS71020::ACS71020(int Vmax, int Imax){			//vmax and Imax must be determined in order to enabling the class
	_Vrate = Vmax;
	_Irate = Imax;
	_Prate = (long)Vmax * Imax;
}


bool ACS71020::begin(unsigned char i2c_address){
	_dev_addr = i2c_address;
	
	Wire.begin();
	
	Wire.beginTransmission(_dev_addr);
	int a = Wire.endTransmission(true);
	if(a != 0){
		return false;
	}
	
	return true;
}


//get V RMS funciton
long ACS71020::getVrms(){
  unsigned long voltage_value = getRaw(0x20);

  voltage_value &= 0x7fff;

  long v = (voltage_value * _Vrate * 10) >> 15; 

  return v;
}

long ACS71020::getIrms(){
  unsigned long current_value = getRaw(0x20);
  current_value = (current_value >> 16) & 0x7fff;

  long i = (current_value * _Irate * 1000) >> 14;

  return i;
}

long ACS71020::getPactive(){

 	unsigned long data_buffer = getRaw(0x21);						// 0x21 is P active register address

	
	long P_buffer = -(data_buffer & 0x10000)  ;
     P_buffer += data_buffer & 0xffff;
  
	
	long Prms = (P_buffer * _Prate * 100) >> 15;
	//if value is 325.40 W then result 32540
	
	return Prms;
	
}

long ACS71020::getPapparent(){
  	long data_buffer = getRaw(0x22);						// 0x22 is P apparent register address

	int Sbuffer = data_buffer & 0xffff;         //16 bit masking
	
	long Srms = ((unsigned long) Sbuffer * _Prate * 100) >> 15;
	//in case the measured Srms is 100.52 W then this variable results 10052
	return Srms;
}


long ACS71020::getPimag(){

	unsigned long data_buffer = getRaw(0x23);						// 0x22 is P reactive register address
	
	//data obtained in array	
	//data is 16 bit unsigned
	long Qrms = ((data_buffer &  0xffff) * _Prate * 100) >> 15;
	//output format
  // 200VAR then results 20000
	// 275.5 VAR then result 27550
	return Qrms;
}

int ACS71020::getPfactor(){
  unsigned long data_buffer = getRaw(0x24);                   //0x24 is Power factor register value
 

  // data obtained in array
  //data is 11 bit

  int Pfactor = 0;

  //masking 11 bit
  Pfactor = 0x3f & data_buffer;

  Pfactor = ((long)Pfactor * 1000) >> 9;  

  //result format 0.95 will be 950

  return Pfactor;
}

unsigned long ACS71020::getRaw(unsigned char reg_address){
  Wire.beginTransmission(_dev_addr);
  Wire.write(reg_address);

  //restart transmission
  unsigned char a  = Wire.endTransmission();
  if(a != 0){ return 0;}
  Wire.requestFrom((int)_dev_addr, (int)4);

  unsigned char buffer[4];

  buffer[0] = Wire.read();  
  buffer[1] = Wire.read();
  buffer[2] = Wire.read();
  buffer[3] = Wire.read();

  Wire.endTransmission();

  unsigned long reg_value = (unsigned long)buffer[0] + ((unsigned long)buffer[1] << 8) + ((unsigned long)buffer[2] << 16) + ((unsigned long)buffer[3] << 24);

  return reg_value;  
}


void ACS71020::writeReg(unsigned char reg_address, unsigned long value){
  Wire.beginTransmission(_dev_addr);
  Wire.write(reg_address);

  //write value
  Wire.write(value & 0xff);
  Wire.write((value >> 8) & 0xff);
  Wire.write((value >> 16) & 0xff);
  Wire.write((value >> 24) & 0xff);

  Wire.endTransmission();
}

int ACS71020::currentSet(int qvo_fine, int sns_fine, int crs_sns, int iavgselen){
  unsigned long data_buffer = 0x1ff & qvo_fine;
  data_buffer |= (0x1ff & (unsigned long)sns_fine) << 9;
  data_buffer |= (0x07 & (unsigned long)crs_sns) << 18;
  data_buffer |= (0x01 & (unsigned long)iavgselen) << 21;

  writeReg(0x0B, data_buffer);

  delay(1);

  //retrieve error checking and correction code
  unsigned long data_reg = getRaw(0x0B);
  
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
}

int ACS71020::avgSelen(int rms_avg_1, int rms_avg_2){
  unsigned long data_buffer = 0x7f & rms_avg_1;
  data_buffer |= (0x7f & (unsigned long)rms_avg_2) << 7;

  writeReg(0x0C, data_buffer);

  delay(1);

  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x0C);
    
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
}


int ACS71020::zeroCross(int pacc_trim, int ichan_del_en, int chan_del_sel, int fault, int fltdly, int halfcycle_en, int squarewave_en){
  unsigned long data_buffer = pacc_trim & 0x3f;
  data_buffer |= ((unsigned long)ichan_del_en & 0x01) << 7;
  data_buffer |= ((unsigned long)chan_del_sel & 0x07) << 9;
  data_buffer |= ((unsigned long)fault & 0xff) << 13;
  data_buffer |= ((unsigned long)fltdly & 0x07) << 21;
  data_buffer |= ((unsigned long)halfcycle_en & 0x01) << 24;
  data_buffer |= ((unsigned long)squarewave_en & 0x01) << 25;

  writeReg(0x0D, data_buffer);

  delay(1);


  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x0D);
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
}

int ACS71020::voltageSet(int vevent_cycs, int vadc_rate_set, int overvreg, int undervreg, int delaycnt_sel){
  unsigned long data_buffer = vevent_cycs & 0x3f;
  data_buffer |= ((unsigned long)vadc_rate_set & 0x01) << 6;
  data_buffer |= ((unsigned long)overvreg & 0x3f) << 8;
  data_buffer |= ((unsigned long)undervreg & 0x3f) <<  14;
  data_buffer |= ((unsigned long)delaycnt_sel & 0x01) << 20;

  writeReg(0x0E, data_buffer);

  delay(1);

  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x0E);
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
}

int ACS71020::periphSet(int i2c_slave_addr, int i2c_dis_slv_addr, int dio_0_sel, int dio_1_sel){
  unsigned long data_buffer = ((unsigned long)i2c_slave_addr & 0x7f) << 1;
  data_buffer |= ((unsigned long)i2c_dis_slv_addr & 0x01) << 9;
  data_buffer |= ((unsigned long)dio_0_sel & 0x03) << 16;
  data_buffer |= ((unsigned long)dio_1_sel & 0x03) << 18;

  writeReg(0x0F, data_buffer);
  
  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x0F);
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
  
}

int ACS71020::shadow_currentSet(int qvo_fine, int sns_fine, int crs_sns, int iavgselen){
  unsigned long data_buffer = 0x1ff & qvo_fine;
  data_buffer |= (0x1ff & (unsigned long)sns_fine) << 9;
  data_buffer |= (0x07 & (unsigned long)crs_sns) << 18;
  data_buffer |= (0x01 & (unsigned long)iavgselen) << 21;

  writeReg(0x1B, data_buffer);

  delay(1);


  //retrieve error checking and correction code
  
  unsigned long data_reg = getRaw(0x1B);
  
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
  
}

int ACS71020::shadow_avgSelen(int rms_avg_1, int rms_avg_2){
  unsigned long data_buffer = 0x7f & rms_avg_1;
  data_buffer |= (0x7f & (unsigned long)rms_avg_2) << 7;

  writeReg(0x1C, data_buffer);

  delay(1);

  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x1C);
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
}


int ACS71020::shadow_zeroCross(int pacc_trim, int ichan_del_en, int chan_del_sel, int fault, int fltdly, int halfcycle_en, int squarewave_en){
  unsigned long data_buffer = pacc_trim & 0x3f;
  data_buffer |= ((unsigned long)ichan_del_en & 0x01) << 7;
  data_buffer |= ((unsigned long)chan_del_sel & 0x07) << 9;
  data_buffer |= ((unsigned long)fault & 0xff) << 13;
  data_buffer |= ((unsigned long)fltdly & 0x07) << 21;
  data_buffer |= ((unsigned long)halfcycle_en & 0x01) << 24;
  data_buffer |= ((unsigned long)squarewave_en & 0x01) << 25;

  writeReg(0x1D, data_buffer);

  delay(1);


  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x1D);
  
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc

  
}

int ACS71020::shadow_voltageSet(int vevent_cycs, int vadc_rate_set, int overvreg, int undervreg, int delaycnt_sel){
  unsigned long data_buffer = vevent_cycs & 0x3f;
  data_buffer |= ((unsigned long)vadc_rate_set & 0x01) << 6;
  data_buffer |= ((unsigned long)overvreg & 0x3f) << 8;
  data_buffer |= ((unsigned long)undervreg & 0x3f) <<  14;
  data_buffer |= ((unsigned long)delaycnt_sel & 0x01) << 20;

  writeReg(0x1E, data_buffer);

  delay(1);

  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x1E);
 
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
}

int ACS71020::shadow_periphSet(int i2c_slave_addr, int i2c_dis_slv_addr, int dio_0_sel, int dio_1_sel){
  unsigned long data_buffer = ((unsigned long)i2c_slave_addr & 0x7f) << 1;
  data_buffer |= ((unsigned long)i2c_dis_slv_addr & 0x01) << 9;
  data_buffer |= ((unsigned long)dio_0_sel & 0x03) << 16;
  data_buffer |= ((unsigned long)dio_1_sel & 0x03) << 18;

  writeReg(0x1F, data_buffer);
  
  //retrieve error checking and correction code

  unsigned long data_reg = getRaw(0x1F);
 
  if((data_reg & 0x3ffffff) != data_buffer){
    return 4;
  }
  
  return (data_reg >> 26) & 0x03; //return ecc
  
}

long ACS71020::getVavg(int param){
  unsigned long data_buffer;
  if(param == 0){ //one sec averaging
    data_buffer = getRaw(0x26);
  }else{
    data_buffer = getRaw(0x27);
  } 

  //masking
  data_buffer &= 0x7fff;

  long V = (data_buffer * 10 * _Vrate) >> 15;

  return V;  
}

long ACS71020::getIavg(int param){
  unsigned long data_buffer;

  if(param == 0){ //one sec averaging
    data_buffer = getRaw(0x26);
  }else{
    data_buffer = getRaw(0x27);
  }

  //masking 

  data_buffer = (data_buffer >> 16) & 0x7fff;

  long I = (data_buffer * 1000 * _Irate) >> 14;

  return I;
}

long ACS71020::getPavg(int param){
  unsigned long data_buffer;

  if(param == 0){ //one sec averaging
    data_buffer = getRaw(0x28);
  }else{
    data_buffer = getRaw(0x29);
  }

  //masking
  long P_buffer = -(data_buffer & 0x10000)  ;
  P_buffer += data_buffer & 0xffff;
  
  
  long P = (P_buffer * _Prate * 100) >> 15;
  //if value is 325.40 W then result 32540

  return P;
}

int ACS71020::custom_en(){
    writeReg(0x2F, 0x4F70656E);

//  delay(1);

  //enabling customer code
  writeReg(0x30, 1);

  delay(1);
  unsigned long data_reg = getRaw(0x30);
  if(data_reg == 1){
    return 1;
  }else{
    return 0;
  }
}


int ACS71020::custom_dis(){
  writeReg(0x2F, 0x4F70656E);

 // delay(1);

  //enabling customer code
  writeReg(0x30, 0);

  delay(1);
  unsigned long data_reg = getRaw(0x30);
  if(data_reg == 0){
    return 1;
  }else{
    return 0;
  }
  
}


int ACS71020::iavgselen(){
  unsigned long data_buffer = getRaw(0x0B);

  int ret = (data_buffer>>21) & 0x01;

  return ret;
}


int ACS71020::iavgselen_shadow(){
  unsigned long data_buffer = getRaw(0x1B);

  int ret = (data_buffer>>21) & 0x01;

  return ret;
}

int ACS71020::crs_sns(){
  unsigned long data_buffer = getRaw(0x0B);

  int ret = (data_buffer >> 18) & 0x07;

  return ret;
}

int ACS71020::crs_sns_shadow(){
  unsigned long data_buffer = getRaw(0x1B);

  int ret = (data_buffer >> 18) & 0x07;

  return ret;
}


int ACS71020::sns_fine(){
  unsigned long data_buffer = getRaw(0x0B);

  int ret = (data_buffer >> 9) & 0x1ff;
  return ret;
}

int ACS71020::sns_fine_shadow(){
  unsigned long data_buffer = getRaw(0x1B);

  int ret = (data_buffer >> 9) & 0x1ff;
  return ret;
}

int ACS71020::qvo_fine(){
  unsigned long data_buffer = getRaw(0x0B);

  int ret = data_buffer & 0x1ff;
  return ret;
}

int ACS71020::qvo_fine_shadow(){
  unsigned long data_buffer = getRaw(0x1B);

  int ret = data_buffer & 0x1ff;
  return ret;
}

int ACS71020::rms_avg1(){
  unsigned long data_buffer = getRaw(0x0C);

  int ret = (data_buffer) & 0x7f;
  return ret;
}

int ACS71020::rms_avg1_shadow(){
  unsigned long data_buffer = getRaw(0x1C);

  int ret = (data_buffer) & 0x7f;
  return ret;
}


int ACS71020::rms_avg2(){
  unsigned long data_buffer = getRaw(0x0C);
  int ret = (data_buffer >> 7) & 0x3ff;
  return ret; 
}

int ACS71020::rms_avg2_shadow(){
  unsigned long data_buffer = getRaw(0x1C);
  int ret = (data_buffer >> 7) & 0x3ff;
  return ret; 
}
