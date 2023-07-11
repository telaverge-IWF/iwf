
#include "Component.h"
#include "Dispatcher.h"
#include "SockEvent.h"
#include "Timer.h"
#include "SctpSock.h"

#include <sstream>

using namespace eAccelero;

class Association
{
 public:
    Association(const SctpSock& sock, int assocId)
        : m_sock(sock),
          m_assocId(assocId),
          m_closed(false)
    {
    }
    ~Association()
    {
        if (!m_closed)
        {
            // Socket not owned by me
            this->Close();
        }
        m_sock.Release();
    }

    int Send(void *msg, int msgLen, uint16_t flags = 0, 
             uint16_t streamNo = 0, uint32_t ppid = 0)
    {
        struct sctp_sndrcvinfo sinfo;
        memset(&sinfo, 0, sizeof(struct sctp_sndrcvinfo));
        sinfo.sinfo_flags = flags;
        sinfo.sinfo_stream = streamNo;
        sinfo.sinfo_assoc_id = m_assocId;
        sinfo.sinfo_ppid = htonl(ppid);

        return m_sock.Sendx(msg, msgLen, 0, sinfo);
    }

    void OnRead(void *msg, int msgLen)
    {
        CLOG_NOTICE("Received: %d %s", m_assocId, msg);
    }

    void Close()
    {
        CLOG_NOTICE("Closing the association: %d %d", m_assocId, m_sock.FD());
        this->Send(NULL, 0, SCTP_EOF);
        // Send with SCTP_EOF flag
    }

    void Abort()
    {
        CLOG_NOTICE("Aborting the association: %d %d", m_assocId, m_sock.FD());
        this->Send(NULL, 0, SCTP_ABORT);
    }

    void SetClosed(bool closed = true)
    {
        m_closed = closed;
    }
    

 protected:
    SctpSock m_sock;
    int m_assocId;
    bool m_closed;
};

class SctpTest: public ComponentBase, public SctpNotificationHandler
{
 public:
    SctpTest()
        : ComponentBase("SctpTest", 1),
          m_sock(AF_INET, SOCK_SEQPACKET),
          m_evhId(-1),
          m_timerId(-1),
          m_counter(0)
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

        m_sock.RegisterNotifications(SctpSock::EVENT_ALL, this);
        m_sock.Bindx(m_localAddrs);
        m_sock.Listen();
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
            CLOG_NOTICE("Server mode.");
        }

        EventSlot<SockEvent, SctpTest> slot(this, &SctpTest::OnSockEvent);
        m_evhId = this->GetDispatcher()->AddEventHandler(slot, 
                SockEvent(m_sock.FD(), SockEvent::READ_EVENT));

        m_timerId = this->GetDispatcher()->AddEventHandler(
                    EventSlot<TimerEvent, SctpTest>(this,
                        &SctpTest::OnTimer),
                    TimerEvent(5000));
    }

    virtual void Terminate()
    {
        ConnClose();
        ComponentBase::Terminate();
    }

    int OnTimer(TimerEvent& ev)
    {
        if (m_config.serverPort)
        {
            if (m_assocMap.size() == 0)
            {
                // We are a client
                int assocId = 0;
                CLOG_NOTICE("Initiating connections");
                std::cout << "Connecting to " << m_remoteAddrs << std::endl;
                m_sock.Connectx(m_remoteAddrs, &assocId);

                CLOG_NOTICE("Creating new association: %d", assocId);
                Association* assoc = new Association(m_sock, assocId);
                m_assocMap[assocId] = assoc;
            }
            else
            {
                if (m_counter == 5)
                {
                    m_assocMap.begin()->second->Close();
                    return 0;
                }
                m_counter++;
                //send message
                std::string msg("Hello world! client");
                CLOG_NOTICE("Sending Message");
                m_assocMap.begin()->second->Send((void*)msg.c_str(), msg.size());
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
            AssocClose(sinfo.sinfo_assoc_id, false);
            return 0;
        }
        m_assocMap[sinfo.sinfo_assoc_id]->OnRead(buf, ret);
        if (m_config.serverPort == 0)
        {
            std::string st("Hello world! response");
            m_assocMap[sinfo.sinfo_assoc_id]->Send((void*)st.c_str(), st.size());
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
            std::map<int, Association*>::iterator it;
            for (it = m_assocMap.begin(); it != m_assocMap.end(); it++)
            {
                delete it->second;
            }

            CLOG_NOTICE("Closing connection");
            ComponentBase::Instance().
                GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_evhId);
            m_evhId = Socket::INVALID_FD;
            m_sock.Close();
        }
    }

    void AssocClose(int assocId, bool closeAssoc = true)
    {
        Association* assoc = m_assocMap[assocId];
        m_assocMap.erase(assocId);
        if (!closeAssoc) assoc->SetClosed(true);
        delete assoc;
    }

    virtual void OnAssociationChange(sctp_assoc_change& event)
    {
        CLOG_NOTICE("--- Association change event received ---\n"
                    "  type: %d  flags: %d  length: %d state: %d\n"
                    "  error: %d ostream: %d  istream: %d assoc_id: %d",
                    event.sac_type, event.sac_flags, event.sac_length,
                    event.sac_state, event.sac_error, event.sac_outbound_streams,
                    event.sac_inbound_streams, event.sac_assoc_id);
        // New association. Add it to association map
        if (m_config.serverPort == 0)
        {
            // Server, create a new association
            Association *assoc = new Association(m_sock, event.sac_assoc_id);
            CLOG_NOTICE("Creating association for %d", event.sac_assoc_id);
            m_assocMap[event.sac_assoc_id] = assoc;
        }
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
        AssocClose(event.sse_assoc_id, false);
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

private:
    SctpSock m_sock;
    EventHandlerId m_evhId;
    EventHandlerId m_timerId;
    std::map<int, Association*> m_assocMap;

    SockAddrArray m_localAddrs;
    SockAddrArray m_remoteAddrs;
    unsigned m_counter;
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
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    CLOG_NOTICE("Application exiting");

    return 0;
}

