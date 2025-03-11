// ======================================================================
// \title  Generic_mag.cpp
// \author jstar
// \brief  cpp file for Generic_mag component implementation class
// ======================================================================

#include "Components/Generic_mag/Generic_mag.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_mag_device.h"
#include "libspi.h"
}

  
#include "nos_link.h"

/*
** Global Variables
*/
spi_info_t Generic_magSpi;
GENERIC_MAG_Device_Data_tlm_t Generic_magData;


namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_mag ::
    Generic_mag(const char* const compName) :
      Generic_magComponentBase(compName)
  {
    uint32_t status = OS_SUCCESS;

    nos_init_link();

    /* Open device specific protocols */
    Generic_magSpi.deviceString = GENERIC_MAG_CFG_STRING;
    Generic_magSpi.handle = GENERIC_MAG_CFG_HANDLE;
    Generic_magSpi.baudrate = GENERIC_MAG_CFG_BAUD;
    Generic_magSpi.spi_mode = GENERIC_MAG_CFG_SPI_MODE;
    Generic_magSpi.bits_per_word = GENERIC_MAG_CFG_BITS_PER_WORD;
    Generic_magSpi.bus = GENERIC_MAG_CFG_BUS;
    Generic_magSpi.cs = GENERIC_MAG_CFG_CS;
    status = spi_init_dev(&Generic_magSpi);
    if (status == OS_SUCCESS)
    {
        printf("SPI device %s configured with baudrate %d \n", Generic_magSpi.deviceString, Generic_magSpi.baudrate);
    }
    else
    {
        printf("SPI device %s failed to initialize! \n", Generic_magSpi.deviceString);
        status = OS_ERROR;
    }
  }

  Generic_mag ::
    ~Generic_mag()
  {
    uint32_t status = OS_SUCCESS;
    
    status = spi_close_device(&Generic_magSpi);

    nos_destroy_link();

    OS_printf("Cleanly exiting generic_mag application...\n\n"); 
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  // void Generic_mag ::
  //   TODO_cmdHandler(
  //       FwOpcodeType opCode,
  //       U32 cmdSeq
  //   )
  // {
  //   // TODO
  //   this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  // }


  void Generic_mag :: REQUEST_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) 
  {
    int32_t status = OS_SUCCESS;
    int32_t  MagneticIntensityX;
    int32_t  MagneticIntensityY;
    int32_t  MagneticIntensityZ;

    
    status = GENERIC_MAG_RequestData(&Generic_magSpi, &Generic_magData);
    if (status == OS_SUCCESS)
    {
        this->log_ACTIVITY_HI_TELEM("RequestData command success\n");
    }
    else
    {
        this->log_ACTIVITY_HI_TELEM("RequestData command failed!\n");
    }

    MagneticIntensityX = Generic_magData.MagneticIntensityX;
    MagneticIntensityY = Generic_magData.MagneticIntensityY;
    MagneticIntensityZ = Generic_magData.MagneticIntensityZ;

    this->tlmWrite_MagneticIntensityX(MagneticIntensityX);
    this->tlmWrite_MagneticIntensityY(MagneticIntensityY);
    this->tlmWrite_MagneticIntensityZ(MagneticIntensityZ);

    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
