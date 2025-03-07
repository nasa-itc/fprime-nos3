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

trq_info_t trqDevice;
GENERIC_TORQUER_Device_tlm_t trqHk;
uint32_t req_percent, req_direction;


namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_torquer ::
    Generic_torquer(const char* const compName) :
      Generic_torquerComponentBase(compName), m_greetingCount(0)

  {
    int status = OS_SUCCESS;

    status = trq_init(&trqDevice);
    if (status == OS_SUCCESS)
    {
        printf("Torquer initialized successfully \n");
    }
    else
    {
        printf("Torquer device failed to initialize with error %d!\n", status);
    }
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
  }

  Generic_torquer ::
    ~Generic_torquer()
  {
    trq_close(&trqDevice);
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

  void Generic_torquer :: GENERIC_TORQUER_CONFIG_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& greeting) {
    // Copy the command string input into an event string for the Hello event
    Fw::LogStringArg eventGreeting(greeting.toChar());
    int status = OS_SUCCESS;
    std::string tokens = greeting.toChar();
    const char rp = tokens[0];
    const char rd = tokens[1];
    req_percent = atoi(&rp);
    req_direction = atoi(&rd);

    // TODO - add error checking to the above

    status = GENERIC_TORQUER_Config(&trqHk, &trqDevice, req_percent, req_direction);
    if (status == OS_SUCCESS)
    {
        OS_printf("GENERIC_TORQUER_Config command success\n");
    }
    else
    {
        OS_printf("GENERIC_TORQUER_Config command failed!\n");
    }
    // Emit the Hello event with the copied string
    this->log_ACTIVITY_HI_Hello(eventGreeting);
    
    this->tlmWrite_GreetingCount(++this->m_greetingCount);
 
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);

    OS_printf("trqHk.Direction = %d \n", trqHk.Direction);
    OS_printf("trqHk.PercentOn = %d \n", trqHk.PercentOn);
  }



}
