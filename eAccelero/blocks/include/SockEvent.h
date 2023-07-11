#ifndef __EACC_SockEvent_h__
#define __EACC_SockEvent_h__

#include "Socket.h"
#include <sys/epoll.h>
#include "Allocator.h"
#include "Dispatcher.h"
#include "Signal.h"

namespace eAccelero
{


/**
 * \class EPoll
 * \file EPoll.h
 * \brief Wrapper for the epoll_xxx system calls in linux. epoll is a faster way
 * of polling especially when the number of file descriptors polled are large.
 */
class EPoll
{
public:
	enum
	{
        MAX_EVENTS = 20,
        DEFAULT_TIMEOUT = 8, // milli seconds
        INVALID_CONTEXT = 0xFFFFFFFF,
        DEFAULT_EVENTS = EPOLLIN | EPOLLOUT | EPOLLPRI,
	};

	/**
	 * \brief Constructor to initialize the newly created EPoll object
	 * \param flags [in] Optional. Can be set to 0 if the poll file descriptor
	 * needs be present across execs.
	 */
	EPoll(int flags = EPOLL_CLOEXEC)
		: m_epollFd(-1)
	{
		m_epollFd = epoll_create1(flags);
		if (m_epollFd < 0)
		{
			throw SocketException("EPoll creation failed");
		}
	}

	/**
	 * \brief Desctructor that closes the underlying epoll fd.
	 * \return
	 */
	~EPoll()
	{
		if (m_epollFd != -1)
		{
			close(m_epollFd);
		}
	}

	/**
	 * \brief Adds the file descriptor the poll list.
	 * \param fd [in] File descriptor to be polled for events
	 * \param events [in] events to be polled on the file descriptor.
	 * Possible events are
	 * 		EPOLLIN  - fd available for read
	 * 		EPOLLOUT - fd available for write
	 * 		EPOLLRDHUP - Stream  socket peer closed connection, or shut down
	 * 					 writing half of connection.
	 * 		EPOLLPRI - There is urgent data available for read operations
	 * 		EPOLLERR - error happened on fd, epoll always waits for this event
	 * 		EPOLLHUP - hang up happened, epoll always waits for this event
	 * 		EPOLLET  - sets Edge Triggered behavior. Default is level triggered
	 * 		EPOLLONESHOT - One shot behavior. Use modify() to reenable.
	 * \param context [in] returned back if an event is set on the fd.
	 */
	void add(int fd, unsigned events = EPOLLIN, unsigned context = INVALID_CONTEXT)
	{
		int ret;
		struct epoll_event event = {0};
		event.events = events;

		this->addEventData(event, fd, context);

		ret = epoll_ctl(m_epollFd, EPOLL_CTL_ADD, fd, &event);
		if (ret < 0)
		{
            abort();
			throw SocketException("Add file descriptor failed");
		}
	}

	/**
	 * \brief Removes the fd from event polling list
	 * \param fd [in] FD to be removed from polling list
	 */
	void remove(int fd)
	{
		int ret;

		ret = epoll_ctl(m_epollFd, EPOLL_CTL_DEL, fd, NULL);
		if (ret < 0)
		{
			throw SocketException("Removing file descriptor failed");
		}
	}

	/**
	 * \brief Modify the event parameters of the fd.
	 * \param fd [in] fd for which the event parameters need to be changed.
	 * \param events [in] modified events. See add() for possible values.
	 * \param context [in] value that will be returned if the fd has event.
	 * If context is null then, fd is treated as the context. For an epoll
	 * object intermixing fd and context is not recommended unless there is
	 * a clear way to differentiate fd with context.
	 */
	void modify(int fd, unsigned events, unsigned context = INVALID_CONTEXT)
	{
		int ret;
		struct epoll_event event = {0};
		event.events = events;

		this->addEventData(event, fd, context);

		ret = epoll_ctl(m_epollFd, EPOLL_CTL_MOD, fd, &event);
		if (ret < 0)
		{
			throw SocketException("Modify file descriptor failed");
		}
	}

	/**
	 * \brief Wait for the events on the added file desriptors.
	 * \param events [out] Available events.
	 * \param maxEvents [in] Maximum events that can be received per wait().
	 * \param timeout [in] Timeout in millisecs.
	 * \return Number of events available. 0 if timeout occured.
	 */
	int wait(struct epoll_event* events,
			 int timeout = DEFAULT_TIMEOUT,
		     int maxEvents = MAX_EVENTS)
	{
		int ret;

		ret = epoll_wait(m_epollFd, events, maxEvents, timeout);
		if (ret < 0 && errno != EINTR)
		{
			throw SocketException("EPoll wait failed");
		}

		return ret;
	}

    int pwait(struct epoll_event* events,
              const SigSet& sigMask,
              int timeout = DEFAULT_TIMEOUT,
              int maxEvents = MAX_EVENTS)
    {
        int ret;

        ret = epoll_pwait(m_epollFd, events, maxEvents, timeout, sigMask);
		if (ret < 0 && errno != EINTR)
		{
			throw SocketException("EPoll pwait failed");
		}

        return ret;
    }

private:
    void addEventData(struct epoll_event& event, int fd, unsigned context)
    {
		if (context == INVALID_CONTEXT)  event.data.fd = fd;
		else                             event.data.u32 = context;
    }

	int m_epollFd;
};

class SockEventNotifier;

#define SOCK_EVENT_TYPE 1
class SockEvent: public Event
{
 public:
    enum
    {
        READ_EVENT  = EPOLLIN,
        WRITE_EVENT = EPOLLOUT,
        HUP_EVENT   = EPOLLHUP,
        PRI_EVENT   = EPOLLPRI,
        ERROR_EVENT = EPOLLERR,
        RDHUP_EVENT = EPOLLRDHUP,

        DEFAULT_EVENTS = READ_EVENT | WRITE_EVENT | PRI_EVENT,
    };
    SockEvent(int fd = Socket::INVALID_FD, unsigned events = DEFAULT_EVENTS)
        : Event(SOCK_EVENT_TYPE),
          m_sockFD(fd),
          m_events(events),
          m_evhId(0)
    {
    }
    SockEvent(int fd, EventHandlerId evhId, unsigned events)
        : Event(SOCK_EVENT_TYPE),
          m_sockFD(fd),
          m_events(events),
          m_evhId(evhId)
    {
    }
    const int& FD() const
    {
        return m_sockFD;
    }
    const unsigned& Events() const
    {
        return m_events;
    }
    unsigned& Events()
    {
        return m_events;
    }
    const EventHandlerId& EvhId() const
    {
        return m_evhId;
    }
 
 protected:
    friend class  SockEventNotifier;
    
    int m_sockFD;
    unsigned m_events;
    EventHandlerId m_evhId;
};

struct EPollEntry
{
    unsigned char m_slot[4*sizeof(void*)];
    int m_fd;
};


class SockEventNotifier: public NotifierBase
{
 public:

    enum
    {
        DEFAULT_POLL_TIMEOUT = EPoll::DEFAULT_TIMEOUT
    };

    SockEventNotifier()
        : m_pollTimeout(DEFAULT_POLL_TIMEOUT),
          m_allocator()
    {
    }

    void PollTimeout(unsigned pollTimeout)
    {
        m_pollTimeout = pollTimeout;
    }
    const unsigned& PollTimeout() const
    {
        return m_pollTimeout;
    }

    EventHandlerId AddEventHandler(const EventSlotBase &slot, const Event &eventDetails);

    void RemoveEventHandler(EventHandlerId id);

    int Poll(int &waitDuration);

 private:
    typedef IndexAllocator<EPollEntry> Allocator;

    EPoll    m_epoll;
    unsigned m_pollTimeout; // in millisecs

    Allocator m_allocator;
     
    struct epoll_event m_events[EPoll::MAX_EVENTS];
};

} //namespace eAccelero
#endif // __EACC_SockEvent_h__
