
/*
 * *******************************************************************************
 * *      
 * *      
 * *******************************************************************************
 * *     
 * *      PROJECT         : DRE
 * *      FILE            : CommonMeSS.cpp
 * *      MODULE          : common
 * *      ENGINEER        : Ananth,Prabhakar,krishna
 * *      DESCRIPTION     : This file include MESS implementation part of managment. 
 *                      MESS thread which runs as a client, sends and receives configuraiton request/response.
 * *      HISTORY         : <Initial Implementation>
 * *      
 * *******************************************************************************
 * */
#include "LibCli.h"
#include "HAMeSSComponent.h"
#include "CommonMeSS.h"
#include "AvailabilityManager_cfg.h"
#include "CommonStructure.h"
#include "InterfaceDefs.h"
#include "Component.h"
#include "Common.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"
#include "Common.pb.h"
#include "utils.h"
#include "cmd_utils.h"
#include <cstring>
#include "Compo_def.h"
#include "CMAPICommon.h"
#include "CMApiComp.h"
#include "CMApiHA.h"
#include "CMAPIConfig.h"
#include "iwfconfig.pb.h"
#include "iwfconfig_def.h"
#include "CMApiIwf.h"
#include "dreconfig.pb.h"
#include <map>
#include "CMAPILib.h"
#include "Logger.h"
#define USE_CMAPI_COMM  1
#define     USE_STRUCT_COMM 0
using namespace eAccelero;
bool messThreadExit;
extern "C" void* MeSSThread(void *args);
extern "C" void* ConfigFetchThread(void *args);
class CmnMgmtMess;

extern "C" void SendConfigRequest(int port,void* buf,int len,int cmdID,int interfaceID);
extern "C" int SendResponseToMgmt(void *result,void *port);
extern "C" int SendResponseToMgmt2(void *result,int port);

extern "C" int NumThreads;
extern "C" pthread_mutex_t ClientCounterLock; 
extern "C" struct _ClientData* ClientThreadData;

extern "C" void TerminateCmnMgmtMeSS();
extern "C" void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);

class CmnMgmtMess: public HAMeSSComponent
{
    private:
        CmnMgmtMess() : HAMeSSComponent("CLI", COMP_CLI_PROC)

    {
#if 1
        m_objSyslogChannel = new SyslogChannel("CLI", (LOG_PID),LOG_LOCAL6);
        this->GetLogger().SetLogChannel(m_objSyslogChannel);
#endif
        /***************************** REPLICATION  MANAGER RESPONCES ******************************/

        /*MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_REPLFLAG), 
          CallbackSlot<CmnMgmtMess, AllResponses>(this, &CmnMgmtMess::SetReplicationFlagRespCbk));

          MeSSObj().RegisterRespHandler(MakeMsgId(I_REPMGR_ID, M_REPMGR_LOGLEVEL), 
          CallbackSlot<CmnMgmtMess, AllResponses>(this, &CmnMgmtMess::SetReplLogLevelRespCbk));*/
        m_cmapi = NULL;
        m_hacmapi = NULL;
        m_dtfcmapi = NULL;
        m_prodcmapi = NULL; 
        m_iwfcmapi = NULL;
    }
        CMApiComponents *m_cmapi;
        CMApiHA         *m_hacmapi;
        CMAPIConfig     *m_dtfcmapi;
        CMAPIProdConfig *m_prodcmapi;
        CMApiIwfConfig  *m_iwfcmapi;
        std::map<string, int> peerIdMap;
        //peersIdMap peerIdMap;
        SyslogChannel *m_objSyslogChannel;
    public:
        static CmnMgmtMess *cliApp;
        ~CmnMgmtMess()
        {
            if(m_objSyslogChannel != NULL)
                delete m_objSyslogChannel;
            m_objSyslogChannel = NULL;
            m_cmgrAvlble.signal();
        }

        static bool ms_cliInitialized;
        CondVar m_cmgrAvlble;

	static CondVar m_terminateMess;
        uint16_t m_oldInstanceId;

        void RegisterMethods()
        {
            CLOG_DEBUG("Registering methods in CLI\n");
        }


        void Initialize()
        {
            HAMeSSComponent::Initialize();
            m_cmapi = new CMApiComponents();
            m_cmapi->InitializeLibrary();        
            m_hacmapi = new CMApiHA();
            m_hacmapi->InitializeLibrary();
            m_dtfcmapi = new CMAPIConfig();
            m_dtfcmapi->InitializeLibrary();
            m_prodcmapi =  new CMAPIProdConfig();
            m_prodcmapi->InitializeLibrary();
            m_iwfcmapi = new CMApiIwfConfig();
            m_iwfcmapi->InitializeLibrary();

            m_cmapi->UpdateCurrentInstanceId(MeSSObj().Self().instance);

        }
        void Terminate()
        {   
/*	    delete m_cmapi;
	    delete m_hacmapi;
	    delete m_dtfcmapi;
	    delete m_prodcmapi;
	    delete m_iwfcmapi;*/
            HAMeSSComponent::Terminate();
        }

        //Over-riding HAMeSSComponent functions.
        int ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId)
        {
            m_oldInstanceId = MeSS::MeSSObj().Self().instance;
            return 0;
        }
        int ProcessAvailabilityStatusResetPostFunc(bool switchOver)
        {
            uint16_t newInstanceId = MeSS::MeSSObj().Self().instance;
            if (!ms_cliInitialized)
            {
                ms_cliInitialized = true;
                return 0;
            }

            if (m_oldInstanceId == newInstanceId)
            {
                CLOG_DEBUG("No change in instance Id %d, nothing to do", m_oldInstanceId);
                return 0;
            }

            CLOG_DEBUG("ProcessAvailabilityStatusResetPostFunc with switchover flag as %d",switchOver);

            if (switchOver)
            {
                m_hacmapi->SetData(HA_SWITCHOVER, CMAPIRetCodes::CMAPI_SUCCESS);
            }

            m_cmapi->UpdateCurrentInstanceId(newInstanceId);

            return 0;
        }
        int ProcessComponentStatusUpdate(uint16_t componentId, eAccelero::HAComponentStatus newStatus)
        {
            //If CMGR is initialized then signal DRE to proceed with Config fetch.                 
            if(componentId == COMP_CONFIG_MANAGER && newStatus == COMPONENT_STATUS_INITIALIZED)
            {   
                CLOG_DEBUG(" Going ahead with initialization since received an update that CMGR is initialized.");
                m_cmgrAvlble.signal();
            }
            return 0;
        }
        int HandleCmgrErrorResponse(AllResponses resp);
        int HandleDreErrorResponse();
        int FetchConfiguration();
        static CmnMgmtMess* CreateObj(void);
#if USE_CMAPI_COMM
        #include "iwf_CommonMess.cpp"
        void setUser(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            int retVal=0;
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp = NULL;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            string userName = "";
            char password[PASSWORD_LENGTH];//to be populated by encrypted password by any algo (MD5)
            Users userlist;
            UserResp userRsp;
            UserInfo *userInfo = userlist.add_userdata();
            Group *group = userInfo->mutable_usergroup();
            rsp->cmd_id = cmdID;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            if(cliReq->Payload.dreUserConfigPayload.UserKeyInfo.UserName != INVALID_STR) {
                userName = cliReq->Payload.dreUserConfigPayload.UserKeyInfo.UserName;
                CLOG_DEBUG(" userName = %s",userName.c_str());
                userInfo->set_username(userName);
            }
            if(!(cliReq->OP_CODE == DELETE) && (cliReq->Payload.dreUserConfigPayload.UserConfigInfo.password[0] != INVALID_STR)) {
                memcpy(password, cliReq->Payload.dreUserConfigPayload.UserConfigInfo.password,PASSWORD_LENGTH);
                CLOG_DEBUG(" password = %s",password);
                userInfo->set_password((void *)&password,PASSWORD_LENGTH);
            }

            if(cliReq->OP_CODE == DELETE)
            {
                if ((retVal = m_prodcmapi->DeleteUser(userlist,&userRsp)) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("CMAPILib::Deleted user success");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("CMAPILib::Delete User failed");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(userRsp.errordetails_size() == 1)
                    {
                        ErrorDetails det = userRsp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else if(cliReq->OP_CODE == ADD)
            {

                if (cliReq->Payload.dreUserConfigPayload.UserConfigInfo.privilege ==  PRIVILEGE_ADMIN)
                {
                    CLOG_DEBUG("groupname: admin");
                    group->set_groupname("admin");
                }
                else if (cliReq->Payload.dreUserConfigPayload.UserConfigInfo.privilege ==  PRIVILEGE_OPERATOR)
                {
                    CLOG_DEBUG("groupname: operator");
                    group->set_groupname("operator");
                }
                else {}

                if ((retVal = m_prodcmapi->AddUser(userlist,&userRsp)) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("CMAPILib:Add user success ");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("CMAPILib:Add User failed ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(userRsp.errordetails_size() == 1)
                    {
                        ErrorDetails det = userRsp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else /*modify command*/
            {
                if ((retVal = m_prodcmapi->ChangePassword(userName, password, PASSWORD_LENGTH,&userRsp)) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("CMAPILib::Reset password success ");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("CMAPILib::Reset password failed ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(userRsp.errordetails_size() == 1)
                    {
                        ErrorDetails det = userRsp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            SendResponseToMgmt2((void*)rsp, portnum);   
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            return; 
        }

        void ShowUser(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp; 
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            SetConfigReq *cliReq = (SetConfigReq *)req;
            string userName = "";
            Users userlist;
            ErrorDetails err;
            int retVal;
            int user_flag = 0;

            if(cliReq->Payload.dreUserConfigPayload.UserKeyInfo.UserName[0] != INVALID_STR) {
                userName = cliReq->Payload.dreUserConfigPayload.UserKeyInfo.UserName;
                CLOG_DEBUG("UserName : %s",userName.c_str());
                user_flag = 1;
            }

            if ((retVal = m_prodcmapi->GetUser(userName, userlist, err)) == CMAPI_SUCCESS)
            {
                int numOfUser = userlist.userdata_size();
                CLOG_INFO("Num of Users = %d",numOfUser);
                if(user_flag == 1 && numOfUser == 0)
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    ErrorDetails Err;
                    Err.set_errormsgkey("user.authentication.err.invalid.logindetails");
                    Err.add_variables(userName);
                    //Form Error Response Message
                    formErrorMessage(Err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   User-Table");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                            FIELD_DELIMITER,"UserName", 
                            FIELD_DELIMITER,"Privilege", ROW_DELIMITER);

                    for(int curUser = 0 ; curUser < numOfUser ; curUser++)
                    {
                        UserInfo user = userlist.userdata(curUser);
                        // password for user validation in cli
                        if((cmdID == C_cli_verify_passwd_Id) && (user.has_password()))
                            memcpy(rsp->password,user.password().c_str(),PASSWORD_LENGTH);

                        if(user.has_username())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",user.username().c_str(), FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                        Group group;
                        group = user.usergroup();
                        if(group.has_groupname())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",group.groupname().c_str());
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                    }   
                    CLOG_DEBUG("Get User Success");
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS; 
                }

            }
            else {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                if(err.IsInitialized()) 
                {
                    //Form Error Response Message
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }

            }
            rsp->cmd_id = cmdID;
            SendResponseToMgmt2((void*)rsp, portnum);   
            CLOG_DEBUG(" < %s ",__FUNCTION__);
        }       

        void SetDefaultRoute(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            DRECfgResp cfgResp;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            string hostName = "";
            string realmName = "";
            if(cliReq->Payload.dreDefaultRoutePayload.defaultRouteInfo.PeerHostIds[0] != INVALID_STR) {
                hostName = cliReq->Payload.dreDefaultRoutePayload.defaultRouteInfo.PeerHostIds;
                CLOG_DEBUG(" hostName = %s",hostName.c_str());
            }

            if(cliReq->Payload.dreDefaultRoutePayload.defaultRouteKeyInfo.RealmName[0] != INVALID_STR) {
                realmName = cliReq->Payload.dreDefaultRoutePayload.defaultRouteKeyInfo.RealmName;
                CLOG_DEBUG(" RealmName = %s",realmName.c_str());
            }

            if (cliReq->OP_CODE == DELETE)
            {

                if(m_prodcmapi->DeleteDefaultRoute(&cfgResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Deleted the Default Route");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else {
                    CLOG_ERROR("Error in Deleting Default Route");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(cfgResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = cfgResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }

                }
            }
            else
            {
                if(m_prodcmapi->SetDefaultRoute(hostName,realmName,&cfgResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Added the Default Route");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else {
                    CLOG_ERROR("Error in Adding Default Route");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(cfgResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = cfgResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }

            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);       
        }

        void ShowdefaultRouteConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            RealmConfig defRoute;
            ErrorDetails errResp;

            if(m_prodcmapi->GetDefaultRoute(defRoute, errResp) == CMAPI_SUCCESS)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Default-Route Table");
                RealmConfig *RC = &defRoute;
                if(RC->has_realmname())
                {
                    CLOG_DEBUG(" Succcess Fetching Default Route Information ");
                    CLOG_INFO("Default Route Count = 1");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                            FIELD_DELIMITER,"RealmName", 
                            FIELD_DELIMITER,"DefaultRoute", ROW_DELIMITER);
                    if(RC->has_realmname())     
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->realmname().c_str(),FIELD_DELIMITER);
                    else 
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                    if(RC->has_defaultroute())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->defaultroute().c_str(),ROW_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                    rsp->ResponseCode = CMGR_FETCH_SUCCESS; 
                }
                else
                {
                    CLOG_INFO("Default Route Count = 0");
                    rsp->ResponseCode = CMGR_FETCH_ERROR;  
                    CLOG_ERROR(" Error Fetching Default Route Information ");
                    if(errResp.IsInitialized())
                    {
                        //Form Error Response Message
                        formErrorMessage(errResp,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else{
                rsp->ResponseCode = CMGR_FETCH_ERROR;  
                CLOG_ERROR(" Error Fetching Default Route Information ");
                if(errResp.IsInitialized())
                {
                    //Form Error Response Message
                    formErrorMessage(errResp,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }

            CLOG_DEBUG(" < %s ",__FUNCTION__);
            rsp->cmd_id = cmdID;
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void ShowVersion(int portnum, void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            const char dreVersion[] = DRE_VER;

            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   DRE Version");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,"Diametriq DRE Version ",ROW_DELIMITER);
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,dreVersion, ROW_DELIMITER);
            CLOG_DEBUG("Diametriq DRE Version : %s",dreVersion);

            rsp->cmd_id = cmdID;
            rsp->ResponseCode = CMGR_FETCH_SUCCESS; 
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void GetNodeState(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            string NodeStatus = "";
            AvaMgrConfigResp Resp;
            if(m_hacmapi->GetNodeStatus(NodeStatus,&Resp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG("Successfully Got Node Status");
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                strncpy(rsp->payload,NodeStatus.c_str(),MAX_PAYLOAD_LEN - 1); 
                CLOG_DEBUG(" NodeStatus : %s",NodeStatus.c_str());
            }
            else
            {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("Error Getting Node Status");
                //Form Error Response Message
                if(Resp.errordetails_size() == 1)
                {
                    ErrorDetails det = Resp.errordetails(0);
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }

            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void SwitchOver(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            AvaMgrConfigResp Resp;
            if(m_hacmapi->SwitchOver(&Resp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG("Successfully SwitchOver done");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("SwitchOver Failed");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                //Form Error Response Message
                if(Resp.errordetails_size() == 1)
                {
                    ErrorDetails det = Resp.errordetails(0);
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void ShowAvamgrConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            AvaMgrConfig Avamgrconfig;
            AvaMgrConfigResp Resp;
            if(m_hacmapi->GetAMConfiguration(&Avamgrconfig,&Resp) == CMAPI_SUCCESS)
            {
                AvaMgrConfig *avamgrconfig = &Avamgrconfig;
                CLOG_DEBUG("Successfully Got AVAMGR Config %s",avamgrconfig->DebugString().c_str());
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "HA_Configuration");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                        FIELD_DELIMITER,"Peer-Ping-Periodicity",
                        FIELD_DELIMITER,"Peer-Ack-Failures",
                        FIELD_DELIMITER,"Gateway-IP-Address",
                        FIELD_DELIMITER,"Arbtr-Ping-Periodicity",
                        FIELD_DELIMITER,"Arbtr-Ack-Failures",
                        FIELD_DELIMITER,"Process-Restart-Interval",
                        FIELD_DELIMITER,"Process-Restart-Count",
                        FIELD_DELIMITER,"Restart-Max-Count-For-Stop",
                        FIELD_DELIMITER,"Restart-Max-Interval-For-Stop",ROW_DELIMITER);
                if(avamgrconfig->has_peerpingperiodicity())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->peerpingperiodicity(),FIELD_DELIMITER);
                else 
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_peernumconsecpingackrcvfailures())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->peernumconsecpingackrcvfailures(),FIELD_DELIMITER);
                else 
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_arbitratoripaddress())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",avamgrconfig->arbitratoripaddress().c_str(),FIELD_DELIMITER);
                else 
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_arbitratorpingperiodicity())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->arbitratorpingperiodicity(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_arbitratornumconsecpingackrcvfailures())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->arbitratornumconsecpingackrcvfailures(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_processrestartmaxallowedinterval())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->processrestartmaxallowedinterval(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_processrestartmaxallowedcount())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->processrestartmaxallowedcount(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_processrestartmaxallowedcountforstop())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->processrestartmaxallowedcountforstop(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(avamgrconfig->has_processrestartmaxallowedintervalforstop())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",avamgrconfig->processrestartmaxallowedintervalforstop(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

            }
            else
            {
                CLOG_ERROR("Error Getting AVAMGR Config");
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                //Form Error Response Message
                if(Resp.errordetails_size() == 1)
                {
                    ErrorDetails det = Resp.errordetails(0);
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void SetConfigRealm(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            RealmsConfig RSC;
            DRECfgResp cfgResp;
            RealmConfig  *RC = RSC.add_realms();

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            string RealmName = "";
            string PeerHostId = "";
            string AltRealmName = "";
            long AppId = 0;
            string LocalAction = "";
            int Priority = 0;
            int RedirectHostUsage = 0;
            int RedirectMaxCacheTime = 0;
            if(cliReq->Payload.dreRealmPayload.realmKeyInfo.RealmName[0] != INVALID_STR)
            {
                RealmName = cliReq->Payload.dreRealmPayload.realmKeyInfo.RealmName;
                RC->set_realmname(RealmName);
                CLOG_DEBUG("RealmName : %s",RealmName.c_str());
            }
            if(cmdID == C_cli_configRealm_Id) 
            {
                // Add,Modify,Delete Realm 
                if(cliReq->OP_CODE == DELETE)
                {
                    if (m_prodcmapi->DeleteRealm(RealmName,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Deleted the Realm Configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else {
                        CLOG_ERROR("Error Deleting the Realm Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        //Form Error Response Message
                        if(cfgResp.errordetails_size() == 1)
                        {
                            ErrorDetails det = cfgResp.errordetails(0);
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
                else
                {
                    if(cliReq->Payload.dreRealmPayload.realmInfo.LocalAction != INVALID_NUM)
                    {
                        if(cliReq->Payload.dreRealmPayload.realmInfo.LocalAction == LOCAL_ACTION_LOCAL)
                            LocalAction = "Local";
                        else if(cliReq->Payload.dreRealmPayload.realmInfo.LocalAction == LOCAL_ACTION_RELAY) 
                        {
                            LocalAction = "Relay";
                            RC->set_enableproxyinfoavp(true);
                        }
                        else if(cliReq->Payload.dreRealmPayload.realmInfo.LocalAction == LOCAL_ACTION_PROXY)
                            LocalAction = "Proxy";
                        else
                            LocalAction = "Redirect";
                        CLOG_DEBUG("LocalAction = %s",LocalAction.c_str());
                        RC->set_localaction(LocalAction);
                    }
                    if(cliReq->Payload.dreRealmPayload.realmInfo.RedirectHostUsage != INVALID_NUM)
                    {
                        RedirectHostUsage = cliReq->Payload.dreRealmPayload.realmInfo.RedirectHostUsage;
                        CLOG_DEBUG("RedirectHostUsage = %d",RedirectHostUsage);
                        RC->set_redirecthostusage(RedirectHostUsage);
                    }
                    if(cliReq->Payload.dreRealmPayload.realmInfo.RedirectMaxCacheTime != INVALID_NUM)
                    {
                        RedirectMaxCacheTime = cliReq->Payload.dreRealmPayload.realmInfo.RedirectMaxCacheTime;
                        CLOG_DEBUG("RedirectMaxCacheTime = %d",RedirectMaxCacheTime);
                        RC->set_redirectmaxcachetime(RedirectMaxCacheTime);
                    }
                    if(cliReq->OP_CODE == MODIFY)
                    {
                        if (m_prodcmapi->ModifyRealm(RSC,&cfgResp) == CMAPI_SUCCESS)
                        {
                            CLOG_DEBUG("Succesfully Modified the Realm Configuration");
                            rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                        }
                        else 
                        {
                            CLOG_ERROR("Error Modfifying the Realm Configuration ");
                            rsp->ResponseCode = DRE_CONFIG_ERROR;
                            //Form Error Response Message
                            if(cfgResp.errordetails_size() == 1)
                            {
                                ErrorDetails det = cfgResp.errordetails(0);
                                formErrorMessage(det,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
                            else
                            {
                                ErrorDetails det;
                                det.set_errormsgkey("config.common.err.generic.error");
                                formErrorMessage(det,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
                        }
                    }
                    else
                    {
                        if(m_prodcmapi->SetRealm(RSC,&cfgResp) == CMAPI_SUCCESS)
                        {
                            CLOG_DEBUG("Succesfully Added the Realm Configuration");
                            rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                        }
                        else 
                        {
                            CLOG_ERROR("Error Adding the Realm Configuration ");
                            rsp->ResponseCode = DRE_CONFIG_ERROR;
                            //Form Error Response Message
                            if(cfgResp.errordetails_size() == 1)
                            {
                                ErrorDetails det = cfgResp.errordetails(0);
                                formErrorMessage(det,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
                            else
                            {
                                ErrorDetails det;
                                det.set_errormsgkey("config.common.err.generic.error");
                                formErrorMessage(det,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
                        }
                    }
                }
            }
            else 
            {
                Destination *Dt = RC->add_destinfo();   
                // Add, Modify, Delete destination
                // vendor-id setting to zero 
                Dt->set_vendorid(0);
                if(cliReq->Payload.dreRealmPayload.realmKeyInfo.PeerHostId[0] != INVALID_STR)
                {
                    PeerHostId = cliReq->Payload.dreRealmPayload.realmKeyInfo.PeerHostId;
                    CLOG_DEBUG("PeerHostId = %s",PeerHostId.c_str());
                    Dt->set_peername(PeerHostId);
                }
                if(cliReq->Payload.dreRealmPayload.realmInfo.AltRealmName[0] != INVALID_STR)
                {
                    AltRealmName = cliReq->Payload.dreRealmPayload.realmInfo.AltRealmName;
                    CLOG_DEBUG("AltRealmName = %s",AltRealmName.c_str());
                    Dt->set_realmname(AltRealmName);
                }
                if(cliReq->Payload.dreRealmPayload.realmKeyInfo.AppId != INVALID_NUM)
                {
                    AppId = cliReq->Payload.dreRealmPayload.realmKeyInfo.AppId;
                    CLOG_DEBUG("AppId = %d",AppId);
                    Dt->set_applicationid(AppId);
                }
                if(cliReq->Payload.dreRealmPayload.realmInfo.Priority != INVALID_NUM)
                {
                    Priority = cliReq->Payload.dreRealmPayload.realmInfo.Priority;
                    CLOG_DEBUG("Priority = %d",Priority);
                    Dt->set_priority(Priority);
                }
                if(cliReq->OP_CODE == DELETE)
                {
                    if (m_prodcmapi->DeleteDestination(RSC,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Deleted the destination");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else {
                        CLOG_ERROR("Error deleting the destination");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        //Form Error Response Message
                        if(cfgResp.errordetails_size() == 1)
                        {
                            ErrorDetails det = cfgResp.errordetails(0);
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
                else if(cliReq->OP_CODE == MODIFY)
                {
                    if (m_prodcmapi-> ModifyDestination(RSC,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Modified the Destination Configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else {
                        CLOG_ERROR("Error Modfifying the Destination Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        //Form Error Response Message
                        if(cfgResp.errordetails_size() == 1)
                        {
                            ErrorDetails det = cfgResp.errordetails(0);
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }

                }  
                else
                {
                    if(m_prodcmapi->SetDestination(RSC,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Added the Destination Configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else {
                        CLOG_ERROR("Error Adding the Destination Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        //Form Error Response Message
                        if(cfgResp.errordetails_size() == 1)
                        {
                            ErrorDetails det = cfgResp.errordetails(0);
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }

                }
            }
            rsp->cmd_id = cmdID;
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void PeerControl(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            string hostName = "";
            string realmName = "";
            int status;
            PeersConfig PSC;
            DRECfgResp cfgResp;
            PeerConfig *PC = PSC.add_peers();

            hostName = cliReq->Payload.drePeerPayload.peerKeyInfo.HostName;
            PC->set_peerhostname(hostName);
            CLOG_DEBUG("hostName = %s",hostName.c_str());

            realmName = cliReq->Payload.drePeerPayload.peerKeyInfo.RealmName;
            PC->set_realm(realmName);
            CLOG_DEBUG("realmName = %s",realmName.c_str());

            status = cliReq->Payload.drePeerPayload.peerInfo.Enable_Status;
            CLOG_DEBUG("status = %d",status);
            if(status==ENABLE)
            {
                PC->set_peerstatus(true);
            }
            else
            {
                PC->set_peerstatus(false);
            }

            if(m_prodcmapi->SetPeerStatus(PSC,&cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG("Succesfully set Peer state");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error setting peer state");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                //Form Error Response Message
                if(cfgResp.errordetails_size() == 1)
                {
                    ErrorDetails det = cfgResp.errordetails(0);
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void Settlsconfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            TLSConfig tlsconfig;

            if(cliReq->Payload.tlsconfig.identityverification != INVALID_NUM)
            {
                int id_verification = cliReq->Payload.tlsconfig.identityverification;
                CLOG_DEBUG("id_verification = %d",id_verification);
                (id_verification==ENABLE)?tlsconfig.set_enableidverification(true):tlsconfig.set_enableidverification(false);
            }
            if(cliReq->Payload.tlsconfig.crlverification != INVALID_NUM)
            {
                int crl_verification = cliReq->Payload.tlsconfig.crlverification;
                CLOG_DEBUG("crl_verification = %d",crl_verification);
                (crl_verification==ENABLE)?tlsconfig.set_enablecrlverification(true):tlsconfig.set_enablecrlverification(false);
            }

            if(m_prodcmapi->SetTLSConfiguration(tlsconfig) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG("Succesfully set TLS configuration");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }    
            else
            {
                CLOG_ERROR("Error setting TLS configuration");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void SetTrustedCA(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            string file_name = "";
            TrustedCAConfiguration trustedca;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            if(cliReq->Payload.trustedca.cafile[0] != INVALID_STR)
            {
                file_name = cliReq->Payload.trustedca.cafile;
                CLOG_DEBUG(" ca_file_name =%s",file_name.c_str());
                trustedca.set_cafile(file_name);
            }
            if(cliReq->Payload.trustedca.crlfile[0] != INVALID_STR)
            {
                file_name = cliReq->Payload.trustedca.crlfile;
                CLOG_DEBUG(" crl_file_name =%s",file_name.c_str());
                trustedca.set_crlfile(file_name);
            }

            if(cliReq->OP_CODE == DELETE)
            {
                if(cmdID != C_cli_notrustedca_Id) 
                {
                    if(m_prodcmapi->DeleteCACRLConfiguration(trustedca) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully deleted trustedCA configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error deleting trustedCA configuration");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                    }
                }
                else
                {
                    if(m_prodcmapi->RemoveCACRLAssociation(trustedca) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully removed the CRL association");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error removing the CRL configuration");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                    }

                }
            }
            else if(cliReq->OP_CODE == MODIFY)
            {
                if(m_prodcmapi->ModifyCACRLConfiguration(trustedca) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Modified trustedCA configuration");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("Error Modifying trustedCA configuration");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                }
            }
            else
            {
                if(m_prodcmapi->AddCACRLConfiguration(trustedca) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Added trustedCA configuration");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("Error Adding trustedCA configuration");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                }
            }
            if(rsp->ResponseCode == DRE_CONFIG_ERROR)
            {
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void SetCipherSuite(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            string cipher_suite = "";

            if(cliReq->Payload.ciphersuite.ciphersuitename[0] != INVALID_STR)
            {
                cipher_suite = cliReq->Payload.ciphersuite.ciphersuitename;
                CLOG_DEBUG("cipher_suite = %s",cipher_suite.c_str());
                if(cliReq->Payload.ciphersuite.cipherenable != INVALID_NUM)
                {
                    if(cliReq->Payload.ciphersuite.cipherenable == ENABLE)
                    {
                        if(m_prodcmapi->EnableTlsCipherSuite(cipher_suite) == CMAPI_SUCCESS)
                        {
                            CLOG_DEBUG("Succesfully enabled Cipher Suite configuration");
                            rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                        }
                        else
                        {
                            CLOG_ERROR("Error enabling Cipher Suite configuration");
                            rsp->ResponseCode = DRE_CONFIG_ERROR;
                        }
                    }
                    else
                    {
                        if(m_prodcmapi->DisableTlsCipherSuite(cipher_suite) == CMAPI_SUCCESS)
                        {
                            CLOG_DEBUG("Succesfully disabled Cipher Suite configuration");
                            rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                        }
                        else
                        {
                            CLOG_ERROR("Error disabling Cipher Suite configuration");
                            rsp->ResponseCode = DRE_CONFIG_ERROR; 
                        }
                    }

                    if(rsp->ResponseCode == DRE_CONFIG_ERROR)
                    {
                        ErrorDetails err;
                        m_prodcmapi->GetLastCallErrorDetails(err);
                        //Form Error Response Message
                        if(err.IsInitialized())
                        {
                            formErrorMessage(err,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            err.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(err,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
            }
            else
                CLOG_ERROR("Mandotary Field Cipher-Suite name is not set");
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void SetSctpConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            SctpProtocol sctpconfig;

            if(cliReq->Payload.sctpconfig.heartbeat != INVALID_NUM)
            {
                int heartbeat = cliReq->Payload.sctpconfig.heartbeat;
                CLOG_DEBUG("heartbeat = %d ",heartbeat);
                (heartbeat==ENABLE)?sctpconfig.set_heartbeatenable(true):sctpconfig.set_heartbeatenable(false);   
            }
            if(cliReq->Payload.sctpconfig.heartbeattimeout != INVALID_NUM)
            {
                int timeout = cliReq->Payload.sctpconfig.heartbeattimeout;
                CLOG_DEBUG("heartbeattimeout = %d ",timeout);
                sctpconfig.set_hearbeattimeout(timeout);
            } 
            if(cliReq->Payload.sctpconfig.inittimeout != INVALID_NUM)
            {
                int inittimeout = cliReq->Payload.sctpconfig.inittimeout;
                CLOG_DEBUG("inittimeout = %d ",inittimeout);
                sctpconfig.set_initialtimeout(inittimeout);
            }
            if(cliReq->Payload.sctpconfig.maxattempts != INVALID_NUM)
            {
                int maxattempts = cliReq->Payload.sctpconfig.maxattempts;
                CLOG_DEBUG("maxattempts = %d ",maxattempts);
                sctpconfig.set_maximumattempts(maxattempts);
            }
            if(cliReq->Payload.sctpconfig.pathfailureretrycount != INVALID_NUM)
            {
                int pathfailure = cliReq->Payload.sctpconfig.pathfailureretrycount;
                CLOG_DEBUG("pathfailure = %d ",pathfailure);
                sctpconfig.set_pathfailretrycount(pathfailure);
            }
            if(cliReq->Payload.sctpconfig.rtoinit != INVALID_NUM)
            {
                int rtoint = cliReq->Payload.sctpconfig.rtoinit;
                CLOG_DEBUG("rtoint = %d ",rtoint);
                sctpconfig.set_rtoinitial(rtoint);
            }
            if(cliReq->Payload.sctpconfig.rtomin != INVALID_NUM)
            {
                int rtomin = cliReq->Payload.sctpconfig.rtomin;
                CLOG_DEBUG("rtomin = %d ",rtomin);
                sctpconfig.set_rtominimum(rtomin);
            }
            if(cliReq->Payload.sctpconfig.rtomax != INVALID_NUM)
            {
                int rtomax = cliReq->Payload.sctpconfig.rtomax;
                CLOG_DEBUG("rtomax = %d ",rtomax);
                sctpconfig.set_rtomaximum(rtomax);
            }
            if(m_prodcmapi->SetSctpProtocolConfiguration(sctpconfig) == CMAPI_SUCCESS) 
            {
                CLOG_DEBUG("Succesfully Updated SCTP configuration");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error Updating SCTP configuration");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void SetPredictiveLoopDetection(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            GeneralConfig generalconfig;
            int Val=0;

            Val = cliReq->Payload.predictiveLoopdetection.predectiveloopdetection;
            generalconfig.set_ispredictiveloopavdrequired(Val);
            CLOG_DEBUG("predictiveloopavdrequired = %d",Val);
            if(m_prodcmapi->SetGeneralConfiguration(generalconfig) == CMAPI_SUCCESS) 
            {
                CLOG_DEBUG("Succesfully Updated ispredictiveloopavdrequired value");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error Updating ispredictiveloopavdrequired value");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
        
        void SetSnaptrSupport(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            GeneralConfig generalconfig;
            int Val=0;

            Val = cliReq->Payload.snaptrSupport.snaptrsupport;
            generalconfig.set_issnaptrsupported(Val);
            CLOG_DEBUG("snaptrsupport = %d",Val);
            if(m_prodcmapi->SetGeneralConfiguration(generalconfig) == CMAPI_SUCCESS) 
            {
                CLOG_DEBUG("Succesfully Updated snaptr support value");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error Updating snaptr support value");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
 
        void SetIpCheck(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            GeneralConfig generalconfig;
            int Val=0;

            Val = cliReq->Payload.peeripcheck.ipcheck;
            generalconfig.set_enablepeeripcheck(Val);
            CLOG_DEBUG(" ipcheck = %d",Val);
            if(m_prodcmapi->SetGeneralConfiguration(generalconfig) == CMAPI_SUCCESS) 
            {
                CLOG_DEBUG("Succesfully Updated Peer-Ip-check value");
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error Updating Peer-Ip-check value");
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
        void ShowStaticRouting(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;

            StaticRoutingTableConfigReq SRTC;
            StaticRoutingTableConfigResp SRTCResp;
            string hostName = "";
            string realmName = "";

            if(cmdID == C_cli_showstaticrouting_Id)
            {
                StaticRoutingTableConfig *srt = SRTC.add_srtconfig();
                if(cliReq->Payload.staticRoutingPayload.dest_info.dest_hostname[0] != INVALID_STR)
                {
                    hostName = cliReq->Payload.staticRoutingPayload.dest_info.dest_hostname;
                    CLOG_DEBUG(" Destination host Name = %s",hostName.c_str());
                    srt->set_destionatinhost(hostName); 
                }
                if(cliReq->Payload.staticRoutingPayload.dest_info.dest_realmname[0] != INVALID_STR)
                {
                    realmName = cliReq->Payload.staticRoutingPayload.dest_info.dest_realmname;
                    CLOG_DEBUG(" Destination realm Name = %s",realmName.c_str());
                    srt->set_destionatinrealm(realmName);
                }
            }

            if(m_prodcmapi->GetStaticRoutingEntries(SRTC, SRTCResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG("Succesfully received the Static Routing configuration");
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                unsigned int NumOfEntries = SRTCResp.srtconfig_size();
                CLOG_INFO(" Num of Static Routing Entries = %d ",NumOfEntries);
                if(NumOfEntries != 0)
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Static Routing Table");
                    if(cmdID == C_cli_showallstaticrouting_Id)
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c",
                                FIELD_DELIMITER,"Dest-Peer-Name", 
                                FIELD_DELIMITER,"Dest-Realm-Name",
                                FIELD_DELIMITER,"Peer-Name", 
                                FIELD_DELIMITER,"Realm-Name", 
                                FIELD_DELIMITER,"Application-Id", 
                                FIELD_DELIMITER,"Priority", ROW_DELIMITER);
                    }
                    else
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",
                                FIELD_DELIMITER,"Peer-Name", 
                                FIELD_DELIMITER,"Realm-Name", 
                                FIELD_DELIMITER,"Application-Id", 
                                FIELD_DELIMITER,"Priority", ROW_DELIMITER);
                    }
                    for(unsigned int i=0; i<NumOfEntries; i++)
                    {
                        StaticRoutingTableConfig srt = SRTCResp.srtconfig(i);
                        if(cmdID == C_cli_showallstaticrouting_Id)
                        {
                            if(srt.has_destionatinhost())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", srt.destionatinhost().c_str(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                            if(srt.has_destionatinrealm())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", srt.destionatinrealm().c_str(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                        }
                        if(srt.has_peer())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", srt.peer().c_str(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                        if(srt.has_realm())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", srt.realm().c_str(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                        if(srt.has_applicationid())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%d%c", srt.applicationid(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                        if(srt.has_priority())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%d%c", srt.priority(),ROW_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",ROW_DELIMITER);
                    }
                }
                else
                {
                    CLOG_ERROR("Error Fetching the Static Routing configuration ");
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                }
            }
            else
            {
                CLOG_ERROR("Error Fetching the Static Routing configuration ");
                rsp->ResponseCode = CMGR_FETCH_ERROR;
            }

            if(rsp->ResponseCode == CMGR_FETCH_ERROR)
            {
                //Form Error Response Message
                if(SRTCResp.errordetails_size() == 1)
                {
                    ErrorDetails det = SRTCResp.errordetails(0);
                    formErrorMessage(det,rsp);
                    CLOG_DEBUG("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_DEBUG("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
        void SetStaticRouting(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            rsp->ResponseCode = DRE_CONFIG_SUCCESS;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            StaticRoutingTableConfigReq SRTC;
            StaticRoutingTableConfig *srt = SRTC.add_srtconfig();
            StaticRoutingTableConfigResp SRTCResp;
            string hostName = "";
            string realmName = "";
            int priority = 0;
            long app_id = 0;

            if(cliReq->Payload.staticRoutingPayload.dest_info.dest_hostname[0] != INVALID_STR)
            {
                hostName = cliReq->Payload.staticRoutingPayload.dest_info.dest_hostname;
                CLOG_DEBUG(" Destination host Name = %s",hostName.c_str());
                srt->set_destionatinhost(hostName); 
            }
            if(cliReq->Payload.staticRoutingPayload.dest_info.dest_realmname[0] != INVALID_STR)
            {
                realmName = cliReq->Payload.staticRoutingPayload.dest_info.dest_realmname;
                CLOG_DEBUG(" Destination realm Name = %s",realmName.c_str());
                srt->set_destionatinrealm(realmName);
            }
            if(cliReq->Payload.staticRoutingPayload.peer_info.peername[0] != INVALID_STR)
            {
                hostName = cliReq->Payload.staticRoutingPayload.peer_info.peername;
                CLOG_DEBUG(" peer Name = %s",hostName.c_str());
                srt->set_peer(hostName);
            }
            if(cliReq->Payload.staticRoutingPayload.peer_info.realmname[0] != INVALID_STR)
            {
                realmName = cliReq->Payload.staticRoutingPayload.peer_info.realmname;
                CLOG_DEBUG(" Realm Name = %s",realmName.c_str());
                srt->set_realm(realmName);
            }
            if(cliReq->Payload.staticRoutingPayload.peer_info.appId != INVALID_NUM)
            {
                app_id = cliReq->Payload.staticRoutingPayload.peer_info.appId;
                CLOG_DEBUG(" App_id = %ld",app_id);
                srt->set_applicationid(app_id);
            }
            if(cliReq->Payload.staticRoutingPayload.peer_info.priority != INVALID_NUM)
            {
                priority = cliReq->Payload.staticRoutingPayload.peer_info.priority;
                CLOG_DEBUG(" priority = %d",priority);
                srt->set_priority(priority);
            }

            if(cliReq->OP_CODE == DELETE)
            {
                if(m_prodcmapi->DeleteStaticRoutingEntry(SRTC, SRTCResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Deleted the Static Routing entry");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("Error Deleting the Static Routing entry ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                }
            }
            else if (cliReq->OP_CODE == MODIFY)
            {
                if(m_prodcmapi->ModifyStaticRoutingEntry(SRTC, SRTCResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Modified the Static Routing entry");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("Error Modifying the Static Routing entry ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                }
            }
            else
            {
                if(m_prodcmapi->AddStaticRoutingEntry(SRTC, SRTCResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Added the Static Routing entry");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else
                {
                    CLOG_ERROR("Error Adding the Static Routing entry ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                }
            }  

            if(rsp->ResponseCode == DRE_CONFIG_ERROR)
            {
                //Form Error Response Message
                if(SRTCResp.errordetails_size() == 1)
                {
                    ErrorDetails det = SRTCResp.errordetails(0);
                    formErrorMessage(det,rsp);
                    CLOG_DEBUG("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_DEBUG("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
        void SetConfigPeer(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            PeersConfig PSC;
            PeerConfig *PC = PSC.add_peers();   
            DRECfgResp cfgResp;
            string hostName = "";
            string realmName = "";
            bool tlsEnabled = 0;
            bool isDisconnectCauseSupported = 0;
            string transportType = "";
            string serverIpAddr = "";
            int port = 0;
            int tcTimerVal=0;
            int watchdogTimerVal = 0;
            int expiryTimerVal = 0;
            int busyReconnectTimerVal=0;
            int doNotWantTalkToYouReconnectTimerVal = 0;
            int num_dict = 0;
            string dict_name = "";
            bool failbackEnable = 0;
            bool failoverEnable = 0;
            bool isMate = 0;
            string AltHostName = "";


            if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.HostName[0] != INVALID_STR) 
            {
                hostName = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.HostName;
                CLOG_DEBUG(" hostName = %s",hostName.c_str());
            }

            if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.RealmName[0] != INVALID_STR) 
            {
                realmName = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.RealmName;
                CLOG_DEBUG(" realmName = %s",realmName.c_str());
            }
            if(cliReq->OP_CODE == DELETE)
            {   
                if(cmdID == C_cli_no_peer_Id) 
                {
                    if(m_prodcmapi->RemovePeerConfig(hostName,realmName,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Deleted the Peer entry");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error Deleting the Peer Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                    }
                }
                else if(cmdID == C_cli_no_peersecondaryip_Id)
                {
                    PC->set_peerhostname(hostName);
                    PC->set_realm(realmName); 
                    if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[0][0] != INVALID_STR)
                    {
                        serverIpAddr = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[0];
                        PC->add_secondaryipaddr(serverIpAddr);
                    }
                    if(m_prodcmapi->DeleteSecIPFromPeer(PSC,&cfgResp)  == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Deleted Secondary-ip from peer");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error Deleting the Secondary-ip from peer");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                    }
                }
                else
                {
                    if(m_prodcmapi->RemoveAlternatePeer(hostName,realmName,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Deleted the alternate-Peer entry");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error Deleting the alternate-peer Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                    }
                }
                if(rsp->ResponseCode == DRE_CONFIG_ERROR)
                {
                    //Form Error Response Message
                    if(cfgResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = cfgResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_DEBUG("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_DEBUG("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else{
                PC->set_peerhostname(hostName);
                PC->set_realm(realmName); 
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TransportType != INVALID_NUM)
                {
                    if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TransportType == TRANSTYPE_TCP)
                        transportType = "TCP";
                    else
                    {
                        transportType = "SCTP";
                        for(int j = 0;j < MAX_LOCALTRANSPORT_ATTRIBUTES;j++)
                        {
                            if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[j][0] != INVALID_STR)
                            {
                                serverIpAddr = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[j];
                                CLOG_DEBUG("secondary-Ips = %s",serverIpAddr.c_str());
                                PC->add_secondaryipaddr(serverIpAddr);
                            }
                        }
                    }
                    CLOG_DEBUG("TransportType =%s",transportType.c_str());
                    PC->set_transporttype(transportType);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr[0] != INVALID_STR) 
                {
                    serverIpAddr = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr;
                    CLOG_DEBUG("serverIpAddr = %s",serverIpAddr.c_str());
                    PC->set_serveripaddr(serverIpAddr);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.PortNumber != INVALID_NUM) 
                {
                    port = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.PortNumber;
                    CLOG_DEBUG("port = %d",port);
                    PC->set_port(port);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.SecurePortNumber != INVALID_NUM) 
                {
                    port = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.SecurePortNumber;
                    CLOG_DEBUG("SecurePort = %d",port);
                    PC->set_secureport(port);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failback != INVALID_NUM) 
                {
                    failbackEnable = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failback;
                    CLOG_DEBUG("failbackEnable = %d",failbackEnable);
                    (failbackEnable==ENABLE)?PC->set_failebackenable(true):PC->set_failebackenable(false);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failover != INVALID_NUM) 
                {
                    failoverEnable =cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failover;
                    CLOG_DEBUG("failoverEnable = %d",failoverEnable);
                    (failoverEnable==ENABLE)?PC->set_failoverenable(true):PC->set_failoverenable(false);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.AltHostName[0] != INVALID_STR)
                {
                    AltHostName = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.AltHostName;
                    CLOG_DEBUG("AltHostName = %s",AltHostName.c_str());
                    PC->set_altpeername(AltHostName);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue != INVALID_NUM) 
                {
                    watchdogTimerVal =cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue;
                    CLOG_DEBUG("watchdogTimerVal = %d",watchdogTimerVal);
                    PC->set_watchdogtimer(watchdogTimerVal);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue != INVALID_NUM) 
                {
                    tcTimerVal =cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue;
                    CLOG_DEBUG("tcTimerVal = %d",tcTimerVal);
                    PC->set_tctimerval(tcTimerVal);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue != INVALID_NUM) 
                {
                    expiryTimerVal =cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue;
                    CLOG_DEBUG("expiryTimerVal = %d",expiryTimerVal);
                    PC->set_expirytimer(expiryTimerVal);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.busyReconnectTimerVal != INVALID_NUM) 
                {
                    busyReconnectTimerVal =cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.busyReconnectTimerVal;
                    CLOG_DEBUG("busyReconnectTimerVal = %d",busyReconnectTimerVal);
                    PC->set_busyreconnecttimerval(busyReconnectTimerVal);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.doNotWantToTalkToYouReconnectTimer != INVALID_NUM) 
                {
                    doNotWantTalkToYouReconnectTimerVal =cliReq->Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.doNotWantToTalkToYouReconnectTimer;
                    CLOG_DEBUG("doNotWantToTalkToYouReconnectTimer = %d",doNotWantTalkToYouReconnectTimerVal);
                    PC->set_donotwanttotalktoyoutimerval(doNotWantTalkToYouReconnectTimerVal);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsMate != INVALID_NUM)
                {
                    isMate = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsMate;   
                    CLOG_DEBUG("isMate = %d",isMate);
                    (isMate==ENABLE)?PC->set_ismate(true):PC->set_ismate(false);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TLS != INVALID_NUM)
                {
                    tlsEnabled = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TLS;
                    CLOG_DEBUG("tlsEnabled = %d",tlsEnabled);
                    if (tlsEnabled==ENABLE)
                        PC->set_tlsenabled(true);
                    else 
                        PC->set_tlsenabled(false);
                }
                if(cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsDisconnectCauseSupported != INVALID_NUM)
                {
                    isDisconnectCauseSupported = cliReq->Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsDisconnectCauseSupported;
                    CLOG_DEBUG("IsDisconnectCauseSupported = %d",isDisconnectCauseSupported);
                    if (isDisconnectCauseSupported==ENABLE)
                        PC->set_issupportdisconnectcause(true);
                    else 
                        PC->set_issupportdisconnectcause(false);
                }
                if(cliReq->Payload.drePeerPayload.peerDictionaryInfo.num_dict != INVALID_NUM)
                {
                    num_dict = cliReq->Payload.drePeerPayload.peerDictionaryInfo.num_dict;
                    CLOG_DEBUG("num_dict_count = %d",num_dict);
                }
                for(int i = 0;i < num_dict;i++)
                {
                    dict_name = cliReq->Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[i];
                    CLOG_DEBUG("dict_name = %s",dict_name.c_str());
                    PC->add_dictionaryname(dict_name);
                }
                if (cliReq->OP_CODE == ADD)  
                {
                    // Peer state/status is set to enabled while the peer is added. so by default the peer-state will be enabled, however, enable/disable command is provided from cli so that the user can disable the peer-state later if required.
                    PC->set_peerstatus(true);
                    if(m_prodcmapi->SetPeerConfig(PSC,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Added Peer Config");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    } 
                    else 
                    {
                        CLOG_ERROR("Error in Adding Peer Config");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;           
                        //Form Error Response Message
                        if(cfgResp.errordetails_size() == 1)
                        {
                            ErrorDetails det = cfgResp.errordetails(0);
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
                else 
                {
                    if(m_prodcmapi->ModifyPeerConfig(PSC,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Modified Peer Config");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error in Modifying Peer Config");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        if(cfgResp.errordetails_size() == 1)
                        {
                            ErrorDetails det = cfgResp.errordetails(0);
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }

                    }
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetErlbfPeerConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            LBPeerGroupResp errResp;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            unsigned short peer_weight =0;
            unsigned short peer_priority =0;
            string realmName = "";               
            string peergroupname = "";
            string peer_name = "";
            LBPeer peer;
            //int peerId = 0;
            string peerKey = "";
            rsp->cmd_id = cmdID;

            if(cliReq->Payload.peerGroupsPayload.peer_group.groupname[0] != INVALID_STR)
            {
                peergroupname = cliReq->Payload.peerGroupsPayload.peer_group.groupname;
                CLOG_DEBUG("peergroupname =%s",peergroupname.c_str()); 
            }

            peer_name = cliReq->Payload.peerGroupsPayload.peer_info.peer_name;
            peer.set_lbpeername(peer_name);
            CLOG_DEBUG("peer_name =%s",peer_name.c_str()); 

            realmName = cliReq->Payload.peerGroupsPayload.peer_info.realmName;
            peer.set_lbpeerrealm(realmName);
            CLOG_DEBUG("realm_name =%s",realmName.c_str()); 
#if 0
            peerKey = peer_name + realmName;
            std::map<string, int>::iterator ii = peerIdMap.find(peerKey);
            if(ii!=peerIdMap.end())
            {
                peerId = (*ii).second;
                peer.set_lbpeerid(peerId);
            }
            else
            {
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }
#endif
            if(cliReq->OP_CODE == DELETE) 
            {
                if (m_cmapi->RemovePeerFromPeerGroup(peergroupname, peer_name, realmName,&errResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully deleted the Peer in peer-group");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                } 
                else {
                    CLOG_ERROR("Error deleting Peer in peer-group ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    if(errResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = errResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }

                }
                CLOG_DEBUG(" < %s ",__FUNCTION__);
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }

            if(cliReq->Payload.peerGroupsPayload.peer_info.peer_weight != INVALID_NUM)
            {
                peer_weight = cliReq->Payload.peerGroupsPayload.peer_info.peer_weight;
                CLOG_DEBUG("peer_weight = %d ",peer_weight);
                peer.set_lbpeerweight(peer_weight);
            }
            else if(cliReq->OP_CODE == ADD)
            {
                //default value for peer-weight 
                peer_weight = 100;
                CLOG_DEBUG("peer_weight = %d ",peer_weight);
                peer.set_lbpeerweight(peer_weight);
            }

            if(cliReq->Payload.peerGroupsPayload.peer_info.peer_priority != INVALID_NUM)
            {   
                peer_priority= cliReq->Payload.peerGroupsPayload.peer_info.peer_priority;
                CLOG_DEBUG("peer_priority = %d ",peer_priority);
                peer.set_lbpeerpriority(peer_priority);
            }

            if (cliReq->OP_CODE == MODIFY) 
            {   
                if (m_cmapi->ModifyPeerConfig(peergroupname, peer, &errResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Modified the  Peer under peer-group");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                } 
                else {
                    CLOG_ERROR("Error Modfifying the  Peer under peer-Group ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;           
                    if(errResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = errResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }

                }
                CLOG_DEBUG(" < %s ",__FUNCTION__);
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }
            else {
                if (m_cmapi->AddPeerToPeerGroup(peergroupname, peer, &errResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully added peer under peer-group");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;         

                }
                else {
                    CLOG_ERROR("Error adding peer under peer-group ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;                           
                    if(errResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = errResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }

                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);

        }
        void ShowPeerGroups(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            LBPeerGroups Req; LBPeerGroups Resp; LBAlgorithm lbalgo;
            ErrorDetails errResp;
            unsigned int NumPeers; 

            rsp->cmd_id = cmdID;
            string realmName = "";               
            string peergroupname = "";
            string peer_name = "";

            if(cliReq->Payload.peerGroupsPayload.peer_group.groupname[0] != INVALID_STR)
            {
                peergroupname = cliReq->Payload.peerGroupsPayload.peer_group.groupname;
                CLOG_DEBUG("peergroupname = %s to fetch",peergroupname.c_str());
            }

            LBPeerGroup* PGrp;
            if(cmdID == C_cli_show_erlbf_peer_group_Id || cmdID == C_cli_show_erlbf_peer_group_peers_Id)
            {
                PGrp = Req.add_peergroups();
                PGrp->set_lbpeergroupname(peergroupname);
            }

            if(m_cmapi->GetPeerGroup(Req, Resp, errResp) == CMAPI_SUCCESS)
            {
                unsigned int NumPGrps = Resp.peergroups_size();
                CLOG_INFO(" Num of PeerGroups = %d ",NumPGrps);
                if(NumPGrps != 0)
                {
                    char pcrf[20];
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "PeerGroup Table");
                    unsigned int nPGrp = 0;
                    if(cmdID == C_cli_show_erlbf_peer_group_Id || cmdID == C_cli_show_all_erlbf_peer_group_Id)
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",
                                FIELD_DELIMITER,"PeerGroup Name", 
                                FIELD_DELIMITER,"PeerGroup ID",
                                FIELD_DELIMITER,"LB-Algorithm", 
                                FIELD_DELIMITER,"Pcrf-binding", ROW_DELIMITER);
                        for (nPGrp = 0; nPGrp < NumPGrps; nPGrp++)
                        {   
                            LBPeerGroup PGrp = Resp.peergroups(nPGrp);
                            if(PGrp.has_lbpeergroupname())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", PGrp.lbpeergroupname().c_str(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            if(PGrp.has_lbpeergroupid())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%d%c", PGrp.lbpeergroupid(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            if((PGrp.lbalgo()).has_lbmethod())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", (PGrp.lbalgo()).lbmethod().c_str(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            if(PGrp.has_enablepcrfbinding())
                            {

                                if(PGrp.enablepcrfbinding() == 1)
                                    strcpy(pcrf,"enable");
                                else
                                    strcpy(pcrf,"disable");
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c", pcrf, ROW_DELIMITER);
                            }
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",ROW_DELIMITER);
                        }
                    }
                    else
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c", 
                                FIELD_DELIMITER,"Peer Name",
                                FIELD_DELIMITER,"Peer ID", 
                                FIELD_DELIMITER,"Peer Realm", 
                                FIELD_DELIMITER,"Peer Weight", 
                                FIELD_DELIMITER,"Peer Priority", ROW_DELIMITER);

                        LBPeerGroup PGrp = Resp.peergroups(nPGrp);
                        NumPeers = PGrp.lbpeers_size();
                        CLOG_INFO("Number of Peers under Peer-group = %d",NumPeers);
                        if(NumPeers) 
                        {
                            for (unsigned int nP = 0; nP < NumPeers; nP++)
                            {   
                                LBPeer Pr = PGrp.lbpeers(nP);
                                if(Pr.has_lbpeername())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c",  Pr.lbpeername().c_str(), FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                                if(Pr.has_lbpeerid())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%d%c",  Pr.lbpeerid(), FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                                if(Pr.has_lbpeerrealm())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%s%c",  Pr.lbpeerrealm().c_str(), FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                                if(Pr.has_lbpeerweight())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%d%c",  Pr.lbpeerweight(), FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);

                                if(Pr.has_lbpeername())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "%d%c",  Pr.lbpeerpriority(), ROW_DELIMITER);
                                else 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",ROW_DELIMITER);
                            } 
                        } 
                        else 
                        {
#if 0
                            rsp->ResponseCode = CMGR_FETCH_ERROR;
                            CLOG_ERROR("Error Fetching Peer Group Names ");
                            if(errResp.IsInitialized())
                            {
                                formErrorMessage(errResp,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
#endif
                            //if no peers are present in peer-group
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",FIELD_DELIMITER);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN, "NULL%c",ROW_DELIMITER);   
                        }  
                    }
                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching Peer Group Names ");
                    if(errResp.IsInitialized())
                    {
                        formErrorMessage(errResp,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                } 
            } else {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("Error Fetching Peer Group Names ");
                if(errResp.IsInitialized())
                {
                    formErrorMessage(errResp,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
        /****************************************************************************************
         *                           TRANSFORM FUNCTIONS                                        *
         ***************************************************************************************/



        void SetdictionaryConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {

            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;

            //std::cout << "\n OP recieved = " << cliReq->OP_CODE; 
            //std::cout << std::endl << "dictionary-name = " << cliReq->Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName;

            if(cliReq->OP_CODE == UNLOAD){
                //std::cout << "\n UNLOAD OP_CODE recieved.";
            }
            else {
                //std::cout << "\n LOAD OP_CODE recieved.";
            }

            string dictionaryname = "";

            if(cliReq->Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName != NULL)
            {
                dictionaryname = cliReq->Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName;
            }
            if(cliReq->OP_CODE == UNLOAD)
            {
                if(m_cmapi->UnLoadDictionary(dictionaryname) == CMAPI_SUCCESS)
                {
                    //cout << "Succesfully UnLoaded Dictionary" << endl;
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;         

                }
                else {
                    //cout << "Error UnLoading Dictionary" << endl;
                    rsp->ResponseCode = DRE_CONFIG_ERROR;                                     }
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }
            else if(cliReq->OP_CODE == LOAD)
            {
                if(m_cmapi->LoadDictionary(dictionaryname) == CMAPI_SUCCESS)
                {
                    //cout << "Succesfully Loaded Dictionary" << endl;
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;         

                }
                else {
                    //cout << "Error Loading Dictionary" << endl;
                    rsp->ResponseCode = DRE_CONFIG_ERROR;                           
                }
            }

            rsp->cmd_id = cmdID;
            SendResponseToMgmt2((void*)rsp, portnum);
        }


        void SettransformpluginConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {

            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;

            //std::cout << "\n OP recieved = " << cliReq->OP_CODE; 
            //std::cout << std::endl << "plugin-name = " << cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName;

            if(cliReq->OP_CODE == UNLOAD){
                //std::cout << "\n UNLOAD OP_CODE recieved.";
            }
            else {
                //std::cout << "\n LOAD OP_CODE recieved.";
            }

            string pluginName  = "";
            string dictionary1 = "";
            string dictionary2 = "";
            string configFile  = "";

            if(cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName != NULL)
            {
                pluginName = cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName;
            }

            if(cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.Dictionary1 != NULL)
            {
                dictionary1 = cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.Dictionary1;
            }
            if(cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.Dictionary2 != NULL)
            {
                dictionary2 = cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.Dictionary2;
            }
            if(cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.ConfigFileName != NULL)
            {
                configFile = cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.ConfigFileName;
            }

            if(cliReq->OP_CODE == UNLOAD)
            {
                if(m_cmapi->UnLoadTransformPlugin(pluginName)== CMAPI_SUCCESS)
                {
                    //cout << "Succesfully UnLoaded Plugin" << endl;
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;         

                }
                else {
                    //cout << "Error UnLoading Plugin" << endl;
                    rsp->ResponseCode = DRE_CONFIG_ERROR;                                     }
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }
            else if(cliReq->OP_CODE == LOAD)
            {
                if(m_cmapi->LoadTransformPlugin(pluginName, dictionary1, dictionary2, configFile) == CMAPI_SUCCESS)
                {
                    //cout << "Succesfully Loaded Plugin" << endl;
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;         

                }
                else {
                    //cout << "Error Loading Plugin" << endl;
                    rsp->ResponseCode = DRE_CONFIG_ERROR;                           
                }
            }

            rsp->cmd_id = cmdID;
            SendResponseToMgmt2((void*)rsp, portnum);

        }


        void ShowLoadedTransformPlugin(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            TransformPlugin plugin;
            DynDictionaryResponse *Resp = NULL;

            string pluginname = "";
            if(cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName != NULL)
            {
                pluginname = cliReq->Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName;  
            }
            if(cmdID == C_cli_show_loaded_transformplugin_Id)
            {
                if(m_cmapi->ShowTransformPlugin(pluginname,plugin)== CMAPI_SUCCESS)
                {
                    rsp->cmd_id = cmdID;
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Transform-Plugin Table");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",FIELD_DELIMITER,"Plugin Name", FIELD_DELIMITER,"Dictionary1", FIELD_DELIMITER,"Dictionary2", FIELD_DELIMITER,"configFileName",ROW_DELIMITER);
                    //cout << "Dictionary Name :   " << plugin.pluginname() << endl;
                    //cout << "Dictionary1 :" << plugin.fromdictionary() << endl;
                    //cout << "Dictionary2 :  " << plugin.todictionary() <<endl;
                    //cout << "configFileName :  " << plugin.configfilename() <<endl;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.pluginname().c_str(), FIELD_DELIMITER);
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.fromdictionary().c_str(), FIELD_DELIMITER);
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.todictionary().c_str(), FIELD_DELIMITER);
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.configfilename().c_str(),ROW_DELIMITER);
                }
                else {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    //cout << "Error Fetching Plugin Names " << endl;
                }
            }
            if(cmdID == C_cli_show_all_loaded_transformplugin_Id)
            {
                if(m_dtfcmapi->GetDTFConfiguration(Resp)== CMAPI_SUCCESS)
                {
                    rsp->cmd_id = cmdID;
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    unsigned int NumPlug = 0;
                    if(Resp != NULL)
                        NumPlug = Resp->plugins_size();

                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Transform-Plugin Table");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",FIELD_DELIMITER,"Plugin Name", FIELD_DELIMITER,"Dictionary1", FIELD_DELIMITER,"Dictionary2", FIELD_DELIMITER,"configFileName",ROW_DELIMITER);
                    //cout << "Plugin Name :   " << plugin.pluginname() << endl;
                    //cout << "Dictionary1  :  " << plugin.fromdictionary() << endl;
                    //cout << "Dictionary2 :  " << plugin.todictionary() <<endl;
                    //cout << "configFileName :  " << plugin.configfilename() <<endl;


                    for(unsigned int NumOfDict = 0; NumOfDict < NumPlug; NumOfDict++)
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.pluginname().c_str(), FIELD_DELIMITER);
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.fromdictionary().c_str(), FIELD_DELIMITER);
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.todictionary().c_str(), FIELD_DELIMITER);
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", plugin.configfilename().c_str(),ROW_DELIMITER);
                    }
                }
                else {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    //cout << "Error Fetching Dictionary Names " << endl;
                }
            }

            SendResponseToMgmt2((void*)rsp, portnum);
        }


        void ShowLoadedDictionary(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            //SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            Dictionary dictionary;
            DynDictionaryResponse Resp;
#if 0
            string dictionaryname = "";
            if(cliReq->Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName != NULL)
            {
                dictionaryname = cliReq->Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName;
                //std::cout << "dictionary-name = " << dictionaryname << std::endl << __LINE__<< std::endl;
            }
            if(cmdID == C_cli_show_loaded_dictionary_Id)
            {
                if(m_cmapi->ShowDictionary(dictionaryname,dictionary) == CMAPI_SUCCESS)
                {
                    rsp->cmd_id = cmdID;
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Dictionary Table");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",FIELD_DELIMITER,"Dictionary Name", FIELD_DELIMITER,"Dictionary ID", FIELD_DELIMITER,"Interface Name", FIELD_DELIMITER,"Release Number",ROW_DELIMITER);
                    cout << "Dictionary Name :   " << dictionary.dictionaryname() << endl;
                    cout << "Dictionary ID   :  " << dictionary.dictionaryid() << endl;
                    cout << "Interface Name :  " << dictionary.interfacename()<< endl;
                    cout << "Release No. :  " << dictionary.releasenum()<< endl;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", dictionary.dictionaryname().c_str(), FIELD_DELIMITER);
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c", dictionary.dictionaryid(), FIELD_DELIMITER);
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", dictionary.interfacename().c_str(), FIELD_DELIMITER);
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", dictionary.releasenum().c_str(),ROW_DELIMITER);
                }
                else {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    cout << "Error Fetching Dictionary Names " << endl;
                }
            }
#endif
            if(cmdID == C_cli_show_all_loaded_dictionary_Id || cmdID == C_cli_show_peerdictionary_Id)
            {
                if(m_dtfcmapi->GetDTFConfiguration(&Resp)== CMAPI_SUCCESS)
                {
                    rsp->cmd_id = cmdID;
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    unsigned int NumDict = Resp.dictionaries_size();
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Dictionary Table");
                    CLOG_INFO("Num of Dict's = %d",NumDict);
                    if(cmdID == C_cli_show_all_loaded_dictionary_Id)
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c",
                                FIELD_DELIMITER,"Dictionary Name", 
                                FIELD_DELIMITER,"Interface Name", 
                                FIELD_DELIMITER,"Release Number",ROW_DELIMITER);
                        for(unsigned int NumOfDict = 0; NumOfDict < NumDict; NumOfDict++)
                        {
                            dictionary = Resp.dictionaries(NumOfDict);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", dictionary.dictionaryname().c_str(), FIELD_DELIMITER);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", dictionary.interfacename().c_str(), FIELD_DELIMITER);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", dictionary.releasenum().c_str(),ROW_DELIMITER);
                        }
                    }
                    else
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,"Available Dictionary Names",ROW_DELIMITER);
                        for(unsigned int NumOfDict = 0; NumOfDict < NumDict; NumOfDict++)
                        {
                            dictionary = Resp.dictionaries(NumOfDict); 
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s", dictionary.dictionaryname().c_str());
                            if(NumOfDict < NumDict-1)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN," | ");
                        }
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                    }           
                }
                else {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching Dictionary Names ");
                }
            }
            rsp->cmd_id = cmdID;
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }


        void insertIntoMap(string peersKey, int peerId)
        {

            peerIdMap.insert(std::pair<string,int>(peersKey,peerId));
            std::map<string, int>::iterator ii;
#if 0
            for( ii=peerIdMap.begin(); ii!=peerIdMap.end(); ++ii)
            {
                //std::cout << endl<< (*ii).first << ": " << (*ii).second << endl;

            }
#endif
        }

        void GetPeerIds(int portnum,void* req,int len,int cmdID,int interfaceID) 
        {
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            //std::cout << "Going to get Peer-Ids ... " << __LINE__<< std::endl;
            DRECfgResp dreCfgResp;
            //if(cmdID == C_cli_show_loaded_dictionary_Id)

            if(m_dtfcmapi->GetDreConfiguration(&dreCfgResp) == CMAPI_SUCCESS)
            {
                //std::cout<<std::endl<<"Success  GetDreConfiguration from CMAPI." ;

                if (dreCfgResp.has_peers()) 
                {

                    PeersConfig *peers = dreCfgResp.mutable_peers();
                    int numPeers = peers->peers_size();
                    // Get each of the peer configuration from the peers
                    for (int i = 0; i < numPeers; i++)
                    {
                        string PeersKey = "";
                        string peerName = "";
                        string realmName = "";
                        int peerId = 0;

                        PeerConfig *peerConfig = peers->mutable_peers(i);
                        peerName = peerConfig->peerhostname().c_str();
                        realmName = peerConfig->realm().c_str();
                        peerId  = peerConfig->peerid();
                        PeersKey = peerName + realmName;
                        //std::cout <<std::endl<< "Peers Key = " << PeersKey;
                        insertIntoMap(PeersKey, peerId);

                    }
                }
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else {
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }



        /****************************************************************************************
         *                           TRANSFORM FUNCTIONS ENDS                                   *
         ***************************************************************************************/




        void SetDictionaryIds(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            PeersConfig PSC;
            PeerConfig *PC = PSC.add_peers();
            DRECfgResp cfgResp;
            string hostname = "";
            string realmname = "";
            int num_dict = 0;
            string dict_Id = "";

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            if(cliReq->Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.HostName[0] != INVALID_STR) 
            {
                hostname = cliReq->Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.HostName;
                CLOG_DEBUG("hostname = %s ",hostname.c_str());
            }

            if(cliReq->Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.RealmName[0] != INVALID_STR) 
            {
                realmname = cliReq->Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.RealmName;
                CLOG_DEBUG("realmname = %s ",realmname.c_str());
            }

            PC->set_peerhostname(hostname);
            PC->set_realm(realmname);
            if(cliReq->Payload.drePeerPayload.peerDictionaryInfo.num_dict != INVALID_NUM)
            {
                num_dict = cliReq->Payload.drePeerPayload.peerDictionaryInfo.num_dict;
                CLOG_DEBUG(" num_dict = %d ",num_dict);
            }
            for(int i = 0;i < num_dict;i++)
            {
                dict_Id = cliReq->Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[i];
                PC->add_dictionaryname(dict_Id);
                CLOG_DEBUG("dict_name : %s",dict_Id.c_str());
            }
            if(cliReq->OP_CODE == ADD)
            {
                if(m_prodcmapi->AddDictionaryID(PSC,&cfgResp)  == CMAPI_SUCCESS)
                {
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    CLOG_DEBUG("successfully added dictinary Id's");
                }
                else
                {
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    CLOG_ERROR("Error in adding dictionary Id's");
                    //Form Error Response Message
                    if(cfgResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = cfgResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }       
            }
            else if(cliReq->OP_CODE == DELETE)
            {
                if(m_prodcmapi->DeleteDictionaryID(PSC,&cfgResp) == CMAPI_SUCCESS)
                {
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    CLOG_DEBUG("successfully deleted dictinary Id's");
                }
                else
                {
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    CLOG_ERROR("Error in deleting dictionary Id's");
                    //Form Error Response Message
                    if(cfgResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = cfgResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }       
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }


        void SetErlbfPeerGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            LBPeerGroups Req;
            LBPeerGroup*pg = NULL;
            LBAlgorithm* lbalgo = NULL;
            LBPeerGroupResp errResp;

            unsigned short pcrfBinding =0;
            string lb_algo = "";               
            string peergroupname = "";
            string peer_name = "";

            if(cliReq->Payload.peerGroupsPayload.peer_group.groupname[0] != INVALID_STR)
            {
                peergroupname = cliReq->Payload.peerGroupsPayload.peer_group.groupname;
                CLOG_DEBUG("peergroupname = %s",peergroupname.c_str());
            }
            pg = Req.add_peergroups();
            pg->set_lbpeergroupname(peergroupname);

            if(cliReq->OP_CODE == DELETE) 
            {
                if (m_cmapi->DeletePeerGroup(peergroupname,&errResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully deleted the  Peer Group");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                } 
                else {
                    CLOG_ERROR("Error deleting  Peer Group ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(errResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = errResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
                CLOG_DEBUG(" < %s ",__FUNCTION__);
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }
            if(cliReq->Payload.peerGroupsPayload.peer_group.lb_algo[0] != INVALID_STR)
            {
                lbalgo = pg->mutable_lbalgo();
                lb_algo = cliReq->Payload.peerGroupsPayload.peer_group.lb_algo; 
                CLOG_DEBUG(" lb_algo = %s ",lb_algo.c_str());
                lbalgo->set_lbmethod(lb_algo);
            }
            if(cliReq->Payload.peerGroupsPayload.peer_group.pcrf_binding != INVALID_NUM)
            {      
                pcrfBinding = cliReq->Payload.peerGroupsPayload.peer_group.pcrf_binding;
                CLOG_DEBUG(" pcrfBinding = %d ",pcrfBinding);
                pg->set_enablepcrfbinding(pcrfBinding);
            }
            if (cliReq->OP_CODE == MODIFY) 
            {   
                if (m_cmapi->ModifyPeerGroup(Req,&errResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully Modified the  Peer Group");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                } 
                else {
                    CLOG_ERROR("Error Modfifying the  Peer Group ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;           
                    //Form Error Response Message
                    if(errResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = errResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
                CLOG_DEBUG(" < %s ",__FUNCTION__);
                SendResponseToMgmt2((void*)rsp, portnum);           
                return;
            }       
            else {
                if (m_cmapi->CreatePeerGroup(Req,&errResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG("Succesfully created Peer Group");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;         

                }
                else {
                    CLOG_ERROR("Error create Peer Group ");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;                           
                    //Form Error Response Message
                    if(errResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = errResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }
        void SetLocalHost(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            LocalHost lHost;
            DRECfgResp cfgResp;
            string HostName = "";
            string RealmName = "";
            string transportType = "";
            string serverIpAddr = "";
            int port = 0;
            int authlifetime = 0;
            int authgracetime = 0;
            int authtimeout = 0;
            int accinterim = 0;
            int acctimeout = 0;

            if(cliReq->Payload.dreLocalHostPayload.LocalHostKeyInfo.HostName[0] != INVALID_STR)
            {
                HostName = cliReq->Payload.dreLocalHostPayload.LocalHostKeyInfo.HostName;
                CLOG_DEBUG("HostName = %s",HostName.c_str());
            }           
            if(cliReq->Payload.dreLocalHostPayload.LocalHostKeyInfo.RealmName[0] != INVALID_STR)
            {
                RealmName = cliReq->Payload.dreLocalHostPayload.LocalHostKeyInfo.RealmName;
                CLOG_DEBUG("RealmName = %s",RealmName.c_str());
            }
            if(cliReq->OP_CODE == DELETE)
            {
                if(cmdID == C_cli_no_localhost_Id)
                {
                    if(m_prodcmapi->DeleteLocalHostConfig(HostName,RealmName,&cfgResp) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Deleted LocalHost Configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else
                    {
                        CLOG_ERROR("Error Deleting the LocalHost Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                    }
                }
                else
                {
                    ::LHTransport *lHostTransport = lHost.add_transports();
                    int transport_id = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.transport_id[0];
                    lHostTransport->set_transportslot(transport_id);
                    CLOG_DEBUG("transport_id = %d",transport_id);
                    if(cmdID == C_cli_deletetransport_Id)
                    {
                        if(m_prodcmapi->DeleteLocalHostTransport(HostName,RealmName,*lHostTransport) == CMAPI_SUCCESS)
                        {
                            CLOG_DEBUG("Succesfully Deleted LocalHostTransport Configuration");
                            rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                        }
                        else
                        {
                            CLOG_DEBUG("Error Deleting the LocalHostTransport Configuration ");
                            rsp->ResponseCode = DRE_CONFIG_ERROR;
                        }
                    }
                    else
                    {
                        lHost.set_localhostname(HostName);
                        lHost.set_realmname(RealmName); 
                        if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[0][0][0] != INVALID_STR)
                        {
                            serverIpAddr = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[0][0];
                            lHostTransport->add_secondaryipaddr(serverIpAddr);
                            CLOG_DEBUG("Secondary-ip to be deleted = %s",serverIpAddr.c_str());
                        }
                        if(m_prodcmapi->DeleteSecIPFromLocalHost(lHost) == CMAPI_SUCCESS)
                        {
                            CLOG_DEBUG("Succesfully Deleted Secondary-ip from LocalHostTransport.");
                            rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                        }
                        else
                        {
                            CLOG_DEBUG("Error Deleting the Secondary-ip from LocalHostTransport");
                            rsp->ResponseCode = DRE_CONFIG_ERROR;
                        }

                    }
                }
                if(rsp->ResponseCode == DRE_CONFIG_ERROR)
                {
                    ErrorDetails err;
                    m_prodcmapi->GetLastCallErrorDetails(err);
                    //Form Error Response Message
                    if(err.IsInitialized())
                    {
                        formErrorMessage(err,rsp);
                        CLOG_DEBUG("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        err.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(err,rsp);
                        CLOG_DEBUG("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else {
                lHost.set_localhostname(HostName);
                lHost.set_realmname(RealmName); 
                if(cliReq->Payload.dreLocalHostPayload.LocalHostAuthInfo.LifeTime != INVALID_NUM)
                {
                    authlifetime = cliReq->Payload.dreLocalHostPayload.LocalHostAuthInfo.LifeTime;
                    CLOG_DEBUG("authlifetime = %d",authlifetime);
                    lHost.set_authsessionlifetime(authlifetime);
                }
                if(cliReq->Payload.dreLocalHostPayload.LocalHostAuthInfo.GraceTime != INVALID_NUM)
                {
                    authgracetime = cliReq->Payload.dreLocalHostPayload.LocalHostAuthInfo.GraceTime;
                    CLOG_DEBUG("authgracetime = %d",authgracetime);
                    lHost.set_authsessiongraceperiod(authgracetime);
                }
                if(cliReq->Payload.dreLocalHostPayload.LocalHostAuthInfo.TimeOut != INVALID_NUM)
                {
                    authtimeout = cliReq->Payload.dreLocalHostPayload.LocalHostAuthInfo.TimeOut;
                    CLOG_DEBUG("authtimeout = %d",authtimeout);
                    lHost.set_authsessiontimeout(authtimeout);
                }
                if(cliReq->Payload.dreLocalHostPayload.LocalHostAcctInfo.Interim != INVALID_NUM)
                {
                    accinterim = cliReq->Payload.dreLocalHostPayload.LocalHostAcctInfo.Interim;
                    CLOG_DEBUG("accinterim = %d",accinterim);
                    lHost.set_acctsessioninteriminterval(accinterim);
                }
                if(cliReq->Payload.dreLocalHostPayload.LocalHostAcctInfo.TimeOut != INVALID_NUM)
                {
                    acctimeout = cliReq->Payload.dreLocalHostPayload.LocalHostAcctInfo.TimeOut;
                    CLOG_DEBUG("acctimeout = %d",acctimeout);
                    lHost.set_acctsessiontimeout(acctimeout);
                }
                if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.transport_count != INVALID_NUM)
                {
                    for(int i = 0;i < MAX_LOCALTRANSPORT_ATTRIBUTES;i++)
                    {
                        if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[i] != INVALID_NUM)
                        {
                            ::LHTransport *lHostTransport = lHost.add_transports();
                            lHostTransport->set_transportslot(i+1);
                            CLOG_DEBUG("transport_id = %d",i+1);
                            
                            if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[i] != INVALID_NUM)
                            {
                                port = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[i];
                                lHostTransport->set_port(port);
                                CLOG_DEBUG("port = %d",port);
                            }
                            if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.secureportno[i] != INVALID_NUM)
                            {
                                port = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.secureportno[i];
                                lHostTransport->set_secureport(port);
                                CLOG_DEBUG("secureport = %d",port);
                            }

                            serverIpAddr = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.IpAddr[i];
                            lHostTransport->set_hostipaddr(serverIpAddr);
                            CLOG_DEBUG("serverIpAddr = %s",serverIpAddr.c_str());

                            if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.PublicIpAddr[i][0] != INVALID_STR)
                            {
                                serverIpAddr = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.PublicIpAddr[i];
                                lHostTransport->set_publicserveripaddr(serverIpAddr);
                                CLOG_DEBUG("publicserverIpAddr = %s",serverIpAddr.c_str());
                            }

                            if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[i] == TRANSTYPE_TCP)
                                transportType = "TCP";
                            else    
                            {
                                transportType = "SCTP";
                                for(int j = 0;j < MAX_LOCALTRANSPORT_ATTRIBUTES;j++)
                                {
                                    if(cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[i][j][0] != INVALID_STR)
                                    {
                                        serverIpAddr = cliReq->Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[i][j];
                                        CLOG_DEBUG("secondary_ip's = %s",serverIpAddr.c_str());
                                        lHostTransport->add_secondaryipaddr(serverIpAddr);
                                    }
                                }
                            }
                            CLOG_DEBUG("transportType = %s",transportType.c_str());
                            lHostTransport->set_transporttype(transportType);
                        }
                    }
                }
                if(cliReq->OP_CODE == MODIFY)
                {

                    if(m_prodcmapi->ModifyLocalHostConfig(lHost) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Modified the LoclaHost Configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else {
                        ErrorDetails Resp;
                        m_prodcmapi->GetLastCallErrorDetails(Resp);
                        CLOG_ERROR("Error Modfifying the LocalHost Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        if(Resp.IsInitialized())
                        {
                            formErrorMessage(Resp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            Resp.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(Resp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }

                }
                else
                {
                    if(m_prodcmapi->SetLocalHostConfig(lHost) == CMAPI_SUCCESS)
                    {
                        CLOG_DEBUG("Succesfully Added the LocalHost Configuration");
                        rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    }
                    else {
                        ErrorDetails Resp;
                        m_prodcmapi->GetLastCallErrorDetails(Resp);
                        CLOG_ERROR("Error Adding the LocalHost Configuration ");
                        rsp->ResponseCode = DRE_CONFIG_ERROR;
                        //Form Error Response Message
                        if(Resp.IsInitialized())
                        {
                            formErrorMessage(Resp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            Resp.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(Resp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }

                }
            }
            rsp->cmd_id = cmdID;
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void setLogging(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            memset(rsp,0,sizeof(AllResponses));
            rsp->cmd_id = cmdID;
            LoggerInfo logInfo;
            LoggerConf_LogLevel loglevel;
            LoggerConf_LogChannel logChannel;
            LoggerConfResp loggerResp;

            if(cliReq->OP_CODE == DELETE){
                CLOG_DEBUG(" DEL OP_CODE recieved.");
            }
            else if (cliReq->OP_CODE == MODIFY){
                CLOG_DEBUG(" MOD OP_CODE recieved.");
            }
            else {
                CLOG_DEBUG(" add OP_CODE recieved.");
            }

            string componentName = "";

            if(cliReq->Payload.loggingPayload.compName[0] != INVALID_STR)
            {
                componentName = cliReq->Payload.loggingPayload.compName;
                CLOG_DEBUG("componentName = %s ",componentName.c_str());
            }

            if(cmdID == C_cli_set_log_level_Id || cmdID == C_cli_setall_log_level_Id) {
                if(cliReq->Payload.loggingPayload.logLevel != NULL)
                {
                    if(strcmp(cliReq->Payload.loggingPayload.logLevel, "DEBUG") == 0)
                    {
                        loglevel =LoggerConf_LogLevel_DEBUG_LOG;
                        CLOG_DEBUG(" loglevel = DEBUG ");
                    }
                    else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "INFO") == 0)
                    {
                        loglevel =LoggerConf_LogLevel_INFO_LOG;
                        CLOG_DEBUG(" loglevel = INFO ");
                    }
                    else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "NOTICE") == 0)
                    {
                        loglevel =LoggerConf_LogLevel_NOTICE_LOG;
                        CLOG_DEBUG(" loglevel = NOTICE ");
                    }
                    else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "WARNING") == 0)
                    {
                        loglevel =LoggerConf_LogLevel_WARNING_LOG;
                        CLOG_DEBUG(" loglevel = WARNING ");
                    }
                    else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "CRITICAL") == 0)
                    {
                        loglevel =LoggerConf_LogLevel_CRITICAL_LOG;
                        CLOG_DEBUG(" loglevel = CRITICAL ");
                    }            
                    else
                    {
                        loglevel =LoggerConf_LogLevel_ERROR_LOG;
                        CLOG_DEBUG(" loglevel = ERROR ");
                    }
                }
            }
            else {
                if(cliReq->Payload.loggingPayload.logChannel[0] != INVALID_STR)
                {
                    if(strcmp(cliReq->Payload.loggingPayload.logChannel, "syslog") == 0)
                    {
                        logChannel =LoggerConf_LogChannel_SYSLOG;
                        CLOG_DEBUG(" logChannel = syslog ");
                    }
                    else if(strcmp(cliReq->Payload.loggingPayload.logChannel, "file") == 0)
                    {
                        logChannel =LoggerConf_LogChannel_FILENAME;
                        CLOG_DEBUG(" logChannel = file ");
                    }        
                    else if(strcmp(cliReq->Payload.loggingPayload.logChannel, "console") == 0)
                    {
                        logChannel =LoggerConf_LogChannel_CONSOLE;
                        CLOG_DEBUG(" logChannel = console ");
                    }
                    else {
                        logChannel =LoggerConf_LogChannel_SYSLOG;
                        CLOG_DEBUG(" logChannel = syslog ");
                    }
                }
            }

            if(cmdID == C_cli_set_log_level_Id || cmdID == C_cli_setall_log_level_Id)
            {
                LoggerConf *logger = logInfo.add_loggerconfig();
                logger->set_componentname(componentName);
                logger->set_level(loglevel);
                if(m_cmapi->SetLogLevel(componentName, loglevel, &loggerResp)== CMAPI_SUCCESS)
                {
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                    if(componentName == "CLI")
                    {
                        if(strcmp(cliReq->Payload.loggingPayload.logLevel, "DEBUG") == 0)
                            this->GetLogger().SetLevel(Logger::EACC_LOG_DEBUG,true);
                        else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "INFO") == 0)
                            this->GetLogger().SetLevel(Logger::EACC_LOG_INFO,true);
                        else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "NOTICE") == 0)
                            this->GetLogger().SetLevel(Logger::EACC_LOG_NOTICE,true);
                        else if(strcmp(cliReq->Payload.loggingPayload.logLevel, "WARNING") == 0)
                            this->GetLogger().SetLevel(Logger::EACC_LOG_WARNING,true);
                        else if(strcmp(cliReq->Payload.loggingPayload.logLevel,"CRITICAL") == 0)
                            this->GetLogger().SetLevel(Logger::EACC_LOG_CRITICAL,true);
                        else
                            this->GetLogger().SetLevel(Logger::EACC_LOG_ERROR,true);
                    }
                    CLOG_DEBUG(" Succesfully set the %s components logging.",componentName.c_str());
                    sprintf(rsp->payload + strlen(rsp->payload),"Successfully set Log-Level for %s",componentName.c_str());
                }
                else
                {
                    CLOG_ERROR("Error in setting Loggin configuration for %s component.",componentName.c_str());
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(loggerResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = loggerResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        if(cmdID == C_cli_setall_log_level_Id)
                            sprintf(rsp->payload + strlen(rsp->payload)," Failed to set Log-Level for %s",componentName.c_str());
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        if(cmdID == C_cli_setall_log_level_Id)
                            sprintf(rsp->payload + strlen(rsp->payload)," Failed to set Log-Level for %s",componentName.c_str());
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else {
                if (m_cmapi->SetLogChannel(componentName, logChannel, &loggerResp) == CMAPI_SUCCESS)
                {
                    CLOG_DEBUG(" Successfully Set Log Channel ");
                    rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }
                else {
                    CLOG_ERROR("Error in Setting the Log Channel");
                    rsp->ResponseCode = DRE_CONFIG_ERROR;
                    //Form Error Response Message
                    if(loggerResp.errordetails_size() == 1)
                    {
                        ErrorDetails det = loggerResp.errordetails(0);
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }

            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);           
            return;
        }

        void showLoggingConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            SetConfigReq *cliReq = (SetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            LoggerInfo logInfo;
            string componentName = "";
            int logLevel=0;
            int logChannel =0;
            ErrorDetails errResp;
            // not setting componentName if user wants to see logging info for all the components 
            if(cliReq->Payload.loggingPayload.compName[0] != INVALID_STR &&
                    strcmp(cliReq->Payload.loggingPayload.compName,"all"))
            {
                componentName = cliReq->Payload.loggingPayload.compName;
                CLOG_DEBUG("componentName = %s ",componentName.c_str());
            }

            if(m_cmapi->GetLogConfig(componentName, logInfo, errResp) == CMAPI_SUCCESS)
            {
                int numOfCmp = logInfo.loggerconfig_size();
                CLOG_INFO("num Of Components = %d ",numOfCmp);
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                if(numOfCmp != 0)
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, " Logging Table");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"Component Name", 
                            FIELD_DELIMITER,"Log Level", 
                            FIELD_DELIMITER,"Log Channel",ROW_DELIMITER);

                    for(int curCmp = 0 ; curCmp < numOfCmp ; curCmp++)
                    {
                        LoggerConf curLogConfig = logInfo.loggerconfig(curCmp);
                        logLevel = curLogConfig.level();
                        logChannel =curLogConfig.channel();
                        componentName = curLogConfig.componentname();
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c", componentName.c_str(), FIELD_DELIMITER);
                        if(logLevel == LoggerConf_LogLevel_DEBUG_LOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"DEBUG%c", FIELD_DELIMITER);
                        }
                        else if(logLevel == LoggerConf_LogLevel_INFO_LOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"INFO%c", FIELD_DELIMITER);
                        }
                        else if(logLevel == LoggerConf_LogLevel_ERROR_LOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"ERROR%c", FIELD_DELIMITER);
                        }
                        else if(logLevel == LoggerConf_LogLevel_NOTICE_LOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NOTICE%c", FIELD_DELIMITER);
                        }
                        else if(logLevel == LoggerConf_LogLevel_WARNING_LOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"WARNING%c", FIELD_DELIMITER);
                        }
                        else if(logLevel == LoggerConf_LogLevel_CRITICAL_LOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"CRITICAL%c", FIELD_DELIMITER);
                        }

                        if(logChannel == LoggerConf_LogChannel_SYSLOG)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"syslog%c", ROW_DELIMITER);
                        }
                        else if(logChannel == LoggerConf_LogChannel_FILENAME)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"file%c", ROW_DELIMITER);
                        }
                        else{
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"console%c", ROW_DELIMITER);
                        }
                    }
                }
                else 
                {
                    CLOG_ERROR("Error in fetching the Logging Configurations ");
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    if(errResp.IsInitialized())
                    {
                        formErrorMessage(errResp,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else {
                CLOG_ERROR("Error in fetching the Logging Configurations ");
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                if(errResp.IsInitialized())
                {
                    formErrorMessage(errResp,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        /***************************** AVAILABILITY  MANAGER SETTING FUNCTIONS ******************************/

        void SetConfigPingPeriodicity(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigPingPeriodicityReq *cliReq = (AvaMgrConfigPingPeriodicityReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;


            int PingPeriodicity = 0;

            if(cliReq->uiConfigPingPeriodicity != NULL)
            {
                PingPeriodicity = cliReq->uiConfigPingPeriodicity;
            }

            if (m_hacmapi->SetAMPeerPingPeriodicity(PingPeriodicity) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully Ping Periodicity is set" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting Ping Periodicity " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }


        void SetConfigPingPeriodicityArbitrator(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigPingPeriodicityForArbitratorReq *cliReq = (AvaMgrConfigPingPeriodicityForArbitratorReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;


            int PingPeriodicity = 0;
            if(cliReq->uiConfigPingPeriodicityForArbitrator != NULL)
                PingPeriodicity = cliReq->uiConfigPingPeriodicityForArbitrator;

            if (m_hacmapi->SetAMArbitratorPingPeriodicity(PingPeriodicity) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully Ping Periodicity Arbitrator is set" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting Ping Periodicity Arbitrator" << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetConfigPeerPingAckReceiveFailures(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeerReq *cliReq = (AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeerReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;


            int Failures = 0;
            if(cliReq->uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer != NULL)
                Failures = cliReq->uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer;

            if (m_hacmapi->SetAMMaximumPingACKReceiveFailures(Failures) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully set number of ping ack receive failures" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting number of ping ack receive failures " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetConfigArbitratorPingAckReceiveFailures(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitratorReq *cliReq = (AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitratorReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;


            int Failures = 0;
            if(cliReq->uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator != NULL)
                Failures = cliReq->uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator;

            if (m_hacmapi->SetAMMaximumArbPingACKReceiveFailures(Failures) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully set number of ping Arbitrator ack receive failures" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting set number of ping Arbitrator ack receive failures" << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }


        void SetConfigProcessRestartMaxInterval(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigProcessRestartMaximumAllowedIntervalReq *cliReq = (AvaMgrConfigProcessRestartMaximumAllowedIntervalReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;


            int Interval = 0;
            if(cliReq->uiConfigProcessRestartMaximumAllowedInterval != NULL)
                Interval = cliReq->uiConfigProcessRestartMaximumAllowedInterval;

            if (m_hacmapi->SetAMProcessRestartMAXAllowedInterval(Interval) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully set process restart maximum interval" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting process restart maximum interval " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetConfigProcessRestartMaxCount(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigProcessRestartMaximumAllowedCountReq *cliReq = (AvaMgrConfigProcessRestartMaximumAllowedCountReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;


            int Count = 0;
            if(cliReq->uiConfigProcessRestartMaximumAllowedCount != NULL)
                Count = cliReq->uiConfigProcessRestartMaximumAllowedCount;

            if (m_hacmapi->SetAMProcessRestartMaxAllowedCount(Count) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully set process restart maximum Count" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting process restart maximum Count " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetConfigGatewayIP(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigGatewayIpAddressReq *cliReq = (AvaMgrConfigGatewayIpAddressReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;

            char ipaddress[64];
            if(cliReq->cConfigGatewayIpAddress != NULL)
                strcpy(ipaddress,cliReq->cConfigGatewayIpAddress);
            if (m_hacmapi->SetAMArbitratorIpAddress(ipaddress) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully set Gateway Ip address" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting Gateway Ip address " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetPrimaryVirtualIpAddress(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            AvaMgrConfigPrimaryVirtualIpAddressReq *cliReq = (AvaMgrConfigPrimaryVirtualIpAddressReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;
            //cout << "IN SetPrimaryVirtualIpAddress functin" << endl;
            char ipaddress[MAX_PARAM_SIZE];
            char dev[MAX_RECORD_SIZE];
            if(cliReq->cConfigPrimaryVirtualIpAddress != NULL)
                strcpy(ipaddress,cliReq->cConfigPrimaryVirtualIpAddress);
            //cout<< "ipaddress" << ipaddress <<endl;

            if(cliReq->cConfigDev != NULL)
                strcpy(dev,cliReq->cConfigDev);
            //cout<< "dev" << dev <<endl;

            if (m_hacmapi->SetAMVirtualAddressInfo(ipaddress,dev) == CMAPI_SUCCESS)
            {
                //cout << "Succesfully set Virtual Ip address" << endl;
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
            }
            else
            {
                //cout << "Error setting virtual Ip address " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
            }
            SendResponseToMgmt2((void*)rsp, portnum);

        }

        void SetConfigAvaMgrLogchannel(int portnum,void* req,int len,int cmdID,int interfaceID)
        {           
            AvaMgrConfigSetLogChannelReq *cliReq =(AvaMgrConfigSetLogChannelReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;  
            rsp->cmd_id = cmdID;

            char componentId[64];
            char logchannel[64];
            char filename[MAX_NAME_LEN];
            if(cliReq->componentId != NULL)
                strcpy(componentId,cliReq->componentId);
            if(cliReq->log_channel !=NULL)
                strcpy(logchannel,cliReq->log_channel);
            if(cliReq->logFileName != NULL)
                strcpy(filename,cliReq->logFileName);
            /*  if (m_hacmapi->SetAMArbitratorIpAddress(ipaddress) == CMAPI_SUCCESS)                      
                {
                cout << "Succesfully Log channel is set" << endl;                             
                rsp->ResponseCode = DRE_CONFIG_SUCCESS;
                }       
                else    
                {
                cout << "Error setting Log channel " << endl;                              
                rsp->ResponseCode = DRE_CONFIG_ERROR;                                             
                }       
                SendResponseToMgmt2((void*)rsp, portnum);                                         
                */              
        }          

        void SetConfigAvaMgrLogLevel(int portnum,void* req,int len,int cmdID,int interfaceID)                 
        {
            AvaMgrConfigSetLogLevelReq *cliReq =(AvaMgrConfigSetLogLevelReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            rsp->cmd_id = cmdID; 

            char componentId[64];
            char loglevel[64];
            char logstatus[64];
            if(cliReq->componentId != NULL)
                strcpy(componentId,cliReq->componentId);

            if(cliReq->uiConfigSetLogLevelReq != NULL)
                strcpy(loglevel,cliReq->uiConfigSetLogLevelReq);

            if(cliReq->log_status != NULL)
                strcpy(logstatus,cliReq->log_status);
            /*  if (m_hacmapi->SetAMArbitratorIpAddress(ipaddress) == CMAPI_SUCCESS)
                {
                cout << "Succesfully Log Level is set" << endl;                                                
                rsp->ResponseCode = DRE_CONFIG_SUCCESS; 
                }
                else
                {
                cout << "Error setting Log Level " << endl;
                rsp->ResponseCode = DRE_CONFIG_ERROR;
                }
                SendResponseToMgmt2((void*)rsp, portnum);
                */
        }   


        /*************************************AVALAIBILITY MANAGER ENDS*******************************/

        void ShowGeneralConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            rsp->cmd_id = cmdID;

            if(cmdID == C_cli_showsctpconfig_Id)
            {
                SctpProtocol sctpconfig;
                if(m_prodcmapi->GetSctpProtocolConfiguration(sctpconfig) == CMAPI_SUCCESS)
                {
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   SCTP Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"HeartBeatEnable",
                            FIELD_DELIMITER,"HearBeatTimeOut",
                            FIELD_DELIMITER,"InitialTimeOut",
                            FIELD_DELIMITER,"MaximumAttempts",
                            FIELD_DELIMITER,"RTOMaximum",
                            FIELD_DELIMITER,"RTOMinimum",
                            FIELD_DELIMITER,"RTOInitial",
                            FIELD_DELIMITER,"PathFailRetryCount",ROW_DELIMITER);

                    if(sctpconfig.has_heartbeatenable())
                    {
                        if(sctpconfig.heartbeatenable()==0)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sctpconfig.has_hearbeattimeout())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.hearbeattimeout(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER); 

                    if(sctpconfig.has_initialtimeout())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.initialtimeout(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sctpconfig.has_maximumattempts())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.maximumattempts(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sctpconfig.has_rtomaximum())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.rtomaximum(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sctpconfig.has_rtominimum())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.rtominimum(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sctpconfig.has_rtoinitial())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.rtoinitial(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sctpconfig.has_pathfailretrycount())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig.pathfailretrycount(),ROW_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching SCTP configuration Information ");
                }
            }
            else if(cmdID == C_cli_showtlsconfig_Id)
            {   
                TLSConfig tlsconfig;
                if(m_prodcmapi->GetTLSConfiguration(tlsconfig) == CMAPI_SUCCESS)
                {
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   TLS Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                            FIELD_DELIMITER,"Identity-Verification",
                            FIELD_DELIMITER,"CRL-verification",ROW_DELIMITER);

                    if(tlsconfig.has_enableidverification())
                    {
                        if(tlsconfig.enableidverification() == 0)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(tlsconfig.has_enablecrlverification())
                    {
                        if(tlsconfig.enablecrlverification() == 0)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",ROW_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",ROW_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching TLS configuration Information ");
                }
            }
            else if(cmdID == C_cli_showtrustedcaconfig_Id)
            {
                CACRLs cacrls;
                if(m_prodcmapi->GetCACRLConfiguration(cacrls) == CMAPI_SUCCESS)
                {
                    unsigned int Numofcrl = cacrls.tcacfg_size();
                    CLOG_INFO("Num of Trusted-CA Config = %d",Numofcrl);
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Trusted CA Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                            FIELD_DELIMITER,"CA-file",
                            FIELD_DELIMITER,"CRL-file",ROW_DELIMITER);

                    for(unsigned int crl = 0; crl < Numofcrl; crl++)
                    {    
                        TrustedCAConfiguration trustedca = cacrls.tcacfg(crl);
                        if(trustedca.has_cafile())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",trustedca.cafile().c_str(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                        if(trustedca.has_crlfile())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",trustedca.crlfile().c_str(),ROW_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                    }
                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching Trusted CA configuration Information ");
                }
            }
            else if(cmdID == C_cli_showciphersuiteconfig_Id || cmdID == C_cli_show_ciphersuites_Id)
            {
                TLSCipherConfigs tlscipher;
                if(m_prodcmapi->GetTlsCipherCfg(tlscipher) == CMAPI_SUCCESS)
                {
                    unsigned int NumofTls = tlscipher.tlsciphers_size();
                    CLOG_INFO("Num of TLS Cipher Suite Config = %d",NumofTls);
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "TLS Cipher-Suite Config");
                    if(cmdID == C_cli_showciphersuiteconfig_Id)
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                                FIELD_DELIMITER,"Cipher-Suite",
                                FIELD_DELIMITER,"Cipher-Suite-State",ROW_DELIMITER);
                        for(unsigned int tls = 0 ; tls < NumofTls; tls++)
                        {
                            TLSCipherConfig cipher = tlscipher.tlsciphers(tls);
                            if(cipher.has_ciphersuitename())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",cipher.ciphersuitename().c_str(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                            if(cipher.has_enableciphersuite())
                            {
                                if(cipher.enableciphersuite() == 0)
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",ROW_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",ROW_DELIMITER);
                            }
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                        }
                    }
                    else
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",
                                FIELD_DELIMITER,"Available-Cipher-Suites",ROW_DELIMITER);
                        for(unsigned int tls = 0 ; tls < NumofTls; tls++)
                        {
                            TLSCipherConfig cipher = tlscipher.tlsciphers(tls);
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",cipher.ciphersuitename().c_str());
                            if(tls < NumofTls-1)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                        }
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                    }
                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching TLS Cipher-Suite configuration");
                }
            }
            else
            {
                GeneralConfig generalconfig;
                if(m_prodcmapi->GetGeneralConfiguration(generalconfig) == CMAPI_SUCCESS)
                {
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   General Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"EnablePeerIPCheck",
                            FIELD_DELIMITER,"PredictiveLoopdetection",
                            FIELD_DELIMITER,"SNaptrSupport",
                            ROW_DELIMITER);

                    if(generalconfig.has_enablepeeripcheck())
                    {
                        if(generalconfig.enablepeeripcheck() == 0)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                    
                    if(generalconfig.has_ispredictiveloopavdrequired())
                    {
                        if(generalconfig.ispredictiveloopavdrequired() == 0)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                    
                    if(generalconfig.has_issnaptrsupported())
                    {
                        if(generalconfig.issnaptrsupported() == 0)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",ROW_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",ROW_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }
                else 
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching General configuration");
                }
            }

            if(rsp->ResponseCode == CMGR_FETCH_ERROR)
            {
                ErrorDetails err;
                m_prodcmapi->GetLastCallErrorDetails(err);
                //Form Error Response Message
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    err.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }

            }
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }

        void ShowPeerConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            GetConfigReq *clireq=(GetConfigReq *)req;
            ErrorDetails err;

            if(cmdID == C_cli_showpeer_Id || cmdID == C_cli_show_dictionary_Id || cmdID == C_cli_showpeerconfig_Id)
            {
                string realmname = "";
                string hostname = "";
                PeerConfig Peer;

                if(clireq->shReqPayload.dreKeyInfo.peerKeyInfo.HostName[0] != INVALID_STR)
                {
                    hostname = clireq->shReqPayload.dreKeyInfo.peerKeyInfo.HostName;
                    CLOG_DEBUG("hostname = %s",hostname.c_str());
                }
                if(clireq->shReqPayload.dreKeyInfo.peerKeyInfo.RealmName[0] != INVALID_STR)
                {
                    realmname = clireq->shReqPayload.dreKeyInfo.peerKeyInfo.RealmName;
                    CLOG_DEBUG("realmname = %s",realmname.c_str());
                }
                if(cmdID == C_cli_showpeer_Id || cmdID == C_cli_showpeerconfig_Id) 
                {
                    if(m_prodcmapi->GetPeerConfig(hostname,realmname,Peer,err) == CMAPI_SUCCESS)
                    {
                        PeerConfig *PC = &Peer;
                        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                        if(PC->has_peerhostname()) 
                        {
                            if(cmdID == C_cli_showpeer_Id)
                            {
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Peer Table");
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",FIELD_DELIMITER,"PeerStatus",FIELD_DELIMITER,"PeerState",ROW_DELIMITER);
                                if(PC->has_peerstatus())
                                {
                                    if(PC->peerstatus() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_peerstate())
                                {
                                    if(PC->peerstate() == PEER_CLOSED)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSED%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_I_CEA)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_I_CEA%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK_ELECT)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK_ELECT%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_RETURNS)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_RETURNS%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_I_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_I_OPEN%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_R_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_R_OPEN%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_CLOSING)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSING%c",ROW_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                            }
                            else
                            {
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Peer Table");
#if DRE
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                                        FIELD_DELIMITER,"PeerName", 
                                        FIELD_DELIMITER,"RealmName", 
                                        FIELD_DELIMITER,"IP(or)Fqdn",
                                        FIELD_DELIMITER,"Port",
                                        FIELD_DELIMITER,"SecurePort",
                                        FIELD_DELIMITER,"TransportType",
                                        FIELD_DELIMITER,"Secondary-ip's",
                                        FIELD_DELIMITER,"TLSEnabled",
                                        FIELD_DELIMITER,"IsDPRDisconnCauseSupport",
                                        FIELD_DELIMITER,"FailOverEnable",
                                        FIELD_DELIMITER,"FailBackEnable",
                                        FIELD_DELIMITER,"Alternate-peer",
                                        FIELD_DELIMITER,"IsMate",
                                        FIELD_DELIMITER,"TcTimerVal",
                                        FIELD_DELIMITER,"WatchDogTimer",
                                        FIELD_DELIMITER,"ExpiryTimer",
                                        FIELD_DELIMITER,"BusyReconnectTimer",
                                        FIELD_DELIMITER,"DoNotwantToTalkToYouTimer",
                                        FIELD_DELIMITER,"PeerStatus",
                                        FIELD_DELIMITER,"PeerState",
                                        FIELD_DELIMITER,"Dictionary-names",ROW_DELIMITER);
#else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                                        FIELD_DELIMITER,"PeerName", 
                                        FIELD_DELIMITER,"RealmName", 
                                        FIELD_DELIMITER,"IP(or)Fqdn",
                                        FIELD_DELIMITER,"Port",
                                        FIELD_DELIMITER,"TransportType",
                                        FIELD_DELIMITER,"Secondary-ip's",
                                        FIELD_DELIMITER,"FailOverEnable",
                                        FIELD_DELIMITER,"FailBackEnable",
                                        FIELD_DELIMITER,"Alternate-peer",
                                        FIELD_DELIMITER,"IsMate",
                                        FIELD_DELIMITER,"TcTimerVal",
                                        FIELD_DELIMITER,"WatchDogTimer",
                                        FIELD_DELIMITER,"ExpiryTimer",
                                        FIELD_DELIMITER,"BusyReconnectTimer",
                                        FIELD_DELIMITER,"DoNotwantToTalkToYouTimer",
                                        FIELD_DELIMITER,"PeerStatus",
                                        FIELD_DELIMITER,"PeerState",
                                        FIELD_DELIMITER,"Dictionary-names",ROW_DELIMITER);
#endif
                                if(PC->has_peerhostname())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->peerhostname().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_realm()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->realm().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_serveripaddr())  
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->serveripaddr().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_port())  
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->port(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if DRE
                                if(PC->has_secureport())  
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->secureport(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                                if(PC->has_transporttype()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->transporttype().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                int Ipcount = PC->secondaryipaddr_size();
                                CLOG_DEBUG("Ipcount = %d",Ipcount);
                                if(Ipcount !=0)
                                {
                                    for(int j=0; j<Ipcount;j++)
                                    {
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",PC->secondaryipaddr(j).c_str());
                                        if(j < Ipcount -1)
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,",");
                                    }
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",FIELD_DELIMITER);
                                }
                                else 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if DRE
                                if(PC->has_tlsenabled())
                                {   
                                    if(PC->tlsenabled() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_issupportdisconnectcause())
                                {   
                                    if(PC->issupportdisconnectcause() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                                if(PC->has_failoverenable())
                                {
                                    if(PC->failoverenable() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }   
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_failebackenable())
                                {
                                    if(PC->failebackenable() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_altpeername())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->altpeername().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_ismate())
                                {           
                                    if(PC->ismate() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_tctimerval())    
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->tctimerval(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_watchdogtimer()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->watchdogtimer(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_expirytimer())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->expirytimer(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_busyreconnecttimerval())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->busyreconnecttimerval(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_donotwanttotalktoyoutimerval())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->donotwanttotalktoyoutimerval(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_peerstatus())
                                {
                                    if(PC->peerstatus() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_peerstate())
                                {
                                    if(PC->peerstate() == PEER_CLOSED)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSED%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_I_CEA)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_I_CEA%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK_ELECT)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK_ELECT%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_RETURNS)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_RETURNS%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_I_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_I_OPEN%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_R_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_R_OPEN%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_CLOSING)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSING%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                int nDictionaryID = PC->dictionaryname_size();
                                CLOG_DEBUG("num of Dictionaries = %d",nDictionaryID);
                                if(nDictionaryID == 0)
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s ","NULL");
                                }
                                for(int j=0;j<nDictionaryID;j++)
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",PC->dictionaryname(j).c_str());
                                    if(j < nDictionaryID-1)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                                }
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                            }
                        }
                        else
                        {
                            rsp->ResponseCode = CMGR_FETCH_ERROR;
                            CLOG_ERROR("Error Fetching Peer Information ");
                            if(err.IsInitialized())
                            {
                                formErrorMessage(err,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
                        }
                    }
                    else
                    {
                        rsp->ResponseCode = CMGR_FETCH_ERROR;
                        CLOG_ERROR("Error Fetching Peer Information ");
                        if(err.IsInitialized())
                        {
                            formErrorMessage(err,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
                else
                {
                    if(m_prodcmapi->GetPeerConfig(hostname,realmname,Peer,err) == CMAPI_SUCCESS)
                    {
                        PeerConfig *PC = &Peer;
                        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                        if(PC->has_peerhostname())
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Peer Dictionary Table");
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,"Dictionary-names",ROW_DELIMITER);
                            int nDictionaryID = PC->dictionaryname_size();
                            CLOG_INFO("num of Dictionaries = %d",nDictionaryID);
                            if(nDictionaryID == 0)
                            {
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s ","NULL");
                            }
                            for(int j=0;j<nDictionaryID;j++)
                            {
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",PC->dictionaryname(j).c_str());
                                if(j < nDictionaryID-1)
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                            }
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                        }
                        else
                        {
                            rsp->ResponseCode = CMGR_FETCH_ERROR;
                            CLOG_ERROR("Error Fetching Peer Information ");
                            if(err.IsInitialized())
                            {
                                formErrorMessage(err,rsp);
                                CLOG_ERROR("Error Message received is %s",rsp->payload);
                            }
                        }
                    }
                    else
                    {
                        rsp->ResponseCode = CMGR_FETCH_ERROR;
                        CLOG_ERROR("Error Fetching Dictionary-names Information ");
                        if(err.IsInitialized())
                        {
                            formErrorMessage(err,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                        else
                        {
                            ErrorDetails det;
                            det.set_errormsgkey("config.common.err.generic.error");
                            formErrorMessage(det,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
            }
            else if (cmdID == C_cli_showallpeer_Id || cmdID == C_cli_showpeerstatus_Id)
            {
                PeersConfig Peers;
                if(m_prodcmapi->GetAllPeers(Peers,err) == CMAPI_SUCCESS)
                {
                    int NPeers = Peers.peers_size();
                    CLOG_INFO("Num of peers = %d",NPeers);
                    if (NPeers != 0)
                    {
                        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Peer Table");
                        if(cmdID == C_cli_showallpeer_Id)
                        {
#if DRE
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                                    FIELD_DELIMITER,"PeerName", 
                                    FIELD_DELIMITER,"RealmName", 
                                    FIELD_DELIMITER,"IP(or)Fqdn",
                                    FIELD_DELIMITER,"Port",
                                    FIELD_DELIMITER,"SecurePort",
                                    FIELD_DELIMITER,"TransportType",
                                    FIELD_DELIMITER,"Secondary-ip's",
                                    FIELD_DELIMITER,"TLSEnabled",
                                    FIELD_DELIMITER,"IsDPRDisconnCauseSupport",
                                    FIELD_DELIMITER,"FailOverEnable",
                                    FIELD_DELIMITER,"FailBackEnable",
                                    FIELD_DELIMITER,"Alternate-peer",
                                    FIELD_DELIMITER,"IsMate",
                                    FIELD_DELIMITER,"TcTimerVal",
                                    FIELD_DELIMITER,"WatchDogTimer",
                                    FIELD_DELIMITER,"ExpiryTimer",
                                    FIELD_DELIMITER,"BusyReconnectTimer",
                                    FIELD_DELIMITER,"DoNotwantToTalkToYouTimer",
                                    FIELD_DELIMITER,"PeerStatus",
                                    FIELD_DELIMITER,"PeerState",
                                    FIELD_DELIMITER,"Dictionary-names",ROW_DELIMITER);  
#else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                                    FIELD_DELIMITER,"PeerName", 
                                    FIELD_DELIMITER,"RealmName", 
                                    FIELD_DELIMITER,"IP(or)Fqdn",
                                    FIELD_DELIMITER,"Port",
                                    FIELD_DELIMITER,"TransportType",
                                    FIELD_DELIMITER,"Secondary-ip's",
                                    FIELD_DELIMITER,"FailOverEnable",
                                    FIELD_DELIMITER,"FailBackEnable",
                                    FIELD_DELIMITER,"Alternate-peer",
                                    FIELD_DELIMITER,"IsMate",
                                    FIELD_DELIMITER,"TcTimerVal",
                                    FIELD_DELIMITER,"WatchDogTimer",
                                    FIELD_DELIMITER,"ExpiryTimer",
                                    FIELD_DELIMITER,"BusyReconnectTimer",
                                    FIELD_DELIMITER,"DoNotwantToTalkToYouTimer",
                                    FIELD_DELIMITER,"PeerStatus",
                                    FIELD_DELIMITER,"PeerState",
                                    FIELD_DELIMITER,"Dictionary-names",ROW_DELIMITER);  

#endif
                            for (int i = 0; i < NPeers; i++)
                            {
                                PeerConfig *PC = Peers.mutable_peers(i);
                                if(PC->has_peerhostname())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->peerhostname().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_realm()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->realm().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_serveripaddr())  
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->serveripaddr().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_port())  
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->port(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if DRE
                                if(PC->has_secureport())  
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->secureport(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                                if(PC->has_transporttype()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->transporttype().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                int Ipcount = PC->secondaryipaddr_size();
                                if(Ipcount !=0)
                                {
                                    for(int j=0; j<Ipcount;j++)
                                    {
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",PC->secondaryipaddr(j).c_str());
                                        if(j < Ipcount -1)
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,",");
                                    }
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",FIELD_DELIMITER);
                                }
                                else 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if DRE
                                if(PC->has_tlsenabled())
                                {   
                                    if(PC->tlsenabled() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_issupportdisconnectcause())
                                {   
                                    if(PC->issupportdisconnectcause() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                                if(PC->has_failoverenable())
                                {
                                    if(PC->failoverenable() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }   
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_failebackenable())
                                {
                                    if(PC->failebackenable() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_altpeername())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->altpeername().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_ismate())
                                {           
                                    if(PC->ismate() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_tctimerval())    
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->tctimerval(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_watchdogtimer()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->watchdogtimer(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_expirytimer())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->expirytimer(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                
                                if(PC->has_busyreconnecttimerval())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->busyreconnecttimerval(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_donotwanttotalktoyoutimerval())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",PC->donotwanttotalktoyoutimerval(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_peerstatus())
                                {
                                    if(PC->peerstatus() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                
                                if(PC->has_peerstate())
                                {
                                    if(PC->peerstate() == PEER_CLOSED)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSED%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_I_CEA)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_I_CEA%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK_ELECT)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK_ELECT%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_RETURNS)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_RETURNS%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_I_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_I_OPEN%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_R_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_R_OPEN%c",FIELD_DELIMITER);
                                    else if(PC->peerstate() == PEER_CLOSING)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSING%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                int nDictionaryID = PC->dictionaryname_size();
                                if(nDictionaryID == 0)
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s ","NULL");
                                }
                                for(int j=0;j<nDictionaryID;j++)
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",PC->dictionaryname(j).c_str());
                                    if(j < nDictionaryID-1)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                                }
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                            }
                        }
                        else
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",FIELD_DELIMITER,"PeerName",FIELD_DELIMITER,"RealmName",FIELD_DELIMITER,"PeerStatus",FIELD_DELIMITER,"PeerState",ROW_DELIMITER);
                            for (int i = 0; i < NPeers; i++)
                            {
                                PeerConfig *PC = Peers.mutable_peers(i);

                                if(PC->has_peerhostname())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->peerhostname().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_realm()) 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",PC->realm().c_str(),FIELD_DELIMITER);
                                else 
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_peerstatus())
                                {
                                    if(PC->peerstatus() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(PC->has_peerstate())
                                {
                                    if(PC->peerstate() == PEER_CLOSED)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSED%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_I_CEA)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_I_CEA%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_CONN_ACK_ELECT)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_CONN_ACK_ELECT%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_WAIT_RETURNS)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_WAIT_RETURNS%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_I_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_I_OPEN%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_R_OPEN)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_R_OPEN%c",ROW_DELIMITER);
                                    else if(PC->peerstate() == PEER_CLOSING)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"PEER_CLOSING%c",ROW_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                            }
                        } 
                    }
                    else
                    {
                        rsp->ResponseCode = CMGR_FETCH_ERROR;
                        CLOG_ERROR("Error Fetching Peer Information ");
                        if(err.IsInitialized())
                        {
                            formErrorMessage(err,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }

                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching Peer Information ");
                    if(err.IsInitialized())
                    {

                        formErrorMessage(err,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }                
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }

            rsp->cmd_id = cmdID;
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);   
        }

        void ShowConfigLocalHost(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            AllResponses cliRsp, *rsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            rsp = &cliRsp;
            LocalHost localhost;
            ErrorDetails err;
            if(m_prodcmapi->GetLocalHostConfig(localhost) == CMAPI_SUCCESS)
            {
                LocalHost *LC = &localhost;
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                if(LC->has_localhostname())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   LocalHost Table");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"HostName", 
                            FIELD_DELIMITER,"RealmName",
                            FIELD_DELIMITER,"Auth TimeOut",
                            FIELD_DELIMITER,"Auth GraceTime",
                            FIELD_DELIMITER,"Auth LifeTime",
                            FIELD_DELIMITER,"Acct Interim",
                            FIELD_DELIMITER,"Acct TimeOut",
                            FIELD_DELIMITER,"local-transport-id",
                            FIELD_DELIMITER,"local-transport-id",
                            FIELD_DELIMITER,"local-transport-id",
                            FIELD_DELIMITER,"local-transport-id",ROW_DELIMITER);
                    if(LC->has_localhostname())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LC->localhostname().c_str(),FIELD_DELIMITER);
                    }

                    if(LC->has_realmname())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LC->realmname().c_str(),FIELD_DELIMITER);
                    }

                    if(LC->has_authsessiontimeout())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->authsessiontimeout(),FIELD_DELIMITER);
                    }

                    if(LC->has_authsessiongraceperiod())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->authsessiongraceperiod(),FIELD_DELIMITER);
                    }

                    if(LC->has_authsessionlifetime())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->authsessionlifetime(),FIELD_DELIMITER);
                    }

                    if(LC->has_acctsessioninteriminterval())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->acctsessioninteriminterval(),FIELD_DELIMITER);
                    }

                    if(LC->has_acctsessiontimeout())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->acctsessiontimeout(),FIELD_DELIMITER);
                    }
                    int transportcount = LC->transports_size();
                    CLOG_INFO("Num of Transports configured = %d",transportcount);
                    for (int j = 0;j<4;j++)
                    {
                        int iFlag = 0;
                        for(int i = 0; i<transportcount; i++)
                        {
                            int transportType = 0;
                            LHTransport *LocalTransport= LC->mutable_transports(i);
                            if(LocalTransport->transportslot() == (unsigned )(j+1))
                            {
                                iFlag = 1;
                                int slot_value = 0;
                                slot_value = LocalTransport->transportslot();
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d",LocalTransport->transportslot());
                                if(LocalTransport->has_transporttype())
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", TransportType - ");
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",LocalTransport->transporttype().c_str());
                                    if(!strcmp(LocalTransport->transporttype().c_str(),"TCP"))
                                        transportType = TRANSTYPE_TCP;
                                    else    
                                        transportType = TRANSTYPE_SCTP;
                                }
                                if(LocalTransport->has_hostipaddr())   
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", IpAddr - ");
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",LocalTransport->hostipaddr().c_str());
                                }
                                    
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", PublicIpAddr - ");
                                if(LocalTransport->has_publicserveripaddr())   
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",LocalTransport->publicserveripaddr().c_str());
                                }
                                else
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL");
                                }

                                int secondaryIpnum = LocalTransport->secondaryipaddr_size();
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", Secondary-Ip's - ");
                                if(secondaryIpnum != 0)
                                {
                                    for( int k=0 ; k < secondaryIpnum; k++)
                                    {
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",LocalTransport->secondaryipaddr(k).c_str());
                                        if(k < secondaryIpnum - 1)
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                                    }
                                }
                                else
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL");
                                }
#if DRE
                                if(LocalTransport->has_port())
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", Port - ");
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d",LocalTransport->port());
                                }
                                else
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL");
                                }
                                if(LocalTransport->has_secureport())
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", SecurePort - ");
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LocalTransport->secureport(),FIELD_DELIMITER);
                                }
                                else
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                }
#else
                                if(LocalTransport->has_port())
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", Port - ");
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LocalTransport->port(),FIELD_DELIMITER);
                                }
                                else
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                }
#endif
                            }
                        }
                        if(iFlag == 0)
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d",(j+1));
                            if(j+1 == MAX_LOCALTRANSPORT_ATTRIBUTES)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN," - NULL%c",ROW_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN," - NULL%c",FIELD_DELIMITER);
                        }
                    }
                }
                else
                {
                    m_prodcmapi->GetLastCallErrorDetails(err);
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error in Fetching Local-host info");
                    if(err.IsInitialized())
                    {
                        formErrorMessage(err,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }

                }
            }
            else
            {

                m_prodcmapi->GetLastCallErrorDetails(err);
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("Error in Fetching Local-host info");
                if(err.IsInitialized())
                {
                    formErrorMessage(err,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
                else
                {
                    ErrorDetails det;
                    det.set_errormsgkey("config.common.err.generic.error");
                    formErrorMessage(det,rsp);
                    CLOG_ERROR("Error Message received is %s",rsp->payload);
                }
            }
            rsp->cmd_id = cmdID;
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);
        }


        void ShowRealmConfigcmapi(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            CLOG_DEBUG(" > %s ",__FUNCTION__);
            GetConfigReq *clireq=(GetConfigReq *)req;
            AllResponses cliRsp, *rsp;
            rsp = &cliRsp;
            memset(&cliRsp,0,sizeof(cliRsp));
            RealmConfig Realm;
            ErrorDetails errResp;
            string InputVal= clireq->shReqPayload.dreKeyInfo.realmKeyInfo.RealmName;
            CLOG_DEBUG("InputVal = %s ",InputVal.c_str());
            if(cmdID == C_cli_showconfigrealm_Id)
            {
                if(m_prodcmapi->GetRealm(InputVal,Realm,errResp) == CMAPI_SUCCESS)
                {
                    RealmConfig *RC = &Realm;
                    if(RC->has_realmname())
                    {
                        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Realm Table");
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                                FIELD_DELIMITER,"RealmName",
                                FIELD_DELIMITER,"Local-Action",ROW_DELIMITER);

#if 0
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c",
                                FIELD_DELIMITER,"RealmName",
                                FIELD_DELIMITER,"Local-Action",
                                FIELD_DELIMITER,"Proxy-Info-Avp",
                                FIELD_DELIMITER,"RedirectHostUsage",
                                FIELD_DELIMITER,"RedirectMaxCacheTime",ROW_DELIMITER);         
#endif
                        if(RC->has_realmname())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->realmname().c_str(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                        if(RC->has_localaction())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->localaction().c_str(),ROW_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
#if 0
                        if(RC->has_enableproxyinfoavp())
                        {
                            if(RC->has_enableproxyinfoavp() == 0)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                        }
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                        if(RC->has_redirecthostusage())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirecthostusage(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                        if(RC->has_redirectmaxcachetime())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirectmaxcachetime(),ROW_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
#endif
                    }
                    else 
                    {
                        rsp->ResponseCode = CMGR_FETCH_ERROR;  
                        CLOG_ERROR("Error Fetching Realm Information ");
                        if(errResp.IsInitialized())
                        {
                            formErrorMessage(errResp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }     
                }
                else{
                    rsp->ResponseCode = CMGR_FETCH_ERROR;  
                    CLOG_ERROR("Error Fetching Realm Information ");
                    if(errResp.IsInitialized())
                    {
                        formErrorMessage(errResp,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }
            }
            else if(cmdID == C_cli_showroute_Id)
            {
                if(m_prodcmapi->GetRealmRouting(InputVal,Realm,errResp) == CMAPI_SUCCESS)
                {
                    RealmConfig *RC = &Realm;
                    int DestinationsCount = RC->destinfo_size();
                    CLOG_INFO("Destinations Count = %d ",DestinationsCount);
                    if(DestinationsCount != 0)
                    {
                        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Realm-Routing Table");
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",
                                FIELD_DELIMITER,"PeerName",
                                FIELD_DELIMITER,"Asso-RealmName", 
                                FIELD_DELIMITER,"ApplicationID",
                                FIELD_DELIMITER,"Priority",ROW_DELIMITER);            
                        for (int Dest = 0; Dest < DestinationsCount; Dest++)
                        {
                            Destination *DT = RC->mutable_destinfo(Dest);
                            if(DT->has_peername())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DT->peername().c_str(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                            if(DT->has_realmname())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DT->realmname().c_str(),FIELD_DELIMITER);
                            else 
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                            if(DT->has_applicationid())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DT->applicationid(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                            if(DT->has_priority())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DT->priority(),ROW_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                        }
                    }
                    else
                    {
                        CLOG_ERROR("Error Fetching Realm-Route Information ");
                        rsp->ResponseCode = CMGR_FETCH_ERROR;  
                        if(errResp.IsInitialized())
                        {
                            formErrorMessage(errResp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }

                } else {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;  
                    if(errResp.IsInitialized())
                    {
                        formErrorMessage(errResp,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    CLOG_ERROR("Error Fetching Realm-Route Information ");
                }

            }
            else if(cmdID == C_cli_showrealm_Id || cmdID == C_cli_showconfigallrealm_Id)    
            {
                RealmsConfig Realms;
                if(m_prodcmapi->GetAllRealms(Realms,errResp) == CMAPI_SUCCESS)
                {
                    int NRealms = Realms.realms_size();
                    CLOG_INFO("Number of Realms = %d ",NRealms);
                    if(NRealms != 0)
                    {
                        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                        if(cmdID == C_cli_showrealm_Id)
                        {                
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Realm-Routing Table");
#if 0
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
#endif
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c",
                                    FIELD_DELIMITER,"RealmName",
                                    FIELD_DELIMITER,"Local-Action",
#if 0
                                    FIELD_DELIMITER,"Proxy-Info-Avp",
                                    FIELD_DELIMITER,"RedirectHostUsage",
                                    FIELD_DELIMITER,"RedirectMaxCacheTime", 
#endif
                                    FIELD_DELIMITER,"PeerName",
                                    FIELD_DELIMITER,"Asso-RealmName", 
                                    FIELD_DELIMITER,"ApplicationID",
                                    FIELD_DELIMITER,"Priority",ROW_DELIMITER);            

                            for(int i = 0;i < NRealms; i++)
                            {
                                RealmConfig *RC = Realms.mutable_realms(i);
                                int DestinationsCount = RC->destinfo_size();
                                CLOG_INFO(" Destinations Count = %d ",DestinationsCount);
                                if(DestinationsCount !=0) 
                                {
                                    for (int Dest = 0; Dest < DestinationsCount; Dest++)
                                    {
                                        Destination *DT = RC->mutable_destinfo(Dest);

                                        if(RC->has_realmname())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->realmname().c_str(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                        if(RC->has_localaction())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->localaction().c_str(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if 0
                                        if(RC->has_enableproxyinfoavp())
                                        {
                                            if(RC->has_enableproxyinfoavp() == 0)
                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                            else
                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                        } 
                                        else 
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                        if(RC->has_redirecthostusage())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirecthostusage(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                        if(RC->has_redirectmaxcachetime())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirectmaxcachetime(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                                        if(DT->has_peername())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DT->peername().c_str(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                        if(DT->has_realmname())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DT->realmname().c_str(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                        if(DT->has_applicationid())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DT->applicationid(),FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                        if(DT->has_priority())
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DT->priority(),ROW_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                                    }
                                } else {
                                    if(RC->has_realmname())
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->realmname().c_str(),FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);


                                    if(RC->has_localaction())
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->localaction().c_str(),FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if 0
                                    if(RC->has_enableproxyinfoavp())
                                    {
                                        if(RC->has_enableproxyinfoavp() == 0)
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                        else
                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                    }
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                    if(RC->has_redirecthostusage())
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirecthostusage(),FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                    if(RC->has_redirectmaxcachetime())
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirectmaxcachetime(),FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                                }
                            }
                        }
                        else
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Realm Table");
#if 0
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c",
#endif
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                                    FIELD_DELIMITER,"RealmName",
                                    FIELD_DELIMITER,"Local-Action",ROW_DELIMITER);
#if 0
                                    FIELD_DELIMITER,"Proxy-Info-Avp",
                                    FIELD_DELIMITER,"RedirectHostUsage",
                                    FIELD_DELIMITER,"RedirectMaxCacheTime",ROW_DELIMITER);         
#endif
                            for(int i = 0;i < NRealms; i++)
                            {
                                RealmConfig *RC = Realms.mutable_realms(i);
                                if(RC->has_realmname())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->realmname().c_str(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(RC->has_localaction())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RC->localaction().c_str(),ROW_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
#if 0
                                if(RC->has_enableproxyinfoavp())
                                {
                                    if(RC->has_enableproxyinfoavp() == 0)
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                                }
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(RC->has_redirecthostusage())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirecthostusage(),FIELD_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                                if(RC->has_redirectmaxcachetime())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RC->redirectmaxcachetime(),ROW_DELIMITER); 
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
#endif
                            }
                        }
                    }
                    else
                    {
                        rsp->ResponseCode = CMGR_FETCH_ERROR;
                        CLOG_ERROR("Error Fetching Realm Information ");
                        if(errResp.IsInitialized())
                        {
                            formErrorMessage(errResp,rsp);
                            CLOG_ERROR("Error Message received is %s",rsp->payload);
                        }
                    }
                }
                else
                {
                    rsp->ResponseCode = CMGR_FETCH_ERROR;
                    CLOG_ERROR("Error Fetching Realm Information ");
                    if(errResp.IsInitialized())
                    {
                        formErrorMessage(errResp,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                    else
                    {
                        ErrorDetails det;
                        det.set_errormsgkey("config.common.err.generic.error");
                        formErrorMessage(det,rsp);
                        CLOG_ERROR("Error Message received is %s",rsp->payload);
                    }
                }

            }
            rsp->cmd_id = cmdID;
            CLOG_DEBUG(" < %s ",__FUNCTION__);
            SendResponseToMgmt2((void*)rsp, portnum);       
        }
#endif

        /***************************** REPLICATION  MANAGER SETTING FUNCTIONS ******************************/

        void SetReplicationFlag(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            int *port ;
            port = (int*) malloc(sizeof(int));
            *port = portnum;
            MessageId msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_REPLFLAG);
            MeSSEndpoint dest = {COMP_REPLICATION_MANAGER, 64};

            //std::cout << " SetReplicationFlag>> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)req, sizeof(SetConfigReq),port);


            msgId = MakeMsgId(I_CONFIG_MANAGER, M_REPMGR_REPLFLAG);
            dest = {CMGR_COMP_ID, 10};

            //std::cout << "Replication Flag: Sending to CMGR>> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)req, sizeof(SetConfigReq),port);
        }

        void SetReplLogLevel(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            int *port ;
            port = (int*) malloc(sizeof(int));
            *port = portnum;
            MessageId msgId = MakeMsgId(I_REPMGR_ID, M_REPMGR_LOGLEVEL);
            MeSSEndpoint dest = {COMP_REPLICATION_MANAGER, 64};

            //std::cout << "SetReplLogLevel>> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)req, sizeof(SetConfigReq),port);

            msgId = MakeMsgId(I_CONFIG_MANAGER, M_REPMGR_LOGLEVEL);
            dest = {CMGR_COMP_ID, 10};

            //std::cout << "Replication Flag: Sending to CMGR>> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)req, sizeof(SetConfigReq),port);
        }
#if 0
        void delete_tableAndrecordInDb(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            //int *port ;
            int methodId;
            DrePeerConfigReq drePeerConfigReq;
            DreRealmConfigReq dreRealmConfigReq;
            //int dreRetCode = 0;
            //int cmgrRetCode = 0;
            SetConfigReq *cliReq = (SetConfigReq *)req;
            //ClientInfo *clientInfo = new ClientInfo;
            SetReqCookie *cookie = new SetReqCookie;
            MessageId msgId;
            MeSSEndpoint dest;

            cookie->req = new SetConfigReq;
            memcpy(cookie->req,req,sizeof(SetConfigReq));

            if(cmdID == C_cli_no_configRealm_Id)
                methodId = M_DELETE_REALMTABLE;
            else if(cmdID == C_cli_no_localhost_Id) 
                methodId = M_DELETE_LOCALHOST;
            else if(cmdID == C_cli_no_peer_Id)
                methodId = M_DELETE_PEERTABLE;
            //else if(cmdID ==  C_cli_peer_dictionary_Id)
            //  methodId = M_PEER_DELETE_DICT_ID;

            cookie->clientInfo.udpPort = portnum;

            if(methodId == M_DELETE_PEERTABLE) {
                strcpy(drePeerConfigReq.peerKeyInfo.HostName, cliReq->Payload.drePeerPayload.peerKeyInfo.HostName);
                strcpy(drePeerConfigReq.peerKeyInfo.RealmName, cliReq->Payload.drePeerPayload.peerKeyInfo.RealmName);
                msgId = MakeMsgId(I_DRE_APP, M_DELETE_PEERTABLE);
                MeSSEndpoint dest = {COMP_DRE_APP, 10};
                MeSSObj().Send(dest, msgId,reinterpret_cast<void*>(&drePeerConfigReq),sizeof(DrePeerConfigReq), cookie);
            }
            else if(methodId == M_DELETE_REALMTABLE){
                strcpy(dreRealmConfigReq.realmKeyInfo.RealmName, cliReq->Payload.dreRealmPayload.realmKeyInfo.RealmName);

                msgId = MakeMsgId(I_DRE_APP, M_DELETE_REALMTABLE);
                dest = {COMP_DRE_APP, 10};
                MeSSObj().Send(dest, msgId, reinterpret_cast<void*> (&dreRealmConfigReq),sizeof(DreRealmConfigReq), cookie);
                //this->SetAllConfig(cookie,sizeof(DrePeerConfigReq),I_DRE_APP,methodId, COMP_DRE_APP);
            }else{
                this->SetAllConfig(cookie,sizeof(SetConfigReq),I_CONFIG_MANAGER,methodId, CMGR_COMP_ID);
            }

#if 0
            MessageId msgId = MakeMsgId(I_DRE_APP, M_PEER_DELETE_REQ);
            MeSSEndpoint dest = {COMP_DRE_APP, 10};

            //std::cout << "Sending DELETE Request to DRE ... " << std::endl;
            dreRetCode = MeSSObj().Send(dest, msgId, (void*)&dreReq, sizeof(DrePeerConfigReq),port);
            //std::cout << "Sent request to DRE ... " << std::endl;

            memset(&msgId, 0, sizeof(MessageId));
            msgId = MakeMsgId(interfaceID, methodId);
            dest = {CMGR_COMP_ID, 10};

            //std::cout << "Deleting table/record from ConfigDB>> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)req, len, port);
#endif
        }
#endif
        /***************************** AVAILABILITY  MANAGER SETTING FUNCTIONS ******************************/

        void SetAllConfig(void *cookie,int len,int InterfaceID,int MethodID,short int ComponentID)
        {

            MessageId msgId = MakeMsgId(InterfaceID, MethodID);
            MeSSEndpoint dest = {ComponentID, 10};

            //std::cout << "Set All req >> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)reinterpret_cast <SetReqCookie*>(cookie)->req, len,(void*)cookie);
        }

        void SetASGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {   
            SetReqCookie *cookie;
            try{
                cookie = new SetReqCookie;
                cookie->req = new SetConfigReq;
            }
            catch(...){
                //std::cout <<"malloc exception" << std::endl;
            }

            memcpy((void*)cookie->req, (void*)req,sizeof(SetConfigReq));
            //std::cout << "SetASGroup Req >>" << std::endl;
            cookie->clientInfo.udpPort = portnum;

            this->SetAllConfig(cookie, sizeof(SetConfigReq), I_DRE_APP, M_SET_ASGROUP_REQ, COMP_DRE_APP);
        }

        void DeleteASGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {   
            SetReqCookie *cookie;
            try{
                cookie = new SetReqCookie;
                cookie->req = new SetConfigReq;
            }
            catch(...){
                //std::cout <<"malloc exception" << std::endl;
            }

            memcpy((void*)cookie->req, (void*)req,sizeof(SetConfigReq));
            //std::cout << "Delete ASGroup Req >>" << std::endl;
            cookie->clientInfo.udpPort = portnum;

            this->SetAllConfig(cookie, sizeof(SetConfigReq), I_DRE_APP, M_DELETE_ASGROUP_REQ, COMP_DRE_APP);
        }
        void responseTimeoutASGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {   
            SetReqCookie *cookie;
            try{
                cookie = new SetReqCookie;
                cookie->req = new SetConfigReq;
            }
            catch(...){
                //std::cout <<"malloc exception" << std::endl;
            }

            memcpy((void*)cookie->req, (void*)req,sizeof(SetConfigReq));
            //std::cout << "responseTimeout ASGroup Req >>" << std::endl;
            cookie->clientInfo.udpPort = portnum;

            this->SetAllConfig(cookie, sizeof(SetConfigReq), I_DRE_APP, M_ASF_RESPONSE_TIMEOUT_REQ, COMP_DRE_APP);
        }
        void ConfigASGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {   
            SetReqCookie *cookie;
            try{
                cookie = new SetReqCookie;
                cookie->req = new SetConfigReq;
            }
            catch(...){
                //std::cout <<"malloc exception" << std::endl;
            }

            memcpy((void*)cookie->req, (void*)req,sizeof(SetConfigReq));
            //std::cout << "Config ASGroup Req >>" << std::endl;
            cookie->clientInfo.udpPort = portnum;

            this->SetAllConfig(cookie, sizeof(SetConfigReq), I_DRE_APP, M_ASF_CONFIG_REQ, COMP_DRE_APP);
        }

        void TerminateASGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {   
            SetReqCookie *cookie;
            try{
                cookie = new SetReqCookie;
                cookie->req = new SetConfigReq;
            }
            catch(...){
                //std::cout <<"malloc exception" << std::endl;
            }

            memcpy((void*)cookie->req, (void*)req,sizeof(SetConfigReq));
            //std::cout << "Terminate AS groupReq >>" << std::endl;
            cookie->clientInfo.udpPort = portnum;

            this->SetAllConfig(cookie, sizeof(SetConfigReq), I_DRE_APP, M_TERMINATE_ASGROUP_REQ, COMP_DRE_APP);
        }

        void ShowASGroup(int portnum,void* req,int len,int cmdID,int interfaceID)
        {
            int *port ;
            port = (int*) malloc(sizeof(int));
            *port = portnum;
            MessageId msgId = MakeMsgId(I_CONFIG_MANAGER, M_SHOW_ASGROUP_REQ);
            MeSSEndpoint dest = {CMGR_COMP_ID, 10};

            //std::cout << "show AS Group>> " << std::endl;
            MeSSObj().Send(dest, msgId, (void*)req, sizeof(GetConfigReq),port);
        }

};

CondVar CmnMgmtMess::m_terminateMess;
CmnMgmtMess* CmnMgmtMess::cliApp = NULL;

//Flag to check if cli is initialized or not, this is used to controll thread manipulation
bool CmnMgmtMess::ms_cliInitialized;
//CondVar CmnMgmtMess::ms_cmgrAvlble;

CmnMgmtMess* CmnMgmtMess::CreateObj(void)
{
    if(cliApp == NULL)
        cliApp = new CmnMgmtMess;
    return cliApp;
}

void SendConfigRequest(int port,void* buf,int len,int cmdID,int InterfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    CmnMgmtMess *ptr;
    ptr = CmnMgmtMess::CreateObj();

    CLOG_DEBUG("cmdID = %d",cmdID);
    CLOG_INFO("* CLI Instance-id * = %d",MeSS::MeSSObj().Self().instance);

    if(!(eAccelero::MESS_ISActiveInst(MeSS::MeSSObj().Self().instance)))
    {
        CLOG_CRITICAL("* CLI Instance-id * = %d",MeSS::MeSSObj().Self().instance);
        AllResponses cliRsp, *rsp;
        memset(&cliRsp,0,sizeof(cliRsp));
        rsp = &cliRsp;
        rsp->cmd_id = cmdID;
        rsp->ResponseCode = DONT_ALLOW_STANDBY;     
        ErrorDetails det;
        det.set_errormsgkey("config.common.not.allowed.in.standby");
        formErrorMessage(det,rsp);
        CLOG_CRITICAL("Error Message received is %s",rsp->payload);
        SendResponseToMgmt2((void*)rsp, port);  
        CLOG_ERROR("User is not allowed to execute commands in Standby CLI ");
    }
    else
    {
        switch(cmdID) {
            case C_cli_tlsconfig_Id:
                ptr->Settlsconfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_tlssuite_Id:
                ptr->SetCipherSuite(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_trustedca_Id:
            case C_cli_notrustedca_Id:
                ptr->SetTrustedCA(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_sctpconfig_Id:
                ptr->SetSctpConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_peeripcheck_Id:
                ptr->SetIpCheck(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_predectiveloopdetection_Id:
                ptr->SetPredictiveLoopDetection(port,buf,len,cmdID,InterfaceID);
                break;
            
            case C_cli_snaptrsupport_Id:
                ptr->SetSnaptrSupport(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_showsctpconfig_Id:
            case C_cli_showtlsconfig_Id:
            case C_cli_showtrustedcaconfig_Id:
            case C_cli_showciphersuiteconfig_Id:
            case C_cli_showgeneralconfig_Id:
            case C_cli_show_ciphersuites_Id:
                ptr->ShowGeneralConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_GetNodeState_Id:
                ptr->GetNodeState(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_showconfigavamgr_Id:
                ptr->ShowAvamgrConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_switchover_Id:
                ptr->SwitchOver(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_staticrouting_Id:
                ptr->SetStaticRouting(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_showstaticrouting_Id:
            case C_cli_showallstaticrouting_Id:
                ptr->ShowStaticRouting(port,buf,len,cmdID,InterfaceID);
                break;
            
            case C_cli_no_peer_Id:
            case C_cli_peer_Id:
            case C_cli_modifypeer_Id:
            case C_cli_no_altpeer_Id:
            case C_cli_no_peersecondaryip_Id:
                ptr->SetConfigPeer(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_showpeer_Id:
            case C_cli_showallpeer_Id:
            case C_cli_show_dictionary_Id:
            case C_cli_showpeerconfig_Id:
            case C_cli_showpeerstatus_Id:
                ptr->ShowPeerConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_peerControl_Id:
                ptr->PeerControl(port,buf,len,cmdID,InterfaceID);

                break;

            case C_cli_showrealm_Id:
            case C_cli_showconfigrealm_Id:
            case C_cli_showroute_Id:
            case C_cli_showconfigallrealm_Id:
                ptr->ShowRealmConfigcmapi(port,buf,len,cmdID,InterfaceID);

                break;

            case C_cli_showlocalhost_Id:
            case C_cli_get_localhostconfig_Id:
                ptr->ShowConfigLocalHost(port,buf,len,cmdID,InterfaceID);
                break;          

            case C_cli_showtask_Id:
                //std::cout << "case C_cli_showtask_Id:" << std::endl;
                break;

            case C_cli_restart_Id:
                //std::cout << "C_cli_restart_Id:" << std::endl;
                break;

            case C_cli_configRealm_Id:
            case C_cli_RealmDestination_Id:
                ptr->SetConfigRealm(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_localhost_Id:
            case C_cli_modifylocalhost_Id:
            case C_cli_no_localhost_Id:
            case C_cli_deletetransport_Id:
            case C_cli_deletesecondaryip_Id:
                ptr->SetLocalHost(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_showdefaultRoute_Id:
                ptr->ShowdefaultRouteConfig(port,buf,len,cmdID,InterfaceID);
                break;


            case C_cli_defaultRoute_Id:
            case C_cli_nodefaultRoute_Id:
                ptr->SetDefaultRoute(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_adduser_Id:
            case C_cli_deleteuser_Id:
            case C_cli_moduser_Id:
                ptr->setUser(port,buf,len,cmdID,InterfaceID);
                break;
            case C_cli_verify_passwd_Id:
            case C_cli_showuser_Id:
                ptr->ShowUser(port,buf,len,cmdID,InterfaceID);
                break;
            case C_cli_show_version_Id:
                ptr->ShowVersion(port, buf, len, cmdID, InterfaceID);
                break;
            case SetReplicationFlag_cmd:
                ptr->SetReplicationFlag(port,buf,len,cmdID,InterfaceID);
                break;

            case SetReplLogLevel_cmd:
                ptr->SetReplLogLevel(port,buf,len,cmdID,InterfaceID);
                break;
#if 0       
            case C_cli_no_configRealm_Id:
            case C_cli_no_localhost_Id:
            case C_cli_no_peer_Id:
                ptr->delete_tableAndrecordInDb(port,buf,len,cmdID,InterfaceID);
                break;
#endif
            case C_cli_deletedictionary_Id:
            case  C_cli_peer_dictionary_Id:
                ptr->SetDictionaryIds(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_set_log_level_Id:
            case C_cli_set_log_channel_Id:
            case C_cli_setall_log_level_Id:
                ptr->setLogging(port,buf,len,cmdID,InterfaceID);
                break;
            case C_cli_show_log_config_Id:
                ptr->showLoggingConfig(port,buf,len,cmdID,InterfaceID);
                break;

                /***************************** AVAILABILITY  MANAGER SETTING  ******************************/

            case SetAvaMgrLogLevel_cmd:
                ptr->SetConfigAvaMgrLogLevel(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigPingPeriodicity_cmd:
                ptr->SetConfigPingPeriodicity(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigPingPeriodicityArbitrator_cmd:
                ptr->SetConfigPingPeriodicityArbitrator(port,buf,len,cmdID,InterfaceID);
                break;

                /*      case SetConfigVirtualInterfaceActivationTime_cmd:
                        ptr->SetConfigVirtualInterfaceActivationTime(port,buf,len,cmdID,InterfaceID);
                        break;
                        */          
            case SetConfigPingAckReceiveFailures_cmd:
                ptr->SetConfigPeerPingAckReceiveFailures(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigArbitratorPingAckReceiveFailures_cmd:
                ptr->SetConfigArbitratorPingAckReceiveFailures(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigProcessRestartMaxInterval_cmd:
                ptr->SetConfigProcessRestartMaxInterval(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigProcessRestartMinCount_cmd:
                ptr->SetConfigProcessRestartMaxCount(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigGatewayIpAddress_cmd:
                ptr->SetConfigGatewayIP(port,buf,len,cmdID,InterfaceID);
                break;

            case SetConfigPrimaryVirtualIpAddress_cmd:
                ptr->SetPrimaryVirtualIpAddress(port,buf,len,cmdID,InterfaceID);
                break;

            case SetAvaMgrLogchannel_cmd:
                ptr->SetConfigAvaMgrLogchannel(port,buf,len,cmdID,InterfaceID);
                break;  
                /*  
                    case SetConfigIpV6_cmd:
                    ptr->SetConfigIpV6(port,buf,len,cmdID,InterfaceID);
                    break;

                    case SetConfigPrimaryVirtualIpAddress_cmd:
                    ptr->SetConfigPrimaryVirtualIpAddress(port,buf,len,cmdID,InterfaceID);
                    break;

                    case SetConfigSecondaryVirtualIpAddress_cmd:
                    ptr->SetConfigSecondaryVirtualIpAddress(port,buf,len,cmdID,InterfaceID);
                    break;
                    case Restart_cmd:
                    ptr->Restart(port,buf,len,cmdID,InterfaceID);
                    break;

                    case ShowProcess_cmd:
                    ptr->ShowProcess(port,buf,len,cmdID,InterfaceID);
                    break;
                    */
            case C_cli_add_asgroup_Id:

                ptr->SetASGroup(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_modify_asgroup_Id:
                ptr->SetASGroup(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_asgroup_Id:
                ptr->ShowASGroup(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_delete_asgroup_Id:
                ptr->DeleteASGroup(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_asf_config_Id:
                ptr->ConfigASGroup(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_asf_responseTimeout_Id:
                ptr->responseTimeoutASGroup(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_asf_terminate_Id:
                ptr->TerminateASGroup(port,buf,len,cmdID,InterfaceID);
                break;

                /***************************** ERLBF  Config *************************/

            case C_cli_set_erlbf_peer_config_Id:
                ptr->SetErlbfPeerConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_set_erlbf_peer_group_Id:
                ptr->SetErlbfPeerGroup(port,buf,len,cmdID,InterfaceID);
                break;
            case C_cli_show_erlbf_peer_group_Id:
            case C_cli_show_erlbf_peer_group_peers_Id:
            case C_cli_show_all_erlbf_peer_group_Id:
                ptr->ShowPeerGroups(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_get_erlbf_peer_ids_Id:
                ptr->GetPeerIds(port,buf,len,cmdID,InterfaceID);
                break;

                /******************************TRANSFORM Config*************************/
            case C_cli_load_dictionary_Id:
            case C_cli_unload_dictionary_Id:
                ptr->SetdictionaryConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_load_transformplugin_Id:
            case C_cli_unload_transformplugin_Id:
                ptr->SettransformpluginConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_loaded_dictionary_Id:
            case C_cli_show_all_loaded_dictionary_Id:
            case C_cli_show_peerdictionary_Id: 
                ptr->ShowLoadedDictionary(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_loaded_transformplugin_Id:   
            case C_cli_show_all_loaded_transformplugin_Id:   
                ptr->ShowLoadedTransformPlugin(port,buf,len,cmdID,InterfaceID);
                break;


                /**************************** IWF Config ********************************/
            case C_cli_localconfig_Id:
                ptr->SetLocalConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_translation_rule_config_Id:
            case C_cli_translation_vplmn_Id:
                ptr->SetTranslatorRule(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_s6a_map_config_Id:
                ptr->SetS6aMAPConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_map_s6a_config_Id:
            case C_cli_map_s6a_vplmn_config_Id:
            case C_cli_map_s6a_vplmn_sgsn_config_Id:
                ptr->SetMAPS6aConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_cap_ro_idp_config_Id:
                ptr->SetCAPRoIDPConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_cap_ro_idp_sms_config_Id:
                ptr->SetCAPRoIDPSMSConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_sctp_endpoint_Id:
            case C_cli_modify_sctp_endpoint_Id:
            case C_cli_delete_sctp_endpoint_Id:
            case C_cli_delete_sctpendpoint_multihoming_Id:
                ptr->SetSCTPEndPointConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_remoteroute_config_Id:
                ptr->SetRemoteRouteConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_sctp_profile_Id:
            case C_cli_modify_sctp_profile_Id:
                ptr->SetSCTPProfileConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_assocation_Id:
            case C_cli_no_assocation_Id:
            case C_cli_modify_assocation_Id:
                ptr->SetAssociationConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_assocation_set_Id:
            case C_cli_modify_assocation_set_Id:
                ptr->SetAssociationSetConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_destination_config_Id:
                ptr->SetDestinationConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_activate_association_Id:
                ptr->SetAssociationStatus(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_activate_associationSet_Id:
                ptr->SetAssociationSetStatus(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_local_config_Id:
                ptr->ShowSigtranLocalConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_sctp_profile_config_Id:
            case C_cli_show_all_sctp_profile_config_Id:
                ptr->ShowSctpProfileConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_sctp_endpoint_config_Id:
            case C_cli_show_all_sctp_endpoint_config_Id:
                ptr->ShowSctpEndPointConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_association_config_Id:
            case C_cli_show_all_association_config_Id:
                ptr->ShowAssociationConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_associationset_config_Id:
            case C_cli_show_all_associationset_config_Id:
                ptr->ShowAssociationSetConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_destination_config_Id:
            case C_cli_show_all_destination_config_Id:
                ptr->ShowDestinationConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_remoteroute_config_Id:
            case C_cli_show_all_remoteroute_config_Id:
                ptr->ShowRemoteRouteConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_translatorrule_config_Id:
            case C_cli_show_all_translatorrule_config_Id:
                ptr->ShowTranslatorRuleConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_s6amap_config_Id:
            case C_cli_show_s6amap_sgsn_addr_config_Id:
            case C_cli_show_s6amap_sgsn_prefix_config_Id:
                ptr->ShowS6aMAPConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_maps6a_config_Id:
                ptr->ShowMAPS6aConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_capro_idp_config_Id:
            case C_cli_show_capro_idpsms_config_Id:
            case C_cli_show_capro_idp_ext_tele_config_Id:
            case C_cli_show_capro_idp_ext_bearer_config_Id:
                ptr->ShowCAPRoConfig(port,buf,len,cmdID,InterfaceID);
                break;
            
            case C_cli_ual_set_Id:
                ptr->SetUALConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_ual_config_Id:
                ptr->ShowUALConfig(port,buf,len,cmdID,InterfaceID);
                break;

            case C_cli_show_iwf_version_Id:
                ptr->ShowIwfVersion(port, buf, len, cmdID, InterfaceID);
                break;
	    
            case C_cli_cap_timers_Id:
                ptr->SetIwfCapProtoConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_show_cap_timers_Id:
                ptr->ShowIwfCapProtoConfig(port, buf, len, cmdID, InterfaceID);
                break;
            
            case C_cli_show_log_cdr_Id:
                ptr->ShowLogCdrConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_show_tAns_trigger_config_Id:
            case C_cli_show_congestion_management_config_Id:
                ptr->ShowIwfFeatureConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_log_cdr_config_Id:
            case C_cli_tAns_trigger_config_Id:
            case C_cli_congestion_management_config_Id:
                ptr->SetIWFFeatureConfig(port, buf, len, cmdID, InterfaceID);
                break;
            
            case C_cli_dcca_general_config_Id:
            case C_cli_dcca_failure_handling_Id:
                ptr->SetIWFDccaGeneralConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_show_dcca_general_config_Id:
                ptr->ShowIWFDccaGeneralConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_dcca_dest_config_Id:
            case C_cli_dcca_dest_realm_config_Id:
                ptr->SetIWFDccaDestConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_show_dcca_dest_config_Id:
                ptr->ShowIWFDccaDestConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_protocol_actions_Id:
            case C_cli_no_eventspecific_config_Id:
            case C_cli_no_eventtype_config_Id:
            case C_cli_no_call_scenario_config_Id:
                ptr->SetIWFProtocolActionsConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_show_protocolactions_config_Id:
                ptr->ShowIWFProtocolActionsConfig(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_clear_session_config_Id:
                ptr->ClearSessionContext(port, buf, len, cmdID, InterfaceID);
                break;

            case C_cli_dump_system_info_config_Id:
                ptr->DumpSystemInfo(port, buf, len, cmdID, InterfaceID);
                break;

            default:
                AllResponses cliRsp, *rsp;
                memset(&cliRsp,0,sizeof(cliRsp));
                rsp = &cliRsp;
                rsp->cmd_id = cmdID;
                rsp->ResponseCode = DEFAULT_OPTION;     
                SendResponseToMgmt2((void*)rsp, port);  
                CLOG_CRITICAL("Entered Default option.");
                break;
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);

}
int CmnMgmtMess::FetchConfiguration()     
{     
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    string componentName = "CLI";
    LoggerInfo logInfo;
    ErrorDetails errResp;
    int logLevel=0;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    if(m_cmapi->GetLogConfig(componentName, true ,logInfo, errResp) == CMAPI_SUCCESS)
    {
        int numOfCmp = logInfo.loggerconfig_size();
        CLOG_INFO("num Of Components = %d ",numOfCmp);
        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
        if(numOfCmp != 0)
        {    
            for(int curCmp = 0 ; curCmp < numOfCmp ; curCmp++)
            {    
                LoggerConf curLogConfig = logInfo.loggerconfig(curCmp);
                logLevel = curLogConfig.level();
                componentName = curLogConfig.componentname();
                if(logLevel == LoggerConf_LogLevel_DEBUG_LOG)
                {    
                    this->GetLogger().SetLevel(Logger::EACC_LOG_DEBUG,true);
                }    
                else if(logLevel == LoggerConf_LogLevel_INFO_LOG)
                {    
                    this->GetLogger().SetLevel(Logger::EACC_LOG_INFO,true);
                }    
                else if(logLevel == LoggerConf_LogLevel_ERROR_LOG)
                {    
                    this->GetLogger().SetLevel(Logger::EACC_LOG_ERROR,true);
                }    
                else if(logLevel == LoggerConf_LogLevel_NOTICE_LOG)
                {
                    this->GetLogger().SetLevel(Logger::EACC_LOG_NOTICE,true);
                }
                else if(logLevel == LoggerConf_LogLevel_WARNING_LOG)
                {
                    this->GetLogger().SetLevel(Logger::EACC_LOG_WARNING,true);
                }
                else if(logLevel == LoggerConf_LogLevel_CRITICAL_LOG)
                {
                    this->GetLogger().SetLevel(Logger::EACC_LOG_CRITICAL,true);
                }
                CLOG_DEBUG("Successfully set the CLI Log-Level.");
            }
        }
        else
        {
            CLOG_ERROR("Error in fetching the Logging Configuration for CLI ");
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            if(errResp.IsInitialized())
            {
                formErrorMessage(errResp,rsp);
                CLOG_ERROR("Error Message received is %s",rsp->payload);
            }
        }
    }
    else {
        CLOG_ERROR("Error in fetching the Logging Configurations for CLI ");
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        if(errResp.IsInitialized())
        {
            formErrorMessage(errResp,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return 0;
}

int CmnMgmtMess::HandleCmgrErrorResponse(AllResponses resp)
{

    SetReqCookie* cookie = reinterpret_cast <SetReqCookie*> (MeSS::Handle().m_cookie);
    resp.cmd_id = reinterpret_cast <SetConfigReq*>(cookie->req)->cmd_id;
    if(resp.ResponseCode == DRE_DB_FAIL)
    {
        resp.ResponseCode = CMGR_CONFIG_ERROR;
    }
    SendResponseToMgmt2(reinterpret_cast <void*>(&resp), cookie->clientInfo.udpPort);
    free_z(cookie->req);
    free_z(cookie);
    return 0;
}
int CmnMgmtMess::HandleDreErrorResponse()
{
    AllResponses resp;
    memset(&resp,0,sizeof(AllResponses));
    SetReqCookie* cookie = reinterpret_cast <SetReqCookie*> (MeSS::Handle().m_cookie);
    resp.cmd_id = reinterpret_cast <SetConfigReq*>(cookie->req)->cmd_id;
    resp.ResponseCode = DRE_CONFIG_ERROR;
    SendResponseToMgmt2(reinterpret_cast <void*>(&resp), cookie->clientInfo.udpPort);
    free_z(cookie->req);
    free_z(cookie);
    return 0;
}

void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...)
{
    va_list vaList;
    char message[1024];
    char func[1024];
    snprintf(func,1024," %s : %d ",funName,lineNo);
    va_start(vaList,dataString);
    vsnprintf(message, 1024, dataString, vaList);
    va_end(vaList);
    strncat(func,message,strlen(message));
    //CLOG_DEBUG(func);
    if(loglevel == CLI_DEBUG)
        CLOG_DEBUG(func);
    else if(loglevel == CLI_INFO)
        CLOG_INFO(func);
    else if(loglevel == CLI_NOTICE)
        CLOG_NOTICE(func);
    else if(loglevel == CLI_WARNING)
        CLOG_WARNING(func);
    else if(loglevel == CLI_FATAL)
        CLOG_FATAL(func);
    else if(loglevel == CLI_CRITICAL)
        CLOG_CRITICAL(func);
    else
        CLOG_ERROR(func);
}

void* ConfigFetchThread(void *args)
{
    CmnMgmtMess *cmnMessobj = CmnMgmtMess::CreateObj();

    try {

        cmnMessobj->m_cmgrAvlble.wait();

        // Fetch the configuration Logging Configuration from cmgr
        if(!messThreadExit)
        {
            cmnMessobj->FetchConfiguration();
            //Update AM of Self Status Change
            cmnMessobj->UpdateComponentSelfStatus(COMPONENT_STATUS_INITIALIZED); 

        }
    }
    catch(eAccelero::SyncException &e)
    {
        std::cerr << "ConfigFetchThread: SyncException caught - " << e.what() << std::endl;
    }
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

void* MeSSThread(void *args)
{
    messThreadExit=false;
    CliArgs *cmdLine = (CliArgs*)args;
    int argc = 0;
    char **argv = NULL;//[] = {(char*)"dummy",(char*)"-l",(char*)"6",(char*)"-i",(char*)"10"};

    if (cmdLine)
    {
        argc = cmdLine->argc;
        argv = cmdLine->argv;
    }
    CmnMgmtMess *app = NULL;

    try
    {
	
        app = CmnMgmtMess::CreateObj();

        app->Init(argc, argv);
        int ret = 0;
#if DRE
        ret = populateErrorMap("/opt/diametriq/dre/config/MessageResources.properties");
#else
        ret = populateErrorMap("/opt/diametriq/iwf/config/MessageResources.properties");
#endif
        //TODO: Think if it is correct to exit or continue.
        if(ret < 0)
            exit(1);

        CLOG_NOTICE("Application initialized");

        //If CLI is already started with "-i 0" option we dont have to wait 
        //for status reset from AM, set ms_cliInitialized to true
        for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-i"))
            {
                if (argv[i+1] && (atoi(argv[i+1]) == 0) )
                {
                    CmnMgmtMess::ms_cliInitialized = true;
                }
                break; //dont have to continue
            }
        }

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

    //CLOG_NOTICE("Application exiting");

    //CmnMgmtMess *cmnMessobj = CmnMgmtMess::CreateObj();
    //cmnMessobj->m_cmgrAvlble.signal();

    //if (app) delete app;
    //CmnMgmtMess::m_terminateMess.wait();
    eAccelero::Logger::currLogger = NULL;
    
    return 0;
}

void TerminateCmnMgmtMeSS()
{

    CmnMgmtMess *app =NULL;
    app = CmnMgmtMess::CreateObj();
    messThreadExit=true;
    app->m_cmgrAvlble.signal();
    if(app)
    {
	delete app;
    }


}

void InitializeCmnMgntMeSS(void *args)
{
    CliArgs *cmdLine = (CliArgs*)args;
    int argc = 0;
    char **argv = NULL;//[] = {(char*)"dummy",(char*)"-l",(char*)"6",(char*)"-i",(char*)"10"};

    if (cmdLine)
    {
        argc = cmdLine->argc;
        argv = cmdLine->argv;
    }
    CmnMgmtMess *app = NULL;

    try
    {
        app = CmnMgmtMess::CreateObj();

        app->Init(argc, argv);
        int ret = 0;
#if DRE
        ret = populateErrorMap("/opt/diametriq/dre/config/MessageResources.properties");
#else
        ret = populateErrorMap("/opt/diametriq/iwf/config/MessageResources.properties");
#endif
        //TODO: Think if it is correct to exit or continue.
        if(ret < 0)
            exit(1);

        CLOG_NOTICE("Application initialized");

        //If CLI is already started with "-i 0" option we dont have to wait 
        //for status reset from AM, set ms_cliInitialized to true
        for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-i"))
            {
                if (argv[i+1] && (atoi(argv[i+1]) == 0) )
                {
                    CmnMgmtMess::ms_cliInitialized = true;
                }
                break; //dont have to continue
            }
        }

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

}
