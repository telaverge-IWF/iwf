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
 *
 * LOG: $Log: mcrlicense.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.3  2005/03/21 13:51:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.2.2.1  2003/08/05 13:31:02  mmanikandan
 * LOG: Temporary license file generation.
 * LOG:
 *
 ****************************************************************************/

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
#include <its_crypt.h>
#include "itscore.h"

#else /* TANDEM */

#include <stdioh>
#include <stdlibh>
#include <stringh>
#include <timeh>

#include <itsh>
#include <itslicen>
#include <itsbanne>
#include <itscrypt>
#include "itscoreh"

#endif /* TANDEM */

#define SECS_PER_DAY     (86400)
#define MAX_TEMP_COUNTER (4)
#define TEMP_LICENSE     (0x80)
#define TEMP_COUNTER_BYTE 31
#define NUMBER_OF_DAYS     7

extern ITS_License __its_data;
extern void printNotice(const char *string);

static void
extendLicense()
{
    int last = 0;

    __its_data.capabilities[TEMP_COUNTER_BYTE] |= TEMP_LICENSE;

    __its_data.capabilities[TEMP_COUNTER_BYTE] += 1;
    
    last = time(NULL);

    __its_data.capabilities[30] = ((last & 0xff000000) >> 24);
    __its_data.capabilities[29] = ((last & 0x00ff0000) >> 16);
    __its_data.capabilities[28] = ((last & 0x0000ff00) >> 8);
    __its_data.capabilities[27] = (last & 0x000000ff);

    __its_data.expiry = last;

    __its_data.expiry += (NUMBER_OF_DAYS * SECS_PER_DAY);

    __its_data.duration = __its_data.expiry - last;
}

int 
main(int argc, char* argv[])
{
    LICENSE_Load();

    if ((__its_data.capabilities[TEMP_COUNTER_BYTE] & 0x7f)
                        >= MAX_TEMP_COUNTER)
    {
        printNotice("License Expired");
        return 0;
    }

    extendLicense();

    LICENSE_Update();

    printNotice("This is Temporary license for one week.");

    return 0;
}
