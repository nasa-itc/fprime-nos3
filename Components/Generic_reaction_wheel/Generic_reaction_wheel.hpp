// ======================================================================
// \title  Generic_reaction_wheel.hpp
// \author jstar
// \brief  hpp file for Generic_reaction_wheel component implementation class
// ======================================================================

#ifndef Components_Generic_reaction_wheel_HPP
#define Components_Generic_reaction_wheel_HPP

#include "Components/Generic_reaction_wheel/Generic_reaction_wheelComponentAc.hpp"

namespace Components {

  class Generic_reaction_wheel :
    public Generic_reaction_wheelComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_reaction_wheel object
      Generic_reaction_wheel(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_reaction_wheel object
      ~Generic_reaction_wheel();

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
