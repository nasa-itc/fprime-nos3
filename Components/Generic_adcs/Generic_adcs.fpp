module Components {
    @ adcs
    active component Generic_adcs {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port

        @ IMU Data input
        async input port IMUin: IMUDataPort

        @ Mag Data input
        async input port MAGin: MagDataPort

        @ FSS Data input
        async input port FSSin: FSSDataPort

        @ CSS Data input
        async input port CSSin: CSSDataPort

        @ RW Data input
        async input port RWin: RWDataPort

        @ ST Data input
        async input port STin: STDataPort

        @ Update Control and Cmd Outputs
        async input port updateData: Svc.Sched

        @ Cmd Torquer
        output port TORQout: TORQDataPort

        @ Cmd RW
        output port RWOUTout: RWOUTDataPort

        @ Counter for keeping track of IMU updating
        telemetry ingestIMUCount: U32

        @ Counter for keeping track of Mag updating
        telemetry ingestMagCount: U32

        @ Counter for keeping track of FSS updating
        telemetry ingestFSSCount: U32

        @ Counter for keeping track of CSS updating
        telemetry ingestCSSCount: U32

        @ Counter for keeping track of RW updating
        telemetry ingestRWCount: U32

        @ Counter for keeping track of ST updating
        telemetry ingestSTCount: U32


        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}