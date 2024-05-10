// ======================================================================
// \title  Generic_mag.cpp
// \author jstar
// \brief  cpp file for Generic_mag component implementation class
// ======================================================================

#include "Components/Generic_mag/Generic_mag.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_mag_device.h"
#include "sample_device.h"
#include "libuart.h"
}

/*
** Global Variables
*/
uart_info_t Generic_magUart;
// GENERIC_MAG_Device_HK_tlm_t Generic_magHK;
// GENERIC_MAG_Device_Data_tlm_t Generic_magData;
int32_t status_2 = OS_SUCCESS;

/* 
** Generic command to device
** Note that confirming the echoed response is specific to this implementation
*/
int32_t GENERIC_MAG_CommandDevice(uart_info_t* device, uint8_t cmd_code, uint32_t payload)
{
    int32_t status = OS_SUCCESS;
    int32_t bytes = 0;
    uint8_t write_data[SAMPLE_DEVICE_CMD_SIZE];
    uint8_t read_data[SAMPLE_DEVICE_DATA_SIZE];

    /* Prepare command */
    write_data[0] = SAMPLE_DEVICE_HDR_0;
    write_data[1] = SAMPLE_DEVICE_HDR_1;
    write_data[2] = cmd_code;
    write_data[3] = payload >> 24;
    write_data[4] = payload >> 16;
    write_data[5] = payload >> 8;
    write_data[6] = payload;
    write_data[7] = SAMPLE_DEVICE_TRAILER_0;
    write_data[8] = SAMPLE_DEVICE_TRAILER_1;

    /* Flush any prior data */
    status = uart_flush(device);
    if (status == UART_SUCCESS)
    {
        /* Write data */
        bytes = uart_write_port(device, write_data, SAMPLE_DEVICE_CMD_SIZE);
        #ifdef SAMPLE_CFG_DEBUG
            OS_printf("  SAMPLE_CommandDevice[%d] = ", bytes);
            for (uint32_t i = 0; i < SAMPLE_DEVICE_CMD_SIZE; i++)
            {
                OS_printf("%02x", write_data[i]);
            }
            OS_printf("\n");
        #endif
        if (bytes == SAMPLE_DEVICE_CMD_SIZE)
        {
            status = SAMPLE_ReadData(device, read_data, SAMPLE_DEVICE_CMD_SIZE);
            if (status == OS_SUCCESS)
            {
                /* Confirm echoed response */
                bytes = 0;
                while ((bytes < (int32_t) SAMPLE_DEVICE_CMD_SIZE) && (status == OS_SUCCESS))
                {
                    if (read_data[bytes] != write_data[bytes])
                    {
                        status = OS_ERROR;
                    }
                    bytes++;
                }
            } /* SAMPLE_ReadData */
            else
            {
                #ifdef SAMPLE_CFG_DEBUG
                    OS_printf("SAMPLE_CommandDevice - SAMPLE_ReadData returned %d \n", status);
                #endif
            }
        } 
        else
        {
            #ifdef SAMPLE_CFG_DEBUG
                OS_printf("SAMPLE_CommandDevice - uart_write_port returned %d, expected %d \n", bytes, SAMPLE_DEVICE_CMD_SIZE);
            #endif
        } /* uart_write */
    } /* uart_flush*/
    return status;
}


namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_mag ::
    Generic_mag(const char* const compName) :
      Generic_magComponentBase(compName)
  {

  }

  Generic_mag ::
    ~Generic_mag()
  {

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


  void Generic_mag :: NOOP_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
  
    /* Open device specific protocols */
    Generic_magUart.deviceString = GENERIC_MAG_CFG_STRING;
    Generic_magUart.handle = GENERIC_MAG_CFG_HANDLE;
    Generic_magUart.isOpen = PORT_CLOSED;
    Generic_magUart.baud = GENERIC_MAG_CFG_BAUDRATE_HZ;
    
    status_2 = uart_init_port(&Generic_magUart);
    
    status_2 = GENERIC_MAG_CommandDevice(&Generic_magUart, SAMPLE_DEVICE_NOOP_CMD, 0);
    this->log_ACTIVITY_HI_TELEM("NOOP SENT");
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    // this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
