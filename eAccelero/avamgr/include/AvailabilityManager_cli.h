/* 
 * File:   AvailabilityManager_cli.h
 * Author: adey
 *
 * Created on July 10, 2012, 6:43 PM
 */

#ifndef AVAILABILITYMANAGER_CLI_H
#define	AVAILABILITYMANAGER_CLI_H

#include "HAMeSSComponent.h"

struct AvaMgrConfigSetLogLevelReq {
	Logger::Level uiConfigSetLogLevelReq;
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

struct AvaMgrConfigPrimaryVirtualIpAddressReq {
    char cConfigPrimaryVirtualIpAddress[64];
};

struct AvaMgrConfigSecondaryVirtualIpAddressReq {
    char cConfigSecondaryVirtualIpAddress[64];
};

struct AvaMgrConfigGatewayIpAddressReq {
    char cConfigGatewayIpAddress[64];
};

struct AvaMgrConfigRestartReq {
	uint16_t componentId;
	uint16_t instanceId;
};

struct AvaMgrConfigResp {
	int respCode;
};

struct AvaMgrShowProcessResp {
    std::string setProcessNames[64];
};

#endif	/* AVAILABILITYMANAGER_CLI_H */

