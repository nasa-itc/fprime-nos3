module Components {
    @ generic_imu
    active component Generic_imu {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ TODO

        @ Command to Request Housekeeping
        async command REQUEST_HOUSEKEEPING(
        )

        @ Command to Request Data
        async command REQUEST_DATA(
        )

        @ NOOP Command
        async command NOOP(
        )

        @ event with maximum length of 30 characters
        event TELEM(
            log_info: string size 30 @< 
        ) severity activity high format "Generic_imu: {}"

         @ Device Command Counter Parameter 
        telemetry DeviceCounter: U32

         @ Device Status Parameter
        telemetry DeviceStatus: U32

         @ X Axis Linear Acceleration
        telemetry X_Axis_LinearAcc: F32

         @ X Axis Angular Acceleration
        telemetry X_Axis_AngularAcc: F32

         @ Y Axis Linear Acceleration
        telemetry Y_Axis_LinearAcc: F32

         @ Y Axis Angular Acceleration
        telemetry Y_Axis_AngularAcc: F32

         @ Z Axis Linear Acceleration
        telemetry Z_Axis_LinearAcc: F32

         @ Z Axis Angular Acceleration
        telemetry Z_Axis_AngularAcc: F32

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