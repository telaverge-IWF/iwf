/* 
 * File:   CnfMgr_Dummy.h
 * Author: adey
 *
 * Created on July 10, 2012, 3:46 PM
 */

#ifndef CNFMGR_DUMMY_H
#define	CNFMGR_DUMMY_H

#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"

//These are dummy component and interface definitions.
//The realistic components MUST use the respective definitions from 
//blocks/include/ComponentDefines.h & blocks/include/InterfaceDefines.h.
#define COMP_CONFIG_MANAGER_DUMMY      (COMP_CONFIG_MANAGER + 100)
#define I_CONFIG_MANAGER_DUMMY         (I_CONFIG_MANAGER + 100)

//This is meant for the sample code.
#define PERIODICITY             5000

#endif	/* CNFMGR_DUMMY_H */

