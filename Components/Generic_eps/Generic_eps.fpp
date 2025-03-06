module Components {
    @ generic_eps
    active component Generic_eps {

        @ Command to Request Housekeeping
        async command REQUEST_HOUSEKEEPING(
        )

        @ Greeting event with maximum greeting length of 30 characters
        event TELEM(
            log_info: string size 30 @< 
        ) severity activity high format "Generic_eps: {}"

         @ Battery Voltage Parameter
        telemetry BatteryVoltage: U16

         @ Battery Temperature Parameter
        telemetry BatteryTemperature: U16

         @ Bus 3p3 Voltage Parameter
        telemetry Bus3p3Voltage: U16

         @ Bus 5p0 Voltage Parameter
        telemetry Bus5p0Voltage: U16

         @ Bus 12 Voltage Parameter
        telemetry Bus12Voltage: U16

         @ EPS Temperature Parameter
        telemetry EPSTemperature: U16

         @ Solar Array Voltage Parameter
        telemetry SolarArrayVoltage: U16

         @ Solar Array Temperature Parameter
        telemetry SolarArrayTemperature: U16

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