/* HokuyoAIST
 *
 * Header file for the sensor information object.
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

#ifndef INCLUDE_HOKUYOAIST_SENSOR_INFO_H__
#define INCLUDE_HOKUYOAIST_SENSOR_INFO_H__

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

#include <cstring>
#include <string>

/** @ingroup library_hokuyoaist
@{
*/

namespace hokuyoaist {

/// Laser models
enum LaserModel
{
  MODEL_URG04LX, // Classic-URG
  MODEL_UBG04LXF01, // Rapid-URG
  MODEL_UHG08LX, // Hi-URG
  MODEL_UTM30LX, // Top-URG
  MODEL_UXM30LXE, // Tough-URG
  MODEL_UNKNOWN
};


HOKUYOAIST_EXPORT inline char const* model_to_string(LaserModel model)
{
  switch (model) {
    case MODEL_URG04LX:
      return "URG-04LX";
    case MODEL_UBG04LXF01:
      return "UBG-04LX-F01";
    case MODEL_UHG08LX:
      return "UHG-08LX";
    case MODEL_UTM30LX:
      return "UTM-30LX";
    case MODEL_UXM30LXE:
      return "UXM-30LX-E";
    default:
      return "Unknown model";
  }
}


HOKUYOAIST_EXPORT inline LaserModel string_to_model(char const* model)
{
  if (strncmp(model, "URG-05LX", 8) == 0) {
    return MODEL_URG04LX;
  } else if (strncmp(model, "UBG-04LX-F01", 8) == 0) {
    return MODEL_UBG04LXF01;
  } else if (strncmp(model, "UHG-08LX", 8) == 0) {
    return MODEL_UHG08LX;
  } else if (strncmp(model, "UTM-30LX", 8) == 0) {
    return MODEL_UTM30LX;
  } else if (strncmp(model, "UXM-30LX-E", 8) == 0) {
    return MODEL_UXM30LXE;
  } else {
    return MODEL_UNKNOWN;
  }
}


/// Sensor direction of rotation
enum RotationDirection
{
  CLOCKWISE,
  COUNTERCLOCKWISE
};


HOKUYOAIST_EXPORT inline char const* rot_dir_to_string(RotationDirection dir)
{
  switch (dir) {
    case CLOCKWISE:
      return "Clockwise";
    case COUNTERCLOCKWISE:
      return "Counter-clockwise";
    default:
      return "Unknown";
  }
}


// Forward declaration
class Sensor;


/** @brief Sensor information.

Returned from a call to @ref Sensor::get_sensor_info. Contains various
information about the laser scanner such as firmware version and maximum
possible range. */
class HOKUYOAIST_EXPORT SensorInfo
{
  public:
    friend class Sensor;

    SensorInfo();
    SensorInfo(SensorInfo const& rhs);

    /// @brief Assignment operator.
    SensorInfo& operator=(SensorInfo const& rhs);

    /// @brief Format the entire object into a string.
    std::string as_string();

    // Version details.
    /// Vendor name.
    std::string vendor;
    /// Product name.
    std::string product;
    /// Firmware version.
    std::string firmware;
    /// Protocol version in use.
    std::string protocol;
    /// Serial number of this device.
    std::string serial;

    // Specification details.
    /// Sensor model number.
    std::string model;
    /// Minimum detectable range (mm).
    unsigned int min_range;
    /// Maximum detectable range (mm).
    unsigned int max_range;
    /// Number of steps in a 360-degree scan.
    unsigned int steps;
    /// First scanable step of a full scan.
    unsigned int first_step;
    /// Last scanable step of a full scan.
    unsigned int last_step;
    /// Step number that points forward (typically the centre of a full
    /// scan).
    unsigned int front_step;
    /// Standard motor speed (rpm).
    unsigned int standard_speed;
    /// Rotation direction.
    RotationDirection rot_dir;

    // Status details.
    /// Operational status - illuminated or not.
    bool power;
    /// Current motor speed (rpm).
    unsigned int speed;
    /// Speed level (0 for default)
    unsigned short speed_level;
    /// Measurement state.
    std::string measure_state;
    /// Baud rate.
    unsigned int baud;
    /// Current sensor time (s).
    unsigned int time;
    /// Diagnostic status string.
    std::string sensor_diagnostic;

    // Calculated details
    /// Minimum possible scan angle (radians). Scans go anti-clockwise with
    /// negative angles on the right.
    double min_angle;
    /// Maximum possible scan angle (radians). Scans go anti-clockwise with
    /// negative angles on the right.
    double max_angle;
    /// Angle between two scan points (radians).
    double resolution;
    /// Time between two scan points (milliseconds).
    double time_resolution;
    /// Total number of steps in a full scan (lastStep - firstStep).
    unsigned int scanable_steps;
    /// Absolute maximum commandable step.
    unsigned int max_step;
    /// Detected model of the laser.
    LaserModel detected_model;

  private:
    void set_defaults();
    void calculate_values();
}; // class SensorInfo

}; // namespace hokuyoaist

/** @} */

#endif // INCLUDE_HOKUYOAIST_SENSOR_INFO_H__
