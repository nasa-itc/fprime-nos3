module Components {
    @ fine sun sensor component from NOS3
    active component Generic_fss {

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        @ Command to request data
        async command REQUEST_DATA(
        )

        @ Telemetry event
        event TELEM(
            log_info: string size 30
        ) severity activity high format "Generic_fss: {}"

        @ Angle alpha
        telemetry ALPHA: U32

        @ Angle beta
        telemetry BETA: U32

        @ errorcode
        telemetry ERRORCODE: U8



        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

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
