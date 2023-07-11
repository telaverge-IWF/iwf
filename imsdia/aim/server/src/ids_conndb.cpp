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
 *  ID: $Id: ids_conndb.cpp,v 3.8 2009/03/18 13:08:12 rajeshak Exp $
 *
 *  LOG: $Log: ids_conndb.cpp,v $
 *  LOG: Revision 3.8  2009/03/18 13:08:12  rajeshak
 *  LOG: Added new Callback for getting IDC connection info.
 *  LOG:
 *  LOG: Revision 3.7  2009/03/03 11:10:47  rajeshak
 *  LOG: Klockwork reported issue fix
 *  LOG:
 *  LOG: Revision 3.6  2009/02/26 05:19:29  nvijikumar
 *  LOG: Delete Mutex when connEntry is freed
 *  LOG:
 *  LOG: Revision 3.5  2009/02/19 05:41:22  nvijikumar
 *  LOG: Introduced mutex for trans info
 *  LOG:
 *  LOG: Revision 3.4  2008/11/06 07:36:07  rajeshak
 *  LOG: IDS Connection Status Information (Establishment time)
 *  LOG:
 *  LOG: Revision 3.3  2008/11/06 07:13:14  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: 3.1.1 release feature
 *  LOG: Description: UDP Transport support between IDS and IDC
 *  LOG:
 *  LOG: Revision 3.2  2008/10/31 05:35:24  nvijikumar
 *  LOG: IssueID:1189
 *  LOG: FeatureID: none
 *  LOG: Description: 1. Introducing additional TQs and Threads for better
 *  LOG:                 Performance on PP50 and initial stack tunning
 *  LOG:              2. Unwanted code cleanup
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.4  2006/11/14 07:07:54  kamakshilk
 *  LOG: Fix for bugID 4686
 *  LOG:
 *  LOG: Revision 2.3  2006/11/08 06:12:40  kamakshilk
 *  LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 *  LOG:
 *  LOG: Revision 2.2  2006/10/29 05:25:05  kamakshilk
 *  LOG: Added RemoveAllEntries() method
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/04/26 10:08:19  adutta
 *  LOG: Debug trace added in HasEntry()
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 *  LOG: First cut
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ids_conndb.cpp,v 3.8 2009/03/18 13:08:12 rajeshak Exp $"

#include <iostream>

#include <engine++.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#include <dia_trace.h>
#include <ids_conndb.h>



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
ConnectionTable::~ConnectionTable()
{   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ConnectionTable::Lock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Acquire();
    
    if (res != ITS_SUCCESS)
    {   
        ITS_THROW_ERROR(res);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ConnectionTable::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {   
        ITS_THROW_ERROR(res);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
bool
ConnectionTable::HasEntry_MT(const ITS_UINT& entryKey) const
{
    bool found = false;

    Lock();

    ConInfoTable::const_iterator iter = conInfo.find(entryKey);

    found = (iter != conInfo.end());

    DIA_TRACE_DEBUG(("ConnectionTable: HasEntry_MT %d", found));

    Unlock();
    
    return found;
}

/*****************************************************************************
 *  Purpose:
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
bool
ConnectionTable::HasEntry(const ITS_UINT& entryKey) const
{ 
    bool found = false;

    ConInfoTable::const_iterator iter = conInfo.find(entryKey);

    found = (iter != conInfo.end());

    DIA_TRACE_DEBUG(("ConnectionTable: HasEntry %d", found));

    return (found);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ConnectionTable::InsertEntry(ITS_UINT key, IDS_TRANS_INFO* entryParam)
{
    IDS_TRANS_INFO *dInfo = NULL;
    DIA_TRACE_DEBUG(("ConnectionTable: InsertEntry"));

    Lock();

    /* Get Time */
    time(&(entryParam->estbTime));

    dInfo = (IDS_TRANS_INFO *)malloc(sizeof(IDS_TRANS_INFO));
    if (dInfo == NULL)
    {
        //alloc failed throw exception();
        throw "Error: memory allocation failed";
    }

    memcpy(dInfo, entryParam, sizeof(IDS_TRANS_INFO));
 
    if (MUTEX_CreateMutex(&dInfo->wMutex, 0) != ITS_SUCCESS)
    {
        DIA_TRACE_ERROR(("Failed to create mutex"));
    }
    pair<ConInfoTable::iterator, bool> insertRes =
        conInfo.insert(ConInfoTable::value_type(key, dInfo));

    ITS_ENSURE(insertRes.second);

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      Not thread safe. To be used in conjunction with Lock() and Unlock().
 *
 *  See Also:
 *  
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    11-11-06    Bug Id 4686     Unlock when entry not found.
 *
 ****************************************************************************/
IDS_TRANS_INFO *
ConnectionTable::RetrieveEntry(const ITS_UINT entryKey)
{
    IDS_TRANS_INFO *entry = NULL;
    Lock();

    DIA_TRACE_DEBUG(("ConnectionTable: RetrieveEntry"));
#if 0
    if (!(HasEntry(entryKey)))
    {
        Unlock();
        return (ITS_ENOTFOUND);
    }
#endif

    ConInfoTable::iterator iter = conInfo.find(entryKey);

    if (iter != conInfo.end())
    {
        entry = ((*iter).second);
    }

    Unlock();

    return (entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ConnectionTable::RemoveEntry(const ITS_UINT entryKey)
{
    IDS_TRANS_INFO *info = NULL;

    Lock();

    DIA_TRACE_DEBUG(("ConnectionTable: RemoveEntry"));

    if (HasEntry(entryKey))
    {
        DIA_TRACE_DEBUG(("RemoveEntry: key <%d>", entryKey));
        if ((info = RetrieveEntry(entryKey)) != NULL)
        {
            MUTEX_DeleteMutex(&info->wMutex);
            free(info);
        }
        conInfo.erase(entryKey);
    }

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Removes all the existing entries from the map
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ConnectionTable::RemoveAllEntries()
{
    IDS_TRANS_INFO *info = NULL;
    Lock();

    DIA_TRACE_DEBUG(("ConnectionTable::RemoveAllEntries"));

    ConInfoTable::iterator bIter = conInfo.begin();

    while(bIter != conInfo.end())
    {
        DIA_TRACE_DEBUG(("RemoveAllEntries: Removing entry <%u>",
                              bIter->first));
        info = bIter->second;
        if (info != NULL)
        {
            free(info);
            info = NULL;
        }
        conInfo.erase(bIter);
        
        bIter = conInfo.begin();        
    }

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ConnectionTable::Print(std::ostream& os) const
{
    Lock();

    os << "-----------------------------------------------------------" << endl;
    os << "-- Connection Table Begin --" << endl;
    os << "-----------------------------------------------------------" << endl;
    os << endl;
    os << "Size: <" << conInfo.size() << ">" << endl;
    os << endl;
    os << "Entries:" << endl;
    os << "--------------------------------------------------" << endl;

    ConInfoTable::const_iterator iter = conInfo.begin();

    bool hasEntry = false;

    while(iter != conInfo.end())
    {
        hasEntry = true;

	IDS_TRANS_INFO *info = (*iter).second;

	struct tm tbuf;

        char buff[80];

        localtime_r(&info->estbTime, &tbuf);
        strftime(buff, 80, "%d %B %Y %H:%M:%S" , &tbuf);

        os << "Client Id \t\t: " << ((*iter).first) <<endl;

        if ( info->type == IDS_TCP )
        {
            os << "Transport Instance \t: " << info->u.tcpInfo << endl;
            os << "Transport Type \t\t: " << "TCP" << endl;
        }
        else
        {
            os << "Port \t\t\t: " << info->u.udpInfo.port << endl;
            os << "IP Address \t\t: " << info->u.udpInfo.ipAddr << endl;
            os << "Transport Type \t\t: " << "UDP" << endl;
        }

        os << "Establishment Time \t: " << buff << endl;
        os << "Status \t\t\t: " << "Connected" << endl;

        os << "--------------------------------------------------" << endl;

        iter++;
    }

    if (!hasEntry)
    {
        os << "--------------------------------------------------" << endl;
    }

    os << "-----------------------------------------------------------" << endl;
    os << "-- Connection Table End --" << endl;
    os << "-----------------------------------------------------------" << endl;

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
IDS_TRANS_INFO*
ConnectionTable::GetAllValues(ITS_UINT* count)
{
    ITS_INT index = 0;
    IDS_TRANS_INFO *dInfo= NULL;

    Lock();

    DIA_TRACE_DEBUG(("ConnectionTable: GetAllValues"));

    ConInfoTable::const_iterator iter = conInfo.begin();
    *count = conInfo.size();

    if (*count)
    {
        dInfo= (IDS_TRANS_INFO*)calloc(*count, sizeof(IDS_TRANS_INFO));
        for (index = 0; index < *count; index++)
        {
            memcpy(&dInfo[index], ((*iter).second), sizeof(IDS_TRANS_INFO));
            iter++;
        }
    }

    Unlock();

    return (dInfo);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To get the size of IDC connection Table
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT 
ConnectionTable::GetCount()
{
    int count = 0;

    Lock();

    DIA_TRACE_DEBUG(("ConnectionTable: GetCount"));

    ConInfoTable::const_iterator iter = conInfo.begin();
    count = conInfo.size();

    Unlock();

    return count;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT
ConnectionTable::GetKeyFromValue(IDS_TRANS_INFO * dInfo)
{
    ITS_INT ret = 0;
    ConInfoTable::const_iterator iter = conInfo.begin();

    Lock();

    DIA_TRACE_DEBUG(("ConnectionTable: GetKeyFromValue"));
    IDS_TRANS_INFO *tmpInfo =NULL;

    if(dInfo->type == IDS_UDP)
    {
        while(iter != conInfo.end())
        {
            tmpInfo = (*iter).second;

            if ((strcmp(dInfo->u.udpInfo.ipAddr, tmpInfo->u.udpInfo.ipAddr) == 0) &&
                    (dInfo->u.udpInfo.port == tmpInfo->u.udpInfo.port))
            {
                ret = ((*iter).first);
                break;
            }
            iter++;
        }
    }
    else
    {
        while(iter != conInfo.end())
        {
            if (iter->second->u.tcpInfo == dInfo->u.tcpInfo)
            {
                ret = ((*iter).first);
                break;
            }
            iter++;
        }

        Unlock();
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ostream&
operator<< (ostream& os, const ConnectionTable& table)
{
    table.Print(os);
    return os;
}


