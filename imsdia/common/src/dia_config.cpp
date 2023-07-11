/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: dia_config.cpp,v $
 * LOG: Revision 3.6.46.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.6  2010/07/10 08:06:46  nvijikumar
 * LOG: APIs to enable/disable OAM/MML/DCCA feature in XML data
 * LOG:
 * LOG: Revision 3.5  2010/07/09 07:05:22  nvijikumar
 * LOG: Support for enable/disable MML/OAM feature for TCS
 * LOG:
 * LOG: Revision 3.4  2010/07/03 09:14:04  nvijikumar
 * LOG: Support for both DEBUG and NDEBUG builds
 * LOG:
 * LOG: Revision 3.3  2010/06/21 04:24:20  nvijikumar
 * LOG: Accelero xmlData is returned as heap object, so app no need to do strdup
 * LOG:
 * LOG: Revision 3.2  2010/06/17 04:38:16  nvijikumar
 * LOG: APIs to build default accelero engine XML
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/11/14 06:35:13  kamakshilk
 * LOG: Added routeScheme required for IDS
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.4  2006/06/21 10:41:27  nvijikumar
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.3  2006/04/17 10:31:07  adutta
 * LOG: Setting Heart beat params from xml.
 * LOG:
 * LOG: Revision 1.2  2006/04/13 18:06:18  yranade
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 * LOG: Building IMS Infrastructure
 * LOG:
 *
 * ID: $Id: dia_config.cpp,v 3.6.46.1 2013/02/27 08:49:06 jvikram Exp $
 ****************************************************************************/
#ident "$Id: dia_config.cpp,v 3.6.46.1 2013/02/27 08:49:06 jvikram Exp $"

#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>

#include <dia_trace.h>
#include <dia_config.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#define MAX_XML_DATA_LEN 4096
#define DEFAULT_MML_PORT 2012
#define DEFAULT_OAM_PORT 5555

char * BuildAcceleroXML(int mmlPort, int oamPort);

ITS_Mutex DiaConfig::guard(0);
ITS_Mutex DiaConfig::lock(0);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
DiaConfig::DiaConfig()
    :isDebugDump(false),
     _mmlPort(DEFAULT_MML_PORT),
     _oamPort(DEFAULT_OAM_PORT),
     enableOam(false),
     enableMml(false),
     enableDcca(false),
     xmlData(NULL)
{
   //ParseResourceManager();
   //Initializing Uninitialized fields
   configFile = NULL;
   xmlData = NULL;
   hbIntvl = 0;
   hbRetry = 0;
}
   

DiaConfig::~DiaConfig()
{
    if (configFile)
    {
        free (configFile);
    }

    if (xmlData)
    {
        free(xmlData);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void
DiaConfig::Lock() const
{
    int res;
    res = const_cast<ITS_Mutex&>(lock).Acquire();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void
DiaConfig::Unlock() const
{
    int res;
    res = const_cast<ITS_Mutex&>(lock).Release();    
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    14-11-06    Enhancement     routeScheme added for IDS.
 *
 ****************************************************************************/
int
DiaConfig::ParseResourceManager()
{ 
    char key[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];
    ITS_ResourceManager *rf = new  
                         ITS_ResourceManager(APPL_GetConfigFileName());

    rf->Lock();
    rf->Rewind(NULL);

    while (rf->GetKeyName(NULL, key, ITS_PATH_MAX) == ITS_SUCCESS &&
           rf->GetKeyValue(NULL, value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (strcmp(key, "DiameterConfigFile") == 0)
        {            
            configFile = strdup(value); 
        }

        if (strcmp(key, "HeartBeatInterval") == 0)
        {          
            hbIntvl = atoi(value);
        }
    
        if (strcmp(key, "HeartBeatRetry") == 0)
        {
            hbRetry = atoi(value);
        }

        if (strcmp(key, "RoutingScheme") == 0)
        {          
            //Fixing Resource Leak
            //routeScheme = strdup(value); 
            routeScheme.assign(value); 
        }
    }
    rf->Unlock();

    delete rf;

    return ITS_SUCCESS;
}

static DiaConfig *config = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  retrieve the current Dia configuration.
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************///
DiaConfig* DiaConfig::GetDiaConfig()
{
    ITS_ASSERT(DiaConfig::guard.Acquire() == ITS_SUCCESS);

    if (config == NULL)
    {
        config = new DiaConfig;
    }

    DiaConfig::guard.Release();

    return config;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
#if 0
void DiaConfig::ReloadDiaConfig()
{
    DiaConfig* tmp = new DiaConfig;
    static DiaConfig* release = NULL;

    if (release)
    {
        TIMERS_Sleep(3);
        delete release;
    }

    ITS_ASSERT(DiaConfig::guard.Acquire() == ITS_SUCCESS);

    release = config;
    config = tmp;

    DiaConfig::guard.Release();
}
#endif

char *
DiaConfig::GetEngineXMLData() 
{
    return BuildAcceleroXML(GetMMLPort(), GetOAMPort());
}

const char *xmlDataPart1 = "<?xml version=\"1.0\"?> \
   <Application name = \"DiaServer\" \
                type = \"console-application\" \
                globalStart = \"\" \
                binding = \"CPP\" \
                library = \"\" \
                preFunc  = \"AppPreFunc\" \
                postFunc  = \"AppPostFunc\">  \
   <AppOptions name = \"traceFlushAfterWrite\" value = \"yes\"/> \
   <AppOptions name = \"routeUniqueLinkCodesRequired\" value = \"yes\"/> \
   <AppOptions name = \"memPoolChecksOn\" value = \"no\"/> \
   <FaultTolerance maxNumFtGroups = \"2\" \
                   maxNumProcesses  = \"1\" \
                   maxNumNodes = \"1\" \
                   nodeId  = \"0\" \
                   processId  = \"0\" \
                   routingFtGroupId = \"0\" \
                   timersFtGroupId = \"0\" \
                   mgmtDataFtGroupId = \"0\" > \
   <Procedures> </Procedures> <Callbacks> </Callbacks> \
   <FtGroups> <FtGroup ftGroupId = \"0\" ftGroupName = \"FtGroup0\" > \
   <DsmConfig dsmSize = \"20971520\" dsmBaseAddress  = \"0x80000000\" \
              dsmMaxNumTables = \"256\" dsmType = \"STUB\" /> \
   <FtGroupMembers> \
   <FtGroupMember nodeId  = \"0\" nodeName = \"Node0\" \
                  processId   = \"0\" processName = \"Node0Process0\" /> \
   </FtGroupMembers> \
   <MasterFtGroupMembers> </MasterFtGroupMembers> <Callbacks> </Callbacks> \
   </FtGroup> <FtGroup ftGroupId  = \"1\" ftGroupName = \"FtGroup1\" > \
   <DsmConfig dsmSize = \"20971520\" dsmBaseAddress  = \"0x90000000\" \
              dsmMaxNumTables = \"256\" dsmType = \"STUB\" /> \
   <FtGroupMembers> \
   <FtGroupMember nodeId = \"0\" nodeName = \"Node0\" \
                  processId   = \"0\" processName = \"Node0Process0\" /> \
   </FtGroupMembers> \
   <MasterFtGroupMembers> </MasterFtGroupMembers> <Callbacks> </Callbacks> \
   </FtGroup> </FtGroups> </FaultTolerance> ";
#if defined(DEBUG)
const char *xmlDataDsmFeature=  "<Feature name = \"DSM  - STUB\" library = \"libDSM-STUBD.so\" \
           classRec  = \"itsDSM_StubImplClass\" />";
const char *xmlDataDccaFeature=  " <Feature name  = \"DCCA\" library     = \"libdccacoreD.so\" \
           classRec  = \"itsDCCA_Class\" /> ";
const char *xmlDataOamFeature = "<Feature name = \"OAM Server Class\" library = \"libDiaOAMServerD.so\" \
                classRec = \"itsDIAOAMServer_Class\" /> ";
#else
const char *xmlDataDsmFeature=  "<Feature name = \"DSM  - STUB\" library = \"libDSM-STUB.so\" \
           classRec  = \"itsDSM_StubImplClass\" />";
const char *xmlDataDccaFeature=  " <Feature name  = \"DCCA\" library     = \"libdccacore.so\" \
           classRec  = \"itsDCCA_Class\" /> ";
const char *xmlDataOamFeature = "<Feature name = \"OAM Server Class\" library = \"libDiaOAMServer.so\" \
                classRec = \"itsDIAOAMServer_Class\" /> ";
#endif

const char *xmlDataPart2 ="<ToolkitTrace> \
   <Critical  output = \"stdout\"/> <Error output = \"stdout\"/> \
   <Warning   output = \"stdout\"/> <Debug     output = \"\"/> \
   </ToolkitTrace> \
   <ApplicationTrace> \
   <Critical output=\"stdout\"/> <Error output=\"stdout\"/> \
   <Warning  output=\"stdout\"/> <Debug  output=\"stdout\"/> \
   </ApplicationTrace> \
   <WorkerPool stackSize = \"0\"> \
   <Transport  type = \"TaskQueue\" count = \"20\" family = \"\"> </Transport> \
   </WorkerPool> \
   <BorderPool stackSize = \"0\">";

const char *xmlDataDbcTransPart1 = "<Transport  name = \"MML Console Dispatcher\" type = \"ServerSocket\" \
               family  = \"\"> <StreamData socketDomain  = \"INET\" \
               serverHostName  = \"127.0.0.1\" serverPort      = \"";

const char *xmlDataDbcTransPart2 = "\" /> <Callbacks type = \"debug-console\"/> </Transport>";

const char *xmlDataOamTransPart1 =" <Transport  name = \"DiaOAMServer\" type = \"ServerSocket\" \
          family  = \"0\"> <StreamData socketDomain = \"INET\" \
          serverHostName = \"127.0.0.1\" serverPort  = \"";

#if defined(DEBUG)
const char *xmlDataOamTransPart2 ="\" /> <Callbacks library   = \"libDiaOAMServerD.so\" \
    type = \"blocking\" preInitialize   = \"OAMServerPreInit\" \
    postInitialize  = \"OAMServerPostInit\" preNextEvent    = \"null\" \
    nextEventFailed = \"null\" postNextEvent   = \"OAMServerPostNext\" \
    userDispatch = \"null\" SCCPDispatch = \"null\" ISUPDispatch = \"null\" \
    preTerminate    = \"null\" postTerminate   = \"null\" /> </Transport> ";
#else
const char *xmlDataOamTransPart2 ="\" /> <Callbacks library   = \"libDiaOAMServer.so\" \
    type = \"blocking\" preInitialize   = \"OAMServerPreInit\" \
    postInitialize  = \"OAMServerPostInit\" preNextEvent    = \"null\" \
    nextEventFailed = \"null\" postNextEvent   = \"OAMServerPostNext\" \
    userDispatch = \"null\" SCCPDispatch = \"null\" ISUPDispatch = \"null\" \
    preTerminate    = \"null\" postTerminate   = \"null\" /> </Transport> ";
#endif

const char *xmlDataPart4 = " </BorderPool> <Diameter> </Diameter> </Application> ";

char * 
DiaConfig::BuildAcceleroXML(int mmlPort, int oamPort)
{
   char buff[MAX_XML_DATA_LEN];
   memset(buff, 0 , MAX_XML_DATA_LEN);

   char tmp[MAX_XML_DATA_LEN];
   memset(tmp, 0 , MAX_XML_DATA_LEN);

   if (xmlData != NULL)
   {
       free(xmlData);
   }

   if (enableDcca == true)
   {
        //Correcting calling risky function
        snprintf(tmp,MAX_XML_DATA_LEN-1, "%s%s%s",xmlDataPart1, xmlDataDsmFeature,xmlDataDccaFeature);
   }
   else
   {
        //Correcting calling risky function
        snprintf(tmp,MAX_XML_DATA_LEN-1, "%s%s",xmlDataPart1, xmlDataDsmFeature);
   }

   if (enableOam == true && enableMml == true)
   {
        //Correcting calling risky function
       snprintf(buff,MAX_XML_DATA_LEN-1, "%s%s%s%s%d%s%s%d%s%s", tmp, xmlDataOamFeature,
                             xmlDataPart2, xmlDataDbcTransPart1, mmlPort, xmlDataDbcTransPart2,
                             xmlDataOamTransPart1,oamPort,
                             xmlDataOamTransPart2,xmlDataPart4);
   }
   else if (enableOam == true)
   {
        //Correcting calling risky function
       snprintf(buff,MAX_XML_DATA_LEN-1,"%s%s%s%s%d%s%s", tmp, xmlDataOamFeature,
                             xmlDataPart2,
                             xmlDataOamTransPart1,oamPort,
                             xmlDataOamTransPart2,xmlDataPart4);
   }
   else if (enableMml == true)
   {
        //Correcting- calling risky function
       snprintf(buff,MAX_XML_DATA_LEN-1,"%s%s%s%d%s%s", tmp, xmlDataPart2, xmlDataDbcTransPart1, mmlPort, 
                                  xmlDataDbcTransPart2, xmlDataPart4);
   }
   else
   {
        //Correcting- calling risky function
       snprintf(buff,MAX_XML_DATA_LEN-1,"%s%s%s", tmp, xmlDataPart2, xmlDataPart4);
   }
  
   //Coveirty Issue Fix - 11856 - Allocation too small for a string.
   xmlData = (char *)malloc(strlen(buff)+1);
   memcpy(xmlData,buff,strlen(buff));
   return xmlData;
}
