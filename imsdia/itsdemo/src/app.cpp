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
 * LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/04/25 15:24:40  nvijikumar
 * LOG: Code Enhancement (Documentation, Flowerboxes)
 * LOG:
 * LOG: Revision 1.2  2006/03/20 06:36:54  yranade
 * LOG: Cleanups.
 * LOG:
 * LOG: Revision 1.1  2006/03/18 12:35:41  nvijikumar
 * LOG: Program to get the Host(Origin/Dest) and Realm (Origin/Dest)
 * LOG:
 * LOG:
 *
 * ID: $Id: app.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $
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
 *     Method to get OriginHost  
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
 *     orHost - type char 
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginHost() 
{
    return orHost;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get OriginRealm 
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
 *     orRealm - type char
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginRealm() 
{
    return orRealm;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get DestinationHost 
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
 *     dhHost - type char
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetDestinationHost() 
{
    return dhHost;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get DestinationRealm 
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
 *     dhRealm - type char
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetDestinationRealm() 
{
    return drRealm;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set OriginHost 
 *
 *  Input Parameters:
 *      OriginHost - type char.
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

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set OriginRealm 
 *
 *  Input Parameters:
 *      OriginRealm - type char.
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
void SetOriginRealm(const char* OriginRealm) 
{
    orRealm = strdup(OriginRealm);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set DestinationHost
 *
 *  Input Parameters:
 *      DestinationHost - type char.
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
void SetDestinationHost(const char* DestinationHost) 
{
    dhHost = strdup(DestinationHost);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set DestinationRealm 
 *  
 *  Input Parameters:
 *      DestinationRealm - type char.
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
void SetDestinationRealm(const char* DestinationRealm) 
{
    drRealm = strdup(DestinationRealm);
}


