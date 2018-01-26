/* HokuyoAIST
 *
 * Header file for the scan data object.
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

#ifndef INCLUDE_HOKUYOAIST_SCAN_DATA_H__
#define INCLUDE_HOKUYOAIST_SCAN_DATA_H__

#if defined(WIN32)
  typedef unsigned char       uint8_t;
  typedef unsigned int      uint32_t;
  #if defined(HOKUYOAIST_STATIC)
    #define HOKUYOAIST_EXPORT
  #elif defined(hokuyoaist_EXPORTS)
    #define HOKUYOAIST_EXPORT     __declspec(dllexport)
  #else
    #define HOKUYOAIST_EXPORT     __declspec(dllimport)
  #endif
#else
  #include <stdint.h>
  #define HOKUYOAIST_EXPORT
#endif

#include <hokuyoaist/sensor_info.h>

#include <string>

/** @ingroup library_hokuyoaist
@{
*/

namespace hokuyoaist {

class Sensor;

/** @brief Structure to store data returned from the laser scanner. */
class HOKUYOAIST_EXPORT ScanData
{
  public:
    friend class Sensor;

    /// This constructor creates an empty ScanData with no data currently
    /// allocated.
    ScanData();
    /// This constructor uses a provided data buffer rather than allocating
    /// automatically.
    ///
    /// If the intensity pointer is 0, no data will be provided of that
    /// type.
    ///
    /// @param ranges_buffer A pointer to a data area to store range data
    /// in. It is the caller's responsibility to ensure that it is big
    /// enough.
    /// @param ranges_length The size of the ranges buffer. Used only for
    /// copy constructor and similar.
    /// @param intensities_buffer A pointer to a data area to store
    /// intensity data in. It is the caller's responsibility to ensure that
    /// it is big enough.
    /// @param intensities_length The size of the intensities buffer. Used
    /// only for copy constructor and similar.
    ScanData(
      uint32_t* const ranges_buffer,
      unsigned int ranges_length,
      uint32_t* const intensities_buffer = 0,
      unsigned int intensities_length = 0);
    /// This copy constructor performs a deep copy of present data.
    ScanData(ScanData const& rhs);
    ~ScanData();

    /** @brief Return a pointer to array of range readings in millimetres.

    Values less than 20mm indicate an error. Check the error value for the
    data to see a probable cause for the error. Most of the time, it will
    just be an out-of-range reading. */
    const uint32_t* ranges() const
      { return ranges_; }
    /// @brief Return a pointer to an array of intensity readings.
    const uint32_t* intensities() const
      { return intensities_; }
    /// @brief Get the number of range samples in the data.
    unsigned int ranges_length() const { return ranges_length_; }
    /// @brief Get the number of intensity samples in the data.
    unsigned int intensities_length() const { return intensities_length_; }
    /** @brief Indicates if one or more steps had an error.

    A step's value will be less than 20 if it had an error. Use @ref
    error_code_to_string to get a textual representation of the error. */
    bool get_error_status() const { return error_; }
    /// @brief Return a string representing the error for the given error
    /// code.
    std::string error_code_to_string(uint32_t error_code);
    /** @brief Get the raw time stamp of the data in milliseconds.

    This value is only available using SCIP version 2). */
    unsigned int laser_time_stamp() const { return laser_time_; }
    /** @brief Get the system time stamp of the data in milliseconds.

    This value is only available using SCIP version 2). */
    unsigned long long system_time_stamp() const { return system_time_; }
    /// Get the model of the laser that produced this scan.
    LaserModel model() const { return model_; }
    /// Check if the buffers are being provided instead of automatic.
    bool buffers_provided() const { return buffers_provided_; }

    /// @brief Assignment operator.
    ///
    /// If the rhs has provided buffers, the lhs will not receive the same
    /// buffers. Instead, it will copy the data into its own buffers.
    /// If the lhs has provided buffers, it is the caller's responsibility
    /// to ensure they will be big enough to receive the data from the rhs,
    /// except in the case of 0 buffers (no data will be copied for 0
    /// buffers).
    ScanData& operator=(ScanData const& rhs);
    /** @brief Subscript operator.

    Provides direct access to an element of the range data. */
    uint32_t operator[](unsigned int index);

    /// @brief Format the entire object into a string.
    std::string as_string();

    /// @brief Force the data to clean up.
    void clean_up();

  protected:
    uint32_t* ranges_;
    uint32_t* intensities_;
    unsigned int ranges_length_;
    unsigned int intensities_length_;
    bool error_;
    unsigned int laser_time_;
    unsigned long long system_time_;
    LaserModel model_;
    bool buffers_provided_;

    void allocate_data(unsigned int length,
    bool include_intensities = false);
    void write_range(unsigned int index, uint32_t value);
    void write_intensity(unsigned int index, uint32_t value);
}; // class ScanData

} // namespace hokuyoaist

/** @} */

#endif // INCLUDE_HOKUYOAIST_SCAN_DATA_H__
