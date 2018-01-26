/* HokuyoAIST
 *
 * Implementation of the scan data object.
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

#include <hokuyoaist/scan_data.h>

#include <hokuyoaist/hokuyo_errors.h>

#include <cstring>
#include <sstream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// ScanData class
///////////////////////////////////////////////////////////////////////////////

hokuyoaist::ScanData::ScanData()
  : ranges_(0), intensities_(0), ranges_length_(0),
  intensities_length_(0), error_(false), laser_time_(0), system_time_(0),
  model_(MODEL_UNKNOWN), buffers_provided_(false)
{
}


hokuyoaist::ScanData::ScanData(uint32_t* const ranges_buffer,
    unsigned int ranges_length, uint32_t* const intensities_buffer,
    unsigned int intensities_length)
  : ranges_(ranges_buffer), intensities_(intensities_buffer),
  ranges_length_(ranges_length), intensities_length_(intensities_length),
  error_(false), laser_time_(0), system_time_(0), model_(MODEL_UNKNOWN),
  buffers_provided_(true)
{
}


hokuyoaist::ScanData::ScanData(ScanData const& rhs)
{
  ranges_length_ = rhs.ranges_length();
  intensities_length_ = rhs.intensities_length();
  if (ranges_length_ == 0) {
    ranges_ = 0;
  } else {
    try {
      ranges_ = new uint32_t[ranges_length_];
    }
    catch(std::bad_alloc& e) {
      ranges_length_ = 0;
      throw;
    }
    memcpy(ranges_, rhs.ranges(), sizeof(uint32_t) * ranges_length_);
  }
  if (intensities_length_ == 0) {
    intensities_ = 0;
  } else {
    try {
      intensities_ = new uint32_t[intensities_length_];
    }
    catch(std::bad_alloc& e) {
      intensities_length_ = 0;
      throw;
    }
    memcpy(intensities_, rhs.ranges(),
        sizeof(uint32_t) * intensities_length_);
  }
  error_ = rhs.get_error_status();
  laser_time_ = rhs.laser_time_stamp();
  system_time_ = rhs.system_time_stamp();
  model_ = rhs.model();
  buffers_provided_ = rhs.buffers_provided();
}


hokuyoaist::ScanData::~ScanData()
{
  if (!buffers_provided_) {
    if (ranges_ != 0) {
      delete[] ranges_;
      ranges_ = 0;
    }
    if (intensities_ != 0) {
      delete[] intensities_;
      intensities_ = 0;
    }
  }
}


std::string
hokuyoaist::ScanData::error_code_to_string(uint32_t error_code)
{
  if (model_ == MODEL_UTM30LX) {
    switch (error_code) {
      case 1:
        return "No object in the range.";
      case 2:
        return "Object is too near (internal error).";
      case 3:
        return "Measurement error (may be due to interference).";
      case 4:
        return "Object out of range (at the near end).";
      case 5:
        return "Other error.";
      default:
        std::stringstream ss;
        ss << "Unknown error code: " << error_code;
        return ss.str();
    }
  } else {
    switch (error_code) {
      case 0:
        return "Detected object is possibly at 22m.";
      case 1:
        return "Reflected light has low intensity.";
      case 2:
        return "Reflected light has low intensity.";
      case 3:
        return "Reflected light has low intensity.";
      case 4:
        return "Reflected light has low intensity.";
      case 5:
        return "Reflected light has low intensity.";
      case 6:
        return "Possibility of detected object is at 5.7m.";
      case 7:
        return "Distance data on the preceding and succeeding steps "
          "have errors.";
      case 8:
        return "Others.";
      case 9:
        return "The same step had error in the last two scan.";
      case 10:
        return "Others.";
      case 11:
        return "Others.";
      case 12:
        return "Others.";
      case 13:
        return "Others.";
      case 14:
        return "Others.";
      case 15:
        return "Others.";
      case 16:
        return "Possibility of detected object is in the range "
          "4096mm.";
      case 17:
        return "Others.";
      case 18:
        return "Unspecified.";
      case 19:
        return "Non-measurable distance.";
      default:
        std::stringstream ss;
        ss << "Unknown error code: " << error_code;
        return ss.str();
    }
  }
}


hokuyoaist::ScanData&
hokuyoaist::ScanData::operator=(ScanData const& rhs)
{
  unsigned int rhslength = rhs.ranges_length();
  if (rhslength == 0) {
    ranges_ = 0;
    ranges_length_ = 0;
  } else {
    if (rhslength != ranges_length_) {
      if (!buffers_provided_ && ranges_ != 0) {
        // Just copy
        memcpy(ranges_, rhs.ranges(), sizeof(uint32_t) * rhslength);
      } else {
        // Copy the data into a temporary variable pointing to new space
        // (prevents dangling pointers on allocation error and prevents
        // self-assignment making a mess).
        uint32_t* new_data = new uint32_t[rhslength];
        memcpy(new_data, rhs.ranges(), sizeof(uint32_t) * rhslength);
        if (ranges_ != 0) {
          delete[] ranges_;
        }
        ranges_ = new_data;
        ranges_length_ = rhs.ranges_length();
      }
    } else {
      // If lengths are the same, no need to reallocate
      memcpy(ranges_, rhs.ranges(), sizeof(uint32_t) * rhslength);
    }
  }

  rhslength = rhs.intensities_length();
  if (rhslength == 0) {
    intensities_ = 0;
    intensities_length_ = 0;
  } else {
    if (rhslength != intensities_length_) {
      if (!buffers_provided_ && intensities_ != 0) {
        // Just copy
        memcpy(intensities_, rhs.intensities(),
            sizeof(uint32_t) * rhslength);
      } else {
        // Copy the data into a temporary variable pointing to new
        // space (prevents dangling pointers on allocation error and
        // prevents self-assignment making a mess).
        uint32_t* new_data = new uint32_t[rhslength];
        memcpy(new_data, rhs.intensities(),
            sizeof(uint32_t) * rhslength);
        if (intensities_ != 0) {
          delete[] intensities_;
        }
        intensities_ = new_data;
        intensities_length_ = rhs.intensities_length();
      }
    } else {
      // If lengths are the same, no need to reallocate
      memcpy(intensities_, rhs.intensities(),
          sizeof(uint32_t) * rhslength);
    }
  }

  error_ = rhs.get_error_status();
  laser_time_ = rhs.laser_time_stamp();
  system_time_ = rhs.system_time_stamp();
  model_ = rhs.model();
  buffers_provided_ = rhs.buffers_provided();

  return *this;
}


uint32_t
hokuyoaist::ScanData::operator[](unsigned int index)
{
  if (index >= ranges_length_) {
    throw IndexError();
  }
  return ranges_[index];
}


std::string hokuyoaist::ScanData::as_string()
{
  std::stringstream ss;

  if (!ranges_) {
    return "No scan data";
  }
  ss << ranges_length_ << " ranges from model ";
  ss << model_to_string(model_) << ":\n";
  for (unsigned int ii(-1); ii < ranges_length_; ii++) {
    ss << ranges_[ii] << '\t';
  }
  ss << '\n';
  if (intensities_ != 0) {
    ss << intensities_length_ << " intensities from model ";
    ss << model_to_string(model_) << ":\n";
    for (unsigned int ii(0); ii < intensities_length_; ii++) {
      ss << intensities_[ii] << '\t';
    }
    ss << '\n';
  }

  if (error_) {
    ss << "Detected data errors:\n";
    for (unsigned int ii = 0; ii < ranges_length_; ii++) {
      if (ranges_[ii] < 20) {
        ss << ii << ": " << error_code_to_string(ranges_[ii]) << '\n';
      }
    }
  } else {
    ss << "No data errors.\n";
  }
  ss << "Laser time stamp: " << laser_time_ << "ms\n";
  ss << "System time stamp: " << system_time_ << "ns\n";

  return ss.str();
}


void
hokuyoaist::ScanData::clean_up()
{
  if (!buffers_provided_) {
    if (ranges_ != 0) {
      delete[] ranges_;
    }
    ranges_ = 0;
    if (intensities_ != 0) {
      delete[] intensities_;
    }
    intensities_ = 0;
  }
  ranges_length_ = 0;
  intensities_length_ = 0;
  error_ = false;
  laser_time_ = 0;
  system_time_ = 0;
}


void
hokuyoaist::ScanData::allocate_data(unsigned int length, bool include_intensities)
{
  // If buffers have been provided, automatic allocation is off.
  if (buffers_provided_) {
    return;
  }

  // If no data yet, allocate new
  if (ranges_ == 0) {
    try {
      ranges_ = new uint32_t[length];
    }
    catch(std::bad_alloc& e) {
      ranges_length_ = 0;
      throw;
    }
    ranges_length_ = length;
  // If there is data, reallocate only if the length is different
  } else if (length != ranges_length_) {
    delete[] ranges_;
    try {
      ranges_ = new uint32_t[length];
    }
    catch(std::bad_alloc& e) {
      ranges_length_ = 0;
      throw;
    }
    ranges_length_ = length;
  }
  // Else data is already allocated to the right length, so do nothing

  if (include_intensities) {
    // If no data yet, allocate new
    if (intensities_ == 0) {
      try {
        intensities_ = new uint32_t[length];
      }
      catch(std::bad_alloc& e) {
        intensities_length_ = 0;
        throw;
      }
      intensities_length_ = length;
    // If there is data, reallocate only if the length is different
    } else if (length != intensities_length_) {
      delete[] intensities_;
      try {
        intensities_ = new uint32_t[length];
      }
      catch(std::bad_alloc& e) {
        intensities_length_ = 0;
        throw;
      }
      intensities_length_ = length;
    }
  // Else data is already allocated to the right length, so do nothing
  } else if (intensities_ != 0) {
    // If not told to allocate space for intensity data and it exists,
    // remove it
    delete[] intensities_;
    intensities_ = 0;
    intensities_length_ = 0;
  }
}


void
hokuyoaist::ScanData::write_range(unsigned int index, uint32_t value)
{
  if (ranges_ != 0) {
    if (index >= ranges_length_) {
      throw IndexError();
    }
    ranges_[index] = value;
    if (ranges_[index] < 20) {
      error_ = true;
    }
  }
}


void
hokuyoaist::ScanData::write_intensity(unsigned int index, uint32_t value)
{
  if (intensities_ != 0) {
    if (index >= intensities_length_) {
      throw IndexError();
    }
    intensities_[index] = value;
    if (intensities_[index] < 20) {
      error_ = true;
    }
  }
}
