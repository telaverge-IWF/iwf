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
 *  ID: $Id: test.c,v 9.1 2005/03/23 12:55:26 cvsadmin Exp $
 *
 * LOG: $Log: test.c,v $
 * LOG: Revision 9.1  2005/03/23 12:55:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:52  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/10/25 16:37:10  ngoel
 * LOG: with adax mtp2
 * LOG:
 * LOG: Revision 1.5  2001/10/19 20:49:00  mmiers
 * LOG: Get things working with the engine.
 * LOG:
 * LOG: Revision 1.4  2001/10/19 16:47:34  mmiers
 * LOG: Convert to engine for testing.
 * LOG:
 * LOG: Revision 1.3  2001/10/12 23:14:52  mmiers
 * LOG: Fun with NMS.  The MTP2 API now works.
 * LOG:
 * LOG: Revision 1.2  2001/10/04 21:31:34  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 1.1  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <engine.h>

#include <ss7_mgmt.h>

#ident "$Id: test.c,v 9.1 2005/03/23 12:55:26 cvsadmin Exp $"

ITS_THREAD thr;

ITSDLLAPI int
StartMTP3(TPOOL_THREAD *thr)
{
    MGMT_Main_ANSI(MTP3_USER,
                   MGMT_TRIGGER_RESTART,
                   NULL, 0,
                   ITS_SS7_DEFAULT_LINK_SET,
                   ITS_SS7_DEFAULT_LINK_CODE);

    return (ITS_SUCCESS);
}

int
main(int argc, char **argv)
{
    APPL_SetConfigDir("/opt/ngoel/cvsroot/current/vendors/adax/mtp3test/");
    APPL_SetName("test");
    APPL_SetConfigFileExtension("xml");
    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}
