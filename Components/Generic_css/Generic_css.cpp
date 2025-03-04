// ======================================================================
// \title  Generic_css.cpp
// \author jstar
// \brief  cpp file for Generic_css component implementation class
// ======================================================================

#include "Components/Generic_css/Generic_css.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_css_device.h"
#include "libi2c.h"
}

#include "nos_link.h"


i2c_bus_info_t Generic_CSSI2c;
GENERIC_CSS_Device_Data_tlm_t Generic_CSSData;
namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_css ::
    Generic_css(const char* const compName) :
      Generic_cssComponentBase(compName)
  {

    /* Initialize HWLIB */
    nos_init_link();

    int32_t status = OS_SUCCESS;
    uint16_t Voltage[GENERIC_CSS_NUM_CHANNELS];

    /* Open device specific protocols */
    Generic_CSSI2c.handle = GENERIC_CSS_CFG_HANDLE;
    Generic_CSSI2c.isOpen = PORT_CLOSED;
    Generic_CSSI2c.speed = GENERIC_CSS_CFG_BAUDRATE_HZ;
    Generic_CSSI2c.addr = GENERIC_CSS_I2C_ADDRESS;
    status = i2c_master_init(&Generic_CSSI2c);
    if (status == OS_SUCCESS)
    {
        printf("I2C device %d configured with speed %d \n", Generic_CSSI2c.handle, Generic_CSSI2c.speed);
    }
    else
    {
        printf("I2C device %d failed to initialize! \n", Generic_CSSI2c.handle);
    }
  }

  Generic_css ::
    ~Generic_css()
  {
    // Close the device 
    i2c_master_close(&Generic_CSSI2c);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

//   void Generic_css ::
//     TODO_cmdHandler(
//         FwOpcodeType opCode,
//         U32 cmdSeq
//     )
//   {
//     // TODO
//     this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);


//   }

// }

 // GENERIC_CSS_RequestData
 void Generic_css :: REQUEST_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

  int32_t status = OS_SUCCESS;

  status = GENERIC_CSS_RequestData(&Generic_CSSI2c, &Generic_CSSData);
  if (status == OS_SUCCESS)
  {
    this->log_ACTIVITY_HI_TELEM("GENERIC_CSS command success\n");
  }
  else
  {
    this->log_ACTIVITY_HI_TELEM("GENERIC_CSS command failed!\n");
  }
  // Tell the fprime command system that we have completed the processing of the supplied command with OK status
  this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}


}

 
