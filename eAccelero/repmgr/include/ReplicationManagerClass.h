/* ********************************-*-H-*-************************************
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

#ifndef  __REPLICATIONMANAGERCLASS_H__
#define  __REPLICATIONMANAGERCLASS_H__

#include <iostream>
#include <string>

#include "MemcachedClass.h"
#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "RepMgrCommon.h"


namespace eAccelero
{
 
 enum DepConfig { A1C1 = 1, A1S1, AnSk, AnAn };
 
//static __thread unsigned Sender_CompId;
//static bool AmIActive = false;
//class MemcachedClient;
    
 // Class for Replication Manager Component
class ReplicationManager : public HAMeSSComponent 
{  
 public:
  // Attributes
  //static bool AmIActive;          // My Active/Standby status    
  // Methods
 ReplicationManager();            // Replication Manager Constructor.
 ~ReplicationManager();           // Destructor
  void Initialize();      // Initialization Method  -- More Comments -- TODO
  void ReadConfiguration(); // Read Configuration File on Startup
  void Terminate();       // Termination Method   -- More Comments -- TODO
  void RegisterMethods(); // Register Methods for calling REPMGR services.
  int  CreateCacheEntry(DREBindInfo *Req, DREBindResp *Resp);  // Create a hash table entry
  int  UpdateCacheEntry(DREBindInfo *Req, DREBindResp *Resp);  // Modify/Update the hash table entry
  int  DeleteCacheEntry(DREBindInfo *Req, DREBindResp *Resp);  // Delete the hash table entry
  int  CreateRxCacheEntry(DRERxBindInfo *Req, DREBindResp *Resp);  // Create a hash table entry
  int  DeleteRxCacheEntry(DRERxBindInfo *Req, DREBindResp *Resp);  // Delete the hash table entry
  int  CacheOperationResp(DREBindResp *Resp);  // Response to Create a hash table entry
  void ReplicateRecord(DREBindInfo *Req, RepMgrMethods MId); 
  void SendDREBindingInfo(DREBindInfo *Req, unsigned DREMId);
  void SendDRERxBindingInfo(DRERxBindInfo *Req, unsigned DREMId);
    
  bool GetState(void);
  
  // CLI Interfacing Methods
  int SetReplLogLevel(ReplLogLevelReq *req, ReplLogLevelResp *resp);
 
  // to set my active/standy status - to be called by AVAILABILITY MANAGER
  int ProcessAvailabilityStatusResetReq(AvailabilityStatusResetReqObj *req, AvailabilityStatusResetRespObj *resp);
  /*  Used to get the Instance Id for a specific Component */
  int ProcessAvailabilityStatusGetReq(AvailabilityStatusReqObj *req, AvailabilityStatusRespObj *resp);
  int ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId);
  int ProcessAvailabilityStatusResetPostFunc();

 private:
     // Methods
     int Handle_DREBind_CacheOP(DREBindInfo *Req, DREBindResp *Resp, RepMgrMethods MId);
     int Handle_DRERxBind_CacheOP(DRERxBindInfo *Req, DREBindResp *Resp, RepMgrMethods MId);
     int SetCurDeployment(void);
     bool m_AmIActive;          // My Active/Standby status
     MeSSEndpoint m_PeerRepMgrInstance;     // Peer Instance Information.
     MeSSEndpoint m_DreStandbyInstance;     // Peer Instance Information.
     DepConfig m_eCurDeployment;    // Current Deployment Configuration
     MemcachedClient *m_cacheMgr;        // Object to handle key:value storage access
     
 };  // RepMgrApp

}  // namespace eAccelero

#endif  //  __EACC_RepMgr_h__

