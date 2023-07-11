/* 
 * File:   CliInterface.h
 * Author: adey
 *
 * Created on July 10, 2012, 6:43 PM
 */

#ifndef AVAILABILITYMANAGER_CFG_H
#define AVAILABILITYMANAGER_CFG_H

#include "HAMeSSComponent.h"
#include "Logger.h"
//#include "AvailabilityManager.h"

using namespace eAccelero;


struct AvaMgrConfigSetLogChannelReq {
    char componentId[MAX_NAME_LEN];
    char log_channel[MAX_NAME_LEN];
    char logFileName[MAX_NAME_LEN];
    char log_status[MAX_NAME_LEN];
};
struct AvaMgrConfigSetLogLevelReq {
    char componentId[MAX_NAME_LEN];
    //Logger::Level uiConfigSetLogLevelReq;
    char uiConfigSetLogLevelReq[MAX_NAME_LEN];
    char log_status[MAX_NAME_LEN];
};

struct AvaMgrConfigSetAvailabilityStatusReq {
    InstanceAvailabilityStatus instanceAvailabilityStatus;
};

struct AvaMgrConfigPingPeriodicityReq {
    uint16_t uiConfigPingPeriodicity;
};

struct AvaMgrConfigPingPeriodicityForArbitratorReq {
    uint16_t uiConfigPingPeriodicityForArbitrator;
};

struct AvaMgrConfigVirtualInterfaceActivationTimeReq {
    uint16_t uiConfigVirtualInterfaceActivationTime;
};

struct AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeerReq {
    uint8_t uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer;
};

struct AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitratorReq {
    uint8_t uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator;
};

struct AvaMgrConfigProcessRestartMaximumAllowedIntervalReq {
    uint16_t uiConfigProcessRestartMaximumAllowedInterval;
};

struct AvaMgrConfigProcessRestartMaximumAllowedCountReq {
    uint8_t uiConfigProcessRestartMaximumAllowedCount;
};

struct AvaMgrConfigUseIpV6Req {
    bool bConfigUseIpV6;
};

struct AvaMgrConfigSecondaryVirtualIpAddressReq {
    char cConfigSecondaryVirtualIpAddress[64];
};

struct AvaMgrConfigGatewayIpAddressReq {
    char cConfigGatewayIpAddress[64];
};

/*struct AvaMgrConfigPrimaryVirtualIpAddressReq {
  char cConfigPrimaryVirtualIpAddress[64];
  char cConfigDev[64];
  };*/

struct AvaMgrConfigRestartReq {
    uint16_t componentId;
    uint16_t instanceId;
};

struct AvaMgrCfgResp {
    int respCode;
};

struct AvaMgrShowProcessResp {
    std::string setProcessNames[64];
};

#if 0
typedef union _AvaMgrCongifReq {

    struct AvaMgrConfigSetLogLevelReq configLogReq;
    //    struct AvaMgrConfigSetNodeStatusReq configNodeStatus;
    struct AvaMgrConfigPingPeriodicityReq configPingPeriod;
    struct AvaMgrConfigPingPeriodicityForArbitratorReq configArbtrPingPeriod;
    struct AvaMgrConfigVirtualInterfaceActivationTimeReq configVirtualInterfaceActvationT;
    struct AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeerReq configNoofPingAckRecFailure;
    struct AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitratorReq configNoofPingAckRecFromArbtr;
    struct AvaMgrConfigProcessRestartMaximumAllowedIntervalReq configProcessRestartMaxIntrl;
    struct AvaMgrConfigProcessRestartMaximumAllowedCountReq configProcessRestartmaxCnt;
    struct AvaMgrConfigUseIpV6Req configIpV6Req;
    struct AvaMgrConfigPrimaryVirtualIpAddressReq configPrimVirtualIp;
    struct AvaMgrConfigSecondaryVirtualIpAddressReq configSecVirtualIp;
    struct AvaMgrConfigGatewayIpAddressReq configGatewayIp;
    struct AvaMgrConfigRestartReq configRestart;
}AvaMgrConfigInfo;
#endif


#endif  /* AVAILABILITYMANAGER_CFG_H */

