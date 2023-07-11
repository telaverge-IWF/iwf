#ifndef __EACC_Transceiver_h__
#define __EACC_Transceiver_h__

#include "MeSSage.h"
#include "Tipc.h"
#include "SockEvent.h"
#include "Timer.h"
#include "Sync.h"

namespace eAccelero
{

class MeSSageQ
{
  public:
    MeSSageQ()
        : m_head(NULL),
          m_tail(NULL),
          m_count(0)
    {
        
    }
    ~MeSSageQ()
    {
        
    }
    
    void PushBack(MeSSage* msg);
    void PushFront(MeSSage* msg);
    
    MeSSage* Peek()
    {
        // no Checks are made, its upto the caller to check NULL ptr.
        return m_head;
    }
    
    MeSSage* PopFront()
    {
        Mutex::ScopedMutex  guard(m_lock);
        return PopFrontNoLock();
    }

    MeSSage* PopFrontNoLock();
    
    void Erase(MeSSage* msg);
    
    const unsigned& Count() const
    {
        return m_count;
    }
    
    bool Empty()
    {
        bool ret = (m_count == 0);
        return ret;
    }

    void Lock()
    {
        m_lock.lock();
    }
    void Unlock()
    {
        m_lock.unlock();
    }

  private:
    MeSSage* m_head;
    MeSSage* m_tail;
    
    unsigned m_count;
    Mutex    m_lock;
};

class Transceiver
{
 public:
    enum
    {
        MAX_MSGS_PER_SEND = 40,
        PERIODIC_TIMER = 500, // every 500 ms
        MAX_RECV_BUFF_SZ = 32 * 1024,
    };
    
    Transceiver(MeSSEndpoint &self, unsigned sockType);
    Transceiver(int sockFD);
    ~Transceiver();
    
    int OnSockEvent(SockEvent &event);
    
    int OnTimerEvent(TimerEvent &event);
    
    void Send(MeSSage *msg);

    void Send();
    
    void Cleanup();
    
    void Bind(MeSSEndpoint &self);

    TimeVal& Timestamp()
    {
        return m_timeStamp;
    }
  
 protected:

    void BouncePending();

    // The following hooks are required by MeSSConnection
    virtual int OnRead(MeSSage *in)
    {
        return 0;
    }

    virtual int OnWritable()
    {
        return 0;
    }

    virtual int OnError()
    {
        return 0;
    }

    virtual int OnCleanup()
    {
        return 0;
    }

    void ResetHooks()
    {
        m_hooks.onReadHook = 0;
        m_hooks.onWritableHook = 0;
        m_hooks.onErrorHook = 0;
        m_hooks.onCleanupHook = 0;
    }

    virtual int SockSend(TIPCAddr &addr, void *msg, unsigned len);
    
    TIPCSock        m_sock;
    unsigned        m_sockType;
    EventHandlerId  m_evhId;
    MeSSageQ        m_sendQ;
    MeSSageQ        m_pendingQ;
    EventHandlerId  m_timerId;
    TimeVal         m_timeStamp; // last active operation on this transeiver
    
    //uint8_t         m_recvBuf[MAX_RECV_BUFF_SZ];
    
    bool    m_writable;
    struct Hooks {
        uint8_t onReadHook:1;
        uint8_t onWritableHook:1;
        uint8_t onErrorHook:1;
        uint8_t onCleanupHook:1;
    } m_hooks;
}; // class Transceiver

class MeSSConnection: public Transceiver
{
 public:
    enum State
    {
        Idle,
        Connecting,
        Connected,
        Active,
        Passive,
        Terminating
    };

    // TODO Topology events to cleanup connections

    // Active connection from the client
    MeSSConnection(MeSSEndpoint &self)
        : Transceiver(self, SOCK_SEQPACKET),
          m_state(Idle)
    {
        m_sock.SetNonBlocking(1);
        m_hooks.onReadHook = 1;
        m_hooks.onWritableHook = 1;
        m_hooks.onCleanupHook = 1;
        m_writable = true; // start as writable, for the first message to go thru
    }

    // Passive connection on the server side
    MeSSConnection(int sockFd)
        : Transceiver(sockFd),
          m_state(Connected)
    {
        m_sock.SetNonBlocking(1);
        m_hooks.onReadHook = 1;
        m_hooks.onCleanupHook = 1;
    }

#if 0 
    // For active client side connection
    void Connect(const MeSSEndpoint &dest)
    {
        TIPCAddr addr;
        int ret;
        addr.SetName(dest.compId, dest.instance);
        m_sock.SetNonBlocking(0);
        ret = m_sock.Connect(addr);
        if (ret == 0)
        {
            m_state = Connecting;
        }
        else
        {
            m_state = Connected;
        }
        m_sock.SetNonBlocking(1);
        m_dest = dest;
    }
#endif

    void SetState(State &state)
    {
        m_state = state;
    }

    // Called for the passive connection  
    virtual int OnRead(MeSSage *in);

    // This will be called for the client socket, after connecting
    virtual int OnWritable();

    // virtual int OnError();

    virtual int OnCleanup();

    MeSSEndpoint& Dest()
    {
        return m_dest;
    }
 
 protected:
    virtual int SockSend(TIPCAddr &addr, void *msg, unsigned len);

    State m_state;
    MeSSEndpoint m_dest;
    
}; // class MeSSConnection

} // namespace eAccelero

#endif // namespace __EACC_Transceiver_h__
