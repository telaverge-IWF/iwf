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
 *  ID: $Id: test1DecodeInvoke.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: test1DecodeInvoke.c,v $
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
 * LOG: Revision 1.2  1998/11/11 00:17:01  ite
 * LOG: More testing on bitstrings. Debugging vendor library.
 * LOG:
 * LOG: Revision 1.1  1998/09/14 15:30:15  ite
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
TEST_DecodeInvoke( TCAP_CPT *cpt, ITS_HANDLE handle )
{
    int ret = 0, nbits = 0;
    unsigned char *bitstr = NULL;
    void *data;

    if (cpt->ptype != TCPPT_TC_INVOKE)
    {
        printf("Received component type 0x02x - not an invoke."
               " Will not try to decode. \n");
        return TEST_BAD_MSG;
    }

    switch(cpt->u.invoke.operation.data[2])
    {
        case (GSMMAP_OP_sendIdentification):
        {
            printf("Going to decode RestoreData Invoke.\n");
            ret = GSMMAP_DecodeSendIdentificationArg(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_SendIdentificationArgTmsi(data);
            }
        }
        break;

        case (GSMMAP_OP_restoreData):
        {
            printf("Going to decode RestoreData Invoke.\n");
            ret = GSMMAP_DecodeRestoreDataArg(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_RestoreDataArg(data);
            }
        }
        break;
        
        case (GSMMAP_OP_insertSubscriberData):
        {
            struct type_GSMMAP_InsertSubscriberDataArg *arg;
            printf("Going to decode InsertSubscriberDataArg Invoke.\n");
            ret = GSMMAP_DecodeInsertSubscriberDataArg(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                arg = (struct type_GSMMAP_InsertSubscriberDataArg *)data;
                if (arg->odb__Data->odb__GeneralDataArg != NULL)
                {
                    (char *)bitstr = bitstr2strb(arg->odb__Data->odb__GeneralDataArg, 
                                                 &nbits);
                    printf("nbits %d, bitstr 0x%02x.\n", nbits, *bitstr);
                    free(bitstr);
                }
                if (arg->odb__Data->odb__HPLMN__Data != NULL)
                {
                    (char *)bitstr = bitstr2strb(arg->odb__Data->odb__HPLMN__Data, 
                                                 &nbits);
                    printf("nbits %d, bitstr 0x%02x.\n", nbits, *bitstr);
                    free(bitstr);
                }
                free_GSMMAP_InsertSubscriberDataArg(data);
            }
        }
        break;
        
        case (GSMMAP_OP_activateTraceMode):
        {
            printf("Going to decode ActivateTraceModeArg Invoke.\n");
            ret = GSMMAP_DecodeActivateTraceModeArg(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_ActivateTraceModeArg(data);
            }
        }
        break;
        
        case (GSMMAP_OP_deactivateTraceMode):
        {
            printf("Going to decode DeactivateTraceModeArg Invoke.\n");
            ret = GSMMAP_DecodeDeactivateTraceModeArg(handle, cpt, &data);
            if (ret == ITS_SUCCESS)
            {
                free_GSMMAP_DeactivateTraceModeArg(data);
            }
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

