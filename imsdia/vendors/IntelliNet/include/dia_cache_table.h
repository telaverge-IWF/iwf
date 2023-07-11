/*********************************-HPP-**************************************
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
 * LOG: $Log: dia_cache_table.h,v $
 * LOG: Revision 1.3  2009/02/05 09:49:29  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 1.2  2009/02/04 05:47:58  nvijikumar
 * LOG: Fix for compilation issue
 * LOG:
 * LOG: Revision 1.1  2009/02/03 10:11:13  ssaxena
 * LOG: Added a new header for Redirect Agent functionality.
 * LOG:
 * ID: $Id: dia_cache_table.h,v 1.3 2009/02/05 09:49:29 ssaxena Exp $
 ****************************************************************************/
#ident "$Id: dia_cache_table.h,v 1.3 2009/02/05 09:49:29 ssaxena Exp $"

#ifndef DIA_CACHE_TABLE_H
#define DIA_CACHE_TABLE_H 
 
#define DEST_HOST_MAX_SIZE                     64
#define CACHE_TABLE_ID                         0x74
 
typedef struct _cache_entry
{
    const char   *destHost;
    ITS_SERIAL   cacheTimer;
}CACHE_ENTRY;
 
 
#define DIA_CACHE_DEST_HOST(x) \
(((CACHE_ENTRY *)(x))->destHost)
 
#define DIA_CACHE_MAX_TIME(x) \
(((CACHE_ENTRY *)(x))->cacheTimer)
 
class CacheTable
{
public:
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Create an instance of CacheTable  
    *           
    ************************************************************************/
    static CacheTable* GetCacheTable();
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Insert Cache Entry in table.
    *           
    ************************************************************************/
    int InsertEntry( const char *key,
                     ITS_UINT duration,
                     CACHE_ENTRY *&cEntry );
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Entry Lookup using key
    *           
    ************************************************************************/
    bool FindEntry(const char *key, CACHE_ENTRY **cEntry);
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Remove a CacheEntry from Table using key.
    *
    ************************************************************************/
    int RemoveEntry(const char *key);
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Start a CacheEntry Lifetime Timer 
    *           
    ************************************************************************/
    int StartTimer( DIA_TIMER_TYPE type,
                    const char *key,
                    ITS_UINT duration,
                    CACHE_ENTRY *&entry );
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Stop a CacheEntry Lifetime Timer 
    *           
    ************************************************************************/
    int StopTimer( DIA_TIMER_TYPE type,
                   CACHE_ENTRY *cEntry );
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Print CacheTable 
    *           
    ************************************************************************/
    void Print(std::ostream& os) const;
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Return num of Entries in HashTable. 
    *           
    ************************************************************************/
    int GetTableSize() const;
 
 
/*.implementation:public,CacheTable
    ************************************************************************
    *  Purpose:
    *      Iterate over HashTable Entries. 
    *           
    ************************************************************************/
    void IterateTable( void *in, void *out,
                                   HASH_IterateEntryProc proc ) const;
 
    HASH_Table  hTable;
 
private:
 
     CacheTable();
    ~CacheTable();
 
    static its::ITS_Mutex lock;
    static its::ITS_Mutex guard;
 
    void Lock() const;
 
    void Unlock() const;
};
 
/* CacheTable ostream operator<< declaration. */
 
std::ostream& operator<< (std::ostream& os, const CacheTable & table);
 
#define CACHE_TABLE CacheTable::GetCacheTable()
 
#endif
