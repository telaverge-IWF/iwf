/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ids_routedb.h,v 3.5 2010/09/22 05:23:49 nvijikumar Exp $
 *
 *  LOG: $Log: ids_routedb.h,v $
 *  LOG: Revision 3.5  2010/09/22 05:23:49  nvijikumar
 *  LOG: GlobalUniqueAddr based routing/distribution support
 *  LOG:
 *  LOG: Revision 3.4  2010/08/19 11:23:06  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 3.3.18.2  2010/06/02 06:15:34  rajeshak
 *  LOG: Fix for Help desk ID:2377
 *  LOG:
 *  LOG: Revision 3.3.18.1  2010/04/26 06:28:26  rajeshak
 *  LOG: 1.Locking the complete operation in FindBestMatch to avoid List corruption.
 *  LOG: 2.Proper Handling of Timeout indication
 *  LOG:
 *  LOG: Revision 3.3  2008/10/31 05:32:03  nvijikumar
 *  LOG: IssueID:1189
 *  LOG: FeatureID: none
 *  LOG: Description: 1. Introducing additional TQs and Threads for better
 *  LOG:                 Performance on PP50 and initial stack tunning
 *  LOG:              2. Unwanted code cleanup
 *  LOG:
 *  LOG: Revision 3.2  2008/07/31 06:24:29  sureshj
 *  LOG: Removing Errors for RH5.0 Linux
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.8  2008/03/27 11:21:05  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.5.6.2  2007/03/15 18:22:07  hbhatnagar
 *  LOG: added new function RemoveEntryWithAppId
 *  LOG:
 *  LOG: Revision 2.5.6.1  2007/03/13 05:09:06  hbhatnagar
 *  LOG: RetrieveWithAppId method added
 *  LOG:
 *  LOG: Revision 2.5  2006/12/12 14:10:28  kamakshilk
 *  LOG: Added GetAllEntries method to get clientId list
 *  LOG:
 *  LOG: Revision 2.4  2006/11/14 06:57:01  kamakshilk
 *  LOG: Overloaded FindBestMatch() for round robin routing
 *  LOG:
 *  LOG: Revision 2.3  2006/11/08 06:13:38  kamakshilk
 *  LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 *  LOG:
 *  LOG: Revision 2.2  2006/10/29 05:20:59  kamakshilk
 *  LOG: RemoveAllEntries() method added
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 12:48:31  adutta
 *  LOG: First cut
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ids_routedb.h,v 3.5 2010/09/22 05:23:49 nvijikumar Exp $"

#if !defined(ROUTE_TABLE_H)
#define ROUTE_TABLE_H

#include <list>

#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>

/*.Interface: RouteTable
 *****************************************************************************
 *  Interface:
 *      RouteTable Class
 *
 *  Purpose:
 *      Implement the Route DB Functionality
 *****************************************************************************/
class RouteTable
{
public:

    RouteTable()
    :   lock(0)
    {};

    ~RouteTable();

    void Lock() const;

    void Unlock() const;

    void InsertEntry(ClientRoutingInfo* entryParam);

    void InsertRoutingEntry(ClientRoutingInfo* entryParam);

    ClientRoutingInfo* RetrieveEntry(const ITS_UINT entryKey);

    ClientRoutingInfo* RetrieveWithAppId(const ITS_UINT entryKey, 
                                 ITS_UINT appId);

    void RemoveEntry(const ITS_UINT entryKey);

    void RemoveEntryWithAppId(const ITS_UINT entryKey, ITS_UINT appId);

    void RemoveAllEntries();

    ITS_UINT* GetAllEntries(ITS_UINT &count);

    ITS_UINT* GetAllEntries(ITS_UINT appId, ITS_UINT &count);

    ITS_UINT FindBestMatch(ITS_UINT appId, ITS_UINT* clientID);

    ITS_UINT FindBestMatch(ITS_UINT appId);

    ITS_UINT FindBestMatch(unsigned char *guIpAddr, ITS_UINT appId);

    void Print(std::ostream& os) const;

    ITS_UINT GetSize()
    {
        ITS_UINT size = 0;
        Lock();
        size = routInfo_.size();
        Unlock();
        return size;
    }

private:

    std::list<ClientRoutingInfo*> routInfo_;
    its::ITS_Mutex lock;
};

// RouteTable ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const RouteTable& table);

#endif
