#ifndef __IWF_H__
#define __IWF_H__

#include "iwf_mess.h"
#include "iwf_prot_defines.h"
#include "CMAPIConfig.h"
#include "iwf_config.h"
#include "iwf_transaction_manager.h"
#include "iwf_prot_translator.h"
#include "its_dia_config.h"
#include "ThreadQueue.h"
#include "Logger.h"
#include "iwf.pb.h"
#include "ReplicationClient.h"
#include "iwf_transport_controller.h"
#include "iwf_alarms.h"

// Configuration types
#define DIA_CONFIG_LOCALHOST     1
#define DIA_CONFIG_PEER          2
#define DIA_CONFIG_REALM         4

#define IWF_AVAMGR_UPDATE_TIMEOUT 500000 //500ms

//Replica name to be used during replication
#define IWF_STATE_REPLICATION           "IwfFsmState"
#define IWF_SESSION_ENTRY_LIST          "IwfSessionEntries"
#define IWF_SESSION_CONTEXT_REPLICA     "IwfImsiContextEntries"
#define LIST_START 0
#define LIST_INITIAL 10
#define LIST_END 15000
#define MAX_BULKFETCH_RETRY 5
#define IWF_MAX_REP_DIA_SESSION_DATA_LENGTH 256
#define IWF_REPLICATION_CONFIG "/config/replicationConfig.json"
#define IWF_BULKFETCH_TIMEOUT 5 //30 seconds for bulkfetch timer
#define MAX_IWF_BULKFETCH_TIMEOUT_RETRY  3
#define IWF_PENDING_QUEUE_EXPIRY_TIME 30

enum UpdateStateFromAvaMgr
{
    WAIT_TIMEOUT,
    PROCESS_STOPPED,
    RECEIVED_UPDATE
};

class IwfController
{
    public:
        static const unsigned MaxTranslators = 8;
 
        static void Create(const char *configFile)
        {
            //m_self = new IwfController(configFile);
        }
        static void Init(int &argc, const char **&argv, const char *configFile);

        static IwfController& Instance()
        {
            return *m_self;
        }

        static void Destroy()
        {
            if (m_self)
            {
                delete m_self;
                m_self = NULL;
            }
        }

        // There is no de-register function. Not required for now
        // Returns an id for the translator
        // The Config Parse should be done only after this
        int RegisterTranslator(const std::string& tranStr, IwfTranslator* obj);

        int InitDiameterStack(bool isActive);

        void ApplyStackConfigurations(const StackConfiguration& refStackConfig);

        int PopulateConfig(int configToFetch, const LocalHost& lHostCfg);

        int InitSigTranStack(bool isActive);

        int PopulateLocalHostConfig(const IwfLocalHostConfig& refLocaHostConfig);

        int PopulateUalGeneralConfig(const IwfSigtranUalManagerConfig& refUalManagerCfg);

        int PopulateAssociationSetConfig(const IwfSigtranAssociationSetsConfig& refAssociationSetConfig);

        int PopulateAssociationConfig(const IwfSigtranAssociationsConfig& refAssociationCfg);

        int PopulateRemoteRouteConfig(const IwfSigtranRemoteRoutesConfig& refRemoteRoute);

        int PopulateDccaConfig(const IwfDccaConfig& refDccaConfig);

        IwfConfig& Config()
        {
            return m_config;
        }

        IwfTranslator* GetTranslator(int id)
        {
            if ((id < 0) || (id > (int)(MaxTranslators - 1)))
            {
                return NULL;
            }
            return m_translators[id];
        }
        int GetTranslatorId(const std::string& translStr)
        {
            TranslStrMap::iterator it = m_translStrMap.find(translStr);
            if (it == m_translStrMap.end())
            {
                return IwfTranslator::InvalidId;
            }
            return it->second;
        }
        IwfTranslator* GetTranslator(const std::string& translStr)
        {
            IwfTranslator* obj = NULL;
            int id = this->GetTranslatorId(translStr);
            if (id != IwfTranslator::InvalidId)
            {
                obj = this->GetTranslator(id);
            }
            return obj;
        }

        void UpdateIWFStatus(HAComponentStatus status);
        static int WaitForUpdateFromAvaMgr();
        static void SetUpdateFromAvaMgr(uint16_t componentId,
                eAccelero::HAComponentStatus newStatus);
        //ThreadShared Data for stack initialization.
        static ThreadSharedData<int> cmgrAvlblFlag;
        IwfMeSS m_iwfMeSS;
        iwf::IWFTransportController m_transport;
        static bool initialized;
        ReplicationClient* repClient;

        Logger& GetLogger();

        void InitTrace();
        static void TraceRuleRemoveHandler(uint16_t ruleId, void *ruleData, void *arg);
        void SetLogConfig(const unsigned int channel,const unsigned int level);
        void SetLogLevel(const unsigned int level);
        void SetLogChannel(const unsigned int channel);
        bool SetDiaStackLogLevel(int level);
        int PopulateLoggerConfig();

        int SendEventRsp(TimerEvent &ev);

        static uint32_t GetNextReplicationEntryFromFreeList();

        static int  SetReplicationEntryToFreeList(uint32_t freeKey); 

        static void PopulateReplicationFreeList();

        static int RemoveReplicationEntryFromFreeList(uint32_t usedKey);
        
        static void SetNodeStatus(bool isNodeActive);
 
        static bool GetNodeStatus();

        void SetIsBulkFetchSuccess(bool isBulkFetchSuccess);

        bool GetIsBulkFetchSuccess();

        static void GoActive();

        static void GoStandby();

        static int ReplStatusCbk(bool status);

        void EnableReplication();

        IwfAlarms* GetIwfAlarmInstance();

        void StartBulkFetchTimer();

        void StopBulkFetchTimer();

        void SetIfBulkFetchTimerRunning(bool isItRunning)
        {
            m_isBulkFetchTimerRunning = isItRunning;
        }

        bool IsBulkFetchTimerRunning()
        {
            return m_isBulkFetchTimerRunning;
        }

        void SetBulkFetchTimerInfo(STimerInfo& timerInfo);

        STimerInfo& GetBulkFetchTimerInfo();

        void SetBulkFetchRetryCount(uint32_t retryCount)
        {
            m_bulkFetchMaxRetry = retryCount;
        }

        uint32_t GetBulkFetchRetryCount()
        {
            return m_bulkFetchMaxRetry;
        }

        void StartPendingQueueExpiryTimer();

        bool m_initializationFlagsSet;

        bool m_becameActive;

        bool m_becameStandby;

        Json::Value m_peerStatusRoot;

        std::string m_peerStatusInDb;

    protected:
        friend class IwfConfig;

        IwfController(int& argc, const char **&argv, const char *confFileName = NULL);
        ~IwfController();

        IwfConfig m_config;
        /* pointer to IWF configuration fetch */
        IWFConfigFetch *m_IwfCmapiConfigObj;

        /*pointer to Diameter Stack Configuration fetdh */
        CMAPIConfig* m_cmapiConfigObj;

        // Holds the string to index of m_translators
        typedef std::map<std::string, int> TranslStrMap;
        TranslStrMap m_translStrMap;

        IwfTranslator* m_translators[MaxTranslators];
        eAccelero::Thread* messThread;
        eAccelero::Thread* transportControlThread;
        eAccelero::Logger m_logger;
        eAccelero::SyslogChannel m_syslogChannel;

        static IwfController *m_self;

        IwfAlarms *m_iwfAlarms;

        static its::ITS_Mutex m_freeListGuard;
        static std::vector<uint32_t> m_freeList;

        static bool m_isNodeActive;

        bool m_enableReplication;

        bool m_isBulkFetchSuccess;

        STimerInfo m_stimerInfo;

        uint32_t m_bulkFetchMaxRetry;

        bool m_isBulkFetchTimerRunning;

};


#endif
