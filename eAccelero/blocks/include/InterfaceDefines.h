/* 
 * File:   InterfaceDefines.h
 * Author: adey
 *
 * Created on July 1, 2012, 8:28 PM
 */

#ifndef INTERFACEDEFINES_H
#define	INTERFACEDEFINES_H

namespace eAccelero {

#define INTERFACE_ID_START 1

    enum InterfaceId {
        I_AVAILABILITY_MANAGER = INTERFACE_ID_START,
        I_REPLICATION_MANAGER,
        I_CLI_PROC,
        I_CONFIG_MANAGER,
        I_DRE_APP,
        I_SUB_AGENT,
        I_STATS_LOGGER,
        I_WEBAGENT_PROC
    };

}

#endif	/* INTERFACEDEFINES_H */

