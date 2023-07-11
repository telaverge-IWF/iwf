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
 * LOG: $Log: its_sctp_cm_transcallback.cpp,v $
 * LOG: Revision 1.2  2008/06/27 14:05:53  mpatri
 * LOG: Accelero CGI Phase I: To support SCTP Configuration APIs & move to new directory sctp-cm
 * LOG:
 * LOG: Revision 1.1  2008/06/27 13:37:24  mpatri
 * LOG: new directory is created for sctp configuration manager files
 * LOG:
 * LOG: Revision 1.1  2008/06/20 11:32:30  mpatri
 * LOG: Accelero CGI Phase I: Support for SCTP Configuration APIs
 * LOG:
 * LOG:
 * LOG:
 *
 * ID: $Id: its_sctp_cm_transcallback.cpp,v 1.2 2008/06/27 14:05:53 mpatri Exp $
 ****************************************************************************/

#ident "$Id: its_sctp_cm_transcallback.cpp,v 1.2 2008/06/27 14:05:53 mpatri Exp $"


#include <its_sctp_cm.h>
#include <its_sctp_event_interface.h>
#include <its_sctp_cm_definitions.h>

extern "C"
{
#include <its_lksctp.h>
}

using namespace std;

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *        Receives the Event for the sctp_abstraction layer.
	  Prepare an event by filling in object, userData and callData
          Post the message into SCTP configuration manager thread.s queue

 *  Input Parameters:
 *        ITS_POINTER object,
          ITS_POINTER userData,
          ITS_POINTER callData
 *  Output Parameters:
 *        void

 *  Return Value:
 *        none

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			   Initial Code
 ****************************************************************************/


void
SCTPCM_SCTPTransCallback (ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    int ret, i;	
    TRANSPORT_Control *transport = (TRANSPORT_Control *)object; 
						//Holds the object->transport.instance
    SCTP_API_MSG_HDR *msg = (SCTP_API_MSG_HDR *)callData;       
    SCTP_API_CMSG *cmsg = (SCTP_API_CMSG *)(msg->control);
    ITS_EVENT sctpMsg;

    ITS_EVENT_INIT(&sctpMsg, ITS_SCTPCM_EVENT_RCV_THREAD_CONTEXT,
                   (sizeof(ITS_USHORT)+ sizeof(SCTP_API_MSG_HDR)));

    memcpy(&sctpMsg.data[0], &TRANSPORT_INSTANCE(transport),
               sizeof(ITS_USHORT));
    
    i = sizeof(ITS_USHORT);

    memcpy(&sctpMsg.data[i], msg, sizeof(SCTP_API_MSG_HDR));

    ret = TRANSPORT_PutEvent(SCTPCM_MSGQ_ID, &sctpMsg);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
	  receives the event from the Event Queue and do the necessary updation
          in SCTP_CM level and and then calls the appropiate event handler 
	  function registered by the the module which sits on the top of SCTP_CM

 *  Input Parameters:
 *        ITS_POINTER object,
          ITS_POINTER userData,
          ITS_POINTER callData
 *  Output Parameters:
 *        none

 *  Return Value:
 *        THREAD_RET_TYPE

 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date           Reference                Description
 * -------------------------------------------------------------------------
 *  mpatri           23-MAY-2008			    Initial Code
 ****************************************************************************/

THREAD_RET_TYPE
SCTPConfigManagerThreadFunc(void* arg)
{
    SCTPConfigurationManager* configMgr =
                          (SCTPConfigurationManager*) arg;

    ISCTPEvent* eventSink = configMgr->GetEventSink();

    ITS_EVENT SCTPEvent;
    ITS_EVENT_INIT(&SCTPEvent, 0, 0);

    while ( TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(SCTPCM_EventRcvQueue))
                                                        (SCTPCM_EventRcvQueue,
                                                         &SCTPEvent)
                                                         == ITS_SUCCESS)
    {
        if(SCTPEvent.src == ITS_SCTPCM_EVENT_RCV_THREAD_CONTEXT)
        {
            /** handle event --starts-- */
	    //SCTPCM_HandleSCTPEvent(&SCTPEvent);
	    ITS_USHORT trId_Event= SCTPEvent.data[0];
	    memcpy(&trId_Event,&SCTPEvent.data[0],
                   sizeof(ITS_USHORT)); 
	    
	    SCTP_API_MSG_HDR *msg =(SCTP_API_MSG_HDR *) &(SCTPEvent.data[sizeof(ITS_USHORT)]);
	    SCTP_API_CMSG *cmsg = (SCTP_API_CMSG *)(msg->control);

	    TRANSPORT_Control* tc_Event= TRANSPORT_FindTransport(trId_Event);
            SCTPTRAN_Manager* tm_Event= (SCTPTRAN_Manager*) tc_Event;

            if (msg->flags == SCTP_IS_EVENT && NULL != eventSink)
            {
                switch(cmsg->hdr.type)
                {
                    case SCTP_CM_ASSOC_CHG:
                    {
                        if(cmsg->data.assocChg.state == SCTP_AC_COMM_UP)
			{
                            /*********Implementation PLAN ************/
                            /*check the end point on which the event is received is client or server 
			    (by searching through the vector of server end points, for searching compare
			    the socketid of end points in the vector to the socket id received through the 
			    event to find a match. the socket id can be obtained by getting the 
			    SCTPTRAN_Manager from the TrId of the EndPoint and then calling 
			    --int sd = SOCKTRAN_SOURCE(sctp_tran_obj)->socket,-- as done in line no.3226 
			    of its_lksctp.c file . 
			    */
 
			    /* if it is a server then do as per the sequence diagram in Figure.11 of the 
			    design doc. if client, then ignore it. But don't forget to call the 
			    eventSink->OnUp(associationObj) after enabling the client in Enable API.*/
                    
                            /**---- Implementation --starts----**/
                          
			    int temp_event_sd= SOCKTRAN_CONNECT(tm_Event)->socket; 

						/**FIXME: Check whether SOCKTRAN_SOURCE or SOCKTRAN_CONNECT
						depending on the value of "obj", whether it is remote transport
						object or local transport object*/

			    std::vector<SCTPEndPoint*>& temp_LocalServerEndPointVector=
					       configMgr->GetLocalServerEndPointVector();
 
                            bool flag= false;  //is set if the event is received on a server endpoint
			    int i;
                            for( i=0; i< temp_LocalServerEndPointVector.size(); i++)
                            {
      			        SCTPTRAN_Manager* temp_LocalServerEndPointTransport=
				temp_LocalServerEndPointVector[i]->GetTransport();

			        int iter_sd= SOCKTRAN_SOURCE(temp_LocalServerEndPointTransport)->socket;

			        if(temp_event_sd == iter_sd)
			        {
			            flag= true;
				        break;
  				}
                            }
			    if(i != temp_LocalServerEndPointVector.size())
			    {
			        SCTPAssociation* ServerAssoc = new SCTPAssociation ;
				  
			        ServerAssoc->AddLocalEndPoint(temp_LocalServerEndPointVector[i]);    
				  
				  /*STEPS: Create a SCTPEndPoint Object for remote EndPoint
				   and Find a method to get the peer address and then set the primary and 
				   secondary IPAddresses using SCTPEndPoint::SetPrimaryIP() and 
				   SCTPEndPoint::AddSecondaryIP() . Then call AddRemoteEndPoint() for the 
				   ServerAssoc association Object with the created SCTPEndPoint as argument.*/
		
			        SCTPEndPoint* temp_RemoteEndPoint = new SCTPEndPoint;
           			temp_RemoteEndPoint->SetTrId(trId_Event);
				ServerAssoc->AddRemoteEndPoint(temp_RemoteEndPoint);

				sctp_assoc_t temp_AssocId_Event= 
				     FindAssocId(SOCKTRAN_SOURCE(tm_Event)->socket,
				                (sockaddr_in*) SOCKTRAN_SOURCE(tm_Event)->addr);


				ServerAssoc->SetAssociationID(temp_AssocId_Event);
				ServerAssoc->SetAssociationState(ITS_SCTP_ESTABLISHED);  

         			/**Add the Created Association to the Hash table --starts--**/

			        ITS_INT key_AssociationID = SCTP_HASH(SCTPCM_ASSOC_ID(temp_AssocId_Event));
								 //gets the hash key from Association ID

			        SCTPAssociationEntry* iter = (configMgr->GetSCTPAssocHashTable())
							[key_AssociationID].entry ;

			        while(iter != NULL)
        			{
				    iter = iter->next;
        			}
                                iter = (SCTPAssociationEntry*)CONFIG_MALLOC(sizeof(SCTPAssociationEntry));

                                if(iter == NULL)
        			{
			            //return ITS_EMALLOCFAIL;  //FIXME:Need to have a Debug Trace here
       				}

			        iter->associationID = temp_AssocId_Event;
				iter->ptrToSCTPAssociationObj = ServerAssoc;
			        iter->next= NULL;

				/**Add the Created Association to the Hash table --ends--**/
				  
				/**Add the Created Association to the Backwardref vector --starts--**/
 				  
				std::vector<SCTPAssociation*>& arg_SCTPAssociationBackwardRef
                                        = (temp_LocalServerEndPointVector[i])->GetSCTPAssociationBackwardRef();

				arg_SCTPAssociationBackwardRef.push_back(ServerAssoc);

				eventSink->OnUp(*ServerAssoc);
				/**Add the Created Association to the Backwardref vector --ends--**/
			    }   
 			  
                            /**process the event it is not received on a server end point --starts--*/
		            if(flag == false)
			    {
				std::vector<SCTPAssociation*>& temp_UnEnabledClientVector=
                                               configMgr->GetUnEnabledClientVector();

				int i;
                                for( i=0; i< temp_UnEnabledClientVector.size(); i++)
                                {
				    SCTPEndPoint* temp_SCTPLocalEndPoint=
				        	temp_UnEnabledClientVector[i]->GetSCTPLocalEndPoint();
					
				    SCTPTRAN_Manager* temp_UnEnabledClientLocalTransport=
							temp_SCTPLocalEndPoint->GetTransport();

                                    int iter_sd= SOCKTRAN_SOURCE(temp_UnEnabledClientLocalTransport)->socket;
                                    if(temp_event_sd == iter_sd)
                                    {
                                        break;
                                    }
                                }
         			sctp_assoc_t temp_AssocId_Event=
                                                FindAssocId(SOCKTRAN_SOURCE(tm_Event)->socket,
                                                (sockaddr_in*) SOCKTRAN_SOURCE(tm_Event)->addr);

				temp_UnEnabledClientVector[i]->SetAssociationID(temp_AssocId_Event);
				temp_UnEnabledClientVector[i]->SetAssociationState(ITS_SCTP_ESTABLISHED);
			
			        /**Add the Created Association to the Hash table --starts--**/

                                ITS_INT key_AssociationID = SCTP_HASH( SCTPCM_ASSOC_ID(temp_AssocId_Event));
                                                                 //gets the hash key from Association ID
				
				SCTPAssociationEntry* iter = (configMgr->GetSCTPAssocHashTable())
                                                                         [key_AssociationID].entry ;
    
				while(iter != NULL)
	                        {
                                    iter = iter->next;
                                }
				      
				iter = (SCTPAssociationEntry*)CONFIG_MALLOC(sizeof(SCTPAssociationEntry));

                                if(iter == NULL)
                                {
                                    //return ITS_EMALLOCFAIL;  //FIXME: Need a Debug Trace here
                                }
				
				iter->associationID = temp_AssocId_Event;
	                        iter->ptrToSCTPAssociationObj = temp_UnEnabledClientVector[i];
                                iter->next= NULL;
			        /**Add the Created Association to the Hash table --ends--**/
				temp_UnEnabledClientVector.erase(temp_UnEnabledClientVector.begin()+i);
				                                	//removes the UnEnabled Association.
				eventSink->OnUp(*(iter->ptrToSCTPAssociationObj));
                            }
				  /**process the event it is not received on a server end point --ends--*/
              		}
              
                        if(cmsg->data.assocChg.state == SCTP_AC_COMM_LOST)
                        {
			    sctp_assoc_t temp_AssocId_Event= FindAssocId(SOCKTRAN_SOURCE(tm_Event)->socket,
                                                             (sockaddr_in*) SOCKTRAN_SOURCE(tm_Event)->addr);


          		    /**Call the --SCTPAssociation* SCTPConfigurationManager::
                            GetSCTPAssociationObject(sctp_assoc_t associationID) -- function 
			    to get the pointer to the SCTPAssociation Object and then Disable it --**/
					
        		    SCTPAssociation* temp_SCTPAssociationObj=
					configMgr->GetSCTPAssociationObject(temp_AssocId_Event);
			    
			    SCTPAssociation temp_CONFIG_SCTPAssociationObj = *temp_SCTPAssociationObj;
			
			    /*Disable the Association by calling the Disable function of SCTP_CM*/
			    int rc;
			    rc=configMgr->Disable(*temp_SCTPAssociationObj);
						   			    
			    eventSink->OnDown(temp_CONFIG_SCTPAssociationObj);
			}
                        if(cmsg->data.assocChg.state == SCTP_AC_COMM_RESTART)
                        {
			    //eventSink->OnRestart(associationObj);  //FIXME: to be handled later
			}
                        if(cmsg->data.assocChg.state ==SCTP_AC_COMM_ABORTED)
			{
                            
                            sctp_assoc_t temp_AssocId_Event= FindAssocId(SOCKTRAN_SOURCE(tm_Event)->socket,
                                                              (sockaddr_in*) SOCKTRAN_SOURCE(tm_Event)->addr); 

	                    /**Call the --SCTPAssociation* SCTPConfigurationManager::
                            GetSCTPAssociationObject(sctp_assoc_t associationID) -- function
                            to get the pointer to the SCTPAssociation Object and then Disable it --**/

                            SCTPAssociation* temp_SCTPAssociationObj=
                                        configMgr->GetSCTPAssociationObject(temp_AssocId_Event);

			    SCTPAssociation temp_CONFIG_SCTPAssociationObj = *temp_SCTPAssociationObj;
        
                            /*Disable the Association by calling the Disable function of SCTP_CM*/
                            int rc;
                            rc=configMgr->Disable(*temp_SCTPAssociationObj);
                            
                            eventSink->OnAbort(temp_CONFIG_SCTPAssociationObj);
			}
                        if(cmsg->data.assocChg.state ==SCTP_AC_SHUTDOWN_DONE)
			{
                            sctp_assoc_t temp_AssocId_Event= FindAssocId(SOCKTRAN_SOURCE(tm_Event)->socket,
                                              (sockaddr_in*) SOCKTRAN_SOURCE(tm_Event)->addr);


                            /**Call the --SCTPAssociation* SCTPConfigurationManager::
                            GetSCTPAssociationObject(sctp_assoc_t associationID) -- function
                            to get the pointer to the SCTPAssociation Object and then Disable it --**/

                            SCTPAssociation* temp_SCTPAssociationObj=
                                        configMgr->GetSCTPAssociationObject(temp_AssocId_Event);

			    SCTPAssociation temp_Config_SCTPAssociationObj = *temp_SCTPAssociationObj;

                            /*Disable the Association by calling the Disable function of SCTP_CM*/
                            int rc;
                            rc=configMgr->Disable(*temp_SCTPAssociationObj);
                               
			    eventSink->OnShutdown(temp_Config_SCTPAssociationObj);
			}
                        
                        if(cmsg->data.assocChg.state ==SCTP_AC_CANT_START)
                        {
			    std::vector<SCTPAssociation*>& temp_UnEnabledClientVector=
                                               configMgr->GetUnEnabledClientVector();

			    int temp_event_sd= SOCKTRAN_CONNECT(tm_Event)->socket;

                            int i;
                            for( i=0; i< temp_UnEnabledClientVector.size(); i++)
                            {
                                SCTPEndPoint* temp_SCTPLocalEndPoint=
                                                temp_UnEnabledClientVector[i]->GetSCTPLocalEndPoint();

                                SCTPTRAN_Manager* temp_UnEnabledClientLocalTransport=
                                                        temp_SCTPLocalEndPoint->GetTransport();

                                int iter_sd= SOCKTRAN_SOURCE(temp_UnEnabledClientLocalTransport)->socket;
                                if(temp_event_sd == iter_sd)
                                {
                                    break;
                                }
                            }
			    eventSink->OnCantStart(*(temp_UnEnabledClientVector[i]));
                            break;
                        }
                    }   

		    #if 0
                    /**FIX ME:Event to be Handled later--starts--*/
                    case SCTP_CM_INTF_CHG:
                    {
                        if(cmsg->data.intfChg.state ==SCTP_IC_ADDR_REACHABLE)
                        eventSink->OnAddressReachable(remoteEndPointObj);

                        if(cmsg->data.intfChg.state ==SCTP_IC_ADDR_UNREACHABLE)
                        eventSink->OnAddressUnreachable(remoteEndPointObj);

                        break;
	            }
                    case SCTP_CM_REMOTE_ERR:
                    {
                        break;
                    }
		    #endif
                    /**FIX ME:Event to be Handled --ends--*/
                }
            /** handle event --ends-- */
            }
       }
   } /***  SCTPConfigManagerThreadFunc  --ends-- ***/
}


