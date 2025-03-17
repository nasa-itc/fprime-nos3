// ======================================================================
// \title  Generic_thruster.hpp
// \author jstar
// \brief  hpp file for Generic_thruster component implementation class
// ======================================================================

#ifndef Components_Generic_thruster_HPP
#define Components_Generic_thruster_HPP

#include "Components/Generic_thruster/Generic_thrusterComponentAc.hpp"

namespace Components {

  class Generic_thruster :
    public Generic_thrusterComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_thruster object
      Generic_thruster(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_thruster object
      ~Generic_thruster();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO
      //!
      //! TODO
      void SetPercentage_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          const U8 percent, //!< Percentage to set Thruster
          const U8 thruster_number //!< Thruster Number to set

  };

}

#endif
