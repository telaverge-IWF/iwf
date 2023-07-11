/*********************************-*-H-*-**********************************
**                                                                          *
**             Copyright 2012 IntelliNet Technologies, Inc.                 *
**                            All Rights Reserved.                          *
**             Manufactured in the United States of America.                *
**       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
**                                                                          *
**   This product and related documentation is protected by copyright and   *
**   distributed under licenses restricting its use, copying, distribution  *
**   and decompilation.  No part of this product or related documentation   *
**   may be reproduced in any form by any means without prior written       *
**   authorization of IntelliNet Technologies and its licensors, if any.    *
**                                                                          *
**   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
**   government is subject to restrictions as set forth in subparagraph     *
**   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
**   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
**                                                                          *
*****************************************************************************/

#if !defined DIA_RATE_FILTER_H_
#define DIA_RATE_FILTER_H_
#include <its++.h>
#include <its_mutex.h>
#include <TimeVal.h>
#include <Thread.h>
#include <Atomic.h>
#include <dia_cmn.h>

#define TOKEN_BUCKET_UPDATE_INTERVAL 200

class TokenBucketFilter
{
    public:
        enum FilterResult
        {
            BUCKET_OVERFLOW = 0,
            ALLOW
        };
        TokenBucketFilter(unsigned rate, unsigned burst, unsigned updateInterval)
            : m_rate(rate),
            m_bucketSize(burst),
            m_updateInterval(updateInterval),
            m_tokens(rate)
        {
            if(m_rate != 0xFFFFFFFF)
            {
                m_isMsgBasedLicensingEnabled = true;
            }
            else
            {
                m_isMsgBasedLicensingEnabled = false;
            }
            m_tokenIncr = (rate * updateInterval) / 1000;
            m_isAlarmRaised = 0;
            m_last.now();
        }
        unsigned MessageRate();
        FilterResult Consume(unsigned tokens = 1);
        void UpdateTokens();
        bool IsMessageBasedLicensingEnabled()
        {
            return m_isMsgBasedLicensingEnabled;
        }
        static TokenBucketFilter* GetTokenBucketFilter();
        eAccelero::TimeVal m_lastAlarmRaised;
        
    private:
        unsigned m_rate;
        unsigned m_bucketSize;
        unsigned m_tokenIncr;
        unsigned m_updateInterval;
        eAccelero::Atomic<unsigned> m_tokens;
        eAccelero::Atomic<unsigned> m_isAlarmRaised;
        eAccelero::TimeVal m_last;
        static TokenBucketFilter* m_tokenBucketFilterObj;
        bool m_isMsgBasedLicensingEnabled;
};

#define TOKEN_BUCKET_FILTER   TokenBucketFilter::GetTokenBucketFilter()

class TokenUpdateThread: public eAccelero::Runnable
{
    public:
    TokenUpdateThread():m_exitCondition(false) {}
    ~TokenUpdateThread() {}
    void Run(void *arg)
    {
        while (!m_exitCondition)
        {
            TOKEN_BUCKET_FILTER->UpdateTokens();
            eAccelero::ThisThread::Sleep(TOKEN_BUCKET_UPDATE_INTERVAL);
        }
    }
    private:
    bool m_exitCondition;
};


#endif 
