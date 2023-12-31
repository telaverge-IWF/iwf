
#ifndef __TESTAGENT_H__
#define __TESTAGENT_H__

#include "dreconfig.h"
#include "CMAPICommon.h"
#include "CMAPIInterface.h"
#include "MeSSComponent.h"
#include "CMAPILib.h"
#include "Sync.h"

#define COMP_TEST_AGENT_ID  501

eAccelero::Mutex  AgentSync;

enum { GETLOCALHOST = 1, GETPEERINFO, SETAUTHTIMERS, SETLOCALHOST, SETACCTTIMERS, SETIPADDR,
       GETREALM, GETALLREALMS, SETREALM, DELREALM, SETDEFROUTE, GETDEFROUTE, SETDEST, 
       ENBPXY, DISPXY, GETALLPEERS, GETALLREALMPEERS, SETPEER, DELPEER, MODPEER, MODREALM, MODLOCALHOST, MODDEST, DELDEST, DELDEFROUTE,
       GETPEERGENERALSTATS, GETPEERTRANSPORTSTATS, GETPEERERRORSTATS, RESETPEERSTATS, ADDDICTID, DELDICTID, PEERSTATUS,
       GETUSER, SETUSER, DELUSER, RESETPSSWD, GETUNIQUEREALMS, SETTRACE, DELTRACE, MODTRACE, GETTRACE, ENABLETRACE,GETFILTERSTATUS, INVALIDCODE};

int   uAction;

#endif // __TESTAGENT_H__

