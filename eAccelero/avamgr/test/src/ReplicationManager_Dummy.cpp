#include "ReplicationManager_Dummy.h"

using namespace eAccelero;

class ReplicationManager_Dummy : public HAMeSSComponent {
public:

    //For the realistic component,
    //replace COMP_REPLICATION_MANAGER_DUMMY with COMP_REPLICATION_MANAGER (defined in ComponentDefines.h) &
    //replace I_REPLICATION_MANAGER_DUMMY with I_REPLICATION_MANAGER (defined in InterfaceDefines.h).
    ReplicationManager_Dummy()
    : HAMeSSComponent("ReplicationManager_Dummy", COMP_REPLICATION_MANAGER_DUMMY) {
    }

    void Initialize() {
        //The following line is a MUST.
        HAMeSSComponent::Initialize();

        //The following line is for the sample code.
        m_objRecurringTimerId = this->GetDispatcher()->AddEventHandler(
                EventSlot<TimerEvent, ReplicationManager_Dummy > (this,
                &ReplicationManager_Dummy::OnRecurringTimerExpiry),
                TimerEvent(PERIODICITY));

    }

    void Terminate() {
        this->GetDispatcher()->RemoveEventHandler(TIMER_EVENT_TYPE, m_objRecurringTimerId);

        //The following line is a MUST.
        HAMeSSComponent::Terminate();
    }

    void RegisterMethods() {
        //PLEASE INCLUDE METHODS YOU WANT TO REGISTER, HERE.
    }

    //The function is for the sample code.
    //However, an individual component MUST kill itself if it becomes orphan (parent process id == 1)-
    //this function shows an example of how to do it.
    int OnRecurringTimerExpiry(TimerEvent &ev) {
        
        if (getppid() == 1) {
            pid_t pid = getpid();
            CLOG_NOTICE("Process %d orphaned (not a daemon)... sending SIGKILL to itself for cleanup", pid);
            kill(pid, SIGKILL);
        }
        
        if (MeSSObj().Self().instance < MESS_MIN_STANDBY_INSTANCE) {
            CLOG_NOTICE("Self status is ACTIVE with instance id %u, component id %u",
                    MeSSObj().Self().instance,
                    MeSSObj().Self().compId);
        } else if (MeSSObj().Self().instance >= MESS_MIN_STANDBY_INSTANCE) {
            CLOG_NOTICE("Self status is STANDBY with instance id %u, component id %u",
                    MeSSObj().Self().instance,
                    MeSSObj().Self().compId);
        }

        return 1;
    }

private:
    EventHandlerId m_objRecurringTimerId;

};

int main(int argc, char *argv[]) {
    ReplicationManager_Dummy *app = NULL;
    try {
        app = new ReplicationManager_Dummy();

        app->Init(argc, argv);

        CLOG_NOTICE("Application initialized");

        app->Run();
    } catch (CmdParseException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    CLOG_NOTICE("Application exiting");

    if (app) delete app;

    return 0;
}

