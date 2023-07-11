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
 *  ID: $Id: test1SendInvoke.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: test1SendInvoke.c,v $
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
 * LOG: Revision 1.3  1998/11/11 00:17:02  ite
 * LOG: More testing on bitstrings. Debugging vendor library.
 * LOG:
 * LOG: Revision 1.2  1998/11/05 23:35:32  ite
 * LOG: Update to current IntelliSS7
 * LOG:
 * LOG: Revision 1.1  1998/09/14 15:30:17  ite
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
TEST_SendGSMMAPInvoke(int cmdInput, int *replyExpected, ITS_HANDLE handle)
{
    int ret = 0, c;
    TCAP_CPT cpt;
    ITS_EVENT event;    
    ITS_HDR hdr;
    TCAP_DLG dlg;

    /*
     * Some generic data for building messages.
     */
	unsigned char digits[9] = {0x01,0x01,0x21,0x0A,0x04,0x97,0x25,0x23,0x13};
    unsigned char ESN[4] = {0x01,0x01,0x02,0x03};
	unsigned char MIN[5] = {0x04,0x77,0x62,0x60,0x68};
    unsigned char bitstr1 = 0x8C;
    unsigned char bitstr2 = 0x90;
    unsigned char ACNAME[11] = {0xA1,0x09,0x06,0x07,0x04,0x00,0x00,0x01,0x00,
                                0x0F,0x02};

    /* 
     * Fill in the PC and SSN in the address strings  
         0x13, address indicator: routeOnGT, GTi=0100, SSNi=1, PCi=1 
    0x2, 0x0,  Signalling point code
    0x4,   SSN=4 
    0x0,  GT1: translation type
    0x11,  GT2: numberingPlan=E.164, encodingScheme=odd 
    0x4,   GT3: natureOfAddress=International
    0x44, 0x83, 0x55, 0x10, 0x32, 0x04  addr digits; 44385501234

     */
    //unsigned char dest_addr_string[] = { 0x13,0x02,0x00,0x04, 0x00, 0x11, 0x04, 
    //                                     0x44, 0x83, 0x55, 0x10, 0x32, 0x04 };

    /* 
     * Dest addr with GTT only
     * 0x10, address indicator: routeOnGT, GTi=0100, no SSN, no PC
     * 0x0, GT1: translation type
     * 0x11,  GT2: numberingPlan=E.164, encodingScheme=odd 
     * 0x4,   GT3: natureOfAddress=International
     * 0x44, 0x83, 0x55, 0x10, 0x32, 0x04  addr digits; 44385501234
     */
    //unsigned char dest_addr_string[] = { 0x10, 0x00, 0x11, 0x04, 
    //                                     0x44, 0x83, 0x55, 0x10, 0x32, 0x04 };

	unsigned char dest_addr_string[] ={0xc3,0x02,0x00,0x04};
	//unsigned char dest_addr_string[] ={0xc3,0x00,0x01,0x03};
	unsigned char orig_addr_string[] ={0xc0,0x00,0x00,0x00};

    memset((char *)&cpt, 0, sizeof(TCAP_CPT));
    memset((char *)&hdr, 0, sizeof(ITS_HDR));
    memset((char *)&dlg, 0, sizeof(TCAP_DLG));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    hdr.type = ITS_TCAP;
    TCAP_AllocateDialogueId(&hdr.context.dialogue_id);
    printf("dialogue_id allocated = %d.\n", hdr.context.dialogue_id);
    dlg.ptype = TCPPT_TC_BEGIN;

    dlg.u.begin.orig_addr.len = 4;
    dlg.u.begin.dest_addr.len = 4;
    printf("Dest addr copied in: ");
    for (c = 0; c < 4; c++)
    {
        dlg.u.begin.dest_addr.data[c] = dest_addr_string[c];
        printf(" 0x%02x", dlg.u.begin.dest_addr.data[c]);
    }
    printf("\n");

    printf("Orig addr copied in: ");
    for (c = 0; c < 4; c++)
    {
        dlg.u.begin.orig_addr.data[c] = orig_addr_string[c];
        printf(" 0x%02x", dlg.u.begin.orig_addr.data[c]);
    }
    printf("\n");
    dlg.u.begin.qos.indicator |= QOSI_RET_OPT;
    dlg.u.begin.cpt_present = 1;

    cpt.ptype = TCPPT_TC_INVOKE;
//  cpt.u.invoke.timeout = 15;
    cpt.u.invoke.opClass = 1;

    cpt.u.invoke.invoke_id.data[0] = INVOKE_TAG; /* tag */
    cpt.u.invoke.invoke_id.data[1] = 1; 
    cpt.u.invoke.invoke_id.data[2] = 5; 
    cpt.u.invoke.invoke_id.len = 3;
    cpt.u.invoke.linked_id.len = 0;
    cpt.last_component = 1;

    printf("Built component header, building parameters.\n");

    switch(cmdInput)
    {
        case (TEST_SENDID):
        {
            struct type_GSMMAP_SendIdentificationArgTmsi *arg;

            /*dlg.u.begin.orig_addr.len = 4;
            dlg.u.begin.dest_addr.len = 10;
            printf("Dest addr copied in: ");
            for (c = 0; c < dlg.u.begin.dest_addr.len; c++)
            {
                dlg.u.begin.dest_addr.data[c] = dest_addr_string[c];
                printf(" 0x%02x", dlg.u.begin.dest_addr.data[c]);
            }
            printf("\n");

            printf("Orig addr copied in: ");
            for (c = 0; c < dlg.u.begin.orig_addr.len; c++)
            {
                dlg.u.begin.orig_addr.data[c] = orig_addr_string[c];
                printf(" 0x%02x", dlg.u.begin.orig_addr.data[c]);
            }
            printf("\n");*/
            dlg.u.begin.qos.indicator |= QOSI_RET_OPT;
            dlg.u.begin.cpt_present = 1;

            dlg.u.begin.ac_name.len = 11;
            for (c = 0; c < dlg.u.begin.ac_name.len; c++)
            {
                dlg.u.begin.ac_name.data[c] = ACNAME[c];
            }

            dlg.u.begin.user_info.len = 9;
            for (c = 0; c < dlg.u.begin.ac_name.len; c++)
            {
                dlg.u.begin.user_info.data[c] = digits[c];
            }

            printf("Building component\n");
            arg = calloc(1, sizeof(struct type_GSMMAP_SendIdentificationArgTmsi) 
                            + 4);
            arg->qb_len = 4;
            arg->qb_data = arg->qb_base;
            memcpy( arg->qb_data, ESN, 4 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->qb_forw = arg;
            arg->qb_back = arg;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            printf("Encode and Send SendIdentification Invoke.\n");
            ret = GSMMAP_SendSendIdentificationArg( handle, &hdr, &cpt, 
                                                    (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send SendIdentification failed with error %d.\n", ret);
                *replyExpected = 0;
            }
            *replyExpected = 1;
        }
        break;

        case (TEST_RESTDATA):
        {
            struct type_GSMMAP_RestoreDataArg *arg;

            printf("Building component\n");
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
	        arg = calloc(1, sizeof(struct type_GSMMAP_RestoreDataArg));

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
             * Fill in LMSI
             */
            arg->lmsi = calloc( 1, sizeof(struct qbuf) + 4 );
            arg->lmsi->qb_len = 4;
            arg->lmsi->qb_data = arg->lmsi->qb_base;
            memcpy( arg->lmsi->qb_data, digits, 4 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->lmsi->qb_forw = arg->lmsi;
            arg->lmsi->qb_back = arg->lmsi;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            printf("Encode and Send RestoreDataArg Invoke.\n");
            ret = GSMMAP_SendRestoreDataArg( handle, &hdr, &cpt, (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send RestoreDataArg failed with error %d.\n", ret);
                *replyExpected = 0;
            }
            *replyExpected = 1;
        }
        break;
        
        case (TEST_INSSUBSDATA):
        {
            struct type_GSMMAP_InsertSubscriberDataArg *arg;

            printf("Building component\n");
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
	        arg = calloc(1, sizeof(struct type_GSMMAP_InsertSubscriberDataArg));

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
             * Fill in provisionedSS.
             */
            arg->provisionedSS = calloc(1, sizeof(struct element_GSMMAP_48));
            arg->provisionedSS->next = NULL; /* only one element in this seq */

            arg->provisionedSS->element_GSMMAP_49 = 
                                calloc(1, sizeof(struct choice_GSMMAP_9));
            /* CHOICE: ss_Data. */
            arg->provisionedSS->element_GSMMAP_49->offset = 
                                                choice_GSMMAP_9_ss__Data;
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data = 
                                calloc(1, sizeof(struct element_GSMMAP_67));
            /* ss_Code in ss_Data */
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code = 
                                        calloc(1, sizeof(struct qbuf) + 1);
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code->qb_len = 1;
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code->qb_data = 
                arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code->qb_base;
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code->qb_data[0] = 57;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code->qb_forw = 
                    arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code;
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code->qb_back = 
                    arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__Code;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__SubscriptionOption = 
                                    calloc(1, sizeof(struct choice_GSMMAP_14));
            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__SubscriptionOption->offset = 
                                    choice_GSMMAP_14_overrideCategory;

            arg->provisionedSS->element_GSMMAP_49->un.ss__Data->ss__SubscriptionOption->un.overrideCategory =
                                    int_GSMMAP_overrideCategory_overrideDisabled;

            /*
             * Fill in odb_GeneralData.
             */
            arg->odb__Data = calloc(1, sizeof(struct element_GSMMAP_70));

            /*
             * To fill in a parameter which is a BIT STRING, first construct 
             * the bit string to be sent, then call the following function, 
             * where the second parameter gives the maximum number of bits 
             * that are valid in the bit string, starting at the MSB.
             */
            arg->odb__Data->odb__GeneralDataArg = 
                        strb2bitstr(&bitstr1, 6, PE_CLASS_UNIV, PE_PRIM_BITS);

            arg->odb__Data->odb__HPLMN__Data = 
                        strb2bitstr(&bitstr2, 4, PE_CLASS_UNIV, PE_PRIM_BITS);

            /*
             * Fill in both optionals.
             */
            arg->optionals |= opt_GSMMAP_InsertSubscriberDataArg_subscriberStatus;
            arg->optionals |= 
                opt_GSMMAP_InsertSubscriberDataArg_roamingRestrictionDueToUnsupportedFeature;

            arg->subscriberStatus = int_GSMMAP_subscriberStatus_serviceGranted;
            arg->roamingRestrictionDueToUnsupportedFeature = 1;

            printf("Encode and Send InsertSubscriberDataArg Invoke.\n");
            ret = GSMMAP_SendInsertSubscriberDataArg( handle, &hdr, &cpt, 
                                                      (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send RestoreDataArg failed with error %d.\n", ret);
                *replyExpected = 0;
            }
            *replyExpected = 1;
        }
        break;
        
        case (TEST_ACTTRMODE):
        {
            struct type_GSMMAP_ActivateTraceModeArg *arg;

            dlg.ptype = TCPPT_TC_UNI;
            /*dlg.u.uni.orig_addr.len = 4;
            dlg.u.uni.dest_addr.len = 13;
            printf("Dest addr copied in: ");
            for (c = 0; c < dlg.u.uni.dest_addr.len; c++)
            {
                dlg.u.uni.dest_addr.data[c] = dest_addr_string[c];
                printf(" 0x%02x", dlg.u.uni.dest_addr.data[c]);
            }
            printf("\n");

            printf("Orig addr copied in: ");
            for (c = 0; c < dlg.u.uni.orig_addr.len; c++)
            {
                dlg.u.uni.orig_addr.data[c] = orig_addr_string[c];
                printf(" 0x%02x", dlg.u.uni.orig_addr.data[c]);
            }
            printf("\n");*/
            dlg.u.uni.qos.indicator |= QOSI_RET_OPT;
            dlg.u.uni.cpt_present = 1;

            cpt.u.invoke.opClass = 2;

            printf("Building component\n");
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
            arg = calloc(1, sizeof(struct type_GSMMAP_ActivateTraceModeArg));

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
             * Fill in traceReference
             */
            arg->traceReference = calloc( 1, sizeof(struct qbuf) + 2 );
            arg->traceReference->qb_len = 2;
            arg->traceReference->qb_data = arg->traceReference->qb_base;
            memcpy( arg->traceReference->qb_data, ESN, 2 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->traceReference->qb_forw = arg->traceReference;
            arg->traceReference->qb_back = arg->traceReference;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            
            /*
             * Fill in traceType.
             */
            arg->traceType = 23;

            /*
             * Fill in omc__ld
             */
            arg->omc__ld = calloc( 1, sizeof(struct qbuf) + 9 );
            arg->omc__ld->qb_len = 9;
            arg->omc__ld->qb_data = arg->omc__ld->qb_base;
            memcpy( arg->omc__ld->qb_data, digits, 9 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->omc__ld->qb_forw = arg->omc__ld;
            arg->omc__ld->qb_back = arg->omc__ld;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

            printf("Encode and Send ActivateTraceModeArg Invoke.\n");
            ret = GSMMAP_SendActivateTraceModeArg( handle, &hdr, &cpt, 
                                                   (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send ActivateTraceModeArg failed with error %d.\n", ret);
            }

            *replyExpected = 0; /* this is being sent as a Unidirectional */
        }
        break;
        
        case (TEST_DEACTTRMODE):
        {
            struct type_GSMMAP_DeactivateTraceModeArg *arg;

            dlg.ptype = TCPPT_TC_UNI;
            dlg.u.uni.orig_addr.len = 4;
            dlg.u.uni.dest_addr.len = 4;
            printf("Dest addr copied in: ");
            for (c = 0; c < dlg.u.uni.dest_addr.len; c++)
            {
                dlg.u.uni.dest_addr.data[c] = dest_addr_string[c];
                printf(" 0x%02x", dlg.u.uni.dest_addr.data[c]);
            }
            printf("\n");

            printf("Orig addr copied in: ");
            for (c = 0; c < dlg.u.uni.orig_addr.len; c++)
            {
                dlg.u.uni.orig_addr.data[c] = orig_addr_string[c];
                printf(" 0x%02x", dlg.u.uni.orig_addr.data[c]);
            }
            printf("\n");
            dlg.u.uni.qos.indicator |= QOSI_RET_OPT;
            dlg.u.uni.cpt_present = 1;

            cpt.u.invoke.opClass = 2;

            printf("Building component\n");
            /* 
             * Strucures MUST be dynamically allocated.  The ITS will free
	         * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	         * INITIALIZE EVERY FIELD!!!
	         */
            arg = calloc(1, sizeof(struct type_GSMMAP_DeactivateTraceModeArg));

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
             * Fill in traceReference
             */
            arg->traceReference = calloc( 1, sizeof(struct qbuf) + 2 );
            arg->traceReference->qb_len = 2;
            arg->traceReference->qb_data = arg->traceReference->qb_base;
            memcpy( arg->traceReference->qb_data, ESN, 2 );
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	         * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	         * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	         * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	         * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            arg->traceReference->qb_forw = arg->traceReference;
            arg->traceReference->qb_back = arg->traceReference;
	        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
            
            printf("Encode and Send DeactivateTraceModeArg Invoke.\n");
            ret = GSMMAP_SendDeactivateTraceModeArg( handle, &hdr, &cpt, 
                                                     (void *)arg );
            if (ret != ITS_SUCCESS)
            {
                printf("Send DeactivateTraceModeArg failed with error %d.\n", ret);
            }

            *replyExpected = 0; /* this is being sent as a Unidirectional */
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
        ret = TCAP_SendDialogue(handle, &hdr, &dlg);
    }
    if (ret != ITS_SUCCESS && ret != TEST_NOT_IMPL)
    {       
        printf("Cannot send dialogue \n");
    }
    else if (ret == TEST_NOT_IMPL)
    {
        printf("Nothing send out, as message is not implemented.\n");
    }
    else if (ret == ITS_SUCCESS)
    {
        printf("Dialogue sent \n");
    }
    fflush(stdout);

    return ret;
}

