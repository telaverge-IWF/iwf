
#ifndef __TESTAGENT_H__
#define __TESTAGENT_H__

#include "StackStats.h"
#include "CMAPICommon.h"
#include "MeSSComponent.h"
#include "CMAPIStatsLib.h"
#include "InterfaceStat.h"
#include "Sync.h"

#define COMP_TEST_AGENT_ID  501

eAccelero::Mutex  AgentSync;

enum { GETINTERFACESTATS = 1, RESETINTERFACESTATS , GETAPPLICATIONSPECSTATS, RESETAPPLICATIONSPECSTATS, GETSTACKINDICATIONSTATS, RESETSTACKINDICATIONSTATS, GETGENERICERRORSTATS, RESETGENERICERRORSTATS, GETGENERICSTATS, RESETGENERICSTATS};

int   uAction;

#endif // __TESTAGENT_H__
