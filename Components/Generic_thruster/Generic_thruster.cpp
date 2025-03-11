// ======================================================================
// \title  Generic_thruster.cpp
// \author jstar
// \brief  cpp file for Generic_thruster component implementation class
// ======================================================================

#include "Components/Generic_thruster/Generic_thruster.hpp"
#include <Fw/Logger/Logger.hpp>
#include "FpConfig.hpp"


extern "C"{
  #include "generic_thruster_device.h"
  #include "libuart.h"
  }

uart_info_t ThrusterUart;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_thruster ::
    Generic_thruster(const char* const compName) : Generic_thrusterComponentBase(compName),
    m_greetingCount(0)
  {

    int status = OS_SUCCESS;


     /* Initialize HWLIB */
    #ifdef _NOS_ENGINE_LINK_
        nos_init_link();
    #endif

    /* Open device specific protocols */
    ThrusterUart.deviceString = GENERIC_THRUSTER_CFG_STRING;
    ThrusterUart.handle = GENERIC_THRUSTER_CFG_HANDLE;
    ThrusterUart.isOpen = PORT_CLOSED;
    ThrusterUart.baud = GENERIC_THRUSTER_CFG_BAUDRATE_HZ;
    status = uart_init_port(&ThrusterUart);
    if (status == OS_SUCCESS)
    {
        printf("UART device %s configured with baudrate %d \n", ThrusterUart.deviceString, ThrusterUart.baud);
    }
    else
    {
        printf("UART device %s failed to initialize! \n", ThrusterUart.deviceString);
    }
  }

  Generic_thruster ::
    ~Generic_thruster()
  {
    uart_close_port(&ThrusterUart);

    #ifdef _NOS_ENGINE_LINK_
        nos_destroy_link();
    #endif

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_thruster ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        const Fw::CmdStringArg& percent, //!< Greeting to repeat in the Hello event
        const Fw::CmdStringArg& thruster_number //!< Greeting to repeat in the Hello event
    )
  {
    int32_t status = OS_SUCCESS;
    int32_t exit_status = OS_SUCCESS;
    uint8_t tnum = atoi(thruster_number.toChar());
    uint8_t perc = atoi(percent.toChar());


    this->tlmWrite_thruster_number(tnum);
    this->tlmWrite_percentage(perc);
    // TODO
    //thruster_number = atoi(tokens[0]);
    //percentage = atoi(tokens[1]);
    status = GENERIC_THRUSTER_SetPercentage(&ThrusterUart, tnum, perc, GENERIC_THRUSTER_DEVICE_CMD_SIZE);
      if (status == OS_SUCCESS)
        {
          //this->log_ACTIVITY_HI_TELEM("Thruster %d command success with value %u\n", tnum, perc);
          this->log_ACTIVITY_HI_TELEM("Configuration command success!\n");

        }
        else
        {
          this->log_ACTIVITY_HI_TELEM("Configuration command failed!\n");
        }
    this->tlmWrite_GreetingCount(++this->m_greetingCount);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
