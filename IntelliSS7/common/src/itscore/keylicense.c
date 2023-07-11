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
 * LOG: $Log: keylicense.c,v $
 * LOG: Revision 9.1.176.1  2014/09/19 07:18:53  jkchaitanya
 * LOG: changes for translator specific license validation and alarm implementation in IWF application
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:51:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.40.1  2004/12/16 03:30:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.36.1  2004/10/25 20:39:59  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.2  2002/12/17 20:45:11  mmiers
 * LOG: Add license version.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 16:51:38  mmiers
 * LOG: Add licensing for china.
 * LOG:
 * LOG: Revision 6.1  2002/06/13 16:59:39  mmiers
 * LOG: Fix warning, add key generation tools
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:22  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
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
 * LOG: Revision 3.1  2000/08/16 00:04:59  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/07/27 19:59:16  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 * LOG: Revision 2.4  2000/07/17 15:24:19  mmiers
 * LOG:
 * LOG:
 * LOG: Small API changes, mostly typing.
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:48  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 16:35:44  mmiers
 * LOG:
 * LOG:
 * LOG: Remove stubs include.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:19:19  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:18  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/10/06 22:19:47  mmiers
 * LOG:
 * LOG:
 * LOG: Update new user part, integrate into licensing scheme.
 * LOG:
 * LOG: Revision 1.4  1999/03/24 22:45:26  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.3  1999/03/15 23:11:41  mmiers
 * LOG:
 * LOG:
 * LOG: Update the licensing utilities to reflect the capabilities code.
 * LOG:
 * LOG: Revision 1.2  1999/03/13 00:12:29  mmiers
 * LOG:
 * LOG:
 * LOG: Add capabilities test to license generation.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:09  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.6  1999/03/01 18:12:13  mmiers
 * LOG:
 * LOG:
 * LOG: Clean up the current build.
 * LOG:
 * LOG: Revision 1.5  1999/02/04 22:57:41  mmiers
 * LOG:
 * LOG:
 * LOG: Some tweaks, detail improvement.
 * LOG:
 * LOG: Revision 1.4  1999/02/04 22:26:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.3  1998/05/14 20:45:59  mmiers
 * LOG: Remove references to non-associated projects.
 * LOG:
 * LOG: Revision 1.2  1998/04/23 01:34:08  mmiers
 * LOG: Update after building on Solaris.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 19:00:12  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.1  1998/01/24 21:51:14  mmiers
 * LOG: Move these around a bit.
 * LOG:
 * LOG: Revision 1.1  1998/01/24 21:49:04  mmiers
 * LOG: license.c: Encrypt/decrypt the license file.
 * LOG: crlicense.c: create a license.
 * LOG: mklicense.c: convert a plaintext license to encrypted form.
 * LOG: readlicense.c: read a license file.
 * LOG:
 *
 ****************************************************************************/

#ident "$Id: keylicense.c,v 9.1.176.1 2014/09/19 07:18:53 jkchaitanya Exp $"

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
#include <its_banner.h>
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

#define SECS_PER_DAY    (86400)

ITS_License license =
{
    ITS_LICENSE_MAGIC,
    DEFAULT_EXPIRE_TIME,
    DEFAULT_DURATION,
    DEFAULT_PORT_COUNT,
    DEFAULT_LINK_COUNT,
    ITS_LIC_REVISION
}; 

char    serial[ITS_LIC_STRING_LEN];
char    textkey[ITS_LIC_STRING_LEN];

static void
getDate(char *string)
{
    struct tm tm;
    char buf[ITS_LIC_STRING_LEN];

    if (strlen(string) != strlen("yyyymmddhhmmss"))
    {
        printf("Expiration date format is yyyymmddhhmmss\n");
        exit(0);
    }

    /* year */
    strncpy(buf, string, 4);
    buf[4] = 0;
    tm.tm_year = atoi(buf);

    /* month */
    strncpy(buf, &string[4], 2);
    buf[2] = 0;
    tm.tm_mon = atoi(buf);

    /* day */
    strncpy(buf, &string[6], 2);
    buf[2] = 0;
    tm.tm_mon = atoi(buf);

    /* hour */
    strncpy(buf, &string[8], 2);
    buf[2] = 0;
    tm.tm_mon = atoi(buf);

    /* minute */
    strncpy(buf, &string[10], 2);
    buf[2] = 0;
    tm.tm_mon = atoi(buf);

    /* second */
    strncpy(buf, &string[12], 2);
    buf[2] = 0;
    tm.tm_mon = atoi(buf);

    license.expiry = mktime(&tm);

    license.duration = license.expiry - time(NULL);
}

static void
getDays(char *string)
{
    license.expiry = time(NULL);

    license.expiry += atoi(string) * SECS_PER_DAY;

    license.duration = license.expiry - time(NULL);
}

static void
getPorts(char *string)
{
    license.max_voice_ports = atoi(string);
}

static void
getLinks(char *string)
{
    license.max_links = atoi(string);
}

static void
getKey(char *string)
{
    unsigned i;

    if (strlen(string) & 1)
    {
        printf("Invalid key length\n");
        exit(0);
    }

    if (strlen(string) > (ITS_LIC_STRING_LEN << 1))
    {
        printf("Invalid key length\n");
        exit(0);
    }

    for (i = 0; i < strlen(string); i += 2)
    {
        unsigned tmp;
        char *ptr;

        ptr = &string[i];
        sscanf(ptr, "%02x", &tmp);
        textkey[i/2] = tmp;
    }
}

static void
getSerial(char *string)
{
    strcpy(serial, string);
}

static void
genSerial(char *string)
{
#if defined(unix)
    int i;

    if (strlen(string) != 8)
    {
        printf("Serial number must contain 8 hex digits.\n");
        exit(0);
    }

    license.serial_number = 0;
    for (i = 0; i < 8; i++)
    {
        license.serial_number <<= 4;

        switch (string[i])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            license.serial_number |= string[i] - '0';
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            license.serial_number |= (string[i] - 'a') + 10;
            break;

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            license.serial_number |= (string[i] - 'A') + 10;
            break;

        default:
            printf("Invalid hex digit %c\n", string[i]);
            exit(0);
        }
    }
#elif defined(WIN32)
    memset(license.serial_number, 0, sizeof(license.serial_number));

    if (strlen(string) >= sizeof(license.serial_number))
    {
        printf("Serial number too long.\n");
        exit(0);
    }

    strcpy(license.serial_number, string);
#endif
}

void
handleLongOptions(char *option, char *second, int *argc)
{
    if (strcmp(option, "mtp3") == 0)
    {
        if (strcmp(second, "ansi") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_MTP3, license);
        }
        else if (strcmp(second, "itu") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_MTP3, license);
        }
        else if (strcmp(second, "china") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_MTP3, license);
        }
        else if (strcmp(second, "japan") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_MTP3, license);
        }
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_MTP3, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_MTP3, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_MTP3, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_MTP3, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
    else if (strcmp(option, "sccp") == 0)
    {
        if (strcmp(second, "ansi") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_SCCP, license);
        }
        else if (strcmp(second, "itu") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_SCCP, license);
        }
        else if (strcmp(second, "china") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_SCCP, license);
        }
        else if (strcmp(second, "japan") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_SCCP, license);
        }
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_SCCP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_SCCP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_SCCP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_SCCP, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
    else if (strcmp(option, "tcap") == 0)
    {
        if (strcmp(second, "ansi") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_TCAP, license);
        }
        else if (strcmp(second, "itu") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_TCAP, license);
        }
        else if (strcmp(second, "china") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_TCAP, license);
        }
        else if (strcmp(second, "japan") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_TCAP, license);
        }
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_TCAP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_TCAP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_TCAP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_TCAP, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
    else if (strcmp(option, "isup") == 0)
    {
        if (strcmp(second, "ansi") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_ISUP, license);
        }
        else if (strcmp(second, "itu") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_ISUP, license);
        }
        else if (strcmp(second, "china") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_ISUP, license);
        }
        else if (strcmp(second, "japan") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_ISUP, license);
        }
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_ISUP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_ISUP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_ISUP, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_ISUP, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
    else if (strcmp(option, "snmm") == 0)
    {
        if (strcmp(second, "ansi") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_SNMM, license);
        }
        else if (strcmp(second, "itu") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_SNMM, license);
        }
        else if (strcmp(second, "china") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_SNMM, license);
        }
        else if (strcmp(second, "japan") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_SNMM, license);
        }
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_SNMM, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_SNMM, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_SNMM, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_SNMM, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
    else if (strcmp(option, "sltm") == 0)
    {
        if (strcmp(second, "ansi") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_SLTM, license);
        }
        else if (strcmp(second, "itu") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_SLTM, license);
        }
        else if (strcmp(second, "china") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_SLTM, license);
        }
        else if (strcmp(second, "japan") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_SLTM, license);
        }
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ITU_SLTM, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_ANSI_SLTM, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_PRC_SLTM, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_CAP_TTC_SLTM, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
    else if (strcmp(option, "inap") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_INAP, license);
    }
    else if (strcmp(option, "is634") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_IS634, license);
    }
    else if (strcmp(option, "is41") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_IS41, license);
    }
    else if (strcmp(option, "ain") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_AIN, license);
    }
    else if (strcmp(option, "lidb") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_LIDB, license);
    }
    else if (strcmp(option, "lnp") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_LNP, license);
    }
    else if (strcmp(option, "gsmmap") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_GSMMAP, license);
    }
    else if (strcmp(option, "is651") == 0)
    {
        LICENSE_SET_CAPABILITY(ITS_LIC_CAP_IS651, license);
    }
    else if (strcmp(option, "iwf") == 0)
    {
        if(strcmp(second, "caprotsl") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_CAP_RO_TSL, license);
        }
        else if(strcmp(second, "capro") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_CAP_RO, license);
        }
        else if(strcmp(second, "maps6a") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_MAP_S6A, license);
        }
        else if(strcmp(second, "s6amap") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_S6A_MAP, license);
        }    
        else if (strcmp(second, "all") == 0)
        {
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_CAP_RO_TSL, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_CAP_RO, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_MAP_S6A, license);
            LICENSE_SET_CAPABILITY(ITS_LIC_IWF_S6A_MAP, license);
        }
        else
        {
            printf("Missing option\n");
            exit(0);
        }

        (*argc)++;
    }
}

static void
cryptLicense()
{
    ITS_Key key;

    CRYPT_InitKey(&key, (ITS_OCTET *)serial, strlen(serial));

    CRYPT_Decrypt(&key, (ITS_OCTET *)textkey, strlen(textkey));

    if (strcmp(textkey, serial) != 0)
    {
        printf("Bad key data\n");
        exit(0);
    }

    genSerial(serial);

    CRYPT_InitKey(&key, (ITS_OCTET *)ITS_Banner, strlen(ITS_Banner));

    CRYPT_Encrypt(&key, (ITS_OCTET *)&license, sizeof(ITS_License));
}

int
main(int argc, char **argv)
{
    int i;

    if (argc == 1)
    {
        printf("Usage: %s [-e yyyymmddhhmmss | -n days] -p x -l x -s xxxxxxxx\n",
               argv[0]);
        printf("          [--tcap [ansi|itu|china|japan|all] --sccp [ansi|itu|china|japan|all]]\n");
        printf("          [--isup [ansi|itu|china|japan|all] --mtp3 [ansi|itu|china|japan|all]]\n");
        printf("          [--sltm [ansi|itu|china|japan|all] --snmm [ansi|itu|china|japan|all]]\n");
        printf("          [--inap --is41 --is634 --ain --gsmmap --lidb]\n");
        printf("          [--lnp --is651]\n");
        printf("  where:\n");
        printf("          -e expiration date\n");
        printf("          -n expiration in days from now\n");
        printf("          -p number of voice ports\n");
        printf("          -l number of links\n");
        printf("          -k key phrase\n");
        printf("          --tcap enable TCAP protocol family(ies)\n");
        printf("          --sccp enable SCCP protocol family(ies)\n");
        printf("          --isup enable ISUP protocol family(ies)\n");
        printf("          --mtp3 enable MTP3 protocol family(ies)\n");
        printf("          --sltm enable SLTM protocol family(ies)\n");
        printf("          --snmm enable SNMM protocol family(ies)\n");
        printf("          --inap enable INAP application protocol\n");
        printf("          --is41 enable IS41 application protocol\n");
        printf("          --is634 enable IS634 protocol\n");
        printf("          --ain enable AIN application protocol\n");
        printf("          --gsmmap enable GSMMAP application protocol\n");
        printf("          --lidb enable LIDB application protocol\n");
        printf("          --lnp enable LNP application protocol\n");
        printf("          --is651 enable IS651 protocol\n");
        printf("          [--iwf [caprotsl | capro | maps6a | s6amap | all]--enable IWF translators\n");
        return (0);
    }

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'i':
                break;

            case 'e':
                if (argv[i][2] == 0)
                {
                    i++;
                    getDate(argv[i]);
                }
                else
                {
                    getDate(&argv[i][2]);
                }
                break;

            case 'n':
                if (argv[i][2] == 0)
                {
                    i++;
                    getDays(argv[i]);
                }
                else
                {
                    getDays(&argv[i][2]);
                }
                break;

            case 'p':
                if (argv[i][2] == 0)
                {
                    i++;
                    getPorts(argv[i]);
                }
                else
                {
                    getPorts(&argv[i][2]);
                }
                break;

            case 'l':
                if (argv[i][2] == 0)
                {
                    i++;
                    getLinks(argv[i]);
                }
                else
                {
                    getLinks(&argv[i][2]);
                }
                break;

            case 'k':
                if (argv[i][2] == 0)
                {
                    i++;
                    getKey(argv[i]);
                }
                else
                {
                    getKey(&argv[i][2]);
                }
                break;

            case 's':
                if (argv[i][2] == 0)
                {
                    i++;
                    getSerial(argv[i]);
                }
                else
                {
                    getSerial(&argv[i][2]);
                }
                break;

            case '-':
                handleLongOptions(&argv[i][2], argv[i+1], &i);
                break;

            default:
                printf("Invalid argument %s\n", argv[i]);
                exit(0);
            }
        }
    }

    cryptLicense();

#if defined(WIN32)
    _write(1, (char *)&license, sizeof(license));
#else
    write(1, (char *)&license, sizeof(license));
#endif

    return (0);
}
