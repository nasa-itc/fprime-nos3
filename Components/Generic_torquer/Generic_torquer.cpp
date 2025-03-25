// ======================================================================
// \title  Generic_torquer.cpp
// \author jstar
// \brief  cpp file for Generic_torquer component implementation class
// ======================================================================

#include <string>
#include "Components/Generic_torquer/Generic_torquer.hpp"
#include <Fw/Logger/Logger.hpp>
#include "FpConfig.hpp"

extern "C"{
#include "generic_torquer_device.h"
#include "libtrq.h"
}

#include "nos_link.h"

trq_info_t trqDevice;
GENERIC_TORQUER_Device_tlm_t trqHk;




namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_torquer ::
    Generic_torquer(const char* const compName) :
      Generic_torquerComponentBase(compName), m_greetingCount(0)

  {
    int32_t status = OS_SUCCESS;
    /* Initialize HWLIB */
    nos_init_link();
    
    /* Open device specific protocols */
    trqHk.Direction = 0;
    trqHk.PercentOn = 0;
    
    trqDevice.trq_num = 0;
    trqDevice.timer_period_ns = GENERIC_TORQUER_CFG_PERIOD;
    trqDevice.timerfd = 0;
    trqDevice.direction_pin_fd = 0;
    trqDevice.timer_high_ns = 0;
    trqDevice.positive_direction = false;
    trqDevice.enabled = false;
    
    status = trq_init(&trqDevice);
    if (status == OS_SUCCESS)
    {
        printf("Torquer initialized successfully \n");
    }
    else
    {
        printf("Torquer device failed to initialize with error %d!\n", status);
    }
  }

  Generic_torquer ::
    ~Generic_torquer()
  {
    trq_close(&trqDevice);
    nos_destroy_link();
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_torquer :: GENERIC_TORQUER_CONFIG_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const uint8_t Percent, const uint8_t Direction) {
    int32_t status = OS_SUCCESS;
    uint8_t req_percent, req_direction;
      

    req_percent = Percent;
    req_direction = Direction;

    // TODO - add error checking to the above

    status = GENERIC_TORQUER_Config(&trqHk, &trqDevice, req_percent, req_direction);
    if (status == OS_SUCCESS)
    {
        this->log_ACTIVITY_HI_TELEM("trq command success\n");
    }
    else
    {
        this->log_ACTIVITY_HI_TELEM("trq command failed!\n");
    }

    //trqHk.PercentOn = req_percent;
    //rqHk.Direction = req_direction;


    this->tlmWrite_Percent(trqHk.PercentOn);
    this->tlmWrite_Direction(trqHk.Direction);
   


    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);

    OS_printf("trqHk.Direction = %d \n", trqHk.Direction);
    OS_printf("trqHk.PercentOn = %d \n", trqHk.PercentOn);
  }



}
