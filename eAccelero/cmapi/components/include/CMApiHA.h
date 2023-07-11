
#ifndef _CMAPIHA_H_
#define _CMAPIHA_H_

#include "AvaMgrHAInterface_caller.h"
#include "RepMgrHAInterface_caller.h"
#include "DreHAInterface_caller.h"
#include "CMgrHAInterface_caller.h"
#include "HA.pb.h"

using namespace std;

class CMApiHA : public Stub::AvaMgrHAInterfaceRespCbk,  public Stub::RepMgrHAInterfaceRespCbk,
    public Stub::CMgrHAInterfaceRespCbk, public Stub::DreHAInterfaceRespCbk
{
    public:

        CMApiHA() {}
        ~CMApiHA() {}
    
        // LIbrary API - User Callable.
        int InitializeLibrary();

        int SetAMPeerPingPeriodicity(int PingPeriodicity);
        int SetAMArbitratorPingPeriodicity(int ArbPingPeriodicity);
        int SetAMMaximumPingACKReceiveFailures(int MaxValue);
        int SetAMMaximumArbPingACKReceiveFailures(int MaxValue);
        int SetAMProcessRestartMAXAllowedInterval(int MaxValue);
        int SetAMProcessRestartMaxAllowedCount(int MaxValue);
        int SetAMArbitratorIpAddress(string IPAddress);
        int SetAMVirtualAddressInfo(string VirtualIpAddresses, string EthernetInterfaces);
        int GetAMConfiguration(AvaMgrConfig *AvaMgrData,AvaMgrConfigResp* Response);
        int GetRMConfiguration(RepMgrConfig *RepMgrData);
        int SetDREReplicationFlag(bool ReplicateData);
        int GetDREHAConfiguration(DreHAConfig *DreHAData);

        int GetNodeStatus(string& nodeStatus,AvaMgrConfigResp* Response);
        int SwitchOver(AvaMgrConfigResp* Response);

        // Internal DON't Call
        int AvaMgrSetConfigurationRespCbk(AvaMgrConfigResp *Response);
        int AvaMgrGetConfigurationRespCbk(AvaMgrConfigResp *Response);
        int AvaMgrSwitchOverRequestRespCbk(AvaMgrConfigResp *Response);
        int DreSetConfigurationRespCbk(DreHAConfigResp *Response);
        int RepMgrSetConfigurationRespCbk(RepMgrConfigResp *Response);

        int CMgrAMSetConfigurationRespCbk(AvaMgrConfigResp *Response);
        int CMgrRMSetConfigurationRespCbk(RepMgrConfigResp *Response);
        int CMgrDreSetConfigurationRespCbk(DreHAConfigResp *Response);
        int FetchAvaMgrConfigurationRespCbk(AvaMgrConfigResp *Response);
        int FetchRepMgrConfigurationRespCbk(RepMgrConfigResp *Response);
        int FetchDreHAConfigurationRespCbk(DreHAConfigResp *Response);

        // Hack -- Response setter from within
        int SetData(int requestId, int retCode);

    private:

        // Methods
        int SendCMgrRequest(AvaMgrConfig& Request, AvaMgrConfigResp *Response = NULL);
        int SendCMgrRequest(RepMgrConfig& Request, RepMgrConfigResp *Response = NULL);
        int SendCMgrRequest(DreHAConfig&  Request, DreHAConfigResp  *Response = NULL);
        int SendAMRequest(AvaMgrConfig& Request);
        int SendAMRequest(ComponentActionReq& Request, AvaMgrConfigResp *Response);
        int SendRMRequest(RepMgrConfig& Request);
        int SendDRERequest(DreHAConfig& Request);
        //int IsResponseOK();

        // Caller Handlers.
        Stub::AvaMgrHAInterface* m_AMObj;
        Stub::CMgrHAInterface*   m_CMgrObj;
        Stub::DreHAInterface*    m_DREObj;
        Stub::RepMgrHAInterface* m_RMObj;

        // HA Sync Object
        CMAPIIntSync *m_HAResponse;
        static const unsigned int m_waitTime = 32000000;

        // MeSS Send Status
        bool m_SendSuccess;

};


#endif  //_CMAPIHA_H_
