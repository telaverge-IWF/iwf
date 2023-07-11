/* ********************************-*-H-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#ifndef  __HASHINTERFACE_H__
#define  __HASHINTERFACE_H__

#include <string.h>

using namespace eAccelero;
using namespace std;

 class KeyValue
 {
 public:
     KeyValue() {}
     KeyValue(KeyValue& Pair)
     {
         m_sKey = Pair.Get_HashKey();
         m_sValue << Pair.Get_HashValue();
     }

     ~KeyValue() {}


     void Set_HashKey(string& sKey)
     {
         m_sKey.assign(sKey);
     }

     string Get_HashKey(void)
     { 
         return  m_sKey;
     }  

     unsigned int Get_HashKeyLength(void)
     {
         if (!m_sKey.empty())
             return m_sKey.length();
         else
             return 0;
     }

     void Add_HashValue(string& sValue)
     {
         m_sValue << sValue << ";";
     }

     void Add_HashValue(unsigned int sValue)
     {
         m_sValue << sValue << ";" ;
     }

     void Add_HashValue(bool sValue)
     {
         if (sValue == true)
             m_sValue << "true" << ";";
         else
             m_sValue << "false" << ";";
     }

     string Get_HashValue(void)
     {
         return (std::string) m_sValue.str();
     }

     unsigned int Get_HashValueLength(void)
     {
         if (!(m_sValue.str()).empty())
             return m_sValue.str().length();
         else
             return 0;
     }
     
 private:
   std::string       m_sKey;
   std::stringstream m_sValue;
 }; // NodeStats

 // Interface for accessing hash table implementor.
 class HashInterface 
 {
 public:
     // Method to handle the initialization of cache server and required
     // procedure
     virtual bool InitializeCache(void) = 0;
     
     // Method to get total number of records/keys present in the cache
     virtual int GetTotalRecordsNum(void) = 0;
     
     // Method to store a Key:Value pair into the cache
     virtual void StoreEntry(KeyValue kvl) = 0;
     
     // Method to retrieve a Key:Value pair from the cache
     virtual KeyValue GetEntry(std::string key) = 0;
     
     // Method to delete Key:Value pair from the cache
     virtual bool DeleteEntry(std::string key) = 0;
 };


#endif  //  __HASHINTERFACE_H__

