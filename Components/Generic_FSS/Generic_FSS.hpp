// ======================================================================
// \title  Generic_FSS.hpp
// \author jstar
// \brief  hpp file for Generic_FSS component implementation class
// ======================================================================

#ifndef Components_Generic_FSS_HPP
#define Components_Generic_FSS_HPP

#include "Components/Generic_FSS/Generic_FSSComponentAc.hpp"

namespace Components {

  class Generic_FSS :
    public Generic_FSSComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_FSS object
      Generic_FSS(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_FSS object
      ~Generic_FSS();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO
      //!
      //! TODO
      void TODO_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

  };

}

#endif
