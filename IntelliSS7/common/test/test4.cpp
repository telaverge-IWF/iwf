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
 *  ID: $Id: test4.cpp,v 9.1 2005/03/23 12:53:52 cvsadmin Exp $
 *
 * LOG: $Log: test4.cpp,v $
 * LOG: Revision 9.1  2005/03/23 12:53:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1998/11/18 18:07:12  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.4  1998/05/29 03:31:39  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.3  1998/04/15 00:07:17  mmiers
 * LOG: Tests and bug fixes for infrastructure.
 * LOG:
 * LOG: Revision 1.2  1998/04/13 22:19:22  mmiers
 * LOG: Fifo (named pipe) implementation.  For portability, fifos can be
 * LOG: RDONLY or WRONLY, but not both (i.e., not bidirectional).  For
 * LOG: bidirectional communication, use two fifos.
 * LOG:
 * LOG: Revision 1.1  1998/04/13 21:42:28  mmiers
 * LOG: Add fifo test.
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <exception>

#include <its++.h>
#include <its_fifo.h>
#include <its_statics.cpp>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

int
main(int argc, char **argv)
{
    ITS_Fifo *fifo;
    
    try
    {
#if defined(WIN32)
        fifo = new ITS_Fifo("\\\\.\\pipe\\this_fifo_test4",
                            "\\\\.\\pipe\\this_fifo_test5");
#else
        fifo = new ITS_Fifo("./this_fifo_test4",
                            "./this_fifo_test5");
#endif
    }
    catch (exception& ex)
    {
        printf("Couldn't create fifo\n");

        return (0);
    }

    printf(" Write returns: %d\n", fifo->Write("foo", 3));

    char buf[5];

    printf(" Read returns: %d\n", fifo->Read(buf, 3));
    printf("buf: %3.3s\n", buf);

    delete fifo;

    return (0);
}
