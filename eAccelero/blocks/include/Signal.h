#ifndef __EACC_Signal_h__
#define __EACC_Signal_h__

#include "Dispatcher.h"
#include <ucontext.h>
#include <signal.h>

namespace eAccelero
{

class SigSet
{
 public:
    SigSet()
    {
        this->Empty();
    }

    SigSet(sigset_t* set)
    {
        memcpy(&m_set, set, sizeof(m_set));
    }
    SigSet(const SigSet& rhs)
    {
        memcpy(&m_set, &(rhs.m_set), sizeof(m_set));
    }
    SigSet& operator = (const SigSet& rhs)
    {
        memcpy(&m_set, &(rhs.m_set), sizeof(m_set));

        return *this;
    }

    void Add(int signo)
    {
        int ret;
        ret = sigaddset(&m_set, signo);
        if (ret < 0)
        {
            throw SystemException("Sigaddset failed");
        }
    }

    void Del(int signo)
    {
        int ret;
        ret = sigdelset(&m_set, signo);
        if (ret < 0)
        {
            throw SystemException("Sigdelset failed");
        }
    }

    void Empty()
    {
        sigemptyset(&m_set);
    }

    void Fill()
    {
        sigfillset(&m_set);
    }

    int IsMember(int signo)
    {
        return sigismember(&m_set, signo);
    }

    operator sigset_t*()
    {
        return &m_set;
    }

    operator const sigset_t*() const
    {
        return (const sigset_t*)&m_set;
    }

    static void SetMask(int how, SigSet *set = NULL, SigSet *old = NULL);

    void BlockAll(SigSet *old = NULL)
    {
        this->Fill();
        SetMask(SIG_BLOCK, this, old);
    }
    void UnblockAll(SigSet *old = NULL)
    {
        this->Fill();
        SetMask(SIG_UNBLOCK, this, old);
    }

 protected:
    sigset_t m_set;
};

class SignalEventNotifier;

#define SIGNAL_EVENT_TYPE   2

class SignalEvent: public Event
{
 public:
    SignalEvent(int sigNum, SigSet *set = NULL, int flags = 0)
        : Event(SIGNAL_EVENT_TYPE),
          m_sigNum(sigNum),
          m_flags(flags),
          m_sigInfo(NULL)
    {
        if (set != NULL)
        {
            m_set = *set;
        }
        else
        {
            m_set.Fill();
        }
        if (m_flags == 0)
        {
            m_flags = SA_NOCLDSTOP | SA_NOCLDWAIT | SA_SIGINFO;
        }
    }
    SignalEvent(int sigNum, siginfo_t *sigInfo, ucontext_t *ctxt)
        : Event(SIGNAL_EVENT_TYPE),
          m_sigNum(sigNum),
          m_flags(0),
          m_sigInfo(sigInfo),
          m_ucontext(ctxt)
    {
    }
    ucontext_t *UContext()
    {
        return m_ucontext;
    }
    siginfo_t *SigInfo()
    {
        return m_sigInfo;
    }
 protected:
    friend class SignalEventNotifier;

    int     m_sigNum;
    SigSet  m_set;

    // Possible 'or' values
    //  SA_NOCLDSTOP SA_NOCLDWAIT SA_RESETHAND SA_ONSTACK SA_RESTART
    //  SA_NODEFER SA_SIGINFO
    int     m_flags;


    //--- Filled on Signal ---
    siginfo_t   *m_sigInfo;
    ucontext_t  *m_ucontext;
};

class SignalEventNotifier: public NotifierBase
{
 public:
    enum
    {
        MAX_SIGNALS = _NSIG,
    };

    SignalEventNotifier();
    ~SignalEventNotifier();

    EventHandlerId AddEventHandler(const EventSlotBase &slot,
                                   const Event         &event);
    void RemoveEventHandler(EventHandlerId id);

    int Poll(int &waitDuration)
    {
        (void)waitDuration;
        return 0;
    }

    static void SignalHandlerFunc(int sigNum, siginfo_t *info, void *ctxt);

 private:
    // TODO make it non-static
    static EventSlotBase* m_slots[MAX_SIGNALS];
};

} // namespace eAccelero

#endif // __EACC_Signal_h__
