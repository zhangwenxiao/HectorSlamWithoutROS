/* Flexiport
 *
 * Header file for some types that are not defined on Windows.
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

#ifndef __FLEXIPORT_TYPES_H
#define __FLEXIPORT_TYPES_H

#if defined (WIN32)
    typedef unsigned char           uint8_t;
    typedef unsigned int            uint32_t;
    #if defined (_WIN64)
        typedef __int64                 ssize_t;
    #else
        typedef _W64 int                ssize_t;
    #endif
#else
    #include <stdint.h>
    #include <sys/types.h>
#endif

#endif // __FLEXIPORT_TYPES_H

