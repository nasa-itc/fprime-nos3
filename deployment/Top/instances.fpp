module deployment {

  # ----------------------------------------------------------------------
  # Base ID Convention
  # ----------------------------------------------------------------------
  #
  # All Base IDs follow the 8-digit hex format: 0xDSSCCxxx
  #
  # Where:
  #   D   = Deployment digit (1 for this deployment)
  #   SS  = Subtopology digits (00 for main topology, 01-05 for subtopologies)
  #   CC  = Component digits (00, 01, 02, etc.)
  #   xxx = Reserved for internal component items (events, commands, telemetry)
  #

  # ----------------------------------------------------------------------
  # Defaults
  # ----------------------------------------------------------------------

  module Default {
    constant QUEUE_SIZE = 100
    constant STACK_SIZE = 64 * 1024
    constant QUEUE_SIZE_BIG = 20000
  }

  # ----------------------------------------------------------------------
  # Active component instances
  # ----------------------------------------------------------------------

  instance rateGroup1: Svc.ActiveRateGroup base id 0x10001000 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 95

  instance rateGroup2: Svc.ActiveRateGroup base id 0x10002000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 90

  instance rateGroup3: Svc.ActiveRateGroup base id 0x10003000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 90
  
  instance rateGroup4: Svc.ActiveRateGroup base id 0xEB00 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 90

  instance cmdSeq: Svc.CmdSequencer base id 0x10004000 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 20

   instance sampleSim: Components.SampleSim base id 0x0F00 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_mag: Components.Generic_mag base id 0xEF00 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_star_tracker: Components.Generic_star_tracker base id 0xE000 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_radio: Components.Generic_radio base id 0xE100 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 50
    
  instance generic_css: Components.Generic_css base id 0xE300 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50
    
  instance generic_eps: Components.Generic_eps base id 0xE200 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance arducam: Components.Arducam base id 0xF900 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_thruster: Components.Generic_thruster base id 0xE500 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_fss: Components.Generic_fss base id 0xE400 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_imu: Components.Generic_imu base id 0xE600 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_reaction_wheel: Components.Generic_reaction_wheel base id 0xE700 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance novatel_oem615: Components.novatel_oem615 base id 0xE800 \
    queue size Default.QUEUE_SIZE \
    stack size Default.STACK_SIZE \
    priority 50
    
  instance generic_torquer: Components.Generic_torquer base id 0xE900 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 50

  instance generic_adcs: Components.Generic_adcs base id 0xEA00 \
    queue size Default.QUEUE_SIZE_BIG \
    stack size Default.STACK_SIZE \
    priority 45

  # ----------------------------------------------------------------------
  # Queued component instances
  # ----------------------------------------------------------------------


  # ----------------------------------------------------------------------
  # Passive component instances
  # ----------------------------------------------------------------------

  #instance chronoTime: Svc.ChronoTime base id 0x10010000
  instance nos3Time: Components.Nos3Time base id 0x4500

  instance rateGroupDriver: Svc.RateGroupDriver base id 0x10011000

  instance systemResources: Svc.SystemResources base id 0x10012000

  instance timer: Svc.LinuxTimer base id 0x10013000
  instance comDriver: Drv.TcpClient base id 0x10014000

}
