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
 * LOG: $Log: prlicense.c,v $
 * LOG: Revision 9.2.34.1.20.1  2014/09/19 07:18:53  jkchaitanya
 * LOG: changes for translator specific license validation and alarm implementation in IWF application
 * LOG:
 * LOG: Revision 9.2.34.1  2011/04/13 07:37:34  nvijikumar
 * LOG: Merging Diameter specific changes
 * LOG:
 * LOG: Revision 9.2  2007/01/10 11:15:10  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.1  2005/09/06 09:51:09  mmanikandan
 * LOG: RANAP is added.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.2.6.1.8.1  2004/12/16 03:30:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.3.2.2.6.1.4.1  2004/10/25 20:39:59  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.3.2.2.6.1  2004/07/26 06:54:50  mmanikandan
 * LOG: License support for BSSAP.
 * LOG:
 * LOG: Revision 7.3.2.2  2003/07/07 12:16:22  mmanikandan
 * LOG: License capability is added for IS652, IS653, IS826, CAMEL, WIN, JSTD.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/06/16 11:13:03  sjaddu
 * LOG: Added license capability for CAMEL.
 * LOG:
 * LOG: Revision 7.3  2002/12/17 20:45:11  mmiers
 * LOG: Add license version.
 * LOG:
 * LOG: Revision 7.2  2002/09/20 15:44:08  mmiers
 * LOG: Fix the licensing binaries
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/07/10 19:10:25  mmiers
 * LOG: Buggy license printing fixes
 * LOG:
 * LOG: Revision 6.5  2002/07/03 16:51:38  mmiers
 * LOG: Add licensing for china.
 * LOG:
 * LOG: Revision 6.4  2002/05/07 16:19:28  mmiers
 * LOG: Formatting issues.
 * LOG:
 * LOG: Revision 6.3  2002/04/24 18:42:38  yranade
 * LOG: Pretty print capabilites information.
 * LOG:
 * LOG: Revision 6.2  2002/04/04 19:58:14  mmiers
 * LOG: Fix build errors.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/17 21:10:35  hdivoux
 * LOG: Added init of license class (for mutex).
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:07  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/07/27 19:59:17  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:51  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 16:35:44  mmiers
 * LOG:
 * LOG:
 * LOG: Remove stubs include.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:19:21  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:23  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/06/15 15:33:48  labuser
 * LOG:
 * LOG:
 * LOG: Add utility for printing a license file.
 * LOG:
 * LOG: Revision 1.3  1999/03/24 22:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.2  1999/03/15 23:11:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update the licensing utilities to reflect the capabilities code.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:12  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.1  1999/02/04 22:57:42  mmiers
 * LOG:
 * LOG:
 * LOG: Some tweaks, detail improvement.
 * LOG:
 *
 ****************************************************************************/

#ident "$Id: prlicense.c,v 9.2.34.1.20.1 2014/09/19 07:18:53 jkchaitanya Exp $"

#if !defined(TANDEM)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(WIN32)
#include <io.h>
#else
#include <unistd.h>
#endif

#include <its.h>
#include <its_license.h>
#include <its_assertion.h>

#include "itscore.h"

#else
#include <stdioh>
#include <stdlibh>
#include <stringh>
#include <timeh>

#include <itsh>
#include <itslicen>
#include <itsasser>

#include "itscoreh"
#endif

extern ITS_License __its_data;

static const char *types[] =
{
    "ansi-mtp3",
    "itu-mtp3",
    "ansi-isup",
    "itu-isup",
    "ansi-sccp",
    "itu-sccp",
    "ansi-tcap",
    "itu-tcap",
    "inap",
    "is41",
    "is634",
    "ain",
    "gsmmap",
    "is651",
    "lidb",
    "lnp",
    "ansi-snmm",
    "itu-snmm",
    "ansi-sltm",
    "itu-sltm",
    "china-mtp3",
    "china-isup",
    "china-sccp",
    "china-tcap",
    "china-snmm",
    "china-sltm",
    "camel",
    "is652",
    "is653",
    "is826",
    "win",
    "jstd",
    "bssap",
    "japan-mtp3",
    "japan-isup",
    "japan-sccp",
    "japan-tcap",
    "japan-snmm",
    "japan-sltm",
    "diameter",
    "dcca",
    "ranap",
    "iwf-caprotsl",
    "iwf-capro",
    "iwf-maps6a",
    "iwf-s6amap"
};

int
main(int argc, char **argv)
{
    int i, j;
    int tsize = sizeof(types)/sizeof(types[0]);

    /* don't care about success here */
    LICENSE_Load();

    printf("License info:\n");
    printf("  cookie         : 0x%08x\n", __its_data.cookie);
    printf("  expiry         : 0x%08lx\n", __its_data.expiry);
    printf("  duration       : 0x%08lx\n", __its_data.duration);
    printf("  max_voice_ports: 0x%08x\n", __its_data.max_voice_ports);
    printf("  max_links      : 0x%02x\n", __its_data.max_links);
    printf("  revision       : %d.%d\n", __its_data.revision / 0x100,
                                         __its_data.revision % 0x100);
#if defined(unix)
    printf("  serial_number  : 0x%08x\n", __its_data.serial_number);
#elif defined(WIN32)
    printf("  serial_number  : %s\n", __its_data.serial_number);
#endif

    printf("------------------------------------------------------\n");
    printf("Licenses enabled for:\n");
    for (i = 0, j = 1; i < tsize; i ++)
    {
        if (LICENSE_CheckCapability(i))
        {
             printf("%-15s", types[i]);

             if (j % 3 == 0)
             {
                 printf("\n");
             }

             j++;
        }
    }
    printf("\n------------------------------------------------------\n");
    printf("Licenses NOT enabled for:\n");
    for (i = 0, j = 1; i < tsize; i ++)
    {
        if (!LICENSE_CheckCapability(i))
        {
             printf("%-15s", types[i]);

             if (j % 3 == 0)
             {
                 printf("\n");
             }

             j++;
        }
    }
    printf("\n------------------------------------------------------\n");

    return (0);
}
