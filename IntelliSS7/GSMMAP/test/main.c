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
 *     FILE: main.c                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: main.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: main.c,v $
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
 * LOG: Revision 3.1  2000/08/15 23:57:06  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:06  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/03/24 17:40:56  mmiers
 * LOG:
 * LOG:
 * LOG: Start updating the tests.
 * LOG:
 * LOG: Revision 1.1  1998/09/14 15:49:35  jpakrasi
 * LOG: Basic testing of encode/decode functions. Tested OK.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <its.h>
#include <its_ss7_stubs.h>

#include <tcap.h>
#include <GSMMAP.h>
#include <its_GSMMAP.h>
#include <GSMMAP-types.h>

int TCAP_SendComponent(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt);
struct qbuf *FollowQBuffer(struct qbuf *arg);

int main(int argc, char** argv)
{
	TCAP_CPT cpt;
	int dialogue_id = 4, ret, c;
	ITS_HANDLE handle = (void *)1;
	ITS_HDR hdr;
    /*
     * Some data for encoding test messages. 
     */
	unsigned char digits[4] = {0x07,0x06,0x12,0x48};
	unsigned char MIN[5] = {0x07,0x06,0x09,0x01,0x05};
	unsigned char SID[5] = {0x07,0x06,0x09,0x01,0x05};
	unsigned char AAV = 0xFF;
	unsigned char ARUC[3] = {0x01,0x02,0x03};
	unsigned char mydata[3]= {0x01, 0x00, 0xFF};
	unsigned char LID[2]={0x01,0x02};
	unsigned char RSSD[7] = {0x07,0x06,0x09,0x01,0x05,0x01,0x05};
	unsigned char RVUC[3] = {0x07,0x06,0x09};
	unsigned char SSD[16] = {0x07,0x06,0x09,0x01,0x05,0x01,0x05,0x07,0x06,0x09,0x01,0x05,0x01,0x05,0x01,0x05};
    unsigned char bitstr[6] = { 0x0A, 0x3B, 0x5F, 0x29, 0x1C, 0xD0 };
    /*
     * Structures declared in GSMMAP-types.h
     */
    struct type_GSMMAP_RestoreDataArg *arg;
    struct type_GSMMAP_InsertSubscriberDataArg *arg2;

        ITS_GlobalStart(0);

	fflush(stdout);

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	/* strucures MUST be dynamically allocated.  The ITS will free
	 * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	 * INITIALIZE EVERY FIELD!!!
	 */
	arg = calloc(1, sizeof(struct type_GSMMAP_RestoreDataArg));

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

    /*
     * The ITS_HDR only needs the dialogue ID to be filled in.
     */
	hdr.context.dialogue_id = dialogue_id;

    printf("Encode and Send RestoreDataArg Invoke.\n");
    ret = GSMMAP_SendRestoreDataArg( handle, &hdr, &cpt, (void *)arg );
    if (ret != ITS_SUCCESS)
    {
        printf("Send RestoreDataArg failed with error %d.\n", ret);
        c = getch();
        return 0;
    }
    printf("Press any key to continue...\n");
    c = getch();

	arg2 = calloc(1, sizeof(struct type_GSMMAP_InsertSubscriberDataArg));

    arg2->imsi = calloc( 1, sizeof(struct qbuf) + 5 );
    arg2->imsi->qb_len = 5;
    arg2->imsi->qb_data = arg2->imsi->qb_base;
    memcpy( arg2->imsi->qb_data, MIN, 5 );
    arg2->imsi->qb_forw = arg2->imsi;
    arg2->imsi->qb_back = arg2->imsi;

    arg2->odb__Data = calloc(1, sizeof(struct element_GSMMAP_70));

    /*
     * To fill in a parameter which is a BIT STRING, first construct the bit string to 
     * be sent, then call the following function, where the second parameter gives the 
     * maximum number of bits that are valid in the bit string.
     */
    AAV = 0x80;
    arg2->odb__Data->odb__GeneralDataArg = strb2bitstr(&AAV, 3, PE_CLASS_UNIV, PE_PRIM_BITS);

    /*
     * The ITS_HDR only needs the dialogue ID to be filled in.
     */
    hdr.context.dialogue_id = dialogue_id++;
    printf("\nEncode and Send InsertSubscriberDataArg Invoke.\n");
    ret = GSMMAP_SendInsertSubscriberDataArg( handle, &hdr, &cpt, (void *)arg2 );
    if (ret != ITS_SUCCESS)
    {
        printf("Send InsertSubscriberDataArg failed with error %d.\n", ret);
        c = getch();
        return 0;
    }
    printf("Press any key to continue...\n");
    c = getch();
}

/*
 * For test purposes, the following function just decodes the message to be
 * sent, instead of putting the parameter set into the TCAP component and
 * passing it on to the SCCP layer.
 */
int
TCAP_SendComponent(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    void *data;
    int i, ret;
    unsigned char buf[512];
    unsigned char *bitstr;
    struct type_GSMMAP_RestoreDataArg *arg;
    struct type_GSMMAP_InsertSubscriberDataArg *arg2;
    struct qbuf *qbptr;

    memset( buf, 0, 512 );

    printf("\nHex dump of invoke component: 0x");
    for (i = 0; i < cpt->u.invoke.param.len; i++)
    {
        printf("%02x ", cpt->u.invoke.param.data[i]);
    }
    printf("\n\n");

    switch(cpt->u.invoke.operation.data[2])
    {
        case(GSMMAP_OP_insertSubscriberData):
        {
            printf("DECODE InsertSubscriberDataArg\n");

            ret = GSMMAP_DecodeInsertSubscriberDataArg( handle, cpt, &data );
            if (ret != ITS_SUCCESS)
            {
                printf("Decode InsertSubscriberDataArg failed with error %d.\n", ret);
                i = getch();
                return -65;
            }
            arg2 = (struct type_GSMMAP_InsertSubscriberDataArg *)data;

            /* char   *bitstr2strb (pe, k) */
            (char *)bitstr = bitstr2strb(arg2->odb__Data->odb__GeneralDataArg, &i);
            printf("bitstr = 0x%02x, bits used %d.\n", *bitstr, i);
            free_GSMMAP_InsertSubscriberDataArg(data);
        }
        break;

        case(GSMMAP_OP_restoreData):
        {
            printf("DECODE RestoreDataArg\n");

            ret = GSMMAP_DecodeRestoreDataArg( handle, cpt, &data );
            if (ret != ITS_SUCCESS)
            {
                printf("Decode RestoreDataArg failed with error %d.\n", ret);
                i = getch();
                return -65;
            }
            arg = (struct type_GSMMAP_RestoreDataArg *)data;
            printf("Got IMSI with len %d: ", arg->imsi->qb_len);
            qbptr = FollowQBuffer( arg->imsi );
            if (qbptr != NULL)
            {
                for (i = 0; i < arg->imsi->qb_len; i++)
                {
                    printf("0x%02x ", qbptr->qb_data[i]);
                }
                printf("\n");
            }
            printf("Got LMSI with len %d: ", arg->lmsi->qb_len);
            qbptr = FollowQBuffer( arg->lmsi );
            if (qbptr != NULL)
            {
                for (i = 0; i < arg->lmsi->qb_len; i++)
                {
                    printf("0x%02x ", qbptr->qb_data[i]);
                }
                printf("\n");
            }
            free_GSMMAP_RestoreDataArg(data);
        }
        break;

        default:
            break;
    }
    
    return 0;
}

/*
 * This function is needed when decoding messages where parameters are 
 * qbuf structs. Usage is as shown above.
 */
struct qbuf *
FollowQBuffer(struct qbuf *arg)
{
    struct qbuf *ptr = arg;

    while ( ptr && (!ptr->qb_data) ) 
    {
        ptr = ptr->qb_forw;
    }

    if ( ptr && ptr->qb_data ) 
    {
        return ptr;
    } 
    else 
    {
        return (struct qbuf *)NULL;
    }
}
