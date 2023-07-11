#include "Component.h"
#include "Dispatcher.h"
#include "SockEvent.h"
#include "Tipc.h"

using namespace eAccelero;

#define TEST_APP_SRV    100

class Connection
{
 public:
    Connection(int fd)
    {
        m_sock.FD() = fd;

        EventSlot<SockEvent, Connection> slot(this, &Connection::OnSockEvent);
        m_evhId = ComponentBase::Instance().
                    GetDispatcher()->AddEventHandler(slot, SockEvent(fd));
    }

    Connection(unsigned toSvc, unsigned toInst)
        : m_sock(SOCK_SEQPACKET)
    {
        TIPCAddr addr(TIPC_CLUSTER_SCOPE);
        addr.SetName(toSvc, toInst);

        std::cout << "Connecting to " << addr << std::endl;
        m_sock.Connect(addr);

        EventSlot<SockEvent, Connection> slot(this, &Connection::OnSockEvent);
        m_evhId = ComponentBase::Instance().
                    GetDispatcher()->AddEventHandler(slot, SockEvent(m_sock.FD()));

        std::string st("Hello world! client");
        m_sock.Send((void*)st.c_str(), st.size());
    }

    ~Connection()
    {
        ConnClose();
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
        static int i = 0;
        char buf[128] = {0};
        CLOG_DEBUG("Read event received on socket connection");

        int ret = m_sock.Recv(buf, 128);
        if (ret == 0)
        {
            ConnClose();
            return 0;
        }
        CLOG_NOTICE("Received: %s", buf);
        if (i == 0)
        {
            std::string st("Hello world! again");
            m_sock.Send((void*)st.c_str(), st.size());
            i++;
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

 protected:
    TIPCSock m_sock;
    EventHandlerId m_evhId;
};

class TestApp: public ComponentBase
{
 public:
    TestApp()
        : ComponentBase("TestApp", TEST_APP_SRV),
          m_instance(0),
          m_sock(SOCK_SEQPACKET),
          m_srvEvH(0),
          m_topSrv(SOCK_SEQPACKET),
          m_srvInst(0),
          m_rdmSock(SOCK_RDM),
          m_rdmEvh(0),
          m_dgmSock(SOCK_DGRAM),
          m_dgmEvh(0),
          m_clientConn(NULL),
          m_serverConn(NULL)
    {
    }

    void Initialize()
    {
        ComponentBase::Initialize();

        m_instance = m_cmdArgs.instance;
        m_srvInst  = m_cmdArgs.srvInst;

        TIPCAddr addr(TIPC_CLUSTER_SCOPE);
        addr.SetNameSeq(TEST_APP_SRV, m_instance, m_instance);
        m_sock.Bind(addr);
        m_sock.Listen();

        EventSlot<SockEvent, TestApp> slot(this, &TestApp::OnSockEvent);
        m_srvEvH = this->GetDispatcher()->AddEventHandler(slot, 
                    SockEvent(m_sock.FD(), SockEvent::READ_EVENT));

        TIPCAddr rdmAddr(TIPC_CLUSTER_SCOPE);
        rdmAddr.SetNameSeq(TEST_APP_SRV, m_instance+1, m_instance+1);
        m_rdmSock.Bind(rdmAddr);
        m_rdmEvh = this->GetDispatcher()->AddEventHandler(
                    EventSlot<SockEvent, TestApp>(this, &TestApp::OnRdmEvent),
                    SockEvent(m_rdmSock.FD(), SockEvent::READ_EVENT));
       
        addr.SetNameSeq(TEST_APP_SRV, m_instance+2, m_instance+2);
        m_dgmSock.Bind(addr);
        m_dgmEvh = this->GetDispatcher()->AddEventHandler(
                    EventSlot<SockEvent, TestApp>(this, &TestApp::OnDgmEvent),
                    SockEvent(m_dgmSock.FD(), SockEvent::READ_EVENT));                    

        TIPCAddr topAddr(TIPC_CLUSTER_SCOPE);
        topAddr.SetName(TIPC_TOP_SRV, TIPC_TOP_SRV);
        m_topSrv.Connect(topAddr);

        EventSlot<SockEvent, TestApp> clSlot(this, &TestApp::OnTopSrvEvent);
        this->GetDispatcher()->AddEventHandler(clSlot, 
                    SockEvent(m_topSrv.FD(), SockEvent::READ_EVENT));

        std::cout << "Seq sock: <fd:" << m_sock.FD() << ", ev:" << m_srvEvH << ">\n"
                  << "RDM sock: <fd:" << m_rdmSock.FD() << ", ev:" << m_rdmEvh << ">\n"
                  << "DGM sock: <fd:" << m_dgmSock.FD() << ", ev:" << m_dgmEvh << ">\n"
                  << "TOP sock: <fd:" << m_topSrv.FD() << ">\n\n";
                  
        TIPCSubscr sub(TEST_APP_SRV, m_srvInst, m_srvInst, TIPC_SUB_PORTS, 5000);
        m_topSrv.Send((struct tipc_subscr*)sub, sizeof(struct tipc_subscr));

        CLOG_NOTICE("Sending toplogy subscription");
    }

    void Terminate()
    {
        if (m_clientConn != NULL)
        {
            delete m_clientConn;
            m_clientConn = NULL;
        }
        if (m_serverConn != NULL)
        {
            delete m_serverConn;
            m_serverConn = NULL;
        }

        this->GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_rdmEvh);
        m_rdmSock.Close();
        this->GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_dgmEvh);
        m_dgmSock.Close();        

        this->GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, m_srvEvH);
        m_sock.Close();
        ComponentBase::Terminate();
    }

    int OnSockEvent(SockEvent &event)
    {
        // We should be getting only read event here
        if (event.Events() & SockEvent::READ_EVENT)
        {
            TIPCAddr from;
            int connFd;
            connFd = m_sock.Accept(from);

            CLOG_NOTICE("Accepted connection %d", connFd);
            std::cout << from << std::endl;

            m_serverConn = new Connection(connFd);
        }
        return 0;
    }

    int OnTopSrvEvent(SockEvent& event)
    {
        bool close = false;
        if (event.Events() & SockEvent::READ_EVENT)
        {
            TIPCEvent te;
            m_topSrv.Recv((struct tipc_event*)te, sizeof(tipc_event));

            if (te.Event() == TIPC_SUBSCR_TIMEOUT)
            {
                CLOG_NOTICE("Server not up yet. Timeout occurred");
            }
            else if (te.Event() == TIPC_PUBLISHED)
            {
                std::cout << "Published Event:" << te << std::endl;
                // Now connect to server

                if (m_instance == 10)
                {
                    m_clientConn = new Connection(TEST_APP_SRV, m_srvInst);
                
                    TIPCAddr addr(TIPC_CLUSTER_SCOPE);
                    addr.SetNameSeq(TEST_APP_SRV, m_srvInst+1, m_srvInst+1);
                    
                    const char *msg = "RDM data message";
                    m_rdmSock.Send(addr, (void*)msg, strlen(msg)+1);
                    
                    addr.SetNameSeq(TEST_APP_SRV, m_srvInst+2, m_srvInst+2);
                    const char *msg1 = "DGM data message";
                    m_dgmSock.Send(addr, (void*)msg1, strlen(msg1)+1);

                }               
            }
            else
            {
                // TIPC_WITHDRAWN
            }
            this->GetDispatcher()->RemoveEventHandler(SOCK_EVENT_TYPE, event.EvhId());
            m_topSrv.Close();
            close = true;
        }
        if (!close && (event.Events() & SockEvent::WRITE_EVENT))
        {
            event.Events() = SockEvent::READ_EVENT;
        }
        return 0;
    }
    
    int OnRdmEvent(SockEvent& event)
    {
        if (event.Events() & SockEvent::READ_EVENT)
        {
            char buf[256] = {0};
            CLOG_NOTICE("RDM event received:");
            
            m_rdmSock.Recv(buf, 256);
            
            std::cout << "Received: " << buf << std::endl;
        }
        return 0;
    }
    int OnDgmEvent(SockEvent& event)
    {
        if (event.Events() & SockEvent::READ_EVENT)
        {
            char buf[256] = {0};
            CLOG_NOTICE("DGM event received:");
            
            m_dgmSock.Recv(buf, 256);
            
            std::cout << "Received: " << buf << std::endl;
        }
        return 0;
    }    

    struct CmdArgs
    {
        CmdArgs()
            : instance("i", "inst", "Application instance", true),
              srvInst("s", "server-inst", "Server instance to connecto", true)
        {
        }
        CmdOption<int>  instance;
        CmdOption<int>  srvInst;
    }m_cmdArgs;
 protected:
    int m_instance;
    TIPCSock m_sock;
    EventHandlerId m_srvEvH;

    TIPCSock m_topSrv;
    int m_srvInst;
    
    TIPCSock m_rdmSock;
    EventHandlerId m_rdmEvh;
    
    TIPCSock m_dgmSock;
    EventHandlerId m_dgmEvh;

    Connection *m_clientConn;
    Connection *m_serverConn;
};

int main(int argc, char *argv[])
{
    TestApp app;
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

