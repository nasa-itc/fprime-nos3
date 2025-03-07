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
#include "libuart.h"
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

    /* Initialize HWLIB */
    nos_init_link();

    int32_t status = OS_SUCCESS;
    
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

  /*void Generic_torquer ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }*/

  void Generic_torquer :: GENERIC_TORQUER_CONFIG_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& Percent, const Fw::CmdStringArg& Direction) {
    int32_t status = OS_SUCCESS;
    uint8_t req_percent, req_direction;
    // Copy the command string input into an event string for the Hello event
    //Fw::LogStringArg eventGreeting(greeting.toChar());  
    //Fw::LogStringArg eventGreeting2(greeting2.toChar());  

    req_percent = atoi(Percent.toChar());
    req_direction = atoi(Direction.toChar());

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
    // Emit the Hello event with the copied string
    //this->log_ACTIVITY_HI_Hello(eventGreeting);
    //this->log_ACTIVITY_HI_Hello(eventGreeting2);

    
    this->tlmWrite_GreetingCount(++this->m_greetingCount);
 

    trqHk.PercentOn = req_percent;
    trqHk.Direction = req_direction;


    this->tlmWrite_Percent(trqHk.PercentOn);
    this->tlmWrite_Direction(trqHk.Direction);
   


    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);

    OS_printf("trqHk.Direction = %d \n", trqHk.Direction);
    OS_printf("trqHk.PercentOn = %d \n", trqHk.PercentOn);
  }



}
