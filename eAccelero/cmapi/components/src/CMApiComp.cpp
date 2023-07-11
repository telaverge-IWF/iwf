
/* ********************************-*-CPP-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#include "string"
#include "CMAPICommon.h"
#include "CMApiComp.h"
#include "Compo.h"
#include "ComponentDefines.h"
#include "ErrorResp.h"

using namespace std;

// Global Sync Object

void CMApiComponents::CopyPeerGroups(LBPeerGroups *To, LBPeerGroupResp *From)
{
    int NumPGs = From->peergroups_size();
    LBPeerGroup *LBPeerG = NULL;
    if (NumPGs > 0)
    {
        for (int i=0; i < NumPGs; i++)
        {
            LBPeerG = To->add_peergroups();
            LBPeerG->CopyFrom(From->peergroups(i));
        }
    }
}

void CMApiComponents::CopyPeerGroups(LBPeerGroupResp *To, LBPeerGroups *From)
{
    int NumPGs = From->peergroups_size();
    LBPeerGroup *LBPeerG = NULL;
    if (NumPGs > 0)
    {
        for (int i=0; i < NumPGs; i++)
        {
            LBPeerG = To->add_peergroups();
            LBPeerG->CopyFrom(From->peergroups(i));
        }
    }
}

void CMApiComponents::CopyPeerGroups(LBPeerGroups *To, LBPeerGroupReq *From)
{
    int NumPGs = From->peergroups_size();
    LBPeerGroup *LBPeerG = NULL;
    if (NumPGs > 0)
    {
        for (int i=0; i < NumPGs; i++)
        {
            LBPeerG = To->add_peergroups();
            LBPeerG->CopyFrom(From->peergroups(i));
        }
    }
}


void CMApiComponents::CopyPeerGroups(LBPeerGroupReq *To, LBPeerGroups *From)
{
    int NumPGs = From->peergroups_size();
    LBPeerGroup *LBPeerG = NULL;
    if (NumPGs > 0)
    {
        for (int i=0; i < NumPGs; i++)
        {
            LBPeerG = To->add_peergroups();
            LBPeerG->CopyFrom(From->peergroups(i));
        }
    }
}

int CMApiComponents::SendCMgrRequest(LBPeerGroupReq& Request, bool GetReq, LBPeerGroupResp *Response)
{ 
    int retVal = CMAPI_SUCCESS;   
    int ReqID = 0;
    std::string StrVal;
    ReqID = Request.requestid();
    CLOG_DEBUG("Sending Request to Config Manager %d", ReqID);
    m_SendSuccess = true;

    if (GetReq == true)
    {
        m_CmgrObj->CMgrGetLBPeerConfigs(Request, 
                new CMAPICookie(Request.requestid(), (void *) &Request));
    } else {
        m_CmgrObj->CMgrSetLBPeerConfigs(Request,
                new CMAPICookie(Request.requestid(), (void *) &Request));
    }

    if (m_SendSuccess == false)
    {
        ErrorDetails *err =Response->add_errordetails();
        retVal = CMAPI_MESSERROR;
        Response->set_responseid(retVal);
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("SendCmgrRequest: Waiting for Response");
    if (m_CMgrResponse->Get(StrVal, m_waitTime))
    {
        if (!StrVal.empty())
        {
            Response->ParseFromString(StrVal);
            if (Response->has_responseid())
            {
                retVal = Response->responseid();        
            }
        }
    } else {
        ErrorDetails *err =Response->add_errordetails();
        retVal = CMAPI_TIMEOUT;
        Response->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    return retVal;
}

// This Method initializes the CMAPI Library
int CMApiComponents::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">CMApiComponents: InitializeLibrary\n");
    CLOG_DEBUG("InitializeLibrary: Initializing Config Manager Interface");
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CmgrObj = new Stub::CmgrComponents(dest, 0);
    Stub::CmgrComponentsRespCbk::RegisterCmgrComponentsRespHandler();

    CLOG_DEBUG("InitializeLibrary: Initializing DRE Erlbf Statistics Interface");
    MeSSEndpoint destdre = {COMP_DRE_APP, DRE_INSTANCE_ID};
    m_ErlbfStatsObj = new Stub::ErlbfStats(destdre,0);
    Stub::ErlbfStatsRespCbk::RegisterErlbfStatsRespHandler();

    m_CMgrResponse = new CMAPIIntSync();
    return retVal;
}

// Create PeerGroup Method
int CMApiComponents::CreatePeerGroup(LBPeerGroups& Req,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: CreatePeerGroup");
    if (!Req.IsInitialized())
    {
        CLOG_DEBUG("CreatePeerGroup: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    CopyPeerGroups(&Request, &Req);
    Request.set_requestid(ADD_PEERGROUP);
    //LBPeerGroupResp Response;
    return SendCMgrRequest(Request, false, &(*Response));
}

int CMApiComponents::ModifyPeerGroup(LBPeerGroups& Req,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: ModifyPeerGroup");
    if (!Req.IsInitialized())
    {
        CLOG_DEBUG("ModifyPeerGroup: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    CopyPeerGroups(&Request, &Req);
    Request.set_requestid(MOD_PEERGROUP);
    //LBPeerGroupResp Response;
    return SendCMgrRequest(Request, false, Response);
}

int CMApiComponents::DeletePeerGroup(string PeerGroupName,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: DeletePeerGroup");
    if (PeerGroupName.empty())
    {
        CLOG_DEBUG("DeletePeerGroup: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup *LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    Request.set_requestid(DEL_PEERGROUP);
    // LBPeerGroupResp Response;
    return SendCMgrRequest(Request, false, Response);
}

int CMApiComponents::GetPeerGroup(LBPeerGroups& Req, LBPeerGroups& Resp,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetPeerGroup");
    LBPeerGroupReq LibReq;
    CopyPeerGroups(&LibReq, &Req);
    LibReq.set_requestid(GET_PEERGROUP);
    LBPeerGroupResp Response;
    if (SendCMgrRequest(LibReq, true, &Response) == CMAPI_SUCCESS)
    {
        CopyPeerGroups(&Resp, &Response);
        //In case of no records in DB then we are going to show message to user...hence
        //reusing the same errorDEtails field for the same.
        if(Response.peergroups_size() == 0)
        {
            if(Response.errordetails_size())           
            {                                          
                err.CopyFrom(Response.errordetails(0));
            }     
        }
    }
    else
    {
        retVal = CMAPI_ERROR;
        if(Response.errordetails_size())           
        {                                          
            err.CopyFrom(Response.errordetails(0));
        }     
    }
    return retVal;
}

int CMApiComponents::EnableERLFBF(bool Enable)
{
    // Deferred Implementation
    return INVALID_REQID;
}
bool CMApiComponents::IsERLBFEnabled()
{
    // Deferred Implementation
    return false;    //INVALID_REQID;
}

int CMApiComponents::SetLoadBalancingAlgorithm(string PeerGroupName, string LBAlgo,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: SetLoadBalancingAlgorithm");
    if (PeerGroupName.empty())
    {
        CLOG_DEBUG("SetLoadBalAlgo: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup *LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    LBAlgorithm *lbAlgo = LBPeerG->mutable_lbalgo();
    lbAlgo->set_lbmethod(LBAlgo);
    Request.set_requestid(MOD_PEERGROUP);
    //LBPeerGroupResp Response;
    return SendCMgrRequest(Request, false, Response);
}

int CMApiComponents::GetLoadBalancingAlgorithm(string PeerGroupName, string& AlgoType ,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetLoadBalancingAlgorithm");
    if (PeerGroupName.empty())
    {
        CLOG_DEBUG("GetLoadBalAlgo: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    Request.set_requestid(GET_PEERGROUP);
    LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, true, &Response);
    if (retVal == CMAPI_SUCCESS)
    {
        LBPeerGroup LBPeerGrp = Response.peergroups(0);
        LBAlgorithm LBAlgo = LBPeerGrp.lbalgo();
        AlgoType = LBAlgo.lbmethod();
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0));
    }

    return retVal;
}

int CMApiComponents::SetPCRFBinding(string PeerGroupName, bool Enable,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetLoadBalancingAlgorithm");
    if (PeerGroupName.empty())
    {
        CLOG_DEBUG("GetLoadBalAlgo: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    LBPeerG->set_enablepcrfbinding(Enable);
    Request.set_requestid(MOD_PEERGROUP);
    //LBPeerGroupResp Response;
    return SendCMgrRequest(Request, false, Response);
}

bool CMApiComponents::IsPCRFBindingEnabled(string PeerGroupName,ErrorDetails& err)
{
    bool retVal = true;
    CLOG_DEBUG(">CMApiComponents: IsPCRFBindingEnabled");
    if (PeerGroupName.empty())
    {
        CLOG_DEBUG("ISPCRFBindingEnabled: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    Request.set_requestid(GET_PEERGROUP);
    LBPeerGroupResp Response;
    if (SendCMgrRequest(Request, true, &Response) == CMAPI_SUCCESS)
    {
        LBPeerGroup LBPeerGrp = Response.peergroups(0);
        if (LBPeerGrp.enablepcrfbinding())
        {
            retVal = true;
        } else {
            retVal = false;
        }
    } else {
        retVal = false;
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    return retVal;
}

int CMApiComponents::AddPeerToPeerGroup(string PeerGroupName, LBPeer& Req,LBPeerGroupResp* Response)
{
    bool retVal = true;
    CLOG_DEBUG(">CMApiComponents: AddPeerToPeerGroup");
    if (PeerGroupName.empty())
    {
        CLOG_DEBUG("AddPeerToPeerGroup: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    LBPeer* newPeer = LBPeerG->add_lbpeers();
    newPeer->CopyFrom(Req);
    Request.set_requestid(ADD_PEERCONFIG);
    //LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, false, Response);
    return retVal;
}

int CMApiComponents::RemovePeerFromPeerGroup(string PeerGroupName, string LBPeerName, string RealmName,LBPeerGroupResp* Response)
{
    bool retVal = true;
    CLOG_DEBUG(">CMApiComponents: RemovePeerFromGroup");
    if (PeerGroupName.empty() || LBPeerName.empty())
    {
        CLOG_DEBUG("AddPeerToPeerGroup: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    LBPeer* newPeer = LBPeerG->add_lbpeers();
    newPeer->set_lbpeername(LBPeerName);
    newPeer->set_lbpeerrealm(RealmName);
    Request.set_requestid(DEL_PEERCONFIG);
    //LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, false, Response);
    return retVal;
}

int CMApiComponents::ModifyPeerConfig(string PeerGroupName, LBPeer& Req,LBPeerGroupResp* Response)
{
    bool retVal = true;
    CLOG_DEBUG(">CMApiComponents: ModifyPeer");
    if (!Req.IsInitialized() || !Req.has_lbpeername())
    {
        CLOG_DEBUG("ModifyPeerConfig: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname(PeerGroupName);
    LBPeer* mPeer = LBPeerG->add_lbpeers();
    mPeer->CopyFrom(Req);
    Request.set_requestid(MOD_PEERCONFIG);
    //LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, false, Response);
    return retVal;
}

/*
   int CMApiComponents::SetPeerWeightage(string LBPeerName, int Weight)
   {
   bool retVal = true;
   CLOG_DEBUG(">CMApiComponents: SetPeerWeightage");
   if (LBPeerName.isEmpty() || Weight <= 0) 
   {
   CLOG_DEBUG("SetPeerWeightage: Invalid Params Received");
   retVal = CMAPI_INVALIDPARAMS;
   return retVal;
   }

   LBPeerGroupReq *Request = new LBPeerGroupReq();
   LBPeerGroup*  LBPeerG = Request->add_peergroups();
   LBPeer* mPeer = LBPeerG->add_lbpeers();
   mPeer->set_lbpeername(LBPeerName);
   mPeer->set_lbpeerweight(Weight);
   LBPeerG->set_requestid(MOD_PEERCONFIG);
   retVal = SendErlbfRequest(Request);
   return retVal;
   }

   int CMApiComponents::GetPeerWeightage(string LBPeerName, int& Weightage)
   {
   int retVal = CMAPI_SUCCESS;
   CLOG_DEBUG(">CMApiComponents: GetPeerWeightage");
   if (LBPeerName.isEmpty()) 
   {
   CLOG_DEBUG("GetPeerWeightage: Invalid Params Received");
   retVal = CMAPI_INVALIDPARAMS;
   return retVal;
   }

   LBPeerGroupReq *Request = new LBPeerGroupReq();
   LBPeerGroup*  LBPeerG = Request->add_peergroups();
   LBPeer* mPeer = LBPeerG->add_lbpeers();
   mPeer->set_lbpeername(LBPeerName);
   LBPeerG->set_requestid(GET_PEERCONFIG);
   LBPeerConfigResp Response;
   retVal = SendCMgrRequest(Request, true, &Response);
   if (retVal == CMAPI_SUCCESS)
   {
   LBPeerGroup LBPeerG = Response->peergroups(0);
   LBPeer mPeer = LBPeerG.lbpeers(0);
   if ( mPeer.has_lbpeerweight() )
   {
   Weightage = mPeer.lbpeerweight();
   } else {
   retVal = CMAPI_ERROR;
   }
   }
   return retVal;
   }

   int CMApiComponents::SetPeerPriority(string LBPeerName, int Priority)
   {
   bool retVal = true;
   CLOG_DEBUG(">CMApiComponents: SetPeerPriority");
   if (LBPeerName.isEmpty() || Priority <= 0) 
   {
   CLOG_DEBUG("SetPeerWeightage: Invalid Params Received");
   retVal = CMAPI_INVALIDPARAMS;
   return retVal;
   }

   LBPeerGroupReq *Request = new LBPeerGroupReq();
   LBPeerGroup*  LBPeerG = Request->add_peergroups();
   LBPeer* mPeer = LBPeerG->add_lbpeers();
   mPeer->set_lbpeername(LBPeerName);
   mPeer->set_lbpeerpriority(Priority);
   LBPeerG->set_requestid(MOD_PEERCONFIG);
retVal = SendErlbfRequest(Request);
return retVal;
}

int CMApiComponents::GetPeerPriority(string LBPeerName, int& Priority)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetPeerPriority");
    if (LBPeerName.isEmpty()) 
    {
        CLOG_DEBUG("GetPeerPriority: Invalid Params Received");
        retVal = CMAPI_INVALIDPARAMS;
        return retVal;
    }

    LBPeerGroupReq *Request = new LBPeerGroupReq();
    LBPeerGroup*  LBPeerG = Request->add_peergroups();
    LBPeer* mPeer = LBPeerG->add_lbpeers();
    mPeer->set_lbpeername(LBPeerName);
    LBPeerG->set_requestid(GET_PEERCONFIG);
    LBPeerConfigResp Response;
    retVal = SendCMgrRequest(Request, true, &Response);
    if (retVal == CMAPI_SUCCESS)
    {
        LBPeerGroup LBPeerG = Response->peergroups(0);
        LBPeer mPeer = LBPeerG.lbpeers(0);
        if ( mPeer.has_lbpeerpriority() )
        {
            Priority = mPeer.lbpeerpriority();
        } else {
            retVal = CMAPI_ERROR;
        }
    }
    return retVal;
}
    */
int CMApiComponents::GetLBAlgorithmSchemes(LBAlgorithm_SuppComponentID CompID ,LBAlgorithms& Resp,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname("Dummy");
    Request.set_requestid(GET_LBALGO);
    LBAlgorithm* AlgoSch = LBPeerG->mutable_lbalgo();
    AlgoSch->set_lbmethod("Dummy");
    AlgoSch->set_suppcomponent(CompID);
    LBPeerGroupResp Response;
    if (SendCMgrRequest(Request, true, &Response) == CMAPI_SUCCESS)
    {
        int Num = Response.lbalgos_size();
        CLOG_DEBUG("Num REturned : %d", Num);
        if (Num > 0)
        {
            for (int i = 0; i < Num; i++)
            {
                LBAlgorithm* AlgoSch = Resp.add_lbalgos();
                AlgoSch->CopyFrom(Response.lbalgos(i));
            }
        }
    }
    else
    {
        retVal = Response.responseid();
        if(Response.errordetails_size())           
        {                                          
            err.CopyFrom(Response.errordetails(0));
        }     
    }
    return retVal;
}

int CMApiComponents::AddLBAlgorithmSchemes(LBAlgorithm& Req,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname("Dummy");
    LBAlgorithm* AlgoSch = LBPeerG->mutable_lbalgo();
    AlgoSch->CopyFrom(Req);
    Request.set_requestid(ADD_LBALGO);
    //LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, true, Response);
    if (retVal == CMAPI_SUCCESS)
    {
        CLOG_DEBUG("SuccessFully Added Algorithm ");
    }
    else
    {
        CLOG_DEBUG("Error Adding Algorithm ");
    }
    return retVal;
}

int CMApiComponents::DeleteLBAlgorithmSchemes(string LBAlgo,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname("Dummy");
    LBAlgorithm* AlgoSch = LBPeerG->mutable_lbalgo();
    AlgoSch->set_lbmethod(LBAlgo);
    Request.set_requestid(DEL_LBALGO);
    //LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, true, Response);
    if (retVal == CMAPI_SUCCESS)
    {
        CLOG_DEBUG("SuccessFully Deleted Algorithm ");
    }
    else
    {    
        CLOG_DEBUG("Error Deleting Algorithm ");
    }   

    return retVal;
}

int CMApiComponents::ModifyLBAlgorithmSchemes(LBAlgorithm& Req,LBPeerGroupResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    LBPeerGroupReq Request;
    LBPeerGroup*  LBPeerG = Request.add_peergroups();
    LBPeerG->set_lbpeergroupname("Dummy");
    LBAlgorithm* AlgoSch = LBPeerG->mutable_lbalgo();
    AlgoSch->CopyFrom(Req);
    Request.set_requestid(MOD_LBALGO);
    //LBPeerGroupResp Response;
    retVal = SendCMgrRequest(Request, true, Response);
    if (retVal == CMAPI_SUCCESS)
    {
        CLOG_DEBUG("SuccessFully Modified Algorithm ");
    }
    else
    {
        CLOG_DEBUG("Error Modifing Algorithm ");
    }
    return retVal;
}

// Call Backs Implementation.
// CallBack From DRE ERLBF


int CMApiComponents::IsResponseOK(LBPeerGroupResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(">CMApiComponents: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || 
            Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        LBPeerGroupResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        if ( Resp != NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMgrResponse->Set(StrVal);
        delete lCookie;
    }

    return retVal;
}


// CallBack From CONFIG MANAGER

int CMApiComponents::CMgrSetLBPeerConfigsRespCbk(LBPeerGroupResp *Resp)
{
    CLOG_DEBUG(">CMGR SetLBPeerConfigsRespCbk ");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        delete lCookie;
    }
    return retVal;
}


int CMApiComponents::CMgrGetLBPeerConfigsRespCbk(LBPeerGroupResp *Resp)
{
    CLOG_DEBUG(">CMGR GetLBPeerConfigsRespCbk ");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        delete lCookie;
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMgrResponse->Set(StrVal);
    }
    return retVal;
}



// Library API for ERLBF Component Statistics 
int CMApiComponents::GetPeerGroupStats(ERLBFPeerGroupStatsReq &Req,ERLBFPeerGroupStatsResp &resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetPeerGroupStats");
    if( Req.peergroupid_size() > 0 )
    {
        Req.set_requestid(GET_PEERGROUPSTATS);
        retVal = SendErlbfRequest(Req,&resp);
    }
    else{
        return CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMApiComponents::SendErlbfRequest(ERLBFPeerGroupStatsReq& Request,ERLBFPeerGroupStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    m_SendSuccess = true;
    CLOG_DEBUG("Sending GetPeerGroupStats Request to Erlbf");
    m_ErlbfStatsObj->FetchERLBFPeerGroupStats(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    CLOG_DEBUG("SendErlbfRequest:GetPeerGroupStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        ErrorDetails *err = resp->add_errordetails();
        retVal = CMAPI_MESSERROR;
        resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }
    if (m_CMgrResponse->Get(StrVal, m_waitTime))
    {
        CLOG_DEBUG("SendErlbfRequest:GetPeerGroupStats: Response Received");
        if(StrVal.empty())
        {
            return CMAPI_SRVERROR;
        }
        resp->ParseFromString(StrVal);
        if (resp->has_responseid())
        {
            retVal = resp->responseid();
        }
    } else {
        ErrorDetails *err = resp->add_errordetails();
        retVal = CMAPI_TIMEOUT;
        resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");

    }
    return retVal;
}

int CMApiComponents::GetSessionBindingStats(SessionBindingStatsReq &Req,SessionBindingStatsRsp &resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetSessionBindingStats");
    Req.set_requestid(GET_SESSBINDSTATS);
    retVal = SendErlbfRequest(Req,&resp);
    return retVal;
}

int CMApiComponents::ResetSessionBindingStats(SessionBindingStatsRsp &resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(">CMApiComponents: GetSessionBindingStats");
    SessionBindingStatsReq Req;
    Req.set_requestid(RESET_SESSBINDSTATS);
    retVal = SendErlbfRequest(Req,&resp);
    return retVal;
}

int CMApiComponents::SendErlbfRequest(SessionBindingStatsReq& Request,SessionBindingStatsRsp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    m_SendSuccess = true;
    CLOG_DEBUG("Sending GetPeerGroupStats Request to Erlbf");
    m_ErlbfStatsObj->FetchSessionBindingStats(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    CLOG_DEBUG("SendErlbfRequest:GetPeerGroupStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        ErrorDetails *err = resp->add_errordetails();
        retVal = CMAPI_MESSERROR;
        resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if (m_CMgrResponse->Get(StrVal, m_waitTime))
    {
        CLOG_DEBUG("SendErlbfRequest:GetPeerGroupStats: Response Received");
        if(StrVal.empty())
        {
            return CMAPI_SRVERROR;
        }
        resp->ParseFromString(StrVal);
        if (resp->has_responseid())
        {
            retVal = resp->responseid();
        }
    } else {
        ErrorDetails *err = resp->add_errordetails();
        retVal = CMAPI_TIMEOUT;
        resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");

    }
    return retVal;
}

//ERLBF Stats related Callbacks
int CMApiComponents::FetchERLBFPeerGroupStatsRespCbk(ERLBFPeerGroupStatsResp *Resp) {
    CLOG_DEBUG(">CMGR FetchERLBFPeerGroupStatsRespCbk ");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    { 
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        delete lCookie;
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMgrResponse->Set(StrVal);
    }
    return retVal;
}

int CMApiComponents::FetchSessionBindingStatsRespCbk(SessionBindingStatsRsp *Resp){
    CLOG_DEBUG(">CMGR FetchSessionBindingStatsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        delete lCookie;
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMgrResponse->Set(StrVal);
    }
    return retVal;
}

int CMApiComponents::IsResponseOK(ERLBFPeerGroupStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(">CMApiComponents: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        ERLBFPeerGroupStatsResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMgrResponse->Set(StrVal);
        delete lCookie;
    }

    return retVal;
}

int CMApiComponents::IsResponseOK(SessionBindingStatsRsp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(">CMApiComponents: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || !Resp->IsInitialized() ||
            Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        SessionBindingStatsRsp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        //int lReqID = (int) lCookie->ReqID;
        if ( Resp != NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMgrResponse->Set(StrVal);
        delete lCookie;
    }

    return retVal;
}

int CMApiComponents::ResetPeerGroupStats(ERLBFResetPeerGroupStatsReq& Req,ERLBFResetPeerGroupStatsResp &resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG("CMApiComponents: ResetPeerGroupStats");
    Req.set_requestid(RESET_PEERGROUPSTATS);
    retVal = SendErlbfRequest(Req,&resp);
    return retVal;
}

int CMApiComponents::SendErlbfRequest(ERLBFResetPeerGroupStatsReq& Request,ERLBFResetPeerGroupStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    m_SendSuccess = true;

    CLOG_DEBUG("Sending ResetPeerGroupStats Request to Erlbf");
    m_ErlbfStatsObj->ResetERLBFPeerGroupStats(Request,
            new CMAPICookie(Request.requestid(), (void *) &Request));
    CLOG_DEBUG("ResetErlbfRequest:GetPeerGroupStats: Waiting for Response");
    if(m_SendSuccess == false)
    {
        ErrorDetails *err = resp->add_errordetails();
        retVal = CMAPI_MESSERROR;
        resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if (m_CMgrResponse->Get(StrVal, m_waitTime))
    {
        CLOG_DEBUG("ResetErlbfRequest:GetPeerGroupStats: Response Received");
        if(StrVal.empty())
        {
            return CMAPI_SRVERROR;
        }
        resp->ParseFromString(StrVal);
        if (resp->has_responseid())
        {
            retVal = resp->responseid();
        }
    } else {
        ErrorDetails *err = resp->add_errordetails();
        retVal = CMAPI_TIMEOUT;
        resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    return retVal;
}

int CMApiComponents::IsResponseOK(ERLBFResetPeerGroupStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(">CMApiComponents: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL ||
            Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        ERLBFResetPeerGroupStatsResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        if ( Resp != NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMgrResponse->Set(StrVal);
        //LBResponses->Set(StrVal);
        delete lCookie;
    }

    return retVal;
}

int CMApiComponents::ResetERLBFPeerGroupStatsRespCbk(ERLBFResetPeerGroupStatsResp *Resp)
{
    CLOG_DEBUG(">ResetERLBFPeerGroupStatsRespCbk ");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        delete lCookie;
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMgrResponse->Set(StrVal);
    }
    return retVal;
}

int CMApiComponents::SendPeerGrpConfigResult(LBPeerGroupResp *Resp,CMAPIRes *result)
{
    CLOG_DEBUG("Product Configuration ReportResult");
    string StrVal;
    if (Resp != NULL)
    {
        //Resp->set_responseid(CMAPI_SUCCESS);
        Resp->SerializeToString(&StrVal);
        CLOG_DEBUG("LBPeerGroupResp Resp = %s",Resp->DebugString().c_str());
    }
    else
    {
        LBPeerGroupResp resp;
        resp.set_responseid(CMAPI_ERROR);
        resp.SerializeToString(&StrVal);
    }
    m_CMgrResponse->Set(StrVal);
    //Resp->set_responseid(CMAPI_SUCCESS);
    return 0;
}

int CMApiComponents::SendLogConfigResult(LoggerConfResp *Resp, CMAPIRes *result)
{
    CLOG_DEBUG("Product Configuration ReportResult");
    string StrVal;
    if(Resp !=NULL)
    {
        //Resp->set_responseid(CMAPI_SUCCESS);
        Resp->SerializeToString(&StrVal);
    }
    else
    {
        //Create Error object and set it
        CLOG_DEBUG("SendLogConfigResult: CMAPI  Error ");
        LoggerConfResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        ErrResp.SerializeToString(&StrVal);

        delete lCookie;
    }
    m_CMgrResponse->Set(StrVal);
    return 0;
}

int CMApiComponents::GetLogConfig(string& CompName, LoggerInfo& LogInfo,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    LoggerConfReq req;
    LoggerConfResp resp;
    std::string StrVal;
    int numOfCompo; 
    m_SendSuccess = true;

    CLOG_DEBUG("CMApiComponents:: GetLogConfig");
    req.set_requestid(GET_LOGGERCONFIG);
    if(!(CompName.empty()))
    {
        LoggerConf *loggerConf;
        loggerConf = req.add_loggerconfig();
        loggerConf->set_componentname(CompName);
    }

    m_CmgrObj->GetComponentLoggingConf(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("GetLogConfig::Waiting for Response");
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal); 
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMgrResponse->Get(StrVal); 
    CLOG_DEBUG("GetLogConfig::Response received");
    if(StrVal.empty())
    {
        retVal = CMAPI_ERROR;
    }
    else
    {
        resp.ParseFromString(StrVal);

        if(resp.responseid() == CMAPI_SUCCESS)
        {
            retVal = resp.responseid();
            CLOG_DEBUG("GetLogConfig::Successfully retuned LoggerConfig");
            numOfCompo = resp.loggerconfig_size();
            //In case of no records in DB then we are going to show message to user...hence 
            //reusing the same errorDEtails field for the same.
            if(numOfCompo == 0)
            {
                if(resp.errordetails_size())           
                {                                          
                    err.CopyFrom(resp.errordetails(0));
                }
            }
            for(int curCompo = 0; curCompo < numOfCompo ; curCompo++)
            {
                LoggerConf respLoggerConf = resp.loggerconfig(curCompo);
                LoggerConf *loggerConf = LogInfo.add_loggerconfig();
                loggerConf->CopyFrom(respLoggerConf);
            }
        }
        else
        {
            retVal = CMAPI_SRVERROR;
            CLOG_ERROR("GetLogConfig::No Loggerconfig returned");
            if(resp.errordetails_size())           
            {                                          
                err.CopyFrom(resp.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::GetLogConfig(string& CompName,bool useCurrentInstanceId, LoggerInfo& LogInfo,ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    LoggerConfReq req;
    LoggerConfResp resp;
    std::string StrVal;
    int numOfCompo; 
    m_SendSuccess = true;

    CLOG_DEBUG("CMApiComponents:: GetLogConfig");
    req.set_requestid(GET_LOGGERCONFIG);
    if(!(CompName.empty()))
    {
        LoggerConf *loggerConf;
        loggerConf = req.add_loggerconfig();
        loggerConf->set_componentname(CompName);
    }

    /*m_CmgrObj->GetComponentLoggingConf(req,
            new CMAPICookie(req.requestid(), (void *) &req));*/

    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, m_currentIntanceId};
    Stub::CmgrComponents cmgrObj(dest,0);
    cmgrObj.GetComponentLoggingConf(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("GetLogConfig::Waiting for Response");
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal); 
        err.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMgrResponse->Get(StrVal); 
    CLOG_DEBUG("GetLogConfig::Response received");
    if(StrVal.empty())
    {
        retVal = CMAPI_ERROR;
    }
    else
    {
        resp.ParseFromString(StrVal);

        if(resp.responseid() == CMAPI_SUCCESS)
        {
            retVal = resp.responseid();
            CLOG_DEBUG("GetLogConfig::Successfully retuned LoggerConfig");
            numOfCompo = resp.loggerconfig_size();
            //In case of no records in DB then we are going to show message to user...hence 
            //reusing the same errorDEtails field for the same.
            if(numOfCompo == 0)
            {
                if(resp.errordetails_size())           
                {                                          
                    err.CopyFrom(resp.errordetails(0));
                }
            }
            for(int curCompo = 0; curCompo < numOfCompo ; curCompo++)
            {
                LoggerConf respLoggerConf = resp.loggerconfig(curCompo);
                LoggerConf *loggerConf = LogInfo.add_loggerconfig();
                loggerConf->CopyFrom(respLoggerConf);
            }
        }
        else
        {
            retVal = CMAPI_SRVERROR;
            CLOG_ERROR("GetLogConfig::No Loggerconfig returned");
            if(resp.errordetails_size())           
            {                                          
                err.CopyFrom(resp.errordetails(0));
            }
        }
    }
    return retVal;
}
int CMApiComponents::GetComponentLoggingConfRespCbk(LoggerConfResp *Resp)
{
    CLOG_DEBUG(">CMGR GetComponentLoggingConfRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        delete lCookie;
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMgrResponse->Set(StrVal);
    }
    return 0;
}

int CMApiComponents::IsResponseOK(LoggerConfResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG(">CMApiComponents: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        LoggerConfResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMgrResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMApiComponents::SetLogConfig(LoggerInfo& LogInfo,LoggerConfResp* resp)
{
    int retVal = CMAPI_SUCCESS;
    LoggerConfReq req;
    //LoggerConfResp resp;
    string StrVal;
    int numOfCompo;
    m_SendSuccess = true;

    CLOG_DEBUG("CMApiComponents::SetLogConfig");
    req.set_requestid(SET_LOGGERCONFIG);
    numOfCompo = LogInfo.loggerconfig_size();
    if(numOfCompo > 0)
    {
        for(int curCompo = 0; curCompo < numOfCompo ; curCompo++)
        {
            LoggerConf *loggerConf = req.add_loggerconfig();
            loggerConf->CopyFrom((LogInfo.loggerconfig(curCompo)));
        }

        m_CmgrObj->SetComponentLoggingConf(req,
                new CMAPICookie(req.requestid(), (void *) &req));
        CLOG_DEBUG("SetLogConfig::Waiting for Response");
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            resp->set_responseid(retVal); 
            ErrorDetails *err=resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if (m_CMgrResponse->Get(StrVal, m_waitTime))
        { 
            CLOG_DEBUG("SetLogConfig::Response received");
            if(StrVal.empty())
            {
                retVal = CMAPI_ERROR;
            }
            else
            {
                resp->ParseFromString(StrVal);
                if(resp->responseid() == CMAPI_SUCCESS)
                {
                    retVal = resp->responseid();
                    CLOG_DEBUG("SetLogConfig::Successfully set LoggerConfig");
                }
                else
                {
                    retVal = CMAPI_SRVERROR;
                    CLOG_DEBUG("SetLogConfig::Error in setting the LoggerConfig");
                }
            }
        } else {
            retVal = CMAPI_TIMEOUT;
            resp->set_responseid(retVal); 
            ErrorDetails *err=resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    else
    {
        CLOG_ERROR("SetLogConfig::Invalid LoggerInfo parameters");
        retVal = CMAPI_INVALIDPARAMS;
    }  
    return retVal;
}


int CMApiComponents::SetComponentLoggingConfRespCbk(LoggerConfResp *Resp)
{
    CLOG_DEBUG(">CMGR SetComponentLoggingConfRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        delete lCookie;
    }
    return 0;
}

int CMApiComponents::SetLogChannel(string& CompName, LoggerConf_LogChannel Channel, LoggerConfResp* resp)
{
    int retVal = CMAPI_SUCCESS;
    LoggerConfReq req;
    //LoggerConfResp resp;
    LoggerConf *loggerConfig;
    string StrVal;
    m_SendSuccess = true;

    req.set_requestid(MOD_LOGGERCONFIG);
    if(!(CompName.empty()))
    {
        loggerConfig = req.add_loggerconfig();
        loggerConfig->set_componentname(CompName);
        loggerConfig->set_channel(Channel);

        m_CmgrObj->SetComponentLoggingConf(req,
                new CMAPICookie(req.requestid(), (void *) &req));
        CLOG_DEBUG("SetLogChannel::Waiting for Response");
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            resp->set_responseid(retVal); 
            ErrorDetails *err=resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if (m_CMgrResponse->Get(StrVal, m_waitTime)) 
        {
            CLOG_DEBUG("SetLogchannel::Response received");
            if(StrVal.empty())
            {
                retVal = CMAPI_ERROR;
            }
            else
            {
                resp->ParseFromString(StrVal);
                if(resp->responseid() == CMAPI_SUCCESS)
                {
                    retVal = resp->responseid();
                    CLOG_DEBUG("SetLogChannel::Successfull set the LogChannel");
                }
                else 
                {
                    retVal = CMAPI_SRVERROR;
                    CLOG_DEBUG("SetLogChannel::error in setting the LogChannel");
                }
            }
        } else {
            retVal = CMAPI_TIMEOUT;
            resp->set_responseid(retVal); 
            ErrorDetails *err=resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    else
    {
        CLOG_ERROR("SetLogChannel::No component name");
        retVal = CMAPI_INVALIDPARAMS;
    }  
    return retVal;
}

int CMApiComponents::SetLogLevel(string& CompName, LoggerConf_LogLevel Level,LoggerConfResp* resp)
{
    int retVal = CMAPI_SUCCESS;
    LoggerConfReq req;
    //LoggerConfResp resp;
    LoggerConf *loggerConfig;
    string StrVal;
    m_SendSuccess = true;

    req.set_requestid(MOD_LOGGERCONFIG);
    if(!(CompName.empty()))
    {
        loggerConfig = req.add_loggerconfig();
        loggerConfig->set_componentname(CompName);
        loggerConfig->set_level(Level);

        m_CmgrObj->SetComponentLoggingConf(req,
                new CMAPICookie(req.requestid(), (void *) &req));
        CLOG_DEBUG("SetLogLevel::Waiting for Response");
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            resp->set_responseid(retVal); 
            ErrorDetails *err=resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if (m_CMgrResponse->Get(StrVal, m_waitTime)) 
        {
            CLOG_DEBUG("SetLogLevel::Response received");
            if(StrVal.empty())
            {
                retVal = CMAPI_ERROR;
            }
            else
            {
                resp->ParseFromString(StrVal);
                if(resp->responseid() == CMAPI_SUCCESS)
                {
                    retVal = resp->responseid();
                    CLOG_DEBUG("SetLogLevel::Successfull set the LogChannel");
                }
                else 
                {
                    retVal = CMAPI_SRVERROR;
                    CLOG_DEBUG("SetLogLevel::error in setting the LogChannel");
                }

            }
        } else {
            retVal = CMAPI_TIMEOUT;
            resp->set_responseid(retVal); 
            ErrorDetails *err=resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    else
    {
        CLOG_ERROR("SetLogLevel::No component name");
        retVal = CMAPI_INVALIDPARAMS;
    }  
    return retVal;
}

void CMApiComponents::UpdateCurrentInstanceId(uint16_t newInstanceId)
{
    m_currentIntanceId = newInstanceId;
}
