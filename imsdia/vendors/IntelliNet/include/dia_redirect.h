/*********************************-HPP-**************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_redirect.h,v $
 * LOG: Revision 1.2  2009/02/19 13:17:26  ssaxena
 * LOG: Change in signature of HandleRedirectReqMsg from its::Event to
 * LOG: ITS_USHORT. Performance changes(Viji).
 * LOG:
 * LOG: Revision 1.1  2009/02/03 10:09:42  ssaxena
 * LOG: Added a new header for Redirect Agent functionality.
 * LOG:
 * ID: $Id: dia_redirect.h,v 1.2 2009/02/19 13:17:26 ssaxena Exp $
 ****************************************************************************/
#ident "$Id: dia_redirect.h,v 1.2 2009/02/19 13:17:26 ssaxena Exp $"

#if !defined DIA_REDIRECT_H
#define DIA_REDIRECT_H
 
#include <dia_realm_table.h>
 
#define MAX_LEN_APPID                10
#define MAX_USG                      6
 
typedef enum  _its_dia_redirect_usage
{
    DONT_CACHE=0,
    ALL_SESSION,
    ALL_REALM,
    REALM_AND_APPLICATION,
    ALL_APPLICATION,
    ALL_HOST,
    ALL_USER
}
REDIRECT_USAGE;
 
typedef enum  _usage_precedence
{
    SESSION = 1,
    USER,
    REALM_AND_APP,
    REALM,
    APPLICATION,
    HOST
}
USG_PRECEDNCE;
 
 
/*.Interface: DiaRedirectHandler 
 *****************************************************************************
 *  Interface:
 *      DiaRedirectHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from the Network.  
 *****************************************************************************/
class DiaRedirectHandler
{
public:
    /*.implementation:public,inline,DiaRedirectHandler
    ************************************************************************
    *  Purpose:
    *       DiaRedirectHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaRedirectHandler () {}
 
 
    /*.implementation:public,inline,DiaRedirectHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaRedirectHandler
    *           
    ************************************************************************/
    ~DiaRedirectHandler() {}
 
 
    /*.implementation:public,DiaRedirectHandler
    ************************************************************************
    *  Purpose:
    *      Redirect Agent process the request received.  
    *           
    ************************************************************************/
    static int HandleRedirectReqMsg( DIA_BASE_CMD *&bCmd,
                                     REALM_ENTRY *&rEntry,
                                     ITS_USHORT inst);
 
 
    /*.implementation:public,DiaRedirectHandler
    ************************************************************************
    *  Purpose:
    *      Node which requested the redirect information, process the answer  
    *      received from redirect agent.     
    ************************************************************************/
    static int HandleRedirectedAnsMsg( DIA_BASE_CMD *&bCmd,
                                       PEER_ENTRY *&pEntry );
 
 
    /*.implementation:public,DiaRedirectHandler
    ************************************************************************
    *  Purpose:
    *      Check in Local Cache Table.  
    *           
    ************************************************************************/
    static bool CheckInLocalCache( DIA_BASE_CMD *&bCmd,
                                   SESSION_ENTRY *&sessInfo,
                                   ITS_USHORT &peerInstance,
                                   REALM_ENTRY *rEntry );
 
private:
 
};
 
#endif
