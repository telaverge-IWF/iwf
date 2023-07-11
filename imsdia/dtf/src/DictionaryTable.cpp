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
 * Log: $Log $  
 ****************************************************************************/


#include <string>
#include <iostream>
#include <map>
#include <DTFLog.h>
#include <Sync.h>
#include <PluginObj.h>
#include <diameter/Command.h>
#include <DiameterDictionary.h>
#include <DictionaryTable.h>

using namespace eAccelero;
namespace diameter {

    //Methods for the dictionary Table

    /*
     * This method is used to get the Dictionary object, given the dictionary id. 
     */
    DiameterDictionaryRef DictionaryTable::fetchDictionaryObject(unsigned int dictionaryId)
    {
        if(dictionaryId >= MAX_DICTIONARIES)
        {
            DTF_ERR(("Dictionary with Dictionary Id %d is invalid.",dictionaryId));
            throw PluginException("Invalid Dictionary Id");
        }
        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);      
        DiameterDictionaryRef dictRef = m_dictionaries[dictionaryId];
        if(dictRef.IsNull())
        {
            DTF_ERR(("Dictionary Object is NULL with Dictionary Id %u  [ or not found in the table ]",dictionaryId));
            throw PluginException("Dictionary not found");
        }
        //DTF_DBG(("Found the dictionary for Id %u in the dictionary table.",dictionaryId));
        return dictRef;
    }

    /*
     * This method is used to get the Dictionary object, given the dictionary name.
     */
    DiameterDictionaryRef DictionaryTable::fetchDictionaryObject(std::string dictionaryName)
    {
        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);      
        unsigned int dictionaryId = 0;
        map<string,unsigned int>::iterator it;

        it = m_dictStrMap.find(dictionaryName);
        if(it ==  m_dictStrMap.end())
        {
            //Dictionary is not loaded.         
            DTF_ERR(("Dictionary %s is not loaded.",dictionaryName.c_str()));
            throw PluginException("Dictionary not found");
        }
        dictionaryId = it->second;
        if(dictionaryId >= MAX_DICTIONARIES)
        {
            DTF_ERR(("Dictionary with Dictionary Id %d is invalid.",dictionaryId));
            throw PluginException("Invalid Dictionary Id");
        }

        DiameterDictionaryRef dictRef = m_dictionaries[dictionaryId];
        if(dictRef.IsNull())
        {
            DTF_ERR(("Dictionary  %s is not found in the dictionary table"));
            throw PluginException("Dictionary not found");
        }
        return dictRef;
    }

    /*
     * Given the dictionary name, this method loads the dictionary into the table
     * and creates the dictionary object. If the object is already loaded, this does nothing.
     * Returns 0 in case of any error.
     */
    unsigned int DictionaryTable::loadDictionary(std::string dictName,bool& isNewlyLoaded)
    {
        PluginObject* obj = NULL;
        if(dictName.empty())
        {
            DTF_ERR(("Dictionary Name is NULL"));
            return 0;
        }
        map<string,unsigned int>::iterator it;
        pair<map<string,unsigned int>::iterator,bool> ret;

        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);      

        it = m_dictStrMap.find(dictName);
        if(it !=  m_dictStrMap.end())
        {
            //Dictionary is already loaded.         
            DTF_WRN(("Dictionary %s is already loaded.",(char*)dictName.c_str()));
            return it->second;
        }
        //TODO: Need to define an enum/macro for Plugin Type.
        try
        {
            obj= PluginLoader::LoadPlugin(dictName, "dict");
        }
        catch (eAccelero::PluginException& x) //Fixing Big parameter passing by value
        {
            DTF_ERR(("PluginException:: %s",x.what()));
            return 0;
        }
        isNewlyLoaded = true;
        DiameterDictionaryRef dictObjRef = dynamic_cast<DiameterDictionary*>(obj);

        unsigned int dictId = dictObjRef->getDictionaryId();

        //Store the Ref in Array indexed with Dictionary Id.
        m_dictionaries[dictId] = dictObjRef;    

        ret = m_dictStrMap.insert(pair<string,unsigned int>(dictName,dictId));
        if(ret.second == false)
        {
            DTF_WRN(("Dictionary %s already exists in the table",(char*)dictName.c_str()));
            return dictId;
        }
        //Initialize the dictionary
        dictObjRef->Initialize();
        return dictId;
    }
    
    /*
     * This method unloads the dictionary object from the table and the corresponding
     * library from the memory. This method will make sure that the dictionary object
     * is not referenced by any module at the time of unloading.
     */
    void DictionaryTable::unloadDictionary(std::string dictName)
    {
        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);      
        if(dictName.empty())
        {
            DTF_ERR(("Dictionary Name is null."));
            return;
        }
        map<string,unsigned int>::iterator it;

        it = m_dictStrMap.find(dictName);
        if(it ==  m_dictStrMap.end())
        {
            //Dictionary is not loaded.         
            DTF_WRN(("Dictionary %s is not loaded.",(char*)dictName.c_str()));
            return;
        }
        m_dictionaries[it->second] = NULL;
        m_dictStrMap.erase(it); 
        return;
    }

    bool DictionaryTable::fetchDictionaryObject(unsigned int dictionaryId,
            DiameterDictionaryRef& dictRef)
    {
        try
        {
            dictRef = this->fetchDictionaryObject(dictionaryId);
            return true; 
        }
        catch (eAccelero::PluginException &e)
        {
            DTF_ERR(("DictionaryID not found PluginException:: %s",e.what()));
            return false;
        }
    }
    DiameterDictionaryRef DictionaryTable::operator[] (const int index)
    {   
        bool dictMatch = false;
        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);

        DiameterDictionaryRef dictRef;
        std::map<std::string,unsigned int>::iterator it = m_dictStrMap.begin();
        for( ; it != m_dictStrMap.end(); it++)
        {  
            if(it->second == index)
            {   
                dictMatch = true;
                try 
                {   
                    dictRef = this->fetchDictionaryObject(it->first);
                    return dictRef;
                }   
                catch(eAccelero::PluginException &e)
                {   
                    DTF_ERR(("Exception %s",e.what()));
                    throw PluginException("Invalid Dictionary"); 
                }
                 
            }   
        }
        if(dictMatch == false)
        {
            DTF_ERR(("Dictionary Id %d not found",index));
            throw PluginException("Invalid Dictonary");
       }
    }

    unsigned int DictionaryTable:: GetDictionaryTableSize()
    {
        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);
        return m_dictStrMap.size();
    }
    void  DictionaryTable::GetDictionaryIds(unsigned int dictIds[])
    {
        int index = 0;
        //Acquire the Scoped Lock for the table.
        Mutex::ScopedMutex sMutex(m_lock);
        std::map<std::string,unsigned int>::iterator it = m_dictStrMap.begin();
        for( ; it != m_dictStrMap.end(); it++)
        {
            dictIds[index] = it->second;
            index++;
        }

    }
}

