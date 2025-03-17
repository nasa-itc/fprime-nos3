module Components {
    @ generic_css
    active component Generic_css {
        
        @ Command to Request Data
        async command REQUEST_DATA()

        @ event with maximum greeting length of 30 characters
        event TELEM(
            log_info: string size 30 @<
        ) severity activity high format "Generic_css: {}"

        @ A count of the number of greetings issues
        telemetry ADCVoltage0: U16

        @ A count of the number of greetings issues
        telemetry ADCVoltage1: U16

        @ A count of the number of greetings issues
        telemetry ADCVoltage2: U16

        @ A count of the number of greetings issues
        telemetry ADCVoltage3: U16

        @ A count of the number of greetings issues
        telemetry ADCVoltage4: U16

        @ A count of the number of greetings issues
        telemetry ADCVoltage5: U16

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