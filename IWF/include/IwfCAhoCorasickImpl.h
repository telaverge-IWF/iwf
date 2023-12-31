/*
 * AhoCorasickPlus.h: This is the header file for a sample
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

#ifndef IWFCAHOCORASICKIMPL_H_
#define IWFCAHOCORASICKIMPL_H_

#include <string>
using std::string;
#include <queue>
using std::queue;
#include <map>
#include <vector>
using namespace std;
#include "IwfCTrieImpl.h"

class IwfCTrieImpl;
// forward declaration
struct AC_AUTOMATA;
struct AC_TEXT;


class IwfCAhoCorasickImpl: public IwfCTrieImpl
{
public:

    enum EnumReturnStatus
    {
        RETURNSTATUS_SUCCESS = 0,       // No error occurred
        RETURNSTATUS_DUPLICATE_PATTERN, // Duplicate patterns
        RETURNSTATUS_LONG_PATTERN,      // Pattern length is bigger than AC_PATTRN_MAX_LENGTH
        RETURNSTATUS_ZERO_PATTERN,      // Empty pattern (zero length)
        RETURNSTATUS_AUTOMATA_CLOSED,   // Automata is closed
        RETURNSTATUS_FAILED,            // General unknown failure
    };

    //typedef unsigned int PatternId;
    typedef std::string PatternId;

    struct Match
    {
        unsigned int    position;
        PatternId       id;
    };

public:

    IwfCAhoCorasickImpl();
    virtual ~IwfCAhoCorasickImpl();

    virtual int PopulateRules(map<string,string> &RuleNameVsPatternLst);
    virtual int SearchString(string &inputTxt, vector<string> &matchLst);
    virtual int FlushRules();
    
protected :
    EnumReturnStatus addPattern (const std::string &pattern, PatternId id);
    EnumReturnStatus addPattern (const char pattern[], PatternId id); // zero ending string
    void             finalize   ();

    void search   (std::string& text, bool keep);
    bool findNext (Match& match);
    //bool findNext (vector<string> & match);
    void display ();

    void InitAutomata();
    int ConstructAndSetPatterns(map<string,string>  &PatternNameVsRuleNameMap);
    

private:
    AC_AUTOMATA            *m_automata;
    AC_TEXT                *m_acText;
    std::queue<Match>       m_matchQueue;   // if multiple matches occur in a single position we save them here and return one by one for simplicity
    char                   *m_pRuleName;    
    bool                    m_configuredRules;
};  

#endif /* AHOCORASICKPPW_H_ */
