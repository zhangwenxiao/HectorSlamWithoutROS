/* Flexiport
 *
 * Header file for the Bluetooth rfcomm port class.
 *
 * Copyright 2016 Rich Mattes richmattes@gmail.com
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

#ifndef __RFCOMMPORT_H
#define __RFCOMMPORT_H

#include <flexiport/port.h>

#include <map>
#include <string>

/** @ingroup library_flexiport
@{
*/

namespace flexiport
{

/** @brief Bluetooth rfcomm implementation of the @ref Port class.

Connects to Bluetooth devices using the RFCOMM protocol.
Uses the bluez library for bluetooth support.
See the @ref Port class documentation for how to use the common API.

@par Options
 - deviceid \<string\>
   - Bluetooth device ID to connect to.
   - Default: 00:00:00:00:00:00
 - port \<integer\>
   - Bluetooth channel to listen on
   - Default: 1
 - listen
   - Listen on the specified port rather than connecting to it. Other
     network applications can connect and send data, which will become
     available as normal.
   - Default: off */
class FLEXIPORT_EXPORT RFCOMMPort : public Port
{
    public:
        RFCOMMPort (std::map<std::string, std::string> options);
        ~RFCOMMPort ();

        /** @brief Open the port.

        For a listening port, this will call accept() and therefore
        cause the calling process to block until an incoming connection.
        */
        void Open ();
        /// @brief Close the port.
        void Close ();
        /// @brief Read from the port.
        ssize_t Read (void * const buffer, size_t count);
        /// @brief Read the requested quantity of data from the port.
        ssize_t ReadFull (void * const buffer, size_t count);
        /// @brief Get the number of bytes waiting to be read at the port. Returns immediatly.
        ssize_t BytesAvailable ();
        /// @brief Get the number of bytes waiting after blocking for the timeout.
        ssize_t BytesAvailableWait ();
        /// @brief Write data to the port.
        ssize_t Write (const void * const buffer, size_t count);
        /// @brief Flush the port's input and output buffers, discarding all data.
        void Flush ();
        /// @brief Drain the port's input and output buffers.
        void Drain ();
        /// @brief Get the status of the port (type, device, etc).
        std::string GetStatus () const;
        /// @brief Set the timeout value in milliseconds.
        void SetTimeout (Timeout timeout);
        /// @brief Set the read permissions of the port.
        void SetCanRead (bool canRead);
        /// @brief Set the write permissions of the port.
        void SetCanWrite (bool canWrite);
        /// @brief Check if the port is open
        bool IsOpen () const                        { return _open; }

    private:
        int _sock;          // Socket connected to wherever the data is coming from.
        int _listenSock;    // Socket to listen on when in listen mode.

        std::string _devid;
        unsigned char _port;
        bool _isListener;    // True if this port should listen instead of actively connecting.
        bool _open;

        void CheckPort (bool read);

        bool ProcessOption (const std::string &option, const std::string &value);

        void Connect ();
        void WaitForConnection ();
        typedef enum {TIMED_OUT, DATA_AVAILABLE, CAN_WRITE} WaitStatus;
        WaitStatus WaitForDataOrTimeout ();
        bool IsDataAvailable ();
        WaitStatus WaitForWritableOrTimeout ();
        void SetSocketBlockingFlag ();
};

} // namespace flexiport

/** @} */

#endif // __RFCOMMPORT_H

