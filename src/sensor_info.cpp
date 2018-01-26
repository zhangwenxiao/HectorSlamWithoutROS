/* HokuyoAIST
 *
 * Implementation of the sensor information object.
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

#include <hokuyoaist/sensor_info.h>
#include <hokuyoaist/utils.h>

#include <sstream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// SensorInfo class
///////////////////////////////////////////////////////////////////////////////

hokuyoaist::SensorInfo::SensorInfo()
  : min_range(0), max_range(0), steps(0), first_step(0), last_step(0),
  front_step(0), standard_speed(0), rot_dir(COUNTERCLOCKWISE), power(false),
  speed(0), speed_level(0), baud(0), time(0), min_angle(0.0), max_angle(0.0),
  resolution(0.0), time_resolution(0), scanable_steps(0), max_step(0),
  detected_model(MODEL_UNKNOWN)
{
}


// Set various known values based on what the manual says
void
hokuyoaist::SensorInfo::set_defaults()
{ switch (detected_model)
  {
    case MODEL_URG04LX:
      min_range = 20;
      max_range = 4095;
      steps = 1024;
      first_step = 44;
      last_step = 725;
      front_step = 384;
      max_step = 768;
      break;
    case MODEL_UBG04LXF01:
      min_range = 20;
      max_range = 4095;
      steps = 1024;
      first_step = 44;
      last_step = 725;
      front_step = 384;
      max_step = 768;
      break;
    case MODEL_UHG08LX:
      min_range = 20;
      max_range = 8000;
      steps = 1024;
      first_step = 0;
      last_step = 768;
      front_step = 384;
      max_step = 768;
      break;
    case MODEL_UTM30LX:
      min_range = 20;
      max_range = 60000;
      steps = 1440;
      first_step = 0;
      last_step = 1080;
      front_step = 540;
      max_step = 1080;
      break;
    case MODEL_UXM30LXE:
      min_range = 20;
      max_range = 60000;
      steps = 1440;
      first_step = 0;
      last_step = 760;
      front_step = 380;
      max_step = 760;
      break;
    case MODEL_UNKNOWN:
    default:
      // Use the URG-04LX settings
      min_range = 20;
      max_range = 4095;
      steps = 1024;
      first_step = 44;
      last_step = 725;
      front_step = 384;
      max_step = 768;
      break;
  }
}


void
hokuyoaist::SensorInfo::calculate_values()
{
  resolution = DTOR(360.0) / steps;
  // If any of the steps are beyond INT_MAX, we have problems.
  // We also have an incredibly high-resolution sensor.
  min_angle = (static_cast<int>(first_step) - static_cast<int>(front_step)) *
    resolution;
  max_angle = (static_cast<int>(last_step) - static_cast<int>(front_step)) *
    resolution;
  scanable_steps = last_step - first_step + 1;
  // Calculate the time taken for a single scan.
  if (speed == 0) {
    time_resolution = 60000.0 / 600.0;
  } else {
    // 60000 = milliseconds in a minute
    // speed is in RPM
    time_resolution = 60000.0 / speed;
  }
  time_resolution /= static_cast<double>(steps);
}


std::string
hokuyoaist::SensorInfo::as_string()
{
  std::stringstream ss;

  ss << "Vendor: " << vendor << '\n';
  ss << "Product: " << product << '\n';
  ss << "Identified as: " << model_to_string(detected_model) << '\n';
  ss << "Firmware: " << firmware << '\n';
  ss << "Protocol: " << protocol << '\n';
  ss << "Serial: " << serial << '\n';
  ss << "Model: " << model << '\n';

  ss << "Minimum range: " << min_range << "mm\tMaximum range: " << max_range <<
    "mm\n";
  ss << "Steps in 360 degrees: " << steps << "\tScanable steps: " <<
    scanable_steps << '\n';
  ss << "First step: " << first_step << "\tFront step: " << front_step <<
    "\tLast step: " << last_step << "\tMax step: " << max_step << '\n';
  ss << "Resolution: " << resolution << " radians/step\n";
  ss << "Minimum angle: " << min_angle << " radians\tMaximum angle: " <<
    max_angle << " radians\n";
  ss << "Standard motor speed: " << standard_speed << "rpm\n";
  ss << "Rotation direction: " << rot_dir_to_string(rot_dir) << '\n';

  ss << "Power status: " << (power ? "On" : "Off") <<
    "\tMeasurement state: " << measure_state << '\n';
  ss << "Motor speed: " << speed << "rpm (level " << speed_level <<
    ")\tBaud rate: " << baud << "bps\n";
  ss << "Time stamp: " << time << "ms\n";
  ss << "Time between scan points: " << time_resolution << "ms\n";
  ss << "Sensor diagnostic: " << sensor_diagnostic << '\n';

  return ss.str();
}

