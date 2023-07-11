/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ttc-mtp3_ifc.c,v 9.5 2008/06/17 06:38:02 nvijikumar Exp $
 *
 * LOG: $Log: ttc-mtp3_ifc.c,v $
 * LOG: Revision 9.5  2008/06/17 06:38:02  nvijikumar
 * LOG: Updated for ITU over TTC support (Split Stack)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::D7040,D7080
 * LOG:
 * LOG: Revision 9.4  2008/06/12 12:51:50  nvijikumar
 * LOG: Renaming from COT to CPOT (CCITT prime - 16bit)
 * LOG: ACC-CG-SDS-SS7-V1.0.02::ID:: D6030
 * LOG:
 * LOG: Revision 9.3  2008/06/04 10:38:48  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.2  2007/01/11 12:43:40  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.2  2007/10/05 11:16:14  mshanmugam
 * LOG: CPOT Stack support as per design Id D0060
 * LOG:
 * LOG: Revision 9.1.10.1  2006/12/23 10:05:37  randresol
 * LOG: Modifications to allow TTC and ITU stacks to run in parallel
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/18 11:26:52  dsatish
 * LOG: Added Initial version file for TTC
 * LOG:
 * LOG: Revision 7.1.48.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:34:12  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.3  2001/10/22 21:18:21  rsonak
 * LOG: Get cvs logs in the file
 * LOG:
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI

#if defined(SPLIT_STACK) && defined(USE_TTC_SCCP)
#define TTC
#endif

#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#if defined(CPOT_SPLIT_STACK)
#undef CCITT
#define TTC
#endif

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>

#if defined(PRC)
#include <china/snmm.h>
#include <china/sltm.h>
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/snmm.h>
#include <japan/sltm.h>
#include <japan/mtp3.h>
#else
#include <itu/snmm.h>
#include <itu/sltm.h>
#include <itu/mtp3.h>
#endif

#ident "$Id: ttc-mtp3_ifc.c,v 9.5 2008/06/17 06:38:02 nvijikumar Exp $"

#include "mtp3_intern.h"

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
int INTELLINET_SendMTP3Event_TTC(ITS_HANDLE handl,
                                   ITS_OCTET type, MTP3_HEADER *mtp3,
                                   ITS_OCTET *buf, ITS_USHORT len)
{
    ITS_EVENT ev;
    int ret;

    memset(&ev, 0, sizeof(ITS_EVENT));

    printf("=========== INTELLINET_SendMTP3Event_TTC ========== \n");

    if ((ret = MTP3_Encode(&ev, type, mtp3, buf, len)) != ITS_SUCCESS)
    {
        return (ret);
    }

    return TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
}

