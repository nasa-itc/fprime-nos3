// ======================================================================
// \title  Generic_radio.cpp
// \author jstar
// \brief  cpp file for Generic_radio component implementation class
// ======================================================================

#include "Components/Generic_radio/Generic_radio.hpp"
#include <Fw/Logger/Logger.hpp>
#include "FpConfig.hpp"

extern "C"{
#include "generic_radio_device.h"
// #include "generic_radio_app.h"
}

/*
** Global Variables
*/
socket_info_t RadioSocket;
socket_info_t ProxSocket;
GENERIC_RADIO_Device_HK_tlm_t RadioHK;
uint8_t RadioData;
uint16_t SCID = 0x42;


void init_socket_data() {

  int status = OS_SUCCESS;
  uint8_t run_status = OS_SUCCESS;

  /* Initialize HWLIB */
    #ifdef _NOS_ENGINE_LINK_
        nos_init_link();
    #endif

    /*
    ** Initialize sockets
    */
    RadioSocket.sockfd = -1;
    RadioSocket.port_num = GENERIC_RADIO_CFG_UDP_RADIO_TO_FSW;
    RadioSocket.ip_address = GENERIC_RADIO_CFG_FSW_IP;
    RadioSocket.address_family = ip_ver_4;
    RadioSocket.type = dgram;
    RadioSocket.category = client;
    RadioSocket.block = false;
    RadioSocket.keep_alive = false;
    RadioSocket.created = false;
    RadioSocket.bound = false;
    RadioSocket.listening = false;
    RadioSocket.connected = false;

    status = socket_create(&RadioSocket);
    if (status != SOCKET_SUCCESS)
    {
        printf("GENERIC_RADIO: Radio interface create error %d\n", status);
        run_status = OS_ERROR;
    }
    else
    {
        printf("GENERIC_RADIO: Radio Interface %d created successfully!\n", RadioSocket.sockfd);
    }

    OS_printf("port: %d; IP: %s \n", RadioSocket.port_num, RadioSocket.ip_address);

    ProxSocket.sockfd = -1;
    ProxSocket.port_num = GENERIC_RADIO_CFG_UDP_PROX_TO_FSW;
    ProxSocket.ip_address = GENERIC_RADIO_CFG_FSW_IP;
    ProxSocket.address_family = ip_ver_4;
    ProxSocket.type = dgram;
    ProxSocket.category = client;
    ProxSocket.block = false;
    ProxSocket.keep_alive = false;
    ProxSocket.created = false;
    ProxSocket.bound = false;
    ProxSocket.listening = false;
    ProxSocket.connected = false;

    status = socket_create(&ProxSocket);
    if (status != SOCKET_SUCCESS)
    {
        printf("GENERIC_RADIO: Proximity interface create error %d\n", status);
        run_status = OS_ERROR;
    }
    else
    {
        printf("GENERIC_RADIO: Proximity Interface %d created successfully!\n", ProxSocket.sockfd);
    }

    OS_printf("port: %d; IP: %s \n", ProxSocket.port_num, ProxSocket.ip_address);


}

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_radio ::
    Generic_radio(const char* const compName) :
      Generic_radioComponentBase(compName)
  {
        init_socket_data();
  }

  Generic_radio ::
    ~Generic_radio()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  // GENERIC_radio_RequestHK
  void Generic_radio :: REQUEST_HOUSEKEEPING_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    uint32_t  DeviceCounter;
    uint32_t  DeviceConfig;
    uint32_t  ProxySignal;
    int32_t status = OS_SUCCESS;
    // uint32_t  DeviceCounter;
    // uint32_t DeviceConfig;

    status = GENERIC_RADIO_RequestHK(&RadioSocket, &RadioHK);
    
    if (status == OS_SUCCESS)
    {
        this->log_ACTIVITY_HI_TELEM("RequestHK command success\n");
    }
    else
    {
        this->log_ACTIVITY_HI_TELEM("RequestHK command failed!\n");
    }

    
    // OS_printf("GENERIC_RADIO_RequestHK command success!\n");
    // OS_printf("GENERIC_RADIO_DEVICE_HK:\n");
    // OS_printf("  Device Counter:  %u\n", RadioHK.DeviceCounter);
    // OS_printf("  Device Config: 0x%07X\n", RadioHK.DeviceConfig);
    // OS_printf("  Prox Signal:     %u\n", RadioHK.ProxSignal);
    // OS_printf("\n");

    DeviceCounter = RadioHK.DeviceCounter;
    DeviceConfig =  RadioHK.DeviceConfig;
    ProxySignal = RadioHK.ProxSignal;

    // DeviceCounter = Generic_radioHK.DeviceCounter;
    // DeviceCounter = GENERIC_RADIO_AppData.HkTelemetryPkt.DeviceCounter;
    // DeviceConfig =  Generic_radioHK.DeviceConfig;
    // DeviceStatus = Generic_radioHK.DeviceStatus;
    // DeviceCounter = SampleHK.DeviceCounter;

    this->tlmWrite_DeviceCounter(DeviceCounter);
    // this->tlmWrite_DeviceConfig(DeviceConfig);
    // this->tlmWrite_ProxySignal(ProxySignal);
    // this->tlmWrite_DeviceStatus(DeviceStatus);
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
