// ======================================================================
// \title  Generic_imu.cpp
// \author jstar
// \brief  cpp file for Generic_imu component implementation class
// ======================================================================

#include "Components/Generic_imu/Generic_imu.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_imu_device.h"
#include "generic_imu_app.h"
#include "generic_imu_platform_cfg.h"
#include "libuart.h"
}

/*
** Global Variables
*/
can_info_t Generic_IMUcan;
GENERIC_IMU_Device_HK_tlm_t Generic_IMUHK;
GENERIC_IMU_Device_Data_tlm_t Generic_IMUData;


/*
** Global Data
*/
GENERIC_IMU_AppData_t GENERIC_IMU_AppData;
int32_t status = OS_SUCCESS;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_imu ::
    Generic_imu(const char* const compName) :
      Generic_imuComponentBase(compName)
  {
    nos_init_link();

    int32_t status = OS_SUCCESS;
    /* Open device specific protocols */
    Generic_IMUcan.handle = GENERIC_IMU_CFG_HANDLE;
    Generic_IMUcan.isUp = CAN_INTERFACE_DOWN;
    Generic_IMUcan.loopback = false;
    Generic_IMUcan.listenOnly = false;
    Generic_IMUcan.tripleSampling = false;
    Generic_IMUcan.oneShot = false;
    Generic_IMUcan.berrReporting = false;
    Generic_IMUcan.fd = false;
    Generic_IMUcan.presumeAck = false;
    Generic_IMUcan.bitrate = GENERIC_IMU_CFG_CAN_BITRATE;
    Generic_IMUcan.second_timeout = GENERIC_IMU_CFG_CAN_TIMEOUT;
    Generic_IMUcan.microsecond_timeout = GENERIC_IMU_CFG_CAN_MS_TIMEOUT;
    Generic_IMUcan.xfer_us_delay = GENERIC_IMU_CFG_CAN_XFER_US;

    status = can_init_dev(&Generic_IMUcan);

    if (status == OS_SUCCESS)
    {
        printf("CAN device 0x%02x configured with speed %d \n", Generic_IMUcan.handle, Generic_IMUcan.bitrate);
    }
    else
    {
        printf("I2C device 0x%02x failed to initialize! \n", Generic_IMUcan.handle);
        status = OS_ERROR;
    }

  }

  Generic_imu ::
    ~Generic_imu()
  {
     // Close the device 
    can_close_device(&Generic_IMUcan);

    nos_destroy_link();

    OS_printf("Cleanly exiting generic_imu application...\n\n"); 
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

// GENERIC_IMU_RequestHK
void Generic_imu :: REQUEST_HOUSEKEEPING_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

  int32_t status = OS_SUCCESS;
  uint32_t DeviceCounter;
  uint32_t DeviceStatus;

  status = GENERIC_IMU_RequestHK(Generic_IMUcan, Generic_IMUHK);
  if (status == OS_SUCCESS)
  {
      this->log_ACTIVITY_HI_TELEM("RequestHK command success\n");
  }
  else
  {
      this->log_ACTIVITY_HI_TELEM("RequestHK command failed!\n");
  }

  DeviceCounter = Generic_IMUHK.DeviceCounter;
  DeviceStatus =  Generic_IMUHK.DeviceStatus;

  this->tlmWrite_DeviceCounter(DeviceCounter);
  this->tlmWrite_DeviceStatus(DeviceStatus);

  
  // Tell the fprime command system that we have completed the processing of the supplied command with OK status
  this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// GENERIC_IMU_RequestData
void Generic_imu :: REQUEST_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

  int32_t status = OS_SUCCESS;
  float X_Axis_LinearAcc;
  float X_Axis_AngularAcc;
  float Y_Axis_LinearAcc;
  float Y_Axis_AngularAcc;
  float Z_Axis_LinearAcc;
  float Z_Axis_AngularAcc;

  status = GENERIC_IMU_RequestData(Generic_IMUcan, Generic_IMUData);
  if (status == OS_SUCCESS)
  {
      this->log_ACTIVITY_HI_TELEM("RequestData command success\n");
  }
  else
  {
      this->log_ACTIVITY_HI_TELEM("RequestData command failed!\n");
  }

  X_Axis_LinearAcc = Generic_IMUData.X_Data.LinearAcc;
  X_Axis_AngularAcc = Generic_IMUData.X_Data.AngularAcc;
  Y_Axis_LinearAcc = Generic_IMUData.Y_Data.LinearAcc;
  Y_Axis_AngularAcc = Generic_IMUData.Y_Data.AngularAcc;
  Z_Axis_LinearAcc = Generic_IMUData.Z_Data.LinearAcc;
  Z_Axis_AngularAcc = Generic_IMUData.Z_Data.AngularAcc;

  this->tlmWrite_X_Axis_LinearAcc(X_Axis_LinearAcc);
  this->tlmWrite_X_Axis_AngularAcc(X_Axis_AngularAcc);
  this->tlmWrite_Y_Axis_LinearAcc(Y_Axis_LinearAcc);
  this->tlmWrite_Y_Axis_AngularAcc(Y_Axis_AngularAcc);
  this->tlmWrite_Z_Axis_LinearAcc(Z_Axis_LinearAcc);
  this->tlmWrite_Z_Axis_AngularAcc(Z_Axis_AngularAcc);

  
  // Tell the fprime command system that we have completed the processing of the supplied command with OK status
  this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void Generic_imu :: NOOP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

  status = GENERIC_IMU_CommandDevice(&Generic_IMUcan, GENERIC_IMU_DEVICE_NOOP_CMD);
  this->log_ACTIVITY_HI_TELEM("NOOP SENT");
  
  // Tell the fprime command system that we have completed the processing of the supplied command with OK status
  this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}


}

