#include "Component.h"
#include "Signal.h"
#include <sys/stat.h>

#define SIGTEST_APP_ID  200

using namespace eAccelero;
static void daemonize(void)
{
    pid_t pid, sid;

    /* already a daemon */
    if ( getppid() == 1 ) return;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* At this point we are executing as the child process */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

#if 0
    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    /* Redirect standard files to /dev/null */
    freopen( "/dev/null", "r", stdin);
    freopen( "/dev/null", "w", stdout);
    freopen( "/dev/null", "w", stderr);
#endif
}

class SignalTestApp: public ComponentBase
{
 public:
    SignalTestApp()
        : ComponentBase("SignalTestApp", SIGTEST_APP_ID)
    {
    }
    ~SignalTestApp()
    {
    }

    void Initialize()
    {
        ComponentBase::Initialize();

        this->GetDispatcher()->AddEventHandler(
            EventSlot<SignalEvent, SignalTestApp>(this, &SignalTestApp::OnSigChld),
            SignalEvent(SIGCHLD));

        this->LaunchProcess();
    }

    void Terminate()
    {
        ComponentBase::Terminate();
    }

    int OnSigChld(SignalEvent &event)
    {
        CLOG_NOTICE("SIGCHLD received");
        CLOG_NOTICE("SigInfo \n"
                "   si_errno: %d\n"
                "   si_code : %d\n"
                "   si_pid  : %d\n"
                "   si_uid  : %d\n"
                "   si_status: 0x%x\n"
                "   si_utime: 0x%x\n"
                "   si_stime: 0x%x\n"
                ,event.SigInfo()->si_errno, event.SigInfo()->si_code,
                event.SigInfo()->si_pid, event.SigInfo()->si_uid, 
                event.SigInfo()->si_status, event.SigInfo()->si_utime, 
                event.SigInfo()->si_stime);
        switch (event.SigInfo()->si_code)
        {
            case CLD_EXITED:
                std::cout << "Child exited normally\n";
                break;
            case CLD_KILLED:
                std::cout << "Child was killed\n";
                break;
            case CLD_DUMPED:
                std::cout << "Child dumped core\n";
                break;
            case CLD_TRAPPED:
                std::cout << "Child trapped\n";
                break;
            // no need for CLD_STOPPED and CLD_CONTINUED, as we are not
            // monitoring for it
        }
        return 0;
    }

 private:
    void LaunchProcess()
    {
        const char *procName = ((std::string)m_cmdArgs.cldProcName).c_str();
        pid_t pid = fork();
        if (pid == 0)
        {
            int ret = 0;
            char args[256];
            const char *argv[32];
            char *ptr = NULL;
            strncpy(args, ((std::string)m_cmdArgs.cldArgs).c_str(), 256);
            args[255] = 0;

            int i = 0;
            argv[i++] = procName;
            char *token = strtok_r(args, " ", &ptr);
            while(token)
            {
                argv[i++] = token;
                token = strtok_r(NULL, " ", &ptr);
            }
            argv[i] = NULL;

            ret = execve(procName, (char * const*)argv, NULL);
            if (ret < 0)
            {
                CLOG_CRITICAL("Process <%s> launch failed <%d>", procName, errno); 
            }

            exit(-1);
        }
        else if (pid < 0)
        {
            CLOG_CRITICAL("Process <%s> launch failed <%d>", procName, errno); 
        }
    }

    struct CmdArgs
    {
        CmdArgs()
            : cldProcName("c", "child", "Launch Child process path", true),
              cldArgs("a", "args", "Child proc arguments")
        {
        }
        CmdOption<std::string> cldProcName;
        CmdOption<std::string> cldArgs;
    }m_cmdArgs;
    
};

int main(int argc, char *argv[])
{
    daemonize();
    SignalTestApp app;
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
