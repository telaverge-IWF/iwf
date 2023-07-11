
#include "MeSSComponent.h"
//#include "repmgrcmn.h"
#include "RepMgrCommon.h"
#include "repmgr_cfg.h"

#include <iostream>

using namespace eAccelero;

class SampCliApp: public MeSSComponent
{
public:
    SampCliApp()
        : MeSSComponent("SampleCliApp", COMP_DREAPP_ID)
    {
        MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_REPLFLAG), 
            CallbackSlot<SampCliApp, struct ReplFlagResp>(this, &SampCliApp::GetRepFlagRespCbk));
        MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_LOGLEVEL), 
            CallbackSlot<SampCliApp, struct ReplLogLevelResp>(this, &SampCliApp::GetLogLevelRespCbk));
    }
    
    void Initialize()
    {
        MeSSComponent::Initialize();
        
        TopologyEvent compEvent(RepMgrID);
        MeSSObj().TopSvc().Subscribe(
            EventSlot<TopologyEvent, SampCliApp>(this, &SampCliApp::OnServerEvent),
            compEvent);          
    }
    void Terminate()
    {
        MeSSComponent::Terminate();
    }
   
    int GetRepFlagRespCbk(ReplFlagResp *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "Replication Flag Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        
        std::cout << "Replication Flag set Successful" << std::endl;
        
        return 0;
    }
    
    int GetLogLevelRespCbk(ReplLogLevelResp *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "Replication Log Level Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        
        std::cout << "Replication Log Level set Successful" << std::endl;
        
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
                this->reqCliOperation();
                once++;
            }
        }
        return 0;
    }

protected:
    
    void reqCliOperation()
    {
        MessageId msgId;
        MeSSEndpoint dest = {RepMgrID, m_cmdArgs.RepMgrInst};
        
        switch (m_cmdArgs.actionf)
        {
            case 1:   // Replication Flag
                struct ReplFlagReq req;
                if (m_cmdArgs.YesNoflag == 1)
                req.bRepl = true;
                else req.bRepl = false;
                msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_REPLFLAG);
                MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
                break;
            case 2:  // LogLevel change
                struct ReplLogLevelReq req1;
                req1.bReplLogLvl =  m_cmdArgs.LogLvl;
                if (m_cmdArgs.YesNoflag == 1)
                req1.bLogFlag = true;
                else req1.bLogFlag = false;                
                msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_LOGLEVEL);
                MeSSObj().Send(dest, msgId, (void*)&req1, sizeof(req1));
                break;
            case 3:   // State Change
                struct RepMgrStateReq StateReq;
                if (m_cmdArgs.YesNoflag == 1)
                   StateReq.RepMgrState = true;
                else  StateReq.RepMgrState = false;
                msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_CHANGESTATE);
                MeSSObj().Send(dest, msgId, (void*)&StateReq, sizeof(StateReq));
   
                break;

                
        }
        

        std::cout << "Operation Run. Bye Bye!" << std::endl;
        exit(0);

    }

    struct CmdArgs
    {
        CmdArgs()
            : RepMgrInst("r", "repmgr", "Replication manager Instance", false),
            actionf("a", "action", "1-Replication Flag 2- Log Level 3-State ", false),
            YesNoflag("y", "yesno", "Yes NoFlag ", false),
            LogLvl("g", "golvl", "Replication LogLevel ", false)          
        {
        }
        CmdOption<int> RepMgrInst;
        CmdOption<int>  actionf;
        CmdOption<int>  YesNoflag;
        CmdOption<int>  LogLvl;
    }m_cmdArgs;
 
};

int main(int argc, char *argv[])
{
    SampCliApp *app = NULL;
    try
    {
        app = new SampCliApp();
        
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
