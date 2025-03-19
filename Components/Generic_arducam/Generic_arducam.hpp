// ======================================================================
// \title  Generic_arducam.hpp
// \author jstar
// \brief  hpp file for Generic_arducam component implementation class
// ======================================================================

#ifndef Components_Generic_arducam_HPP
#define Components_Generic_arducam_HPP

#include "Components/Generic_arducam/Generic_arducamComponentAc.hpp"

namespace Components {

  class Generic_arducam :
    public Generic_arducamComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_arducam object
      Generic_arducam(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_arducam object
      ~Generic_arducam();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------
      void NOOP_cmdHandler(
          FwOpcodeType opcode, // The opcode
          U32 cmdSeq // The command sequence number
      ) override;

      void I2C_cmdHandler(
          FwOpcodeType opcode, // The opcode
          U32 cmdSeq // The command sequence number
      ) override;

      void SPI_cmdHandler(
          FwOpcodeType opcode, // The opcode
          U32 cmdSeq // The command sequence number
      ) override;

      void IMAGE_cmdHandler(
          FwOpcodeType opcode, // The opcode
          U32 cmdSeq, // The command sequence number
          U32 size // A value for the size of the image
      ) override;

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
