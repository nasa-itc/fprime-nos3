// ======================================================================
// \title  Generic_fss.cpp
// \author jstar
// \brief  cpp file for Generic_fss component implementation class
// ======================================================================

#include "Components/Generic_fss/Generic_fss.hpp"
#include "FpConfig.hpp"

/*
** Global Variables
*/
spi_info_t FssSpi;
GENERIC_FSS_Device_Data_tlm_t FSSData;

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_fss ::
    Generic_fss(const char* const compName) :
      Generic_fssComponentBase(compName)
  {
    /* Initialize HWLIB */
    nos_init_link();

    /*
    ** Initialize hardware interface data
    */ 
    FssSpi.deviceString = GENERIC_FSS_CFG_STRING;
    FssSpi.handle = GENERIC_FSS_CFG_HANDLE;
    FssSpi.baudrate = GENERIC_FSS_CFG_BAUD;
    FssSpi.spi_mode = GENERIC_FSS_CFG_SPI_MODE;
    FssSpi.bits_per_word = GENERIC_FSS_CFG_BITS_PER_WORD;
    FssSpi.bus = GENERIC_FSS_CFG_BUS;
    FssSpi.cs = GENERIC_FSS_CFG_CS;

    /* Open device specific protocols */
    status = spi_init_dev(&FssSpi);
    if (status == OS_SUCCESS)
    {
        printf("SPI device %s configured with baudrate %d \n", FssSpi.deviceString, FssSpi.baudrate);
    }
    else
    {
        printf("SPI device %s failed to initialize! \n", FssSpi.deviceString);
        run_status = OS_ERROR;
    }

  }

  Generic_fss ::
    ~Generic_fss()
  {
    // Close the device 
    spi_close_device(&FssSpi);

    nos_destroy_link();


  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_fss :: REQUEST_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq)
  {
    int32_t status = OS_SUCCESS;
    uint8_t read_data[GENERIC_FSS_DEVICE_DATA_SIZE];
    uint8_t write_data[GENERIC_FSS_DEVICE_DATA_SIZE];
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
