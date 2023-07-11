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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: sccp.c,v 9.1 2005/03/23 12:56:16 cvsadmin Exp $
 *
 * LOG: $Log: sccp.c,v $
 * LOG: Revision 9.1  2005/03/23 12:56:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:39  cvsadmin
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
 * LOG: Revision 5.5  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/12/14 00:05:04  mmiers
 * LOG: Generic vendor framework.
 * LOG:
 * LOG: Revision 5.2  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:34  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2001/02/13 23:06:38  mmiers
 * LOG: Correct a load of signatures.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:10:52  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/07/25 20:00:33  hxing
 * LOG:
 * LOG:
 * LOG: Sanitize the source.  Get layer builds working for all 4 parts.
 * LOG:
 * LOG: Revision 2.2  2000/05/24 18:45:24  fhasle
 * LOG:
 * LOG: Added GTT for ANSI, fixed GTT Ind. for ITU (TCAP and SCCP).
 * LOG:
 * LOG: Revision 2.1  2000/01/28 00:47:06  rsonak
 * LOG:
 * LOG: Commit the PR2 patch. Added MTPS Pause and Resume callbacks for the STANDALONE
 * LOG: and INTEGRATED cases
 * LOG:
 * LOG: Revision 1.35.2.1  2000/01/27 23:16:48  rsonak
 * LOG:
 * LOG: Added MTP3 Pause and Resumes for the INTEGRATED and STANDALONE modes
 * LOG:
 * LOG: Revision 1.35  1999/11/06 00:03:00  mmiers
 * LOG:
 * LOG:
 * LOG: Do it right.
 * LOG:
 * LOG: Revision 1.34  1999/11/05 23:29:36  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize the build.  Single configuration now.
 * LOG:
 * LOG: Revision 1.33  1999/10/07 17:43:49  mmiers
 * LOG:
 * LOG:
 * LOG: Try to bring some sanity to the build process.
 * LOG:
 * LOG: Revision 1.32  1999/09/24 19:35:31  ite
 * LOG:
 * LOG: fixed typo
 * LOG:
 * LOG: Revision 1.31  1999/06/21 22:28:16  ite
 * LOG:
 * LOG: Don't invert the logic.  Duh.
 * LOG:
 * LOG: Revision 1.30  1999/06/21 22:22:22  ite
 * LOG:
 * LOG:
 * LOG: Make sure all code is aware of integrated vs. standalone.
 * LOG:
 * LOG: Revision 1.29  1999/01/19 23:39:29  mmiers
 * LOG: Some missing debug for SS7
 * LOG:
 * LOG: Revision 1.28  1998/11/25 23:57:39  mmiers
 * LOG: SS7 integration is complete.
 * LOG:
 * LOG: Revision 1.27  1998/11/13 23:15:52  mmiers
 * LOG: Sanitize the NT build environment.
 * LOG:
 * LOG: Revision 1.26  1998/11/13 18:42:12  mmiers
 * LOG: Fix this up for HNS.
 * LOG:
 * LOG: Revision 1.25  1998/11/12 18:50:26  mmiers
 * LOG: Integrating NMS
 * LOG:
 * LOG: Revision 1.24  1998/11/12 18:45:23  mmiers
 * LOG: Reduce amount of standalone specific modifiers.
 * LOG:
 * LOG: Revision 1.23  1998/11/12 18:34:32  mmiers
 * LOG: Get ANSI building again.
 * LOG:
 * LOG: Revision 1.22  1998/11/05 21:30:33  mmiers
 * LOG: Working on pause/resume.
 * LOG:
 * LOG: Revision 1.21  1998/10/28 23:51:49  mmiers
 * LOG: Halfway through SCMG.
 * LOG:
 * LOG: Revision 1.20  1998/10/28 00:27:19  mmiers
 * LOG: More fixes for NMS SCCP/MTP3.
 * LOG:
 * LOG: Revision 1.19  1998/10/27 21:08:55  mmiers
 * LOG: Finish up round 1 of NMS/SCCP integration.
 * LOG:
 * LOG: Revision 1.18  1998/10/27 18:24:04  mmiers
 * LOG: Continue implementing NMS SCCP.
 * LOG:
 * LOG: Revision 1.17  1998/10/27 16:19:34  mmiers
 * LOG: Recreate a header file.
 * LOG:
 * LOG: Revision 1.16  1998/10/27 01:25:32  mmiers
 * LOG: A little more thinking about SCCP integration.
 * LOG:
 * LOG: Revision 1.15  1998/10/26 23:54:15  mmiers
 * LOG: Rework so that we can integrate with our SCCP and TCAP.
 * LOG:
 * LOG: Revision 1.14  1998/10/16 14:41:59  mmiers
 * LOG: Update to match current header definitions.
 * LOG:
 * LOG: Revision 1.13  1998/08/06 17:23:17  ite
 * LOG: More cleanup for new infrastructure.
 * LOG:
 * LOG: Revision 1.12  1998/08/06 17:11:01  ite
 * LOG: Cleanup for new infrastructure.
 * LOG:
 * LOG: Revision 1.11  1998/06/17 20:46:36  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.10  1998/04/29 23:03:18  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.  Same with SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/04/09 14:50:56  mmiers
 * LOG: Remove printf() when unable to retrieve a message from the board.  Fix bug
 * LOG: reporting the wrong status (sccp).
 * LOG:
 * LOG: Revision 1.8  1998/04/08 19:44:28  ite
 * LOG: For now, only send one SCCP IE for management messages (SCMG).
 * LOG:
 * LOG: Revision 1.7  1998/04/07 15:41:56  mmiers
 * LOG: Remove error text function from vendor library (event.c).
 * LOG:
 * LOG: Add reception of sccp messages (sccp.c).  Update dsp file to reflect
 * LOG: death of queue.c.
 * LOG:
 * LOG: Revision 1.6  1998/02/26 22:24:19  mmiers
 * LOG: Add primitives for SCCP message passing.
 * LOG:
 * LOG: Revision 1.5  1998/02/26 18:46:53  mmiers
 * LOG: Add SCCP notifications to the event handling.
 * LOG:
 * LOG: Revision 1.4  1998/02/26 15:45:58  mmiers
 * LOG: Modifications to bring NMS signatures in line with everyone else.  INI files
 * LOG: are now read for the initial parameters (sapid, srcInst, boardNum, etc).
 * LOG:
 * LOG: Revision 1.3  1998/02/06 15:37:51  ite
 * LOG: Build after modifying its headers.
 * LOG:
 * LOG: Revision 1.2  1998/01/27 15:41:43  mmiers
 * LOG: NMS baseline for ITS
 * LOG:
 * LOG: Revision 1.1  1998/01/24 22:34:28  mmiers
 * LOG: Add SCCP functions for IntelliSS7 on NMS.
 * LOG:
 * LOG: Revision 1.1  1998/01/24 20:25:00  mmiers
 * LOG: Add vendor dependent SCCP library.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:27  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:48:35  rsonak
 * LOG: Baseline port.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <its_intern.h>

#if defined(INCLUDE_SCCP)

#include <its_mlist.h>
#include <its_ss7_trans.h>

#if defined (UNIX)
#include <unistd.h>
#elif defined (WIN32)
#include <windows.h>
#include <winbase.h>
#include <io.h>
#include <fcntl.h>
#endif

#include <sys/types.h>

#if defined (UNIX)
#include <sys/kernel.h>
#endif

/*
 * back compat
 */
#define oPc	opc

extern int nms_debug;
extern int nms_errno;

/* 
 * Callback Manager
 */
extern CALLBACK_Manager*   SCCP_ManagementCallbacks;
extern CALLBACK_Manager*   MTP3_ManagementCallbacks;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert from NMS SCCP addr to ours
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
static void
DecodeSccpAddr(SCCP_ADDR *addr, SccpAddr *naddr)
{
    int index = 0;

    if (naddr->presInd == NOT_PRESENT)
    {
        addr->len = 0;

        return;
    }

    addr->data[0] = 0;
    addr->len = 1;

#if defined(CCITT)
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

#elif defined(ANSI)
    if (naddr->subsystemInd == SUBSYS_INC)
    {
        addr->data[0] |= SCCP_CPA_HAS_SSN;
        SCCP_SET_SSN(&addr->data[addr->len], naddr->subsystem);
        addr->len++;
    }

    if (naddr->pointCodeInd == PTCODE_INC)
    {
        addr->data[0] |= SCCP_CPA_HAS_PC;
        SCCP_ANSI_SET_PC(&addr->data[addr->len], naddr->pointCode);
        addr->len += 3;
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
static void
BuildSccpAddr(SCCP_ADDR *addr, SccpAddr *naddr)
{
    ITS_OCTET *pc = NULL, *ssn = NULL, *gtti = NULL;
    int g = 0;
#if defined(CCITT)
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

        switch (addr->data[0] & SCCP_CPA_GTTI_MASK)
        {
            g = 1;
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
            naddr->glTitleLen = addr->len - (g + 1);
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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
            naddr->glTitleLen = addr->len - (g + 1);
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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
            naddr->glTitleLen = addr->len - (g + 1);
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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
            naddr->glTitleLen = addr->len - (g + 1);
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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

#elif defined(ANSI)
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
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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
            if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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
        if (naddr->glTitleLen > 0 && naddr->glTitleLen < MAX_GLT_SZ)
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
DoEncode(ITS_SCCP_IE* ies, int ieCount, ITS_OCTET mType,
         ITS_EVENT *ev, SCCP_MSG_DESC* desc,
         MTP3_HEADER* mtp3)
{
    int ret;

#if defined(STANDALONE) || defined(WITH_TOOLKIT)
    ITS_HDR hdr;

    ret = SCCP_Encode(ies, ieCount, mType,
                      ev, &hdr, desc);
#else
    ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT len;

    ret = SCCP_EncodeMTP3(buf, &len, mType,
                          ies, ieCount, desc);

    if (ret == ITS_SUCCESS)
    {
        ret = MTP3_Encode(ev, MTP3_MSG_USER_DATA, mtp3,
                          buf, len);
    }
#endif

    return (ret);
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
NMSInitializeSCCP(ITS_SS7_HANDLE handl)
{
    S16       retval = !SCCP_SUCCESS;
    U8        boardNum;
    S16       sapid;
    S16       servUserId;
    U8        ssn;
    U8        srcEnt;
    U8        srcInst;
    U8        type;
    ITS_SS7_CONTEXT *context;
    int       i;
    
    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;
    sapid = context->sapid;
    servUserId = context->servUserId;
    srcEnt = context->srcEnt;
    srcInst = context->srcInst;
    type = context->type;

    if ((context->sccpFD = SCCPInitAPI(boardNum,
                                      srcEnt,
                                      srcInst)) < 0)
    {
        nms_errno = retval;

        return (ITS_ENOPROXY);
    }

    /* get a synchronization handle for this board */
    if ((context->sccpSync = SCCPSyncObj(context->sccpFD,
                                         &retval)) == OS_NULL_HSYNC)
    {
        nms_errno = retval;

        return (ITS_ENOPROXY);
    }

    /* now bind to the SAP */
    for (i = 0; i < context->maxSubs; i++)
    {
        ssn = context->ssn[i];
        if ((retval = SCCPBindRqst(boardNum, srcEnt, srcInst,
                                   servUserId, sapid,
                                   ssn, type)) != SCCP_SUCCESS)
        {
            nms_errno = retval;

            return (ITS_ENOPROXY);
        }

        SCCPStateRqst(boardNum, sapid, ssn, SS_OOS);
        SCCPStateRqst(boardNum, sapid, ssn, SS_IS);
    }

#if defined(STANDALONE) || defined(WITH_TOOLKIT)

    /* Initialize SCCP and MTP3 callback Management */ 
    SCCP_ManagementCallbacks =
        (CALLBACK_Manager *)calloc(1, sizeof(CALLBACK_Manager));
    if (SCCP_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quiting...");
        return (int)NULL;
    }

    if (CALLBACK_InitManager(SCCP_ManagementCallbacks) != ITS_SUCCESS)
    {
        printf("\n Could not create SCCP Callback structure, quiting...");
        free(SCCP_ManagementCallbacks);
        return (int)NULL;
    }

    MTP3_ManagementCallbacks =
        (CALLBACK_Manager *)calloc(1, sizeof(CALLBACK_Manager));
    if (MTP3_ManagementCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quiting...");
        return (int)NULL;
    }

    if (CALLBACK_InitManager(MTP3_ManagementCallbacks) != ITS_SUCCESS)
    {
        printf("\n Could not create MTP3 Callback structure, quiting...");
        free(MTP3_ManagementCallbacks);
        return (int)NULL;
    }

#endif

    return (ITS_SUCCESS);
}

/*.implementation:static
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
NMSTermSCCP(ITS_SS7_HANDLE handl)
{
    S16     retval = !SCCP_SUCCESS;
    U8      boardNum;
    U8      srcEnt;
    U8      srcInst;
    S16     sapid;
    ITS_SS7_CONTEXT *context;

    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;
    sapid = context->sapid;
    srcEnt = context->srcEnt;
    srcInst = context->srcInst;

    if ((retval = SCCPUnbindRqst(boardNum, srcEnt, srcInst,
                                 sapid, 0)) != SCCP_SUCCESS)
    {
        nms_errno = retval;

        return (ITS_ENOPROXY);
    }

    if ((retval = SCCPTermAPI(context->sccpFD)) != SCCP_SUCCESS)
    {
        nms_errno = retval;

        return (ITS_ENOPROXY);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
NMSRetrieveSCCPMessage(ITS_SS7_HANDLE handl)
{
    SccpRcvInfoBlk infoBlk;
    SccpAllMsgs msg;
    S16 retval;
    U8 boardNum;
    ITS_EVENT ev;
    ITS_SCCP_IE ies[ITS_MAX_SCCP_IES];
    int ieCount;
    int ret;
    MTP3_HEADER mtp3;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handl;
    MTP3_PAUSE_RESUME pr;

    boardNum = context->boardNum;

    memset(&msg, 0, sizeof(msg));
    memset(&mtp3, 0, sizeof(MTP3_HEADER));

    /* get SCCP message from API */
    if ((retval = SCCPRetrieveMessage(context->sccpFD, &msg,
                                      &infoBlk, ITS_FALSE)) != SCCP_SUCCESS)
    {
        if (nms_debug)
        {
            printf("SCCPRetrieveMessage was unsuccessful.\n");
            fflush(stdout);
        }

        return (ITS_ENOMSG);
    }

    if (nms_debug)
    {
        printf("SCCPRetrieveMessage: type %d\n", infoBlk.evntType);
        fflush(stdout);
    }

    MTP3_RL_SET_OPC_VALUE(mtp3.label, infoBlk.opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, context->opc);
    MTP3_RL_SET_SLS(mtp3.label, 0);

    switch (infoBlk.indType)
    {
    case SCCPCONNCFM:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_DEST_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.destinationLocalReference;

        ies[2].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[2].param_length = sizeof(SCCP_REF_NUM);
        ies[2].param_data.sourceLocalReference;

        ies[3].param_id = SCCP_PRM_PROTOCOL_CLASS;
        ies[3].param_length = sizeof(SCCP_PROT_CLASS);
        ies[3].param_data.protocolClass.pclass =
            msg.connRqst.protoClass.classInd |
            (msg.connRqst.protoClass.msgHandling << 4);

        ieCount = 4;

        if (msg.connRqst.protoClass.classInd == SCCP_CLASS3)
        {
            ies[ieCount].param_id = SCCP_PRM_CREDIT;
            ies[ieCount].param_length = sizeof(SCCP_CREDIT);
            ies[ieCount].param_data.credit.win_size =
                msg.connRqst.credit;

            ieCount++;
        }

        if (msg.connRqst.calledPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.calledPartyAddr,
                           &msg.connRqst.calledPty);
            ieCount++;
        }

        if (msg.connRqst.callingPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.callingPartyAddr,
                           &msg.connRqst.callingPty);
            ieCount++;
        }

        if (msg.connRqst.data.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_DATA;
            ies[ieCount].param_length = (ITS_OCTET)msg.connRqst.data.dataLen;
            memcpy(ies[ieCount].param_data.userData.data,
                   msg.connRqst.data.data,
                   ies[ieCount].param_length);
            ieCount++;
        }

        ret = DoEncode(ies, ieCount, SCCP_MSG_CC,
                       &ev, &SCCP_CC_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPCONNIND:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.sourceLocalReference;

        ies[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        ies[2].param_length = sizeof(SCCP_PROT_CLASS);
        ies[2].param_data.protocolClass.pclass =
            msg.connRqst.protoClass.classInd |
            (msg.connRqst.protoClass.msgHandling << 4);

        ieCount = 3;

        if (msg.connRqst.protoClass.classInd == SCCP_CLASS3)
        {
            ies[ieCount].param_id = SCCP_PRM_CREDIT;
            ies[ieCount].param_length = sizeof(SCCP_CREDIT);
            ies[ieCount].param_data.credit.win_size =
                msg.connRqst.credit;

            ieCount++;
        }

        if (msg.connRqst.calledPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.calledPartyAddr,
                           &msg.connRqst.calledPty);
            ieCount++;
        }

        if (msg.connRqst.callingPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.callingPartyAddr,
                           &msg.connRqst.callingPty);
            ieCount++;
        }

        if (msg.connRqst.data.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_DATA;
            ies[ieCount].param_length = (ITS_OCTET)msg.connRqst.data.dataLen;
            memcpy(ies[ieCount].param_data.userData.data,
                   msg.connRqst.data.data,
                   ies[ieCount].param_length);
            ieCount++;
        }

        ret = DoEncode(ies, ieCount, SCCP_MSG_CR,
                       &ev, &SCCP_CR_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPRELIND:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.sourceLocalReference;

        ies[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        ies[2].param_length = sizeof(SCCP_PROT_CLASS);
        ies[2].param_data.protocolClass.pclass =
            msg.connRqst.protoClass.classInd |
            (msg.connRqst.protoClass.msgHandling << 4);

        ieCount = 3;

        if (msg.connRqst.protoClass.classInd == SCCP_CLASS3)
        {
            ies[ieCount].param_id = SCCP_PRM_CREDIT;
            ies[ieCount].param_length = sizeof(SCCP_CREDIT);
            ies[ieCount].param_data.credit.win_size =
                msg.connRqst.credit;

            ieCount++;
        }

        if (msg.connRqst.calledPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.calledPartyAddr,
                           &msg.connRqst.calledPty);
            ieCount++;
        }

        if (msg.connRqst.callingPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.callingPartyAddr,
                           &msg.connRqst.callingPty);
            ieCount++;
        }

        if (msg.connRqst.data.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_DATA;
            ies[ieCount].param_length = (ITS_OCTET)msg.connRqst.data.dataLen;
            memcpy(ies[ieCount].param_data.userData.data,
                   msg.connRqst.data.data,
                   ies[ieCount].param_length);
            ieCount++;
        }

        ret = DoEncode(ies, ieCount, SCCP_MSG_RLSD,
                       &ev, &SCCP_RLSD_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPDATIND:
        if (nms_debug)
        {
            printf("SCCPRetrieveMessage returned DATIND.\n");
            fflush(stdout);
        }

        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_DEST_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.destinationLocalReference;

        ieCount = 2;

        if (msg.dataRqst.data.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_DATA;
            ies[ieCount].param_length = (ITS_OCTET)msg.dataRqst.data.dataLen;
            memcpy(ies[ieCount].param_data.userData.data,
                   msg.dataRqst.data.data,
                   ies[ieCount].param_length);
            ieCount++;
        }
        ret = DoEncode(ies, ieCount, SCCP_MSG_DT1,
                       &ev, &SCCP_DT1_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPUDATIND:
        if (nms_debug)
        {
            printf("SCCPRetrieveMessage returned UDATIND.\n");
            fflush(stdout);
        }

        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_PROTOCOL_CLASS;
        ies[1].param_length = sizeof(SCCP_PROT_CLASS);
        ies[1].param_data.protocolClass.pclass =
            msg.udataRqst.protoClass.classInd |
            (msg.udataRqst.protoClass.msgHandling << 4);

        ieCount = 2;

        if (msg.udataRqst.calledPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.calledPartyAddr,
                           &msg.udataRqst.calledPty);
            ieCount++;
        }

        if (msg.udataRqst.callingPty.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
            ies[ieCount].param_length = sizeof(SCCP_ADDR);
            DecodeSccpAddr(&ies[ieCount].param_data.callingPartyAddr,
                           &msg.udataRqst.callingPty);
            ieCount++;
        }

        if (msg.udataRqst.data.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_DATA;
            ies[ieCount].param_length = (ITS_OCTET)msg.udataRqst.data.dataLen;
            memcpy(ies[ieCount].param_data.userData.data,
                   msg.udataRqst.data.data,
                   ies[ieCount].param_length);
            ieCount++;
        }

        ret = DoEncode(ies, ieCount, SCCP_MSG_UDT,
                       &ev, &SCCP_UDT_Desc, &mtp3);

        if (nms_debug)
        {
            printf("SCCPRetrieveMessage encode1 ok.\n");
            fflush(stdout);
        }

        if (ret == ITS_SUCCESS)
        {
            if (nms_debug)
            {
                printf("SCCPRetrieveMessage msg enqueued.\n");
                fflush(stdout);
            }

            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPEDATIND:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_DEST_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.destinationLocalReference;

        ieCount = 2;

        if (msg.dataRqst.data.presInd == PRESENT)
        {
            ies[ieCount].param_id = SCCP_PRM_DATA;
            ies[ieCount].param_length = (ITS_OCTET)msg.dataRqst.data.dataLen;
            memcpy(ies[ieCount].param_data.userData.data,
                   msg.dataRqst.data.data,
                   ies[ieCount].param_length);
            ieCount++;
        }

        ret = DoEncode(ies, ieCount, SCCP_MSG_ED,
                       &ev, &SCCP_ED_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPDACKIND:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_DEST_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.destinationLocalReference;

        ies[2].param_id = SCCP_PRM_RCV_SEQ_NUM;
        ies[2].param_length = sizeof(SCCP_RSN);
        ies[2].param_data.receivedSequenceNumber;

        ieCount = 3;

        ies[ieCount].param_id = SCCP_PRM_CREDIT;
        ies[ieCount].param_length = sizeof(SCCP_CREDIT);
        ies[ieCount].param_data.credit.win_size =
            msg.connRqst.credit;

        ieCount++;

        ret = DoEncode(ies, ieCount, SCCP_MSG_AK,
                       &ev, &SCCP_AK_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPRESETCFM:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_DEST_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.destinationLocalReference;

        ies[2].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[2].param_length = sizeof(SCCP_REF_NUM);
        ies[2].param_data.sourceLocalReference;

        ies[3].param_id = SCCP_PRM_PROTOCOL_CLASS;
        ies[3].param_length = sizeof(SCCP_PROT_CLASS);
        ies[3].param_data.protocolClass.pclass =
            msg.connRqst.protoClass.classInd |
            (msg.connRqst.protoClass.msgHandling << 4);

        ieCount = 4;

        ret = DoEncode(ies, ieCount, SCCP_MSG_RSC,
                       &ev, &SCCP_RSC_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPRESETIND:
        ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[0].param_length = sizeof(MTP3_HEADER);
        ies[0].param_data.routingLabel = mtp3;

        ies[1].param_id = SCCP_PRM_DEST_LOCAL_REF;
        ies[1].param_length = sizeof(SCCP_REF_NUM);
        ies[1].param_data.destinationLocalReference;

        ies[2].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[2].param_length = sizeof(SCCP_REF_NUM);
        ies[2].param_data.sourceLocalReference;

        ies[3].param_id = SCCP_PRM_RESET_CAUSE;
        ies[3].param_length = sizeof(SCCP_RES_CAUSE);
        ies[3].param_data.resetCause.cause;

        ieCount = 4;

        ret = DoEncode(ies, ieCount, SCCP_MSG_RSR,
                       &ev, &SCCP_RSR_Desc, &mtp3);

        if (ret == ITS_SUCCESS)
        {
            MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
        }

        break;

    case SCCPSTAIND:
    case SCCPCOORDIND:
    case SCCPCOORDCFM:
    case SCCPSTATEIND:    
        if (nms_debug)
        {
            printf("SCCPRetrieveMessage got one that we don't handle.\n");
            fflush(stdout);
        }
        break;

    case SCCPPCSTIND:

        if (msg.coordRqst.status == SP_INACC)
        {
            memset(&pr, 0, sizeof(MTP3_PAUSE_RESUME));

            MTP3_PC_SET_VALUE(pr.affected, infoBlk.oPc);

            MTP3_Encode(&ev, MTP3_MSG_PAUSE, &mtp3,
                        (ITS_OCTET *)&pr, sizeof(MTP3_PAUSE_RESUME));
        }
        else if (msg.coordRqst.status == SP_ACC)
        {
            memset(&pr, 0, sizeof(MTP3_PAUSE_RESUME));

            MTP3_PC_SET_VALUE(pr.affected, infoBlk.oPc);

            MTP3_Encode(&ev, MTP3_MSG_RESUME, &mtp3,
                        (ITS_OCTET *)&pr, sizeof(MTP3_PAUSE_RESUME));
        }
        else
        {
            return (ITS_ENOMSG);
        }

        MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));        


    default:
        if (nms_debug)
        {
            printf("SCCPRetrieveMessage got unknown one.\n");
            fflush(stdout);
        }
        ret = ITS_ENOMSG;
        break;
    }

    return (ret);
}

/*.implementation:extern
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
NMSSendSCCPEvent(ITS_SS7_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
                 ITS_SCCP_IE* ies, int ieCount, SCCP_MSG_DESC* desc)
{
    U8 board;
    int ret, i, dlen;
    SccpConnId connId;
    SccpConnRqst connRqst;
    SccpReleased relRqst;
    SccpDataRqst dataRqst;
    SccpDAckRqst dackRqst;
    SccpResetRqst resRqst;
    SccpUdataRqst udataRqst;
    SCCP_REF_NUM *slref = NULL, *dlref = NULL;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    SCCP_CREDIT *credit = NULL;
    SCCP_PROT_CLASS *pclass = NULL;
    SCCP_DATA *data = NULL;
    SCCP_RSN *rsn = NULL;
    SCCP_REF_CAUSE *refc = NULL;
    SCCP_RES_CAUSE *resc = NULL;
    SCCP_REL_CAUSE *relc = NULL;
    SCCP_ERR_CAUSE *errc = NULL;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handl;

#if !defined(STANDALONE) && !defined(WITH_TOOLKIT)
    ITS_EVENT ev;

    /* make sure everything's there */
    if ((ret = SCCP_Encode(ies, ieCount, type,
                           &ev, hdr, desc)) != ITS_SUCCESS)
    {
        return (ret);
    }
#endif

    board = context->boardNum;

    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_DEST_LOCAL_REF:
            dlref = &ies[i].param_data.destinationLocalReference;
            break;

        case SCCP_PRM_SRC_LOCAL_REF:
            slref = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_CALLING_PARTY_ADDR:
            clp = &ies[i].param_data.callingPartyAddr;
            break;

        case SCCP_PRM_CREDIT:
            credit = &ies[i].param_data.credit;
            break;

        case SCCP_PRM_DATA:
            data = &ies[i].param_data.userData;
            dlen = ies[i].param_length;
            break;

        case SCCP_PRM_PROTOCOL_CLASS:
            pclass = &ies[i].param_data.protocolClass;
            break;

        case SCCP_PRM_RCV_SEQ_NUM:
            rsn = &ies[i].param_data.receivedSequenceNumber;
            break;

        case SCCP_PRM_RESET_CAUSE:
            resc = &ies[i].param_data.resetCause;
            break;

        case SCCP_PRM_REFUSAL_CAUSE:
            refc = &ies[i].param_data.refusalCause;
            break;

        case SCCP_PRM_RELEASE_CAUSE:
            relc = &ies[i].param_data.releaseCause;
            break;

        case SCCP_PRM_ERROR_CAUSE:
            errc = &ies[i].param_data.errorCause;
            break;
        }
    }

    connId.suId = context->servUserId;
    connId.spId = context->sapid;
    connId.suConnId = hdr->context.conref;
    connId.spConnId = 0;

    switch (type)
    {
    case SCCP_MSG_CR:
        assert(pclass != NULL && cdp != NULL);

        memset(&connRqst, 0, sizeof(connRqst));

        BuildSccpAddr(cdp, &connRqst.calledPty);
        if (clp)
        {
            BuildSccpAddr(clp, &connRqst.callingPty);
        }
        connRqst.protoClass.classInd = pclass->pclass & SCCP_PCLASS_MASK;
        connRqst.protoClass.msgHandling = (pclass->pclass >> 4);

        if (credit)
        {
            connRqst.credit = credit->win_size;
        }

        connRqst.rcs = RCS_REQ;
        connRqst.eds = EDS_NONE;

        if (data)
        {
            connRqst.data.presInd = PRESENT;
            connRqst.data.dataLen = dlen;
            memcpy(connRqst.data.data, data->data, dlen);
        }

        if (slref)
        {
            connId.suConnId = RN_GET_REF_NUM(*slref);
        }

        ret = SCCPConnectRqst(board, &connId, &connRqst);
        break;

    case SCCP_MSG_CC:
        assert(pclass != NULL && cdp != NULL);

        memset(&connRqst, 0, sizeof(connRqst));

        BuildSccpAddr(cdp, &connRqst.calledPty);
        if (clp)
        {
            BuildSccpAddr(clp, &connRqst.callingPty);
        }
        connRqst.protoClass.classInd = pclass->pclass & SCCP_PCLASS_MASK;
        connRqst.protoClass.msgHandling = (pclass->pclass >> 4);

        if (credit)
        {
            connRqst.credit = credit->win_size;
        }

        connRqst.rcs = RCS_REQ;
        connRqst.eds = EDS_NONE;

        if (data)
        {
            connRqst.data.presInd = PRESENT;
            connRqst.data.dataLen = dlen;
            memcpy(connRqst.data.data, data->data, dlen);
        }

        if (slref)
        {
            connId.suConnId = RN_GET_REF_NUM(*slref);
        }
        
        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }

        ret = SCCPConnectResp(board, &connId, &connRqst);
        break;

    case SCCP_MSG_CREF:
        memset(&relRqst, 0, sizeof(relRqst));

        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }

        if (refc)
        {
            relRqst.relCause = refc->cause;
        }
        relRqst.relOrig = ORIGENDUSER;

        if (data)
        {
            relRqst.data.presInd = PRESENT;
            relRqst.data.dataLen = dlen;
            memcpy(relRqst.data.data, data->data, dlen);
        }

        ret = SCCPReleaseRqst(board, &connId, &relRqst);
        break;

    case SCCP_MSG_RLSD:
        memset(&relRqst, 0, sizeof(relRqst));

        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        if (slref)
        {
            connId.suConnId = RN_GET_REF_NUM(*slref);
        }

        if (relc)
        {
            relRqst.relCause = relc->cause;
        }
        relRqst.relOrig = ORIGENDUSER;

        if (data)
        {
            relRqst.data.presInd = PRESENT;
            relRqst.data.dataLen = dlen;
            memcpy(relRqst.data.data, data->data, dlen);
        }

        ret = SCCPReleaseRqst(board, &connId, &relRqst);
        break;

    case SCCP_MSG_RLC:
        /* discard */
        ret = SCCP_SUCCESS;
        break;

    case SCCP_MSG_DT1:
        memset(&dataRqst, 0, sizeof(dataRqst));

        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        if (data)
        {
            dataRqst.data.presInd = PRESENT;
            dataRqst.data.dataLen = dlen;
            memcpy(dataRqst.data.data, data->data, dlen);
        }

        ret = SCCPDataRqst(board, &connId, &dataRqst);
        break;

    case SCCP_MSG_DT2:
        memset(&dataRqst, 0, sizeof(dataRqst));

        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        if (data)
        {
            dataRqst.data.presInd = PRESENT;
            dataRqst.data.dataLen = dlen;
            memcpy(dataRqst.data.data, data->data, dlen);
        }

        ret = SCCPDataRqst(board, &connId, &dataRqst);
        break;

    case SCCP_MSG_AK:
        if (credit)
        {
            dackRqst.credit = credit->win_size;
        }

        if (rsn)
        {
            dackRqst.rsn = rsn->rsn;
        }

        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        ret = SCCPDAckRqst(board, &connId, &dackRqst);
        break;

    case SCCP_MSG_UDT:
        assert(pclass != NULL && cdp != NULL);

        memset(&udataRqst, 0, sizeof(udataRqst));

        BuildSccpAddr(cdp, &udataRqst.calledPty);
        if (clp)
        {
            BuildSccpAddr(clp, &udataRqst.callingPty);
        }
        udataRqst.protoClass.classInd = pclass->pclass & SCCP_PCLASS_MASK;
        udataRqst.protoClass.msgHandling = (pclass->pclass >> 4);

        if (data)
        {
            udataRqst.data.presInd = PRESENT;
            udataRqst.data.dataLen = dlen;
            memcpy(udataRqst.data.data, data->data, dlen);
        }

        ret = SCCPUDataRqst(board, context->sapid, &udataRqst);
        break;

    case SCCP_MSG_XUDT:
        assert(pclass != NULL && cdp != NULL);

        memset(&udataRqst, 0, sizeof(udataRqst));

        BuildSccpAddr(cdp, &udataRqst.calledPty);
        if (clp)
        {
            BuildSccpAddr(clp, &udataRqst.callingPty);
        }
        udataRqst.protoClass.classInd = pclass->pclass & SCCP_PCLASS_MASK;
        udataRqst.protoClass.msgHandling = (pclass->pclass >> 4);

        if (data)
        {
            udataRqst.data.presInd = PRESENT;
            udataRqst.data.dataLen = dlen;
            memcpy(udataRqst.data.data, data->data, dlen);
        }

        ret = SCCPUDataRqst(board, context->sapid, &udataRqst);
        break;

    case SCCP_MSG_UDTS:
        /* discard */
        ret = SCCP_SUCCESS;
        break;

    case SCCP_MSG_XUDTS:
        /* discard */
        ret = SCCP_SUCCESS;
        break;

    case SCCP_MSG_ED:
        memset(&dataRqst, 0, sizeof(dataRqst));

        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        if (data)
        {
            dataRqst.data.presInd = PRESENT;
            dataRqst.data.dataLen = dlen;
            memcpy(udataRqst.data.data, data->data, dlen);
        }

        ret = SCCPEDataRqst(board, &connId, &dataRqst);
        break;

    case SCCP_MSG_EA:
        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        ret = SCCPDAckRqst(board, &connId, &dackRqst);
        break;

    case SCCP_MSG_RSR:
        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }

        if (resc)
        {
            resRqst.resCause = resc->cause;
        }
        resRqst.resOrig = ORIGENDUSER;

        ret = SCCPResetRqst(board, &connId, &resRqst);
        break;

    case SCCP_MSG_RSC:
        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        ret = SCCPResetResp(board, &connId);
        break;

    case SCCP_MSG_ERR:
        if (dlref)
        {
            connId.spConnId = RN_GET_REF_NUM(*dlref);
        }
        
        if (errc)
        {
            relRqst.relCause = errc->cause;
        }
        relRqst.relOrig = ORIGENDUSER;

        ret = SCCPReleaseRqst(board, &connId, &relRqst);
        break;

    case SCCP_MSG_IT:
        /* discard */
        ret = SCCP_SUCCESS;
        break;

    default:
        break;
    }

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
NMSSendUserOutOfService(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                        ITS_UINT pc, ITS_OCTET ssn)
{
    S16  retval;
    U8   boardNum;
    S16  sapid;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handle;

    boardNum = context->boardNum;
    sapid = context->sapid;

    if ((retval = SCCPStateRqst(boardNum, sapid,
                                (U8)ssn, SS_OOS)) != SCCP_SUCCESS)
    {
        printf("\n SCCPStateReq return val = %d.", retval);

        return(retval);
    }

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
NMSSendUserInService(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                     ITS_UINT pc, ITS_OCTET ssn)
{
    S16  retval;
    U8   boardNum;
    S16  sapid;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handle;
    
    boardNum = context->boardNum;
    sapid = context->sapid;

    if ((retval = SCCPStateRqst(boardNum, sapid,
                                (U8)ssn, SS_IS)) != SCCP_SUCCESS)
    {
        printf("\n TCAPStateReq return val = %d.", retval);

        return(retval);
    }

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
NMSSetCongestion(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                 ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
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
NMSGetNextLocalRef(ITS_USHORT *did)
{
    static ITS_USHORT nextRef = 0;

    /*
     * keep it simple for now.  This needs to have some context to
     * be done correctly.
     */
    nextRef++;
    if (nextRef == 0x8000)
    {
        nextRef = 1;
    }
    
    *did = nextRef;

    return (ITS_SUCCESS);
}

#endif /* INCLUDE_SCCP */
