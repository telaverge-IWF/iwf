#include "MeSSComponent.h"
#include "MeSSTest.h"
#include "TopSrv.h"

using namespace eAccelero;

class MeSSServer: public MeSSComponent, public Interface
{
public:
    MeSSServer()
        : MeSSComponent("MeSSServer", SERVER_COMP_ID),
          Interface(I_TEST_ID),
          m_counter(42)
    {
        MeSSObj().RegisterInterface(this);
    }
    
    void Initialize()
    {
        MeSSComponent::Initialize();
      
    }
    void Terminate()
    {
        MeSSComponent::Terminate();
    }
    
    void RegisterMethods()
    {
        std::cout << "Registering methods..." << std::endl;
        this->RegisterMethod(M_GET_CONFIG, 
            MethodSlot<MeSSServer, GetConfigReq, GetConfigResp>(this, &MeSSServer::GetConfig));

	this->RegisterMethod(M_SET_CONFIG,
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::SetConfig));

	this->RegisterMethod(M_MULTICAST_REQ,
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::MulticastReq));

	this->RegisterMethod(M_MULTICAST_REQ1,
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::MulticastReq1));

	this->RegisterMethod(M_DELAY_RESP,
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::DelayRespReq));

	this->RegisterMethod(M_TIMEOUT_RESP,
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::TimeoutRespReq));

	this->RegisterMethod(M_MULTICAST_DELAY_REQ,
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::MulticastDelayReq));

	this->RegisterMethod(M_HIGH_NOOF_RESP,
            MethodSlot<MeSSServer, GetConfigReq, GetConfigResp>(this, &MeSSServer::HighNoOfReq));
    }
    
    int GetConfig(GetConfigReq *req, GetConfigResp *resp)
    {
        std::cout << "GET_CONFIG_REQ: " << req->id << " " << req->str << std::endl;
        
        resp->id = req->id;
        resp->val = 120;
        strcpy(resp->result, "get_config success");
        
        return 0;
    }

    int HighNoOfReq(GetConfigReq *req, GetConfigResp *resp)
    {
        //std::cout << "GET_CONFIG_REQ: " << req->id << " " << req->str << std::endl;
        
        resp->id = req->id;
        resp->val = 120;
        strcpy(resp->result, "get_config success");
        
        return 0;
    }

    int SetConfig(SetConfigReq *req, SetConfigResp *resp)
    {
        std::cout << "SET_CONFIG_REQ: " << req->id << " " << req->val
                  << " "<< req->descr << std::endl;

        resp->id = req->id;
        strcpy(resp->result, "set_config success");

        return 0;
    }


    int MulticastReq(SetConfigReq *req, SetConfigResp *resp)
    {
        std::cout << "MULTICAST_REQ: " << req->id << " " << req->val
                  << " "<< req->descr << std::endl;

        resp->id = m_counter + MeSSObj().Self().instance;
        strcpy(resp->result, "multicast_req success");

        return 0;
    }


    int MulticastReq1(SetConfigReq *req, SetConfigResp *resp)
    {
        std::cout << "MULTICAST_REQ 1 : " << req->id << " " << req->val
                  << " "<< req->descr << std::endl;

        resp->id = m_counter + MeSSObj().Self().instance;	
        strcpy(resp->result, "multicast_req success 1");

        return 0;
    }

    int DelayRespReq(SetConfigReq *req, SetConfigResp *resp)
    {
        std::cout << "DELAY_REQ  : " << req->id << " " << req->val
                  << " "<< req->descr << std::endl;

        resp->id = m_counter + MeSSObj().Self().instance;
        strcpy(resp->result, "Delay Request success");
        sleep(20);
        return 0;
    }

    int TimeoutRespReq(SetConfigReq *req, SetConfigResp *resp)
    {
        std::cout << "TIMEOUT_REQ  : " << req->id << " " << req->val
                  << " "<< req->descr << std::endl;

        resp->id = m_counter + MeSSObj().Self().instance;
        strcpy(resp->result, "Time out req success");
        sleep(40);
        return 0;
    }

    int MulticastDelayReq(SetConfigReq *req, SetConfigResp *resp)
    {
        std::cout << "MULTICAST_DELAY_REQ: " << req->id << " " << req->val
                  << " "<< req->descr << std::endl;

        resp->id = m_counter + MeSSObj().Self().instance;
	sleep(20);
        strcpy(resp->result, "multicast_delay_req success");

        return 0;
    }


protected:
    unsigned m_counter;
};


int main(int argc, char *argv[])
{
    MeSSServer *app = NULL;
    try
    {
        app = new MeSSServer();
        
        app->Init(argc, argv);

        CLOG_NOTICE("Application initialized");

        app->Run();
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
    
    if (app) delete app;    

    return 0;
}
