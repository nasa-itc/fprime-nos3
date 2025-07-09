module SampleSimDeployment {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

    enum Ports_RateGroups {
      rateGroup1
      rateGroup2
      rateGroup3
      rateGroup4
    }

  topology SampleSimDeployment {

    # ----------------------------------------------------------------------
    # Instances used in the topology
    # ----------------------------------------------------------------------

    instance $health
    instance blockDrv
    instance tlmSend
    instance cmdDisp
    instance cmdSeq
    instance comDriver
    instance comQueue
    instance comStub
    instance deframer
    instance eventLogger
    instance fatalAdapter
    instance fatalHandler
    instance fileDownlink
    instance fileManager
    instance fileUplink
    instance bufferManager
    instance framer
    instance prmDb
    instance rateGroup1
    instance rateGroup2
    instance rateGroup3
    instance rateGroup4
    instance rateGroupDriver
    instance textLogger
    instance systemResources
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
    instance generic_adcs
    # ----------------------------------------------------------------------
    # Pattern graph specifiers
    # ----------------------------------------------------------------------

    command connections instance cmdDisp

    event connections instance eventLogger

    param connections instance prmDb

    telemetry connections instance tlmSend

    text event connections instance textLogger

    time connections instance nos3Time

    health connections instance $health

    # ----------------------------------------------------------------------
    # Direct graph specifiers
    # ----------------------------------------------------------------------

    connections Downlink {

      eventLogger.PktSend -> comQueue.comQueueIn[0]
      tlmSend.PktSend -> comQueue.comQueueIn[1]
      fileDownlink.bufferSendOut -> comQueue.buffQueueIn[0]

      comQueue.comQueueSend -> framer.comIn
      comQueue.buffQueueSend -> framer.bufferIn

      framer.framedAllocate -> bufferManager.bufferGetCallee
      framer.framedOut -> comStub.comDataIn
      framer.bufferDeallocate -> fileDownlink.bufferReturn

      comDriver.deallocate -> bufferManager.bufferSendIn
      comDriver.ready -> comStub.drvConnected

      comStub.comStatus -> framer.comStatusIn
      framer.comStatusOut -> comQueue.comStatusIn
      comStub.drvDataOut -> comDriver.$send

    }

    connections FaultProtection {
      eventLogger.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections RateGroups {
      # Block driver
      blockDrv.CycleOut -> rateGroupDriver.CycleIn

      # Rate group 1
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      rateGroup1.RateGroupMemberOut[0] -> tlmSend.Run
      rateGroup1.RateGroupMemberOut[1] -> fileDownlink.Run
      rateGroup1.RateGroupMemberOut[2] -> systemResources.run
      rateGroup1.RateGroupMemberOut[3] -> generic_imu.updateTlm
      rateGroup1.RateGroupMemberOut[4] -> generic_star_tracker.updateTlm
      rateGroup1.RateGroupMemberOut[5] -> generic_mag.updateTlm
      rateGroup1.RateGroupMemberOut[6] -> generic_reaction_wheel.updateTlm
      rateGroup1.RateGroupMemberOut[7] -> generic_fss.updateTlm
      rateGroup1.RateGroupMemberOut[8] -> generic_css.updateTlm
      rateGroup1.RateGroupMemberOut[9] -> generic_torquer.updateTlm

      # Rate group 2
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup2] -> rateGroup2.CycleIn
      rateGroup2.RateGroupMemberOut[0] -> cmdSeq.schedIn

      # Rate group 3
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup3] -> rateGroup3.CycleIn
      rateGroup3.RateGroupMemberOut[0] -> $health.Run
      rateGroup3.RateGroupMemberOut[1] -> blockDrv.Sched
      rateGroup3.RateGroupMemberOut[2] -> bufferManager.schedIn

      # Rate group 4
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup4] -> rateGroup4.CycleIn
      rateGroup4.RateGroupMemberOut[0] -> generic_imu.updateData
      rateGroup4.RateGroupMemberOut[1] -> generic_star_tracker.updateData
      rateGroup4.RateGroupMemberOut[2] -> generic_mag.updateData
      rateGroup4.RateGroupMemberOut[3] -> generic_reaction_wheel.updateData
      rateGroup4.RateGroupMemberOut[4] -> generic_fss.updateData
      rateGroup4.RateGroupMemberOut[5] -> generic_css.updateData
      rateGroup4.RateGroupMemberOut[6] -> generic_adcs.updateData

    }

    connections Sequencer {
      cmdSeq.comCmdOut -> cmdDisp.seqCmdBuff
      cmdDisp.seqCmdStatus -> cmdSeq.cmdResponseIn
    }

    connections Uplink {

      comDriver.allocate -> bufferManager.bufferGetCallee
      comDriver.$recv -> comStub.drvDataIn
      comStub.comDataOut -> deframer.framedIn

      deframer.framedDeallocate -> bufferManager.bufferSendIn
      deframer.comOut -> cmdDisp.seqCmdBuff

      cmdDisp.seqCmdStatus -> deframer.cmdResponseIn

      deframer.bufferAllocate -> bufferManager.bufferGetCallee
      deframer.bufferOut -> fileUplink.bufferSendIn
      deframer.bufferDeallocate -> bufferManager.bufferSendIn
      fileUplink.bufferSendOut -> bufferManager.bufferSendIn
    }

    connections SampleSimDeployment {
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
