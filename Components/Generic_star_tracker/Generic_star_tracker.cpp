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

  void Generic_star_tracker :: REQUEST_HOUSEKEEPING_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

    int32_t status = OS_SUCCESS;
    uint32_t  DeviceCounter;

     /* Open device specific protocols */
    Generic_star_trackerUart.deviceString = GENERIC_STAR_TRACKER_CFG_STRING;
    Generic_star_trackerUart.handle = GENERIC_STAR_TRACKER_CFG_HANDLE;
    Generic_star_trackerUart.isOpen = PORT_CLOSED;
    Generic_star_trackerUart.baud = GENERIC_STAR_TRACKER_CFG_BAUDRATE_HZ;
    status = uart_init_port(&Generic_star_trackerUart);
    
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

}
