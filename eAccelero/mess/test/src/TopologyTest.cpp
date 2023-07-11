#include "TopSrv.h"
#include "Component.h"
#include "Timer.h"

using namespace eAccelero;

const unsigned TOPTEST_APP_ID = 200;

class TopTestApp: public ComponentBase
{
 public:
    TopTestApp()
        : ComponentBase("TopTestApp", TOPTEST_APP_ID)
    {
        
    }
    void Initialize()
    {
        ComponentBase::Initialize();
        m_topSrv.Initialize();
        
        TopologyEvent compEvent(m_cmdArgs.compId);
        m_topSrv.Subscribe(
            EventSlot<TopologyEvent, TopTestApp>(this, &TopTestApp::OnComponentEvent),
            compEvent);
            
        TopologyEvent instEvent(m_cmdArgs.compId, m_cmdArgs.instId, m_cmdArgs.instId);
        m_instEvhId = m_topSrv.Subscribe(
            EventSlot<TopologyEvent, TopTestApp>(this, &TopTestApp::OnInstanceEvent),
            instEvent);
        
        TopologyEvent nodeEvent(TIPC_CFG_SRV, 1, TIPC_MAX_INST);  
        m_topSrv.Subscribe(
            EventSlot<TopologyEvent, TopTestApp>(this, &TopTestApp::OnNodeEvent),
            nodeEvent);
            
        // This timer expires after 20 secs
        this->GetDispatcher()->AddEventHandler(
            EventSlot<TimerEvent, TopTestApp>(this, &TopTestApp::OnTimerEvent),
            TimerEvent(20000));
        
    }
    void Terminate()
    {
        m_topSrv.Terminate();
        ComponentBase::Terminate();
    }
    int OnComponentEvent(TopologyEvent &event)
    {
        CLOG_NOTICE("Component event received %d", event.NotificationType());
        std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
        return 0;
    }
    int OnInstanceEvent(TopologyEvent &event)
    {
        CLOG_NOTICE("Instance event received %d", event.NotificationType());
        std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
        return 0;
    }
    int OnNodeEvent(TopologyEvent &event)
    {
        CLOG_NOTICE("Node event received %d", event.NotificationType());
        std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
        return 0;
    }
    int OnTimerEvent(TimerEvent &event)
    {
        CLOG_NOTICE("Unsubscribing Instance level events");
        m_topSrv.Unsubscribe(m_instEvhId);
        return 0;
    }
 protected:
    TopologyService m_topSrv;
    EventHandlerId  m_instEvhId;
    
    struct CmdArgs
    {
        CmdArgs()
            : compId("a", "compid", "Component Id requesting notification", "1"),
              instId("i", "instance", "Instance id which is to be monitored", "0")
        {
        }
        CmdOption<int>   compId;
        CmdOption<int>   instId;
    }m_cmdArgs;    
};

int main(int argc, char *argv[])
{
    TopTestApp app;
    try
    {
        app.Init(argc, argv);

        CLOG_NOTICE("Application initialized");

        app.Run();
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

    return 0;
}
