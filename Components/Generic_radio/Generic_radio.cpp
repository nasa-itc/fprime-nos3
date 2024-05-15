// ======================================================================
// \title  Generic_radio.cpp
// \author jstar
// \brief  cpp file for Generic_radio component implementation class
// ======================================================================

#include "Components/Generic_radio/Generic_radio.hpp"
#include "FpConfig.hpp"

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

  void Generic_radio ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
