/*********************************-*-H-*-************************************
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
#ifndef __DIA_TRACER_H__
#define __DIA_TRACER_H__

#include <sstream>
#include <dia_session_table.h>
#include <dia_peer_table.h>
//#include "Exception.h"
#include "Tracer.h"
#include "Logger.h"

class DiaVarHandler: public eAccelero::VarHandler
{
 public:
    DiaVarHandler();
    ~DiaVarHandler();
    
    virtual eAccelero::Operand* ConstructOperand(std::string &str,
                                    eAccelero::VarIdentifier &varId);

    static eAccelero::OperandValBase* GetVal(
                                    eAccelero::VarIdentifier &varId,
                                    eAccelero::RuleRuntime *rt);
    
    // TODO move this the DiaTracer
    static void RuleRemovalHandler(uint16_t ruleId, void *ruleData, void *arg);

 protected:

    static eAccelero::OperandValBase* GetHdrVal(
                                    eAccelero::VarIdentifier &varId,
                                    eAccelero::RuleRuntime *rt);

    static eAccelero::OperandValBase* GetAvpVal(
                                    eAccelero::VarIdentifier &varId,
                                    eAccelero::RuleRuntime *rt);

    static eAccelero::OperandValBase* GetSpecialVal(
                                    eAccelero::VarIdentifier &varId,
                                    eAccelero::RuleRuntime *rt);

    static bool GetSubscriptionIdValue(diameter::DiaMsgFlow *msg, unsigned subIdType,
                                    std::string& value);

    typedef std::unordered_map<std::string, eAccelero::VarIdentifier> FieldMap;
    FieldMap m_fieldMap;
};

class DiaTracer
{
 public:
    static void Init(const char *tracePath,eAccelero::Tracer::RuleRemovalCbk handler);

    static int Configure(int filterid, std::string filtername, 
                        std::string rule, int priority,  bool filtstatus, std::string loglevel,int expdur = -1, int expmsg = -1);

    static int ModifyTracer(std::string filtername, std::string rule = "", int priority = -1,  char *filtstatus = NULL, std::string loglevel = "", int expdur = -1, int expmsg = -1);

    static void GetTraceStatus(std::string filtername,std::map<string, int>& traceStatus);

    static void SetTraceStatus(bool tracestatus);

    static int RemoveTracer(std::string& filterName);

    static void Destroy()
    {
        if (m_self)
        {
            delete m_self;
        }
        eAccelero::Tracer::Destroy();
    }

    static DiaTracer& Instance()
    {
        return *m_self;
    }

    static void MsgToString(diameter::DiaMsgFlow* msgFlow, std::stringstream& sstr);

    static void SessTraceCheckAndLog(diameter::DiaMsgFlow* msgFlow, SESSION_ENTRY* ent,
                    const char* sessId, unsigned trInst)
    {
        if ((&eAccelero::Tracer::Instance()) != NULL && 
                eAccelero::Tracer::Instance().IsEnabled())
        {
            SessTraceInitiate(msgFlow, ent, sessId, trInst);
        }
    }

    // Set the trace object to the thread from the DiaMsgFlow
    static void SetTraceObj(diameter::DiaMsgFlow *cmd)
    {
        if ((&eAccelero::Tracer::Instance()) != NULL && 
                eAccelero::Tracer::Instance().IsEnabled() &&
                cmd->GetTraceObj().Ptr() != NULL)
        {
            eAccelero::Tracer::ThreadTraceObj(cmd->GetTraceObj());
        }
    }
    
    static void LogProtoMsg(diameter::DiaMsgFlow *cmd, PEER_ENTRY* peer, bool isOut = true)
    {
        if (&(eAccelero::Tracer::Instance()) != NULL &&
                 eAccelero::Tracer::Instance().IsEnabled() &&
                 eAccelero::Tracer::Instance().IsThreadTraceable())
        {
            LogProtoMsgInternal(cmd, peer, isOut);
        }  
    }

    static void LogProtoMsg(diameter::DiaMsgFlow *cmd, ITS_USHORT peerInst, bool isOut = true)
    {
        if (&(eAccelero::Tracer::Instance()) != NULL &&
                 eAccelero::Tracer::Instance().IsEnabled() &&
                 eAccelero::Tracer::Instance().IsThreadTraceable())
        {
            LogProtoMsgInternal(cmd, peerInst, isOut);
        }  
    }
    
    static void LogProtoMsg(DIA_GEN_CMD *cmd, ITS_USHORT peerInst, bool isOut = true)
    {
        if (&(eAccelero::Tracer::Instance()) != NULL &&
                 eAccelero::Tracer::Instance().IsEnabled() &&
                 eAccelero::Tracer::Instance().IsThreadTraceable())
        {
            LogProtoMsgInternal(cmd, peerInst, isOut);
        }  
    }
    
    static void ClearThreadTraceObj()
    {
        if (&(eAccelero::Tracer::Instance()) != NULL)
        {
            try
            {
                eAccelero::Tracer::ThreadTraceObj(NULL);
            }
            catch(eAccelero::SystemException& systemExpn) //Fixing Big parameter passing by value
            {
               DT_ERR(("Error in setting trace obj.%s",systemExpn.what())); 
            }
        }
    }

 protected:
    DiaTracer();
    ~DiaTracer();
    
    static void SessTraceInitiate(diameter::DiaMsgFlow* msgFlow, SESSION_ENTRY* ent,
                    const char* sessId, unsigned trInst);
    static void LogProtoMsgInternal(diameter::DiaMsgFlow *cmd, PEER_ENTRY* peer, bool isOut = true);
    static void LogProtoMsgInternal(diameter::DiaMsgFlow *cmd, ITS_USHORT peerInst, bool isOut = true);
    static void LogProtoMsgInternal(DIA_GEN_CMD *cmd, ITS_USHORT peerInst, bool isOut = true);
    
    DiaVarHandler m_varHandler;

    static DiaTracer* m_self;
};

#endif // __DIA_TRACER_H__
