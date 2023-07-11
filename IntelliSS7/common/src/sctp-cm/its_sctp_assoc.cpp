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
 * LOG: $Log: its_sctp_assoc.cpp,v $
 * LOG: Revision 1.2  2008/06/27 13:54:57  mpatri
 * LOG: Accelero CGI Phase I: To support SCTP Configuration APIs & move to new directory sctp-cm
 * LOG:
 * LOG: Revision 1.1  2008/06/27 13:37:24  mpatri
 * LOG: new directory is created for sctp configuration manager files
 * LOG:
 * LOG: Revision 1.1  2008/06/20 11:29:18  mshanmugam
 * LOG: Accelero CGI Phase I: To support SCTP Configuration APIs
 * LOG:
 * LOG:
 * LOG:
 *
 * ID: $Id: its_sctp_assoc.cpp,v 1.2 2008/06/27 13:54:57 mpatri Exp $
 ****************************************************************************/

#ident "$Id: its_sctp_assoc.cpp,v 1.2 2008/06/27 13:54:57 mpatri Exp $"


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <linux/types.h>
#include <stdlib.h>

#include <engine.h>

#include <its_sctp_cm.h>
#include <its_sctp_event_interface.h>
#include <its_sctp_cm_definitions.h>
//#include <its_sctp_cm_macros.h>


#include <its_sctp_trans.h>

#include <its_ip_trans.h>
#include <string>


#ifdef _SCTP_SCOKET_IETF_DRAFT_11_AND_ABOVE_

#define MSG_UNORDERED   SCTP_UNORDERED
#define MSG_ADDR_OVER   SCTP_ADDR_OVER
#define MSG_ABORT       SCTP_ABORT
#define MSG_EOF         SCTP_EOF

#endif

using namespace std;

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Fills the Local End Point member of SCTPAssociation Object
 *
 *  Input Parameters:
 *        Pointer to localEndPoint 
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *       
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri           16-June-2008                          Initial Code
 ****************************************************************************/

void SCTPAssociation::AddLocalEndPoint(SCTPEndPoint* localEndPoint)
{
        m_LocalEndPoint = localEndPoint ;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Fills the Remote Point member of SCTPAssociation Object
 *
 *  Input Parameters:
 *        Pointer to remoteEndPoint
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
	  none
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           16-June-2008                         Initial Code
 ****************************************************************************/

void SCTPAssociation::AddRemoteEndPoint(SCTPEndPoint* remoteEndPoint)
{
    m_RemoteEndPoint = remoteEndPoint ;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        constructor for SCTPTPAssociation Object
 *
 *  Input Parameters:
 *        Pointer to remoteEndPoint
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
          none
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri           16-June-2008			Initial Code
 ****************************************************************************/

SCTPAssociation::SCTPAssociation()
{
    m_PtrToSCTPAssocProperties = new SCTPAssociationProperties;
  
    m_PtrToSCTPAssocProperties->associationID = (sctp_assoc_t)(0x7fffffff); 
		 /**FIXME: to be checked about the 
                starting value of the Association ID from the ietf draft.*/

    m_PtrToSCTPAssocProperties->state = ITS_SCTP_CLOSED;
    m_LocalEndPoint   = NULL;
    m_RemoteEndPoint  = NULL;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        method to access the value of SCTPTPAssociationProperties of the 
	  SCTPAssociation Object
 *
 *  Input Parameters:
 *        value of SCTPTPAssociationProperties
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *        none
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri           16-June-2008                         Initial Code
 ****************************************************************************/

SCTPAssociationProperties SCTPAssociation::GetSCTPAssociationProperties(void) const
{
    return *m_PtrToSCTPAssocProperties;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        method to access the EndPoint Details of SCTPLocalEndPoint of the
          SCTPAssociation Object
 *
 *  Input Parameters:
 *        value of SCTPTPAssociationProperties
 *
    Input/Output Parameters:
          Address of the SCTPEndPoint structure where the copy of 
	  SCTPLocalEndPoint is to be put.

 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *        none
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008                         Initial Code
 ****************************************************************************/
SCTPEndPoint* SCTPAssociation::GetSCTPLocalEndPoint(void) const
{
    return m_LocalEndPoint;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        method to access the EndPoint Details of SCTPRemoteEndPoint of the
          SCTPAssociation Object
 *  Input Parameters:
 *        value of SCTPTPAssociationProperties
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *        none
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008                         Initial Code
 ****************************************************************************/

SCTPEndPoint* SCTPAssociation::GetSCTPRemoteEndPoint(void) const
{
    return m_RemoteEndPoint;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        copy constructor for SCTPAssociation
          
 *  Input Parameters:
 *        reference to SCTPAssociation object
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *        none
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008			Initial Code
 ****************************************************************************/

SCTPAssociation::SCTPAssociation(const SCTPAssociation& arg_SCTPAssociation)
{
    SCTPAssociationProperties temp_SCTPAssociationProperties= 
						arg_SCTPAssociation.GetSCTPAssociationProperties();
    m_PtrToSCTPAssocProperties= &(temp_SCTPAssociationProperties);
        
    SCTPEndPoint* temp_SCTPLocalEndPoint = GetSCTPLocalEndPoint();
    SCTPEndPoint* temp_SCTPRemoteEndPoint = GetSCTPRemoteEndPoint();
    
    *m_LocalEndPoint  = *temp_SCTPLocalEndPoint;
    *m_RemoteEndPoint = *temp_SCTPRemoteEndPoint;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Crates an SCTPAssociation

 *  Input Parameters:
 *        none
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        ITS_INT
 *
 *  Return Value:
 *        Returns ITS_SUCCESS on successful creation of the Association Object      
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008			Initial Code
 ****************************************************************************/

ITS_INT SCTPAssociation::Enable(void)
{
    int ret = ITS_SUCCESS;

    ITS_USHORT localTrid = 0;
    ITS_USHORT remoteTrid = 0;

    ENGINE_TransportSpecificsPart localInfo;   
    ENGINE_TransportCallbacksPart localCBs;
    ENGINE_TransportSpecificsPart virtualInfo; 
    ENGINE_TransportCallbacksPart virtualCBs;
    
    
    SCTPEndPointProperties arg_SCTPLocalEndPointProperties=
                        m_LocalEndPoint->GetSCTPEndPointProperties();

    SCTPTRAN_Manager* arg_LocalEndPointTransport = m_LocalEndPoint->GetTransport();
    SCTPTRAN_Manager* arg_RemoteEndPointTransport = m_RemoteEndPoint->GetTransport();    


    /* Note:
     We have to allocate everytime we connect since the ENGINE function deletes those when
     the transport is created (See BuildTransport() in resources.c). As a result these do
     not need to be freed in destructor
    */

    localInfo.data.sctpSpecs.udpPart.localHost = (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.udpPart.localPort = (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.udpPart.associates = (char **)CONFIG_MALLOC(sizeof(char *));
    localInfo.data.sctpSpecs.udpPart.associates[0] = (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.maxInStreams =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.numOutStreams =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.maxAttempts =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.cookieLife =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.hbOn =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.initTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.sendTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.recvTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.hbTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.shutdownTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.pmtuTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.isClient =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.payloadType =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));

    localInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;

    strcpy(localInfo.data.sctpSpecs.udpPart.localHost,
                                        (arg_SCTPLocalEndPointProperties.primaryIPAddress).c_str());
    sprintf(localInfo.data.sctpSpecs.udpPart.localPort,"%d",
                                (arg_SCTPLocalEndPointProperties.port));
    strcpy(localInfo.data.sctpSpecs.udpPart.associates[0] ,
                                (arg_SCTPLocalEndPointProperties.name).c_str());
    strcat(localInfo.data.sctpSpecs.udpPart.associates[0] , ASSOC_REMOTE_NAME_STRING);
    strcpy(localInfo.data.sctpSpecs.payloadType ,
                                (arg_SCTPLocalEndPointProperties.family).c_str());
    strcat(localInfo.data.sctpSpecs.payloadType , "-M3UA");
    localInfo.data.sctpSpecs.udpPart.numAssociates = 1;
    sprintf(localInfo.data.sctpSpecs.maxInStreams, "%d",
                                (arg_SCTPLocalEndPointProperties.maxInboundStreams));
    sprintf(localInfo.data.sctpSpecs.numOutStreams, "%d",
                                (arg_SCTPLocalEndPointProperties.numOutboundStreams));
    strcpy(localInfo.data.sctpSpecs.isClient ,"yes"); 
				 /** FIXME: point to check -- whether 
                                 isClient is to be initialized to"yes" or "no" **/
   
     sprintf(localInfo.data.sctpSpecs.maxAttempts ,"%d",
                                (arg_SCTPLocalEndPointProperties.initMaxAttempts));
    
    //
    // Multihoming
    //
    localInfo.data.sctpSpecs.numExtraHomes = arg_SCTPLocalEndPointProperties.secondaryIPAddress.size();
    if (localInfo.data.sctpSpecs.numExtraHomes)
    {
        localInfo.data.sctpSpecs.extraHomes = (char**)CONFIG_MALLOC
				((arg_SCTPLocalEndPointProperties.secondaryIPAddress.size()) * sizeof(char*));
        for (int i = 0; i < arg_SCTPLocalEndPointProperties.secondaryIPAddress.size(); i++)
        {
            localInfo.data.sctpSpecs.extraHomes[i] = (char*)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(localInfo.data.sctpSpecs.extraHomes[i],
					arg_SCTPLocalEndPointProperties.secondaryIPAddress[i].c_str());
        }
    }

    strcpy(localInfo.data.sctpSpecs.cookieLife ,
                                        arg_SCTPLocalEndPointProperties.cookieLife);
    strcpy(localInfo.data.sctpSpecs.hbOn ,
                                        arg_SCTPLocalEndPointProperties.hbOn);
    strcpy(localInfo.data.sctpSpecs.initTimeOut ,
                                        arg_SCTPLocalEndPointProperties.initTimeOut);
    strcpy(localInfo.data.sctpSpecs.sendTimeOut ,
                                        arg_SCTPLocalEndPointProperties.sendTimeOut);
    strcpy(localInfo.data.sctpSpecs.recvTimeOut ,
                                        arg_SCTPLocalEndPointProperties.recvTimeOut);
    strcpy(localInfo.data.sctpSpecs.hbTimeOut ,
                                        arg_SCTPLocalEndPointProperties.hbTimeOut);
    strcpy(localInfo.data.sctpSpecs.shutdownTimeOut ,
                                        arg_SCTPLocalEndPointProperties.shutdownTimeOut);
    strcpy(localInfo.data.sctpSpecs.pmtuTimeOut ,
                                        arg_SCTPLocalEndPointProperties.pmtuTimeOut);
    
    virtualInfo.data.sctpSpecs.udpPart.localHost = (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    virtualInfo.data.sctpSpecs.udpPart.localPort = (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));


    std::string temp_RemotePrimaryIP =  m_RemoteEndPoint->GetPrimaryIP();
    ITS_USHORT temp_RemotePort = m_RemoteEndPoint->GetPort();

    
    strcpy(virtualInfo.data.sctpSpecs.udpPart.localHost, temp_RemotePrimaryIP.c_str());
    sprintf(virtualInfo.data.sctpSpecs.udpPart.localPort,"%d", temp_RemotePort);

    virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
    virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
    virtualInfo.data.sctpSpecs.numExtraHomes = 0;
     
    /*** Filling the Call Back Structure  --starts-- ***/

    /**FIXME:  These members of the call back structure
     needs to be initialized with proper values,
     instead of assigning them to NULL --starts-- **/

    localCBs.libName = "";
    localCBs.preInit = "";
    localCBs.postInit = "";
    localCBs.preNextEvent = "";
    localCBs.postNextEvent = "";
    localCBs.nextEventFailed = "";
    localCBs.dispUser = "";

    /** FIX ME: --ends-- **/

    /*** Filling the Call Back Structure  --ends-- ***/

    memset(&virtualCBs, 0, sizeof(ENGINE_TransportCallbacksPart));  
                               // Filling the Call Back Structure  for remote Transport


    //
    // 1) Create Virtual Instance
    //
    ret = ENGINE_AddTransport(localInfo.data.sctpSpecs.udpPart.associates[0],
                              "Virtual",
                              (char*)(m_RemoteEndPoint->GetFamily()).c_str(),
                              "SCTP",
                              virtualInfo, &virtualCBs);
    
    if (ret <= 0)
    {
        return ITS_ENOTRANSPORT;
    }

    remoteTrid = (ITS_USHORT)ret;

    /**FIXME:TRANSPORT_FindTransport is used to get the SCTPTRAN_Manager
             from Transport ID of the EndPoint  **/

    TRANSPORT_Control *temp_RemoteTransport = TRANSPORT_FindTransport(remoteTrid);
    arg_RemoteEndPointTransport = (SCTPTRAN_Manager*)temp_RemoteTransport ;

    //m_RemoteEndPoint->SetTransport(arg_RemoteEndPointTransport); 
        	/* setting the transport of the remoteEndPoint;
		commented as we are not maintaining SCTPTRAN_Manager at
		the EndPoint level, we are only maintaining TrId*/
								    	
    m_RemoteEndPoint->SetTrId(remoteTrid);  
                     //setting the transport ID of remoteEndPoint

    
    //
    // 2) Create Local Instance
    //
    ret = ENGINE_AddTransport((char*)m_LocalEndPoint->GetName().c_str(),
                              "Datagram",
                              (char*)m_LocalEndPoint->GetFamily().c_str(),
                              "SCTP MTP3",
                              localInfo, &localCBs);
    
    
    if (ret <= 0)
    {
        return ITS_ENOTRANSPORT;
    }

    localTrid = (ITS_USHORT)ret;
 
    TRANSPORT_Control *temp_LocalTransport = TRANSPORT_FindTransport(localTrid);
    arg_LocalEndPointTransport = (SCTPTRAN_Manager*)temp_LocalTransport ;

    //m_LocalEndPoint->SetTransport(arg_LocalEndPointTransport); 
		/*setting the transport of LocalEndPoint;
		commented as we are not maintaining SCTPTRAN_Manager at
                the EndPoint level, we are only maintaining TrId*/

    m_LocalEndPoint->SetTrId(localTrid);          
             //setting transport ID of LocalEndPoint
      
     return (ITS_SUCCESS);    
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Gets the AssociationID of an SCTPAssociation

 *  Input Parameters:
 *        none
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        sctp-assoc_t
 *
 *  Return Value:
 *        retuns the Association ID
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008			Initial Code
 ****************************************************************************/

sctp_assoc_t SCTPAssociation::GetAssociationID(void)
{
    return (m_PtrToSCTPAssocProperties->associationID);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Disables SCTPAssociation

 *  Input Parameters:
 *        none
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        sctp-assoc_t
 *
 *  Return Value:
 *        retuns the Association ID
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008			Initial Code
 ****************************************************************************/


int SCTPAssociation::Disable(void)
{
    SCTPEndPointProperties temp_LocalEndPointProperties = m_LocalEndPoint->GetSCTPEndPointProperties();
    
    if(temp_LocalEndPointProperties.type == SCTP_ENDPOINT_CLIENT)
    {
        int ret_client = ITS_SUCCESS;
        TRANSPORT_Control *tc = NULL;
        ITS_USHORT localTrid = m_LocalEndPoint->GetTrId();
 
        if((tc = TRANSPORT_FindTransport(localTrid)) != NULL)
        {
            SOCKTRAN_RETRY_COUNT((SOCKTRAN_Manager*)tc) = 0;
        }
        
        TRANSPORT_UnfindTransport(tc);
        
        ret_client = ENGINE_DeleteTransport(localTrid);
        if (ret_client == ITS_SUCCESS)
        {
            m_LocalEndPoint->SetTrId(0);
            m_RemoteEndPoint->SetTrId(0);
            m_PtrToSCTPAssocProperties->state= ITS_SCTP_CLOSED;
        }

        
        //return ret_client;
    }
    else
        if(temp_LocalEndPointProperties.type == SCTP_ENDPOINT_SERVER)    
        {
            SCTP_API_MSG_HDR msg;
	    SCTP_API_IOVEC iovec;
            SCTP_API_CMSG cmsg;
            msg.name = (char *) SOCKTRAN_CONNECT(m_LocalEndPoint->GetTransport())->addr;
            msg.nameLen  = sizeof(SOCK_AddrStore);
            msg.ioVecs   = &iovec;
            msg.numIOVecs= 1;
            iovec.vector = NULL;
            iovec.len    = 0;
            msg.control = (ITS_POINTER)&cmsg;
            msg.controlLen = sizeof(cmsg);
            cmsg.hdr.len = sizeof(SCTP_API_SND_RCV);
            cmsg.hdr.type = SCTP_SNDRCV;
            cmsg.hdr.level = IPPROTO_SCTP;
            cmsg.data.sndRcv.flags = MSG_EOF /*SCTP_EOF*/;
            SCTPTRAN_SENDMSG(ITS_OBJ_CLASS(m_LocalEndPoint->GetTransport()))
                   (m_LocalEndPoint->GetTransport(),
                    &msg,
                    SCTP_API_SYNC);    //changed the first parameter as the the Send Msg function takes 
				       //SCTPTRAN_Manager* as the first parameter
       }

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Sets the AssociationID of an SCTPAssociation

 *  Input Parameters:
 *        sctp_assoc_t
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *        retuns the Association ID
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008			Initial Code
 ****************************************************************************/

void SCTPAssociation::SetAssociationID(sctp_assoc_t AssocID)
{
    m_PtrToSCTPAssocProperties->associationID = AssocID;    
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Sets the state of an SCTPAssociation

 *  Input Parameters:
 *        sctp_assoc_t
 *
 *  Input/Output Parameters:
 *        none
 *
 *  Output Parameters:
 *        none
 *
 *  Return Value:
 *        retuns the Association ID
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           27-MAY-2008			Initial Code
 ****************************************************************************/
void SCTPAssociation::SetAssociationState(ITS_SCTP_STATE AssocState)
{
    m_PtrToSCTPAssocProperties->state = AssocState;
}



