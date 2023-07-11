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
 *  ID: $Id: app_main.cpp,v 3.1.84.1 2013/12/04 05:46:42 vsarath Exp $
 *  
 *  LOG: $Log: app_main.cpp,v $
 *  LOG: Revision 3.1.84.1  2013/12/04 05:46:42  vsarath
 *  LOG: Fix for issue 2515
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.2  2008/03/27 11:58:28  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 1.1.10.1  2007/06/29 09:56:41  nvijikumar
 *  LOG: SOlaris GCC support ( removed engine name space).
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
#ident "$Id: app_main.cpp,v 3.1.84.1 2013/12/04 05:46:42 vsarath Exp $"

#include <engine++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
//using namespace engine;
#endif

#include <app.h>
#include <app_mml.h>

int commandSet;
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
    exit(0);
}


int parseArguments(int argc, const char** args)
{
   int i = 1;
   int flag = 1;
   int ret = 0;
                                                                                
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
       else if(strcmp(args[i], "-load") == 0)
       {
          printf("Setup for Load Testing\n");
          appMode = LOAD_TEST;
       }
       else
       {
          Usage(args);
       }
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
        cout << endl << "Do you wish to run the Application as"
        << endl << "1: Command Initiator "
        << endl << "2: Command Receiver"
        << endl << "9: To exit now"
        << endl;

        cin >>input;
        ret = atoi(input.c_str());
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
}


int GetCommandSet()
{
   int retval=0;
   string input;
   bool validInput=false;

   while(!validInput)
   {
   cout << endl << "Select Command Set"
         << endl << "1: Base Protocol"
         << endl << "2: Sh Interface"
         << endl << "3: Cx/Dx Interface"
         << endl << "4: Gq/Gq' Interface"
         << endl << "5: Rf/Ro Interface"
         << endl << "9: to Exit" << endl;

        cin >>input;
        retval = atoi(input.c_str());
        switch(retval)
        {
           case 1:
           case 2:
           case 3:
           case 4:
           case 5:
               validInput = true;
               break;
           case 9:
               retval = EXIT_VAL;
               validInput = true;
               break;
           default:
               break;
        }
   }
   return(retval);
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
int main(int argc, const char** argv)
{

    //Select the application
   int ret = parseArguments(argc, argv);

    //Read in Subscriber profile for HSS simulation
    ReadInSubsProfile();

    if (appMode == UNIT_TEST)
    {
        runMode = GetMode();

        if((runMode != RECEIVER) && (commandSet=GetCommandSet()) == EXIT_VAL)
        {
            exit(1);
        }
    }

    ITS_Application::SetName("DiameterApp");

    APPMMLServer appMMLServer("DIA_TEST MML Server");
    ENGINE_Initialize((argc - ret), &argv[ret], NULL, 0);

    ENGINE_Run(argc, argv);

    return ITS_SUCCESS;
}
