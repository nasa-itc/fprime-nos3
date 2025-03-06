// ======================================================================
// \title  Generic_reaction_wheel.cpp
// \author jstar
// \brief  cpp file for Generic_reaction_wheel component implementation class
// ======================================================================

/*
** Include Files
*/
#include "Components/Generic_reaction_wheel/Generic_reaction_wheel.hpp"
#include "FpConfig.hpp"

extern "C"{
#include "generic_reaction_wheel_device.h"
#include "libuart.h"
}

#include "nos_link.h"

/*
** Global Variables
*/
static uart_info_t RW_UART[3] = {
  {.deviceString = &GENERIC_REACTION_WHEEL_1_CFG_STRING[0], .handle = GENERIC_REACTION_WHEEL_1_CFG_HANDLE, .isOpen = GENERIC_REACTION_WHEEL_1_CFG_IS_OPEN, .baud = GENERIC_REACTION_WHEEL_1_CFG_BAUDRATE_HZ},
  {.deviceString = &GENERIC_REACTION_WHEEL_2_CFG_STRING[0], .handle = GENERIC_REACTION_WHEEL_2_CFG_HANDLE, .isOpen = GENERIC_REACTION_WHEEL_2_CFG_IS_OPEN, .baud = GENERIC_REACTION_WHEEL_2_CFG_BAUDRATE_HZ},
  {.deviceString = &GENERIC_REACTION_WHEEL_3_CFG_STRING[0], .handle = GENERIC_REACTION_WHEEL_3_CFG_HANDLE, .isOpen = GENERIC_REACTION_WHEEL_3_CFG_IS_OPEN, .baud = GENERIC_REACTION_WHEEL_3_CFG_BAUDRATE_HZ},
};

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_reaction_wheel ::
    Generic_reaction_wheel(const char* const compName) :
      Generic_reaction_wheelComponentBase(compName)
  {
    uint32_t status = OS_SUCCESS;

    /* Initialize HWLIB */
    nos_init_link();

    /* Connect to the UART */
    status = uart_init_port(&RW_UART[0]);
    if(status != OS_SUCCESS)
    {
    	OS_printf("GENERIC_RW Checkout: UART 0 port initialization error!\n");
    }    
    status = uart_init_port(&RW_UART[1]);
    if(status != OS_SUCCESS)
    {
    	OS_printf("GENERIC_RW Checkout: UART 1 port initialization error!\n");
    }    
    status = uart_init_port(&RW_UART[2]);
    if(status != OS_SUCCESS)
    {
    	OS_printf("GENERIC_RW Checkout: UART 2 port initialization error!\n");
    } 
  }

  Generic_reaction_wheel ::
    ~Generic_reaction_wheel()
  {
    // Close the devices
    for ( int i = 0; i < 3; i++ )
    {
        uart_close_port(&RW_UART[i]);
    }

    nos_destroy_link();

    OS_printf("Cleanly exiting generic_reaction_wheel application...\n\n"); 
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  // GENERIC_REACTION_WHEEL_Get_Momentum
  void Generic_reaction_wheel :: GET_MOMENTUM_cmdHandler(FwOpcodeType opCode, U32 cmdSeq)
  {

    int32_t status = OS_SUCCESS;
    double RW0_Data;
    double RW1_Data;
    double RW2_Data;

    status = GetCurrentMomentum(&RW_UART[0], &RW0_Data);
    if (status < 0)
    {
        OS_printf("GENERIC_REACTION_WHEEL_RequestData command failed for RW 0!\n");
    }
    else
    {
        OS_printf("RW_GetCurrentMomentum: Success for RW 0! Momentum: %lf\n", RW0_Data);
    }
    status = GetCurrentMomentum(&RW_UART[1], &RW1_Data);
    if (status < 0)
    {
        OS_printf("GENERIC_REACTION_WHEEL_RequestData command failed for RW 1!\n");
    }
    else
    {
        OS_printf("RW_GetCurrentMomentum: Success for RW 1! Momentum: %lf\n", RW1_Data);
    }
    status = GetCurrentMomentum(&RW_UART[2], &RW2_Data);
    if (status < 0)
    {
        OS_printf("GENERIC_REACTION_WHEEL_RequestData command failed for RW 2!\n");
    }
    else
    {
        OS_printf("RW_GetCurrentMomentum: Success for RW 2! Momentum: %lf\n", RW2_Data);
    }


    this->tlmWrite_RW0_Data(RW0_Data);
    this->tlmWrite_RW1_Data(RW1_Data);
    this->tlmWrite_RW2_Data(RW2_Data);
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  // GENERIC_REACTION_WHEEL_Set_Torque
  void Generic_reaction_wheel :: SET_TORQUE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, const Fw::CmdStringArg& wheel_num, const Fw::CmdStringArg& torque) 
  {

    int32_t status = OS_SUCCESS;
    int wheel = atoi(wheel_num.toChar());
    double torqueVal = atof(torque.toChar());
    
    status = SetRWTorque(&RW_UART[wheel], torqueVal);
    if (status < 0)
    {   
        OS_printf("GENERIC_REACTION_WHEEL_SetTorque command failed for RW %d!\n", wheel);
    }
    else
    {
        OS_printf("RW %d torque successfully set to %lf\n", wheel, torqueVal);
    }    
    
    // Tell the fprime command system that we have completed the processing of the supplied command with OK status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
