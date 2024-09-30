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
uart_info_t Generic_imuUart;
GENERIC_IMU_Device_HK_tlm_t Generic_imuHK;
GENERIC_IMU_Device_Data_tlm_t Generic_imuData;


/*
** Global Data
*/
GENERIC_IMU_AppData_t GENERIC_IMU_AppData;
int32_t status = OS_SUCCESS;

// #define GENERIC_IMU_CFG_HANDLE           0 
// #define GENERIC_IMU_CFG_CAN_ID           15
// #define GENERIC_IMU_CFG_BAUDRATE_HZ      115200
// #define GENERIC_IMU_CFG_MS_TIMEOUT       50            /* Max 255 */

// #define GENERIC_IMU_CFG_CAN_BITRATE                 1000000
// #define GENERIC_IMU_CFG_CAN_TIMEOUT                 1
// #define GENERIC_IMU_CFG_CAN_MS_TIMEOUT              100
// #define GENERIC_IMU_CFG_CAN_XFER_US                 5000
// #define GENERIC_IMU_CFG_RETRY_ATTEMPTS              3

void init_socket_data() {

//   status = GENERIC_IMU_AppInit();
//     if (status != CFE_SUCCESS)
//     {
//         GENERIC_IMU_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
//     }

  GENERIC_IMU_AppData.HkTelemetryPkt.DeviceEnabled = GENERIC_IMU_DEVICE_DISABLED;
  GENERIC_IMU_AppData.HkTelemetryPkt.DeviceHK.DeviceCounter = 0;
  GENERIC_IMU_AppData.HkTelemetryPkt.DeviceHK.DeviceStatus = 0;

  /*
  ** Initialize hardware interface data
  */ 
  
  GENERIC_IMU_AppData.Generic_imuCan.handle = GENERIC_IMU_CFG_HANDLE;
  GENERIC_IMU_AppData.Generic_imuCan.isUp = CAN_INTERFACE_DOWN;
  GENERIC_IMU_AppData.Generic_imuCan.loopback = false;
  GENERIC_IMU_AppData.Generic_imuCan.listenOnly = false;
  GENERIC_IMU_AppData.Generic_imuCan.tripleSampling = false;
  GENERIC_IMU_AppData.Generic_imuCan.oneShot = false;
  GENERIC_IMU_AppData.Generic_imuCan.berrReporting = false;
  GENERIC_IMU_AppData.Generic_imuCan.fd = false;
  GENERIC_IMU_AppData.Generic_imuCan.presumeAck = false;
  GENERIC_IMU_AppData.Generic_imuCan.bitrate = GENERIC_IMU_CFG_CAN_BITRATE;
  GENERIC_IMU_AppData.Generic_imuCan.second_timeout = GENERIC_IMU_CFG_CAN_TIMEOUT;
  GENERIC_IMU_AppData.Generic_imuCan.microsecond_timeout = GENERIC_IMU_CFG_CAN_MS_TIMEOUT;
  GENERIC_IMU_AppData.Generic_imuCan.xfer_us_delay = GENERIC_IMU_CFG_CAN_XFER_US;

  status = can_init_dev(&GENERIC_IMU_AppData.Generic_imuCan);

}

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_imu ::
    Generic_imu(const char* const compName) :
      Generic_imuComponentBase(compName)
  {

  }

  Generic_imu ::
    ~Generic_imu()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  // void Generic_imu ::
  //   TODO_cmdHandler(
  //       FwOpcodeType opCode,
  //       U32 cmdSeq
  //   )
  // {
  //   // TODO
  //   this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  // }

  void Generic_imu :: NOOP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

    int32_t status = OS_SUCCESS;
    uint32_t  DeviceCounter;

    init_socket_data();

    
     /* Open device specific protocols */
    Generic_imuUart.deviceString = GENERIC_IMU_CFG_STRING;
    Generic_imuUart.handle = GENERIC_IMU_CFG_HANDLE;
    Generic_imuUart.isOpen = PORT_CLOSED;
    Generic_imuUart.baud = GENERIC_IMU_CFG_BAUDRATE_HZ;
    status = uart_init_port(&Generic_imuUart);
    if (status == OS_SUCCESS)
    {
        printf("UART device %s configured with baudrate %d \n", Generic_imuUart.deviceString, Generic_imuUart.baud);
    }
    else
    {
        printf("UART device %s failed to initialize! \n", Generic_imuUart.deviceString);
    }
    
    status = GENERIC_IMU_CommandDevice(&GENERIC_IMU_AppData.Generic_imuCan, GENERIC_IMU_DEVICE_NOOP_CMD);
    // if (status == OS_SUCCESS)
    // {
    //     OS_printf("NOOP command success\n");
    // }
    // else
    // {
    //     OS_printf("NOOP command failed!\n");
    // }
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}

