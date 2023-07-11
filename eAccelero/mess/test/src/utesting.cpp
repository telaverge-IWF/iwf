// This utesting.cpp file is the client application for testing the unit test cases of MeSS


#include <signal.h>
//#include <sys/time.h>

#include "MeSSComponent.h"
#include "MeSSTest.h"

#include <iostream>
#include <thread>

using namespace eAccelero;

unsigned int gReqCount= 1;
unsigned int gRespCount= 1;
unsigned int gPassed;
unsigned int gFailed;

#if 0
struct TimerData
{
    TimeVal start;
    TimeVal end;
} s_data[20];

struct timeval start[25000], end[25000],end1;
long mtime,mtime1, seconds, useconds;
#endif
int g_stop = 0;

static const int SLEEP_DURATION = (20 * 1000);

void RunTest()
{
    TimeVal start, end;
    MessageId msgId = MakeMsgId(I_TEST_ID, M_HIGH_NOOF_RESP);
    MeSSEndpoint dest = {SERVER_COMP_ID, 10};
    GetConfigReq req;
    req.id = 100;
    strcpy(req.str, "GetConfigGetConfigGetConfigGetConfigGetConfigGetConfigGetCon");
    int sleepTime = SLEEP_DURATION;

    while (!g_stop)
    {
        start.now();
        for(int i=1; i< 2000; i++)
        {
            //MeSSComponent::Instance().MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req),
            //    NULL, MeSS::SEQ_DELIVERY);
            MeSSComponent::Instance().MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
        }
        end.now();
        end -= start;

        sleepTime = SLEEP_DURATION - ((timeval*)end)->tv_usec;
        if (sleepTime > 0)
        {
            TimeVal::uSleep(sleepTime);
        }
        else
        {
            std::cout << "Oops.. send duration exceed sleep duration!!\n";
        }
    }

}

class MeSSClient: public MeSSComponent
{
public:
	MeSSClient()
        	: MeSSComponent("MeSSClient", CLIENT_COMP_ID),
              m_thread(NULL)
	{
		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_GET_CONFIG), 
		CallbackSlot<MeSSClient, GetConfigResp>(this, &MeSSClient::tc1_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_SET_CONFIG),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc2_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_MULTICAST_REQ),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc3_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_MULTICAST_REQ1),
		    CallbackSlot<MeSSClient, GetConfigResp>(this, &MeSSClient::tc3_1_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_HIGH_NOOF_RESP), 
		CallbackSlot<MeSSClient, GetConfigResp>(this, &MeSSClient::tc27_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_MULTICAST_DELAY_REQ),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc26_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_DELAY_RESP),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc4_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_TIMEOUT_RESP),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc5_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_WRONGCOMP_RESP),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc6_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID1, M_WRONG_IFACE_RESP),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc7_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_WRONG_METHOD_RESP),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc8_Cbk));

		MeSSObj().RegisterRespHandler(MakeMsgId(I_TEST_ID, M_CBK_RGS_FAILED),
		    CallbackSlot<MeSSClient, SetConfigResp>(this, &MeSSClient::tc12_Cbk));
	}
    ~MeSSClient()
    {
    }

    void join()
    {
        if (m_thread)
        {
            m_thread->join();
            delete m_thread;
        }
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
  
	//Registered call back for test case 1 
        int tc1_Cbk(GetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "GetConfig Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
			std::cout << "\nTest case " << m_cmdArgs.testId << " FAILED\n";
		}
		
		else{       
			std::cout << "GET_CONFIG_RESP: " << resp->id << " " << resp->val << " " << resp->result << std::endl;
		    	if(m_cmdArgs.testId != 9)
				std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 27
        int tc27_Cbk(GetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			gFailed++;
		}
		
		else{       
			gPassed++;
		}

		if (gPassed % 50000 == 0)
		{
			std::cout << "\n gPassed : " << gPassed << " , gFailed : " << gFailed << " , gPassed + gFailed : " << gPassed+gFailed << "\n";
			std::cout << "Time: " << m_time.now() << std::endl;
		}

		return 0;
	}
	
	//Registered call back for 
	int tc2_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
		    std::cout << "Sending bulk message response failed. Error: " << MeSS::Handle().m_state << std::endl;
		    std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		#if 0
		    if(m_cmdArgs.testId == 28)
		    {
				gettimeofday(&end[gRespCount], NULL);

				seconds  = end[gRespCount].tv_sec  - start[gRespCount].tv_sec;
				useconds = end[gRespCount].tv_usec - start[gRespCount].tv_usec;

				mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
				std::cout<<"\n-------------------Elapsed time failed : " <<mtime<<" milliseconds ----------------------\n";

				std::cout << "\n gRespCount : " << gRespCount << "\n";
				gRespCount++;
				gFailed++;
				std::cout << "\n gPassed : " << gPassed << " , gFailed : " << gFailed << " , gPassed + gFailed : " << gPassed+gFailed << "\n";
		    }
		#endif

		}
		else
		{
			std::cout << "SET_CONFIG_RESP: " << resp->id
				  << " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";

		#if 0
			if(m_cmdArgs.testId == 28)
			{
				gettimeofday(&end[gRespCount], NULL);

				seconds  = end[gRespCount].tv_sec  - start[gRespCount].tv_sec;
				useconds = end[gRespCount].tv_usec - start[gRespCount].tv_usec;

				mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
				std::cout<<"\n-------------------Elapsed time passed : " <<mtime<<" milliseconds----------------------\n";

				std::cout << "\n gRespCount : " << gRespCount << "\n";
				gRespCount++;
				gPassed++;
			}
		#endif

		}
		return 0;
	}

	//Registered call back for test case 3
	int tc3_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Multicast Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		else
		{
			std::cout << "MULTICAST_CONFIG_RESP: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		return 0;
	}

	//Registered call back for 
	int tc3_1_Cbk(GetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Multicast Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		else
		{
			std::cout << "MULTICAST_CONFIG_RESP  1 : " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 4
	int tc4_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Delay in Resp Failed. Error: " << MeSS::Handle().m_state << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		else
		{
			std::cout << "DELAY_CONFIG_RESP: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 5
	int tc5_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Timeout Resp Failed. Error: " << MeSS::Handle().m_state << std::endl;
                	std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		else
		{
			std::cout << "TIMEOUT_RESP: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 6
	int tc6_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Wrong component Failed. Error: " << MeSS::Handle().m_state << std::endl;
    	        	std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		else
		{
			std::cout << "WRONGCOMP_RESP: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 7
	int tc7_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Wrong Interface Id Failed. Error: " << MeSS::Handle().m_state << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		else
		{
			std::cout << "WRONG_IFACE_RESP: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 8
	int tc8_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Wrong Method Id Failed. Error: " << MeSS::Handle().m_state << std::endl;
	        	std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		else
		{
			std::cout << "WRONG_METHOD_RESP: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 12
	int tc12_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "server call back register Failed. Error: " << MeSS::Handle().m_state << std::endl;
	        	std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
		else
		{
			std::cout << "CBK_RGS_FAILED: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		return 0;
	}

	//Registered call back for test case 26
	int tc26_Cbk(SetConfigResp *resp)
	{
		if (MeSS::Handle().m_state != MESS_STATUS_SUCCESS)
		{
			std::cout << "Multicast delay Request message failed. Error: " << MeSS::Handle().m_state << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " FAILED\n\n";
		}
		else
		{
			std::cout << "MULTICAST_DELAY_REQ: " << resp->id
				<< " " << resp->result << std::endl;
			std::cout << "\n\nTest case " << m_cmdArgs.testId << " PASSED\n\n";
		}
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
				std::cout <<"\n---------------------TEST CASE " << m_cmdArgs.testId << " ---------------------------------\n";

				switch(m_cmdArgs.testId)      //m_cmdArgs.testId gives the test case number 
				{
					case 1:				 
						this->tc1();
						break;
					case 2:
						this->tc2();
						break;
					case 3:
						this->tc3();
						break;
					case 4:
						this->tc4();
						break;
					case 5:
						this->tc5();
						break;
					case 6:
						this->tc6();
						break;
					case 7:
						this->tc7();
						break;
					case 8:
						this->tc8();
						break;
					case 9:   // for sending multiple different requests from client to server
						this->tc1();
						this->tc2();
						break;
					case 10:
						this->tc3();
						this->tc3_1();
						break;
					case 11:
						this->tc1();
						break;
					case 12:
						this->tc12();
						break;
					case 16:
						this->tc1();
						this->tc2();
						break;
					case 26:
						this->tc26();
						break;
					case 27:
						std::cout << "Staring test @ " << m_time.now() << std::endl;
						this->tc27();
						break;
					case 28:
						for(int tc28 = 1; tc28 <= 10000; tc28++)
						{
							this->tc1();
							this->tc2();
						}
						break;
					default:
						std::cout << "wrong test case" << std::endl;
				}
			        once++;
			}
		}
		return 0;
	}

protected:    

	void tc1()
	{
		if(m_cmdArgs.testId == 1)
		{
			std::cout << "\nThis test case is to verify sending request from client to server  \n";
		}
		if(m_cmdArgs.testId == 9)
		{
			std::cout << "\nThis test case is to verify sending multiple different requests from client to server  \n";
		}
		if(m_cmdArgs.testId == 11)
		{
			std::cout << "\nThis test case is to verify sending message from client to server when server is not up \n";
			int ret;
			ret = system("ps -eaf | grep ./bin/debug/unitmessserver|grep -v grep|awk '{print $2}'|xargs kill -9");
		}

		MessageId msgId = MakeMsgId(I_TEST_ID, M_GET_CONFIG);
		MeSSEndpoint dest = {SERVER_COMP_ID, 10};
		GetConfigReq req;
		req.id = 100;
		strcpy(req.str, "GetConfig");

		if(m_cmdArgs.testId == 28)
		{
			//gettimeofday(&start[gReqCount], NULL);
			std::cout << "GET_CONFIG_REQ >> " << std::endl;	
			MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
			std::cout << "\ngReqCount " << gReqCount << "\n";	
			gReqCount++;
		}
		else
		{        
			std::cout << "GET_CONFIG_REQ >> " << std::endl;	
			MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
		}
	}	
	
	void tc27()
	{
		//MessageId msgId = MakeMsgId(I_TEST_ID, M_HIGH_NOOF_RESP);
		//MeSSEndpoint dest = {SERVER_COMP_ID, 10};
		//GetConfigReq req;
		//req.id = 100;
		//strcpy(req.str, "GetConfigGetConfigGetConfigGetConfigGetConfigGetConfigGetCon");
		//	CLOG_NOTICE("Starting OneTime timer for 100ms");
#if 0
	        this->GetDispatcher()->AddEventHandler(
	    	    EventSlot<TimerEvent, MeSSClient>(this, &MeSSClient::OnOnceTimeout),
		    TimerEvent(50));		
#endif
        m_thread = new std::thread(RunTest);
	}

	// Time out function for register timer event for test case 27
	int OnOnceTimeout(TimerEvent &ev)
	{
		MessageId msgId = MakeMsgId(I_TEST_ID, M_HIGH_NOOF_RESP);
	        MeSSEndpoint dest = {SERVER_COMP_ID, 10};
	        GetConfigReq req;
        	req.id = 100;
	        strcpy(req.str, "GetConfigGetConfigGetConfigGetConfigGetConfigGetConfigGetCon");
		for(int i=1; i< 2000; i++)
			MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));

		this->GetDispatcher()->AddEventHandler(
                            EventSlot<TimerEvent, MeSSClient>(this, &MeSSClient::OnOnceTimeout),
                            TimerEvent(50));

	        CLOG_NOTICE("Onetime timer expired");
	        return 0;
	}


	void tc2()
	{
		if(m_cmdArgs.testId == 2)
			std::cout << "\nThis test case is to Verify sending the message from client to server \n";
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_SET_CONFIG);
	        MeSSEndpoint dest = {SERVER_COMP_ID, 10};
		if(m_cmdArgs.testId == 28)
        	{
        		SetConfigReq req;
		        req.id = 100;
		        req.val = 10;
        		strcpy(req.descr, "SetConfig");

	                //gettimeofday(&start[gReqCount], NULL);
		        std::cout << "SET_CONFIG_REQ >> " << std::endl;
                	MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	                std::cout << "\ngReqCount " << gReqCount << "\n";
        	        gReqCount++;                  
		}
		// for sending bulk message greater than its size. For test case 3
		else 
		{
        		SetConfigReq req[10000];
		        req[0].id = 100;
		        req[0].val = 10;
	        	strcpy(req[0].descr, "SetConfig");

		        std::cout << "SET_CONFIG_REQ >> " << std::endl;
        		//MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
		        MeSSObj().Send(dest, msgId, (void*)&req, 10000);
		}
	}

	void tc3()
	{
		std::cout << "\nThis test case is to Verify sending the message to different servers using MULTICAST option with set config req \n";
		int ret;
        	ret = system("sh server.sh");
		sleep(1);
        	MessageId msgId = MakeMsgId(I_TEST_ID, M_MULTICAST_REQ);
	        MeSSEndpoint dest = {SERVER_COMP_ID, MESS_MULTICAST_ACTIVE};
        	SetConfigReq req;
	        req.id = 100;
	        req.val = 10;
	        strcpy(req.descr, "MulticastReq");

        	std::cout << "MULTICAST_REQ >> " << std::endl;
	        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc3_1()
	{
		std::cout << "\nThis test case is to Verify sending the message to different servers using MULTICAST option with get config req  \n";
	        //system("sh server.sh");
		//sleep(1);
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_MULTICAST_REQ1);
        	MeSSEndpoint dest = {SERVER_COMP_ID, MESS_MULTICAST_ACTIVE};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "MulticastReq 1");

	        std::cout << "MULTICAST_REQ 1 >> " << std::endl;
	        MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc4()
	{
		std::cout << "\nThis test case is to Verify sending the message to the server and getting the response with some delay\n";
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_DELAY_RESP);
        	MeSSEndpoint dest = {SERVER_COMP_ID, 10};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "SetConfig");

	        std::cout << "DELAY_RESP_REQ >> " << std::endl;
                MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc5()
	{
		std::cout << "\nThis test case is to Verify sending the message to the server and getting the response after time out\n";
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_TIMEOUT_RESP);
        	MeSSEndpoint dest = {SERVER_COMP_ID, 10};
	        SetConfigReq req;
	        req.id = 100;
	        req.val = 10;
	        strcpy(req.descr, "SetConfig");

		std::cout << "TIMEOUT_REQ >> " << std::endl;
		MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc6()
	{
		std::cout << "\nThis test case is to Verify sending the message to the server with wrong component ID\n";
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_WRONGCOMP_RESP);
        	MeSSEndpoint dest = {SERVER_COMP_ID1, 10};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "SetConfig");

	        std::cout << "WRONGCOMP_REQ >> " << std::endl;
		MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc7()
	{
		std::cout << "\nThis test case is to Verify sending the message to the server with wrong interface ID\n";
	        MessageId msgId = MakeMsgId(I_TEST_ID1, M_WRONG_IFACE_RESP);
        	MeSSEndpoint dest = {SERVER_COMP_ID, 10};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "SetConfig");

		std::cout << "WRONG_IFACE_REQ >> " << std::endl;
		MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc8()
	{
		std::cout << "\nThis test case is to Verify sending the message to the server with wrong method ID\n";
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_WRONG_METHOD_RESP);
        	MeSSEndpoint dest = {SERVER_COMP_ID, 10};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "SetConfig");

	        std::cout << "WRONG_METHOD_REQ >> " << std::endl;
		MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc12()
	{
		std::cout << "\nThis test case is to Verify sending the message to the server when call back is not registered\n";
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_CBK_RGS_FAILED);
        	MeSSEndpoint dest = {SERVER_COMP_ID, 10};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "SetConfig");

	        std::cout << "WRONG_METHOD_REQ >> " << std::endl;
		MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
	}

	void tc26()
	{
        	std::cout << "\nThis test case is to Verify sending the message to different servers using MULTICAST option with some delay from server \n";
		int ret;
	        ret = system("sh server.sh");
        	sleep(1);
	        MessageId msgId = MakeMsgId(I_TEST_ID, M_MULTICAST_DELAY_REQ);
        	MeSSEndpoint dest = {SERVER_COMP_ID, MESS_MULTICAST_ACTIVE};
	        SetConfigReq req;
        	req.id = 100;
	        req.val = 10;
        	strcpy(req.descr, "Multicast Delay Req ");

	        std::cout << "MULTICAST_DELAY_REQ >> " << std::endl;
        	MeSSObj().Send(dest, msgId, (void*)&req, sizeof(req));
    	}	

	// This structure is for adding test case number in the command line options (-t <test case number>)
	struct CmdArgs
    	{
      		CmdArgs()
	            : testId("t", "testId", "Test Id requesting notification", "1")	
       		{
       		}
	        CmdOption<int> testId;
	}m_cmdArgs;

	TimeVal m_time;

    std::thread *m_thread;
};

int main(int argc, char *argv[])
{    
	MeSSClient app;
	try
	{
        	app.Init(argc, argv);

	        CLOG_NOTICE("Application initialized");

        	app.Run();
            g_stop = 1;
            app.join();
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
	
	std::cout << "\n gPassed : " << gPassed << " , gFailed : " << gFailed << " , gPassed + gFailed : " << gPassed+gFailed << "\n";
	TimeVal t;
	std::cout << t.now() << std::endl;
    
	//if (app) delete app;        

	return 0;
}
