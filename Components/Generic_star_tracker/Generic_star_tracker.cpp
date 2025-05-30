// ======================================================================
// \title  Generic_star_tracker.cpp
// \author jstar
// \brief  cpp file for Generic_star_tracker component implementation class
// ======================================================================

#include "Components/Generic_star_tracker/Generic_star_tracker.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_star_tracker_device.h"
#include "libuart.h"
}

uart_info_t Generic_star_trackerUart;
GENERIC_STAR_TRACKER_Device_HK_tlm_t Generic_star_trackerHK;
GENERIC_STAR_TRACKER_Device_Data_tlm_t Generic_star_trackerData;
// int32_t status = OS_SUCCESS;

// uint32_t  DeviceCounter;
// uint32_t  DeviceConfig;
// uint32_t  DeviceStatus;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_star_tracker ::
    Generic_star_tracker(const char* const compName) :
      Generic_star_trackerComponentBase(compName)
  {
    int32_t status = OS_SUCCESS;
     /* Open device specific protocols */
    Generic_star_trackerUart.deviceString = GENERIC_STAR_TRACKER_CFG_STRING;
    Generic_star_trackerUart.handle = GENERIC_STAR_TRACKER_CFG_HANDLE;
    Generic_star_trackerUart.isOpen = PORT_CLOSED;
    Generic_star_trackerUart.baud = GENERIC_STAR_TRACKER_CFG_BAUDRATE_HZ;
    status = uart_init_port(&Generic_star_trackerUart);
     if (status == OS_SUCCESS)
    {
        printf("UART device %s configured with baudrate %d \n", Generic_star_trackerUart.deviceString, Generic_star_trackerUart.baud);
    }
    else
    {
        printf("UART device %s failed to initialize! \n", Generic_star_trackerUart.deviceString);
    }

  }

  Generic_star_tracker ::
    ~Generic_star_tracker()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  // void Generic_star_tracker ::
  //   TODO_cmdHandler(
  //       FwOpcodeType opCode,
  //       U32 cmdSeq
  //   )
  // {
  //   // TODO
  //   this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  // }

  // CMD_NOOP
  void Generic_star_tracker :: NOOP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    int32_t status = OS_SUCCESS;
    uint32_t  DeviceCounter;
    
    status = GENERIC_STAR_TRACKER_CommandDevice(&Generic_star_trackerUart, GENERIC_STAR_TRACKER_DEVICE_NOOP_CMD, 0);
    if (status == OS_SUCCESS)
    {
        this->log_ACTIVITY_HI_TELEM("Star Tracker NOOP command success\n");
    }
    else
    {
        this->log_ACTIVITY_HI_TELEM("Star Tracker NOOP command failed!\n");
    }
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  // GENERIC_STAR_TRACKER_RequestHK
  void Generic_star_tracker :: REQUEST_HOUSEKEEPING_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

    int32_t status = OS_SUCCESS;
    uint32_t  DeviceCounter;

    status = GENERIC_STAR_TRACKER_RequestHK(&Generic_star_trackerUart, &Generic_star_trackerHK);
    if (status == OS_SUCCESS)
    {
        this->log_ACTIVITY_HI_TELEM("RequestHK command success\n");
    }
    else
    {
        this->log_ACTIVITY_HI_TELEM("RequestHK command failed!\n");
    }

    DeviceCounter = Generic_star_trackerHK.DeviceCounter;
    // DeviceConfig =  Generic_star_trackerHK.DeviceConfig;
    // DeviceStatus = Generic_star_trackerHK.DeviceStatus;

    this->tlmWrite_DeviceCounter(DeviceCounter);
    // this->tlmWrite_DeviceConfig(DeviceConfig);
    // this->tlmWrite_DeviceStatus(DeviceStatus);
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  //GENERIC_STAR_TRACKER_RequestData
  void Generic_star_tracker :: REQUEST_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    int32_t status = OS_SUCCESS;

    status = GENERIC_STAR_TRACKER_RequestData(&Generic_star_trackerUart, &Generic_star_trackerData);
    if(status < 0)
    {
      this->log_ACTIVITY_HI_TELEM("ST_RequestData: Command Failed");
      OS_printf("GENERIC_STAR_TRACKER_RequestData command \n");
    }
    else{
      this->log_ACTIVITY_HI_TELEM("ST_RequestData: Success!");
      OS_printf("GENERIC_STAR_TRACKER_RequestData: Success for ST!");
      OS_printf("Q0: %lf\n", Generic_star_trackerData.Q0);
      OS_printf("Q1: %lf\n", Generic_star_trackerData.Q1);
      OS_printf("Q2: %lf\n", Generic_star_trackerData.Q2);
      OS_printf("Q3: %lf\n", Generic_star_trackerData.Q3);
      OS_printf("IsValid: %d\n", Generic_star_trackerData.IsValid);
    }

    this->tlmWrite_Q0_Data(Generic_star_trackerData.Q0);
    this->tlmWrite_Q1_Data(Generic_star_trackerData.Q1);
    this->tlmWrite_Q2_Data(Generic_star_trackerData.Q2);
    this->tlmWrite_Q3_Data(Generic_star_trackerData.Q3);
    this->tlmWrite_IsValid(Generic_star_trackerData.IsValid);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
