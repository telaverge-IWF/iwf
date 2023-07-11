/* ********************************-*-CPP-*-***********************************
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

/**
 *
 *   @file  CMAPIDreConfig.cpp
 *
 *  @brief  Implementation Methods from DRE towards CMAPI Library
 *
 **/

#include <iwf_mess.h>
#include "CMAPIDreConfig.h"
#include "ErrorResp.h"
#include "dia_tracer.h"
#include "iwf.h"

using namespace eAccelero;
using namespace std;

CMAPIDreConfig::CMAPIDreConfig()
{
    // Register Server Methods
    // RegisterMethods();

    CLOG_DEBUG(">>CMAPIDreConfig Constructor");
    //Get pointer to Diameter Management Object; 
    m_diaMgtObj = DiaMgmt::GetDiaMgmt();
}

CMAPIDreConfig::~CMAPIDreConfig()
{

}

int CMAPIDreConfig::HandleLocalHostConfigReqs(LocalHostConfig *req,DRECfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(">>CMAPIDreConfig HandleLocalHostConfigReqs");
    int retVal = (int) CMAPI_SUCCESS;
    switch (req->operreqid())
    {
        // Request to set Local Host IP Address.
        case SET_HOSTIP:
            DLOG_DEBUG("CMAPIDreConfig SET_HOSTIP");
            LOCAL_HOST_INFO localHost;
            // Check if host IPAddress is provided. If yes get Local hostname
            // and realm info. Then Set the IPAddress of the Local Host
            if ( req->has_hostipaddr() && (m_diaMgtObj->GetLocalHostInfo(&localHost) == ITS_SUCCESS) )
            {
                // Required information is met, set the locahost IP Address
                DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Setting Local Host Configuration");
                /*
                if (m_diaMgtObj->SetLocalHostInfo((const char *) localHost.hostName,
                        (const char *) localHost.realmName, (const char *) localHost.ipAddr) != ITS_SUCCESS)
                {
                    // Failed to set the local host IP Address
                    DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Failed to Set Host IP Address");
                    retVal = (int) CMAPI_ERROR;
                }
                else
                {
                    DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Successfully Set IP Address ");
                }
                */
            }
            else
            {
                // Required Information is not provided
                DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Failed to Fetch Local Host Information");
                retVal = (int) CMAPI_ERROR;
            }    
            break;

            // Request to set the Local Host Information + ACCT and AUTH timers.
        case MOD_HOST:   
            retVal = ModifyLocalHost(req); 
            break;

        case SET_HOST: 
            DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : SET_HOST  ");
            retVal = SetLocalHost(req);
            break;

        case SET_AUTHTIMERS:
            // Set AuthSession Timer Values;
            // Check if AUTH timers information is provided.
            DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : SET_AUTHTIMERS ");
            if ( req->has_authsessiontimeout() && req->has_authsessionlifetime() && req->has_authsessiongraceperiod() )
            {
                // Yes, required information is available, then proceed to set
                // AUTH Timers Info.
                  DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Setting the AUTH Timers ");
                  if ( m_diaMgtObj->SetAuthSessionTimers(req->authsessionlifetime(), 
                              req->authsessiongraceperiod(), req->authsessiontimeout()) != ITS_SUCCESS) 
                  {
                      // Failed to set AUTH Timers
                      DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Failed to Set AUTH Timers");
                      retVal = CMAPI_ERROR;
                  }
            }
            break;

        case SET_ACCTTIMERS:
            // Set AcctSession Timers values
            // Check if ACCT Timers values are provided.
            DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : SET_ACCTTIMERS");
            if ( req->has_acctsessioninteriminterval() && req->has_acctsessiontimeout())
            {
                // Yes ACCT Timers Values are provided, Proceed to Set ACCT 
                // Timers Values.
                DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : SET_ACCTTIMERS : Setting ACCT Timers");
                  if ( m_diaMgtObj->SetAcctSessionTimers(req->acctsessioninteriminterval(), 
                              req->acctsessiontimeout()) != ITS_SUCCESS )
                  {
                      // Failed to set the ACCT Timer Values
                      DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : SET_ACCTTIMERS : Failed to Set ACCT Timers");
                      retVal = CMAPI_ERROR;
                  }
            }
            break;

        default:
            // Unsupported Operation
            DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : Invalid Request for Local Host Configuration");
            retVal = CMAPI_INVALIDPARAMS;
            break;
    }

    DLOG_DEBUG("CMAPIDreConfig HandleLocalHostConfigReqs : RespCode : %d", retVal);
    resp->set_respcode(retVal);
    return 0;
}

int CMAPIDreConfig::HandleDreSetPeerConfigReqs(PeersConfig *req,DRECfgResp *resp)
{
    // Assume operation will be Successful;
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(">>CMAPIDreConfig::HandleDreSetPeerConfigReqs");
    int retVal = (int) CMAPI_SUCCESS;
    //Initializing Uninitialized Scalar Variable
    int errorCode = MOD_PEER_ERR_MAX_ERROR;
    int totalPeers = req->peers_size();
    DLOG_DEBUG("CMAPIDreConfig::HandleDreSetPeerConfigReqs : Num Peers - %d", totalPeers);
    int reqID = req->operreqid();
    if ((reqID == GET_PEERSTATE) || (reqID == GET_PEER))
    {
        DLOG_DEBUG("Request to Get Peer States");
        GetAllPeersState(resp);
    }
    else if (totalPeers > 0)
    {
        int reqID = req->operreqid();
        if ((reqID == GET_PEERSTATE) || (reqID == GET_PEER))
        {
            DLOG_DEBUG("Request to Get Peer States");
            GetAllPeersState(resp);
        } else
        {
            for (int peerNo = 0; peerNo < totalPeers; peerNo++)
            {
                PeerConfig peerCfg = req->peers(peerNo);
                PEER_INFO peerInfo;
                try {
                    switch (reqID)
                    {
                        case MOD_PEER:
                            if ( peerCfg.has_peerhostname() && peerCfg.has_realm())
                            {
                                DIA_PEER_STATUS peerStatus;
                                peerInfo.peerName = (const char *) (peerCfg.peerhostname()).c_str();
                                peerInfo.realmName = (const char *) (peerCfg.realm()).c_str();
                                retVal = m_diaMgtObj->GetDiaPeerStatus((void *) &peerStatus, &peerInfo);
                                if ((retVal == ITS_SUCCESS) && (peerStatus.pState == PEER_CLOSED))
                                {  
                                    retVal = ModifyPeerConfig(peerCfg);
                                } 
                                else 
                                {
                                    ErrorDetails* err = resp->add_errordetails();
                                    if(peerStatus.isStatic == ITS_TRUE)
                                    {
                                        errorCode = MOD_PEER_ERR_PEER_STATICALLY_CONFIGURED;
                                    }
                                    else if(peerStatus.pState != PEER_CLOSED)
                                    {
                                        errorCode = MOD_PEER_ERR_PEER_IN_OPEN_STATE;
                                    }                       
                                    err->set_errorcode(errorCode);
                                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                    err->add_variables(peerCfg.peerhostname());
                                    err->add_variables(peerCfg.realm());
                                    retVal = CMAPI_SRVERROR;
                                }
                            }
                            else 
                            {
                                retVal = CMAPI_INVALIDPARAMS;
                            }
                            break;
                        case SET_PEER:
                            DLOG_DEBUG("CMAPIDreConfig::HandleDreSetPeerConfigReqs : Peers# - %d", peerNo);
                            if ( peerCfg.has_peerhostname() && peerCfg.has_realm())
                            {
                                retVal = AddPeerConfig(peerCfg);
                                if(retVal != ITS_SUCCESS)
                                {
                                    ErrorDetails* err = resp->add_errordetails();
                                    errorCode = retVal;
                                    err->set_errorcode(errorCode);
                                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                    err->add_variables(peerCfg.peerhostname());
                                    err->add_variables(peerCfg.realm());
                                    retVal = CMAPI_SRVERROR;
                                }
                            }
                            break;

                        case ADD_DICTID:
                            if ( peerCfg.has_peerhostname() && peerCfg.has_realm())
                            {
                                retVal = AddDictionaryID(&peerCfg);
                                if(retVal != ITS_SUCCESS)
                                {
                                    ErrorDetails* err = resp->add_errordetails();
                                    errorCode = retVal;
                                    err->set_errorcode(errorCode);
                                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                    err->add_variables(peerCfg.peerhostname());
                                    err->add_variables(peerCfg.realm());
                                    //err->add_variables(peerCfg.dictionaryname(*errCode));
                                    retVal = CMAPI_SRVERROR;
                                }
                            }
                            break;

                        case SET_PEERSTATUS:
                            // set PeerStatus
                            if ( peerCfg.has_peerhostname() && peerCfg.has_realm() &&  peerCfg.has_peerstatus())
                            {
                                retVal = ConfigPeerStatus((const char *) (peerCfg.peerhostname()).c_str(),
                                        (peerCfg.realm()).c_str(), peerCfg.peerstatus());
                                if(retVal != ITS_SUCCESS)
                                {
                                    ErrorDetails* err = resp->add_errordetails();
                                    errorCode = retVal;
                                    err->set_errorcode(errorCode);
                                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                    err->add_variables(peerCfg.peerhostname());
                                    err->add_variables(peerCfg.realm());
                                    retVal = CMAPI_SRVERROR;
                                }

                            }
                            break;
                        default:
                            break;
                    }
                } catch (...) {
                    // What to DO!!!???
                    DLOG_DEBUG("CMAPIDreConfig::HandleDreSetPeerConfigReqs : Exception ");
                }
            }
        }
    }
    DLOG_DEBUG("CMAPIDreConfig::HandleDreSetPeerConfigReqs : RespCode : %d", retVal);
    resp->set_respcode(retVal);
    return 0;
}

int CMAPIDreConfig::HandleDreDelPeerConfigReqs(PeersConfig *req,DRECfgResp *resp)
{
   ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
   DLOG_DEBUG(">>CMAPIDreConfig::HandleDreDelPeerConfigReqs ");
   int retVal = (int) CMAPI_SUCCESS;
   int errorCode;
   int totalPeers = req->peers_size();
   DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Num Peers: %d", totalPeers);
   if (totalPeers > 0)
   {
       for (int numPeer = 0; numPeer < totalPeers; numPeer++)
       {
           PeerConfig peer = req->peers(numPeer);
           try { 
               switch (req->operreqid())
               {
                   case DEL_PEER:
                       DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Deleting Peer# %d", numPeer);
                       if ((retVal = m_diaMgtObj->RemovePeer( (const char *) (peer.peerhostname()).c_str(),
                                   (const char *) (peer.realm()).c_str()) )!= ITS_SUCCESS)
                       {
                           DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Failed Deleting Peer");
                           ErrorDetails* err = resp->add_errordetails();
                           errorCode = retVal;
                           err->set_errorcode(errorCode);
                           err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                           err->add_variables(peer.peerhostname());
                           err->add_variables(peer.realm());
                           retVal = CMAPI_ERROR;
                           break;
                       }
                       else
                       {
                           //Delete the peer if it is part of any peer group
                           /*DREController::Instance().DelPeerFromPeerGroup(peer.peerhostname().c_str(),
                                                                          peer.realm().c_str()); 
                            */
                       }

                       DESTINATION_INFO dstInfo;
                       if((m_diaMgtObj->GetDefaultRoute(&dstInfo) == ITS_SUCCESS))
                       {
                           DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs : checking for defaultroute (peer=%s,default-peer=%s)",peer.peerhostname().c_str(),dstInfo.peerName);
                           if(!dstInfo.peerName)
                           {
                               DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs : triggering defaultroute deletion");
                               if(m_diaMgtObj->RemoveDefaultRoute() != ITS_SUCCESS)
                               {
                                   //Not setting/sending error, as it will cause more difference in the db and dre.
                                   DLOG_ERROR("Failed to delete the default-Route (realm=%s,peer=%s)",dstInfo.realmName,dstInfo.peerName);
                               }
                               else
                               {
                                   DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs : Successfully deleted default-route");
                               }
                           }
                       }

                       break;

                   case DEL_DICTID:
                        if ( peer.has_peerhostname() && peer.has_realm())
                       {
                           retVal = DeleteDictionaryID(&peer);
                       }
                       break;

                   case DEL_ALTPEER:
                       if ( peer.has_peerhostname() && peer.has_realm())
                       {
                           if (m_diaMgtObj->RemoveAlternatePeer((const char *) (peer.peerhostname()).c_str(),
                                   (const char *) (peer.realm()).c_str()) == ITS_SUCCESS)
                           {
                               DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: ALT PEER REMOVED");
                               retVal = CMAPI_SUCCESS;
                           } else {
                               DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: ALT PEER REMOVAL FAILED");
                               retVal = CMAPI_SRVERROR;
                           }

                       } else {
                           DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Invalid Params to Delete Alternate Peer");
                           retVal = CMAPI_INVALIDPARAMS;
                       }
                       break;
                    case DEL_SECIP:
                       if ( peer.has_peerhostname() && peer.has_realm()&& peer.secondaryipaddr_size()>0)
                       {
                           char *multiHomeIpAddrs[4] = {NULL};
                           int noIPs = 0;

                           for(int i = 0;i < peer.secondaryipaddr_size();i++)
                           {
                               std::string * secondaryIpAddrs = peer.mutable_secondaryipaddr(i);
                               DLOG_DEBUG("Delete Secondary ip addrs %s for Peer %s",
                               secondaryIpAddrs->c_str(),peer.peerhostname().c_str());

                               multiHomeIpAddrs[i]= strdup(secondaryIpAddrs->c_str());
                               noIPs++;
                           }
                           int returnValue; 
                           if ((returnValue=m_diaMgtObj->RemoveSecondaryIp((char *) (peer.peerhostname()).c_str(),
                                   (const char *) (peer.realm()).c_str(),multiHomeIpAddrs,noIPs)) == ITS_SUCCESS)
                           {
                               DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Secondary Ip removed");
                               retVal = CMAPI_SUCCESS;
                           }
                           else
                           {
                               ErrorDetails* err = resp->add_errordetails();
                               errorCode = returnValue;
                               err->set_errorcode(errorCode);
                               err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                               err->add_variables(peer.peerhostname());
                               err->add_variables(peer.realm());
                               retVal = CMAPI_ERROR;
                               if(returnValue == DEL_SECONDARYIP_ERR_PEER_NOT_IN_CLOSED_STATE)
                               {
                                    DLOG_ERROR("Secondary Ip remove failed since %s peer is not in closed state",peer.peerhostname().c_str());
                               }
                               else if(returnValue == DEL_SECONDARYIP_ERR_UNKNOWN_PEER)
                               {
                                   DLOG_ERROR("Secondary Ip remove failed since %s peer is not configured",peer.peerhostname().c_str());
                               }
                           }
                           for(int i=0;i< noIPs;i++)
                           {
                               free(multiHomeIpAddrs[i]);
                           }   
                       }
                 
                       else
                       {
                            DLOG_WARNING("Invalid parameters to delete secondary ip");
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = DEL_SECONDARYIP_ERR_NOT_ALL_PARAMETERS_PRESENT;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(peer.peerhostname());
                            err->add_variables(peer.realm());
                            retVal = CMAPI_ERROR;
                       }
                       break;
                   default:
                       DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Invalid Request");
                       retVal = CMAPI_INVALIDPARAMS;
               }
           } catch (...) {
               // What to DO!!!??
               DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: Exception ");
           }
       }
   }
   DLOG_DEBUG("CMAPIDreConfig::HandleDreDelPeerConfigReqs: RespCode %d", retVal);
   resp->set_respcode(retVal);
   return 0;
}

int CMAPIDreConfig::HandleDreSetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp)
{
   ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
   DLOG_DEBUG(">>CMAPIDreConfig::HandleDreSetRealmConfigReqs");
   int retVal = (int) CMAPI_SUCCESS;
   int TotalRealms = req->realms_size();
   int Dests = 0;
   DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Total Realms %d", TotalRealms);
   if ( TotalRealms > 0 )
   {
       try {
             int ReqID = req->operreqid();
             for (int NumRealm  = 0; NumRealm < TotalRealms; NumRealm++)
             {
                 RealmConfig realm = req->realms(NumRealm);
                 DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Total Dests %d", Dests);
                 switch (ReqID)
                 {
                     case MOD_REALM:
                         if (realm.has_realmname())
                         {
                             retVal = ModifyRealmConfig(realm);
                             Dests = (int) realm.destinfo_size();
                             if (Dests > 0)
                             {
                                 for (int NumDest = 0; NumDest < Dests; NumDest++)
                                 {
                                     Destination Dest = realm.destinfo(NumDest);
                                     retVal = ModifyRealmRouting(realm.realmname(), Dest);
                                 }
                             }
                         }
                         break;

                     case MOD_DEST:
                          if (realm.has_realmname())
                         {
                             Dests = (int) realm.destinfo_size();
                             if (Dests > 0)
                             {
                                 for (int NumDest = 0; NumDest < Dests; NumDest++)
                                 {
                                     Destination Dest = realm.destinfo(NumDest);
                                     retVal = ModifyRealmRouting(realm.realmname(), Dest);
                                 }
                             }
                         }
                         break;
                         
                     case SET_REALM:
                         DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Adding Realm# %d", NumRealm);
                          if (realm.has_realmname())
                         {
                             retVal = AddRealmConfig(realm);
                         }
                         break;

                     case SET_DEST: 
                         if (realm.has_realmname())
                         {
                             Dests = (int) realm.destinfo_size();
                             if (Dests > 0)
                             {
                                 for (int NumDest = 0; NumDest < Dests; NumDest++)
                                 {
                                     Destination Dest = realm.destinfo(NumDest);
                                     retVal = AddRealmRouting(realm.realmname(), Dest);
                                     if(retVal != ITS_SUCCESS)
                                     {
                                         ErrorDetails* err = resp->add_errordetails();
                                         err->set_errorcode(retVal);
                                         err->set_errormsgkey(IwfMeSS::errorMap[retVal]);
                                         err->add_variables(realm.realmname());
                                         err->add_variables(Dest.peername());
                                         retVal = CMAPI_SRVERROR;
                                     }
                                 }
                             }
                         }
                         break;
                     case ENBPXYIAVP: 
                         DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Enabling Proxy AVP");
                         if (m_diaMgtObj->SetProxyInfoAVPEnabled(
                                     (const char *) (realm.realmname()).c_str(), ITS_TRUE ) != ITS_SUCCESS)
                         {
                             DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : FAILED Enabling Proxy AVP");
                             retVal = CMAPI_ERROR;
                         }
                         // Fall Though for SET REALM Request Is the below
                         // required ??!! TBD!
                         // if (ReqID == ENBPXYIAVP) { break; }
                         break;
                     case DISPXYIAVP:
                         DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Disabling Proxy AVP");
                         if (m_diaMgtObj->SetProxyInfoAVPEnabled(
                                     (const char *) (realm.realmname()).c_str(), ITS_FALSE ) != ITS_SUCCESS)
                         {
                             DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : FAILED Disabling Proxy AVP");
                             retVal = CMAPI_ERROR;
                         }
                         break;
                     case MOD_DEFROUTE:
                         DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Modify Default Route request");
                         DESTINATION_INFO dstInfo;
                         if ( (m_diaMgtObj->GetDefaultRoute(&dstInfo) == ITS_SUCCESS) && 
                              (m_diaMgtObj->RemoveDefaultRoute() == ITS_SUCCESS) 
                            )
                         {
                             DLOG_DEBUG("Modify Default Route request : Setting to Old Default Route");
                             if (m_diaMgtObj->SetDefaultRoute((const char *) (realm.defaultroute()).c_str(),
                                         (const char *) (realm.realmname()).c_str()) != ITS_SUCCESS)
                             {
                                 retVal = CMAPI_ERROR;
                             } else {
                                 DLOG_DEBUG("Modify Default Route request : Reverting back to old defaultroute");
                                 m_diaMgtObj->SetDefaultRoute((const char *) (dstInfo.peerRealm),
                                         (const char *) (dstInfo.peerName));
                             }
                         }
                         break;
                     case SET_DEFROUTE:
                       DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Setting Default Route ");
                       if (m_diaMgtObj->SetDefaultRoute((const char *) (realm.defaultroute()).c_str(),
                                   (const char *) (realm.realmname()).c_str()) != ITS_SUCCESS)
                       {
                           DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Failed Setting Default Route ");
                           retVal = CMAPI_ERROR;
                       }
                       break;
                    default:
                         DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : Invalid Request");
                         break;
                 }
             } 
       } catch (...) {
           // What to DO!!!??
           DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : EXCEPTION");
           
       }
   }
   DLOG_DEBUG("CMAPIDreConfig::HandleDreSetRealmConfigReqs : RespCode %d", retVal);
   resp->set_respcode(retVal);
   return 0;
}

int CMAPIDreConfig::HandleDreDelRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(">>CMAPIDreConfig::HandleDreDelRealmConfigReqs ");
    // Assume Operation will be successful
    int retVal = (int) CMAPI_SUCCESS;
    int TotalRealms = req->realms_size();

    DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Num Realms %d", TotalRealms);
    if (TotalRealms > 0)
    {
        for (int NumRealm = 0; NumRealm < TotalRealms; NumRealm++)
        {
            RealmConfig realm = req->realms(NumRealm);
            int reqID = req->operreqid();
            int NumDests = realm.destinfo_size();

            try {
                // What is requested !!?
                switch (reqID)
                {
                    // Delete the REALM Information Request
                    case DEL_DEST:
                        if (realm.has_realmname())
                        {
                            NumDests = (int) realm.destinfo_size();
                            if (NumDests > 0)
                            {
                                for (int NumDest = 0; NumDest < NumDests; NumDest++)
                                {
                                    Destination Dest = realm.destinfo(NumDest);
                                    retVal = DeleteRealmRouting(realm.realmname(), Dest);
                                    if(retVal != ITS_SUCCESS)
                                    {
                                        ErrorDetails* err = resp->add_errordetails();
                                        err->set_errorcode(retVal);
                                        err->set_errormsgkey(IwfMeSS::errorMap[retVal]);
                                        err->add_variables(Dest.peername());
                                        err->add_variables(realm.realmname());
                                        retVal = CMAPI_ERROR;            
                                    }
                                }
                            }
                        }
                        break;

                    case DEL_REALM:

                        DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Deleting Realm# %d", NumRealm);
                        // Get number of Realms to be deleted.
                        // Delete all the requested number of realms
                        if ((retVal = m_diaMgtObj->RemoveRealm((const char *) (realm.realmname()).c_str())) != ITS_SUCCESS)
                        {
                            // Failure to delete REALM Information
                            DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : FAILED Deleting Realm");
                            ErrorDetails* err = resp->add_errordetails();
                            err->set_errorcode(retVal);
                            err->set_errormsgkey(IwfMeSS::errorMap[retVal]);
                            err->add_variables(realm.realmname());
                            retVal = CMAPI_ERROR;
                            break;
                        }
                        DESTINATION_INFO dstInfo;
                        if((m_diaMgtObj->GetDefaultRoute(&dstInfo) == ITS_SUCCESS))
                        {
                             DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : checking for defaultroute (default-realm %s realm %s)",dstInfo.peerRealm,realm.realmname().c_str());
                            if(strcasecmp(realm.realmname().c_str(),dstInfo.peerRealm) == 0)
                            {
                                DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : triggering defaultroute deletion");
                                if(m_diaMgtObj->RemoveDefaultRoute() != ITS_SUCCESS)
                                {
                                    //Not setting/sending error, as it will cause more difference in the db and dre.
                                    DLOG_ERROR("Failed to delete the default-Route (realm=%s,peer=%s)",dstInfo.peerRealm,dstInfo.peerName);
                                    DLOG_DEBUG("Deleting Default Route request : Reverting back to old defaultroute");
                                    m_diaMgtObj->SetDefaultRoute((const char *) (dstInfo.peerRealm),
                                            (const char *) (dstInfo.peerName));
                                }
                                else
                                {
                                    DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Successfully deleted default-route");
                                }
                            }
                            else
                            {
                                DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : defaultroute-realm %s realm %s",dstInfo.peerRealm,realm.realmname().c_str());
                            }
                        }
                        break;
                    case DEL_DEFROUTE:
                        DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Deleting Default Route ");
                        if (m_diaMgtObj->RemoveDefaultRoute() != ITS_SUCCESS)
                        {
                            DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Deleting Default Route - FAILED");
                            retVal = CMAPI_ERROR;
                        }
                        break;
                    default:
                        DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Invalid Request");
                        retVal = CMAPI_INVALIDPARAMS;
                        break;
                }
            } catch (...) {
                // What to DO!!!??
                DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : EXCEPTION "); 
            }
        }
    }
    else
    {
        int reqID = req->operreqid();
        switch(reqID)
        {
            case DEL_DEFROUTE:
                DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Deleting Default Route ");
                if (m_diaMgtObj->RemoveDefaultRoute() != ITS_SUCCESS)
                {
                    DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : Deleting Default Route - FAILED");
                    retVal = CMAPI_ERROR;
                }
                break;
            default:
                break;
        }
    }
    DLOG_DEBUG("CMAPIDreConfig::HandleDreDelRealmConfigReqs : RespCode %d", retVal);
    resp->set_respcode(retVal);
    return 0;
}

int CMAPIDreConfig::HandleStaticRoutingTableConfigReqs(StaticRoutingTableConfigReq* req,
                                                       StaticRoutingTableConfigResp* resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(">>CMAPIDreConfig::HandleStaticRoutingTableConfigReqs");
    // Assume operation will be Successful;
    int retVal = (int) CMAPI_SUCCESS;
    int numOfEntries = req->srtconfig_size();
    int reqID = req->requestid();

    DLOG_DEBUG("CMAPIDreConfig::HandleStaticRoutingTableConfigReqs: Num Entries:%d", numOfEntries);

    for (int i = 0; i < numOfEntries; i++)
    {
         StaticRoutingTableConfig staticRoutingCfg = req->srtconfig(i);
         switch (reqID)
         {
              case MOD_SRCONFIG:
                   DLOG_DEBUG(" Modify static routing Request for destHost %s and peer %s",
                               staticRoutingCfg.destionatinhost().c_str(),staticRoutingCfg.peer().c_str());
                   if(staticRoutingCfg.has_destionatinhost() && staticRoutingCfg.has_peer() && 
                      staticRoutingCfg.priority())
                   {
                        int applicationId = 0;
                        if(staticRoutingCfg.has_applicationid())
                        {
                            applicationId = staticRoutingCfg.applicationid();
                        }
                        retVal = m_diaMgtObj->ModifyStaticRoutingPriority(staticRoutingCfg.destionatinhost().c_str(),
                                                                          staticRoutingCfg.peer().c_str(),
                                                                          staticRoutingCfg.priority(),
                                                                          applicationId);
                        if(retVal == ITS_SUCCESS)
                        {
                             DLOG_DEBUG("Modify static routing successful");
                        }
                        else
                        {
                             DLOG_DEBUG("Modify static routing errorCode = %d", retVal);
                             retVal = DreStaticRoutingErrorConfig(retVal, staticRoutingCfg, resp);
                        }
                    }
                    else 
                    {
                        retVal = MOD_STATIC_ROUTING_MANDATORY_DESTHOST_PEERNAME_MISSING;
                        retVal = DreStaticRoutingErrorConfig(retVal, staticRoutingCfg, resp);
                    }
                    break;
                                                        
                    case SET_SRCONFIG:
                         DLOG_DEBUG("Set static routing Request for destHost %s and peer %s",
                                     staticRoutingCfg.destionatinhost().c_str(),staticRoutingCfg.peer().c_str());     
                         if(staticRoutingCfg.has_destionatinhost() && staticRoutingCfg.has_peer())
                         {
                              int applicationId = 0;
                              if(staticRoutingCfg.has_applicationid())
                              {
                                  applicationId = staticRoutingCfg.applicationid();
                              }

                              retVal=m_diaMgtObj->AddStaticRoutingConfig(staticRoutingCfg.destionatinhost().c_str(),
                                                              staticRoutingCfg.destionatinrealm().c_str(),
                                                              staticRoutingCfg.peer().c_str(),
                                                              staticRoutingCfg.realm().c_str(),
                                                              applicationId,
                                                              staticRoutingCfg.priority());
                              if(retVal != ITS_SUCCESS)
                              {
                                  DLOG_DEBUG("Add static routing entry failed errorCode = %d", retVal);
                                  retVal = DreStaticRoutingErrorConfig(retVal, staticRoutingCfg, resp);
                              }
                         }
                         else 
                         {
                              DLOG_ERROR("SET_SRCONFIG : Mandatory Parameter missing ..!!");
                              retVal = ADD_STATIC_ROUTING_MANDATORY_PARAMETERS_MISSING;
                              retVal = DreStaticRoutingErrorConfig(retVal, staticRoutingCfg, resp);
                         }
                         break;

                    case DEL_SRCONFIG:
                         DLOG_DEBUG("Delete static routing Request for destHost %s and peer %s",
                                     staticRoutingCfg.destionatinhost().c_str(),staticRoutingCfg.peer().c_str());
                         if(staticRoutingCfg.has_destionatinhost() && staticRoutingCfg.has_peer())
                         {
                             int applicationId = 0;
                             if(staticRoutingCfg.has_applicationid())
                             {
                                 applicationId = staticRoutingCfg.applicationid();
                             }

                             retVal = m_diaMgtObj->DeleteStaticRoutingEntry(staticRoutingCfg.destionatinhost().c_str(),
                                                               staticRoutingCfg.peer().c_str(),applicationId);
                             if(retVal != ITS_SUCCESS)
                             {       
                                  DLOG_DEBUG("Delete static routing Failed errorCode = %d", retVal);
                                  retVal = DreStaticRoutingErrorConfig(retVal, staticRoutingCfg, resp);
                             }
                         }
                         else
                         {
                             DLOG_ERROR("SET_SRCONFIG : Mandatory Parameter missing ..!!");
                             retVal = DEL_STATIC_ROUTING_MANDATORY_DESTHOST_PEERNAME_MISSING;
                             retVal = DreStaticRoutingErrorConfig(retVal, staticRoutingCfg, resp);
                         }
                         break;

                    default :
                         DLOG_DEBUG("CMAPIDreConfig::HandleStaticRoutingTableConfigReqs: Invalid Request");
                         retVal = CMAPI_INVALIDPARAMS;
                         break;
         }
    } 
    DLOG_DEBUG("CMAPIDreConfig::HandleStaticRoutingTableConfigReqs: RespCode %d", retVal);
    resp->set_responseid(retVal);
    return 0;
}

int CMAPIDreConfig::HandleTraceConfigReqs(TraceReq *req, TraceResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(">>CMAPIDreConfig::HandleTraceConfigReqs");
    // Assume operation will be Successful;
    int retVal = (int) CMAPI_SUCCESS;
    int errorCode = 0;
    bool traceStatus = 0;
    int totaltracedata = req->tracedata_size();

    DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs : Num filters - %d", totaltracedata);
    int reqID = req->requestid();

    if(reqID == ENABLE_TRACE)
    {
        if(req->has_enabletrace())
        {
            traceStatus = req->enabletrace();
            DiaTracer::SetTraceStatus(traceStatus);
        }
        else
        {
            DLOG_ERROR("Trace status not present in the Configuration");
            errorCode = ENABLE_TRACECONFIG_ERR_MANDATORY_PARAM_ENABLE_MISSING;
            ErrorDetails* err = resp->add_errordetails();
            err->set_errorcode(errorCode);
            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
            retVal = CMAPI_SRVERROR;
        }
     }
     else  
     {
         if(totaltracedata > 0)
         {
             try {
                 for (int FilterNo = 0; FilterNo < totaltracedata; FilterNo++)
                 {
                     TraceConfig tracecfg = req->tracedata(FilterNo);
                     switch (reqID)
                     {
                         case MOD_TRACE:
                             DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs : Modify Request");
                             if(tracecfg.has_filtername())
                             {
                                 retVal = ModifyTraceConfig(tracecfg);
                                 if(retVal != ITS_SUCCESS)
                                 {
                                     DLOG_DEBUG("ModifyTraceConfig Failed errorCode = %d", retVal);
                                     retVal = DreTraceErrorConfig(retVal, tracecfg, resp);
                                 }
                             }
                             else 
                             {
                                 DLOG_ERROR("MOD_TRACE : Mandatory Parameter filter-name missing ..!!");
                                 retVal = MOD_TRACECONFIG_ERR_MANDATORY_PARAM_FILTERNAME_MISSING;
                                 retVal = DreTraceErrorConfig(errorCode, tracecfg, resp);
                             }
                             break;
                                                         
                         case SET_TRACE:
                             DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs : FilterNo.# - %d", FilterNo);     
                             if(tracecfg.has_filterid() && tracecfg.has_filtername())
                             {
                                 retVal = AddTraceConfig(tracecfg);
                                 if(retVal != ITS_SUCCESS)
                                 {
                                     DLOG_DEBUG("AddTraceConfig Failed errorCode = %d", retVal);
                                     retVal = DreTraceErrorConfig(retVal, tracecfg, resp);
                                 }
                             }
                             else 
                             {
                                 DLOG_ERROR("SET_TRACE : Mandatory Parameter filter-name missing ..!!");
                                 retVal = SET_TRACECONFIG_ERR_MANDATORY_PARAM_FILTERNAME_MISSING;
                                 retVal = DreTraceErrorConfig(errorCode, tracecfg, resp);
                             }
                             break;

                         case DEL_TRACE:
                                 DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs: Deleting Filter# %s", tracecfg.filtername().c_str());

                                 retVal = DeleteTraceConfig(tracecfg);
                                 if(retVal != ITS_SUCCESS)
                                 {       
                                     DLOG_DEBUG("DeleteTraceConfig Failed errorCode = %d", retVal);
                                     retVal = DreTraceErrorConfig(retVal, tracecfg, resp);
                                 }
                             break;

                         default :
                             DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs: Invalid Request");
                             retVal = CMAPI_INVALIDPARAMS;
                             break;
                     }
                 } 
             } catch (...) {
                     // What to DO!!!??
                     retVal = CMAPI_SRVERROR;
                     DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs: EXCEPTION "); 
               }
         }
     }
    DLOG_DEBUG("CMAPIDreConfig::HandleTraceConfigReqs: RespCode %d", retVal);
    resp->set_responseid(retVal);
    return 0;
}

int CMAPIDreConfig::GetTraceConfigReqs(TraceReq *req, TraceResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int errorCode = 0;
    string filtername = "";
    TraceConfig tracecfg;
    TraceConfig *rspTraceCfg = NULL;
    map<string,int> traceData;

    int totaltracedata = req->tracedata_size();
    DLOG_DEBUG("CMAPIDreConfig::GetTraceConfigReqs : Num filters - %d", totaltracedata);

    if(totaltracedata > 0)
    {
        for (int FilterNo = 0; FilterNo < totaltracedata; FilterNo++)
        {
            tracecfg = req->tracedata(FilterNo);
            if(tracecfg.has_filtername())
            {
                filtername = tracecfg.filtername();
                DiaTracer::GetTraceStatus(filtername,traceData);
                rspTraceCfg = resp->add_tracedata();
                rspTraceCfg->set_filtername(filtername);
                map<string,int>::iterator it = traceData.find(filtername);
                rspTraceCfg->set_filterstatus(it->second);

            }
            else
            {
                DLOG_ERROR("SET_TRACE : Mandatory Parameter filter-name missing ..!!");
                retVal = SET_TRACECONFIG_ERR_MANDATORY_PARAM_FILTERNAME_MISSING;
                retVal = DreTraceErrorConfig(errorCode, tracecfg, resp);
            }
        }
     }
    else
    {
        DiaTracer::GetTraceStatus(filtername,traceData);
        map<string,int>::iterator it;
        for (it = traceData.begin(); it != traceData.end(); ++it)
        {
            rspTraceCfg = resp->add_tracedata();
            rspTraceCfg->set_filtername(it->first);
            rspTraceCfg->set_filterstatus(it->second);
        }
    }
    resp->set_responseid((int)CMAPI_SUCCESS);

    return 0;
}

int CMAPIDreConfig::ModifyTraceConfig(TraceConfig& tracecfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    char *filtStatus = NULL; 
    string Rule = "";
    int Priority = -1, expDuration = -1, expMsg = -1;
    string logLevel = "";
    string filterName = "";
    DLOG_DEBUG("In CMAPIDreConfig::ModifyTraceConfig to modify filter : %s", tracecfg.filtername().c_str());
    if(tracecfg.has_filtername())
    {
        filterName = tracecfg.filtername();
        if(tracecfg.has_rule())
        {
            Rule = tracecfg.rule();
        }
        if(tracecfg.has_priority())
        {
            Priority = tracecfg.priority();
        }
        if(tracecfg.has_filterstatus())
        {
            filtStatus = const_cast<char *>(tracecfg.filterstatus() ? "true" : "false");
        }
        if(tracecfg.has_loglevel())
        {
            logLevel = static_cast<ostringstream*>( &(ostringstream() << (tracecfg.loglevel())) )->str();
        }
        if(tracecfg.has_expireduration())
        {
            expDuration = tracecfg.expireduration();
        }
        if(tracecfg.has_expiremessages())
        {
            expMsg= tracecfg.expiremessages();
        }
            retVal = DiaTracer::ModifyTracer(filterName, Rule, Priority, filtStatus, logLevel, expDuration, expMsg);
            if(retVal == CMAPI_SUCCESS)
            DLOG_DEBUG("CMAPIDreConfig::ModifyTraceConfig : Modify Tracer success");
    }
    else
    {
        DLOG_ERROR("filter name to be modified is not passed");
        retVal = MOD_TRACECONFIG_ERR_MANDATORY_PARAM_FILTERNAME_MISSING;
    }
       return retVal; 
        
}

int CMAPIDreConfig:: AddTraceConfig(TraceConfig& tracecfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    bool filtStatus; 
    int filterId; 
    string Rule = "";
    int Priority, expDuration = -1, expMsg = -1;
    string logLevel = "";
    string filterName = "";
    DLOG_DEBUG("In CMAPIDreConfig::AddTraceConfig to add filtername : %s",tracecfg.filtername().c_str());


    if(tracecfg.has_filterid() && tracecfg.has_filtername() && tracecfg.has_rule() && tracecfg.has_priority()
                  && tracecfg.has_filterstatus() && tracecfg.has_loglevel())
    {
        if(tracecfg.has_expireduration() || tracecfg.has_expiremessages())
        {
            filterId = tracecfg.filterid();
            filterName = tracecfg.filtername();
            Rule = tracecfg.rule();
            Priority = tracecfg.priority();
            if(tracecfg.has_expireduration())
            {
                expDuration = tracecfg.expireduration();
            }
            else
            {
                expMsg = tracecfg.expiremessages();
            }
            filtStatus = tracecfg.filterstatus();
            logLevel = static_cast<ostringstream*>( &(ostringstream() << (tracecfg.loglevel())) )->str();

            retVal = DiaTracer::Configure(filterId, filterName, Rule, Priority, filtStatus, logLevel, expDuration, expMsg);
        }
        else
        {
            DLOG_ERROR("Expire Duration and Expire Message both are not configured :");
            retVal = SET_TRACECONFIG_ERR_MANDATORY_PARAM_MISSING;
        }
    } 
    else 
    {
        DLOG_ERROR("Some Parameters are not configured :");
        retVal = SET_TRACECONFIG_ERR_MANDATORY_PARAM_MISSING;
    }
    return retVal;
}

int CMAPIDreConfig:: DeleteTraceConfig(TraceConfig& tracecfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    string filterName = "";
    DLOG_DEBUG("In CMAPIDreConfig::DeleteTraceConfig to delete filter %s : ", tracecfg.filtername().c_str());
    if(tracecfg.has_filtername())
    {
        filterName = tracecfg.filtername();
        retVal = DiaTracer::RemoveTracer(filterName);
    }
    else
    {
        DLOG_ERROR("FilterName to remove is not passed :");
        retVal = DEL_TRACECONFIG_ERR_MANDATORY_PARAM_FILTERNAME_MISSING;
    }
    return retVal;
}
    
bool CMAPIDreConfig::IsSameLocalHost(string lhost)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    bool bResult = true;
    LOCAL_HOST_INFO lHostInfo;
    if ( (m_diaMgtObj->GetLocalHostInfo(&lHostInfo) == ITS_SUCCESS) &&
         (strcasecmp(lhost.c_str(),lHostInfo.hostName) == 0)
       )
    {
        bResult = true;
    }
    else
    {
        bResult = false;
    }
    return bResult;
}

int CMAPIDreConfig::ModifyLocalHost(LocalHostConfig *localhost)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    LOCAL_HOST_INFO lHostInfo;
    if ( (m_diaMgtObj->GetLocalHostInfo(&lHostInfo) == ITS_SUCCESS) &&
            (strcasecmp(localhost->localhostname().c_str(),lHostInfo.hostName)  == 0 ))
    {
        if (localhost->has_realmname() || localhost->has_hostipaddr())
        {
            char *realm;
            char *ipAddr;
            if (localhost->has_realmname())
                realm = (char *) (localhost->realmname()).c_str();
            else
                realm = (char *) lHostInfo.realmName;
            if (localhost->has_hostipaddr())
                ipAddr = (char *) (localhost->hostipaddr()).c_str();
            else
                ipAddr = (char *) lHostInfo.ipAddr;
            /*
            if ( m_diaMgtObj->SetLocalHostInfo((const char *) (localhost->localhostname()).c_str(),
                        (const char *) realm, (const char *) ipAddr) != ITS_SUCCESS)
            */
                retVal = CMAPI_SRVERROR;
        }

        if (localhost->has_transporttype() || localhost->has_port())
        {
            //Initializing Pointer and Scalar Variables
            char *ipAddr = NULL;
            MGMT_TR_TYPE transportType = DIA_TRANS_TCP; 
            int lport =  0;

            if (m_diaMgtObj->GetLocalTransportInfo(transportType, lport) == ITS_SUCCESS)
            {

                if (localhost->has_hostipaddr())
                    ipAddr = (char *) (localhost->hostipaddr()).c_str();
                else
                    ipAddr = (char *) lHostInfo.ipAddr;

                //Logging Unused Pointer Value
                DLOG_DEBUG("CMAPIDreConfig::ModifyLocalHost : IpAddress# %s", ipAddr);

                if (localhost->has_transporttype())
                {
                    if ((localhost->transporttype()).compare("STCP") == 0)
                        transportType = DIA_TRANS_SCTP;
                    else if ((localhost->transporttype()).compare("TCP") == 0)
                        transportType = DIA_TRANS_TCP;
                }

                if (localhost->has_port())
                    lport = localhost->port();

                /*if ( m_diaMgtObj->SetLocalTransportInfo((const char *) (localhost->hostipaddr()).c_str(),
                            (int) transportType, (ITS_USHORT) lport) != ITS_SUCCESS) */
                    retVal = CMAPI_SRVERROR;
            }
        }

        if ( localhost->has_authsessiontimeout() || localhost->has_authsessionlifetime() || 
                localhost->has_authsessiongraceperiod() )
        {
            ITS_SERIAL timeOut;
            ITS_SERIAL lifeTime;
            ITS_SERIAL graceTime;
            if (m_diaMgtObj->GetAuthSessionTimers(lifeTime, graceTime, timeOut) == ITS_SUCCESS)
            {
                if (localhost->has_authsessiontimeout())
                    timeOut = (ITS_SERIAL) localhost->authsessiontimeout();
                if (localhost->has_authsessionlifetime())
                    lifeTime = (ITS_SERIAL) localhost->authsessionlifetime();
                if (localhost->has_authsessiongraceperiod())
                    graceTime = (ITS_SERIAL) localhost->authsessiongraceperiod();

                if (m_diaMgtObj->SetAuthSessionTimers(lifeTime, graceTime, timeOut) != ITS_SUCCESS)
                    retVal = CMAPI_SRVERROR;
            }
        }

        if ( localhost->has_acctsessioninteriminterval() || localhost->has_acctsessiontimeout())
        {
            ITS_SERIAL timeOut;
            ITS_SERIAL interval;
            if (m_diaMgtObj->GetAcctSessionTimers(interval, timeOut) == ITS_SUCCESS)
            {
                if (localhost->has_acctsessioninteriminterval())
                    interval = (ITS_SERIAL) localhost->acctsessioninteriminterval();
                if (localhost->has_acctsessiontimeout())
                    timeOut = (ITS_SERIAL) localhost->acctsessiontimeout();

                if (m_diaMgtObj->SetAcctSessionTimers(interval, timeOut) != ITS_SUCCESS)
                    retVal = CMAPI_SRVERROR;
            }
        }

    } else {
        retVal = CMAPI_SRVERROR;
    }

    return retVal;
}

int CMAPIDreConfig::SetLocalHost(LocalHostConfig *localhost)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;

    if (localhost->has_localhostname() && localhost->has_realmname() && 
            localhost->has_hostipaddr())
    {
        /*
        if ( m_diaMgtObj->SetLocalHostInfo((const char *) (localhost->localhostname()).c_str(),
                    (const char *) (localhost->realmname()).c_str(), 
                    (const char *) (localhost->hostipaddr()).c_str()) != ITS_SUCCESS)
        */
            retVal = CMAPI_SRVERROR;
    }

    if (localhost->has_hostipaddr() && localhost->has_transporttype() && localhost->has_port())
    {
        MGMT_TR_TYPE transportType = DIA_TRANS_SCTP;
        if ((localhost->transporttype()).compare("TCP") == 0)
            transportType = DIA_TRANS_TCP;

        /*if ( m_diaMgtObj->SetLocalTransportInfo((const char *) (localhost->hostipaddr()).c_str(),
                    (int) transportType, (ITS_USHORT) localhost->port()) != ITS_SUCCESS) */
            retVal = CMAPI_SRVERROR;
    }

    if ( localhost->has_authsessiontimeout() && localhost->has_authsessionlifetime() && 
            localhost->has_authsessiongraceperiod() )
    {
        if (m_diaMgtObj->SetAuthSessionTimers((ITS_SERIAL) localhost->authsessionlifetime(),
                    (ITS_SERIAL) localhost->authsessiongraceperiod(), 
                    (ITS_SERIAL) localhost->authsessiontimeout()) != ITS_SUCCESS)
            retVal = CMAPI_SRVERROR;
    }

    if ( localhost->has_acctsessioninteriminterval() && localhost->has_acctsessiontimeout())
    {
        if (m_diaMgtObj->SetAcctSessionTimers((ITS_SERIAL) localhost->acctsessioninteriminterval(),
                    (ITS_SERIAL) localhost->acctsessiontimeout()) != ITS_SUCCESS)
            retVal = CMAPI_SRVERROR;
    }
    return retVal;
}

// Peer related methods
int CMAPIDreConfig::ModifyPeerConfig(PeerConfig& PeerCfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    PEER_INFO peerInfo;
    
    peerInfo.peerName = (const char *) (PeerCfg.peerhostname()).c_str();
    peerInfo.realmName = (const char *) (PeerCfg.realm()).c_str();

    if ( PeerCfg.has_tlsenabled() || PeerCfg.has_transporttype() || 
            PeerCfg.has_serveripaddr() || PeerCfg.has_port())
    {
	    if (PeerCfg.has_serveripaddr())
		    peerInfo.ipAddr = (const char *) (PeerCfg.serveripaddr()).c_str();

	    if (PeerCfg.has_port())
		    peerInfo.port = (unsigned short) PeerCfg.port();

	    if (PeerCfg.has_transporttype())
	    {
		    if ((PeerCfg.transporttype()).compare("TCP") == 0)
			    peerInfo.type = (MGMT_TR_TYPE) DIA_TRANS_TCP;
		    else if((PeerCfg.transporttype()).compare("SCTP") == 0)
			    peerInfo.type = (MGMT_TR_TYPE) DIA_TRANS_SCTP;
	    }

	    if (PeerCfg.has_tlsenabled())
		    peerInfo.tlsEnabled = PeerCfg.tlsenabled();

	    retVal = m_diaMgtObj->ModifyPeer(&peerInfo, false);
	    if(retVal != ITS_SUCCESS)
		    return retVal;
    }

    if ( PeerCfg.has_altpeername() && (PeerCfg.has_failoverenable() || 
            PeerCfg.has_failebackenable() || PeerCfg.has_ismate()))
    {
        ALT_PEER_INFO altPeer;
        altPeer.altHost = (const char *) (PeerCfg.altpeername()).c_str();
        altPeer.altRealmName = (PeerCfg.realm()).c_str();
        if (m_diaMgtObj->GetAlternatePeer(&altPeer) == ITS_SUCCESS)
        {
            altPeer.peerName = (const char *) (PeerCfg.peerhostname()).c_str();
            altPeer.realmName = (const char *) (PeerCfg.realm()).c_str();
            if (PeerCfg.has_failebackenable())
                altPeer.isFailbackEnable = (PeerCfg.failebackenable()?ITS_TRUE:ITS_FALSE);
            if (PeerCfg.has_failoverenable())
                altPeer.isFailoverEnable = (PeerCfg.failoverenable()?ITS_TRUE:ITS_FALSE);
            if (PeerCfg.has_ismate())
                altPeer.isRedundantMate = PeerCfg.ismate();
           
            if((retVal = m_diaMgtObj->GetAlternatePeerForPeer(&altPeer)) == ITS_SUCCESS)
            {
                retVal = m_diaMgtObj->ModifyAlternatePeer(&altPeer);
		DLOG_DEBUG("ModifyAlternatePeer  result = %d",retVal);
            }
            else 
            {
                retVal = m_diaMgtObj->AddAlternatePeer(&altPeer);
		DLOG_DEBUG("AddAlternatePeer  result = %d",retVal);
            }
        }
	else
	{
	    DLOG_ERROR("Modify/Add alternate peer Failed :: Check if Alternate peer %s is in the realm  %s",altPeer.altHost, altPeer.altRealmName);
	    return CMAPI_ERROR;
	}

    }

    if (PeerCfg.has_watchdogtimer() || PeerCfg.has_tctimerval() || PeerCfg.has_expirytimer())
    {
        if (PeerCfg.has_watchdogtimer())
            peerInfo.watchdog = (ITS_SERIAL)PeerCfg.watchdogtimer();
        if (PeerCfg.has_tctimerval())
            peerInfo.retry = (ITS_SERIAL)PeerCfg.tctimerval();
        if (PeerCfg.has_expirytimer())
            peerInfo.expiry =PeerCfg.expirytimer();

        if (m_diaMgtObj->SetPeerTimers(&peerInfo) != ITS_SUCCESS)
        { retVal = (!ITS_SUCCESS);}
    }
 
    if(PeerCfg.has_busyreconnecttimerval() || PeerCfg.has_donotwanttotalktoyoutimerval())
    {
        if (PeerCfg.has_busyreconnecttimerval())
            peerInfo.busyReconnectTimerVal = PeerCfg.busyreconnecttimerval();
        if (PeerCfg.has_donotwanttotalktoyoutimerval())
            peerInfo.doNotWantToTalkYouReconnectTimerVal =
            PeerCfg.donotwanttotalktoyoutimerval();
        if (m_diaMgtObj->SetPeerDPRCauseReconnectimers(&peerInfo) != ITS_SUCCESS)
        { retVal = (!ITS_SUCCESS);}
    }

    if( PeerCfg.has_issupportdisconnectcause())
    {
        if (PeerCfg.issupportdisconnectcause())
            peerInfo.isSupportDisconnectCause = PeerCfg.issupportdisconnectcause();
        
        if (m_diaMgtObj->SetPeerIsDisconnectCauseSupported(&peerInfo) != ITS_SUCCESS)
        { retVal = (!ITS_SUCCESS);}
    }

    if (PeerCfg.has_peerstatus() )
    {
        retVal = ConfigPeerStatus(PeerCfg.peerhostname(), PeerCfg.realm(), PeerCfg.peerstatus());
    }

    int dict_count = PeerCfg.dictionaryname_size();
    if(dict_count > 0)
    {
        retVal= AddDictionaryID(&PeerCfg);
    }
    if(PeerCfg.secondaryipaddr_size()>0)
    {
        char *multiHomeIpAddrs[4] = {NULL};
        int noIPs = 0;

        for(int i = 0;i < PeerCfg.secondaryipaddr_size();i++)
        {
            std::string * secondaryIpAddrs = PeerCfg.mutable_secondaryipaddr(i);
            DLOG_DEBUG("Add Secondary ip addrs %s for Peer %s",
            secondaryIpAddrs->c_str(),PeerCfg.peerhostname().c_str());

            multiHomeIpAddrs[i]= strdup(secondaryIpAddrs->c_str());
            noIPs++;
        }
        retVal = m_diaMgtObj->AddSecondaryIp((char *) (PeerCfg.peerhostname()).c_str(),
                  (const char *) (PeerCfg.realm()).c_str(),multiHomeIpAddrs,noIPs);
   }

    return retVal;
}

int CMAPIDreConfig::AddPeerConfig(PeerConfig& PeerCfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    PEER_INFO peerInfo;
    memset(&peerInfo,0,sizeof(PEER_INFO));
    if ( PeerCfg.has_peerhostname() && PeerCfg.has_realm() && 
          PeerCfg.has_serveripaddr())
    {
        peerInfo.peerName = (const char *) (PeerCfg.peerhostname()).c_str();
        peerInfo.realmName = (const char *) (PeerCfg.realm()).c_str();
        peerInfo.ipAddr = (const char *) (PeerCfg.serveripaddr()).c_str();
        if(PeerCfg.has_port())
        {
            peerInfo.port = (unsigned short) PeerCfg.port();
        }
        if(PeerCfg.has_secureport())
        {
            //peerInfo.securePort = (unsigned short) PeerCfg.secureport();
        }
        peerInfo.tlsEnabled = PeerCfg.tlsenabled();

        if (PeerCfg.has_transporttype() && 
                ((PeerCfg.transporttype()).compare("TCP") == 0))
        {
            peerInfo.type = (MGMT_TR_TYPE) DIA_TRANS_TCP;
        }else if(PeerCfg.has_transporttype() &&
                   ((PeerCfg.transporttype()).compare("SCTP") == 0))
	{
            peerInfo.type = (MGMT_TR_TYPE) DIA_TRANS_SCTP;
        }
	else 
        {    
            peerInfo.type = (MGMT_TR_TYPE)DIA_TRANS_INVALID;
        }  
        if (PeerCfg.has_tlsenabled())
            peerInfo.tlsEnabled = PeerCfg.tlsenabled();
        else
            peerInfo.tlsEnabled = false;


        /* TODO: Need to have configurable parameter from CLI currently enabling 
         * PendingQ by default  to be used for validation Answer message*/
        peerInfo.isRetransmissionEnabled = true;

        if((PeerCfg.secondaryipaddr_size()>0 && PeerCfg.secondaryipaddr_size() <4)
                        && peerInfo.type == DIA_TRANS_SCTP )
        {
             const char *multiHomeIpAddrs[4] = {NULL};
             int noIPs = 0;
             for(int i = 0;i < PeerCfg.secondaryipaddr_size();i++)
             {
                  std::string * secondaryIpAddrs = PeerCfg.mutable_secondaryipaddr(i);
                  DLOG_DEBUG("Secondary ip addrs is %s for IP %s",
                  secondaryIpAddrs->c_str(),PeerCfg.serveripaddr().c_str());

                  multiHomeIpAddrs[i]= strdup(secondaryIpAddrs->c_str());
                  noIPs++;
             }
             peerInfo.noIPs=noIPs;
             peerInfo.multiHomeipaddrs=multiHomeIpAddrs;
        }

        if ((retVal = m_diaMgtObj->AddPeer(&peerInfo)) != ITS_SUCCESS)
        {
            return retVal;
        }
    }

    if ( PeerCfg.has_peerhostname() && PeerCfg.has_realm() && PeerCfg.has_altpeername() &&
            PeerCfg.has_failoverenable() && PeerCfg.has_failebackenable() && PeerCfg.has_ismate())
    {
        ALT_PEER_INFO altPeer;
        altPeer.peerName = (const char *) (PeerCfg.peerhostname()).c_str();
        altPeer.realmName = (const char *) (PeerCfg.realm()).c_str();
        altPeer.altHost = (const char *) (PeerCfg.altpeername()).c_str();
        altPeer.altRealmName = altPeer.realmName;
        altPeer.isFailoverEnable = (PeerCfg.failoverenable()?ITS_TRUE:ITS_FALSE);
        altPeer.isFailbackEnable = (PeerCfg.failebackenable()?ITS_TRUE:ITS_FALSE);
        altPeer.isRedundantMate = PeerCfg.ismate();

        if (m_diaMgtObj->AddAlternatePeer(&altPeer) != ITS_SUCCESS)
            retVal = CMAPI_SRVERROR;
    }

    if (PeerCfg.has_watchdogtimer() && PeerCfg.has_tctimerval() && PeerCfg.has_expirytimer())
    {
	peerInfo.watchdog = (ITS_SERIAL) PeerCfg.watchdogtimer();
	peerInfo.retry = (ITS_SERIAL) PeerCfg.tctimerval();
	peerInfo.expiry = (ITS_SERIAL) PeerCfg.expirytimer();

	if (m_diaMgtObj->SetPeerTimers(&peerInfo) != ITS_SUCCESS)
		retVal = CMAPI_SRVERROR;
    }

    if(PeerCfg.has_busyreconnecttimerval() || PeerCfg.has_donotwanttotalktoyoutimerval())
    {
        if (PeerCfg.has_busyreconnecttimerval())
            peerInfo.busyReconnectTimerVal = PeerCfg.busyreconnecttimerval();
        if (PeerCfg.has_donotwanttotalktoyoutimerval())
            peerInfo.doNotWantToTalkYouReconnectTimerVal =
            PeerCfg.donotwanttotalktoyoutimerval();
        if (m_diaMgtObj->SetPeerDPRCauseReconnectimers(&peerInfo) != ITS_SUCCESS)
        { retVal = (!ITS_SUCCESS);}
    }

    if( PeerCfg.has_issupportdisconnectcause())
    {
        if (PeerCfg.issupportdisconnectcause())
            peerInfo.isSupportDisconnectCause = PeerCfg.issupportdisconnectcause();
        
        if (m_diaMgtObj->SetPeerIsDisconnectCauseSupported(&peerInfo) != ITS_SUCCESS)
        { retVal = (!ITS_SUCCESS);}
    }

    if (PeerCfg.has_peerstatus() && PeerCfg.peerstatus())
    {
        if (ConfigPeerStatus(PeerCfg.peerhostname(), PeerCfg.realm(), true) != ITS_SUCCESS)
        {
            retVal = CMAPI_SRVERROR;
        }
    }

    if (PeerCfg.dictionaryname_size())
    {    
        retVal= AddDictionaryID(&PeerCfg);
    }

    return retVal;
}

int CMAPIDreConfig::AddDictionaryID(PeerConfig* peerCfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = ITS_SUCCESS;
    int dict_count;
    string dict_names[MAX_DICT_IDS_PER_PEER];
    APPLICATION_TYPE appType[MAX_DICT_IDS_PER_PEER];
    PEER_INFO peerInfo;
    peerInfo.peerName = (const char *) (peerCfg->peerhostname()).c_str();
    peerInfo.realmName = (const char *) (peerCfg->realm()).c_str();
    dict_count = peerCfg->dictionaryname_size();
    for (int dict_idx = 0; (dict_idx < dict_count) && (dict_count <= MAX_DICT_IDS_PER_PEER); dict_idx++)
    {
        dict_names[dict_idx] = peerCfg->dictionaryname(dict_idx);
        appType[dict_idx] = (APPLICATION_TYPE)DIA_AUTH_APP;//(peerCfg->typeofapp(dict_idx));
    }
    retVal = m_diaMgtObj->AssociateDictToPeer(&peerInfo, dict_count, dict_names,appType,true);
    return retVal;
}

int CMAPIDreConfig::DeleteDictionaryID(PeerConfig* PeerCfg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int dict_count;
    int dict_Id[MAX_DICT_IDS_PER_PEER] = {0};
    PEER_INFO peerInfo;
    peerInfo.peerName = (const char *) (PeerCfg->peerhostname()).c_str();
    peerInfo.realmName = (const char *) (PeerCfg->realm()).c_str();
    dict_count = PeerCfg->dictionaryid_size();
    for (int dict_idx = 0; (dict_idx < dict_count) && (dict_count <= MAX_DICT_IDS_PER_PEER); dict_idx++)
    {
        dict_Id[dict_idx] = PeerCfg->dictionaryid(dict_idx);
    }
    retVal = m_diaMgtObj->RemoveDictId(&peerInfo, dict_count, dict_Id);
    return retVal;
}

int CMAPIDreConfig::ConfigPeerStatus(string Peer, string Realm, bool state)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = ITS_SUCCESS;
    if (state == true)
    {
        retVal = m_diaMgtObj->StartPeer((const char *) Peer.c_str(),
                (const char *) Realm.c_str());
	if(retVal == ITS_SUCCESS)
	{
	    DLOG_DEBUG("Started Successfully peer %s realm %s",Peer.c_str(),Realm.c_str());
	}
	else
	{
	    DLOG_DEBUG("Failed to start peer %s realm %s",Peer.c_str(),Realm.c_str());
	}
    } else {
        // Hard coded the expiry to 30 since we are not sending this value in the API
        // and disconnect cause to DisconnectCause::DO_NOT_WANT_TO_TALK_TO_YOU(2) since we 
        // will have to include the other header files if we use the DisonnectCause class
        retVal = m_diaMgtObj->ForceDisconectPeer((const char *) Peer.c_str(),
                    Realm.c_str(), 2, 30);
    }
    return retVal;
}


// Realm related methods
int CMAPIDreConfig::AddRealmConfig(RealmConfig& Realm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int numDests = Realm.destinfo_size();

    if (Realm.has_realmname() && Realm.has_localaction())
    {
        bool proxyInfoAVP = (Realm.has_enableproxyinfoavp() && Realm.enableproxyinfoavp());
        if (!((Realm.localaction()).compare("Relay") == 0) ||
                (proxyInfoAVP))
        {
            retVal = m_diaMgtObj->AddRealm((const char *) (Realm.realmname()).c_str(),
                    (const char *) (Realm.localaction()).c_str(),
                    (proxyInfoAVP?ITS_TRUE:ITS_FALSE));
        } else {
            retVal = !ITS_SUCCESS;
        }
    }

    if (Realm.has_defaultroute())
    {
        m_diaMgtObj->RemoveDefaultRoute();
        retVal = m_diaMgtObj->SetDefaultRoute((const char *) (Realm.defaultroute().c_str()),
                (const char *) (Realm.realmname()).c_str());
    }

    if (numDests > 0)
    {
        for (int i = 0; i < numDests; i++)
        {
            Destination Dest = Realm.destinfo(i);
            retVal = AddRealmRouting(Realm.realmname(), Dest);
        }
    }
    return retVal;

}

int CMAPIDreConfig::ModifyRealmConfig(RealmConfig& Realm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int numDests = Realm.destinfo_size();
    const char *realmName = (Realm.realmname()).c_str();

    if (Realm.has_localaction())
        retVal = m_diaMgtObj->SetRealmLocalAction(realmName, (Realm.localaction()).c_str());

    if (Realm.has_redirecthostusage())
        retVal = m_diaMgtObj->ModifyRedirectUsage(realmName, Realm.redirecthostusage());

    if (Realm.has_redirectmaxcachetime())
        retVal = m_diaMgtObj->ModifyRedirectUsage(realmName, Realm.redirectmaxcachetime());

    if (numDests > 0)
    {
        for (int i = 0; i < numDests; i++)
        {
            Destination Dest = Realm.destinfo(i);
            retVal = ModifyRealmRouting(Realm.realmname(), Dest);
        }
    }
 
    return retVal;

}

int CMAPIDreConfig::AddRealmRouting(string Realm, Destination& Dest)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    DESTINATION_INFO DestInfo;
    DestInfo.realmName = (const char *) Realm.c_str();
    DestInfo.peerName  = (const char *) (Dest.peername()).c_str();
    DestInfo.peerRealm = (const char *) (Dest.realmname()).c_str();
    DestInfo.applicationId = (int) Dest.applicationid();
    DestInfo.vendorId = (int) Dest.vendorid();
    DestInfo.priority = (int) Dest.priority();

    retVal = m_diaMgtObj->AddDestination(&DestInfo);
    return retVal;

}

int CMAPIDreConfig::DeleteRealmRouting(string Realm, Destination& Dest)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    DESTINATION_INFO DestInfo;
    DestInfo.realmName = (const char *) Realm.c_str();
    DestInfo.peerName  = (const char *) (Dest.peername()).c_str();
    DestInfo.peerRealm = (const char *) (Dest.realmname()).c_str();
    DestInfo.applicationId = (int) Dest.applicationid();
    DestInfo.vendorId = (int) Dest.vendorid();
    retVal = m_diaMgtObj->RemoveDestination(&DestInfo);   
    return retVal;
}

int CMAPIDreConfig::ModifyRealmRouting(string Realm, Destination& Dest)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;

    DESTINATION_INFO DestInfo;
    DestInfo.realmName = (const char *) Realm.c_str();
    DestInfo.peerName  = (const char *) (Dest.peername()).c_str();
    DestInfo.peerRealm = (const char *) (Dest.realmname()).c_str();
    DestInfo.applicationId = (int) Dest.applicationid();
    DestInfo.vendorId = (int) Dest.vendorid();
    DestInfo.priority = (int) Dest.priority();
    retVal = m_diaMgtObj->ModifyDestinationPriority(&DestInfo);   
    return retVal;
}

unsigned int CMAPIDreConfig::GetAllPeersState(DRECfgResp *resp)
{
   ScopedLogger scopedLogger(IwfController::Instance().GetLogger()); 
   unsigned int nPeers = 0;
   int retVal = CMAPI_SUCCESS;
   DIA_PEER_STATES *allPeers = NULL;
   allPeers = m_diaMgtObj->GetPeersState(nPeers);
   DLOG_DEBUG("STATE: Total Peers : %d", nPeers);

   if ((allPeers != NULL) && (nPeers > 0))
   {
      PeersConfig* tPeers = resp->mutable_peers();
      for (unsigned int idx = 0; idx < nPeers; idx++)
      {
         PeerConfig* curPeer = tPeers->add_peers();
         curPeer->set_peerhostname((const char*) allPeers[idx].peerName);
         curPeer->set_realm((const char*) allPeers[idx].realmName);
         curPeer->set_peerstate((int) allPeers[idx].pState);
      }
      delete [] allPeers;
      allPeers = NULL;

   } else {
      //  Fill in Error Details
      nPeers = 0;
   }

   if(allPeers != NULL)
   {
       delete[] allPeers;
       allPeers = NULL;
   }

   resp->set_respcode(retVal);
   return nPeers;
}

int CMAPIDreConfig::DreTraceErrorConfig(int retVal, TraceConfig tracecfg, TraceResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int errorCode ;
    ErrorDetails* err = resp->add_errordetails();
    errorCode = retVal;
    err->set_errorcode(errorCode);
    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
    err->add_variables(tracecfg.filtername());
    retVal = CMAPI_SRVERROR;   
    return retVal;
}

int CMAPIDreConfig::DreStaticRoutingErrorConfig(int retVal, StaticRoutingTableConfig staticRoutingCfg,
                                                StaticRoutingTableConfigResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int errorCode ;
    ErrorDetails* err = resp->add_errordetails();
    errorCode = retVal;
    err->set_errorcode(errorCode);
    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
    err->add_variables(staticRoutingCfg.destionatinhost());
    err->add_variables(staticRoutingCfg.peer());
    retVal = CMAPI_SRVERROR;   
    return retVal;
}

int CMAPIDreConfig::HandleSDTFConfig(SDTFReq* req, SDTFResp* rsp)
{
    return CMAPI_SUCCESS;
}

int CMAPIDreConfig::HandleTHFConfig(THFReq* req, THFResp* rsp)
{
    return CMAPI_SUCCESS;
}

int CMAPIDreConfig::HandlePluginConfig(TransformPluginConfigReq* req, DRECfgResp* rsp)
{
    return CMAPI_SUCCESS;
}

int CMAPIDreConfig::HandleDictionaryConfig(DictionaryConfigReq* req, DRECfgResp* rsp)
{
    return CMAPI_SUCCESS;
}

