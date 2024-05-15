// ======================================================================
// \title  Generic_star_tracker.cpp
// \author jstar
// \brief  cpp file for Generic_star_tracker component implementation class
// ======================================================================

#include "Components/Generic_star_tracker/Generic_star_tracker.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_star_tracker ::
    Generic_star_tracker(const char* const compName) :
      Generic_star_trackerComponentBase(compName)
  {

  }

  Generic_star_tracker ::
    ~Generic_star_tracker()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_star_tracker ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
