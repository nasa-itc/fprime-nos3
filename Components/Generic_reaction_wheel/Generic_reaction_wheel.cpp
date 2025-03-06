// ======================================================================
// \title  Generic_reaction_wheel.cpp
// \author jstar
// \brief  cpp file for Generic_reaction_wheel component implementation class
// ======================================================================

#include "Components/Generic_reaction_wheel/Generic_reaction_wheel.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_reaction_wheel ::
    Generic_reaction_wheel(const char* const compName) :
      Generic_reaction_wheelComponentBase(compName)
  {

  }

  Generic_reaction_wheel ::
    ~Generic_reaction_wheel()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_reaction_wheel ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
