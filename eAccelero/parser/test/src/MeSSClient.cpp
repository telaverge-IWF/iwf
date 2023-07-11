#include "FlatUserAccess_caller.h"
#include "UserAccess_caller.h"
#include <string.h>

#define SERVER_COMP_ID  400
#define CLIENT_COMP_ID  500

using namespace eAccelero;

class MeSSClient: public MeSSComponent, 
                  public Stub::FlatUserAccessRespCbk, public Stub::UserAccessRespCbk
{
 public:
    MeSSClient()
        : MeSSComponent("IDLClient", CLIENT_COMP_ID),
          m_flatStub(NULL),
          m_pbStub(NULL)
    {
        this->RegisterUserAccessRespHandler();
        this->RegisterFlatUserAccessRespHandler();
    }
    ~MeSSClient()
    {
        if (m_flatStub) delete m_flatStub;
        if (m_pbStub)   delete m_pbStub;
    }

    void Initialize()
    {
        MeSSComponent::Initialize();

        std::cout << "Server component" << m_cmdArgs.servCompId << std::endl;
	    TopologyEvent compEvent(m_cmdArgs.servCompId);

        MeSSObj().TopSvc().Subscribe(EventSlot<TopologyEvent, MeSSClient>(this, 
                                        &MeSSClient::OnTopologyEvent),
                                     compEvent);
      
        MeSSEndpoint dest = {m_cmdArgs.servCompId, m_cmdArgs.servInst};
        m_flatStub = new Stub::FlatUserAccess(dest);
        m_pbStub   = new Stub::UserAccess(dest);
    }

    void Terminate()
    {
        MeSSComponent::Terminate();
    }

    int OnTopologyEvent(TopologyEvent &event)
    {
        if (event.NotificationType() == TopologyEvent::NOTIFY_TYPE_PUBLISHED)        
        {
            std::cout << "Server component up: " << event.Port() << std::endl;
            this->Trigger();

        }
        return 0;
    }

    void Trigger()
    {
        FlatUser user;
        memset(&user, 0, sizeof(user));
        strcpy(user.userName, "balaji");
        user.userId = 3002;

        m_flatStub->Login(user);
        std::cout << "--- Sent Flat Login req ---\n";
    }


    int LoginRespCbk(FlatResult *resCode)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "LoginRespCbk Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        std::cout << "-- Received Login resp cbk --\n";
        std::cout << "Res Code: " << resCode->resCode << " descr: " << resCode->descr
                  <<  std::endl;

        FlatUser user;
        memset(&user, 0, sizeof(user));
        strcpy(user.userName, "balaji");
        user.userId = 3002;
        m_flatStub->Logout(user);

        std::cout << "--- Send Flat Logout Req ---\n";
               
        return 0;
    }

    int LogoutRespCbk(FlatResult *resCode)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "LogoutRespCbk Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        std::cout << "-- Received Logout resp cbk --\n";
        std::cout << "Res Code: " << resCode->resCode << " descr: " << resCode->descr
                  <<  std::endl;

        User user;
        user.set_username("pbuser");
        user.set_userid(3000);
        m_pbStub->Login(user);
             
        return 0;
    }

	int LoginRespCbk(Result *resCode)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "PB LoginRespCbk Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }        
        std::cout << "-- Received PB Login resp cbk --\n";
        std::cout << "Res Code: " << resCode->resultcode() << " descr: " << resCode->descr()
                  <<  std::endl;

        User user;
        user.set_username("pbuser");
        user.set_userid(3000);
        m_pbStub->Logout(user);

        return 0;
    }

	int LogoutRespCbk(Result *resCode)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "Pb LogoutRespCbk Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }        
        std::cout << "-- Received Logout resp cbk --\n";
        std::cout << "Res Code: " << resCode->resultcode() << " descr: " << resCode->descr()
                  << std::endl;
        return 0;
    }

	int GetUsersRespCbk(Users *users)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "GetUsersRespCbk Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }        

        return 0;
    }

 protected:
    struct CmdArgs
    {
        CmdArgs()
            : servCompId("c", "scomp", "Server Component Id", true),
              servInst("s", "server", "Server Instance Id", true)
        {
        }
        CmdOption<int> servCompId;
        CmdOption<int> servInst;
    }m_cmdArgs;
    
    Stub::FlatUserAccess *m_flatStub;
    Stub::UserAccess     *m_pbStub;
};

int main(int argc, char *argv[])
{
    MeSSClient app1;
    try
    {
    	app1.Init(argc, argv);
        CLOG_NOTICE("Application initialized");
    	app1.Run();
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

