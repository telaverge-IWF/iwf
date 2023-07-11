#include "Signal.h"
#include <pthread.h>
#include <stdexcept>
#include "Component.h"

namespace eAccelero
{

void SigSet::SetMask(int how, SigSet *set, SigSet *omask)
{
    sigset_t *nset = NULL;
    sigset_t *oset = NULL;
    int ret = 0;

    if (set) nset = *set;
    if (omask) oset = *omask;

#ifdef _REENTRANT
    ret = pthread_sigmask(how, nset, oset);
#else
    ret = sigprocmask(how, nset, oset);
#endif
    if (ret != 0)
    {
        throw SystemException("Set Sigmask failed", ret);
    }
}

EventSlotBase* SignalEventNotifier::m_slots[MAX_SIGNALS] = {NULL};
SignalEventNotifier::SignalEventNotifier()
{
}
SignalEventNotifier::~SignalEventNotifier()
{
    for(int i = 0; i < MAX_SIGNALS; i++)
    {
        this->RemoveEventHandler(i);
    }
}

EventHandlerId SignalEventNotifier::AddEventHandler(
                            const EventSlotBase &slot, const Event &event)
{
    const SignalEvent& ev = static_cast<const SignalEvent&>(event);

    if (ev.m_sigNum >= MAX_SIGNALS)
    {
        throw std::out_of_range("Signal num range exceeded");
    }

    if (m_slots[ev.m_sigNum])
    {
        throw DispatcherExceptionLog(Logger::EACC_LOG_CRITICAL, "Signal alredy defined", EINVAL);
    }

    struct sigaction sa;
    sa.sa_handler   = NULL;
    sa.sa_sigaction = &SignalEventNotifier::SignalHandlerFunc;
    sa.sa_mask      = *(const sigset_t*)ev.m_set;
    sa.sa_flags     = ev.m_flags;

    int ret = sigaction(ev.m_sigNum, &sa, NULL);
    if (ret != 0)
    {
        throw SystemException("Sigaction install failed");
    }

    m_slots[ev.m_sigNum] = const_cast<EventSlotBase&>(slot).Duplicate();

    return ev.m_sigNum;
}
 
void SignalEventNotifier::RemoveEventHandler(EventHandlerId id)
{
    if (id >= MAX_SIGNALS)
    {
        return;
    }
    sigaction(id, NULL, NULL);
    if (m_slots[id] == NULL)
    {
        return;
    }
    delete m_slots[id];
    m_slots[id] = NULL;
}

void SignalEventNotifier::SignalHandlerFunc(
                    int sigNum, siginfo_t *info, void *ctxt)
{
    if (m_slots[sigNum] == NULL)
    {
        return;
    }
    SignalEvent ev(sigNum, info, (ucontext*)ctxt);
    m_slots[sigNum]->Notify(ev);
}

} // namespace eAccelero
