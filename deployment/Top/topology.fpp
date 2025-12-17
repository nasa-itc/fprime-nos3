module deployment {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

  enum Ports_RateGroups {
    rateGroup1
    rateGroup2
    rateGroup3
    rateGroup4
  }

  topology deployment {

  # ----------------------------------------------------------------------
  # Subtopology imports
  # ----------------------------------------------------------------------
    import CdhCore.Subtopology
    import ComCcsds.Subtopology
    import DataProducts.Subtopology
    import FileHandling.Subtopology
    
  # ----------------------------------------------------------------------
  # Instances used in the topology
  # ----------------------------------------------------------------------
    #instance chronoTime
    instance rateGroup1
    instance rateGroup2
    instance rateGroup3
    instance rateGroup4
    instance rateGroupDriver
    instance systemResources
    instance timer
    instance comDriver
    instance cmdSeq
    instance sampleSim
    instance nos3Time
    instance generic_mag
    instance generic_star_tracker
    instance generic_radio
    instance generic_torquer
    instance generic_css
    instance generic_fss
    instance generic_eps
    instance arducam
    instance generic_thruster
    instance generic_imu
    instance generic_reaction_wheel
    instance novatel_oem615
    instance generic_adcs

  # ----------------------------------------------------------------------
  # Pattern graph specifiers
  # ----------------------------------------------------------------------

    command connections instance CdhCore.cmdDisp
    event connections instance CdhCore.events
    telemetry connections instance CdhCore.tlmSend
    text event connections instance CdhCore.textLogger
    health connections instance CdhCore.$health
    param connections instance FileHandling.prmDb
    time connections instance nos3Time

  # ----------------------------------------------------------------------
  # Telemetry packets (only used when TlmPacketizer is used)
  # ----------------------------------------------------------------------

    # include "deploymentPackets.fppi"

  # ----------------------------------------------------------------------
  # Direct graph specifiers
  # ----------------------------------------------------------------------

    connections ComCcsds_CdhCore {
      # Core events and telemetry to communication queue
      CdhCore.events.PktSend -> ComCcsds.comQueue.comPacketQueueIn[ComCcsds.Ports_ComPacketQueue.EVENTS]
      CdhCore.tlmSend.PktSend -> ComCcsds.comQueue.comPacketQueueIn[ComCcsds.Ports_ComPacketQueue.TELEMETRY]

      # Router to Command Dispatcher
      ComCcsds.fprimeRouter.commandOut -> CdhCore.cmdDisp.seqCmdBuff
      CdhCore.cmdDisp.seqCmdStatus -> ComCcsds.fprimeRouter.cmdResponseIn
      
    }

    connections ComCcsds_FileHandling {
      # File Downlink to Communication Queue
      FileHandling.fileDownlink.bufferSendOut -> ComCcsds.comQueue.bufferQueueIn[ComCcsds.Ports_ComBufferQueue.FILE]
      ComCcsds.comQueue.bufferReturnOut[ComCcsds.Ports_ComBufferQueue.FILE] -> FileHandling.fileDownlink.bufferReturn

      # Router to File Uplink
      ComCcsds.fprimeRouter.fileOut -> FileHandling.fileUplink.bufferSendIn
      FileHandling.fileUplink.bufferSendOut -> ComCcsds.fprimeRouter.fileBufferReturnIn
    }

    connections Communications {
      # ComDriver buffer allocations
      comDriver.allocate      -> ComCcsds.commsBufferManager.bufferGetCallee
      comDriver.deallocate    -> ComCcsds.commsBufferManager.bufferSendIn
      
      # ComDriver <-> ComStub (Uplink)
      comDriver.$recv                     -> ComCcsds.comStub.drvReceiveIn
      ComCcsds.comStub.drvReceiveReturnOut -> comDriver.recvReturnIn
      
      # ComStub <-> ComDriver (Downlink)
      ComCcsds.comStub.drvSendOut      -> comDriver.$send
      comDriver.ready         -> ComCcsds.comStub.drvConnected
    }

    connections FileHandling_DataProducts {
      # Data Products to File Downlink
      DataProducts.dpCat.fileOut -> FileHandling.fileDownlink.SendFile
      FileHandling.fileDownlink.FileComplete -> DataProducts.dpCat.fileDone
    }

    connections RateGroups {
      # timer to drive rate group
      timer.CycleOut -> rateGroupDriver.CycleIn

      # Rate group 1
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      rateGroup1.RateGroupMemberOut[0] -> CdhCore.tlmSend.Run
      rateGroup1.RateGroupMemberOut[1] -> FileHandling.fileDownlink.Run
      rateGroup1.RateGroupMemberOut[2] -> systemResources.run
      rateGroup1.RateGroupMemberOut[3] -> ComCcsds.comQueue.run
      #rateGroup1.RateGroupMemberOut[4] -> generic_imu.updateTlm
      #rateGroup1.RateGroupMemberOut[5] -> generic_star_tracker.updateTlm
      #rateGroup1.RateGroupMemberOut[6] -> generic_mag.updateTlm
      #rateGroup1.RateGroupMemberOut[7] -> generic_reaction_wheel.updateTlm
      #rateGroup1.RateGroupMemberOut[8] -> generic_fss.updateTlm
      #rateGroup1.RateGroupMemberOut[9] -> generic_css.updateTlm
      #rateGroup1.RateGroupMemberOut[10] -> generic_torquer.updateTlm


      # Rate group 2
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup2] -> rateGroup2.CycleIn
      rateGroup2.RateGroupMemberOut[0] -> cmdSeq.schedIn

      # Rate group 3
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup3] -> rateGroup3.CycleIn
      rateGroup3.RateGroupMemberOut[0] -> CdhCore.$health.Run
      rateGroup3.RateGroupMemberOut[1] -> ComCcsds.commsBufferManager.schedIn
      rateGroup3.RateGroupMemberOut[2] -> DataProducts.dpBufferManager.schedIn
      rateGroup3.RateGroupMemberOut[3] -> DataProducts.dpWriter.schedIn
      rateGroup3.RateGroupMemberOut[4] -> DataProducts.dpMgr.schedIn
    

      # Rate group 4
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup4] -> rateGroup4.CycleIn
      #rateGroup4.RateGroupMemberOut[0] -> generic_imu.updateData
      #rateGroup4.RateGroupMemberOut[1] -> generic_star_tracker.updateData
      #rateGroup4.RateGroupMemberOut[2] -> generic_mag.updateData
      #rateGroup4.RateGroupMemberOut[3] -> generic_reaction_wheel.updateData
      #rateGroup4.RateGroupMemberOut[4] -> generic_fss.updateData
      #rateGroup4.RateGroupMemberOut[5] -> generic_css.updateData
      #rateGroup4.RateGroupMemberOut[6] -> generic_adcs.updateData
    }

    connections CdhCore_cmdSeq {
      # Command Sequencer
      cmdSeq.comCmdOut -> CdhCore.cmdDisp.seqCmdBuff
      CdhCore.cmdDisp.seqCmdStatus -> cmdSeq.cmdResponseIn
    }

    connections deployment {
      # Add here connections to user-defined components
      generic_imu.IMUout -> generic_adcs.IMUin
      generic_mag.MAGout -> generic_adcs.MAGin
      generic_fss.FSSout -> generic_adcs.FSSin
      generic_css.CSSout -> generic_adcs.CSSin
      generic_reaction_wheel.RWout -> generic_adcs.RWin
      generic_star_tracker.STout -> generic_adcs.STin
      generic_adcs.RWOUTout -> generic_reaction_wheel.RWin
      generic_adcs.TORQout -> generic_torquer.TORQin
    }

  }

}
