// ======================================================================
// \title  Generic_css.cpp
// \author jstar
// \brief  cpp file for Generic_css component implementation class
// ======================================================================

#include "Components/Generic_css/Generic_css.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_css ::
    Generic_css(const char* const compName) :
      Generic_cssComponentBase(compName)
  {

  }

  Generic_css ::
    ~Generic_css()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_css ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
