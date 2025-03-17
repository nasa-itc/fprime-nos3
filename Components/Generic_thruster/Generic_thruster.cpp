// ======================================================================
// \title  Generic_thruster.cpp
// \author jstar
// \brief  cpp file for Generic_thruster component implementation class
// ======================================================================

#include "Components/Generic_thruster/Generic_thruster.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_thruster_device.h"
#include "libuart.h"
}

#include "nos_link.h"

uart_info_t ThrusterUart;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_thruster ::
    Generic_thruster(const char* const compName) : Generic_thrusterComponentBase(compName)
  {

    int status = OS_SUCCESS;


    /* Initialize HWLIB */
    nos_init_link();


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

    nos_destroy_link();

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_thruster ::
    SetPercentage_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        const U8 percent, 
        const U8 thruster_number
    )
  {
    int32_t status = OS_SUCCESS;
    int32_t exit_status = OS_SUCCESS;

    status = GENERIC_THRUSTER_SetPercentage(&ThrusterUart, thruster_number, percent, GENERIC_THRUSTER_DEVICE_CMD_SIZE);
      if (status == OS_SUCCESS)
        {
          this->log_ACTIVITY_HI_TELEM("Thruster SetPercentage Command Success!");
          OS_printf("Thruster %u command success with value %u\n", thruster_number, percent);
          this->tlmWrite_thruster_number(thruster_number);
          this->tlmWrite_percentage(percent);
        }
        else
        {
          this->log_ACTIVITY_HI_TELEM("Thruster SetPercentage Command Failure!");
          OS_printf("Thruster %u command failure with value %u\n", thruster_number, percent);
        }
        
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
