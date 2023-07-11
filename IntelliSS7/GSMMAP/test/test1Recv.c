/****************************************************************************
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
 * CONTRACT: GSMMAP testbed                                                 *
 *                                                                          *
 *     FILE: test1Recv.c                                                    *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: test1Recv.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: test1Recv.c,v $
 * LOG: Revision 9.1  2005/03/23 12:51:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:50  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:20  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:21  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:08  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:08  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1998/09/14 15:30:17  ite
 * LOG: Tested successfully on NMS hardware. This version also sent to Nokia
 * LOG: for trial.
 * LOG:
 * LOG: Revision 1.1  1998/09/03 22:10:35  jpakrasi
 * LOG: First draft. Setting up test prgm on NMS hardware.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_fifo_trans.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_route.h>

#include <tcap.h>
#include <GSMMAP.h>
#include <its_GSMMAP.h>
#include <GSMMAP-types.h>
#include <assert.h>

#include <testcommon.h>

ITS_HANDLE handle = NULL;

/*
 * termination handler
 */
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
#else
static void exitHandler(int sig)
#endif
{
    ITS_Terminate(handle);
}

int
main(int argc, char** argv)
{
    TCAP_CPT cpt;//, cpts;
    ITS_EVENT event;	
    ITS_HDR hdr;
    TCAP_DLG dlg;
    
    /* 
     * Fill in the PC and SSN in the address strings  
     */

    unsigned char dest_addr_string[] ={0xc3,0x00,0x00,0x01,0x03};
    unsigned char orig_addr_string[] ={0xc0,0x00,0x00,0x00,0x00};
   
    unsigned char digits[9] = {0x01,0x01,0x21,0x0A,0x04,0x77,0x62,0x60,0x68};
  	
#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    handle = (ITS_HANDLE)ITS_Initialize(ITS_TCAP | ITS_SCCP |
                                        ITS_TRANSPORT_SS7 |
                                        ITS_TRANSPORT_SINGLE_USER, 1);
    if (handle == NULL)
    {
        printf("Couldn't create ITS_HANDLE. Exiting...\n");
        exit(0);
    }
    
    memset(&hdr, 0, sizeof(hdr));
    memset(&dlg, 0, sizeof(dlg));
    
    for(;;)
    {
        /*
         * Wait for event, get event, check for the type (dialogue/component) 
         * and send a Return Result (RRL)
         */
        printf("Waiting for event..\n\n");
        if(ITS_GetNextEvent(handle, &event) == ITS_SUCCESS)
        {
            printf("Event received\n");
            
            if(event.data[0] == ITS_TCAP_DLG)
            {
                printf("Received Dialogue\n");
                TCAP_ReceiveDialogue(handle, &event, &hdr, &dlg);
                printf("ptype 0x%x dialogue_id 0x%x\n",
                        dlg.ptype, hdr.context.dialogue_id);
            }
            if (event.data[0] == ITS_TCAP_CPT)
            {
                ITS_OCTET inv;

                printf("Received Component: ");
                TCAP_ReceiveComponent(handle, &event, &hdr, &cpt);
                printf(" ptype 0x%x\n", cpt.ptype);			

                TEST_DecodeInvoke( &cpt, handle );

                inv = cpt.u.invoke.invoke_id.data[2];

                if (dlg.ptype != TCPPT_TC_UNI)
                {
                    TEST_SendGSMMAPResult(&hdr, &cpt, handle);
                }
            }
        } /* ITS_GetNextEvent() */
    } /* for(;;) */

    return EXIT_SUCCESS;
}





