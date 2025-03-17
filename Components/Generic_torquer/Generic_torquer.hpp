// ======================================================================
// \title  Generic_torquer.hpp
// \author jstar
// \brief  hpp file for Generic_torquer component implementation class
// ======================================================================

#ifndef Components_Generic_torquer_HPP
#define Components_Generic_torquer_HPP

#include "Components/Generic_torquer/Generic_torquerComponentAc.hpp"

namespace Components {

  class Generic_torquer :
    public Generic_torquerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_torquer object
      Generic_torquer(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_torquer object
      ~Generic_torquer();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO
      //!
      //! TODO
      /*void TODO_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;*/
      
      U32 m_greetingCount;
      //! Handler implementation for command SAY_HELLO
      //!
      //! Command to issue greeting with maximum length of 20 characters
      void GENERIC_TORQUER_CONFIG_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          const uint8_t Percent, //!< Greeting to repeat in the Hello event
          const uint8_t Direction

      ) ;

  };

}

#endif
