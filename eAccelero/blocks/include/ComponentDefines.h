#ifndef __ComponentDefines_h__
#define __ComponentDefines_h__

extern "C" const char DREVer[];

namespace eAccelero
{

#define COMPONENT_ID_START      1000
#define SUBCOMPONENT_ID_START   10000

enum ComponentId
{
    COMP_AVAILABILITY_MANAGER = COMPONENT_ID_START,
    COMP_REPLICATION_MANAGER,
    COMP_CLI_PROC,
    COMP_CONFIG_MANAGER,
    COMP_DRE_APP,
    COMP_SUB_AGENT,
    COMP_STATS_LOGGER,
    COMP_WEBAGENT_PROC,
    COMP_RESOURCE_MANAGER,
    COMP_TEST_APP,
    COMP_IWF_APP,
    //This signals the end of component ID's.
    //All new Component ID's need to be added before the same.
    COMPONENT_ID_END,
    SUBCOMP_MESS = SUBCOMPONENT_ID_START,
};

#define COMPONENT_INITIAL_STATUS 0

enum HAComponentStatus
{
    COMPONENT_STATUS_INDETERMINATE = COMPONENT_INITIAL_STATUS,
    COMPONENT_STATUS_INITIALIZED,
    COMPONENT_STATUS_STOPPED
};

};

#endif
