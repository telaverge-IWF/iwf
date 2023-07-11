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
 *  ID: $Id: sendISUPMsg.h,v 9.1 2005/03/23 12:56:18 cvsadmin Exp $
 *
 * LOG: $Log: sendISUPMsg.h,v $
 * LOG: Revision 9.1  2005/03/23 12:56:18  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:45  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:10  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:06  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/09/05 20:59:29  mmiers
 * LOG: Move the 3.5 test.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:43  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:08  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 1.1  2000/12/11 23:14:38  hxing
 * LOG: Add testing files
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:15  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.4  2000/07/31 21:39:17  hxing
 * LOG: Testing more ies and more messages
 * LOG:
 * LOG: Revision 1.3  2000/07/17 22:37:46  hxing
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2000/07/17 20:17:23  hxing
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:37  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _SEND_ISUP_MSG_H_
#define _SEND_ISUP_MSG_H_

#include <its.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


#ifdef ANSI
#define FILENAME        "ansi_msgs.txt"
#else
#define FILENAME        "ccitt_msgs.txt"
#endif


char* GetFilename();

int TestSendACMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendANMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendBLARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendBLORequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCCRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCFNRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGBRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGBARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGURequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCOTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCPGRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCQMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFOTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendGRARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendGRSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendINFRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendINRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendLPARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendPAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRELRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRESRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRSCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSUSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUBLRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUBARequest(ITS_HANDLE handle, ITS_HDR *hdr);


#ifdef ANSI

int TestSendCRARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCRMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCVRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCVTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendEXMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif



#ifdef CCITT

int TestSendCONRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFAARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFACRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFARRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFRJRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIDRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIRSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendNRMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendOLMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSGMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUPARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUPTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUSRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* _SEND_ISUP_MSG_H_ */


