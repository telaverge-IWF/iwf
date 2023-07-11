
#ifndef __IWF_CFG_H__
#define __IWF_CFG_H__
#include <config.h>
#include "CommonStructure.h"

/* SHOW IDs */
#define SH_IWF_STATS 		1
#define SH_PEER_STATUS 		2

typedef struct _IwfPeerConfigReq {
    OpCode_e OP_CODE;
IwfPeerKeyInfo peerKeyInfo;
IwfPeerInfo peerInfo ;
IwfPeerSwitchingInfo peerSwitchingInfo;
IwfPeerTimersConfigPayload drePeerTimerConfigInfo;
}IwfPeerConfigReq; 

typedef struct _IwfRealmConfigReq {
IwfRealmRoutingKeyInfo realmKeyInfo;
IwfRealmRoutingInfo realmInfo;
}IwfRealmConfigReq;

typedef struct _IwfDefaultRouteConfigReq{
IwfDefaultRouteKeyInfo defaultRouteKeyInfo;
IwfDefaultRouteConfigInfo defaultRouteInfo;
}IwfDefaultRouteConfigReq;

typedef struct _IwfLocalHostConfigReq {
	IwfLocalHostKeyInfo localHostKeyInfo;
	IwfLocalHostTransportInfo localHostTransportInfo;
	IwfLocalHostAuthTimersInfo localHostAuthInfo;
	IwfLocalHostAcctTimersInfo localHostAcctInfo;
}IwfLocalHostConfigReq;


#if 0
/* 5. PeerGlobalConfigTable */
typedef struct _IwfOverPeerGlobalConfigKeyInfo {
int ComponentID;
}IwfPeerGlobalConfigKeyInfo;

typedef struct _IwfPeerGlobalConfigInfo {
long DiscoveryInterval;
}IwfPeerGlobalConfigInfo;

#endif
typedef struct _IwfPeerGlobalConfigReq {
IwfPeerGlobalConfigKeyInfo PeerGlobalConfigKeyInfo;
IwfPeerGlobalConfigInfo PeerGlobalConfigInfo;
}IwfPeerGlobalConfigReq;

typedef struct _IwfDynamicDiscoveryConfigReq {
	IwfDynamicDiscoveryKeyInfo dynamicDiscoveryKeyInfo;
	IwfDynamicDiscoveryConfigInfo dynamicDiscoveryConfigInfo;
}IwfDynamicDiscoveryConfigReq;

typedef struct _IwfPeerTimersConfigReq {
	IwfPeerTimersKeyInfo peerTimersKeyInfo;
	IwfPeerTimersConfigInfo peerTimersConfigInfo;
}IwfPeerTimersConfigReq;


typedef struct _IwfConfigResp {
	int ResponseCode;
}IwfConfigResp;

#endif

