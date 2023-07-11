////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: internal					                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: win_trace.h,v 9.1 2005/03/23 12:52:45 cvsadmin Exp $				
//
////////////////////////////////////////////////////////////////////////////////

#if !defined(WIN_TRACE_H)
#define WIN_TRACE_H


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


#endif // #if !defined(WIN_TRACE_H)

