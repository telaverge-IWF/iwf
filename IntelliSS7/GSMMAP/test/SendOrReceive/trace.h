/*
 ****************************************************************************
 * DISCLAIMER:
 *
 * INTELLINET DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * INTELLINET BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *  
 ****************************************************************************
 *
 *  ID: $Id: trace.h,v 9.1 2005/03/23 12:51:34 cvsadmin Exp $
 *
 * LOG: $Log: trace.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:34  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:31  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:21  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:22  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:22  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/11/01 17:26:35  cbascon
 * LOG:
 * LOG:
 * LOG: Should have log entries on files now.
 * LOG:
 ****************************************************************************/

#ifndef TRACE_H
#define TRACE_H

#include <its++.h>
#include <sccp++.h>
#include <tcap++.h>

// HEX dump functions for ITS_OCTETS
void hexDump(ITS_OCTET *array, int len);

// Display SCCP_Address information
void traceSCCPAddress(its::SCCP_Address &addr);

// Display Dialogue information
void traceDialogue(its::TCAP_Dialogue *dlg);
void traceAbortDlg(its::TCAP_Abort *dlg);
void traceBeginDlg(its::TCAP_Begin *dlg);
void traceContinueDlg(its::TCAP_Continue *dlg);
void traceEndDlg(its::TCAP_End *dlg);

// Display Component information
void traceComponent(its::TCAP_Component *cpt);
void traceComponentType(its::TCAP_Component *cpt);

void traceCancelCpt(its::TCAP_Component *cpt);
void traceErrorCpt(its::TCAP_Component *cpt);
void traceInvokeCpt(its::TCAP_Component *cpt);
void traceRejectCpt(its::TCAP_Component *cpt);
void traceResultCpt(its::TCAP_Component *cpt);


#endif // TRACE_H