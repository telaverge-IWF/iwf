
#ifndef __TESTAGENT_H__
#define __TESTAGENT_H__

#include "dreconfig.h"
#include "CMAPICommon.h"
//#include "CMAPIInterface.h"
#include "MeSSComponent.h"
#include "CMAPIUsrMgtLib.h"
#include "Sync.h"

#define COMP_TEST_AGENT_ID  501

#define ADD_USER_ROLE       1
#define DEL_USER_ROLE       2
#define MOD_USER_ROLE       3
#define GET_USER_ROLE       4
#define GET_EMAIL_SERVER    5
#define SET_EMAIL_SERVER    6
#define DEL_EMAIL_SERVER    7
#define GET_EMAIL_CONTENT   8
#define MOD_EMAIL_CONTENT   9
#define SET_USER            10
#define MOD_USER            11
#define DEL_USER            12
#define GET_USER            13
#define GET_USER_PRIVILEGE  14

eAccelero::Mutex  AgentSync;

enum { GETLOCALHOST = 1 }; 

int   uAction;

#endif // __TESTAGENT_H__

