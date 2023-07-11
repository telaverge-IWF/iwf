/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************/
#ifndef _DICTIONARY_TABLE_H_
#define _DICTIONARY_TABLE_H_

#include "Ref.h"
#include "PluginObj.h"


namespace diameter {

#define MAX_DICTIONARIES 256
/*
 */
typedef eAccelero::Reference<DiameterDictionary,eAccelero::PluginObjRP> DiameterDictionaryRef;

class DictionaryTable
{
public:
    DictionaryTable():m_lock(PTHREAD_MUTEX_RECURSIVE) {}
    ~DictionaryTable() {}

    //Methods for the dictionary Table

    DiameterDictionaryRef fetchDictionaryObject(unsigned int dictionaryId);
    DiameterDictionaryRef fetchDictionaryObject(std::string dictionaryName);

    unsigned int loadDictionary(std::string dictName,bool& isNewlyLoaded);
    void unloadDictionary(std::string dictName);
   
    bool fetchDictionaryObject(unsigned int dictionaryId, DiameterDictionaryRef& dictRef);
    unsigned int  GetDictionaryTableSize();
    void  GetDictionaryIds(unsigned int dictIds[]);
    DiameterDictionaryRef operator[] (const int index);

private:

    DiameterDictionaryRef m_dictionaries[MAX_DICTIONARIES];
    eAccelero::Mutex m_lock;
    std::map<std::string,unsigned int> m_dictStrMap;

};

}

#endif
