/****************************************************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: mab_tcap_client.h,v 1.1 2005/05/25 10:13:58 mmanikandan Exp $
 *
 ****************************************************************************/

#ifndef TCAPCLIENTIMPL_H
#define TCAPCLIENTIMPL_H

#include <mab_client.h>

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Get the  TCAP components from the queue 
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
MABCL_DLLAPI ITS_INT
TCAP_GetComponentFromQ(ITS_CTXT did, ITS_EVENT *evPtr);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Get the  TCAP Dialogue from the queue 
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
MABCL_DLLAPI ITS_INT
TCAP_GetDialogueFromQ(ITS_CTXT did, TCAP_DLG *dlg);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Storing TCAP components/dialogue in queue to be packed 
 *     and sent on receiving DLG/CPT request
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
MABCL_DLLAPI ITS_INT
TCAP_StoreTcapEvent(ITS_EVENT *event);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode component 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeCpt(ITS_CTXT dlgId,
               TCAP_CPT *cpt, 
               ITS_EVENT *ev);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode dialogue 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeDlg(ITS_CTXT  dlgId,
               TCAP_DLG  *dlg, 
               ITS_EVENT *ev);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode Dlg and components to Msg frame 
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
MABCL_DLLAPI ITS_INT 
TCAP_EncodeDlgCptFrame(ITS_ULONG clid , ITS_OCTET msgType,
                       ITS_CTXT dlgid,  TCAP_DLG *dlg, 
                       ITS_EVENT *ev);

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode Dlg and components to Msg frame 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeMsgFrame(ITS_ULONG clid , ITS_OCTET msgType,
                    ITS_CTXT dlgid,  TCAP_CPT *cpt,
                    ITS_EVENT *ev);

#endif
