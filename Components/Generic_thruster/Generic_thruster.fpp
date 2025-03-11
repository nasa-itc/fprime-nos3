module Components {
    @ Satellite Thruster
    active component Generic_thruster {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        #@ TODO
        #async command TODO opcode 0

        @ Command to issue greeting with maximum length of 20 characters
        async command SetPercentage(
            percent: string size 20 @< Percent speed of rotation
            thruster_number: string size 20 @< Direction of rotation
        )

        @ Greeting event with maximum greeting length of 20 characters
        event Hello(
            percent: string size 20 @< Greeting supplied from the GENERIC_TORQUER_CONFIG command
            thruster_number:  string size 20 @< Greeting supplied from the GENERIC_TORQUER_CONFIG command
        ) severity activity high format "I say: {} {}"

        @ Greeting event with maximum greeting length of 30 characters
        event TELEM(
            log_info: string size 30 @< 
        ) severity activity high format "Generic_thruster: {}"

        @ A count of the number of greetings issued
        telemetry GreetingCount: U32

        @ A count of the number of greetings issued
        telemetry thruster_number: U8

        @ A count of the number of greetings issued
        telemetry percentage: U8

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