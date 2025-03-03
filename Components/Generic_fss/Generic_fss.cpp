// ======================================================================
// \title  Generic_fss.cpp
// \author jstar
// \brief  cpp file for Generic_fss component implementation class
// ======================================================================

#include "Components/Generic_fss/Generic_fss.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_fss ::
    Generic_fss(const char* const compName) :
      Generic_fssComponentBase(compName)
  {

  }

  Generic_fss ::
    ~Generic_fss()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_fss ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
