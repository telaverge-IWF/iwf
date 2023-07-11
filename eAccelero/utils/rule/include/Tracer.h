/*********************************-*-H-*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************/
#ifndef __EACC_TRACER_H__
#define __EACC_TRACER_H__

#include <unordered_map>
#include <vector>


#include "Atomic.h"
#include "Rules.h"
#include "Timer.h"
#include "Ref.h"
#include "ThreadSpec.h"
#include "Sync.h"
#include "SockEvent.h"

/**
 * @file Tracer.h
 * 
 * Generic session tracing framework related code.
 * For more details refer @ref tracer_frame "Tracing framework".
 */
 
/**@mainpage Generic Session Tracing Framework
 *  - @ref tracer_frame "Generic Tracing Framework"
 *  - @ref rule_proc    "Rule Processing"
 *  - @ref expr_parser  "Expression Parsing"
 */
 
/**@page tracer_frame "Generic Tracing Framework"
 * @section tracer_intro Introduction
 * The generic tracing framework provides the following functionality
 *  - installation of trace filter rules ( @ref rule_proc "Rules")
 *  - evaluate the rules for a given message and find a match
 *  - trace object and macros to log the trace messages
 * 
 * @section tracer_rules Rules:
 * @subsection Rule Installation:
 * Rules are installed from a configuration file (json format). A sample config
 * file looks like this.
 * @code
 * { 
 *   // Enables/Disables the tracing
 *   "enable-tracing" : true,
 *
 *   // List of filter rules
 *   "filter-rules" : [
 *       { 
 *         "name" : "filter1",
 *         "id"   : 1,
 *         "priority": 1,
 *         "rule" : "dia.Request == 1 && dia.Command-Code == 272 &&
 *                   dia.Origin-Realm == regex('^inti.*com$')",
 *         "expiryDuration": 1000,
 *         "level": "info",
 *         "enabled": true
 *       },
 *       { 
 *         "name" : "filter2",
 *         "id"   : 2,
 *         "priority": 1,
 *         "rule" : "dia.Application-Id == 4 && 
 *                   dia.MSISDN == '919123456789'",
 *         "expiryMessages": 10,
 *         "level": "debug",
 *         "enabled": true
 *       }
 *   ]
 * }
 * @endcode
 * Most of the filter-rule fields are self explanatory. 
 *  - `expriyDuration` specifies the time in secs after which the rule expires
 *    and goes to disabled state.
 *  - `expiryMessages` field is used to specify the number of matched messages
 *    after which the rule is disabled automatically. 
 *  - `level` field mentions the log level upto which the messages will be 
 *     logged into the trace file.
 * 
 * Changes made to the configuration file is can be dynamically reloaded using a
 * reload script.
 * 
 * When a rule is removed and if a trace object was created for that rule, the
 * associated TraceObj is also removed and a callback is provided to the user to
 * remove any detail associated with the TraceObj. For this purpose, the tracer
 * has a Tracer::RegisterRuleRemovalCbk()
 * 
 * @subsection trace_rule_eval Rule Evaluation:
 * When a incoming message arrives and the Tracer is invoked to find if there is
 * a rule match among the installed rules. The Tracer used the RuleTable to
 * match the rule. Once a match is found, the matched rule Id and rule name is
 * provided to the caller. Also a trace object corresponding to the rule is 
 * created if it doesn't exists. This TraceObj is used to log the messages trace
 * messages into a file. For more details on how a rule is evaluated refer 
 * @ref rule_proc "Rule Processing".
 * 
 * @section trace_obj Trace Objects:
 * TraceObj is created to log the session trace messages into a file. This 
 * resuses the logging functionality from eAccelero:Logger. Tracer provides
 * methods to maintain the TraceObj for each thread. Once the trace object
 * is set to a thread, the utility macro function, get the current thread
 * trace object and if it is enabled, logs the trace. 
 * 
 * @section trace_impl Tracer Implementation:
 * The generic tracing framework maintains the following
 *  - table of TraceFilterRule (nothing but the rule configuration)
 *  - the RuleTable object (for rule processing)
 *  - table of TraceObj objects per rule
 *  - the RuleRuntime object to store the temporary results and pass the message
 *    to custom VarHandler
 */

namespace eAccelero
{

// Forward declarions required by the TraceObj
class Tracer;
class TraceFilterRule;

/**
 * @class TraceObj
 * @brief Object used to log the session trace 
 * 
 * Reuses the eAcceler::Logger object, for file tracing, log level and trace
 * format. This object is also reference counted as this is accessed across 
 * different modules. An user data can be associated with this tracer, so when
 * the tracer object is delted, a callback will be invoked to the user with the
 * user data.
 */
class TraceObj: public Logger, public RefObj<>
{
 public:
    /**
     * @brief Defatul constructor
     */
    TraceObj()
        : Logger("",true),
          m_ruleId(0)
    {
    }
    
    /**
     * @brief Constructs the TraceObj from the TraceFilterRule
     * @param rule  TraceFilterRule object for which the TraceObj to be created
     */
    TraceObj(TraceFilterRule& rule);

    /**
     * @brief Destructor that cleans up the file channel used
     */
    ~TraceObj()
    {
        if (m_channel)
        {
            delete m_channel;
        }
    }

    /**
     * Returns the rule id associated with the trace object
     */
    const uint16_t& RuleId() const
    {
        return m_ruleId;
    }
    
    /**
     * Returns the rule name assocaited with the trace object
     */
    const char* Name() const
    {
        return m_name.c_str();
    }

    /**
     * Returns the user data associated with the trace object
     */
    void* UserData()
    {
        return m_userData;
    }
    
    /**
     * Sets the user data for the trace object.
     */
    void UserData(void *data)
    {
        m_userData = data;
    }
    
    /**
     * Sets the protocol decoder that can decode the message octets.
     * (not used currently)
     */
    void SetProtoDecoder(LogProtoDecoder *decoder)
    {
        if (m_channel)
        {
            m_channel->RegisterProtoDecoder(decoder);
        }
    }
    unsigned int GetGeneration()
    {
        return m_generation;
    }

 protected:
    uint16_t m_ruleId;      /**< Rule id associated with the trace object */
    void* m_userData;       /**< User data set the user for the trace object 
                             *   used when the rule is removed   */
    unsigned int m_generation;//Required to identify ruleId after modify of filter
    static uint16_t m_currentGeneration;
};

/** Smart pointer associated with the Trace object. TraceRef should be used
 *  intsetad of a pointer to TraceObj where ever possible*/
typedef Reference<TraceObj> TraceRef;

/**
 * @class TraceFilterRule
 * @brief Stores the configuration values related to a Rule
 * 
 * In addition to storing the configuration of a Rule, this object maintains 
 *  - the status of the rule (enabled/disabled)
 *  - expiry timer in case the expiryDuration is specified
 *  - keeps count of the number of times, the rule is matched for expiryCalls 
 */
class TraceFilterRule
{
 public:
    static const int InvalidValue = -1;

    /**
     * @brief Constructor
     * @param ruleName       Name of the rule
     * @param ruleId         Unique identifcation for the rule
     * @param priority       Priority of the rule
     * @param expiryDuration Duration after which the rule will be disabled
     * @param expiryCalls    Number of matched calls after which the rule is 
     *                       disabled
     * @param level          Log level upto which the traces are logged
     * @param enabled        initial state of the rule (enabled/disabled)
     */
    TraceFilterRule(const char* ruleName,
            int ruleId, int priority,
            int expiryDuration = InvalidValue,
            int expiryCalls = InvalidValue,
            Logger::Level level = Logger::EACC_LOG_NOTICE,
            bool enabled = true);

    /**
     * Desctructor 
     */
    ~TraceFilterRule();

    /**
     * @brief Parses the expression as specified in the exprStr
     * @param exprStr   expression string to be parsed
     * 
     * The parsed result is stored internally as Expr
     */
    void ParseExpr(const char* exprStr);

    /**
     * Enables the rule, so that subsequent traces are logged 
     */
    void Enable();

    /**
     * Disables the rule, so that no traces are logged to this object
     */
    void Disable();

    /**
     * @brief Handles the expiryDuration timer posted from Dispatcher
     * @param ev    Timer event from the Dispatcher
     * @return Always returns TimerStopped so that it is not restarted
     */
    int OnTimerExpiry(TimerEvent &ev);

    std::string GetRuleName()
    {
        return m_name;
    }

    uint16_t GetRuleId()
    {
        return m_ruleId;
    }

    uint16_t GetPriority()
    {
        return m_priority;
    }

    int GetExpiryDuration()
    {
        return m_expiryDuration;
    }
    
    int GetExpiryCalls()
    {
        return m_expiryCalls;
    }

    Logger::Level GetLoglevel()
    { 
        return m_logLevel;
    }

    ExprRef GetRule()
    {
        return m_rule;
    }

    void SetRule(ExprRef& rule)
    {
        
        this->m_rule = rule;
    }

    bool GetTraceStatus()
    {
        return m_enabled;
    }
 protected:

    /**
     * @brief Does internal book keeping when a match is found
     * @param traceObj
     * @return True if the trace object is enabled else false
     * 
     * This is a hook invoked from the Tracer when a match is found. Does the 
     * following
     *  - Increments the number of calls (used for expiryMessages). If the 
     *    expiryMessages are reached, returns false
     *  - Creates a new TraceObj if there is no trace object associated with the
     *    rule
     */
    bool Matched(TraceRef &traceObj);

    std::string m_name;         /**< Rule name */
    uint16_t  m_ruleId;         /**< Unique id */
    uint16_t  m_priority;       /**< Priority of the rule */
    int  m_expiryDuration;      /**< Time after which the rule is disabled */
    int  m_expiryCalls;         /**< Matched messages after which rule is disabled */
    Logger::Level m_logLevel;   /**< Log level for the rule */

    ExprRef m_rule;             /**< Filter expression for the rule */

    bool m_enabled;             /**< Rule enabled/disabled */
    EventHandlerId m_timerId;   /**< Timer handle - started for expiryDuration */
    int m_msgCounter;           /**< Counter used for expiryMessages */

    /** Operations like message counting, disabling a rule, creating new trace
     *  object are made atomic to prevent race conditions. */
    Futex m_lock;               

    friend class Tracer;
    friend class TraceObj;
};



/**
 * @class Tracer
 * @brief Generic session tracing framework
 * 
 * Tracer is a singleton class that encapsulates the filter rule configuration,
 * rule processing and trace object creation to log the traces.
 */
class Tracer
{
 public:
    static const unsigned MAX_TRACE_FILTER_RULES = 32;
    static const char *DEFAULT_LOG_TRACE_PATH;
    
    /** 
     * @brief Rule removal callback that will be invoked on rule deletion
     * @param ruleId   - rule id that is getting removed
     * @param ruleData - is the userData associated with the rule
     * @param arg      - arguement passed when the callback was registered
     * @see RegisterRuleRemovalCbk
     */
    typedef void (*RuleRemovalCbk)(uint16_t ruleId, void *ruleData, void *arg);
    
    /**
     * @brief Creates and initializes the Tracer object
     * @param tracePath Trace path, where the rule filter traces are logged
     */
    static void Init(const char* tracePath);

    /**
     * @brief Destroys the Tracer object
     */
    static void Destroy();

    /**
     * Returns the singleton instance of Trace object 
     */
    static Tracer& Instance()
    {
        return *m_self;
    }

    /**
     * @brief Configures the trace object
     * @param confFileName  Configuration file name
     */
    void Configure(const char* confFileName);

    /**
     * @brief configure the trace object
     * @parm set from CLI or GUI
     */

    int Configure(int filterid, std::string& filtername,
                        std::string& rule, int priority, int expdur, int expmsg, int filtstatus, std::string loglevel);


    int ModifyTracer(std::string filtername, std::string rule, int priority, char *filtstatus, std::string loglevel, int expdur, int expmsg);

    void GetRuleStatus(std::string &filtername,std::map<std::string, int> &traceStatus);

    /**
     * @brief Adds a new trace filter rule
     * @param rule  trace filter rule to be added
     */
    int AddFilterRule(TraceFilterRule *rule);

    /**
     * @brief Remove the trace filter rule identified by rule name
     * @param name  rule to be removed
     */
    int RemoveFilterRule(std::string& name);

    /**
     * Enable system wide session tracing 
     */
    void Enable()
    {
        m_enabled = true;
    }
    /**
     * Disable system wide session tracing
     */
    void Disable()
    {
        m_enabled = false;
    }
    /**
     * Check if the session tracing is enabled or not
     */
    bool IsEnabled()
    {
        return m_enabled;
    }

    /**
     * @brief Given the message as userData, returns the matched rules
     * @param [in]  userData  Message passed as a userData
     * @param [out] traceObj  Trace object for the matched rule
     * @return True if a filter match is found, otherwise returns false
     * 
     * If no rule is matched, the traceObj will be NULL.
     */
    bool Filter(void *userData, TraceRef &traceObj);

    /**
     * @brief Enable a rule by the rule name
     * @param filterName    Rule to be enabled
     * @see Tracer::DisableRule()
     * 
     * If the rule is not enabled already, this method add the Rule object to
     * the RuleTable.
     */
    void EnableRule(std::string &filterName);

    /**
     * @brief Disable a rule by the rule name
     * @param filterName    Rule to be disabled
     * @see Tracer::EnableRule()
     * 
     * When a rule is disabled, the internal Rule object is removed from the
     * RuleTable, so that is it no longer included for filter match.
     */
    void DisableRule(std::string &filterName);

    /**
     * @brief Register the callback that will be invoked when a Rule is removed
     * @param cbk   Callback function
     * @param arg   Argument associated with the callback function
     */
    void RegisterRuleRemovalCbk(RuleRemovalCbk cbk, void *arg = NULL);

    /**
     * @brief Invokes the rule reomoval callback registered
     * @param ruleId    Rule id that is getting deleted
     * @param ruleUserData  User data associated with the rule
     */
    void InvokeRuleRemovalCbk(uint16_t ruleId, void *ruleUserData)
    {
        if (m_disableCbk)
        {
            (*m_disableCbk)(ruleId, ruleUserData, m_disableCbkArg);
        }
    }

    /**
     * @brief Remove the Rule from internal RuleTable
     * @param ruleId    Rule id to be removed
     * @param priority  priority of the rule to be removed
     * 
     * This does not remove the filter rule from Tracer. It removes only from
     * the RuleTable
     */
    void RemoveFromRuleTable(uint16_t ruleId, uint16_t priority)
    {
        m_rules.RemoveRule(ruleId, priority);
    }

    /**
     * Returns the configured trace path, where the traces will be dumped 
     */
    const char* TracePath() const
    {
        return m_tracePath.c_str();
    }

    /**
     * Returns the thread specific TraceObj 
     */
    static TraceObj* ThreadTraceObj()
    {
        // Should be assigned with a valid obj before calling this
        return m_thrTraceObj;
    }
    
    /**
     * Sets the TraceObj specific to the thread
     */
    static void ThreadTraceObj(TraceObj* obj)
    {
        m_thrTraceObj = obj;
    }
    
    /**
     * Checks if the thread has a TraceObj set.
     */
    static bool IsThreadTraceable()
    {
        return (m_thrTraceObj.GetData() != NULL);
    }

    /**
     * @brief Gets the trace object given the rule id
     * @param ruleId    Rule id for which the trace object to be obtained
     * @return Trace object for the given rule id
     */
    TraceObj* GetTraceObj(uint16_t ruleId)
    {
        return m_traceObjs[ruleId];
    }
    
    /**
     * @brief Sets the trace object for the rule id
     * @param ruleId    Rule id for which the trace object to be set
     * @param obj       Trace object
     */
    void SetTraceObj(uint16_t ruleId, TraceObj* obj)
    {
        m_traceObjs[ruleId] = obj;
    }

    /**
     * @brief Register the custom VarHandler
     * @param str       prefix that identfies the custom protocol
     * @param handler   VarHandler object that interprets the protocol variables
     */
    void RegisterVarHandler(const char *str, VarHandler *handler)
    {
        m_rules.RegisterVarHandler(str, handler);
    }

    /**
     * Cleanup the thread specific data in the main thread. Not required for other
     * threads.
     */
    static void MainCleanup()
    {
        RuleRuntime* rt = m_rt.GetData();
        if (rt != 0)
        {
            delete rt;
            m_rt = NULL;
        }
    }

    /**
     * Clears the filter rules installed in the Tracer 
     */
    void Flush();

    /**
     * @brief Utility function that get ths loglevel id given the level string
     * @param levelStr  log level as a string
     * @return Log level in integer
     */
    Logger::Level GetLogLevel(std::string levelStr);

    /**
     * @brief Handler for config reload socket event
     * @param event
     * @return Always returns success
     * 
     * Config reload is implemented uisng Unix domain sockets.
     */
    int OnSockEvent(SockEvent &event);

    // TODO have a protoco specific message tracer

    // TODO an iterator to iterate all the filter rules

 protected:
    typedef std::unordered_map<std::string, TraceFilterRule*> RuleFilterMap;
 
    /**
     * @brief Constructor
     * @param tracePath     Path where the trace logs will be written to
     */
    Tracer(const char* tracePath);
    
    /**
     * @brief Desctructor
     */
    ~Tracer();

    /**
     * @brief Given the expression parses it into an Expr tree
     * @param exprStr   Expression string
     * @return Expression tree object
     */
    ExprRef ParseExpr(std::string& exprStr);

    bool      m_enabled;        /**< Enable/disable tracing*/

    RuleFilterMap m_table;      /**< Rule filter table */
    RWLock        m_tableLock;  /**< Lock for the rule filter table */

    RuleTable m_rules;          /**< Rule processing table */

    std::vector<TraceRef> m_traceObjs; /**< Table of trace objects */
    std::string m_tracePath;        /**< Path to which trace will be logged */

    RuleRemovalCbk m_disableCbk;    /**< Callback called on Rule removal */
    void*          m_disableCbkArg; /**< Arugument that will be passed to cbk */

    std::string    m_confFileName;  /**< Rule configuration file name */
    Socket         m_reloadSock;    /**< Config Reload will be sent to this */
    EventHandlerId m_reloadEvh;     /**< Socket event handle for reload */

    static Tracer *m_self;          /**< Singleton tracer object */
    static ThreadSpec<RuleRuntime> m_rt;    /**< Thread specific runtime obj */

    static ThreadSpec<TraceObj> m_thrTraceObj; /**< Thread specific trace obj */

    /** Map that is used to convert log level stringto integer */
    static std::map<std::string, Logger::Level> m_logMap;
};



// Starts with level, format and var args
#define EACC_SESS_TRACE(...)   \
    eAccelero::Tracer::Instance().IsEnabled()  && \
        eAccelero::Tracer::IsThreadTraceable() ? \
            EACC_LOG((*eAccelero::Tracer::ThreadTraceObj()), __VA_ARGS__) : 0

#define EACC_PROTO_TRACE(...) \
    EACC_SESS_TRACE(eAccelero::Logger::EACC_LOG_NOTICE,  __VA_ARGS__);

// This is a TODO
#if 0
#define EACC_PROTO_TRACE(_proto, _src, _dest, _bytes, _len) \
  eAccelero::Tracer::Instance().IsEnabled() && \
    eAccelero::Tracer::IsThreadTraceable() ? \
      eAccelero::Tracer::LogProtoTrace(_proto, _src, _dest, _bytes, _len) : 0
#endif   

// Override the Logging macro with this one.
// This will log and also trace
#ifdef SUB_COMP_LOG
#   undef  SUB_COMP_LOG
#   define SUB_COMP_LOG(_level, ...) \
      EACC_LOG((*(eAccelero::Logger::currLogger.GetData())), _level,__VA_ARGS__); \
      EACC_SESS_TRACE(_level, __VA_ARGS__)
#endif

} // namespace eAccelero

#endif // __EACC_TRACER_H__
