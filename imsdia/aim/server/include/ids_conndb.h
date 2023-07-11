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
 *  ID: $Id: ids_conndb.h,v 3.3 2009/03/18 13:08:43 rajeshak Exp $
 *
 *  LOG: $Log: ids_conndb.h,v $
 *  LOG: Revision 3.3  2009/03/18 13:08:43  rajeshak
 *  LOG: Added new Callback for getting IDC connection info.
 *  LOG:
 *  LOG: Revision 3.2  2008/11/06 07:01:22  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: 3.1.1 release feature
 *  LOG: Description: UDP Transport support between IDS and IDC
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 *  LOG: Start GA 3.0
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
 *  LOG: Revision 1.2  2006/04/26 10:09:00  adutta
 *  LOG: RetrieveEntry() returns -ve
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 12:48:31  adutta
 *  LOG: First cut
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ids_conndb.h,v 3.3 2009/03/18 13:08:43 rajeshak Exp $"

#if !defined(CONN_TABLE_H)
#define CONN_TABLE_H

#include <map>

#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>
#include <ids_common.h>

/*.Interface: ConnectionTable
 *****************************************************************************
 *  Interface:
 *      ConnectionTable Class
 *      
 *  Purpose:
 *      Implement the Connection DB Functionality
 *****************************************************************************/
class ConnectionTable
{
public:

    ConnectionTable()
    :   lock(0)
    {};

    ~ConnectionTable();

    void Lock() const;

    void Unlock() const;

    bool HasEntry(const ITS_UINT& entryKey) const;

    bool HasEntry_MT(const ITS_UINT& entryKey) const;

    void InsertEntry(ITS_UINT key, IDS_TRANS_INFO* entryParam);

    IDS_TRANS_INFO* RetrieveEntry(const ITS_UINT entryKey);

    void RemoveEntry(const ITS_UINT entryKey);
    
    void RemoveAllEntries();

    IDS_TRANS_INFO* GetAllValues(ITS_UINT* count);

    ITS_UINT GetKeyFromValue(IDS_TRANS_INFO* value);

    ITS_UINT GetCount(); 

    void Print(std::ostream& os) const;

private:

    typedef std::map<ITS_UINT, IDS_TRANS_INFO*> ConInfoTable;
    ConInfoTable conInfo; 
    its::ITS_Mutex lock;
};

// SwitchMatrixTable ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const ConnectionTable& table);

#endif
