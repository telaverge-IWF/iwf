/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: dia_cache_table.cpp,v $
 * LOG: Revision 1.3.42.2  2013/04/12 04:15:46  vsarath
 * LOG: Logs improvement
 * LOG:
 * LOG: Revision 1.3.42.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.3  2010/07/07 08:24:46  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 1.2  2009/02/05 10:00:22  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 1.1  2009/02/03 10:19:46  ssaxena
 * LOG: Added a new src file for Redirect Agent functionality.
 * LOG:
 * ID: $Id: dia_cache_table.cpp,v 1.3.42.2 2013/04/12 04:15:46 vsarath Exp $
 ****************************************************************************/
#ident "$Id: dia_cache_table.cpp,v 1.3.42.2 2013/04/12 04:15:46 vsarath Exp $"

#include <dia_err.h>
#include <dia_cache_table.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

ITS_Mutex CacheTable::guard(0);
ITS_Mutex CacheTable::lock(0);

static CacheTable *cTable = NULL;

static int PrintCacheEntry( ITS_INT context,
                            ITS_POINTER data,
                            void *in,
                            void *out );

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
CacheTable*
CacheTable::GetCacheTable()
{
    if (cTable == NULL)
    {
        ITS_ASSERT(CacheTable::guard.Acquire() == ITS_SUCCESS);
 
        cTable  = new CacheTable();
 
        CacheTable::guard.Release();
    }
 
    return cTable;
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
CacheTable::CacheTable()
{

    if ((hTable = HASH_CreateTable()) == NULL)
    {
        DT_ERR(("HashTables: Hash create failed\n"));
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
CacheTable::~CacheTable()
{
    Lock();
 
    HASH_DeleteTable(hTable);
 
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
CacheTable::Lock() const
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
CacheTable::Unlock() const
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
int
CacheTable::InsertEntry( const char *key,
                         ITS_UINT duration,
                         CACHE_ENTRY *&cEntry )
{
    ITS_INT ret;
    CACHE_ENTRY *tmp = NULL;
    ITS_INT hash = HASH_MakeKey( key, strlen(key) );

    DT_DBG(("InsertEntry:: key value : %s  key size : %d", key, strlen(key)));
    DT_DBG(("InsertEntry:: Hash value : %d", hash));

    Lock();

    ret = HASH_FindEntry( hTable,
                          CACHE_TABLE_ID,
                          hash,
                          (ITS_POINTER*) &tmp );

    if ( ret == ITS_SUCCESS )
    {
         DT_DBG(("InsertEntry:: Entry Aready Present for Key : %s", key));
         Unlock();
         return !ITS_SUCCESS;
    }

    StartTimer( CACHE_TIMER, key, duration, cEntry );

    ret = HASH_AddEntry( hTable,
                         CACHE_TABLE_ID,
                         hash,
                         (ITS_POINTER)cEntry );

    if ( ret !=  ITS_SUCCESS)
    {
        DT_ERR(("Insert failed\n"));
        StopTimer( CACHE_TIMER, cEntry);
        free(cEntry);
        Unlock();
        return ITS_ENOMEM;
    }
    DT_DBG(("Entry Inserted Successfully\n"));

    Unlock();
    return ITS_SUCCESS;
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
CacheTable::FindEntry( const char *key, CACHE_ENTRY **cEntry )
{
    ITS_INT ret;
    ITS_INT hash = HASH_MakeKey( key, strlen(key) );

    DT_DBG(("FindEntry:: key value : %s  key size : %d", key, strlen(key)));
    DT_DBG(("FindEntry:: Hash value : %d", hash));

    Lock();

    ret = HASH_FindEntry( hTable,
                          CACHE_TABLE_ID,
                          hash,
                          (ITS_POINTER *)cEntry );

    if ( ret == ITS_SUCCESS )
    {
         DT_DBG(("FindEntry:: Entry is Present for Key : %s\n", key));

         Unlock();
         return true;
    }
    else
    {
         DT_DBG(("FindEntry:: Entry is Not Present for Key : %s\n", key));

         Unlock();
         return false;
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
int
CacheTable::RemoveEntry( const char *key )
{
    ITS_INT ret;
    CACHE_ENTRY *tmp = NULL;
    ITS_INT hash = HASH_MakeKey( key, strlen(key) );

    DT_DBG(("RemoveEntry:: key value : %s  key size : %d", key, strlen(key)));
    DT_DBG(("RemoveEntry:: Hash value : %d", hash));

    Lock();

    ret = HASH_FindEntry( hTable,
                          CACHE_TABLE_ID,
                          hash,
                          (ITS_POINTER *)&tmp );

    if ( ret == ITS_SUCCESS )
    {
         DT_DBG(("RemoveEntry:: Entry is Present for Key : %s", key));

         free((void*) DIA_CACHE_DEST_HOST(tmp));
         free(tmp);
         ret = HASH_DeleteEntry( hTable, CACHE_TABLE_ID, hash );
    }
    else
    {
         DT_DBG(("RemoveEntry:: Entry is Not Present for Key : %s", key));
    }
 
    Unlock();
    return ret;
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
CacheTable::IterateTable( void *in, void *out, HASH_IterateEntryProc proc) const
{
    HASH_VTableIterate( hTable,
                        CACHE_TABLE_ID,
                        (void*)in,
                        (void*)out,
                        proc );
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
int
CacheTable::GetTableSize() const
{
    ITS_UINT size = HASH_Size(hTable);
    return size;
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
CacheTable::Print(std::ostream& os) const
{
    os << "------------------------------------------------------------" << endl;
    os << "-- Cache Table Begin --" << endl;
    os << "------------------------------------------------------------" << endl;
    os << "Size: <" << GetTableSize() << ">" << endl;
    os << endl;
    os << endl;
    os << "Entries:" << endl;
    os << "--------------------------------------------------" << endl;
    IterateTable((void *)&os, NULL, (HASH_IterateEntryProc)PrintCacheEntry);
    os << endl;
    os << endl;
    os << "------------------------------------------------------------" << endl;
    os << "-- Cache Table End   --" << endl;
    os << "------------------------------------------------------------" << endl;
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
static int
PrintCacheEntry(ITS_INT context,ITS_POINTER data, void *in, void *out)
{
    std::ostream *os = (std::ostream *)in;
    CACHE_ENTRY *cEntry = ( CACHE_ENTRY *)data;

    *os<< "Redirected Dest Host :" << cEntry->destHost<<endl;
    *os<< "Max Cache Timer      :" << cEntry->cacheTimer<<endl;
    *os << "--------------------------------------------------" << endl;

    return (ITS_SUCCESS);
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
operator<< (ostream& os, const CacheTable& table )
{
    table.Print(os);
    return os;
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
int
CacheTable::StartTimer( DIA_TIMER_TYPE type,
                        const char *key,
                        ITS_UINT duration,
                        CACHE_ENTRY *&entry )
{
    DIA_TIMER_CTXT timerCtxt;
    timerCtxt.timerType = type;
    //Correcting Copy into fixed size buffer
    strncpy(timerCtxt.data.cacheInfo.key, key, ITS_DIA_TIMER_CXT_SIZE-1);

    DIA_CACHE_MAX_TIME(entry) = TIMERS_StartTimer( DIASTACK_TQ_INST,
                                                   duration,
                                                   &timerCtxt,
                                                   sizeof(DIA_TIMER_CTXT) );
    DT_DBG(("CacheTable::StartTimer :  %s  Id = %d\n",
                          TIMER_TO_TEXT(type), DIA_CACHE_MAX_TIME(entry) ));

    return (ITS_SUCCESS);
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
int
CacheTable::StopTimer(DIA_TIMER_TYPE type, CACHE_ENTRY *entry)
{
    DT_DBG(("StopTimer Type = %s Id = %d",
              TIMER_TO_TEXT(type),  DIA_CACHE_MAX_TIME(entry) ));

    if ( DIA_CACHE_MAX_TIME(entry) != TIMER_BAD_SERIAL )
    {
        TIMERS_CancelTimer(DIA_CACHE_MAX_TIME(entry));
        DIA_CACHE_MAX_TIME(entry) = TIMER_BAD_SERIAL;
    }
    return (ITS_SUCCESS);
}

