
#include "MeSSComponent.h"
#include "MeSSTest.h"

#include <iostream>
#include "testing.pb.h"

#if 0
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#endif

using namespace eAccelero;

using namespace google::protobuf::io;

class MeSSClient: public MeSSComponent
{
public:
    MeSSClient()
        : MeSSComponent("MeSSClient", CLIENT_COMP_ID)
    {
        MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_GET_CONFIG), 
            CallbackSlot<MeSSClient, GetConfigResp_pb, 
                PBEncodingTraits, PBEncodingPolicy>(this, &MeSSClient::GetConfigRespCbk));

        MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_SET_CONFIG), 
            CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::SetConfigRespCbk));

        MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_SET_CONFIG+100), 
            CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::UnhandledRespCbk));
            
        MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_MULTICAST_REQ), 
            CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::MulticastRespCbk));            
    }
    
    void Initialize()
    {
        MeSSComponent::Initialize();
        
        TopologyEvent compEvent(SERVER_COMP_ID);
        MeSSObj().TopSvc().Subscribe(
            EventSlot<TopologyEvent, MeSSClient>(this, &MeSSClient::OnServerEvent),
            compEvent);          
    }
    void Terminate()
    {
        MeSSComponent::Terminate();
    }
   
    int GetConfigRespCbk(GetConfigResp_pb *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "GetConfig Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        
        std::cout << "GET_CONFIG_RESP: " << resp->id() << " " << resp->val()
                  << " " << resp->result() << std::endl;
                  
        // Now do set config
        TimeVal::uSleep(1000 * 100);
         
        this->SetConfig();
        
        this->UnhandledReq();
        
        this->MulticastReq();
        
        return 0;
    }
    int SetConfigRespCbk(SetConfigResp *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "SetConfig Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        
        std::cout << "SET_CONFIG_RESP: " << resp->id 
                  << " " << resp->result << std::endl; 
        return 0;
    }
    int UnhandledRespCbk(SetConfigResp *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "UnhandledReq Request message failed. ERROR: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        int unexpected = 0;
        EACC_ASSERT(unexpected);
        return 0;
    }
    int MulticastRespCbk(SetConfigResp *resp)
    {
        if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        {
            std::cout << "Multicast Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
            return 0;
        }
        
        std::cout << "MULTICAST_CONFIG_RESP: " << resp->id 
                  << " " << resp->result << std::endl; 
        return 0;
    }
    
    int OnServerEvent(TopologyEvent &event)
    {
        static int once = 0;
        if (event.NotificationType() == TopologyEvent::NOTIFY_TYPE_PUBLISHED)
        {
            std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
            if (once == 0)
            {
                this->GetConfig();
                once++;
            }
        }
        return 0;
    }

protected:
    
    void GetConfig()
    {
        MessageId msgId = MakeMsgId(I_TEST_ID, M_GET_CONFIG);
        MeSSEndpoint dest = {SERVER_COMP_ID, 10};
        //GetConfigReq req;
		GetConfigReq_pb req;
        req.set_id(10);
        //strcpy(req.str, "GetConfig");
        req.set_str("GetConfig");

        std::cout << "GET_CONFIG_REQ >> " << req.id() << " " << req.ByteSize() <<std::endl;
        MeSSObj().Send(dest, msgId, req, NULL, MeSS::SEQ_DELIVERY);
    }
    void SetConfig()
    {
        MessageId msgId = MakeMsgId(I_TEST_ID, M_SET_CONFIG);
        MeSSEndpoint dest = {SERVER_COMP_ID, 25};
        SetConfigReq req;
        memset(&req, 0, sizeof(req));
        req.id = 100;
        req.val = 10;
        strcpy(req.descr, "SetConfig");
        
        std::cout << "SET_CONFIG_REQ >> " << std::endl;
        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req), NULL, MeSS::SEQ_DELIVERY);
    }
    void UnhandledReq()
    {
        // Sending an invalid message, not handled at the server
        MessageId msgId = MakeMsgId(I_TEST_ID, M_SET_CONFIG+100);
        MeSSEndpoint dest = {SERVER_COMP_ID, 25};
        SetConfigReq req;
        memset(&req, 0, sizeof(req));
        req.id = 100;
        req.val = 10;
        strcpy(req.descr, "Unhandled");
        
        std::cout << "Unhandled_REQ >> " << std::endl;
        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req), NULL, MeSS::SEQ_DELIVERY);
    }
    void MulticastReq()
    {
        MessageId msgId = MakeMsgId(I_TEST_ID, M_MULTICAST_REQ);
        MeSSEndpoint dest = {SERVER_COMP_ID, MESS_MULTICAST_ACTIVE};
        SetConfigReq req;
        memset(&req, 0, sizeof(req));
        req.id = 100;
        req.val = 10;
        strcpy(req.descr, "MulticastReq");
        
        std::cout << "MULTICAST_REQ >> " << std::endl;
        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
    }    
};

int main(int argc, char *argv[])
{
    MeSSClient *app = NULL;
    try
    {
        app = new MeSSClient();
        
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
