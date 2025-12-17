telemetry packets deploymentPackets {

  packet CDH id 1 group 1 {
    CdhCore.cmdDisp.CommandsDispatched

    FileHandling.fileUplink.FilesReceived
    FileHandling.fileUplink.PacketsReceived
    FileHandling.fileDownlink.FilesSent
    FileHandling.fileDownlink.PacketsSent
    FileHandling.fileManager.CommandsExecuted

    deployment.cmdSeq.CS_LoadCommands
    deployment.cmdSeq.CS_CancelCommands
    deployment.cmdSeq.CS_CommandsExecuted
    deployment.cmdSeq.CS_SequencesCompleted
    ComCcsds.comQueue.comQueueDepth
    ComCcsds.comQueue.buffQueueDepth
    ComCcsds.commsBufferManager.TotalBuffs
    ComCcsds.commsBufferManager.CurrBuffs
    ComCcsds.commsBufferManager.HiBuffs
    #ComCcsds.tlmSend.SendLevel

    deployment.rateGroup1.RgMaxTime
    deployment.rateGroup2.RgMaxTime
    deployment.rateGroup3.RgMaxTime
    deployment.rateGroup4.RgMaxTime
  }

  packet CDHErrors id 2 group 1 {
    CdhCore.$health.PingLateWarnings

    FileHandling.fileUplink.Warnings
    FileHandling.fileDownlink.Warnings
    FileHandling.fileManager.Errors

    deployment.cmdSeq.CS_Errors
    ComCcsds.commsBufferManager.NoBuffs
    ComCcsds.commsBufferManager.EmptyBuffs

    deployment.rateGroup1.RgCycleSlips
    deployment.rateGroup2.RgCycleSlips
    deployment.rateGroup3.RgCycleSlips
    deployment.rateGroup4.RgCycleSlips
  }

  packet SystemRes1 id 5 group 2 {
    deployment.systemResources.MEMORY_TOTAL
    deployment.systemResources.MEMORY_USED
    deployment.systemResources.NON_VOLATILE_TOTAL
    deployment.systemResources.NON_VOLATILE_FREE
  }

  packet SystemRes3 id 6 group 2 {
    deployment.systemResources.CPU
    deployment.systemResources.CPU_00
    deployment.systemResources.CPU_01
    deployment.systemResources.CPU_02
    deployment.systemResources.CPU_03
    deployment.systemResources.CPU_04
    deployment.systemResources.CPU_05
    deployment.systemResources.CPU_06
    deployment.systemResources.CPU_07
    deployment.systemResources.CPU_08
    deployment.systemResources.CPU_09
    deployment.systemResources.CPU_10
    deployment.systemResources.CPU_11
    deployment.systemResources.CPU_12
    deployment.systemResources.CPU_13
    deployment.systemResources.CPU_14
    deployment.systemResources.CPU_15
  }

  packet DataProducts id 21 group 3 {
    DataProducts.dpCat.CatalogDps
    DataProducts.dpCat.DpsSent

    DataProducts.dpMgr.NumSuccessfulAllocations
    DataProducts.dpMgr.NumFailedAllocations
    DataProducts.dpMgr.NumDataProducts
    DataProducts.dpMgr.NumBytes

    DataProducts.dpWriter.NumBuffersReceived
    DataProducts.dpWriter.NumBytesWritten
    DataProducts.dpWriter.NumSuccessfulWrites
    DataProducts.dpWriter.NumFailedWrites
    DataProducts.dpWriter.NumErrors

    DataProducts.dpBufferManager.TotalBuffs
    DataProducts.dpBufferManager.CurrBuffs
    DataProducts.dpBufferManager.HiBuffs
    DataProducts.dpBufferManager.NoBuffs
    DataProducts.dpBufferManager.EmptyBuffs
  }

  packet Version1 id 22 group 2 {
    CdhCore.version.FrameworkVersion
    CdhCore.version.ProjectVersion
  }

  packet Version_Library1 id 23 group 2 {
    CdhCore.version.LibraryVersion01
    CdhCore.version.LibraryVersion02
  }

  packet Version_Library2 id 24 group 2 {
    CdhCore.version.LibraryVersion03
    CdhCore.version.LibraryVersion04
  }

  packet Version_Library3 id 25 group 2 {
    CdhCore.version.LibraryVersion05
    CdhCore.version.LibraryVersion06
  }

  packet Version_Library4 id 26 group 2 {
    CdhCore.version.LibraryVersion07
    CdhCore.version.LibraryVersion08
  }

  packet Version_Library5 id 27 group 2 {
    CdhCore.version.LibraryVersion09
    CdhCore.version.LibraryVersion10
  }

  packet Version_Custom1 id 28 group 2 {
    CdhCore.version.CustomVersion01
  }

  packet Version_Custom2 id 29 group 2 {
    CdhCore.version.CustomVersion02
  }

  packet Version_Custom3 id 30 group 2 {
    CdhCore.version.CustomVersion03
  }

  packet Version_Custom4 id 31 group 2 {
    CdhCore.version.CustomVersion04
  }

  packet Version_Custom5 id 32 group 2 {
    CdhCore.version.CustomVersion05
  }

  packet Version_Custom6 id 33 group 2 {
    CdhCore.version.CustomVersion06
  }

  packet Version_Custom7 id 34 group 2 {
    CdhCore.version.CustomVersion07
  }

  packet Version_Custom8 id 35 group 2 {
    CdhCore.version.CustomVersion08
  }

  packet Version_Custom9 id 36 group 2 {
    CdhCore.version.CustomVersion09
  }

  packet Version_Custom10 id 37 group 2 {
    CdhCore.version.CustomVersion10
  }

} omit {
  CdhCore.cmdDisp.CommandErrors

  Components.arducam.CommandCount
  Components.arducam.CommandErrorCount

  Components.generic_css.CommandCount
  Components.generic_css.CommandErrorCount
  Components.generic_css.DeviceCount
  Components.generic_css.DeviceErrorCount
  Components.generic_css.DeviceEnabled
  Components.generic_css.ADCVoltage0
  Components.generic_css.ADCVoltage1
  Components.generic_css.ADCVoltage2
  Components.generic_css.ADCVoltage3
  Components.generic_css.ADCVoltage4
  Components.generic_css.ADCVoltage5

  Components.generic_eps.DeviceCount
  Components.generic_eps.DeviceErrorCount
  Components.generic_eps.CommandErrorCount
  Components.generic_eps.CommandCount
  Components.generic_eps.BatteryVoltage
  Components.generic_eps.BatteryTemperature
  Components.generic_eps.Bus3p3Voltage
  Components.generic_eps.Bus5p0Voltage
  Components.generic_eps.Bus12Voltage
  Components.generic_eps.EPSTemperature
  Components.generic_eps.SolarArrayVoltage
  Components.generic_eps.SolarArrayTemperature
  Components.generic_eps.RawBatteryVoltage
  Components.generic_eps.RawBatteryTemperature
  Components.generic_eps.RawBus3p3V
  Components.generic_eps.RawBus5p0V
  Components.generic_eps.RawBus12V
  Components.generic_eps.RawEPSTemperature
  Components.generic_eps.RawSAVoltage
  Components.generic_eps.RawSATemperature
  Components.generic_eps.SW0Voltage
  Components.generic_eps.SW0Current
  Components.generic_eps.RawSW0Voltage
  Components.generic_eps.RawSW0Current
  Components.generic_eps.SW0State
  Components.generic_eps.SW0Flag
  Components.generic_eps.SW1Voltage
  Components.generic_eps.SW1Current
  Components.generic_eps.RawSW1Voltage
  Components.generic_eps.RawSW1Current
  Components.generic_eps.SW1State
  Components.generic_eps.SW1Flag
  Components.generic_eps.SW2Voltage
  Components.generic_eps.SW2Current
  Components.generic_eps.RawSW2Voltage
  Components.generic_eps.RawSW2Current
  Components.generic_eps.SW2State
  Components.generic_eps.SW2Flag
  Components.generic_eps.SW3Voltage
  Components.generic_eps.SW3Current
  Components.generic_eps.RawSW3Voltage
  Components.generic_eps.RawSW3Current
  Components.generic_eps.SW3State
  Components.generic_eps.SW3Flag
  Components.generic_eps.SW4Voltage
  Components.generic_eps.SW4Current
  Components.generic_eps.RawSW4Voltage
  Components.generic_eps.RawSW4Current
  Components.generic_eps.SW4State
  Components.generic_eps.SW4Flag
  Components.generic_eps.SW5Voltage
  Components.generic_eps.SW5Current
  Components.generic_eps.RawSW5Voltage
  Components.generic_eps.RawSW5Current
  Components.generic_eps.SW5State
  Components.generic_eps.SW5Flag
  Components.generic_eps.SW6Voltage
  Components.generic_eps.SW6Current
  Components.generic_eps.RawSW6Voltage
  Components.generic_eps.RawSW6Current
  Components.generic_eps.SW6State
  Components.generic_eps.SW6Flag
  Components.generic_eps.SW7Voltage
  Components.generic_eps.SW7Current
  Components.generic_eps.RawSW7Voltage
  Components.generic_eps.RawSW7Current
  Components.generic_eps.SW7State
  Components.generic_eps.SW7Flag

  Components.generic_fss.CommandCount
  Components.generic_fss.CommandErrorCount
  Components.generic_fss.DeviceCount
  Components.generic_fss.DeviceErrorCount
  Components.generic_fss.DeviceEnabled
  Components.generic_fss.ALPHA
  Components.generic_fss.BETA
  Components.generic_fss.ERRORCODE

  Components.generic_imu.CommandCount
  Components.generic_imu.CommandErrorCount
  Components.generic_imu.DeviceCount
  Components.generic_imu.DeviceErrorCount
  Components.generic_imu.DeviceEnabled
  Components.generic_imu.ReportedComponentCount
  Components.generic_imu.DeviceStatus
  Components.generic_imu.X_Axis_LinearAcc
  Components.generic_imu.X_Axis_AngularAcc
  Components.generic_imu.Y_Axis_LinearAcc
  Components.generic_imu.Y_Axis_AngularAcc
  Components.generic_imu.Z_Axis_LinearAcc
  Components.generic_imu.Z_Axis_AngularAcc

  Components.generic_mag.CommandCount
  Components.generic_mag.CommandErrorCount
  Components.generic_mag.DeviceCount
  Components.generic_mag.DeviceErrorCount
  Components.generic_mag.DeviceEnabled
  Components.generic_mag.MagneticIntensityX
  Components.generic_mag.MagneticIntensityY
  Components.generic_mag.MagneticIntensityZ

  Components.generic_radio.CommandCount
  Components.generic_radio.CommandErrorCount
  Components.generic_radio.DeviceCount
  Components.generic_radio.DeviceErrorCount
  Components.generic_radio.ReportedComponentCount
  Components.generic_radio.DeviceConfig
  Components.generic_radio.ProxySignal

  Components.generic_reaction_wheel.CommandCount
  Components.generic_reaction_wheel.CommandErrorCount
  Components.generic_reaction_wheel.DeviceCountRW0
  Components.generic_reaction_wheel.DeviceErrorCountRW0
  Components.generic_reaction_wheel.DeviceEnabledRW0
  Components.generic_reaction_wheel.RW0_Data
  Components.generic_reaction_wheel.DeviceCountRW1
  Components.generic_reaction_wheel.DeviceErrorCountRW1
  Components.generic_reaction_wheel.DeviceEnabledRW1
  Components.generic_reaction_wheel.RW1_Data
  Components.generic_reaction_wheel.DeviceCountRW2
  Components.generic_reaction_wheel.DeviceErrorCountRW2
  Components.generic_reaction_wheel.DeviceEnabledRW2
  Components.generic_reaction_wheel.RW2_Data

  Components.generic_star_tracker.ReportedComponentCount
  Components.generic_star_tracker.CommandCount
  Components.generic_star_tracker.CommandErrorCount
  Components.generic_star_tracker.DeviceCount
  Components.generic_star_tracker.DeviceErrorCount
  Components.generic_star_tracker.DeviceEnabled
  Components.generic_star_tracker.Q0_Data
  Components.generic_star_tracker.Q1_Data
  Components.generic_star_tracker.Q2_Data
  Components.generic_star_tracker.Q3_Data
  Components.generic_star_tracker.IsValid

  Components.generic_thruster.CommandCount
  Components.generic_thruster.CommandErrorCount
  Components.generic_thruster.DeviceCount
  Components.generic_thruster.DeviceErrorCount
  Components.generic_thruster.DeviceEnabled
  Components.generic_thruster.Percentage_0
  Components.generic_thruster.Percentage_1
  Components.generic_thruster.Percentage_2
  Components.generic_thruster.Percentage_3

  Components.generic_torquer.DeviceCount
  Components.generic_torquer.DeviceErrorCount
  Components.generic_torquer.CommandErrorCount
  Components.generic_torquer.CommandCount
  Components.generic_torquer.DeviceEnabled
  Components.generic_torquer.Direction_0
  Components.generic_torquer.Percent_0
  Components.generic_torquer.Direction_1
  Components.generic_torquer.Percent_1
  Components.generic_torquer.Direction_2
  Components.generic_torquer.Percent_2

  Components.generic_adcs.ingestIMUCount
  Components.generic_adcs.ingestMagCount
  Components.generic_adcs.ingestFSSCount
  Components.generic_adcs.ingestCSSCount
  Components.generic_adcs.ingestRWCount
  Components.generic_adcs.ingestSTCount
  Components.generic_adcs.ingestBDOT
  Components.generic_adcs.ingestSUNSAFE
  Components.generic_adcs.ingestPASSIVE
  Components.generic_adcs.ADCSMode
  Components.generic_adcs.INERTIALQUATERNIONX
  Components.generic_adcs.INERTIALQUATERNIONY
  Components.generic_adcs.INERTIALQUATERNIONZ
  Components.generic_adcs.INERTIALQUATERNIONW
  Components.generic_adcs.CommandCount
  Components.generic_adcs.CommandErrorCount
  Components.generic_adcs.ADCSMomentumManagement

  Components.sampleSim.ReportedComponentCount
  Components.sampleSim.DeviceConfig
  Components.sampleSim.DeviceStatus
  Components.sampleSim.DeviceCount
  Components.sampleSim.DeviceErrorCount
  Components.sampleSim.CommandCount
  Components.sampleSim.CommandErrorCount
  Components.sampleSim.DeviceEnabled

  Components.novatel_oem615.Weeks
  Components.novatel_oem615.SecondsIntoWeek
  Components.novatel_oem615.Fractions
  Components.novatel_oem615.ECEFX
  Components.novatel_oem615.ECEFY
  Components.novatel_oem615.ECEFZ
  Components.novatel_oem615.VelX
  Components.novatel_oem615.VelY
  Components.novatel_oem615.VelZ
  Components.novatel_oem615.lat
  Components.novatel_oem615.lon
  Components.novatel_oem615.alt

}
