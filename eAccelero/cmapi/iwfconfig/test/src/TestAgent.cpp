#include "MeSSComponent.h"
#include "ComponentDefines.h"
#include <iostream>
#include "Compo_def.h"
#include "PeerStats_def.h"

#include "TestAgent.h"
#include "CMAPILib.h"
#include "ThreadQueue.h"
#include "Thread.h"

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

class ApiLibUser: public Runnable
{
    private:

        void Initialize()
        {
            CMApiLibObj = new  CMAPIProdConfig();
            CMApiLibObj->InitializeLibrary();
        }

	int  GetLocalHostConfig(void)
	{
		cout << "In Agent GetLocalHostConfig " << endl;
		if ( CMApiLibObj == NULL )
		{
			cout << "CMAPILIB Obj not created " << endl;
		}
		else
		{
			cout << " Calling Library " << endl;
			LocalHostConfig lHost;
            ErrorDetails err;
			if ( CMApiLibObj->GetLocalHostConfig(lHost,err) == CMAPI_SUCCESS)
			{
				cout << "LOCAL HOST INFO : " << endl;
				cout << "  Host Name     :  " << lHost.localhostname() << endl;
				cout << "  Realm Name    :  " << lHost.realmname() << endl;
                cout << "  IP Address    :  " << lHost.hostipaddr() << endl;
                cout << "  Port          :  " << lHost.port() << endl;
                cout << "  Transport Type:  " << lHost.transporttype() << endl;
				cout << "  AUTH TIMEOUT  :  " << lHost.authsessiontimeout() << endl;
				cout << "  AUTH GRACETO  :  " << lHost.authsessiongraceperiod() << endl;
				cout << "  AUTH LIFETO   :  " << lHost.authsessionlifetime() << endl;
				cout << "  ACCT INTERIM  :  " << lHost.acctsessioninteriminterval() << endl;
				cout << "  ACCT REALTO   :  " << lHost.acctsessionrealtime() << endl;
				cout << "  ACCT TIMEOUT  :  " << lHost.acctsessiontimeout() << endl;
                cout << "  Mate Host     :  " << lHost.matehostname() << endl;
				cout << "CMAPI Return SUCCESS" << endl;
			}
			else
				cout << "CMAPI FAILED" << endl;
		}

		return 0;
	}

	int GetPeerInfo()
	{
		string peer;
		string realm;
		cout << "\n\n **** Enter Peer Name "; cin >> peer;
		cout << "**** Enter realm Name "; cin >> realm;

		cout << "Requesting Info for " << peer << " and " << realm << endl;
		PeerConfig Peers;
        ErrorDetails err;
		if ( CMApiLibObj->GetPeerConfig(peer, realm, Peers,err) == CMAPI_SUCCESS)
		{
			PeerConfig *PC = &Peers;
			cout << "*********PEERINFO*************" << endl;
			cout << "PeerName       : " << PC->peerhostname() << endl;
			cout << "Peer ID        : " << PC->peerid() << endl;
			cout << "Realm          : " << PC->realm() << endl;
			cout << "TlsEnabled     : " << PC->tlsenabled() << endl;
			cout << "TransportType  : " << PC->transporttype() << endl;
			cout << "IPAddr         : " << PC->serveripaddr() << endl;
			cout << "Port           : " << PC->port() << endl;
			cout << "FailoverEnable : " << PC->failoverenable() << endl;
			cout << "FailebackEnable: " << PC->failebackenable() << endl;
			cout << "AltPeerName    : " << PC->altpeername() << endl;
			cout << "IsMate         : " << PC->ismate() << endl;
			cout << "TcTimerVal     : " << PC->tctimerval() << endl;
			cout << "WatchDogTimer  : " << PC->watchdogtimer() << endl;
			cout << "ExpiryTimer    : " << PC->expirytimer() << endl;
            cout << "PeerStatus     : " << PC->peerstatus() << endl;
            cout << "Dictionaries   :  ";
            for(int i = 0; i < PC->dictionaryname_size();i++)
                cout << PC->dictionaryname(i) << ", " << endl;

			cout << "CMAPI Return SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int  SetAuthTimers()
	{
		int Lt, Rt, Tt;
        DRECfgResp *resp = NULL;
		cout << "\n\n **** Enter LifeTime" << endl; cin >> Lt;
		cout << "**** Enter GraceTime" << endl; cin >> Rt;
		cout << "**** Enter Timeout" << endl; cin >> Tt;
		cout << "Requesting to Set Auth Timers" << endl;
		if(CMApiLibObj->SetLocalHostAuthTimers(Lt, Rt,Tt,resp) == CMAPI_SUCCESS) 
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}

		return 0;
	}


	int SetLocalHost()
	{
		LocalHostConfig lHost;
        DRECfgResp *resp = NULL;
		string InputVal; int TimVal;
		cout << "Enter Host Name : "; cin >> InputVal; lHost.set_localhostname(InputVal);
		cout << "Enter Realm Name : "; cin >> InputVal; lHost.set_realmname(InputVal);
        cin.ignore(256, '\n');
		//cout << "Enter Mate Name "  << endl; cin >> InputVal; lHost.set_matehostname(InputVal);
		cout << "Enter Mate Name (blank to ignore): "; getline(cin,InputVal); if (!InputVal.empty()) lHost.set_matehostname(InputVal);
		cout << "Enter transport Type (blank to ignore): ";  getline(cin,InputVal); if (!InputVal.empty()) lHost.set_transporttype(InputVal);
        cout << "Enter Port (-1 to ignore) : ";  cin >> TimVal; if (TimVal != -1) lHost.set_port(TimVal);
		cout << "Enter Auth Timeout (-1 to ignore) : ";  cin >> TimVal; if (TimVal != -1)  lHost.set_authsessiontimeout(TimVal);
		cout << "Enter Auth LifeTime (-1 to ignore) : " ;  cin >> TimVal; if (TimVal != -1) lHost.set_authsessionlifetime(TimVal);
		cout << "Enter Auth Grace : (-1 to ignore) "; cin >> TimVal; if (TimVal != -1) lHost.set_authsessiongraceperiod(TimVal);
		cout << "Enter Acct Interim : (-1 to ignore) " ; cin >> TimVal; if (TimVal != -1) lHost.set_acctsessioninteriminterval(TimVal);
		cout << "Enter Acct Timeout : (-1 to ignore) "; cin >> TimVal; if (TimVal != -1) lHost.set_acctsessiontimeout(TimVal);
		cout << "Enter IP Address (blank to ignore): "; getline(cin,InputVal); if (!InputVal.empty()) lHost.set_hostipaddr(InputVal);

		if(CMApiLibObj->SetLocalHostConfig(lHost,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}


	int ModLocalHost()
	{
		LocalHostConfig lHost;
        DRECfgResp *resp = NULL;
		string InputVal; int TimVal;
		cout << "Enter Host Name : "; cin >> InputVal; lHost.set_localhostname(InputVal);
        cout << "Enter Realm Name: "; cin >> InputVal; lHost.set_realmname(InputVal);
		cin.ignore(256, '\n');
		cout << "Enter Mate Name (blank to ignore): "; getline(cin,InputVal); if (!InputVal.empty()) lHost.set_matehostname(InputVal);
		cout << "Enter transport Type (blank to ignore): ";  getline(cin,InputVal); if (!InputVal.empty()) lHost.set_transporttype(InputVal);
        cout << "Enter Port (-1 to ignore) : ";  cin >> TimVal; if (TimVal != -1) lHost.set_port(TimVal);
		cout << "Enter Auth Timeout (-1 to ignore) : ";  cin >> TimVal; if (TimVal != -1)  lHost.set_authsessiontimeout(TimVal);
		cout << "Enter Auth LifeTime (-1 to ignore) : " ;  cin >> TimVal; if (TimVal != -1) lHost.set_authsessionlifetime(TimVal);
		cout << "Enter Auth Grace : (-1 to ignore) "; cin >> TimVal; if (TimVal != -1) lHost.set_authsessiongraceperiod(TimVal);
		cout << "Enter Acct Interim : (-1 to ignore) " ; cin >> TimVal; if (TimVal != -1) lHost.set_acctsessioninteriminterval(TimVal);
		cout << "Enter Acct Timeout : (-1 to ignore) "; cin >> TimVal; if (TimVal != -1) lHost.set_acctsessiontimeout(TimVal);
		cout << "Enter IP Address (blank to ignore): "; getline(cin,InputVal); if (!InputVal.empty()) lHost.set_hostipaddr(InputVal);

		if(CMApiLibObj->ModifyLocalHostConfig(lHost,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}


	int SetAcctTimers()
	{
		int Lt, Rt, Tt;
        DRECfgResp *resp = NULL;
		cout << "\n\n **** Enter Interim : "; cin >> Lt;
		cout << "**** Enter RealTime : "; cin >> Rt;
		cout << "**** Enter Timeout : "; cin >> Tt;
		cout << "Requesting to Set Acct Timers" << endl;
		if(CMApiLibObj->SetLocalHostAcctTimers(Lt, Rt,Tt, resp) == CMAPI_SUCCESS) 
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int SetHostIPAddr()
	{
		string InputVal;
        DRECfgResp *resp = NULL;
		cout << "Enter IP Address : "; cin >> InputVal; 
		if(CMApiLibObj->SetLocalHostIPAddr(InputVal,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int GetRealm()
	{
		string InputVal;
        ErrorDetails err;
		cout << "Enter Realm Name : "; cin >> InputVal; 
		RealmConfig Realms;
		if(CMApiLibObj->GetRealm(InputVal,Realms,err) == CMAPI_SUCCESS)
		{
			RealmConfig *RC = &Realms;
			cout << "\n******** REALM INFO **************" << endl;
			cout << "RealmName          : " << RC->realmname() << endl;
			cout << "LocalAction        : " << RC->localaction() << endl;
			cout << "EnableProxyInfoAVP : " << RC->enableproxyinfoavp() << endl;
			cout << "RedirectHostUsage  : " << RC->redirecthostusage() << endl;
			cout << "RedirectMaxCacheTime : " << RC->redirectmaxcachetime() << endl;
			int Dests = RC->destinfo_size();
			for (int Dest = 0; Dest < Dests; Dest++)
			{
				Destination *DT = RC->mutable_destinfo(Dest);
				cout << "     ****** Destination ***** " << endl;
				cout << "PeerName       : " << DT->peername() << endl;
                cout << "Peer Realm     : " << DT->realmname() << endl;
				cout << "PeerID         : " << DT->peerid() << endl;
				cout << "Application ID : " << DT->applicationid() << endl;
				cout << "VendorID       : " << DT->vendorid() << endl;
				cout << "Priority       : " << DT->priority() << endl;
			}
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}

		return 0;
	}

	int GetAllRealms()
	{
		RealmsConfig Realms;
        ErrorDetails err;
		if(CMApiLibObj->GetAllRealms(Realms,err) == CMAPI_SUCCESS)
		{
			int NRealms = Realms.realms_size();
			for (int i = 0; i < NRealms; i++)
			{
				RealmConfig *RC = Realms.mutable_realms(i);
				cout << "\n******** REALM INFO **************" << endl;
				cout << "RealmName          : " << RC->realmname() << endl;
				cout << "LocalAction        : " << RC->localaction() << endl;
				cout << "EnableProxyInfoAVP : " << RC->enableproxyinfoavp() << endl;
				cout << "RedirectHostUsage  : " << RC->redirecthostusage() << endl;
				cout << "RedirectMaxCacheTime : " << RC->redirectmaxcachetime() << endl;
				int Dests = RC->destinfo_size();
				for (int Dest = 0; Dest < Dests; Dest++)
				{
					Destination *DT = RC->mutable_destinfo(Dest);
					cout << "     ****** Destination ***** " << endl;
					cout << "PeerName       : " << DT->peername() << endl;
					cout << "PeerID         : " << DT->peerid() << endl;
                    cout << "Peer Realm     : " << DT->realmname() << endl;
					cout << "Application ID : " << DT->applicationid() << endl;
					cout << "VendorID       : " << DT->vendorid() << endl;
					cout << "Priority       : " << DT->priority() << endl;
				}
			}
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int SetRealm()
	{
		RealmsConfig RSC;
		RealmConfig  *RC = RSC.add_realms();
        DRECfgResp *resp = NULL;
		string InputVal; int iVal;
		cout << "Enter Realm : "; cin >> InputVal; RC->set_realmname(InputVal);
        cin.ignore(256, '\n');
		cout << "Enter Action (blank to ignore) : "; getline(cin, InputVal); if (!InputVal.empty()) RC->set_localaction(InputVal);
		cout << "Enable ProxyAVP (-1 to ignore) : "; cin >> iVal; if (iVal != -1) ((iVal==1)?RC->set_enableproxyinfoavp(true):RC->set_enableproxyinfoavp(false));
		cout << "Enter Redirectmaxcachetime (-1 to ignore) : "; cin >> iVal; if (iVal != -1) RC->set_redirectmaxcachetime(iVal);
		cout << "Redirecthostusage (-1 to ignore) : "; cin >> iVal; if (iVal != -1) RC->set_redirecthostusage(iVal);
		while (1)
		{
			cout << " Want to Add Destination : 1 / 0 "; cin >> iVal;
			if (iVal == 0) break;
			Destination *Dt = RC->add_destinfo();
			cout << "Enter Peer Name : "; cin >> InputVal; Dt->set_peername(InputVal);
            cout << "Enter Peer Realm : " ; cin >> InputVal; Dt->set_realmname(InputVal);
			cout << "Enter App ID    : "; cin >> iVal; Dt->set_applicationid(iVal);
			cout << "Enter Vendor ID : "; cin >> iVal; Dt->set_vendorid(iVal);
			cout << "Enter Priority  (-1 to ignore) : "; cin >> iVal; if (iVal != -1) Dt->set_priority(iVal);
		}

		if(CMApiLibObj->SetRealm(RSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int ModRealm()
	{
		RealmsConfig RSC;
		RealmConfig  *RC = RSC.add_realms();
		string InputVal; int iVal;
        DRECfgResp *resp = NULL;
	
		cout << "Enter Realm : "; cin >> InputVal; RC->set_realmname(InputVal);
        cin.ignore(256, '\n');
		cout << "Enter Action (blank to ignore) : "; getline(cin, InputVal); if (!InputVal.empty()) RC->set_localaction(InputVal);
		cout << "Enable ProxyAVP (-1 to ignore) : "; cin >> iVal; if (iVal != -1) ((iVal==1)?RC->set_enableproxyinfoavp(true):RC->set_enableproxyinfoavp(false));
		cout << "Enter Redirectmaxcachetime (-1 to ignore) : "; cin >> iVal; if (iVal != -1) RC->set_redirectmaxcachetime(iVal);
		cout << "Redirecthostusage (-1 to ignore) : "; cin >> iVal; if (iVal != -1) RC->set_redirecthostusage(iVal);
		while (1)
		{
			cout << " Want to Modify Destination (Only Priority can be modified): 1 / 0 "; cin >> iVal;
			if (iVal == 0) break;
			Destination *Dt = RC->add_destinfo();
			cout << "Enter Peer Name : "; cin >> InputVal; Dt->set_peername(InputVal);
            cout << "Enter Peer Realm : " ; cin >> InputVal; Dt->set_realmname(InputVal);
			cout << "Enter App ID    : "; cin >> iVal; Dt->set_applicationid(iVal);
			cout << "Enter Vendor ID : "; cin >> iVal; Dt->set_vendorid(iVal);
			cout << "Enter Priority  (-1 to ignore) : "; cin >> iVal; if (iVal != -1) Dt->set_priority(iVal);
        }

		if(CMApiLibObj->ModifyRealm(RSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
    }

	int ModifyDestination()
	{
		RealmsConfig RSC;
		RealmConfig  *RC = RSC.add_realms();
		string InputVal; int iVal;
        DRECfgResp *resp = NULL;
	
		cout << "Enter Realm : "; cin >> InputVal; RC->set_realmname(InputVal);
        cin.ignore(256, '\n');
		while (1)
		{
			cout << " Want to Modify Realm Route (Only Priority can be modified): 1 / 0 "; cin >> iVal;
			if (iVal == 0) break;
			Destination *Dt = RC->add_destinfo();
			cout << "Enter Peer Name : "; cin >> InputVal; Dt->set_peername(InputVal);
            cout << "Enter Peer Realm : " ; cin >> InputVal; Dt->set_realmname(InputVal);
			cout << "Enter App ID    : "; cin >> iVal; Dt->set_applicationid(iVal);
			cout << "Enter Vendor ID : "; cin >> iVal; Dt->set_vendorid(iVal);
			cout << "Enter Priority  : "; cin >> iVal; Dt->set_priority(iVal);
        }

		if(CMApiLibObj->ModifyDestination(RSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
    }
    

	int DeleteDestination()
	{
		RealmsConfig RSC;
		RealmConfig  *RC = RSC.add_realms();
		string InputVal; int iVal;
        DRECfgResp *resp = NULL;
		cout << "Enter Realm : "; cin >> InputVal; RC->set_realmname(InputVal);
		while (1)
		{
			cout << " Want to Delete Destination : 1 / 0 "; cin >> iVal;
			if (iVal == 0) break;
			Destination *Dt = RC->add_destinfo();
			cout << "Enter Peer Name : "; cin >> InputVal; Dt->set_peername(InputVal);
            cout << "Enter Peer Realm: "; cin >> InputVal; Dt->set_realmname(InputVal);
			cout << "Enter App ID    : "; cin >> iVal; Dt->set_applicationid(iVal);
            cout << "Enter Vendor ID : "; cin >> iVal; Dt->set_vendorid(iVal);
		}

		if(CMApiLibObj->DeleteDestination(RSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
 
	}



	int DeleteRealm()
	{
		string InputVal;
        DRECfgResp *resp = NULL;
		cout << "Enter Realm Name : "; cin >> InputVal; 

		if(CMApiLibObj->DeleteRealm(InputVal,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

    int GetUniqueRealms()
    {
        string InputVal;
        RealmsConfig Realms;
        ErrorDetails err;

        if(CMApiLibObj->GetUniqueRealmsOfPeer(Realms,err) == CMAPI_SUCCESS)
        {
            int NumRealms = Realms.realms_size();
            for (int i=0; i<NumRealms;i++)
            {
                cout << "Realm: " << (Realms.realms(i)).realmname() << endl;
            }
            cout << "CMAPI SUCCESS" << endl;
        }
        else
        {
            cout << "CMAPI FAILED" << endl;
        }
        return 0;
    }

	int DeleteDefRoute()
	{
        DRECfgResp *resp = NULL;
		if(CMApiLibObj->DeleteDefaultRoute(resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}



	int SetDefaultRoute()
	{
		string Host, Realm;
        DRECfgResp *resp = NULL;
		cout << "Enter Host Name  : "; cin >> Host;             
		cout << "Enter Realm Name : "; cin >> Realm;             
		if(CMApiLibObj->SetDefaultRoute(Host, Realm,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}


	int GetDefaultRoute()
	{

		RealmConfig Realm;
        ErrorDetails err;
		if(CMApiLibObj->GetDefaultRoute(Realm,err) == CMAPI_SUCCESS)
		{
			RealmConfig *RC = &Realm;
			if (RC->destinfo_size() > 0)
			{
				Destination *DT = RC->mutable_destinfo(0);
			    cout << "\n******** DEFAULT ROUTE **************" << endl;
			    cout << "RealmName      : " << RC->realmname() << endl;
				cout << "PeerName       : " << DT->peername() << endl;
			    cout << "CMAPI SUCCESS" << endl;
			} else {
                cout << "ERROR: No Default route available" << endl;
            }
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;

	}

	int SetDest()
	{
		RealmsConfig RSC;
		RealmConfig  *RC = RSC.add_realms();
		string InputVal; int iVal;
        DRECfgResp *resp = NULL;
        cout << "Enter Realm     : "; cin >> InputVal; RC->set_realmname(InputVal);
		while (1)
		{
			Destination *Dt = RC->add_destinfo();
			cout << "Enter Peer Name : "; cin >> InputVal; Dt->set_peername(InputVal);
			cout << "Enter Peer Realm: "; cin >> InputVal; Dt->set_realmname(InputVal);
			cout << "Enter App ID    : "; cin >> iVal; Dt->set_applicationid(iVal);
			cout << "Enter Vendor ID : "; cin >> iVal; Dt->set_vendorid(iVal);
			cout << "Enter Priority  : "; cin >> iVal; Dt->set_priority(iVal);
			cout << " Want to ADD more Destinations : 1 / 0 "; cin >> iVal;
			if (iVal == 0) break;
		}
		if(CMApiLibObj->SetDestination(RSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int EnableProxy()
	{
		string Realm;
        DRECfgResp *resp = NULL;
		cout << "Enter Realm Name  : "; cin >> Realm;   
		if(CMApiLibObj->EnableProxyInfoAvp(Realm,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int DisableProxy()
	{
		string Realm;
        DRECfgResp *resp = NULL;
		cout << "Enter Realm Name  : "; cin >> Realm;    
		if(CMApiLibObj->DisableProxyInfoAvp(Realm,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;                
	}

    int GetAllPeers()
    {
        PeersConfig Peers;
        ErrorDetails err;
        if(CMApiLibObj->GetAllPeers(Peers,err) == CMAPI_SUCCESS)
        {
            int NPeers = Peers.peers_size();
            if (NPeers > 0)
            {
                cout << "*********PEERINFO*************\n" << endl;
                for (int i = 0; i < NPeers; i++) 
                {
                    PeerConfig *PC = Peers.mutable_peers(i);
                    cout << "PeerName       : " << PC->peerhostname() << endl;
                    cout << "Peer ID        : " << PC->peerid() << endl;
                    cout << "Realm          : " << PC->realm() << endl;
                    cout << "TlsEnabled     : " << PC->tlsenabled() << endl;
                    cout << "TransportType  : " << PC->transporttype() << endl;
                    cout << "IPAddr         : " << PC->serveripaddr() << endl;
                    cout << "Port           : " << PC->port() << endl;
                    cout << "FailoverEnable : " << PC->failoverenable() << endl;
                    cout << "FailebackEnable: " << PC->failebackenable() << endl;
                    cout << "AltPeerName    : " << PC->altpeername() << endl;
                    cout << "IsMate         : " << PC->ismate() << endl;
                    cout << "TcTimerVal     : " << PC->tctimerval() << endl;
                    cout << "WatchDogTimer  : " << PC->watchdogtimer() << endl;
                    cout << "ExpiryTimer    : " << PC->expirytimer() << endl;
                    cout << "PeerStatus     : " << PC->peerstatus() << endl;
                    cout << "Dictionaries   :  ";
                    for(int i = 0; i < PC->dictionaryname_size();i++)
                        cout << PC->dictionaryname(i) << ", " << endl;
                }
                cout << "CMAPI SUCCESS" << endl;
            }
            else
            {
                cout << "CMAPI FAILED" << endl;
            }
        }
        return 0;
    }

	int GetAllPeersofRealm()
	{
		string Realm;
		cout << "Enter Realm Name "; cin >> Realm;     
		PeersConfig Peers;
        ErrorDetails err;
		if(CMApiLibObj->GetAllPeersofRealm(Realm,Peers,err) == CMAPI_SUCCESS)
		{
	        int NPeers = Peers.peers_size();
            if (NPeers > 0)
            {
                cout << "*********PEERINFO*************\n" << endl;
                for (int i = 0; i < NPeers; i++) 
                {
                    PeerConfig *PC = Peers.mutable_peers(i);
                    cout << "PeerName       : " << PC->peerhostname() << endl;
                    cout << "Peer ID        : " << PC->peerid() << endl;
                    cout << "Realm          : " << PC->realm() << endl;
                    cout << "TlsEnabled     : " << PC->tlsenabled() << endl;
                    cout << "TransportType  : " << PC->transporttype() << endl;
                    cout << "IPAddr         : " << PC->serveripaddr() << endl;
                    cout << "Port           : " << PC->port() << endl;
                    cout << "FailoverEnable : " << PC->failoverenable() << endl;
                    cout << "FailebackEnable: " << PC->failebackenable() << endl;
                    cout << "AltPeerName    : " << PC->altpeername() << endl;
                    cout << "IsMate         : " << PC->ismate() << endl;
                    cout << "TcTimerVal     : " << PC->tctimerval() << endl;
                    cout << "WatchDogTimer  : " << PC->watchdogtimer() << endl;
                    cout << "ExpiryTimer    : " << PC->expirytimer() << endl;
                    cout << "PeerStatus     : " << PC->peerstatus() << endl;
                    cout << "Dictionaries   :  ";
                    for(int i = 0; i < PC->dictionaryname_size();i++)
                        cout << PC->dictionaryname(i) << ", " << endl;
                }
		    }
            cout << "CMAPI SUCCESS" << endl;
        }
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;   
	}

	int SetPeerConfig()
	{
		PeersConfig PSC;
		PeerConfig *PC = PSC.add_peers();
        DRECfgResp *resp = NULL;
		string InputVal; int iVal;
		cout << "Enter PeerName : " ; cin >> InputVal; PC->set_peerhostname(InputVal);
		cout << "Enter Realm    : " ; cin >> InputVal; PC->set_realm(InputVal);
        cin.ignore(256,'\n');
		cout << "Enable TLS 1 / 0 (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_tlsenabled(true):PC->set_tlsenabled(false);}
		cout << "Transport Type SCTP / TCP  (blank to ignore) "; getline(cin , InputVal); if (!InputVal.empty()) PC->set_transporttype(InputVal);
		cout << "IP Address (blank to ignore)   : "; getline(cin , InputVal); if (!InputVal.empty())  PC->set_serveripaddr(InputVal);
		cout << "Port Num  (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) PC->set_port(iVal);
		cout << "Enable FailBack 1 / 0 (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_failebackenable(true):PC->set_failebackenable(false); }
		cout << "Enable FailOver 1 / 0 (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_failoverenable(true):PC->set_failoverenable(false); }
		cout << "Alternate Peer (blank to ignore) : " ; getline(cin , InputVal); if (!InputVal.empty()) PC->set_altpeername(InputVal);
		cout << "Is Mate 1 / 0 (-1 to ignore) : "; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_ismate(true):PC->set_ismate(false); }
		cout << "TC Timer  (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) PC->set_tctimerval(iVal);
		cout << "WatchDog Timer (-1 to ignore) : "; cin >> iVal; if (iVal != -1) PC->set_watchdogtimer(iVal);
		cout << "Expiry Time (-1 to ignore) : "; cin >> iVal; if (iVal != -1) PC->set_expirytimer(iVal);
        cout << "Peer Status (-1 to ignore) : "; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_peerstatus(true):PC->set_peerstatus(false); }
        cout << "Dictionary Names (blank to ignore) : "; getline(cin,InputVal);
        if (!InputVal.empty())
        {
            while (1) {
                cout << "Enter Dictionary Name (blank to ignore) : "; getline(cin , InputVal);
                if (!InputVal.empty()) PC->add_dictionaryname((const string) InputVal);
            }
        }

		if(CMApiLibObj->SetPeerConfig(PSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

	int ModifyPeerConfig()
	{
		PeersConfig PSC;
		PeerConfig *PC = PSC.add_peers();
		string InputVal; int iVal;
        DRECfgResp *resp = NULL;

		cout << "Enter PeerName : " ; cin >> InputVal; PC->set_peerhostname(InputVal);
		cout << "Enter Realm    : " ; cin >> InputVal; PC->set_realm(InputVal);
        cin.ignore(256,'\n');
		cout << "Enable TLS 1 / 0 (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_tlsenabled(true):PC->set_tlsenabled(false);}
		cout << "Transport Type SCTP / TCP  (blank to ignore) "; getline(cin , InputVal); if (!InputVal.empty()) PC->set_transporttype(InputVal);
		cout << "IP Address (blank to ignore)   : "; getline(cin , InputVal); if (!InputVal.empty())  PC->set_serveripaddr(InputVal);
		cout << "Port Num  (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) PC->set_port(iVal);
		cout << "Enable FailBack 1 / 0 (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_failebackenable(true):PC->set_failebackenable(false); }
		cout << "Enable FailOver 1 / 0 (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_failoverenable(true):PC->set_failoverenable(false); }
		cout << "Alternate Peer (blank to ignore) : " ; getline(cin , InputVal); if (!InputVal.empty()) PC->set_altpeername(InputVal);
		cout << "Is Mate 1 / 0 (-1 to ignore) : "; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_ismate(true):PC->set_ismate(false); }
		cout << "TC Timer  (-1 to ignore) : " ; cin >> iVal; if (iVal != -1) PC->set_tctimerval(iVal);
		cout << "WatchDog Timer (-1 to ignore) : "; cin >> iVal; if (iVal != -1) PC->set_watchdogtimer(iVal);
		cout << "Expiry Time (-1 to ignore) : "; cin >> iVal; if (iVal != -1) PC->set_expirytimer(iVal);
        cout << "Peer Status (-1 to ignore) : "; cin >> iVal; if (iVal != -1) { (iVal==1)?PC->set_peerstatus(true):PC->set_peerstatus(false); }
        cout << "Dictionary Names (blank to ignore) : "; getline(cin,InputVal);
        if (!InputVal.empty())
        {
            while (1) {
                cout << "Enter Dictionary Name (blank to ignore) : "; getline(cin , InputVal);
                if (!InputVal.empty()) PC->add_dictionaryname((const string) InputVal);
            }
        }


		if(CMApiLibObj->ModifyPeerConfig(PSC,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;
	}

    int AddDictID()
    {
		PeersConfig PSC;
		PeerConfig *PC = PSC.add_peers();
		string InputVal; 
        DRECfgResp *resp;

		cout << "Enter PeerName : " ; cin >> InputVal; PC->set_peerhostname(InputVal);
		cout << "Enter Realm    : " ; cin >> InputVal; PC->set_realm(InputVal);
        cin.ignore(256, '\n');
        while (1) {
             cout << "Enter Dictionary Name (blank to ignore) : "; getline(cin , InputVal);
             if (!InputVal.empty()) PC->add_dictionaryname((const string) InputVal);
        }
 
        if(CMApiLibObj->AddDictionaryID(PSC,resp)  == CMAPI_SUCCESS)
        {
            cout << "CMAPI SUCCESS" << endl;
        }
        else
        {
            cout << "CMAPI FAILED" << endl;
        }

        return 0;
    }

    int DelDictID()
    {
		PeersConfig PSC;
		PeerConfig *PC = PSC.add_peers();
		string InputVal; 

        DRECfgResp *resp;
		cout << "Enter PeerName : " ; cin >> InputVal; PC->set_peerhostname(InputVal);
		cout << "Enter Realm    : " ; cin >> InputVal; PC->set_realm(InputVal);
        cin.ignore(256, '\n');
        while (1) {
             cout << "Enter Dictionary Name (blank to ignore) : "; getline(cin , InputVal);
             if (!InputVal.empty()) PC->add_dictionaryname((const string) InputVal);
        }
 
        if(CMApiLibObj->DeleteDictionaryID(PSC,resp)  == CMAPI_SUCCESS)
        {
            cout << "CMAPI SUCCESS" << endl;
        }
        else
        {
            cout << "CMAPI FAILED" << endl;
        }

        return 0;
    }

	int RemovePeerConfig()
	{
		string Peer;
		string Realm;
        DRECfgResp *resp = NULL;
		cout << "Enter Peer Name  : "; cin >> Peer;     
		cout << "Enter Realm Name : "; cin >> Realm;     
		if(CMApiLibObj->RemovePeerConfig(Peer, Realm,resp) == CMAPI_SUCCESS)
		{
			cout << "CMAPI SUCCESS" << endl;
		}
		else
		{
			cout << "CMAPI FAILED" << endl;
		}
		return 0;   

	}
    
    int GetPeerGeneralStats()
    {

        PeerGeneralStatsReq req;
        PeerGeneralStatsResp resp;
        PeerGeneralStats peerGeneralStats; 
        int retVal;
        string input;
        char name[50];
        char realm[50];

        do
        {
            cout << "Enter the Peer Name : " << endl;
            cin >> name;
            req.add_peername(name);
            cout << "Enter the Realm : " << endl;
            cin >> realm;
            req.add_realm(realm);
            cout << " Do you want to enter another Peer Name(y/n) : " << endl;
            cin >> input ;
        }while((input.compare("n")) != 0);
        
        if ((retVal = CMApiLibObj->GetPeerGeneralStats(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::GetGeneralStats success " << endl;
            int numOfPeers = resp.genstats_size();

            for(int i = 0; i < numOfPeers ; i++)
            {
                peerGeneralStats = resp.genstats(i);

                cout << " Peer General Statistics " << endl;
                cout << "========================================" << endl;
                cout << " Peer Name                    : " << peerGeneralStats.peername() << endl;
                cout << " Total request  Msgs sent     : " << peerGeneralStats.totalreqout() << endl;
                cout << " Total request  Msgs received : " << peerGeneralStats.totalreqin() << endl;
                cout << " Total response Msgs sent     : " << peerGeneralStats.totalansout() << endl;
                cout << " Total response Msgs received : " << peerGeneralStats.totalansin() << endl;
                cout << " Total CER sent               : " << peerGeneralStats.cerout() << endl;
                cout << " Total CER received           : " << peerGeneralStats.cerin() << endl; 
                cout << " Total CEA sent               : " << peerGeneralStats.ceaout() << endl;
                cout << " Total CEA received           : " << peerGeneralStats.ceain() << endl;
                cout << " Total DWR sent               : " << peerGeneralStats.dwrout() << endl;
                cout << " Total DWR received           : " << peerGeneralStats.dwrin() << endl;
                cout << " Total DWA sent               : " << peerGeneralStats.dwaout() << endl;
                cout << " Total DWA received           : " << peerGeneralStats.dwain() << endl;
                cout << " Total DPR sent               : " << peerGeneralStats.dprout() << endl;
                cout << " Total DPR received           : " << peerGeneralStats.dprin() << endl;
                cout << " Total DPA sent               : " << peerGeneralStats.dpaout() << endl;
                cout << " Total DPA received           : " << peerGeneralStats.dpain() << endl;
                cout << " Total Msgs retransmitted     : " << peerGeneralStats.totalmsgsretransmitted() << endl;

            }
        }
        else
        {
            cout << "CMAPILib::GetGeneralStats failed " << endl;
        }
    return 0;

    }


    int GetPeerTransportStats()
    {

        PeerTransportStatsReq req;
        PeerTransportStatsResp resp;
        PeerTransportStats peerTransportStats; 
        int retVal;
        string input;
        char name[50];
        char realm[50];

        do
        {
            cout << "Enter the Peer Name : " << endl;
            cin >> name;
            req.add_peername(name);
            cout << "Enter the Realm : " << endl;
            cin >> realm;
            req.add_realm(realm);
            cout << " Do you want to enter another Peer Name(y/n) : " << endl;
            cin >> input ;
        }while((input.compare("n")) != 0);
        
        if ((retVal = CMApiLibObj->GetPeerTransportStats(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::GetTransportStats success " << endl;
            int numOfPeers = resp.transportstats_size();

            for(int i = 0; i < numOfPeers ; i++)
            {
                peerTransportStats = resp.transportstats(i);

                cout << " Peer Transport Statistics " << endl;
                cout << "========================================" << endl;
                cout << " Peer Name                       : " << peerTransportStats.peername() << endl;
                cout << " Total Connection Attempts       : " << peerTransportStats.connectionattempts() << endl;
                cout << " Total Connection Success        : " << peerTransportStats.totalconnectionsuccess() << endl;
                cout << " Total Connection Failed         : " << peerTransportStats.totalconnectionfailed() << endl;
                cout << " Total Connection Closed by Peer : " << peerTransportStats.totalconnectionclosurebypeer() << endl;
                cout << " Total Connection Closed by DRE  : " << peerTransportStats.totalconnectionclosurebydre() << endl;
                cout << " Total Socket Bind Success       : " << peerTransportStats.socketbindssuccess() << endl; 
                cout << " Total Socket Bind Failed        : " << peerTransportStats.socketbindsfailed() << endl;
                cout << " Total Transport Down            : " << peerTransportStats.totaltranportdown() << endl;
            }
        }
        else
        {
            cout << "CMAPILib::GetTransportStats failed " << endl;
        }
    return 0;

    }


    int SetPeerStatus()
    {
		PeersConfig PSC;
		PeerConfig *PC = PSC.add_peers();
		string InputVal; int iVal; 
        DRECfgResp *resp = NULL;

        cout << "Enter PeerName : " ; cin >> InputVal; PC->set_peerhostname(InputVal);
        cout << "Enter Realm    : " ; cin >> InputVal; PC->set_realm(InputVal);
        cout << "Enable : 1 / 0 :"  ; cin >> iVal;
        if (iVal == 1)
            PC->set_peerstatus(true);
        else
            PC->set_peerstatus(false);


        if(CMApiLibObj->SetPeerStatus(PSC,resp)  == CMAPI_SUCCESS)
        {
            cout << "CMAPI SUCCESS" << endl;
        }
        else
        {
            cout << "CMAPI FAILED" << endl;
        }
    return 0;
 
    }

    int GetPeerErrorStats()
    {

        PeerDREProtocolErrorStatsReq req;
        PeerDREProtocolErrorStatsResp resp;
        PeerDREProtocolErrorStats peerErrorStats;
        int retVal;
        string input;
        char name[50];
        char realm[50];
        do
        {
            cout << "Enter the Peer Name : " << endl;
            cin >> name;
            req.add_peername(name);
            cout << "Enter the Realm : " << endl;
            cin >> realm;
            req.add_realm(realm);
            cout << " Do you want to enter another Peer Name(y/n) : " << endl;
            cin >> input ;
        }while((input.compare("n")) != 0);
        
        if ((retVal = CMApiLibObj->GetPeerDREProtocolErrorStats(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::GetTransportStats success " << endl;
            int numOfPeers = resp.protoerrstats_size();

            for(int i = 0; i < numOfPeers ; i++)
            {
                peerErrorStats = resp.protoerrstats(i);

                cout << " Peer DRE Generated Protocol Error Statistics " << endl;
                cout << "========================================" << endl;
                cout << " Peer Name                     : " << peerErrorStats.peername() << endl;
                cout << " Total UnableToDeliver Errors  : " << peerErrorStats.unabletodeliver() << endl;
                cout << " Total RealmNotServed Errors   : " << peerErrorStats.realmnotserved() << endl;
                cout << " Total UnknownPeer Errors      : " << peerErrorStats.unknownpeer() << endl;
                cout << " Total UnknownSessionId Errors : " << peerErrorStats.unknownsessionid() << endl;
                cout << " Total InvalidAvpValue Errors  : " << peerErrorStats.invalidavpvalue() << endl;
                cout << " Total MissionAvp Errors       : " << peerErrorStats.missingavp() << endl; 
                cout << " Total NoCommonAppErrors       : " << peerErrorStats.nocommonapplication() << endl;
                cout << " Total InvalidAvpLength Errors : " << peerErrorStats.invalidavplength() << endl;
                cout << " Total InvalidMsgLength Errors : " << peerErrorStats.invalidmsglength() << endl;
                cout << " Total LoopDetected Errors     : " << peerErrorStats.loopdetected() << endl;
                cout << " Total AppNotSupported Errors  : " << peerErrorStats.applicationnotsupported() << endl;
                cout << " Total Other Errors            : " << peerErrorStats.othererrors() << endl;
            }
        }
        else
        {
            cout << "CMAPILib::GetDREProtocolErrorStats failed " << endl;
        }
        return 0;
    }

    int ResetPeerStats()
    {
        ResetPeerStatsReq req;
        ResetPeerStatsResp resp;
        int retVal;
        string input;
        char name[50];
        char realm[50];

        do
        {
            cout << "Enter the Peer Name : " << endl;
            cin >> name;
            req.add_peername(name);
            cout << "Enter the Realm : " << endl;
            cin >> realm;
            req.add_realm(realm);
            cout << " Do you want to enter another Peer Name(y/n) : " << endl;
            cin >> input ;
        }while((input.compare("n")) != 0);
        
        if ((retVal = CMApiLibObj->ResetAllPeerStats(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::ResetAllPeerStats success " << endl;
        }
        else
        {
            cout << "CMAPILib::ResetAllPeerStats failed " << endl;
        }
        return 0;
    }
    int GetUsers()
    {
        string userName;
        Users userlist;
        int retVal;
        ErrorDetails err;
        
        cout << " Enter the User Name : " << endl;
        cin >> userName;
        
        
        if ((retVal = CMApiLibObj->GetUser(userName, userlist,err)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::User Data retreived success " << endl;
            int numOfUser = userlist.userdata_size();
            for(int curUser = 0 ; curUser < numOfUser ; curUser++)
            {
                UserInfo user = userlist.userdata(curUser);
                
                cout << " User Data " << endl;
                cout << " -----------------------" << endl;
                cout << " User Name : " << user.username() << endl;
                cout << " password  : " << user.password() << endl;
                cout << " privilege : " << user.privilege() << endl;
                cout << " status    : " << user.status() << endl;
                Group group;
                group = user.usergroup();
                cout << " Group NAme : " << group.groupname() << endl;
                cout << " Group Desc : " << group.groupdesc() << endl;
                
            }
        }
        else
        {
            cout << "CMAPILib::User Data fetch failed " << endl;
        }
        return 0;

    }

    int AddUsers()
    {
        Users userlist;
        string name;
        char password[100];//to be populated by encrypted password by any algo (MD5)
        int privilege;
        UserInfo_UserStatus status;
        string input;
        int choice = 1;
        UserResp *resp = NULL;

        do
        { 
            UserInfo *userInfo = userlist.add_userdata();
 
            cout << "Enter User Name : " << endl;
            cin >> name;
            userInfo->set_username(name);

            cout << "populate password : " << endl;
            cin >> password;
            userInfo->set_password(password);

            cout << "Enter privilege : " << endl;
            cin >> privilege;
            userInfo->set_privilege(privilege);

            cout << "1.ACTIVE 2.INACTIVE 3.DELETED " << endl;
            cout << " Enter Status : " << endl;
            cin >> choice;
            status = ((choice == 1) ? UserInfo_UserStatus_ACTIVE : ((choice == 2) ? UserInfo_UserStatus_INACTIVE : UserInfo_UserStatus_DELETED)); 
            userInfo->set_status(status);
          
            Group *group = userInfo->mutable_usergroup();
            group->set_groupname("group1");
               
            cout << " Do you want to add another User (y/n) : " << endl;
            cin >> input ;
        }while((input.compare("n")) != 0);

        if (( CMApiLibObj->AddUser(userlist,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib:Add users success " << endl;
        }
        else
        {
            cout << "CMAPILib:Add User failed " << endl;
        }
        return 0;
        
    }

    int DeleteUsers()
    {
        string userName;
        Users userlist;
        string input;
        UserResp *resp = NULL;
        int retVal;
        do
        {
            UserInfo *user = userlist.add_userdata();
            cout << "Enter the User Name : " << endl;
            cin >> userName;
            user->set_username(userName);

            cout << " Do you want to enter another User Name(y/n) : " << endl;
            cin >> input ;
           
        }while((input.compare("n")) != 0);

        if ((retVal = CMApiLibObj->DeleteUser(userlist,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Deleted users success " << endl;
        }
        else
        {
            cout << "CMAPILib::Delete User failed " << endl;
        }
        return 0;

    }

    int ResetPassword()
    {
        string userName;
        char passwd[100];//copy the encryped password into this buffer
        size_t length;
        int retVal;
        UserResp *resp = NULL;

        cout << " Enter the UserName : " << endl;
        cin >> userName;
        cout << " Enter the password(encrypted password) : " << endl;
        cin >> passwd;
        length = strlen(passwd);
        
        if ((retVal = CMApiLibObj->ChangePassword(userName, passwd, length,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Reset password success " << endl;
        }
        else
        {
            cout << "CMAPILib::Reset passoword failed " << endl;
        }
        return 0;
    }

    int AddTraceFilters()
    {
        TraceReq req;
        TraceResp resp;
        int id,priority,expDur,expMsg,loglevel,retVal;
        bool status;
        std::string name,rule,input;

        do
        {
            TraceConfig *filter = req.add_tracedata();
            
            cout<<"Filter ID : ";
            cin>>id;
            filter->set_filterid(id);
            cout<<"Filter Name : ";
            cin>>name;
            filter->set_filtername(name);
            cout<<"Filter Rule : ";
            //cin>>rule;
            cin.ignore();
            std::getline(cin,rule);
            filter->set_rule(rule);
            cout<<"Filter Priority : ";
            cin>>priority;
            filter->set_priority(priority);
            cout<<"Expiry Duration : ";
            cin>>expDur;
            filter->set_expireduration(expDur);
            cout<<"Expiry Message : ";
            cin>>expMsg;
            filter->set_expiremessages(expMsg);
            cout<<"Filter Status(1-Enable/0-Disable) : ";
            cin>>status;
            filter->set_filterstatus(status);
            cout<<"Log Level : ";
            cin>>loglevel;
            filter->set_loglevel(loglevel);

            cout << " Do you want to enter another Filter details(y/n) : " << endl;
            cin >> input ;

        }while((input.compare("n")) != 0);

        if ((retVal = CMApiLibObj->AddTraceFilter(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Add Tracing Filter success " << endl;
        }
        else
        {
            cout << "CMAPILib::Add Tracing Filter failed " << endl;
        }
        return 0;
    }

    int DeleteTraceFilters()
    {
        string filterName;
        TraceReq req;
        TraceResp resp;
        string input;
        int retVal;
        do
        {
            TraceConfig *filter = req.add_tracedata();

            cout << "Enter the Filter Name to be deleted : " << endl;
            cin >> filterName;
            filter->set_filtername(filterName);

            cout << " Do you want to enter another Filter Name(y/n) : " << endl;
            cin >> input ;

        }while((input.compare("n")) != 0);

        if ((retVal = CMApiLibObj->DeleteTraceFilter(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Delete Filters success " << endl;
        }
        else
        {
            cout << "CMAPILib::Delete Filters failed " << endl;
        }
        return 0;
    }

    int ModifyTraceFilters()
    {
        TraceReq req;
        TraceResp resp;
        int priority,expDur,expMsg,loglevel,retVal;
        bool status;
        std::string name,rule,input;

        do
        {
            TraceConfig *filter = req.add_tracedata();
            
            cout<<"Filter Name to be Modified : "<<endl;
            cin>>name;
            filter->set_filtername(name);
            cout<<"Filter Rule : ";
            //cin>>rule;
            cin.ignore();
            std::getline(cin,rule);
            filter->set_rule(rule);
            cout<<"Filter Priority : ";
            cin>>priority;
            filter->set_priority(priority);
            cout<<"Expiry Duration : ";
            cin>>expDur;
            filter->set_expireduration(expDur);
            cout<<"Expiry Message : ";
            cin>>expMsg;
            filter->set_expiremessages(expMsg);
            cout<<"Filter Status(1-Enable/0-Disable) : ";
            cin>>status;
            filter->set_filterstatus(status);
            cout<<"Log Level : ";
            cin>>loglevel;
            filter->set_loglevel(loglevel);

            cout << " Do you want to modify another Filter details(y/n) : " << endl;
            cin >> input ;

        }while((input.compare("n")) != 0);

        if ((retVal = CMApiLibObj->ModifyTraceFilter(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Modified Filters successfully " << endl;
        }
        else
        {
            cout << "CMAPILib::Modify Tracing Filters failed " << endl;
        }
        return 0;
    }

    int GetTraceFilters()
    {
        string filterName;
        TraceReq req;
        TraceResp resp;
        string input;
        int retVal;
        do
        {
            TraceConfig *filter = req.add_tracedata();

            cout << "Enter the Filter Name : " << endl;
            cin >> filterName;
            filter->set_filtername(filterName);

            cout << " Do you want to enter another Filter Name(y/n) : " << endl;
            cin >> input ;

        }while((input.compare("n")) != 0);

        if ((retVal = CMApiLibObj->GetTraceFilter(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Get Filters success " << endl;
            cout << "Enable Tracing : "<<resp.enabletrace() << endl;
            int size = resp.tracedata_size();
            int errsize = resp.errordetails_size();
            cout << "number of errors recieved : "<< errsize << endl;
            cout << "number of filter recieved : "<< size << endl;
            for(int i=0 ; i<size ; i++)
            {
                TraceConfig filter = resp.tracedata(i);

                cout << " Fileter Id     : " << filter.filterid();
                cout << " Fileter Name   : " << filter.filtername();
                cout << " Rule           : " << filter.rule();
                cout << " Priority       : " << filter.priority();
                cout << " Exp. Duration  : " << filter.expireduration();
                cout << " Exp. Msgs      : " << filter.expiremessages();
                cout << " Fileter Status : " << filter.filterstatus();
                cout << " Log Level      : " << filter.loglevel();
            }
        }
        else
        {
            cout << "CMAPILib::Delete Filters failed " << endl;
        }
        return 0;
    }

    int EnableTracing()
    {
        TraceReq req;
        TraceResp resp;
        string input;
        int retVal;

        cout << "Enable System Level Tracing(y/n) : ";
        cin >> input;
        if((input.compare("y")) == 0)
        {
            cout<<"Enabling Tracing"<<endl;
            req.set_enabletrace(true);
        }
        else
        {
            cout<<"Disabling Tracing"<<endl;
            req.set_enabletrace(false);
        }
        if ((retVal = CMApiLibObj->EnableTracing(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::System Level Tracing Enabled " << endl;
        }
        else
        {
            cout << "CMAPILib::System Level Tracing disabled " << endl;
        }

        return 0;
    }

    int GetFilterStatus()
    {
        string filterName;
        TraceReq req;
        TraceResp resp;
        string input;
        int retVal;
        do
        {
            //TraceConfig *filter = req.add_tracedata();

            //cout << "Enter the Filter Name : " << endl;
            //cin >> filterName;
            //filter->set_filtername(filterName);

            cout << " Do you want to enter another Filter Name(y/n) : " << endl;
            cin >> input ;

        }while((input.compare("n")) != 0);

        if ((retVal = CMApiLibObj->PollTraceFilter(req,resp)) == CMAPI_SUCCESS)
        {
            cout << "CMAPILib::Get Filters success " << endl;
            cout << "Enable Tracing : "<<resp.enabletrace() << endl;
            int size = resp.tracedata_size();
            int errsize = resp.errordetails_size();
            cout << "number of errors recieved : "<< errsize << endl;
            cout << "number of filter recieved : "<< size << endl;
            for(int i=0 ; i<size ; i++)
            {
                TraceConfig filter = resp.tracedata(i);

                cout << " Fileter Name   : " << filter.filtername();
                cout << " Fileter Status : " << filter.filterstatus();
            }
        }
        else
        {
            cout << "CMAPILib::Delete Filters failed " << endl;
        }
        return 0;
    }

	int Menu()
	{
		cout << " \n\n\n****** MENU *******" << endl;
		cout << " 1: Get Local Host Info " << endl;
		cout << " 2: Get Peer Info " << endl;
		cout << " 3: Set Auth Timers"<< endl;
		cout << " 4: Set Local Host " << endl;
		cout << " 5: Set Acct Timers " << endl;
		cout << " 6: Set Host IP Addr " << endl;
		cout << " 7: Get Realm        " << endl;
		cout << " 8: Get All Realms   " << endl;
		cout << " 9: Add Realm  " << endl;
		cout << "10: Delete Realm " << endl;
		cout << "11: Set Default Route " << endl;
		cout << "12: Get Default Route " << endl;
		cout << "13: Add Realm Route  " << endl;
		cout << "14: Enable Proxy AVP " << endl;
		cout << "15: Disable Proxy AVP " << endl;
		cout << "16: Get All Pears " << endl;
		cout << "17: Get All Pears of the Realm " << endl;
		cout << "18: Add Peer " << endl;
		cout << "19: Remove Peer " << endl;
		cout << "20: Modify Peer " << endl;
        cout << "21: Modify Realm " << endl;
        cout << "22: Modify Local Host " << endl;
        cout << "23: Modify Realm Route " << endl;
        cout << "24: Delete Realm Route " << endl;
        cout << "25: Delete DefaultRoute " << endl;
        cout << "26: Get Peer General Stats " << endl;
        cout << "27: Get Peer Transport Stats " <<endl;
        cout << "28: Get Peer DRE Error Stats " << endl;
        cout << "29: Rest All Peer Stats " << endl;
        cout << "30: Add Dictionaries to Peer   " << endl;
        cout << "31: Delete Dictionaries From Peer " << endl;
        cout << "32: Set Peer Status " << endl;
        cout << "33: Add User " << endl;
        cout << "34: Get User " << endl;
        cout << "35: Delete User " << endl;
        cout << "36: Reset Password " << endl;
        cout << "37: Get Unique Realms from Peer Table " << endl;
        cout << "38: Add Trace Filter " << endl;
        cout << "39: Delete Trace Filter " << endl;
        cout << "40: Modify Trace Filter " << endl;
        cout << "41: Get Trace Filters" << endl;
        cout << "42: Enable System Tracing " << endl;
        cout << "43: Get Tracing Filter Status " << endl;
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
		    case GETLOCALHOST:
			    cout << "GETLOCALHOST Request" << endl;
			    GetLocalHostConfig();
			    break;
		    case GETPEERINFO:
			    cout << "GETPEERINFO Request" << endl;
			    GetPeerInfo();
			    break;
		    case SETAUTHTIMERS:
			    cout << "SETAUTHTIMERS Request" << endl;
			    SetAuthTimers();
			    break;
		    case  SETLOCALHOST:
			    cout << "SETLOCALHOST Request" << endl;
			    SetLocalHost();
			    break;
		    case SETACCTTIMERS:
			    cout << "SETACCTTIMERS Request" << endl;
			    SetAcctTimers();
			    break;
		    case SETIPADDR:
			    cout << "SETIPADDR Request" << endl;
			    SetHostIPAddr();
			    break;
		    case  GETREALM:
			    cout << "GETREALM Request" << endl;
			    GetRealm();
			    break;
		    case GETALLREALMS:
			    cout << "GETALLREALMS Request" << endl;
			    GetAllRealms();
			    break;
		    case SETREALM:
			    cout << "SETREALM Request" << endl;
			    SetRealm();
			    break;
		    case DELREALM:
			    cout << "DELREALM Request" << endl;
			    DeleteRealm();
			    break;
		    case SETDEFROUTE:
			    cout << "SETDEFROUTE Request" << endl;
			    SetDefaultRoute();
			    break;
		    case GETDEFROUTE:
			    cout << "GETDEFROUTE Request" << endl;
			    GetDefaultRoute();
			    break;
		    case SETDEST:
			    cout << "SETDEST Request" << endl;
			    SetDest();
			    break;
		    case ENBPXY:
			    cout << "ENBPXY Request" << endl;
			    EnableProxy();
			    break;
		    case DISPXY:
			    cout << "DISPXY Request" << endl;
			    DisableProxy();
			    break;
		    case GETALLPEERS:
			    cout << "GETALLPEERS Request" << endl;
			    GetAllPeers();
			    break;
		    case GETALLREALMPEERS:
			    cout << "GETALLREALMPEERS Request" << endl;
			    GetAllPeersofRealm();
			    break;
		    case SETPEER:
			    cout << "SETPEER Request" << endl;
			    SetPeerConfig();
			    break;
		    case DELPEER:
			    cout << "DELPEER Request" << endl;
			    RemovePeerConfig();
			    break;
            case MODPEER:
                cout << "MODPEER Request" << endl;
                ModifyPeerConfig();
                break;
            case MODREALM:
                cout << "MODREALM Request" << endl;
                ModRealm();
                break;
            case  MODLOCALHOST:
                cout << "SETLOCALHOST Request" << endl;
			    ModLocalHost();
			    break;

            case MODDEST:
                cout << "Modify Realm Route Request" << endl;
                ModifyDestination();
                break;
            case DELDEST:
                cout << "DELREALM Request" << endl;
                DeleteDestination();
                break;
            case DELDEFROUTE:
                cout << "DELDEFROUTE Request" << endl;
                DeleteDefRoute();
                break;
            case GETPEERGENERALSTATS:
                cout << "GETPEERGENERALSTATS Request" << endl;
                GetPeerGeneralStats();
                break;
            case GETPEERTRANSPORTSTATS:
                cout << "GETPEERTRANSPORTSTATS Request" << endl;
                GetPeerTransportStats();
                break;
            case GETPEERERRORSTATS:
                cout << "GETPEERERRORSTATS Request" << endl;
                GetPeerErrorStats();
                break;
            case RESETPEERSTATS:
                cout << "RESETPEERSTATS Request" << endl;
                ResetPeerStats();
                break;
            case ADDDICTID:
                cout << "Add Dictionary " << endl;
                AddDictID();
                break;
            case DELDICTID:
                cout << "Delete Dictionary " << endl;
                DelDictID();
                break;
            case PEERSTATUS:
                cout << "Set Peer Status " << endl;
                SetPeerStatus();
                break;
            case GETUSER:
                cout << " Get Users " << endl;
                GetUsers();
                break;
            case SETUSER:
                cout << " Set User " << endl;
                AddUsers();
                break;
            case DELUSER:
                cout << " Delete User " << endl;
                DeleteUsers();
                break;
            case RESETPSSWD:
                cout << " Reset Password " << endl;
                ResetPassword();
                break;
            case GETUNIQUEREALMS:
                GetUniqueRealms();
                cout << "Get unique realms request" << endl;
                break;
            case SETTRACE:
                cout << "Add Filter for Tracing" << endl;
                AddTraceFilters();
                break;
            case DELTRACE:
                cout << "Delete Filter from Tracing" << endl;
                DeleteTraceFilters();
                break;
            case MODTRACE:
                cout << "Modify Filters in Tracing" << endl;
                ModifyTraceFilters();
                break;
            case GETTRACE:
                cout << "Get All Filter " << endl;
                GetTraceFilters();
                break;
            case ENABLETRACE:
                cout << "Enable Tracing" << endl;
                EnableTracing();
                break;
            case GETFILTERSTATUS:
                cout<<"Get Filter STatus"<<endl;
                GetFilterStatus();
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
        ApiLibUser() {}
        ~ApiLibUser() {}

        void Run(void *arg)
        {
            Initialize();
            RunMain();
            cout << "CMAPI Test Agent Exiting... BYE" << endl;
            exit(0);
        }

    private:
       CMAPIProdConfig *CMApiLibObj;
        
};


int main(int argc, char *argv[])
{

    ApiLibUser LibUser;
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
