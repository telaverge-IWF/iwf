/*********************************-*-C-*-************************************
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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 *     FILE: event.c                                                        *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: tcap.c,v 9.1 2005/03/23 12:56:16 cvsadmin Exp $
 *
 * LOG: $Log: tcap.c,v $
 * LOG: Revision 9.1  2005/03/23 12:56:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/05 16:38:26  mmiers
 * LOG: Clean up for chinese TCAP
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:05  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.6  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 5.3  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 20:35:48  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2001/02/13 23:06:38  mmiers
 * LOG: Correct a load of signatures.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:10:54  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/08/02 14:53:08  hxing
 * LOG:
 * LOG: fhasle: fixed bug in SCCP_SendUserInService, cleaned up SSN State Ind.
 * LOG:
 * LOG: Revision 2.5  2000/07/25 20:00:34  hxing
 * LOG:
 * LOG:
 * LOG: Sanitize the source.  Get layer builds working for all 4 parts.
 * LOG:
 * LOG: Revision 2.4  2000/05/24 18:45:24  fhasle
 * LOG:
 * LOG: Added GTT for ANSI, fixed GTT Ind. for ITU (TCAP and SCCP).
 * LOG:
 * LOG: Revision 2.3  2000/01/29 00:10:46  rsonak
 * LOG:
 * LOG: Added externs for MTP3 and SCCP management callback managers
 * LOG:
 * LOG: Revision 2.2  2000/01/28 00:47:07  rsonak
 * LOG:
 * LOG: Commit the PR2 patch. Added MTPS Pause and Resume callbacks for the STANDALONE
 * LOG: and INTEGRATED cases
 * LOG:
 * LOG: Revision 1.65.2.2  2000/01/27 23:16:50  rsonak
 * LOG:
 * LOG: Added MTP3 Pause and Resumes for the INTEGRATED and STANDALONE modes
 * LOG:
 * LOG: Revision 2.1  1999/12/17 21:31:53  rsonak
 * LOG: Fix problems with mixed stack config.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:33:19  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.65  1999/11/06 00:03:01  mmiers
 * LOG:
 * LOG:
 * LOG: Do it right.
 * LOG:
 * LOG: Revision 1.64  1999/11/01 17:12:41  cbascon
 * LOG:
 * LOG:
 * LOG: Make note of several inconsistencies in the library.  Things need
 * LOG: to be updated to the "new" vendor format.
 * LOG:
 * LOG: Revision 1.63  1999/10/07 17:43:50  mmiers
 * LOG:
 * LOG:
 * LOG: Try to bring some sanity to the build process.
 * LOG:
 * LOG: Revision 1.62  1999/09/24 19:36:38  ite
 * LOG:
 * LOG: fhasle: fixed several bugs in ITU TCAP
 * LOG:
 * LOG: Revision 1.61  1999/08/25 22:03:46  mmiers
 * LOG:
 * LOG:
 * LOG: Minor formatting change.
 * LOG:
 * LOG: Revision 1.60  1999/08/25 22:03:09  mmiers
 * LOG:
 * LOG:
 * LOG: Add sanity check calls in.
 * LOG:
 * LOG: Revision 1.59  1999/08/10 15:08:57  ite
 * LOG:
 * LOG: fhasle: fixed several bugs for ITU: Problem was not set correctly when
 * LOG:         sending/receiving TC_Reject. Same with TC_U_ERROR and error code.
 * LOG:         In addition src of TC_Reject was not checked when receiving, thus
 * LOG:         app was getting TC_R_Reject only.
 * LOG:         Did some cleaning also.
 * LOG:
 * LOG: Revision 1.58  1999/08/06 21:13:06  ite
 * LOG:
 * LOG: fhasle: updated missing case statement User_abort when receiving a dialog.
 * LOG:        Joe also fixed some problems regarding GTT.
 * LOG:
 * LOG: Revision 1.57  1999/06/22 20:07:07  ite
 * LOG:
 * LOG:
 * LOG: Change size of abort_reason field.
 * LOG:
 * LOG: Revision 1.56  1999/06/21 22:28:16  ite
 * LOG:
 * LOG: Don't invert the logic.  Duh.
 * LOG:
 * LOG: Revision 1.55  1999/06/21 22:22:23  ite
 * LOG:
 * LOG:
 * LOG: Make sure all code is aware of integrated vs. standalone.
 * LOG:
 * LOG: Revision 1.54  1999/03/12 21:25:46  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitized build.
 * LOG:
 * LOG: Revision 1.53  1999/03/11 20:17:14  fhasle
 * LOG: replace INVOKE_TAG by TCPPN_INVOKE_TAG and

 * LOG: LOCAL_OP_TAG by TCPPN_LOCAL_OP_TAG
 * LOG:
 * LOG: Revision 1.52  1999/01/27 17:59:56  mmiers
 * LOG:
 * LOG:
 * LOG: Add support for separate specifictation of OPC/DPC in TCAP.
 * LOG:
 * LOG: Revision 1.51  1998/12/02 22:07:50  jpakrasi
 * LOG: Merge in mods from the testing for Nokia.
 * LOG:
 * LOG: Revision 1.50  1998/11/12 18:34:33  mmiers
 * LOG: Get ANSI building again.
 * LOG:
 * LOG: Revision 1.49  1998/11/09 16:53:15  mmiers
 * LOG: Fix decomposition bug (semantic error with array).
 * LOG:
 * LOG: Revision 1.48  1998/10/26 23:54:16  mmiers
 * LOG: Rework so that we can integrate with our SCCP and TCAP.
 * LOG:
 * LOG: Revision 1.47  1998/10/16 15:38:45  ite
 * LOG: Corrections from preliminary testing of ac_name.
 * LOG:
 * LOG: Revision 1.46  1998/10/16 14:42:00  mmiers
 * LOG: Update to match current header definitions.
 * LOG:
 * LOG: Revision 1.45  1998/10/15 23:07:03  jpakrasi
 * LOG: Work in ac_name for ITU92 TCAP.
 * LOG:
 * LOG: Revision 1.44  1998/10/05 16:40:24  jpakrasi
 * LOG: Includes GTT for ITU, with latest NMS headers & binaries. Needs some
 * LOG: testing.
 * LOG:
 * LOG: Revision 1.43  1998/09/15 21:42:25  jpakrasi
 * LOG: Formatting of the SCCP_ADDR for ANSI is changed from { flags, pc, ssn }
 * LOG: to { flags, ssn, pc }. For ITU, the format remains as before ie,
 * LOG: { flags, pc, ssn }. The 'pc' param is 3 octets in ANSI, 2 in ITU.
 * LOG:
 * LOG: Revision 1.42  1998/09/15 00:04:41  whu
 * LOG: Change for proper ANSI formatting.
 * LOG:
 * LOG: Revision 1.41  1998/09/09 23:54:41  ite
 * LOG: Bug fix to ITU tcap for prearranged end.
 * LOG:
 * LOG: Revision 1.40  1998/09/04 19:03:43  jpakrasi
 * LOG: Minor mods to compile with latest IntelliSS7 libraries (CCITT ver).
 * LOG:
 * LOG: Revision 1.39  1998/08/06 21:27:24  ite
 * LOG: Forgot that TCAP needs a HANDLE, NOT SS7_HANDLE.
 * LOG:
 * LOG: Revision 1.38  1998/08/06 20:26:58  ite
 * LOG: List buffering free() bug.
 * LOG:
 * LOG: Revision 1.37  1998/08/06 17:25:29  ite
 * LOG: Typo fix.
 * LOG:
 * LOG: Revision 1.36  1998/08/06 17:23:17  ite
 * LOG: More cleanup for new infrastructure.
 * LOG:
 * LOG: Revision 1.35  1998/08/02 19:58:16  jpakrasi
 * LOG: Modified return type for TCAP_Terminate() to int from void to match
 * LOG: latest tcap.h. Added extern int declarations for nms_debug & nms_errno
 * LOG: to remove compiler errors/warnings (already declared in event.c).
 * LOG:
 * LOG: Revision 1.34  1998/06/17 20:46:37  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.33  1998/05/19 14:03:02  mmiers
 * LOG: Cover modifications made to TCAP.
 * LOG:
 * LOG: Revision 1.32  1998/04/09 17:17:21  mmiers
 * LOG: Fix new memory leak.
 * LOG:
 * LOG: Revision 1.31  1998/04/06 22:47:44  mmiers
 * LOG: event.c, tcap.c: Change over to use the new support library in IntelliSS7
 * LOG:
 * LOG: queue.c, queue.h: These are no longer relevant due to the above change.
 * LOG:
 * LOG: Revision 1.30  1998/04/06 15:46:11  ite
 * LOG: commit bug fix for ITE.
 * LOG:
 * LOG: Revision 1.29  1998/04/03 16:41:13  ite
 * LOG: Commit changes only present on the ITE machine.
 * LOG:
 * LOG: Revision 1.28  1998/04/02 19:52:42  mmiers
 * LOG: Gotta handle long form length in BOTH directions (send and receive).
 * LOG:
 * LOG: Revision 1.27  1998/04/02 19:26:45  mmiers
 * LOG: Pay attention to termination value (BASIC or PREARRANGED).
 * LOG:
 * LOG: Revision 1.26  1998/03/13 15:42:18  mmiers
 * LOG: Fix possible memory leak where NMS routine failed but we still had a buffer.
 * LOG:
 * LOG: Revision 1.25  1998/02/26 15:45:59  mmiers
 * LOG: Modifications to bring NMS signatures in line with everyone else.  INI files
 * LOG: are now read for the initial parameters (sapid, srcInst, boardNum, etc).
 * LOG:
 * LOG: Revision 1.24  1998/02/25 00:04:40  ite
 * LOG: Fix reject and error component coding.  Use identifiers as specified in
 * LOG: tcap.h.
 * LOG:
 * LOG: Revision 1.23  1998/02/24 17:34:13  ite
 * LOG: Finish off the response bug.
 * LOG:
 * LOG: Revision 1.22  1998/02/24 17:16:51  ite
 * LOG: Debugging the response problem.  The error code must be formed correctly or
 * LOG: NMS will not send it.  NOTE: NMS will NOT tell the sender that it couldn't
 * LOG: send the message -- it just happily eats the message without any indication.
 * LOG:
 * LOG: Revision 1.21  1998/02/20 17:41:07  mmiers
 * LOG: Add more debug info.
 * LOG:
 * LOG: Revision 1.20  1998/02/20 17:29:29  mmiers
 * LOG: Add debug for did's.
 * LOG:
 * LOG: Revision 1.19  1998/02/19 17:53:04  mmiers
 * LOG: Make sure it compiles on NT.
 * LOG:
 * LOG: Revision 1.18  1998/02/19 17:47:47  mmiers
 * LOG: Update to get proper handling of did.
 * LOG:
 * LOG: Revision 1.17  1998/02/13 21:57:14  mmiers
 * LOG: CONV, not QUERY in SendTCAPDialogue
 * LOG:
 * LOG: Revision 1.16  1998/02/13 17:22:20  mmiers
 * LOG: Move invoke id into correlation id for NMS (RET_ERR and REJECT).
 * LOG:
 * LOG: Revision 1.15  1998/02/12 17:57:26  mmiers
 * LOG: Add passing the error code and problem codes to the user.
 * LOG:
 * LOG: Revision 1.14  1998/02/11 19:24:37  mmiers
 * LOG: small printf for debugging
 * LOG:
 * LOG: Revision 1.13  1998/02/11 15:22:18  mmiers
 * LOG: Update for new function signatures.
 * LOG:
 * LOG: Revision 1.12  1998/02/06 15:37:51  ite
 * LOG: Build after modifying its headers.
 * LOG:
 * LOG: Revision 1.11  1998/02/06 15:00:22  mmiers
 * LOG: Include sccp.h
 * LOG:
 * LOG: Revision 1.10  1998/02/06 14:14:53  mmiers
 * LOG: Change ITS_INAP to ITS_TCAP.
 * LOG:
 * LOG: Revision 1.9  1998/02/06 01:02:39  ite
 * LOG: Various Modifications (for ITE).
 * LOG:
 * LOG: Revision 1.8  1998/02/05 15:47:20  mmiers
 * LOG: Don't use the context in SendTCAPComponent (all necessary information is in
 * LOG: the component anyway).
 * LOG:
 * LOG: Revision 1.7  1998/02/04 18:51:04  ite
 * LOG: Debug for TCAP test applications
 * LOG:
 * LOG: Revision 1.6  1998/02/03 02:11:25  ite
 * LOG: Debug of NMS baseline.
 * LOG:
 * LOG: Revision 1.5  1998/01/28 02:01:51  rsonak
 * LOG: Forgot to complete ANSI build (Mitch).  Cleanup to reflect this.
 * LOG:
 * LOG: Revision 1.4  1998/01/27 23:34:06  mmiers
 * LOG: Finish up the port.
 * LOG:
 * LOG: Revision 1.3  1998/01/27 15:41:43  mmiers
 * LOG: NMS baseline for ITS
 * LOG:
 * LOG: Revision 1.2  1998/01/26 04:42:28  mmiers
 * LOG: Basic cleanup for NMS usage.  Need to add queue handling for correctness.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <its_intern.h>

#if defined(INCLUDE_TCAP)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <its_mlist.h>
#include <its_ss7_trans.h>

#include <windows.h>
#include <winbase.h>
#include <io.h>
#include <fcntl.h>

#include <sys/types.h>

/*
 * this value must be large enough to contain the entire range of
 * possible dialogue ids.
 */
#define MAX_TCAP_DLGS     0x0000FFFF

/*
 * NMS doesn't do any association for incoming and outgoing TIDs.
 * We have to do it ourselves.
 */
static U32 its_spDlgIds[MAX_TCAP_DLGS];

/*
 * this should be pulled from elsewhere
 */
#define SEQ_TAG               0x30U
#define PARAM_SET_IDENT    0xF2U

extern int nms_debug;
extern int nms_errno;

/*
 * this needs to be rethought.
 *
 * Right now, incoming dialogue id's consist of the lower
 * fifteen bits of the spDlgId, and bit 16 is set.
 *
 * Outgoing dialogue id's must be in the range of 0 to 0x7fff.
 */
#define DLG_DIR_BIT     (1 << 15)
#define DLG_ID_MASK     (0x7FFFU)

#define    IPCmsg_t    void

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      A Function to dump data in hex+ascii format
 *
 *  Input Parameters:
 *      Buf - data to show
 *      ByteCnt - #Bytes in Buf
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
dumpMsg(unsigned char *Buf, unsigned short ByteCnt)
{
    unsigned short Li, LMax, ToDo, Bi, Ai;
    char Ascii[80];
    unsigned char B;

    /* Dump to std out in hex followed by ascii */

    for (ToDo = ByteCnt, Bi = 0; ToDo > 0; ToDo -= LMax)
    {
        LMax = (ToDo > 16) ? 16 : ToDo;            /* max bytes this line */
        printf("%04X| ", Bi);
        Ai = 0;

        for (Li = 0; Li < LMax; Li++)              /* each byte this line */
        {
            B = *Buf++;                           /* next byte to show */
            printf("%02X ", B);                    /* as hex */
            if (!isprint(B))                      /* printable ascii? */
                B = '.';                           /* no, use this */
            Ascii[Ai++] = B;                      /* into ascii portiob */
        }    /* for Li */

        for (Li = LMax; Li < 16; Li++)             /* pad short ln if necessary */
            printf("   ");                         /* so asci lines up */

        Ascii[Ai] = 0;                             /* terminate the ascii */
        printf("    ");
        printf("%s\n", Ascii);                     /* show the ascii */
        Bi += LMax;
    }    /* for ToDo */

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert a char array into an integer by shifting.
 *
 *  Input Parameters:
 *      buf - array to convert
 *      len - length of array
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      converted value
 *
 ****************************************************************************/
static unsigned int
BufToId(ITS_OCTET *buf, int len)
{
    int i;
    unsigned int ret = 0;

    if (len > sizeof(unsigned int))
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        ret <<= 8;
        ret |= buf[i];
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert an int into an array of chars
 *
 *  Input Parameters:
 *      id - int to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      buf - converted int
 *      len - byte count in buf
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
static void
IdToBuf(unsigned int id, ITS_OCTET *buf, int *len)
{
    int i, f_nonz = 0;

    *len = 0;
    for (i = 0; i < sizeof(unsigned int); i++)
    {
        unsigned int tmp = (id >> (8 * (sizeof(unsigned int) - i - 1))) &
                            0xFFU;

        if (tmp == 0 && !f_nonz)
        {
            continue;
        }

        f_nonz = 1;
        buf[*len] = tmp;
        *len++;
    }

    if (*len == 0)
    {
        buf[0] = 0;
        *len = 1;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert between our addr and theirs
 *
 *  Input Parameters:
 *      naddr - their addr
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - our addr
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
DecodeSccpAddr(SCCP_ADDR *addr, TcapSpAddr *naddr)
{
    int index = 0;

    if (naddr->presInd == NOT_PRESENT)
    {
        addr->len = 0;

        return;
    }

    addr->data[0] = 0;
    addr->len = 1;

#ifdef DEBUG

    printf("\nAddress received from NMS stack:\n");
    printf("\tnaddr->presInd = %d\n", naddr->presInd);
    printf("\tnaddr->pointCodeInd = %d\n", naddr->pointCodeInd);
    printf("\tnaddr->pointCode = 0x%08x\n", naddr->pointCode);
    printf("\tnaddr->subsystemInd = %d\n", naddr->subsystemInd);
    printf("\tnaddr->subsystem = %d\n", naddr->subsystem);
    printf("\tnaddr->routingInd = %d\n", naddr->routingInd);
    printf("\tnaddr->natIntInd =  %d\n", naddr->natIntInd) ;

    printf("\tnaddr->glTitleInd = %d\n", naddr->glTitleInd);
    if (naddr->glTitleInd != GLT_NONE)
    {
        printf("\tnaddr->glTransType = %d\n", naddr->glTransType);
        printf("\tnaddr->encoding = %d\n", naddr->encoding);
        printf("\tnaddr->numPlan =  %d\n", naddr->numPlan);
        printf("\tnaddr->natAddrInd = %d\n", naddr->natAddrInd);
        printf("\tnaddr->glTitleLen = %d\n", naddr->glTitleLen);
        if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
        {
            printf("\tnaddr->glTitle = 0x");
            for (index = 0; index < naddr->glTitleLen; index++)
            {
                printf("%02x ", naddr->glTitle[index]);
            }
            printf("\n");
            index = 0;
        }
    }
#endif

#if defined(USE_ITU_SCCP)
    if (naddr->pointCodeInd == PTCODE_INC)
    {
        addr->data[0] |= SCCP_CPA_HAS_PC;
        SCCP_ITU_SET_PC(&addr->data[1], naddr->pointCode);
        addr->len += 2;
    }

    if (naddr->subsystemInd == SUBSYS_INC)
    {
        addr->data[0] |= SCCP_CPA_HAS_SSN;
        SCCP_SET_SSN(&addr->data[addr->len], naddr->subsystem);
        addr->len++;
    }

    if (naddr->routingInd == ROUTE_PC_SN)
    {
        addr->data[0] |= SCCP_CPA_ROUTE_SSN;
    }

    if (naddr->natIntInd == ADDRIND_INT)
    {
        addr->data[0] |= SCCP_CPA_ROUTE_INT;
    }

    index = addr->len;

    switch (naddr->glTitleInd)
    {
    case GLT_NONE:
        break;

    /* ITU only - Global title includes encoding and nature of address */
    /* only */
    case GLT_ITU_FMT1:
        addr->data[0] |= SCCP_CPA_GTTI_NATURE;

        if (naddr->encoding == ENC_BCD_ODD)
        {
            addr->data[index] |= 0x80U;
        }
        addr->data[index++] |= (naddr->natAddrInd & 0xEFU);
        addr->len++;
        if (naddr->glTitleLen > 0)
        {
            memcpy(&addr->data[index], naddr->glTitle, naddr->glTitleLen);
            addr->len += naddr->glTitleLen;
        }
        break;

    /* ITU only - Global title includes translation type only */
    case GLT_ITU_FMT2:
        addr->data[0] |= SCCP_CPA_GTTI_TRANS;

        addr->data[index++] = naddr->glTransType;
        addr->len++;
        if (naddr->glTitleLen > 0)
        {
            memcpy(&addr->data[index], naddr->glTitle, naddr->glTitleLen);
            addr->len += naddr->glTitleLen;
        }
        break;

    /* ITU only - Global title includes translation type, numbering plan */
    /*  & encoding */
    case GLT_ITU_FMT3:
        addr->data[0] |= SCCP_CPA_GTTI_TNE;

        addr->data[index++] = naddr->glTransType;
        addr->len++;
        addr->data[index] |= ((naddr->numPlan << 4) & 0xF0U);
        addr->data[index++] |= (naddr->encoding & 0x0FU);
        addr->len++;
        if (naddr->glTitleLen > 0)
        {
            memcpy(&addr->data[index], naddr->glTitle, naddr->glTitleLen);
            addr->len += naddr->glTitleLen;
        }
        break;

    /* ITU only - Global title includes translation type, numbering plan,*/
    /* encoding, and nature of address  */
    case GLT_ITU_FMT4:
        addr->data[0] |= SCCP_CPA_GTTI_ALL;

        addr->data[index++] = naddr->glTransType;
        addr->len++;
        addr->data[index] |= ((naddr->numPlan << 4) & 0xF0U);
        addr->data[index++] |= (naddr->encoding & 0x0FU);
        addr->len++;
        if (naddr->encoding == ENC_BCD_ODD)
        {
            addr->data[index] |= 0x80U;
        }
        addr->data[index++] |= (naddr->natAddrInd & 0xEFU);
        addr->len++;
        if (naddr->glTitleLen > 0)
        {
            memcpy(&addr->data[index], naddr->glTitle, naddr->glTitleLen);
            addr->len += naddr->glTitleLen;
        }
        break;
    }

#elif defined(USE_ANSI_SCCP)
    if (naddr->pointCodeInd == PTCODE_INC)
    {
        addr->data[0] |= SCCP_CPA_HAS_PC;
        SCCP_ANSI_SET_PC(&addr->data[1], naddr->pointCode);
        addr->len += 3;
    }

    if (naddr->subsystemInd == SUBSYS_INC)
    {
        addr->data[0] |= SCCP_CPA_HAS_SSN;
        SCCP_SET_SSN(&addr->data[addr->len], naddr->subsystem);
        addr->len++;
    }

    if (naddr->routingInd == ROUTE_PC_SN)
    {
        addr->data[0] |= SCCP_CPA_ROUTE_SSN;
    }

    if (naddr->natIntInd == ADDRIND_INT)
    {
        addr->data[0] |= SCCP_CPA_ROUTE_INT;
    }

    index = addr->len;
    
    switch (naddr->glTitleInd)
    {
    case GLT_NONE:
        break;

    /* ANSI only - Global title includes translation type only */
    case GLT_TT:
        addr->data[0] |= SCCP_CPA_GTTI_TRANS;

        addr->data[index++] = naddr->glTransType;
        addr->len++;
        if (naddr->glTitleLen > 0)
        {
            memcpy(&addr->data[index], naddr->glTitle, naddr->glTitleLen);
            addr->len += naddr->glTitleLen;
        }
        break;

    /* ANSI only - Global title includes translation type, numbering plan */
    /*  & encoding */
    case GLT_TT_NP_E:
        addr->data[0] |= SCCP_CPA_GTTI_TNE;

        addr->data[index++] = naddr->glTransType;
        addr->len++;
        addr->data[index] |= ((naddr->numPlan << 4) & 0xF0U);
        addr->data[index++] |= (naddr->encoding & 0x0FU);
        addr->len++;
        if (naddr->glTitleLen > 0)
        {
            memcpy(&addr->data[index], naddr->glTitle, naddr->glTitleLen);
            addr->len += naddr->glTitleLen;
        }
        break;    
    }
#endif

#ifdef DEBUG
    printf("\nSCCP_ADDR (len %d) encoded from NMS struct: 0x", addr->len);
    for (index = 0; index < addr->len; index++)
    {
        printf("%02x ", addr->data[index]);
    }
    printf("\n");
#endif

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert between our addr and theirs
 *
 *  Input Parameters:
 *      addr - our addr;
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      naddr - their addr
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
BuildSccpAddr(SCCP_ADDR *addr, TcapSpAddr *naddr)
{
    ITS_OCTET *pc = NULL, *ssn = NULL, *gtti = NULL;
    int g = 0;

#if defined(USE_ITU_SCCP)
    naddr->swType  = SW_ITU;
    if (addr->len > 0)
    {
        naddr->presInd = PRESENT;

        if (addr->data[0] & SCCP_CPA_HAS_PC)
        {
            naddr->pointCodeInd = PTCODE_INC;
            naddr->pointCode = SCCP_ITU_GET_PC(&addr->data[1]);
            pc = &addr->data[1];
        }
        else
        {
            naddr->pointCodeInd = PTCODE_NONE;
            naddr->pointCode = 0;
        }

        if (addr->data[0] & SCCP_CPA_HAS_SSN)
        {
            naddr->subsystemInd = SUBSYS_INC;
            if (pc)
            {
                naddr->subsystem = addr->data[3];
                ssn = &addr->data[3];
            }
            else
            {
                naddr->subsystem = addr->data[1];
                ssn = &addr->data[1];
            }
        }
        else
        {
            naddr->subsystemInd = SUBSYS_NONE;
            naddr->subsystem =   0;
        }

        if (addr->data[0] & SCCP_CPA_ROUTE_SSN)
        {
            naddr->routingInd =  ROUTE_PC_SN;
        }
        else
        {
            naddr->routingInd =  ROUTE_GLT;
        }

        if (addr->data[0] & SCCP_CPA_ROUTE_INT)
        {
            naddr->natIntInd =   ADDRIND_INT;
        }
        else
        {
            naddr->natIntInd =   ADDRIND_NAT;
        }

        /*
         * Set up the index to begin extracting the GTT info.
         */
        g = 1; /* first byte contains the address indicator */
        if (pc && ssn)
        {
            g += 3; /* 2 for pc + 1 for ssn */
        }
        else if (pc && !ssn)
        {
            g += 2; /* 2 for pc only */
        }
        else if (ssn && !pc)
        {
            g += 1; /* 1 for ssn only */
        }

        switch (addr->data[0] & SCCP_CPA_GTTI_MASK)
        {
        case SCCP_CPA_GTTI_NONE:
            naddr->glTitleInd =  GLT_NONE;
            naddr->glTransType = 0;
            naddr->encoding = ENC_UNKNOWN;
            naddr->numPlan =  NP_UNK;
            naddr->natAddrInd = 0;
            naddr->glTitleLen = 0;
            break;

        /* ITU only - Global title includes encoding and nature of address */
        /* only */
        case SCCP_CPA_GTTI_NATURE:
            naddr->glTitleInd =  GLT_ITU_FMT1;
            naddr->glTransType = 0;
            if (addr->data[g] & 0x80U)
            {
                naddr->encoding = ENC_BCD_ODD;
            }
            else
            {
                naddr->encoding = ENC_BCD_EVEN;
            }
            naddr->numPlan =  NP_UNK;
            naddr->natAddrInd = addr->data[g++] & 0xEFU;
            naddr->glTitleLen = addr->len - g;
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
            {
                memcpy(naddr->glTitle, &addr->data[g], naddr->glTitleLen);
            }
            break;

        /* ITU only - Global title includes translation type only */
        case SCCP_CPA_GTTI_TRANS:
            naddr->glTitleInd =  GLT_ITU_FMT2;
            naddr->glTransType = addr->data[g++];
            naddr->encoding = ENC_UNKNOWN;
            naddr->numPlan =  NP_UNK;
            naddr->natAddrInd = 0;
            naddr->glTitleLen = addr->len - g;
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
            {
                memcpy(naddr->glTitle, &addr->data[g], naddr->glTitleLen);
            }
            break;
        
        /* ITU only - Global title includes translation type, numbering plan */
        /*  & encoding */
        case SCCP_CPA_GTTI_TNE:
            naddr->glTitleInd = GLT_ITU_FMT3;
            naddr->glTransType = addr->data[g++];
            naddr->encoding = addr->data[g] & 0x0FU;
            naddr->numPlan = (addr->data[g++] >> 4) & 0x0FU;
            naddr->natAddrInd = 0;
            naddr->glTitleLen = addr->len - g;
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
            {
                memcpy(naddr->glTitle, &addr->data[g], naddr->glTitleLen);
            }
            break;

        /* ITU only - Global title includes translation type, numbering plan,*/
        /* encoding, and nature of address  */
        case SCCP_CPA_GTTI_ALL:
            naddr->glTitleInd =  GLT_ITU_FMT4;
            naddr->glTransType = addr->data[g++];
            naddr->encoding = addr->data[g] & 0x0FU;
            naddr->numPlan =  (addr->data[g++] >> 4) & 0x0FU;
            naddr->natAddrInd = addr->data[g++] & 0xEFU;
            naddr->glTitleLen = addr->len - g;
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
            {
                memcpy(naddr->glTitle, &addr->data[g], naddr->glTitleLen);
            }
            break;
        }
    }
    else
    {
        naddr->presInd = NOT_PRESENT;
        naddr->pointCodeInd = PTCODE_NONE;
        naddr->pointCode = 0;
        naddr->subsystemInd = SUBSYS_NONE;
        naddr->subsystem =   0;
        naddr->routingInd =  ROUTE_GLT;
        naddr->natIntInd =   ADDRIND_NAT;

        naddr->glTitleInd =  GLT_NONE;
        naddr->glTransType = 0;
        naddr->encoding = ENC_UNKNOWN;
        naddr->numPlan =  NP_UNK;
        naddr->natAddrInd = NATIND_SUBS;
        naddr->glTitleLen = 0;
    }

#elif defined(USE_ANSI_SCCP)
    naddr->swType  = SW_ANSI;
    if (addr->len > 0)
    {
        naddr->presInd = PRESENT;

        if (addr->data[0] & SCCP_CPA_HAS_PC)
        {
            naddr->pointCodeInd = PTCODE_INC;
            naddr->pointCode = SCCP_ANSI_GET_PC(&addr->data[2]);
            pc = &addr->data[2];
        }
        else
        {
            naddr->pointCodeInd = PTCODE_NONE;
            naddr->pointCode = 0;
        }

        if (addr->data[0] & SCCP_CPA_HAS_SSN)
        {
            naddr->subsystemInd = SUBSYS_INC;
            if (pc)
            {
                naddr->subsystem = addr->data[1];
                ssn = &addr->data[1];
            }
            else
            {
                naddr->subsystem = addr->data[1];
                ssn = &addr->data[1];
            }
        }
        else
        {
            naddr->subsystemInd = SUBSYS_NONE;
            naddr->subsystem =   0;
        }

        if (addr->data[0] & SCCP_CPA_ROUTE_SSN)
        {
            naddr->routingInd =  ROUTE_PC_SN;
        }
        else
        {
            naddr->routingInd =  ROUTE_GLT;
        }

        if (addr->data[0] & SCCP_CPA_ROUTE_NAT)
        {
            naddr->natIntInd =   ADDRIND_NAT;
        }
        else
        {
            naddr->natIntInd =   ADDRIND_INT;
        }

        /*
         * Set up the index to begin extracting the GTT info.
         */
        g = 1; /* first byte contains the address indicator */
        if (pc && ssn)
        {
            g += 4; /* 3 for pc + 1 for ssn */
        }
        else if (pc && !ssn)
        {
            g += 3; /* 3 for pc only */
        }
        else if (ssn && !pc)
        {
            g += 1; /* 1 for ssn only */
        }

        switch (addr->data[0] & SCCP_CPA_GTTI_MASK)
        {
        case SCCP_CPA_GTTI_NONE:
            naddr->glTitleInd =  GLT_NONE;
            naddr->glTransType = 0;
            naddr->encoding = ENC_UNKNOWN;
            naddr->numPlan =  NP_UNK;
            naddr->natAddrInd = NATIND_SUBS;
            naddr->glTitleLen = 0;
            break;

        case SCCP_CPA_GTTI_TRANS:
            naddr->glTitleInd =  GLT_TT;
            naddr->glTransType = addr->data[g++];
            naddr->encoding = ENC_UNKNOWN;
            naddr->numPlan =  NP_UNK;
            naddr->natAddrInd = 0;
            naddr->glTitleLen = addr->len - g;
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
            {
                memcpy(naddr->glTitle, &addr->data[g], naddr->glTitleLen);
            }                        
            break;

        case SCCP_CPA_GTTI_TNE:
            naddr->glTitleInd =  GLT_TT_NP_E;
            naddr->glTransType = addr->data[g++];
            naddr->encoding = addr->data[g] & 0x0FU;
            naddr->numPlan = (addr->data[g++] >> 4) & 0x0FU;
            naddr->natAddrInd = 0;
            naddr->glTitleLen = addr->len - g;
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
            {
                memcpy(naddr->glTitle, &addr->data[g], naddr->glTitleLen);
            }
            break;
        }
    }
    else
    {
        naddr->presInd = NOT_PRESENT;
        naddr->pointCodeInd = PTCODE_NONE;
        naddr->pointCode = 0;
        naddr->subsystemInd = SUBSYS_NONE;
        naddr->subsystem =   0;
        naddr->routingInd =  ROUTE_GLT;
        naddr->natIntInd =   ADDRIND_NAT;

        naddr->glTitleInd =  GLT_NONE;
        naddr->glTransType = 0;
        naddr->encoding = ENC_UNKNOWN;
        naddr->numPlan =  NP_UNK;
        naddr->natAddrInd = NATIND_SUBS;
        naddr->glTitleLen = 0;
    }
#endif

#ifdef DEBUG

    printf("\n");
    printf("\nAddress coded for NMS stack:\n");
    printf("\tnaddr->presInd = %d\n", naddr->presInd);
    printf("\tnaddr->pointCodeInd = %d\n", naddr->pointCodeInd);
    printf("\tnaddr->pointCode = 0x%08x\n", naddr->pointCode);
    printf("\tnaddr->subsystemInd = %d\n", naddr->subsystemInd);
    printf("\tnaddr->subsystem = %d\n", naddr->subsystem);
    printf("\tnaddr->routingInd = %d\n", naddr->routingInd);
    printf("\tnaddr->natIntInd =  %d\n", naddr->natIntInd) ;

    printf("\tnaddr->glTitleInd = %d\n", naddr->glTitleInd);
    if (naddr->glTitleInd != GLT_NONE)
    {
        printf("\tnaddr->glTransType = %d\n", naddr->glTransType);
        printf("\tnaddr->encoding = %d\n", naddr->encoding);
        printf("\tnaddr->numPlan =  %d\n", naddr->numPlan);
        printf("\tnaddr->natAddrInd = %d\n", naddr->natAddrInd);
        printf("\tnaddr->glTitleLen = %d\n", naddr->glTitleLen);
        if (naddr->glTitleLen > 0 && naddr->glTitleLen < TCAP_MAX_GLT_SZ)
        {
            printf("\tnaddr->glTitle = 0x");
            for (g = 0; g < naddr->glTitleLen; g++)
            {
                printf("%02x ", naddr->glTitle[g]);
            }
            printf("\n");
        }
    }
#endif
}


/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
void
NMSBuildSCCPCoordEvent(ITS_SS7_CONTEXT *context, int isInd,
                       TcapCoordEvent *coord, ITS_EVENT *ev)
{
    ITS_SCCP_IE ies[4];
    ITS_HDR hdr;
    int offset = 0;

#ifdef NOT_YET
    hdr.type = ITS_SCCP;
    hdr.context.ssn = context->ssn[0]; /* FIXME: Should come from addr */

    /* protocol class */
    ies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies[0].param_length = sizeof(SCCP_PROT_CLASS);
    ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* called party addr */
    ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[1].param_length = sizeof(SCCP_ADDR);
    ies[1].param_data.calledPartyAddr.data[0] = SCCP_CPA_HAS_PC|
                                                SCCP_CPA_HAS_SSN|
                                                SCCP_CPA_ROUTE_SSN;
#if defined(CCITT)
    SCCP_ITU_SET_PC(&ies[1].param_data.calledPartyAddr.data[1],
                    context->dpc);
    offset = 3;
#elif defined(ANSI)
    SCCP_ANSI_SET_PC(&ies[1].param_data.calledPartyAddr.data[1],
                     context->dpc);
    offset = 4;
#endif
    SCCP_SET_SSN(&ies[1].param_data.calledPartyAddr.data[offset],
                 SCCP_SSN_SCCPMGMT);
    offset++;
    ies[1].param_data.calledPartyAddr.len = offset;

    /* calling party addr */
    ies[2].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[2].param_length = sizeof(SCCP_ADDR);
    ies[2].param_data.callingPartyAddr.data[0] = SCCP_CPA_HAS_PC|
                                                  SCCP_CPA_HAS_SSN|
                                                  SCCP_CPA_ROUTE_SSN;
#if defined(CCITT)
    SCCP_ITU_SET_PC(&ies[2].param_data.callingPartyAddr.data[1],
                    context->dpc);
    offset = 3;
#elif defined(ANSI)
    SCCP_ANSI_SET_PC(&ies[2].param_data.callingPartyAddr.data[1],
                     context->opc);
    offset = 4;
#endif
    SCCP_SET_SSN(&ies[2].param_data.callingPartyAddr.data[offset],
                 SCCP_SSN_SCCPMGMT);
    offset++;
    ies[2].param_data.calledPartyAddr.len = offset;

    ies[3].param_id = SCCP_PRM_DATA;
    ies[3].param_length = sizeof(SCCP_SCMG);
#if defined(ANSI)
    ies[3].param_data.managementMessageANSI.type = SCCP_SCMG_SS_OOS_GRANT;
    ies[3].param_data.managementMessageANSI.ssn = coord->aSsn;
#elif defined(CCITT)
    ies[3].param_data.managementMessageCCITT.type = SCCP_SCMG_SS_OOS_GRANT;
    ies[3].param_data.managementMessageCCITT.ssn = coord->aSsn;
#endif
    MTP3_PC_SET_VALUE(ies[0].param_data.managementMessage.pointCode,
                      context->dpc);

    ies[3].param_data.managementMessage.multiplicity = coord->smi;

    SCCP_Encode(ies, 4, SCCP_MSG_UDT, ev, &hdr, &SCCP_UDT_Desc);
#else

    ies[0].param_id = SCCP_PRM_DATA;
    ies[0].param_length = sizeof(SCCP_SCMG);
#if defined(ANSI)
    ies[0].param_data.managementMessageANSI.type = SCCP_SCMG_SS_OOS_GRANT;
    ies[0].param_data.managementMessageANSI.ssn = coord->aSsn;
    MTP3_PC_SET_VALUE(ies[0].param_data.managementMessageANSI.pointCode,
                      context->dpc);

    ies[0].param_data.managementMessageANSI.multiplicity = coord->smi;
#elif defined(CCITT)
    ies[0].param_data.managementMessageCCITT.type = SCCP_SCMG_SS_OOS_GRANT;
    ies[0].param_data.managementMessageCCITT.ssn = coord->aSsn;
    MTP3_PC_SET_VALUE(ies[0].param_data.managementMessageCCITT.pointCode,
                      context->dpc);

    ies[0].param_data.managementMessageCCITT.multiplicity = coord->smi;
#endif

    SCCP_Encode(ies, 4, SCCP_MSG_UDT, ev, &hdr, &SCCP_UDT_Desc);
#endif
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
void
NMSBuildSCCPSSCEvent(ITS_SS7_CONTEXT *context,
                     TcapSsnStateEvent *state, ITS_EVENT *ev)
{
    ITS_SCCP_IE ies[4];
    ITS_HDR hdr;
    int offset = 0;

#ifdef NOT_YET
    hdr.type = ITS_SCCP;
    hdr.context.ssn = context->ssn[0]; /* FIXME: Should come from addr */

    /* protocol class */
    ies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies[0].param_length = sizeof(SCCP_PROT_CLASS);
    ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

    /* called party addr */
    ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[1].param_length = sizeof(SCCP_ADDR);
    ies[1].param_data.calledPartyAddr.data[0] = SCCP_CPA_HAS_PC|
                                                SCCP_CPA_HAS_SSN|
                                                SCCP_CPA_ROUTE_SSN;
#if defined(CCITT)
    SCCP_ITU_SET_PC(&ies[1].param_data.calledPartyAddr.data[1],
                    context->dpc);
    offset = 3;
#elif defined(ANSI)
    SCCP_ANSI_SET_PC(&ies[1].param_data.calledPartyAddr.data[1],
                     context->dpc);
    offset = 4;
#endif
    SCCP_SET_SSN(&ies[1].param_data.calledPartyAddr.data[offset],
                 SCCP_SSN_SCCPMGMT);
    offset++;
    ies[1].param_data.calledPartyAddr.len = offset;

    /* calling party addr */
    ies[2].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[2].param_length = sizeof(SCCP_ADDR);
    ies[2].param_data.callingPartyAddr.data[0] = SCCP_CPA_HAS_PC|
                                                  SCCP_CPA_HAS_SSN|
                                                  SCCP_CPA_ROUTE_SSN;
#if defined(CCITT)
    SCCP_ITU_SET_PC(&ies[2].param_data.callingPartyAddr.data[1],
                    context->dpc);
    offset = 3;
#elif defined(ANSI)
    SCCP_ANSI_SET_PC(&ies[2].param_data.callingPartyAddr.data[1],
                     context->opc);
    offset = 4;
#endif
    SCCP_SET_SSN(&ies[2].param_data.callingPartyAddr.data[offset],
                 SCCP_SSN_SCCPMGMT);
    offset++;
    ies[2].param_data.calledPartyAddr.len = offset;

    ies[3].param_id = SCCP_PRM_DATA;
    ies[3].param_length = sizeof(SCCP_SCMG);

    if (state->status == SS_OOS)
    {
        ies[3].param_data.managementMessage.type = SCCP_SCMG_SS_PROHIBIT;
    }
    else
    {
        ies[3].param_data.managementMessage.type = SCCP_SCMG_SS_ALLOWED;
    }
    ies[3].param_data.managementMessage.ssn = state->aSsn;

    MTP3_PC_SET_VALUE(ies[0].param_data.managementMessage.pointCode,
                      context->dpc);

    ies[3].param_data.managementMessage.multiplicity = state->smi;

    SCCP_Encode(ies, 4, SCCP_MSG_UDT, ev, &hdr, &SCCP_UDT_Desc);
#else

    ies[0].param_id = SCCP_PRM_DATA;
    ies[0].param_length = sizeof(SCCP_SCMG);

#if defined(ANSI)
    if (state->status == SS_OOS)
    {
        ies[0].param_data.managementMessageANSI.type = SCCP_SCMG_SS_ALLOWED;
    }
    else
    {
        ies[0].param_data.managementMessageANSI.type = SCCP_SCMG_SS_PROHIBIT;
    }
    ies[0].param_data.managementMessageANSI.ssn = state->aSsn;

    MTP3_PC_SET_VALUE(ies[0].param_data.managementMessageANSI.pointCode,
                      context->dpc);

    ies[0].param_data.managementMessageANSI.multiplicity = state->smi;
#elif defined(CCITT)
    if (state->status == SS_OOS)
    {
        ies[0].param_data.managementMessageCCITT.type = SCCP_SCMG_SS_ALLOWED;
    }
    else
    {
        ies[0].param_data.managementMessageCCITT.type = SCCP_SCMG_SS_PROHIBIT;
    }
    ies[0].param_data.managementMessageCCITT.ssn = state->aSsn;

    MTP3_PC_SET_VALUE(ies[0].param_data.managementMessageCCITT.pointCode,
                      context->dpc);

    ies[0].param_data.managementMessageCCITT.multiplicity = state->smi;
#endif

    SCCP_Encode(ies, 4, SCCP_MSG_UDT, ev, &hdr, &SCCP_UDT_Desc);
#endif
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
void
NMSBuildSCCPReturnEvent(ITS_SS7_CONTEXT *context,
                        TcapNotifEvent *note, ITS_EVENT *ev)
{
    ITS_SCCP_IE ies[4];
    int offset = 0;
    ITS_HDR hdr;

    hdr.type = ITS_SCCP;
    hdr.context.ssn = context->ssn[0]; /* FIXME: Should come from addr */

    /* protocol class */
    ies[0].param_id = SCCP_PRM_RETURN_CAUSE;
    ies[0].param_length = sizeof(SCCP_RET_CAUSE);
    ies[0].param_data.returnCause.cause = note->retcause;

    /* called party addr */
    ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[1].param_length = sizeof(SCCP_ADDR);
    ies[1].param_data.calledPartyAddr.data[0] = SCCP_CPA_HAS_PC|
                                                SCCP_CPA_HAS_SSN|
                                                SCCP_CPA_ROUTE_SSN;
#if defined(CCITT)
    SCCP_ITU_SET_PC(&ies[1].param_data.calledPartyAddr.data[1],
                    context->dpc);
    offset = 3;
#elif defined(ANSI)
    SCCP_ANSI_SET_PC(&ies[1].param_data.calledPartyAddr.data[1],
                     context->dpc);
    offset = 4;
#endif
    SCCP_SET_SSN(&ies[1].param_data.calledPartyAddr.data[offset],
                 SCCP_SSN_SCCPMGMT);
    offset++;
    ies[1].param_data.calledPartyAddr.len = offset;

    /* calling party addr */
    ies[2].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[2].param_length = sizeof(SCCP_ADDR);
    ies[2].param_data.callingPartyAddr.data[0] = SCCP_CPA_HAS_PC|
                                                  SCCP_CPA_HAS_SSN|
                                                  SCCP_CPA_ROUTE_SSN;
#if defined(CCITT)
    SCCP_ITU_SET_PC(&ies[2].param_data.callingPartyAddr.data[1],
                    context->dpc);
    offset = 3;
#elif defined(ANSI)
    SCCP_ANSI_SET_PC(&ies[2].param_data.callingPartyAddr.data[1],
                     context->opc);
    offset = 4;
#endif
    SCCP_SET_SSN(&ies[2].param_data.callingPartyAddr.data[offset],
                 SCCP_SSN_SCCPMGMT);
    offset++;
    ies[2].param_data.calledPartyAddr.len = offset;

    ies[3].param_id = SCCP_PRM_DATA;
    ies[3].param_length = sizeof(SCCP_DATA);
    memcpy(ies[3].param_data.userData.data, &note->transInfo,
           sizeof(TcapTransInfo) <= SCCP_MAX_DATA
            ? sizeof(TcapTransInfo)
            : SCCP_MAX_DATA);

    SCCP_Encode(ies, 4, SCCP_MSG_UDT, ev, &hdr, &SCCP_UDT_Desc);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert their component to ours
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
NMSReceiveComponent(ITS_USHORT dialogue_id, ITS_EVENT *event,
                    TcapComp* comp, U8* pbuf, U16 plen,
                    ITS_BOOLEAN lastComponent)
{
    int i = 0;
    TCAP_CPT cpt;

    if (nms_debug)
    {
        printf("VENDOR:  ENTER RCV CPT\n");
    }

    memset(&cpt, 0, sizeof(TCAP_CPT));

    switch (comp->compType)
    {
#if defined(CCITT)
    case TCAP_INVOKE:
        cpt.ptype = TCPPT_TC_INVOKE;
        cpt.u.invoke.opClass = comp->uProt.ituComp.opClass;
        cpt.u.invoke.timeout = comp->uProt.ituComp.invokeTimer;

        cpt.u.invoke.invoke_id.len = 3;
        cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.invoke.invoke_id.data[1] = 1;
        cpt.u.invoke.invoke_id.data[2] = comp->uProt.ituComp.invokeId.compId;

        if (comp->uProt.ituComp.linkedId.present == PRESENT)
        {
            cpt.u.invoke.linked_id.len = 3;
            cpt.u.invoke.linked_id.data[0] = TCPPN_INVOKE_TAG;
            cpt.u.invoke.linked_id.data[1] = 1;
            cpt.u.invoke.linked_id.data[2] = comp->uProt.ituComp.linkedId.compId;
        }
        else
        {
            cpt.u.invoke.linked_id.len = 0;
        }

        /* Setting the operation Code */
        if (comp->uProt.ituComp.uComp.opcode.opCodeType == TCAP_LOCAL)
        {
            cpt.u.invoke.operation.len = 3;
            cpt.u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt.u.invoke.operation.data[1] = 1;
            cpt.u.invoke.operation.data[2] =
                comp->uProt.ituComp.uComp.opcode.opCode.octStr[0];
        }
        else if (comp->uProt.ituComp.uComp.opcode.opCodeType ==
                 TCAP_GLOBAL)
        {
            cpt.u.invoke.operation.len = 
                comp->uProt.ituComp.uComp.opcode.opCode.length + 2;
            cpt.u.invoke.operation.data[0] = TCPPN_GLOBAL_OP_TAG;
            cpt.u.invoke.operation.data[1] = 
                (ITS_OCTET)comp->uProt.ituComp.uComp.opcode.opCode.length;

            memcpy(&cpt.u.invoke.operation.data[2],
                   comp->uProt.ituComp.uComp.opcode.opCode.octStr,
                   comp->uProt.ituComp.uComp.opcode.opCode.length);
        }

        cpt.u.invoke.param.len = plen;
        memcpy(cpt.u.invoke.param.data, pbuf, plen);

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }
        break;

    case TCAP_RET_RES_L:
    case TCAP_RET_RES_NL:
        if (comp->compType == TCAP_RET_RES_L)
        {
            cpt.ptype = TCPPT_TC_RESULT_L;
        }
        else
        {
            cpt.ptype = TCPPT_TC_RESULT_NL;
        }

        cpt.u.result.invoke_id.len = 3;
        cpt.u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.result.invoke_id.data[1] = 1;
        cpt.u.result.invoke_id.data[2] = comp->uProt.ituComp.invokeId.compId;

        /* Setting the operation Code */
        if (comp->uProt.ituComp.uComp.opcode.opCodeType == TCAP_LOCAL)
        {
            cpt.u.result.operation.len = 3;
            cpt.u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt.u.result.operation.data[1] = 1;
            cpt.u.result.operation.data[2] =
                comp->uProt.ituComp.uComp.opcode.opCode.octStr[0];
        }
        else if (comp->uProt.ituComp.uComp.opcode.opCodeType == TCAP_GLOBAL)
        {
            cpt.u.result.operation.len = 
                comp->uProt.ituComp.uComp.opcode.opCode.length + 2;
            cpt.u.result.operation.data[0] = TCPPN_GLOBAL_OP_TAG;
            cpt.u.result.operation.data[1] = 
                (ITS_OCTET)comp->uProt.ituComp.uComp.opcode.opCode.length;

            memcpy(&cpt.u.result.operation.data[2],
                   comp->uProt.ituComp.uComp.opcode.opCode.octStr,
                   comp->uProt.ituComp.uComp.opcode.opCode.length);
        }

        cpt.u.result.param.len = plen;
        memcpy(cpt.u.result.param.data, pbuf, plen);

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;
    
    case TCAP_RET_ERR:
        cpt.ptype = TCPPT_TC_U_ERROR;

        cpt.u.error.invoke_id.len = 3;
        cpt.u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.error.invoke_id.data[1] = 1;
        cpt.u.error.invoke_id.data[2] = comp->uProt.ituComp.invokeId.compId;

        if (comp->uProt.ituComp.uComp.errcode.errCodeId == TCAP_LOCAL)
        {
            cpt.u.error.error.data[0]= TCPPN_LOCAL_ERR_TAG;        
            /* len of error tag */
            cpt.u.error.error.data[1] = 1;
            /* total len to include Error code tag and len. */
            cpt.u.error.error.len = 3;
            cpt.u.error.error.data[2] = 
                comp->uProt.ituComp.uComp.errcode.errCode.octStr[0];
        }
        else
        {
            cpt.u.error.error.data[0] = TCPPN_GLOBAL_ERR_TAG;
            cpt.u.error.error.data[1] = (ITS_OCTET)
                comp->uProt.ituComp.uComp.errcode.errCode.length;
            /* +2 to include Error code tag and len. */
            cpt.u.error.error.len = cpt.u.error.error.data[1] + 2;

            memcpy(&cpt.u.error.error.data[2],
                   comp->uProt.ituComp.uComp.errcode.errCode.octStr,
                   cpt.u.error.error.data[1]);
        }

        cpt.u.error.param.len = plen;
        memcpy(cpt.u.error.param.data, pbuf, plen);

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_REJECT:
        /* Source of the Reject tell us if it is Local, Remote or User */
        switch (comp->rejSrc)
        {
        case TCAP_COMP_REJ_USR:
            cpt.ptype = TCPPT_TC_U_REJECT;
            break;
        case TCAP_COMP_REJ_LOCAL:
            cpt.ptype = TCPPT_TC_L_REJECT;
            break;
        case TCAP_COMP_REJ_REMOTE:
            cpt.ptype = TCPPT_TC_R_REJECT;
            break;
        }
        
        cpt.u.reject.invoke_id.len = 3;
        cpt.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.reject.invoke_id.data[1] = 1;
        cpt.u.reject.invoke_id.data[2] = comp->uProt.ituComp.invokeId.compId;

        switch (comp->uProt.ituComp.uComp.prbcode.probType)
        {
        case TCAP_PROB_NONE:
            /* Is it possible ? */
            break;

        case TCAP_PROB_GENERAL:
        case TCAP_PROB_INVOKE:
        case TCAP_PROB_RET_RES:
        case TCAP_PROB_RET_ERR:

            /* high bit is set for NMS Reject family */
            cpt.u.reject.problem.data[0] = 
                (comp->uProt.ituComp.uComp.prbcode.probType - 0x80);

            if (comp->uProt.ituComp.uComp.prbcode.prbCode.length == 1)
            {
                /* length */
                cpt.u.reject.problem.data[1] = 1;
                /* Problem code (identical between NMS and ITS*/
                cpt.u.reject.problem.data[2] =                     
                    comp->uProt.ituComp.uComp.prbcode.prbCode.octStr[0];
                cpt.u.reject.problem.len = 3;
            }
            else
            {
                cpt.u.reject.problem.data[1] = (ITS_OCTET)
                    comp->uProt.ituComp.uComp.prbcode.prbCode.length;

                memcpy(&cpt.u.reject.problem.data[2], 
                       comp->uProt.ituComp.uComp.prbcode.prbCode.octStr,
                       cpt.u.reject.problem.data[1]);

                /* +2 to include family and length of problem. */
                cpt.u.reject.problem.len = cpt.u.reject.problem.data[1] + 2;
            }
            break;

        default:
            /* This should not happen */
            break;
        }

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_CANCEL:
        /* Src of Cancel can only be Local. */
        cpt.ptype = TCPPT_TC_L_CANCEL;

        cpt.u.cancel.invoke_id.len = 3;
        cpt.u.cancel.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.cancel.invoke_id.data[1] = 1;
        cpt.u.cancel.invoke_id.data[2] = comp->uProt.ituComp.invokeId.compId;

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

#elif defined(ANSI)

    case TCAP_INVOKE_L:
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: INVOKE_L: did: %04x\n",
                   dialogue_id);
        }
        cpt.ptype = TCPPT_TC_INVOKE;
        cpt.u.invoke.timeout = comp->uProt.ansiComp.invokeTimer;

        cpt.u.invoke.invoke_id.len = 3;
        cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.invoke.invoke_id.data[1] = 1;
        cpt.u.invoke.invoke_id.data[2] = comp->uProt.ansiComp.invokeId.compId;

        if (comp->uProt.ansiComp.corrId.present == PRESENT)
        {
            cpt.u.invoke.linked_id.len = 3;
            cpt.u.invoke.linked_id.data[0] = TCPPN_INVOKE_TAG;
            cpt.u.invoke.linked_id.data[1] = 1;
            cpt.u.invoke.linked_id.data[2] = comp->uProt.ansiComp.corrId.compId;
        }
        else
        {
            cpt.u.invoke.linked_id.len = 0;
        }

        cpt.u.invoke.operation.len = 4;
        if (comp->uProt.ansiComp.uComp.opcode.opCodeId == TCAP_PRIVATE)
        {
            cpt.u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
        }
        else
        {
            cpt.u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        }

        cpt.u.invoke.operation.data[1] = 2;
        cpt.u.invoke.operation.data[2] =
            comp->uProt.ansiComp.uComp.opcode.opFamily;
        cpt.u.invoke.operation.data[3] =
            comp->uProt.ansiComp.uComp.opcode.opSpec;

        cpt.u.invoke.param.data[0] = PARAM_SET_IDENT;
        if (plen < 128)
        {
            cpt.u.invoke.param.len = plen + 2;
            cpt.u.invoke.param.data[1] = (ITS_OCTET)plen;
            memcpy(cpt.u.invoke.param.data + 2, pbuf, plen);
        }
        else
        {
            cpt.u.invoke.param.len = plen + 3;
            cpt.u.invoke.param.data[1] = 0x81;
            cpt.u.invoke.param.data[2] = (ITS_OCTET)plen;
            memcpy(cpt.u.invoke.param.data + 3, pbuf, plen);
        }

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_INVOKE_NL:
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: INVOKE_NL: did: %04x\n",
                   dialogue_id);
        }
        cpt.ptype = TCPPT_TC_INVOKE_NL;
        cpt.u.invoke.timeout = comp->uProt.ansiComp.invokeTimer;

        cpt.u.invoke.invoke_id.len = 3;
        cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.invoke.invoke_id.data[1] = 1;
        cpt.u.invoke.invoke_id.data[2] = comp->uProt.ansiComp.invokeId.compId;

        if (comp->uProt.ansiComp.corrId.present == PRESENT)
        {
            cpt.u.invoke.linked_id.len = 3;
            cpt.u.invoke.linked_id.data[0] = TCPPN_INVOKE_TAG;
            cpt.u.invoke.linked_id.data[1] = 1;
            cpt.u.invoke.linked_id.data[2] = comp->uProt.ansiComp.corrId.compId;
        }
        else
        {
            cpt.u.invoke.linked_id.len = 0;
        }

        cpt.u.invoke.operation.len = 4;
        if (comp->uProt.ansiComp.uComp.opcode.opCodeId == TCAP_PRIVATE)
        {
            cpt.u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
        }
        else
        {
            cpt.u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        }

        cpt.u.invoke.operation.data[1] = 2;
        cpt.u.invoke.operation.data[2] =
            comp->uProt.ansiComp.uComp.opcode.opFamily;
        cpt.u.invoke.operation.data[3] =
            comp->uProt.ansiComp.uComp.opcode.opSpec;

        cpt.u.invoke.param.data[0] = PARAM_SET_IDENT;
        if (plen < 128)
        {
            cpt.u.invoke.param.len = plen + 2;
            cpt.u.invoke.param.data[1] = (ITS_OCTET)plen;
            memcpy(cpt.u.invoke.param.data + 2, pbuf, plen);
        }
        else
        {
            cpt.u.invoke.param.len = plen + 3;
            cpt.u.invoke.param.data[1] = 0x81;
            cpt.u.invoke.param.data[2] = (ITS_OCTET)plen;
            memcpy(cpt.u.invoke.param.data + 3, pbuf, plen);
        }

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_RET_RES_L:
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: RESULT_L: did: %04x\n",
                   dialogue_id);
        }
        cpt.ptype = TCPPT_TC_RESULT_L;

        cpt.u.result.invoke_id.len = 3;
        cpt.u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.result.invoke_id.data[1] = 1;
        cpt.u.result.invoke_id.data[2] = comp->uProt.ansiComp.corrId.compId;

        cpt.u.result.param.data[0] = PARAM_SET_IDENT;
        if (plen < 128)
        {
            cpt.u.result.param.len = plen + 2;
            cpt.u.result.param.data[1] = (ITS_OCTET)plen;
            memcpy(cpt.u.result.param.data + 2, pbuf, plen);
        }
        else
        {
            cpt.u.result.param.len = plen + 3;
            cpt.u.result.param.data[1] = 0x81;
            cpt.u.result.param.data[2] = (ITS_OCTET)plen;
            memcpy(cpt.u.invoke.param.data + 3, pbuf, plen);
        }

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_RET_RES_NL:
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: RESULT_NL: did: %04x\n",
                   dialogue_id);
        }
        cpt.ptype = TCPPT_TC_RESULT_NL;

        cpt.u.result.invoke_id.len = 3;
        cpt.u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.result.invoke_id.data[1] = 1;
        cpt.u.result.invoke_id.data[2] = comp->uProt.ansiComp.corrId.compId;

        cpt.u.result.param.data[0] = PARAM_SET_IDENT;
        if (plen < 128)
        {
            cpt.u.result.param.len = plen + 2;
            cpt.u.result.param.data[1] = (ITS_OCTET)plen;
            memcpy(cpt.u.result.param.data + 2, pbuf, plen);
        }
        else
        {
            cpt.u.result.param.len = plen + 3;
            cpt.u.result.param.data[1] = 0x81;
            cpt.u.result.param.data[2] = (ITS_OCTET)plen;
            memcpy(cpt.u.invoke.param.data + 3, pbuf, plen);
        }

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_RET_ERR:
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: ERROR: did: %04x\n",
                   dialogue_id);
        }
        cpt.ptype = TCPPT_TC_ERROR;

        cpt.u.error.invoke_id.len = 3;
        cpt.u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.error.invoke_id.data[1] = 1;
        cpt.u.error.invoke_id.data[2] = comp->uProt.ansiComp.invokeId.compId;

        cpt.u.error.error.len = 3;
        if (comp->uProt.ansiComp.uComp.errcode.errCodeId == TCAP_NATIONAL)
        {
            cpt.u.error.error.data[0] = TCPPN_ECI_NATIONAL_TCAP;
        }
        else
        {
            cpt.u.error.error.data[0] = TCPPN_ECI_PRIVATE_TCAP;
        }
        cpt.u.error.error.data[1] = 2;
        cpt.u.error.error.data[2] =
            comp->uProt.ansiComp.uComp.errcode.errCode;

        cpt.u.error.param.data[0] = PARAM_SET_IDENT;
        if (plen < 128)
        {
            cpt.u.error.param.len = plen + 2;
            cpt.u.error.param.data[1] = (ITS_OCTET)plen;
            memcpy(cpt.u.error.param.data + 2, pbuf, plen);
        }
        else
        {
            cpt.u.error.param.len = plen + 3;
            cpt.u.error.param.data[1] = 0x81;
            cpt.u.error.param.data[2] = (ITS_OCTET)plen;
            memcpy(cpt.u.error.param.data + 3, pbuf, plen);
        }

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_REJECT:
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: REJECT: did: %04x\n",
                   dialogue_id);
        }
        cpt.ptype = TCPPT_TC_REJECT;

        cpt.u.reject.invoke_id.len = 3;
        cpt.u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.reject.invoke_id.data[1] = 1;
        cpt.u.reject.invoke_id.data[2] = comp->uProt.ansiComp.corrId.compId;

        cpt.u.reject.problem.len = 4;
        cpt.u.reject.problem.data[0] = TCPPROB_IDENT;
        cpt.u.reject.problem.data[1] = 2;
        cpt.u.reject.problem.data[2] =
            comp->uProt.ansiComp.uComp.prbcode.probType;
        cpt.u.reject.problem.data[3] =
            comp->uProt.ansiComp.uComp.prbcode.probSpec;

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

    case TCAP_CANCEL:
    if (nms_debug)
    {
        printf("VENDOR: INBOUND: CANCEL: did: %04x\n",
               dialogue_id);
    }
        cpt.ptype = TCPPT_TC_CANCEL;

        cpt.u.cancel.invoke_id.len = 3;
        cpt.u.cancel.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.cancel.invoke_id.data[1] = 1;
        cpt.u.cancel.invoke_id.data[2] = comp->uProt.ansiComp.invokeId.compId;

        if (lastComponent)
        {
            cpt.last_component = TCAP_LAST_CPT;
        }
        else
        {
            cpt.last_component = TCAP_MORE_CPTS;
        }

        break;

#endif

    case TCAP_UNKNOWN:
        break;

    default:
        break;
    }

    if (TCAP_VendorComponentSanityCheck(&cpt) != ITS_SUCCESS)
    {
        if (nms_debug)
        {
            printf("VENDOR: Component from stack failed sanity check\n");
        }

        return (ITS_BADTCAPMESSAGE);
    }

    event->len = sizeof(TCAP_CPT);
    event->src = ITS_TCAP_SRC;
    event->data[0] = ITS_TCAP_CPT;
    event->data[1] = (ITS_OCTET)((dialogue_id >> 8) & 0xFFU);
    event->data[2] = (ITS_OCTET)(dialogue_id & 0xFFU);

    memcpy(&event->data[3], &cpt, sizeof(TCAP_CPT));

    nms_errno = ITS_SUCCESS;

    if (nms_debug)
    {
        printf("VENDOR:  EXIT RCV CPT\n");
    }

    return nms_errno;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert their dialogue to ours
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
NMSReceiveDialogue(ITS_USHORT dialogue_id, ITS_EVENT *event,
                   TcapRecvInfo* tRecv)
{
    TcapTransEvent* tEvent;
    TcapTransInfo* tInfo;
    TcapDlgSect* tSect;
    TCAP_DLG dlg;
    DLG_BEGIN *beg;
    DLG_END *end;
    DLG_UNI *uni;
    DLG_CONTINUE *cont;
    DLG_ABORT *abort;

    if (nms_debug)
    {
        printf("VENDOR:  ENTER RCV DLG\n");
    }

    tEvent = &tRecv->event.data;
    tInfo = &tEvent->transInfo;
    tSect = &tEvent->dlgPart;

    memset(&dlg, 0, sizeof(TCAP_DLG));

    switch (tInfo->msgType)
    {
    case TCAP_UNI:
        dlg.ptype = TCPPT_TC_UNI;
        uni = &dlg.u.uni;

        /* load transaction info */
        if (tInfo->qos.priority > 0)
        {
            uni->qos.indicator |= QOSI_PRIORITY;
            uni->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            uni->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            uni->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            if (tSect->apConName.length > 0)
            {
                uni->ac_name.len = tSect->apConName.length + 2;
                uni->ac_name.data[0] = 0x06;
                uni->ac_name.data[1] = (ITS_OCTET)tSect->apConName.length;
                memcpy(&uni->ac_name.data[2], tSect->apConName.octStr,
                       uni->ac_name.len);
            }
        }
        else
        {
            uni->ac_name.len = 0;
        }

        uni->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(uni->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        DecodeSccpAddr(&uni->dest_addr, &tInfo->cdAddr);
        DecodeSccpAddr(&uni->orig_addr, &tInfo->cgAddr);

        if (tInfo->cdAddr.presInd == PRESENT &&
            tInfo->cdAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(uni->dpc, tInfo->cdAddr.pointCode);
        }
        if (tInfo->cgAddr.presInd == PRESENT &&
            tInfo->cgAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(uni->opc, tInfo->cgAddr.pointCode);
        }

        uni->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

#if defined(CCITT)
    case TCAP_BEGIN:
        dlg.ptype = TCPPT_TC_BEGIN;
        beg = &dlg.u.begin;

        /* load transaction info */
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: BEGIN: SP-DLG: %08x SU-DLG: %08x\n",
                   tInfo->spDlgId, tInfo->suDlgId);
        }
        if (tInfo->qos.priority > 0)
        {
            beg->qos.indicator |= QOSI_PRIORITY;
            beg->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            beg->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            beg->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {            
            if (tSect->apConName.length > 0)
            {
                beg->ac_name.len = tSect->apConName.length + 2;
                beg->ac_name.data[0] = 0x06;
                beg->ac_name.data[1] = (ITS_OCTET)tSect->apConName.length;
                memcpy(&beg->ac_name.data[2], tSect->apConName.octStr,
                       beg->ac_name.len);
            }
        }
        else
        {
            beg->ac_name.len = 0;
        }

        beg->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(beg->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        DecodeSccpAddr(&beg->dest_addr, &tInfo->cdAddr);
        DecodeSccpAddr(&beg->orig_addr, &tInfo->cgAddr);

        if (tInfo->cdAddr.presInd == PRESENT &&
            tInfo->cdAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(beg->dpc, tInfo->cdAddr.pointCode);
        }
        if (tInfo->cgAddr.presInd == PRESENT &&
            tInfo->cgAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(beg->opc, tInfo->cgAddr.pointCode);
        }

        beg->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

    case TCAP_CONTINUE:
        dlg.ptype = TCPPT_TC_CONTINUE;
        cont = &dlg.u.cont;

        /* load transaction info */
        if (tInfo->qos.priority > 0)
        {
            cont->qos.indicator |= QOSI_PRIORITY;
            cont->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            cont->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            cont->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            if (tSect->apConName.length > 0)
            {
                cont->ac_name.len = tSect->apConName.length + 2;
                cont->ac_name.data[0] = 0x06;
                cont->ac_name.data[1] = (ITS_OCTET)tSect->apConName.length;
                memcpy(&cont->ac_name.data[2], tSect->apConName.octStr,
                       cont->ac_name.len);
            }
        }
        else
        {
            cont->ac_name.len = 0;
        }

        cont->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(cont->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        DecodeSccpAddr(&cont->orig_addr, &tInfo->cgAddr);

        if (tInfo->cgAddr.presInd == PRESENT &&
            tInfo->cgAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(cont->opc, tInfo->cgAddr.pointCode);
        }

        cont->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

    case TCAP_END:
        dlg.ptype = TCPPT_TC_END;
        end = &dlg.u.end;

        /* load transaction info */
        if (tInfo->qos.priority > 0)
        {
            end->qos.indicator |= QOSI_PRIORITY;
            end->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            end->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            end->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            if (tSect->apConName.length > 0)
            {
                end->ac_name.len = tSect->apConName.length + 2;
                end->ac_name.data[0] = 0x06;
                end->ac_name.data[1] = (ITS_OCTET)tSect->apConName.length;
                memcpy(&end->ac_name.data[2], tSect->apConName.octStr,
                       end->ac_name.len);
            }
        }
        else
        {
            end->ac_name.len = 0;
        }

        end->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(end->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        end->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

    case TCAP_P_ABORT:
        dlg.ptype = TCPPT_TC_P_ABORT;
        abort = &dlg.u.abort;

        /* load transaction info */
        if (tInfo->qos.priority > 0)
        {
            abort->qos.indicator |= QOSI_PRIORITY;
            abort->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            abort->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            abort->qos.indicator |= QOSI_SEQ_CTRL;
        }

        abort->abort_reason = tInfo->abortCause;
        break;

    case TCAP_U_ABORT:
        dlg.ptype = TCPPT_TC_U_ABORT;
        abort = &dlg.u.abort;

        /* load transaction info */
        if (tInfo->qos.priority > 0)
        {
            abort->qos.indicator |= QOSI_PRIORITY;
            abort->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            abort->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            abort->qos.indicator |= QOSI_SEQ_CTRL;
        }

        abort->abort_reason = tInfo->abortCause;

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            if (tSect->apConName.length > 0)
            {
                abort->ac_name.len = tSect->apConName.length + 2;
                abort->ac_name.data[0] = 0x06;
                abort->ac_name.data[1] = (ITS_OCTET)tSect->apConName.length;
                memcpy(&abort->ac_name.data[2], tSect->apConName.octStr,
                       abort->ac_name.len);
            }
        }
        else
        {
            abort->ac_name.len = 0;
        }

        abort->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(abort->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        break;

#elif defined(ANSI)

    case TCAP_ANSI_UNI:
        dlg.ptype = TCPPT_TC_UNI;
        uni = &dlg.u.uni;

        /* load transaction info */
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: UNI: SP-DLG: %08x SU-DLG: %08x %04x\n",
                   tInfo->spDlgId, tInfo->suDlgId, dialogue_id);
        }

        if (tInfo->qos.priority > 0)
        {
            uni->qos.indicator |= QOSI_PRIORITY;
            uni->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            uni->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            uni->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            uni->ac_name.len = tSect->apConName.length;
            if (tSect->apConName.length > 0)
            {
                memcpy(uni->ac_name.data, tSect->apConName.octStr,
                       uni->ac_name.len);
            }
        }
        else
        {
            uni->ac_name.len = 0;
        }

        uni->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(uni->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        DecodeSccpAddr(&uni->dest_addr, &tInfo->cdAddr);
        DecodeSccpAddr(&uni->orig_addr, &tInfo->cgAddr);

        if (tInfo->cdAddr.presInd == PRESENT &&
            tInfo->cdAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(uni->dpc, tInfo->cdAddr.pointCode);
        }
        if (tInfo->cgAddr.presInd == PRESENT &&
            tInfo->cgAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(uni->opc, tInfo->cgAddr.pointCode);
        }

        uni->cpt_present = (unsigned char)tEvent->numComps;

        break;

    case TCAP_QRY_PRM:
        dlg.ptype = TCPPT_TC_QUERY_W_PERM;
    case TCAP_QRY_NO_PRM:
        if (tInfo->msgType != TCAP_QRY_PRM)
        {
            dlg.ptype = TCPPT_TC_QUERY_WO_PERM;
        }
        beg = &dlg.u.begin;

        /* load transaction info */
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: QUERY: SP-DLG: %08x SU-DLG: %08x DLG: %04x\n",
                   tInfo->spDlgId, tInfo->suDlgId, dialogue_id);
        }

        if (tInfo->qos.priority > 0)
        {
            beg->qos.indicator |= QOSI_PRIORITY;
            beg->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            beg->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            beg->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            beg->ac_name.len = tSect->apConName.length;
            if (tSect->apConName.length > 0)
            {
                memcpy(beg->ac_name.data, tSect->apConName.octStr,
                       beg->ac_name.len);
            }
        }
        else
        {
            beg->ac_name.len = 0;
        }

        beg->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(beg->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        DecodeSccpAddr(&beg->dest_addr, &tInfo->cdAddr);
        DecodeSccpAddr(&beg->orig_addr, &tInfo->cgAddr);

        if (tInfo->cdAddr.presInd == PRESENT &&
            tInfo->cdAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(beg->dpc, tInfo->cdAddr.pointCode);
        }
        if (tInfo->cgAddr.presInd == PRESENT &&
            tInfo->cgAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(beg->opc, tInfo->cgAddr.pointCode);
        }

        beg->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

    case TCAP_CNV_PRM:
        dlg.ptype = TCPPT_TC_CONV_W_PERM;
    case TCAP_CNV_NO_PRM:
        if (tInfo->msgType != TCAP_CNV_PRM)
        {
            dlg.ptype = TCPPT_TC_CONV_WO_PERM;
        }
        cont = &dlg.u.cont;

        /* load transaction info */
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: CONV: SP-DLG: %08x SU-DLG: %08x DLG: %04x\n",
                   tInfo->spDlgId, tInfo->suDlgId, dialogue_id);
        }

        if (tInfo->qos.priority > 0)
        {
            cont->qos.indicator |= QOSI_PRIORITY;
            cont->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            cont->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            cont->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            cont->ac_name.len = tSect->apConName.length;
            if (tSect->apConName.length > 0)
            {
                memcpy(cont->ac_name.data, tSect->apConName.octStr,
                       cont->ac_name.len);
            }
        }
        else
        {
            cont->ac_name.len = 0;
        }

        cont->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(cont->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        DecodeSccpAddr(&cont->orig_addr, &tInfo->cgAddr);

        if (tInfo->cgAddr.presInd == PRESENT &&
            tInfo->cgAddr.pointCodeInd == PTCODE_INC)
        {
            MTP3_PC_SET_VALUE(cont->opc, tInfo->cgAddr.pointCode);
        }

        cont->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

    case TCAP_RESPONSE:
        dlg.ptype = TCPPT_TC_RESP;
        end = &dlg.u.end;

        /* load transaction info */
        if (nms_debug)
        {
            printf("VENDOR: INBOUND: RESP: SP-DLG: %08x SU-DLG: %08x DLG: %04x\n",
                   tInfo->spDlgId, tInfo->suDlgId, dialogue_id);
        }

        if (tInfo->qos.priority > 0)
        {
            end->qos.indicator |= QOSI_PRIORITY;
            end->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            end->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            end->qos.indicator |= QOSI_SEQ_CTRL;
        }

        if (tSect->dlgType != TCAP_DLGP_NONE)
        {
            end->ac_name.len = tSect->apConName.length;
            if (tSect->apConName.length > 0)
            {
                memcpy(end->ac_name.data, tSect->apConName.octStr,
                       end->ac_name.len);
            }
        }
        else
        {
            end->ac_name.len = 0;
        }

        end->user_info.len = tEvent->userInfoLen;
        if (tEvent->userInfoLen > 0)
        {
            memcpy(end->user_info.data, 
                   tEvent->pUserInfo,
                   tEvent->userInfoLen);
        }

        tInfo->preArgEnd = 0;

        end->cpt_present = (ITS_OCTET)tEvent->numComps;

        break;

    case TCAP_ANSI_ABORT:
        abort = &dlg.u.abort;

        /* load transaction info */
        if (tInfo->qos.priority > 0)
        {
            abort->qos.indicator |= QOSI_PRIORITY;
            abort->qos.priority = tInfo->qos.priority;
        }

        if (tInfo->qos.retOpt == MSG_RETURN)
        {
            abort->qos.indicator |= QOSI_RET_OPT;
        }

        if (tInfo->qos.seqDlvy == TCAP_QOS_SEQDEL)
        {
            abort->qos.indicator |= QOSI_SEQ_CTRL;
        }

        abort->abort_reason = tInfo->abortCause;
        break;

#endif

    default:
        break;
    }

    if (TCAP_VendorDialogueSanityCheck(&dlg) != ITS_SUCCESS)
    {
        if (nms_debug)
        {
            printf("VENDOR: Dialogue from stack failed sanity check\n");
        }

        return ITS_BADTCAPMESSAGE;
    }

    event->len = sizeof(TCAP_DLG);
    event->src = ITS_TCAP_SRC;

    event->data[0] = ITS_TCAP_DLG;
    event->data[1] = (ITS_OCTET)((dialogue_id >> 8) & 0xFFU);
    event->data[2] = (ITS_OCTET)(dialogue_id & 0xFFU);

    memcpy(&event->data[3], &dlg, sizeof(TCAP_DLG));

    if (nms_debug)
    {
        printf("VENDOR:  EXIT RCV DLG\n");
    }

    return ITS_SUCCESS;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
static int
RetrieveTransaction(ITS_SS7_HANDLE handl, TcapRecvInfo* infoBlk, U8* Msg)
{
    TcapTransInfo *tInfo;
    TcapComp comp;
    S32 retval;
    U8 index;
    U8 pbuf[512]/*, tMsg[NMS_MSG_SIZE] */;
    U16 plen;
    ITS_EVENT ev;
    ITS_USHORT dialogue_id;
    ITS_SS7_CONTEXT *context;

    context = (ITS_SS7_CONTEXT *)handl;

    if (nms_debug)
    {
        printf("\nData Indication received - from pc = %d.%d.%d\n",
               ((infoBlk->event.data.opc >> 16) & 0xff),
               ((infoBlk->event.data.opc >>  8) & 0xff),
               ((infoBlk->event.data.opc >>  0) & 0xff));
        printf("\nTransInfo, event = %d abort cause = %d\n"
               "suId = %d, spId = %d, cdpc = %d.%d.%d:%d, "
               "cgpc = %d.%d.%d:%d\n",
               infoBlk->event.data.transInfo.msgType, 
               infoBlk->event.data.transInfo.abortCause,
               infoBlk->event.data.transInfo.suDlgId, 
               infoBlk->event.data.transInfo.spDlgId,
               ((infoBlk->event.data.transInfo.cdAddr.pointCode >> 16) &
                0xff),
               ((infoBlk->event.data.transInfo.cdAddr.pointCode >>  8) &
                0xff),
               ((infoBlk->event.data.transInfo.cdAddr.pointCode >>  0) &
                0xff),
               infoBlk->event.data.transInfo.cdAddr.subsystem,
               ((infoBlk->event.data.transInfo.cgAddr.pointCode >> 16) &
                0xff),
               ((infoBlk->event.data.transInfo.cgAddr.pointCode >>  8) &
                0xff),
               ((infoBlk->event.data.transInfo.cgAddr.pointCode >>  0) &
                0xff),
               infoBlk->event.data.transInfo.cgAddr.subsystem);
    }

    /* dump dialog part and user info part */
    if (nms_debug)
    {
        if (infoBlk->event.data.dlgPart.dlgType != TCAP_DLGP_NONE)
        {
             printf("\nDialog Part:\n");
             dumpMsg((char *)&(infoBlk->event.data.dlgPart),
                     sizeof(TcapDlgSect));
        }
        if ( infoBlk->event.data.userInfoLen)
        {
             printf("\nUser Info Part:\n");
             dumpMsg((char *)infoBlk->event.data.pUserInfo,
                     infoBlk->event.data.userInfoLen);
        }
    }

    dialogue_id = 0;
    memset((char *)&comp, 0, sizeof(TcapComp));
    memset((char *)&ev, 0, sizeof(ITS_EVENT));

    tInfo = &infoBlk->event.data.transInfo;
    switch (tInfo->msgType)
    {
#if defined(CCITT)
    case TCAP_UNI:
        dialogue_id =
            (ITS_USHORT)((tInfo->spDlgId & DLG_ID_MASK) | DLG_DIR_BIT);
        its_spDlgIds[dialogue_id] = 0;
        break;

    case TCAP_BEGIN:
        dialogue_id = 
            (ITS_USHORT)((tInfo->spDlgId & DLG_ID_MASK) | DLG_DIR_BIT);
        its_spDlgIds[dialogue_id] = tInfo->spDlgId;
        break;

    case TCAP_CONTINUE:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = tInfo->spDlgId;
        break;

    case TCAP_END:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = 0;
        break;

    case TCAP_P_ABORT:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = 0;
        break;

    case TCAP_U_ABORT:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = 0;
        break;

    /* Local Cancel: Time out */
    case TCAP_LOC_IND:
       dialogue_id = (ITS_USHORT)tInfo->suDlgId;
       its_spDlgIds[dialogue_id] = tInfo->spDlgId;;

       for (index = 0; index < infoBlk->event.data.numComps; index++)
       {
           plen = 512;
           /*memcpy( tMsg, Msg, NMS_MSG_SIZE ); */
           if ((retval = TCAPGetComp(Msg, index,
                                     &comp, &plen, pbuf)) != TCAP_SUCCESS)
           {
               printf("\nTCAPGetComp failed, ret = %d.\n",  retval);
               return(retval);
           }

           if (nms_debug)    
           {
               printf("\nTCAP component:\n");
               dumpMsg((char *)&comp, sizeof(TcapComp));
           }
           /* Is this component the last component ? */
           if (index == (infoBlk->event.data.numComps - 1))
           {
               /* This is the last component */
               NMSReceiveComponent(dialogue_id, &ev, &comp, pbuf, plen, ITS_TRUE);
           }
           else
           {
               /* This is NOT the last component */
               NMSReceiveComponent(dialogue_id, &ev, &comp, pbuf, plen, ITS_FALSE);
           }
           
           MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));    
       }       
       return ITS_SUCCESS;
       break;

#elif defined(ANSI)
    case TCAP_ANSI_UNI:
        dialogue_id =
            (ITS_USHORT)(tInfo->spDlgId & DLG_ID_MASK) | DLG_DIR_BIT;
        its_spDlgIds[dialogue_id] = 0;
        break;

    case TCAP_QRY_PRM:
    case TCAP_QRY_NO_PRM:
        dialogue_id =
            (ITS_USHORT)(tInfo->spDlgId & DLG_ID_MASK) | DLG_DIR_BIT;
        its_spDlgIds[dialogue_id] = tInfo->spDlgId;
        break;

    case TCAP_CNV_PRM:
    case TCAP_CNV_NO_PRM:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = tInfo->spDlgId;
        break;

    case TCAP_RESPONSE:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = 0;
        break;

    case TCAP_ANSI_PABORT:
        dialogue_id = (ITS_USHORT)tInfo->suDlgId;
        its_spDlgIds[dialogue_id] = 0;
        break;
#endif

    default:
        printf("VENDOR: Unknown dialogue component type (%d)\n",
               tInfo->msgType);
        return !ITS_SUCCESS;
    }

    NMSReceiveDialogue(dialogue_id, &ev, infoBlk);

    MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

    /* memcpy( tMsg, Msg, NMS_MSG_SIZE ); */
    for (index = 0; index < infoBlk->event.data.numComps; index++)
    {
        plen = 512;
        memset(&comp, 0, sizeof(TcapComp));
        
        if ((retval = TCAPGetComp(Msg, index,
        /*if ((retval = TCAPGetComp((U8 *)&tMsg, index, */
                                  &comp, &plen, pbuf)) != TCAP_SUCCESS)
        {
            printf("\nTCAPGetComp failed, ret = %d.\n",  retval);
            return(retval);
        }

        /* dump component */
        if (nms_debug)
        {
            printf("\nTCAP component:\n");
            dumpMsg((char *)&comp, sizeof(TcapComp));
        }

        /* dump parameter buffer */
        if (nms_debug)
        {
            printf("\nParameters:\n");
            dumpMsg((char *)pbuf, plen);
        }

        /* Is this component the last component ? */
       if (index == (infoBlk->event.data.numComps - 1))
       {
           /* This is the last component */
           NMSReceiveComponent(dialogue_id, &ev, &comp, pbuf, plen, ITS_TRUE);
       }
       else
       {
           /* This is NOT the last component */
           NMSReceiveComponent(dialogue_id, &ev, &comp, pbuf, plen, ITS_FALSE);
       }
        MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the NMS board interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSInitializeTCAP(ITS_SS7_HANDLE handl)
{
    S16        retval;
    U8         boardNum;
    S16        sapid;
    S16        servUserId;
    U8         ssn;
    U8         srcEnt;
    U8         srcInst;
    ITS_SS7_CONTEXT *context;
    int i;
    
    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;
    sapid = context->sapid;
    servUserId = context->servUserId;
    srcEnt = context->srcEnt;
    srcInst = context->srcInst;

    if ((retval = TCAPInitAPI(boardNum, srcEnt, srcInst)) != TCAP_SUCCESS)
    {
        return (ITS_EBINDFAIL);
    }

    /* get a synchronization handle for this board */
    if ((context->tcapSync = TCAPSyncObj(boardNum, &retval)) == OS_NULL_HSYNC)
    {
        return (ITS_EBINDFAIL);
    }

    /* now bind to the SAP */
    for (i = 0; i < context->maxSubs; i++)
    {
        ssn = context->ssn[i];
        if ((retval = TCAPBindReq(boardNum, servUserId, sapid, ssn)) !=
            TCAP_SUCCESS)
        {
            return (ITS_EBINDFAIL);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the NMS interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSTermTCAP(ITS_SS7_HANDLE handl)
{
    S16     retval;
    U8        boardNum;
    S16        sapid;
    ITS_SS7_CONTEXT *context;

    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;
    sapid = context->sapid;

    CALLBACK_DestroyManager(SCCP_ManagementCallbacks);
    free(SCCP_ManagementCallbacks);
    CALLBACK_DestroyManager(MTP3_ManagementCallbacks);
    free(MTP3_ManagementCallbacks);

    if ((retval = TCAPUnbindReq(boardNum, sapid, 0)) != TCAP_SUCCESS)
    {
        return (retval);
    }

    if ((retval = TCAPTermAPI(boardNum)) != TCAP_SUCCESS)
    {
        return (retval);
    }

    return (TCAP_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSRetrieveTCAPMessage(ITS_SS7_HANDLE handl)
{
    U8 Msg[NMS_MSG_SIZE];
    TcapRecvInfo infoBlk;
    S32 retval = 0;
    ITS_SS7_CONTEXT *context;
    U8 boardNum = 0;
    ITS_EVENT ev;

    MTP3_PAUSE_RESUME pr;
    MTP3_HEADER mtp3;

    SCCP_SCMG stateIndication;

    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;

    memset(Msg, 0, NMS_MSG_SIZE);
    memset((char *)&infoBlk, 0, sizeof(TcapRecvInfo));
    memset((char *)&ev, 0, sizeof(ITS_EVENT));

    /* get TCAP message from API */
    if ((retval = TCAPRetrieveMessage(boardNum, (U8 *)&Msg, &infoBlk)) != TCAP_SUCCESS)
    {
        return (ITS_ENOMSG);
    }

    switch (infoBlk.eventType)
    {
    case TCAP_EVENT_STA_IND:
        /* this is a TCAP error indication  */
        if (nms_debug)
        {
            printf("\nStatus Indication received, status = %d, suId = %d\n",
                    infoBlk.event.status.status,infoBlk.event.status.suId);
        }

        return (ITS_ENOMSG);

    case TCAP_EVENT_COORD_IND:
        /* this is a notification from SCCP of an state change has been made */
        if (nms_debug)
        {
            printf("\nCoordinated Status change, SSN = %d, smi = %d\n", 
                    infoBlk.event.coord.aSsn,infoBlk.event.coord.smi);
        }

        if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
        {
            /* Replace this with a call to the SCCP_ManagementCallbacks */
            NMSBuildSCCPCoordEvent(context, ITS_TRUE, &infoBlk.event.coord, &ev);

            CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                                      NULL,
                                      (ITS_POINTER)&ev);

            return (ITS_SUCCESS);
        }

        return (ITS_ENOMSG);

    case TCAP_EVENT_COORD_CFM:
        /* this is a notification from SCCP that a requested state change
         * is ok with SCCP */
        if (nms_debug)
        {
            printf("\nCoordinated Status change confirm, SSN = %d, smi = %d\n", 
                    infoBlk.event.coord.aSsn,infoBlk.event.coord.smi);
        }

        if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
        {
            /* Replace this with a call to the SCCP_ManagementCallbacks */
            NMSBuildSCCPCoordEvent(context, ITS_FALSE, &infoBlk.event.coord, &ev);

            CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                                      NULL,
                                      (ITS_POINTER)&ev);

            return (ITS_SUCCESS);
        }

        return (ITS_ENOMSG);

    case TCAP_EVENT_SSN_STATE:
        /* this is a notification from SCCP of a SSP or SSA */
        if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
        {
            /* Retrieves the status of the subSystem */
            memset((char *)&stateIndication, 0, sizeof(SCCP_SCMG));

            /* getting SSN */
            stateIndication.ssn = infoBlk.event.ssnstate.aSsn;

        /* Getting affected PC, reserved for future use. */
        MTP3_PC_SET_VALUE(stateIndication.pointCode,
                      infoBlk.event.ssnstate.aPc);
                    
        /* Getting the status */
        if (infoBlk.event.ssnstate.status == SS_IS)
        {
        /* In service */
        stateIndication.type = SCCP_SCMG_SS_ALLOWED;
        }
        else
        {
        if (infoBlk.event.ssnstate.status == SS_OOS)
        {
            /* Out of service */
            stateIndication.type = SCCP_SCMG_SS_PROHIBIT;
        }
        }
       
            /* Create the SCCP Management Callbacks List */
            retval = CALLBACK_CallCallbackList(SCCP_ManagementCallbacks,
                                               (ITS_POINTER)handl,
                                               (ITS_POINTER)&stateIndication);
            if (retval != ITS_SUCCESS)
            {
                printf("\n Failed to call SCCP Callback Manager");

        if (nms_debug)
        {
            printf("\nSubsystem status change, pc = %d.%d.%d:%d, "
                   "smi = %d, status = %d\n",
                   ((infoBlk.event.ssnstate.aPc >> 16) & 0xff),
                   ((infoBlk.event.ssnstate.aPc >>  8) & 0xff),
                   ((infoBlk.event.ssnstate.aPc >>  0) & 0xff),
                   infoBlk.event.ssnstate.aSsn,
                   infoBlk.event.ssnstate.smi,
                   infoBlk.event.ssnstate.status);
        }
            }
        }
        return (ITS_ENOMSG);

    case TCAP_EVENT_PC_STATE:
        if (nms_debug)
        {
            printf("\nPointCode status change, pc = %d.%d.%d, status = %d\n",
                    ((infoBlk.event.pcstate.aPc >> 16) & 0xff),
                    ((infoBlk.event.pcstate.aPc >>  8) & 0xff),
                    ((infoBlk.event.pcstate.aPc >>  0) & 0xff),
                    infoBlk.event.pcstate.status);
        }

        if (infoBlk.event.pcstate.status == SP_INACC)
        {
            memset(&pr, 0, sizeof(MTP3_PAUSE_RESUME));

            MTP3_PC_SET_VALUE(pr.affected, infoBlk.event.pcstate.aPc);

            MTP3_Encode(&ev, MTP3_MSG_PAUSE, &mtp3,
                        (ITS_OCTET *)&pr, sizeof(MTP3_PAUSE_RESUME));
        }
        else if (infoBlk.event.pcstate.status == SP_ACC)
        {
            memset(&pr, 0, sizeof(MTP3_PAUSE_RESUME));

            MTP3_PC_SET_VALUE(pr.affected, infoBlk.event.pcstate.aPc);

            MTP3_Encode(&ev, MTP3_MSG_RESUME, &mtp3,
                        (ITS_OCTET *)&pr, sizeof(MTP3_PAUSE_RESUME));
        }
        else
        {
            return (ITS_ENOMSG);
        }

        CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                  NULL,
                                  (ITS_POINTER)&ev);

        return (ITS_ENOMSG);

    case TCAP_EVENT_NOT_IND:
        /* this is an SCCP notification of a delivery problem */
        if (nms_debug)
        {
            printf("\nNotify Event received - cause = %d\n",
                    infoBlk.event.notif.retcause);
            printf("\nTransInfo, event = %d abort cause = %d\n"
                   "suId = %d, spId = %d, cdpc = %d.%d.%d:%d, cgpc = %d.%d.%d:%d\n",
                   infoBlk.event.notif.transInfo.msgType, 
                   infoBlk.event.notif.transInfo.abortCause,
                   infoBlk.event.notif.transInfo.suDlgId, 
                   infoBlk.event.notif.transInfo.spDlgId,
                   ((infoBlk.event.notif.transInfo.cdAddr.pointCode >> 16) &
                    0xff),
                   ((infoBlk.event.notif.transInfo.cdAddr.pointCode >>  8) &
                    0xff),
                   ((infoBlk.event.notif.transInfo.cdAddr.pointCode >>  0) &
                    0xff),
                   infoBlk.event.notif.transInfo.cdAddr.subsystem,
                   ((infoBlk.event.notif.transInfo.cgAddr.pointCode >> 16) &
                    0xff),
                   ((infoBlk.event.notif.transInfo.cgAddr.pointCode >>  8) &
                    0xff),
                   ((infoBlk.event.notif.transInfo.cgAddr.pointCode >>  0) &
                    0xff),
                   infoBlk.event.notif.transInfo.cgAddr.subsystem);
        }

        if ((TRANSPORT_MASK(VENDOR_OWNING_TRANSPORT(context)) & ITS_SCCP) == ITS_SCCP)
        {
#if 0
            /* FIXME: This is wrong.  This should be sending a TC-NOTICE
             * to the user, not a UDTS.
             */
            NMSBuildSCCPReturnEvent(context, &infoBlk.event.notif, &ev);

            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));

            return (ITS_SUCCESS);
#endif
        }

        return (ITS_ENOMSG);

    case TCAP_EVENT_DAT_IND:
        RetrieveTransaction(handl, &infoBlk, (U8 *)&Msg);
        break;

    default:
        printf("\nUnknown TCAP indication %d received\n",
               infoBlk.eventType);
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      A Function to dump data in hex+ascii format
 *
 *  Input Parameters:
 *      Buf - data to show
 *      ByteCnt - #Bytes in Buf
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
SendTransaction(ITS_SS7_HANDLE handle, unsigned short dialog)
{
    U8 *uptr = NULL;
    U8 *Msg;
    ITS_SS7_CONTEXT *context;
    U8 boardNum;
    S16 sapid;
    S32 retVal;
    TcapTransEvent tEvent;
    TcapDlgSect *pSect = NULL;
    TcapComp comp;
    MQUEUE_Msg *msg, *trmsg;
    ITS_EVENT *ev;

    context = (ITS_SS7_CONTEXT *)handle;
    boardNum = context->boardNum;
    sapid = context->sapid;

    if (nms_debug)
    {
        printf("VENDOR:  BEGIN SEND TRANSACTION\n");
    }

    if ((Msg = (U8 *)malloc(1024)) == NULL)
    {
        if (nms_debug)
        {
            printf("VENDOR: OUT OF MEMORY\n");
        }

        return (ITS_ENOMEM);
    }

    MQUEUE_Lock(VENDOR_SND_Q(context));

    /* find the transInfo */
    if (nms_debug)
    {
        printf("VENDOR: SEARCH FOR TRANSACTION\n");
    }

    for (trmsg = LIST_HEAD(VENDOR_SND_Q(context)); trmsg != NULL; trmsg = trmsg->next)
    {
        ev = (ITS_EVENT *)trmsg->data;

        if (ev->src == ITS_TCAP &&
            ev->data[0] == ITS_TCAP_DLG &&
            ev->data[1] == ((dialog >> 8) & 0xFFU) &&
            ev->data[2] == (dialog & 0xFFU))
        {
            MQUEUE_RemoveNoLock(VENDOR_SND_Q(context), trmsg);

            break;
        }
    }

    if (nms_debug)
    {
        printf("VENDOR: FOUND TRANSACTION\n");
    }

    /* didn't find the message? */
    if (trmsg == NULL)
    {
        MQUEUE_Unlock(VENDOR_SND_Q(context));

        if (nms_debug)
        {
            printf("VENDOR: NO TRANSACTION ON MQUEUE.\n");
        }

        free(Msg);

        return (ITS_ENOMSG);
    }

    /* initialize the transaction */
    memset(&tEvent, 0, sizeof(TcapTransEvent));
    memcpy(&tEvent, &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
           sizeof(TcapTransEvent));
#if defined(CCITT)
    if (tEvent.dlgPart.dlgType)
    {
        pSect = &tEvent.dlgPart;
    }
#endif
    if (tEvent.userInfoLen > 0)
    {
        uptr = &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT) + sizeof(TcapTransEvent)];
    }
    ITS_Free(trmsg->data);
    ITS_Free(trmsg);

    if ((retVal = TCAPInitTrans(Msg, &tEvent.transInfo, pSect, tEvent.userInfoLen, 
                                uptr)) != TCAP_SUCCESS)
    {
        MQUEUE_Unlock(VENDOR_SND_Q(context));


        if (nms_debug)
        {
            printf("VENDOR: ERROR IN NMSInitTrans() call.\n");
        }

        free(Msg);

        return (ITS_ENOMSG);
    }

    /*
     * loop through the send queue, pulling all components within this dialogue
     * out.
     */
    if (nms_debug)
    {
        printf("VENDOR: SEARCH FOR TRANSACTION COMPONENTS\n");
    }

    for (msg = LIST_HEAD(VENDOR_SND_Q(context)); msg != NULL;)
    {
        MQUEUE_Msg *tmp = msg->next;

        ev = (ITS_EVENT *)msg->data;

        if (ev->src == ITS_TCAP &&
            ev->data[0] == ITS_TCAP_CPT &&
            ev->data[1] == ((dialog >> 8) & 0xFFU) &&
            ev->data[2] == (dialog & 0xFFU))
        {

            MQUEUE_RemoveNoLock(VENDOR_SND_Q(context), msg);

            memset(&comp, 0, sizeof(TcapComp));
            memcpy(&comp, &ev->data[3], sizeof(comp));

            if (nms_debug)
            {
                printf("VENDOR: AddComp: len: %d\n",
                       ev->len - sizeof(comp) - 3);
            }

            if ((U16)(ev->len - sizeof(comp) - 3) == 0)
            {
                if ((retVal = TCAPAddComp(Msg, &comp, 0, NULL)) != TCAP_SUCCESS)
                {
                    printf("\nError on AddComp, err = %d\n", retVal);
                    /* what to do here? */
                }
            }
            else if ((retVal = TCAPAddComp(Msg, &comp,
                                           (U16)(ev->len - sizeof(comp) - 3),
                                           &ev->data[sizeof(comp) + 3]))
                     != TCAP_SUCCESS)
            {
                printf("\nError on AddComp, err = %d\n", retVal);
                /* what to do here? */
            }

            ITS_Free(msg->data);
            ITS_Free(msg);
        }

        msg = tmp;
    }

    if (nms_debug)
    {
        printf("VENDOR: FOUND TRANSACTION COMPONENTS\n");
    }

    /* send transaction */
    if ((retVal = TCAPTransRqst(boardNum, sapid, Msg)) != TCAP_SUCCESS)
    {
        MQUEUE_Unlock(VENDOR_SND_Q(context));


        if (nms_debug)
        {
            printf("VENDOR: ERROR IN NMSTransRequest().\n");
        }

        free(Msg);

        return (ITS_ENOMSG);
    }

    MQUEUE_Unlock(VENDOR_SND_Q(context));

    free(Msg);

    if (nms_debug)
    {
        printf("VENDOR:  EXIT SEND TRANSACTION\n");
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send our component to the stack
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSSendComponent(ITS_SS7_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    TcapComp comp;
    U8 boardNum;
    S16 sapid;
    ITS_EVENT ev;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handle;

    if (nms_debug)
    {
        printf("VENDOR:  ENTER SEND CPT\n");
    }

    boardNum = context->boardNum;
    sapid = context->sapid;
    memset(&comp, 0, sizeof(TcapComp));

    switch (cpt->ptype)
    {
#if defined(CCITT)
    case TCPPT_TC_INVOKE:
        comp.compType  = TCAP_INVOKE;
        if (cpt->u.invoke.invoke_id.len != 0 &&
            cpt->u.invoke.invoke_id.len >= 2)
        {
            comp.uProt.ituComp.invokeId.present = PRESENT;
            comp.uProt.ituComp.invokeId.compId =
                BufToId(cpt->u.invoke.invoke_id.data + 2,
                        cpt->u.invoke.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ituComp.invokeId.compId = 0;
        }

        if (cpt->u.invoke.linked_id.len != 0 &&
            cpt->u.invoke.linked_id.len >= 2)
        {
            comp.uProt.ituComp.linkedId.present = PRESENT;
            comp.uProt.ituComp.linkedId.compId =
                BufToId(cpt->u.invoke.linked_id.data + 2,
                        cpt->u.invoke.linked_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.linkedId.present = NOT_PRESENT;
            comp.uProt.ituComp.linkedId.compId = 0;
        }

        comp.uProt.ituComp.invokeTimer = cpt->u.invoke.timeout;        
        comp.uProt.ituComp.opClass = (U8)cpt->u.invoke.opClass;
        
        /* Setting the operation Code */
        if (cpt->u.invoke.operation.len >= 2)
        {
            if (cpt->u.invoke.operation.data[0] == TCPPN_LOCAL_OP_TAG)
            {
                comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_LOCAL;
                comp.uProt.ituComp.uComp.opcode.opCode.length = 1;
                comp.uProt.ituComp.uComp.opcode.opCode.octStr[0] =
                    cpt->u.invoke.operation.data[2];
            }
            else if (cpt->u.invoke.operation.data[0] == TCPPN_GLOBAL_OP_TAG)
            {
                comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_GLOBAL;
                comp.uProt.ituComp.uComp.opcode.opCode.length = 
                    cpt->u.invoke.operation.data[1];
                memcpy(comp.uProt.ituComp.uComp.opcode.opCode.octStr,
                       &cpt->u.invoke.operation.data[2], 
                       cpt->u.invoke.operation.data[1]);
            }
        }
        
        /* add component to transaction */
        ITS_EVENT_INIT(&ev, ITS_TCAP,
                       sizeof(comp) + cpt->u.invoke.param.len + 3);

        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));
        if (cpt->u.invoke.param.len > 0)
        {
            memcpy(&ev.data[sizeof(comp) + 3],
                   cpt->u.invoke.param.data, cpt->u.invoke.param.len);
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }
        break;

    case TCPPT_TC_RESULT_L:
        comp.compType  = TCAP_RET_RES_L;
        if (cpt->u.result.invoke_id.len != 0 &&
            cpt->u.result.invoke_id.len >= 2)
        {
            comp.uProt.ituComp.invokeId.present = PRESENT;
            comp.uProt.ituComp.invokeId.compId =
                BufToId(cpt->u.result.invoke_id.data + 2,
                        cpt->u.result.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ituComp.invokeId.compId = 0;
        }

        comp.uProt.ituComp.linkedId.present = NOT_PRESENT;
        comp.uProt.ituComp.linkedId.compId = 0;

        comp.uProt.ituComp.invokeTimer = 0;
        comp.uProt.ituComp.opClass = 0;

        /* Setting the operation Code */
        if (cpt->u.result.operation.len >= 2)
        {
            if (cpt->u.result.operation.data[0] == TCPPN_LOCAL_OP_TAG)
            {
                comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_LOCAL;
                comp.uProt.ituComp.uComp.opcode.opCode.length = 1;
                comp.uProt.ituComp.uComp.opcode.opCode.octStr[0] =
                    cpt->u.result.operation.data[2];
            }
            else if (cpt->u.result.operation.data[0] == TCPPN_GLOBAL_OP_TAG)
            {
                comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_GLOBAL;
                comp.uProt.ituComp.uComp.opcode.opCode.length = 
                    cpt->u.result.operation.data[1];
                memcpy(comp.uProt.ituComp.uComp.opcode.opCode.octStr,
                       &cpt->u.result.operation.data[2], 
                       cpt->u.result.operation.data[1]);
            }
            else
            {
                comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_NONE;
                comp.uProt.ituComp.uComp.opcode.opCode.length = 0;
            }
        }

        /* add component to transaction */
        ITS_EVENT_INIT(&ev, ITS_TCAP,
                       sizeof(comp) + cpt->u.result.param.len + 3);
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));
        if (cpt->u.result.param.len > 0)
        {
            memcpy(&ev.data[sizeof(comp) + 3],
                   cpt->u.result.param.data, cpt->u.result.param.len);
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_RESULT_NL:
        comp.compType  = TCAP_RET_RES_NL;
        if (cpt->u.result.invoke_id.len != 0 &&
            cpt->u.result.invoke_id.len >= 2)
        {
            comp.uProt.ituComp.invokeId.present = PRESENT;
            comp.uProt.ituComp.invokeId.compId =
                BufToId(cpt->u.result.invoke_id.data + 2,
                        cpt->u.result.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ituComp.invokeId.compId = 0;
        }

        comp.uProt.ituComp.linkedId.present = NOT_PRESENT;
        comp.uProt.ituComp.linkedId.compId = 0;

        comp.uProt.ituComp.invokeTimer = 0;
        comp.uProt.ituComp.opClass = 0;

        comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_LOCAL;

        /* opCode set to anything */
        comp.uProt.ituComp.uComp.opcode.opCode.length = 1;
        comp.uProt.ituComp.uComp.opcode.opCode.octStr[0] =
            cpt->u.result.operation.data[2];


        /* add component to transaction */
        ITS_EVENT_INIT(&ev, ITS_TCAP,
                       sizeof(comp) + cpt->u.result.param.len + 3);
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));
        if (cpt->u.result.param.len > 0)
        {
            memcpy(&ev.data[sizeof(comp) + 3],
                   cpt->u.result.param.data, cpt->u.result.param.len);
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_U_ERROR:
        comp.compType  = TCAP_RET_ERR;
        if (cpt->u.error.invoke_id.len != 0 &&
            cpt->u.error.invoke_id.len >= 2)
        {
            comp.uProt.ituComp.invokeId.present = PRESENT;
            comp.uProt.ituComp.invokeId.compId =
                BufToId(cpt->u.error.invoke_id.data + 2,
                        cpt->u.error.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ituComp.invokeId.compId = 0;
        }

        comp.uProt.ituComp.linkedId.present = NOT_PRESENT;
        comp.uProt.ituComp.linkedId.compId = 0;

        comp.uProt.ituComp.invokeTimer = 0;
        comp.uProt.ituComp.opClass = 0;

        /* Setting Error Code */
        if (cpt->u.error.error.data[0] == TCPPN_LOCAL_ERR_TAG)
        {
            comp.uProt.ituComp.uComp.errcode.errCodeId = TCAP_LOCAL;        
            comp.uProt.ituComp.uComp.errcode.errCode.length = 1;
            comp.uProt.ituComp.uComp.errcode.errCode.octStr[0] = 
                cpt->u.error.error.data[2];
        }
        else
        {
            comp.uProt.ituComp.uComp.errcode.errCodeId = TCAP_GLOBAL;
            comp.uProt.ituComp.uComp.errcode.errCode.length =
                cpt->u.error.error.data[1];

            memcpy(comp.uProt.ituComp.uComp.errcode.errCode.octStr,
                   &cpt->u.error.error.data[2],
                   cpt->u.error.error.data[1]);
        }

        /* add component to transaction */
        ITS_EVENT_INIT(&ev, ITS_TCAP,
                       sizeof(comp) + cpt->u.error.param.len + 3);
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));
        if (cpt->u.error.param.len > 0)
        {
            memcpy(&ev.data[sizeof(comp) + 3],
                   cpt->u.error.param.data, cpt->u.error.param.len);
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_U_CANCEL:
        comp.compType  = TCAP_CANCEL;
        /* 
         * No need to set rejSrc only used for Indication,
         * since we can only send U Cancel.
         */
        if (cpt->u.cancel.invoke_id.len != 0 &&
            cpt->u.cancel.invoke_id.len >= 2)
        {
            comp.uProt.ituComp.invokeId.present = PRESENT;
            comp.uProt.ituComp.invokeId.compId =
                BufToId(cpt->u.cancel.invoke_id.data + 2,
                        cpt->u.cancel.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ituComp.invokeId.compId = 0;
        }

        comp.uProt.ituComp.linkedId.present = NOT_PRESENT;
        comp.uProt.ituComp.linkedId.compId = 0;

        comp.uProt.ituComp.invokeTimer = 0;
        comp.uProt.ituComp.opClass = 0;

        comp.uProt.ituComp.uComp.opcode.opCodeType = TCAP_LOCAL;

        /* opCode set to anything */
        comp.uProt.ituComp.uComp.opcode.opCode.length = 0;

        /* add component to transaction */
        ITS_EVENT_INIT(&ev, ITS_TCAP,
                       sizeof(comp) + 3);
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_U_REJECT:
        comp.compType  = TCAP_REJECT;
        /* 
         * No need to set rejSrc only used for Indication,
         * since we can only send U Reject.
         */

        if (cpt->u.reject.invoke_id.len != 0 &&
            cpt->u.reject.invoke_id.len >= 2)
        {
            comp.uProt.ituComp.invokeId.present = PRESENT;
            comp.uProt.ituComp.invokeId.compId =
                BufToId(cpt->u.reject.invoke_id.data + 2,
                        cpt->u.reject.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ituComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ituComp.invokeId.compId = 0;
        }

        comp.uProt.ituComp.linkedId.present = NOT_PRESENT;
        comp.uProt.ituComp.linkedId.compId = 0;

        comp.uProt.ituComp.invokeTimer = 0;
        comp.uProt.ituComp.opClass = 0;

        /* populating Problem Type: high bit must be set for NMS */
        comp.uProt.ituComp.uComp.prbcode.probType = 
            (cpt->u.reject.problem.data[0] | 0x80);

        /* Populating Error Code */
        if (cpt->u.reject.problem.len == 3)
        {
            comp.uProt.ituComp.uComp.prbcode.prbCode.length = 1;
            comp.uProt.ituComp.uComp.prbcode.prbCode.octStr[0] = 
                cpt->u.reject.problem.data[2];
        }
        else
        {
            comp.uProt.ituComp.uComp.prbcode.prbCode.length = 
                cpt->u.reject.problem.data[1];
            memcpy(comp.uProt.ituComp.uComp.prbcode.prbCode.octStr,
                   &cpt->u.reject.problem.data[2],
                   cpt->u.reject.problem.data[1]);
        }

        /* add component to transaction */
        ITS_EVENT_INIT(&ev, ITS_TCAP,
                       sizeof(comp) + 3);
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }
        break;

#else /* defined(ANSI) */

    case TCPPT_TC_INVOKE:
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: INVOKE_L: did: %04x\n",
                   hdr->context.dialogue_id);
        }

        comp.compType  = TCAP_INVOKE_L;
        if (cpt->u.invoke.invoke_id.len != 0 &&
            cpt->u.invoke.invoke_id.len >= 2)
        {
            comp.uProt.ansiComp.invokeId.present = PRESENT;
            comp.uProt.ansiComp.invokeId.compId =
                BufToId(cpt->u.invoke.invoke_id.data + 2,
                        cpt->u.invoke.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ansiComp.invokeId.compId = 0;
        }

        if (cpt->u.invoke.linked_id.len != 0 &&
            cpt->u.invoke.linked_id.len >= 2)
        {
            comp.uProt.ansiComp.corrId.present = PRESENT;
            comp.uProt.ansiComp.corrId.compId =
                BufToId(cpt->u.invoke.linked_id.data + 2,
                        cpt->u.invoke.linked_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.corrId.present = NOT_PRESENT;
            comp.uProt.ansiComp.corrId.compId = 0;
        }

        comp.rejSrc = TCAP_COMP_NONE;

        comp.uProt.ansiComp.invokeTimer = cpt->u.invoke.timeout;

        if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_PRIVATE_TCAP)
        {
            comp.uProt.ansiComp.uComp.opcode.opCodeId = TCAP_PRIVATE;
        }
        else
        {
            comp.uProt.ansiComp.uComp.opcode.opCodeId = TCAP_NATIONAL;
        }

        comp.uProt.ansiComp.uComp.opcode.opFamily =
            cpt->u.invoke.operation.data[2];
        comp.uProt.ansiComp.uComp.opcode.opSpec =
            cpt->u.invoke.operation.data[3];

        if (nms_debug)
        {
            printf("VENDOR: Send cpt: len %d\n", cpt->u.invoke.param.len);
        }

        if (cpt->u.invoke.param.len == 0)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_NO_SET_SEQ;
        }
        else if (cpt->u.invoke.param.data[0] == SEQ_TAG)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SEQUENCE;
        }
        else
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SET;
        }

        /* add component to transaction */
        ev.len = sizeof(comp) +
                    (cpt->u.invoke.param.len >= 2
                        ? cpt->u.invoke.param.len - 2
                        : 0) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT); 
        ev.src = ITS_TCAP;
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
               &comp, sizeof(comp));
        /* strip off the SET tag that pepsy adds */
        if (cpt->u.invoke.param.len >= 2)
        {
            if (cpt->u.invoke.param.data[1] != 0x81)
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.invoke.param.data + 2,
                       cpt->u.invoke.param.len - 2);
            }
            else
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.invoke.param.data + 3,
                       cpt->u.invoke.param.len - 3);
            }
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_RESULT_L:
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: RESULT_L: did: %04x\n",
                   hdr->context.dialogue_id);
        }
        comp.compType  = TCAP_RET_RES_L;
        comp.uProt.ansiComp.invokeId.present = NOT_PRESENT;
        comp.uProt.ansiComp.invokeId.compId = 0;

        if (cpt->u.result.invoke_id.len != 0 &&
            cpt->u.result.invoke_id.len >= 2)
        {
            comp.uProt.ansiComp.corrId.present = PRESENT;
            comp.uProt.ansiComp.corrId.compId =
                BufToId(cpt->u.result.invoke_id.data + 2,
                        cpt->u.result.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.corrId.present = NOT_PRESENT;
            comp.uProt.ansiComp.corrId.compId = 0;
        }

        comp.uProt.ansiComp.invokeTimer = 0;

        if (cpt->u.result.param.len == 0)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_NO_SET_SEQ;
        }
        else if (cpt->u.result.param.data[0] == SEQ_TAG)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SEQUENCE;
        }
        else
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SET;
        }

        /* add component to transaction */
        ev.len = sizeof(comp) +
                    (cpt->u.result.param.len >= 2
                        ? cpt->u.result.param.len - 2
                        : 0) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT); 
        ev.src = ITS_TCAP;
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
               &comp, sizeof(comp));
        if (cpt->u.result.param.len >= 2)
        {
            if (cpt->u.result.param.data[1] != 0x81)
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.result.param.data + 2,
                       cpt->u.result.param.len - 2);
            }
            else
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.result.param.data + 3,
                       cpt->u.result.param.len - 3);
            }
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_ERROR:
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: ERROR: did: %04x\n",
                   hdr->context.dialogue_id);
        }
        comp.compType  = TCAP_RET_ERR;

        comp.uProt.ansiComp.invokeId.present = NOT_PRESENT;
        comp.uProt.ansiComp.invokeId.compId = 0;

        if (cpt->u.error.invoke_id.len != 0 &&
            cpt->u.error.invoke_id.len >= 2)
        {
            comp.uProt.ansiComp.corrId.present = PRESENT;
            comp.uProt.ansiComp.corrId.compId =
                BufToId(cpt->u.error.invoke_id.data + 2,
                        cpt->u.error.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.corrId.present = NOT_PRESENT;
            comp.uProt.ansiComp.corrId.compId = 0;
        }

        comp.uProt.ansiComp.invokeTimer = 0;
 
        /* add component to transaction */
        ev.len = sizeof(comp) +
                    (cpt->u.error.param.len >= 2
                        ? cpt->u.error.param.len - 2
                        : 0) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT); 
        ev.src = ITS_TCAP;
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        /* note the length of the errcode must be at least 4 */
        if (cpt->u.error.error.data[0] == TCPPN_ECI_NATIONAL_TCAP)
        {
            comp.uProt.ansiComp.uComp.errcode.errCodeId = TCAP_NATIONAL;
        }
        else
        {
            comp.uProt.ansiComp.uComp.errcode.errCodeId = TCAP_PRIVATE;
        }
        comp.uProt.ansiComp.uComp.errcode.errCode =
            cpt->u.error.error.data[2];

        if (cpt->u.error.param.len == 0)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_NO_SET_SEQ;
        }
        else if (cpt->u.error.param.data[0] == SEQ_TAG)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SEQUENCE;
        }
        else
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SET;
        }

        memcpy(&ev.data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
               &comp, sizeof(comp));
        if (cpt->u.error.param.len >= 2)
        {
            if (cpt->u.error.param.data[1] != 0x81)
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.error.param.data + 2,
                       cpt->u.error.param.len - 2);
            }
            else
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.error.param.data + 3,
                       cpt->u.error.param.len - 3);
            }
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_REJECT:
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: REJECT: did: %04x\n",
                   hdr->context.dialogue_id);
        }
        comp.compType  = TCAP_REJECT;

        comp.uProt.ansiComp.invokeId.present = NOT_PRESENT;
        comp.uProt.ansiComp.invokeId.compId = 0;

        if (cpt->u.reject.invoke_id.len != 0 &&
            cpt->u.reject.invoke_id.len >= 2)
        {
            comp.uProt.ansiComp.corrId.present = PRESENT;
            comp.uProt.ansiComp.corrId.compId =
                BufToId(cpt->u.reject.invoke_id.data + 2,
                        cpt->u.reject.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.corrId.present = NOT_PRESENT;
            comp.uProt.ansiComp.corrId.compId = 0;
        }

        comp.uProt.ansiComp.uComp.prbcode.probType =
            cpt->u.reject.problem.data[2];
        comp.uProt.ansiComp.uComp.prbcode.probSpec =
            cpt->u.reject.problem.data[3];

        comp.uProt.ansiComp.invokeTimer = 0;

        /* add component to transaction */
        ev.len = sizeof(comp) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT);
        ev.src = ITS_TCAP;
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_INVOKE_NL:
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: INVOKE_NL: did: %04x\n",
                   hdr->context.dialogue_id);
        }
        comp.compType  = TCAP_INVOKE_NL;

        if (cpt->u.invoke.invoke_id.len != 0 &&
            cpt->u.invoke.invoke_id.len >= 2)
        {
            comp.uProt.ansiComp.invokeId.present = PRESENT;
            comp.uProt.ansiComp.invokeId.compId =
                BufToId(cpt->u.invoke.invoke_id.data + 2,
                        cpt->u.invoke.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.invokeId.present = NOT_PRESENT;
            comp.uProt.ansiComp.invokeId.compId = 0;
        }

        if (cpt->u.invoke.linked_id.len != 0 &&
            cpt->u.invoke.linked_id.len >= 2)
        {
            comp.uProt.ansiComp.corrId.present = PRESENT;
            comp.uProt.ansiComp.corrId.compId =
                BufToId(cpt->u.invoke.linked_id.data + 2,
                        cpt->u.invoke.linked_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.corrId.present = NOT_PRESENT;
            comp.uProt.ansiComp.corrId.compId = 0;
        }

        comp.uProt.ansiComp.invokeTimer = cpt->u.invoke.timeout;        

        if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_PRIVATE_TCAP)
        {
            comp.uProt.ansiComp.uComp.opcode.opCodeId = TCAP_PRIVATE;
        }
        else
        {
            comp.uProt.ansiComp.uComp.opcode.opCodeId = TCAP_NATIONAL;
        }

        comp.uProt.ansiComp.uComp.opcode.opFamily =
            cpt->u.invoke.operation.data[2];
        comp.uProt.ansiComp.uComp.opcode.opSpec =
            cpt->u.invoke.operation.data[3];

        if (cpt->u.invoke.param.len == 0)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_NO_SET_SEQ;
        }
        else if (cpt->u.invoke.param.data[0] == SEQ_TAG)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SEQUENCE;
        }
        else
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SET;
        }

        /* add component to transaction */
        ev.len = sizeof(comp) +
                    (cpt->u.invoke.param.len >= 2
                        ? cpt->u.invoke.param.len - 2
                        : 0) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT); 
        ev.src = ITS_TCAP;
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));
        if (cpt->u.invoke.param.len >= 2)
        {
            if (cpt->u.invoke.param.data[1] != 0x81)
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.invoke.param.data + 2,
                       cpt->u.invoke.param.len - 2);
            }
            else
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.invoke.param.data + 3,
                       cpt->u.invoke.param.len - 3);
            }
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

    case TCPPT_TC_RESULT_NL:
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: RESULT_NL: did: %04x\n",
                   hdr->context.dialogue_id);
        }
        comp.compType  = TCAP_RET_RES_NL;

        comp.uProt.ansiComp.invokeId.present = NOT_PRESENT;
        comp.uProt.ansiComp.invokeId.compId = 0;

        if (cpt->u.result.invoke_id.len != 0 &&
            cpt->u.result.invoke_id.len >= 2)
        {
            comp.uProt.ansiComp.corrId.present = PRESENT;
            comp.uProt.ansiComp.corrId.compId =
                BufToId(cpt->u.result.invoke_id.data + 2,
                        cpt->u.result.invoke_id.len - 2);
        }
        else
        {
            comp.uProt.ansiComp.corrId.present = NOT_PRESENT;
            comp.uProt.ansiComp.corrId.compId = 0;
        }

        comp.uProt.ansiComp.invokeTimer = 0;

        if (cpt->u.result.param.len == 0)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_NO_SET_SEQ;
        }
        else if (cpt->u.result.param.data[0] == SEQ_TAG)
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SEQUENCE;
        }
        else
        {
            comp.uProt.ansiComp.paramFlg = TCAP_SET;
        }

        /* add component to transaction */
        ev.len = sizeof(comp) +
                    (cpt->u.result.param.len >= 2
                        ? cpt->u.result.param.len - 2
                        : 0) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT); 
        ev.src = ITS_TCAP;
        ev.data[0] = ITS_TCAP_CPT;
        ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
        ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;

        memcpy(&ev.data[3], &comp, sizeof(comp));
        if (cpt->u.result.param.len > 0)
        {
            if (cpt->u.result.param.data[1] != 0x81)
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.result.param.data + 2,
                       cpt->u.result.param.len - 2);
            }
            else
            {
                memcpy(&ev.data[sizeof(comp) + sizeof(ITS_OCTET) +
                        sizeof(ITS_USHORT)],
                       cpt->u.result.param.data + 3,
                       cpt->u.result.param.len - 3);
            }
        }

        if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("VENDOR: ERROR ADDING COMPONENT TO MQUEUE.\n");
            }

            return (ITS_ESENDFAIL);
        }

        break;

#endif

    default:
        break;
    }

    nms_errno = ITS_SUCCESS;

    if (nms_debug)
    {
        printf("VENDOR:  EXIT SEND CPT\n");
    }

    return nms_errno;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send our dialogue to the stack
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSSendDialogue(ITS_SS7_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    TcapTransEvent tEvent;
    ITS_EVENT ev;
    DLG_BEGIN *beg;
    DLG_END *end;
    DLG_UNI *uni;
    DLG_CONTINUE *cont;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handle;
#if defined(CCITT)
    DLG_ABORT *abt;
    DLG_USR_INF *uInfo = NULL;
#endif

    if (nms_debug)
    {
        printf("VENDOR:  ENTER SEND DLG\n");
    }

    memset(&tEvent, 0, sizeof(TcapTransEvent));
    memset(&ev, 0, sizeof(ITS_EVENT));

    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        uni = &dlg->u.uni;

        /* load transaction info */
        tEvent.transInfo.msgType = TCAP_UNI;
        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        /* MUST be zero */
        tEvent.transInfo.spDlgId = 0;

        if (uni->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = uni->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (uni->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (uni->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = 0;

        BuildSccpAddr(&uni->dest_addr, &tEvent.transInfo.cdAddr);
        BuildSccpAddr(&uni->orig_addr, &tEvent.transInfo.cgAddr);

        if (tEvent.transInfo.cdAddr.presInd == PRESENT &&
            tEvent.transInfo.cdAddr.pointCodeInd == PTCODE_NONE)
        {
            tEvent.transInfo.cdAddr.pointCodeInd = PTCODE_INC;
            tEvent.transInfo.cdAddr.pointCode = MTP3_PC_GET_VALUE(uni->dpc);
        }
        if (tEvent.transInfo.cgAddr.presInd == PRESENT &&
            tEvent.transInfo.cgAddr.pointCodeInd == PTCODE_NONE)
        {
            tEvent.transInfo.cgAddr.pointCodeInd = PTCODE_INC;
            tEvent.transInfo.cgAddr.pointCode = MTP3_PC_GET_VALUE(uni->opc);
        }
#if defined(CCITT)
        /*
         * AC-name is mandatory in dlgPart. So we send the dlgPart only if the
         * user given us, at the least, the ac_name to send. This also takes 
         * care of Blue Book ('88) support in the vendor lib.
         */
        if ((uni->ac_name.len > 0) || (uni->user_info.len > 0))
        {
            tEvent.dlgPart.dlgType = TCAP_DLGP_UNI;
#ifdef DEBUG
            printf("VENDOR: Sending UNI Dialogue Portion for Uni.\n");
#endif
        }
        if (uni->ac_name.len > 0)
        {
            tEvent.dlgPart.apConName.length = uni->ac_name.data[1];
            memcpy(tEvent.dlgPart.apConName.octStr, &uni->ac_name.data[2], 
                   uni->ac_name.len);
        }
        uInfo = &uni->user_info;
#endif

        break;

#if defined(CCITT)
    case TCPPT_TC_BEGIN:
        beg = &dlg->u.begin;

        /* load transaction info */
        tEvent.transInfo.msgType = TCAP_BEGIN;
        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        /* MUST be zero */
        tEvent.transInfo.spDlgId = 0;

        if (beg->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = beg->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (beg->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (beg->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = 0;

        BuildSccpAddr(&beg->dest_addr, &tEvent.transInfo.cdAddr);
        BuildSccpAddr(&beg->orig_addr, &tEvent.transInfo.cgAddr);

        if (tEvent.transInfo.cdAddr.presInd == PRESENT &&
            tEvent.transInfo.cdAddr.pointCodeInd == PTCODE_NONE)
        {
            tEvent.transInfo.cdAddr.pointCodeInd = PTCODE_INC;
            tEvent.transInfo.cdAddr.pointCode = MTP3_PC_GET_VALUE(beg->dpc);
        }
        if (tEvent.transInfo.cgAddr.presInd == PRESENT &&
            tEvent.transInfo.cgAddr.pointCodeInd == PTCODE_NONE)
        {
            tEvent.transInfo.cgAddr.pointCodeInd = PTCODE_INC;
            tEvent.transInfo.cgAddr.pointCode = MTP3_PC_GET_VALUE(beg->opc);
        }

        /*
         * AC-name is mandatory in dlgPart. So we send the dlgPart only if the
         * user given us, at the least, the ac_name to send. This also takes 
         * care of Blue Book ('88) support in the vendor lib.
         */
        if ((beg->ac_name.len > 0) || (beg->user_info.len > 0))
        {
            tEvent.dlgPart.dlgType = TCAP_DLGP_REQ;
#ifdef DEBUG
            printf("VENDOR: Sending REQ Dialogue Portion for Begin.\n");
#endif
        }
        if (beg->ac_name.len > 0)
        {
            tEvent.dlgPart.apConName.length = beg->ac_name.data[1];
            memcpy(tEvent.dlgPart.apConName.octStr, &beg->ac_name.data[2], 
                   beg->ac_name.data[1]);
        }
        uInfo = &beg->user_info;

        break;

    case TCPPT_TC_CONTINUE:
        cont = &dlg->u.cont;

        /* load transaction info */
        tEvent.transInfo.msgType = TCAP_CONTINUE;
        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        /* use Dlg ID from request */
        tEvent.transInfo.spDlgId = its_spDlgIds[hdr->context.dialogue_id];

        if (cont->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = cont->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (cont->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (cont->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = 0;

        /*
         * AC-name is mandatory in dlgPart. So we send the dlgPart only if the
         * user given us, at the least, the ac_name to send. This also takes 
         * care of Blue Book ('88) support in the vendor lib.
         */
        if ((cont->ac_name.len > 0) || (cont->user_info.len > 0))
        {
            tEvent.dlgPart.dlgType = TCAP_DLGP_RSP;
#ifdef DEBUG
            printf("VENDOR: Sending RSP Dialogue Portion for Continue.\n");
#endif
        }
        if (cont->ac_name.len > 0)
        {
            tEvent.dlgPart.apConName.length = cont->ac_name.data[1];
            memcpy(tEvent.dlgPart.apConName.octStr, &cont->ac_name.data[2], 
                   cont->ac_name.data[1]);
        }
        uInfo = &cont->user_info;

        break;

    case TCPPT_TC_END:
        end = &dlg->u.end;

        /* load transaction info */
        tEvent.transInfo.msgType = TCAP_END;
        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        tEvent.transInfo.spDlgId = its_spDlgIds[hdr->context.dialogue_id];

        its_spDlgIds[hdr->context.dialogue_id] = 0;

        if (end->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = end->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (end->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (end->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = end->termination;

        /*
         * AC-name is mandatory in dlgPart. So we send the dlgPart only if the
         * user given us, at the least, the ac_name to send. This also takes 
         * care of Blue Book ('88) support in the vendor lib.
         */
        if ((end->ac_name.len > 0) || (end->user_info.len > 0))
        {
            tEvent.dlgPart.dlgType = TCAP_DLGP_RSP;
#ifdef DEBUG
            printf("VENDOR: Sending RSP Dialogue Portion for End.\n");
#endif
        }
        if (end->ac_name.len > 0)
        {
            tEvent.dlgPart.apConName.length = end->ac_name.data[1];
            memcpy(tEvent.dlgPart.apConName.octStr, &end->ac_name.data[2], 
                   end->ac_name.data[1]);
        }
        uInfo = &end->user_info;

        break;

    case TCPPT_TC_U_ABORT:
        abt = &dlg->u.abort;

        /* load transaction info */
        tEvent.transInfo.msgType = TCAP_ABORT;
        tEvent.transInfo.spDlgId = its_spDlgIds[hdr->context.dialogue_id];
        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        its_spDlgIds[hdr->context.dialogue_id] = 0;

        tEvent.transInfo.abortCause = (ITS_OCTET)abt->abort_reason;

        if (abt->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = abt->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (abt->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (abt->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = 0;

        /*
         * AC-name is mandatory in dlgPart. So we send the dlgPart only if the
         * user given us, at the least, the ac_name to send. This also takes 
         * care of Blue Book ('88) support in the vendor lib.
         */
        if ((abt->ac_name.len > 0) || (abt->user_info.len > 0))
        {
            tEvent.dlgPart.dlgType = TCAP_DLGP_ABT;
            tEvent.dlgPart.abrtSrc = TCAP_DLG_USR_ABRT;
#ifdef DEBUG
            printf("VENDOR: Sending ABT Dialogue Portion for U-Abort.\n");
#endif
        }
        if (abt->ac_name.len > 0)
        {
            tEvent.dlgPart.apConName.length = abt->ac_name.data[1];
            memcpy(tEvent.dlgPart.apConName.octStr, &abt->ac_name.data[2], 
                   abt->ac_name.data[1]);
        }
        tEvent.dlgPart.abrtSrc = TCAP_DLG_USR_ABRT;
        uInfo = &abt->user_info;

        break;

#else /* !defined(CCITT) */

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        beg = &dlg->u.begin;

        /* load transaction info */
        if (dlg->ptype == TCPPT_TC_QUERY_W_PERM)
        {
            tEvent.transInfo.msgType = TCAP_QRY_PRM;
        }
        else
        {
            tEvent.transInfo.msgType = TCAP_QRY_NO_PRM;
        }

        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        /* Must be zero */
        tEvent.transInfo.spDlgId = 0;
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: QUERY: SP-DLG: %08x SU-DLG: %08x DLG %04x\n",
                   tEvent.transInfo.spDlgId, tEvent.transInfo.suDlgId, hdr->context.dialogue_id);
        }

        if (beg->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = beg->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (beg->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (beg->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = 0;

        BuildSccpAddr(&beg->dest_addr, &tEvent.transInfo.cdAddr);
        BuildSccpAddr(&beg->orig_addr, &tEvent.transInfo.cgAddr);

        if (tEvent.transInfo.cdAddr.presInd == PRESENT &&
            tEvent.transInfo.cdAddr.pointCodeInd == PTCODE_NONE)
        {
            tEvent.transInfo.cdAddr.pointCodeInd = PTCODE_INC;
            tEvent.transInfo.cdAddr.pointCode = MTP3_PC_GET_VALUE(beg->dpc);
        }
        if (tEvent.transInfo.cgAddr.presInd == PRESENT &&
            tEvent.transInfo.cgAddr.pointCodeInd == PTCODE_NONE)
        {
            tEvent.transInfo.cgAddr.pointCodeInd = PTCODE_INC;
            tEvent.transInfo.cgAddr.pointCode = MTP3_PC_GET_VALUE(beg->opc);
        }

        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        cont = &dlg->u.cont;

        /* load transaction info */
        if (dlg->ptype == TCPPT_TC_CONV_W_PERM)
        {
            tEvent.transInfo.msgType = TCAP_CNV_PRM;
        }
        else
        {
            tEvent.transInfo.msgType = TCAP_CNV_NO_PRM;
        }

        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        tEvent.transInfo.spDlgId = its_spDlgIds[hdr->context.dialogue_id];
        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: CONV: SP-DLG: %08x SU-DLG: %08x DLG %04x\n",
                   tEvent.transInfo.spDlgId, tEvent.transInfo.suDlgId, hdr->context.dialogue_id);
        }

        if (cont->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = cont->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (cont->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (cont->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = 0;

        break;

    case TCPPT_TC_RESP:
        end = &dlg->u.end;

        /* load transaction info */
        tEvent.transInfo.msgType = TCAP_RESPONSE;

        tEvent.transInfo.suDlgId = hdr->context.dialogue_id;
        tEvent.transInfo.spDlgId = its_spDlgIds[hdr->context.dialogue_id];

        if (nms_debug)
        {
            printf("VENDOR: OUTBOUND: RESP: SP-DLG: %08x SU-DLG: %08x DLG %04x\n",
                   tEvent.transInfo.spDlgId, tEvent.transInfo.suDlgId, hdr->context.dialogue_id);
        }
        its_spDlgIds[hdr->context.dialogue_id] = 0;


        if (end->qos.indicator & QOSI_PRIORITY)
        {
            tEvent.transInfo.qos.priority = end->qos.priority;
        }
        else
        {
            tEvent.transInfo.qos.priority = 0;
        }

        if (end->qos.indicator & QOSI_RET_OPT)
        {
            tEvent.transInfo.qos.retOpt = MSG_RETURN;
        }
        else
        {
            tEvent.transInfo.qos.retOpt = MSG_DISCARD;
        }

        if (end->qos.indicator & QOSI_SEQ_CTRL)
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_SEQDEL;
        }
        else
        {
            tEvent.transInfo.qos.seqDlvy = TCAP_QOS_NORMAL;
        }

        tEvent.transInfo.preArgEnd = end->termination;

        break;
#endif

    default:
        break;
    }

    ev.src = ITS_TCAP;
    ev.len = sizeof(TcapTransEvent) + sizeof(ITS_OCTET) + sizeof(ITS_USHORT);
#if defined(CCITT)
    if (uInfo->len > 0)
    {
        ev.len += uInfo->len;
        tEvent.userInfoLen = uInfo->len;
    }
#endif

    ev.data[0] = ITS_TCAP_DLG;
    ev.data[1] = (hdr->context.dialogue_id >> 8) & 0xFFU;
    ev.data[2] = (hdr->context.dialogue_id) & 0xFFU;
    memcpy(&ev.data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)], &tEvent, 
           sizeof(TcapTransEvent));
#if defined(CCITT)
    if (uInfo->len > 0)
    {
        memcpy(&ev.data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT) + sizeof(TcapTransEvent)], 
               uInfo->data, uInfo->len);
    }
#endif

    if (MQUEUE_Enqueue(VENDOR_SND_Q(context), &ev, sizeof(ITS_EVENT)) != ITS_SUCCESS)
    {
        if (nms_debug)
        {
            printf("VENDOR: ERROR ADDING DIALOGUE TO MQUEUE.\n");
        }

        return (ITS_ENOMSG);
    }

    if (nms_debug)
    {
        printf("VENDOR:  EXIT SEND DLG\n");
    }

    return (SendTransaction(handle, hdr->context.dialogue_id));
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSAllocDID(ITS_USHORT *did)
{
    static ITS_USHORT idid = 0;

    idid++;
    if (idid == 0x8000)
    {
        idid = 1;
    }
    
    *did = idid;

    return (ITS_SUCCESS);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSSendTCAPUOS(ITS_SS7_HANDLE handle, ITS_OCTET ni,
               ITS_UINT pc, ITS_OCTET ssn)
{
    S32  retval;
    U8   boardNum;
    S16  sapid;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handle;

    boardNum = context->boardNum;
    sapid = context->sapid;

    if ((retval = TCAPStateReq(boardNum, sapid,
                               (U8)ssn, SS_OOS)) != TCAP_SUCCESS)
    {
        printf("\n TCAPStateReq return val = %d.", retval);
        return(retval);
    }

    return (TCAP_SUCCESS);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSSendTCAPUIS(ITS_SS7_HANDLE handle, ITS_OCTET ni,
               ITS_UINT pc, ITS_OCTET ssn)
{
    S16  retval;
    U8   boardNum;
    S16  sapid;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handle;
    
    boardNum = context->boardNum;
    sapid = context->sapid;

    if ((retval = TCAPStateReq(boardNum, sapid,
                               (U8)ssn, SS_IS)) != TCAP_SUCCESS)
    {
        printf("\n TCAPStateReq return val = %d.", retval);
        return(retval);
    }

    return (TCAP_SUCCESS);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSSetTCAPCong(ITS_SS7_HANDLE handle, ITS_OCTET ni,
               ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
    return (TCAP_SUCCESS);
}

#endif /* INCLUDE_TCAP */
