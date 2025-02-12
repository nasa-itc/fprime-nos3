// ======================================================================
// \title  Generic_eps.cpp
// \author jstar
// \brief  cpp file for Generic_eps component implementation class
// ======================================================================

#include "Components/Generic_eps/Generic_eps.hpp"
#include "FpConfig.hpp"

extern "C"{
  #include "generic_eps_device.h"
  #include "libi2c.h"
  }
  
  i2c_bus_info_t Generic_epsI2c;
  GENERIC_EPS_Device_HK_tlm_t Generic_epsHK;
  // int32_t status = OS_SUCCESS;
  
  // uint32_t  DeviceCounter;
  // uint32_t  DeviceConfig;
  // uint32_t  DeviceStatus;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_eps ::
    Generic_eps(const char* const compName) :
      Generic_epsComponentBase(compName)
  {

  }

  Generic_eps ::
    ~Generic_eps()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

// GENERIC_EPS_RequestHK
void Generic_eps :: REQUEST_HOUSEKEEPING_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

  int32_t status = OS_SUCCESS;
  uint16_t  BatteryVoltage;
  uint16_t  BatteryTemperature;
  uint16_t  Bus3p3Voltage;
  uint16_t  Bus5p0Voltage;
  uint16_t  Bus12Voltage;
  uint16_t  EPSTemperature;
  uint16_t  SolarArrayVoltage;
  uint16_t  SolarArrayTemperature;
  // GENERIC_EPS_Switch_tlm_t  Switch[8];

   /* Open device specific protocols */
  Generic_epsI2c.handle = GENERIC_EPS_CFG_I2C_HANDLE;
  Generic_epsI2c.addr = GENERIC_EPS_CFG_I2C_ADDRESS;
  Generic_epsI2c.isOpen = I2C_CLOSED;
  Generic_epsI2c.speed = GENERIC_EPS_CFG_I2C_SPEED;
  status = i2c_master_init(&Generic_epsI2c);
  
  status = GENERIC_EPS_RequestHK(&Generic_epsI2c, &Generic_epsHK);
  if (status == OS_SUCCESS)
  {
      this->log_ACTIVITY_HI_TELEM("RequestHK command success\n");
  }
  else
  {
      this->log_ACTIVITY_HI_TELEM("RequestHK command failed!\n");
  }

  BatteryVoltage = Generic_epsHK.BatteryVoltage;
  BatteryTemperature =  Generic_epsHK.BatteryTemperature;
  Bus3p3Voltage = Generic_epsHK.Bus3p3Voltage;
  Bus5p0Voltage =  Generic_epsHK.Bus5p0Voltage;
  Bus12Voltage = Generic_epsHK.Bus12Voltage;
  EPSTemperature =  Generic_epsHK.EPSTemperature;
  SolarArrayVoltage = Generic_epsHK.SolarArrayVoltage;
  SolarArrayTemperature =  Generic_epsHK.SolarArrayTemperature;
  // Switch = Generic_epsHK.Switch;

  this->tlmWrite_BatteryVoltage(BatteryVoltage);
  this->tlmWrite_BatteryTemperature(BatteryTemperature);
  this->tlmWrite_Bus3p3Voltage(Bus3p3Voltage);
  this->tlmWrite_Bus5p0Voltage(Bus5p0Voltage);
  this->tlmWrite_Bus12Voltage(Bus12Voltage);
  this->tlmWrite_EPSTemperature(EPSTemperature);
  this->tlmWrite_SolarArrayVoltage(SolarArrayVoltage);
  this->tlmWrite_SolarArrayTemperature(SolarArrayTemperature);
  // this->tlmWrite_Switch(Switch);

  
  // Tell the fprime command system that we have completed the processing of the supplied command with OK status
  this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}
