// ======================================================================
// \title  Generic_arducam.cpp
// \author jstar
// \brief  cpp file for Generic_arducam component implementation class
// ======================================================================

#include "Components/Generic_arducam/Generic_arducam.hpp"
#include "FpConfig.hpp"

extern "C"{

}

i2c_bus_info_t CAM_I2C;
spi_info_t CAM_SPI;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_arducam ::
    Generic_arducam(const char* const compName) :
      Generic_arducamComponentBase(compName)
  {
    nos_init_link();
  }

  Generic_arducam ::
    ~Generic_arducam()
  {
    // Close the device(s)
    i2c_master_close(&CAM_I2C);
    spi_close_device(&CAM_SPI);

    #ifdef _NOS_ENGINE_LINK_
        nos_destroy_link();
    #endif

    OS_printf("Cleanly exiting arducam application...\n\n");
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_arducam :: NOOP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    int32_t status = OS_SUCCESS;
    uint32_t  DeviceCounter;
    status = GENERIC_ARDUCAM_CommandDevice(&Generic_arducamUart, GENERIC_ARDUCAM_DEVICE_NOOP_CMD, 0);
    if (status == OS_SUCCESS)
    {   
        this->log_ACTIVITY_HI_TELEM("Arducam NOOP command success\n");
    }   
    else
    {   
        this->log_ACTIVITY_HI_TELEM("Arducam NOOP command failed!\n");
    }   
                                                                                               
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void Generic_arducam ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
