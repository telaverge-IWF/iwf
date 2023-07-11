#include "MeSSTest.h"
#include "ABC_caller.h"
#include <iostream>
//using namespace eAccelero;

class SampleClient:public MeSSComponent
{
public:
	SampleClient()
	        :MeSSComponent("SampleClient", CLIENT_COMP_ID)
	{

	}

        void Initialize()
	{
	    MeSSComponent::Initialize();
	    TopologyEvent compEvent(SERVER_COMP_ID);

            MeSSObj().TopSvc().Subscribe(EventSlot<TopologyEvent, SampleClient>(this, &SampleClient::OnServerEvent),compEvent);
	    MeSSEndpoint dest = {SERVER_COMP_ID, 10};
 	    m_stubObj = new Stub::ABC(dest, flags=0);
	    Stub::ABC::Setmethod1RespHandler<SampleClient>(this,&SampleClient::method1RespCbk);
	    Stub::ABC::Setmethod2RespHandler<SampleClient>(this,&SampleClient::method2RespCbk);
	}

	void Terminate()
    	{
       	     MeSSComponent::Terminate();
        }

	int OnServerEvent(TopologyEvent &event)
    	{
        	static int once = 0;
        	if (event.NotificationType() == TopologyEvent::NOTIFY_TYPE_PUBLISHED)
        	{
            		std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
                	if (once == 0)
            		{
	   			this->Trigger1();		
                		once++;
            		}
        	}
	        return 0;
    	}

	//callback function triggered when server acknowledges for method 1
	int method1RespCbk(Resp1 *r2)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
        	{
        		std::cout << "Method 1 Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
        		return 0;
        	}

		std::cout << "METHOD_1_RESP: " << r2->id << " " << r2->val
                  << " " << r2->result << std::endl;

		// For testing purpose Trigger2() is triggering here
		this->Trigger2();
		return 0;
	}

	//callback function triggered when server acknowledges for method 2
	int  method2RespCbk(Resp2  *r2)
  	{
		 if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
                {
                        std::cout << "Method 2 Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
                        return 0;
                }

                std::cout << "METHOD_2_RESP: " << r2->id
                  << " " << r2->result << std::endl;

                return 0;
	}

protected:
	Stub::ABC *m_stubObj;
	unsigned flags;
	void Trigger1()
	{	
        	Req1 req;
	        req.id = 100;
        	strcpy(req.str, "Method 1 ");
		m_stubObj->method1(req);

	        std::cout << "METHOD_1_REQ >> " << std::endl;
	}

	void Trigger2()
	{
	        Req2 req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "Method 2 ");
		m_stubObj->method2(req);
	        std::cout << "METHOD_2_REQ >> " << std::endl;
	}

};

int main(int argc, char *argv[])
{
	SampleClient *app = NULL;
	
	try 
	{
	     app = new SampleClient();
	     app->Init(argc,argv);
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
	if(app) delete app;
	return 0;
}	

