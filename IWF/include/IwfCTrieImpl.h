#ifndef IWFCTRIEIMPL_H_
#define IWFCTRIEIMPL_H_

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "Sync.h"


class IwfCTrieImpl
{

public :
        IwfCTrieImpl() {};
        virtual ~IwfCTrieImpl() {};
        virtual int PopulateRules(map<string,string> &RuleNameVsPatternLst)=0;
        virtual int SearchString(string &inputTxt, vector<string> &matchLst)=0;
        virtual int FlushRules()=0;

};

class IwfPrefixRules
{

public : 
    IwfPrefixRules(IwfCTrieImpl *pTrieImpl);
    ~IwfPrefixRules();
    int PopulateRules(map<string,string> &RuleNameVsPatternLst);
    int SearchString(string &inputTxt, vector<string> &matchLst);
    
int FlushRules();


private :
    IwfCTrieImpl *m_ptrieImpl;
    eAccelero::Mutex m_automataGuard;
    map<string,string> m_rulenameVsIMSIprefixMap;
};
#endif
