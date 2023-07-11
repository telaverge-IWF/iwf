/* 
 * File:   CliProc_Dummy.h
 * Author: adey
 *
 * Created on July 10, 2012, 3:43 PM
 */

#ifndef CLIPROC_DUMMY_H
#define	CLIPROC_DUMMY_H

#include "HAMeSSComponent.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"

//These are dummy component and interface definitions.
//The realistic components MUST use the respective definitions from 
//blocks/include/ComponentDefines.h & blocks/include/InterfaceDefines.h.
#define COMP_CLI_PROC_DUMMY      (COMP_CLI_PROC + 100)
#define I_CLI_PROC_DUMMY         (I_CLI_PROC + 100)

//This is meant for the sample code.
#define PERIODICITY             5000

#endif	/* CLIPROC_DUMMY_H */

