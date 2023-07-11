/**********************************-*-H-*-***********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 */


#ifndef __IWF_DCCA_H__
#define __IWF_DCCA_H__

#include "iwf_config.h"
#include "itsdiameter.h"
#include "dia_msg_flow.h"
#include "iwf.pb.h"

class IwfDccaSessionCtxt
{
 public:
    enum DccaState
    {
        DccaIdle,
        DccaPendingI,
        DccaPendingU,
        DccaPendingT,
        DccaPendingE,
        DccaOpen
    };

    IwfDccaSessionCtxt();

    ~IwfDccaSessionCtxt()
    {
        if (m_lastSentCCR)
        {
            delete m_lastSentCCR;
            m_lastSentCCR = NULL;
        }
    }

    void ClearTransaction()
    {
        if (m_lastSentCCR)
        {
            delete m_lastSentCCR;
            m_lastSentCCR = NULL;
        }
        m_pbIwfDccaSessionctxt.clear_retrycount();
    }

    const std::string& GetDestHost() const
    {
        return m_pbIwfDccaSessionctxt.desthost();
    }
    void SetDestHost(const std::string& destHost)
    {
        m_pbIwfDccaSessionctxt.set_desthost(destHost);
    }
    const std::string& GetDestRealm() const
    {
        return m_pbIwfDccaSessionctxt.destrealm();
    }
    void SetDestRealm(const std::string& destRealm)
    {
        m_pbIwfDccaSessionctxt.set_destrealm(destRealm);
    }

    IwfCCFHAction GetCCFHAction() const
    {
        return (IwfCCFHAction)m_pbIwfDccaSessionctxt.iwfccfhaction();
    }
    void SetCCFHAction(IwfCCFHAction action)
    {
        m_pbIwfDccaSessionctxt.set_iwfccfhaction(action);
    }

    bool IsFailoverSupported() const
    {
        return m_pbIwfDccaSessionctxt.isfailoversupported();
    }
    void SetFailoverSupported(bool supported = true)
    {
        m_pbIwfDccaSessionctxt.set_isfailoversupported(supported);
    }

    DIA_BASE_CMD* GetLastSentCCR()
    {
        return m_lastSentCCR;
    }
    void SetLastSentCCR(DIA_BASE_CMD* cmd)
    {
        if (cmd == NULL)
        {
            // Don't delete, deletion will happen in the stack
            m_lastSentCCR = NULL;
            return;
        }
        if (m_lastSentCCR)
        {
            delete m_lastSentCCR;
        }
        m_lastSentCCR = new DIA_BASE_CMD(*cmd);
    }

    uint32_t GetRetryCount() const
    {
        return  m_pbIwfDccaSessionctxt.retrycount();
    }
    void IncrementRetryCount()
    {
        int retryCount = GetRetryCount();
        retryCount++;
        m_pbIwfDccaSessionctxt.set_retrycount(retryCount);
    }
    void ResetRetryCount()
    {
        m_pbIwfDccaSessionctxt.clear_retrycount();
    }

    const DccaState& GetState() const
    {
        return (DccaState)m_pbIwfDccaSessionctxt.dccastate();
    }
    void SetState(DccaState state)
    {
        m_pbIwfDccaSessionctxt.set_dccastate(state);
    }

    bool IsDone() const
    {
        return m_pbIwfDccaSessionctxt.isdone();
    }
    void SetIsDone(bool isDone = true)
    {
        m_pbIwfDccaSessionctxt.set_isdone(isDone);
    }

    pbIwfDccaSessionCtxt& GetDccaReplicableData()
    {
        return m_pbIwfDccaSessionctxt;
    }

 protected:
#if 0
    DccaState m_state;
    // Bound Destination host and destination realm
    std::string m_destHost;
    std::string m_destRealm;

    // Current CCFH Action - based on incoming CCFH AVP or local config
    IwfCCFHAction m_ccfhAction;

    // Does OCS supports failover - based on CC-Session-Failover AVP
    bool      m_isFailoverSupported;
    bool      m_isDone;

    // Retry count - incremented after every retry
    uint32_t m_retryCount;
#endif
    // Last sent CCR message - used for retry
    DIA_BASE_CMD* m_lastSentCCR;

    pbIwfDccaSessionCtxt m_pbIwfDccaSessionctxt;
};

class IwfDcca
{
 public:
    enum FailureAction
    {
        FA_Terminate = 0, // terminate the dcca session
        FA_Continue = 1,  // grant the server and terminate dcca session
        FA_Retry = 2      // retry to alternate server
    };

    IwfDcca()
    {
    }

    bool IsFailureCondition(IwfDccaSessionCtxt& dccaCtxt, DIA_BASE_CMD* cmd)
    {
        bool ret = false;
        int32_t resultCode = 0;
        if (cmd->getResultCode())
        {
            resultCode = cmd->getResultCode()->value();
        }
        if (resultCode == ITS_DIA_TOO_BUSY || 
            resultCode == ITS_DIA_UNABLE_TO_DELIVER)
        {
            ret = true;
        }
        return ret;
    }

    FailureAction HandleFailure(IwfDccaSessionCtxt& dccaCtxt, DIA_BASE_CMD*& cmd);

    bool SetAlternateDHost(IwfDccaSessionCtxt& dccaCtxt, DIA_BASE_CMD* cmd);

    // Update DCCA context based on the response message
    void HandleResponse(IwfDccaSessionCtxt& dccaCtxt,
                       diameter::base::BaseGenericCommand* cca);

    void HandleRequest(IwfDccaSessionCtxt& dccaCtxt,
                       DIA_BASE_CMD* cmd, unsigned ccreqType);

    static bool SelectDestinationHost(const std::string& destRealm,
                    std::string& outDestHost);

    void ResetDccaContext(IwfDccaSessionCtxt& dccaCtxt);
};

#endif // __IWF_DCCA_H__
