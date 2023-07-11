
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


#include "MeSSComponent.h"
#include "ComponentDefines.h"
#include <iostream>
#include "Compo_def.h"
#include "CMAPICommon.h"
#include "CMApiComp.h"
#include "CMAPILib.h"

#include "ThreadQueue.h"
#include "Thread.h"

#define TESTAGENT_COMP_ID  COMP_CLI_PROC
#if 0
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using namespace eAccelero;

using namespace google::protobuf::io;

class TestAgent: public MeSSComponent
{
    public:
        TestAgent(int CompID)
            : MeSSComponent("TestAgent", CompID)
        {
        }

        void Initialize()
        {
            MeSSComponent::Initialize();

            TopologyEvent compEvent(COMP_CONFIG_MANAGER);
            MeSSObj().TopSvc().Subscribe(
                    EventSlot<TopologyEvent, TestAgent>(this, &TestAgent::OnServerEvent),
                    compEvent);          
        }
        void Terminate()
        {
            MeSSComponent::Terminate();
        }

        int OnServerEvent(TopologyEvent &event)
        {
            if (event.NotificationType() == TopologyEvent::NOTIFY_TYPE_PUBLISHED)
            {
                std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
                std::cout << "Config Manager UP" << endl;
            }
            return 0;
        }

    protected:

};

class ApiUser: public Runnable
{
    private:

        void Initialize()
        {
            m_cmapi = new CMApiComponents();
            m_cmapi->InitializeLibrary();
            m_cmapiprod = new CMAPIProdConfig();
            m_cmapiprod->InitializeLibrary();
        }
        void SetTLSConfiguration()
        {
            TLSConfig tlsconfig;
            unsigned short Val;
            cout << "Enter the EnableIDVerification : " ; cin >> Val;
            tlsconfig.set_enableidverification(Val==0?false:true);
            cout << "Enter the EnableCRLVerification : " ; cin >> Val;
            tlsconfig.set_enablecrlverification(Val==0?false:true);
            
            if(m_cmapiprod->SetTLSConfiguration(tlsconfig) == CMAPI_SUCCESS)
                cout << " Successfully configured TLS config" <<endl;
            else
                cout << " Error setting TLS config"<<endl;
        }
        void GetTLSConfiguration()
        {
            TLSConfig tlsconfig;
            if(m_cmapiprod->GetTLSConfiguration(tlsconfig) == CMAPI_SUCCESS)
            {
                cout << " EnableIDVerification : " << (tlsconfig.enableidverification() == true?"Enabled":"Disabled") <<endl;
                cout << " EnableCRLVerification : " << (tlsconfig.enablecrlverification() == true?"Enabled":"Disabled") <<endl;
            }   
            else
                cout << " Error getting TLS config"<<endl;
        }
        void GetTlsCipherCfg()
        {
            TLSCipherConfigs tlscipher;
            if(m_cmapiprod->GetTlsCipherCfg(tlscipher) == CMAPI_SUCCESS)
            {
                unsigned int NumofTls = tlscipher.tlsciphers_size();
                for(unsigned int tls = 0 ; tls < NumofTls; tls++)
                {
                    TLSCipherConfig cipher = tlscipher.tlsciphers(tls);
                    cout << " Cipher Suite Name : " << cipher.ciphersuitename() <<endl;
                    cout << " EnableCipherSuite : " << (cipher.enableciphersuite() == true?"Enabled":"Disabled") <<endl;
                }
            }
            else
                cout << " Error getting TlsCipher config "<<endl;
        }
        void EnableTlsCipherSuite()
        {
            string StrVal;
            cout << " Cipher Suite Name : "; cin >> StrVal;
            if(m_cmapiprod->EnableTlsCipherSuite(StrVal) == CMAPI_SUCCESS)
                cout << "successfully enabled Cipher Suite " <<endl;
            else
                cout << "Error enabling Cipher Suite " <<endl;
        }
        void DisableTlsCipherSuite()
        {
            string StrVal;
            cout << " Cipher Suite Name : "; cin >> StrVal;
            if(m_cmapiprod->DisableTlsCipherSuite(StrVal) == CMAPI_SUCCESS)
                cout << "successfully disabled Cipher Suite " <<endl;
            else
                cout << "Error disabling Cipher Suite " <<endl;
        }
        void AddCACRLConfiguration()
        {
            TrustedCAConfiguration trustedca;
            string StrVal;
            cout << "Enter the CA file name : " ;cin >>StrVal;
            trustedca.set_cafile(StrVal);
            cout << "Enter the CRL file name : " ;cin  >>StrVal;
            trustedca.set_crlfile(StrVal);
            if(m_cmapiprod->AddCACRLConfiguration(trustedca) == CMAPI_SUCCESS)
                cout << " Successfully configured Trusted CA configuration" <<endl;
            else
                cout << " Error setting Trusted CA configuration" <<endl; 

        }
        void DeleteCACRLConfiguration()
        {
            TrustedCAConfiguration trustedca;
            string StrVal;
            cout << "Enter the CA file name :" ;cin >>StrVal;
            trustedca.set_cafile(StrVal);
        #if 0
            cout << "Enter the CRL file name :" ;cin  >>StrVal;
            trustedca.set_crlfile(StrVal);
        #endif
            if(m_cmapiprod->DeleteCACRLConfiguration(trustedca) == CMAPI_SUCCESS)
                cout << " Successfully deleted Trusted CA configuration" <<endl;
            else
                cout << " Error deleting Trusted CA configuration" <<endl; 

        }
        void ModifyCACRLConfiguration()
        {
            
            TrustedCAConfiguration trustedca;
            string StrVal;
            cout << "Enter the CA file name :" ;cin >>StrVal;
            trustedca.set_cafile(StrVal);
            cout << "Enter the CRL file name :" ;cin  >>StrVal;
            trustedca.set_crlfile(StrVal);
            if(m_cmapiprod->ModifyCACRLConfiguration(trustedca) == CMAPI_SUCCESS)
                cout << " Successfully modified Trusted CA configuration" <<endl;
            else
                cout << " Error modifying Trusted CA configuration" <<endl; 
        }
        void GetCACRLConfiguration()
        {
            CACRLs cacrls;
            //TrustedCAConfiguration *trustedcaconfig = cacrls.add_tcacfg();
            if(m_cmapiprod->GetCACRLConfiguration(cacrls) == CMAPI_SUCCESS)
            {
                unsigned int Numofcrl = cacrls.tcacfg_size();
                for(unsigned int crl = 0; crl < Numofcrl; crl++)
                {
                    TrustedCAConfiguration trustedca = cacrls.tcacfg(crl);
                    cout << "CA file : " << trustedca.cafile() <<endl;
                    cout << "CRL file: " << trustedca.crlfile() <<endl;
                }

            }    
            else
                cout << " Error getting Trusted CA configuration" <<endl;

        }
        void SetSCTPConfig()
        {
            SctpProtocol sctpconfig;
            unsigned short Val;
            string StrVal;
            int NumVal;
            cout << "Enter the HeartBeatEnable value : ";cin >> Val;
            sctpconfig.set_heartbeatenable(Val==0?false:true);
            cout << "Enter HearBeatTimeOut : ";cin >> NumVal;
            sctpconfig.set_hearbeattimeout(NumVal);
            cout << "InitialTimeOut : "; cin >> NumVal;
            sctpconfig.set_initialtimeout(NumVal);
            cout << "MaximumAttempts : ";cin >> NumVal;
            sctpconfig.set_maximumattempts(NumVal);
            cout << "RTOMaximum : ";cin >> NumVal;
            sctpconfig.set_rtomaximum(NumVal);
            cout << "RTOMinimum : ";cin >> NumVal;
            sctpconfig.set_rtominimum(NumVal);
            cout << "RTOInitial : ";cin >> NumVal;
            sctpconfig.set_rtoinitial(NumVal);
            cout << "PathFailRetryCount : ";cin >> NumVal;
            sctpconfig.set_pathfailretrycount(NumVal);

            if(m_cmapiprod->SetSctpProtocolConfiguration(sctpconfig) == CMAPI_SUCCESS)
                cout << " Successfully configured SCTP Config" <<endl;
            else
                cout << " Error setting SCTP Config" <<endl;
        }

        void GetSCTPConfig()
        {

            SctpProtocol sctpconfig;
            if(m_cmapiprod->GetSctpProtocolConfiguration(sctpconfig) == CMAPI_SUCCESS)
            {
                cout << "HeartBeatEnable value : " << (sctpconfig.heartbeatenable()==true?"Enabled":"Disabled") <<endl;
                cout << "HearBeatTimeOut : " << sctpconfig.hearbeattimeout()<<endl;
                cout << "InitialTimeOut : " << sctpconfig.initialtimeout() <<endl;
                cout << "MaximumAttempts : " << sctpconfig.maximumattempts() <<endl;
                cout << "RTOMaximum : " << sctpconfig.rtomaximum() <<endl;
                cout << "RTOMinimum : " << sctpconfig.rtominimum() <<endl;
                cout << "RTOInitial : " << sctpconfig.rtominimum() <<endl;
                cout << "PathFailRetryCount : " << sctpconfig.pathfailretrycount() <<endl;
            }
            else
                cout << " Error Getting SCTP Config" <<endl;

        }
        void SetGeneralConfig()
        {
            GeneralConfig generalconfig;
            int Val;
            cout << "Enter EnablePeerIPCheck : "; cin >>Val;
            generalconfig.set_enablepeeripcheck(Val);

            if(m_cmapiprod->SetGeneralConfiguration(generalconfig) == CMAPI_SUCCESS)
                cout << "success setting StackGeneralConfig " <<endl;
            else
                cout << "error setting StackGeneralConfig " <<endl;
        }

        void GetGeneralConfig()
        {
            GeneralConfig generalconfig;
            if(m_cmapiprod->GetGeneralConfiguration(generalconfig) == CMAPI_SUCCESS)
                cout << " EnablePeerIPCheck : " << (generalconfig.enablepeeripcheck() == true?"Enabled":"Disabled") <<endl;
            else
                cout << " Error Getting StackGeneralConfig" <<endl;
        }
        void ModifyASFGroup()
        {
            ASGroupsCfg AsGroups;
            string AsgroupName;
            string StrVal;
            unsigned short Val;
            int NumVal;
            ASGroupCfg *Asgroup = AsGroups.add_asgroups();
            cout << "Enter the AsGroupName : " << endl;
            cin >> AsgroupName;
            Asgroup->set_appgroup(AsgroupName);
            cout << "Enter the Priority : "; cin >> NumVal;
            Asgroup->set_priority(NumVal);
            cout << "Enter the ishostedapp : "; cin >> Val;
            Asgroup->set_ishostedapp(Val==0?false:true);
            cout << "Enter the maxappinstances : "; cin >> NumVal;
            Asgroup->set_maxappinstances(NumVal);
            cout << "Enter the LB Algorithm : "; cin >> StrVal;
            LBAlgorithm* lbalgo = Asgroup->mutable_lbalgo();
            lbalgo->set_lbmethod(StrVal);
            cout << "Enter the user name who created group : "; cin >> StrVal;
            Asgroup->set_createdby(StrVal);
            cout << "Enter the added time : "; cin >> StrVal;
            Asgroup->set_creationdate(StrVal);
            cout << "Enter the user name who modified group : "; cin >> StrVal;
            Asgroup->set_modifiedby(StrVal);
            cout << "Enter the modification time : "; cin >> StrVal;
            Asgroup->set_modifytime(StrVal);
            if (m_cmapi->ModifyASGroup(AsGroups) == CMAPI_SUCCESS)
                cout << "successfully modified ASF group " << endl;
            else
                cout << "error modify ASF group " << endl;
        }

        void SetASFGroup()
        {
            ASGroupsCfg AsGroups;
            string AsgroupName;
            string StrVal;
            unsigned short Val;
            int NumVal;
            ASGroupCfg *Asgroup = AsGroups.add_asgroups();
            cout << "Enter the AsGroupName : " << endl;
            cin >> AsgroupName;
            Asgroup->set_appgroup(AsgroupName);
            cout << "Enter the Priority : "; cin >> NumVal;
            Asgroup->set_priority(NumVal);
            cout << "Enter the ishostedapp : "; cin >> Val;
            Asgroup->set_ishostedapp(Val==0?false:true);
            cout << "Enter the maxappinstances : "; cin >> NumVal;
            Asgroup->set_maxappinstances(NumVal);
            cout << "Enter the LB Algorithm : "; cin >> StrVal;
            LBAlgorithm* lbalgo = Asgroup->mutable_lbalgo();
            lbalgo->set_lbmethod(StrVal);
            cout << "Enter the user name who created group : "; cin >> StrVal;
            Asgroup->set_createdby(StrVal);
            cout << "Enter the added time : "; cin >> StrVal;
            Asgroup->set_creationdate(StrVal);
            cout << "Enter the user name who modified group : "; cin >> StrVal;
            Asgroup->set_modifiedby(StrVal);
            cout << "Enter the modification time : "; cin >> StrVal;
            Asgroup->set_modifytime(StrVal);

            if (m_cmapi->AddASGroup(AsGroups) == CMAPI_SUCCESS)
                cout << "Succesfully created ASF Group" << endl;
            else
                cout << "Error create ASF Group " << endl;
            
        }
        
        void DelASFGroup()
        {
            ASGroupsCfg AsGroups;
            string AsgroupName;
            ASGroupCfg *Asgroup = AsGroups.add_asgroups();
            cout << "Enter the AsGroupName : " << endl;
            cin >> AsgroupName;
            Asgroup->set_appgroup(AsgroupName);
            if (m_cmapi->RemoveASGroup(AsGroups) == CMAPI_SUCCESS)
                cout << " Succesfully Deleted ASF Group" << endl;
            else 
                cout << "Error deleting ASF Group " << endl;

        }
        void SetASFTimeout()
        {
            unsigned short NumVal;
            cout << "Enter the AppRespTimeOut : " ; cin >> NumVal;
            if (m_cmapi->SetASFAppResponseTimeout(NumVal) == CMAPI_SUCCESS)
                cout << "succesfully set Asf Response time out" <<endl;
            else
                cout << "Error Setting Asf Resp Time out" <<endl;
        }

        void GetASFTimeout()
        {
            int NumVal;
            cout << " Get Asf Response time out" << endl;
            if (m_cmapi->GetASFAppResponseTimeout(NumVal) == CMAPI_SUCCESS)
                cout << " Response time out = " << NumVal <<endl;
            else
                cout << "Error Getting Asf Resp Time out" <<endl;
        }
        void GetASFGroup()
        {
            ASGroupsCfg AsGroups;
            string StrVal;
            cout << "Enter ASFGroup Details : " << endl;
            cout << "Enter ASFGroup Name : (or leave Blank for None) "; 
            cin >> StrVal;
            ASGroupCfg *Asgroup = AsGroups.add_asgroups();
            Asgroup->set_appgroup(StrVal);
            cout << "Getting Peer Groups " << endl;
            if (m_cmapi->GetASGroupConfig(AsGroups) == CMAPI_SUCCESS)
            {
                unsigned int NumAsfGroup = AsGroups.asgroups_size();

                cout << "Num ASFGroups " << NumAsfGroup << endl;
                for(unsigned int NumAsf = 0 ; NumAsf < NumAsfGroup ; NumAsf++)
                {
                    ASGroupCfg Asgrp = AsGroups.asgroups(NumAsf);
                    cout << "ASF Group Name  :  " << Asgrp.appgroup() <<endl;
                    cout << "Priority        :  " << Asgrp.priority() <<endl;
                    cout << "ishostedapp     :  " << (Asgrp.ishostedapp()==true?"Enabled":"Disabled") << endl;
                    cout << "maxappinstances :  " << Asgrp.maxappinstances() <<endl;
                    LBAlgorithm* lbalgo = Asgrp.mutable_lbalgo();
                    cout << "LB Algorithm    :  " << lbalgo->lbmethod() <<endl;
                    cout << "user created    :  " << Asgrp.createdby() <<endl;
                    cout << "created time    :  " << Asgrp.creationdate() <<endl;
                    cout << "user modified   :  " << Asgrp.modifiedby() <<endl;
                    cout << "modified time   :  " << Asgrp.modifytime() <<endl;
                }
                
            }
            else
            cout << "Error Fetching Asf Group" << endl;
        }


#if 0
        void CreatePeerGroups()
        {
            LBPeerGroups Req;
            LBPeerGroupResp Resp;
            string StrVal;
            unsigned short NumVal;
            cout << "Enter Peer Group : " << endl;
            string peergroupname;
            cin >> peergroupname;
            LBPeerGroup*pg = Req.add_peergroups();
            pg->set_lbpeergroupname(peergroupname);
            cout << "Enter PeerGroup ID : "; cin >> NumVal; pg->set_lbpeergroupid(NumVal);
            cout << "Enable PCRF Binding : ";  cin >> NumVal; 
            pg->set_enablepcrfbinding(NumVal==0?false:true);
            cout << "Enter LB Algorithm : "; cin >> StrVal;
            LBAlgorithm* lbalgo = pg->mutable_lbalgo();
            lbalgo->set_lbmethod(StrVal);
            cout << "Enter Peer Name : ";
            cin >> StrVal;
            LBPeer* peer = pg->add_lbpeers();
            peer->set_lbpeername(StrVal);
            cout << "Enter Peer ID : "; cin >> NumVal; peer->set_lbpeerid(NumVal);
            cout << "Enter Peer realm : " ; cin >> StrVal;
            peer->set_lbpeerrealm(StrVal);
            cout << "Enter Weightage : "; cin >> NumVal; peer->set_lbpeerweight(NumVal);
            cout << "Enter Priority  : "; cin >> NumVal; peer->set_lbpeerpriority(NumVal);

            if (m_cmapi->CreatePeerGroup(Req,&Resp) == CMAPI_SUCCESS)
            {
                cout << "Succesfully created Peer Group" << endl;
            } else {
                cout << "Error create Peer Group " << endl;
            }
        }

        void GetPeerGroups()
        {
            LBPeerGroups Req; LBPeerGroups Resp;
            ErrorDetails Err;
            string StrVal; unsigned int NumPeers;
            cout << "Enter Peer Details : " << endl;
            cout << "Enter PeerGroup Name : (or leave Blank for None) "; 
            cin >> StrVal;
            LBPeerGroup* PGrp = Req.add_peergroups();
            PGrp->set_lbpeergroupname(StrVal);

            cout << "Getting Peer Groups " << endl;
            if (m_cmapi->GetPeerGroup(Req, Resp, Err) == CMAPI_SUCCESS)
            {
                unsigned int NumPGrps = Resp.peergroups_size();
                cout << "Num Groups " << NumPGrps << endl;
                for (unsigned int nPGrp = 0; nPGrp < NumPGrps; nPGrp++)
                {
                    LBPeerGroup PGrp = Resp.peergroups(nPGrp);
                    cout << "PeerGroup Name :   " << PGrp.lbpeergroupname() << endl;
                    cout << "PeerGroup ID   :  " << PGrp.lbpeergroupid() << endl;
                    //cout << "PeerGroup Algo :  " << PGrp.
                    cout << "PeerGroup PCRF :  " << (PGrp.enablepcrfbinding()==true?"Enabled":"Disabled") << endl;
                    NumPeers = PGrp.lbpeers_size();
                    for (unsigned int nP = 0; nP < NumPeers; nP++)
                    {
                        LBPeer Pr = PGrp.lbpeers(nP);
                        cout << "Peer Name : " << Pr.lbpeername() << endl;
                        cout << "Peer ID   : " << Pr.lbpeerid() << endl;
                        cout << "Peer Realm: " << Pr.lbpeerrealm() << endl;
                        cout << "Peer Weight : " << Pr.lbpeerweight() << endl;
                        cout << "Peer Priority : " << Pr.lbpeerpriority() << endl;
                    }
                }
            } else {
                cout << "Error Fetching Peer Group Names " << endl;
            }
        }

        void GetPeerGroupStats()
        {
            ERLBFPeerGroupStatsReq Request;
            ERLBFPeerGroupStatsResp Resp;
            uint32_t pgID;
            while(1)
            {
                cout << "Enter Peer group ID's : " << endl;
                cout << "Enter PeerGroup ID : (or Enter 0 to Exit) "; 
                cin >> pgID;
                if(pgID == 0)
                    break;
                Request.add_peergroupid(pgID);
            }

            cout << "Getting Peer Group Stats " << endl;
            if (m_cmapi->GetPeerGroupStats(Request, Resp) == CMAPI_SUCCESS)
            {
                unsigned int NumPGrps = Resp.peergroupstats_size();
                cout << "Num Groups " << NumPGrps << endl;
                for (unsigned int nPGrp = 0; nPGrp < NumPGrps ; nPGrp++)
                {
                    ERLBFPeerGroupStats PGrp = Resp.peergroupstats(nPGrp);
                    cout << "PeerGroup ID   :  " << PGrp.peergroupid() << endl;
                    cout << "PeerGroup Name :  " << PGrp.peergroupname() << endl;
                    unsigned int NumPeers = PGrp.peerstats_size();
                    for (unsigned int nPeer = 0; nPeer < NumPeers ; nPeer++)
                    {
                        ERLBFPeerStats pStats = PGrp.peerstats(nPeer);
                        cout << "    Peer ID   : " << pStats.peerid() << endl;
                        cout << "    Peer Name   : " << pStats.peername() << endl;
                        cout << "    Num of Msgs Sent to the Peer: " << pStats.msgssent() << endl;
                        cout << "    Num of Msgs Skipped for Peer since it is down: " << pStats.msgsskipped() << endl;
                    }
                }

            } else {
                cout << "Error Fetching Peer Group Stats." << endl;
            }
        }

        void GetSessionBindingStats()
        {
            SessionBindingStatsReq Request;
            SessionBindingStatsRsp Resp;

            cout << "Getting Peer Group Stats " << endl;
            if (m_cmapi->GetSessionBindingStats(Request, Resp) == CMAPI_SUCCESS)
            {
                SessionBindingStats stats = Resp.sessstats();
                cout << "Total Current Session Binds   :  " << stats.currentsessbinds() << endl;
                cout << "Total Number of Session Binds Expired  : " << stats.totalsessbindsexpired() << endl;
                cout << "Total Number of Session Binds Added: " << stats.totalsessbindsadded() << endl;
                cout << "Total Number of Session Binds Deleted : " << stats.totalsessbindsdeleted() << endl;
            } else {
                cout << "Error Fetching Session Binding Stats." << endl;
            }
        }

        void ModifyPeerGroups(){
            LBPeerGroups Req;
            LBPeerGroupResp Resp;
            string StrVal;
            unsigned short NumVal;
            cout << "Enter Peer Group : " << endl;
            string peergroupname;
            cin >> peergroupname;
            LBPeerGroup*pg = Req.add_peergroups();
            pg->set_lbpeergroupname(peergroupname);
            cout << "Enter PeerGroup ID : "; cin >> NumVal; pg->set_lbpeergroupid(NumVal);
            cout << "Enable PCRF Binding : ";  cin >> NumVal; 
            pg->set_enablepcrfbinding(NumVal==0?false:true);
            cout << "Enter LB Algorithm : "; cin >> StrVal;
            LBAlgorithm* lbalgo = pg->mutable_lbalgo();
            lbalgo->set_lbmethod(StrVal);
            cout << "Enter Peer Name : ";
            cin >> StrVal;
            LBPeer* peer = pg->add_lbpeers();
            peer->set_lbpeername(StrVal);
            cout << "Enter Peer ID : "; cin >> NumVal; peer->set_lbpeerid(NumVal);
            cout << "Enter Peer realm : " ; cin >> StrVal;
            peer->set_lbpeerrealm(StrVal);
            cout << "Enter Weightage : "; cin >> NumVal; peer->set_lbpeerweight(NumVal);
            cout << "Enter Priority  : "; cin >> NumVal; peer->set_lbpeerpriority(NumVal);

            if (m_cmapi->ModifyPeerGroup(Req,&Resp) == CMAPI_SUCCESS)
            {
                cout << "Succesfully Modified Peer Group" << endl;
            } else {
                cout << "Error Modify Peer Group " << endl;
            }
        }
        void DeletePeerGroups(){
            LBPeerGroups Req;
            LBPeerGroupResp Resp;
            string StrVal;
                cout << "Enter Peer Group  To be delete: " << endl;
                string peergroupname;
                cin >> peergroupname;
            if (m_cmapi->DeletePeerGroup(peergroupname,&Resp) == CMAPI_SUCCESS)
            {
                cout << "Succesfully deleted the  Peer Group" << endl;
            } else {
                cout << "Error deleting  Peer Group " << endl;
            }
        }

        void DeletePeers(){
            LBPeerGroups Req;
            LBPeerGroupResp Resp; 
            string StrVal; string RealmVal;
            cout << "Enter Peer Group : " << endl;
            string peergroupname;
            cin >> peergroupname;
            cout << "Enter Peer Name : ";
            cin >> StrVal;
            cout << "Enter Realm Name : ";
            cin >> RealmVal;
            if (m_cmapi->RemovePeerFromPeerGroup(peergroupname, StrVal, RealmVal, &Resp) == CMAPI_SUCCESS)
            {
                cout << "Peer deleted Successfully " << endl;

            }
        }

        void ModifyPeers(){
            LBPeerGroups Req; string StrVal; int NumVal;
            LBPeerGroupResp Resp;
            LBPeerGroup*pg = Req.add_peergroups();
            cout << "Enter Peer group : ";
            cin >> StrVal;
            pg->set_lbpeergroupname(StrVal);
            cout << "Enter Peer Name : ";
            cin >> StrVal;
            LBPeer* peer = pg->add_lbpeers();
            peer->set_lbpeername(StrVal);
            cout << "Enter Peer ID : "; cin >> NumVal; peer->set_lbpeerid(NumVal);
            cout << "Enter Peer realm : " ; cin >> StrVal;
            peer->set_lbpeerrealm(StrVal);
            cout << "Enter Weightage : "; cin >> NumVal; peer->set_lbpeerweight(NumVal);
            cout << "Enter Priority  : "; cin >> NumVal; peer->set_lbpeerpriority(NumVal);
            if (m_cmapi->ModifyPeerConfig(pg->lbpeergroupname(), *peer,&Resp) == CMAPI_SUCCESS)
            {
                cout << "Peer Modified Successfully " << endl;
            }
        }
        void AddPeers(){
               LBPeerGroups Req; string StrVal; int NumVal;
                LBPeerGroupResp Resp;
                LBPeerGroup*pg = Req.add_peergroups();
                cout << "Enter Peer group : ";
                cin >> StrVal;
                pg->set_lbpeergroupname(StrVal);
                cout << "Enter Peer Name : ";
                cin >> StrVal;
                LBPeer* peer = pg->add_lbpeers();
                peer->set_lbpeername(StrVal);
                cout << "Enter Peer ID : "; cin >> NumVal; peer->set_lbpeerid(NumVal);
                cout << "Enter Peer realm : " ; cin >> StrVal;
                peer->set_lbpeerrealm(StrVal);
                cout << "Enter Weightage : "; cin >> NumVal; peer->set_lbpeerweight(NumVal);
                cout << "Enter Priority  : "; cin >> NumVal; peer->set_lbpeerpriority(NumVal);
            if (m_cmapi->AddPeerToPeerGroup(pg->lbpeergroupname(), *peer, &Resp) == CMAPI_SUCCESS)
            {
                cout << "Peer Added Successfully " << endl;
            }
        }

#endif
        void GetAlgos() {

            LBAlgorithms AllAlgos;
            ErrorDetails Err;
            LBAlgorithm_SuppComponentID CompID; string CName;
            cout << "Enter Component Name ASF/ERLBF/ALL : " << endl; 
            cin >> CName;
            if (CName.compare("ASF") == 0)
                CompID = LBAlgorithm_SuppComponentID_COMP_ASF;
            else if (CName.compare("ERLBF") == 0)
                CompID = LBAlgorithm_SuppComponentID_COMP_ERLBF;
            else 
                CompID = LBAlgorithm_SuppComponentID_COMP_ALL;

            if (m_cmapi->GetLBAlgorithmSchemes(CompID,
                               AllAlgos,Err) == CMAPI_SUCCESS)
            {
                int Num = AllAlgos.lbalgos_size();
                cout << "List of Algos : "  << Num << endl;
                if ( Num > 0)
                {
                    cout << "List of Algos : "  << endl;
                    for (int i =0; i < Num; i++)
                    {
                        LBAlgorithm *Algo = AllAlgos.mutable_lbalgos(i);
                        cout << "Algorithm : " << Algo->lbmethod() << endl;
                        cout << "Desc      : " << Algo->lbmethoddesc() << endl;
                    }
                }
            }

        }

        void AddAlgo() {
            LBAlgorithm Req; string strval;
            int val;
            
            LBPeerGroupResp Resp; 
            cout << "Enter LB Method : " ; cin >> strval; Req.set_lbmethod(strval);
            cout << "Enter Description : "; cin >> strval; Req.set_lbmethoddesc(strval);
            cout << " Available component ids:   1 - ASF, 2 - ERLBF, 0 - ALL, 3 - Both ASF AND ERLBF" <<endl;
            cout << "Enter LB component : "; cin >> val; Req.set_suppcomponent((LBAlgorithm_SuppComponentID)val);
            if (m_cmapi->AddLBAlgorithmSchemes(Req,&Resp) == CMAPI_SUCCESS)
            {
                cout << " Successfully Added Algorithm " << endl;
            }

        }
        void DelAlgo() {

            LBAlgorithm Req; string strval;
            LBPeerGroupResp Resp;
            cout << "Enter LB Method to Delete: " ; cin >> strval; Req.set_lbmethod(strval);
            if (m_cmapi->DeleteLBAlgorithmSchemes(strval,&Resp) == CMAPI_SUCCESS)
            {
                cout << " Successfully Delete Algorithm " << endl;
            }
        }
        void ModAlgo() {
            LBAlgorithm Req; string strval;
            int val;
            LBPeerGroupResp Resp;
            cout << "Enter LB Method to Modify: " ; cin >> strval; Req.set_lbmethod(strval);
            cout << "Enter Description : "; cin >> strval; Req.set_lbmethoddesc(strval);
            cout << " Available component ids:   1 - ASF, 2 - ERLBF, 0 - ALL, 3 - Both ASF AND ERLBF" <<endl;
            cout << "Enter LB component : "; cin >> val; Req.set_suppcomponent((LBAlgorithm_SuppComponentID)val);
            if (m_cmapi->ModifyLBAlgorithmSchemes(Req,&Resp) == CMAPI_SUCCESS)
            {
                cout << " Successfully Modified Algorithm " << endl;
            }
        }

#if 0
        void SetLoggingConfig()
        {
            LoggerInfo logInfo;
            string compName;
            int channel,level,i=1;
            LoggerConf_LogChannel logchannel;
            LoggerConf_LogLevel loglevel;
            string input;
            LoggerConfResp Resp;

            do
            {
                LoggerConf *logger = logInfo.add_loggerconfig();
                cout << "Enter the Component Name : " << endl;
                cin >> compName;
                logger->set_componentname(compName);

                cout << " 1. SYSLOG 2. FILE 3. CONSOLE " << endl;
                cout << " Choose Log Channel :  " << endl; 
                cin >> channel;
                logchannel = ((channel == 1) ? LoggerConf_LogChannel_SYSLOG :((channel == 2) ? LoggerConf_LogChannel_FILENAME : LoggerConf_LogChannel_CONSOLE));
                logger->set_channel(logchannel);

                cout << " Choose the Preferred Log Level : " << endl;
                cout << " 1. CRITICAL_LOG  2. ERROR_LOG  3. WARNING_LOG " << endl;
                cout << " 4. NOTICE_LOG  5. INFO_LOG 6. DEBUG_LOG " << endl;
                cin >> level;

                if(level <= 3)
                { 
                    loglevel = ((level == 1) ? LoggerConf_LogLevel_CRITICAL_LOG : ((level == 2) ? LoggerConf_LogLevel_ERROR_LOG : LoggerConf_LogLevel_WARNING_LOG));
                    logger->set_level(loglevel);
                }
                else
                {
                    loglevel = ((level == 4) ? LoggerConf_LogLevel_NOTICE_LOG : ((level == 5) ? LoggerConf_LogLevel_INFO_LOG : LoggerConf_LogLevel_DEBUG_LOG));
                    logger->set_level(loglevel);
                }

                cout << " Do you want to set Log for another component(y/n) : " << endl;
                cin >> input ;
                i++;
            }while((input.compare("n")) != 0);
            if(m_cmapi->SetLogConfig(logInfo,&Resp) == CMAPI_SUCCESS)
            {
                cout << " Succesfully set the components logging configuration " << endl;
            }
            else
                cout << " Error in setting Loggin configuration" << endl;
        }

        void GetLoggingConfig()
        {
            LoggerInfo logInfo;
            ErrorDetails Err;
            string compoName;

            cout << " Enter the Component Name to fetch Logging config " << endl;
            cin >> compoName;

            /*CMAPI to fetch the Logging Configuration  
              If the component name is empty then logging config
              of all the components will be fetched*/
            if(m_cmapi->GetLogConfig(compoName, logInfo, Err) == CMAPI_SUCCESS)
            {
                int numOfCmp = logInfo.loggerconfig_size();
                for(int curCmp = 0 ; curCmp < numOfCmp ; curCmp++)
                {
                    LoggerConf curLogConfig = logInfo.loggerconfig(curCmp);

                    cout << " Components Logging details " << endl;
                    cout << "-------------------------------" << endl;
                    cout << " Component Name  : " << curLogConfig.componentname() << endl;
                    cout << " Log Channel set : " << curLogConfig.channel() << endl;
                    cout << " Log Level set   : " << curLogConfig.level() << endl;
                }
            }
            else
                cout << " Error in fetching the Logging Configurations " << endl;
        }

        void SetLogChannel()
        {
            string compoName;
            LoggerConf_LogChannel channel;
            LoggerConfResp Resp;
            int option;
            cout << "Enter the Component Name " << endl;
            cin >> compoName;
            cout << " Choose the Preferred Log Channel : " << endl;
            cout << " 1. SYSLOG " << endl;
            cout << " 2. FILe " << endl;
            cout << " 3. CONSOLE " << endl;
            cin >> option;
            switch(option)
            {
                case 1:
                    channel = LoggerConf_LogChannel_SYSLOG;
                    break;
                case 2:
                    channel = LoggerConf_LogChannel_FILENAME;
                    break;
                case 3:
                    channel = LoggerConf_LogChannel_CONSOLE;
                    break;
                default :
                    cout << "Invalid Log Channel " << endl;
                    break; 
            }
            cout << " Componenet Name : " << compoName << endl;
            cout << " Log Channel     : " << channel << endl;

            //CAMPI to set the Log Channel
            if (m_cmapi->SetLogChannel(compoName, channel,&Resp) == CMAPI_SUCCESS)
            {
                cout << " Successfully Set Log Channel " << endl;
            } 
            else
                cout << " Error in Setting the Log Channel"<<endl;
        }

        void SetLogLevel()
        {

            string compoName;
            LoggerConf_LogLevel level;
            LoggerConfResp Resp;
            int option;
            cout << "Enter the Component Name " << endl;
            cin >> compoName;
            cout << " Choose the Preferred Log Level : " << endl;
            cout << " 1. CRITICAL_LOG " << endl;
            cout << " 2. ERROR_LOG " << endl;
            cout << " 3. WARNING_LOG " << endl;
            cout << " 4. NOTICE_LOG " << endl;
            cout << " 5. INFO_LOG " << endl;
            cout << " 6. DEBUG_LOG " << endl;
            cin >> option;
            switch(option)
            {
                case 1:
                    level = LoggerConf_LogLevel_CRITICAL_LOG;
                    break;
                case 2:
                    level = LoggerConf_LogLevel_ERROR_LOG;
                    break;
                case 3:
                    level = LoggerConf_LogLevel_WARNING_LOG;
                    break;
                case 4:
                    level = LoggerConf_LogLevel_NOTICE_LOG;
                    break;
                case 5:
                    level = LoggerConf_LogLevel_INFO_LOG;
                    break;
                case 6:
                    level = LoggerConf_LogLevel_DEBUG_LOG;
                    break;
                default :
                    cout << "Invalid Log Level" << endl;
                    break; 
            }
            cout << " Componenet Name : " << compoName << endl;
            cout << " Log Level     : " << level << endl;

            //CAMPI to set the Log Channel
            if (m_cmapi->SetLogLevel(compoName, level,&Resp) == CMAPI_SUCCESS)
            {
                cout << " Successfully Set Log Channel " << endl;
            } 
            else
                cout << " Error in setting Log Level " << endl; 
        }

#endif
        int Menu()
        {
            cout << "************ MENU ************" << endl;
#if 0
            cout << "1. Create Peer Group " << endl;
            cout << "2. Get Peer Group " << endl;
            cout << "3. Delete Peer Group " << endl;
            cout << "4. Add Peer          " << endl;
            cout << "5. Modify Peer       " << endl;
            cout << "6. Delete Peer       " << endl;
            cout << "7. Get Algorithms    " << endl;
            cout << "8. Add Algorithm    " << endl;
            cout << "9. Modify Algorithm    " << endl;
            cout << "10. Delete Algorithm    " << endl;
            cout << "11. Get ERPLBF PeerGroup Statistics    " << endl;
            cout << "12. Get Session Binding Statistics    " << endl;
            cout << "13. GetLoggingConfig  " << endl;
            cout << "14. SetLoggingConfig  " << endl;
            cout << "15. SetLoggChannel " << endl;
            cout << "16. SetLoggLevel " << endl;
#endif
            cout << "7. Get Algorithms    " << endl;
            cout << "8. Add Algorithm    " << endl;
            cout << "9. Modify Algorithm    " << endl;
            cout << "10. Delete Algorithm    " << endl;
            cout << "17. SetASFGroup " << endl;
            cout << "18. GetASFGroup " << endl;
            cout << "19. ModifyASFGroup " <<endl;
            cout << "20. SetASFTimeOut " <<endl;
            cout << "21. GetASFTimeOUt " <<endl;
            cout << "22. DelASFGroup " <<endl;
            cout << "23. SetSCTPConfiguration " <<endl;
            cout << "24. GetSCTPConfiguration " <<endl;
            cout << "25. SetGeneralConfig " <<endl;
            cout << "26. GetGeneralConfig " <<endl;
            cout << "27. AddCACRLConfiguration " <<endl;
            cout << "28. DeleteCACRLConfiguration" <<endl;
            cout << "29. ModifyCACRLConfiguration" <<endl;
            cout << "30. GetCACRLConfiguration" <<endl;
            cout << "31. GetTLSConfiguration" <<endl;
            cout << "32. SetTLSConfiguration" <<endl;
            cout << "33. GetTlsCipherCfg " <<endl;
            cout << "34. EnableTlsCipherSuite "<<endl;
            cout << "35. DisableTlsCipherSuite " <<endl;
            cout << "0. Exit           " << endl;
            cout << "Please Choose " << endl;

            int Ch;
            cin >> Ch;

            cout << "Choice Entered " << Ch << endl;
            return Ch;
        }

        void CallCMAPI(int ch)
        {
            switch (ch)
            {
               case 0:
                    exit(0);
                    break;
#if 0
                case 1:
                    CreatePeerGroups();
                    break;
                case 2:
                    GetPeerGroups();
                    break;
                case 3:
                    DeletePeerGroups();
                    break;
                case 4:
                    AddPeers();
                    break;
                case 5:
                    ModifyPeers();
                    break;
                case 6:
                    DeletePeers();
                    break;
#endif
                case 7:
                    GetAlgos();
                    break;
                case 8:
                    AddAlgo();
                    break;
                case 9:
                    ModAlgo();
                    break;
                case 10:
                    DelAlgo();
                    break;
#if 0
                case 11:
                    GetPeerGroupStats();
                    break;
                case 12:
                    GetSessionBindingStats();
                    break;
                case 13:
                    GetLoggingConfig();
                    break;
                case 14:
                    SetLoggingConfig();
                    break;
                case 15:
                    SetLogChannel();
                    break;
                case 16:
                    SetLogLevel();
                    break;
#endif
                case 17:
                    SetASFGroup();
                    break;
                case 18:
                    GetASFGroup();
                    break;
                case 19:
                    ModifyASFGroup();
                    break;
                case 20:
                    SetASFTimeout();
                    break;
                case 21:
                    GetASFTimeout();
                    break;
                case 22:
                    DelASFGroup();
                    break;
                case 23:
                    SetSCTPConfig();
                    break;
                case 24:
                    GetSCTPConfig();
                    break;
                case 25:
                    SetGeneralConfig();
                    break;
                case 26:
                    GetGeneralConfig();
                    break;
                case 27:
                    AddCACRLConfiguration();
                    break;
                case 28:
                    DeleteCACRLConfiguration();
                    break;
                case 29:
                    ModifyCACRLConfiguration();
                    break;
                case 30:
                    GetCACRLConfiguration();
                    break;
                case 31:
                    GetTLSConfiguration();
                    break;
                case 32:
                    SetTLSConfiguration();
                    break;
                case 33:
                    GetTlsCipherCfg();
                    break;
                case 34:
                    EnableTlsCipherSuite();
                    break;
                case 35:
                    DisableTlsCipherSuite();
                    break;
                default:
                    cout << "Invalid Choice " << endl;
                    break;
            }
        }

        void RunMain()
        {
            bool Done = false;
            int Choice = 0;
            while (!Done)
            {
                Choice = Menu();
                if (Choice == 0)
                    Done = true;
                else
                    CallCMAPI(Choice);
            }

        }

    public:
        ApiUser() {}
        ~ApiUser() {}

        void Run(void *arg)
        {
            Initialize();
            RunMain();
        }

    private:
        CMApiComponents *m_cmapi;
        CMAPIProdConfig *m_cmapiprod;

};

int main(int argc, char *argv[])
{

    ApiUser LibUser;
    Thread  LibTest("CMAPITest");
    int ComponentID = 0;


    if (argc >= 2)
    {

        if (strcmp(argv[1], "CLI") == 0)
        {
            ComponentID = COMP_CLI_PROC;
        } else if (strcmp(argv[1], "GUI") == 0)
        {
            ComponentID = COMP_WEBAGENT_PROC;
        }
    } else {
        cout << "Error Invoking TestAgent : " << endl;
        cout << "Usage : " << endl;
        cout << "TestAgent \"CLI\" or \"GUI\"" << endl;
        exit(0);
    }

    TestAgent *app = NULL;
    try
    {
        cout << "Starting CMAPI Test Thread" << endl;
        char *Args[]= { "TestAgent", "-i", "0", "-l", "7" };
        int  NumArgs = 5;
        app = new TestAgent(ComponentID);
        
        app->Init(NumArgs, Args);

        CLOG_NOTICE("Application initialized");
        LibTest.Start(&LibUser);
        MeSSComponent::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_DEBUG, true);
        app->Run();
    }
    catch(CmdParseException &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    }
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    CLOG_NOTICE("Application exiting");
    
    if (app) delete app;
        

    return 0;
}

/*
int main(int argc, char *argv[])
{

    ApiUser LibUser;
    Thread  LibTest("CMAPITest");
    cout << "Starting CMAPI Test Thread" << endl;

    TestAgent *app = NULL;
    try
    {
        app = new TestAgent();

        app->Init(argc, argv);
        LibTest.Start(&LibUser);

        CLOG_NOTICE("Application initialized");
        MeSSComponent::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_DEBUG, true);
        app->Run();
    }
    catch(CmdParseException &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    }
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    CLOG_NOTICE("Application exiting");

    if (app) delete app;


    return 0;
}

*/
