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
 *  ID: $Id: ids_main.cpp,v 3.3.60.1 2013/02/27 08:49:06 jvikram Exp $
 *
 *  LOG: $Log: ids_main.cpp,v $
 *  LOG: Revision 3.3.60.1  2013/02/27 08:49:06  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.3  2009/03/03 10:44:55  nvijikumar
 *  LOG: Using static memory instead of heap as stream buffer (free was causing
 *  LOG: coredump in new version of  GCC)
 *  LOG:
 *  LOG: Revision 3.2  2009/01/03 06:07:30  rajeshak
 *  LOG: Fix for KLOCK works reported issues
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.3  2008/03/27 11:21:05  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.2.4.1  2007/10/25 07:38:30  hbhatnagar
 *  LOG: Changes made to Redirect standard output stream to IDS.out file.
 *  LOG: (Bridgewater ticket 1800 resolution )
 *  LOG:
 *  LOG: Revision 2.2  2007/01/30 05:26:39  nanaparthi
 *  LOG: Enhancements for MML application
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 *  LOG: First cut
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ids_main.cpp,v 3.3.60.1 2013/02/27 08:49:06 jvikram Exp $"

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>

#include <engine++.h>
#include <ids_common.h>
#include <ids_msghandler.h>
#include <ids_mml.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#include <its_callback.h>

#define BUF_SIZE 1024

extern "C"
{
    CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
    CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
    CALLBACK_Manager* MTP3_PRC_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_PRC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_PRC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_PRC_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_PRC_SSNRoutingCallbacks = NULL;
    CALLBACK_Manager* MTP3_TTC_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_TTC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_TTC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_TTC_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_TTC_SSNRoutingCallbacks = NULL;
}


int
main(int argc, const char **argv)
{
    /**
     * Adding the facility to redirect the traces from stdout to a file.
     */ 
    char *diaServerOutputEnv = getenv("IMS_LOG_DIR");
        
    if (diaServerOutputEnv!= NULL)  
    {
        int len = strlen(diaServerOutputEnv);
        char* idsOutput = new char[ len + strlen("/IDS.out") +1];

        strncpy(idsOutput, diaServerOutputEnv, len);
        //Correcting Calling risky function
        strncat(idsOutput, "/IDS.out", ((len + strlen("/IDS.out") +1)-strlen(idsOutput)-1));

        cout <<"Output sent to "<< idsOutput << endl;
 
        FILE* fp = freopen(idsOutput, "a", stdout);
        delete [] idsOutput;

    }
    else
    {
        cout <<"Output sent to ./IDS.out"<< endl;
    }
 
    //Correcting Out-of-bound Access
    char buf[BUF_SIZE*2];
    memset(buf, 0, BUF_SIZE*2);

    if (setvbuf(stdout, buf, _IOLBF, (BUF_SIZE * 2)) != ITS_SUCCESS)
    {
        cout << "Error opening buffer" << endl;
    }
 
    IDSMMLServer idsMMLServer("IDS MML Server");

    ENGINE_Initialize(argc , argv, NULL, 0);

    ENGINE_Run(argc, argv);

    return (0);
}
