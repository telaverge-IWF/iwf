/*********************************-*CPP*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
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
 ****************************************************************************/
 
#include <dia_cmn.h>
#include <dia_msg_flow.h>
#include <dia_stack.h>
#include <dia_session_table.h>
#include <dia_ip_trans.h>

#include "dia_tracer.h"


#define GY_INTERFACE_APP_ID      4
#define GX_INTERFACE_APP_ID      16777238
#define GXX_INTERFACE_APP_ID     16777266
#define RX_INTERFACE_APP_ID      16777236
#define RFRO_INTERFACE_APP_ID    3
#define S6A_S6D_INTERFACE_APP_ID 16777251
#define S13_INTERFACE_APP_ID     16777252
#define S9_INTERFACE_APP_ID      16777267

enum TDIA_FIELD_TYPE
{
    DIA_FIELD_TYPE_NONE = 0,
    DIA_FIELD_TYPE_HDR  = 1,
    DIA_FIELD_TYPE_AVP  = 2,
    DIA_FIELD_TYPE_SPEC = 3
};

enum TDIA_HDR_CODE
{
    DIA_HDR_NONE = 0,
    DIA_HDR_VERSION = 1,
    DIA_HDR_MSG_LEN = 2,
    DIA_HDR_R_BIT = 3,
    DIA_HDR_P_BIT = 4,
    DIA_HDR_E_BIT = 5,
    DIA_HDR_T_BIT = 6 ,
    DIA_HDR_CMD_CODE = 7,
    DIA_HDR_APP_ID   = 8,
    DIA_HDR_H2H      = 9,
    DIA_HDR_E2E      = 10
};

enum TDIA_AVP_CODE
{
    DIA_AVP_CODE_NONE = 0,
    DIA_ORIGIN_HOST_AVP_CODE = 264,
    DIA_ORIGIN_REALM_AVP_CODE = 296,
    DIA_DEST_HOST_AVP_CODE = 293,
    DIA_DEST_REALM_AVP_CODE = 283,
    DIA_SUBS_ID_AVP_CODE = 443,
    DIA_SUBS_ID_TYPE_AVP_CODE = 450,
    DIA_SUBS_ID_VALUE_AVP_CODE = 444,
    DIA_USER_NAME_AVP_CODE = 1,
};

enum TDIA_SPEC_AVP
{
    DIA_SPEC_AVP_NONE = 0,
    DIA_SPEC_AVP_IMSI = 1,
    DIA_SPEC_AVP_MSISDN = 2,
};

enum SubscriptionIdType
{
    SUB_ID_TYPE_E164 = 0,
    SUB_ID_TYPE_IMSI = 1,
    SUB_ID_TYPE_SIP_URI = 2,
    SUB_ID_TYPE_NAI  = 3,
    SUB_ID_TYPE_PRIVATE = 4
};

#define DiaVar eAccelero::VarTypeUserDefined

// TODO add the field name also, so that while initizliaing the map, we can loop
// through and create the map
static eAccelero::VarIdentifier gVarIdents[] = {
    { DiaVar, {DIA_FIELD_TYPE_HDR,  DIA_HDR_R_BIT,  0, 0, 0, 0, 0, 0} },
    { DiaVar, {DIA_FIELD_TYPE_HDR, DIA_HDR_CMD_CODE, 0, 0, 0, 0, 0, 0} },
    { DiaVar, {DIA_FIELD_TYPE_HDR, DIA_HDR_APP_ID, 0, 0, 0, 0, 0, 0} },

    { DiaVar, { DIA_FIELD_TYPE_AVP, 
                  DIA_ORIGIN_HOST_AVP_CODE, diameter::UTF8StringType,
                  0, 0, 0, 0, 0} },
    { DiaVar, { DIA_FIELD_TYPE_AVP, 
                  DIA_ORIGIN_REALM_AVP_CODE, diameter::UTF8StringType,
                  0, 0, 0, 0, 0} },
    { DiaVar, { DIA_FIELD_TYPE_AVP,
                  DIA_DEST_HOST_AVP_CODE, diameter::UTF8StringType,
                  0, 0, 0, 0, 0} },
    { DiaVar, { DIA_FIELD_TYPE_AVP, 
                  DIA_DEST_REALM_AVP_CODE, diameter::UTF8StringType,
                  0, 0, 0, 0, 0} },
    { DiaVar, { DIA_FIELD_TYPE_AVP, 
                  DIA_USER_NAME_AVP_CODE, diameter::UTF8StringType,
                  0, 0, 0, 0, 0} },

    { DiaVar, {DIA_FIELD_TYPE_SPEC, DIA_SPEC_AVP_IMSI, 0, 0, 0, 0, 0, 0} },
    { DiaVar, {DIA_FIELD_TYPE_SPEC, DIA_SPEC_AVP_MSISDN, 0, 0, 0, 0, 0, 0} }

};

DiaTracer* DiaTracer::m_self = NULL;

DiaVarHandler::DiaVarHandler()
{
    // TODO change this into an loop
    m_fieldMap["Request"] = gVarIdents[0];
    m_fieldMap["Command-Code"] = gVarIdents[1];
    m_fieldMap["Application-Id"] = gVarIdents[2];

    m_fieldMap["Origin-Host"] = gVarIdents[3];
    m_fieldMap["Origin-Realm"] = gVarIdents[4];
    m_fieldMap["Destination-Host"] = gVarIdents[5];
    m_fieldMap["Destination-Realm"] = gVarIdents[6];
    m_fieldMap["User-Name"] = gVarIdents[7];

    m_fieldMap["IMSI"] = gVarIdents[8];
    m_fieldMap["MSISDN"] = gVarIdents[9];
}

DiaVarHandler::~DiaVarHandler()
{
}

eAccelero::Operand* DiaVarHandler::ConstructOperand(std::string &str,
                                    eAccelero::VarIdentifier &varId)
{
    size_t pos = str.find_first_of('.');
    std::string subStr = str.substr(pos+1);
    DT_DBG(("Tracing: Constructing AVP -> %s\n", subStr.c_str()));
    varId = m_fieldMap[subStr];

    return (new eAccelero::VarOperand<DiaVarHandler>(varId));
}

eAccelero::OperandValBase* DiaVarHandler::GetVal(
                                eAccelero::VarIdentifier &varId,
                                eAccelero::RuleRuntime *rt)
{
    eAccelero::OperandValBase* val = NULL;
    switch(varId.subId[0])
    {
        case DIA_FIELD_TYPE_HDR:
            {
                val = GetHdrVal(varId, rt);
                break;
            }
        case DIA_FIELD_TYPE_AVP:
            {
                val = GetAvpVal(varId, rt);
                break;
            }
        case DIA_FIELD_TYPE_SPEC:
            {
                val = GetSpecialVal(varId, rt);
                break;
            }
        default:
            DT_ERR(("#### Unknown Field type! ####\n"));
    }
    return val;
}

eAccelero::OperandValBase* DiaVarHandler::GetHdrVal(
                                eAccelero::VarIdentifier &varId,
                                eAccelero::RuleRuntime *rt)
{
    eAccelero::OperandValBase* val = NULL;
    diameter::DiaMsgFlow *msg = reinterpret_cast<diameter::DiaMsgFlow*>(rt->UserData());

    switch(varId.subId[1])
    {
        case DIA_HDR_R_BIT:
            {
                val = new eAccelero::IntVal((int)msg->isRequest());
                break;
            }
        case DIA_HDR_CMD_CODE:
            {
                val = new eAccelero::IntVal((int)msg->getCommandCode());
                break;
            }
        case DIA_HDR_APP_ID:
            {
                val = new eAccelero::IntVal((int)msg->getApplicationId());
                break;
            }
        default:
            DT_ERR(("#### Unknown header field type! ####\n"));
    }

    return val;
}
eAccelero::OperandValBase* DiaVarHandler::GetAvpVal(
                                eAccelero::VarIdentifier &varId,
                                eAccelero::RuleRuntime *rt)
{
    eAccelero::OperandValBase* val = NULL;
    diameter::DiaMsgFlow *msg = reinterpret_cast<diameter::DiaMsgFlow*>(rt->UserData());

    switch(varId.subId[1])
    {
        case DIA_ORIGIN_HOST_AVP_CODE:
            {
                diameter::AVP_STRING *avpStr = msg->getOriginHost();
                val = new eAccelero::StringVal(avpStr->value());
                break;
            }
        case DIA_ORIGIN_REALM_AVP_CODE:
            {
                diameter::AVP_STRING *avpStr =msg->getOriginRealm();
                val = new eAccelero::StringVal(avpStr->value());
                break;
            }
        case DIA_DEST_HOST_AVP_CODE:
            {
                diameter::AVP_STRING *avpStr = msg->getDestinationHost();
                if (avpStr)
                {
                    val = new eAccelero::StringVal(avpStr->value());
                }
                break;
            }
        case DIA_DEST_REALM_AVP_CODE:
            {
                diameter::AVP_STRING *avpStr = msg->getDestinationRealm();
                if (avpStr)
                {
                    val = new eAccelero::StringVal(avpStr->value());
                }
                break;
            }
        case DIA_USER_NAME_AVP_CODE:
            {
                diameter::base::BaseGenericCommand *bgCmd = msg->GetBaseGenCommand();
                if (bgCmd->countUserName())
                {
                    val = new eAccelero::StringVal(bgCmd->getUserName(0)->value());
                }
                break;
            }
        default:
            {
                // not handled currently
                DT_ERR(("#### Unknown AVP Code to get value from ####\n"));
            }
    }
    return val;
}
eAccelero::OperandValBase* DiaVarHandler::GetSpecialVal(
                                eAccelero::VarIdentifier &varId,
                                eAccelero::RuleRuntime *rt)
{
    int ret;
    unsigned type = 0;
    unsigned appId;
    eAccelero::OperandValBase* val = NULL;
    diameter::DiaMsgFlow *msg = reinterpret_cast<diameter::DiaMsgFlow*>(rt->UserData());

    msg->init_reflection();

    appId = msg->getApplicationId();

    switch(varId.subId[1])
    {
        case DIA_SPEC_AVP_IMSI:
            {
                std::string imsi;
                if (appId == S6A_S6D_INTERFACE_APP_ID ||
                        appId == S13_INTERFACE_APP_ID || appId == RFRO_INTERFACE_APP_ID)
                {
                    // Get it from user name avp
                    diameter::base::BaseGenericCommand *bgCmd = msg->GetBaseGenCommand();
                    if (bgCmd->countUserName())
                    {
                        std::string userName = bgCmd->getUserName(0)->value();
                        imsi = userName.substr(0, userName.find_first_of('@'));
                    }
                }
                else
                {
                    GetSubscriptionIdValue(msg, SUB_ID_TYPE_IMSI, imsi);
                }
                // If not found NULL string will be returned
                if(!imsi.empty())
                {
                    val = new eAccelero::StringVal(imsi);
                }
                break;
            }
        case DIA_SPEC_AVP_MSISDN:
            {
                std::string msisdn;
                if (GetSubscriptionIdValue(msg, SUB_ID_TYPE_E164, msisdn))
                {
                    val = new eAccelero::StringVal(msisdn);
                }
                break;
            }
        default:
            {
                DT_ERR(("#### Special AVP Not handled! ####"));
            }
    }

    return val;
}

bool DiaVarHandler::GetSubscriptionIdValue(diameter::DiaMsgFlow *msg, 
                        unsigned subIdType, std::string& value)
{
    bool ret = false;
    unsigned type = 0;
    int avpCount = msg->getAvpCount(DIA_SUBS_ID_AVP_CODE, 0);
    for (int i = 0; !ret || (i < avpCount); i++)
    {
        diameter::DerivedGroupedAVP subId;
        ret = msg->getAvpValue(DIA_SUBS_ID_AVP_CODE, i, &subId, diameter::GroupedType, 0);
        if (ret != ITS_SUCCESS)
        {
            continue;
        }
        subId.getAvpValue(DIA_SUBS_ID_TYPE_AVP_CODE, 0, &type, diameter::EnumeratedType, 0);
        if (type !=  subIdType)
        {
            continue;
        }
        subId.getAvpValue(DIA_SUBS_ID_VALUE_AVP_CODE, 0, &value, diameter::UTF8StringType, 0);
        ret = true;
    }

    return ret;
}

void DiaVarHandler::RuleRemovalHandler(uint16_t ruleId, void *ruleData, void *arg)
{
    if (ruleData == NULL)
    {
        return;
    }
    // The rule data will contain the session id
    char *sessId = (char*)ruleData;
    int len = strlen(sessId);
    SESSION_ENTRY *entry = NULL;

    int ret = SESSION_TABLE->FindEntry(entry, (ITS_OCTET*)sessId, len);
    if (ret == ITS_SUCCESS)
    {
        // There might be a potential race condition here. 
        // But mostly harmless, unless the session entry is deleted after
        //    finding
        DIA_SE_TRACE_RULE(entry) = 0;
    }
    free(sessId);
}

void DiaTracer::Init(const char* tracePath,eAccelero::Tracer::RuleRemovalCbk handler)
{
    m_self = new DiaTracer();

    eAccelero::Tracer::Init(tracePath);
    eAccelero::Tracer::Instance().RegisterVarHandler("dia", 
                                    &(m_self->m_varHandler));

    eAccelero::Tracer::Instance().RegisterRuleRemovalCbk(handler);

}

int DiaTracer::Configure(int filterid, std::string filtername, 
                        std::string rule, int priority, bool filtstatus, std::string loglevel, int expdur, int expmsg)
{
    int retVal = eAccelero::Tracer::Instance().Configure(filterid, filtername, rule, priority, expdur, expmsg, filtstatus, loglevel);
    return retVal;
}

void DiaTracer::SetTraceStatus(bool tracestatus)
{
    if(tracestatus)
    {
        eAccelero::Tracer::Instance().Enable(); 
    }
    else
    {
        eAccelero::Tracer::Instance().Disable();
    }
        
}

int DiaTracer::ModifyTracer(std::string filtername, std::string rule, int priority, char *filtstatus, std::string loglevel, int expdur, int expmsg)
{
    int retVal = eAccelero::Tracer::Instance().ModifyTracer(filtername, rule, priority, filtstatus, loglevel, expdur, expmsg);
    return retVal;
}

int DiaTracer::RemoveTracer(std::string& filterName)
{
    int retVal = eAccelero::Tracer::Instance().RemoveFilterRule(filterName);
    return retVal;
}

void DiaTracer::GetTraceStatus(std::string filtername,std::map<string, int>& traceStatus)
{
    eAccelero::Tracer::Instance().GetRuleStatus(filtername,traceStatus);
}
    

DiaTracer::DiaTracer()
{
}

DiaTracer::~DiaTracer()
{
}

void DiaTracer::MsgToString(diameter::DiaMsgFlow *msgFlow, std::stringstream &sstr)
{
    diameter::Command* newCmd = NULL;
    try
    {
        diameter::DiameterDictionaryRef dictRef = 
            DiaStackClass::GetDictionaryTable().fetchDictionaryObject(msgFlow->GetDictId());
        unsigned commandCode = msgFlow->GetBaseGenCommand()->getCommandCode();

        newCmd = dictRef->createCommandObject(commandCode, 
                                msgFlow->GetBaseGenCommand()->getImpl());

        // TODO do a pretty print. Also print the E2E H2H and command string
        sstr << *newCmd;
    }
    catch(...)
    {
        // nothing to do, just ignore, TODO log a error message
    }

    if (newCmd)
    {
        delete newCmd;
    }
}

void DiaTracer::SessTraceInitiate(diameter::DiaMsgFlow* cmd, 
                    SESSION_ENTRY *ent, const char* sessId,
                    unsigned trInst)
{
    bool found = false;
    // Check if the session entry already has the rule enabled
    if (DIA_SE_TRACE_RULE(ent))
    {
        eAccelero::TraceRef traceObj = 
            eAccelero::Tracer::Instance().GetTraceObj(DIA_SE_TRACE_RULE(ent));
        try
        { 
            if(traceObj->GetGeneration() == DIA_SE_GENERATION(ent))
            {
                traceObj->Duplicate();
                cmd->SetTraceObj(traceObj);
                eAccelero::Tracer::ThreadTraceObj(traceObj);
                if (cmd->GetBaseGenCommand() == NULL)
                {
                    // Create a new Base Generic command, required for generic access
                    // and printing protocol trace
                    cmd->SetBaseGenCommand(new DIA_GEN_CMD(
                                                       (const ITS_OCTET*)cmd->getEncodedBuf(),
                                                        cmd->getEncodedBufLen()));

                    DT_DBG(("DiaTracer::SessTraceInitiate: Memory allocated for DIA_GEN_CMD and set to DiaMsgFlow"));
                }
                found = true;
            }
            else
            {
                DT_DBG(("Filter with id %d is modified.Check other filter matches",DIA_SE_TRACE_RULE(ent)));
                DIA_SE_TRACE_RULE(ent) = 0;
            } 
        }
        catch(diameter::CodecException& codecExpn) //Fixing Big parameter passing by value
        {
            DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    codecExpn.name(), codecExpn.what())); 
        }
        catch(eAccelero::NullPtrException &ptrException)
        {
            //Since filter is deleted we can search if any other filter matches  for the session
            // as found flag is still false
            DT_ERR(("Previous filter is deleted.Check is any other filter matches"));
            DIA_SE_TRACE_RULE(ent) = 0;
        }
        catch(...)
        {
            DT_ERR(("Unknown Exception Caught")); 
        }
    }
    if(found == false) 
    {
        try
        { 
            if (cmd->GetBaseGenCommand() == NULL)
            {
                // Create a new Base Generic command, required for generic access
                cmd->SetBaseGenCommand(new DIA_GEN_CMD(
                                                       (const ITS_OCTET*)cmd->getEncodedBuf(),
                                                       cmd->getEncodedBufLen()));

                DT_DBG(("DiaTracer::SessTraceInitiate: Memory allocated for DIA_GEN_CMD and set to DiaMsgFlow"));
            }
        }
        catch(diameter::CodecException codecExpn)
        {
            DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    codecExpn.name(), codecExpn.what())); 
        }
        catch(...)
        {
            DT_ERR(("Unknown Exception Caught")); 
        }
        
        
        // Session entry doesn't have the rule set
        // Tracer filter. Check if any filter mathces
        eAccelero::TraceRef traceObj;
        bool res = eAccelero::Tracer::Instance().Filter(cmd, traceObj);
        if (!res)
        {
            DT_DBG(("SessionTracing: no filters matched"));
            eAccelero::Tracer::ThreadTraceObj(NULL);
        }
        else
        {
            // matched a filter rule. Now set the trace object to the message
            // flow and the current thread. 
            DT_DBG(("SessionTracing: matched rule %d", traceObj->RuleId()));
            traceObj->Duplicate();
            eAccelero::Tracer::ThreadTraceObj(traceObj);
            cmd->SetTraceObj(traceObj);

            // Set the session entry to the rule id
            // The user data is used to reset the SessTraceRule when the trace
            // object is removed, see RuleRemovalHandler()
            DIA_SE_TRACE_RULE(ent) = traceObj->RuleId();
            DIA_SE_GENERATION(ent) = traceObj->GetGeneration();
            //traceObj->UserData(strdup(sessId));
            found = true;
        }         
    }

    if (found)
    {
        // Log the message to the tracer
        LogProtoMsgInternal(cmd, trInst, false);
    }
}

void DiaTracer::LogProtoMsgInternal(diameter::DiaMsgFlow *msg, PEER_ENTRY* peer, bool isOut)
{
    // If trace is enabled log to the file
    std::stringstream sstr;
    if (isOut)
    {
        sstr << "\nOUTGOING to ";
    }
    else
    {
        sstr << "\nINCOMING from ";
    }
    
    sstr << DIA_PE_HOST(peer) << "\n";
    DiaTracer::MsgToString(msg, sstr);
    EACC_PROTO_TRACE(sstr.str().c_str());
}

void DiaTracer::LogProtoMsgInternal(diameter::DiaMsgFlow *msg, ITS_USHORT peerInst, bool isOut)
{
    // If trace is enabled log to the file
    std::stringstream sstr;
    if (isOut)
    {
        sstr << "\nOUTGOING to ";
    }
    else
    {
        sstr << "\nINCOMING from ";
    }
    
    const char* host = "";
    if (trTable[peerInst])
    {
        host = DIA_PE_HOST(trTable[peerInst]->GetPeer());
    }
    sstr << host << "\n";
    DiaTracer::MsgToString(msg, sstr);
    EACC_PROTO_TRACE(sstr.str().c_str());
}

void DiaTracer::LogProtoMsgInternal(DIA_GEN_CMD *msg, ITS_USHORT peerInst, bool isOut)
{
    // If trace is enabled log to the file
    std::stringstream sstr;
    if (isOut)
    {
        sstr << "\nOUTGOING to ";
    }
    else
    {
        sstr << "\nINCOMING from ";
    }
    
    const char* host = "";
    if (trTable[peerInst])
    {
        host = DIA_PE_HOST(trTable[peerInst]->GetPeer());
    }
    
    try
    {
        sstr << host << "\n" << *msg;
    }
    catch(...)
    {
        // ignore
    }
 
    EACC_PROTO_TRACE(sstr.str().c_str());
}
