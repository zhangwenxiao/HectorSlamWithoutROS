/* HokuyoAIST
 *
 * Header file for exceptions.
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

#ifndef INCLUDE_HOKUYOAIST_HOKUYO_ERRORS_H__
#define INCLUDE_HOKUYOAIST_HOKUYO_ERRORS_H__

#include <sstream>
#include <string>

#if defined(WIN32)
  typedef unsigned char     uint8_t;
  typedef unsigned int    uint32_t;
  #if defined(HOKUYOAIST_STATIC)
  #define HOKUYOAIST_EXPORT
  #elif defined(hokuyoaist_EXPORTS)
  #define HOKUYOAIST_EXPORT   __declspec(dllexport)
  #else
  #define HOKUYOAIST_EXPORT   __declspec(dllimport)
  #endif
#else
  #include <stdint.h>
  #define HOKUYOAIST_EXPORT
#endif

/** @ingroup library_hokuyoaist
@{
*/

namespace hokuyoaist {

/// Translates a SCIP2 error code into a string.
std::string scip2_error_to_string(char const* const error,
  char const* const cmd);

/// Translates an error description code into a string.
std::string desc_code_to_string(unsigned int code);


/// General error class.
class HOKUYOAIST_EXPORT BaseError : public std::exception
{
  public:
    /** @brief Hokuyo error constructor.

    @param desc_code Index into the error descriptions string table.
    @param error_type The error as a string.
    */
    BaseError(unsigned int desc_code, char const* error_type);
    BaseError(BaseError const& rhs);
    virtual ~BaseError() throw() {}

    virtual unsigned int desc_code() const throw()
      { return desc_code_; }

    virtual char const* error_type() const throw()
      { return error_type_; }

    virtual const char* what() const throw();

  protected:
    /** Description code for use with the error string table. */
    unsigned int desc_code_;

    /** Formatted description of the error. */
    std::string error_str_;

    /** String representation of the error. */
    char error_type_[32];
};


/// Logic error class
class HOKUYOAIST_EXPORT LogicError : public BaseError
{
  public:
    /** @brief Logic error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit LogicError(unsigned int desc_code)
      : BaseError(desc_code, "LogicError")
    {}
    explicit LogicError(unsigned int desc_code, char const* error_type)
      : BaseError(desc_code, error_type)
    {}
    virtual ~LogicError() throw() {}
};


/// Runtime error class
class HOKUYOAIST_EXPORT RuntimeError : public BaseError
{
  public:
    /** @brief Runtime error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit RuntimeError(unsigned int desc_code)
      : BaseError(desc_code, "RuntimeError")
    {}
    explicit RuntimeError(unsigned int desc_code, char const* error_type)
      : BaseError(desc_code, error_type)
    {}
    virtual ~RuntimeError() throw() {}
};


/// Read error class
class HOKUYOAIST_EXPORT ReadError: public RuntimeError
{
  public:
    /** @brief Read error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit ReadError(unsigned int desc_code)
      : RuntimeError(desc_code, "ReadError")
    {}
}; // class ReadError


/// Write error class
class HOKUYOAIST_EXPORT WriteError: public RuntimeError
{
  public:
    /** @brief Write error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit WriteError(unsigned int desc_code)
      : RuntimeError(desc_code, "WriteError")
    {}
}; // class WriteError


/// Baudrate error class
class HOKUYOAIST_EXPORT BaudrateError: public RuntimeError
{
  public:
    /** @brief Baud rate error constructor.

    @param baud The bad baud rate. */
    explicit BaudrateError(unsigned int baud);
    BaudrateError(BaudrateError const& rhs);

    unsigned int baud() const throw()
    {
      return baud_;
    }

    protected:
    /** Baud rate that caused the error. */
    unsigned int baud_;
}; // class BaudrateError


/// Close error class
class HOKUYOAIST_EXPORT CloseError: public RuntimeError
{
  public:
    CloseError()
      : RuntimeError(3, "CloseError")
    {}
}; // class CloseError


/// No destination error class
class HOKUYOAIST_EXPORT NoDestinationError: public RuntimeError
{
  public:
    NoDestinationError()
      : RuntimeError(11, "NoDestinationError")
    {}
}; // class NoDestinationError


/// Bad firmware error class
class HOKUYOAIST_EXPORT FirmwareError: public RuntimeError
{
  public:
    FirmwareError()
      : RuntimeError(23, "FirmwareError")
    {}
}; // class FirmwareError


/// SCIP version error class
class HOKUYOAIST_EXPORT ScipVersionError: public RuntimeError
{
  public:
    ScipVersionError()
      : RuntimeError(22, "ScipVersionError")
    {}
}; // class ScipVersionError


/// Unknown SCIP version error class
class HOKUYOAIST_EXPORT UnknownScipVersionError: public RuntimeError
{
  public:
    UnknownScipVersionError()
      : RuntimeError(4, "UnknownScipVersionError")
    {}
}; // class UnknownScipVersionError


/// Unsupported feature error class
class HOKUYOAIST_EXPORT UnsupportedError: public RuntimeError
{
  public:
    /** @brief Unsupported error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit UnsupportedError(unsigned int desc_code)
      : RuntimeError(desc_code, "UnsupportedError")
    {}
}; // class UnsupportedError


/// Bad argument error class
class HOKUYOAIST_EXPORT ArgError: public RuntimeError
{
  public:
    /** @brief Argument error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit ArgError(unsigned int desc_code)
      : RuntimeError(desc_code, "ArgError")
    {}
    ArgError(unsigned int desc_code, char const* error_type)
      : RuntimeError(desc_code, error_type)
    {}
    virtual ~ArgError() throw() {}
}; // class ArgError


/// No data error class
class HOKUYOAIST_EXPORT NoDataError: public RuntimeError
{
  public:
    NoDataError()
      : RuntimeError(13, "NoDataError")
    {}
}; // class NoDataError


/// Not a serial connection error class
class HOKUYOAIST_EXPORT NotSerialError: public RuntimeError
{
  public:
    NotSerialError()
      : RuntimeError(5, "NotSerialError")
    {}
}; // class NotSerialError


/// Bad index error class
class HOKUYOAIST_EXPORT IndexError: public RuntimeError
{
  public:
    IndexError()
      : RuntimeError(2, "IndexError")
    {}
}; // class IndexError


/// Set IP error class
class HOKUYOAIST_EXPORT SetIPError: public RuntimeError
{
  public:
    SetIPError()
      : RuntimeError(37, "SetIPError")
    {}
}; // class SetIPError


/// Invalid motor speed error class
class HOKUYOAIST_EXPORT MotorSpeedError: public ArgError
{
  public:
    MotorSpeedError()
      : ArgError(9, "MotorSpeedError")
    {}
}; // class MotorSpeedError


/// Bad start step error class
class HOKUYOAIST_EXPORT StartStepError: public ArgError
{
  public:
    StartStepError()
      : ArgError(14, "StartStepError")
    {}
}; // class StartStepError


/// Bad end step error class
class HOKUYOAIST_EXPORT EndStepError: public ArgError
{
  public:
    EndStepError()
      : ArgError(15, "EndStepError")
    {}
}; // class EndStepError


/// Base protocol error
class HOKUYOAIST_EXPORT ProtocolError: public RuntimeError
{
  public:
    /** @brief Protocol error constructor.

    @param desc_code Index into the error descriptions string table. */
    explicit ProtocolError(unsigned int desc_code)
      : RuntimeError(desc_code, "ProtocolError")
    {}
    ProtocolError(unsigned int desc_code, char const* error_type)
      : RuntimeError(desc_code, error_type)
    {}
    virtual ~ProtocolError() throw() {}
}; // class ProtocolError


/// Bad checksum error
class HOKUYOAIST_EXPORT ChecksumError: public ProtocolError
{
  public:
    /** @brief Checksum error constructor.

    @param expected The expected checksum.
    @param calculated The calculated checksum. */
    ChecksumError(int expected, int calculated);
    ChecksumError(ChecksumError const& rhs);

    virtual int expected() const throw()
      { return expected_; }

    virtual int calculated() const throw()
      { return calculated_; }

  protected:
    /** Expected checksum value. */
    int expected_;
    /** Calculated checksum value. */
    int calculated_;
}; // class ProtocolError


/// Incorrect number of data sets read error
class HOKUYOAIST_EXPORT DataCountError: public ProtocolError
{
  public:
    DataCountError()
      : ProtocolError(25, "DataCountError")
    {}
}; // class DataCountError


/// Misplaced line feed error
class HOKUYOAIST_EXPORT MisplacedLineFeedError: public ProtocolError
{
  public:
    MisplacedLineFeedError()
      : ProtocolError(26, "MisplacedLineFeedError")
    {}
}; // class MisplacedLineFeedError


/// UnknownLine error
class HOKUYOAIST_EXPORT UnknownLineError: public ProtocolError
{
  public:
    /** @brief Unknown line error constructor.

    @param line The mystery line that was not understood. */
    explicit UnknownLineError(char const* const line);
    UnknownLineError(UnknownLineError const& rhs);

    virtual char const* const line() const throw()
      { return line_; }

  protected:
    /** The mystery line. */
    char line_[128];
}; // class UnknownLineError


/// Parse error
class HOKUYOAIST_EXPORT ParseError: public ProtocolError
{
  public:
    /** @brief Parse error constructor.

    @param line The line that could not be parsed.
    @param type The type of line that was expected. */
    ParseError(char const* const line, char const* const type);
    ParseError(ParseError const& rhs);

    virtual char const* const line() const throw()
      { return line_; }

    virtual char const* const type() const throw()
      { return type_; }

  protected:
    /** The bad line. */
    char line_[128];
    /** The type of line. */
    char type_[16];
}; // class ParseError


/// Missing firmware specification error
class HOKUYOAIST_EXPORT MissingFirmSpecError: public ProtocolError
{
  public:
    MissingFirmSpecError()
      : ProtocolError(29, "MissingFirmSpecError")
    {}
}; // class MissingFirmSpecError


/// Bad response error - may be sent in response to any command
class HOKUYOAIST_EXPORT ResponseError: public ProtocolError
{
  public:
    /** @brief Response error constructor.

    @param error The two-byte error code received.
    @param cmd The command that caused the error. */
    ResponseError(char const* const error, char const* const cmd);
    ResponseError(ResponseError const& rhs);

    /// Get the two-byte error code as a non-null-terminated array.
    virtual char const* const error_code() const throw()
      { return error_; }

    /// Get the two-byte command code as a non-null-terminated array.
    virtual char const* const cmd_code() const throw()
      { return cmd_; }

  protected:
    /** Error code as defined in SCIP2 (two bytes). */
    char error_[2];
    /** Command that triggered the error, from SCIP2 (two bytes). */
    char cmd_[2];
}; // class ResponseError


/// Bad response error (SCIP1 version)
class HOKUYOAIST_EXPORT Scip1ResponseError: public ProtocolError
{
  public:
    /** @brief Response error constructor.

    @param error The two-byte error code received.
    @param cmd The command that caused the error. */
    Scip1ResponseError(char error, char cmd);
    Scip1ResponseError(Scip1ResponseError const& rhs);
    /// Get the one-byte error code.
    virtual char error_code() const throw()
      { return error_; }

    /// Get the one-byte command code.
    virtual char cmd_code() const throw()
      { return cmd_; }

  protected:
    /** Error code as defined in SCIP2 (two bytes). */
    char error_;
    /** Command that triggered the error, from SCIP2 (two bytes). */
    char cmd_;
}; // class Scip1ResponseError


/// Command echo error
class HOKUYOAIST_EXPORT CommandEchoError: public ProtocolError
{
  public:
    /** @brief Command echo error constructor.

    @param cmd The two-byte command code expected.
    @param echo The two-byte command echo received. */
    CommandEchoError(char const* const cmd, char const* const echo);
    CommandEchoError(CommandEchoError const& rhs);

    /// Get the two-byte command code as a non-null-terminated array.
    virtual char const* const cmd_code() const throw()
      { return cmd_; }

    /// Get the two-byte command echo as a non-null-terminated array.
    virtual char const* const cmd_echo() const throw()
      { return echo_; }

  protected:
    /** Command that triggered the error, from SCIP2 (two bytes). */
    char cmd_[2];
    /** Received echo. */
    char echo_[2];
}; // class CommandEchoError


/// Parameter echo error
class HOKUYOAIST_EXPORT ParamEchoError: public ProtocolError
{
  public:
    /** @brief Parameter echo error constructor.

    @param cmd The two-byte command code sent. */
    explicit ParamEchoError(char const* const cmd);
    ParamEchoError(ParamEchoError const& rhs);

    /// Get the two-byte command code as a non-null-terminated array.
    virtual char const* const cmd_code() const throw()
      { return cmd_; }

  protected:
    /** Command that triggered the error, from SCIP2 (two bytes). */
    char cmd_[2];
}; // class ParamEchoError


/// Insufficient bytes to calculate checksum error
class HOKUYOAIST_EXPORT InsufficientBytesError: public ProtocolError
{
  public:
    /** @brief Insufficient bytes error constructor.

    @param num The number of bytes received.
    @param line_length The length of the line. */
    InsufficientBytesError(int num, int line_length);
    InsufficientBytesError(InsufficientBytesError const& rhs);

    virtual int num() const throw()
      { return num_; }

    virtual int line_length() const throw()
      { return line_length_; }

  protected:
    /** Number of bytes available. */
    int num_;
    /** Length of the line. */
    int line_length_;
}; // class InsufficientBytesError


/// Incorrect line length error
class HOKUYOAIST_EXPORT LineLengthError: public ProtocolError
{
  public:
    /** @brief Line length error constructor.

    @param length The number of bytes received.
    @param expected The expected length of the line. */
    LineLengthError(int length, int expected);
    LineLengthError(LineLengthError const& rhs);

    virtual int length() const throw()
      { return length_; }

    virtual int expected() const throw()
      { return expected_; }

  protected:
    /** The received line length. */
    int length_;
    /** The expected line length. */
    int expected_;
}; // class LineLengthError

} // namespace hokuyoaist

/** @} */

#endif // INCLUDE_HOKUYOAIST_HOKUYO_ERRORS_H__
