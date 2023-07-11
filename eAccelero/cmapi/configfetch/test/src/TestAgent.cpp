
#include "MeSSComponent.h"
#include "ComponentDefines.h"
#include <iostream>
#include "Compo_def.h"
#include "CMAPIConfig.h"

#include "ThreadQueue.h"
#include "Thread.h"

#define TESTAGENT_COMP_ID  3333
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
    TestAgent()
        : MeSSComponent("CONFIGFETCH", TESTAGENT_COMP_ID)
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
            m_cmapi = new CMAPIConfig();
            m_cmapi->InitializeLibrary();
        }

        void GetDreInfo()
        {
            DRECfgResp resp1;
            if (m_cmapi->GetDreConfiguration(&resp1) == CMAPI_SUCCESS)
            {
                DRECfgResp *resp = &resp1;
                if (resp->has_respcode() && resp->respcode() == CMAPICODE_SUCCESS)
                {
                    cout << "Successfully processed by server" << endl;
                    if (resp->has_localhost())
                    {
                        LocalHostConfig *lHost = resp->mutable_localhost();
                        cout << "LOCAL HOST INFO : " << endl;
                        cout << "  Host Name     :  " << lHost->localhostname() << endl;
                        cout << "  Realm Name    :  " << lHost->realmname() << endl;
                        cout << "  AUTH TIMEOUT  :  " << lHost->authsessiontimeout() << endl;
                        cout << "  AUTH GRACETO  :  " << lHost->authsessiongraceperiod() << endl;
                        cout << "  AUTH LIFETO   :  " << lHost->authsessionlifetime() << endl;
                        cout << "  ACCT INTERIM  :  " << lHost->acctsessioninteriminterval() << endl;
                        cout << "  ACCT REALTO   :  " << lHost->acctsessionrealtime() << endl;
                        cout << "  ACCT TIMEOUT  :  " << lHost->acctsessiontimeout() << endl;
                    }
                }

                if (resp->has_peers())
                {
                    cout << "Response for GETPEERINFO REquest " << endl;
                    PeersConfig *Peers = resp->mutable_peers();
                    int NPeers = Peers->peers_size();
                    for (int i = 0; i < NPeers; i++)
                    {
                        PeerConfig *PC = Peers->mutable_peers(i);
                        cout << "*********PEERINFO*************" << endl;
                        cout << "PeerName       : " << PC->peerhostname() << endl;
                        cout << "Realm          : " << PC->realm() << endl;
                        cout << "IPAddr         : " << PC->serveripaddr() << endl;
                        cout << "Port           : " << PC->port() << endl;
                        cout << "TransportType  : " << PC->transporttype() << endl;
                        cout << "TlsEnabled     : " << PC->tlsenabled() << endl;
                        cout << "FailoverEnable : " << PC->failoverenable() << endl;
                        cout << "FailebackEnable: " << PC->failebackenable() << endl;
                        cout << "AltPeerName    : " << PC->altpeername() << endl;
                        cout << "IsMate         : " << PC->ismate() << endl;
                        cout << "TcTimerVal     : " << PC->tctimerval() << endl;
                        cout << "WatchDogTimer  : " << PC->watchdogtimer() << endl;
                        cout << "ExpiryTimer    : " << PC->expirytimer() << endl;
                    }
                }

                if (resp->has_realms())
                {
                    RealmsConfig *Realms = resp->mutable_realms();
                    int NRealms = Realms->realms_size();
                    for (int i = 0; i < NRealms; i++)
                    {
                        RealmConfig *RC = Realms->mutable_realms(i);
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
                            cout << "Application ID : " << DT->applicationid() << endl;
                            cout << "VendorID       : " << DT->vendorid() << endl;
                            cout << "Priority       : " << DT->priority() << endl;
                        }
                    }
                }
            }else
            {
                cout << "No Dre Configuration " << endl;
            }


        }

        void GetErlbfInfo()
        {
            LBPeerGroups Resp; int NumPeers;
            if (m_cmapi->GetErlbfConfiguration(&Resp) == CMAPI_SUCCESS)
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
                    for (int nP = 0; nP < NumPeers; nP++)
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

        int Menu()
        {
            cout << "************ MENU ************" << endl;
            cout << "1. Get Dre Configuration  " << endl;
            cout << "2. Get Erlbf Configuration" << endl;
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
                case 1:
                    GetDreInfo();
                    break;
                case 2:
                    GetErlbfInfo();
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
        CMAPIConfig *m_cmapi;
        
};


int main(int argc, char *argv[])
{

    ApiUser LibUser;
    Thread  LibTest("ConfigFetch");
    cout << "Starting CMAPI Test Thread" << endl;
    LibTest.Start(&LibUser);

    TestAgent *app = NULL;
    try
    {
        app = new TestAgent();
        
        app->Init(argc, argv);

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
