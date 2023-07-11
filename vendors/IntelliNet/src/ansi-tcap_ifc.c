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
 ****************************************************************************
 *
 *  ID: $Id: ansi-tcap_ifc.c,v 9.1 2005/03/23 12:54:37 cvsadmin Exp $
 *
 * LOG: $Log: ansi-tcap_ifc.c,v $
 * LOG: Revision 9.1  2005/03/23 12:54:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.42.2  2005/02/03 10:19:32  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.3.42.1  2004/12/31 08:09:21  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.3  2003/02/07 11:45:11  tsanthosh
 * LOG: Modified to add some tcap pegs.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/03/01 23:12:06  mmiers
 * LOG: Start the DSM/pegs/alarms merge.  ANSI-TCAP done, 3 left.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.4  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.3  2000/12/22 00:36:41  mmiers
 * LOG: Traces
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:23  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/18 00:21:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:28  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/10/05 19:01:02  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.4  1999/09/07 21:02:30  ite
 * LOG:
 * LOG:
 * LOG: Change interface for TCAP such that the dialogue id is not memcpy'd.
 * LOG: This fixes a reject bug.
 * LOG:
 * LOG: Revision 1.3  1999/08/26 23:44:56  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.2  1999/08/25 21:34:47  mmiers
 * LOG:
 * LOG:
 * LOG: Call sanity check function when sending message to stack.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:45  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.4  1999/03/16 20:58:29  mmiers
 * LOG:
 * LOG:
 * LOG: Fix interface names, start ITU TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/06/26 15:08:06  mmiers
 * LOG: Convert TCAP to use C style transport.
 * LOG:
 * LOG: Revision 1.2  1998/06/17 22:19:18  mmiers
 * LOG: Add dialogue allocator.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:33  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.8  1998/06/16 00:00:21  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.7  1998/06/01 23:18:17  mmiers
 * LOG: More documentation.  Custom build steps for TCAP, SCCP.
 * LOG:
 * LOG: Revision 1.6  1998/05/05 20:24:09  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.5  1998/05/05 00:00:04  mmiers
 * LOG: Add new signatures, remove TCSM code from tcap.h.
 * LOG:
 * LOG: Revision 1.4  1998/05/01 14:22:14  mmiers
 * LOG: Clean up existing workspaces, add IS634 workspace.
 * LOG:
 * LOG: Revision 1.3  1998/04/29 22:45:02  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_ANSI_SRC.
 * LOG:
 * LOG: Revision 1.2  1998/04/16 16:40:03  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:05:35  mmiers
 * LOG: TCAP implementation for ANSI.  Not quite there yet.
 * LOG:
 * LOG: Revision 1.1  1998/02/10 22:32:09  mmiers
 * LOG: Separate out the PART specific stuff from its.h.  Everything is now in
 * LOG: its appropriate place.  The TCAP headers moved from common to TCAP.  The
 * LOG: state machine code has been added to the tree.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_license.h>
#include <its_transports.h>


#ident "$Id: ansi-tcap_ifc.c,v 9.1 2005/03/23 12:54:37 cvsadmin Exp $"

#include <ansi/tcap.h>
#include "tcap_intern.h"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is used by an application to send components to TCAP
 *      for processing.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context this component is operating in
 *      cpt - the component to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the component is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_SendComp_ANSI(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    ITS_EVENT ev;
    int ret;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_TCAP))
    {
        return (ITS_ENOLICENSE);
    }

    ITS_EVENT_INIT(&ev, 0,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));

    ev.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&ev.data[1], hdr->context.dialogue_id);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], cpt, sizeof(TCAP_CPT));

    ret = TRANSPORT_PutEvent(ITS_TCAP_ANSI_SRC, &ev);

    ITS_EVENT_TERM(&ev);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is used by an application to send a dialogue to TCAP
 *      for processing.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context this component is operating in
 *      dlg - the dialogue to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the dialogue is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_SendDlg_ANSI(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    ITS_EVENT ev;
    int ret;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_TCAP))
    {
        return (ITS_ENOLICENSE);
    }

    ITS_EVENT_INIT(&ev, 0,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_DLG));

    /* send to TCAP */
    ev.data[0] = ITS_TCAP_DLG;
    ITS_SET_CTXT(&ev.data[1], hdr->context.dialogue_id);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], dlg, sizeof(TCAP_DLG));
      
    /* Incr Peg Count at Application Interface */
    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_DLG_SENT);

    ret = TRANSPORT_PutEvent(ITS_TCAP_ANSI_SRC, &ev);

    ITS_EVENT_TERM(&ev);

    return (ret);
}
