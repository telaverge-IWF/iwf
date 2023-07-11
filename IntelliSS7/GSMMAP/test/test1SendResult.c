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
 *  ID: $Id: test1SendResult.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: test1SendResult.c,v $
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
 * LOG: Revision 2.0  1999/12/03 23:19:09  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1998/09/14 15:30:18  ite
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
TEST_SendGSMMAPResult(ITS_HDR *hdr, TCAP_CPT *cpt, ITS_HANDLE handle)
{
    TCAP_CPT rr_cpt;
    ITS_HDR resp_hdr;
    TCAP_DLG resp_dlg;
    int ret = 0;

    /*
     * Some generic data for building messages.
     */
    unsigned char digits[9] = { 0x01,0x01,0x21,0x0A,0x04,0x97,0x25,0x23,0x13 };
    unsigned char ESN[4] = { 0x01,0x01,0x02,0x03 };
    unsigned char MIN[5] = { 0x04,0x77,0x62,0x60,0x68 };
    unsigned char RAND[16] = { 0x43, 0x23, 0x65, 0x83, 0x39, 0x74, 0x52, 0x28,
                               0x78, 0x19, 0x48, 0x81, 0x72, 0x57, 0x35, 0x95 };

    memset( (char *)&rr_cpt, 0, sizeof(TCAP_CPT));
    memset( (char *)&resp_hdr, 0, sizeof(ITS_HDR));
    memset( (char *)&resp_dlg, 0, sizeof(TCAP_DLG));

    resp_hdr.context.dialogue_id = hdr->context.dialogue_id;
    resp_hdr.type = ITS_TCAP;

    resp_dlg.ptype = TCPPT_TC_END;
    resp_dlg.u.end.cpt_present = 1;

    rr_cpt.ptype = TCPPT_TC_RESULT_L;	            
    rr_cpt.u.result.invoke_id.data[0] = INVOKE_TAG; /* tag */
    rr_cpt.u.result.invoke_id.data[1] = 1; 
    rr_cpt.u.result.invoke_id.data[2] = cpt->u.invoke.invoke_id.data[2]; 
    rr_cpt.u.result.invoke_id.len = 3;	                  
    
    rr_cpt.u.result.operation.len = 3;
    rr_cpt.u.result.operation.data[0] = LOCAL_OP_TAG;
    rr_cpt.u.result.operation.data[1] = 1;
    rr_cpt.u.result.operation.data[2] = cpt->u.invoke.operation.data[2];
    rr_cpt.last_component = 1;


    switch(cpt->u.invoke.operation.data[2])
    {
        case (GSMMAP_OP_sendIdentification):
        {
            struct type_GSMMAP_SendIdentificationRes *arg;
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
	        arg = calloc(1, sizeof(struct type_GSMMAP_SendIdentificationRes));
            /*
             * Fill in IMSI
             */

            arg->imsi = calloc( 1, sizeof(struct qbuf) + 5 );
            arg->imsi->qb_len = 5;
            arg->imsi->qb_data = arg->imsi->qb_base;
            memcpy( arg->imsi->qb_data, MIN, 5 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->imsi->qb_forw = arg->imsi;
            arg->imsi->qb_back = arg->imsi;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            /* 
             * Fill in AuthenticationSetList with one list. 
             * ie, one rand, one sres, and one kc.
             */
            arg->authenticationSetList = calloc(1, 
                                            sizeof(struct element_GSMMAP_2));
            arg->authenticationSetList->next = NULL;

            arg->authenticationSetList->element_GSMMAP_3 = calloc(1, 
                                            sizeof(struct element_GSMMAP_4));
            /* rand */
            arg->authenticationSetList->element_GSMMAP_3->rand = 
                                        calloc(1, sizeof(struct qbuf) + 16);
            arg->authenticationSetList->element_GSMMAP_3->rand->qb_len = 16;
            arg->authenticationSetList->element_GSMMAP_3->rand->qb_data = 
                 arg->authenticationSetList->element_GSMMAP_3->rand->qb_base;
            memcpy(arg->authenticationSetList->element_GSMMAP_3->rand->qb_data, 
                   RAND, 16);
            arg->authenticationSetList->element_GSMMAP_3->rand->qb_forw = 
                            arg->authenticationSetList->element_GSMMAP_3->rand;
            arg->authenticationSetList->element_GSMMAP_3->rand->qb_back = 
                            arg->authenticationSetList->element_GSMMAP_3->rand;

            /* sres */
            arg->authenticationSetList->element_GSMMAP_3->sres = 
                                            calloc(1, sizeof(struct qbuf) + 4);
            arg->authenticationSetList->element_GSMMAP_3->sres->qb_len = 4;
            arg->authenticationSetList->element_GSMMAP_3->sres->qb_data = 
                    arg->authenticationSetList->element_GSMMAP_3->sres->qb_base;
            memcpy(arg->authenticationSetList->element_GSMMAP_3->sres->qb_data, 
                   ESN, 4);
            arg->authenticationSetList->element_GSMMAP_3->sres->qb_forw = 
                            arg->authenticationSetList->element_GSMMAP_3->sres;
            arg->authenticationSetList->element_GSMMAP_3->sres->qb_back = 
                            arg->authenticationSetList->element_GSMMAP_3->sres;

            /* kc */
            arg->authenticationSetList->element_GSMMAP_3->kc = 
                                            calloc(1, sizeof(struct qbuf) + 8);
            arg->authenticationSetList->element_GSMMAP_3->kc->qb_len = 8;
            arg->authenticationSetList->element_GSMMAP_3->kc->qb_data = 
                    arg->authenticationSetList->element_GSMMAP_3->kc->qb_base;
            memcpy(arg->authenticationSetList->element_GSMMAP_3->kc->qb_data, 
                   digits, 8);
            arg->authenticationSetList->element_GSMMAP_3->kc->qb_forw = 
                                arg->authenticationSetList->element_GSMMAP_3->kc;
            arg->authenticationSetList->element_GSMMAP_3->kc->qb_back = 
                                arg->authenticationSetList->element_GSMMAP_3->kc;

            printf("Encode and Send SendIdentificationRes Result.\n");
            ret = GSMMAP_SendSendIdentificationRes( handle, &resp_hdr, &rr_cpt, 
                                                    (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send SendIdentificationRes failed with error %d.\n", ret);
                return TEST_BAD_MSG;
            }
        }
        break;

        case (GSMMAP_OP_restoreData):
        {
            struct type_GSMMAP_RestoreDataRes *arg;
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
	        arg = calloc(1, sizeof(struct type_GSMMAP_RestoreDataRes));

            /*
             * Fill in HLR Number
             */

            arg->hlr__Number = calloc( 1, sizeof(struct qbuf) + 5 );
            arg->hlr__Number->qb_len = 5;
            arg->hlr__Number->qb_data = arg->hlr__Number->qb_base;
            memcpy( arg->hlr__Number->qb_data, MIN, 5 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->hlr__Number->qb_forw = arg->hlr__Number;
            arg->hlr__Number->qb_back = arg->hlr__Number;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            /*
             * Fill in mscNotReachable
             */
            arg->optionals |= opt_GSMMAP_RestoreDataRes_mscNotReachable;
            arg->mscNotReachable = 1; /* Does not matter */

	        printf("Building component\n");


            printf("Encode and Send RestoreDataRes Result.\n");
            ret = GSMMAP_SendRestoreDataRes( handle, &resp_hdr, &rr_cpt, 
                                             (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send RestoreDataRes failed with error %d.\n", ret);
                return TEST_BAD_MSG;
            }
        }
        break;
        
        case (GSMMAP_OP_insertSubscriberData):
        {
            struct type_GSMMAP_InsertSubscriberDataRes *arg;
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
	        arg = calloc(1, sizeof(struct type_GSMMAP_InsertSubscriberDataRes));

            /*
             * Fill in teleServiceList.
             */
            arg->teleserviceList = calloc(1, sizeof(struct element_GSMMAP_73));

            arg->teleserviceList->element_GSMMAP_74 = 
                                            calloc(1, sizeof(struct qbuf) + 1);
            arg->teleserviceList->element_GSMMAP_74->qb_len = 1;
            arg->teleserviceList->element_GSMMAP_74->qb_data = 
                            arg->teleserviceList->element_GSMMAP_74->qb_base;
            arg->teleserviceList->element_GSMMAP_74->qb_data[0] = 4;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->teleserviceList->element_GSMMAP_74->qb_forw = 
                                    arg->teleserviceList->element_GSMMAP_74;
            arg->teleserviceList->element_GSMMAP_74->qb_back = 
                                    arg->teleserviceList->element_GSMMAP_74;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            /* Fill in another element in the teleserviceList */
            arg->teleserviceList->next = 
                                calloc(1, sizeof(struct element_GSMMAP_73));

            arg->teleserviceList->next->element_GSMMAP_74 = 
                                            calloc(1, sizeof(struct qbuf) + 1);
            arg->teleserviceList->next->element_GSMMAP_74->qb_len = 1;
            arg->teleserviceList->next->element_GSMMAP_74->qb_data = 
                        arg->teleserviceList->next->element_GSMMAP_74->qb_base;
            arg->teleserviceList->next->element_GSMMAP_74->qb_data[0] = 6;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->teleserviceList->next->element_GSMMAP_74->qb_forw = 
                                arg->teleserviceList->next->element_GSMMAP_74;
            arg->teleserviceList->next->element_GSMMAP_74->qb_back = 
                                arg->teleserviceList->next->element_GSMMAP_74;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            arg->teleserviceList->next->next = NULL;

            /*
             * Fill in odb-GeneralData.
             */

            ret = GSMMAP_SendInsertSubscriberDataRes( handle, &resp_hdr, &rr_cpt,
                                                      (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Cannot build/send component \n");
            }
        }
        break;
        
        default:
        {
            printf("\nNot Implemented yet....\n");
            ret =  TEST_NOT_IMPL;
        }
        break;
    }

    printf("Sending dialogue \n");

    if (ret == ITS_SUCCESS)
    {
        ret = TCAP_SendDialogue(handle, &resp_hdr, &resp_dlg);
    }
    if (ret != ITS_SUCCESS && ret != TEST_NOT_IMPL)
    {       
        printf("Cannot send dialogue \n");
    }
    else if (ret == TEST_NOT_IMPL)
    {
        printf("Nothing sent out, as message is not implemented.\n");
    }
    else if (ret == ITS_SUCCESS)
    {
        printf("Dialogue sent \n");
    }
    fflush(stdout);

    return ret;
}

