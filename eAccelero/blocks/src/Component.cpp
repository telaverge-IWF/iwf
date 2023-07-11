#include <Component.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include "Dispatcher.h"
#include "SockEvent.h"
#include "Timer.h"
#include "ThreadSpec.h"

#include <execinfo.h>

namespace eAccelero
{

CmdParser CmdParser::m_instance;
ComponentBase* ComponentBase::m_instance = NULL;

void CmdParser::AddOption(CmdOptionBase *opt)
{
    if (m_shortOptMap.find(opt->m_shortOpt) != m_shortOptMap.end())
    {
        throw CmdParseException("Unable to add short option. Already present!");
    }
    if (m_longOptMap.find(opt->m_longOpt) != m_longOptMap.end())
    {
        throw CmdParseException("Unable to add long option. Already present!");
    }
    m_shortOptMap[opt->m_shortOpt] = opt;
    m_longOptMap[opt->m_longOpt] = opt;
}

std::string CmdParser::Help()
{
    std::stringstream ostr;

    ostr << "OPTIONS:\n";
    for (CmdMap::iterator it = m_shortOptMap.begin();
         it != m_shortOptMap.end(); it++)
    {
        ostr <<  "-" << (*it).second->m_shortOpt
             << std::left << ", --" << std::setw(20) << (*it).second->m_longOpt;
        ostr << (*it).second->m_descr;
        if (!(*it).second->m_default.empty())
        {
             ostr <<  " [Default: " << (*it).second->m_default << "]";
        }
        if ((*it).second->m_required)
        {
            ostr << " [Required]";
        }
        ostr << std::endl;
    }
    return ostr.str();
}

void CmdParser::Parse(int argc, char *argv[])
{
    int i = 0;
    CmdOptionBase *cmdOpt = NULL;
    CmdMap::iterator itCmd;
    char tempOpt[256];
    bool found = false;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            throw CmdParseException("Invalid option, missing -");
        }

        if (argv[i][1] == '-')
        {
            // Long option provided, search in longOptMap
            strncpy(tempOpt, argv[i]+2, 256);
            tempOpt[255] = '\0';
            itCmd = m_longOptMap.find(std::string(tempOpt));
            found = (itCmd != m_longOptMap.end());
        }
        else
        {
            strncpy(tempOpt, argv[i]+1, 256);
            tempOpt[255] = '\0';
            itCmd = m_shortOptMap.find(std::string(tempOpt));
            found = (itCmd != m_shortOptMap.end());
        }

        if (!found)
        {
            throw CmdParseException("Unknown option");
        }
        cmdOpt = itCmd->second;

        if (cmdOpt->m_argRequired)
        {
            if (argc <= (i+1))
            {
                throw CmdParseException("Argument required");
            }
            cmdOpt->SetVal(argv[i+1]);
            i++;
        }
        else
        {
            cmdOpt->SetVal(NULL);
        }
        cmdOpt->m_parsed = true;
    }

    for (CmdMap::iterator it = m_shortOptMap.begin();
         it != m_shortOptMap.end(); it++)
    {
        cmdOpt = (*it).second;
        if (cmdOpt->m_required && !(cmdOpt->m_parsed))
        {
            throw CmdParseException("Missing mandatory arguments");
        }
        // Set the default values if present and not parsed
        if (!(cmdOpt->m_parsed) && !cmdOpt->m_default.empty())
        {
            cmdOpt->SetVal(cmdOpt->m_default.c_str());
        }
    }
}

ComponentBase::ComponentBase(const char *name, unsigned id)
    : Subcomponent(name, id),
      m_logger(name),
      m_initialized(false),
      m_running(0)
{
    m_instance = this;

    // Set the current logger to Component logger by default
    Logger::currLogger = &m_logger;

    // Register me as a subcomponent of myself
    this->RegisterSubcomponent(this);
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::Init(int argc, char *argv[])
{
    CmdParser::Instance().Parse(argc, argv);

    m_logger.SetLevel((Logger::Level)(int)m_cmdArgs.logLevel);

    this->Initialize();

    // Probably the Application class has not called
    // ComponentBase::Initialize() from its Initialize(0
    EACC_ASSERT(m_dispatcher);

    m_initialized = true;
}

void ComponentBase::Stop()
{
    // Don't call this function from a signal handler
    m_running = 0;

    this->Terminate();
#if 0
    // Go in the reverse order of registration and terminate the components
    for(SubcomponentList::reverse_iterator it = m_subComponentList.rbegin();
        it != m_subComponentList.rend(); )
    {
        Subcomponent *sub = *it;
        sub->Terminate();
        m_subComponentHash.erase(sub->Id());

        // Get the iterator for the reverse iterator and remove
        m_subComponentList.erase((++it).base());

        // Hey! don't delete me
        if (sub != this)
        {
            delete sub;
        }
    }
#endif
    m_initialized = false;
}

void ComponentBase::Run()
{
    m_dispatcher->Run();
    this->Stop();
}

void ComponentBase::Initialize()
{
    m_dispatcher = new Dispatcher();
    m_dispatcher->RegisterNotifier(SIGNAL_EVENT_TYPE, new SignalEventNotifier());
    m_dispatcher->RegisterNotifier(SOCK_EVENT_TYPE, new SockEventNotifier());
    m_dispatcher->RegisterNotifier(TIMER_EVENT_TYPE, new TimerWheel());

    // Install signal handlers
    m_dispatcher->AddEventHandler(
           EventSlot<SignalEvent, ComponentBase>(this, &ComponentBase::OnSigInt),
           SignalEvent(SIGINT));
    m_dispatcher->AddEventHandler(
           EventSlot<SignalEvent, ComponentBase>(this, &ComponentBase::OnSigInt),
           SignalEvent(SIGTERM));
    m_dispatcher->AddEventHandler(
           EventSlot<SignalEvent, ComponentBase>(this, &ComponentBase::OnSigCrash),
           SignalEvent(SIGSEGV));
    m_dispatcher->AddEventHandler(
           EventSlot<SignalEvent, ComponentBase>(this, &ComponentBase::OnSigCrash),
           SignalEvent(SIGABRT));
    m_dispatcher->AddEventHandler(
           EventSlot<SignalEvent, ComponentBase>(this, &ComponentBase::OnSigCrash),
           SignalEvent(SIGILL));
    m_dispatcher->AddEventHandler(
           EventSlot<SignalEvent, ComponentBase>(this, &ComponentBase::OnSigCrash),
           SignalEvent(SIGBUS));

    for(SubcomponentList::iterator it = m_subComponentList.begin();
        it != m_subComponentList.end(); it++)
    {
        // I'am already initialized, don't Initialize me again
        if (*it != this)
            (*it)->Initialize();
    }

}

void ComponentBase::Terminate()
{
    // Go in the reverse order of registration and terminate the components
    for(SubcomponentList::reverse_iterator it = m_subComponentList.rbegin();
        it != m_subComponentList.rend(); )
    {
        Subcomponent *sub = *it;
        if (sub != this)
        {
            sub->Terminate();
            m_subComponentHash.erase(sub->Id());
            // Get the iterator for the reverse iterator and remove
            m_subComponentList.erase((++it).base());

            delete sub;
        }
        else
        {
            m_subComponentHash.erase(sub->Id());
            // Get the iterator for the reverse iterator and remove
            m_subComponentList.erase((++it).base());
        }
    }
    delete m_dispatcher;
    m_dispatcher = NULL;
}

static void UContextToStr(siginfo_t *info, ucontext_t *ctxt, std::string &str);

int ComponentBase::OnSigInt(SignalEvent &event)
{
    m_dispatcher->m_exitCause = eAccelero::Dispatcher::SIGTERM_SIGINT_EXIT;

    m_dispatcher->Stop();

    return 0;
}

int ComponentBase::OnSigCrash(SignalEvent &event)
{
    m_dispatcher->RemoveEventHandler(SIGNAL_EVENT_TYPE, SIGSEGV);
    m_dispatcher->RemoveEventHandler(SIGNAL_EVENT_TYPE, SIGABRT);
    m_dispatcher->RemoveEventHandler(SIGNAL_EVENT_TYPE, SIGILL);
    m_dispatcher->RemoveEventHandler(SIGNAL_EVENT_TYPE, SIGBUS);

    CLOG_FATAL("FATAL error! Process Crash!");

    std::string str;
    UContextToStr(event.SigInfo(), event.UContext(), str);
    std::cerr << str << std::endl;

    abort();

    return 0;
}

#if __WORDSIZE == 64
static const char* _regStr[NGREG] = {
    "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15",
    "RDI", "RSI", "RBP", "RBX", "RDX", "RAX", "RCX", "RSP", "RIP",
    "EFL", "CSG", "ERR", "TRP", "OMS", "CR2"
};
#else // __WORDSIZE == 64
static const char* _regStr[NGREG] = {
    "GS ", "FS ", "ES ", "DS ",
    "EDI", "ESI", "EBP", "ESP", "EBX", "EDX", "ECX", "EAX",
    "TRP", "ERR", "EIP", "CS ", "EFL", "UES", "SS "
};

#endif // __WORDSIZE == 64

void UContextToStr(siginfo_t *info, ucontext_t *ctxt, std::string &str)
{
    std::stringstream ostr;

    ostr << "Signal: " << info->si_signo << " " << strsignal(info->si_signo) << std::endl;
    if (info->si_signo == SIGSEGV || info->si_signo == SIGBUS)
    {
        ostr << "Fault address: 0x" << std::hex << info->si_addr << std::endl;
    }
    ostr << "si_code: " << info->si_code << std::endl;

    ostr << "Registers: \n";
    for(int i = 0; i < NGREG; i++)
    {
        ostr << std::hex << _regStr[i]
             << ": 0x" << std::left << std::setw(16)
             << ctxt->uc_mcontext.gregs[i] << std::setw(0);
        if ((i+1) % 3 == 0)
        {
            ostr << "\n";
        }
    }

    // addr2line -f -C -s -p -e <binary> addresses
    ostr << "\nBacktrace:\n";
    const int SIZE = 32 + 5;
    int nptrs = 0;
    void *buf[SIZE];
    char **strings;
    nptrs = backtrace(buf, SIZE);
    strings = backtrace_symbols(buf, nptrs);
    for(int i = 5; i < nptrs; i++)
    {
        ostr << strings[i] << std::endl;
    }
    free(strings);

    str = ostr.str();
}

} // namespace eAccelero
