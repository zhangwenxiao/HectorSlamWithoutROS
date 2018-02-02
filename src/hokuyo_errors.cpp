/* HokuyoAIST
 *
 * Implementation of the exceptions.
 *
 * Copyright 2008-2011 Geoffrey Biggs geoffrey.biggs@aist.go.jp
 *   RT-Synthesis Research Group
 *   Intelligent Systems Research Institute,
 *   National Institute of Advanced Industrial Science and Technology (AIST),
 *   Japan
 *   All rights reserved.
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

#include <hokuyoaist/hokuyo_errors.h>

#include <cstdlib>
#include <cstring>

namespace hokuyoaist {

// error must be null-terminated
std::string
scip2_error_to_string(char const* const error, char const* const cmd)
{
  std::stringstream ss;

  // Check for non-errors
  if (error[0] == '0' && error[1] == '0') {
    return "Status OK - 00";
  } else if (error[0] == '9' && error[1] == '9') {
    return "Status OK - 99";
  }

  // Check for universal errors
  if (error[0] == '0' && error[1] == 'A') {
    return "Unable to create transmission data or reply command internally";
  } else if (error[0] == '0' && error[1] == 'B') {
    return "Buffer shortage or command repeated that is already processed";
  } else if (error[0] == '0' && error[1] == 'C') {
    return "Command with insufficient parameters 1";
  } else if (error[0] == '0' && error[1] == 'D') {
    return "Undefined command 1";
  } else if (error[0] == '0' && error[1] == 'E') {
    return "Undefined command 2";
  } else if (error[0] == '0' && error[1] == 'F') {
    return "Command with insufficient parameters 2";
  } else if (error[0] == '0' && error[1] == 'G') {
    return "String character in command exceeds 16 letters";
  } else if (error[0] == '0' && error[1] == 'H') {
    return "String character has invalid letters";
  } else if (error[0] == '0' && error[1] == 'I') {
    return "Sensor is now in firmware update mode";
  }

  int error_code = atoi(error);

  if (cmd[0] == 'B' && cmd[1] == 'M') {
    switch (error_code) {
      case 1:
        return "Unable to control due to laser malfunction";
      case 2:
        return "Laser is already on";
    }
// No info in the manual for this.
//  } else if (cmd[0] == 'Q' && cmd[1] == 'T') {
//    switch (error_code) {
//      default:
//        std::stringstream ss;
//        ss << "Unknown error code " << error_code <<
//            " for command " << cmd[0] << cmd[1];
//        return ss.str ();
//    }
//  }
  } else if (((cmd[0] == 'G' || cmd[0] == 'H') &&
              (cmd[1] == 'D' || cmd[1] == 'E')) ||
             (cmd[0] == 'G' && cmd[1] == 'S'))
  {
    switch (error_code) {
      case 1:
        return "Starting step has non-numeric value";
      case 2:
        return "Ending step has non-numeric value";
      case 3:
        return "Cluster count has non-numeric value";
      case 4:
        return "Ending step is out of range";
      case 5:
        return "Ending step is smaller than start step";
      case 10:
        return "Laser is off";
      default:
        if (error_code >= 50) {
          ss << "Hardware error: " << error_code;
        } else {
          ss << "Unknown error code " << error_code << " for command " << cmd[0] << cmd[1];
        }

        return ss.str();
    }
  } else if (((cmd[0] == 'M' || cmd[0] == 'N') &&
            (cmd[1] == 'D' || cmd[1] == 'E')) ||
           (cmd[0] == 'M' && cmd[1] == 'S'))
  {
    switch (error_code) {
      case 1:
        return "Starting step has non-numeric value";
      case 2:
        return "Ending step has non-numeric value";
      case 3:
        return "Cluster count has non-numeric value";
      case 4:
        return "Ending step is out of range";
      case 5:
        return "Ending step is smaller than start step";
      case 6:
        return "Scan interval has non-numeric value";
      case 7:
        return "Number of scans is non-numeric";
      default:
        if (error_code >= 21 && error_code <= 49) {
          return "Processing stopped to verify error. "
            "This function is not yet supported by hokuyoaist.";
        } else if (error_code >= 50 && error_code <= 97) {
          ss << "Hardware error: " << error_code;
        } else if (error_code == 98) {
          return "Resumption of processing after confirming normal "
            "laser opteration. This function is not yet supported by hokuyoaist.";
        } else {
          ss << "Unknown error code " << error_code << " for command " << cmd[0] << cmd[1];
        }

        return ss.str();
    }
  } else if (cmd[0] == 'T' && cmd[1] == 'M') {
    switch (error_code) {
      case 1:
        return "Invalid control code";
      case 2:
        return "Adjust mode on command received when sensor's adjust "
          "mode is already on";
      case 3:
        return "Adjust mode off command received when sensor's adjust "
          "mode is already off";
      case 4:
        return "Adjust mode is off when requested time";
    }
  } else if (cmd[0] == 'S' && cmd[1] == 'S') {
    switch (error_code) {
      case 1:
        return "Baud rate has non-numeric value";
      case 2:
        return "Invalid baud rate";
      case 3:
        return "Sensor is already running at that baud rate";
      case 4:
        return "Not compatible with the sensor model";
    }
  } else if (cmd[0] == 'C' && cmd[1] == 'R') {
    switch (error_code) {
      case 1:
        return "Invalid speed";
      case 2:
        return "Speed is out of range";
      case 3:
        return "Motor is already running at that speed";
      case 4:
        return "Not compatible with the sensor model";
    }
  } else if (cmd[0] == 'H' && cmd[1] == 'S') {
    switch (error_code) {
      case 1:
        return "Parameter error";
      case 2:
        return "Already running in the set mode";
      case 3:
        return "Not compatible with the sensor model";
    }
// No info in the manual for this.
//  } else if (cmd[0] == 'R' && cmd[1] == 'S')
//  {
//    switch(error_code)
//    {
//      case :
//        return "";
//      default:
//        std::stringstream ss;
//        ss << "Unknown error code " << error_code <<
//          " for command " << cmd[0] << cmd[1];
//        return ss.str ();
//    }
//  }
// No info in the manual for this.
//  else if (cmd[0] == 'V' && cmd[1] == 'V')
//  {
//    switch(error_code)
//    {
//      case :
//        return "";
//    }
//  }
// No info in the manual for this.
//  else if (cmd[0] == 'P' && cmd[1] == 'P')
//  {
//    switch(error_code)
//    {
//      case :
//        return "";
//    }
//  }
// No info in the manual for this.
//  else if (cmd[0] == 'I' && cmd[1] == 'I')
//  {
//    switch(error_code)
//    {
//      case :
//        return "";
//    }
//  }
  } else if (cmd[0] == 'D' && cmd[1] == 'B') {
    switch (error_code) {
      case 1:
        return "Parameter error";
      case 2:
        return "Already running in the set mode";
      case 3:
        return "Already returned to normal mode";
      case 4:
        return "Selected mode does not match the SCIP version in use";
      case 5:
        return "Sensor has a physical malfunction";
    }
  } else {
    ss << "Unknown command: " << cmd[0] << cmd[1];
    return ss.str();
  }

  // Known commands with unknown error codes fall through to here
  ss << "Unknown error code " << error_code << " for command " << cmd[0] << cmd[1];
  return ss.str();
}


std::string
desc_code_to_string(unsigned int code)
{
  static char const* const descriptions[] = {
/* 0 */  "Timed out trying to read a line",
/* 1 */  "No data received when trying to read a line.",
/* 2 */  "Invalid data index.",
/* 3 */  "Port is not open.",
/* 4 */  "Unknown SCIP version.",
/* 5 */  "Cannot change baud rate of non-serial connection.",
/* 6 */  "Bad baud rate: ",
/* 7 */  "SCIP version 1 does not support the reset command.",
/* 8 */  "SCIP version 1 does not support the set motor speed command.",
/* 9 */  "Invalid motor speed.",
/* 10 */ "SCIP version 1 does not support the high sensitivity command.",
/* 11 */ "No info object provided.",
/* 12 */ "SCIP version 1 does not support the get time command.",
/* 13 */ "No data received. Check data error code.",
/* 14 */ "Start step is out of range.",
/* 15 */ "End step is out of range.",
/* 16 */ "SCIP version 1 does not support the get new ranges command.",
/* 17 */ "SCIP version 1 does not support the get new ranges and intensities command.",
/* 18 */ "Timed out while skipping.",
/* 19 */ "Failed to write command byte.",
/* 20 */ "Failed to write command parameters.",
/* 21 */ "Failed to write termination character.",
/* 22 */ "SCIP versions 1 and 2 failed.",
/* 23 */ "Out-of-range firmware version.",
/* 24 */ "Invalid checksum: ",
/* 25 */ "Read a different number of range or intensity readings than were asked for.",
/* 26 */ "Found line feed in a data block.",
/* 27 */ "Unknown line: ",
/* 28 */ "Parse error: ",
/* 29 */ "'FIRM:' was not found when checking firmware version.",
/* 30 */ "Bad response.",
/* 31 */ "Incorrect command echo.",
/* 32 */ "Incorrect parameters echo for command.",
/* 33 */ "Not enough bytes to calculate checksum.",
/* 34 */ "Incorrect line length received.",
/* 35 */ "SCIP version 1 does not support the semi-reset command.",
/* 36 */ "SCIP version 1 does not support the get ranges and intensities command.",
/* 37 */ "Error configuring IP address.",
/* 38 */ "Did not receive a full line."
  };

  return std::string(descriptions[code]);
}


BaseError::BaseError(unsigned int desc_code, char const* error_type)
  : desc_code_(desc_code)
{
  strncpy(error_type_, error_type, 32);
  error_type_[31] = 0;
  std::stringstream ss;
  ss << error_type_ << " (" << desc_code_ << "): " << desc_code_to_string(desc_code_);
  error_str_ = ss.str();
}


BaseError::BaseError(BaseError const& rhs)
  : desc_code_(rhs.desc_code()),
  error_str_(rhs.error_str_)
{
  strncpy(error_type_, rhs.error_type(), 32);
}

const char *
BaseError::what() const throw()
{
  return error_str_.c_str();
}

BaudrateError::BaudrateError(unsigned int baud)
  : RuntimeError(6, "BaudrateError"), baud_(baud)
{
  std::stringstream ss;
  ss << baud_;
  error_str_ += ss.str();
}

ChecksumError::ChecksumError(int expected, int calculated)
  : ProtocolError(24, "ChecksumError"), expected_(expected), calculated_(calculated)
{
  std::stringstream ss;
  ss << "expected " << expected_ << ", calculated " << calculated_;
  error_str_ += ss.str();
}

UnknownLineError::UnknownLineError(char const* const line)
  : ProtocolError(27, "UnknownLineError")
{
  strncpy(line_, line, 128);
  error_str_ += std::string(line);
}


UnknownLineError::UnknownLineError(UnknownLineError const& rhs)
  : ProtocolError(rhs)
{
  strncpy(line_, rhs.line(), 128);
}

ParseError::ParseError(char const* const line, char const* const type)
  : ProtocolError(28, "ParseError")
{
  strncpy(line_, line, 128);
  line_[127] = 0;
  strncpy(type_, type, 16);
  type_[15] = 0;
  std::stringstream ss;
  ss << "Line type: " << type_ << ". Line: " << line_;
  error_str_ += ss.str();
}


ParseError::ParseError(ParseError const& rhs)
  : ProtocolError(rhs)
{
  strncpy(line_, rhs.line(), 128);
  strncpy(type_, rhs.type(), 16);
}

ResponseError::ResponseError(char const* const error, char const* const cmd)
  : ProtocolError(30, "ResponseError")
{
  error_[0] = error[0]; error_[1] = error[1];
  cmd_[0] = cmd[0]; cmd_[1] = cmd[1];
  std::stringstream ss;
  ss << " Command: " << cmd_[0] << cmd_[1];
  ss << " Error : (" << error_[0] << error_[1] << ") " <<
    scip2_error_to_string(error_, cmd_);
  error_str_ += ss.str();
}
ResponseError::ResponseError(ResponseError const& rhs)
  : ProtocolError(rhs)
{
  error_[0] = rhs.error_code()[0];
  error_[1] = rhs.error_code()[1];
  cmd_[0] = rhs.cmd_code()[0];
  cmd_[1] = rhs.cmd_code()[1];
}

Scip1ResponseError::Scip1ResponseError(char error, char cmd)
  : ProtocolError(30, "Scip1ResponseError"),
  error_(error), cmd_(cmd)
{
  std::stringstream ss;
  ss << " Command: " << cmd_;
  ss << " Error : " << error_;
  error_str_ += ss.str();
}
Scip1ResponseError::Scip1ResponseError(Scip1ResponseError const& rhs)
  : ProtocolError(rhs), error_(rhs.error_code()),
  cmd_(rhs.cmd_code())
{
}

CommandEchoError::CommandEchoError(char const* const cmd, char const* const echo)
  : ProtocolError(31, "CommandEchoError")
{
  cmd_[0] = cmd[0]; cmd_[1] = cmd[1];
  echo_[0] = echo[0]; echo_[1] = echo[1];
  std::stringstream ss;
  ss << " Command: " << cmd_[0] << cmd_[1];
  ss << " Received echo: " << echo_[0] << echo_[1];
  error_str_ += ss.str();
}
CommandEchoError::CommandEchoError(CommandEchoError const& rhs)
  : ProtocolError(rhs)
{
  cmd_[0] = rhs.cmd_code()[0];
  cmd_[1] = rhs.cmd_code()[1];
  echo_[0] = rhs.cmd_echo()[0];
  echo_[1] = rhs.cmd_echo()[1];
}

ParamEchoError::ParamEchoError(char const* const cmd)
  : ProtocolError(32, "ParamEchoError")
{
  cmd_[0] = cmd[0]; cmd_[1] = cmd[1];
  std::stringstream ss;
  ss << " Command: " << cmd_[0] << cmd_[1];
  error_str_ += ss.str();
}

ParamEchoError::ParamEchoError(ParamEchoError const& rhs)
  : ProtocolError(rhs)
{
  cmd_[0] = rhs.cmd_code()[0];
  cmd_[1] = rhs.cmd_code()[1];
}

InsufficientBytesError::InsufficientBytesError(int num, int line_length)
  : ProtocolError(33, "InsufficientBytesError"),
  num_(num), line_length_(line_length)
{
  std::stringstream ss;
  ss << " Number of bytes: " << num_;
  ss << " Line length: " << line_length_;
  error_str_ += ss.str();
}
InsufficientBytesError::InsufficientBytesError(InsufficientBytesError const& rhs)
  : ProtocolError(rhs), num_(rhs.num()),
  line_length_(rhs.line_length())
{
}

LineLengthError::LineLengthError(int length, int expected)
  : ProtocolError(34, "LineLengthError"),
  length_(length), expected_(expected)
{
  std::stringstream ss;
  ss << " Received length: " << length_;
  ss << " Expected line length: " << expected_;
  error_str_ += ss.str();
}

LineLengthError::LineLengthError(LineLengthError const& rhs)
  : ProtocolError(rhs), length_(rhs.length()),
  expected_(rhs.expected())
{
}

} // namespace hokuyoaist

