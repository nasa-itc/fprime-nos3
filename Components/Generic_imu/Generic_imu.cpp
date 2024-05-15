// ======================================================================
// \title  Generic_imu.cpp
// \author jstar
// \brief  cpp file for Generic_imu component implementation class
// ======================================================================

#include "Components/Generic_imu/Generic_imu.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_imu ::
    Generic_imu(const char* const compName) :
      Generic_imuComponentBase(compName)
  {

  }

  Generic_imu ::
    ~Generic_imu()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_imu ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
