/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: app_main.cpp,v 1.1.2.2 2013/02/04 06:08:24 pramana Exp $
 *  
 *  LOG: $Log: app_main.cpp,v $
 *  LOG: Revision 1.1.2.2  2013/02/04 06:08:24  pramana
 *  LOG: Committing changes done
 *  LOG:
 *  LOG: Revision 3.2.4.1  2012/06/22 03:58:36  ncshivakumar
 *  LOG: IMSI range addition to the app file
 *  LOG:
 *  LOG: Revision 3.2  2011/01/03 14:46:17  nvijikumar
 *  LOG: MVL compilation Issue fix
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 *  LOG: Common files required for static setup
 *  LOG:
 *  LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 *  LOG: Baseline ITS Demo.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.11  2006/06/30 08:21:53  kamakshilk
 *  LOG: Removed previous code for reading Menu Value from stdin
 *  LOG:
 *  LOG: Revision 1.10  2006/06/23 14:08:17  kamakshilk
 *  LOG: Fix for bug ID 3773
 *  LOG:
 *  LOG: Revision 1.9  2006/06/21 09:57:29  kamakshilk
 *  LOG: Modification for Copyright info.
 *  LOG:
 *  LOG: Revision 1.8  2006/06/02 13:13:35  kamakshilk
 *  LOG: RfRo menu addition
 *  LOG:
 *  LOG: Revision 1.7  2006/04/26 21:36:37  ahanda
 *  LOG: Added support for reading in Subscriber Profile for the UserData
 *  LOG:
 *  LOG: Revision 1.5  2006/04/22 00:08:31  ahanda
 *  LOG: Menu and code cleanup
 *  LOG:
 *  LOG: Revision 1.4  2006/04/17 16:10:44  yranade
 *  LOG: Load Generator Support.
 *  LOG:
 *  LOG: Revision 1.3  2006/03/24 05:20:11  nvijikumar
 *  LOG: Choice Validation has included
 *  LOG:
 *  LOG: Revision 1.2  2006/03/18 12:19:12  nvijikumar
 *  LOG: Update for CommandLine Args.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/03 14:17:08  sumag
 *  LOG: First Version of Demo Application.
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: app_main.cpp,v 1.1.2.2 2013/02/04 06:08:24 pramana Exp $"

#include <engine++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
//using namespace engine;
#endif

#include <app.h>
#include <app_mml.h>

char subsProfile[2000];
ApplicationMode appMode = UNIT_TEST;
RunMode runMode = UNKNOWN;
int     displayMode = 0;
extern ApplicationStats appStats;
#define EXIT_VAL 99
#define DEMO_INITIATOR 1
#define DEMO_RECEIVER 2

#include <its_callback.h>

void Usage(const char** args)
{
    printf("Usage: %s ", args[0]);
    printf("interactive\n");
    printf("Usage: %s ", args[0]);
    printf("-oh <value> | ");
    printf("-or <value> | ");
    printf("-dh <value> | ");
    printf("-dr <value>| ");
    printf("-load");
    printf("\n");
    exit(0);
}

char banner[256];

int parseArguments(int argc, const char** args)
{
   int i = 1;
   int flag = 1;
   int ret = 0;
   int imsi_s = 1;
   int imsi_e = 1;
                                                                                
   if (argc == 1)
   {
       Usage(args);
       return 0;
   }

#ifndef NO_PRINTF
   printf("\033[2J");
#endif
   for(; i < argc && flag ; i++)
   {
       if(strcmp(args[i], "-name") == 0)
       {
          i++;
#ifndef NO_PRINTF
          printf("OH = %s\n", args[i]);
#endif
       }
       else if(strcmp(args[i], "-oh") == 0)
       {
          SetOriginHost(args[++i]);
#ifndef NO_PRINTF
          printf("OH = %s\n", args[i]);
#endif
       }
       else if(strcmp(args[i], "-or") == 0)
       {
          SetOriginRealm(args[++i]);
#ifndef NO_PRINTF
          printf("OriginRealm = %s\n", args[i]);
#endif
       }
       else if(strcmp(args[i], "-dh") == 0)
       {
          SetDestinationHost(args[++i]);
#ifndef NO_PRINTF
          printf("DH = %s\n", args[i]);
#endif
       }
       else if(strcmp(args[i], "-dr") == 0)
       {
          SetDestinationRealm(args[++i]);
#ifndef NO_PRINTF
          printf("DR = %s\n", args[i]);
#endif
       }
       else if(strcmp(args[i], "-load") == 0)
       {
#ifndef NO_PRINTF
          printf("Setup for Load Testing\n");
#endif
          appMode = LOAD_TEST;
       }
       else if(strcmp(args[i], "-imsistart") == 0)
       {
         imsi_s=0;
         i++;
#ifndef NO_PRINTF
	 printf("imsistart = %s\n",args[i]);
#endif

       }
       else if(strcmp(args[i], "-imsiend") == 0)
       {
         imsi_e=0;
         i++;
#ifndef NO_PRINTF
	 printf("imsiend = %s\n",args[i]);
#endif
       }
	else if(strcmp(args[i], "-configFile") == 0)
       {

         flag=0;
       }

       else
       {
          Usage(args);
       }
    }
	
	if(imsi_s==1||imsi_e==1)
	{
#ifndef NO_PRINTF
	printf("IMSI RANGE NOT PASSED AS COMMAND ARGUMENT\n");
	printf("PASS AS -imsistart <value> -imsiend <value>\n");
#endif
	exit(-1);
	}
	
	
    /* from here onwrds engine arguments. */
    return i - 2;
}

void DisplayStats()
{
}

void ResetStats()
{
    memset(&appStats.u, 0, sizeof(appStats.u));
}


RunMode GetMode()
{
   RunMode retval=UNKNOWN;
   string input;
   int ret = 0;
   bool validInput=false;

#if 0   
   cout << endl << "_____________________________________" << endl;
           printf("        %-30s", banner);
   cout << endl << "_____________________________________" << endl;
#endif

   while(!validInput)
   {
#if 0
        cout << endl << "Command Execution"
        << endl << "1: Send Mode "
        << endl << "2: Receive Mode"
        << endl << "3: Statistics"
        << endl << "4: Reset"
        << endl << "5: Quit"
        << endl;
#endif
        cin >>input;
        ret = atoi(input.c_str());
        switch(ret)
        {
           case 1:
           case 11:
           case 111:
           case 1111:
           case 11111:
           case 111111:
               retval = INITIATOR;
	       displayMode = 10;
               validInput = true;
               break;
           case 2:
           case 22:
           case 222:
           case 2222:
           case 22222:
           case 222222:
               retval = RECEIVER;
	       displayMode = 20;
               validInput = true;
               break;
           case 3:
           case 33:
           case 333:
           case 3333:
           case 33333:
           case 333333:
               ResetStats();
               validInput = true;
               break;
           case 4:
           case 44:
           case 444:
           case 4444:
           case 44444:
           case 444444:
               validInput = true;
               exit(1);
               break;
           default:
               break;
        }
   }
   return(retval);
}

void ReadInSubsProfile()
{
    FILE *fp;
    int i=0;

    subsProfile[0] = '\0';

    if((fp = fopen("SubsProfile.xml","r")) != NULL)
    {
       while ((subsProfile[i] = fgetc(fp)) !=EOF)
       {
          i++;
       }
       subsProfile[i] = '\0';
    }
    else
    {
       strcpy(subsProfile,"Subscriber not provisioned");
    }
    //Printing User Data Read
    //printf("User Data Read %s", subsProfile);
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
int AppMain(int argc, const char** argv)
{

    //Select the application
   int ret = parseArguments(argc, argv);

    //Read in Subscriber profile for HSS simulation
    ReadInSubsProfile();

    //strcpy(banner, argv[2]);
#if 0
    if (appMode == UNIT_TEST)
    {
        runMode = GetMode();
    }
#endif

    ITS_Application::SetName("DiameterApp");

    APPMMLServer appMMLServer("DIA_TEST MML Server");
    ENGINE_Initialize((argc - ret), &argv[ret], NULL, 0);

    ENGINE_Run(argc, argv);

    return ITS_SUCCESS;
}
