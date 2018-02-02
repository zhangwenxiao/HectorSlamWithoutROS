#!/usr/bin/env python

from __future__ import print_function

import argparse
import hokuyoaist


def main():
    parser = argparse.ArgumentParser(
        description="HokuyoAIST Python bindings demo")
    parser.add_argument(
        '-c',
        '--cluster-count',
        type=int,
        default='1',
        help='Cluster count [default: %(default)s]')
    parser.add_argument(
        '-e',
        '--end-angle',
        type=float,
        default='0',
        help='End angle to get ranges to [default: %(default)s]')
    parser.add_argument(
        '-f',
        '--first-step',
        type=int,
        default='-1',
        help='First step to get ranges from [default: %(default)s]')
    parser.add_argument(
        '-l',
        '--last-step',
        type=int,
        default='-1',
        help='Last step to get ranges to [default: %(default)s]')
    parser.add_argument(
        '-n',
        '--get-new',
        action='store_true',
        default='False',
        help='Get new ranges instead of latest ranges [default: %(default)s]')
    parser.add_argument(
        '-o',
        '--port-options',
        type=str,
        default='type=serial,device=/dev/ttyACM0,timeout=1',
        help='Port options (see flexiport library) [default: %(default)s]')
    parser.add_argument(
        '-s',
        '--start-angle',
        type=float,
        default='0',
        help='Start angle to get ranges from [default: %(default)s]')
    parser.add_argument(
        '-v',
        '--verbose',
        action='store_true',
        default='False',
        help='Put the hokuyoaist library into verbose mode [Default: %(default)s]')

    # Scan command line arguments
    args = parser.parse_args()

    try:
        # Create an instance of a laser scanner object
        laser = hokuyoaist.Sensor()
        if args.verbose:
            # Set verbose mode so we see more information in stderr
            laser.set_verbose(True)

        # Open the laser
        laser.open(args.port_options)
        # Turn the laser on
        laser.set_power(True)

        # Get some laser info
        # print('Laser sensor information:')
        # info = hokuyoaist.SensorInfo info()
        # laser.get_sensor_info(info)
        # print(info.as_string())

        # Get range data
        data = hokuyoaist.ScanData()
        if ((args.first_step == -1 and args.last_step == -1) and
                (args.start_angle == 0 and args.end_angle == 0)):
            # Get all ranges
            if args.get_new:
                laser.get_new_ranges(data, -1, -1, args.cluster_count)
            else:
                laser.get_ranges(data, -1, -1, args.cluster_count)
        elif args.first_step != -1 or args.last_step != -1:
            # Get by step
            if args.get_new:
                laser.get_new_ranges(data, args.first_step, args.last_step, args.cluster_count)
            else:
                laser.get_ranges(data, args.first_step, args.last_step, args.cluster_count)
        else:
            # Get by angle
            if args.get_new:
                laser.get_new_ranges_by_angle(
                    data,
                    args.start_angle,
                    args.end_angle,
                    args.cluster_count)
            else:
                laser.get_ranges_by_angle(
                    data,
                    args.start_angle,
                    args.end_angle,
                    args.cluster_count)

        print('Laser range data:', data.as_string())

        # Close the laser
        laser.close()

    except hokuyoaist.BaseError as e:
        print('Caught exception:', e.what())
        return 1
    return 0


if __name__ == '__main__':
    main()
