
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

#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"
#include "repmgr_cfg.h"
#include "RepMgrCommon.h"
#include "ReplicationManagerClass.h"

using namespace eAccelero;

    class MeSSComponent;
    class Interface;
    class MeSS;

    // Replication Manager Constructor.
    ReplicationManager::ReplicationManager() : 
        HAMeSSComponent("ReplicationManager", RepMgrID , I_REPLICATION_MANAGER)
    {
        m_AmIActive = false;  // Initial Status
        m_eCurDeployment = A1C1;      // Default Configuration
        MeSSObj().RegisterInterface(this);  // Register Interface for REPMGR
        m_DreStandbyInstance.compId = COMP_DRE_APP;
        m_DreStandbyInstance.instance = MESS_MULTICAST_STANDBY;
    }

    // Destructor
    ReplicationManager::~ReplicationManager() 
    {

    }

    void ReplicationManager::Initialize() 
    {
        // MeSSEndpoint PEndPt;
        HAMeSSComponent::Initialize();
        CLOG_DEBUG("Initializing Replication Manager");
        m_PeerRepMgrInstance.compId = COMP_REPLICATION_MANAGER;   
        int MyInstance = MeSSObj().Self().instance;
        if ( MyInstance  >= MESS_MIN_STANDBY_INSTANCE) 
        {
            m_AmIActive = false;
            m_PeerRepMgrInstance.instance = MyInstance - MESS_MIN_STANDBY_INSTANCE;
        }
        else 
        {
            m_AmIActive  = true;
            m_PeerRepMgrInstance.instance = MyInstance + MESS_MIN_STANDBY_INSTANCE;
        }

        // Object to handle key:value storage access
        m_cacheMgr = new MemcachedClient("localhost");
        if (m_cacheMgr->InitializeCache() == false)
        {
            CLOG_NOTICE("Memcache Init Failed: Memcache Server Not Running");
        }
        else
            CLOG_DEBUG("Memcache Init Success");

        this->GetDispatcher()->AddEventHandler(
                EventSlot<TimerEvent, MemcachedClient>(m_cacheMgr, &MemcachedClient::OnTimerEvt),
                TimerEvent(15000));   // Every 1 second    
    }

    int ReplicationManager::SetCurDeployment(void)
    {
        // Default and Current Deployment configuration
        m_eCurDeployment = A1S1;
        return 0;
    }

    int ReplicationManager::SetReplLogLevel(ReplLogLevelReq *req, ReplLogLevelResp *resp)
    {
        // Set the LogLevel Here   // Save the setting;
        GetLogger().SetLevel((Logger::Level) req->bReplLogLvl, req->bLogFlag);
        std::cout << "Log Level Set : " << req->bReplLogLvl << std::endl;
        CLOG_DEBUG("Log Level Set %d", (int) req->bReplLogLvl);
        resp->RespCode = 0;      // Success
        return 0;     
    }

    // Termination Method   -- More Comments -- TODO
    void ReplicationManager::Terminate() 
    {
        HAMeSSComponent::Terminate();

        // Clear our replication manager related memory
        if (m_cacheMgr) delete m_cacheMgr;
    }

    // Read Configuration File and update the attributes accordingly
    // Say Active/Standy State, Standy Node Address(es)
    void ReplicationManager::ReadConfiguration(void)
    {
        //TODO: Read configuration file here and set related attibutes

    }

    // to get my active/standy status
    bool ReplicationManager::GetState(void)
    {
        return m_AmIActive;
    }

    int  ReplicationManager::ProcessAvailabilityStatusResetReq(AvailabilityStatusResetReqObj *req,
            AvailabilityStatusResetRespObj *resp)
    {
        HAMeSSComponent::ProcessAvailabilityStatusResetReq(req, resp);
        if (resp->isAvailabilityStatusReset == true)
        {
            if (req->newInstanceId < MESS_MIN_STANDBY_INSTANCE)
            {
                m_PeerRepMgrInstance.instance = req->newInstanceId + MESS_MIN_STANDBY_INSTANCE;
                m_AmIActive = true;
            }
            else 
            {
                m_PeerRepMgrInstance.instance = (req->newInstanceId - MESS_MIN_STANDBY_INSTANCE);
                m_AmIActive = false;			
            }			
        }
        return 0;
    }

int ReplicationManager::ProcessAvailabilityStatusGetReq(AvailabilityStatusReqObj *req, 
        AvailabilityStatusRespObj *resp)
{
    resp->instanceId =  MeSSObj().Self().instance;
    return 0;
}

int ReplicationManager::ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId)
{

    return 0;
}

int ReplicationManager::ProcessAvailabilityStatusResetPostFunc()
{
  return 0;
}

    void ReplicationManager:: RegisterMethods() 
    {  // Register Methods for calling REPMGR services.
        CLOG_DEBUG("Registering Replication Manager Services");
        HAMeSSComponent::RegisterMethods();

        this->RegisterMethod(M_REPMGR_CACHE_DREBINDINFO, 
                MethodSlot<ReplicationManager,DREBindInfo, DREBindResp>(this, &ReplicationManager::CreateCacheEntry));
        this->RegisterMethod(M_REPMGR_UPDATE_DREBINDINFO, 
                MethodSlot<ReplicationManager,DREBindInfo, DREBindResp>(this, &ReplicationManager::UpdateCacheEntry));
        this->RegisterMethod(M_REPMGR_DELETE_DREBINDINFO, 
                MethodSlot<ReplicationManager,DREBindInfo, DREBindResp>(this, &ReplicationManager::DeleteCacheEntry));

        this->RegisterMethod(M_REPMGR_CACHE_DRERXBINDINFO, 
                MethodSlot<ReplicationManager,DRERxBindInfo, DREBindResp>(this, &ReplicationManager::CreateRxCacheEntry));
        this->RegisterMethod(M_REPMGR_DELETE_DRERXBINDINFO, 
                MethodSlot<ReplicationManager,DRERxBindInfo, DREBindResp>(this, &ReplicationManager::DeleteRxCacheEntry));

        // CLI Interfacing Method
        this->RegisterMethod(M_REPMGR_LOGLEVEL, 
                MethodSlot<ReplicationManager,ReplLogLevelReq, ReplLogLevelResp>(this, &ReplicationManager::SetReplLogLevel));

        // Response Handlers
        // For Calling DREApp
        MeSSObj().RegisterRespHandler(MakeMsgId(I_DRE_APP, M_DREAPP_SAVE_SESSION_ID), 
                CallbackSlot<ReplicationManager, DREBindResp>(this, &ReplicationManager::CacheOperationResp));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_DRE_APP, M_DREAPP_UPDATE_SESSION_ID), 
                CallbackSlot<ReplicationManager, DREBindResp>(this, &ReplicationManager::CacheOperationResp));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_DRE_APP, M_DREAPP_DELETE_SESSION_ID), 
                CallbackSlot<ReplicationManager, DREBindResp>(this, &ReplicationManager::CacheOperationResp));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_DRE_APP, M_DREAPP_SAVE_RXSESSION_ID), 
                CallbackSlot<ReplicationManager, DREBindResp>(this, &ReplicationManager::CacheOperationResp));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_DRE_APP, M_DREAPP_DELETE_RXSESSION_ID), 
                CallbackSlot<ReplicationManager, DREBindResp>(this, &ReplicationManager::CacheOperationResp));


    }

    int ReplicationManager::Handle_DRERxBind_CacheOP(DRERxBindInfo *Req, DREBindResp *Resp, RepMgrMethods MId)
    {

        int retVal = 0;

        return retVal;

    }

    int ReplicationManager::Handle_DREBind_CacheOP(DREBindInfo *Req, DREBindResp *Resp, RepMgrMethods MId)
    {
        unsigned DREApp_Method;
        KeyValue kvl;
        // Construct KeyValue object from Req structure.
        //kvl.sKey.assign((char *) Req->diaSessionId);
        switch (MId)
        {
            case M_REPMGR_CACHE_DREBINDINFO:
                //kvl.sValue.assign((char *) Req->diaPeer);
                m_cacheMgr->StoreEntry(kvl);
                DREApp_Method = M_DREAPP_SAVE_SESSION_ID;
                break;          
            case M_REPMGR_UPDATE_DREBINDINFO:
                //kvl.sValue.assign((char *) Req->diaPeer);
                m_cacheMgr->StoreEntry(kvl);
                DREApp_Method = M_DREAPP_UPDATE_SESSION_ID;
                break;
            case M_REPMGR_DELETE_DREBINDINFO:
                m_cacheMgr->DeleteEntry(kvl.Get_HashKey());
                DREApp_Method = M_DREAPP_DELETE_SESSION_ID;
                break;
            default:
                CLOG_DEBUG("DREBIND CACHE OP: Invalid request received");
        }

        Resp->responseID = RM_SUCCESS;  //SUCCESS;
        return 0;
    }

    void ReplicationManager::SendDRERxBindingInfo(DRERxBindInfo *Req, unsigned DREMId)
    {
        // Build Message  and send
        MessageId DreMsgID = MakeMsgId(I_DRE_APP, DREMId);
        //CLOG_DEBUG("*** Sending DRE info %s : %s", Req->diaSessionId, Req->diaPeer);
        MeSSObj().Send(m_DreStandbyInstance, DreMsgID, (void *) Req, sizeof(struct DREBindInfo));
    }
    void ReplicationManager::SendDREBindingInfo(DREBindInfo *Req, unsigned DREMId)
    {
        // Build Message  and send
        MessageId DreMsgID = MakeMsgId(I_DRE_APP, DREMId);
        //CLOG_DEBUG("*** Sending DRE info %s : %s", Req->diaSessionId, Req->diaPeer);
        MeSSObj().Send(m_DreStandbyInstance, DreMsgID, (void *) Req, sizeof(struct DREBindInfo));
    }

    // This method handles the insertion of key:value pair into the Database store
    int ReplicationManager::CreateCacheEntry(DREBindInfo *Req, DREBindResp *Resp) 
    {
        // handle_DREBind_CacheOP(Req, Resp, M_REPMGR_CACHE_DREBINDINFO);
        if (!m_AmIActive && m_eCurDeployment != A1C1)
        {
            SendDREBindingInfo(Req, M_DREAPP_SAVE_SESSION_ID);
            CLOG_DEBUG("Record Sent to DREAPP"); // temp code
        }
        KeyValue kvl;
        // Construct KeyValue object from Req structure.
        kvl.Set_HashKey(Req->dreBindInfoKey);
        kvl.Add_HashValue(Req->serverName);
        kvl.Add_HashValue(Req->isIPV6);
        kvl.Add_HashValue(Req->counter);
        kvl.Add_HashValue(Req->sessionTerminateTimerId);
        kvl.Add_HashValue(Req->gxSessionFlag);
        kvl.Add_HashValue(Req->gxxSessionFlag);
        kvl.Add_HashValue(Req->rxSessionFlag);

        m_cacheMgr->StoreEntry(kvl);
        CLOG_DEBUG("Replication Manager:  Key:Value pair cached ");
        if (Resp != NULL)
        {
            Resp->responseID = RM_SUCCESS;
        }

        return 0;
    }

    // This method handles the modifies/updates the key:value pair in the Database store
    int ReplicationManager::UpdateCacheEntry(DREBindInfo *Req, DREBindResp *Resp) 
    {
        //handle_DREBind_CacheOP(Req, Resp, M_REPMGR_UPDATE_DREBINDINFO);
        if (!m_AmIActive && m_eCurDeployment != A1C1)
        {
            SendDREBindingInfo(Req, M_DREAPP_UPDATE_SESSION_ID);
            CLOG_DEBUG("Update Record Sent to DREAPP"); // temp code
        }
        KeyValue kvl;
        // Construct KeyValue object from Req structure.
        kvl.Set_HashKey(Req->dreBindInfoKey);
        kvl.Add_HashValue(Req->serverName);
        kvl.Add_HashValue(Req->isIPV6);
        kvl.Add_HashValue(Req->counter);
        kvl.Add_HashValue(Req->sessionTerminateTimerId);
        kvl.Add_HashValue(Req->gxSessionFlag);
        kvl.Add_HashValue(Req->gxxSessionFlag);
        kvl.Add_HashValue(Req->rxSessionFlag);

        m_cacheMgr->StoreEntry(kvl);
        CLOG_DEBUG("Replication Manager:  Key:Value pair updated ");
        if (Resp != NULL)
        {
            Resp->responseID = RM_SUCCESS;
        }

        return 0;
    }

    // This method handles the deletion key:value pair from the Database store
    int ReplicationManager::DeleteCacheEntry(DREBindInfo *Req, DREBindResp *Resp) 
    {
        // handle_DREBind_CacheOP(Req, Resp, M_REPMGR_DELETE_DREBINDINFO);
        if (!m_AmIActive && m_eCurDeployment != A1C1)
        {
            SendDREBindingInfo(Req, M_DREAPP_DELETE_SESSION_ID);
            CLOG_DEBUG("Delete Record Sent to DREAPP"); 
        }
        m_cacheMgr->DeleteEntry(Req->dreBindInfoKey);
        CLOG_DEBUG("Replication Manager:  Cache Entry Deleted");
        if (Resp != NULL)
        {
            Resp->responseID = RM_SUCCESS;
        }
        return 0;
    }


    int ReplicationManager::CreateRxCacheEntry(DRERxBindInfo *Req, DREBindResp *Resp) 
    {
        //handle_DREBind_CacheOP(Req, Resp, M_REPMGR_UPDATE_DREBINDINFO);
        if (!m_AmIActive && m_eCurDeployment != A1C1)
        {
            SendDRERxBindingInfo(Req, M_DREAPP_SAVE_RXSESSION_ID);
            CLOG_DEBUG("Create Record Sent to DREAPP"); // temp code
        }

        // Construct KeyValue object from Req structure.
        KeyValue kvl;
        kvl.Set_HashKey(Req->dreBindInfoKey);
        kvl.Add_HashValue(Req->sessionId);
        kvl.Add_HashValue(Req->isIPv4Address);
        m_cacheMgr->StoreEntry(kvl);
        CLOG_NOTICE("Replication Manager:  Entry Cached");
        if (Resp != NULL)
        {
            Resp->responseID = RM_SUCCESS;
        }
        return 0;
    }

    int ReplicationManager::DeleteRxCacheEntry(DRERxBindInfo *Req, DREBindResp *Resp) 
    {
        //handle_DREBind_CacheOP(Req, Resp, M_REPMGR_UPDATE_DREBINDINFO);
        if (!m_AmIActive && m_eCurDeployment != A1C1)
        {
            SendDRERxBindingInfo(Req, M_DREAPP_DELETE_RXSESSION_ID);
            CLOG_DEBUG("Delete Request Sent to DREAPP"); 
        }

        m_cacheMgr->DeleteEntry(Req->dreBindInfoKey);
        CLOG_NOTICE("Replication Manager: Entry Deleted");
        if (Resp != NULL)
        {
            Resp->responseID = RM_SUCCESS;
        }
        return 0;
    }

    // This method duplicates the DRE Binding data to the 
    // configured list of standby nodes
    void ReplicationManager::ReplicateRecord(DREBindInfo *Req, RepMgrMethods MId)
    {
        // Add Code here to call the Replication Manager's
        // Exposed Interface:Methods
        // Mostly this method handles Create/Modify requests -- To Study further
        MessageId RepMsgID = MakeMsgId(I_REPLICATION_MANAGER, (unsigned) MId);

        // Build Message  and send
        MeSSObj().Send(m_PeerRepMgrInstance, RepMsgID, (void *) Req, sizeof(struct DREBindInfo));

        CLOG_DEBUG(" Create or Update record Replication Message Sent");
    }

    // This method handles all the responses for the create, update and 
    // Delete Cache requests.
    int ReplicationManager::CacheOperationResp(DREBindResp *Resp) 
    {
        // Add code to handle the response
        CLOG_DEBUG("Entry Created/Update/Deleted in Cache");
        return 0;
    }

// End of the Module : repmgr.cpp



