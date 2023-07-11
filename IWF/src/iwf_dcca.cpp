/*********************************-*-CPP-*-**********************************
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

#include "iwf_dcca.h"
#include "iwf.h"
#include "iwf_prot_utils.h"
#include "dcca_common.h"

#if 0
IwfDccaSessionCtxt::IwfDccaSessionCtxt()
    : m_state(DccaIdle),
      m_isFailoverSupported(true),
      m_isDone(false),
      m_lastSentCCR(NULL),
      m_retryCount(0)
{
    m_ccfhAction = IwfController::Instance().Config().
                        DCCAConfig().GetInitialCCFHAction();
}
#endif

IwfDccaSessionCtxt::IwfDccaSessionCtxt()
    :m_lastSentCCR(NULL)
{
    SetCCFHAction(IwfController::Instance().Config().
                        DCCAConfig().GetInitialCCFHAction());
}

IwfDcca::FailureAction IwfDcca::HandleFailure(IwfDccaSessionCtxt& dccaCtxt,
                                     DIA_BASE_CMD*& outCmd)
{
    FailureAction retAction = FA_Terminate;
    outCmd = NULL;

    if (!dccaCtxt.IsFailoverSupported() ||
        dccaCtxt.GetRetryCount() != 0)
    {
        if (dccaCtxt.GetCCFHAction() == IWF_CCFH_ACTION_CONTINUE)
        {
            retAction = FA_Continue;
        }
        dccaCtxt.SetState(IwfDccaSessionCtxt::DccaIdle);
        // Don't need the transaction info anymore
        dccaCtxt.ClearTransaction();
        DLOG_DEBUG("CCFH: Already retried or failover is not supported"
                   " - Action: %d", retAction);
        return retAction;
    }

    // Retry count is going to be zero here
    if (dccaCtxt.GetCCFHAction() == IWF_CCFH_ACTION_RETRY_TERMINATE ||
         dccaCtxt.GetCCFHAction() ==  IWF_CCFH_ACTION_CONTINUE)
    {
        outCmd = dccaCtxt.GetLastSentCCR();
        if (outCmd != NULL)
        {
            dccaCtxt.IncrementRetryCount();

            bool setAltHost = this->SetAlternateDHost(dccaCtxt, outCmd);
            if (setAltHost)
            {
                retAction = FA_Retry;
                DLOG_DEBUG("CCFH action is retry or continue. Request will be retried.");

                // The outCmd will be deleted by the stack. So we need to delete it
                // explicitly
                dccaCtxt.SetLastSentCCR(NULL);
            }
            else
            {
                DLOG_DEBUG("No alternate host found. CCFH action is Terminate");
                // Terminate action, clear the dcca transaction
                dccaCtxt.ClearTransaction();
                dccaCtxt.SetState(IwfDccaSessionCtxt::DccaIdle);
            }
        }
        else
        {
            DLOG_WARNING("Last Sent CCR message is not set");
            dccaCtxt.ClearTransaction();
            dccaCtxt.SetState(IwfDccaSessionCtxt::DccaIdle);
        }
    }
    else
    {
        // Terminate action, clear the dcca transaction
        dccaCtxt.ClearTransaction();
        dccaCtxt.SetState(IwfDccaSessionCtxt::DccaIdle);
    }

    DLOG_DEBUG("CCFH: Determined failure action %d", retAction);
    return retAction;
}

bool IwfDcca::SetAlternateDHost(IwfDccaSessionCtxt& dccaCtxt, DIA_BASE_CMD* cmd)
{
    IwfDCCADestinations& destinations = IwfController::Instance().Config().
                                            DCCAConfig().GetDestinations();
    IwfDCCAEndpointsConf* endpoints = destinations.LookupEndpointsConf(
                                            cmd->getDestinationRealm()->value());
    if (endpoints == NULL)
    {
        DLOG_ERROR("No DCCA endpoints founds for realm %s",
                    cmd->getDestinationRealm()->value().c_str());
        return false;
    }

    for (IwfDCCAEndpointsConf::EndpointsList::iterator it = endpoints->Begin();
         it != endpoints->End(); it++)
    {
        if (it->GetEndpoint() != dccaCtxt.GetDestHost())
        {
            IWFUtils::SetDestHost(cmd, it->GetEndpoint());

            if (IwfController::Instance().Config().DCCAConfig().IsTbitRequired())
            {
                //Set the T-bit to indicate Retransmitted message
                DIA_HDR &diaHdr = (DIA_HDR &)cmd->getHeader();
                diaHdr.flags.t = 1;
            }

            // Update the destination host in the dccaContext
            dccaCtxt.SetDestHost(it->GetEndpoint());
            DLOG_DEBUG("DCCA: Alternate host set to %s for session %s",
                    it->GetEndpoint().c_str(),
                    cmd->getSessionId()->value().c_str());
            return true;
        }
    }
    return false;
}

void IwfDcca::HandleResponse(IwfDccaSessionCtxt& dccaCtxt,
        diameter::base::BaseGenericCommand* cca)
{
    if (cca->countResultCode() && 
        cca->getResultCode()->value() == ITS_DIA_SUCCESS)
    {
        dccaCtxt.SetDestHost(cca->getOriginHost()->value());
        dccaCtxt.SetDestRealm(cca->getOriginRealm()->value());

        unsigned value = 0;
        if (cca->getAvpValue(CCFH_AVP_CODE, &value, 
                    diameter::EnumeratedType) == 0)
        {
            if (value >= DCCA_CCFH_TERMINATE &&
                    value <= DCCA_CCFH_RETRY_TERMINATE)
            {
                DLOG_DEBUG("Received CCFH value : %d",value);
                dccaCtxt.SetCCFHAction((IwfCCFHAction)value);
            }
            else
            {
                DLOG_ERROR("Received invalid CCFH value : %d",value);
                DLOG_DEBUG("Retaining existing CCFH value : %d",dccaCtxt.GetCCFHAction());
            }

        }
        if (cca->getAvpValue(CC_SESS_FAILOVER_AVP_CODE, &value,
                    diameter::EnumeratedType) == 0)
        {
            dccaCtxt.SetFailoverSupported((bool)value);
        }
        else
        {
            dccaCtxt.SetFailoverSupported(false);
            DLOG_DEBUG("CC-Session-Failover avp not present, Failure handling is not performed");
        }
        dccaCtxt.SetState(IwfDccaSessionCtxt::DccaOpen);

        DLOG_DEBUG("CC Answer <%s> CCFH: %d FailoverSupported: %d",
            cca->getSessionId()->value().c_str(), dccaCtxt.GetCCFHAction(),
            dccaCtxt.IsFailoverSupported());
    }

    dccaCtxt.ClearTransaction();
}

void IwfDcca::HandleRequest(IwfDccaSessionCtxt& dccaCtxt,
                            DIA_BASE_CMD* cmd,
                            unsigned ccreqType)
{
    switch(ccreqType)
    {
        case DCCA_INI_REQUEST:
        {
            // The previous state must be IDLE or PendingI
            dccaCtxt.SetState(IwfDccaSessionCtxt::DccaPendingI);
            break;
        }
        case DCCA_UPD_REQUEST:
        {
            dccaCtxt.SetState(IwfDccaSessionCtxt::DccaPendingU);
            break;
        }
        case DCCA_TER_REQUEST:
        {
            dccaCtxt.SetState(IwfDccaSessionCtxt::DccaPendingT);
            break;
        }
        default:
        {
            dccaCtxt.SetState(IwfDccaSessionCtxt::DccaIdle);
        }
    }
    dccaCtxt.SetLastSentCCR(cmd);
    
    if (cmd->getDestinationHost())
    {
        dccaCtxt.SetDestHost(cmd->getDestinationHost()->value());
    }
#if 0
    else if (dccaCtxt.GetState() == IwfDccaSessionCtxt::DccaPendingI)
    {
        IwfDCCADestinations& destinations = IwfController::Instance().Config().
            DCCAConfig().GetDestinations();
        IwfDCCAEndpointsConf* endpoints = destinations.LookupEndpointsConf(
                cmd->getDestinationRealm()->value());
        if (endpoints == NULL)
        {
            DLOG_WARNING("No DCCA endpoints founds for realm %s",
                    cmd->getDestinationRealm()->value().c_str());
        }
        else if (endpoints->Size() != 0)
        {
            DLOG_DEBUG("DCCA Selected endpoint %s <%s>", 
                    endpoints->GetPrimary().c_str(),
                    cmd->getSessionId()->value().c_str());
            // Get the primary dest host and set it
            IWFUtils::SetDestHost(cmd, endpoints->GetPrimary());
            dccaCtxt.SetDestHost(cmd->getDestinationHost()->value());
        }
        else
        {
            DLOG_DEBUG("No endpoints are configured under realm %s",
                    cmd->getDestinationRealm()->value().c_str());
        }
    }
#endif

    dccaCtxt.SetDestRealm(cmd->getDestinationRealm()->value());
    
    DLOG_DEBUG("DCCA: CCRequest <%s>", cmd->getSessionId()->value().c_str());
}

bool IwfDcca::SelectDestinationHost(const std::string& destRealm,
                    std::string& outDestHost)
{
    IwfDCCADestinations& destinations = IwfController::Instance().Config().
                                            DCCAConfig().GetDestinations();
    IwfDCCAEndpointsConf* endpoints = destinations.LookupEndpointsConf(destRealm);
    if (endpoints == NULL)
    {
        DLOG_DEBUG("No DCCA endpoints founds for realm %s", destRealm.c_str());
        return false;
    }
    if (endpoints->Size() == 0)
    {
        DLOG_DEBUG("No endpoints are configured under realm %s", destRealm.c_str());
        return false;
    }

    // Get the primary dest host and set it
    outDestHost = endpoints->GetPrimary();

    return true;
}

void IwfDcca::ResetDccaContext(IwfDccaSessionCtxt& dccaCtxt)
{
    dccaCtxt.ClearTransaction();
    dccaCtxt.SetCCFHAction(IwfController::Instance().Config().
            DCCAConfig().GetInitialCCFHAction());
    dccaCtxt.SetFailoverSupported(true);
    dccaCtxt.SetState(IwfDccaSessionCtxt::DccaIdle);
}
