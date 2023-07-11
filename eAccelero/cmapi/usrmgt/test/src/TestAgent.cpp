#include "MeSSComponent.h"
#include <stdlib.h>
#include "ComponentDefines.h"
#include <iostream>
#include "Compo_def.h"
#include "PeerStats_def.h"
#include "UserManagement_def.h"

#include "TestAgent.h"
#include "CMAPIUsrMgtLib.h"
#include "ThreadQueue.h"
#include "Thread.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

using namespace eAccelero;

using namespace google::protobuf::io;

class TestAgent: public MeSSComponent
{
    public:
        TestAgent(int CompID)
            : MeSSComponent("TestAgent", CompID)
        {
        }

        void Initialize()
        {
            MeSSComponent::Initialize();

            TopologyEvent compEvent(COMP_CONFIG_MANAGER);
            MeSSObj().TopSvc().Subscribe(
                    EventSlot<TopologyEvent, TestAgent>(this, &TestAgent::OnServerEvent),
                    compEvent);          
        }
        void Terminate()
        {
            MeSSComponent::Terminate();
        }

        int OnServerEvent(TopologyEvent &event)
        {
            if (event.NotificationType() == TopologyEvent::NOTIFY_TYPE_PUBLISHED)
            {
                std::cout << "Subscription:" << event.Subscription() << " Port:" << event.Port() << std::endl;
                std::cout << "Config Manager UP" << endl;
            }
            return 0;
        }

    protected:

};

class ApiLibUser: public Runnable
{
    private:
        void Initialize()
        {
            CMApiLibObj = new  CMAPIUserConfig();
            CMApiLibObj->InitializeLibrary();
        }

        int CMAPI_GetPrevilage(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                UserDetailResp Resp;

                Previlages LocalPrevilagesObj;

                string PrevilageName;
                int id;
                bool all = false;
                cout << "All (1/0): ";cin>>all;
                if(!all)
                {
                    Previlage *pPrevilage = LocalPrevilagesObj.add_previlageinfo();
                    cout << "PrevilageName: ";
                    cin.ignore(256,'\n');
                    getline(cin,PrevilageName);
                    pPrevilage->set_previlagename(PrevilageName);
                }

                if(CMApiLibObj->GetPrevilage(LocalPrevilagesObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                    Previlages *pPrevilages = Resp.mutable_previlageinfo();
                    int pCount = pPrevilages->previlageinfo_size();
                    cout << "Returned Previlage Count : "<< pCount << endl;  
                    if (pCount > 0)
                    {
                        cout <<"**********************************"<<endl;
                        for (int index=0; index<pCount; index++)
                        {
                            Previlage *pPrevilage = pPrevilages->mutable_previlageinfo(index);
                            if (pPrevilage->has_previlageid())
                                cout <<"PrevilageId : "<<pPrevilage->previlageid() <<endl;
                            if (pPrevilage->has_previlagename())
                                cout <<"PrevilageName : "<<pPrevilage->previlagename() <<endl;
                            if (pPrevilage->has_previlagedesc())
                                cout <<"PrevilageDesc : "<<pPrevilage->previlagedesc() <<"\n\n";
                        }
                        cout <<"**********************************"<<endl;
                    }
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }


        int CMAPI_GetUser(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                UserDetailResp Resp;
                
                UserDetails LocalUserDetailsObj;
                UserDetail *pUserDetail = LocalUserDetailsObj.add_userinfo();
                Role *pRole = pUserDetail -> mutable_roledetails();
                

                string UserName;

                cout << "UserName: "; cin >> UserName;
                pUserDetail->set_username(UserName);


                if(CMApiLibObj->GetUser(LocalUserDetailsObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int CMAPI_DelUser(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                UserDetailResp Resp;
                
                UserDetails LocalUserDetailsObj;
                UserDetail *pUserDetail = LocalUserDetailsObj.add_userinfo();
                Role *pRole = pUserDetail -> mutable_roledetails();
                
                string UserName;

                cout << "UserName: "; cin >> UserName;
                pUserDetail->set_username(UserName);

                if(CMApiLibObj->DelUser(LocalUserDetailsObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int CMAPI_ModUser(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                UserDetailResp Resp;
                
                UserDetails LocalUserDetailsObj;
                UserDetail *pUserDetail = LocalUserDetailsObj.add_userinfo();
                Role *pRole = pUserDetail -> mutable_roledetails();
                

                string UserName;
                string Password;
                string FirstName;
                string LastName;
                string Email;
                bool UserStatus;
                string UserType;
                string LastLogin;
                string CreatedBy;
                string CreationTime;
                string ModifiedBy;
                string ModificationTime;

                string RoleName;
                bool RoleStatus;

                string ConnectionURL;
                string DomainName;
                string LoginId;
                string IPassword;
                int iUserid;

                // User Details
                cout << "User ID:  "; cin >> iUserid;
                pUserDetail->set_userid(iUserid);
                cout << "UserName: "; cin >> UserName;
                pUserDetail->set_username(UserName);

                cout << "Password: ";cin >> Password;
                pUserDetail->set_password(Password);

                cout << "FirstName: ";cin >> FirstName;
                pUserDetail->set_firstname(FirstName);

                cout << "Email: ";cin >> Email;
                pUserDetail->set_email(Email);

                cout << "LastName: ";cin >> LastName;
                pUserDetail->set_lastname(LastName);

                cout << "UserStatus-0/1:"; cin >> UserStatus;
                pUserDetail->set_userstatus(UserStatus);

                cout << "UserType: ";cin >> UserType;
                pUserDetail->set_usertype(UserType);

                cout << "LastLogin: ";cin >> LastLogin;
                pUserDetail->set_lastlogin(LastLogin);

                cout << "CreatedBy: ";cin >> CreatedBy;
                pUserDetail->set_createdby(CreatedBy);

                cout << "CreationTime: ";//cin >> CreationTime;
                pUserDetail->set_creationtime("0006-05-04 03:02:01");

                cout << "ModifiedBy: ";cin >> ModifiedBy;
                pUserDetail->set_modifiedby(ModifiedBy);

                cout << "ModificationTime: ";//cin >> ModificationTime; 
                pUserDetail->set_modificationtime("1006-05-04 03:02:01");
           
                //Role Table data
                cout << "Role Name : ";cin >> RoleName;
                pRole->set_rolename(RoleName);

                if(CMApiLibObj->ModUser(LocalUserDetailsObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int CMAPI_AddUser(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                UserDetailResp Resp;
                
                UserDetails LocalUserDetailsObj;
                UserDetail *pUserDetail = LocalUserDetailsObj.add_userinfo();
                Role *pRole = pUserDetail -> mutable_roledetails();
                

                string UserName;
                string Password;
                string FirstName;
                string LastName;
                string Email;
                bool UserStatus;
                string UserType;
                string LastLogin;
                string CreatedBy;
                string CreationTime;
                string ModifiedBy;
                string ModificationTime;

                string RoleName;
                bool RoleStatus;

                string ConnectionURL;
                string DomainName;
                string LoginId;
                string IPassword;

                // User Details
                cout << "UserName: "; cin >> UserName;
                pUserDetail->set_username(UserName);

                cout << "Password: ";cin >> Password;
                pUserDetail->set_password(Password);

                cout << "FirstName: ";cin >> FirstName;
                pUserDetail->set_firstname(FirstName);

                cout << "Email: ";cin >> Email;
                pUserDetail->set_email(Email);

                cout << "LastName: ";cin >> LastName;
                pUserDetail->set_lastname(LastName);

                cout << "UserStatus-0/1:"; cin >> UserStatus;
                pUserDetail->set_userstatus(UserStatus);

                cout << "UserType: ";cin >> UserType;
                pUserDetail->set_usertype(UserType);

                cout << "LastLogin: ";cin >> LastLogin;
                pUserDetail->set_lastlogin(LastLogin);

                cout << "CreatedBy: ";cin >> CreatedBy;
                pUserDetail->set_createdby(CreatedBy);

                cout << "CreationTime: ";cin >> CreationTime;
                pUserDetail->set_creationtime(CreationTime);

                cout << "ModifiedBy: ";cin >> ModifiedBy;
                pUserDetail->set_modifiedby(ModifiedBy);

                cout << "ModificationTime: ";cin >> ModificationTime; 
                pUserDetail->set_modificationtime(ModificationTime);
           
                //Role Table data
                cout << "Role Name : ";cin >> RoleName;
                pRole->set_rolename(RoleName);

                if(CMApiLibObj->AddUser(LocalUserDetailsObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }
            return 0;
        }

        int  CMAPI_GetEmailContentDetails(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                EmailContentReq LocalEmailServerReqObj;
                EmailContent *pEmailContent = LocalEmailServerReqObj.add_emailcontents();

                EmailContentResp Resp;

                string EmailContentFor;
                bool EmailStatus;
                string Subject="{FNAME}, Diameter Route Engine Login Credentials -new-";
                string Message="Hi {FNAME}, Your account has been created for Diameter Route Engine. Your login details are: -new-";
                
                cout << "EmailContentFor : ";
                cin.ignore(256,'\n');
                getline(cin,EmailContentFor);
                pEmailContent->set_emailcontentfor(EmailContentFor);

                cout << "EmailStatus  (1/0): ";cin >> EmailStatus;
                pEmailContent->set_emailstatus(EmailStatus);

                //cout << "Subject : ";cin >> Subject;
                //pEmailContent->set_subject(Subject);

                //cout << "Message : ";cin >> Message;
                //pEmailContent->set_message(Message);

                if ( CMApiLibObj->GetEmailContentDetails(LocalEmailServerReqObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int  CMAPI_ModEmailContentDetails(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                EmailContentReq LocalEmailServerReqObj;
                EmailContent *pEmailContent = LocalEmailServerReqObj.add_emailcontents();

                EmailContentResp Resp;

                string EmailContentFor="New User";
                bool EmailStatus;
                string Subject="{FNAME}, Diameter Route Engine Login Credentials -new-";
                string Message="Hi {FNAME}, Your account has been created for Diameter Route Engine. Your login details are: -new-";
                
                cout << "EmailContentFor : ";
                pEmailContent->set_emailcontentfor(EmailContentFor);

                cout << "EmailStatus  (1/0): ";
                cin >> EmailStatus;
                pEmailContent->set_emailstatus(EmailStatus);

                cout << "Subject : ";
                //cin >> Subject;
                pEmailContent->set_subject(Subject);

                cout << "Message : " << endl;
                //cin >> Message;
                pEmailContent->set_message(Message);

                if ( CMApiLibObj->ModEmailContentDetails(LocalEmailServerReqObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }
        int  CMAPI_GetEmailServerDetails(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                EmailServerReq LocalEmailServerReqObj;
                EmailServerResp Resp;
                if ( CMApiLibObj->GetEmailServerDetails(LocalEmailServerReqObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                    int iCount = Resp.emailservers_size();

                    for(int i=0;i<iCount;i++)
                    {
                        EmailServer *pEmailServer = Resp.mutable_emailservers(i);

                        cout << "HostName :" << pEmailServer->hostname();
                        cout << "Port :" << pEmailServer->portnumber();
                        cout << "Email :" << pEmailServer->systememail();
                        cout << "password :" << pEmailServer->passwordstring();
                    }
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }
        int  CMAPI_DelEmailServerDetails(void)
        {
            cout << "In Agent CMAPI_DelEmailServerDetails " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                EmailServerReq LocalEmailServerReqObj;
                EmailServer *pEmailServer = LocalEmailServerReqObj.add_emailservers();

                EmailServerResp Resp;

                string hostname;
                int portnumber;
                string systememail;
                string Password;
               
#if 1
                cout << "hostname : ";
                cin.ignore(256, '\n');
                cin >> hostname;
                pEmailServer->set_hostname(hostname);

                cout << "portnumber :";
                cin >> portnumber;
                pEmailServer->set_portnumber(portnumber);

                cout << "systememail : ";
                cin >> systememail;
                pEmailServer->set_systememail(systememail);

                cout << "Password : ";
                cin >> Password;
                pEmailServer->set_password(Password);
#endif
                if ( CMApiLibObj->DelEmailServerDetails(LocalEmailServerReqObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int  CMAPI_SetEmailServerDetails(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                EmailServerReq LocalEmailServerReqObj;
                EmailServer *pEmailServer = LocalEmailServerReqObj.add_emailservers();

                EmailServerResp Resp;

                string hostname;
                int portnumber;
                string systememail;
                string Password;
               
                cout << "hostname : ";
                cin.ignore(256, '\n');
                cin >> hostname;
                pEmailServer->set_hostname(hostname);

                cout << "portnumber : ";
                cin >> portnumber;
                pEmailServer->set_portnumber(portnumber);

                cout << "systememail : ";
                cin >> systememail;
                pEmailServer->set_systememail(systememail);

                cout << "Password : ";
                cin >> Password;
                pEmailServer->set_passwordstring(Password);

                if ( CMApiLibObj->SetEmailServerDetails(LocalEmailServerReqObj,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int  CMAPI_GetUserRole(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;
                Roles lRoleList;
                Role *pRoleObj = lRoleList.add_roleinfo();


                UserDetailResp Resp;
                string RoleName;
                bool RoleStatus;

                cout << "Role Name : " << endl;
                cin >> RoleName;
                pRoleObj->set_rolename(RoleName);

                if ( CMApiLibObj->GetUserRole(lRoleList,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                    cout << "Role Name : " ;
                    cout << "Role Status : " ;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int  CMAPI_DelUserRole(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;
                Roles lRoleList;
                Role *pRoleObj = lRoleList.add_roleinfo();

                UserDetailResp Resp;
                string RoleName;
                bool RoleStatus;

                cout << "Role Name : " << endl;
                cin >> RoleName;
                pRoleObj->set_rolename(RoleName);

                if ( CMApiLibObj->DelUserRole(lRoleList,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }

        int  CMAPI_ModUserRole(void)
        {
            cout << "In Agent GetLocalHostConfig " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                Roles lRoleList;
                Role *pRoleObj = lRoleList.add_roleinfo();
                Previlages *pPrevilages = pRoleObj -> mutable_previlagesdetails();
                Previlage *pPrevilage = pPrevilages -> add_previlageinfo();


                string Previlage;
                UserDetailResp Resp;
                string RoleName;
                bool RoleStatus;
                int RoleID;

                cout << "Role ID : " << endl;
                cin >> RoleID;
                pRoleObj->set_roleid(RoleID);
                cout << "Role Name : " << endl;
                cin >> RoleName;
                pRoleObj->set_rolename(RoleName);
                cout << "Role Status : 1/0" << endl;
                cin >> RoleStatus;
                pRoleObj->set_rolestatus(RoleStatus);

                bool input_privilage = false;
                cout << "Want Privilage  (1/0):";cin >> input_privilage;
                if (input_privilage == true)
                {
                    cout << "Previlage: \n " << endl;
                    cin.ignore(256,'\n');
                    getline(cin,Previlage);
                    pPrevilage->set_previlagename(Previlage);
                }
                if ( CMApiLibObj->ModUserRole(lRoleList,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }


            return 0;
        }

        int  CMAPI_AddUserRole(void)
        {
            cout << "In Agent AddUserRole " << endl;
            if ( CMApiLibObj == NULL )
            {
                cout << "CMAPILIB Obj not created " << endl;
            }
            else
            {
                cout << " Calling Library " << endl;

                Roles lRoleList;
                Role *pRoleObj = lRoleList.add_roleinfo();
                Previlages *pPrevilages = pRoleObj -> mutable_previlagesdetails();
                Previlage *pPrevilage = pPrevilages -> add_previlageinfo();

                UserDetailResp Resp;
                string RoleName;
                bool RoleStatus;
                string Previlage;

                cout << "Role Name : " << endl;
                cin >> RoleName;
                pRoleObj->set_rolename(RoleName);
                cout << "Role Status : 1/0" << endl;
                cin >> RoleStatus;
                pRoleObj->set_rolestatus(RoleStatus);
                
                bool input_privilage = false;
                cout << "Want Privilage  (1/0):";cin >> input_privilage;
                if (input_privilage == true)
                {
                    cout << "Previlage: \n " << endl;
                    cin.ignore(256,'\n');
                    getline(cin,Previlage);
                    pPrevilage->set_previlagename(Previlage);
                }


                if ( CMApiLibObj->AddUserRole(lRoleList,&Resp) == CMAPI_SUCCESS)
                {
                    cout << "CMAPI SUCCESS" << endl;
                }
                else
                {
                    cout << "CMAPI FAILED" << endl;
                }
            }

            return 0;
        }
       
        int Menu()
        {
            cout << " \n\n\n****** MENU *******" << endl;
            cout << "  1: ADD_USER_ROLE " << endl;
            cout << "  2: DEL_USER_ROLE " << endl;
            cout << "  3: MOD_USER_ROLE " << endl;
            cout << "  4: GET_USER_ROLE " << endl;
            cout << "  5: GET_EMAIL_SERVER " << endl;
            cout << "  6: SET_EMAIL_SERVER " << endl;
            cout << "  7: DEL_EMAIL_SERVER " << endl;
            cout << "  8: GET_EMAIL_CONTENT " << endl;
            cout << "  9: MOD_EMAIL_CONTENT " << endl;
            cout << " 10: SET_USER " << endl;
            cout << " 11: MOD_USER " << endl;
            cout << " 12: DEL_USER " << endl;
            cout << " 13: GET_USER " << endl;
            cout << " 14: GET_PRIVILEGE " << endl;
   
            cout << "\n  0: Exit" << endl;
            cout << "*********************" << endl;
            int Ch;
            cin >> Ch;

            if(Ch == 0)
                exit(EXIT_FAILURE);

            cout << "Choice Entered " << Ch << endl;
            return Ch;
        }

        void CallCMAPI(int ch)
        {
            switch (ch)
            {
                case ADD_USER_ROLE:
                    cout << "ADD_USER_ROLE Request" << endl;
                    CMAPI_AddUserRole();
                    break;
                case DEL_USER_ROLE:
                    cout << "DEL_USER_ROLE Request" << endl;
                    CMAPI_DelUserRole();
                    break;
                case MOD_USER_ROLE:
                    cout << "MOD_USER_ROLE Request" << endl;
                    CMAPI_ModUserRole();
                    break;
                case GET_USER_ROLE:
                    cout << "GET_USER_ROLE Request" << endl;
                    CMAPI_GetUserRole();
                    break;
                case GET_EMAIL_SERVER:
                    cout << "GetEmailServerDetails Request" << endl;
                    CMAPI_GetEmailServerDetails();
                    break;
                case SET_EMAIL_SERVER:
                    cout << "SET_EMAIL_SERVER Request" << endl;
                    CMAPI_SetEmailServerDetails();
                    break;
                case DEL_EMAIL_SERVER:
                    cout << "DelEmailServerDetails Request" << endl;
                    CMAPI_DelEmailServerDetails();
                    break;
                case GET_EMAIL_CONTENT:
                    cout << "GET_EMAIL_CONTENT Request" << endl;
                    CMAPI_GetEmailContentDetails();
                    break;
                case MOD_EMAIL_CONTENT:
                    cout << "MOD_EMAIL_CONTENT Request" << endl;
                    CMAPI_ModEmailContentDetails();
                    break;
                case SET_USER:
                    cout << "SET_USER Request" << endl;
                    CMAPI_AddUser();
                    break;
                case MOD_USER:
                    cout << "MOD_USER Request" << endl;
                    CMAPI_ModUser();
                    break;
                case DEL_USER:
                    cout << "MOD_USER Request" << endl;
                    CMAPI_DelUser();
                    break;
                case GET_USER:
                    cout << "MOD_USER Request" << endl;
                    CMAPI_GetUser();
                    break;
                case GET_USER_PRIVILEGE:
                    cout << "GET_USER_PRIVILEGE Request" << endl;
                    CMAPI_GetPrevilage();
                    break;
                default:
                    cout << "Invalid Choice " << endl;
                    cout << "value " << ch << " is it correct... ?" << endl;
                    break;
            }
        }

        void RunMain()
        {
            bool Done = false;
            int Choice = 0;
            while (!Done)
            {
                Choice = Menu();
                if (Choice == 0)
                    Done = true;
                else
                    CallCMAPI(Choice);
            }
        }

    public:
        ApiLibUser() {}
        ~ApiLibUser() {}

        void Run(void *arg)
        {
            Initialize();
            RunMain();
            cout << "CMAPI Test Agent Exiting... BYE" << endl;
            exit(0);
        }

        void UpdateStatsIndex() {};

    private:
        CMAPIUserConfig *CMApiLibObj;

};


int main(int argc, char *argv[])
{
    ApiLibUser LibUser;
    Thread  LibTest("CMAPITest");
    int ComponentID = 0;

    if (argc >= 2)
    {
        if (strcmp(argv[1], "CLI") == 0)
        {
            ComponentID = COMP_CLI_PROC;
        } else if (strcmp(argv[1], "GUI") == 0)
        {
            ComponentID = COMP_WEBAGENT_PROC;
        }
    } else {
        cout << "Error Invoking TestAgent : " << endl;
        cout << "Usage : " << endl;
        cout << "TestAgent \"CLI\" or \"GUI\"" << endl;
        exit(0);
    }

    TestAgent *app = NULL;
    try
    {
        cout << "Starting CMAPI Test Thread" << endl;
        char *Args[]= { "TestAgent", "-i", "0", "-l", "7" };
        int  NumArgs = 5;
        app = new TestAgent(ComponentID);

        app->Init(NumArgs, Args);

        CLOG_NOTICE("Application initialized");
        LibTest.Start(&LibUser);
        MeSSComponent::Instance().GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_DEBUG, true);
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
