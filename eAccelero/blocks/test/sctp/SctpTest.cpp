
#include "Component.h"
#include "Dispatcher.h"
#include "SockEvent.h"
#include "Timer.h"
#include "SctpSock.h"

#include <sstream>

using namespace eAccelero;

class Connection: public SctpNotificationHandler
{
 public:
    Connection(int fd)
    {
        m_sock.FD() = fd;
        m_sock.RegisterNotifications(SctpSock::EVENT_ALL, this);

        EventSlot<SockEvent, Connection> slot(this, &Connection::OnSockEvent);
        m_evhId = ComponentBase::Instance().
                    GetDispatcher()->AddEventHandler(slot, SockEvent(fd));
        m_isServer = true;
    }

    Connection(SockAddrArray& local, SockAddrArray& remote)
        : m_sock(AF_INET, SOCK_STREAM)
    {
        m_sock.RegisterNotifications(SctpSock::EVENT_ALL, this);

        std::cout << "Binding on " << local << std::endl;
        m_sock.Bindx(local);
        std::cout << "Connecting to " << remote << std::endl;
        m_sock.Connectx(remote);

        EventSlot<SockEvent, Connection> slot(this, &Connection::OnSockEvent);
        m_evhId = ComponentBase::Instance().
                    GetDispatcher()->AddEventHandler(slot, SockEvent(m_sock.FD()));
        m_isServer = false;

    }

    ~Connection()
    {
        ConnClose();
    }

    void Send()
    {
        std::string st("Hello world! client");
        m_sock.Send((void*)st.c_str(), st.size());
    }

    int OnSockEvent(SockEvent &event)
    {
        if (event.Events() & SockEvent::READ_EVENT)
        {
            this->OnRead(event);
        }
        if (event.Events() & SockEvent::WRITE_EVENT)
        {
            this->OnWrite(event);
        }
        if (event.Events() & SockEvent::ERROR_EVENT ||
            event.Events() & SockEvent::HUP_EVENT)
        {
            this->OnError(event);
        }
        return 0;
    }

    int OnRead(SockEvent &event)
    {
        char buf[1024] = {0};
        int flags = 0;
        struct sctp_sndrcvinfo sinfo;
        CLOG_DEBUG("Read event received on socket connection");

        int ret = m_sock.Recvx(buf, 1024, flags, sinfo);
        if (flags & MSG_NOTIFICATION)
        {
            // nothing to do
            return 0;
        }
        CLOG_NOTICE("Received for assoc id %d", sinfo.sinfo_assoc_id);
        if (ret == 0)
        {
            ConnClose();
            return 0;
        }
        CLOG_NOTICE("Received: %s", buf);
        if (m_isServer)
        {
            std::string st("Hello world! response");
            m_sock.Send((void*)st.c_str(), st.size());
        }
        return 0;
    }

    int OnWrite(SockEvent &event)
    {
        CLOG_DEBUG("Write event received on socket connection");
        event.Events() = SockEvent::READ_EVENT;
        return 0;
    }

    int OnError(SockEvent &event)
    {
        CLOG_ERROR("Error event received on socket connection");

        ConnClose();
        return 0;
    }

    void ConnClose()
    {
        if (m_evhId != (unsigned)Socket::INVALID_FD)
        {
            CLOG_NOTICE("Closing connection");
            ComponentBase::Instance().
                GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_evhId);
            m_evhId = Socket::INVALID_FD;
            m_sock.Close();
        }
    }

    virtual void OnAssociationChange(sctp_assoc_change& event)
    {
        CLOG_NOTICE("--- Association change event received ---\n"
                    "  type: %d  flags: %d  length: %d state: %d\n"
                    "  error: %d ostream: %d  istream: %d assoc_id: %d",
                    event.sac_type, event.sac_flags, event.sac_length,
                    event.sac_state, event.sac_error, event.sac_outbound_streams,
                    event.sac_inbound_streams, event.sac_assoc_id);
    }

    virtual void OnPeerAddrChange(sctp_paddr_change& event)
    {
        SocketAddrIn addr((sockaddr*)&event.spc_aaddr);
        //memcpy((struct sockaddr*)addr, &event.spc_aaddr, addr.len());
        std::stringstream sstr;
        sstr << addr; 
        CLOG_NOTICE("--- Peer address change event recieved ---"
                    "  type: %d  flags: %d   length: %d\n"
                    "  addr: %s\n"
                    "  state: %d  error: %d  assoc_id: %d",
                    event.spc_type, event.spc_flags, event.spc_length,
                    sstr.str().c_str(),
                    event.spc_state, event.spc_error, event.spc_assoc_id);
    }

    virtual void OnSendFailed(sctp_remote_error& event)
    {
        CLOG_NOTICE("--- SCTP Send failed ---");
    }

    virtual void OnRemoteError(sctp_send_failed& event)
    {
        CLOG_NOTICE("--- SCTP remote error ---");
    }

    virtual void OnSctpShutdown(sctp_shutdown_event& event)
    {
        CLOG_NOTICE("--- SCTP Shutdown event received for assoc %d ---", event.sse_assoc_id);
        ConnClose();
    }

    virtual void OnPartialDelivery(sctp_pdapi_event& event)
    {
        CLOG_NOTICE("--- SCTP partial delivery event ---");
    }

    virtual void OnAdaptationIndication(sctp_adaptation_event& event)
    {
        CLOG_NOTICE("--- SCTP Adaptation Indication received ---");
    }

    virtual void OnSctpAuthIndication(sctp_authkey_event& event)
    {
        CLOG_NOTICE("--- Auth Indication received ---");
    }

    virtual void OnSenderDry(sctp_sender_dry_event& event)
    {
        CLOG_NOTICE("--- Sender Dry event ---");
    }

 protected:
    SctpSock m_sock;
    EventHandlerId m_evhId;
    bool m_isServer;
};


class SctpTest: public ComponentBase, public SctpNotificationHandler
{
 public:
    SctpTest()
        : ComponentBase("SctpTest", 1),
          m_sock(AF_INET, SOCK_STREAM),
          m_srvEvH(-1),
          m_clientConn(NULL),
          m_serverConn(NULL)
    {
    }
    ~SctpTest()
    {
    }

    virtual void Initialize()
    {
        ComponentBase::Initialize();

        const char* primary = ((const std::string&)m_config.primary).c_str();
        const char* secondary = ((const std::string&)m_config.secondary).c_str();

        m_localAddrs.Add(SocketAddrIn(IPAddress(primary), m_config.port));
        m_localAddrs.Add(SocketAddrIn(IPAddress(secondary), m_config.port));

        if (m_config.serverPort)
        {
            const char* serverPrimary = ((const std::string&)m_config.serverPrimary).c_str();
            const char* serverSecondary = ((const std::string&)m_config.serverSecondary).c_str();
            m_remoteAddrs.Add(SocketAddrIn(IPAddress(serverPrimary), m_config.serverPort));
            m_remoteAddrs.Add(SocketAddrIn(IPAddress(serverSecondary), m_config.serverPort));
            CLOG_NOTICE("Client mode");
        }
        else
        {
            // Server
            m_sock.RegisterNotifications(SctpSock::EVENT_ALL, this);
            m_sock.Bindx(m_localAddrs);
            m_sock.Listen();

            EventSlot<SockEvent, SctpTest> slot(this, &SctpTest::OnSockEvent);
            m_srvEvH = this->GetDispatcher()->AddEventHandler(slot, 
                    SockEvent(m_sock.FD(), SockEvent::READ_EVENT));
            CLOG_NOTICE("Server listening on address");
        }

        m_timerId = this->GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, SctpTest>(this,
                        &SctpTest::OnTimer),
                    TimerEvent(5000));
    }

    virtual void Terminate()
    {
        if (m_clientConn) delete m_clientConn;
        if (m_serverConn) delete m_serverConn;

        ComponentBase::Terminate();
    }

    int OnTimer(TimerEvent& ev)
    {
        if (m_config.serverPort )
        {
            if (m_clientConn == NULL)
            {
                // We are a client
                CLOG_NOTICE("Initiating connection");
                m_clientConn = new Connection(m_localAddrs, m_remoteAddrs);
            }
            else
            {
                //send message
                CLOG_NOTICE("Sending Message");
                m_clientConn->Send();
            }
        }
        else
        {
            // nothing on the server
        }
        return 1;
    }
    int OnSockEvent(SockEvent &event)
    {
        // We should be getting only read event here
        if (event.Events() & SockEvent::READ_EVENT)
        {
            int connFd;
            connFd = m_sock.Accept();

            CLOG_NOTICE("Accepted connection %d", connFd);

            m_serverConn = new Connection(connFd);
        }
        return 0;
    } 
    
    virtual void OnAssociationChange(sctp_assoc_change& event)
    {
        CLOG_NOTICE("--- Association change event received ---\n"
                    "  type: %d  flags: %d  length: %d state: %d\n"
                    "  error: %d ostream: %d  istream: %d assoc_id: %d",
                    event.sac_type, event.sac_flags, event.sac_length,
                    event.sac_state, event.sac_error, event.sac_outbound_streams,
                    event.sac_inbound_streams, event.sac_assoc_id);
    }
    virtual void OnPeerAddrChange(sctp_paddr_change& event)
    {
        SocketAddrIn addr((sockaddr*)&event.spc_aaddr);
        //memcpy((struct sockaddr*)addr, &event.spc_aaddr, addr.len());
        std::stringstream sstr;
        sstr << addr; 
        CLOG_NOTICE("--- Peer address change event recieved ---"
                    "  type: %d  flags: %d   length: %d\n"
                    "  addr: %s\n"
                    "  state: %d  error: %d  assoc_id: %d",
                    event.spc_type, event.spc_flags, event.spc_length,
                    sstr.str().c_str(),
                    event.spc_state, event.spc_error, event.spc_assoc_id);
    }

    struct CmdArgs
    {
        CmdArgs()
            : primary("a", "pri", "Local Primary IP", true),
              secondary("b", "sec", "Local Secondary IP", true),
              port("p", "port", "Local port", true),
              serverPrimary("c", "server-pri", "Server Primary IP",false),
              serverSecondary("d", "server-sec", "Server Seconday IP", false),
              serverPort("s", "server-port", "Server Port", "0")
        {
        }
        CmdOption<std::string> primary;
        CmdOption<std::string> secondary;
        CmdOption<int> port;
        CmdOption<std::string> serverPrimary;
        CmdOption<std::string> serverSecondary;
        CmdOption<int> serverPort;
    } m_config;

 protected:
    SctpSock m_sock;
    EventHandlerId m_srvEvH;
    Connection *m_clientConn;
    Connection *m_serverConn;
    EventHandlerId m_timerId;

    SockAddrArray m_localAddrs;
    SockAddrArray m_remoteAddrs;

};


int main(int argc, char *argv[])
{
    SctpTest app;
    try
    {
        app.Init(argc, argv);

        CLOG_NOTICE("Application initialized");

        app.Run();
    }
    catch(CmdParseException &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    }
#if 0
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
#endif
    CLOG_NOTICE("Application exiting");

    return 0;
}

