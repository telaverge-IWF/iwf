/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: INTERNAL Demo                                                  *
 *                                                                          *
 ****************************************************************************
 *  ID:$Id  $
 *      
 *  $Log: followme_app_main.c,v $
 *  Revision 9.1  2005/03/23 12:54:28  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.2  2005/03/21 13:53:27  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.1.2.1  2004/12/28 14:04:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.1  2004/05/27 15:15:32  sjaddu
 *  Files created for followme app.
 *
 *
 ****************************************************************************/

#include <engine.h>
#include <sip.h>

/* Debug console function */
void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);

int main(int argc, const char **argv)
{
    printf("\n\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies India Pvt Ltd.\n");
    printf("\t *****  Accelero - SIP FollowMe Demo     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n\n");


    /* Set the application name */
    APPL_SetName("followme");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    /* set debug console function here */
    DBC_SetDoCommand(ExecuteCommand);

    /* Initialize Engine */
    ENGINE_Initialize(argc, argv, NULL, 0);

    /* Run Engine */
    return(ENGINE_Run(argc, argv));
}


/*
 * Debug console function, define all commans here
 */
void ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "Exit", "Exit demo", "","Exit the demo application"))
    {
        exit(0);
    }
}

/* These are required to make linker happy */
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;

#if defined(CCITT)
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#elif defined(ANSI)
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#endif

