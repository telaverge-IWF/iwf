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
 *  ID: $Id: app_main.cpp,v 3.2.4.1.36.2.2.1.2.1.4.2 2014/04/07 04:50:30 jkchaitanya Exp $
 *  
 *  LOG: $Log: app_main.cpp,v $
 *  LOG: Revision 3.2.4.1.36.2.2.1.2.1.4.2  2014/04/07 04:50:30  jkchaitanya
 *  LOG: changes for ro-tsl-perf to support local/remote/sms calls for load
 *  LOG:
 *  LOG: Revision 3.2.4.1.36.2.2.1.2.1.4.1  2014/02/12 07:07:15  millayaraja
 *  LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 *  LOG:
 *  LOG: Revision 3.2.4.1.36.2.2.1.2.1  2013/12/04 05:46:42  vsarath
 *  LOG: Fix for issue 2515
 *  LOG:
 *  LOG: Revision 3.2.4.1.36.2.2.1  2013/07/01 07:32:06  nazad
 *  LOG: changes for memory Leak, Review Request 1041
 *  LOG:
 *  LOG: Revision 3.2.4.1.36.2  2013/03/06 04:52:19  ncshivakumar
 *  LOG: Added condition for checking whether file pointer is null or not before closing it
 *  LOG:
 *  LOG: Revision 3.2.4.1.36.1  2013/02/27 08:49:06  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
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
#ident "$Id: app_main.cpp,v 3.2.4.1.36.2.2.1.2.1.4.2 2014/04/07 04:50:30 jkchaitanya Exp $"

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
RunMode runMode = RECEIVER;
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
    printf("if -dh option is not there, simulator will not send destination host avp.\n");
    exit(0);
}


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

   printf("\033[2J");
   for(; i < argc && flag ; i++)
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
       else if(strcmp(args[i], "-load") == 0)
       {
          printf("Setup for Load Testing\n");
          appMode = LOAD_TEST;
       }
       else if(strcmp(args[i], "-imsistart") == 0)
       {
         imsi_s=0;
         i++;
	 printf("imsistart = %s\n",args[i]);

       }
       else if(strcmp(args[i], "-imsiend") == 0)
       {
         imsi_e=0;
         i++;
	 printf("imsiend = %s\n",args[i]);
       }
       else if(strcmp(args[i], "-callFlow") == 0)
       {
           if(atoi(args[++i]) == 0)
           {
               printf("CallFlow chosen for Load is SMS");
           }
           else if(atoi(args[++i]) == 1)
           {
               printf("CallFlow chosen for Load is LocalVoiceCall");
           }
           else if(atoi(args[++i]) == 2)
           {
               printf("CallFlow chosen for Load is RemoteVoiceCall");
           }
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
	printf("IMSI RANGE NOT PASSED AS COMMAND ARGUMENT\n");
	printf("PASS AS -imsistart <value> -imsiend <value>\n");
	exit(-1);
	}
	
	
    /* from here onwrds engine arguments. */
    return i - 2;
}


RunMode GetMode()
{
   RunMode retval=RECEIVER;
   string input;
   int ret = 0;
   bool validInput=false;

   cout << endl << "_____________________________________" << endl <<
           endl << "     DIAMETRIQ DIAMETER TESTING     " << endl <<
           endl << "_____________________________________" << endl;

   while(!validInput)
   {
#ifdef FOR_IWF
#if 0
        cout << endl << "Do you wish to run the Application as"
        << endl << "1: Command Initiator "
        << endl << "2: Command Receiver"
        << endl << "9: To exit now"
        << endl;

        cin >>input;
        ret = atoi(input.c_str());
#endif
        //HardCoded to Initiator Mode
        ret = 1;
#else
        cout << endl << "Do you wish to run the Application as"
        << endl << "1: Command Initiator "
        << endl << "2: Command Receiver"
        << endl << "9: To exit now"
        << endl;

        cin >>input;
        ret = atoi(input.c_str());
#endif
        switch(ret)
        {
           case 1:
               retval = INITIATOR;
               validInput = true;
               break;
           case 2:
               retval = RECEIVER;
               validInput = true;
               break;
           case 9:
               exit(1);
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
    //Coverity Issue Fix - 10954 - Resource Leak
    if(fp != NULL)
    { 
        fclose(fp);
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
int AppMain(int argc, const char** argv)
{

    //Select the application
   int ret = parseArguments(argc, argv);

    //Read in Subscriber profile for HSS simulation
    ReadInSubsProfile();

    if (appMode == UNIT_TEST)
    {
        runMode = GetMode();
    }

    ITS_Application::SetName("DiameterApp");

    APPMMLServer appMMLServer("DIA_TEST MML Server");
    ENGINE_Initialize((argc - ret), &argv[ret], NULL, 0);

    ENGINE_Run(argc, argv);

    return ITS_SUCCESS;
}
