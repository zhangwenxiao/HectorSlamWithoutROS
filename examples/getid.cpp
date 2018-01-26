/* HokuyoAIST
 *
 * Utility to print a sensor's ID, by Luiz Mirisola.
 *
 * Copyright 2008-2011 Geoffrey Biggs geoffrey.biggs@aist.go.jp
 *     RT-Synthesis Research Group
 *     Intelligent Systems Research Institute,
 *     National Institute of Advanced Industrial Science and Technology (AIST),
 *     Japan
 *     All rights reserved.
 *
 * This file is part of HokuyoAIST.
 *
 * HokuyoAIST is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * HokuyoAIST is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with HokuyoAIST. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cmath>
#include <hokuyoaist/hokuyoaist.h>
#include <hokuyoaist/hokuyo_errors.h>
#include <iostream>
#include <unistd.h>


int main(int argc, char **argv)
{
    std::string port_options="type=serial,device=/dev/ttyACM0,timeout=1";
    bool verbose=false;

#if defined (WIN32)
    port_options = "type=serial,device=COM3,timeout=1";
#else
    int opt;
    // Get some options from the command line
    while((opt = getopt(argc, argv, "b:c:e:f:il:m:no:s:vh")) != -1)
    {
        switch(opt)
        {
            case 'o':
                port_options = optarg;
                break;
            case 'v':
                verbose = true;
                break;
            case '?':
            case 'h':
            default:
                std::cout << "Usage: " << argv[0] << " [options]\n\n";
                std::cout <<
                    "-o options\tPort options (see flexiport library).\n";
                std::cout <<
                    "-v\t\tPut the hokuyoaist library into verbose mode.\n";
                return 1;
        }
    }
#endif // defined (WIN32)

    try
    {
        hokuyoaist::Sensor laser; // Laser scanner object
        // Set the laser to verbose mode (so we see more information in the
        // console)
        if(verbose)
        {
            laser.set_verbose(true);
        }

        // Open the laser
        laser.open(port_options);
        // Turn the laser on
        laser.set_power(true);

        // Get some laser info
        hokuyoaist::SensorInfo info;
        laser.get_sensor_info(info);
        std::cout << info.serial << '\n';

        // Close the laser
        laser.close();
    }
    catch(hokuyoaist::BaseError &e)
    {
        std::cerr << "Caught exception: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

