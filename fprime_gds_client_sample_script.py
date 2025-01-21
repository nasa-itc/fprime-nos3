""" Print each instance of a given channel by name

A sample script showing GDS scripting usage. This script sets up an argument of channel-name, a data handler that
receives channels and filters to that channel-name then printing it.  Running will yield a print-out for each time the
channel is received. e.g.

2023-07-19 18:59:20: blockDrv.BD_Cycles = 1275
2023-07-19 18:59:22: blockDrv.BD_Cycles = 1277
2023-07-19 18:59:24: blockDrv.BD_Cycles = 1279
2023-07-19 18:59:26: blockDrv.BD_Cycles = 1281
2023-07-19 18:59:28: blockDrv.BD_Cycles = 1283

This script is designed to connect to the GDS system using standard GDS arguments. It is a GDS client.

@author lestarch
"""
import sys
from typing import Any, Dict, Tuple

from fprime_gds.executables.cli import ParserBase, StandardPipelineParser  # Import CLI helpers
from fprime_gds.common.handlers import DataHandler  # Import data handler


class SpecificChannel(DataHandler):
    """ Handel a specific channel by name

    A DataHandler must define at least one function with the following type. A data handler can then be registered as a
    consumer of a specific set of data within the standard pipeline. e.g. this data handler will be registered as a
    channel consumer. Each channel received by the GDS will invoke a call to the supplied `data_callback` function.

    Required Function Definition:
    ```py
    def data_callback(data, sender=None):
    ```

    This "SpecificChannel" handler filters channels received to a channels matching a specific ID. Each time this
    channel is received, it will be printed to the terminal.
    """

    def __init__(self, channels_by_name, name):
        """ Initialize the handler with a dictionary and name

        This function will use the channels_by_name dictionary and the name to look up the channel dictionary entry by
        name. This entry provides the ID to be filtered by.

        Note: channel data objects include the name, however; using the ID allows us to demo dictionary look ups.

        Args:
            channels_by_name: python dictionary of channel name to fprime ChannelTemplate dictionary entries
            name: string of channel name
        """
        self.id = channels_by_name[name].id

    def data_callback(self, data, sender=None):
        """ Handle a given data item

        This function is called on every channel received by the GDS. In this specific case, the ID of the incoming
        channel is checked against the supplied ID. If the ID matches, the channel is printed.
        """
        print(data)
        # if data.id == self.id:
        #     print(data)


class ChannelNameParser(ParserBase):
    """  GDS style argument parser used to add an argument specifically for this script

    GDS parsers define two methods. `get_arguments` that returns a dictionary of flag tuples to a dictionary of key word
    arguments provided to argparse. The tuple (keys) are the "arg values" supplied to `argparse.Parser.add_argument()`
    and the value of the is the "kwargs" supplied.

    `handle_arguments` takes in `args` and keyword arguments. This function allows users to validate, update, and derive
    from the arguments received.
    """

    def get_arguments(self) -> Dict[Tuple[str, ...], Dict[str, Any]]:
        """ Get the arguments to add into the parser system

        Specifically add a channel-name argument driven from --channel-name.

        Return:
            tuple of flags to argparse key word arguments
        """
        return {
            ("--channel-name",): {
                "dest": "channel_name",
                "help": "Name of channel to filter on",
                "required": False
            }
        }

    def handle_arguments(self, args, **kwargs):
        """ Do no special argument processing

        Handle arguments can be used to process arguments for later user (e.g. derive special arguments, validate
        arguments passed in, etc). Users should ensure to pass out an argument namespace that is, or is a modified copy
        of, the supplied args.

        Args:
            args: namespace containing arguments passed in. Must be returned, or copied then modified, then returned.
            **kwargs: key-word arguments passed in to allow local adjustment. unused.
        """
        return args


def main():
    """ Parse CLI arguments, connect to GDS, and register example handler """
    
    try:
        # Parse command line arguments using two parsers "StandardPipelineParser", and "ChannelNameParser"
        arguments, _ = ParserBase.parse_args([StandardPipelineParser, ChannelNameParser],
                                             description="An example channel handling script",
                                             client=True,  # This is a client script, thus client=True must be specified
                                             )
        # Use the StandardPipelineParser to build a pipeline from the arguments parsed above
        # pipeline = StandardPipelineParser.pipeline_factory(args_ns=arguments)
        pipeline = StandardPipelineParser.pipeline_factory(args_ns=arguments)
        # http://192.168.80.3:5000/

        # Initialize the SpecificChannel data handler with the pipeline's loaded "channel_name" dictionary and the
        # channel_name argument parsed on the command line
        channel_handler = SpecificChannel(pipeline.dictionaries.channel_name, arguments.channel_name)

        # Register the channel_handler as a channel consumer
        pipeline.coders.register_channel_consumer(channel_handler)
        # Run until CTRL-C shutdown
        while True:
            pass
    except KeyboardInterrupt:
        # Ignore Keyboard interrupt (CTRL-C) as this is a normal shutdown
        pass
    except KeyError as key:
        # Get the keys of the channel_name dictionary and use it to print a verbose error message
        choose_from = "\n\t".join(pipeline.dictionaries.channel_name.keys())
        print(f"[ERROR] Unknown channel name: {key}\n\t{choose_from}", file=sys.stderr)
    except Exception as exc:
        # Capture errors and print a nice message
        print(f"[ERROR] Failed to run example code: {exc}", file=sys.stderr)
    pipeline.disconnect()


if __name__ == "__main__":
    main()
