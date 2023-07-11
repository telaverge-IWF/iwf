/*********************************-*-CPP-*-**********************************
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
 ****************************************************************************/

#include<dia_rate_filter.h>
#include <dia_cmn.h>
#include <dia_stack_alarms.h>
#if defined(ITS_STD_NAMESPACE)
using namespace its;
#endif
#define MAX_BUCKET_SIZE  25000   //Assume that DRE can handle maximum of these many messages
#define MULTIPLICATION_VALUE 3 
#define MIN_TIME_REQUIRED_TO_CLEAR_ALARM 10000 //in milli seconds
extern "C" ITSDLLAPI unsigned int LICENSE_AllowedMsgRate(void);

TokenBucketFilter* TokenBucketFilter::m_tokenBucketFilterObj = NULL;



/*.implementation:static
 *****************************************************************************
 **  Purpose: Static method to create the object.TokenBucketFilter is a
 **           singleton class
 **
 **  Input Parameters:
 **     Message rate allowed per sec,burst rate and updateInterval  
 **
 **  Input/Output Parameters:
 **      None.
 **
 **  Output Parameters:
 **      None
 **  Return Value:
 **        Returns the TokenBucketFilter object.
 **
 **  Notes:
 **
 **  See Also:
 *****************************************************************************/

TokenBucketFilter*
TokenBucketFilter::GetTokenBucketFilter()
{
    if (m_tokenBucketFilterObj == NULL)
    {
        unsigned int msgRate = LICENSE_AllowedMsgRate();
        DT_DBG(("Message rate allowed is = %u msg/sec",msgRate));
        //multiply msg rate by MULTIPLICATION_VALUE to indicate msg burst MULTIPLICATION_VALUEi
        //times of msg rate can DRE handle.
        //This is bec if DRE was idle for some time and suddenly lot of the messages comes
        //in a burst it is better to allow certain message.
        if((msgRate * MULTIPLICATION_VALUE) <= MAX_BUCKET_SIZE)
        {
            m_tokenBucketFilterObj = new TokenBucketFilter(msgRate,(msgRate * MULTIPLICATION_VALUE),
                                                           TOKEN_BUCKET_UPDATE_INTERVAL);
        }
        else
        {
            m_tokenBucketFilterObj = new TokenBucketFilter(msgRate,msgRate,TOKEN_BUCKET_UPDATE_INTERVAL);
        }

    }

    return m_tokenBucketFilterObj;
}


/*.implementation:static
 *****************************************************************************
 **  Purpose:Method to update the tokens at regural interval 
 **
 **  Input Parameters:
 **     None.  
 **
 **  Input/Output Parameters:
 **      None.
 **
 **  Output Parameters:
 **      None
 **  Return Value:
 **        None.
 **
 **  Notes:
 **
 **  See Also:
 *****************************************************************************/

void TokenBucketFilter::UpdateTokens()
{
    if ((unsigned)m_tokens < m_bucketSize)
    {
        eAccelero::TimeVal now;
        unsigned delta;
        now.now();
        delta = (m_tokenIncr * (now - m_last).Truncate())/m_updateInterval;
        if (delta > m_rate) delta = m_rate;
        m_tokens += delta;
        m_last.now();
        if(m_isAlarmRaised)
        {
            //Clear the alarm if messare rate violation is not seen for last 10 secs
            if((now - m_lastAlarmRaised).Truncate() > MIN_TIME_REQUIRED_TO_CLEAR_ALARM)
            {
                DT_DBG(("Clearing the rate limiting filter alarm"));
                std::vector<std::string> variables;
                std::string alarmText("Clearing the rate limiting filter alarm");
                int subComponentId = STACK_MESSAGE_PROCESSING;
                int alarmId = RATE_LIMITING_FILTER_STOPPED_REJECTING_THE_MESSAGE;
                m_isAlarmRaised = 0;
                DIA_STACK_ALARM->RaiseAlarm(subComponentId,alarmId,alarmText, variables);
            }

        }
    }
}

/*.implementation:static
 *****************************************************************************
 **  Purpose:When ever called consumes number of tokens mentioned in input
 **  input paramter for bucket.
 **
 **  Input Parameters:
 **     Number of tokend to bu consumed.  
 **
 **  Input/Output Parameters:
 **      None.
 **
 **  Output Parameters:
 **      None
 **  Return Value:
 **        Returns whether to allow incoming message to be processed or regected.
 **
 **  Notes:
 **
 **  See Also:
 *****************************************************************************/
TokenBucketFilter::FilterResult 
TokenBucketFilter:: Consume(unsigned tokens)
{
    if ((unsigned)m_tokens == 0)
    {
        m_lastAlarmRaised.now();//time stamp of last time overflow seen
        if(m_isAlarmRaised == (unsigned int)0)//Raise only if not raised
        {
            DT_WRN(("Raise the rate limiting filter alarm"));
            std::vector<std::string> variables;
            std::string alarmText("Raise the rate limiting filter alarm");
            int subComponentId = STACK_MESSAGE_PROCESSING;
            int alarmId = RATE_LIMITING_FILTER_STARTED_REJECTING_THE_MESSAGE;
            m_isAlarmRaised = 1;
            DIA_STACK_ALARM->RaiseAlarm(subComponentId,alarmId,alarmText, variables);
        }
        return BUCKET_OVERFLOW;
    }
    m_tokens -= tokens;
    return ALLOW;
}

/*.implementation:static
 *****************************************************************************
 **  Purpose:Returns the message rate allowed by the license provided
 **
 **  Input Parameters:
 **     None.  
 **
 **  Input/Output Parameters:
 **      None.
 **
 **  Output Parameters:
 **      None
 **  Return Value:
 **        Returns Message rate.
 **
 **  Notes:
 **
 **  See Also:
 *****************************************************************************/

 unsigned TokenBucketFilter::MessageRate()
 {
     return m_rate;
 }
