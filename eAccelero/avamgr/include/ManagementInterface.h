/* 
 * File:   ManagementInterface.h
 * Author: adey
 *
 * Created on November 3, 2012, 8:15 AM
 */

#ifndef MANAGEMENTINTERFACE_H
#define	MANAGEMENTINTERFACE_H

#include "HA.h"
#include "CMAPIConfig.h"
#include "Compo.h"
#include "KPI.h"

namespace eAccelero {
    class AvailabilityManager;
}

class ManagementInterface : public AvaMgrHAInterface, public LoggingConf,
                            public AvaMgrKPIInterface
{

public:
    ManagementInterface(AvailabilityManager *avaMgr);

    virtual ~ManagementInterface();

    int AvaMgrSetConfiguration(AvaMgrConfig *req, AvaMgrConfigResp *resp);

    int AvaMgrGetConfiguration(ComponentActionReq *req, AvaMgrConfigResp *resp);

    int AvaMgrSwitchOverRequest(ComponentActionReq *req, AvaMgrConfigResp *resp);

    int SetComponentLoggingConf(LoggerConfReq *req, LoggerConfResp *resp);

    int FetchClusterInfo(ClusterInfoReq *req, ClusterInfoResp *resp);

    int FetchProcessState(ProcessStateReq *req, ProcessStateResp *resp);
    
private:
    AvailabilityManager *m_objAvaMgr;
};

#endif	/* MANAGEMENTINTERFACE_H */

