
#include "CMAPICommon.h"
#include "CMApiComp.h"
#include "ErrorResp.h"
using namespace std;

int CMApiComponents::SendCMgrRequest(DynDictionaryRequest& Req, DynDictionaryResponse* Resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    m_CmgrObj->CMgrDTFConfig(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        Resp->set_responseid(retVal);
        ::ErrorDetails* Err = Resp->add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
    }
    if (Resp != NULL)
    {
        std::string StrVal;
        m_CMgrResponse->Get(StrVal);
        if (!StrVal.empty())
        {
            Resp->ParseFromString(StrVal);
            if (Resp->has_responseid())
            {
                retVal = Resp->responseid();
            }
        }
    }
    return retVal;
}

int CMApiComponents::IsResponseOK(DynDictionaryResponse *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL ||
            Resp->responseid() != CMAPI_SUCCESS )
    {
        DynDictionaryResponse ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_SRVERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        delete lCookie;
        if ( Resp != NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrorResponse.SerializeToString(&StrVal);
        }

        m_CMgrResponse->Set(StrVal);
    }
    return retVal;
}

int CMApiComponents::CMgrDTFConfigRespCbk(DynDictionaryResponse *Resp)
{
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        delete lCookie;
        m_CMgrResponse->Set(StrVal);
    }
    return retVal;
}

int CMApiComponents::LoadDictionary(string DictionaryName)
{
    int retVal = CMAPI_SUCCESS;
    // debug statement here
    if (DictionaryName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        DynDictionaryRequest Req;
        Req.set_requestid(LOAD_DICTIONARY);

        Dictionary* dictionary = Req.add_dictionaries();
        dictionary->set_dictionaryname(DictionaryName);
        retVal = SendCMgrRequest(Req);
    }

    return retVal;

}

int CMApiComponents::UnLoadDictionary(string DictionaryName)
{
    int retVal = CMAPI_SUCCESS;
    // debug statement here
    if (DictionaryName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        DynDictionaryRequest Req;
        Req.set_requestid(UNLOAD_DICTIONARY);

        Dictionary* dictionary = Req.add_dictionaries();
        dictionary->set_dictionaryname(DictionaryName);
        retVal = SendCMgrRequest(Req);
    }

    return retVal;
}

int CMApiComponents::ShowDictionary(string DictionaryName, Dictionary& dictionary)
{
    int retVal = CMAPI_SUCCESS;
    // debug statement here
    if (DictionaryName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        DynDictionaryRequest Req;
        Req.set_requestid(GET_DICTIONARY);

        Dictionary* dictionary = Req.add_dictionaries();
        dictionary->set_dictionaryname(DictionaryName);
        DynDictionaryResponse Response;
        retVal = SendCMgrRequest(Req, &Response);
        if (retVal == CMAPI_SUCCESS)
        {
            if (Response.dictionaries_size() > 0)
            {
                dictionary->CopyFrom(Response.dictionaries(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::LoadTransformPlugin(string PluginName, string FromDictionary,
        string ToDictionary, string ConfigFileName)
{
    int retVal = CMAPI_SUCCESS;
    // debug statement here
    if (PluginName.empty() || FromDictionary.empty() ||
            ToDictionary.empty() || ConfigFileName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        DynDictionaryRequest Req;
        Req.set_requestid(LOAD_PLUGIN);

        TransformPlugin* plugin = Req.add_plugins();
        plugin->set_pluginname(PluginName);
        plugin->set_fromdictionary(FromDictionary);
        plugin->set_todictionary(ToDictionary);
        plugin->set_configfilename(ConfigFileName);
        retVal = SendCMgrRequest(Req);
    }
    return retVal;

}

int CMApiComponents::UnLoadTransformPlugin(string PluginName)
{
    int retVal = CMAPI_SUCCESS;
    // debug statement here
    if (PluginName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        DynDictionaryRequest Req;
        Req.set_requestid(LOAD_PLUGIN);

        TransformPlugin* plugin = Req.add_plugins();
        plugin->set_pluginname(PluginName);
        retVal = SendCMgrRequest(Req);
    }
    return retVal;
}

int CMApiComponents::ShowTransformPlugin(string PluginName, TransformPlugin& plugin)
{
    int retVal = CMAPI_SUCCESS;
    // debug statement here
    if (PluginName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
    } else {
        DynDictionaryRequest Req;
        Req.set_requestid(GET_PLUGIN);

        TransformPlugin* Tplugin = Req.add_plugins();
        Tplugin->set_pluginname(PluginName);
        DynDictionaryResponse Response;
        retVal = SendCMgrRequest(Req, &Response);
        if (retVal == CMAPI_SUCCESS)
        {
            if (Response.plugins_size() > 0)
            {
                plugin.CopyFrom(Response.plugins(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SendDTFConfigResult(DynDictionaryResponse *Resp,CMAPIRes *result)
{
    CLOG_DEBUG("DTF Config ReportResult");
    string StrVal;
    if (Resp != NULL)
    {
        Resp->SerializeToString(&StrVal);
    }
    m_CMgrResponse->Set(StrVal);
    result->set_responsecode(CMAPI_SUCCESS);
    return 0;

}

