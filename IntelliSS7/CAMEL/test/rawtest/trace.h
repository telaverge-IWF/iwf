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