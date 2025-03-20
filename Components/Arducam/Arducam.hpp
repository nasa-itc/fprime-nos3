// ======================================================================
// \title  Arducam.hpp
// \author jstar
// \brief  hpp file for Arducam component implementation class
// ======================================================================

#ifndef Components_Arducam_HPP
#define Components_Arducam_HPP

#include "Components/Arducam/ArducamComponentAc.hpp"

namespace Components {

  class Arducam :
    public ArducamComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Arducam object
      Arducam(
          const char* const compName //!< The component name
      );

      //! Destroy Arducam object
      ~Arducam();

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

      void IMAGE_cmdHandler(
        FwOpcodeType opcode, // The opcode
        U32 cmdSeq, // The command sequence number
        U32 image_size //
      ) override;

      void SPI_cmdHandler(
          FwOpcodeType opcode, // The opcode
          U32 cmdSeq // The command sequence number
      ) override;

  };

}

#endif
