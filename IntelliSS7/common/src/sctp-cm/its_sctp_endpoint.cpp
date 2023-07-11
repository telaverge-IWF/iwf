/*********************************-*-H-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
 *
 * LOG: $Log: its_sctp_endpoint.cpp,v $
 * LOG: Revision 1.2  2008/06/27 14:08:02  mpatri
 * LOG: Accelero CGI Phase I: To support SCTP Configuration APIs & move to new directory sctp-cm
 * LOG:
 * LOG: Revision 1.1  2008/06/27 13:37:24  mpatri
 * LOG: new directory is created for sctp configuration manager files
 * LOG:
 * LOG: Revision 1.1  2008/06/20 11:33:28  mpatri
 * LOG: Accelero CGI Phase I: Support for SCTP Configuration APIs
 * LOG:
 * LOG:
 * LOG:
 *
 * ID: $Id: its_sctp_endpoint.cpp,v 1.2 2008/06/27 14:08:02 mpatri Exp $
 ****************************************************************************/

#ident "$Id: its_sctp_endpoint.cpp,v 1.2 2008/06/27 14:08:02 mpatri Exp $"


#include <algorithm>
#include <vector>
#include <string>     
#include <string.h>

#include <its_sctp_cm.h>
#include <its_sctp_event_interface.h>
#include <its_sctp_cm_definitions.h>

using namespace std;

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Sets the Primary IP Address of SCTPEndPoint Class
 *
 *  Input Parameters:
 *      IPAddress
 * 
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri           6-June-2008   			Initial Code 
 ****************************************************************************/


void SCTPEndPoint::SetPrimaryIP(std::string  IPAddress)
{
    m_SCTPEndPointProperties->primaryIPAddress = IPAddress;
    m_SCTPEndPointProperties->hasLocalIP = true ;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Sets the port of SCTPEndPoint Class
 *
 *  Input Parameters:
 *      IPAddress
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri          6-June-2008				Initial Code
 ****************************************************************************/


void SCTPEndPoint::SetPort(ITS_USHORT port)
{
    m_SCTPEndPointProperties->port = port;
    m_SCTPEndPointProperties->hasLocalPort = true;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Sets the type of SCTPEndPoint
 *
 *  Input Parameters:
 *      IPAddress
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/


void SCTPEndPoint::SetType(SCTP_ENDPOINT_TYPE type)
{
    m_SCTPEndPointProperties-> type = type;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Sets the type of SCTPEndPoint
 *
 *  Input Parameters:
 *      IPAddress
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/
#if 0

void SCTPEndPoint::SetTransport(SCTPTRAN_Manager* transport)
{
    *m_SCTPEndPointTransport = *transport;
}
#endif 

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Adds new secondary IPAddress for a SCTPEndPoint
 *
 *  Input Parameters:
 *      IPAddress
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/

void SCTPEndPoint::AddSecondaryIP(std::string  IPAddress)
{
   m_SCTPEndPointProperties->secondaryIPAddress.push_back(IPAddress);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Gets the primary IPAddress of a EndPoint
 *
 *  Input Parameters:
 *      void
 *
 *  Output Parameters:
 *      std::string
 *
 *  Return Value:
 *      Primary IPAddress of EndPoint
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/

std::string SCTPEndPoint::GetPrimaryIP(void) const
{
    return m_SCTPEndPointProperties->primaryIPAddress;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Gets the SCTPTRAN_Manager structure maintained for a EndPoint
 *
 *  Input Parameters:
 *      none
 *
 *  Output Parameters:
 *      SCTPTRAN_Manager*
 *
 *  Return Value:
 *      Pointer to SCTPTRAN_Manager manager structure maintained for that endpont
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/

SCTPTRAN_Manager* SCTPEndPoint::GetTransport(void) const
{
   TRANSPORT_Control *tc = TRANSPORT_FindTransport(m_TrId);

   return (SCTPTRAN_Manager*)tc;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      returns the Transport to Accelero Transport module
 *
 *  Input Parameters:
 *      pointer to TRANSPORT_Control structure
 *
 *  Output Parameters:
 *      none
 *
 *  Return Value:
 *      none
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/

void SCTPEndPoint::ReturnTransport(TRANSPORT_Control *tc) 
{
    TRANSPORT_UnfindTransport(tc);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get the secondary IPAddress of a EndPoint
 *
 *  Input Parameters:
 *      none
 *
 *  Output Parameters:
 *      std::vector<std::string>
 *
 *  Return Value:
 *      Returning the vector of Secondary IPAddresses
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/

std::vector<std::string> SCTPEndPoint::GetSecondaryIPVector(void) const
{
    return (m_SCTPEndPointProperties->secondaryIPAddress);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Constructor of SCTPEndPoint class
 *
 *  Input Parameters:
 *      1. association name
        2. association family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
    
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           24-MAY-2008			Initial Code
 ****************************************************************************/

SCTPEndPoint::SCTPEndPoint(const string& assocName, const string& assocFamily)
{
   
    m_SCTPEndPointProperties = new SCTPEndPointProperties;
    
    m_TrId = 0; //FIXME: to be decided about the default value of m_TrId                                      

    m_SCTPEndPointProperties-> name              = assocName;
    m_SCTPEndPointProperties-> family            = assocFamily;
     
    //m_SCTPEndPointProperties-> primaryIPAddress  = NULL;

    m_SCTPEndPointProperties->hasLocalIP         = false;
    m_SCTPEndPointProperties->hasLocalPort       = false;
    
    m_SCTPEndPointProperties->numOutboundStreams = ASSOC_DFLT_OUT_STREAM;
    m_SCTPEndPointProperties->maxInboundStreams  = ASSOC_DFLT_IN_STREAM;
    m_SCTPEndPointProperties->initMaxAttempts    = ASSOC_DFLT_MAX_INIT;

    m_SCTPEndPointProperties->cookieLife         = "30";
    m_SCTPEndPointProperties->hbOn	         = "yes";
    m_SCTPEndPointProperties->initTimeOut        = "5,0";
    m_SCTPEndPointProperties->sendTimeOut        = "1,0";
    m_SCTPEndPointProperties->recvTimeOut        = "0,300";
    m_SCTPEndPointProperties->hbTimeOut          = "10,0";
    m_SCTPEndPointProperties->shutdownTimeOut    = "5,0";
    m_SCTPEndPointProperties->pmtuTimeOut        = "600,0";
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get the EndPointProperties of a SCTP EndPoint
 *
 *  Input Parameters:
 *      none
 *
 *  Output Parameters:
 *      SCTPEndPointProperties 
 *
 *  Return Value:
 *      Returns SCTPEndPointProperties by value
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ****************************************************************************/

SCTPEndPointProperties SCTPEndPoint::GetSCTPEndPointProperties(void) const
{
    return (*m_SCTPEndPointProperties);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Get the SCTPAssociationBackwardRef vector(used for backward reference ) of a SCTP EndPoint
 *
 *  Input Parameters:
 *      none
 *
 *  Output Parameters:
 *     reference to backward reference vector
 *
 *  Return Value:
 *      none
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/

std::vector<SCTPAssociation*>& SCTPEndPoint::GetSCTPAssociationBackwardRef(void)
{
    return m_SCTPAssociationBackwardRef;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      copy constructor for SCTPEndPoint Class
 *
 *  Input Parameters:
 *      constant reference to SCTPEndPoint
 *
 *  Input/Output Parameters:
 *      none
 *
 *  Output Parameters:
 *      none
 *
 *  Return Value:
 *      none
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/

SCTPEndPoint::SCTPEndPoint(/*const*/ SCTPEndPoint& arg_SCTPEndPoint)
{
    m_SCTPEndPointProperties = new SCTPEndPointProperties;

    SCTPEndPointProperties arg_SCTPEndPointProperties = *(arg_SCTPEndPoint.m_SCTPEndPointProperties);
    std::vector<SCTPAssociation*>& arg_SCTPAssociationBackwardRef =
                                              arg_SCTPEndPoint.m_SCTPAssociationBackwardRef ;
                                                    
    /**assigning the m_SCTPEndPointProperties --starts-- */    
    (m_SCTPEndPointProperties->primaryIPAddress).assign( (arg_SCTPEndPoint.m_SCTPEndPointProperties)->
									primaryIPAddress); //copying string

    copy(((arg_SCTPEndPoint.m_SCTPEndPointProperties)->secondaryIPAddress).begin(),
 			   (((arg_SCTPEndPoint.m_SCTPEndPointProperties))->secondaryIPAddress).end(),
				    m_SCTPEndPointProperties->secondaryIPAddress.begin());//copying vector

    m_SCTPEndPointProperties->port =  (arg_SCTPEndPoint.m_SCTPEndPointProperties)->port;
    m_SCTPEndPointProperties->type =(arg_SCTPEndPoint.m_SCTPEndPointProperties)->type;
    m_SCTPEndPointProperties->hasLocalIP = (arg_SCTPEndPoint.m_SCTPEndPointProperties)->hasLocalIP;  
    m_SCTPEndPointProperties->hasLocalPort = (arg_SCTPEndPoint.m_SCTPEndPointProperties)->hasLocalPort;
    
    (m_SCTPEndPointProperties->name).assign(arg_SCTPEndPoint.m_SCTPEndPointProperties->name); //copying string

    (m_SCTPEndPointProperties->family).assign(arg_SCTPEndPoint.
                                        m_SCTPEndPointProperties->family); //copying string

    m_SCTPEndPointProperties->minRetransmitTimeout =
				  (arg_SCTPEndPoint.m_SCTPEndPointProperties)->minRetransmitTimeout;
    m_SCTPEndPointProperties->maxRetransmitTimeout =
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->maxRetransmitTimeout;
    m_SCTPEndPointProperties->pathMaxRetransmit =
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->pathMaxRetransmit;
    m_SCTPEndPointProperties->assocMaxRetransmit =
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->assocMaxRetransmit;
    m_SCTPEndPointProperties->maxInboundStreams =
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->maxInboundStreams;
    m_SCTPEndPointProperties->numOutboundStreams=
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->numOutboundStreams;
    m_SCTPEndPointProperties->initMaxAttempts=
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->initMaxAttempts;
    m_SCTPEndPointProperties->SACKDelay=
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->SACKDelay;
    m_SCTPEndPointProperties->hbInterval=
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->hbInterval;
    m_SCTPEndPointProperties->txBufferSize=
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->txBufferSize;
    m_SCTPEndPointProperties->rxBufferSize=
                                 (arg_SCTPEndPoint.m_SCTPEndPointProperties)->rxBufferSize;
    strcpy(m_SCTPEndPointProperties->cookieLife,  (arg_SCTPEndPoint.m_SCTPEndPointProperties)->cookieLife);
    strcpy(m_SCTPEndPointProperties->hbOn,        (arg_SCTPEndPoint.m_SCTPEndPointProperties)->hbOn);
    strcpy(m_SCTPEndPointProperties->initTimeOut, (arg_SCTPEndPoint.m_SCTPEndPointProperties)->initTimeOut);
    strcpy(m_SCTPEndPointProperties->sendTimeOut, (arg_SCTPEndPoint.m_SCTPEndPointProperties)->sendTimeOut);
    strcpy(m_SCTPEndPointProperties->recvTimeOut, (arg_SCTPEndPoint.m_SCTPEndPointProperties)->recvTimeOut);
    strcpy(m_SCTPEndPointProperties->hbTimeOut, (arg_SCTPEndPoint.m_SCTPEndPointProperties)->hbTimeOut);

    strcpy(m_SCTPEndPointProperties->shutdownTimeOut,
                                         (arg_SCTPEndPoint.m_SCTPEndPointProperties)->shutdownTimeOut);
    strcpy(m_SCTPEndPointProperties->pmtuTimeOut,(arg_SCTPEndPoint.m_SCTPEndPointProperties)->pmtuTimeOut);
    
    /** assigning the m_SCTPEndPointProperties --ends--  */

    /** assigning the m_SCTPAssociationBackwardRef --starts--  */

    copy((arg_SCTPAssociationBackwardRef).begin(),
		(arg_SCTPAssociationBackwardRef).end(),
                      			m_SCTPAssociationBackwardRef.begin());
						 
    /** assigning the Transport ID   */
    m_TrId = arg_SCTPEndPoint.m_TrId ;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Gets the port id of the endpoint
 *
 *  Input Parameters:
 *      none
 *
 *  Input/Output Parameters:
 *      none
 *
 *  Output Parameters:
 *      ITS_USHORT
 *
 *  Return Value:
 *      Port no.
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/

ITS_USHORT SCTPEndPoint::GetPort(void) const
{
    return m_SCTPEndPointProperties->port;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Gets the Transport id of the endpoint
 *
 *  Input Parameters:
 *      none
 *
 *  Input/Output Parameters:
 *      none
 *
 *  Output Parameters:
 *      ITS_USHORT
 *
 *  Return Value:
 *      Transport Id
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/

ITS_USHORT SCTPEndPoint::GetTrId(void) const
{
    return m_TrId;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Sets the Transport id of the endpoint
 *
 *  Input Parameters:
 *      Transport ID
 *
 *  Input/Output Parameters:
 *      none
 *
 *  Output Parameters:
 *      ITS_USHORT
 *
 *  Return Value:
 *      none
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/

void SCTPEndPoint::SetTrId(ITS_USHORT TrId)
{
    m_TrId = TrId;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Gets the family name of the EndPoint
 *
 *  Input Parameters:
 *      none
 *
 *  Input/Output Parameters:
 *      none
 *
 *  Output Parameters:
 *      std::string
 *
 *  Return Value:
 *      none
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/
std::string SCTPEndPoint::GetFamily(void) const
{
    return m_SCTPEndPointProperties->family;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Gets the name of the EndPoint
 *
 *  Input Parameters:
 *      none
 *
 *  Input/Output Parameters:
 *      none
 *
 *  Output Parameters:
 *      std::string
 *
 *  Return Value:
 *      none
 *
 *  Revision History:
 *
 *  Notes:
 *
 *  See Also:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           26-MAY-2008			Initial Code
 ***************************************************************************/
std::string SCTPEndPoint::GetName(void) const
{
    return m_SCTPEndPointProperties->name;
}


