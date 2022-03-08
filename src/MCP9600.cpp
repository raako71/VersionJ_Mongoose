/******************************************************************************
SparkFun_MCP9600.h
SparkFun_MCP9600 Library Source File
Fischer Moseley @ SparkFun Electronics
Original Creation Date: July 8, 2019
https://github.com/sparkfunX/Qwiic_MCP9600_Thermocouple

This file implements the MCP9600 class, prototyped in SparkFun_MCP9600.cpp.

Development environment specifics:
	IDE: Arduino 1.8.9
	Hardware Platform: Arduino Uno/SparkFun Redboard
	MCP9600 Breakout Version: 1.0.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#include "MCP9600.h"


/*-------------------------------- Device Status ------------------------*/

bool MCP9600::begin(unsigned char address, TwoWire &wirePort)
{
  _deviceAddress = address; //grab the address that the sensor is on
  _i2cPort = &wirePort;     //grab the port that the user wants to use

  // This is the old .begin code. See below for the reason we don't use it any more...
  //
  //return true if the device is connected and the device ID is what we expect
  //bool success = isConnected();
  //success &= checkDeviceID();

  // The MCP9600 is a fussy device. If we call isConnected twice in succession, the second call fails
  // as the MCP9600 does not ACK on the second call. Only on the first.
  //
  // The OpenLog Artemis routinely uses the same isConnected code twice: once to detect _anything_ that is on the bus;
  // and then again to detect an MCP9600. The second time fails.
  //
  // If there is a device with a lower address on the OLA Qwiic bus, that device responds first and satisfies
  // isConnected. Then the OLA code uses isConnected again to detect an MCP9600. That call is successful, as this time it is the first call.
  // However, the OLA then goes on to call this function to begin the sensor. Previously this was failing as isConnected
  // (12 lines above) was then being called for the second time...
  //
  // Long story short, we should not call isConnected here. We should only call checkDeviceID.

  bool success = checkDeviceID();

  return success;
}

bool MCP9600::available()
{
  unsigned char status = readSingleRegister(SENSOR_STATUS);
  return (status >> 6) & 0x01;
}

bool MCP9600::isConnected()
{
  _i2cPort->beginTransmission(_deviceAddress);
  return (_i2cPort->endTransmission() == 0);
}

unsigned int MCP9600::deviceID()
{
  return readDoubleRegister(DEVICE_ID);
}

bool MCP9600::checkDeviceID()
{
  deviceID(); //this is here because the first read doesn't seem to work, but the second does. No idea why :/
  return (highByte(deviceID()) == DEV_ID_UPPER);
}

bool MCP9600::resetToDefaults()
{
  bool success = writeSingleRegister(SENSOR_STATUS, 0x00);
  success |= writeSingleRegister(THERMO_SENSOR_CONFIG, 0x00);
  success |= writeSingleRegister(DEVICE_CONFIG, 0x00);
  success |= writeSingleRegister(ALERT1_CONFIG, 0x00);
  success |= writeSingleRegister(ALERT2_CONFIG, 0x00);
  success |= writeSingleRegister(ALERT3_CONFIG, 0x00);
  success |= writeSingleRegister(ALERT4_CONFIG, 0x00);
  success |= writeSingleRegister(ALERT1_HYSTERESIS, 0x00);
  success |= writeSingleRegister(ALERT2_HYSTERESIS, 0x00);
  success |= writeSingleRegister(ALERT3_HYSTERESIS, 0x00);
  success |= writeSingleRegister(ALERT4_HYSTERESIS, 0x00);
  success |= writeDoubleRegister(ALERT1_LIMIT, 0x0000);
  success |= writeDoubleRegister(ALERT2_LIMIT, 0x0000);
  success |= writeDoubleRegister(ALERT3_LIMIT, 0x0000);
  success |= writeDoubleRegister(ALERT4_LIMIT, 0x0000);
  return success;
}

/*----------------------------- Sensor Measurements ---------------------*/

float MCP9600::getThermocoupleTemp(bool units)
{
  //read register and convert to celcius
  int16_t raw = readDoubleRegister(HOT_JUNC_TEMP);
  float celcius = ((float)raw * DEV_RESOLUTION);

  //clear data ready bit
  unsigned char status = readSingleRegister(SENSOR_STATUS);
  bitWrite(status, 6, 0);
  writeSingleRegister(SENSOR_STATUS, status);

  //return in celcius or freedom units
  return units ? celcius : (((float)celcius * 1.8f) + 32);
}

float MCP9600::getAmbientTemp(bool units)
{
  int16_t raw = readDoubleRegister(COLD_JUNC_TEMP);
  float celcius = ((float)raw * DEV_RESOLUTION);
  return units ? celcius : (((float)celcius * 1.8f) + 32);
}

float MCP9600::getTempDelta(bool units)
{
  int16_t raw = readDoubleRegister(DELTA_JUNC_TEMP);
  float celcius = ((float)raw * DEV_RESOLUTION);
  return units ? celcius : (((float)celcius * 1.8f) + 32);
}

signed long MCP9600::getRawADC()
{
  for (byte attempts = 0; attempts <= retryAttempts; attempts++)
  {
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(RAW_ADC);
    _i2cPort->endTransmission();

    if (_i2cPort->requestFrom((int)_deviceAddress, (int)3) != 0)
    {
      signed long data = _i2cPort->read() << 16;
      data |= _i2cPort->read() << 8;
      data |= _i2cPort->read();
      return data;
    }
  }
  return (0);
}

bool MCP9600::isInputRangeExceeded()
{
  unsigned char status = readSingleRegister(SENSOR_STATUS);
  return bitRead(status, 4);
}

/*--------------------------- Measurement Configuration --------------- */

bool MCP9600::setAmbientResolution(Ambient_Resolution res)
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG); //get current device configuration so we don't wipe everything else
  bitWrite(config, 7, res);                           //set the bit that controls the ambient (cold) junction resolution

  bool failed = writeSingleRegister(DEVICE_CONFIG, config); //write new config register to MCP9600
  failed |= (readSingleRegister(DEVICE_CONFIG) != config);  //double check that it was set properly
  return failed;                                            //return 1 if the write failed or the register wasn't properly set, 0 otherwise
}

Ambient_Resolution MCP9600::getAmbientResolution()
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG);         //grab current device configuration
  return static_cast<Ambient_Resolution>(bitRead(config, 7)); //return 7th bit from config register
}

bool MCP9600::setThermocoupleResolution(Thermocouple_Resolution res)
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG); //grab current device configuration so we don't wipe everything else
  bool highResolutionBit = bitRead(res, 1);
  bool lowResolutionBit = bitRead(res, 0);
  bitWrite(config, 6, highResolutionBit); //set 6th bit of config register to 1st bit of the resolution
  bitWrite(config, 5, lowResolutionBit);  //set 5th bit of config register to 0th bit of the resolution

  bool failed = writeSingleRegister(DEVICE_CONFIG, config); //write new config register to MCP9600
  failed |= (readSingleRegister(DEVICE_CONFIG) != config);  //double check that it was written properly
  return failed;                                            //return 1 if the write failed or the register wasn't properly set, 0 otherwise
}

Thermocouple_Resolution MCP9600::getThermocoupleResolution()
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG); //grab current device configuration
  unsigned char res = 0;                                        //define new thermocoupleResolution enum to return
  bool highResolutionBit = bitRead(config, 6);
  bool lowResolutionBit = bitRead(config, 5);
  bitWrite(res, 1, highResolutionBit); //set 1st bit of the enum to the 6th bit of the config register
  bitWrite(res, 0, lowResolutionBit);  //set 0th bit of the enum to the 5th bit of the config register
  return static_cast<Thermocouple_Resolution>(res);
}

unsigned char MCP9600::setThermocoupleType(Thermocouple_Type type)
{
  unsigned char config = readSingleRegister(THERMO_SENSOR_CONFIG); //grab current device configuration so we don't wipe everything else
  bitClear(config, 4);                                       //clear the necessary bits so that they can be set
  bitClear(config, 5);
  bitClear(config, 6);
  config |= (type << 4); //set the necessary bits in the config register
  if (writeSingleRegister(THERMO_SENSOR_CONFIG, config))
    return 1; //if write fails, return 1
  if (readSingleRegister(THERMO_SENSOR_CONFIG) != config)
    return 2; //if the register didn't take the new value, return 2

  return 0; //otherwise return 0
}

Thermocouple_Type MCP9600::getThermocoupleType()
{
  unsigned char config = readSingleRegister(THERMO_SENSOR_CONFIG);
  return static_cast<Thermocouple_Type>(config >> 4); //clear the non-thermocouple-type bits in the config registe
}

unsigned char MCP9600::setFilterCoefficient(unsigned char coefficient)
{
  if (coefficient > 7)
    return 3; //return immediately if the value is too big

  unsigned char config = readSingleRegister(THERMO_SENSOR_CONFIG);
  bitWrite(coefficient, 3, bitRead(config, 3));
  bitWrite(coefficient, 4, bitRead(config, 3));
  bitWrite(coefficient, 5, bitRead(config, 3));
  bitWrite(coefficient, 6, bitRead(config, 3));
  bitWrite(coefficient, 7, bitRead(config, 3));

  //config = config >> 3;
  //config = config << 3;
  //config |= coefficient; //set the necessary bits in the config register

  return writeSingleRegister(THERMO_SENSOR_CONFIG, coefficient);
}

unsigned char MCP9600::getFilterCoefficient()
{
  unsigned char config = readSingleRegister(THERMO_SENSOR_CONFIG);
  unsigned char coeff = 0;
  bitWrite(coeff, 0, bitRead(config, 0));
  bitWrite(coeff, 1, bitRead(config, 1));
  bitWrite(coeff, 2, bitRead(config, 2));

  return coeff; //clear the non-filter-Coefficient data in the config register
}

bool MCP9600::setBurstSamples(Burst_Sample samples)
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG);
  bool highResolutionBit = bitRead(samples, 2);
  bool midResolutionBit = bitRead(samples, 1);
  bool lowResolutionBit = bitRead(samples, 0);
  bitWrite(config, 4, highResolutionBit); //write 2nd bit of samples to 4th of config
  bitWrite(config, 3, midResolutionBit);  //write 1st bit of samples to 3rd of config
  bitWrite(config, 2, lowResolutionBit);  //write 0th bit of samples to 2nd of config

  bool failed = writeSingleRegister(DEVICE_CONFIG, config); //write new config register to MCP9600
  failed |= (readSingleRegister(DEVICE_CONFIG) != config);  //double check that it was written properly
  return failed;                                            //return 1 if the write failed or the register wasn't properly set, 0 otherwise
}

Burst_Sample MCP9600::getBurstSamples()
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG);
  bool highResolutionBit = bitRead(config, 4);
  bool midResolutionBit = bitRead(config, 3);
  bool lowResolutionBit = bitRead(config, 2);
  unsigned char samples = 0;
  bitWrite(samples, 2, highResolutionBit); //write 4th bit of config to 2nd bit of samples
  bitWrite(samples, 1, midResolutionBit);  //write 3rd bit of config to 1st bit of samples
  bitWrite(samples, 0, lowResolutionBit);  //write 2nd bit of config to 0th bit of samples
  return static_cast<Burst_Sample>(samples);
}

bool MCP9600::burstAvailable()
{
  unsigned char status = readSingleRegister(SENSOR_STATUS);
  return (status >> 7); //return only the 7th bit where the burst complete flag is
}

bool MCP9600::startBurst()
{
  unsigned char status = readSingleRegister(SENSOR_STATUS);
  bitWrite(status, 7, 0); //clear the 7th bit of the status register, and send over I2C

  bool failed = writeSingleRegister(SENSOR_STATUS, status); //return whether the write was successful
  failed |= setShutdownMode(BURST);

  return failed;
}

bool MCP9600::setShutdownMode(Shutdown_Mode mode)
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG);
  config = (config >> 2) << 2; //clear last two bits of the device config register
  config |= mode;

  bool failed = writeSingleRegister(DEVICE_CONFIG, config); //write new config register to MCP9600
  failed |= (readSingleRegister(DEVICE_CONFIG) != config);  //double check that it was written properly
  return failed;                                            //return 1 if the write failed or the register wasn't properly set, 0 otherwise
}

Shutdown_Mode MCP9600::getShutdownMode()
{
  unsigned char config = readSingleRegister(DEVICE_CONFIG);
  unsigned char mode = 0;
  bitWrite(mode, 0, bitRead(config, 0));
  bitWrite(mode, 1, bitRead(config, 1));
  return static_cast<Shutdown_Mode>(mode); //clear all bits except the last two and return
}

/*---------------------------- Temperature Alerts ------------------- */

bool MCP9600::configAlertTemp(unsigned char number, float temp)
{
  MCP9600_Register tempLimitRegister;
  switch (number)
  { //pick the right register to put the temp limit in
  case 1:
    tempLimitRegister = ALERT1_LIMIT;
    break;
  case 2:
    tempLimitRegister = ALERT2_LIMIT;
    break;
  case 3:
    tempLimitRegister = ALERT3_LIMIT;
    break;
  case 4:
    tempLimitRegister = ALERT4_LIMIT;
    break;
  default:
    return 1;
    break;
  }

  //convert the temp limit from a float to actual bits in the register
  unsigned int unsignedTempLimit = static_cast<unsigned int>(abs(temp) * 4);
  unsignedTempLimit = unsignedTempLimit << 2;
  int16_t signedTempLimit = static_cast<int16_t>(unsignedTempLimit);
  if (temp < 0)
    signedTempLimit *= -1; //if the original temp limit was negative we shifted away the sign bit, so reapply it if necessary

  //write the new temp limit to the MCP9600, return if it was successful
  return writeDoubleRegister(tempLimitRegister, signedTempLimit);
}

bool MCP9600::configAlertJunction(unsigned char number, bool junction)
{
  MCP9600_Register alertConfigRegister; //pick the register that points to the right alert
  switch (number)
  {
  case 1:
    alertConfigRegister = ALERT1_CONFIG;
    break;
  case 2:
    alertConfigRegister = ALERT2_CONFIG;
    break;
  case 3:
    alertConfigRegister = ALERT3_CONFIG;
    break;
  case 4:
    alertConfigRegister = ALERT4_CONFIG;
    break;
  default:
    return 1;
    break;
  }

  //grab the current value of the config register so we don't overwrite any other settings!
  unsigned char config = readSingleRegister(alertConfigRegister);
  bitWrite(config, 4, junction);
  return writeSingleRegister(alertConfigRegister, config);
}

bool MCP9600::configAlertHysteresis(unsigned char number, unsigned char hysteresis)
{
  MCP9600_Register alertHysteresisRegister;
  switch (number)
  { //pick the register that points to the right alert
  case 1:
    alertHysteresisRegister = ALERT1_HYSTERESIS;
    break;
  case 2:
    alertHysteresisRegister = ALERT2_HYSTERESIS;
    break;
  case 3:
    alertHysteresisRegister = ALERT3_HYSTERESIS;
    break;
  case 4:
    alertHysteresisRegister = ALERT4_HYSTERESIS;
    break;
  default:
    return 1;
    break;
  }

  //write to the MCP9600 register and return if it was successful
  return writeSingleRegister(alertHysteresisRegister, hysteresis);
}

bool MCP9600::configAlertEdge(unsigned char number, bool edge)
{
  MCP9600_Register alertConfigRegister; //pick the register that points to the right alert
  switch (number)
  {
  case 1:
    alertConfigRegister = ALERT1_CONFIG;
    break;
  case 2:
    alertConfigRegister = ALERT2_CONFIG;
    break;
  case 3:
    alertConfigRegister = ALERT3_CONFIG;
    break;
  case 4:
    alertConfigRegister = ALERT4_CONFIG;
    break;
  default:
    return 1;
    break;
  }

  //grab the current value of the config register so we don't overwrite any other settings!
  unsigned char config = readSingleRegister(alertConfigRegister);
  bitWrite(config, 3, edge);
  return writeSingleRegister(alertConfigRegister, config);
}

bool MCP9600::configAlertLogicLevel(unsigned char number, bool level)
{
  MCP9600_Register alertConfigRegister; //pick the register that points to the right alert
  switch (number)
  {
  case 1:
    alertConfigRegister = ALERT1_CONFIG;
    break;
  case 2:
    alertConfigRegister = ALERT2_CONFIG;
    break;
  case 3:
    alertConfigRegister = ALERT3_CONFIG;
    break;
  case 4:
    alertConfigRegister = ALERT4_CONFIG;
    break;
  default:
    return 1;
    break;
  }

  //grab the current value of the config register so we don't overwrite any other settings!
  unsigned char config = readSingleRegister(alertConfigRegister);
  bitWrite(config, 2, level);
  return writeSingleRegister(alertConfigRegister, config);
}

bool MCP9600::configAlertMode(unsigned char number, bool mode)
{
  MCP9600_Register alertConfigRegister; //pick the register that points to the right alert
  switch (number)
  {
  case 1:
    alertConfigRegister = ALERT1_CONFIG;
    break;
  case 2:
    alertConfigRegister = ALERT2_CONFIG;
    break;
  case 3:
    alertConfigRegister = ALERT3_CONFIG;
    break;
  case 4:
    alertConfigRegister = ALERT4_CONFIG;
    break;
  default:
    return 1;
    break;
  }

  //grab the current value of the config register so we don't overwrite any other settings!
  unsigned char config = readSingleRegister(alertConfigRegister);
  bitWrite(config, 1, mode);
  return writeSingleRegister(alertConfigRegister, config);
}

bool MCP9600::configAlertEnable(unsigned char number, bool enable)
{
  MCP9600_Register alertConfigRegister; //pick the register that points to the right alert
  switch (number)
  {
  case 1:
    alertConfigRegister = ALERT1_CONFIG;
    break;
  case 2:
    alertConfigRegister = ALERT2_CONFIG;
    break;
  case 3:
    alertConfigRegister = ALERT3_CONFIG;
    break;
  case 4:
    alertConfigRegister = ALERT4_CONFIG;
    break;
  default:
    return 1;
    break;
  }

  //grab the current value of the config register so we don't overwrite any other settings!
  unsigned char config = readSingleRegister(alertConfigRegister);
  bitWrite(config, 0, enable);
  return writeSingleRegister(alertConfigRegister, config);
}

bool MCP9600::clearAlertPin(unsigned char number)
{
  MCP9600_Register alertConfigRegister; //pick the register we need to use
  switch (number)
  {
  case 1:
    alertConfigRegister = ALERT1_CONFIG;
    break;

  case 2:
    alertConfigRegister = ALERT2_CONFIG;
    break;

  case 3:
    alertConfigRegister = ALERT3_CONFIG;
    break;

  case 4:
    alertConfigRegister = ALERT4_CONFIG;
    break;

  default:
    return 1;
    break;
  }
  //grab the data already in the register so we don't override any other settings!
  unsigned char alertConfig = readSingleRegister(alertConfigRegister);
  bitWrite(alertConfig, 7, 1);

  //write the new register to the MCP9600, return if it was successful
  return writeSingleRegister(alertConfigRegister, alertConfig);
}

bool MCP9600::isTempGreaterThanLimit(unsigned char number)
{
  if (number > 4)
    return 0; //if a nonexistent alert number is given, return with nothing
  unsigned char status = readSingleRegister(SENSOR_STATUS);
  switch (number)
  {
  case 1:
    return bitRead(status, 0);
    break;
  case 2:
    return bitRead(status, 1);
    break;
  case 3:
    return bitRead(status, 2);
    break;
  case 4:
    return bitRead(status, 3);
    break;
  default:
    return 1;
    break;
  }
}

/*------------------------- Internal I2C Abstraction ---------------- */

unsigned char MCP9600::readSingleRegister(MCP9600_Register reg)
{
  //Attempt to read the register until we exit with no error code
  //This attempts to fix the bug where clock stretching sometimes failes, as
  //described in the MCP9600 eratta
  for (unsigned char attempts = 0; attempts <= retryAttempts; attempts++)
  {
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->endTransmission();
    if (_i2cPort->requestFrom((int)_deviceAddress, (int)1) != 0)
    {
      return _i2cPort->read();
    }
  }
  return (0);
}

unsigned int MCP9600::readDoubleRegister(MCP9600_Register reg)
{
  //Attempt to read the register until we exit with no error code
  //This attempts to fix the bug where clock stretching sometimes failes, as
  //described in the MCP9600 eratta
  for (byte attempts = 0; attempts <= retryAttempts; attempts++)
  {
    _i2cPort->beginTransmission(_deviceAddress);
    _i2cPort->write(reg);
    _i2cPort->endTransmission();

    if (_i2cPort->requestFrom((int)_deviceAddress, (int)2) != 0)
    {
      unsigned int data = _i2cPort->read() << 8;
      data |= _i2cPort->read();
      return data;
    }
  }
  return (0);
}

bool MCP9600::writeSingleRegister(MCP9600_Register reg, unsigned char data)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(reg);
  _i2cPort->write(data);
  return (_i2cPort->endTransmission() != 0);
}

bool MCP9600::writeDoubleRegister(MCP9600_Register reg, unsigned int data)
{
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(reg);
  _i2cPort->write(highByte(data));
  _i2cPort->write(lowByte(data));
  return (_i2cPort->endTransmission() != 0);
}
