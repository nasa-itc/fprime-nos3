// ======================================================================
// \title  Generic_star_tracker.hpp
// \author jstar
// \brief  hpp file for Generic_star_tracker component implementation class
// ======================================================================

#ifndef Components_Generic_star_tracker_HPP
#define Components_Generic_star_tracker_HPP

#include "Components/Generic_star_tracker/Generic_star_trackerComponentAc.hpp"

namespace Components {

  class Generic_star_tracker :
    public Generic_star_trackerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_star_tracker object
      Generic_star_tracker(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_star_tracker object
      ~Generic_star_tracker();

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

      void REQUEST_HOUSEKEEPING_cmdHandler(
        FwOpcodeType opCode, 
        U32 cmdSeq
      ) override;

  };

}

#endif
