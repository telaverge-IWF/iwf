/* 
 * File:   ReplicationManager_Dummy.h
 * Author: adey
 *
 * Created on July 9, 2012, 3:32 PM
 */

#ifndef REPLICATIONMANAGER_DUMMY_H
#define	REPLICATIONMANAGER_DUMMY_H

#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"

//These are dummy component and interface definitions.
//The realistic components MUST use the respective definitions from 
//blocks/include/ComponentDefines.h & blocks/include/InterfaceDefines.h.
#define COMP_REPLICATION_MANAGER_DUMMY          (COMP_REPLICATION_MANAGER + 100)
#define I_REPLICATION_MANAGER_DUMMY             (I_REPLICATION_MANAGER + 100)

//This is meant for the sample code.
#define PERIODICITY                             5000

#endif	/* REPLICATIONMANAGER_DUMMY_H */

