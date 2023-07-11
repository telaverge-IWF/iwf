#include "MeSSComponent.h"
#include "ComponentDefines.h"
#include <iostream>
#include "StackStats_def.h"
#include "InterfaceStat_def.h"

#include "TestAgent.h"
#include "CMAPIStatsLib.h"
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
            CMApiLibObj = new  CMAPIStatsConfig();
            CMApiLibObj->InitializeLibrary();
        }

        int GetInterfaceStats()
        {

            InterfaceStatsReq req;
            InterfaceStatsResp resp;
            InterfaceStats stats;
            int retVal;
            string input,ch;
            char name[50];

            cout <<"Get Stats for all the Interface (y/n) : ";
            cin >> ch;
            if((ch.compare("n") == 0) || (ch.compare("N") == 0)) 
            {   
                do  
                {   
                    cout << "Enter the Interface Name : " << endl;
                    cin >> name;
                    req.add_interfacename(name);
                    cout << " Do you want to enter another Interface (y/n) : " << endl;
                    cin >> input ;
                }while((input.compare("n")) != 0);
            }
            else
            {
                cout<<"getting stats for all interface"<<endl;
            }
            if ((retVal = CMApiLibObj->GetInterfaceStats(req,resp)) == CMAPI_SUCCESS)
            {
                cout << "CMAPIStatsLib::GetInterfaceStats success " << endl;
                int numOfPeers = resp.stats_size();

                for(int i = 0; i < numOfPeers ; i++)
                {
                    stats = resp.stats(i);

                    cout << " DRE Supported Interface Statistics " << endl;
                    cout << "====================================" << endl;
                    cout << " Interface     : " << stats.interfacename() << endl;
                    cout << " Command Code  : " << stats.commandcode() << endl;
                    cout << " Request In    : " << stats.reqin() << endl;
                    cout << " Request Out   : " << stats.reqout() << endl;
                    cout << " Response In   : " << stats.respin() << endl;
                    cout << " Response Out  : " << stats.respout() << endl;
                    cout << " Error Msgs    : " << stats.errormsgs() << endl;
                    cout << " Invalid Msgs  : " << stats.invalidmsgs() << endl;
                }
             }
            else
            {
                cout << "CMAPIStatsLib::GetInterfaceStats failed" << endl;
                int size = resp.errordetails_size();
                cout << "errror details size " <<resp.errordetails_size()<<endl;
                for(int i =0 ; i < size ; i++)
                {
                    ErrorDetails err = resp.errordetails(i);
                    cout<<"Error details"<<endl;
                    cout<<"Error Code "<<err.errorcode()<<endl;
                    cout<<"Error Msg " <<err.errormsgkey()<<endl;
                    cout<<"Variable size "<<err.variables_size()<<endl;
                    for(int j=0 ; j<err.variables_size();j++)
                    {
                        cout<<"variable " <<err.variables(j)<<endl;
                    }

                }

            }
            return 0;
        }

        int ResetInterfaceStats()
        {
            InterfaceStatsReq req;
            ResetInterfaceStatsResp resp;
            InterfaceStats stats;
            int retVal;
            string input,ch;
            char name[50];

            cout <<"Get Stats for all the Interface (y/n) : ";
            cin >> ch;
            if((ch.compare("n") == 0) || (ch.compare("N") == 0))
            {
                do
                {
                    cout << "Enter the Interface Name : " << endl;
                    cin >> name;
                    req.add_interfacename(name);
                    cout << " Do you want to enter another Peer Name(y/n) : " << endl;
                    cin >> input ;
                }while((input.compare("n")) != 0);
            }

            if ((retVal = CMApiLibObj->ResetInterfaceStats(req,resp)) == CMAPI_SUCCESS)
            {
                cout << "CMAPIStatsLib::ResetAllInterfaceStats success " << endl;
            }
            else
            {
                cout << "CMAPIStatsLib::ResetAllInterfaceStats failed " << endl;
            }
            return 0;
        }

int GetApplicationSpecStats()
{
    ApplicationspecStatsReq req;
    ApplicationspecStatsResp resp;
    int retVal;

    if((retVal = CMApiLibObj->GetApplicationSpecificStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "Global Application Specific Statistics" << endl;
        cout << "======================================" << endl;
        cout << "Total ReqIn    : " << resp.totalreqin() << endl;
        cout << "Total ReqOut   : " << resp.totalreqout() << endl;
        cout << "Total AnsIn    : " << resp.totalansin() << endl;
        cout << "Total AnsOut   : " << resp.totalansout() << endl;
    }
    else
    {
        cout << "CMApiLibObj GetApplicationSpecStats : Failed :"  <<endl;
    }

    return 0;
}

int ResetApplicationSpecStats()
{
    ResetApplicationspecStatsReq req;
    ResetApplicationspecStatsResp resp;
    int retVal;

    if ((retVal = CMApiLibObj->ResetApplicationspecStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "CMAPILib::ResetAllApplicationStats : Success " << endl;
    }
    else
    {
        cout << "CMAPILib::ResetAllApplicationStats : Failed " << endl;
    }
    return 0;
}

int GetStackIndicationStats()
{
    StackIndicationStatsReq req;
    StackIndicationStatsResp resp;
    int retVal;

    if((retVal = CMApiLibObj->GetStackIndicationStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "Global Stack Indication Statistics" << endl;
        cout << "======================================" << endl;
        cout << "Disconnect Indication   : " << resp.disconnectindication() << endl;
        cout << "Timeout Indication      : " << resp.timeoutindication() << endl;
        cout << "Abort Indication        : " << resp.abortindication() << endl;
        cout << "Corrupt Indication      : " << resp.corruptindication() << endl;
        cout << "Unknown Indication      : " << resp.unknownindication() << endl;
        cout << "FailOver Indication     : " << resp.failoverindication() << endl;
        cout << "FailBack Indication     : " << resp.failbackindication() << endl;
    }
    else
    {
        cout << "CMApiLibObj GetStackIndicationStats : Failed :"  <<endl;
    }
    return 0;
}

int ResetStackIndicationStats()
{
    ResetStackIndicationStatsReq req;
    ResetStackIndicationStatsResp resp;
    int retVal;

    if ((retVal = CMApiLibObj->ResetStackIndicationStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "CMAPILib::ResetAllStackIndicationStats : Success " << endl;
    }
    else
    {
        cout << "CMAPILib::ResetAllStackIndicationStats : Failed " << endl;
    }
    return 0;
}

int GetGenericStats()
{
    GenericStatsReq req;
    GenericStatsResp resp;
    int retVal;

    if((retVal = CMApiLibObj->GetGenericStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "Global Generic Statistics" << endl;
        cout << "======================================" << endl;
        cout << "Total Handled Messages  : " << resp.totalhandledmessages() << endl;
        cout << "Total Active Sessions   : " << resp.currentactivesession() << endl;
    }
    else
    {
        cout << "CMApiLibObj GetGenericStats: Failed :"  <<endl;
    }
    return 0;
}

int ResetGenericStats()
{
    ResetGenericStatsReq req;
    ResetGenericStatsResp resp;
    int retVal;

    if ((retVal = CMApiLibObj->ResetGenericStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "CMAPILib::ResetAllGenericStats : Success " << endl;
    }
    else
    {
        cout << "CMAPILib::ResetAllGenericStats : Failed " << endl;
    }
    return 0;
}


int GetGenericErrorStats()
{
    GenericErrorStatsReq req;
    GenericErrorStatsResp resp;
    int retVal;

    if((retVal = CMApiLibObj->GetGenericErrorStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "Global Stack Indication Statistics" << endl;
        cout << "======================================" << endl;
        cout << "Malformed Messages    : " << resp.malformedmessages() << endl;
        cout << "HopByHopDrop Messages : " << resp.hopbyhopdropmessages() << endl;
        cout << "Ans With e Bit SetIn  : " << resp.answerwithebitsetin() << endl;
        cout << "Ans With e Bit SetOut : " << resp.answerwithebitsetout() << endl;
        cout << "Total Failure resp.   : " << resp.failureresponses() << endl;
    }
    else
    {
        cout << "CMApiLibObj GetgenericErrorStats: Failed :"  <<endl;
    }
    return 0;
}

int ResetGenericErrorStats()
{
    ResetGenericErrorStatsReq req;
    ResetGenericErrorStatsResp resp;
    int retVal;

    if ((retVal = CMApiLibObj->ResetGenericErrorStats(req,resp)) == CMAPI_SUCCESS)
    {
        cout << "CMAPILib::ResetAllGenericErrorStats : Success " << endl;
    }
    else
    {
        cout << "CMAPILib::ResetAllGenericErrorStats : Failed " << endl;
    }
    return 0;
}


int Menu()
{
    cout << " \n\n\n****** MENU *******" << endl;
    cout << "01: Get Interface Stats " << endl;
    cout << "02: Reset Interface Stats " << endl;
    cout << "03: Get Application Spec. Stats " << endl;
    cout << "04: Reset application Spec. Stats " << endl;
    cout << "05: Get Stack Indication Stats " << endl;
    cout << "06: Reset Stack Indication Stats " << endl;
    cout << "07: Get GenericError Stats " << endl;
    cout << "08: Reset GenericError Stats " << endl;
    cout << "09: get Generic Stats " << endl;
    cout << "10: Reset Generic Stats " << endl;
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
        case GETINTERFACESTATS:
            cout << "Get interface Stats request" << endl;
            GetInterfaceStats();
            break;
        case RESETINTERFACESTATS:
            cout << "Reset interface Stats request" << endl;
            ResetInterfaceStats();
            break;
        case GETAPPLICATIONSPECSTATS:
            cout << "Get Application specific stats" << endl;
            GetApplicationSpecStats();
            break;
        case RESETAPPLICATIONSPECSTATS:
            cout << "Reset Application specific stats" << endl;
            ResetApplicationSpecStats();
            break;
        case GETSTACKINDICATIONSTATS:
            cout << "Get Stack Indication Stats " << endl;
            GetStackIndicationStats();
            break;
        case RESETSTACKINDICATIONSTATS:
            cout << "Reset Stack Indication Stats" << endl;
            ResetStackIndicationStats();
            break;
        case GETGENERICERRORSTATS:
            cout << "Get Generic error Stats" << endl;
            GetGenericErrorStats();
            break;
        case RESETGENERICERRORSTATS:
            cout << "Reset Generic error stats" << endl;
            ResetGenericErrorStats();
            break;
        case GETGENERICSTATS:
            cout << "Get Generic stats " << endl;
            GetGenericStats();
            break;
        case RESETGENERICSTATS:
            cout << "Reset Generic Stats" << endl;
            ResetGenericStats();
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
CMAPIStatsConfig *CMApiLibObj;

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
