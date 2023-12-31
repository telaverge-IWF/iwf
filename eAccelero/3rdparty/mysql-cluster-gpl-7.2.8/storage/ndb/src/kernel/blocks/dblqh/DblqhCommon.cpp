/* Copyright (C) 2008 MySQL AB, 2008 Sun Microsystems, Inc.
    All rights reserved. Use is subject to license terms.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <GlobalData.hpp>
#include <SimulatedBlock.hpp>
#include "DblqhCommon.hpp"

NdbLogPartInfo::NdbLogPartInfo(Uint32 instanceNo)
{
  LogParts = globalData.ndbLogParts;
  lqhWorkers = globalData.ndbMtLqhWorkers;
  partCount = 0;
  partMask.clear();
  Uint32 lpno;
  for (lpno = 0; lpno < LogParts; lpno++) {
    if (instanceNo != 0) {
      Uint32 worker = instanceNo - 1;
      assert(worker < lqhWorkers);
      if (worker != lpno % lqhWorkers)
        continue;
    }
    partNo[partCount++] = lpno;
    partMask.set(lpno);
  }
}

Uint32
NdbLogPartInfo::partNoFromId(Uint32 lpid) const
{
  return lpid % LogParts;
}

bool
NdbLogPartInfo::partNoOwner(Uint32 lpno) const
{
  assert(lpno < LogParts);
  return partMask.get(lpno);
}

Uint32
NdbLogPartInfo::partNoIndex(Uint32 lpno) const
{
  assert(lpno < LogParts);
  assert(partMask.get(lpno));
  Uint32 i = 0;
  if (lqhWorkers == 0)
    i = lpno;
  else
    i = lpno / lqhWorkers;
  assert(i < partCount);
  assert(partNo[i] == lpno);
  return i;
}
