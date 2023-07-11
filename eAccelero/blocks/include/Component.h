#ifndef __EACC_Component_h__
#define __EACC_Component_h__

#include "Logger.h"
#include "Exception.h"
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <vector>
#include "Dispatcher.h"
#include "Signal.h"

namespace eAccelero
{

class CmdParser;
class ComponentBase;

EACC_DEFINE_EXCEPTION_CLASS(CmdParseException, Exception, "Command Parser Exception");

class CmdOptionBase
{
 public:
    CmdOptionBase(const char *shortOpt, const char *longOpt, 
                  const char *descr, bool required = false)
        : m_shortOpt(shortOpt),
          m_longOpt(longOpt),
          m_descr(descr),
          m_required(required),
          m_parsed(false),
          m_argRequired(true)
    {
    }
    CmdOptionBase(const char *shortOpt, const char *longOpt, 
                  const char *descr, const char *defaultStr = "")
        : m_shortOpt(shortOpt),
          m_longOpt(longOpt),
          m_descr(descr),
          m_default(defaultStr),
          m_required(false),
          m_parsed(false),
          m_argRequired(true)
    {
    }
    virtual ~CmdOptionBase() {}
    virtual void SetVal(const char *str) = 0;
    
 protected:
    friend class CmdParser;

    std::string m_shortOpt;
    std::string m_longOpt;
    std::string m_descr;
    std::string m_default;
    bool m_required;
    bool m_parsed;
    bool m_argRequired;
};

class CmdParser
{
 public:
    CmdParser()
    {
    }
    ~CmdParser()
    {
    }
    void AddOption(CmdOptionBase *opt);

    void Parse(int argc, char *argv[]);

    std::string Help();

    static CmdParser& Instance()
    {
        return m_instance;
    }
 
 private:
    typedef std::map<std::string, CmdOptionBase*> CmdMap;
    CmdMap m_shortOptMap;
    CmdMap m_longOptMap;

    static CmdParser m_instance;
};

template <typename T>
class CmdOption: public CmdOptionBase
{
 public:    
     CmdOption(const char *shortOpt, const char *longOpt, 
               const char *descr, bool required = false)
         : CmdOptionBase(shortOpt, longOpt, descr, required)
     {
         CmdParser::Instance().AddOption(this);
         if (typeid(T) == typeid(bool))
         {
             m_argRequired = false;
         }
     }

     CmdOption(const char *shortOpt, const char *longOpt, 
               const char *descr, const char *defaultStr)
         : CmdOptionBase(shortOpt, longOpt, descr, defaultStr)
     {
         CmdParser::Instance().AddOption(this);
         if (typeid(T) == typeid(bool))
         {
             m_argRequired = false;
         }
     }
    
    ~CmdOption()
    {
    }

    void SetVal(const char *str);

    operator const T&() const
    {
        return m_val;
    }

 private:
    T m_val;
};

// Specialize the SetVal function for int, string and bool
// Bool options are assumed to be without arguments
template <>
inline void CmdOption<int>::SetVal(const char *str)
{
    m_val = atoi(str);
}
template <>
inline void CmdOption<std::string>::SetVal(const char *str)
{
    m_val = std::string(str);
}
template <>
inline void CmdOption<bool>::SetVal(const char *str)
{
    if (str == NULL)
    {
        // when the option is given in command line
        m_val = true;
    }
    else
    {
        // to handle default option
        m_val = (strcmp(str, "true") == 0) ? true: false;
    }
}

class Subcomponent
{
 public:
    Subcomponent(const char *name, unsigned id)
        : m_name(name),
          m_id(id)
    {
    }
    virtual ~Subcomponent()
    {
    }
    const char* Name() const
    {
        return m_name.c_str();
    }
    const unsigned Id() const
    {
        return m_id;
    }

    virtual void Initialize() = 0;
    virtual void Terminate()  = 0;
    // TODO Config set and get
 
 protected:
    std::string m_name;
    unsigned    m_id;
};

EACC_DEFINE_EXCEPTION_CLASS(ComponentException, Exception, "Component Exception")
// Args are log_level, descr, errCode
#define ComponentExceptionLog(_level, _descr, ...) \
            GEN_EXCEPTION_LOG(eAccelero::ComponentException,\
                              _descr,\
                              &eAccelero::ComponentBase::Instance().GetLogger(),\
                              _level,\
                              ##__VA_ARGS__)

class Dispatcher;

// Application can dervice from this.
// Provides basic infrastructure for an application to run
class ComponentBase: public Subcomponent
{
 public:
    static ComponentBase& Instance()
    {
        return *m_instance;
    }

    void Init(int argc, char *argv[]);

    virtual void Initialize();

    virtual void Terminate();

    // For application running on EventDispatcher
    virtual void Run();

    // Triggers the shutdown of the application
    void Stop();

    unsigned& Running();

    Logger& GetLogger();

    void RegisterSubcomponent(Subcomponent *sub);

    Dispatcher* GetDispatcher();

    // Signal Handlers
    virtual int OnSigInt(SignalEvent &event);

    virtual int OnSigCrash(SignalEvent &event);

 protected:
    // To be called by the subclass
    ComponentBase(const char *name, unsigned id);
    virtual ~ComponentBase();
    static ComponentBase* m_instance;
    
 private:
    Logger      m_logger;

    bool m_initialized;
    volatile unsigned m_running;

    // Can add various subsystems, on each, we can call init/destroy etc...
    // Ownership of subcomponet is with Component
    typedef std::vector<Subcomponent*> SubcomponentList;
    typedef std::unordered_map<unsigned, Subcomponent*> SubcomponentHash;
    SubcomponentList m_subComponentList;
    SubcomponentHash m_subComponentHash;

    Dispatcher *m_dispatcher;

    struct CmdArgs
    {
        CmdArgs()
          : logLevel("l", "log-level", "Log level <0-6>", "3")
        {
        }
        CmdOption<int> logLevel;
    }m_cmdArgs;
};

#define COMP_LOG(_level, ...) \
    EACC_LOG(eAccelero::ComponentBase::Instance().GetLogger(), _level, __VA_ARGS__)

#define CLOG_FATAL(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_FATAL, __VA_ARGS__)

#define CLOG_CRITICAL(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_CRITICAL, __VA_ARGS__)

#define CLOG_ERROR(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_ERROR, __VA_ARGS__)

#define CLOG_WARNING(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_WARNING, __VA_ARGS__)

#define CLOG_NOTICE(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_NOTICE, __VA_ARGS__)

#define CLOG_INFO(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_INFO, __VA_ARGS__)

#define CLOG_DEBUG(...) \
    COMP_LOG(eAccelero::Logger::EACC_LOG_DEBUG, __VA_ARGS__)

inline Logger& ComponentBase::GetLogger()
{
    return m_logger;
}

inline Dispatcher* ComponentBase::GetDispatcher()
{
    return m_dispatcher;
}

inline void ComponentBase::RegisterSubcomponent(Subcomponent *sub)
{
    CLOG_DEBUG("Registering subcomponent %s:%d", sub->Name(), sub->Id());
    SubcomponentHash::iterator it = m_subComponentHash.find(sub->Id());
    if (it == m_subComponentHash.end())
    {
        m_subComponentHash[sub->Id()] = sub;
    }
    else
    {
        throw ComponentExceptionLog(Logger::EACC_LOG_FATAL, "Duplicate Subcomponent Id");
    }

    m_subComponentList.push_back(sub);
}

} // namespace eAccelero

#endif // __EACC_Component_h__
