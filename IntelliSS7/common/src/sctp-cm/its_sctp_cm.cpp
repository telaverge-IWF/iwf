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
 * LOG: $Log: its_sctp_cm.cpp,v $
 * LOG: Revision 1.2  2008/06/27 14:03:13  mpatri
 * LOG: Accelero CGI Phase I: To support SCTP Configuration APIs & move to new directory sctp-cm
 * LOG:
 * LOG: Revision 1.1  2008/06/27 13:37:24  mpatri
 * LOG: new directory is created for sctp configuration manager files
 * LOG:
 * LOG: Revision 1.1  2008/06/20 11:31:22  mpatri
 * LOG: Accelero CGI Phase I: Support for SCTP Configuration APIs
 * LOG:
 * LOG:
 * LOG:
 *
 * ID: $Id: its_sctp_cm.cpp,v 1.2 2008/06/27 14:03:13 mpatri Exp $
 ****************************************************************************/

#ident "$Id: its_sctp_cm.cpp,v 1.2 2008/06/27 14:03:13 mpatri Exp $"


/******************************
 * Include Files
 *****************************/


#include <vector>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <linux/types.h>

#include <engine.h>
#include <its_types.h>

#include <its_sctp_cm.h>
#include <its_sctp_event_interface.h>
#include <its_sctp_cm_definitions.h>

using namespace std;

TQUEUETRAN_Manager* SCTPCM_EventRcvQueue = NULL ;

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Initializes the SCTP Configuration Manager
 *
 *  Input Parameters:
 *        none
 *
 *  Input/Output Parameters:
 *        none.
 *
 *  Output Parameters:
 *        ITS_INT
 *
 *  Return Value:
 *	  Returns ITS_SUCCESS on successfully registering the callback
 *        Returns the error code returned by on CALLBACK_AddCallback on failure
  
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri          16-June-2008				Initial Code
 ****************************************************************************/

ITS_INT SCTPConfigurationManager::Initialize(void)
{
    int ret_CBAdd, ret_ThreadCreate;

    /* Call to add the SCTPCM_SCTPTransCallback to the
     SCTPTRAN_ManagementCallbacks list*/

    ret_CBAdd = CALLBACK_AddCallback(SCTPTRAN_ManagementCallbacks, 
                             SCTPCM_SCTPTransCallback,   
                             NULL);

   /**FIXME:Find Appropiate value for the SCTPCM_MSGQ_ID, and also decide what 
   should be the third parameter of the TQUEUETRAN_CreateTransport **/
  
   SCTPCM_EventRcvQueue = TQUEUETRAN_CreateTransport("SCTPCM_EventQueue",
                                                                SCTPCM_MSGQ_ID ,
                                                               ITS_TRANSPORT_TQUEUE );
    
   ret_ThreadCreate = THREAD_CreateThread(&m_SCTPCM_EventRcvThread, 
                               0,
                               SCTPConfigManagerThreadFunc, 
                               this, 
                               ITS_TRUE);
                                                               
   if((SCTPCM_EventRcvQueue!= NULL)&&(ret_CBAdd == ITS_SUCCESS))
   {
       isInitialized = YES ;
       return ITS_SUCCESS;
   }

   /**FIXME:An error code value for ESCTPCMINITIALIZEFAIL has 
   to be decided in case of failure of the 
   above if condition and that error code has to be returned in 
   case of failure. **/

   else
   {
       return ESCTPCMINITIALIZEFAIL;
   }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Registers Event receive object
 *
 *  Input Parameters:
 *        Pointer to the Event receive object
 *
 *  Output Parameters:
 *        ITS_INT
 *
 *  Return Value:
 *        Returns ITS_SUCCESS on successfully registering the ISCTPEvent implemetor object.
 *	  Returns ITS_EBADSTATE otherwise

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * mpatri           16-June-2008			Initial Code
 ****************************************************************************/


ITS_INT SCTPConfigurationManager::RegisterSCTPEventReceiver(ISCTPEvent* SCTPEventSink)
{
    ISCTPEvent* m_ISCTPEventRegPtr ;
	
    /* Register SCTPEventSink, if sctp configuration 
    manager is successfully initialized*/

    if(isInitialized == YES)	
    {
	m_ISCTPEventRegPtr = SCTPEventSink ;
	return ITS_SUCCESS ;
    }
    return ITS_EBADSTATE ;	
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Initializes the end point data structures of an SCTP Association.
 *
 *  Input Parameters:
 *        1. Reference to SCTPEndPoint object that contains details of the local end point.
          2. Reference to SCTPEndPoint object that contains details of the remote end point.
 *
 *  Output Parameters:
 *        Pointer to SCTPAssociation Object
      
 *  Return Value:
 *	  1.    Returns the pointer to instance of SCTPAssociation created on success
 *        2.    Returns NULL pointer on failure
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri          16-June-2008			Initial Code
 ****************************************************************************/

SCTPAssociation* SCTPConfigurationManager::CreateClient(SCTPEndPoint& localEndPoint, 
                              SCTPEndPoint& remoteEndPoint)
{
    SCTPAssociation* ClientAssoc = new SCTPAssociation ;
	
    SCTPEndPoint* temp_localEndPoint = new SCTPEndPoint(localEndPoint); 
    SCTPEndPoint* temp_remoteEndPoint = new SCTPEndPoint(remoteEndPoint);

    ClientAssoc->AddLocalEndPoint(temp_localEndPoint);

    m_LocalClientEndPointVector.push_back(temp_localEndPoint); 
 
    ClientAssoc->AddRemoteEndPoint(temp_remoteEndPoint);

    /**Setting the type of the created client --starts-- */
				
    SCTPEndPoint* temp_LocalEndPoint = ClientAssoc->GetSCTPLocalEndPoint();

    temp_LocalEndPoint-> SetType(SCTP_ENDPOINT_CLIENT);
       
    /**Setting the type of the created client --ends-- */

    return ClientAssoc ;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        starts the server and makes it ready to accept the connections from client.
 *
 *  Input Parameters:
 *        reference to the local endpoint structure on which the server has to be initiated     
 *  Output Parameters:
 *        ITS_INT

 *  Return Value:
 *        1.	Returns ITS_SUCCESS on successful creation of transport
 *        2.	Returns ITS_ENOTRANSPORT if transport creation fails
 *        3.    returns ITS_ENOTCONFIG if the IPAddress & port for the passed localEndPoint
                argument has not been set properly.
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

ITS_INT SCTPConfigurationManager::CreateServer(SCTPEndPoint& localEndPoint)
{
    int ret = ITS_SUCCESS;
    ITS_USHORT localTrid = 0;    

    SCTPEndPointProperties arg_SCTPEndPointProperties= 
			localEndPoint.GetSCTPEndPointProperties();
  
    SCTPTRAN_Manager* arg_EndPointTransport = localEndPoint.GetTransport();


    #if 0
    if ((!hasLocalIP) || (!hasLocalPort))
    {
        return ITS_ENOTCONFIG;
    }
    #endif

    ENGINE_TransportSpecificsPart localInfo;   
    ENGINE_TransportCallbacksPart localCBs;

    // Note:
    // We have to allocate everytime we connect since the ENGINE function deletes those when
    // the transport is created (See BuildTransport() in resources.c). As a result these do
    // not need to be freed in destructor
    //

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
    localInfo.data.sctpSpecs.shutdownTimeOut =  (char *)CONFIG_MALLOC (ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.pmtuTimeOut =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.isClient =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
    localInfo.data.sctpSpecs.payloadType =  (char *)CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
	
    
    localInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;

    strcpy(localInfo.data.sctpSpecs.udpPart.localHost,
					(arg_SCTPEndPointProperties.primaryIPAddress).c_str());
    sprintf(localInfo.data.sctpSpecs.udpPart.localPort,"%d",
                                (arg_SCTPEndPointProperties.port));
    strcpy(localInfo.data.sctpSpecs.udpPart.associates[0] ,
                                (arg_SCTPEndPointProperties.name).c_str());
    strcat(localInfo.data.sctpSpecs.udpPart.associates[0] , ASSOC_REMOTE_NAME_STRING);
    strcpy(localInfo.data.sctpSpecs.payloadType ,
                                (arg_SCTPEndPointProperties.family).c_str());
    strcat(localInfo.data.sctpSpecs.payloadType , "-M3UA");
    localInfo.data.sctpSpecs.udpPart.numAssociates = 1;
    sprintf(localInfo.data.sctpSpecs.maxInStreams, "%d",
                                (arg_SCTPEndPointProperties.maxInboundStreams));
    sprintf(localInfo.data.sctpSpecs.numOutStreams, "%d",
                                (arg_SCTPEndPointProperties.numOutboundStreams));
    strcpy(localInfo.data.sctpSpecs.isClient ,"no");  /** FIX ME: point to check --
                                                      whether be initialized to"yes" or "no" **/
    sprintf(localInfo.data.sctpSpecs.maxAttempts ,"%d",
				(arg_SCTPEndPointProperties.initMaxAttempts));
    
    //
    // Multihoming
    //

    localInfo.data.sctpSpecs.numExtraHomes = arg_SCTPEndPointProperties.secondaryIPAddress.size();

    //localInfo.data.sctpSpecs.numExtraHomes = secondaryIPAddress.size();
    if (localInfo.data.sctpSpecs.numExtraHomes)
    {
        localInfo.data.sctpSpecs.extraHomes = (char**)CONFIG_MALLOC
				((arg_SCTPEndPointProperties.secondaryIPAddress.size()) * sizeof(char*));
        for (int i = 0; i < arg_SCTPEndPointProperties.secondaryIPAddress.size(); i++)
        {
            localInfo.data.sctpSpecs.extraHomes[i] = (char*) CONFIG_MALLOC(ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(localInfo.data.sctpSpecs.extraHomes[i],
						arg_SCTPEndPointProperties.secondaryIPAddress[i].c_str());
        }
    }


    strcpy(localInfo.data.sctpSpecs.cookieLife ,
					arg_SCTPEndPointProperties.cookieLife);
    strcpy(localInfo.data.sctpSpecs.hbOn ,
					arg_SCTPEndPointProperties.hbOn);
    strcpy(localInfo.data.sctpSpecs.initTimeOut ,
					arg_SCTPEndPointProperties.initTimeOut);
    strcpy(localInfo.data.sctpSpecs.sendTimeOut ,
					arg_SCTPEndPointProperties.sendTimeOut);
    strcpy(localInfo.data.sctpSpecs.recvTimeOut ,
					arg_SCTPEndPointProperties.recvTimeOut);
    strcpy(localInfo.data.sctpSpecs.hbTimeOut ,
					arg_SCTPEndPointProperties.hbTimeOut);
    strcpy(localInfo.data.sctpSpecs.shutdownTimeOut ,
					arg_SCTPEndPointProperties.shutdownTimeOut);
    strcpy(localInfo.data.sctpSpecs.pmtuTimeOut ,
					arg_SCTPEndPointProperties.pmtuTimeOut);
   
    
    /*** Filling the Call Back Structure  --starts-- ***/
   
    /**FIXME: setting the callbacks to empty strings as 
    done in Lucent BSG project. If it does not work we have 
    to look for alternative  **/

    localCBs.libName = "";
    localCBs.preInit = "";
    localCBs.postInit = "";
    localCBs.preNextEvent = "";
    localCBs.postNextEvent = "";	
    localCBs.nextEventFailed = "";
    localCBs.dispUser = "";

    /*** Filling the Call Back Structure  --ends-- ***/

    //
    // 2) Create Local Instance
    //
    ret = ENGINE_AddTransport((char*)localEndPoint.GetName().c_str(),
                              "Datagram",
                              (char*)localEndPoint.GetFamily().c_str(),
                              "SCTP MTP3",
                              localInfo, &localCBs);
       
   if (ret <= 0)
    {
        return ITS_ENOTRANSPORT;
    }

    localTrid = (ITS_USHORT)ret;

    TRANSPORT_Control *temp_LocalTransport = TRANSPORT_FindTransport(localTrid);
    arg_EndPointTransport = (SCTPTRAN_Manager*)temp_LocalTransport ;

    //localEndPoint.SetTransport(arg_EndPointTransport); //sets the Transport --commented as we are not 
							 //maintaining the Transport at the EndPoint Level
                                                         //in SCTP Configuration Manager Level

    localEndPoint.SetTrId(localTrid);             

    localEndPoint.SetType(SCTP_ENDPOINT_SERVER);

    m_LocalServerEndPointVector.push_back(&localEndPoint); 
				//putting the created server end point
				// into the vector of server end points

    return (ITS_SUCCESS);
}
                                                                             
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Creates an SCTPAssociation by calling the Enable method of passed 
          SCTPAssociation Object argument.
 *
 *  Input Parameters:
 *        reference to the local endpoint structure on which the server has to be initiated
 *  Output Parameters:
 *        ITS_INT

 *  Return Value:
 *        1.    Returns ITS_SUCCESS on successful creation of Association
 *        2.    Returns ITS_ENOASSOCIATION if association creation fails
 *        3.    returns ITS_EMALLOC if malloc fails
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			   Initial Code
 ****************************************************************************/

ITS_INT SCTPConfigurationManager::Enable(SCTPAssociation& SCTPAssocObj)
{
    if((SCTPAssocObj.Enable()) == ITS_SUCCESS)
    {
	m_UnEnabledClientVector.push_back(&SCTPAssocObj);

	#if 0

        /*Adding the The SCTPAssociation Object into the HASH table --starts--*/  

        sctp_assoc_t temp_AssociationID = SCTPAssocObj.GetAssociationID();
        
        ITS_INT key_AssociationID = SCTP_HASH(temp_AssociationID); //gets the hash key from Association ID
 
        SCTPAssociationEntry* iter = m_SCTPAssocTable[key_AssociationID].entry ;

        while(iter != NULL)
        {
           iter = iter->next;
        }

        iter = (SCTPAssociationEntry*) CONFIG_MALLOC(sizeof(SCTPAssociationEntry));

        if(iter == NULL)
        {
            return ITS_EMALLOCFAIL;
        }
	    
        iter->associationID = temp_AssociationID;
        iter->ptrToSCTPAssociationObj = &SCTPAssocObj;
        iter->next= NULL;
    

	/*Adding the The SCTPAssociation Object into the HASH table --ends--*/
        #endif

        return ITS_SUCCESS;
    }
    return ITS_ENOASSOCIATION;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Disables a SCTPAssociation
 *
 *  Input Parameters:
 *        reference to SCTPAssociation Object
 *  Output Parameters:
 *        ITS_INT

 *  Return Value:
 *        1.    Returns ITS_SUCCESS on successful disable of Association

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			   Initial Code
 ****************************************************************************/

ITS_INT SCTPConfigurationManager::Disable(SCTPAssociation& SCTPAssocObj)
{
    if((SCTPAssocObj.Disable()) == ITS_SUCCESS)
    {
        SCTPEndPoint* arg_LocalEndPoint = SCTPAssocObj.GetSCTPLocalEndPoint();
        SCTPEndPointProperties temp_LocalEndPointProperties = 
                                              arg_LocalEndPoint->GetSCTPEndPointProperties();
        
	//Do clean up if the end point is server
        if(temp_LocalEndPointProperties.type == SCTP_ENDPOINT_SERVER) 
        {

            SCTPEndPoint* arg_RemoteEndPoint = SCTPAssocObj.GetSCTPRemoteEndPoint();        

            /*Clean up Activity --starts--*/
            free(arg_RemoteEndPoint);//removing the remoteEndPoint

            /*removing from the Association from the backward reference vector --starts--*/
            std::vector<SCTPAssociation*>& temp_SCTPAssociationBackwardRef =
                                   arg_LocalEndPoint->GetSCTPAssociationBackwardRef();

            SCTPAssociationProperties arg_SCTPAssociationProperties =
                                 SCTPAssocObj.GetSCTPAssociationProperties();            

            int i;
            for( i=0; i< temp_SCTPAssociationBackwardRef.size(); i++)
            {
            
                SCTPAssociationProperties temp_SCTPAssociationProperties =
                           (temp_SCTPAssociationBackwardRef[i])->GetSCTPAssociationProperties();

                if(temp_SCTPAssociationProperties.associationID ==
                                               arg_SCTPAssociationProperties.associationID)
                    break;
            }

            free(temp_SCTPAssociationBackwardRef[i]);
            temp_SCTPAssociationBackwardRef.erase(temp_SCTPAssociationBackwardRef.begin()+i);
            /*removing from the Association from the backward reference vector --ends--*/
 
            /*removing the SCTPAssociation Object from the Hash Table --starts--*/

            ITS_INT key_argAssociationID= SCTP_HASH
					(atoi((char*)(arg_SCTPAssociationProperties.associationID)));

            SCTPAssociationEntry* iter = m_SCTPAssocTable[key_argAssociationID].entry ;
            SCTPAssociationEntry* prev = NULL;
   
                                     
            while(iter != NULL)
            {
                if((iter->associationID)== (arg_SCTPAssociationProperties.associationID))
                {   
                    SCTPAssociationEntry* temp = iter->next;
                    free(iter ->ptrToSCTPAssociationObj);
                    free(iter);
                    prev->next = temp;
                    break;
                }
                prev = iter;
                iter = iter->next;
            }
            /*removing the SCTPAssociation Object from the Hash Table --ends--*/
        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Deletes a client
 *
 *  Input Parameters:
 *        reference to SCTPAssociation Object
 *  Output Parameters:
 *        ITS_INT

 *  Return Value:
 *        1.    Returns ITS_SUCCESS on successful disable of Association
          2.    Returns ITS_EBADSTATE if the given association object is
                not in  ITS_SCTP_CLOSED state
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

ITS_INT SCTPConfigurationManager::DeleteClient(SCTPAssociation& SCTPAssocObj)
{
    SCTPEndPoint* arg_LocalEndPoint = SCTPAssocObj.GetSCTPLocalEndPoint();
    SCTPEndPoint* arg_RemoteEndPoint = SCTPAssocObj.GetSCTPRemoteEndPoint();

    SCTPAssociationProperties arg_SCTPAssociationProperties =
                                             SCTPAssocObj.GetSCTPAssociationProperties();
    if(arg_SCTPAssociationProperties.state == ITS_SCTP_CLOSED)
    {
        /* Deleting EndPoints */
        free(arg_LocalEndPoint);
        free(arg_RemoteEndPoint);

	ITS_INT arg_AssociationID= SCTPCM_ASSOC_ID(arg_SCTPAssociationProperties.associationID);

        /*removing the SCTPAssociation Object from the Hash Table --starts--*/

        ITS_INT key_argAssociationID= SCTP_HASH((arg_AssociationID));

        SCTPAssociationEntry* iter = m_SCTPAssocTable[key_argAssociationID].entry ;
        SCTPAssociationEntry* prev = NULL;


        while(iter != NULL)
        {
	    ITS_INT temp_AssociationID= SCTPCM_ASSOC_ID(iter->associationID);
 
	    if((/*iter->associationID*/temp_AssociationID)== (arg_AssociationID))
            {
                SCTPAssociationEntry* temp = iter->next;
                free(iter ->ptrToSCTPAssociationObj);
                free(iter);
                prev->next = temp;
                break;
            }
            prev = iter;
            iter = iter->next;
        }
	
	/*removing the SCTPAssociation Object from the Hash Table --ends--*/
        
        return ITS_SUCCESS;
    }
    else
    {
        return ITS_EBADSTATE;
    }
      
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Deletes a server
 *
 *  Input Parameters:
 *        reference to SCTPEnsPoint
 *  Output Parameters:
 *        ITS_INT

 *  Return Value:
 *        1.    Returns ITS_SUCCESS on successful disable of Association
          2.    Returns ITS_EBADSTATE if the EndPoint is still connected to any 
                Association
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

ITS_INT SCTPConfigurationManager::DeleteServer(SCTPEndPoint& localEndPoint)
{
    int ret =0;

    std::vector<SCTPAssociation*>& arg_SCTPAssociationBackwardRef
					= localEndPoint.GetSCTPAssociationBackwardRef();

    if(arg_SCTPAssociationBackwardRef.size() == 0)    
    {
        ITS_USHORT arg_TrId = localEndPoint.GetTrId();
        ret = ENGINE_DeleteTransport(arg_TrId);

        return ITS_SUCCESS;       
    }
    else
    {
        return ITS_EBADSTATE;
    }
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        gets the pointer to the association object whose association ID has
          been passed as parameter.
 *
 *  Input Parameters:
 *        association id
 *  Output Parameters:
 *        SCTPAssociation*

 *  Return Value:
 *        1.	Returns a pointer reference to SCTPAssociation object found on success.
          2.	Returns NULL pointer if no SCTPAssociation object with the 
                given association ID is found.

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

SCTPAssociation* SCTPConfigurationManager::GetSCTPAssociationObject(sctp_assoc_t associationID) const
{
        /*searching SCTPAssociation Object from the Hash Table --starts--*/
                                   
    ITS_INT key_AssociationID= SCTP_HASH(SCTPCM_ASSOC_ID(associationID));

    SCTPAssociationEntry* iter = m_SCTPAssocTable[key_AssociationID].entry ;

    while(iter != NULL)
    {
        if((iter->associationID)== associationID)
        {
            return (iter ->ptrToSCTPAssociationObj);    
        }
        iter = iter->next;
    }
    /*searching the SCTPAssociation Object from the Hash Table --ends--*/
    
    return NULL; //Association Object not found   
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        This method returns a pointer to the registered event sink.

 *  Input Parameters:
 *        none
 *  Output Parameters:
 *        ISCTPEvent*

 *  Return Value:
 *        returns the pointer to the ISCTPEvent class
 
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

ISCTPEvent* SCTPConfigurationManager::GetEventSink(void) const
{
    return (m_SCTPEventReg);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        This method returns a reference to the m_LocalServerEndPointVector

 *  Input Parameters:
 *        none
 *  Output Parameters:
 *        std::vector<SCTPEndPoint>&

 *  Return Value:
 *        returns the reference to the to the m_LocalServerEndPointVector

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			   Initial Code
 ****************************************************************************/

std::vector<SCTPEndPoint*>& SCTPConfigurationManager::GetLocalServerEndPointVector(void)
{
    return m_LocalServerEndPointVector;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        This method returns a reference to the m_UnEnabledClientVector

 *  Input Parameters:
 *        none
 *  Output Parameters:
 *        std::vector<SCTPAssociation*>&

 *  Return Value:
 *        returns the reference to the to the m_UnEnabledClientVector

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/
std::vector<SCTPAssociation*>& SCTPConfigurationManager::GetUnEnabledClientVector(void)
{
    return m_UnEnabledClientVector;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        This method retuns the Base Address of the Hash Table Array

 *  Input Parameters:
 *        none
 *  Output Parameters:
 *        SCTPAssociationHashTable*

 *  Return Value:
 *        returns the Base Address of the Hash Table Array

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

SCTPAssociationHashTable* SCTPConfigurationManager::GetSCTPAssocHashTable(void)
{
    return m_SCTPAssocTable;
}



