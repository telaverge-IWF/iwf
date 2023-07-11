/****************************************************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: app.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/04/28 06:57:12  nvijikumar
 * LOG: Code Enhancements (Documentation)
 * LOG:
 * LOG: Revision 1.1  2006/04/13 11:08:06  nvijikumar
 * LOG: Baseline demo programs
 * LOG:
 * LOG:
 *
 * ID: $Id: app.cpp,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $
 *
 ***************************************************************************/

#include <app.h>

const char* orHost;
const char* orRealm;
const char* dhHost;
const char* drRealm;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Utility methods that are used to get the user configured values
 *     that are passed as commandLine options to the sample program
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
 *     Appropriate (OriginHost, OriginRealm, DestinationHost, DestinationRealm)
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginHost() 
{
    return orHost;
}
const char* GetOriginRealm() 
{
    return orRealm;
}
const char* GetDestinationHost() 
{
    return dhHost;
}
const char* GetDestinationRealm() 
{
    return drRealm;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     Utility methods that are used to set the user configured values
 *     that are passed as commandLine options to the sample program
 *
 *  Input Parameters:
 *     Appropriate (OriginHost, OriginRealm, DestinationHost, DestinationRealm)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void SetOriginHost(const char* OriginHost) 
{
    orHost = strdup(OriginHost);
}
void SetOriginRealm(const char* OriginRealm) 
{
    orRealm = strdup(OriginRealm);
}

void SetDestinationHost(const char* DestinationHost) 
{
    dhHost = strdup(DestinationHost);
}
void SetDestinationRealm(const char* DestinationRealm) 
{
    drRealm = strdup(DestinationRealm);
}


