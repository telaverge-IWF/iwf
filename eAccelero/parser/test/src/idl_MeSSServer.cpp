
#include "MeSSTest.h"
#include "input.h"

using namespace eAccelero;
class test:public MeSSComponent,public ABC
{
public:
    test()
        : MeSSComponent("test", SERVER_COMP_ID),
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
int method1(Req1 *r1,Resp1 *r2)
{
        std::cout << "METHOD_1_REQ: " << r1->id << " " << r1->str << std::endl;
        
        r2->id = r1->id;
        r2->val = 120;
        strcpy(r2->result, "method1 success");
	return 0;
}
int method2(Req2 *r1,Resp2 *r2)
{
        std::cout << "METHOD_2_REQ: " << r1->id << " " << r1->descr << " " << r1->val << std::endl;
        r2->id = r1->id;
       	 
        strcpy(r2->result, "method2 success");
	return 0;
}
protected:
    unsigned m_counter;
	
};


int main(int argc, char *argv[])
{
    test app1;
#if 1
    try
    {
    	app1.Init(argc, argv);
    	app1.Run();
        CLOG_NOTICE("Application initialized");

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
    
#endif
    return 0;
}
