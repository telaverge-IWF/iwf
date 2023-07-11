#include "test.h"
#include <string.h>

#define SERVER_COMP_ID 400

using namespace eAccelero;

class FlatUserAccessImpl: public FlatUserAccess
{
 public:
    int Login(FlatUser *user,FlatResult *resCode)
    {
        std::cout << "----- Login requested: -----" << std::endl;
        std::cout << "User: " << user->userName << " id: " 
                  << user->userId << std::endl;

        memset(resCode, 0, sizeof(resCode));
        resCode->resCode = 0;
        strcpy(resCode->descr, "Login Granted");
        return 0;
    }
    int Logout(FlatUser *user,FlatResult *resCode)
    {
        std::cout << "----- Logout requested: -----" << std::endl;
        std::cout << "User: " << user->userName << " id: " 
                  << user->userId << std::endl;

        memset(resCode, 0, sizeof(resCode));
        resCode->resCode = 0;
        strcpy(resCode->descr, "Logout successful");
        return 0;
    }
};

class UserAccessImpl: public UserAccess
{
 public:
    int Login(User *user,Result *resCode)
    {
        std::cout << "----- PB Login requested: -----" << std::endl;
        std::cout << "User: " << user->username() << " id: " 
                  << user->userid() << std::endl;

        resCode->set_resultcode(0);
        resCode->set_descr("Login Granted");

        return 0;
    }
    int Logout(User *user,Result *resCode)
    {
        std::cout << "----- PB Logout requested: -----" << std::endl;
        std::cout << "User: " << user->username() << " id: " 
                  << user->userid() << std::endl;

        resCode->set_resultcode(0);
        resCode->set_descr("Logout successful");

        return 0;
    }
    int GetUsers(Req *req,Users *users)
    {
        return 0;
    }
};

class MeSSServer: public MeSSComponent
{
 public:
    MeSSServer()
        : MeSSComponent("IDLServer", SERVER_COMP_ID)
    {
    }
    void Initialize()
    {
        MeSSComponent::Initialize();
      
    }
    void Terminate()
    {
        MeSSComponent::Terminate();
    }

 protected:
    FlatUserAccessImpl fuserAccess;
    UserAccessImpl     userAccess;
};

int main(int argc, char *argv[])
{
    MeSSServer app1;
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
    
    return 0;
    
}

