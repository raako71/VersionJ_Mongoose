#ifndef _ACS71020_H_
#define _ACS71020_H_


#define ONE_MIN 1
#define ONE_SEC 0

//address mapping
//control and status will be at 0x0B to 0x1F
//the result can be seen at 0x20 to 0x31

//this library only measures Vrms, Irms, PF, P, Q, S

class ACS71020{ //class for acs71020
	private:
		unsigned char _dev_addr;
		int _Vrate;
		int _Irate;
		long _Prate;

    
    unsigned long getRaw(unsigned char reg_address);

    void writeReg(unsigned char reg_address, unsigned long value);     
		
		
	public:
		ACS71020(int Vmax, int Imax); 			// constructor
    
		bool begin(unsigned char i2c_address);		// begin function
		
		long getVrms();
    	long getIrms();

		long getPactive();			  //the ic returns 17bit signed (-2 - 2)
		long getPapparent();		//the ic returns 16 bit unsigned (0-2)
		long getPimag();		 	 //the ic returns 16 bit unsigned (0-2)
		int getPfactor();   

    long getVavg(int param =0);
    long getIavg(int param =0);
    long getPavg(int param =0);

    int currentSet(int qvo_fine, int sns_fine, int crs_sns, int iavgselen);
    int avgSelen(int rms_avg_1 =0, int rms_avg_2 =0);
    int zeroCross(int pacc_trim = 0, int ichan_del_en = 0, int chan_del_sel = 0, int fault = 255, int fltdly =0, int halfcycle_en=0, int squarewave_en = 0);
    int voltageSet(int vevent_cycs = 0, int vadc_rate_set = 0, int overvreg = 32, int undervreg = 32, int delaycnt_sel = 0);
    int periphSet(int i2c_slave_addr=0, int i2c_dis_slv_addr=0, int dio_0_sel=0, int dio_1_sel =0);

    int shadow_currentSet(int qvo_fine, int sns_fine, int crs_sns, int iavgselen);
    int shadow_avgSelen(int rms_avg_1 =0, int rms_avg_2 =0);
    int shadow_zeroCross(int pacc_trim = 0, int ichan_del_en = 0, int chan_del_sel = 0, int fault = 255, int fltdly =0, int halfcycle_en=0, int squarewave_en = 0);
    int shadow_voltageSet(int vevent_cycs = 0, int vadc_rate_set = 0, int overvreg = 32, int undervreg = 32, int delaycnt_sel = 0);
    int shadow_periphSet(int i2c_slave_addr=0, int i2c_dis_slv_addr=0, int dio_0_sel=0, int dio_1_sel =0);
    
    int custom_en();
    int custom_dis();

    int iavgselen();
    int iavgselen_shadow();
    
    int crs_sns();
    int crs_sns_shadow();

    int sns_fine();
    int sns_fine_shadow();

    int qvo_fine();
    int qvo_fine_shadow();

    int rms_avg1();
    int rms_avg1_shadow();

    int rms_avg2();
    int rms_avg2_shadow();
};



#endif
