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
 * LOG: $Log: genkey.c,v $
 * LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/15 19:02:50  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.1  2002/06/13 16:59:39  mmiers
 * LOG: Fix warning, add key generation tools
 * LOG:
 *
 ****************************************************************************/

#ident "$Id: genkey.c,v 9.1 2005/03/23 12:53:26 cvsadmin Exp $"

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

static void
cryptHost(char *string, int len)
{
    ITS_Key key;

    CRYPT_InitKey(&key, (ITS_OCTET *)string, len);

    CRYPT_Encrypt(&key, (ITS_OCTET *)string, len);
}

int
main(int argc, char **argv)
{
    int i, len;

    if (argc == 1)
    {
        printf("Usage: %s hostid\n", argv[0]);

        return (0);
    }

    len = strlen(argv[1]);

    cryptHost(argv[1], len);

    for (i = 0; i < len; i++)
    {
        printf("%02x", (unsigned char)(argv[1][i]));
    }
    printf("\n");

    return (0);
}
