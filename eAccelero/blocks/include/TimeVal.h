#ifndef __EACC_TimeVal_h__
#define __EACC_TimeVal_h__

#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include "EAcc.h"
#include "Exception.h"

namespace eAccelero
{

class TimeVal
{
 public:
     enum
     {
         US_PER_MS  = 1000,
         MS_PER_SEC = 1000,
         US_PER_SEC = 1000000,
         NS_PER_US  = 1000,
     };

    static void uSleep(unsigned uSec)
    {
        struct timespec ts;
        struct timespec remTime = {0, 0};

        ts.tv_sec = (uSec / (US_PER_SEC));
        ts.tv_nsec = (uSec % US_PER_SEC) * NS_PER_US;

        while (nanosleep(&ts, &remTime) < 0 && (errno == EINTR || errno == EAGAIN))
        {
            ts = remTime;
        }
        if (BRANCH_EXPECT(errno && errno != EINTR && errno != EAGAIN, 0))
        {
            throw SystemException("Nanosleep failed");
        }
    }
 
    TimeVal()
    {
        m_tv.tv_sec = 0;
        m_tv.tv_usec = 0;
    }
    TimeVal(const struct timeval& tv)
        : m_tv(tv)
    {
    }
    TimeVal(const TimeVal& rhs)
      : m_tv(rhs.m_tv)
    {
    }
    TimeVal(const struct timespec& ts)
    {
        this->fromTimeSpec(ts);
    }
    TimeVal(const unsigned milliSec)
    {
        m_tv.tv_sec = 0;
        m_tv.tv_usec = milliSec * US_PER_MS;
        TimeVal::adjustCarry(m_tv);
    }

    // Assignment operators
    TimeVal& operator = (const struct timeval& tv)
    {
        m_tv = tv;
        return *this;
    }
    TimeVal& operator = (const TimeVal& rhs)
    {
        m_tv = rhs.m_tv;
        return *this;
    }
    TimeVal& operator = (const unsigned milliSec)
    {
        m_tv.tv_sec = 0;
        m_tv.tv_usec = milliSec * US_PER_MS;
        TimeVal::adjustCarry(m_tv);

        return *this;
    }

    void addUSec(const unsigned uSec)
    {
        m_tv.tv_usec += uSec;
        TimeVal::adjustCarry(m_tv);
    }

    // Addition operators
    void operator+=(const TimeVal& rhs)
    {
        this->add(rhs.m_tv);
    }
    friend TimeVal operator + (const TimeVal& val1, const TimeVal& val2)
    {
        TimeVal result;
        add(result.m_tv, val1.m_tv, val2.m_tv);
        return result;
    }

    // Subtraction operators
    void operator -= (const TimeVal& rhs)
    {
        this->sub(rhs.m_tv);
    }
    friend TimeVal operator - (const TimeVal& val1, const TimeVal& val2)
    {
        TimeVal result;
        sub(result.m_tv, val1.m_tv, val2.m_tv);
        return result;
    }

    // Comparison operators
    friend bool operator == (const TimeVal& rhs, const TimeVal& lhs)
    {
        return TimeVal::equals(rhs.m_tv, lhs.m_tv);
    }
    friend bool operator != (const TimeVal& rhs, const TimeVal& lhs)
    {
        return !(TimeVal::equals(rhs.m_tv, lhs.m_tv));
    }
    friend bool operator >(const TimeVal& rhs, const TimeVal& lhs)
    {
        return (TimeVal::compare(rhs.m_tv, lhs.m_tv) == 1);
    }
    friend bool operator >=(const TimeVal& rhs, const TimeVal& lhs)
    {
        int result = TimeVal::compare(rhs.m_tv, lhs.m_tv);
        return (result == 1 || result == 0);
    }
    friend bool operator <(const TimeVal& rhs, const TimeVal& lhs)
    {
        return (TimeVal::compare(rhs.m_tv, lhs.m_tv) == -1);
    }
    friend bool operator <=(const TimeVal& rhs, const TimeVal& lhs)
    {
        int result = TimeVal::compare(rhs.m_tv, lhs.m_tv);
        return (result == -1 || result == 0);
    }
   
    operator timeval*()
    {
        return &m_tv;
    }
    operator double()
    {
        return ((double)m_tv.tv_sec + 
                (double)m_tv.tv_usec / (double)US_PER_SEC);
    }
    TimeVal& now()
    {
        gettimeofday(&m_tv, NULL);
        return *this;
    }

    // Does not return the current time. Returns a time elapsed from a previous
    // constant instance after boot.
    // Useful to calculate time differences as it is is not subjected to NTP or
    // data/time modifications in the system
    TimeVal& nowMonotonic()
    {
        struct timespec ts;
#if defined (CLOCK_MONOTONIC_COARSE)
        // faster version of CLOCK_MONOTONIC but less accurate
        // we won't be needing accuracy of few nanosecs
        clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
        this->fromTimeSpec(ts);
#elif defined (CLOCK_MONOTONIC)
        // slower version more accurate
        clock_gettime(CLOCK_MONOTONIC, &ts);
        this->fromTimeSpec(ts);
#else
        // Monotonic clock not awailable, do a gettimeofday
        // since it is more portable
        gettimeofday(&m_tv, NULL);
#endif
        return *this;
    }

    void dump(char* str)
    {
        sprintf(str, "<TimeVal: %u secs , %06u usecs>", 
                (unsigned)m_tv.tv_sec,
                (unsigned)m_tv.tv_usec);
    }

    friend std::ostream& operator << (std::ostream& os, TimeVal& tv)
    {
        os << "<TimeVal: " << std::fixed << (double)tv << " secs>";
        return os;
    }

    void toTimeSpec(struct timespec &ts)
    {
        ts.tv_sec = m_tv.tv_sec;
        ts.tv_nsec = m_tv.tv_usec * NS_PER_US;
    }
    void fromTimeSpec(const struct timespec &ts)
    {
        m_tv.tv_sec = ts.tv_sec;
        m_tv.tv_usec = ts.tv_nsec / NS_PER_US;
    }
    // Truncates to milliseconds (32bit)
    unsigned Truncate()
    {
        return (m_tv.tv_sec * MS_PER_SEC) + (m_tv.tv_usec / US_PER_MS);        
    }
 protected:
    void add(const struct timeval& val)
    {
        m_tv.tv_sec += val.tv_sec;
        m_tv.tv_usec += val.tv_usec;
        TimeVal::adjustCarry(m_tv);
    }
    static void add(struct timeval& result,
             const struct timeval& val1,
             const struct timeval& val2)
    {
        result.tv_sec = val1.tv_sec + val2.tv_sec;
        result.tv_usec = val1.tv_usec + val2.tv_usec;
        adjustCarry(result);
    }
    static void adjustCarry(struct timeval& result)
    {
        unsigned carry = (unsigned)result.tv_usec / US_PER_SEC;
        if (carry)
        {
            result.tv_sec += carry;
            result.tv_usec %= US_PER_SEC;
        }        
    }

    void sub(const struct timeval& rhs)
    {
        m_tv.tv_sec -= rhs.tv_sec;
        m_tv.tv_usec -= rhs.tv_usec;
        TimeVal::adjustBorrow(m_tv);
    }
    static void sub(struct timeval& result,
             const struct timeval& val1,
             const struct timeval& val2)
    {
        result.tv_sec = val1.tv_sec - val2.tv_sec;
        result.tv_usec = val1.tv_usec - val2.tv_usec;
        adjustBorrow(result);
    }
    static void adjustBorrow(struct timeval& result)
    {
        if ((int)result.tv_usec < 0)
        {
            result.tv_sec--;
            result.tv_usec += US_PER_SEC;
        }
    }

    static int compare(const timeval& rhs, const timeval& lhs)
    {
        // Result is 1 if rhs greate than lhs. 0 if both are equal, -1 if rhs
        // less than lhs
        if (rhs.tv_sec > lhs.tv_sec)
        {
            return 1;
        }
        else if (rhs.tv_sec < lhs.tv_sec)
        {
            return -1;
        }
        else if (rhs.tv_usec > lhs.tv_usec)
        {
            // both secs are equal. compare the micro secs value
            return 1;
        }
        else if (rhs.tv_usec < lhs.tv_usec)
        {
            return -1;
        }
        else
        {
            // both are equal, rare case when comparing two instances. If
            // checking for equals to use the equals method
            return 0;
        }
    }

    static int equals(const timeval& rhs, const timeval& lhs)
    {
        int result = 0;
        if ( (rhs.tv_sec == lhs.tv_sec) && 
             (rhs.tv_usec == lhs.tv_usec) )
        {
            result = 1;
        }

        return result;
    }


    struct timeval m_tv;    
}; // class TimeVal

} // namespace eAccelero

#endif // __EACC_TimeVal_h__
