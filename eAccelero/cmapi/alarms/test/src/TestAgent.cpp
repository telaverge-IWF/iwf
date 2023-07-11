
#include "MeSSComponent.h"
#include "ComponentDefines.h"
#include <iostream>
#include "Alarms_def.h"
#include "CMAPICommon.h"
#include "CMAPIAlarms.h"

#include "ThreadQueue.h"
#include "Thread.h"

#define TESTAGENT_COMP_ID  3333

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
        : MeSSComponent("TestAgent", TESTAGENT_COMP_ID)
    {
    }
    
    void Initialize()
    {
        MeSSComponent::Initialize();
        
        TopologyEvent compEvent(COMP_SUB_AGENT);
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
            std::cout << "SubAgent Process is UP" << endl;
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
            m_alarms = new CMAPIAlarms();
            m_alarms->InitializeLibrary(0);
        }

        void RaiseAlarms() {
            AlarmReq Req;
            AlarmResp Resp;
            string strval;
            int NumVal;
            cout << "Enter Alarms Id : " ; cin >> NumVal; Req.set_alarmid(NumVal);
            cout << "Enter Additional Text:"; cin >> strval; Req.set_addtext(strval);
            if (m_alarms->RaiseAlarm(Req,Resp) == CMAPI_SUCCESS)
            {
                 cout << " Successfully Raised an Alarms" << endl;
            }
            
        }

        int Menu()
        {
            cout << "************ MENU ************" << endl;
            cout << "1. Raise an alarm    " << endl;
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
                    RaiseAlarms();
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
        CMAPIAlarms *m_alarms;
        
};


int main(int argc, char *argv[])
{

    ApiUser LibUser;
    Thread  LibTest("CMAPITest");
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
