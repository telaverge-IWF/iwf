/*********************************-*-CPP-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#include "iwf.h"
#include "ssg_trace.h"
#include <ssg_configuration.h>
#include "iwf_transport_controller.h"

#include <its++.h>
#include <its_timers.h>
#include <its_ual.h>
#include <its_redundancy.h>
#include <mtp3_intern.h>

#include <ss7_mgmt.h>

#include <dia_trace.h>
#include <dia_config.h>
#include <dia_frame.h>
#include <dia_module.h>
#include "dia_tracer.h"
#include "Logger.h"
#include "ual_config_mgnt.h"
#include "IWFStateReplication.h"
#include "iwf_prot_utils.h"

#define IWF_MAX_RETRY_COUNT 3
#define MAX_RETRY_COUNT 3

using namespace eAccelero;

IwfController* IwfController::m_self = NULL;
ThreadSharedData<int> IwfController::cmgrAvlblFlag;
std::vector<uint32_t> IwfController::m_freeList;
ITS_Mutex IwfController::m_freeListGuard(0);
bool IwfController::m_isNodeActive = false;
bool IwfController::initialized = false;
extern bool gisShutdownInProgress;

void IwfCleanUP(void)
{
    iwf::IWFTransportController::SetExit(true);
    iwf::IWFTransportController::SetTransportStatus(IWF_DEACTIVATE_TRANSPORTS);
}

IwfController::IwfController(int &argc, const char **&argv, const char* confFileName):
    m_iwfMeSS(argc,argv),
    m_logger("IWF_CONTROLLER"),
    m_config(confFileName,new IwfCAhoCorasickImpl()),
    m_syslogChannel("IWF", (LOG_PID), LOG_LOCAL6),
    m_isBulkFetchSuccess(false)
{
    m_bulkFetchMaxRetry = 0;
    m_logger.SetLogChannel(&m_syslogChannel);
    m_logger.SetLevel(eAccelero::Logger::EACC_LOG_DEBUG);
    this->InitTrace();

    ScopedLogger scopedLogger(this->GetLogger());
    atexit(IwfCleanUP);
    messThread = new eAccelero::Thread("MeSS Thread");
    messThread->Start((eAccelero::Runnable*)&m_iwfMeSS);

    m_iwfMeSS.m_cond.wait();

    //Create the IWFTransportControl thread and start the same
    transportControlThread = new eAccelero::Thread("Transport Control Thread");
    transportControlThread->Start((eAccelero::Runnable*)&m_transport);

    for (unsigned i = 0; i < MaxTranslators; i++)
    {
        m_translators[i] = NULL;
    }

    m_IwfCmapiConfigObj = new IWFConfigFetch();
    m_IwfCmapiConfigObj->UpdateCurrentInstanceId(MeSS::MeSSObj().Self().instance);
    m_IwfCmapiConfigObj->InitializeLibrary();

    m_cmapiConfigObj = new CMAPIConfig();
    m_cmapiConfigObj->UpdateCurrentInstanceId(MeSS::MeSSObj().Self().instance);
    m_cmapiConfigObj->InitializeLibrary();
    /* As per dre how to set current instance id */
    m_iwfAlarms = new::IwfAlarms(instanceId, eAccelero::COMP_IWF_APP);
    
    m_initializationFlagsSet = false;
    m_becameActive = false;
    m_becameStandby = false;
    m_isBulkFetchTimerRunning = false;

    /*To Run IWF in debug Mode */
    int i=1;
    for(; i < argc ; i++)
    {
        if(strcmp(argv[i], "-debugMode") == 0)
        {
            CLOG_DEBUG("Running IWF in Debug Mode");
            cout << "Running IWF in Debug Mode" << endl;
            //Simulate as if Config Manager was initialized.
            //It is assumed that when IWF is run with this argument
            //then configManager is already running.
            SetUpdateFromAvaMgr(COMP_CONFIG_MANAGER,COMPONENT_STATUS_INITIALIZED);
        }

        if(strcmp(argv[i], "-m" ) == 0)
        {    
            if(strcmp(argv[i+1], "4" )== 0)
            {    

                //if the mode is ACTIVE-HOT-STANDBY then enable replication
                m_iwfMeSS.EnableReplication();
            }    
            else 
            {    
                m_iwfMeSS.DisableReplication();
            }    
        }
    }
}

IwfController::~IwfController()
{
    for (unsigned i = 0; i < MaxTranslators; i++)
    {
        if (m_translators[i])
        {
            delete m_translators[i];
            m_translators[i] = NULL;
        }
    }
    
    ComponentBase::Instance().GetDispatcher()->Stop();
    if(messThread)
    {
        delete messThread;
        messThread = NULL;
    }

    if(m_IwfCmapiConfigObj)
    {
        delete m_IwfCmapiConfigObj;
        m_IwfCmapiConfigObj = NULL;
    }

    if(m_cmapiConfigObj)
    {
        delete m_cmapiConfigObj;
        m_cmapiConfigObj = NULL;
    }

    if(m_iwfAlarms != NULL)
    {
        delete m_iwfAlarms;
        m_iwfAlarms = NULL;
    }
}

void IwfController::Init(int &argc, const char **&argv, const char *configFile)
{
    ITS_THROW_ASSERT(!m_self);
    m_self = new IwfController(argc, argv, configFile);
}

int IwfController::RegisterTranslator(
        const std::string& tranStr,
        IwfTranslator* obj)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::RegisterTranslator");
    TranslStrMap::iterator it = m_translStrMap.find(tranStr);
    if (it != m_translStrMap.end())
    {
        DLOG_ERROR("Duplicate Protocol Translator %s, not registering.",
                    tranStr.c_str());
        return -1;
    }

    // Find a free slot
    unsigned i;
    for (i = 0; i < MaxTranslators; i++)
    {
        if (m_translators[i] == NULL)
        {
            break;
        }
    }
    if (i == MaxTranslators)
    {
        DLOG_ERROR("Maximum translators reached. not registering %s", 
                    tranStr.c_str());
        return -1;
    }

    m_translStrMap[tranStr] = i;
    DLOG_DEBUG("IwfController::RegisterTranslator:: Translator String is %s, Id is %d",
                tranStr.c_str(),
                i);
    m_translators[i] = obj;
    obj->Id(i);

    return i;
}

int IwfController::InitDiameterStack(bool isActive)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("InitDiameterStack for IWF application");
    /* Fetch the diameter configuration from DB and
     * Diameter Stack Initialization Access the diameter 
     * stack configuration details via the DiaConfig 
     * Singleton Object Pointer
     */
    DiaConfig *cfg = DiaConfig::GetDiaConfig();
    //DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    StackConfigResponse stackCfgResp;

    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    bool retVal=ITS_SUCCESS;
    uint16_t retry_count = 1;

    if(m_iwfMeSS.isReplicationEnabled())
    {
        DLOG_DEBUG("INITIALIZE CB AND ENABLE REPL");

        const char* configPath = getenv("IWF_ROOT");
        std::string replicationConfigFile(configPath);
        replicationConfigFile.append(IWF_REPLICATION_CONFIG);
        retVal = iwf::IWFStateReplication::Initialize(replicationConfigFile,&(ReplStatusCbk));
        if(retVal != REPL_CLINT_INIT_FAILED)
        {
            IwfController::Instance().EnableReplication();
            // Start the periodic bulk fetch on STBY node.
            if (!isActive)
            {
                IwfController::Instance().StartBulkFetchTimer();
            }
        }
        else
        {
            m_iwfMeSS.DisableReplication();
            DLOG_ERROR("Initialization of Replication Client failed!");
        }

    }
    else
    {
        DLOG_DEBUG("DONT INITIALIZE CB");
    }

    if (diaFrame)
    {
        if (cfg)
        {
            /* Set the XML configuration file that contains the
             * Base Diameter Protocol Specific Configuration
             *
             * Refer to the AppOption:DiameterConfigFile in the
             * ../bin/demo.xml.server and ../bin/demo.xml.client
             * The Configuration object returns the name maintained
             * in this XML AppOption
             */
            diaFrame->SetConfigFile(cfg->GetConfigFile());

            /* Apply Diameter Stack Configuration here
             * Fetch from Database, thru CONFIG MANAGER
             * Config fetch retry in case of failure since
             * there is a possiblility that CMGR is switching 
             * from Standby to Active and hence either request 
             * might be lost and if DRE is switching after sending
             * request then the response might be lost.
             */
            do {

                if (CMAPI_SUCCESS == m_cmapiConfigObj->GetStackConfiguration(true,&stackCfgResp))
                {
                    if (stackCfgResp.has_stackconfig())
                    {
                        ApplyStackConfigurations(stackCfgResp.stackconfig());
                        break;
                    }
                }
                else
                {
                    DLOG_DEBUG("Retrying for Stack configuration");
                    retry_count++;
                }
            }while(retry_count <= MAX_RETRY_COUNT);                    

            if (retry_count >= MAX_RETRY_COUNT)
            {
                DLOG_ERROR("Failed to fetch IWF configuration from Database for max retries...hence exiting!!!!");
                //Exit point 1
                _exit(0);
            }
            //Reset Retry Count.
            retry_count = 1;
            //Retry fetching for configuration for 3 times before giving up.
            StackConfiguration StackCfg = stackCfgResp.stackconfig(); 
            do {
                //if (PopulateConfig(DIA_CONFIG_LOCALHOST | DIA_CONFIG_PEER | DIA_CONFIG_REALM ,StackCfg.lhost()) != ITS_SUCCESS)
                if (PopulateConfig(DIA_CONFIG_PEER | DIA_CONFIG_REALM ,StackCfg.lhost()) != ITS_SUCCESS)
                {
                    DLOG_DEBUG("Failed to fetch DRE configuration from Database....retrying!!!!");
                }
                else
                {
                    break;
                }
                retry_count++;
            }while(retry_count <= MAX_RETRY_COUNT);                    

            if (retry_count >= MAX_RETRY_COUNT)
            {
                DLOG_ERROR("Failed to fetch DRE configuration from Database for max retries...hence exiting!!!!");
                //Exit point 2
                _exit(0);
            }
            //Reset Retry Count.
            retry_count = 1;

            //if( diaFrame->Initialize(DRE_DEACTIVATE_TRANSPORTS) != ITS_SUCCESS)
            if( diaFrame->Initialize(isActive) != ITS_SUCCESS)
            {
                DLOG_ERROR("DiaFrmae Initialisation Failed ");
                retVal = (!ITS_SUCCESS);
            }

            diaFrame->RegisterApplication(BASE_INTERFACE_APP_ID);

#if 0
            //Fetch tracing configuration from DB.
            if(PopulateTracingConfig() != ITS_SUCCESS)
            {
                DLOG_DEBUG("Failed to set Tracing Configuration form Databases");
            }
            else
            {
                DLOG_DEBUG("Fetched tracing config successfully");
            }


            
            if(PopulateStaticRoutingConfig() != ITS_SUCCESS)
            {
                DLOG_ERROR("Failed to set static routing Configuration form Databases");
            }
            else
            {
                DLOG_DEBUG("Fetched static routing config successfully");
            }


            if(m_config.m_enableASF)
            {
                ASFConfigResp ASFCfgData;
                //Fetch ASF configuration from DB.
                if (m_cmapiConfigObj->GetASFConfiguration(true,&ASFCfgData) == CMAPI_SUCCESS)
                {
                    CMAPIAsfConfig::PopulateASFConfig(&ASFCfgData);
                }
                else
                {
                    //Not exiting since this is an optional feature.
                    DLOG_ERROR("Error in fetching ASF Configuration");
                }
            }
        //Fetch ERLBF configuration from DB.
        if(m_erlbfInstance->m_peerGroupTable->FetchPeerGroupConfig() != ITS_SUCCESS)
        {
            //Not exiting since this is an optional feature.
            DLOG_ERROR("Failed to send the request for ERLBF config fetch.");
        }
        else
        {
            DLOG_DEBUG("Successfully sent request for ERLBF config fetch");
        }
#endif
            /*
             * Now Initialize the Base diameter stack.
             */

#if 0
            DiaMsgRouter::OverrideRequestRouting(::RoutingFunc, this);
#endif
            //Fetch logging configuration from DB.
            if(PopulateLoggerConfig() != ITS_SUCCESS)
            {
                DLOG_ERROR("Failed to fetch Logger Configuration form Databases");
            }

        }
    }

    return retVal;
}

void IwfController::ApplyStackConfigurations(const StackConfiguration& refStackConfig)
{

    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("Applying Stack Configurations");
    //ITSDiaConfig::SecurityConfig& secConf = itsDiaConfig.GetSecurityConfig(); 

    if (refStackConfig.has_gconfig())
    {
        GeneralConfig gnConfig = refStackConfig.gconfig();
        if (gnConfig.has_enablepeeripcheck() && gnConfig.enablepeeripcheck())
        {
            itsDiaConfig.EnablePeerIpCheck();
        }
#if 0
        if (gnConfig.has_ispredictiveloopavdrequired() 
                && gnConfig.ispredictiveloopavdrequired())
        {
            itsDiaConfig.setPredectiveLoopAvoidanceEnable(gnConfig.ispredictiveloopavdrequired());
        } 
        if (gnConfig.has_issnaptrsupported() 
                && gnConfig.issnaptrsupported())
        {
            itsDiaConfig.setIsSnaptrSupportedFlag(gnConfig.issnaptrsupported());
        } 
#endif
    }

#if 0
    if (refStackConfig.has_tconfig())
    {
        TLSConfig tlsConfig = refStackConfig.tconfig();
        if (tlsConfig.has_enableidverification())
        {
            if (tlsConfig.enableidverification())
                secConf.SetIdentityVerifyEnabled();
            else
                secConf.SetIdentityVerifyDisabled();
        }

        if (tlsConfig.has_enablecrlverification())
        {
            secConf.SetCrlVerify(tlsConfig.enablecrlverification());
        }
    }
#endif

    if (refStackConfig.has_sctp())
    {
        SctpProtocol sctpConfig = refStackConfig.sctp();
        if (sctpConfig.has_heartbeatenable())
            itsDiaConfig.GetStreamSocketConfig()->hbOn = sctpConfig.heartbeatenable(); 
        if (sctpConfig.has_hearbeattimeout())
            itsDiaConfig.GetStreamSocketConfig()->hbTimeout = sctpConfig.hearbeattimeout();
        if (sctpConfig.has_initialtimeout())
            itsDiaConfig.GetStreamSocketConfig()->initTimeout = sctpConfig.initialtimeout();
        if (sctpConfig.has_maximumattempts())
            itsDiaConfig.GetStreamSocketConfig()->maxAttempts = sctpConfig.maximumattempts();
        if (sctpConfig.has_rtomaximum())
            itsDiaConfig.GetStreamSocketConfig()->rtoMax = sctpConfig.rtomaximum();
        if (sctpConfig.has_rtominimum())
            itsDiaConfig.GetStreamSocketConfig()->rtoMin = sctpConfig.rtominimum();
        if (sctpConfig.has_rtoinitial())
            itsDiaConfig.GetStreamSocketConfig()->rtoInitial = sctpConfig.rtoinitial();
    }
#if 0
    if (refStackConfig.has_tlsciphers())
    {
        TLSCipherConfigs tlsCipCfgs = refStackConfig.tlsciphers();
        for (idx = 0; idx < tlsCipCfgs.tlsciphers_size(); idx++)
        {
            TLSCipherConfig tlscCfg = tlsCipCfgs.tlsciphers(idx);
            if (tlscCfg.has_enableciphersuite() && tlscCfg.enableciphersuite())
            {
                DIA_CIPHER_SUITE CipherSuitID = (DIA_CIPHER_SUITE) TLS_NO_CIPHER_SUITE;
                string CSuitName = tlscCfg.ciphersuitename();
                if (CSuitName.compare("TLS_RSA_WITH_RC4_128_MD5") == 0)
                    CipherSuitID = TLS_RSA_WITH_RC4_128_MD5;
                else if (CSuitName.compare("TLS_RSA_WITH_RC4_128_SHA") == 0)
                    CipherSuitID = TLS_RSA_WITH_RC4_128_SHA;
                else if (CSuitName.compare("TLS_RSA_WITH_3DES_EDE_CBC_SHA") == 0)
                    CipherSuitID = TLS_RSA_WITH_3DES_EDE_CBC_SHA;
                else if (CSuitName.compare("TLS_RSA_WITH_AES_128_CBC_SHA") == 0)
                    CipherSuitID = TLS_RSA_WITH_AES_128_CBC_SHA;
                else if (CSuitName.compare("TLS_RSA_WITH_NULL_MD5") == 0)
                    CipherSuitID = TLS_RSA_WITH_NULL_MD5;
                else if (CSuitName.compare("TLS_RSA_WITH_NULL_SHA") == 0)
                    CipherSuitID = TLS_RSA_WITH_NULL_SHA;
                else if (CSuitName.compare("TLS_RSA_WITH_DES_CBC_SHA") == 0)
                    CipherSuitID = TLS_RSA_WITH_DES_CBC_SHA;
                else if (CSuitName.compare("TLS_RSA_WITH_AES_256_CBC_SHA") == 0)
                    CipherSuitID = TLS_RSA_WITH_AES_256_CBC_SHA;

                secConf.SetCipherSuite((DIA_CIPHER_SUITE) CipherSuitID);
                secConf.PopulateCipherList(CSuitName);
            }
        } 
    }
    if (refStackConfig.has_cacrl())
    {
        CACRLs cacrlCfg = refStackConfig.cacrl();
        for (idx = 0; idx < cacrlCfg.tcacfg_size(); idx++)
        {
            its::CertificateAuthority *cauObj = new its::CertificateAuthority;   
            cauObj->SetCertType(its::CertificateAuthority::CERT_TYPE_PEM);

            TrustedCAConfiguration tCACfg = cacrlCfg.tcacfg(idx);
            if (tCACfg.has_cafile())
            {
                cauObj->SetCertificateFileName((string&) tCACfg.cafile());
            }
            secConf.AddTrustedCA(cauObj);
            if (tCACfg.has_crlfile())
            {
                CRL crl;
                crl.SetCRLFileName((string&) tCACfg.crlfile());
                cauObj->SetCRL(crl);
            }
        }

    }
#endif
}

int IwfController::PopulateConfig(int configToFetch, const LocalHost& lHostCfg)
{

    ScopedLogger scopedLogger(this->GetLogger());
    DRECfgResp dreCfgResp;
    //StackConfigResponse stackCfgResp;
    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();
    DLOG_DEBUG("Getting Diameter configuration from database....\n");

    LocalHost *localHostConfig = (LocalHost *) &lHostCfg;
    // Auth session timers 
    ITS_SERIAL authSessionTimer = 600;
    ITS_SERIAL authSessionLifeTime = 400;
    ITS_SERIAL authSessionGracePeriod = 200;
    // Accounting session timers 
    ITS_SERIAL acctSessionIntermiInterval = 30;
    ITS_SERIAL acctSessionTimeOut = 30;
    DIA_TRANS_TYPE transType = ITS_DIA_T_SCTP;
    ITS_USHORT localPort = 0;
    ITS_USHORT TLSPort = 0;

    if (localHostConfig->has_localhostname() &&
            localHostConfig->has_realmname())
    {
        if (ITS_SUCCESS != diaMgmt->SetLocalHostInfo(
                    localHostConfig->localhostname().c_str(),
                    localHostConfig->realmname().c_str()))
        {
            DLOG_ERROR("Failed to set localhost info: %s:%s",
                    localHostConfig->localhostname().c_str(),
                    localHostConfig->realmname().c_str());
        }
        else
        {
            DLOG_DEBUG("Set local host info: %s:%s",
                    localHostConfig->localhostname().c_str(),
                    localHostConfig->realmname().c_str());
        } 
    }

    for(int i = 0;i < localHostConfig->transports_size();i++)
    {
        LHTransport* localTransport = localHostConfig->mutable_transports(i);
        const char *multiHomeIpAddrs[4] = {NULL};
        const char *publicServerIpAddr = NULL;
        int noIPs = 0;
        if (localTransport->has_transporttype())
        {
            if (strcmp(localTransport->transporttype().c_str(), "TCP") == 0)
            {
                transType = ITS_DIA_T_TCP;
            }
            else
            {
                transType = ITS_DIA_T_SCTP;
            }
        }

        if (localTransport->has_port())
        {
            localPort = localTransport->port();
        }
#if 0
        if (localTransport->has_secureport())
        {
            TLSPort = localTransport->secureport();
        }
#endif
        if(localTransport->has_publicserveripaddr())
        {
            publicServerIpAddr = localTransport->publicserveripaddr().c_str();
            DLOG_DEBUG("Public server ip address is = %s",publicServerIpAddr);
        }
        if(!localTransport->has_hostipaddr())
        {
            DLOG_ERROR("Does not contain ip address for local config");
            continue;
        }

        if((localTransport->secondaryipaddr_size()>0 && localTransport->secondaryipaddr_size() <4)
                && transType == ITS_DIA_T_SCTP )
        {
            for(int i = 0;i < localTransport->secondaryipaddr_size();i++)
            {
                std::string * secondaryIpAddrs = localTransport->mutable_secondaryipaddr(i);
                DLOG_DEBUG("Secondary ip addrs is %s for IP %s",
                          secondaryIpAddrs->c_str(),localTransport->hostipaddr().c_str());

                multiHomeIpAddrs[i]= strdup(secondaryIpAddrs->c_str());
                noIPs++;
            }
        }

        if (ITS_SUCCESS != diaMgmt->SetLocalTransportInfo(
                    localTransport->hostipaddr().c_str(),
                    transType,
                    localPort,multiHomeIpAddrs,noIPs,publicServerIpAddr,TLSPort))
        {
            DLOG_ERROR("Failed to set local tpt info: %s:%d:%d:%d",
                    localTransport->hostipaddr().c_str(),
                    transType,
                    localPort,TLSPort);
        }
        else
        {
            DLOG_DEBUG("Set local tpt info: %s:%d:%d:%d",
                    localTransport->hostipaddr().c_str(),
                    transType,
                    localPort,TLSPort);
        }
    }
    //Get the auth session timer configuration
    if (localHostConfig->has_authsessiontimeout())
    {
        authSessionTimer = localHostConfig->authsessiontimeout();
    }

    //Get the auth session life timer configuration
    if (localHostConfig->has_authsessionlifetime())
    {
        authSessionLifeTime = localHostConfig->authsessionlifetime();
    }

    //Get the auth session grace period configuration
    if (localHostConfig->has_authsessiongraceperiod())
    {
        authSessionGracePeriod = localHostConfig->authsessiongraceperiod();
    }

    if (ITS_SUCCESS != diaMgmt->SetAuthSessionTimers(
                authSessionLifeTime,
                authSessionGracePeriod,
                authSessionTimer))
    {
        DLOG_ERROR("Failed to set auth session timers: %d:%d:%d",
                authSessionLifeTime,
                authSessionGracePeriod,
                authSessionTimer);
    }
    else
    {
        DLOG_DEBUG("Auth session timers set: %d:%d:%d",
                authSessionLifeTime,
                authSessionGracePeriod,
                authSessionTimer);
    }

    //Get the Accounting session interim timer configuration
    if (localHostConfig->has_acctsessioninteriminterval())
    {
        acctSessionIntermiInterval = localHostConfig->acctsessioninteriminterval();
    }

    //Get the accounting session real time configuration
    //if (localHostConfig->has_acctsessionrealtime())
    //{
    //    acctSessionRealTime = localHostConfig->acctsessionrealtime();
    //}

    //Get the acconting session timeout configuration
    if (localHostConfig->has_acctsessiontimeout())
    {
        acctSessionTimeOut = localHostConfig->acctsessiontimeout();
    }

    if (ITS_SUCCESS != diaMgmt->SetAcctSessionTimers(
                acctSessionIntermiInterval,
                acctSessionTimeOut))
    {
        DLOG_ERROR("Failed to set accounting session timers: %d:%d",
                acctSessionIntermiInterval,
                acctSessionTimeOut);
    }
    else
    {
        DLOG_DEBUG("Accounting session timers set: %d:%d",
                acctSessionIntermiInterval,
                acctSessionTimeOut);
    }


    if (CMAPI_SUCCESS == m_cmapiConfigObj->GetDreConfiguration(true,&dreCfgResp) &&
            dreCfgResp.has_respcode() && CMAPI_SUCCESS == dreCfgResp.respcode())
    {

        if ( configToFetch & DIA_CONFIG_PEER )
        {
            //Get the peer configuration
            if (dreCfgResp.has_peers())
            {
                PeersConfig *peers = dreCfgResp.mutable_peers();
                int numPeers = peers->peers_size();
                std::list<ALT_PEER_INFO> altPeerList;
                altPeerList.clear();

                // Get each of the peer configuration from the peers
                for (int i = 0; i < numPeers; i++)
                {
                    PEER_INFO pInfo;
                    const char *multiHomeIpAddrs[4] = {NULL};
                    int noIPs = 0;

                    memset(&pInfo, 0, sizeof(PEER_INFO));
                    pInfo.status=true;
                    PeerConfig *peerConfig = peers->mutable_peers(i);

                    pInfo.peerName = peerConfig->peerhostname().c_str();
                    pInfo.realmName = peerConfig->realm().c_str();
                    pInfo.ipAddr = peerConfig->serveripaddr().c_str();
                    pInfo.port = peerConfig->port();
                    pInfo.tlsEnabled = peerConfig->tlsenabled();
                    const char* trType = peerConfig->transporttype().c_str();
                    if (strcmp(trType, "SCTP") == 0)
                    {
                        pInfo.type = DIA_TRANS_SCTP;
                    }
                    else if (strcmp(trType, "TCP") == 0)
                    {
                        pInfo.type = DIA_TRANS_TCP;
                    }
                    else
                    {
                        pInfo.type = DIA_TRANS_INVALID;
                    }

                    if ( ( peerConfig->has_peerstatus() ) && ( peerConfig->peerstatus() == false))
                    {
                        pInfo.status=peerConfig->peerstatus();
                    }

                    if((peerConfig->secondaryipaddr_size()>0 && peerConfig->secondaryipaddr_size() <4)
                            && pInfo.type == DIA_TRANS_SCTP )
                    {
                        for(int i = 0;i < peerConfig->secondaryipaddr_size();i++)
                        {
                            std::string * secondaryIpAddrs = peerConfig->mutable_secondaryipaddr(i);
                            DLOG_DEBUG("Secondary ip addrs is %s for IP %s",
                            secondaryIpAddrs->c_str(),peerConfig->serveripaddr().c_str());

                            multiHomeIpAddrs[i]= strdup(secondaryIpAddrs->c_str());
                            noIPs++;
                        }
                        pInfo.noIPs=noIPs;
                        pInfo.multiHomeipaddrs=multiHomeIpAddrs;
                    }
                    /* enabling PendingQ by default*/
                    pInfo.isRetransmissionEnabled = true;
#if 0
                    if (peerConfig->has_secureport())
                    {
                        pInfo.securePort = peerConfig->secureport();
                    }
#endif
                    if (ITS_SUCCESS != diaMgmt->AddPeer(&pInfo))
                    {
                        DLOG_CRITICAL("Failed to add peer: %s:%s",
                                pInfo.realmName,
                                pInfo.peerName);
                        continue;
                    }
                    else
                    {
                        DLOG_DEBUG("Added peer: %s:%s",
                                pInfo.realmName,
                                pInfo.peerName);
                    }

                    // Check if we have dictionary IDs and add them to the peer
                    if (peerConfig->dictionaryname_size())
                    {
                        std::string pluginpath;
                        if(!itsDiaConfig.getpluginpathname())
                        {
                            pluginpath = "/opt/diametriq/dre/lib/";
                        }
                        else
                        {
                            pluginpath = itsDiaConfig.getpluginpathname();
                        }

                        eAccelero::PluginLoader::SetPluginDir(pluginpath);
                        string dict_names[MAX_DICT_IDS_PER_PEER];
                        APPLICATION_TYPE appType[MAX_DICT_IDS_PER_PEER];
                        int dict_count = peerConfig->dictionaryname_size();

                        for (int dict_idx = 0; (dict_idx < dict_count) && (dict_count <= MAX_DICT_IDS_PER_PEER); dict_idx++)
                        {    
                            dict_names[dict_idx] = peerConfig->dictionaryname(dict_idx);
                            appType[dict_idx]    = (APPLICATION_TYPE)1;//(peerConfig->typeofapp(dict_idx));
                        }

                        // Add the received dictionary Ids to the peer
                        if (ITS_SUCCESS != diaMgmt->AssociateDictToPeer(&pInfo,
                                    dict_count, dict_names,appType))
                        {
                            DLOG_ERROR("Failed to add dict Ids to peer: %s",
                                    pInfo.peerName);
                            continue;
                        }
                        else
                        {
                            DLOG_DEBUG("Added dictionary Ids to peer: %s",
                                    pInfo.peerName);
                        }

                    }

                    // Start the peer so that the CER will be sent
                    if (peerConfig->has_peerstatus())
                    {
                        if (peerConfig->peerstatus() == true)
                        {
                            if (ITS_SUCCESS != diaMgmt->StartPeer(pInfo.peerName,
                                        pInfo.realmName))
                            {
                                DLOG_CRITICAL("Failed to start peer: %s:%s",
                                        pInfo.realmName,
                                        pInfo.peerName);
                                continue;
                            }
                            else
                            {
                                DLOG_DEBUG("Started peer: %s:%s",
                                        pInfo.realmName,
                                        pInfo.peerName);
                            }
                        }
                    }

                    if (peerConfig->has_altpeername())
                    {
                        ALT_PEER_INFO altPeer;
                        memset(&altPeer, 0, sizeof(ALT_PEER_INFO));
                        altPeer.peerName = (const char *) (peerConfig->peerhostname()).c_str();
                        altPeer.realmName = (const char *) (peerConfig->realm()).c_str();
                        altPeer.altHost = (const char *) (peerConfig->altpeername()).c_str();
                        altPeer.altRealmName = altPeer.realmName;
                        if (peerConfig->has_failoverenable())
                        {
                            altPeer.isFailoverEnable = (peerConfig->failoverenable()?ITS_TRUE:ITS_FALSE);
                        } else {
                            altPeer.isFailoverEnable = ITS_FALSE;
                        }

                        if (peerConfig->has_failebackenable())
                        {
                            altPeer.isFailbackEnable = (peerConfig->failebackenable()?ITS_TRUE:ITS_FALSE);
                        } else {
                            altPeer.isFailbackEnable = ITS_FALSE;
                        }

                        if (peerConfig->has_ismate())
                        {
                            altPeer.isRedundantMate = peerConfig->ismate();
                        } else {
                            altPeer.isRedundantMate = false;
                        }
                        //store the alternate peers in the list 
                        altPeerList.push_back(altPeer);
                    }

                    // Set the peer timers
                    if (peerConfig->has_tctimerval())
                    {
                        pInfo.retry = peerConfig->tctimerval();
                    }
                    if (peerConfig->has_watchdogtimer())
                    {
                        pInfo.watchdog  = peerConfig->watchdogtimer();
                    }
                    if (peerConfig->has_expirytimer())
                    {
                        pInfo.expiry = peerConfig->expirytimer();
                    }
                    if (ITS_SUCCESS != diaMgmt->SetPeerTimers(&pInfo))
                    {
                        DLOG_CRITICAL("Failed to set timers");
                        continue;
                    }
                    else
                    {
                        DLOG_DEBUG("Set peer timers");
                    }

                    if(peerConfig->has_busyreconnecttimerval() || 
                            peerConfig->has_donotwanttotalktoyoutimerval())
                    {
                        if (peerConfig->has_busyreconnecttimerval())
                            pInfo.busyReconnectTimerVal = peerConfig->busyreconnecttimerval();
                        if (peerConfig->has_donotwanttotalktoyoutimerval())
                            pInfo.doNotWantToTalkYouReconnectTimerVal =
                                peerConfig->donotwanttotalktoyoutimerval();
                        if (diaMgmt->SetPeerDPRCauseReconnectimers(&pInfo) != ITS_SUCCESS)
                        {
                            DLOG_CRITICAL("Failed to set peer DPR cause reconenct timers");
                            continue;
                        }
                        else
                        {
                            DLOG_DEBUG("Set peer DPR cause reconenct timers successful");;
                        }

                    }
                    if(peerConfig->has_issupportdisconnectcause())
                    {
                        if (peerConfig->issupportdisconnectcause())
                            pInfo.isSupportDisconnectCause = peerConfig->issupportdisconnectcause();

                        if (diaMgmt->SetPeerIsDisconnectCauseSupported(&pInfo))
                        {
                            DLOG_CRITICAL("Failed to set IsDisconnectCauseSupported flag for peer");
                            continue;
                        }
                        else
                        {
                            DLOG_DEBUG("Set peer IsDisconnectCauseSupported flag success");
                        }
                    }


                    // Add this peer to the peer status DB
                    TransactionManager::Instance()->AddPeerToPeerStatusDb(peerConfig->peerhostname(), peerConfig->realm());
                } // for each peer
                //Add all ther alternate peers.
                for (std::list<ALT_PEER_INFO>::iterator iter=altPeerList.begin(); iter!=altPeerList.end();iter++)
                {
                    ALT_PEER_INFO altPeer=*iter;
                    if (diaMgmt->AddAlternatePeer(&altPeer) != ITS_SUCCESS)
                    {
                        DLOG_CRITICAL("Failed to add alternate peer: %s:%s",
                                altPeer.peerName,
                                altPeer.altHost);
                    }
                    else
                    {
                        DLOG_DEBUG("Added alternate peer: %s:%s",
                                altPeer.peerName,
                                altPeer.altHost);
                    } 
                }
                altPeerList.clear();

            } // if has_peers()
        } // if DIA_CONFIG_PEER

        if ( configToFetch & DIA_CONFIG_REALM )
        {
            //Get the realm configuration
            if (dreCfgResp.has_realms())
            {
                RealmsConfig *realms = dreCfgResp.mutable_realms();
                int numRealms = realms->realms_size();

                // Get all the realms
                for (int i = 0; i < numRealms; i++)
                {
                    RealmConfig *realmConfig = realms->mutable_realms(i);

                    if (realmConfig->has_realmname())
                    {
                        string localaction = "proxy";
                        if (realmConfig->has_localaction())
                        {
                            localaction = realmConfig->localaction();
                        }
                        if (ITS_SUCCESS != diaMgmt->AddRealm(realmConfig->realmname().c_str(),
                                    localaction.c_str(),
                                    realmConfig->has_enableproxyinfoavp() &&
                                    realmConfig->enableproxyinfoavp()))
                        {
                            DLOG_CRITICAL("Failed to add realm: %s",
                                    realmConfig->realmname().c_str());
                            continue;
                        }
                        else
                        {
                            DLOG_DEBUG("Added realm: %s",
                                    realmConfig->realmname().c_str());
                        }
                        if(realmConfig->has_defaultroute())
                        {
                            diaMgmt->SetDefaultRoute((const char *)(realmConfig->defaultroute()).c_str(),(const char *) (realmConfig->realmname()).c_str());
                        }

                    }
                    else
                    {
                        DLOG_ERROR("Realm name not present");
                        continue;
                    }

                    int numServers = realmConfig->destinfo_size();
                    // Get all the servers within this realm
                    for (int j = 0; j < numServers; j++)
                    {
                        DESTINATION_INFO dInfo;
                        memset(&dInfo, 0, sizeof(DESTINATION_INFO));
                        ::Destination *dest = realmConfig->mutable_destinfo(j);

                        if (!dest->has_peername())
                        {
                            DLOG_ERROR("Destination peer name not present");
                            continue;
                        }
                        dInfo.realmName = realmConfig->realmname().c_str();
                        dInfo.peerName = dest->peername().c_str();
                        dInfo.peerRealm = dest->realmname().c_str();
                        if (dest->has_applicationid())
                            dInfo.applicationId = dest->applicationid();
                        if (dest->has_vendorid())
                            dInfo.vendorId = dest->vendorid();
                        if (dest->has_priority())
                            dInfo.priority = dest->priority();

                        if (ITS_SUCCESS != diaMgmt->AddDestination(&dInfo))
                        {
                            DLOG_ERROR("Failed to add destination: %s:%s",
                                    dInfo.peerRealm, dInfo.peerName);
                            continue;
                        }
                        else
                        {
                            DLOG_DEBUG("Added destination: %s:%s",
                                    dInfo.peerRealm, dInfo.peerName);
                        }

                    } // for each destination

                } // for each realm

            } // if has_realms
        } // if DIA_CONFIG_REALM
    } //if GetDreConfiguration is successful
    else
    {
        return !ITS_SUCCESS;
    }

    return ITS_SUCCESS;

} //PopulateConfig


int IwfController::InitSigTranStack(bool isActive)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::InitSigtranStack Entry");
    uint16_t retry_count = 1;
    int retVal = ITS_SUCCESS;
    IWFCfgResp iwfCfgResp;
    //MTP3_OSS_GetLinkset_CCITT(1, &setInfo, &numLinkset);
    //MTP3_OSS_GetLink_CCITT(1, 0, &info);
    //MTP3_OSS_RemoveLink_CCITT(1, 0);
    //MTP3_OSS_RemoveLinkset_CCITT(1);
    //MTP3_OSS_AddLinkset_CCITT(1, FAMILY_ITU, 2057, 4114, 128);
    //MTP3_OSS_AddLink_CCITT(1, 0, 20002);
    //MTP3_OSS_AddLocalTcapPC_CCITT(2057, 131, 149, 0, 0, FAMILY_ITU);
    //MTP3_OSS_AddLocalSccpPC_CCITT(2057, 131, 0, 0, FAMILY_ITU);
    //MTP3_OSS_AddRoutingKeyroutePC_CCITT(2057, 131, 149, 1, FAMILY_ITU);

    /*UALConfigMgmt *ualConfigMgmt;
      ualConfigMgmt = (UALConfigMgmt*)calloc(1, sizeof(UALConfigMgmt));

      strncpy(ualConfigMgmt->interworkingMode, "ASP", MAX_STRING_SIZE);
      strncpy(ualConfigMgmt->protocolType, "M3UA", MAX_STRING_SIZE);
      strncpy(ualConfigMgmt->ipspExchangeType, "single", MAX_STRING_SIZE);
      strncpy(ualConfigMgmt->ipspType, "client", MAX_STRING_SIZE);
      strncpy(ualConfigMgmt->heartbeatFlag, "off", MAX_STRING_SIZE);
      ualConfigMgmt->protocolVersion = 1;
      ualConfigMgmt->localPointCode = 1;
      ualConfigMgmt->heartbeatInterval = 5;
      ualConfigMgmt->ackTimer = 600;
      ualConfigMgmt->auditTimer = 10;
      ualConfigMgmt->pendingTimer = 2;

      if((retVal = ConfigureUalManagement(ualConfigMgmt)) != ITS_SUCCESS)
      {
      DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: UAL General Configuration failed: Error %d", retVal));
      return retVal;
      }

      UAL_TRAFFIC_TYPE trafficMode;
      trafficMode = UAL_OVERRIDE;

      if((retVal = CreateApplicationServer(1, (char *)"ITU", trafficMode, 128, ITS_YES)) != ITS_SUCCESS)
      {
      DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server: Error %d", retVal));
      return retVal;
      }

      if((retVal = CreateApplicationServerProcess(1, 1)) != ITS_SUCCESS)
      {
      DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server Process: Error %d", retVal));
      return retVal;
      }*/

    //fetch local configuration
    {
        /* has passed through engine initialize function now we have to add local route 
           fetch pointcode, ni,ssn and gt 
           action 
         * sigtran action :-
         * 1. First to create linkset for "0" ITU-mtp3.c requires PC and NI.
         * 2. Local route for tcap. 
         * 3. Local route for sccp.
         * iwf action :- 
         * set gtt and ssn at translator level. */
    }

    {
        /* populate all data associationset,association, remote route as done in CMAPIIWFConfig */
    }
    do { 

        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetSigtranLocalHostConfig(true, &iwfCfgResp))
        {    
            if (iwfCfgResp.has_localhostinfo())
            {   
                PopulateLocalHostConfig(iwfCfgResp.localhostinfo().localhostinfo());
                if(iwfCfgResp.has_ualinfo())
                {
                    PopulateUalGeneralConfig(iwfCfgResp.ualinfo());
                }
                else
                {
                    DLOG_WARNING("UALManager Info not present in Database");
                }
                break;
            }    
        }    
        else 
        {    
            DLOG_WARNING("Retrying for Sigtran Localhost configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch IWF Localhost configuration from Database for max retries...hence exiting!!!!");
        //Exit point 1
        _exit(0);
    }    
    //Reset Retry Count.
    retry_count = 1; 


    do { 

        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetSigtranAssociationSetConfig(true, &iwfCfgResp))
        {    
            if (iwfCfgResp.has_associationsetinfo())
            {    
                PopulateAssociationSetConfig(iwfCfgResp.associationsetinfo());
                break;
            }    
        }    
        else 
        {    
            DLOG_WARNING("Retrying for AssoicationSet configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch IWF AssociationSet configuration from Database for max retries...hence proceeding!!!!");
        //Exit point 1
        //exit(1);
    }    
    //Reset Retry Count.
    retry_count = 1; 

    do { 

        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetSigtranAssociationConfig(true, &iwfCfgResp))
        {    
            if (iwfCfgResp.has_associationinfo())
            {    
                PopulateAssociationConfig(iwfCfgResp.associationinfo());
                break;
            }    
        }    
        else 
        {    
            DLOG_WARNING("Retrying for AssoicationSet configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch IWF Association configuration from Database for max retries...hence proceeding!!!!");
        //Exit point 1
        //exit(1);
    }    
    //Reset Retry Count.
    retry_count = 1; 

    do { 

        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetSigtranRemoteRouteConfig(true, &iwfCfgResp))
        {    
            if (iwfCfgResp.has_remoterouteinfo())
            {    
                PopulateRemoteRouteConfig(iwfCfgResp.remoterouteinfo());
                break;
            }    
        }    
        else 
        {    
            DLOG_WARNING("Retrying for RemoteRoute configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch IWF RemoteRoute configuration from Database for max retries...hence proceeding!!!!");
        //Exit point 1
        //exit(1);
    }    

    //Reset Retry Count.
    retry_count = 1; 

    do {
        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetIwfTranslatorRulesConfig(true, &iwfCfgResp))
        {    
            if (iwfCfgResp.has_translatorrulesinfo())
            {   
                IwfTranslatorRulesConfig transRule = iwfCfgResp.translatorrulesinfo();
                retVal = IwfController::Instance().Config().RoutingRules().SetRoutingRulesConfig(&transRule);
                if( retVal != CMAPI_SUCCESS )
                {
                    DLOG_ERROR(" Error in configuring Translator Rule");
                }
                break;
            }           
        }    
        else 
        {    
            DLOG_WARNING("Retrying for TranslatorRules configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch IWF Translator Rules configuration from Database for max retries...hence proceeding!!!!");
        //Exit point 1
        //  exit(1);
    }    

    //Reset Retry Count.
    retry_count = 1; 
    do {
        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetIwfTranslationDataConfig(true, &iwfCfgResp))
        {    
            if (iwfCfgResp.has_translationdatainfo())
            {   
                IwfTranslationDataConfig transData = iwfCfgResp.translationdatainfo();
                if( iwfCfgResp.translationdatainfo().has_s6atomapinfo() )
                {
                    DLOG_DEBUG("fetched S6aToMap configurations");
                    IwfTranslator* translator = IwfController::Instance().GetTranslator(S6A_TO_MAP_STR);
                    retVal = translator->SetConfig(&transData);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in Configuring S6aToMap translator");
                    }
                }
                if( iwfCfgResp.translationdatainfo().has_maptos6ainfo() )
                {
                    DLOG_DEBUG("fetched MapToS6a configurations");
                    IwfTranslator* translator = IwfController::Instance().GetTranslator(MAP_TO_S6A_STR);
                    retVal = translator->SetConfig(&transData);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in Configuring MapToS6a translator");
                    }
                }
                if( iwfCfgResp.translationdatainfo().has_captoroinfo() )
                {
                    DLOG_DEBUG("fetched CapToRo configurations");
                    IwfTranslator* translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR);
                    retVal = translator->SetConfig(&transData);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in Configuring CapToRo translator");
                    }
                }
                break;
            }   
        }    
        else 
        {    
            DLOG_WARNING("Retrying for TranslatorRules configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch IWF Translator Rules configuration from Database for max retries...hence proceeding!!!!");
        //Exit point 1
        //exit(1);
    }

    //Reset Retry Count.
    retry_count = 1;

    do {
        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetIwfTimersConfig(true, &iwfCfgResp))
        {    
            if( iwfCfgResp.has_timersinfo() )
            {
                IwfTimersConfig timerInfo = iwfCfgResp.timersinfo();
                IwfTranslator* CapToRoTsl = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                IwfTranslator* CapToRo = IwfController::Instance().GetTranslator(CAP_TO_RO_STR);
                IwfTranslator* MapToS6a = IwfController::Instance().GetTranslator(MAP_TO_S6A_STR);
                IwfTranslator* S6aToMap = IwfController::Instance().GetTranslator(S6A_TO_MAP_STR);

                if( CMAPI_SUCCESS == CapToRoTsl->SetTimerConfig(&timerInfo) )
                {
                    DLOG_DEBUG(" Successfully configured timers for TransatelCAPToRo transalator");
                }
                if( CMAPI_SUCCESS == CapToRo->SetTimerConfig(&timerInfo) )
                {
                    DLOG_DEBUG(" Successfully configured timers for CAPToRo translator");
                }
                if( CMAPI_SUCCESS == MapToS6a->SetTimerConfig(&timerInfo) )
                {
                    DLOG_DEBUG(" Successfully configured timers for MapToS6a translator");
                }
                if( CMAPI_SUCCESS == S6aToMap->SetTimerConfig(&timerInfo) )
                {
                    DLOG_DEBUG(" Successfully configured timers for S6aToMap translator");
                }
                break;
            }
            else
            {
                DLOG_ERROR("Translator timers not configured, no data returned from Database");
            }
        }    
        else 
        {    
            DLOG_WARNING("Retrying for Translators Timer configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch Translator Timers configuration from Database for max retries...hence proceeding!!!!");
    }    

    //Reset Retry Count.
    retry_count = 1;

    do {
        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetIwfFeaturesConfig(true, &iwfCfgResp))
        {    
            if( iwfCfgResp.has_featuresinfo() )
            {
                IwfFeaturesConfig featuresInfo = iwfCfgResp.featuresinfo();
                IwfTranslator* CapToRoTsl = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                int retVal = CMAPI_SUCCESS;
                for( int curFeature = 0 ; curFeature < featuresInfo.iwffeatureinfo_size() ; curFeature++ )
                {
                    IwfFeatureConfig featureConfig = featuresInfo.iwffeatureinfo(curFeature);
                    if( featureConfig.has_featurename() && featureConfig.has_statusvalue() )
                    {
                        if( featureConfig.featurename() == CDR || featureConfig.featurename() == TANS_TRIGGER)
                        {
                            IwfTranslator* translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                            retVal = translator->SetFeaturesConfig(&featureConfig);
                        }
                        else if(featureConfig.featurename() == CONGESTION_MANAGEMENT)
                        {
                            if(featureConfig.has_statusvalue())
                                DLOG_DEBUG("Feature %s - status %d",CONGESTION_MANAGEMENT,featureConfig.statusvalue());
                            IwfController::Instance().Config().LocalConfig().SetCongestionManagementConfig(featureConfig.statusvalue());
                            DLOG_DEBUG("Success in setting the Congestion Management config");
                        }
                        else if(featureConfig.featurename() == MAX_NUMBER_OF_SESSIONS)
                        {
                            if(featureConfig.has_statusvalue())
                                DLOG_DEBUG("Feature %s - Max Number Of Sessions to Hold %d",MAX_NUMBER_OF_SESSIONS,featureConfig.statusvalue());
                            IwfController::Instance().Config().LocalConfig().SetMaxNumberOfSessionsToHold(featureConfig.statusvalue());
                            DLOG_DEBUG("Success in setting the limit for Max IWF sessions to hold");
                        }
                    }
                }

                if( retVal != CMAPI_SUCCESS )
                {
                    DLOG_ERROR("Error in configuring Iwf Features ");
                }
                break;
            }
            else
            {
                DLOG_ERROR("Features not configured, no data returned from Database");
            }
        }    
        else 
        {    
            DLOG_WARNING("Retrying for Features configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch Features configuration from Database for max retries...hence proceeding!!!!");
    }    

    //Reset Retry Count.
    retry_count = 1;
    do {
        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetIwfDccaConfig(true, &iwfCfgResp))
        {    
            if( iwfCfgResp.has_iwfdccainfo() )
            {
                PopulateDccaConfig(iwfCfgResp.iwfdccainfo()); 
                break;
            }
        }    
        else 
        {    
            DLOG_WARNING("Retrying for Dcca configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch Dcca configuration from Database for max retries...hence proceeding!!!!");
    }    

    //Reset Retry Count.
    retry_count = 1;
    do {
        if (CMAPI_SUCCESS == m_IwfCmapiConfigObj->GetIwfProtocolActionsConfig(true, &iwfCfgResp))
        {    
            if( iwfCfgResp.has_iwfprotocolactionsinfo() )
            {

                IwfProtocolActionsConfig protActionsCfg = iwfCfgResp.iwfprotocolactionsinfo();
                retVal = IwfController::Instance().Config().GetIwfProtActionCfg().SetProtActionConfig(&protActionsCfg);
                if( retVal != CMAPI_SUCCESS )
                {
                    DLOG_ERROR("Error in populating Protocol Action Configs.");
                }
                break;
            }
            else
            {
                DLOG_ERROR("Protocol message specific configuration not configured, no data returned from Database");
            }
        }    
        else 
        {    
            DLOG_WARNING("Retrying for Protocol Action Configs configuration");
            retry_count++;
        }    
    }while(retry_count <= IWF_MAX_RETRY_COUNT);     

    if (retry_count >= IWF_MAX_RETRY_COUNT)
    {    
        DLOG_ERROR("Failed to fetch Protocol Action Configs configuration from Database for max retries...hence proceeding!!!!");
    }    

    /*ENGINE_TransportSpecificsPart localInfo;
      ENGINE_TransportSpecificsPart virtualInfo;

      localInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.udpPart.associates = (char **)malloc(sizeof(char *));
      localInfo.data.sctpSpecs.udpPart.associates[0] = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      localInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));

      localInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;

      virtualInfo.data.sctpSpecs.udpPart.associates = (char **)malloc(sizeof(char *));
      virtualInfo.data.sctpSpecs.udpPart.associates[0] = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
      virtualInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));

      virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
      virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
      virtualInfo.data.sctpSpecs.numExtraHomes = 0;


      strcpy(localInfo.data.sctpSpecs.udpPart.localHost,"172.16.3.18");
      sprintf(localInfo.data.sctpSpecs.udpPart.localPort,"%d",3214);
      strcpy(localInfo.data.sctpSpecs.udpPart.associates[0] ,"ASP1");
      strcpy(localInfo.data.sctpSpecs.payloadType ,"CCITT");
      strcat(localInfo.data.sctpSpecs.payloadType , "-M3UA");
      localInfo.data.sctpSpecs.udpPart.numAssociates = 1;
      sprintf(localInfo.data.sctpSpecs.maxInStreams, "%d",32);
      sprintf(localInfo.data.sctpSpecs.numOutStreams, "%d",32);
      strcpy(localInfo.data.sctpSpecs.isClient ,"yes"); 

      sprintf(localInfo.data.sctpSpecs.maxAttempts ,"%d",-1);

      localInfo.data.sctpSpecs.numExtraHomes = 0;

      strcpy(localInfo.data.sctpSpecs.cookieLife ,"30");
      strcpy(localInfo.data.sctpSpecs.hbOn ,"yes");
      strcpy(localInfo.data.sctpSpecs.initTimeOut ,"5,0");
      strcpy(localInfo.data.sctpSpecs.sendTimeOut ,"1,0");
      strcpy(localInfo.data.sctpSpecs.recvTimeOut ,"0,300");
      strcpy(localInfo.data.sctpSpecs.hbTimeOut ,"10,0");
      strcpy(localInfo.data.sctpSpecs.shutdownTimeOut ,"5,0");
      strcpy(localInfo.data.sctpSpecs.pmtuTimeOut ,"600,0");

      strcpy(virtualInfo.data.sctpSpecs.payloadType ,"CCITT");
      strcat(virtualInfo.data.sctpSpecs.payloadType , "-M3UA");
      sprintf(virtualInfo.data.sctpSpecs.maxInStreams, "%d",32);
      sprintf(virtualInfo.data.sctpSpecs.numOutStreams, "%d",32);
    strcpy(virtualInfo.data.sctpSpecs.isClient ,"yes"); 

    sprintf(virtualInfo.data.sctpSpecs.maxAttempts ,"%d",-1);

    strcpy(virtualInfo.data.sctpSpecs.cookieLife ,"30");
    strcpy(virtualInfo.data.sctpSpecs.hbOn ,"yes");
    strcpy(virtualInfo.data.sctpSpecs.initTimeOut ,"5,0");
    strcpy(virtualInfo.data.sctpSpecs.sendTimeOut ,"1,0");
    strcpy(virtualInfo.data.sctpSpecs.recvTimeOut ,"0,300");
    strcpy(virtualInfo.data.sctpSpecs.hbTimeOut ,"10,0");
    strcpy(virtualInfo.data.sctpSpecs.shutdownTimeOut ,"5,0");
    strcpy(virtualInfo.data.sctpSpecs.pmtuTimeOut ,"600,0");

    virtualInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
    virtualInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));

    strcpy(virtualInfo.data.sctpSpecs.udpPart.localHost, "172.16.3.18");
    sprintf(virtualInfo.data.sctpSpecs.udpPart.localPort,"%d", 9999);

    virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
    virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
    virtualInfo.data.sctpSpecs.numExtraHomes = 0;


    std::string family = "";
    if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ITU)
    {
        family = "ITU";
    }
    else if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ANSI)
    {
        family = "ANSI";
    }

    ret = SetBorderPoolTransport((char *)"ASP1", (char *)"Virtual", (char *)family.c_str(), (char *)"MTP3 SCTP", virtualInfo);
    DLOG_DEBUG("transport instance %d Remotefamily %s", ret, family.c_str()));

    ret1 = SetBorderPoolTransport((char *)"SCTPClient-1", (char *)"Datagram", (char *)family.c_str(), (char *)"MTP3 SCTP", localInfo);
    DLOG_DEBUG("transport instance %d Localfamily %s", ret1, family.c_str()));
    usleep(100000);

    MTP3_OSS_AddLink_CCITT((ITS_OCTET)1, (ITS_OCTET)2, ret);
    MTP3_OSS_AddRemotePC_CCITT(4114, 131, 146, 1, 0, FAMILY_ITU);*/

        /*retVal = DeleteBorderPoolTransport(ret1);
          retVal = MTP3_OSS_RemoveLink_CCITT((ITS_OCTET)1, (ITS_OCTET)2);

          localInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.udpPart.associates = (char **)malloc(sizeof(char *));
          localInfo.data.sctpSpecs.udpPart.associates[0] = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          localInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));

          localInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;

          virtualInfo.data.sctpSpecs.udpPart.associates = (char **)malloc(sizeof(char *));
          virtualInfo.data.sctpSpecs.udpPart.associates[0] = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
          virtualInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));

          virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
          virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
          virtualInfo.data.sctpSpecs.numExtraHomes = 0;


          strcpy(localInfo.data.sctpSpecs.udpPart.localHost,"172.16.3.18");
          sprintf(localInfo.data.sctpSpecs.udpPart.localPort,"%d",3214);
          strcpy(localInfo.data.sctpSpecs.udpPart.associates[0] ,"ASP1");
          strcpy(localInfo.data.sctpSpecs.payloadType ,"CCITT");
          strcat(localInfo.data.sctpSpecs.payloadType , "-M3UA");
          localInfo.data.sctpSpecs.udpPart.numAssociates = 1;
          sprintf(localInfo.data.sctpSpecs.maxInStreams, "%d",32);
          sprintf(localInfo.data.sctpSpecs.numOutStreams, "%d",32);
          strcpy(localInfo.data.sctpSpecs.isClient ,"yes"); 

          sprintf(localInfo.data.sctpSpecs.maxAttempts ,"%d",-1);

          localInfo.data.sctpSpecs.numExtraHomes = 0;

          strcpy(localInfo.data.sctpSpecs.cookieLife ,"30");
          strcpy(localInfo.data.sctpSpecs.hbOn ,"yes");
          strcpy(localInfo.data.sctpSpecs.initTimeOut ,"5,0");
          strcpy(localInfo.data.sctpSpecs.sendTimeOut ,"1,0");
          strcpy(localInfo.data.sctpSpecs.recvTimeOut ,"0,300");
          strcpy(localInfo.data.sctpSpecs.hbTimeOut ,"10,0");
          strcpy(localInfo.data.sctpSpecs.shutdownTimeOut ,"5,0");
          strcpy(localInfo.data.sctpSpecs.pmtuTimeOut ,"600,0");

          strcpy(virtualInfo.data.sctpSpecs.payloadType ,"CCITT");
          strcat(virtualInfo.data.sctpSpecs.payloadType , "-M3UA");
          sprintf(virtualInfo.data.sctpSpecs.maxInStreams, "%d",32);
          sprintf(virtualInfo.data.sctpSpecs.numOutStreams, "%d",32);
        strcpy(virtualInfo.data.sctpSpecs.isClient ,"yes"); 

    sprintf(virtualInfo.data.sctpSpecs.maxAttempts ,"%d",-1);

    strcpy(virtualInfo.data.sctpSpecs.cookieLife ,"30");
    strcpy(virtualInfo.data.sctpSpecs.hbOn ,"yes");
    strcpy(virtualInfo.data.sctpSpecs.initTimeOut ,"5,0");
    strcpy(virtualInfo.data.sctpSpecs.sendTimeOut ,"1,0");
    strcpy(virtualInfo.data.sctpSpecs.recvTimeOut ,"0,300");
    strcpy(virtualInfo.data.sctpSpecs.hbTimeOut ,"10,0");
    strcpy(virtualInfo.data.sctpSpecs.shutdownTimeOut ,"5,0");
    strcpy(virtualInfo.data.sctpSpecs.pmtuTimeOut ,"600,0");

    virtualInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
    virtualInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));

    strcpy(virtualInfo.data.sctpSpecs.udpPart.localHost, "172.16.3.18");
    sprintf(virtualInfo.data.sctpSpecs.udpPart.localPort,"%d", 9999);

    virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
    virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
    virtualInfo.data.sctpSpecs.numExtraHomes = 0;

    ret = SetBorderPoolTransport((char *)"ASP1", (char *)"Virtual", (char *)family.c_str(), (char *)"MTP3 SCTP", virtualInfo);
    DLOG_DEBUG("transport instance %d Remotefamily %s", ret, family.c_str()));

    ret1 = SetBorderPoolTransport((char *)"SCTPClient-1", (char *)"Datagram", (char *)family.c_str(), (char *)"MTP3 SCTP", localInfo);
    DLOG_DEBUG("transport instance %d Localfamily %s", ret1, family.c_str()));
    usleep(1000);

    MTP3_OSS_AddLink_CCITT((ITS_OCTET)1, (ITS_OCTET)2, ret);*/
        IwfController::PopulateReplicationFreeList();

    DLOG_DEBUG("IwfController::InitSigtranStack Exit");
    return 0;
}

int IwfController::PopulateLocalHostConfig(const IwfLocalHostConfig& refLocaHostConfig)
{

    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::PopulateLocalHostConfig Entry");
    int retVal = ITS_SUCCESS;

    char hostname[1024] = {0};
    gethostname(hostname, 1024);
    DLOG_DEBUG("PopulateLocalHostConfig Local Host Name %s", hostname);

    if(refLocaHostConfig.has_hostname1() || refLocaHostConfig.has_hostname2())
    {
        if(strcasecmp(hostname, refLocaHostConfig.hostname1().c_str()) == 0)
        {
            DLOG_DEBUG("PopulateLocalHostConfig ASPId : %d for HostName1 : %s", 
                    refLocaHostConfig.aspid1(), refLocaHostConfig.hostname1().c_str());
            IwfController::Instance().Config().LocalConfig().SetASPId(refLocaHostConfig.aspid1());
            TransactionManager::Instance()->UpdateTcapLocalTransactionTable(refLocaHostConfig.aspid1());
        }
        else if(strcasecmp(hostname, refLocaHostConfig.hostname2().c_str()) == 0)
        {
            DLOG_DEBUG("PopulateLocalHostConfig ASPId : %d for HostName2 : %s", 
                    refLocaHostConfig.aspid2(), refLocaHostConfig.hostname2().c_str());
            IwfController::Instance().Config().LocalConfig().SetASPId(refLocaHostConfig.aspid2()); 
            TransactionManager::Instance()->UpdateTcapLocalTransactionTable(refLocaHostConfig.aspid2());
        }
        else
        {
            DLOG_ERROR("Configured HostNames does not matches the local HostName");
        }
    }
    else
    {
        DLOG_ERROR("No HostName present in incoming configuration");
    }

    if(refLocaHostConfig.has_pointcode())
    {
        DLOG_DEBUG("IwfController::PopulateLocalHostConfig PointCode : %d", refLocaHostConfig.pointcode());
        IwfController::Instance().Config().LocalConfig().SetOriginPointCode(refLocaHostConfig.pointcode());
    }

    int totalSsnNum = refLocaHostConfig.ssn_config_size();
    if(totalSsnNum > 0)
    {
        for(int ssnNum = 0; ssnNum < totalSsnNum; ssnNum++)
        {
            IwfLocalSSNConfig localSSN = refLocaHostConfig.ssn_config(ssnNum);
            if(localSSN.has_ssn())
            {
                DLOG_DEBUG("IwfController::PopulateLocalHostConfig SSN : %d", localSSN.ssn());
                IwfController::Instance().Config().LocalConfig().AddLocalSSN(localSSN.ssn());
            }   
        }
    }

    SS7_LinkSetInfo linkSetInfo;
    ITS_OCTET numLinkSet;
    if(MTP3_OSS_GetLinkset_CCITT(0, &linkSetInfo, &numLinkSet) == ITS_SUCCESS)
    {
        DLOG_DEBUG("Local NetworkIndicator : %d", linkSetInfo.ni);
        if(linkSetInfo.ni) 
        {
            IwfController::Instance().Config().LocalConfig().SetLocalNetworkIndicator(1);
        }
        else
        {
            IwfController::Instance().Config().LocalConfig().SetLocalNetworkIndicator(0);
        }
    }

    if(refLocaHostConfig.has_selectcriteria())
    {
        DLOG_DEBUG("IwfController::PopulateLocalHostConfig Selection Criteria: %d", (SelectionCriteria)refLocaHostConfig.selectcriteria());
        IwfController::Instance().Config().LocalConfig().SetSelectionCriteria((SelectionCriteria)refLocaHostConfig.selectcriteria());
    }

    if(refLocaHostConfig.has_tcapinvoketimer())
    {
        unsigned invokeTimer = refLocaHostConfig.tcapinvoketimer();
        DLOG_DEBUG("IwfController::PopulateLocalHostConfig TcapInvokeTimer : %d", refLocaHostConfig.tcapinvoketimer());
        IwfController::Instance().Config().LocalConfig().SetInvokeTimeout(invokeTimer);
    }

    if(refLocaHostConfig.has_addresstype())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost AddressType : %s", refLocaHostConfig.addresstype().c_str());
        if(!strcasecmp(refLocaHostConfig.addresstype().c_str(), "GT"))
        {
            IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetRouteByGT(true);
        }
        else
        {
            IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetRouteByGT(false);
        }
    }

    if(refLocaHostConfig.has_usesccpcdpafromincommingmsg())
    {
        DLOG_DEBUG("IwfController::PopulateLocalHostConfig UseSCCPCDPAFromIncomingMessage: %d", refLocaHostConfig.usesccpcdpafromincommingmsg());
        IwfController::Instance().Config().LocalConfig().SetIsUseSccpCdPAFromInMsg(refLocaHostConfig.usesccpcdpafromincommingmsg());
    }

    if(refLocaHostConfig.has_localgtusefromconfig())
    {
        DLOG_DEBUG("IwfController::PopulateLocalHostConfig UseLocalGTCOnfiguraiton: %d", refLocaHostConfig.localgtusefromconfig());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetUseFromConfig(refLocaHostConfig.localgtusefromconfig());
    }

    if(refLocaHostConfig.has_includepc())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost IncludePC in GT: %d", refLocaHostConfig.includepc());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetLocalPCIndicator(refLocaHostConfig.includepc());
    }

    if(refLocaHostConfig.has_gti())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetGTI(refLocaHostConfig.gti());
    }
    if(refLocaHostConfig.has_translationtype())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetTranslationType(refLocaHostConfig.translationtype());
    }
    if(refLocaHostConfig.has_numberingplan())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetNumberingPlan(refLocaHostConfig.numberingplan());
    }
    if(refLocaHostConfig.has_encodingscheme())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetEncodingScheme(refLocaHostConfig.encodingscheme());
    }
    if(refLocaHostConfig.has_natureofaddrind())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetAddressIndicator(refLocaHostConfig.natureofaddrind());
    }
    if(refLocaHostConfig.has_gtaddrdigits())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetGtDigits(refLocaHostConfig.gtaddrdigits());
    }
    DLOG_DEBUG("IwfController::PopulateLocalHostConfig Entry");
    return retVal;
}

int IwfController::PopulateUalGeneralConfig(const IwfSigtranUalManagerConfig& refUalManagerCfg)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::PopulateLocalHostConfig Entry");
    int retVal = ITS_SUCCESS;
    if(refUalManagerCfg.has_acktimer() && refUalManagerCfg.has_sigtranmode()) 
    {
        UALConfigMgmt *ualConfigMgmt;
        ualConfigMgmt = (UALConfigMgmt*)calloc(1, sizeof(UALConfigMgmt));

        DLOG_DEBUG("Incoming InterWorking Mode: %s", refUalManagerCfg.sigtranmode().c_str());
        strncpy(ualConfigMgmt->interworkingMode, refUalManagerCfg.sigtranmode().c_str(), MAX_STRING_SIZE);
        strncpy(ualConfigMgmt->protocolType, "M3UA", MAX_STRING_SIZE);
        //strncpy(ualConfigMgmt->ipspExchangeType, "single", MAX_STRING_SIZE);
        //strncpy(ualConfigMgmt->ipspType, "client", MAX_STRING_SIZE);
        strncpy(ualConfigMgmt->ipspExchangeType, "-", MAX_STRING_SIZE);
        strncpy(ualConfigMgmt->ipspType, "-", MAX_STRING_SIZE);
        strncpy(ualConfigMgmt->heartbeatFlag, "off", MAX_STRING_SIZE);
        ualConfigMgmt->protocolVersion = 1;
        ualConfigMgmt->localPointCode = 1;
        ualConfigMgmt->heartbeatInterval = 5;
        DLOG_DEBUG("Incoming Ack Timer: %d", refUalManagerCfg.acktimer());
        ualConfigMgmt->ackTimer = refUalManagerCfg.acktimer();
        ualConfigMgmt->auditTimer = 10;
        ualConfigMgmt->pendingTimer = 2;

        if((retVal = ConfigureUalManagement(ualConfigMgmt)) != ITS_SUCCESS)
        {
            DLOG_ERROR("IwfController::PopulateUalGeneralConfig: UAL General Configuration failed: Error %d", retVal);
            return retVal;
        }
        if(ualConfigMgmt)
        {
            free(ualConfigMgmt);
            ualConfigMgmt = NULL;
        }
    }
    else
    {
        DLOG_ERROR("IwfController::PopulateUalGeneralConfig Mandatory Parameters missing in UAL Configuration..!!");
        return CMAPI_ERROR;
    }
    DLOG_DEBUG("IwfController::PopulateLocalHostConfig Exit");
    return retVal;
}

int IwfController::PopulateAssociationSetConfig(const IwfSigtranAssociationSetsConfig& refAssociationSetConfig)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::PopulateAssociationSetConfig Entry");
    int retVal = ITS_SUCCESS;
    ITS_UINT lpc = IwfController::Instance().Config().LocalConfig().OriginPointCode();
    ITS_UINT rkey = 0;
    UAL_TRAFFIC_TYPE trafficMode;
    ITS_UINT ni;
    ITS_UINT sio;
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    string localFamily = "ITU";
    if(family == FAMILY_ITU)
    {
        localFamily = "ITU";
    }
    else if(family == FAMILY_ANSI)
    {
        localFamily = "ANSI";
    }

    int totalAssociationSetNum = refAssociationSetConfig.associationsetinfo_size();
    if(totalAssociationSetNum > 0)
    {
        for (int assocSetNum = 0; assocSetNum < totalAssociationSetNum; assocSetNum++)
        {
            IwfSigtranAssociationSetConfig assocSetCfg = refAssociationSetConfig.associationsetinfo(assocSetNum);

            if(assocSetCfg.has_associationsetid() && assocSetCfg.has_networkindicator() &&
                    assocSetCfg.has_adjacenpointcode() && assocSetCfg.has_routingcontext())
            {
                ITS_OCTET linkSetId = assocSetCfg.associationsetid();
                ITS_UINT apc = assocSetCfg.adjacenpointcode();
                if(assocSetCfg.networkindicator())
                {
                    DLOG_DEBUG("Network Indicator is National");
                    ni = IWF_NATIONAL_INDICATOR;
                    sio = IWF_NATIONAL_SIO;
                }
                else
                {
                    DLOG_DEBUG("Network Indicator is International");
                    ni = IWF_INTERNATIONAL_INDICATOR;
                    sio = IWF_INTERNATIONAL_SIO;
                }
                rkey = assocSetCfg.routingcontext();

                /* setting the apc for localConfig to be used for GTT routing 
                 * creating the map of GTT Routing with APC */
                IwfController::Instance().Config().LocalConfig().SetAdjacentPointCode(apc);

                if((retVal = MTP3_OSS_AddLinkset_CCITT(linkSetId, family, lpc, apc, ni)) != ITS_SUCCESS)
                {
                    DLOG_ERROR("Addition of AssociationSet falied, Error %d", retVal);
                    return retVal;
                }
                std::vector<unsigned> ssn = IwfController::Instance().Config().LocalConfig().LocalSSN();
                if(!ssn.empty())
                {
                    if((retVal = MTP3_OSS_AddRoutingKeyroutePC_CCITT(lpc, sio, ssn.front(), rkey, family)) != ITS_SUCCESS)
                    {
                        DLOG_ERROR("Addition of RoutingKeyRoute falied, Error %d", retVal);
                        return retVal;
                    }
                }
                else
                {
                    DLOG_ERROR("Local SSN not Configured, Failed to add routing key Route");
                    return CMAPI_ERROR;
                }
            }
            else
            {
                DLOG_ERROR("IwfController::PopulateAssociationSetConfig: Mandatory Parameters missing ..!!");
                return CMAPI_ERROR;
            }

            if(assocSetCfg.has_trafficmode() && assocSetCfg.has_routingcontext() &&
                    assocSetCfg.has_ismember())
            {
                if(UAL_GL_ITW_MODE == UAL_ITW_IPSP && !assocSetCfg.has_homeip())
                {    
                    DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: HomeIp is not set in req as IWF is configured as IPSP Mode");
                    DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Mandatory Parameters missing in UAL Configuration..!!");
                    return CMAPI_ERROR;
                }
                if(strcmp(assocSetCfg.trafficmode().c_str(), UAL_LOAD_SHARE_MODE_STRING) == 0)
                {
                    trafficMode = UAL_LOADSHARE;
                }
                else if(strcmp(assocSetCfg.trafficmode().c_str(), UAL_OVERIDE_MODE_STRING) == 0)
                {
                    trafficMode = UAL_OVERRIDE;
                }
                else
                {
                    DLOG_ERROR("IwfController::PopulateAssociationSetConfig: Invalid Traffic Mode Configured");
                    return CMAPI_ERROR;
                }

                DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet: Incoming isMember Value : %d", assocSetCfg.ismember());
                ITS_BOOLEAN isMem = ITS_TRUE;
                if(assocSetCfg.ismember() == 0)
                {
                    isMem = ITS_FALSE;
                }

                if((retVal = CreateApplicationServer(rkey, (char *)localFamily.c_str(), trafficMode, ni, isMem)) != ITS_SUCCESS)
                {
                    DLOG_ERROR("IwfController::PopulateAssociationSetConfig: Unable to create Application Server: Error %d", retVal);
                    return retVal;
                }

                const char* homeIp = NULL;
                if(assocSetCfg.has_homeip())
                {
                    DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet: Incoming HomeIp Address Value : %s", assocSetCfg.homeip().c_str());
                    homeIp = assocSetCfg.homeip().c_str();
                }

                if(UAL_GL_ITW_MODE != UAL_ITW_IPSP)
                {
                    if((retVal = CreateApplicationServerProcess(rkey, IwfController::Instance().Config().LocalConfig().GetASPId(), homeIp)) != ITS_SUCCESS)
                    {
                        DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server Process: Error %d", retVal);
                        return retVal;
                    }
                }
            }
            else
            {
                DLOG_ERROR("IwfController::PopulateAssociationSetConfig: Mandatory Parameters missing in UAL Configuration..!!");
                return CMAPI_ERROR;
            }
        }
    }
    else
    {
        DLOG_ERROR("Empty AssoicationSet Confgiuration Received from DB");
    }
    DLOG_DEBUG("IwfController::PopulateAssociationSetConfig Exit");
    return retVal;
}

int IwfController::PopulateAssociationConfig(const IwfSigtranAssociationsConfig& refAssociationCfg)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::PopulateAssociationConfig Entry");
    int retVal = ITS_SUCCESS;
    std::string family = "";
    if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ITU)
    {
        family = "ITU";
    }
    else if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ANSI)
    {
        family = "ANSI";
    }
    int totalAssoicationNum = refAssociationCfg.associationinfo_size();
    if(totalAssoicationNum > 0)
    {
        for (int assocNum = 0; assocNum < totalAssoicationNum; assocNum++)
        {
            IwfSigtranAssociationConfig assocCfg = refAssociationCfg.associationinfo(assocNum);

            ITS_OCTET linkSet;
            std::string remoteTransportName = "";
            std::string localTransportName = "";
            std::string endPointType = "";
            ENGINE_TransportSpecificsPart localInfo;
            ENGINE_TransportSpecificsPart virtualInfo;
            int transportInstance = 0;

            if(assocCfg.has_aspid())
            {
                if(IwfController::Instance().Config().LocalConfig().GetASPId() != assocCfg.aspid())
                {
                    DLOG_DEBUG("Incoming ASPId  %d does not does not matches Locally Configured ASPId %d", 
                            assocCfg.aspid(), IwfController::Instance().Config().LocalConfig().GetASPId());
                }
                else
                {
                    if(assocCfg.has_associationsetid())
                    {
                        linkSet = (ITS_OCTET)assocCfg.associationsetid();
                    }
                    else
                    {
                        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing AssociationSet Configuration..!!");
                        return CMAPI_ERROR;
                    }

                    if(assocCfg.has_sctpprofile())
                    {
                        IwfSigtranSctpProfileConfig sctpProfileCfg = assocCfg.sctpprofile();
                        if(sctpProfileCfg.has_maxinstreams())
                        {
                            localInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.maxInStreams, "%d", sctpProfileCfg.maxinstreams());

                            virtualInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.maxInStreams, "%d", sctpProfileCfg.maxinstreams());
                        }
                        if(sctpProfileCfg.has_numoutstreams())
                        {
                            localInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.numOutStreams, "%d", sctpProfileCfg.numoutstreams());

                            virtualInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.numOutStreams, "%d", sctpProfileCfg.numoutstreams());
                        }
                        if(sctpProfileCfg.has_maxattempt())
                        {
                            localInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.maxAttempts, "%d", sctpProfileCfg.maxattempt());

                            virtualInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.maxAttempts, "%d", sctpProfileCfg.maxattempt());
                        }
                        if(sctpProfileCfg.has_assocmaxattempt())
                        {
                            localInfo.data.sctpSpecs.assoMaxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.assoMaxAttempts , "%d", sctpProfileCfg.assocmaxattempt());

                            virtualInfo.data.sctpSpecs.assoMaxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.assoMaxAttempts, "%d", sctpProfileCfg.assocmaxattempt());
                        }

                        if(sctpProfileCfg.has_cookielife())
                        {
                            localInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.cookieLife, "%d", sctpProfileCfg.cookielife());

                            virtualInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.cookieLife, "%d", sctpProfileCfg.cookielife());
                        }
                        if(sctpProfileCfg.has_heartbeatenable())
                        {
                            localInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            strcpy(localInfo.data.sctpSpecs.hbOn, ((sctpProfileCfg.heartbeatenable() == 1) ? "yes" : "no"));

                            virtualInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            strcpy(virtualInfo.data.sctpSpecs.hbOn, ((sctpProfileCfg.heartbeatenable() == 1) ? "yes" : "no"));
                        }
                        if(sctpProfileCfg.has_inittimeout())
                        {
                            uint32_t initTimeOut = (sctpProfileCfg.inittimeout());
                            localInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(initTimeOut)
                                sprintf(localInfo.data.sctpSpecs.initTimeOut, "%d,%d", initTimeOut/1000,initTimeOut%1000);
                            else
                                sprintf(localInfo.data.sctpSpecs.initTimeOut, "0,0");

                            virtualInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(initTimeOut)
                                sprintf(virtualInfo.data.sctpSpecs.initTimeOut, "%d,%d", initTimeOut/1000,initTimeOut%1000);
                            else
                                sprintf(virtualInfo.data.sctpSpecs.initTimeOut, "0,0");
                        }
                        if(sctpProfileCfg.has_sendtimeout())
                        {
                            uint32_t sendTimeOut = (sctpProfileCfg.sendtimeout());
                            localInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(sendTimeOut)
                                sprintf(localInfo.data.sctpSpecs.sendTimeOut, "%d,%d", sendTimeOut/1000,sendTimeOut%1000);
                            else
                                sprintf(localInfo.data.sctpSpecs.sendTimeOut, "0,0");

                            virtualInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(sendTimeOut)
                                sprintf(virtualInfo.data.sctpSpecs.sendTimeOut, "%d,%d", sendTimeOut/1000,sendTimeOut%1000);
                            else
                                sprintf(virtualInfo.data.sctpSpecs.sendTimeOut, "0,0");
                        }
                        if(sctpProfileCfg.has_receivetimeout())
                        {
                            localInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(sctpProfileCfg.receivetimeout())
                                sprintf(localInfo.data.sctpSpecs.recvTimeOut, "%d,%d", sctpProfileCfg.receivetimeout()/1000,sctpProfileCfg.receivetimeout()%1000);
                            else
                                sprintf(localInfo.data.sctpSpecs.recvTimeOut, "0,0");

                            virtualInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(sctpProfileCfg.receivetimeout())
                                sprintf(virtualInfo.data.sctpSpecs.recvTimeOut, "%d,%d", sctpProfileCfg.receivetimeout()/1000,sctpProfileCfg.receivetimeout()%1000);
                            else
                                sprintf(virtualInfo.data.sctpSpecs.recvTimeOut, "0,0");
                        }
                        if(sctpProfileCfg.has_heartbeattimeout())
                        {
                            uint32_t hbTimeOut = (sctpProfileCfg.heartbeattimeout());
                            localInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(hbTimeOut)
                                sprintf(localInfo.data.sctpSpecs.hbTimeOut, "%d,%d", hbTimeOut/1000,hbTimeOut%1000);
                            else
                                sprintf(localInfo.data.sctpSpecs.hbTimeOut, "0,0");

                            virtualInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(hbTimeOut)
                                sprintf(virtualInfo.data.sctpSpecs.hbTimeOut, "%d,%d", hbTimeOut/1000,hbTimeOut%1000);
                            else
                                sprintf(virtualInfo.data.sctpSpecs.hbTimeOut, "0,0");
                        }
                        if(sctpProfileCfg.has_shutdowntimeout())
                        {
                            uint32_t shutdownTimeOut = (sctpProfileCfg.shutdowntimeout());
                            localInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(shutdownTimeOut)
                                sprintf(localInfo.data.sctpSpecs.shutdownTimeOut, "%d,%d", shutdownTimeOut/1000,shutdownTimeOut%1000);
                            else
                                sprintf(localInfo.data.sctpSpecs.shutdownTimeOut, "0,0");

                            virtualInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(shutdownTimeOut)
                                sprintf(virtualInfo.data.sctpSpecs.shutdownTimeOut, "%d,%d", shutdownTimeOut/1000, shutdownTimeOut%1000);
                            else
                                sprintf(virtualInfo.data.sctpSpecs.shutdownTimeOut, "0,0");
                        }
                        if(sctpProfileCfg.has_pmtutimeout())
                        {
                            uint32_t pmtuTimeOut = (sctpProfileCfg.pmtutimeout());
                            localInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(pmtuTimeOut)
                                sprintf(localInfo.data.sctpSpecs.pmtuTimeOut, "%d,%d", pmtuTimeOut/1000,pmtuTimeOut%1000);
                            else
                                sprintf(localInfo.data.sctpSpecs.pmtuTimeOut, "0,0");

                            virtualInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            if(pmtuTimeOut)
                                sprintf(virtualInfo.data.sctpSpecs.pmtuTimeOut, "%d,%d", pmtuTimeOut/1000,pmtuTimeOut%1000);
                            else
                                sprintf(virtualInfo.data.sctpSpecs.pmtuTimeOut, "0,0");
                        }
                        if(sctpProfileCfg.has_rtomax())
                        {
                            localInfo.data.sctpSpecs.rtoMax =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.rtoMax , "%d", sctpProfileCfg.rtomax());

                            virtualInfo.data.sctpSpecs.rtoMax =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.rtoMax , "%d", sctpProfileCfg.rtomax());
                        }
                        if(sctpProfileCfg.has_rtomin())
                        {
                            localInfo.data.sctpSpecs.rtoMin =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.rtoMin, "%d", sctpProfileCfg.rtomin());

                            virtualInfo.data.sctpSpecs.rtoMin =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.rtoMin, "%d", sctpProfileCfg.rtomin());
                        }
                        if(sctpProfileCfg.has_rtoinitial())
                        {
                            localInfo.data.sctpSpecs.rtoInitial =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.rtoInitial, "%d", sctpProfileCfg.rtoinitial());

                            virtualInfo.data.sctpSpecs.rtoInitial =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.rtoInitial , "%d", sctpProfileCfg.rtoinitial());
                        }
                        if(sctpProfileCfg.has_sackdelay())
                        {
                            localInfo.data.sctpSpecs.sackDelay =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.sackDelay , "%d", sctpProfileCfg.sackdelay());

                            virtualInfo.data.sctpSpecs.sackDelay =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.sackDelay , "%d", sctpProfileCfg.sackdelay());
                        }
                        if(sctpProfileCfg.has_sendbufsize())
                        {
                            localInfo.data.sctpSpecs.sendBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.sendBufSize , "%d", sctpProfileCfg.sendbufsize());

                            virtualInfo.data.sctpSpecs.sendBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.sendBufSize, "%d", sctpProfileCfg.sendbufsize());
                        }
                        if(sctpProfileCfg.has_recvbufsize())
                        {
                            localInfo.data.sctpSpecs.recvBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.recvBufSize , "%d", sctpProfileCfg.recvbufsize());

                            virtualInfo.data.sctpSpecs.recvBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.recvBufSize, "%d", sctpProfileCfg.recvbufsize());
                        }
                        if(sctpProfileCfg.has_reconnecttimeout())
                        {
                            localInfo.data.sctpSpecs.reconnectTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.reconnectTimeOut, "%d", sctpProfileCfg.reconnecttimeout());

                            virtualInfo.data.sctpSpecs.reconnectTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.reconnectTimeOut, "%d", sctpProfileCfg.reconnecttimeout());
                        }
                        if(sctpProfileCfg.has_pathfailureretrycount())
                        {
                            localInfo.data.sctpSpecs.pathmaxrxt =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.pathmaxrxt, "%d", sctpProfileCfg.pathfailureretrycount());

                            virtualInfo.data.sctpSpecs.pathmaxrxt =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.pathmaxrxt, "%d", sctpProfileCfg.pathfailureretrycount());
                        }



                        /* Payload type to be filled based on the family configured to be discusseed */ 
                        localInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                        strcpy(localInfo.data.sctpSpecs.payloadType, "CCITT");
                        //strcpy(localInfo.data.sctpSpecs.payloadType, "ANSI");
                        strcat(localInfo.data.sctpSpecs.payloadType , "-M3UA");

                        virtualInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                        strcpy(virtualInfo.data.sctpSpecs.payloadType, "CCITT");
                        //strcpy(virtualInfo.data.sctpSpecs.payloadType, "ANSI");
                        strcat(virtualInfo.data.sctpSpecs.payloadType , "-M3UA");

                        /* isClient to be filled in sctp profile or not */
                        localInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                        strcpy(localInfo.data.sctpSpecs.isClient, "yes");

                        virtualInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                        strcpy(virtualInfo.data.sctpSpecs.isClient, "yes");
                    }
                    else
                    {
                        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing Sctp Profile..!!");
                        return CMAPI_ERROR;
                    }

                    /* validate all localhost's ip address before adding the remote/local
                     * endpoint into association */
                    if( assocCfg.has_localendpoint() )
                    {
                        std::vector<std::string> localIp;
                        int port=0;
                        IwfSigtranSctpEndPointConfig localEndPoint = assocCfg.localendpoint();
                        if( localEndPoint.has_ipaddress() && localEndPoint.has_port() )
                        {
                            /* first entry in the vector will the localhost's primay ip */
                            localIp.push_back(localEndPoint.ipaddress());
                            if (localEndPoint.multihominginfo_size() >  0)
                            {
                                for(int numExtrahomes = 0; numExtrahomes < localEndPoint.multihominginfo_size() ; numExtrahomes++)
                                {
                                    IwfSigtranMultihomingConfig multiHomingInfo = localEndPoint.multihominginfo(numExtrahomes);
                                    if(multiHomingInfo.has_otheripaddress())
                                    {
                                        localIp.push_back(multiHomingInfo.otheripaddress());
                                    }
                                }
                            }
                            /* validate the localhost ip's recieved from configuration to ensure
                             * all ip's are valid ip if not send error response to CMGR */
                            if ( !ITS_SUCCESS == IWFUtils::ValidateLocalHostIP(localIp,port) )
                            {
                                DLOG_ERROR("Validation of LocalHost IP(s) configured failed, unable to add Asscociation");
                                retVal = ADD_ASSOCIATION_ERR_FAILED_INVALID_LOCAL_ENDPOINT_IP;
                                /* Continue adding other association */
                                continue;
                            }
                        }
                        else
                        {
                            DLOG_ERROR("Missing LocalEndPoint configuration ");
                        }
                    }

                    virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
                    virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
                    virtualInfo.data.sctpSpecs.numExtraHomes = 0;


                    if(assocCfg.has_remoteendpoint())
                    {
                        IwfSigtranSctpEndPointConfig remoteEndPoint = assocCfg.remoteendpoint();
                        virtualInfo.data.sctpSpecs.numExtraHomes = remoteEndPoint.multihominginfo_size();
                        if (virtualInfo.data.sctpSpecs.numExtraHomes > 0)
                        {
                            virtualInfo.data.sctpSpecs.extraHomes = (char**)malloc
                                ((remoteEndPoint.multihominginfo_size()) * sizeof(char*));
                            for(int numExtrahomes = 0; numExtrahomes < virtualInfo.data.sctpSpecs.numExtraHomes; numExtrahomes++)
                            {
                                IwfSigtranMultihomingConfig multiHomingInfo = remoteEndPoint.multihominginfo(numExtrahomes);
                                if(multiHomingInfo.has_otheripaddress())
                                {
                                    virtualInfo.data.sctpSpecs.extraHomes[numExtrahomes] = (char*)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                                    strcpy(virtualInfo.data.sctpSpecs.extraHomes[numExtrahomes],
                                            multiHomingInfo.otheripaddress().c_str());
                                }
                            }
                        }
                        if(remoteEndPoint.has_endpointtype())
                        {
                            endPointType = remoteEndPoint.endpointtype(); 
                        }
                        if(remoteEndPoint.has_endpointname() && remoteEndPoint.has_ipaddress() && remoteEndPoint.has_port())
                        {
                            remoteTransportName = remoteEndPoint.endpointname();

                            virtualInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            strcpy(virtualInfo.data.sctpSpecs.udpPart.localHost, remoteEndPoint.ipaddress().c_str());

                            virtualInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(virtualInfo.data.sctpSpecs.udpPart.localPort,"%d", (remoteEndPoint.port()));

                            /* family to be taken from preconfigured value in json */
                            retVal = SetBorderPoolTransport_CCITT((char *)remoteTransportName.c_str(), 
                                    (char *)"Virtual", (char *)family.c_str(), (char *)"MTP3 SCTP", virtualInfo);
                            if(retVal == ITS_ENOMEM)
                            {
                                DLOG_ERROR(" Failed to Set BorderPool for Remote EndPoint errorCode = %d ", retVal);
                                continue;
                            }
                            DLOG_DEBUG("RemoteEndPoint Configured Successfully Transport Instance Configured : %d", retVal);
                            transportInstance = retVal;
                        }
                        else
                        {
                            DLOG_ERROR("IwfController::PopulateAssociationConfig: Mandatory Paramter Missing in Remote EndPoint..!!");
                            return !ITS_SUCCESS;
                        }
                    }
                    else
                    {
                        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing EndPoint Configuration..!!");
                        return CMAPI_ERROR;
                    }

                    if(assocCfg.has_localendpoint())
                    {
                        IwfSigtranSctpEndPointConfig localEndPoint = assocCfg.localendpoint();
                        localInfo.data.sctpSpecs.numExtraHomes = localEndPoint.multihominginfo_size();
                        if (localInfo.data.sctpSpecs.numExtraHomes > 0)
                        {
                            localInfo.data.sctpSpecs.extraHomes = (char**)malloc
                                ((localEndPoint.multihominginfo_size()) * sizeof(char*));
                            for(int numExtrahomes = 0; numExtrahomes < localInfo.data.sctpSpecs.numExtraHomes; numExtrahomes++)
                            {
                                IwfSigtranMultihomingConfig multiHomingInfo = localEndPoint.multihominginfo(numExtrahomes);
                                if(multiHomingInfo.has_otheripaddress())
                                {
                                    localInfo.data.sctpSpecs.extraHomes[numExtrahomes] = (char*)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                                    strcpy(localInfo.data.sctpSpecs.extraHomes[numExtrahomes],
                                            multiHomingInfo.otheripaddress().c_str());
                                }
                            }
                        }

                        localInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
                        if(localEndPoint.has_endpointtype())
                        {
                            endPointType = localEndPoint.endpointtype(); 
                        }
                        if(localEndPoint.has_endpointname() && localEndPoint.has_ipaddress() && localEndPoint.has_port())
                        {
                            localTransportName = localEndPoint.endpointname();
                            localTransportName += assocCfg.associationname();
                            localInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            strcpy(localInfo.data.sctpSpecs.udpPart.localHost, localEndPoint.ipaddress().c_str());

                            localInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            sprintf(localInfo.data.sctpSpecs.udpPart.localPort,"%d", (localEndPoint.port()));

                            localInfo.data.sctpSpecs.udpPart.associates = (char **)malloc(sizeof(char *));
                            localInfo.data.sctpSpecs.udpPart.associates[0] = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                            strcpy(localInfo.data.sctpSpecs.udpPart.associates[0], remoteTransportName.c_str()); 
                            localInfo.data.sctpSpecs.udpPart.numAssociates = 1;

                            /* family to be taken from preconfigured value in json */
                            retVal = SetBorderPoolTransport_CCITT((char *)localTransportName.c_str(), 
                                    (char *)"Datagram", (char *)family.c_str(), (char *)"MTP3 SCTP", localInfo);
                            if(retVal == ITS_ENOMEM)
                            {
                                DLOG_ERROR(" Failed to Set BorderPool for Local EndPoint errorCode = %d ", retVal);
                                continue;
                            }
                            DLOG_DEBUG("LocalEndPoint Configured Successfully Transport Instance Configured : %d", retVal);
                        }
                        else
                        {
                            DLOG_ERROR("IwfController::PopulateAssociationConfig: Mandatory Paramter Missing in Local EndPoint..!!");
                            return !ITS_SUCCESS;
                        }
                    }
                    else
                    {
                        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing EndPoint Configuration..!!");
                        return CMAPI_ERROR;
                    }

                    TRANSPORT_Control   *tc = NULL;
                    int count = 0;
                    DLOG_INFO("Entering TRANSPORT Find LOOP");
                    while(tc == NULL)
                    {
                        usleep(100);
                        tc = TRANSPORT_FindTransport(transportInstance);
                        count++;
                        /* Checking the count for maximum 1 sec if still we
                         * are not able to find the transportInstance exit 
                         * IWF Application */
                        if(count == IWF_WAIT_MAX_COUNT)
                        {
                            DLOG_INFO("Not able to find transportInstance Exiting Application ");
                            _exit(0);
                        }
                    }
                    DLOG_INFO("Exit TRANSPORT Find LOOP, transportInstance found");

                    if(assocCfg.has_associationmappingid())
                    {
                        if((retVal = MTP3_OSS_AddLink_CCITT(linkSet, (ITS_OCTET) assocCfg.associationmappingid(), transportInstance)) != ITS_SUCCESS)
                        {
                            DLOG_ERROR("Addition of Association failed, Error %d", retVal);
                            continue;
                        }
                        DLOG_DEBUG("Association Configured Successfully");
                        if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
                        {
                            IwfSigtranSctpEndPointConfig remoteEndPoint = assocCfg.remoteendpoint();
                            if(remoteEndPoint.has_ipaddress() && remoteEndPoint.has_port() && assocCfg.has_routingkey() && assocCfg.has_homeip())
                            {
                                DLOG_DEBUG("Adding entry to RoutingKey Map with Ip %s port %d routingKey %d homeIp %s",
                                        remoteEndPoint.ipaddress().c_str(),remoteEndPoint.port(),assocCfg.routingkey(), assocCfg.homeip().c_str());
                                IwfController::Instance().Config().LocalConfig().InsertEntryinRoutkingKeyMap(remoteEndPoint.ipaddress().c_str(),
                                        remoteEndPoint.port(),assocCfg.routingkey(), assocCfg.homeip().c_str());
                                
                                for(int numExtrahomes = 0; numExtrahomes < remoteEndPoint.multihominginfo_size(); numExtrahomes++)
                                {
                                    IwfSigtranMultihomingConfig multiHomingInfo = remoteEndPoint.multihominginfo(numExtrahomes);
                                    if(multiHomingInfo.has_otheripaddress())
                                    {
                                        DLOG_DEBUG("Adding entry to RoutingKey Map with Secondary Ip %s port %d routingKey %d homeIp %s",
                                                multiHomingInfo.otheripaddress().c_str(),remoteEndPoint.port(),assocCfg.routingkey(),
                                                assocCfg.homeip().c_str());
                                        IwfController::Instance().Config().LocalConfig().InsertEntryinRoutkingKeyMap(
                                                multiHomingInfo.otheripaddress().c_str(),remoteEndPoint.port(),assocCfg.routingkey(),
                                                assocCfg.homeip().c_str());
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing AssocaitionMappingId..!!");
                        return CMAPI_ERROR;
                    }
                }
            }
            else
            {
                DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing AssocaiationSetAspId..!!");
                retVal = CMAPI_ERROR;
            }
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: No AssocaiationConfig Present..!!");
        retVal = CMAPI_ERROR;
    }
    DLOG_DEBUG("IwfController::PopulateAssociationConfig Exit");
    return retVal;
}

int IwfController::PopulateRemoteRouteConfig(const IwfSigtranRemoteRoutesConfig& refRemoteRoute)
{
    ScopedLogger scopedLogger(this->GetLogger());
    DLOG_DEBUG("IwfController::PopulateRemoteRouteConfig Entry");
    int retVal = CMAPI_SUCCESS;
    int numOfRoute = 0;
    IwfSigtranRemoteRouteConfig remoteRoute;
    IwfSigtranDestinationConfig destInfo;
    ITS_OCTET linkSet;
    ITS_UINT priority = 0;
    ITS_UINT rpc;
    ITS_OCTET ssn;
    ITS_OCTET sio;
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();

    numOfRoute = refRemoteRoute.remoterouteinfo_size();
    if( numOfRoute > 0)
    {
        for( int currRoute = 0 ; currRoute < numOfRoute; currRoute++ )
        {
            remoteRoute = refRemoteRoute.remoterouteinfo(currRoute);
            if(remoteRoute.has_associationsetid() && remoteRoute.has_destinationinfo() && remoteRoute.has_priority())
            {
                destInfo = remoteRoute.destinationinfo();
                if(destInfo.has_pointcode() && destInfo.has_ssn() && destInfo.has_networkindicator())
                {
                    linkSet = (ITS_OCTET)remoteRoute.associationsetid();
                    priority = remoteRoute.priority();
                    rpc = destInfo.pointcode();
                    ssn = (ITS_OCTET)destInfo.ssn();
                    if(destInfo.networkindicator())
                    {
                        DLOG_DEBUG("Network Indicator is National");
                        sio = IWF_NATIONAL_SIO;
                    }
                    else
                    {
                        DLOG_DEBUG("Network Indicator is International");
                        sio = IWF_INTERNATIONAL_SIO;
                    }
                    /* TODO : To call the Sigtran Api's for ANSI in else case same as CCITT */
                    if((retVal = MTP3_OSS_AddRemotePC_CCITT(rpc, sio, ssn, linkSet, priority, family)) != ITS_SUCCESS)
                    {
                        DLOG_ERROR("IwfController::PopulateRemoteRouteConfig:: Failed to add RemoteRoute Error %d", retVal);
                    }
                    if( remoteRoute.has_destinationinfo() && retVal == ITS_SUCCESS)
                    {
                        destInfo = remoteRoute.destinationinfo();
                        retVal = IwfController::Instance().Config().
                            Destinations().SetIwfDestinationConfig(&destInfo);
                        if ( retVal != CMAPI_SUCCESS )
                        {
                            retVal = CMAPI_SRVERROR;
                            DLOG_DEBUG("Failed to add Destination Data");
                        }
                        else
                        {
                            DLOG_DEBUG("Successfully Added Destination Data");
                        }
                    }
                }
                else
                {
                    DLOG_ERROR("IwfController::PopulateRemoteRouteConfig:: Missing Mandatory Parameter in DestinationInfo");
                }
            }
            else
            {
                DLOG_ERROR("IwfController::PopulateRemoteRouteConfig:: Missing Mandatory Parameter in RemoteRouteInfo");
            }
        }
    }
    else
    {
        DLOG_ERROR("IwfController::PopulateRemoteRouteConfig no remote route data in request");
        retVal = CMAPI_INVALIDPARAMS;
    }
    DLOG_DEBUG("IwfController::PopulateRemoteRouteConfig Exit");
    return retVal;
}

void IwfController::SetUpdateFromAvaMgr(uint16_t componentId,
        eAccelero::HAComponentStatus newStatus)
{
    int data = true; 
    if(SERVICE_IsStopped())
    {
        //process is already going down, so not setting the conditional variable
        //It might already get  deleted.
        return;
    }
    try
    {
        cmgrAvlblFlag.Set(data);
    }
    catch(...)
    {
        std::cout << "IWF exiting.. Not signalling the config thread." << std::endl;
    }
}

int IwfController::WaitForUpdateFromAvaMgr()
{
    int status = WAIT_TIMEOUT;
    bool bTimeOut = true;
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    try 
    {
        DLOG_DEBUG("waitin for response from avamgr for cmgr status"); 
        while(bTimeOut)        
        {
            if(!cmgrAvlblFlag.Get(status,IWF_AVAMGR_UPDATE_TIMEOUT))
            {
                DLOG_DEBUG("timeout happent when waiting for response from avamgr"); 
                bTimeOut = true;
                status = WAIT_TIMEOUT;
            }
            else
            {
                DLOG_DEBUG("received update from avamgr"); 
                bTimeOut = false;
                status = RECEIVED_UPDATE; 
                break;
            }

            if(SERVICE_IsStopped())
            {
                DLOG_DEBUG("Process is stopped"); 
                status = PROCESS_STOPPED;
                break;
            }
        }
    }
    catch(eAccelero::SyncException &e) 
    {
        DLOG_DEBUG("Sync Exception while waiting for Status update from avamgr");        
    }
    return status;
}

void IwfController::UpdateIWFStatus(HAComponentStatus status)
{
    m_iwfMeSS.UpdateComponentSelfStatus(status);
}

void IwfController::InitTrace()
{
    /*
    TraceSubSystem::GetTrace().SetSubSystemName("DRE");

    // Add the trace levels to the subsystem.
    TraceSubSystem::
    GetTrace().AddLevel(DRE_DEBUG, AppDebugTrace);
    TraceSubSystem::
    GetTrace().AddLevel(DRE_WARNING,
    AppWarningTrace);
    TraceSubSystem::
    GetTrace().AddLevel(DRE_ERROR,
    AppErrorTrace);
    TraceSubSystem::
    GetTrace().AddLevel(DRE_CRITICAL,
    AppCriticalTrace);
    
    //Turn on APP's trace levels (based on IntelliSS7  trace mechanism).
    this->EnableTrace();
    */
    const char* tracePath = NULL; //getenv("DRE_SESS_TRACE_PATH");
    if
    (tracePath == NULL)
    {    
    tracePath = "./";
    }    
    //Intitialize session tracing
    DiaTracer::Init(tracePath,&IwfController::TraceRuleRemoveHandler);
    DiaTracer::SetTraceStatus(false);
}

void IwfController::TraceRuleRemoveHandler(uint16_t ruleId, void *ruleData, void *arg)
{
    // ruleData is the session id
    DiaVarHandler::RuleRemovalHandler(ruleId, ruleData, arg);
}

eAccelero::Logger& IwfController::GetLogger()
{
    return m_logger;
}

void IwfController::SetLogChannel(const unsigned int channel)
{
    if(channel == Logger::EACC_CHANNEL_SYSLOG)
    {
        this->GetLogger().SetLogChannel(&(IwfController::m_syslogChannel));
    }
    else if (channel == Logger::EACC_CHANNEL_FILE)
    {
        //Commented to avoid log file being created in /var/log/dre
        //this->GetLogger().SetLogChannel(&m_fileLogChannel);
    }    
    else 
    {    
        this->GetLogger().SetLogChannel(ConsoleLogChannel::Instance());
    }    
}

void IwfController::SetLogLevel(const unsigned int level)
{
    this->GetLogger().SetLevel((Logger::Level)(int)level);
    m_iwfMeSS.SetLogLevel(level);
}

void IwfController::SetLogConfig(const unsigned int channel,const unsigned int level)
{
    SetLogChannel(channel);
    SetLogLevel(level);
}

bool IwfController:: SetDiaStackLogLevel(int level)
{
    ScopedLogger scopedlogger(this->GetLogger());
    if(level == eAccelero::Logger::EACC_LOG_INFO || level == eAccelero::Logger::EACC_LOG_NOTICE)
    {
        DLOG_DEBUG("Setting Diameter Stack log level to Error,Critical,Warning");
        DiaTrace::GetDiaTrace()->Disable();
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
        DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
    }
    else if(level ==  eAccelero::Logger::EACC_LOG_WARNING)
    {
        DLOG_DEBUG("Setting Diameter Stack log level to Warning");
        DiaTrace::GetDiaTrace()->Disable();
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
        DiaTrace::GetDiaTrace()->Enable(DIA_WARNING);
    }
    else if(level == eAccelero::Logger::EACC_LOG_CRITICAL)
    {
        DLOG_DEBUG("Setting Diameter Stack log level to Critical");
        DiaTrace::GetDiaTrace()->Disable();
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
    }
    else if(level == eAccelero::Logger::EACC_LOG_ERROR)
    {
        DLOG_DEBUG("Setting Diameter Stack log level to Error");
        DiaTrace::GetDiaTrace()->Disable();
        DiaTrace::GetDiaTrace()->Enable(DIA_CRITICAL);
        DiaTrace::GetDiaTrace()->Enable(DIA_ERROR);
    }
    else
    {
        DLOG_DEBUG("Setting Diameter Stack log level to Debug");
        DiaTrace::GetDiaTrace()->Disable();
        DiaTrace::GetDiaTrace()->Enable();
    }
    return true;
}

int IwfController::PopulateLoggerConfig()
{
    ScopedLogger scopedLogger(this->GetLogger());
    LoggerConfResp logResp;
    int numComp;
    int retVal = ITS_SUCCESS;

    if(m_cmapiConfigObj->GetLoggerConfiguration(true,&logResp) == CMAPI_SUCCESS &&
            logResp.has_responseid() && logResp.responseid() == CMAPI_SUCCESS)
    {
        DLOG_INFO("Received logger configuration from database");
        numComp = logResp.loggerconfig_size();
        if(numComp > 0)
        {
            for(int curComp = 0 ; curComp < numComp ; curComp++)
            {
                LoggerConf logConfig = logResp.loggerconfig(curComp);
                if(logConfig.has_componentname() && logConfig.has_channel()
                        && logConfig.has_level())
                {
                    string compName = logConfig.componentname();
                    const unsigned int channel = (unsigned int) logConfig.channel();
                    const unsigned int level = (unsigned int ) logConfig.level();

                    if((compName.compare("IWF")) == 0)
                    {
                        SetLogConfig(channel,level);
                        //set the log level for Dia Stack to DRE's Log Level
                        SetDiaStackLogLevel(level);
                        DLOG_DEBUG("Successfully set Log configuration for IWF ");
                    }
                    else
                    {
                        DLOG_ERROR("Unknown Component");
                    }
                }
            }
        }
        else
        {
            DLOG_ERROR("No logger config data from database");
            retVal = !ITS_SUCCESS;
        }
    }    
    else
    {
        DLOG_ERROR("CMAPI Error in Fetching Logger Configuratiion");
        retVal = !ITS_SUCCESS;
    }
    return retVal;
}

int IwfController::PopulateDccaConfig(const IwfDccaConfig& refDccaConfig)
{
    ScopedLogger scopedLogger(this->GetLogger());
    int retVal = ITS_SUCCESS;
    
    if (refDccaConfig.has_iwfdccageninfo())
    {
        IwfDccaGenConfig genConfig = refDccaConfig.iwfdccageninfo();
        DLOG_DEBUG("fetched IWF Dcca General configuration");
        for( int currConfig = 0 ; currConfig < genConfig.iwfdccafeatures_size(); currConfig++)
        {    
            IwfDccaFeatureConfig dccaConfig = genConfig.iwfdccafeatures(currConfig);
            if (dccaConfig.dccafeaturename() == TX_TIMEOUT_STR)
            {    
                DLOG_DEBUG("Received Dcca Tx timeout %d sec",dccaConfig.dccavalue());
                IwfController::Instance().Config().DCCAConfig().SetTxTimeout(dccaConfig.dccavalue()); 
            }    
            else if (dccaConfig.dccafeaturename() == INITIAL_ACTION_STR)
            {    
                DLOG_DEBUG("Received Dcca Initial Action %d sec",dccaConfig.dccavalue());
                IwfController::Instance().Config().DCCAConfig().SetInitialCCFHAction((IwfCCFHAction)dccaConfig.dccavalue()); 
            }    
            else if (dccaConfig.dccafeaturename() == UPDATE_ACTION_STR)
            {    
                DLOG_DEBUG("Received Dcca Update Action %d sec",dccaConfig.dccavalue());
                IwfController::Instance().Config().DCCAConfig().SetUpdateCCFHAction((IwfCCFHAction)dccaConfig.dccavalue()); 
            }    
            else 
            {    
                DLOG_ERROR("Invalid Dcca feature :%s value : %d",dccaConfig.dccafeaturename().c_str(), dccaConfig.dccavalue());
            }
        }
    }
    if (refDccaConfig.has_iwfdccadestsinfo())
    {
        IwfDccaDestsConfig destsConfig = refDccaConfig.iwfdccadestsinfo();
        DLOG_DEBUG("Fetched IWF Dcca Destination configuration");
        for( int currConfig = 0 ; currConfig < destsConfig.iwfdccadestinfo_size(); currConfig++)
        {
            IwfDccaDestConfig dccaDest = destsConfig.iwfdccadestinfo(currConfig);
            if( dccaDest.iwfdccaendpoints_size() > 0 && dccaDest.has_destname() && dccaDest.has_sendccrtindicator())
            {
                std::string dccaDestName = dccaDest.destname();
                DLOG_DEBUG("Received Dcca Destination Name %s",dccaDest.destname().c_str());
                for( int currDest = 0 ; currDest < dccaDest.iwfdccaendpoints_size() ; currDest++ )
                {
                    IwfDccaEndPointConfig dccaEndpoint = dccaDest.iwfdccaendpoints(currDest);
                    DLOG_DEBUG("Dcca Endpoint name : %s priority : %d",dccaEndpoint.endpointname().c_str(),dccaEndpoint.priority());
                    
                    bool sendCCRTFlg;
                    DLOG_DEBUG("SendCCRTFlag = %d",dccaDest.sendccrtindicator());
                    if(dccaDest.sendccrtindicator())
                        sendCCRTFlg = true;
                    else
                        sendCCRTFlg = false;
                    if ( IwfController::Instance().Config().DCCAConfig().
                            GetDestinations().AddEndpoint(dccaDestName,dccaEndpoint.endpointname(),dccaEndpoint.priority(),sendCCRTFlg) )
                    {
                        DLOG_DEBUG("Successfully added Dcca Destination Endpoint Configuration");
                    }
                    else
                    {
                        DLOG_ERROR("Failed to add Dcca Endpoint : %s in Destination : %s",
                                dccaEndpoint.endpointname().c_str(),dccaDestName.c_str());
                    }
                }
            }
            else
            {
                DLOG_ERROR("Invalid Dcca Destination configuration missing mandatory parameter");
            }
        }
    }
    return retVal;
}

void IwfController::PopulateReplicationFreeList()
{
    cout<<"IwfController::PopulateReplicationFreeList() entry"<<endl;
    m_freeListGuard.Acquire();
    m_freeList.clear();
    uint32_t maxSessions = MAX_BULK_FETCH_SIZE;

    if (IwfController::Instance().Config().LocalConfig().isCongestionManagementEnabled())
    {
        maxSessions =  IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold();
    }

    for(uint32_t i=0 ; i< maxSessions; i++)
    {
        m_freeList.push_back(i);
    }
    m_freeListGuard.Release();
    cout<<"IwfController::PopulateReplicationFreeList() exit"<<endl;
}

uint32_t IwfController::GetNextReplicationEntryFromFreeList()
{
    uint32_t nextEntry = 0xffffffff;
    m_freeListGuard.Acquire();
    if ( m_freeList.size() > 0 )
    {
        nextEntry = m_freeList.front();
        m_freeList.erase(m_freeList.begin());
    }
    m_freeListGuard.Release();
    return nextEntry;
}

int IwfController::SetReplicationEntryToFreeList(uint32_t freeKey)
{
    m_freeListGuard.Acquire();
    if ( freeKey != 0xffffffff)
    {
        m_freeList.push_back(freeKey);
    }
    m_freeListGuard.Release();
    return ITS_SUCCESS;
}

int IwfController::RemoveReplicationEntryFromFreeList(uint32_t freeKey)
{
    m_freeListGuard.Acquire();
    if (freeKey != 0xffffffff)
    {
	std::vector<uint32_t>::iterator position = std::find(m_freeList.begin(), m_freeList.end(), freeKey);
	if (position != m_freeList.end()) {// the element was found
	    m_freeList.erase(position);
	}
    }
    m_freeListGuard.Release();
    return ITS_SUCCESS;
}

void IwfController::SetNodeStatus(bool isNodeActive)
{
    m_isNodeActive = isNodeActive;    
}

bool IwfController::GetNodeStatus()
{
    return m_isNodeActive;
}

void IwfController::GoActive()
{

    std::vector<std::string> outData;
    CLOG_INFO("Iwf Going Active");
    DiaFrame *diaFrame = NULL;
    ITS_SetNodeState(ITS_STATE_PRIMARY);
    gisShutdownInProgress = false;
    if(!(IwfController::GetNodeStatus()))
    {
        IwfController::SetNodeStatus(true);
        IwfController::Instance().SetIsBulkFetchSuccess(false);
        /* Fetch the IwfFsm entries from CB here */
        if (LICENSE_VerifyCapability(ITS_LIC_IWF_CAP_RO_TSL) && IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
        {
            TransactionManager::Instance()->AcquireBulkFetchLock();
        }

        if(!initialized)
        {
            diaFrame = DiaFrame::InitDiaFrame();
            initialized = true;
        }
        else
        {
            diaFrame = DiaFrame::GetDiaFrame();
        }

#if 0
        if (itsDiaConfig.IsInterWorkingMode())
        {
            if( IwfController::Instance().InitDiameterStack(true) != ITS_SUCCESS )
            {
                cout << "IwfController InitDiaStack failed, Check the Diameter local configuration and restart IWF" <<endl;
                DLOG_DEBUG("IwfController InitDiaStack failed, Check the Diameter local configuration and restart IWF");
            }

            if( IwfController::Instance().InitSigTranStack(true) != ITS_SUCCESS )
            {
                cout << "IwfController InitSigTranStack failed, Chekc the Sigtran Local configurtioan and restart IWF" << endl;
                DLOG_DEBUG("IwfController InitSigTranStack failed, Chekc the Sigtran Local configurtioan and restart IWF");
            }

        }
#endif

        if (diaFrame)
        {
            if (diaFrame->GoActive())
            {
                CLOG_CRITICAL("Failed to Be Active.");
                //Exit from here..so that other node takes over?
                _exit(0);
            }
        }

        /* Fetch the IwfFsm entries from CB here */
        if (LICENSE_VerifyCapability(ITS_LIC_IWF_CAP_RO_TSL) && IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
        {
            /*Post the Event to Create the Tcap Transaction Entry */

            int retVal = PB_REPL_UTILS_SUCCESS;
            int retry = 0;
            uint32_t maxSessions = MAX_BULK_FETCH_SIZE;

            /*Bulk Fetch*/
            //for( ; retry < MAX_BULKFETCH_RETRY ; retry++)
            {
                IwfController::PopulateReplicationFreeList();
                TransactionManager::Instance()->SetRebalancingStatus(true);
                retVal = ReplicableData::FetchBulkEntriesInReplica(IWF_SESSION_ENTRY_LIST,
                        LIST_START,LIST_INITIAL,outData);
                CLOG_DEBUG("BulkFetch for initial entries ret val : %d",retVal);
                if ((retVal == PB_REPL_UTILS_SUCCESS) || (retVal == REPL_KEY_ENOENT))
                {
                    if (!outData.empty())
                    {
                        outData.clear();
                    }

                    if (IwfController::Instance().Config().LocalConfig().isCongestionManagementEnabled())
                    {
                        maxSessions =  IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold();
                    }

                    retVal = ReplicableData::FetchBulkEntriesInReplica(IWF_SESSION_ENTRY_LIST,
                            LIST_START, maxSessions, outData);
                    CLOG_DEBUG("BulkFetch for all entries ret val : %d",retVal);
                    if ((retVal == PB_REPL_UTILS_SUCCESS) || (retVal == REPL_KEY_ENOENT))
                    {
                        TransactionManager::Instance()->SetBulkFetchIwfFsmCount(outData.size());
                        int dataSize = outData.size();
                        for(int currFsm = 0; currFsm < dataSize ; currFsm++)
                        {
                            pbIwfFsmInfo iwfFsm;
                            std::string tmpStr = outData[currFsm];
                            iwfFsm.ParseFromArray(tmpStr.c_str(), tmpStr.length());

                            CLOG_DEBUG("Extraced Fsm Data %s",iwfFsm.DebugString().c_str());
                            TransactionManager::Instance()->CreateTcapTransactionEntryFromReplica(iwfFsm, (currFsm == (dataSize - 1)));
                            TransactionManager::Instance()->CreateDiameterSessionEntry(iwfFsm);
                            TransactionManager::Instance()->CreateIwfFsmFromReplica(iwfFsm);
                            IwfController::RemoveReplicationEntryFromFreeList(iwfFsm.freelistkey());
                        }
                        CLOG_DEBUG("Successsfully FetchBulkEntriesInReplica for %d entries ",dataSize);
                        /* Set this flag to true if bulkfetch is success based on this we will trigger
                         * ASP_Active to MSC */
                        IwfController::Instance().SetIsBulkFetchSuccess(true);
                        //break;
                    }
                    else
                    {
                        CLOG_DEBUG("BulkFetch failed retry for count %d.....",retry);
                    }

                }
                else 
                {
                    CLOG_DEBUG("BulkFetch for intial entries failed return val : %d",retVal);
                    CLOG_DEBUG("BulkFetch failed retrying for count %d",retry+1);
                }
            }

            // If gettting from the Couchbase fails get it from the local data
            CLOG_DEBUG("Checking If BulkFetch from CB is successful : %d", IwfController::Instance().GetIsBulkFetchSuccess());
            if ((IwfController::Instance().GetIsBulkFetchSuccess() == false))
            {
                IwfController::Instance().SetIsBulkFetchSuccess(true);
                TransactionManager::Instance()->PerformLocalBulkFetch(outData);
                CLOG_DEBUG("Local BulkFetch  returned [%d] entries", outData.size());
                int dataSize = outData.size();
                for(int currFsm = 0; currFsm < dataSize ; currFsm++)
                {
                    pbIwfFsmInfo iwfFsm;
                    std::string tmpStr = outData[currFsm];
                    iwfFsm.ParseFromArray(tmpStr.c_str(), tmpStr.length());

                    CLOG_DEBUG("Extraced Fsm Data %s",iwfFsm.DebugString().c_str());
                    TransactionManager::Instance()->CreateTcapTransactionEntryFromReplica(iwfFsm, (currFsm == (dataSize - 1)));
                    TransactionManager::Instance()->CreateDiameterSessionEntry(iwfFsm);
                    TransactionManager::Instance()->CreateIwfFsmFromReplica(iwfFsm);
                    IwfController::RemoveReplicationEntryFromFreeList(iwfFsm.freelistkey());
                }
                CLOG_DEBUG("Successsfully FetchBulkEntriesInReplica for %d entries ", dataSize);
                CLOG_DEBUG("Starting the timer for flushing the stale entries");
                IwfController::Instance().StartBulkFetchTimer();
            }
            TransactionManager::Instance()->ReleaseBulkFetchLock();
            IwfController::Instance().StartPendingQueueExpiryTimer();
// Now we have periodic bulk fetch during standby, we dont retry while going active
#if 0
            /* Set the BulkFetchSuccess to true in case where the BulkFetch failed for 
             * Max. retries and if MSC went down and came up this flag is used to 
             * initiate ASP_AC. */
            if ((retry == MAX_BULKFETCH_RETRY) && 
                (IwfController::Instance().GetIsBulkFetchSuccess() == false))
            {
                CLOG_DEBUG("Maximum retries for BulkFetch failed setting SetIsBulkFetchSucess to success to avoid failure of new calls");
                IwfController::Instance().SetIsBulkFetchSuccess(true);
                /*Start Timer for BulkFetch which will be tried upon 
                 * timeout again BulkFetch of Session will be retried*/
                CLOG_DEBUG("Starting timer for BulkFetch to be retired..");
                uint32_t bulkfetchRetry = IwfController::Instance().GetBulkFetchRetryCount();
                IwfController::Instance().SetBulkFetchRetryCount(bulkfetchRetry+1);
                IwfController::Instance().StartBulkFetchTimer();
            }
#endif
        }
        else
        {
            CLOG_DEBUG("setting BulkFetchSuccess if replication is disabled or for Standalone setup.");
            /* Setting this flag to true for StandAlone case */
            IwfController::Instance().SetIsBulkFetchSuccess(true);
        }

        if (LICENSE_VerifyCapability(ITS_LIC_IWF_MAP_S6A))
        {
            CLOG_DEBUG("setting BulkFetchSuccess if replication is disabled or for Standalone setup.");
            /* Setting this flag to true for StandAlone case */
            IwfController::Instance().SetIsBulkFetchSuccess(true);
        }

        /* After creating IWF application context, Tcap Transaction Entries and
         * Diameter Session Entries and DCCA Session Context Invoke SendASPActiveFromApp()
         * method to iterate through all the ASP entries in ASP table and send the
         * ASP_AC message, this is done only for the switchover triggers */
        if ( SendASPActiveFromApp() == ITS_SUCCESS)
        {
            CLOG_DEBUG("Successfully initiated ASP_AC messages to all the connnected ASP's");
        }
        else
        {
            CLOG_ERROR("Failed to initiate ASP_AC messages to connected peers");
        }
    }
    else
    {
        CLOG_DEBUG("Already in Active State, not invoking BulkFech() and SendASPActiveFromApp()");
    }
}

void IwfController::GoStandby()
{
    CLOG_INFO("Iwf Going Standby");
    DiaFrame *diaFrame = NULL;

    /*Setting the Global flag defined in ssg_callback.cpp to avoid processing of any
     * messages,timer events and indication */
    gisShutdownInProgress = true;
    IwfController::SetNodeStatus(false);
    IwfController::Instance().SetIsBulkFetchSuccess(false);
    IwfController::Instance().SetBulkFetchRetryCount(0);

    if (!IwfController::Instance().Config().LocalConfig().IsSendASPActiveFromStandBySet())
    {
        CLOG_DEBUG("Send ASPInactive");
        SendASPINACTIVE();
    }

    if(!initialized)
    {
        diaFrame = DiaFrame::InitDiaFrame();
        initialized = true;
    }
    else
    {
        diaFrame = DiaFrame::GetDiaFrame();
    }

    CLOG_DEBUG("Initiating ASP Inactive and ASP Down Messages to all connected AS's");
    


    if (diaFrame)
    {
        if (diaFrame->GoStandby())
        {
            CLOG_CRITICAL("Failed to Become Standby");
            //Exit from here..so that other node takes over?
            _exit(0);
        }
    }

    /*Invoke the TransactionManager::Destroy to clear all the FSM context */
    TransactionManager::Destroy();

    if (IwfController::Instance().GetNodeStatus())
    {
        IwfController::Instance().m_becameStandby = false;
    }
    else
    {
        IwfController::Instance().m_becameStandby = true;
    }

    // Since we are going standby, start the bulk fetch timer again
    IwfController::Instance().StartBulkFetchTimer();
}

int IwfController::ReplStatusCbk(bool status)
{
    
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    CLOG_DEBUG("ReplicationStatusCbk called: status=%d",status);
    if(status)
    {    
        CLOG_DEBUG("Enabling Replication");
        //Replication client initialization is successful.
        IwfController::Instance().EnableReplication();
    }    
    else 
    {    
        CLOG_WARNING("Disabling Replication");
        diaFrame->disableReplication();
        IwfController::Instance().m_iwfMeSS.DisableReplication();
    }    
   
}

void IwfController::EnableReplication()
{
    DiaFrame *diaFrame = DiaFrame::InitDiaFrame();
    diaFrame->enableReplication();

    if(!IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
    {    
        /* if previously  replication client initialization failed and we have 
         * disabled replication enable it */
        IwfController::Instance().m_iwfMeSS.EnableReplication();
    }    
}

IwfAlarms* IwfController::GetIwfAlarmInstance()
{
    return m_iwfAlarms;
}

void IwfController::SetIsBulkFetchSuccess(bool isBulkFetchSuccess)
{
    m_isBulkFetchSuccess = isBulkFetchSuccess; 
}

bool IwfController::GetIsBulkFetchSuccess()
{
    return m_isBulkFetchSuccess;
}

void IwfController::StartBulkFetchTimer()
{
    CLOG_DEBUG("StartBulkFetchTimer entry");

    if (m_isBulkFetchTimerRunning)
    {
        CLOG_DEBUG("BulkFetchTimer already running...");
        return;
    }
    STimerContext sTimerCtxt;
    sTimerCtxt.m_eKeyType = EKeyType::BULK_FETCH;
    sTimerCtxt.m_eTimerType = IWF_BULK_FETCH_TIMER;
    IwfTimer timerObj;
    unsigned int timerId;
    timerId = timerObj.StartTimer(sTimerCtxt.m_eTimerType,sTimerCtxt,IWF_BULKFETCH_TIMEOUT);
    m_isBulkFetchTimerRunning = true;

    CLOG_DEBUG("Started BulkFetchTimer for duration %d",IWF_BULKFETCH_TIMEOUT);

    STimerInfo timerInfo;
    timerInfo.m_eTimerType = sTimerCtxt.m_eTimerType;
    timerInfo.m_uiDuration = IWF_BULKFETCH_TIMEOUT;
    timerInfo.m_uiTimerId = timerId;
    
    IwfController::Instance().SetBulkFetchTimerInfo(timerInfo);
    CLOG_DEBUG("StartBulkFetchTimer exit");
}

void IwfController::SetBulkFetchTimerInfo(STimerInfo& timerInfo)
{
    m_stimerInfo = timerInfo;
}

STimerInfo& IwfController::GetBulkFetchTimerInfo()
{
    return m_stimerInfo;
}

void IwfController::StopBulkFetchTimer()
{
    CLOG_DEBUG("StopBulkFetchTimer entry");
    IwfTimer timerObj;
    STimerInfo timerInfo = IwfController::Instance().GetBulkFetchTimerInfo();
    if(ITS_SUCCESS == timerObj.StopTimer(timerInfo.m_uiTimerId))
    {
        CLOG_DEBUG("StopBulkFetchTimer:: TimerType : IWF_BULKFETCH_TIMER, TimerId : %u stopped.",
                timerInfo.m_uiTimerId);
    }
    SetIfBulkFetchTimerRunning(false);
    CLOG_DEBUG("StopBulkFetchTimer exit");
}

void IwfController::StartPendingQueueExpiryTimer()
{
    CLOG_DEBUG("StartPendingQueueExpiryTimer entry");

    STimerContext sTimerCtxt;
    sTimerCtxt.m_eKeyType = EKeyType::PENDING_QUEUE_EXPIRY;
    sTimerCtxt.m_eTimerType = IWF_PENDING_QUEUE_EXPIRY;
    IwfTimer timerObj;
    unsigned int timerId;
    timerId = timerObj.StartTimer(sTimerCtxt.m_eTimerType, sTimerCtxt, IwfController::Instance().Config().LocalConfig().GetPendingQueueExpiryTime());

    CLOG_DEBUG("Started pending queue expiry for duration %d", IwfController::Instance().Config().LocalConfig().GetPendingQueueExpiryTime());

    CLOG_DEBUG("StartPendingQueueExpiryTimer exit");
}
