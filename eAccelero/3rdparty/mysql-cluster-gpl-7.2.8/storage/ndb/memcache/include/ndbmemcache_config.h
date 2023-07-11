/*
 Copyright (c) 2011, Oracle and/or its affiliates. All rights
 reserved.
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; version 2 of
 the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 02110-1301  USA
 */
#ifndef TREE_COMPAT_NDBMEMCACHE_CONFIG_H
#define TREE_COMPAT_NDBMEMCACHE_CONFIG_H

#include "config.h"
#include "ndb_types.h"

/* #undef HAVE_MACH_MACH_TIME_H */
/* #undef HAVE_SRANDOMDEV */
#ifndef HAVE_GETHRTIME
/* #undef HAVE_GETHRTIME */
#endif
/* #undef HAVE_GETHRVTIME */
#define HAVE_MEMSET

/* #undef HAVE_SOLARIS_ATOMICS */
/* #undef HAVE_DARWIN_ATOMICS */
/* #undef HAVE_GCC_ATOMICS_WITH_ARCH_FLAG */

#ifndef HAVE_INTTYPES_H
#define PRIu64 "llu"
#endif
 
#define HAVE_FUNC_IN_CXX

/* #undef HAVE_HTONLL */

#endif
