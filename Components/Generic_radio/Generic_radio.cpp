// ======================================================================
// \title  Generic_radio.cpp
// \author jstar
// \brief  cpp file for Generic_radio component implementation class
// ======================================================================

#include "Components/Generic_radio/Generic_radio.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_radio_device.h"
#include "generic_radio_app.h"
#include "libuart.h"
}

/*
** Global Variables
*/
// socket_info_t Generic_radioUart;
uart_info_t Generic_radioUart;
GENERIC_RADIO_Device_HK_tlm_t Generic_radioHK;
// GENERIC_RADIO_Device_Data_tlm_t Generic_radioData;

/*
** Global Data
*/
GENERIC_RADIO_AppData_t GENERIC_RADIO_AppData;

void init_socket_data() {

  int32_t status = OS_SUCCESS;

  /*
    ** Initialize application data
    ** Note that counters are excluded as they were reset in the previous code block
    */
    GENERIC_RADIO_AppData.HkTelemetryPkt.DeviceCounter = 0; //was HKTelemetryPKT.DeviceHK instead of hktelemtrypkt
    GENERIC_RADIO_AppData.HkTelemetryPkt.DeviceConfig = 0;
    GENERIC_RADIO_AppData.HkTelemetryPkt.ProxSignal = 0;

    /*
    ** Initialize sockets
    */
    GENERIC_RADIO_AppData.RadioSocket.sockfd = -1;
    GENERIC_RADIO_AppData.RadioSocket.port_num = GENERIC_RADIO_CFG_UDP_RADIO_TO_FSW;
    GENERIC_RADIO_AppData.RadioSocket.ip_address = GENERIC_RADIO_CFG_FSW_IP;
    GENERIC_RADIO_AppData.RadioSocket.address_family = ip_ver_4;
    GENERIC_RADIO_AppData.RadioSocket.type = dgram;
    GENERIC_RADIO_AppData.RadioSocket.category = client;
    GENERIC_RADIO_AppData.RadioSocket.block = false;
    GENERIC_RADIO_AppData.RadioSocket.keep_alive = false;
    GENERIC_RADIO_AppData.RadioSocket.created = false;
    GENERIC_RADIO_AppData.RadioSocket.bound = false;
    GENERIC_RADIO_AppData.RadioSocket.listening = false;
    GENERIC_RADIO_AppData.RadioSocket.connected = false;

    status = socket_create(&GENERIC_RADIO_AppData.RadioSocket);
    if (status != SOCKET_SUCCESS)
    {
       printf("radio socket failed to create");
    }

    GENERIC_RADIO_AppData.ProxySocket.sockfd = -1;
    GENERIC_RADIO_AppData.ProxySocket.port_num = GENERIC_RADIO_CFG_UDP_PROX_TO_FSW;
    GENERIC_RADIO_AppData.ProxySocket.ip_address = GENERIC_RADIO_CFG_FSW_IP;
    GENERIC_RADIO_AppData.ProxySocket.address_family = ip_ver_4;
    GENERIC_RADIO_AppData.ProxySocket.type = dgram;
    GENERIC_RADIO_AppData.ProxySocket.category = client;
    GENERIC_RADIO_AppData.ProxySocket.block = false;
    GENERIC_RADIO_AppData.ProxySocket.keep_alive = false;
    GENERIC_RADIO_AppData.ProxySocket.created = false;
    GENERIC_RADIO_AppData.ProxySocket.bound = false;
    GENERIC_RADIO_AppData.ProxySocket.listening = false;
    GENERIC_RADIO_AppData.ProxySocket.connected = false;

  status = socket_create(&GENERIC_RADIO_AppData.ProxySocket);
  if (status != SOCKET_SUCCESS)
    {
       printf("proxy socket failed to create");
    }

}

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_radio ::
    Generic_radio(const char* const compName) :
      Generic_radioComponentBase(compName)
  {

  }

  Generic_radio ::
    ~Generic_radio()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  // void Generic_radio ::
  //   TODO_cmdHandler(
  //       FwOpcodeType opCode,
  //       U32 cmdSeq
  //   )star
  // {
  //   // TODO
  //   this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  // }


  // GENERIC_radio_RequestHK
  void Generic_radio :: REQUEST_HOUSEKEEPING_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {

    int32_t status = OS_SUCCESS;
    uint32_t  DeviceCounter;

    init_socket_data();

     /* Open device specific protocols */ //needs to be changed for socket_infot_t
    Generic_radioUart.deviceString = GENERIC_RADIO_CFG_STRING;
    Generic_radioUart.handle = GENERIC_RADIO_CFG_HANDLE;
    Generic_radioUart.isOpen = PORT_CLOSED;
    Generic_radioUart.baud = GENERIC_RADIO_CFG_BAUDRATE_HZ;
    status = uart_init_port(&Generic_radioUart);
    if (status == OS_SUCCESS)
    {
        printf("UART device %s configured with baudrate %d \n", Generic_radioUart.deviceString, Generic_radioUart.baud);
    }
    else
    {
        printf("UART device %s failed to initialize! \n", Generic_radioUart.deviceString);
    }
    
    status = GENERIC_RADIO_RequestHK(&GENERIC_RADIO_AppData.RadioSocket, &GENERIC_RADIO_AppData.HkTelemetryPkt);
    if (status == OS_SUCCESS)
    {
        // this->log_ACTIVITY_HI_TELEM("RequestHK command success\n");
    }
    else
    {
        // this->log_ACTIVITY_HI_TELEM("RequestHK command failed!\n");
    }

    

    // DeviceCounter = Generic_radioHK.DeviceCounter;
    DeviceCounter = GENERIC_RADIO_AppData.HkTelemetryPkt.DeviceCounter;
    // DeviceConfig =  Generic_radioHK.DeviceConfig;
    // DeviceStatus = Generic_radioHK.DeviceStatus;
    // DeviceCounter = SampleHK.DeviceCounter;

    this->tlmWrite_DeviceCounter(DeviceCounter);
    // this->tlmWrite_DeviceConfig(DeviceConfig);
    // this->tlmWrite_DeviceStatus(DeviceStatus);
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
