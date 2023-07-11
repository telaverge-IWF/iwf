/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 *  ID: $Id: ssg.cpp,v 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1.4.2.2.2 2014/12/16 08:49:56 jkchaitanya Exp $
 *
 *  LOG: $Log: ssg.cpp,v $
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1.4.2.2.2  2014/12/16 08:49:56  jkchaitanya
 *  LOG: changes for IWF crash observed at restart time
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1.4.2.2.1  2014/12/03 09:26:18  mhimanshu
 *  LOG: stats implementation at MML - diaS6aStats and activeSubscribers
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1.4.2  2014/11/17 05:08:40  jkchaitanya
 *  LOG: changes for HA Bug Fixes
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1.4.1  2014/09/19 07:18:53  jkchaitanya
 *  LOG: changes for translator specific license validation and alarm implementation in IWF application
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1  2014/06/25 04:36:18  jkchaitanya
 *  LOG: changes for warnings removal in IWF application code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.4  2014/04/01 09:43:15  jkchaitanya
 *  LOG: Merged SMS changes to Voice Branch
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3.4.3  2014/03/05 11:06:48  jsarvesh
 *  LOG: Merging SMS fixes in VOICE
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.4  2014/03/03 04:33:09  millayaraja
 *  LOG: updated the sigtran log file creation with proper name
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.3  2014/02/14 05:22:15  rsanjay
 *  LOG: modified default sigtran log file location to /var/log/iwf/iwf_sigtran.log
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.2  2014/02/13 14:11:38  jkchaitanya
 *  LOG:  changes for avp mappings for TSL
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3.2.1  2014/02/13 06:55:49  rsanjay
 *  LOG: modified SSG.out to be populated under specified directory or by default /opt/diametriq/iwf/bin/SSG.out
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.3  2013/12/12 11:51:29  jsarvesh
 *  LOG: Changes done to send ASPINACTIVE and ASPDOWN when IWF comes down
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.2  2013/12/10 13:34:00  millayaraja
 *  LOG: updated productization code for eAccelero Logging
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1.2.1  2013/12/03 09:46:00  millayaraja
 *  LOG: initial code checkin for IWF productization
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3.2.1  2013/10/04 13:43:07  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.3  2013/06/19 12:39:42  jsarvesh
 *  LOG: MML implementation for IWF Statistics
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2  2013/05/20 09:01:50  jvikram
 *  LOG: Corrected Coverity Issues
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/04/18 05:41:22  jvikas
 *  LOG: Fixes for High Impact Coverity Issues
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:36  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.2  2011/04/15 11:34:07  nvijikumar
 *  LOG: UT Updates
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ssg.cpp,v 1.1.1.1.2.3.2.1.2.3.2.3.4.4.2.1.4.2.2.2 2014/12/16 08:49:56 jkchaitanya Exp $"

#include <engine++.h>
#include <ssg_trace.h>
#include <ssg_configuration.h>
#include <ssg_dbc.h>
#include "iwf_mess.h"
#include "iwf_config.h"
#include "iwf.h"

#if defined(ITS_STD_NAMESPACE)
#ifdef GCC_LESS_THAN_4_3
//using namespace std::tr1;
using namespace std;
#else
using namespace std;
#endif
using namespace its;
using namespace engine;
#endif

#define BUF_SIZE 1024

void Usage(const char** args)
{
    printf("Usage: %s ", args[0]);
    printf("interactive\n");
    printf("Usage: %s ", args[0]);
    printf("-oh <value> | ");
    printf("-or <value> | ");
    printf("-dh <value> | ");
    printf("-dr <value>| ");
    printf("\n");
    exit(0);
}

int ParseCmdLineArguments(int argc, const char** args)
{
   int i = 1;
   int flag = 1;

   if (argc == 1)
   {
       Usage(args);
       return 0;
   }
   printf("\033[2J");
   for(; i < argc && flag; i++)
   {
       if(strcmp(args[i], "-oh") == 0)
       {
          SetOriginHost(args[++i]);
          printf("OH = %s\n", args[i]);
       }
       else if(strcmp(args[i], "-or") == 0)
       {
          SetOriginRealm(args[++i]);
          printf("OriginRealm = %s\n", args[i]);
       }
       else if(strcmp(args[i], "-dh") == 0)
       {
          SetDestinationHost(args[++i]);
          printf("DH = %s\n", args[i]);
       }
       else if(strcmp(args[i], "-dr") == 0)
       {
          SetDestinationRealm(args[++i]);
          printf("DR = %s\n", args[i]);
       }
       else if(strcmp(args[i], "-configFile") == 0)
       {
          flag = 0;
       }
       else
       {
          //Usage(args);
       }
    }
    /* from here onwrds engine arguments. */
    return i - 2;
}

int main(int argc, const char** argv)
{
   int ret = ParseCmdLineArguments(argc, argv);

   // IWF objects initialization
   char *iwfJson = getenv("IWF_CONFIG_FILE");
   if (iwfJson == NULL)
   {
       iwfJson = (char*)IWF_CONFIG_DEFAULT_FILE;
   }

   IwfController::Init(argc, argv, iwfJson);

   for (int i = 0; i < argc; i++)
   {
       if (!strcmp(argv[i], "-i") && argv[i+1])
       {
           instanceId = atoi(argv[i+1]);
       }
       if(strcmp(argv[i], "-debugMode") == 0)
       {
           IwfController::Instance().SetIsBulkFetchSuccess(true);
       }
   }
   /**
     * Adding the facility to redirect the traces from stdout to a file.
     */

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("In Main after initializing IwfController");

    char *ssgServerOutputEnv = getenv("SSG_LOG_DIR");
    char *outputFile = (char*)IWF_SIGTRAN_LOG_DEFAULT_FILE;

    if (ssgServerOutputEnv != NULL && outputFile != NULL)
    {
        int pathLen = strlen(ssgServerOutputEnv);
        ssgServerOutputEnv[pathLen] = '\0';
        int fileLen = strlen(outputFile);
        char* ssgOutput = new char[ pathLen + fileLen + 1 ];
        memset(ssgOutput, 0, (pathLen+fileLen+1));

        strncpy(ssgOutput, ssgServerOutputEnv, pathLen);
        strncat(ssgOutput, outputFile ,fileLen);
        ssgOutput[pathLen+fileLen] = '\0';

        cout <<"IWF SIGTRAN Logs sent to "<< ssgOutput << endl;

        FILE* fp = freopen(ssgOutput, "a", stdout);
        delete [] ssgOutput;

    }
    else
    {
        cout<<"Sigtran Log file location not set"<<endl;
        cout <<"By Default Sigtran logs sent to /var/log/iwf/iwf_sigtran.log"<< endl;
        FILE* fp = freopen("/var/log/iwf/iwf_sigtran.log", "a", stdout);
    }
    char buf[2*BUF_SIZE];

    if (setvbuf(stdout, buf, _IOLBF, (BUF_SIZE * 2)) != ITS_SUCCESS)
    {
        cout << "Error opening buffer" << endl;
    }


    ITS_Application::SetName("IWF");
    DLOG_DEBUG("In Main Applicaiton Name set to IWF");

    SsgDbcServer dbgConsole("IWF Debug Console");
    //IWFMMLServer mmlServer("IWF MML Server");
    ENGINE_Initialize((argc - ret), &argv[ret], NULL, 0);

    DLOG_DEBUG("In Main Engine Intialized");

    ENGINE_Run(argc, argv);
    DLOG_DEBUG("In Main Engine Run");

    return ITS_SUCCESS;
}
