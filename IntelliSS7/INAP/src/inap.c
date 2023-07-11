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
 *  ID: $Id: inap.c,v 9.1 2005/03/23 12:51:42 cvsadmin Exp $
 *
 * LOG: $Log: inap.c,v $
 * LOG: Revision 9.1  2005/03/23 12:51:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:33  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:04  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:53  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:50  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.20  1999/07/14 14:01:01  cbascon
 * LOG: no message
 * LOG:
 * LOG: Revision 1.19  1999/07/14 13:51:13  cbascon
 * LOG: no message
 * LOG:
 * LOG: Revision 1.18  1999/07/13 23:31:35  cbascon
 * LOG: Added helper functions for RequestCurrentStatusReportResult
 * LOG:
 * LOG: Revision 1.17  1999/07/12 20:32:09  skarmakar
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.16  1999/06/16 19:28:37  jpakrasi
 * LOG: Added comments into the function headers to generate html docs. Details
 * LOG: of parameters need to be added later.
 * LOG:
 * LOG: Revision 1.15  1999/06/14 17:20:14  fhasle
 * LOG: added DEBUG check.
 * LOG:
 * LOG: Revision 1.14  1999/05/24 16:42:57  mmiers
 * LOG:
 * LOG:
 * LOG: Finalize API.
 * LOG:
 * LOG: Revision 1.13  1999/03/15 17:31:56  mmiers
 * LOG:
 * LOG:
 * LOG: Add license checks in.
 * LOG:
 * LOG: Revision 1.12  1999/03/02 22:47:46  mmiers
 * LOG:
 * LOG:
 * LOG: Update for new TCAP operation name.
 * LOG:
 * LOG: Revision 1.11  1999/03/02 22:08:37  mmiers
 * LOG:
 * LOG:
 * LOG: Update for prototypes.
 * LOG:
 * LOG: Revision 1.10.2.1  1999/03/02 21:42:05  mmiers
 * LOG:
 * LOG:
 * LOG: Continue release preparation cleanup.
 * LOG:
 * LOG: Revision 1.10  1998/10/21 18:44:12  mmiers
 * LOG: Remove genreated files.
 * LOG:
 * LOG: Revision 1.9  1998/07/02 14:06:21  mmiers
 * LOG: Get rid of its_debug everywhere.
 * LOG:
 * LOG: Revision 1.8  1998/05/21 02:15:25  mmiers
 * LOG: General cleanup to reflect TCAP changes (INAP, IS41).  Some missing
 * LOG: files in builds.  Update the test to include the SCCP library.  I'll
 * LOG: have to modify TCAP tomorrow to use SCCP_SendEvent instead of
 * LOG: TRANSPORT_PutEvent().  Less efficient, but more useable with someone
 * LOG: else's SCCP.
 * LOG:
 * LOG: Revision 1.7  1998/05/04 22:57:32  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.6  1998/05/04 21:14:26  mmiers
 * LOG: Work on IS634.
 * LOG:
 * LOG: Revision 1.5  1998/05/01 14:22:11  mmiers
 * LOG: Clean up existing workspaces, add IS634 workspace.
 * LOG:
 * LOG: Revision 1.4  1998/04/24 01:41:29  mmiers
 * LOG: General cleanup of the build system.  Need to verify on Digital Unix
 * LOG: to make sure this is ok.
 * LOG:
 * LOG: Revision 1.3  1998/02/05 15:50:23  mmiers
 * LOG: Fixup.
 * LOG:
 * LOG: Revision 1.2  1998/02/05 15:39:06  mmiers
 * LOG: Update for cleanup.
 * LOG:
 * LOG: Revision 1.1  1998/02/05 15:30:47  mmiers
 * LOG: Cleaning up the tree.  The inap library had disappeared, add it back.
 * LOG: Move the test files to the test directory.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <its.h>
#include <its_license.h>

#if defined(CCITT)
#include <itu/sccp.h>
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/sccp.h>
#include <ansi/tcap.h>
#else
#error "Protocol not defined"
#endif

#include <itu/inap.h>
#include <itu/INAP-types.h>

#include <asn-c/AsnC.h>

#ifdef DEBUG
static int local_debug = 1;
#else
static int local_debug = 0;
#endif


/*
 * INAP interface
 */

/*** CALL INFORMATION REQUEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "call information request" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCallInformationRequest();
 *
 ****************************************************************************/
int
INAP_SendCallInformationRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CallInformationRequestArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CallInformationRequestArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CallInformationRequestArg(data);

        return (ITS_BADTCAPMESSAGE);
    }


    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_callInformationRequest;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CallInformationRequestArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "call information request" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CallInformationRequestArg(data);
 *
 *  See Also:
 *      INAP_SendCallInformationRequest();
 *
 ****************************************************************************/
int
INAP_DecodeCallInformationRequest(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CallInformationRequestArg(pe, 1, NULL, NULL,
                                              (char **)data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CallInformationRequestArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** CALL INFORMATION REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "call information report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCallInformationReport();
 *
 ****************************************************************************/
int
INAP_SendCallInformationReport(ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CallInformationReportArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CallInformationReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CallInformationReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }


    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_callInformationReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CallInformationReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "call information request" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CallInformationRequestArg(data);
 *
 *  See Also:
 *      INAP_SendCallInformationRequest();
 *
 ****************************************************************************/
int
INAP_DecodeCallInformationReport(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CallInformationReportArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CallInformationReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** EVENT REPORT BCSM ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "event report BCSM" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeEventReportBCSM();
 *
 ****************************************************************************/
int
INAP_SendEventReportBCSM(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_EventReportBCSMArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_EventReportBCSMArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_EventReportBCSMArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_eventReportBCSM;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_EventReportBCSMArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "event report BCSM" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_EventReportBCSMArg(data);
 *
 *  See Also:
 *      INAP_SendEventReportBCSM();
 *
 ****************************************************************************/
int
INAP_DecodeEventReportBCSM(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_EventReportBCSMArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_EventReportBCSMArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** INITIAL DP ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "initial DP" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeInitialDP();
 *
 ****************************************************************************/
int
INAP_SendInitialDP(ITS_HANDLE handle, ITS_HDR *hdr,
                   TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

    printf("\n INAP: Start in INAP_SendInitialDP\n");
#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif
    printf("\n INAP: After assert.");

    printf("\n INAP: before license verify");

   if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        printf("\n INAP: Error No license");
        return (ITS_ENOLICENSE);
    }

    printf("\n INAP: before encode");
    if (encode_INAP_InitialDPArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        printf("\n INAP: Bad TCAP Message"); 
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        printf("\n INAP: printing InitialDPArg"); 
        print_INAP_InitialDPArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_InitialDPArg(data);
        printf("pe2ssdu returned not OK \n"); 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_initialDP;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);
    printf("TCAP send comp called \n");

    free(enc);

    free_INAP_InitialDPArg(data);

    if (pe)
    {
        pe_free(pe);
    }
    printf("\n INAP: End in INAP_SendInitialDP\n");

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "initial DP" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_InitialDPArg(data);
 *
 *  See Also:
 *      INAP_SendInitialDP();
 *
 ****************************************************************************/
int
INAP_DecodeInitialDP(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_InitialDPArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_InitialDPArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** SERVICE FILTERING RESPONSE ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "service filtering response" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeServiceFilteringResponse();
 *
 ****************************************************************************/
int
INAP_SendServiceFilteringResponse(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ServiceFilteringResponseArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ServiceFilteringResponseArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ServiceFilteringResponseArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_serviceFilteringResponse;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ServiceFilteringResponseArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "service filtering response" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ServiceFilteringResponseArg(data);
 *
 *  See Also:
 *      INAP_SendServiceFilteringResponse();
 *
 ****************************************************************************/
int
INAP_DecodeServiceFilteringResponse(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ServiceFilteringResponseArg(pe, 1, NULL, NULL,
                                                data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ServiceFilteringResponseArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** APPLY CHARGING REQUEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "apply charging request" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeApplyChargingRequest();
 *
 ****************************************************************************/
int
INAP_SendApplyChargingRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ApplyChargingArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ApplyChargingArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ApplyChargingArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_applyCharging;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ApplyChargingArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "apply charging request" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ApplyChargingArg(data);
 *
 *  See Also:
 *      INAP_SendApplyChargingRequest();
 *
 ****************************************************************************/
int
INAP_DecodeApplyChargingRequest(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ApplyChargingArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ApplyChargingArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** APPLY CHARGING REQUEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "apply charging report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeApplyChargingReport();
 *
 ****************************************************************************/
int
INAP_SendApplyChargingReport(ITS_HANDLE handle, ITS_HDR *hdr,
                             TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ApplyChargingReportArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ApplyChargingReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ApplyChargingReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_applyChargingReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ApplyChargingReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "apply charging report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ApplyChargingReportArg(data);
 *
 *  See Also:
 *      INAP_SendApplyChargingReport();
 *
 ****************************************************************************/
int
INAP_DecodeApplyChargingReport(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ApplyChargingReportArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ApplyChargingReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ACTIVATE SERVICE FILTERING ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "activate service filtering" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeActivateServiceFiltering();
 *
 ****************************************************************************/
int
INAP_SendActivateServiceFiltering(ITS_HANDLE handle, ITS_HDR *hdr,
                                 TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ActivateServiceFilteringArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ActivateServiceFilteringArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ActivateServiceFilteringArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_activateServiceFiltering;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ActivateServiceFilteringArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "activate service filtering" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ActivateServiceFilteringArg(data);
 *
 *  See Also:
 *      INAP_SendActivateServiceFiltering();
 *
 ****************************************************************************/
int
INAP_DecodeActivateServiceFiltering(ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ActivateServiceFilteringArg(pe, 1, NULL, NULL,
                                                data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ActivateServiceFilteringArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ACTIVITY TEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "activity test" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeActivityTest();
 *
 ****************************************************************************/
int
INAP_SendActivityTest(ITS_HANDLE handle, ITS_HDR *hdr,
                     TCAP_CPT *cpt, void *data)
{
    int ret;
#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_activityTest;
    cpt->u.invoke.param.len = 0;

    ret = TCAP_SendComponent(handle, hdr, cpt);

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "activity test" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      This function is a NOOP, as the activity test has no argument.  It 
 *      is included only for completeness.
 *
 *  See Also:
 *      INAP_SendActivityTest();
 *
 ****************************************************************************/
int
INAP_DecodeActivityTest(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    int ret = ITS_SUCCESS;

#ifdef DEBUG
    assert((handle != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    /* this is a noop */

    return ret;
}

/*** CALL GAP ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "CallGap" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCallGap();
 *
 ****************************************************************************/
int
INAP_SendCallGap(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CallGapArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CallGapArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CallGapArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_callGap;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CallGapArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "CallGap" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CallGapArg(data);
 *
 *  See Also:
 *      INAP_SendCallGap();
 *
 ****************************************************************************/
int
INAP_DecodeCallGap(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CallGapArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CallGapArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** CANCEL ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "Cancel" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCancel();
 *
 ****************************************************************************/
int
INAP_SendCancel(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CancelArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CancelArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CancelArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_cancel;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CancelArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "cancel" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CancelArg(data);
 *
 *  See Also:
 *      INAP_SendCancel();
 *
 ****************************************************************************/
int
INAP_DecodeCancel(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CancelArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CancelArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** CONNECT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "connect" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeConnect();
 *
 ****************************************************************************/
int
INAP_SendConnect(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ConnectArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ConnectArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ConnectArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_connect;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ConnectArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "connect" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ConnectArg(data);
 *
 *  See Also:
 *      INAP_SendConnect();
 *
 ****************************************************************************/
int
INAP_DecodeConnect(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ConnectArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ConnectArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** CONTINUE ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "continue" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeContinue();
 *
 ****************************************************************************/
int
INAP_SendContinue(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, void *data)
{
    int ret;
#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_continue;
    cpt->u.invoke.param.len = 0;

    ret = TCAP_SendComponent(handle, hdr, cpt);

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "continue" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      This function is a NOOP, as the activity test has no argument.  It 
 *      is included only for completeness.
 *
 *  See Also:
 *      INAP_SendContinue();
 *
 ****************************************************************************/
int
INAP_DecodeContinue(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    int ret = ITS_SUCCESS;
#ifdef DEBUG
    assert((handle != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    /* this is a noop */
    return ret;
}

/*** DISCONNECT FORWARD CONNECTION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "disconnect forward connection" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeDisconnectForwardConnection();
 *
 ****************************************************************************/
int
INAP_SendDisconnectForwardConnection(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data)
{
    int ret;
#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_disconnectForwardConnection;
    cpt->u.invoke.param.len = 0;

    ret = TCAP_SendComponent(handle, hdr, cpt);

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "disconnect forward connection" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CallInformationRequestArg(data);
 *
 *  See Also:
 *      INAP_SendDisconnectForwardConnection();
 *
 ****************************************************************************/
int
INAP_DecodeDisconnectForwardConnection(ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data)
{
    int ret = ITS_SUCCESS;
#ifdef DEBUG
    assert((handle != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    /* this is a noop */
    return ret;
}

/*** ESTABLISH TEMPORARY CONNECTION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "establish temporary connection" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeEstablishTemporaryConnection();
 *
 ****************************************************************************/
int
INAP_SendEstablishTemporaryConnection(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_EstablishTemporaryConnectionArg(&pe, 1, 0,
                                                    NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_EstablishTemporaryConnectionArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_EstablishTemporaryConnectionArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_establishTemporaryConnection;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_EstablishTemporaryConnectionArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "establish temporary connection" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_EstablishTemporaryConnectionArg(data);
 *
 *  See Also:
 *      INAP_SendEstablishTemporaryConnection();
 *
 ****************************************************************************/
int
INAP_DecodeEstablishTemporaryConnection(ITS_HANDLE handle, TCAP_CPT *cpt,
                                       void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_EstablishTemporaryConnectionArg(pe, 1, NULL, NULL,
                                                    data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_EstablishTemporaryConnectionArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** FURNISH CHARGING INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "furnish charging information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeFurnishChargingInformation();
 *
 ****************************************************************************/
int
INAP_SendFurnishChargingInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_FurnishChargingInformationArg(&pe, 1, 0,
                                                  NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_FurnishChargingInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_FurnishChargingInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_furnishChargingInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_FurnishChargingInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "furnish charging information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_FurnishChargingInformationArg(data);
 *
 *  See Also:
 *      INAP_SendFurnishChargingInformation();
 *
 ****************************************************************************/
int
INAP_DecodeFurnishChargingInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_FurnishChargingInformationArg(pe, 1, NULL, NULL,
                                                  data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_FurnishChargingInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** RELEASE CALL ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "release call" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeReleaseCall();
 *
 ****************************************************************************/
int
INAP_SendReleaseCall(ITS_HANDLE handle, ITS_HDR *hdr,
                    TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;
    struct qbuf *qb = (struct qbuf *)data;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ReleaseCallArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ReleaseCallArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ReleaseCallArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_releaseCall;
    /* this is quick: Just strip off the extra before encoding */
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ReleaseCallArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "release call" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ReleaseCallArg(data);
 *
 *  See Also:
 *      INAP_SendReleaseCall();
 *
 ****************************************************************************/
int
INAP_DecodeReleaseCall(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ReleaseCallArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ReleaseCallArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** REQUEST REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "request report BCSM event" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRequestReportBCSMEvent();
 *
 ****************************************************************************/
int
INAP_SendRequestReportBCSMEvent(ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RequestReportBCSMEventArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RequestReportBCSMEventArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RequestReportBCSMEventArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_requestReportBCSMEvent;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RequestReportBCSMEventArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "request report BCSM event" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RequestReportBCSMEventArg(data);
 *
 *  See Also:
 *      INAP_SendRequestReportBCSMEvent();
 *
 ****************************************************************************/
int
INAP_DecodeRequestReportBCSMEvent(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RequestReportBCSMEventArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RequestReportBCSMEventArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** RESET TIMER ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "reset timer" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeResetTimer();
 *
 ****************************************************************************/
int
INAP_SendResetTimer(ITS_HANDLE handle, ITS_HDR *hdr,
                   TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ResetTimerArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ResetTimerArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ResetTimerArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_resetTimer;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ResetTimerArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "reset timer" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ResetTimerArg(data);
 *
 *  See Also:
 *      INAP_SendResetTimer();
 *
 ****************************************************************************/
int
INAP_DecodeResetTimer(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ResetTimerArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ResetTimerArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** CONNECT TO RESOURCE ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "connect to resource" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeConnectToResource();
 *
 ****************************************************************************/
int
INAP_SendConnectToResource(ITS_HANDLE handle, ITS_HDR *hdr,
                          TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ConnectToResourceArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ConnectToResourceArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ConnectToResourceArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_connectToResource;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ConnectToResourceArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "connect to resource" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ConnectToResourceArg(data);
 *
 *  See Also:
 *      INAP_SendConnectToResource();
 *
 ****************************************************************************/
int
INAP_DecodeConnectToResource(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ConnectToResourceArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ConnectToResourceArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** PROMPT AND COLLECT USER INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "prompt and collect user information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodePromptAndCollectUserInformation();
 *
 ****************************************************************************/
int
INAP_SendPromptAndCollectUserInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_PromptAndCollectUserInformation(&pe, 1, 0,
                                                    NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_PromptAndCollectUserInformation(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_PromptAndCollectUserInformation(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_promptAndCollectUserInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_PromptAndCollectUserInformation(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "prompt and collect user information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_PromptAndCollectUserInformation(data);
 *
 *  See Also:
 *      INAP_SendPromptAndCollectUserInformation();
 *
 ****************************************************************************/
int
INAP_DecodePromptAndCollectUserInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_PromptAndCollectUserInformation(pe, 1, NULL, NULL,
                                                    data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_PromptAndCollectUserInformation(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** PROMPT AND COLLECT USER INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "received information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeReceivedInformation();
 *
 ****************************************************************************/
int
INAP_SendReceivedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                            TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ReceivedInformationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ReceivedInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ReceivedInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = INAP_OP_promptAndCollectUserInformation;
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ReceivedInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "received information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ReceivedInformationArg(data);
 *
 *  See Also:
 *      INAP_SendReceivedInformation();
 *
 ****************************************************************************/
int
INAP_DecodeReceivedInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                              void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ReceivedInformationArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ReceivedInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** PLAY ANNOUNCEMENT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "play announcement" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodePlayAnnouncement();
 *
 ****************************************************************************/
int
INAP_SendPlayAnnouncement(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_PlayAnnouncementArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_PlayAnnouncementArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_PlayAnnouncementArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_playAnnouncement;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_PlayAnnouncementArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "play announcement" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_PlayAnnouncementArg(data);
 *
 *  See Also:
 *      INAP_SendPlayAnnouncement();
 *
 ****************************************************************************/
int
INAP_DecodePlayAnnouncement(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_PlayAnnouncementArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_PlayAnnouncementArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ASSIST REQUEST INSTRUCTION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "assist request instructions" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeAssistRequestInstructions();
 *
 ****************************************************************************/
int
INAP_SendAssistRequestInstructions(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_AssistRequestInstructionsArg(&pe, 1, 0,
                                                 NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_AssistRequestInstructionsArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_AssistRequestInstructionsArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_assistRequestInstructions;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_AssistRequestInstructionsArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "assist request instructions" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_AssistRequestInstructionsArg(data);
 *
 *  See Also:
 *      INAP_SendAssistRequestInstructions();
 *
 ****************************************************************************/
int
INAP_DecodeAssistRequestInstructions(ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_AssistRequestInstructionsArg(pe, 1, NULL, NULL,
                                                 data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_AssistRequestInstructionsArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** SPECIALIZED RESOURCE REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "specialized resource report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeSpecializedResourceReport();
 *
 ****************************************************************************/
int
INAP_SendSpecializedResourceReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_SpecializedResourceReportArg(&pe, 1, 0,
                                                 NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_SpecializedResourceReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_SpecializedResourceReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_specializedResourceReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_SpecializedResourceReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "specialized resource report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_SpecializedResourceReportArg(data);
 *
 *  See Also:
 *      INAP_SendSpecializedResourceReport();
 *
 ****************************************************************************/
int
INAP_DecodeSpecializedResourceReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_SpecializedResourceReportArg(pe, 1, NULL, NULL,
                                                 data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_SpecializedResourceReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** INITIATE CALL ATTEMPT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "initiate call attempt" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeInitiateCallAttempt();
 *
 ****************************************************************************/
int
INAP_SendInitiateCallAttempt(ITS_HANDLE handle, ITS_HDR *hdr,
                            TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_InitiateCallAttemptArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_InitiateCallAttemptArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_InitiateCallAttemptArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_initiateCallAttempt;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_InitiateCallAttemptArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "initiate call attempt" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_InitiateCallAttemptArg(data);
 *
 *  See Also:
 *      INAP_SendInitiateCallAttempt();
 *
 ****************************************************************************/
int
INAP_DecodeInitiateCallAttempt(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_InitiateCallAttemptArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_InitiateCallAttemptArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** SEND CHARGING INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "send charging information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeSendChargingInformation();
 *
 ****************************************************************************/
int
INAP_SendSendChargingInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_SendChargingInformationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_SendChargingInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_SendChargingInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_sendChargingInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_SendChargingInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "send charging information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_SendChargingInformationArg(data);
 *
 *  See Also:
 *      INAP_SendSendChargingInformation();
 *
 ****************************************************************************/
int
INAP_DecodeSendChargingInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_SendChargingInformationArg(pe, 1, NULL, NULL,
                                               data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_SendChargingInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** COLLECT INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "collect information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCollectInformation();
 *
 ****************************************************************************/
int
INAP_SendCollectInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                           TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CollectInformationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CollectInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CollectInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_collectInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CollectInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "collect information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CollectInformationArg(data);
 *
 *  See Also:
 *      INAP_SendCollectInformation();
 *
 ****************************************************************************/
int
INAP_DecodeCollectInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                             void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CollectInformationArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CollectInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ANALYSE INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "analyse information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeAnalyseInformation();
 *
 ****************************************************************************/
int
INAP_SendAnalyseInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                           TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_AnalyseInformationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_AnalyseInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_AnalyseInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_analyseInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_AnalyseInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "analyse information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_AnalyseInformationArg(data);
 *
 *  See Also:
 *      INAP_SendAnalyseInformation();
 *
 ****************************************************************************/
int
INAP_DecodeAnalyseInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                             void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_AnalyseInformationArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_AnalyseInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** EVENT NOTIFICATION CHARGING ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "event notification charging" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeEventNotificationCharging();
 *
 ****************************************************************************/
int
INAP_SendEventNotificationCharging(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_EventNotificationChargingArg(&pe, 1, 0,
                                                 NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_EventNotificationChargingArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_EventNotificationChargingArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_eventNotificationCharging;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_EventNotificationChargingArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "event notification charging" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_EventNotificationChargingArg(data);
 *
 *  See Also:
 *      INAP_SendEventNotificationCharging();
 *
 ****************************************************************************/
int
INAP_DecodeEventNotificationCharging(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_EventNotificationChargingArg(pe, 1, NULL, NULL,
                                                 data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_EventNotificationChargingArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** REQUEST CURRENT STATUS REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "request current status report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRequestCurrentStatusReport();
 *
 ****************************************************************************/
int
INAP_SendRequestCurrentStatusReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RequestCurrentStatusReportArg(&pe, 1, 0,
                                                  NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RequestCurrentStatusReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RequestCurrentStatusReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_requestCurrentStatusReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RequestCurrentStatusReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "request current status report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RequestCurrentStatusReportArg(data);
 *
 *  See Also:
 *      INAP_SendRequestCurrentStatusReport();
 *
 ****************************************************************************/
int
INAP_DecodeRequestCurrentStatusReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RequestCurrentStatusReportArg(pe, 1, NULL, NULL,
                                                  data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RequestCurrentStatusReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** REQUEST CURRENT STATUS REPORT RESULT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "request current status report result" result
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRequestCurrentStatusReportResult();
 *
 ****************************************************************************/
int
INAP_SendRequestCurrentStatusReportResult(ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RequestCurrentStatusReportResult(&pe, 1, 0, NULL,
                                                     data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RequestCurrentStatusReportResult(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RequestCurrentStatusReportResult(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.result.operation.len = 3;
    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.result.operation.data[1] = 1;
    cpt->u.result.operation.data[2] = INAP_OP_requestCurrentStatusReportResult;
    cpt->u.result.param.len = len;
    memcpy(cpt->u.result.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RequestCurrentStatusReportResult(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "current status report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RequestCurrentStatusReportArg(data);
 *
 *  See Also:
 *      INAP_SendCurrentStatusReport();
 *
 ****************************************************************************/
int
INAP_DecodeRequestCurrentStatusReportResult(ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.result.param.data,
                 cpt->u.result.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RequestCurrentStatusReportResult(pe, 1, NULL, NULL,
                                                     data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RequestCurrentStatusReportResult(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** REQUEST EVERY STATUS CHANGE REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "request every status change report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRequestEveryStatusChangeReport();
 *
 ****************************************************************************/
int
INAP_SendRequestEveryStatusChangeReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RequestEveryStatusChangeReportArg(&pe, 1, 0,
                                                   NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RequestEveryStatusChangeReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RequestEveryStatusChangeReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_requestEveryStatusChangeReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RequestEveryStatusChangeReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "request every status change report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RequestEveryStatusChangeReportArg(data);
 *
 *  See Also:
 *      INAP_SendRequestEveryStatusChangeReport();
 *
 ****************************************************************************/
int
INAP_DecodeRequestEveryStatusChangeReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RequestEveryStatusChangeReportArg(pe, 1, NULL, NULL,
                                                      data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RequestEveryStatusChangeReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** REQUEST FIRST STATUS MATCH REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "request first status match report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRequestFirstStatusMatchReport();
 *
 ****************************************************************************/
int
INAP_SendRequestFirstStatusMatchReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RequestFirstStatusMatchReportArg(&pe, 1, 0,
                                                     NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RequestFirstStatusMatchReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RequestFirstStatusMatchReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_requestFirstStatusMatchReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RequestFirstStatusMatchReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "request first status match report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RequestFirstStatusMatchReportArg(data);
 *
 *  See Also:
 *      INAP_SendRequestFirstStatusMatchReport();
 *
 ****************************************************************************/
int
INAP_DecodeRequestFirstStatusMatchReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RequestFirstStatusMatchReportArg(pe, 1, NULL, NULL,
                                                     data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RequestFirstStatusMatchReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** REQUEST NOTIFICATION CHARGING EVENT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "request notification charging event" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRequestNotificationChargingEvent();
 *
 ****************************************************************************/
int
INAP_SendRequestNotificationChargingEvent(ITS_HANDLE handle, ITS_HDR *hdr,
                                         TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RequestNotificationChargingEventArg(&pe, 1, 0,
                                                        NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RequestNotificationChargingEventArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RequestNotificationChargingEventArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_requestNotificationChargingEvent;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RequestNotificationChargingEventArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "request notification charging event" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RequestNotificationChargingEventArg(data);
 *
 *  See Also:
 *      INAP_SendRequestNotificationChargingEvent();
 *
 ****************************************************************************/
int
INAP_DecodeRequestNotificationChargingEvent(ITS_HANDLE handle, TCAP_CPT *cpt,
                                           void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RequestNotificationChargingEventArg(pe, 1, NULL, NULL,
                                                        data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RequestNotificationChargingEventArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** SELECT FACILITY ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "select facility" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeSelectFacility();
 *
 ****************************************************************************/
int
INAP_SendSelectFacility(ITS_HANDLE handle, ITS_HDR *hdr,
                           TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_SelectFacilityArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_SelectFacilityArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_SelectFacilityArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_selectFacility;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_SelectFacilityArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "select facility" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_SelectFacilityArg(data);
 *
 *  See Also:
 *      INAP_SendSelectFacility();
 *
 ****************************************************************************/
int
INAP_DecodeSelectFacility(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_SelectFacilityArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_SelectFacilityArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** STATUS REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "status report" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeStatusReport();
 *
 ****************************************************************************/
int
INAP_SendStatusReport(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_StatusReportArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_StatusReportArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_StatusReportArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_statusReport;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_StatusReportArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "status report" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_StatusReportArg(data);
 *
 *  See Also:
 *      INAP_SendStatusReport();
 *
 ****************************************************************************/
int
INAP_DecodeStatusReport(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_StatusReportArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_StatusReportArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** CANCEL STATUS REPORT REQUEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "cancel status report request" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCancelStatusReportRequest();
 *
 ****************************************************************************/
int
INAP_SendCancelStatusReportRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CancelStatusReportRequestArg(&pe, 1, 0,
                                                 NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CancelStatusReportRequestArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CancelStatusReportRequestArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_cancelStatusReportRequest;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CancelStatusReportRequestArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "cancel status report request" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CancelStatusReportRequestArg(data);
 *
 *  See Also:
 *      INAP_SendCancelStatusReportRequest();
 *
 ****************************************************************************/
int
INAP_DecodeCancelStatusReportRequest(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CancelStatusReportRequestArg(pe, 1, NULL, NULL,
                                                 data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CancelStatusReportRequestArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ROUTE SELECT FAILURE ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "route select failure" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeRouteSelectFailure();
 *
 ****************************************************************************/
int
INAP_SendRouteSelectFailure(ITS_HANDLE handle, ITS_HDR *hdr,
                           TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_RouteSelectFailureArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_RouteSelectFailureArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_RouteSelectFailureArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_routeSelectFailure;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_RouteSelectFailureArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "route select failure" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_RouteSelectFailureArg(data);
 *
 *  See Also:
 *      INAP_SendRouteSelectFailure();
 *
 ****************************************************************************/
int
INAP_DecodeRouteSelectFailure(ITS_HANDLE handle, TCAP_CPT *cpt,
                             void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_RouteSelectFailureArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_RouteSelectFailureArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** OCALLED PARTY BUSY ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "o called party busy" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeOCalledPartyBusy();
 *
 ****************************************************************************/
int
INAP_SendOCalledPartyBusy(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_OCalledPartyBusyArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_OCalledPartyBusyArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_OCalledPartyBusyArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_oCalledPartyBusy;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_OCalledPartyBusyArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "o called party busy" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_OCalledPartyBusyArg(data);
 *
 *  See Also:
 *      INAP_SendOCalledPartyBusy();
 *
 ****************************************************************************/
int
INAP_DecodeOCalledPartyBusy(ITS_HANDLE handle, TCAP_CPT *cpt,
                           void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_OCalledPartyBusyArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_OCalledPartyBusyArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** O NO ANSWER ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "o no answer" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeONoAnswer();
 *
 ****************************************************************************/
int
INAP_SendONoAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ONoAnswer(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ONoAnswer(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ONoAnswer(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_oNoAnswer;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ONoAnswer(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "o no answer" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ONoAnswer(data);
 *
 *  See Also:
 *      INAP_SendONoAnswer();
 *
 ****************************************************************************/
int
INAP_DecodeONoAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ONoAnswer(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ONoAnswer(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** O ANSWER ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "o answer" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeOAnswer();
 *
 ****************************************************************************/
int
INAP_SendOAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_OAnswerArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_OAnswerArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_OAnswerArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_oAnswer;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_OAnswerArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "o answer" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_OAnswerArg(data);
 *
 *  See Also:
 *      INAP_SendOAnswer();
 *
 ****************************************************************************/
int
INAP_DecodeOAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                  void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_OAnswerArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_OAnswerArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** O DISCONNECT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "o disconnect" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeODisconnect();
 *
 ****************************************************************************/
int
INAP_SendODisconnect(ITS_HANDLE handle, ITS_HDR *hdr,
                    TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_ODisconnectArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_ODisconnectArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_ODisconnectArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_oDisconnect;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_ODisconnectArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "o disconnect" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_ODisconnectArg(data);
 *
 *  See Also:
 *      INAP_SendODisconnect();
 *
 ****************************************************************************/
int
INAP_DecodeODisconnect(ITS_HANDLE handle, TCAP_CPT *cpt,
                      void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_ODisconnectArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_ODisconnectArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** O TERM ATTEMPT AUTHORIZED ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "o term attempt authorized" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeOTermAttempAuthorized();
 *
 ****************************************************************************/
int
INAP_SendOTermAttempAuthorized(ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_TermAttemptAuthorizedArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_TermAttemptAuthorizedArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_TermAttemptAuthorizedArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_termAttemptAuthorized;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_TermAttemptAuthorizedArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "o term attempt authorized" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_TermAttemptAuthorizedArg(data);
 *
 *  See Also:
 *      INAP_SendOTermAttempAuthorized();
 *
 ****************************************************************************/
int
INAP_DecodeOTermAttempAuthorized(ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_TermAttemptAuthorizedArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_TermAttemptAuthorizedArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** T BUSY ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "t busy" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeTBusy();
 *
 ****************************************************************************/
int
INAP_SendTBusy(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_TBusyArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_TBusyArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_TBusyArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_tBusy;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_TBusyArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "t busy" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_TBusyArg(data);
 *
 *  See Also:
 *      INAP_SendTBusy();
 *
 ****************************************************************************/
int
INAP_DecodeTBusy(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_TBusyArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_TBusyArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** T NO ANSWER ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "t no answer" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeTNoAnswer();
 *
 ****************************************************************************/
int
INAP_SendTNoAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                  TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_TNoAnswerArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_TNoAnswerArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_TNoAnswerArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_tNoAnswer;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_TNoAnswerArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "t no answer" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_TNoAnswerArg(data);
 *
 *  See Also:
 *      INAP_SendTNoAnswer();
 *
 ****************************************************************************/
int
INAP_DecodeTNoAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                    void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_TNoAnswerArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_TNoAnswerArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** T ANSWER ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "t answer" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeTAnswer();
 *
 ****************************************************************************/
int
INAP_SendTAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_TAnswerArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_TAnswerArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_TAnswerArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_tAnswer;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_TAnswerArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "t answer" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_TAnswerArg(data);
 *
 *  See Also:
 *      INAP_SendTAnswer();
 *
 ****************************************************************************/
int
INAP_DecodeTAnswer(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_TAnswerArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_TAnswerArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** T DISCONNECT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "t disconnect" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeTDisconnect();
 *
 ****************************************************************************/
int
INAP_SendTDisconnect(ITS_HANDLE handle, ITS_HDR *hdr,
                    TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_TDisconnectArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_TDisconnectArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_TDisconnectArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_tDisconnect;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_TDisconnectArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "t disconnect" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_TDisconnectArg(data);
 *
 *  See Also:
 *      INAP_SendTDisconnect();
 *
 ****************************************************************************/
int
INAP_DecodeTDisconnect(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_TDisconnectArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_TDisconnectArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** O MID CALL ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "o mid call" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeOMidCall();
 *
 ****************************************************************************/
int
INAP_SendOMidCall(ITS_HANDLE handle, ITS_HDR *hdr,
                 TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_OMidCallArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_OMidCallArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_OMidCallArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_oMidCall;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_OMidCallArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "o mid call" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_OMidCallArg(data);
 *
 *  See Also:
 *      INAP_SendOMidCall();
 *
 ****************************************************************************/
int
INAP_DecodeOMidCall(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_OMidCallArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_OMidCallArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** T MID CALL ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "t mid call" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeTMidCall();
 *
 ****************************************************************************/
int
INAP_SendTMidCall(ITS_HANDLE handle, ITS_HDR *hdr,
                 TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_TMidCallArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_TMidCallArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_TMidCallArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_tMidCall;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_TMidCallArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "t mid call" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_TMidCallArg(data);
 *
 *  See Also:
 *      INAP_SendTMidCall();
 *
 ****************************************************************************/
int
INAP_DecodeTMidCall(ITS_HANDLE handle, TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_TMidCallArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_TMidCallArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** HOLD CALL IN NETWORK ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "hold call in network" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeHoldCallInNetwork();
 *
 ****************************************************************************/
int
INAP_SendHoldCallInNetwork(ITS_HANDLE handle, ITS_HDR *hdr,
                          TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_HoldCallInNetworkArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_HoldCallInNetworkArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_HoldCallInNetworkArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_holdCallInNetwork;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_HoldCallInNetworkArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "hold call in network" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_HoldCallInNetworkArg(data);
 *
 *  See Also:
 *      INAP_SendHoldCallInNetwork();
 *
 ****************************************************************************/
int
INAP_DecodeHoldCallInNetwork(ITS_HANDLE handle, TCAP_CPT *cpt,
                            void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_HoldCallInNetworkArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_HoldCallInNetworkArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ORIGINATION ATTEMPT AUTHORIZED ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "origination attempt authorized" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeOriginationAttemptAuthorized();
 *
 ****************************************************************************/
int
INAP_SendOriginationAttemptAuthorized(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_OriginationAttemptAuthorizedArg(&pe, 1, 0,
                                                    NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_OriginationAttemptAuthorizedArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_OriginationAttemptAuthorizedArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_originationAttemptAuthorized;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_OriginationAttemptAuthorizedArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "origination attempt authorized" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_OriginationAttemptAuthorizedArg(data);
 *
 *  See Also:
 *      INAP_SendOriginationAttemptAuthorized();
 *
 ****************************************************************************/
int
INAP_DecodeOriginationAttemptAuthorized(ITS_HANDLE handle, TCAP_CPT *cpt,
                                       void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_OriginationAttemptAuthorizedArg(pe, 1, NULL, NULL,
                                                    data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_OriginationAttemptAuthorizedArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** COLLECTED INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "collected information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeCollectedInformation();
 *
 ****************************************************************************/
int
INAP_SendCollectedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                             TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_CollectedInformationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_CollectedInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_CollectedInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_collectedInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_CollectedInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "collected information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_CollectedInformationArg(data);
 *
 *  See Also:
 *      INAP_SendCollectedInformation();
 *
 ****************************************************************************/
int
INAP_DecodeCollectedInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                               void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_CollectedInformationArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_CollectedInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*** ANALYSED INFORMATION ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode and send a "analyzed information" invoke component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from, returned from a call
 *               to ITS_Initialize().
 *      hdr - a pointer to the context for this dialogue.
 *      cpt - a pointer to the component header to be sent out.
 *      data -  a pointer to the the tree of structures to encode. 
 *              The tree must be built from heap memory.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameters were succesfully encoded and sent 
 *                    to the TCAP layer.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *  Notes:
 *      The 'data' will be freed automatically after encoding.
 *
 *  See Also:
 *      INAP_DecodeAnalysedInformation();
 *
 ****************************************************************************/
int
INAP_SendAnalysedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                            TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, ret;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    if (encode_INAP_AnalysedInformationArg(&pe, 1, 0, NULL, data) == NOTOK)
    {
        return (ITS_BADTCAPMESSAGE);
    }

    if (local_debug)
    {
        print_INAP_AnalysedInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe2ssdu(pe, &enc, &len) != OK)
    {
        free_INAP_AnalysedInformationArg(data);
 
        return (ITS_BADTCAPMESSAGE);
    }

    cpt->u.invoke.operation.len = 3;
    cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
    cpt->u.invoke.operation.data[1] = 1;
    cpt->u.invoke.operation.data[2] = INAP_OP_analysedInformation;
    cpt->u.invoke.param.len = len;
    memcpy(cpt->u.invoke.param.data, enc, len);

    ret = TCAP_SendComponent(handle, hdr, cpt);

    free(enc);

    free_INAP_AnalysedInformationArg(data);

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To decode a "analyzed information" component.
 *
 *  Input Parameters:
 *      handle - the transport we are receiving from, returned from a call
 *               to ITS_Initialize().
 *      cpt - a pointer to the component header received.
 *
 *  Input/Output Parameters:
 *      data -  a pointer to an allocated tree of structures representing 
 *              the decoded data.    
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the parameter set was succesfully decoded.
 *      ITS_XXXX - other error codes are detailed in its.h, under 
 *                 IntelliSS7\common\include.
 *
 *  Notes:
 *      The TCAP_CPT should be the result of performing a 
 *      TCAP_ReceiveComponent().  The user should free the data when finished 
 *      with it, or a memory leak will occur. This should be done by calling
 *      free_INAP_AnalysedInformationArg(data);
 *
 *  See Also:
 *      INAP_SendAnalysedInformation();
 *
 ****************************************************************************/
int
INAP_DecodeAnalysedInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                               void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_INAP))
    {
        return (ITS_ENOLICENSE);
    }

    pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                 cpt->u.invoke.param.len, NULL, &err);

    if (err != PS_ERR_NONE || pe == NULL)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (decode_INAP_AnalysedInformationArg(pe, 1, NULL, NULL, data) == NOTOK)
    {
        return ITS_BADTCAPMESSAGE;
    }

    if (local_debug)
    {
        print_INAP_AnalysedInformationArg(pe, 1, 0, NULL, data);
    }

    if (pe)
    {
        pe_free(pe);
    }

    return ret;
}
