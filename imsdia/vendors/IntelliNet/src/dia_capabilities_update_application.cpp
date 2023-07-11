/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2012 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 ***************************************************************************/
#include <its++.h>
#include <dia_capabilities_update_application.h>
#include <dia_ip_trans.h>
#include <dia_utils.h>
#include <dia_msg_router.h>
#if defined(ITS_STD_NAMESPACE)
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

ITS_Mutex CapabilitiesUpdateApplication::m_capabilitiesUpdateAppObjectGuard(0);

CapabilitiesUpdateApplication* CapabilitiesUpdateApplication::m_capabilitiesUpdateAppObject = NULL;


/*.implementation:static
 ****************************************************************************
 *  Purpose: Static method to create the object.CapabilitiesUpdateApplication is a 
 *           singleton class
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None 
 *  Return Value:
 *        Returns the CapabilitiesUpdateApplication object. 
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
CapabilitiesUpdateApplication*
CapabilitiesUpdateApplication::GetCapabilitiesUpdateApplication()
{

    //Should not impact performance as this is not called frequently
    ITS_ASSERT(CapabilitiesUpdateApplication::m_capabilitiesUpdateAppObjectGuard.Acquire() == ITS_SUCCESS);
    if (m_capabilitiesUpdateAppObject == NULL)
    {
        m_capabilitiesUpdateAppObject = new CapabilitiesUpdateApplication;
    }
    CapabilitiesUpdateApplication::m_capabilitiesUpdateAppObjectGuard.Release();
    return m_capabilitiesUpdateAppObject;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: Destructor.
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
CapabilitiesUpdateApplication::~CapabilitiesUpdateApplication()
{  
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Method to  process the incoming CUR and also verify the app/acct
 *  id with local CER/CEA.
 *
 *  Input Parameters:pointer to DIA_CMD,peer entry and event received from peer 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: on sucessfully processing ITS_DIA_SUCCESS otherwise error
 *  code 
 *    
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
CapabilitiesUpdateApplication::ProcessCUR(DIA_CMD* cmd,PEER_ENTRY *pEntry,ITS_EVENT *evt)
{
    int ret = ITS_DIA_SUCCESS;
    bool isCommonAppFound = false;
    DIA_GEN_CMD * gCmd = NULL;
    DIA_CUR * cur = NULL;
    bool isError = false;

    DT_DBG(("ProcessCUR::"));

    if(!IsCapabilityUpdateIsSupported())
    {
        DT_ERR(("Capability update not supported.Drop the CUR"));
        return ITS_DIA_SUCCESS;
    }
    ITS_UINT rCode = ITS_DIA_SUCCESS;

    try
    {
        cur = new DIA_CUR(*(DIA_GEN_CMD*)cmd);
    }
    catch (NoSuchAttributeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = ITS_DIA_MISSING_AVP;
    }
    catch (WrongCommandTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = ITS_DIA_CMD_UNSUPPORTED;
    }
    catch (UnknownTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = ITS_DIA_INVALID_BIT_IN_HDR;
    }
    catch (CodecException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = e.errcode();
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));

        ret = ITS_DIA_MISSING_AVP;
    }



    if((DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG))
        && (ret == ITS_DIA_SUCCESS))
    {
        cout << "CUR Received " << endl;
        cout << *cur << endl;
    }
    
    if(ret == ITS_DIA_SUCCESS)
    {
        gCmd = DIA_PE_CE_CACHE(pEntry);
    }
    if (gCmd)
    {
        if(!isCommonAppFound)
        {
            DT_DBG(("Compare first Auth applications"));
            for(int i = 0;i < cur->countAuthApplicationId();i++)
            {
                int authAppIdInCUR = cur->getAuthApplicationId(i).value();
                for(int j = 0; j < gCmd->countAuthApplicationId(); j++)
                {
                    if(authAppIdInCUR == gCmd->getAuthApplicationId(j)->value())
                    {
                        DT_DBG(("Found common auth app id %d",authAppIdInCUR));
                        isCommonAppFound = true;
                        break;
                    }
                    if(gCmd->getAuthApplicationId(j)->value() == 0xffffffff)
                    {
                        DT_DBG(("Advirtised as relay so not disconnecting"));
                        isCommonAppFound = true;
                        break;
                    }
                }
                if(isCommonAppFound)
                    break;
            }
        }
        if(!isCommonAppFound)
        {
            DT_DBG(("Compare Acct applications"));
            for(int i = 0;i < cur->countAcctApplicationId();i++)
            {
                int acctAppIdInCUR = cur->getAcctApplicationId(i).value();
                for(int j = 0; j < gCmd->countAcctApplicationId(); j++)
                {
                    if(acctAppIdInCUR == gCmd->getAcctApplicationId(j)->value())
                    {
                        DT_DBG(("Found common acct app id %d",acctAppIdInCUR));
                        isCommonAppFound = true;
                        break;
                    }
                }
                if(isCommonAppFound)
                    break;
            }
        }
        if(!isCommonAppFound)
        {
            DT_DBG(("Compare vendor specific  applications"));
            for(int i = 0; i < cur->countVendorSpecificApplicationId();i++)
            {
                for(int j=0;j<gCmd->countVendorSpecificApplicationId();j++)
                {
                    if(gCmd->getVendorSpecificApplicationId(i)->containsAcctApplicationId())
                    {
                        if(cur->getVendorSpecificApplicationId(j).containsAcctApplicationId())
                        {
                            if(gCmd->getVendorSpecificApplicationId(i)->getAcctApplicationId().value()==
                                    cur->getVendorSpecificApplicationId(j).getAcctApplicationId().value())
                            {
                                DT_DBG(("Found common vendor specific accounting app %d",
                                            cur->getVendorSpecificApplicationId(j).getAcctApplicationId().value()));
                                isCommonAppFound = true;
                                break;
                            }

                        }
                        if(cur->getVendorSpecificApplicationId(j).containsAuthApplicationId())
                        {
                            if(gCmd->getVendorSpecificApplicationId(i)->getAuthApplicationId().value()==
                                    cur->getVendorSpecificApplicationId(j).getAuthApplicationId().value())
                            {
                                DT_DBG(("Found common vendor specific auth app %d",
                                            cur->getVendorSpecificApplicationId(j).getAuthApplicationId().value()));
                                isCommonAppFound = true;
                                break;
                            }
                        }
                    }
                }
                if(isCommonAppFound)
                    break;
            }
        }
    }

    if((ret == ITS_DIA_SUCCESS) && (!isCommonAppFound))
    {
        DT_ERR(("No common application found"));
        rCode = ITS_DIA_NO_COMMON_APP;
        isError = true;
    }
    else
    {
        UpdateCeCacheOfPeer(cur,pEntry,gCmd->isRequest());
    }
    if ((ret = SendCUA(isError, false,rCode,pEntry,evt)) == ITS_SUCCESS)
    {
        DT_DBG(("SendCUA::Success"));
        if(rCode == ITS_DIA_NO_COMMON_APP)
        {
            DIA_PE_STATE(pEntry) = PEER_ST_CLOSED;
            DiaSocketTransport *tr = (DiaSocketTransport *)
                (DIA_PE_ACC_SPECS(pEntry).trHandle);

            if (tr)
            {
                DT_WRN(("Signaling shutdown of acceptor transport"));
                tr->SetExit();
                DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(pEntry);
                DIA_PE_ACC_SPECS(pEntry).trHandle = NULL;
                DIA_PE_ACC_SPECS(pEntry).trInst = 0;
            }
            tr = (DiaSocketTransport *)
                (DIA_PE_CONN_SPECS(pEntry).trHandle);

            if (tr)
            {
                DT_WRN(("Signaling shutdown of connector transport"));
                tr->SetExit();
                DIA_PE_CONN_SPECS(pEntry).trHandle = NULL;
                DIA_PE_CONN_SPECS(pEntry).trInst = 0;
            }

            pEntry->trHandle = NULL;
            /* Retry connection after disconnect */
            if (DIA_PE_RETRY_TIMER(pEntry) != TIMER_BAD_SERIAL)
            {
                PeerTable::StopTimer(RETRY, pEntry);
            }
        }
    }

    if (itsDiaConfig.IsPeerMsgToAppEnabled())
    {
        DiaMsgRouter::SendPeerMsgToApp((DIA_GEN_CMD *)cmd);
    }

    if(cur != NULL)
    {
        delete cur;
        cur = NULL;
    }
    return (ret);
}


                            /*.implementation:static
 ****************************************************************************
 *  Purpose: Method to  update the cache stored in PEER_ENTRY 
 *
 *  Input Parameters:
 *       pointer DIA_CUR,Peer entry and boolean to indicate is a cer or cea 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None. 
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

void
CapabilitiesUpdateApplication::UpdateCeCacheOfPeer(DIA_CUR* cur,
        PEER_ENTRY *pEntry,bool isRequest)
{
    if(isRequest)
    {
        DIA_CER* cer = new CapabilitiesExchangeRequest(false, false); 
        cer->setProductName(cur->getProductName());
        cer->setOriginHost(cur->getOriginHost());
        cer->setOriginRealm(cur->getOriginRealm());
        cer->setVendorId(cur->getVendorId());
        if(cur->containsOriginStateId())
        {
            cer->setOriginStateId(cur->getOriginStateId());
        }
        for(int i =0;i < cur->countHostIPAddress();i++)
        {
            cer->addHostIPAddress(cur->getHostIPAddress(i));
        }
        for(int i = 0; i < cur->countSupportedVendorId();i++)
        {
            cer->addSupportedVendorId(cur->getSupportedVendorId(i));
        }
        for(int i = 0; i < cur->countAuthApplicationId();i++)
        {
            cer->addAuthApplicationId(cur->getAuthApplicationId(i));
        }
        for(int i = 0; i < cur->countAcctApplicationId();i++)
        {
            cer->addAcctApplicationId(cur->getAcctApplicationId(i));
        }
        for(int i = 0; i < cur->countVendorSpecificApplicationId();i++)
        {
            cer->addVendorSpecificApplicationId(cur->getVendorSpecificApplicationId(i));
        }
        if (DIA_PE_CE_CACHE(pEntry))
        {
            delete DIA_PE_CE_CACHE(pEntry);
            DIA_PE_CE_CACHE(pEntry) = (DIA_GEN_CMD*)cer;
            if((DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG)))
            {
                cout << "Updated CER of peer to be cached: " << endl;
                cout << *cer << endl;
            }
        }
    }
    else
    {
        DIA_CEA* cea = new CapabilitiesExchangeAnswer(false, false);
        cea->setResultCode(ResultCode(ITS_DIA_SUCCESS));
        cea->setProductName(cur->getProductName());
        cea->setOriginHost(cur->getOriginHost());
        cea->setOriginRealm(cur->getOriginRealm());
        cea->setVendorId(cur->getVendorId());
        if(cur->containsOriginStateId())
        {
            cea->setOriginStateId(cur->getOriginStateId());
        }
        for(int i =0;i < cur->countHostIPAddress();i++)
        {
            cea->addHostIPAddress(cur->getHostIPAddress(i));
        }
        for(int i = 0; i < cur->countSupportedVendorId();i++)
        {
            cea->addSupportedVendorId(cur->getSupportedVendorId(i));
        }
        for(int i = 0; i < cur->countAuthApplicationId();i++)
        {
            cea->addAuthApplicationId(cur->getAuthApplicationId(i));
        }
        for(int i = 0; i < cur->countAcctApplicationId();i++)
        {
            cea->addAcctApplicationId(cur->getAcctApplicationId(i));
        }
        for(int i = 0; i < cur->countVendorSpecificApplicationId();i++)
        {
            cea->addVendorSpecificApplicationId(cur->getVendorSpecificApplicationId(i));
        }
        if (DIA_PE_CE_CACHE(pEntry))
        {
            delete DIA_PE_CE_CACHE(pEntry);
            DIA_PE_CE_CACHE(pEntry) = (DIA_GEN_CMD*)cea;
            if((DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG)))
            {
                cout << "Updated CEA of peer to be cached: " << endl;
                cout << *cea << endl;
            }
        }
    }
}

                            /*.implementation:static
 ****************************************************************************
 *  Purpose: Method to process CUA 
 *
 *  Input Parameters:
 *       pointer DIA_CMD 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  sucess or failure
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

int
CapabilitiesUpdateApplication::ProcessCUA(DIA_CMD* cmd,PEER_ENTRY *pEntry)
{
    int ret = ITS_DIA_SUCCESS;
    DIA_CUA *cua = NULL;
    DT_DBG(("ProcessCUA::"));

    try
    {
        cua = new DIA_CUA(*(DIA_GEN_CMD*)cmd);
    }
    catch (NoSuchAttributeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = ITS_DIA_MISSING_AVP;
    }
    catch (WrongCommandTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = ITS_DIA_CMD_UNSUPPORTED;
    }
    catch (UnknownTypeException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = ITS_DIA_INVALID_BIT_IN_HDR;
    }
    catch (CodecException e)
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                    e.name(), e.what()));

        ret = e.errcode();
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));

        ret = ITS_DIA_MISSING_AVP;
    }


    if ((DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG))
         && ret == ITS_DIA_SUCCESS)
    {
        cout << "CUA Received: " << endl;
        cout << *cua << endl;
    }
    
    if (itsDiaConfig.IsPeerMsgToAppEnabled())
    {
        DiaMsgRouter::SendPeerMsgToApp((DIA_GEN_CMD *)cmd);
    }
    if(cua != NULL)
    {
        delete cua;
        cua = NULL;
    }
    return (ret);
}



/*.implementation:static
 ****************************************************************************
 *  Purpose: Method to sending CUA to peer 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  success or failure
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

int
CapabilitiesUpdateApplication::SendCUA(bool error, bool retrans,
                                       ITS_UINT result,PEER_ENTRY *pEntry,ITS_EVENT *evt)
{
    ITS_OCTET *buff;
    int ret, len;
    ITS_OCTET *msg = &evt->data[sizeof(ITS_USHORT)];
    ITS_UINT msgLen = (evt->len - sizeof(ITS_USHORT));
    DiaSocketTransport *handle = (DiaSocketTransport *)pEntry->trHandle;

    DT_DBG(("SentCUA::"));
    DIA_CER *lcer;
    lcer = itsDiaConfig.GetLocalCER();

    DIA_CUA cua(error, retrans);

    cua.setResultCode(ResultCode(result));
    cua.setOriginHost(lcer->getOriginHost());
    cua.setOriginRealm(lcer->getOriginRealm());

    if (DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG))
    {
        DT_DBG(("Send CUA"));
        cout << cua << endl;
    }

    DiaUtils::EncodeMsg(&cua, &buff, len);

    memcpy(&buff[12], &msg[12], sizeof(ITS_UINT));

    memcpy(&buff[16], &msg[16], sizeof(ITS_UINT));

    ret = DiaMsgRouter::SendToPeer(handle, buff, len);
    if(ITS_SUCCESS == ret)
    {
        DIA_INC_PEER_DWA_SENT(pEntry);
        if(result != ITS_DIA_SUCCESS)
        {
            DiaErrHandler::UpdateErrorStats((ITS_UINT)(DIA_PE_INST(pEntry)),result);
        }
    }

    free((char*) buff);
    buff = NULL;

    UPDATE_DIA_STATS_ANSOUT(DIA_MSG_CUR);
    return ret;
}



/*.implementation:static
 ****************************************************************************
 *  Purpose: Method checks is the local host supportes dynamic update of 
 *         capability
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  true if supports otherwise false 
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

bool 
CapabilitiesUpdateApplication::IsCapabilityUpdateIsSupported()
{
    bool isCapabilityUpadteSupported = false;
    DIA_CER* lcer = itsDiaConfig.GetLocalCER();

    for(int i = 0; i < lcer->countAuthApplicationId();i++)
    {
        if(lcer->getAuthApplicationId(i).value() == DIA_CAPABILITIES_UPDATE_APPLICATION_ID)
        {
            isCapabilityUpadteSupported = true;
            break;
        }
    }
    return isCapabilityUpadteSupported;
}
