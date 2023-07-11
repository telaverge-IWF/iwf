/**************************-*-Dia-*-*****************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 *  ID: $Id: app_diatrace.cpp,v 3.1.30.1 2012/10/01 09:00:14 rsanjay Exp $
 *
 *  LOG: $Log: app_diatrace.cpp,v $
 *  LOG: Revision 3.1.30.1  2012/10/01 09:00:14  rsanjay
 *  LOG:  opendiameter code removal changes:bugzilla-id 300
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:06  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.2  2006/10/16 13:17:07  tpanda
 *  LOG: Merging with ITSDIAMETER
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/07/24 14:29:23  nvijikumar
 *  LOG: Baseline common application for all interfaces.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: app_diatrace.cpp,v 3.1.30.1 2012/10/01 09:00:14 rsanjay Exp $"

#include <iostream>
/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

