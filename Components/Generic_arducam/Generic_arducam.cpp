// ======================================================================
// \title  Generic_arducam.cpp
// \author jstar
// \brief  cpp file for Generic_arducam component implementation class
// ======================================================================

#include "Components/Generic_arducam/Generic_arducam.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_arducam ::
    Generic_arducam(const char* const compName) :
      Generic_arducamComponentBase(compName)
  {

  }

  Generic_arducam ::
    ~Generic_arducam()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_arducam ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
