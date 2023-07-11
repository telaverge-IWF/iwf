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
#include <stdint.h>
#include <string>
#include <json/json.h>
#include <DTFLog.h>
#include <its_dia_config.h>
#include <dia_cmn.h>
#include <Sync.h>
#include <dia_msg_flow.h>
#include <PluginObj.h>
#include <DiameterTransformer.h>
#include <DiameterDictionary.h>
#include <DictionaryTable.h>
#include <dtf.h>
#include <ThreadSpec.h>
#include "Logger.h"

using namespace eAccelero;

namespace diameter {

DTF::DTF(): m_syslogChannel("DTF", (LOG_PID),LOG_LOCAL6)
            //m_fileLogChannel("DTF.log", getenv("DRE_LOG_DIR"))
{
   //Initializing Uninitialized Pointer Value
   m_logger = NULL;
}

DTF::~DTF()
{   
    if(m_logger != NULL)
    {
        //Object allocated in InitLog()
        delete m_logger;
    }
}

Logger& DTF::GetLogger()
{
    return *m_logger;
}

void DTF::InitLog()
{
    char *jsonFile = getenv("DRE_JSON");
    if (jsonFile == NULL )
    {
        DLOG_CRITICAL("DRE_JSON is not exported");
        exit(0);
    }
    DLOG_DEBUG("DRE_JSON=%s",jsonFile);

    std::ifstream doc(jsonFile);

    if(!(m_jsonConfigFileReader.parse(doc,m_jsonRoot)))
    {
        std::cout  << "DTF::Failed to parse dre.json configuration\n"
            << m_jsonConfigFileReader.getFormattedErrorMessages();
    }
    const Json::Value dreLogging = m_jsonRoot["Logging"];
    unsigned int logChannel = dreLogging[0]["DTF"]["logChannel"].asInt();
    unsigned int logLevel   = dreLogging[0]["DTF"]["logLevel"].asInt();

    m_logger = new Logger("DTF");

    if(logChannel == Logger::EACC_CHANNEL_SYSLOG)
    {
        m_logger->SetLogChannel(&m_syslogChannel);
    }
    m_logger->SetLevel((Logger::Level)(int)logLevel);
}

void DTF::SetLogChannel(const unsigned int channel)
{
    if(channel == Logger::EACC_CHANNEL_SYSLOG)
    {
        this->GetLogger().SetLogChannel(&m_syslogChannel);
    }
    else if (channel == Logger::EACC_CHANNEL_FILE)
    {
        //commented to avoid files created in /var/dre/logs
        //this->GetLogger().SetLogChannel(&m_fileLogChannel);
    }
    else
    {
        this->GetLogger().SetLogChannel(ConsoleLogChannel::Instance());
    }
}

void DTF::SetLogLevel(const unsigned int level)
{
    this->GetLogger().SetLevel((Logger::Level)(int)level);
}

/*
 * This function throws a PluginException if no transformation plugin is found for the provided 
 * in and out dictionary-id's.
 */
int DTF::CheckAndInvokeTransform(DiaMsgFlow& inMsg,unsigned int outDictId, DiaMsgFlow** outMsg)
{
    //For DTF Logging
    ScopedLogger scopedLogger(this->GetLogger());

    unsigned int inDictId = inMsg.GetDictId();
    DLOG_DEBUG("DTF::CheckAndInvokeTransform: InDictId is %d and outDictId is %d",inDictId,outDictId);
    if((inDictId == outDictId) || (outDictId == 0))
    {
        DLOG_DEBUG("Dict id's are same or outDictId is 0, hence no transformation required.");
        return TRANSFORM_NOT_DONE;
    }

    unsigned int CommandCode = inMsg.getCommandCode();

    if(inMsg.isRequest())
    {
        switch(CommandCode)
        {
            case 318:
            case 320:
            case 322:
            {
                DLOG_DEBUG("Request msg remains the same between releases.");
                return TRANSFORM_NOT_DONE;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else
    {
        switch(CommandCode)
        {
            case 317:
            case 320:
            case 321:
            case 322:
            case 323:
            {
                DLOG_DEBUG("Answer msg remains same between the releases.");
                return TRANSFORM_NOT_DONE;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    uint64_t key = createTransformerKey(inDictId,outDictId);
    std::map<uint64_t,TransformerObjRef>::iterator it;
    TransformerObjRef transfObj; 

    //Acquire lock for the table.
    eAccelero::Mutex::ScopedMutex sMutex(m_tableLock);
    it = m_transformerTable.find(key);
    if(it ==  m_transformerTable.end())
    {
        //Transformation Plugin is not loaded.
        DLOG_ERROR( "Transformation Plugin for dictionary Id's %u and %u is not loaded."
                    ,inDictId ,outDictId);  
        return TRANSFORM_PLUGIN_NOT_FOUND;
    }
    transfObj = it->second;

    /*Release the Lock */
    sMutex.unlock();

    try
    {
    transfObj->transform(inMsg,outDictId,outMsg);
    inMsg.SetDictId(outDictId);
    } catch (diameter::NoSuchAttributeException& e) {//Fixing Big parameter passing by valu
            DLOG_ERROR( "Exception Caught: %s , Error Cause: %s ",
                            e.name(), e.what());
            return TRANSFORM_DECODE_ERR;
    } catch (diameter::WrongCommandTypeException& e) {//fixing Big parameter passing by valu
            DLOG_ERROR("Exception Caught: %s , Error Cause: %s ",
                            e.name(), e.what());
            return TRANSFORM_INVALID_IN_MSG;
    } catch (diameter::UnknownTypeException& e) {//fixing Big parameter passing by valu
            DLOG_ERROR("Exception Caught: %s , Error Cause: %s ",
                            e.name(), e.what());
            return TRANSFORM_INVALID_IN_MSG;
    } catch (diameter::CodecException& e) {//fixing Big parameter passing by valu
            DLOG_ERROR("Exception Caught: %s , Error Cause: %s ",
                            e.name() ,e.what());
            return e.errcode();
    } catch (diameter::CodecExceptionToApp& e) {//fixing Big parameter passing by valu
            DLOG_ERROR("Exception Caught: %s , Error Cause: %s ",
                            e.name() ,e.what());
            return e.errcode();
    } catch (...) {
            DLOG_ERROR("Exception Caught: Error Cause: ");
            return TRANSFORM_FAILURE;
    }
    return TRANSFORM_SUCCESS;
}

/*
 *
 */
int DTF::LoadTransformerObject(unsigned int dict1,unsigned int dict2,std::string pluginName, std::string Config)
{
    std::map<uint64_t,TransformerObjRef>::iterator it;
    TransformerObjRef transfObjRef; 
    uint64_t key = createTransformerKey(dict1,dict2);

    //Acquire lock for the table.
    eAccelero::Mutex::ScopedMutex sMutex(m_tableLock);
    it = m_transformerTable.find(key);
    if(it !=  m_transformerTable.end())
    {
        //Transformation Plugin is already loaded.
        DLOG_WARNING("Transformation Plugin %s is already loaded.",(char*)pluginName.c_str());
        return ITS_SUCCESS;
    }
    pair<map<uint64_t,TransformerObjRef>::iterator,bool> ret;
    PluginObject* obj= PluginLoader::LoadPlugin(pluginName, "transformer");
    transfObjRef = static_cast<DiameterTransformer*>(obj);

    ret = m_transformerTable.insert(pair<uint64_t,TransformerObjRef>(key,transfObjRef));
    if(ret.second == false)
    {
        DLOG_WARNING("Transformation Plugin %s already Exists,hence returning.",(char*)pluginName.c_str());
        return ITS_SUCCESS;
    }

    /*Release the Lock */
    sMutex.unlock();

    transfObjRef->Initialize();

    stringstream ConfigDir ;
    ConfigDir << itsDiaConfig.getpluginpathname() << pluginName << ".json";

    stringstream Configfile;
    Configfile << itsDiaConfig.getpluginpathname() <<Config;

    //ConfigDir << "/home/code/sandbox/B-DRE-0212-01/dre/transformPlugins/s6ar8_s6ar10_transform/config/" << pluginName << ".json";
    DLOG_DEBUG("Plugin Configuration Directory: %s",itsDiaConfig.getpluginpathname());


    bool eFlag = false;
    Json::Value root;

    try
    {
        root = parsePluginConfig(Configfile.str());
    }

    catch(eAccelero::PluginException& x) //fixing Big parameter passing by valu
    {
        DLOG_ERROR("PluginException::%s ", x.what());
        DLOG_ERROR("Failed to parse primary config file, trying secondary file...");
        eFlag = true;
    }
    
    if (eFlag == true)
    {
        try
        {
            root = parsePluginConfig(ConfigDir.str());
            DLOG_DEBUG("Secondary config file parsed successfully");
            eFlag = false;
        }

        catch(eAccelero::PluginException &x)
        {
            DLOG_ERROR("PluginException::%s ", x.what());
        }

    }

    if(root.isNull())
    {
        DLOG_WARNING("Failed to parse Plugin Configuration file.");
    }

    int configRet = 0;  

    if (eFlag == false)
    {
        try{

            int configRet = transfObjRef->Configure(&root);

        }catch(std::runtime_error e) {
            DLOG_CRITICAL("Exception caught while parsing Json Configuration File: %s",e.what());
            throw PluginException("Exception caught while parsing Json Configuration File");
        }
        if(configRet!=0)
        {
            DLOG_CRITICAL("Failed to load  Plugin Config");
            throw PluginException("Failed to load Plugin Configuration from Config file.");
        }
        return ITS_SUCCESS;
    }

    return !ITS_SUCCESS;
}


/*
 *
 */
void DTF::UnloadTransformerObject(unsigned int dict1,unsigned int dict2)
{
    uint64_t key = createTransformerKey(dict1,dict2);
    std::map<uint64_t,TransformerObjRef>::iterator it;

    //Acquire lock for the table.
    Mutex::ScopedMutex sMutex(m_tableLock);
    it = m_transformerTable.find(key);
    if(it ==  m_transformerTable.end())
    {
        //Transformation Plugin is not loaded loaded.
        DLOG_ERROR("Transformation Plugin for dict Id's %u and %u is not loaded"
                    ,dict1,dict2);
        return;
    }
    it->second = NULL;  
    m_transformerTable.erase(it);
    return;
}


/*
 *This function assumes that dict1 is not equal to dict2.
 */
uint64_t DTF::createTransformerKey(unsigned int dict1, unsigned int dict2)
{
    uint64_t transformerKey = 0;
    if(dict1 < dict2)
    {
        transformerKey = dict2;
        transformerKey  = transformerKey << 32 | dict1;
    }
    else
    {
        transformerKey = dict1 ;
        transformerKey = transformerKey << 32 | dict2;
    }
    DLOG_DEBUG("Key to the transformer table is %u.",transformerKey);
    return transformerKey;
}

Json::Value DTF::parsePluginConfig(std::string cfgFileName) 
{

    Json::Reader r;
    Json::Value root;
    std::ifstream doc(cfgFileName.c_str());         
    bool ret = r.parse(doc,root);
    if(ret == false)
    {
        DLOG_CRITICAL("Parsing of JSON Config file failed.");
        throw PluginException("Parsing of JSON Config file failed.");
    }
    return root;
}


unsigned int DTF::getDictIdForAppId(unsigned int appId,diameter::DictionaryTable& dictTable
        ,unsigned int dictIds[])
{

    int i;
    for(i =0;i < MAX_DICT_IDS_PER_PEER ; i++)
    {
        if(dictIds[i] == 0)
        {
            DT_DBG(("Dictionary id is 0..hence continuing."));
            continue;
        }
	try
        {
           DiameterDictionaryRef dictRef = dictTable.fetchDictionaryObject(dictIds[i]);        
           if(dictRef->getApplicationId() == appId)
           {
              DT_DBG(("Found the Dictionary id %d for the Application id %d.",dictIds[i],appId));
              return dictIds[i];
           }
	}catch(PluginException& e) //fixing Big parameter passing by value
	{
	   DT_ERR(("Plugin Exception Caught %s.",e.what()));
	}
    }
    if(i == MAX_DICT_IDS_PER_PEER)
    {
        DT_ERR(("No matching Dictionary for application id %d is configured for the peer.",appId));
        return ITS_DIA_APP_UNSUPPORTED;
    }

    return ITS_DIA_APP_UNSUPPORTED;
}

bool DTF::validateDictIds(diameter::DictionaryTable& dictTable, unsigned int dictIds[])
{
    int i;
    for(i =0;i < MAX_DICT_IDS_PER_PEER ; i++)
    {
        if(dictIds[i] == 0)
        {
            //DTF_DBG(("Dictionary id is 0..hence continuing."));
            continue;
        }
        DiameterDictionaryRef dictRef = dictTable.fetchDictionaryObject(dictIds[i]);        
        if(dictRef.IsNull() )
        {
            DT_ERR(("Dictionary Object is NULL for dict id %d",dictIds[i]));
            return false;
        }
    }
    return true;
}

}
