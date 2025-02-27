// ======================================================================
// \title  Generic_FSS.cpp
// \author jstar
// \brief  cpp file for Generic_FSS component implementation class
// ======================================================================

#include "Components/Generic_FSS/Generic_FSS.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_FSS ::
    Generic_FSS(const char* const compName) :
      Generic_FSSComponentBase(compName)
  {

  }

  Generic_FSS ::
    ~Generic_FSS()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_FSS ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
