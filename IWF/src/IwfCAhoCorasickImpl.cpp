/*
 * AhoCorasickPlus.cpp: This is the implementation file for a sample 
 * C++ wrapper for Aho-Corasick C library 
 * 
 * This file is part of multifast.
 *
    Copyright 2010-2013 Kamiar Kanani <kamiar.kanani@gmail.com>

    multifast is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    multifast is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with multifast.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ahocorasick.h"
#include "IwfCAhoCorasickImpl.h"
#include "iwf.h"
#include <iostream> 
using namespace std;
#include <string.h>


IwfCAhoCorasickImpl::IwfCAhoCorasickImpl ()
{
    //m_acText = new AC_TEXT_t;
    //m_pRuleName = new(char[50]);
    m_configuredRules = false;
}

IwfCAhoCorasickImpl::~IwfCAhoCorasickImpl ()
{
    ac_automata_release (m_automata);
    if(m_acText != NULL)
    {
        delete m_acText;
    }
    if(NULL != m_pRuleName)
    {
        delete m_pRuleName;
    }
}

IwfCAhoCorasickImpl::EnumReturnStatus IwfCAhoCorasickImpl::addPattern (const std::string &pattern, PatternId id)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfCAhoCorasickImpl::addPattern entry");
    EnumReturnStatus rv = RETURNSTATUS_FAILED;
    //char * str = new(char[1024]);
    //strncpy(m_pRuleName,id.c_str(),strlen(id.c_str())+1);
    AC_PATTERN_t tmp_patt;
    tmp_patt.astring = (AC_ALPHABET_t*) pattern.c_str();
    tmp_patt.length = pattern.size();
    tmp_patt.rep.stringy = (const char*)malloc(id.length()+1);
    strcpy((char*)tmp_patt.rep.stringy, id.c_str());

    AC_STATUS_t status = ac_automata_add (m_automata, &tmp_patt);
    DLOG_DEBUG("Pattern value : %s, Pattern Id : %s",(const char*)tmp_patt.astring,tmp_patt.rep.stringy); 
    switch (status)
    {
        case ACERR_SUCCESS:             rv = RETURNSTATUS_SUCCESS; break;
        case ACERR_DUPLICATE_PATTERN:   rv = RETURNSTATUS_DUPLICATE_PATTERN; break;
        case ACERR_LONG_PATTERN:        rv = RETURNSTATUS_LONG_PATTERN; break;
        case ACERR_ZERO_PATTERN:        rv = RETURNSTATUS_ZERO_PATTERN; break;
        case ACERR_AUTOMATA_CLOSED:     rv = RETURNSTATUS_AUTOMATA_CLOSED; break;
    }
    
    return rv;
}

IwfCAhoCorasickImpl::EnumReturnStatus IwfCAhoCorasickImpl::addPattern (const char pattern[], PatternId id)
{
    std::string tmpString = pattern;
    return addPattern (tmpString, id);
}

void IwfCAhoCorasickImpl::finalize ()
{
    ac_automata_finalize (m_automata);
}

void IwfCAhoCorasickImpl::display()
{
    ac_automata_display(m_automata,'s');
}

void IwfCAhoCorasickImpl::search (std::string& text, bool keep)
{
    m_acText->astring = text.c_str();
    m_acText->length = text.size();
    ac_automata_settext (m_automata, m_acText, (int)keep);
}

bool IwfCAhoCorasickImpl::findNext (Match& match)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (m_matchQueue.size()>0)
    {
        match = m_matchQueue.front();
        m_matchQueue.pop();
        return true;
    }
    
    AC_MATCH_t * matchp;
    
    if ((matchp = ac_automata_findnext (m_automata)))
    {
        Match singleMatch;
        singleMatch.position = matchp->position;
        
        for (unsigned int j=0; j < matchp->match_num; j++)
        {
            singleMatch.id = (string)matchp->patterns[j].rep.stringy;
            DLOG_DEBUG("IwfCAhoCorasickImpl::findNext found match in Patterrn : %s, RuleId : %s",matchp->patterns[j].astring,singleMatch.id.c_str());
            // we ignore tmp_patt.astring it may have been invalidated
            m_matchQueue.push(singleMatch);
        }
    }
    
    if (m_matchQueue.size()>0)
    {
        match = m_matchQueue.front();
        m_matchQueue.pop();
        return true;
    }

    return false;
}

void IwfCAhoCorasickImpl::InitAutomata()
{
    m_configuredRules = true;
    m_acText = new AC_TEXT_t;
    m_pRuleName = new(char[50]);
    m_automata = ac_automata_init();
    
}

int IwfCAhoCorasickImpl::ConstructAndSetPatterns(map<string,string>  &PatternNameVsRuleNameMap)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfCAhoCorasickImpl::ConstructAndSetPatterns entry");

    //2. For every sorted map entry, invoke below functions on automata
    //    a) addPattern()
    map<string,string>::iterator itr = PatternNameVsRuleNameMap.begin();

    IwfCAhoCorasickImpl::PatternId patId;
    while(itr != PatternNameVsRuleNameMap.end())
    {
        patId = itr->second;
        addPattern(itr->first,patId);
        itr++;
    }
    //3. finalise() the automata
    finalize();

    DLOG_DEBUG("IwfCAhoCorasickImpl::ConstructAndSetPatterns exit");
    return 0;

}

int IwfCAhoCorasickImpl::PopulateRules(map<string,string> &RuleNameVsPatternLst)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfCAhoCorasickImpl::PopulateRules entry");

    InitAutomata();
    //1. Sort passed map by value  i.e by IMSI-prefix
    ConstructAndSetPatterns(RuleNameVsPatternLst);  
    DLOG_DEBUG("IwfCAhoCorasickImpl::PopulateRules exit");
    
    return 0;
}

int IwfCAhoCorasickImpl::SearchString(string &inputTxt, vector<string> &matchLst)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfCAhoCorasickImpl::SearchString entry");

    //1. invoke search(), to set the search text.
    if(m_configuredRules)
    {
        search( inputTxt,false);
        IwfCAhoCorasickImpl::Match match;
        while(true == findNext(match))
        {
            DLOG_DEBUG("IwfCAhoCorasickImpl::SearchString Found match in RuleName : %s.",match.id.c_str());
            char *token = strtok( const_cast<char*> (match.id.c_str()),",");
            string ruleName;
            while(token != NULL)
            {
                ruleName = token;
                matchLst.push_back(ruleName);            
                token = strtok(NULL, ",");
            }

        }
    }
    else
    {
        DLOG_ERROR("IwfCAhoCorasickImpl:: Translator Rules Not Configured");
    }
    //     - insert into out parameter matchLst
    
    DLOG_DEBUG("IwfCAhoCorasickImpl::SearchString exit");
    return 0;

}

int IwfCAhoCorasickImpl::FlushRules()
{
        ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
        DLOG_DEBUG("IwfCAhoCorasickImpl::FlushRules entry");
        ac_automata_release(m_automata);
        delete m_acText;
        if(NULL != m_pRuleName)
            delete m_pRuleName;

        DLOG_DEBUG("IwfCAhoCorasickImpl::FlushRules exit");
        return 0;
}

