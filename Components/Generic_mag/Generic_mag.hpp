// ======================================================================
// \title  Generic_mag.hpp
// \author jstar
// \brief  hpp file for Generic_mag component implementation class
// ======================================================================

#ifndef Components_Generic_mag_HPP
#define Components_Generic_mag_HPP

#include "Components/Generic_mag/Generic_magComponentAc.hpp"

namespace Components {

  class Generic_mag :
    public Generic_magComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_mag object
      Generic_mag(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_mag object
      ~Generic_mag();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO
      //!
      //! TODO
      // void TODO_cmdHandler(
      //     FwOpcodeType opCode, //!< The opcode
      //     U32 cmdSeq //!< The command sequence number
      // ) override;

       void NOOP_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

  };

}

#endif
