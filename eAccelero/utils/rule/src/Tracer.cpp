/*********************************-*CPP*-************************************
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

#include <fstream>
#include <json/json.h>
#include "Tracer.h"
#include "Component.h"
#include "ErrorResp.h"

namespace eAccelero
{
const char* Tracer::DEFAULT_LOG_TRACE_PATH = "/opt/diametriq/dre/log/trace";
uint16_t TraceObj::m_currentGeneration = 1;

Tracer* Tracer::m_self = NULL;
ThreadSpec<RuleRuntime> Tracer::m_rt;
ThreadSpec<TraceObj> Tracer::m_thrTraceObj;

std::map<std::string, Logger::Level> Tracer::m_logMap;

TraceFilterRule::TraceFilterRule(const char* ruleName, int ruleId, 
        int priority, int expiryDuration, int expiryCalls,
        Logger::Level level, bool enabled)
    : m_name(ruleName),
      m_ruleId(ruleId),
      m_priority(priority),
      m_expiryDuration(expiryDuration),
      m_expiryCalls(expiryCalls),
      m_logLevel(level),
      m_enabled(enabled),
      m_timerId((unsigned)InvalidValue),
      m_msgCounter(0)
{
}

TraceFilterRule::~TraceFilterRule()
{
    this->Disable();
}

void TraceFilterRule::ParseExpr(const char* exprStr)
{
    Lexer lex;
    ExprParser parser;
    lex.Tokenize((char*)exprStr);

    m_rule = parser.Parse(&lex);
}

void TraceFilterRule::Enable()
{
    Futex::ScopedFutex lock(m_lock);

    m_enabled = true;
    if (m_expiryDuration != InvalidValue)
    {
        // if the filter is already enabled, re-enable will cause the timer to
        //   restart again
        if (m_timerId != (unsigned)InvalidValue)
        {
            ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(
                    TIMER_EVENT_TYPE, m_timerId);
            m_timerId = (unsigned)InvalidValue;
        }
        m_timerId = ComponentBase::Instance().GetDispatcher()->AddEventHandler(
                        EventSlot<TimerEvent, TraceFilterRule>(this,
                                &TraceFilterRule::OnTimerExpiry), 
                        TimerEvent(m_expiryDuration * TimeVal::MS_PER_SEC));
    }
    m_msgCounter = 0;

    if (Tracer::Instance().GetTraceObj(m_ruleId))
    {
        Tracer::Instance().GetTraceObj(m_ruleId)->SetLevel(m_logLevel, true);
    }
}

void TraceFilterRule::Disable()
{
    Futex::ScopedFutex lock(m_lock);

    m_enabled = false;

    if (m_timerId != (unsigned)InvalidValue)
    {
        ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(
                        TIMER_EVENT_TYPE, m_timerId);
        m_timerId = (unsigned)InvalidValue;
    }
    m_msgCounter = 0;

    // Disable the log from getting printed
    if (Tracer::Instance().GetTraceObj(m_ruleId))
    {
        Tracer::Instance().GetTraceObj(m_ruleId)->SetLevel(Logger::EACC_LOG_FATAL, false);
    }
    //CLOG_INFO("Trace Filter <%s> disabled", m_name.c_str());
}

int TraceFilterRule::OnTimerExpiry(TimerEvent &ev)
{
    // Filter Disable and remove from rule table goes together
    this->Disable();
    Tracer::Instance().RemoveFromRuleTable(m_ruleId, m_priority);

    CLOG_INFO("Trace Filter <%s> stopped due to timeout", m_name.c_str());

    return TimerEvent::TimerStopped;
}

bool TraceFilterRule::Matched(TraceRef& traceObj)
{
    Futex::ScopedFutex lock(m_lock);

    m_msgCounter++;
    if ((m_expiryCalls != InvalidValue) && (m_msgCounter > m_expiryCalls))
    {
        // Disable the tracing, from the next call onwards
        lock.unlock();
        Tracer::Instance().DisableRule(m_name);
        return false;
    }

    traceObj = Tracer::Instance().GetTraceObj(m_ruleId);
    if (!traceObj)
    {
        // Create a new trace object
        traceObj = new TraceObj(*this);
        Tracer::Instance().SetTraceObj(m_ruleId, traceObj);
    }
    return true;
}

TraceObj::TraceObj(TraceFilterRule& rule)
  : Logger(rule.m_name.c_str(),true),
    m_ruleId(rule.m_ruleId)
{
    LogChannel* channel = new FileLogChannel(rule.m_name.c_str(),
                                Tracer::Instance().TracePath());
    this->SetLevel(rule.m_logLevel, true);
    this->SetLogChannel(channel,true);
    this->m_userData = NULL;
    m_generation = m_currentGeneration++;
}

void Tracer::Init(const char* tracePath)
{
    // Initialize the logmap
    /*
    m_logMap["fatal"] = Logger::EACC_LOG_FATAL;
    m_logMap["critical"] = Logger::EACC_LOG_CRITICAL;
    m_logMap["error"] = Logger::EACC_LOG_ERROR;
    m_logMap["warning"] = Logger::EACC_LOG_WARNING;
    m_logMap["notice"]  = Logger::EACC_LOG_NOTICE;
    m_logMap["info"] = Logger::EACC_LOG_INFO;
    m_logMap["debug"] = Logger::EACC_LOG_DEBUG;
    */
    m_logMap["1"] = Logger::EACC_LOG_FATAL;
    m_logMap["2"] = Logger::EACC_LOG_CRITICAL;
    m_logMap["3"] = Logger::EACC_LOG_ERROR;
    m_logMap["4"] = Logger::EACC_LOG_WARNING;
    m_logMap["5"]  = Logger::EACC_LOG_NOTICE;
    m_logMap["6"] = Logger::EACC_LOG_INFO;
    m_logMap["7"] = Logger::EACC_LOG_DEBUG;
    
    m_self = new Tracer(tracePath);
}
void Tracer::Destroy()
{
    if (m_self)
    {
        delete m_self;
        m_self = NULL;
    }
}

#define UNIX_SOCK_ADDR "/tmp/eacc_tracer_reloader"

Tracer::Tracer(const char* tracePath)
    : m_enabled(false),
      m_traceObjs(MAX_TRACE_FILTER_RULES),
      m_tracePath(tracePath),
      m_disableCbk(NULL),
      m_disableCbkArg(NULL),
      m_reloadEvh((unsigned)TraceFilterRule::InvalidValue)
{
}

Tracer::~Tracer()
{
    for (RuleFilterMap::iterator it = m_table.begin(); it != m_table.end();)
    {
        delete it->second;
        m_table.erase(it++);
    }
    if (m_reloadEvh != (unsigned)(TraceFilterRule::InvalidValue))
    {
        ComponentBase::Instance().GetDispatcher()->RemoveEventHandler(
                            SOCK_EVENT_TYPE, m_reloadEvh);
    }
}

int Tracer::Configure(int filterid, std::string& filtername,
                        std::string& Rule, int priority, int expdur, int expmsg, int filtstatus, std::string loglevel)
{
    TraceFilterRule *rule = NULL;
    Logger::Level logLevel;
    int retVal = 0; //assuming it as a success case
    CLOG_DEBUG("Values to be Added Filtername : %s, Rule : %s, priority : %d, expdur : %d, expmsg : %d, filtstatus : %d, loglevel : %s",filtername.c_str(), Rule.c_str(), priority, expdur, expmsg, filtstatus, loglevel.c_str());
    try
    {
        logLevel = this->GetLogLevel(loglevel.c_str());
        rule = new TraceFilterRule(filtername.c_str(),
                filterid, priority, 
                expdur,expmsg,
                logLevel,
                filtstatus);

    rule->ParseExpr(Rule.c_str());

    retVal = this->AddFilterRule(rule);
    }
    catch(ParserException& exp)
    {
        // Log the exception and continue with the next rule 
        CLOG_ERROR("Parser exception thrown for rule <%s>: %s", 
                filtername.c_str(), exp.what());
        delete rule;
        rule = NULL;
        retVal = SET_TRACECONFIG_ERR_PARSING_RULE_FAILED;
    }
    catch(RuleException ruleExp)
    {
        CLOG_ERROR("Filter Rule exception:%s",ruleExp.what());
    }
        
    return retVal;

}

int Tracer::ModifyTracer(std::string filtername, std::string Rule, int priority, char *filtstatus, std::string loglevel, int expdur, int expmsg)
{
    TraceFilterRule *rule;
    Logger::Level logLevel;
    int rule_flag = 0;
    int retVal = 0; //assuming it as a success case
    CLOG_DEBUG("Values to be Modified Filtername : %s, Rule : %s, priority : %d, expdur : %d, expmsg : %d, filtstatus : %s, loglevel : %s",filtername.c_str(), Rule.c_str(), priority, expdur, expmsg, filtstatus, loglevel.c_str());
   
    CLOG_DEBUG("filtername = %s",filtername.c_str());
    RuleFilterMap::iterator it = m_table.find(filtername.c_str());
    if (it == m_table.end())
    {
        CLOG_ERROR("Rule entry %s to be modified is not found",filtername.c_str());
        return MOD_TRACECONFIG_ERR_FILTER_WITH_FILTER_NAME_NOT_PRESENT;
    }
    rule = m_table[filtername];

    std::string l_rulename         = rule->GetRuleName();
    uint16_t l_ruleid              = rule->GetRuleId();
    uint16_t l_Priority            = rule->GetPriority();
    int l_ExpDur                   = rule->GetExpiryDuration();
    int l_expcall                  = rule->GetExpiryCalls();
    Logger::Level l_logLevel       = rule->GetLoglevel();
    ExprRef l_rule                 = rule->GetRule();
    bool l_filtStatus              = rule->GetTraceStatus();
    
    if(!Rule.empty())
    {
       rule_flag = 1; 
    }        
    if(priority != -1)
    {
        l_Priority = priority;
    }
    if(filtstatus != NULL)
    {
        l_filtStatus = (!strcmp(filtstatus,"true"));
        if(!l_filtStatus)
        {
            CLOG_DEBUG("Disabling the rule %s",l_rulename.c_str());
            Tracer::DisableRule( l_rulename);
        }
    }
    if(!loglevel.empty())
    {
        logLevel = this->GetLogLevel(loglevel.c_str());
        l_logLevel = logLevel;
    }
    if(expdur != -1)
    {
        l_ExpDur = expdur;
    }
    if(expmsg != -1)
    {
        l_expcall = expmsg;
    }
        
    retVal = this->RemoveFilterRule(filtername);
    
    try
    {
        rule = new TraceFilterRule(l_rulename.c_str(),
                l_ruleid, l_Priority, 
                l_ExpDur,l_expcall,
                l_logLevel,
                l_filtStatus);

    if(rule_flag)
    {
        rule->ParseExpr(Rule.c_str());
    }
    else
    {
        rule->SetRule(l_rule);
    }

    retVal = this->AddFilterRule(rule);
    }
    catch(ParserException& exp)
    {
        // Log the exception and continue with the next rule 
        CLOG_ERROR("Parser exception thrown for rule <%s>: %s", 
                filtername.c_str(), exp.what());
        delete rule;
        rule = NULL;
        retVal = SET_TRACECONFIG_ERR_PARSING_RULE_FAILED;
    }
    catch(RuleException ruleExp)
    {
        CLOG_ERROR("Filter Rule exception:%s",ruleExp.what());
    }
        
    return retVal;   //success return
}   

void Tracer::GetRuleStatus(std::string &filtername,std::map<std::string, int> &traceData)
{
    std::map<std::string, int>::iterator iter;
    if(filtername.empty())
    {
        RuleFilterMap::iterator it = m_table.begin();
        for (;it != m_table.end();it++)
        {
            TraceFilterRule *rule = it->second;
            traceData[rule->GetRuleName()] = rule->GetTraceStatus();
        }
        for (iter=traceData.begin(); iter != traceData.end(); ++iter) 
        {
            CLOG_DEBUG("First element %s  Second element %d",iter->first.c_str(),iter->second);
        }

    }
    else
    {
        RuleFilterMap::iterator it = m_table.find(filtername);
        TraceFilterRule *rule = it->second;
        traceData[rule->GetRuleName()] = rule->GetTraceStatus();
        //CLOG_DEBUG("First element %s  Second element %d",iter->first.c_str(),iter->second);
    }

}

void Tracer::Configure(const char *confFileName)
{
    Json::Reader reader;
    Json::Value  root, entry;
    ExprRef expr;
    TraceFilterRule *rule = NULL;

    try
    {
        if (m_confFileName.empty())
        {
            m_confFileName = confFileName;
        }
        std::ifstream doc(m_confFileName);
        bool res = reader.parse(doc, root);
        if (!res)
        {
            CLOG_ERROR("Parsing Tracer JSON file failed: %s", 
                reader.getFormattedErrorMessages().c_str());
            return;
        }
    }
    catch(...)
    {
        CLOG_ERROR("Error reading trace rule filter file");
        return;
    }

    bool traceEnable = root.get("enable-tracing", false).asBool();
    if (traceEnable)
    {
        CLOG_NOTICE("Session Tracing enabled");
        this->Enable();
    }
    else
    {
        CLOG_NOTICE("Session Tracing disabled");
        this->Disable();
    }

    Json::Value filterRules = root["filter-rules"];
    if (filterRules.size() > 0)
    {
        this->Flush();
    }

    Logger::Level logLevel;

    for (unsigned i = 0; i < filterRules.size(); i++)
    {
        try
        {
            entry = filterRules[i];
            logLevel = this->GetLogLevel(entry.get("level", "notice").asString().c_str());

            rule = new TraceFilterRule(entry["name"].asString().c_str(),
                    entry["id"].asInt(), entry["priority"].asInt(), 
                    entry.get("expiryDuration", TraceFilterRule::InvalidValue).asInt(),
                    entry.get("expiryMessages", TraceFilterRule::InvalidValue).asInt(),
                    logLevel,
                    entry.get("enabled", true).asBool());

            rule->ParseExpr(entry["rule"].asString().c_str());

            // Add the rule to the tracer 
            this->AddFilterRule(rule);
        }
        catch(ParserException& exp)
        {
            // Log the exception and continue with the next rule 
            CLOG_ERROR("Parser exception thrown for rule <%s>: %s", 
                        entry["name"].asString().c_str(), exp.what());
            delete rule;
            rule = NULL;
        }
        catch(RuleException ruleExp)
        {
            CLOG_ERROR("Filter Rule exception:%s",ruleExp.what());
        }
        
    }
    CLOG_INFO("Trace config loaded succesfully");

}

Logger::Level Tracer::GetLogLevel(std::string levelStr)
{
    // no error check now
    return m_logMap[levelStr];
}

int Tracer::AddFilterRule(TraceFilterRule *rule)
{
    ScopedWriteLock lock(m_tableLock);

    if (m_table.size() > MAX_TRACE_FILTER_RULES)
    {
        CLOG_ERROR("Maximum filter reached %d.Can not insert more",MAX_TRACE_FILTER_RULES);
        throw std::out_of_range("Maximum filter rules reached");
    }

    // Check for duplicates
    // Add it to rule map and add it to rule table
    RuleFilterMap::iterator it = m_table.find(rule->m_name);
    if (it != m_table.end())
    {
        CLOG_ERROR("Rule entry %s already present. Ignoring the rule",rule->m_name.c_str());
        delete rule;
        return SET_TRACECONFIG_ERR_FILTER_ALREADY_PRESENT;
    }

    m_table[rule->m_name] = rule;

    // Add rule to the rule table and Enable goes together
    if (rule->m_enabled)
    {
         m_rules.AddRule(rule->m_name.c_str(), rule->m_ruleId, rule->m_priority, rule->m_rule,
                         (void*)rule);
         rule->Enable();
    }

    return 0;   //success return
}

int Tracer::RemoveFilterRule(std::string &ruleName)
{
    ScopedWriteLock lock(m_tableLock);

    RuleFilterMap::iterator it = m_table.find(ruleName);
    if (it == m_table.end())
    {
        CLOG_WARNING("No rule <%s> present for removal", ruleName.c_str());
        return DEL_TRACECONFIG_ERR_FILTER_WITH_FILTER_NAME_NOT_PRESENT;
    }

    TraceFilterRule *rule = it->second;
    rule->Disable();
    m_rules.RemoveRule(rule->m_ruleId, rule->m_priority);

    /*
    void *userData = NULL;
    if (m_traceObjs[rule->m_ruleId])
    {
        userData = m_traceObjs[rule->m_ruleId]->UserData();
    }

    this->InvokeRuleRemovalCbk(rule->m_ruleId, userData);
    */
    m_traceObjs[rule->m_ruleId] = NULL;
    
    delete rule;

    m_table.erase(it);
    return 0;   //success return
}

void Tracer::EnableRule(std::string &filterName)
{
    ScopedReadLock lock(m_tableLock);

    RuleFilterMap::iterator it = m_table.find(filterName);
    if (it == m_table.end())
    {
        CLOG_WARNING("No rule <%s> present to enable", filterName.c_str());
        return;
    }

    TraceFilterRule *rule = it->second;

    m_rules.AddRule(rule->m_name.c_str(), rule->m_ruleId, rule->m_priority,
                    rule->m_rule, (void*)rule);
    rule->Enable();
}

void Tracer::DisableRule(std::string &filterName)
{
    ScopedReadLock lock(m_tableLock);

    RuleFilterMap::iterator it = m_table.find(filterName);
    if (it == m_table.end())
    {
        CLOG_WARNING("No rule <%s> present to disable", filterName.c_str());
        return;
    }

    TraceFilterRule *rule = it->second;

    // Disable rule and removal from rule table goes together
    rule->Disable();
    m_rules.RemoveRule(rule->m_ruleId, rule->m_priority);
}

void Tracer::RegisterRuleRemovalCbk(RuleRemovalCbk cbk, void *arg)
{
    m_disableCbk = cbk;
    m_disableCbkArg = arg;
}

bool Tracer::Filter(void *userData, TraceRef& traceObj)
{
    RuleMatch match;
    ScopedReadLock lock(m_tableLock);

    // Rule runtime is a thread specific data
    m_rt->UserData(userData);

    bool matched = m_rules.Match(m_rt, match);
    if (!matched)
    {
        CLOG_DEBUG("No trace filter match found");
    }
    else
    {
        TraceFilterRule* rule = reinterpret_cast<TraceFilterRule*>(match.userData);
        CLOG_INFO("Filter match found for %s", match.ruleName.c_str());

        matched = rule->Matched(traceObj);
    }

    return matched;
}

void Tracer::Flush()
{
    TraceFilterRule *rule = NULL;
    void *userData;
    ScopedWriteLock lock(m_tableLock);

    m_rules.Flush();

    for (RuleFilterMap::iterator it = m_table.begin(); it != m_table.end();)
    {
        rule = it->second;
        
        userData = NULL;
        if (m_traceObjs[rule->m_ruleId])
        {
            userData = m_traceObjs[rule->m_ruleId]->UserData();
            m_traceObjs[rule->m_ruleId]->UserData(NULL);
        }
        this->InvokeRuleRemovalCbk(rule->m_ruleId, userData);
        delete rule;
        m_table.erase(it++);
    }
}

#define DUMMY_PAYLOAD_SZ  16
int Tracer::OnSockEvent(SockEvent &event)
{
    if (event.Events() & SockEvent::READ_EVENT)
    {
        char buf[DUMMY_PAYLOAD_SZ] = {0};
        int fd = m_reloadSock.Accept();
        Socket temp(fd);

        temp.Recv(buf, DUMMY_PAYLOAD_SZ);
        this->Configure(m_confFileName.c_str());
        temp.Send(buf, DUMMY_PAYLOAD_SZ);
    }
    return 0;
}

// TODO do this later
#if 0
// It is assumed that the trace object checks are done in the EACC_PROTO_TRACE
// macro.
void Tracer::LogProtoTrace(ProtocolType proto,
                SockAddr &src, SockAddr &dest,
                const uint8_t* bytes, uint32_t len);
{
    eAccelero::Tracer::ThreadTraceObj()->dump(bytes, len);
}
#endif

} // namespace eAccelero
