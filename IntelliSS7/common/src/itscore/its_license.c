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
 * LOG: $Log: its_license.c,v $
 * LOG: Revision 9.3.32.1.8.1.2.1.6.1  2014/09/19 07:18:53  jkchaitanya
 * LOG: changes for translator specific license validation and alarm implementation in IWF application
 * LOG:
 * LOG: Revision 9.3.32.1.8.1.2.1  2014/02/12 10:43:23  jsarvesh
 * LOG: Changes done for TPS Based Licensing
 * LOG:
 * LOG: Revision 9.3.32.1.8.1  2013/11/28 06:44:47  millayaraja
 * LOG: modified the name in license expiry message from IntelliNet to Diametriq
 * LOG:
 * LOG: Revision 9.3.32.1  2011/04/13 07:37:34  nvijikumar
 * LOG: Merging Diameter specific changes
 * LOG:
 * LOG: Revision 9.3  2007/01/10 11:15:09  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.2.8.1  2005/09/06 09:51:09  mmanikandan
 * LOG: RANAP is added.
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:40:58  mmanikandan
 * LOG: Bug Fix Propagation.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.3.6.2  2004/10/06 13:15:16  mmanikandan
 * LOG: License class exported.
 * LOG:
 * LOG: Revision 7.4.2.3.6.1  2004/07/26 06:53:21  mmanikandan
 * LOG: License support for BSSAP.
 * LOG:
 * LOG: Revision 7.4.2.3  2003/08/05 13:29:36  mmanikandan
 * LOG: Support for temporary license.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/07/07 12:18:42  mmanikandan
 * LOG: License capability is added for IS652, IS653, IS826, CAMEL, WIN, JSTD.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/06/16 11:13:03  sjaddu
 * LOG: Added license capability for CAMEL.
 * LOG:
 * LOG: Revision 7.4  2002/12/17 20:45:11  mmiers
 * LOG: Add license version.
 * LOG:
 * LOG: Revision 7.3  2002/09/30 16:39:30  yranade
 * LOG: Symbol collision
 * LOG:
 * LOG: Revision 7.2  2002/09/20 15:44:08  mmiers
 * LOG: Fix the licensing binaries
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/07/10 19:10:25  mmiers
 * LOG: Buggy license printing fixes
 * LOG:
 * LOG: Revision 6.3  2002/03/28 22:00:41  mmiers
 * LOG: Oops.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/12/07 18:45:14  mmiers
 * LOG: Remove mutex in CheckExpiry, don't exit if it fails.
 * LOG:
 * LOG: Revision 5.2  2001/12/07 17:08:19  mmiers
 * LOG: Add link count to licensing.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.7  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2001/01/04 16:11:35  hdivoux
 * LOG: Warning removal, proper flags.
 * LOG:
 * LOG: Revision 3.2  2000/09/14 20:48:28  mmiers
 * LOG: Add flag for licensing disable.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:04  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.8  2000/07/27 19:59:16  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 * LOG: Revision 2.7  2000/07/17 15:24:19  mmiers
 * LOG:
 * LOG:
 * LOG: Small API changes, mostly typing.
 * LOG:
 * LOG: Revision 2.6  2000/07/03 22:40:15  mmiers
 * LOG:
 * LOG:
 * LOG: Add message digest
 * LOG:
 * LOG: Revision 2.5  2000/07/03 22:06:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add secure hash.
 * LOG:
 * LOG: Revision 2.4  2000/03/18 21:03:49  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:39  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  2000/02/01 23:41:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 2.1  2000/02/01 23:09:13  mmiers
 * LOG:
 * LOG:
 * LOG: Auto start the license system.  Can do away with standalone *now*.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:21  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/11/02 21:45:15  labuser
 * LOG:
 * LOG:
 * LOG: Make clock reversal sensing configurable.
 * LOG:
 * LOG: Revision 1.4  1999/07/29 00:08:39  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.3  1999/03/24 22:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.2  1999/03/24 17:38:12  mmiers
 * LOG:
 * LOG:
 * LOG: Formatting.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:11  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.9  1999/03/12 00:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.8  1999/02/04 22:57:41  mmiers
 * LOG:
 * LOG:
 * LOG: Some tweaks, detail improvement.
 * LOG:
 * LOG: Revision 1.7  1999/02/04 22:26:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.6  1998/11/19 21:13:00  mmiers
 * LOG: Build on Solaris.
 * LOG:
 * LOG: Revision 1.5  1998/11/19 15:39:47  mmiers
 * LOG: Fix NT build.
 * LOG:
 * LOG: Revision 1.4  1998/11/19 00:36:25  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.3  1998/09/22 17:28:29  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.2  1998/05/14 20:45:59  mmiers
 * LOG: Remove references to non-associated projects.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 19:00:13  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.1  1998/01/24 21:51:14  mmiers
 * LOG: Move these around a bit.
 * LOG:
 * LOG: Revision 1.2  1998/01/24 21:49:05  mmiers
 * LOG: license.c: Encrypt/decrypt the license file.
 * LOG: crlicense.c: create a license.
 * LOG: mklicense.c: convert a plaintext license to encrypted form.
 * LOG: readlicense.c: read a license file.
 * LOG:
 *
 ****************************************************************************/

#if !defined(TANDEM)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <its.h>
#include <its_license.h>
#include <its_banner.h>
#include <its_timers.h>
#include <its_app.h>
#include <its_crypt.h>
#include <its_mutex.h>

#include "itscore.h"

#ident "$Id: its_license.c,v 9.3.32.1.8.1.2.1.6.1 2014/09/19 07:18:53 jkchaitanya Exp $"

#if defined (unix)
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <sys/stat.h>
#elif defined (WIN32)
#include <windows.h>
#include <winbase.h>
#include <winreg.h>
#include <io.h>
#include <fcntl.h>
#endif

#include <sys/types.h>

#if defined (UNIX)
#include <sys/kernel.h>
#endif

#else /* TANDEM */

#include <stdioh>
#include <stdargh>
#include <stdlibh>
#include <stringh>

#include <itsh>
#include <itslicen>
#include <itsbanne>
#include <itstimer>
#include <itsapph>
#include <itscrypt>
#include <itscoreh>

#endif /* TANDEM */
#include <its_dre_exit_error_codes.h>
#if defined(EXCLUDE_CAPABILITIES)
#undef LICENSE_VerifyCapability
#endif
#if defined(EXCLUDE_LINK_COUNTING)
#undef LICENSE_AddLink
#undef LICENSE_RemLink
#endif

static time_t startTime = 0;
static ITS_INT numLinks = 0;
static ITS_BOOLEAN firstTime = ITS_TRUE;
static ITS_MUTEX licenseGuard;
static ITS_BOOLEAN exiting = ITS_TRUE;

/*
 * key manipulation
 */
ITS_License __its_data;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a license violation notice
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
printNotice(const char *string)
{
    printf("\n");
    printf("-----------------------------------------------------------\n");
    printf("NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE\n");
    printf("-----------------------------------------------------------\n");
    printf("%s\n", string);
    printf("Please contact Diametriq for additional licensing privileges.\n");
    printf("-----------------------------------------------------------\n");
    printf("NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE\n");
    printf("-----------------------------------------------------------\n");
    fflush(stdout);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Verify the host identifier
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
checkMachine()
{
#if defined(unix)
    ITS_UINT t_hostid = 0;
    t_hostid = (ITS_UINT)gethostid();
    if (t_hostid != __its_data.serial_number)
    {
        printNotice("License violation: invalid host id.");

        return (ITS_ENOLICENSE);
    }

#elif defined(WIN32)

#define ITS_KEY_NAME    "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
#define ITS_VALUE_NAME  "ProductId"

    HKEY hKeyResult = 0;
    DWORD type = 0, len = 64;
    ITS_OCTET buf[64];
    ITS_UINT lResult;
    
    lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, ITS_KEY_NAME,
                           0, KEY_QUERY_VALUE, &hKeyResult);

    if (lResult != ERROR_SUCCESS)
    {
        printNotice("License violation: Missing registry key.");

        return (ITS_ENOLICENSE);
    }

    lResult = RegQueryValueEx(hKeyResult, ITS_VALUE_NAME,
                              0, &type, buf, &len);

    if (lResult != ERROR_SUCCESS)
    {
        printNotice("License violation: Missing registry value.");

        RegCloseKey(hKeyResult);

        return (ITS_ENOLICENSE);
    }

    RegCloseKey(hKeyResult);

    if (type != REG_SZ)
    {
        printNotice("License violation: Unexpected reg value type.");

        return (ITS_ENOLICENSE);
    }

    if (memcmp(__its_data.serial_number, buf, len) != 0)
    {
        printNotice("License violation: License invalid.");

        return (ITS_ENOLICENSE);
    }

#endif

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Read a license.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
LICENSE_Load(void)
{
    char buf[ITS_PATH_MAX];
    ITS_Key key;
    int lic_fd;

    if (APPL_GetConfigDir())
    {
        strcpy(buf, APPL_GetConfigDir());
    }
    else
    {
        buf[0] = 0;
    }

    startTime = time(NULL);

    strcat(buf, LICENSE_FILE);

#if defined(unix)
    if ((lic_fd = open(buf, O_RDONLY)) < 0)
#elif defined(WIN32)
    if ((lic_fd = _open(buf, _O_RDONLY)) < 0)
#endif
    {
        printNotice("License violation: Error opening license file.");

        MUTEX_ReleaseMutex(&licenseGuard);

        exiting = ITS_TRUE;

        exit(ITS_LICENSE_FILE_OPENING_ERROR);
    }

#if defined(unix)
    if (read(lic_fd,
             (char *)&__its_data,
             sizeof(ITS_License)) != sizeof(ITS_License))
#elif defined(WIN32)
    if (_read(lic_fd,
              (char *)&__its_data,
              sizeof(ITS_License)) != sizeof(ITS_License))
#endif
    {
        printNotice("License violation: Malformed license data.");

        MUTEX_ReleaseMutex(&licenseGuard);

        exiting = ITS_TRUE;

        exit(ITS_LICENSE_MALFORMED_LICENSE_DATA);
    }

#if defined(UNIX)
    close(lic_fd);
#elif defined(WIN32)
    _close(lic_fd);
#endif

    CRYPT_InitKey(&key, (ITS_OCTET *)ITS_Banner, strlen(ITS_Banner));

    CRYPT_Decrypt(&key, (ITS_OCTET *)&__its_data, sizeof(ITS_License));

    if (__its_data.cookie != ITS_LICENSE_MAGIC)
    {
        printNotice("License violation: Invalid or altered license data.");

        MUTEX_ReleaseMutex(&licenseGuard);

        exiting = ITS_TRUE;

        exit(ITS_LICENSE_INVALID_DATA);
    }
}

/********************************************************
 * motorola specific API for licence load based on 
 * DISABLE_LICENSING flag.
 *******************************************************/

ITSDLLAPI void
LICENSE_LoadIfEnabled(void)
{

#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return;
#endif

    LICENSE_Load();
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update the license file.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

ITSDLLAPI void
LICENSE_Update(void)
{
    char buf[ITS_PATH_MAX];
    ITS_Key key;
    int lic_fd;

    ITS_License TempLicVar;
    memset(&TempLicVar,0,sizeof(ITS_License));

    if (APPL_GetConfigDir())
    {
        strcpy(buf, APPL_GetConfigDir());
    }
    else
    {
        buf[0] = 0;
    }

    startTime = time(NULL);

    strcat(buf, LICENSE_FILE);

    memcpy(&TempLicVar, &__its_data, sizeof(ITS_License));

    CRYPT_InitKey(&key, (ITS_OCTET *)ITS_Banner, strlen(ITS_Banner));
    CRYPT_Encrypt(&key, (ITS_OCTET *)&TempLicVar, sizeof(ITS_License));

#if defined(unix)
    if ((lic_fd = open(buf, O_WRONLY)) < 0)
#elif defined(WIN32)
    if ((lic_fd = _open(buf, _O_WRONLY)) < 0)
#endif
    {
        printNotice("License violation: Error opening license file.");

        MUTEX_ReleaseMutex(&licenseGuard);

        exiting = ITS_TRUE;

        exit(ITS_LICENSE_FILE_OPENING_ERROR);
    }

#if defined(unix)
    if (write(lic_fd,
             (char *)&TempLicVar,
             sizeof(ITS_License)) != sizeof(ITS_License))
#elif defined(WIN32)
    if (_write(lic_fd,
              (char *)&TempLicVar,
              sizeof(ITS_License)) != sizeof(ITS_License))
#endif
    {
        printNotice("Writing error.");

        MUTEX_ReleaseMutex(&licenseGuard);

        exiting = ITS_TRUE;

        exit(ITS_LICENSE_WRITING_ERROR);
    }

#if defined(UNIX)
    close(lic_fd);
#elif defined(WIN32)
    _close(lic_fd);
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Read and validate a license.
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
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1086   Stopped updating the lisence file for 
 *                                        license file growing issue
 *
 ****************************************************************************/
ITSDLLAPI int
LICENSE_Validate(void)
{
/*
    int last = 0;
*/

#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return (ITS_SUCCESS);
#endif

    if (MUTEX_AcquireMutex(&licenseGuard) != ITS_SUCCESS)
    {
        printNotice("License violation: corrupted mutex.");

        exiting = ITS_TRUE;

        exit(ITS_LICENSE_CORRUPTED_MUTEX);
    }

    if (firstTime)
    {
        LICENSE_Load();

        /* make the license match the revision they bought */
        if (__its_data.revision != ITS_LIC_REVISION)
        {
            printNotice("License violation: Version mismatch.");

            exiting = ITS_TRUE;

            exit(ITS_LICENSE_VERSION_MISMATCH);
        }

        if (checkMachine() != ITS_SUCCESS)
        {
            MUTEX_ReleaseMutex(&licenseGuard);

            exiting = ITS_TRUE;

            exit(ITS_LICENSE_INVALID_HOST_ID);
        }
    }

    if (__its_data.expiry != DEFAULT_EXPIRE_TIME)
    {
/*  Stopped updating the last time - For license file growing issue (Mani) */

/*        last = ((__its_data.capabilities[30] << 24 ) +
            (__its_data.capabilities[29] << 16 ) +
            (__its_data.capabilities[28] << 8 ) +
            __its_data.capabilities[27]);

        if (last > time(NULL))
        {
            printNotice("License violation: Date Check Error.");

            MUTEX_ReleaseMutex(&licenseGuard);

            exiting = ITS_TRUE;

            exit(EXIT_FAILURE);
        }

        last = time(NULL);
        __its_data.capabilities[30] = ((last & 0xff000000) >> 24);
        __its_data.capabilities[29] = ((last & 0x00ff0000) >> 16);
        __its_data.capabilities[28] = ((last & 0x0000ff00) >> 8);
        __its_data.capabilities[27] = (last & 0x000000ff);

        LICENSE_Update(); */

        if (__its_data.expiry < time(NULL))
        {
            printf("LICENSE_Validate: License expired.\n");

            MUTEX_ReleaseMutex(&licenseGuard);

            exiting = ITS_TRUE;

            exit(ITS_LICENSE_EXPIRED);
        }

        firstTime = ITS_FALSE;
    }
    else
    {
        firstTime = ITS_FALSE;
    }

    MUTEX_ReleaseMutex(&licenseGuard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Reread and validate a license.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LICENSE_Revalidate(void)
{
    int ret;

    /* note: recursive mutex required. */
    if (MUTEX_AcquireMutex(&licenseGuard) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    firstTime = ITS_TRUE;

    ret = LICENSE_Validate();

    MUTEX_ReleaseMutex(&licenseGuard);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Verify current time is within bounds
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LICENSE_CheckExpiry(void)
{
#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return (ITS_SUCCESS);
#endif

    if (__its_data.expiry != DEFAULT_EXPIRE_TIME)
    {
        /*
         * Brite requirements can't have this check
         */
#if defined(SENSE_CLOCK_REVERSAL)
        static ITS_TIME lastTime = 0;
#endif

        ITS_TIME curTime = time(NULL);

        /*
         * Brite requirements can't have this check
         */
#if defined(SENSE_CLOCK_REVERSAL)
        if (curTime < lastTime)
        {
            printNotice("License violation: Clock reversal sensed.");

            exiting = ITS_TRUE;

            exit(ITS_LICENSE_CLOCK_REVERSED);
        }

        lastTime = curTime;
#endif

        if (__its_data.duration != DEFAULT_DURATION)
        {
            if ((curTime - startTime) > __its_data.duration)
            {
                printf("License violation: License duration exceeded.");

                exiting = ITS_TRUE;

                exit(ITS_LICENSE_DURATION_EXCEEDED);
            }
        }

        if (__its_data.expiry < curTime)
        {
            printf("License violation: License expired.\n");

            exiting = ITS_TRUE;

            exit(ITS_LICENSE_EXPIRED);
        }
    }

    return (ITS_SUCCESS);
}

/*
 * caps to string
 */
static const char *caps[] =
{
    "ANSI_MTP3",
    "ITU_MTP3",
    "ANSI_ISUP",
    "ITU_ISUP",
    "ANSI_SCCP",
    "ITU_SCCP",
    "ANSI_TCAP",
    "ITU_TCAP",
    "INAP",
    "IS41",
    "IS634",
    "AIN",
    "GSMMAP",
    "IS651",
    "LIDB",
    "LNP",
    "ANSI_SNMM",
    "ITU_SNMM",
    "ANSI_SLTM",
    "ITU_SLTM",
    "CHINA_MTP3",
    "CHINA_ISUP",
    "CHINA_SCCP",
    "CHINA_TCAP",
    "CHINA_SNMM",
    "CHINA_SLTM",
    "CAMEL",
    "IS652",
    "IS653",
    "IS826",
    "WIN",
    "JSTD36",
    "BSSAP",
    "TTC_MTP3",
    "TTC_ISUP",
    "TTC_SCCP",
    "TTC_TCAP",
    "TTC_SNMM",
    "TTC_SLTM",
    "DIAMETER",
    "DCCA",
    "RANAP",
    "CAP to Ro (Transatel) IWF",
    "CAP to Ro IWF",
    "MAP to S6a IWF",
    "S6A to MAP IWF"
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Verify a capability (API purchased).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
LICENSE_VerifyCapability(int capability)
{
#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return (ITS_TRUE);
#else

    ITS_BOOLEAN hc = LICENSE_HAS_CAPABILITY(capability, __its_data);
    char buf[ITS_PATH_MAX];

    if (!hc)
    {
        sprintf(buf, "License violation: You are not licensed for "
                "capability: %s", caps[capability]);
        printNotice(buf);
        if(capability != ITS_LIC_IWF_CAP_RO_TSL &&
                capability != ITS_LIC_IWF_CAP_RO &&
                capability != ITS_LIC_IWF_MAP_S6A &&
                capability != ITS_LIC_IWF_S6A_MAP)
        {
            exiting = ITS_TRUE;

            exit(ITS_LICENSE_CAPABILITY_VIOLATION);
        }
    }

    return (hc);
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Verify a capability (API purchased).
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if !defined(LICENSE_CheckCapability)
ITSDLLAPI ITS_BOOLEAN
LICENSE_CheckCapability(int capability)
{
#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return (ITS_TRUE);
#else
    return LICENSE_HAS_CAPABILITY(capability, __its_data);
#endif
}
#endif

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Try to add a link.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LICENSE_AddLink()
{
#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return (ITS_SUCCESS);
#endif

    if (MUTEX_AcquireMutex(&licenseGuard) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    numLinks++;

    if ((ITS_USHORT)numLinks > __its_data.max_links)
    {
        numLinks--;

        MUTEX_ReleaseMutex(&licenseGuard);

        printNotice("Licensed link count exceeded.");

        return (ITS_ENOLICENSE);
    }

    MUTEX_ReleaseMutex(&licenseGuard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove a link.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
LICENSE_RemLink(int capability)
{
#if defined(TANDEM) || defined(DISABLE_LICENSING)
    return;
#endif

    if (MUTEX_AcquireMutex(&licenseGuard) != ITS_SUCCESS)
    {
        return;
    }

    numLinks--;

    if (numLinks < 0)
    {
        numLinks = 0;
    }

    MUTEX_ReleaseMutex(&licenseGuard);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove a link.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
LICENSE_Exiting()
{
    return (exiting);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the license.
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
 *      ITS_SUCCESS
 *
 *  Notes:
 *
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    if (MUTEX_CreateMutex(&licenseGuard, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    return LICENSE_Validate();
}

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
 *  d    None.
 *
 *  Return Value:
 *      a constant pointer to the application name
 *
 *  Notes:
 *
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    MUTEX_DeleteMutex(&licenseGuard);

    firstTime = ITS_TRUE;
}

LICENSE_ClassRec itsLICENSE_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        LICENSE_CLASS_NAME,             /* class name */
        ClassInitialize,                /* class init */
        ClassDestroy,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsLICENSE_Class = (ITS_Class)&itsLICENSE_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Verify return the allowed message rate
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI unsigned int
LICENSE_AllowedMsgRate(void)
{

    if(__its_data.msg_rate != 0xFFFFFFFF)
    {
        printf("License valid for msg rate = %u",__its_data.msg_rate);
    }
    else
    {
        printf("License is not based on msg rate");
    }
    return __its_data.msg_rate;
}
