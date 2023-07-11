#include "Component.h"
#include "Timer.h"
#include <sys/stat.h>

#define TIMER_TEST_APP_ID  300

using namespace eAccelero;

const unsigned MAX_TIMERS = 80000;

struct TimerData
{
    TimeVal start;
    TimeVal end;
} s_data[MAX_TIMERS];

class TimerTestApp: public ComponentBase
{
 public:
    TimerTestApp()
        : ComponentBase("TimerTestApp", TIMER_TEST_APP_ID),
          m_tid(0),
          m_countTimers(0),
          m_expiredTimers(0)
    {

    }
    ~TimerTestApp()
    {
    }

    void Initialize()
    {
        ComponentBase::Initialize();

        if (!(bool)m_cmdArgs.load)
        {
            CLOG_NOTICE("Starting OneTime timer for 100ms");
            this->GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, TimerTestApp>(this, &TimerTestApp::OnOnceTimeout),
                    TimerEvent(100));
            CLOG_NOTICE("Starting Recurring timer for every 500ms");
            m_tid = this->GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, TimerTestApp>(this,
                        &TimerTestApp::OnRecurTimeout),
                    TimerEvent(500));
        }
        else
        {
            m_tid = this->GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, TimerTestApp>(this,
                    &TimerTestApp::StartTimers),
                    TimerEvent(100));
        }
    }

    void Terminate()
    {
        std::cout << "No of timers started: " << m_countTimers << std::endl;
        std::cout << "No of timers expired: " << m_expiredTimers << std::endl;
        if (!m_cmdArgs.load)
        {
            this->GetDispatcher()->RemoveEventHandler(TIMER_EVENT_TYPE, m_tid);
        }
        ComponentBase::Terminate();
    }

    int OnOnceTimeout(TimerEvent &ev)
    {
        CLOG_NOTICE("Onetime timer expired");
        return 0;
    }
    int OnRecurTimeout(TimerEvent &ev)
    {
        EACC_ASSERT(m_tid == ev.TimerId());
        CLOG_NOTICE("Recurring timer expired");
        return 1;
    }

    int StartTimers(TimerEvent &ev)
    {
        if (m_countTimers == MAX_TIMERS)
        {
            CLOG_NOTICE("All timers started.");
            return 0;
        }
        int tid;
        TimeVal start, end;
        start.now();
        // Everytime start 200 timers
        for (unsigned i = 0; i < MAX_TIMERS; i++)
        {
            tid = this->GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, TimerTestApp>(this,
                        &TimerTestApp::ExpiryTimer),
                    TimerEvent(2000));
            s_data[tid].start.now();
            m_countTimers++;
        }
        end.now();
        end -= start;
        std::cout << "Took " << end << std::endl;

        return 0;
    }

    int ExpiryTimer(TimerEvent &ev)
    {
        TimeVal diff;
        s_data[ev.TimerId()].end.now();
        diff = s_data[ev.TimerId()].end - s_data[ev.TimerId()].start;

        if ((diff.Truncate() - 2000) >= 100)
        {
            CLOG_WARNING("Drift more than 20ms %d %dms", ev.TimerId(), diff.Truncate());
        }
        m_expiredTimers++;

        return 0;
    }

 private:

    struct CmdArgs
    {
        CmdArgs()
            : load("L", "load", "Load with timers", "false")
        {
        }
        CmdOption<bool> load;
    }m_cmdArgs;
    EventHandlerId m_tid;
   
    unsigned m_countTimers;
    unsigned m_expiredTimers;
};

int main(int argc, char *argv[])
{
    TimerTestApp app;
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
