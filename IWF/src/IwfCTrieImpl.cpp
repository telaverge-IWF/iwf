
#include "IwfCTrieImpl.h"
#include "iwf.h"

IwfPrefixRules::IwfPrefixRules(IwfCTrieImpl *pTrieImpl): 
                m_ptrieImpl(pTrieImpl)
{
}

IwfPrefixRules::~IwfPrefixRules()
{
    if(m_ptrieImpl)
    {
        delete m_ptrieImpl;
    }
}


int IwfPrefixRules::PopulateRules(map<string,string> &RuleNameVsPatternLst)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfPrefixRules::PopulateRules entry");
    eAccelero::Mutex::ScopedMutex guard(m_automataGuard);

    //2. Invoke Impl specific PopulateRules() 
    m_ptrieImpl->PopulateRules(RuleNameVsPatternLst);
    DLOG_DEBUG("IwfPrefixRules::PopulateRules exit");
    return 0;

}

int IwfPrefixRules::SearchString(string &inputTxt, vector<string> &matchLst)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfPrefixRules::SearchString entry");

    //1. Acquire & lock
    eAccelero::Mutex::ScopedMutex guard(m_automataGuard);
    //2. Invoke Impl specific SearchString() 
    m_ptrieImpl->SearchString(inputTxt,matchLst);

    DLOG_DEBUG("IwfPrefixRules::SearchString exit");

    return 0;
}

int IwfPrefixRules::FlushRules()
{

     ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
     DLOG_DEBUG("IwfPrefixRules::FlushRules entry");
     eAccelero::Mutex::ScopedMutex guard(m_automataGuard);

     //2. Invoke Impl specific PopulateRules() 
     m_ptrieImpl->FlushRules();
     DLOG_DEBUG("IwfPrefixRules::FlushRules exit");
     return 0;
                    
}
                    
