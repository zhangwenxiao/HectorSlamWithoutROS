/* Flexiport
 *
 * Factory function implementations.
 *
 * Copyright 2008-2011 Geoffrey Biggs geoffrey.biggs@aist.go.jp
 *     RT-Synthesis Research Group
 *     Intelligent Systems Research Institute,
 *     National Institute of Advanced Industrial Science and Technology (AIST),
 *     Japan
 *     All rights reserved.
 *
 * This file is part of Flexiport.
 *
 * Flexiport is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * Flexiport is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Flexiport. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <flexiport/flexiport.h>
#include <flexiport/port.h>
#include <flexiport/serialport.h>
#include <flexiport/tcpport.h>
#include <flexiport/udpport.h>
#include <flexiport/rfcommport.h>
#include <flexiport/logwriterport.h>
#include <flexiport/logreaderport.h>
#include <flexiport/config.h>

#include <errno.h>
#include <iostream>
#include <sstream>
using namespace std;

namespace flexiport
{

///////////////////////////////////////////////////////////////////////////////
// Central factory function
///////////////////////////////////////////////////////////////////////////////

Port* CreatePort (string options)
{
    const char* separators = ", \t\n";
    map<string, string> optionsMap;

    string::size_type pos = 0;
    // Find the start of the first option (skip delimeters at the beginning)
    string::size_type lastPos = options.find_first_not_of (separators, 0);
    // Check first that we did actually get something in the string
    if (lastPos == string::npos)
    {
        // No options. Go boom.
        throw PortException ("No options specified. Must specify a port type.");
    }

    do
    {
        pos = options.find_first_of (separators, lastPos);

        // Got an option, one way or the other
        string option = options.substr (lastPos, pos - lastPos);

        string::size_type splitPos = option.find ('=');
        if (splitPos != string::npos)
        {
            // Need to split this token
            optionsMap[option.substr (0, splitPos)] =
                    option.substr (splitPos + 1, option.length () - splitPos - 1);
        }
        else
        {
            // Boolean option
            optionsMap[option] = "1";
        }

        // Bring lastPos forward to the start of the next option (not just current pos)
        lastPos = options.find_first_not_of (separators, pos);
    }
    while (lastPos != string::npos && pos != string::npos);

    // Now that the options are in a map, call the standard CreatePort function
    return CreatePort (optionsMap);
}

Port* CreatePort (map<string, string> options)
{
    // Look for a type option
    string type;
    if (options.count ("type") == 0)
        throw PortException ("No port type specified.");
    else if (options.count ("type") != 1)
        throw PortException ("Multiple port types specified.");
    else
        type = options["type"];
    options.erase ("type");

#ifdef FLEXIPORT_INCLUDE_SERIAL
    if (type == "serial")
        return new SerialPort (options);
#endif // FLEXIPORT_INCLUDE_SERIAL
#ifdef FLEXIPORT_INCLUDE_TCP
    if (type == "tcp")
        return new TCPPort (options);
#endif // FLEXIPORT_INCLUDE_TCP
#ifdef FLEXIPORT_INCLUDE_UDP
    if (type == "udp")
        return new UDPPort (options);
#endif // FLEXIPORT_INCLUDE_UDP
#ifdef FLEXIPORT_INCLUDE_BT
    if (type == "rfcomm")
        return new RFCOMMPort(options);
#endif // FLEXIPORT_INCLUDE_BT

#ifdef FLEXIPORT_INCLUDE_LOGGING
    if (type == "logreader")
        return new LogReaderPort (options);
    #ifdef FLEXIPORT_INCLUDE_SERIAL
        if (type == "seriallog")
        {
            options["type"] = "serial";
            return new LogWriterPort (options);
        }
    #endif // FLEXIPORT_INCLUDE_SERIAL
    #ifdef FLEXIPORT_INCLUDE_TCP
        if (type == "tcplog")
        {
            options["type"] = "tcp";
            return new LogWriterPort (options);
        }
    #endif // FLEXIPORT_INCLUDE_TCP
#endif // FLEXIPORT_INCLUDE_LOGGING

    // If got to here, it's an unsupported port type
    stringstream ss;
    ss << "Unsupported port type: " << type;
    throw PortException (ss.str ());
}

}; // namespace flexiport

