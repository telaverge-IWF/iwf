/* ********************************-*-C-*-************************************
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

#ifndef __CMAPIDRECONFIG_H_
#define __CMAPIDRECONFIG_H_

#include "dreconfig.h"
#include "CMAPICommon.h"
#include "dia_mgmt.h"
#include "StaticRoutingTable.h"

class CMAPIDreConfig : public DiaMgtMethods, public TraceConfigFetch,public DiaMgtForStaticRoutingMethods
{
    public:
        CMAPIDreConfig();
        ~CMAPIDreConfig(); 
        int HandleLocalHostConfigReqs(LocalHostConfig *req,DRECfgResp *resp);
        int HandleDreSetPeerConfigReqs(PeersConfig *req,DRECfgResp *resp);
        int HandleDreDelPeerConfigReqs(PeersConfig *req,DRECfgResp *resp);
        int HandleDreSetRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp);
        int HandleDreDelRealmConfigReqs(RealmsConfig *req,DRECfgResp *resp);
        int HandleTraceConfigReqs(TraceReq *req, TraceResp *resp);
        int GetTraceConfigReqs(TraceReq *req, TraceResp *resp);
        int HandleStaticRoutingTableConfigReqs(StaticRoutingTableConfigReq* req,
                StaticRoutingTableConfigResp* resp);
        int HandleTHFConfig(THFReq*, THFResp*);
        int HandleSDTFConfig(SDTFReq*, SDTFResp*);
        int HandlePluginConfig(TransformPluginConfigReq*, DRECfgResp*);
        int HandleDictionaryConfig(DictionaryConfigReq*, DRECfgResp*);

    private: // Methods
        // LocalHostRelated Methods
        int ModifyLocalHost(LocalHostConfig *localhost);
        int SetLocalHost(LocalHostConfig *localhost);
        bool IsSameLocalHost(std::string lhost);

        // Peer related methods
        int ModifyPeerConfig(PeerConfig& Peer);
        int AddPeerConfig(PeerConfig& Peer);
        int AddDictionaryID(PeerConfig* Peer);
        int DeleteDictionaryID(PeerConfig* Peer);
        int ConfigPeerStatus(std::string peer, std::string realm, bool state);
        unsigned int GetAllPeersState(DRECfgResp *resp);

        // Realm related methods
        int AddRealmConfig(RealmConfig& Realm);
        int ModifyRealmConfig(RealmConfig& Realm);
        int AddRealmRouting(std::string Realm, Destination& Dest);
        int DeleteRealmRouting(std::string Realm, Destination& Dest);
        int ModifyRealmRouting(std::string Realm, Destination& Dest);

        //Trace related methods
        int AddTraceConfig(TraceConfig& tracecfg);
        int ModifyTraceConfig(TraceConfig& tracecfg);
        int DeleteTraceConfig(TraceConfig& tracecfg);
        int DreTraceErrorConfig(int retVal, TraceConfig tracecfg ,TraceResp *resp);
        int DreStaticRoutingErrorConfig(int retVal, StaticRoutingTableConfig staticRoutingCfg,
                StaticRoutingTableConfigResp *resp);
    private:
        DiaMgmt *m_diaMgtObj;
};

#endif   //  __CMAPIDRECONFIG_H_
