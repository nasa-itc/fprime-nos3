// ======================================================================
// \title  Generic_radio.hpp
// \author jstar
// \brief  hpp file for Generic_radio component implementation class
// ======================================================================

#ifndef Components_Generic_radio_HPP
#define Components_Generic_radio_HPP

#include "Components/Generic_radio/Generic_radioComponentAc.hpp"

namespace Components {

  class Generic_radio :
    public Generic_radioComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_radio object
      Generic_radio(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_radio object
      ~Generic_radio();

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