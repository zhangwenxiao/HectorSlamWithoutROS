/* HokuyoAIST
 *
 * Main header file.
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

#ifndef HOKUYOAIST_H__
#define HOKUYOAIST_H__

#include <hokuyoaist/hokuyo_errors.h>
#include <hokuyoaist/sensor_info.h>
#include <hokuyoaist/scan_data.h>
#include <hokuyoaist/sensor.h>

// TODO: The line reading code is suffering from age. It is getting bloated and
// complicated, not to mention slow. Reading the range data has been switched
// to an improved method. The rest of the reads need to be moved to this new
// method. Not urgent as only the range data needs to be read really
// efficiently.

#endif // HOKUYOAIST_H__

