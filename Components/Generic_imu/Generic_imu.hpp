// ======================================================================
// \title  Generic_imu.hpp
// \author jstar
// \brief  hpp file for Generic_imu component implementation class
// ======================================================================

#ifndef Components_Generic_imu_HPP
#define Components_Generic_imu_HPP

#include "Components/Generic_imu/Generic_imuComponentAc.hpp"

namespace Components {

  class Generic_imu :
    public Generic_imuComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_imu object
      Generic_imu(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_imu object
      ~Generic_imu();

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
