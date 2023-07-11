
#include "MeSSComponent.h"
#include "MeSSTest.h"
#include "TopSrv.h"
#include "testing.pb.h"
#if 0
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#endif
#include<string>
#include<iostream>
using namespace google::protobuf::io;
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
            MethodSlot<MeSSServer, GetConfigReq_pb, GetConfigResp_pb,
			PBEncodingTraits, PBEncodingPolicy>(this, &MeSSServer::GetConfig));
        this->RegisterMethod(M_SET_CONFIG, 
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::SetConfig));
        this->RegisterMethod(M_MULTICAST_REQ, 
            MethodSlot<MeSSServer, SetConfigReq, SetConfigResp>(this, &MeSSServer::MulticastReq));  
    }
    
    int GetConfig(GetConfigReq_pb *req, GetConfigResp_pb *resp)
    {
		GetConfigReq_pb req1;
		std::string data;
		std::cout<<"got instances"<<std::endl;
  	//	std::cout<<"Message is latest"<<req->DebugString()<<std::endl;
		std::cout<<"Message ID="<<req->id()<<std::endl;
		std::cout<<"Message string="<<req->str()<<std::endl;
        //resp->id = 120;
        resp->set_id(req->id());
        resp->set_val(120);
        resp->set_result("get_config success");

        // Try a rebind
        MeSSEndpoint newId = {SERVER_COMP_ID, 25};
        this->MeSSObj().Rebind(newId);
        
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
    
    if (app) delete app;    

    return 0;
}
