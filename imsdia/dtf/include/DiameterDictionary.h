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
#ifndef _DIAMETER_DICTIONARY_H_
#define _DIAMETER_DICTIONARY_H_

#include "DiameterDictionaryStats.h"

// using namespace eAccelero;
// using namespace std;
namespace diameter {

/*
 * This is an interface for Diameter Dictionary.
 * Standard and Custom dictionaries shall be derived from this.
 * This is the wrapper that shall be used to decode application specific messages
 * by components like RulesEngine.
 */

class DiameterDictionary: public eAccelero::PluginObject
{
public:
    DiameterDictionary(std::string dictName,unsigned int applicationId,
            unsigned int dictionaryId):PluginObject(dictName)
    { 
        this->DictionaryId = dictionaryId;
        this->ApplicationId = applicationId;                
    }
    ~DiameterDictionary() 
    {
        /* delete all dictionary stats */
        std::map<uint32_t,diameter::DiameterDictionaryStats*>::iterator it = DictStatsMap.begin();
        for(; it != DictStatsMap.end(); ++it)
        {
            if(it->second != NULL)
            {
                delete it->second;
            }
            it->second = NULL;
            DictStatsMap.erase(it);
        }
    }

    /*
     * This function returns a Command Object based on the Command Code and other params.
     */
    virtual Command* createCommandObject(unsigned int CommandCode,const CommandImpl& ) = 0;
    virtual Command* createCommandObject(unsigned int CommandCode,bool isRequest) = 0;
    virtual Command* createCommandObject(const unsigned char* buf,int length) = 0;

    virtual const CommandAttribute* getCommandAttribute(unsigned int CommandCode,bool isRequest)= 0 ;

    virtual void Initialize(){}
    virtual int Configure(void* conf) {return 0;}
    virtual void Terminate(){}

    /*
     * Returns the dictionary Id for this dictionary.
     */
    unsigned int getDictionaryId()
    {
        return this->DictionaryId;
    }

    /*
     * Sets the Dictionary Id for this dictionary.
     */
    void setDictionaryId(unsigned int dictId)
    {
        this->DictionaryId = dictId;
    }

    /*
     * Returns the Application Id for this dictionary.
     */
    unsigned int getApplicationId()
    {
        return this->ApplicationId;
    }

    /*
     * Sets the Application Id for this dictionary.
     */
    void setApplicationId(unsigned int appId)
    {
        this->ApplicationId = appId;
    }

    /*
     * Returns the human readable Dictionary Name.
     */
    const std::string& getDictionaryName()
    {
        return(GetPluginName());
    }

    /*
     * Sets the Human readable dictionary name for this dictionary.
     * This would be ideally part of the configuration.
     */
    void setDictionaryName(std::string dictName)
    {
        this->DictionaryName = dictName;
    }

    std::map<uint32_t,diameter::DiameterDictionaryStats*> DictStatsMap;

private:

    /*
     * Used to store dictionary Id for a specific Diameter Dictionary.
     */
    unsigned int DictionaryId;
    unsigned int ApplicationId;
    std::string DictionaryName;

};

}

#endif
