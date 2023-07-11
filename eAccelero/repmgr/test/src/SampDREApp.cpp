
#include "MeSSComponent.h"
//#include "repmgrcmn.h"
#include "RepMgrCommon.h"
#include "repmgr_cfg.h"
#include <iostream>

using namespace eAccelero;

class SampDreApp: public MeSSComponent
{
public:
    SampDreApp()
        : MeSSComponent("SampleDREApp", COMP_DREAPP_ID)
    {
        MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_CACHE_DREBINDINFO), 
            CallbackSlot<SampDreApp, DREBindResp>(this, &SampDreApp::GetConfigRespCbk));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_UPDATE_DREBINDINFO), 
            CallbackSlot<SampDreApp, DREBindResp>(this, &SampDreApp::GetConfigRespCbk));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_DELETE_DREBINDINFO), 
            CallbackSlot<SampDreApp, DREBindResp>(this, &SampDreApp::GetConfigRespCbk));
    }
    
    void Initialize()
    {
        MeSSComponent::Initialize();
        
        TopologyEvent compEvent(RepMgrID);
        MeSSObj().TopSvc().Subscribe(
            EventSlot<TopologyEvent, SampDreApp>(this, &SampDreApp::OnServerEvent),
            compEvent);          
    }
    void Terminate()
    {
        MeSSComponent::Terminate();
    }
   
    int GetConfigRespCbk(DREBindResp *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "GetConfig Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        
        std::cout << "Cache Operation Successful" << std::endl;
        
        return 0;
    }

    int OnServerEvent(TopologyEvent &event)
    {
        static int once = 0;
        if (event.NotificationType() == TopologyEvent::NOTIFY_TYPE_PUBLISHED)
        {
            std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
            if (once == 0)
            {
                this->reqCacheOperation();
                once++;
            }
        }
        return 0;
    }

protected:
    
    void reqCacheOperation()
    {
        switch (m_cmdArgs.actionreq)
        {
            case 1:
                SaveSessionID();
                break;
            case 2:
                UpdateSessionID();
                break;
            case 3:
                DeleteSessionID();
                break;
            default:
                std::cout << "invalid request"  << std::endl;                     
        }
        std::cout << "Operation Run. Bye Bye!" << std::endl;
        exit(0);
        
    }
    
    void SaveSessionID()
    {
        MessageId msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_CACHE_DREBINDINFO);
        MeSSEndpoint dest = {RepMgrID, m_cmdArgs.activeRepMgrInst};
        DREBindInfo req;
        strcpy(req.diaSessionId,((std::string)m_cmdArgs.sKey).c_str());
        strcpy(req.diaPeer,((std::string)m_cmdArgs.sValue).c_str());
        std::cout << "Save to RepMgr "<< req.diaSessionId << " : " << req.diaPeer << std::endl;
        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
    }
    void UpdateSessionID() 
    {
        MessageId msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_UPDATE_DREBINDINFO);
        MeSSEndpoint dest = {RepMgrID, m_cmdArgs.activeRepMgrInst};
        DREBindInfo req;
        strcpy(req.diaSessionId,((std::string)m_cmdArgs.sKey).c_str());
        strcpy(req.diaPeer,((std::string)m_cmdArgs.sValue).c_str());
        std::cout << "Save to RepMgr "<< req.diaSessionId << " : " << req.diaPeer << std::endl;
        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
    }
    
    void DeleteSessionID()
    {
        MessageId msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_DELETE_DREBINDINFO);
        MeSSEndpoint dest = {RepMgrID, m_cmdArgs.activeRepMgrInst};
        DREBindInfo req;
        strcpy(req.diaSessionId,((std::string)m_cmdArgs.sKey).c_str());
        std::cout << "Save to RepMgr "<< req.diaSessionId << " : " << req.diaPeer << std::endl;
        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
    }

    struct CmdArgs
    {
        CmdArgs()
            : actionreq("a", "action", "Replication Action ", true),
            activeRepMgrInst("r", "repmgr", "Replication Active instance", true),
            sKey("k", "Key", "Cache Key", true),
            sValue("v", "Value", "Cache Key Value", false)
        {
        }
        CmdOption<int>  actionreq;
        CmdOption<int>  activeRepMgrInst;
        CmdOption<std::string> sKey;
        CmdOption<std::string> sValue;
    }m_cmdArgs;
 
};

int main(int argc, char *argv[])
{
    SampDreApp *app = NULL;
    try
    {
        app = new SampDreApp();
        
        app->Init(argc, argv);

        CLOG_NOTICE("Application initialized");

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
