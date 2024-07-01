// ======================================================================
// \title  Generic_eps.cpp
// \author jstar
// \brief  cpp file for Generic_eps component implementation class
// ======================================================================

#include "Components/Generic_eps/Generic_eps.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_eps ::
    Generic_eps(const char* const compName) :
      Generic_epsComponentBase(compName)
  {

  }

  Generic_eps ::
    ~Generic_eps()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_eps ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
