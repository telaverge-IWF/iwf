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
 ****************************************************************************
 *
 *  ID: $Id: test1DecodeResult.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: test1DecodeResult.c,v $
 * LOG: Revision 9.1  2005/03/23 12:51:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:47  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:20  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:20  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:07  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:07  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1998/09/14 15:30:16  ite
 * LOG: Tested successfully on NMS hardware. This version also sent to Nokia
 * LOG: for trial.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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

int 
TEST_DecodeGSMMAPResult( TCAP_CPT *cpt, ITS_HANDLE handle )
{
    int ret = 0;
    void *data;

    if (cpt->ptype != TCPPT_TC_RESULT_L && cpt->ptype != TCPPT_TC_RESULT_NL)
    {
        printf("Received component type 0x02x - not an Result."
               " Will not try to decode. \n", cpt->ptype);
        return TEST_BAD_MSG;
    }

    if (cpt->u.result.param.len <= 2)
    {
        printf("Received component type 0x%02x (Opcode %d) does not have"
               " any parameters. Will not process any further.\n",
               cpt->ptype, cpt->u.result.operation.data[2]);
        return TEST_BAD_MSG;
    }

    switch(cpt->u.result.operation.data[2])
    {
        case (GSMMAP_OP_sendIdentification):
        {
            printf("Going to decode SendIdentificationRes Result.\n");
            ret = GSMMAP_DecodeSendIdentificationRes(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_SendIdentificationRes(data);
            }
        }
        break;

        case (GSMMAP_OP_restoreData):
        {
            printf("Going to decode RestoreData Result.\n");
            ret = GSMMAP_DecodeRestoreDataRes(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_RestoreDataRes(data);
            }
        }
        break;
        
        case (GSMMAP_OP_insertSubscriberData):
        {
            printf("Going to decode InsertSubscriberData Result.\n");
            ret = GSMMAP_DecodeInsertSubscriberDataRes(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_InsertSubscriberDataRes(data);
            }
        }
        break;
        
        case (GSMMAP_OP_activateTraceMode):
        {
            printf("\nNot Implemented yet....\n");
            ret =  TEST_NOT_IMPL;
        }
        break;
        
        case (GSMMAP_OP_deactivateTraceMode):
        {
            printf("\nNot Implemented yet....\n");
            ret =  TEST_NOT_IMPL;
        }
        break;

        default:
        {
            printf("\nNot Implemented yet....\n");
            ret =  TEST_NOT_IMPL;
        }
        break;

    } /* switch(opFam) */
    return ret;
}

