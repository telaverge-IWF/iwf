/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: ual_sctp_mgnt.c,v 9.13.4.1.4.1.40.2.2.1 2015/01/22 15:08:26 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_sctp_mgnt.c,v $
 *  LOG: Revision 9.13.4.1.4.1.40.2.2.1  2015/01/22 15:08:26  jkchaitanya
 *  LOG: changes for aspid issue faced in the HP site
 *  LOG:
 *  LOG: Revision 9.13.4.1.4.1.40.2  2014/11/17 04:59:50  jkchaitanya
 *  LOG: changes for HA Bug Fixes
 *  LOG:
 *  LOG: Revision 9.13.4.1.4.1.40.1  2014/10/27 08:18:49  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 9.13.4.1.4.1  2010/05/31 14:20:56  ssingh
 *  LOG: fixing issue #2915; Audit Timer Expiry Handling
 *  LOG:
 *  LOG: Revision 9.13.4.1  2009/04/09 08:16:51  ssodhi
 *  LOG: Handling SCTP connection down indication
 *  LOG:
 *  LOG: Revision 9.13  2008/07/07 06:12:02  skatta
 *  LOG: Fix for issue #1044 in whizible
 *  LOG:
 *  LOG: Revision 9.12  2008/06/30 14:05:37  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.11  2008/06/29 15:18:09  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.10  2008/05/01 16:18:31  kramesh
 *  LOG: Propagated Bridgeport issue 1541. Routing Key more than 255.
 *  LOG:
 *  LOG: Revision 9.9  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.8.2.8  2007/06/28 12:51:33  pspl
 *  LOG: (PSPL,abhijeet) few cosmetic changes for Point code val in trace logs
 *  LOG:
 *  LOG: Revision 9.8.2.7  2007/06/22 11:50:36  pspl
 *  LOG: Auditing support for receipt of SSNM message (SCON/DUNA/DRST)
 *  LOG:
 *  LOG: Revision 9.8.2.6  2007/05/23 10:34:14  pspl
 *  LOG: (PSPL, abhijeet) added code to set the trId in the aspList of the asList on the ASP side
 *  LOG:                  the trID is known only at the run-time and not available in static info.
 *  LOG:
 *  LOG: Revision 9.8.2.5  2007/05/21 10:22:37  pspl
 *  LOG: (PSPL, abhijeet) Changes to take care of the UP_ACK messages in DOWN/INACTIVE states of ASP
 *  LOG:
 *  LOG: Revision 9.8.2.4  2007/04/30 11:13:07  pspl
 *  LOG: (PSPL, Abhijeet) misc changes
 *  LOG:
 *  LOG: Revision 9.8.2.3  2007/04/26 06:57:47  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - moved the TRANSPORT_PutEvent() after timer context data being set.
 *  LOG: - other misc changes for trace message
 *  LOG:
 *  LOG: Revision 9.8.2.2  2007/04/05 14:42:34  pspl
 *  LOG: peg count increments replaced by the call to UAL_IncrementMIBStats()
 *  LOG:
 *  LOG: Revision 9.8.2.1  2007/03/29 14:26:01  pspl
 *  LOG: Added NULL check for linkInfo.(Rahul)
 *  LOG:
 *  LOG: Revision 9.8  2007/01/17 09:21:32  yranade
 *  LOG: Warning removals.
 *  LOG:
 *  LOG: Revision 9.7  2005/11/30 23:51:15  clin
 *  LOG: change ITS_TRACE to UAL trace.
 *  LOG:
 *  LOG: Revision 9.6  2005/11/23 20:47:42  clin
 *  LOG: fix bug #2481
 *  LOG:
 *  LOG: Revision 9.5  2005/11/23 19:47:24  clin
 *  LOG: fix bug #2531
 *  LOG:
 *  LOG: Revision 9.4  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.3  2005/05/05 06:01:58  adutta
 *  LOG: Fix for #1794
 *  LOG:
 *  LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 *  LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:49  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:20  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.2.6.2.2.4.4  2005/02/25 11:04:38  dsatish
 *  LOG: if there are no more links in the linkset,
 *  LOG: set the set the linkSet state to down.
 *  LOG:
 *  LOG: Revision 7.2.2.6.2.2.4.3  2005/01/06 19:51:10  sbabu
 *  LOG: Fixed problems during testing
 *  LOG:
 *  LOG: Revision 7.2.2.6.2.2.4.2  2005/01/04 15:16:53  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.2.2.6.2.2.4.1  2004/12/15 13:15:37  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.2.2.6.2.2  2004/10/06 08:43:23  mmanikandan
 *  LOG: Memory corruption is resolved
 *  LOG:
 *  LOG: Revision 7.2.2.6.2.1  2004/05/03 13:13:01  ssingh
 *  LOG: Bug fixes for #781/788/790/806/808.
 *  LOG:
 *  LOG: Revision 7.2.2.6  2003/10/22 13:33:03  lbana
 *  LOG: initialize stack variable.
 *  LOG:
 *  LOG: Revision 7.2.2.5  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.2.2.4  2003/10/15 20:50:57  lbana
 *  LOG: fixes for SG crash on reconnects with serveral ASPs
 *  LOG:
 *  LOG: Revision 7.2.2.3  2003/10/15 15:33:46  lbana
 *  LOG: get kineto fixes to pr6.3
 *  LOG:
 *  LOG: Revision 7.2.2.2  2003/09/12 22:56:09  lbana
 *  LOG: Stop timer for active even when active_ack is received without the TM.
 *  LOG:
 *  LOG: Revision 7.2.2.1  2003/08/04 23:17:34  hcho
 *  LOG: fixes in DUNA/DAVA and propagate CANT_START indication to the user.
 *  LOG:
 *  LOG: Revision 7.2  2002/12/30 17:28:48  lbana
 *  LOG: Propagating bug fixes in PR6.1 to current
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.9  2002/07/24 20:52:06  lbana
 *  LOG: tested pending procedures.
 *  LOG:
 *  LOG: Revision 6.8  2002/07/24 19:53:43  lbana
 *  LOG: fix bugs in reconnect logic, and get aspinfo element from parser
 *  LOG: extension.
 *  LOG:
 *  LOG: Revision 6.7  2002/07/08 18:18:30  ngoel
 *  LOG: add ual alarms
 *  LOG:
 *  LOG: Revision 6.6  2002/06/12 23:01:45  lbana
 *  LOG: Problem in removing the links when receiving ASP Inactive.
 *  LOG:
 *  LOG: Revision 6.5  2002/06/12 19:20:17  lbana
 *  LOG: Put in changes after Henry's comments.
 *  LOG:
 *  LOG: Revision 6.4  2002/05/30 16:17:09  lbana
 *  LOG: More testing on current. Removed a few bugs.
 *  LOG:
 *  LOG: Revision 6.3  2002/05/13 23:24:38  lbana
 *  LOG: Build in current. Now for the testing.....
 *  LOG:
 *  LOG: Revision 6.2  2002/05/13 20:30:42  lbana
 *  LOG: uals in current starts from here...
 *  LOG:
 *  LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 *  LOG: Begin PR7.
 *  LOG:
 *  LOG: Revision 1.2  2002/01/09 22:31:48  lbana
 *  LOG: remove endofline character appended in dos
 *  LOG:
 *  LOG: Revision 1.1  2002/01/09 21:46:15  lbana
 *  LOG: Baseline for M3UA Draft Version 10 and SUA draft ver 9
 *  LOG:
 ****************************************************************************/


#include "ual_intern.h"

#ident "$Id: ual_sctp_mgnt.c,v 9.13.4.1.4.1.40.2.2.1 2015/01/22 15:08:26 jkchaitanya Exp $"
static int UAL_TableCleanUp(ASP_Entry *aspEntryPtr, ITS_OCTET indication);

ITS_UINT localaspId = 0;
/*
 *
 * Manage SCTP indiactions.
 *
 */

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *    This function is used to register the UAL with the SCTP_Transport 
 *    callbacks. This function is called when a message is received on one
 *    association. Two possibilites - Either it is a UAL management message
 *    else it is a SCTP indication (ASSOC_UP,DOWN...). A TRANSPORT_PutEvent
 *    is done to the UAL instance for processing.
 *     
 *  Input Parameters:
 *     
 *    See itsCallBack module.
 *
 *  Input/Output Parameters:
 *  
 *    See itsCallBack module.    
 *
 *  Output Parameters:
 *      
 *    See itsCallBack module.
 *
 *  Return Value:
 *
 *    None.      
 *
 *  Notes:
 *
 *    See itsCallBack module.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 *  Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 *  ssingh    04-01-2005  BugId: 807      Modification with changes propagated.
 *
 *  See Also:
 *
 ******************************************************************************/
void
UAL_SCTPTransCallback(ITS_POINTER object, ITS_POINTER userData, 
                      ITS_POINTER callData)
{
    int ret = ITS_SUCCESS;
    TRANSPORT_Control *transport = (TRANSPORT_Control *)object;
    SCTP_API_MSG_HDR *msg = (SCTP_API_MSG_HDR *)callData;
    SCTP_API_CMSG *cmsg = (SCTP_API_CMSG *)(msg->control);
    ITS_EVENT sctpMsg;
    int i;

    /* If not called with M3UA payload... No need to process */
    if (SCTPTRAN_PAYLOAD(object) != SCTP_PAYLOAD_M3UA)
    {
       return;
    }
    
    UAL_DEBUG(("UAL_SCTPTransCallback: Received Message\n"));

    /* 
     * in the UAL main all these event will fall into the
     * switch default. We know the difference from an indication
     * and DATA from the length
     */
    if (msg->flags == SCTP_IS_EVENT && cmsg->hdr.type == SCTP_CM_ASSOC_CHG)
    {
        UAL_DEBUG(("UAL_SCTPTransCallback: Got ASSOC CHG, state: %d\n",cmsg->data.assocChg.state));

        if ((cmsg->data.assocChg.state == SCTP_AC_COMM_UP) &&
             UAL_GL_ITW_MODE != UAL_ITW_ASP) 
        {
            // Call the callback to register the ASP for the new transport
            CALLBACK_CallCallbackList(UAL_ASP_ManagementCallbacks, userData,  callData);
        }

        if ((cmsg->data.assocChg.state == SCTP_AC_COMM_LOST ||
             cmsg->data.assocChg.state == SCTP_AC_COMM_ABORTED) &&
             UAL_GL_ITW_MODE != UAL_ITW_ASP) 
        {
            ASP_Entry *aspEntryPtr = NULL;

            UAL_WARNING(("UAL_SCTPTransCallback: Received LOST/ABORT Indi.\n"));

            if( (ret = MUTEX_AcquireMutex(&__ualGuard)) != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_SCTPTransCallback:Failed to acquire mutex\n"));

                return;
            }

            ret = ASPTable_FindEntry(TRANSPORT_INSTANCE(transport), &aspEntryPtr);

            if (aspEntryPtr != NULL)
            {
                ret = UAL_TableCleanUp(aspEntryPtr, cmsg->data.assocChg.state);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("UAL_SCTPTransCallback: Error cleaning"
                                     "up the mess after ASSOC_LOST, code %d \n",
                                      ret));
                }
            }
            else
            {
                UAL_ERROR(("UAL_SCTPTransCallback: Could not find "
                                 "ASP entry for trid %d \n", 
                                  TRANSPORT_INSTANCE(transport)));
            }

            MUTEX_ReleaseMutex(&__ualGuard);
        }
     
        ITS_EVENT_INIT(&sctpMsg, SCTP_MANAGER_INSTANCE,
                       sizeof(ITS_USHORT) * 2); 
      

        memcpy(&sctpMsg.data[0], &TRANSPORT_INSTANCE(transport), 
               sizeof(ITS_USHORT));

        i = sizeof(ITS_USHORT);
        sctpMsg.data[i++] = cmsg->hdr.type;
        sctpMsg.data[i]   = cmsg->data.assocChg.state;
    }
    else
    {
        UAL_DEBUG(("UAL_SCTPTransCallback: Unknown type\n"));

        /* we are not interested by this type */
    }

    ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &sctpMsg);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("SCTP UAL_SCTPTransCallback: error sending SCTP Msg,"
                         "code %d", ret));
    }

    return;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Routing Key value more than 255 related function.
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
 *
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-01-2008   BugId: 1541     Propagated Bridgeport Isse.
 *                                          Support of Routing Key value 
 *                                          more than 255.                                          
 *
 *  See Also:
 ****************************************************************************/
static int
Add_List_of_AS_to_ASP_list_of_AS_hash_iterative_proc(ITS_INT context, 
       ITS_POINTER data, void* in, void* out)
{
    int ret = ITS_SUCCESS;
    RK_Context* ctxt = (RK_Context*)data;
    ASP_Entry* aspEntryPtr = (ASP_Entry*)in;
    if (ctxt != NULL)
    {
	 if (ctxt->isMember == ITS_TRUE)
	 {
	     RKListNode entry;

	     entry.rCtxt = ctxt->rCtxt;
	     entry.entry = ctxt;

	     ret = RKList_AddEntry(aspEntryPtr->asList, &entry);
	     if (ret != ITS_SUCCESS)
	     {
		 UAL_ERROR(("UAL_HandleSCTPIndication: Error "
				  "adding AS entry to ASP_Table, "
				  "trid: %d \n", aspEntryPtr->trId));
	     }
             return ret;
	 }
    }
    return !ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *
 *  Input/Output Parameters:
 *      
 *    None.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *     
 *    None. 
 *
 *  Notes:
 *
 *    None.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference     Description
 * -----------------------------------------------------------------------------
 * gdevanand 05-03-2005  BugId:1794    AspId in asp table dump.
 * 
 *  See Also:
 *
 ******************************************************************************/
int
UAL_HandleSCTPIndication(ITS_EVENT *UALEvent)
{
    int ret = ITS_SUCCESS;
    ASP_Entry aspRec, *aspEntryPtr = NULL;
    TRANSPORT_Control *tc = NULL;
    ITS_USHORT        trid;
    UAL_CB_Context    cb_ctxt;
    int               i = 0;

    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));
    memcpy(&trid, &UALEvent->data[0], sizeof(ITS_USHORT));
    
    i = sizeof(ITS_USHORT) + 1;

    ASPTable_FindEntry(trid, &aspEntryPtr);

    UAL_DEBUG(("UAL_HandleSCTPIndication: Got an assoc change "
			   "indication type: %02x (%s).\n", UALEvent->data[i], 
			   SCTP_INDICATION_TYPE_STRING(UALEvent->data[i])));

    /*
     * we are interested in assoc change Indications 
     */
    if (UALEvent->data[i] == SCTP_AC_COMM_UP ||
        UALEvent->data[i] == SCTP_AC_COMM_RESTART)
    { 
        UAL_DEBUG(("UAL_HandleSCTPIndication: received SCTP_AC_COMM_UP "
                         "on trid %d.\n", trid));

        tc = TRANSPORT_FindTransport(trid);
        if (tc == NULL)
        {
            UAL_ERROR(("FindTransport Failed, invalid instance %d\n",
                             trid));
            return ITS_EBADTRANSPORT;
        }

        TRANSPORT_UnfindTransport(tc);

        UALPEGMgr_AddElement(trid);

        if ( UALEvent->data[i] == SCTP_AC_COMM_UP)
        {
            UAL_Alarm(4002,  __FILE__, __LINE__, NULL);
        }
        else
        {
            UAL_Alarm(4005,  __FILE__, __LINE__, NULL);
        }

        if(aspEntryPtr != NULL)
        {
            ret = UAL_TableCleanUp(aspEntryPtr, UALEvent->data[i]);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleSCTPIndication: Error cleaning up "
                                 "the mess after ASSOC_LOST, code %d \n", ret));
            }
        }

        aspRec.payload = SCTPTRAN_PAYLOAD(tc);

        if (!UAL_SUPPORTED_PAYLOADS(aspRec.payload))
        {
            UAL_ERROR(("Unsupported Payload Type: %d, for transport: %d\n",
                             aspRec.payload, trid));

            return ITS_EBADTRANSPORT;
        }

        if(UAL_GL_ITW_MODE != UAL_ITW_SG && UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
        {
            aspRec.aspId = localaspId;
            UAL_GL_ASP_ID = aspRec.aspId;
            UAL_ERROR(("ASPId assigned is %d",aspRec.aspId));
        }
        else if ( (UAL_GL_ASP_ID != -1) && ( UAL_GL_ITW_MODE != UAL_ITW_SG ))
        {
            aspRec.aspId = UAL_GL_ASP_ID;
        }

	/* initialize the timer array */
	aspRec.ackTimer[ASP_UP_MSG] = (ITS_UINT)0;
	aspRec.ackTimer[ASP_DOWN_MSG] = (ITS_UINT)0;
	aspRec.ackTimer[ASP_ACTIVE_MSG] = (ITS_UINT)0;
	aspRec.ackTimer[ASP_INACTIVE_MSG] = (ITS_UINT)0;
	
        aspRec.trId = trid;

        aspRec.state = UAL_ASP_DOWN;

        aspEntryPtr = ASPTable_AddEntry(&aspRec);
        
        if (aspEntryPtr == NULL)
        {
            UAL_ERROR(("UAL_HandleSCTPIndication: Error adding ASP "
                       "entry to ASP_Table, trid: %d \n", 
                       trid));
            return ITS_ENOMEM;
        }

        if (UAL_GL_ITW_MODE != UAL_ITW_SG && !UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
        {
	    HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, aspEntryPtr,
		       NULL, Add_List_of_AS_to_ASP_list_of_AS_hash_iterative_proc);

            ret = UAL_SendASPUP(aspEntryPtr);

            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleSCTPIndication: Could not send "
                                 "ASPUP, code %d.\n", ret));

                return ret;
            }
            //CALLBACK_CallCallbackList(__UAL_SCTPMgntCallBack, NULL,
              //      (ITS_POINTER) aspEntryPtr);
        }
    }
    else if (UALEvent->data[i] == SCTP_AC_COMM_LOST ||
             UALEvent->data[i] == SCTP_AC_COMM_ABORTED)
    {
        UAL_Alarm(4001,  __FILE__, __LINE__, NULL);

        UALPEGMgr_RemoveElement(trid);

        if(aspEntryPtr != NULL)
        {
            ret = UAL_TableCleanUp(aspEntryPtr, UALEvent->data[i]);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleSCTPIndication: Error cleaning up "
                                 "the mess after ASSOC_LOST, code %d \n", ret));
            }
        }

        UAL_CB_CTXT_TYPE(&cb_ctxt) = UAL_CB_ASP_CTXT;
        UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_DOWN;
        UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = trid;

        /* aspEntry is gone, set aspid to unknown(-1) */
        UAL_CB_CTXT_ASP_ID(&cb_ctxt) = -1;

        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                  (ITS_POINTER) &cb_ctxt);
    }
    else if(UALEvent->data[i] == SCTP_AC_CANT_START)
    {
        UAL_Alarm(4003,  __FILE__, __LINE__, NULL);
        UAL_CB_CTXT_TYPE(&cb_ctxt) = UAL_CB_ASP_CTXT;
        UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_CANT_START;
        UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = trid; 

        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
			          (ITS_POINTER) &cb_ctxt);
    }
    else
    {
        UAL_DEBUG(("UAL_HandleSCTPIndication: Ignoring SCTP indication "
                         "%d, on trid %d.\n", UALEvent->data[i], 
                         trid));
    }

    return ret;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *
 *    None.      
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    None.
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Modified function for proper handling
 *                                       of Link Removal at SG, when pending 
 *                                       timer is expired.
 *
 *  See Also:
 ******************************************************************************/
static int 
UAL_TableCleanUp(ASP_Entry *aspEntryPtr, ITS_OCTET indication)
{
    UAL_DEBUG(("UAL_TableCleanUp Entry"));
    int ret = ITS_SUCCESS;

    ITS_C_ASSERT(aspEntryPtr != NULL);

    if (aspEntryPtr->asList == NULL)
    {
        UAL_WARNING(("AS List for ASP not Initialized, trid %d\n",
                           aspEntryPtr->trId));
        return ITS_ENOTFOUND;
    }

    if(AS_LIST_COUNT(aspEntryPtr->asList) != 0)  
    {
        RKListNode* rkNode = NULL;
        ITS_BOOLEAN flag = ITS_TRUE; /* all asp's are down*/
        UAL_CB_Context cb_ctxt;
        TRANSPORT_Control *tc = NULL;

        memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

        rkNode = RKList_Iterate(aspEntryPtr->asList);

        for(; rkNode; rkNode = RKList_Iterate(NULL))
        {
            ITS_UINT key = rkNode->entry->rCtxt;
            ASPListNode *aspNode = NULL;

            /* 1) remove the entry in ASP list for the AS */
            if(rkNode->entry->aspList)
            {
                ITS_BOOLEAN aspClean = ITS_FALSE;

                aspNode = ASPList_Iterate(rkNode->entry->aspList);
                for(;aspNode; aspNode = ASPList_Iterate(NULL))
                {
                    if (aspNode->trId == aspEntryPtr->trId)
                    {
                        aspNode->trId = 0x0000U;
                        aspNode->state = UAL_ASP_DOWN;
                        aspNode->entry = NULL; 

                        aspClean = ITS_TRUE;
                    }
                    else
                    {
                        int aspid = -1;
                        if (UAL_IS_APP_IPSP(UAL_GL_ITW_MODE))
                        {
                            aspid = aspEntryPtr->remoteInfo.aspInfo.aspid;
                        }
						else
						{
                            aspid = aspEntryPtr->aspId;
						}

                        /*Notify ASP failure to other ACTIVE ASPs */
                        ret = UAL_SendNotify(aspNode->trId,
                                             UAL_ST_TYPE_OTHER,
                                             UAL_ST_ASP_FAILURE,
                                             &key, 1, aspid);
                    }

                    if (aspNode->state != UAL_ASP_DOWN)
                    {
                        flag = ITS_FALSE;
                    }
                }

                if(aspClean == ITS_FALSE)
                {
                    UAL_ERROR(("UAL_commLostTableCleanUp: error "
                                     "finding ASP entry in AS table %d \n",
                                      aspEntryPtr->trId));
                }
            }
            else
            {
                /* nothing was configures statically */
            }

            /* 
             * 2) We know the Link and the Linkset, now remove the link
             */
            if ((rkNode->entry->state == UAL_AS_ACTIVE) &&
		!rkNode->entry->isMember)
            {
                SS7_LinkSetPtr linkSetPtr = NULL;

                /* 
                 * if there are no more links in the linkset, set the state to
                 * down.
                 */
                linkSetPtr = LINKSET_FindLinkSet(rkNode->entry->linkSet);
                if (linkSetPtr == NULL)
                {
                    UAL_ERROR(("Error finding LinkSet: %d\n", 
				      rkNode->entry->linkSet));
                }
                else if (linkSetPtr->numLinks == 1)
                {
                    tc = TRANSPORT_FindTransport(aspEntryPtr->trId);
                    if (tc == NULL)
                    {
                      UAL_ERROR(("FindTransport Failed, invalid instance %d\n",
                             aspEntryPtr->trId));
                      return ITS_EBADTRANSPORT;
                    }
 
                    TRANSPORT_UnfindTransport(tc);
 
                    TRANSPORT_SetState(tc, ITS_FALSE);

                    ret = LINKSET_SetLinkSetState(linkSetPtr, ITS_FALSE);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("Error changing LinkSet: %d to DOWN. \n",
                                          rkNode->entry->linkSet));
                    }
                }
                if (rkNode->linkCode != ASP_LINK_CODE_MASK)
                {
                    UAL_RemLink(rkNode->entry->linkSet, rkNode->linkCode);
                }
            }

            if ((indication == SCTP_AC_COMM_LOST)    ||
                (indication == SCTP_AC_COMM_ABORTED) ||
                (indication == SCTP_AC_COMM_RESTART))
            { 
                if (UAL_CheckASPending(rkNode->entry))
                {
                    rkNode->entry->state = UAL_AS_PENDING;

                    ret = UAL_StartPendingStateProcedure(rkNode->entry);

                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_commLostTableCleanUp: error "
                                         "starting pending state proc for "
                                         " AS %d \n", key));
                    }
                }
            }

            //if (flag && rkNode->entry->state == UAL_AS_INACTIVE)
            if (flag)
            {
                UAL_DEBUG(("Setting state of AS to UAL_AS_DOWN"));
                rkNode->entry->state = UAL_AS_DOWN;

                UAL_CB_CTXT_TYPE(&cb_ctxt) = UAL_CB_AS_CTXT;
                UAL_CB_CTXT_AS_STATE(&cb_ctxt) = UAL_AS_DOWN;
                UAL_CB_CTXT_RKEY(&cb_ctxt)     = key;
                UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = 0;

                CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                          (ITS_POINTER) &cb_ctxt);
            }

            /* 4) remove the AS entry for that ASP in the list */
            ret = RKList_RemoveEntry(aspEntryPtr->asList, key);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_commLostTableCleanUp: error "
                                 "deleting AS entry in list"
                                 " AS %d \n", key));
            }
        }

        /* 5) remove the ASP entry in the ASP table */
        ret = ASPTable_RemoveEntry(aspEntryPtr->trId);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_commLostTableCleanUp: could not remove "
                             "ASP entry: %d\n", aspEntryPtr->trId));
        }
    }
    UAL_DEBUG(("UAL_TableCleanUp Exit"));

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *
 *    None.      
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    None.
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Modified functionality of Adding Link
 *                                       during starup of Pending procedure when
 *                                       Last Active ASP in given AS goes
 *                                       Inactive/Down.
 *                                       
 *  See Also:
 *
 ******************************************************************************/
int
UAL_StartPendingStateProcedure(RK_Context* asContext)
{
    int ret = ITS_SUCCESS;
    ASPListNode *aspNode = NULL; 
    UAL_TimerCtx timerCtx;
    char tqName[40];
    SS7_Link       link;

    ITS_C_ASSERT(asContext != NULL);

    /* 1) get the linkset */
    memset(&link, 0, sizeof(SS7_Link));

    if (asContext->isMember)
    {
	/*
	 * We do not want to start pending procedure for
	 * the members of the local routing keys. 
	 */
	UAL_DEBUG(("UAL_StartPendingStateProcedure:"
		         "We are ASP fro rctxt %d", asContext->rCtxt));

	return ITS_SUCCESS;
    }

    UAL_WARNING(("UAL_StartPendingProcedure.\n"));

    /* 2) create the pending queue */
    if(asContext->pendingTrans != NULL)
    {
        if (asContext->state == UAL_AS_PENDING)
        {
            return ITS_SUCCESS; /* TODO think about wether ITS_SUCCESS */
        }
        else
        {
            TQUEUETRAN_DeleteTransport(asContext->pendingTrans);
            asContext->pendingTrans = NULL;
        }

    }
    
    sprintf(tqName, "PENDING %d", asContext->rCtxt);

    asContext->pendingTrans = (ITS_HANDLE)TQUEUETRAN_CreateTransport(tqName,
                                      (ITS_USHORT)(0xFB00 + asContext->rCtxt),
                                      0);
    if(asContext->pendingTrans == NULL)
    {
        UAL_ERROR(("UAL_STartPendingStateProcedure: Failed to Create"
		         " TQUEUE:\n"));
         
        return ITS_ENOQUEUE;            
    }

    TRANSPORT_SetState(asContext->pendingTrans, ITS_TRUE);
    TRANSPORT_EXIT_NOW(asContext->pendingTrans) = ITS_FALSE;

    UAL_AddLink(asContext, NULL, asContext->pendingTrans);

    /* 4) Start pending timer */
    timerCtx.type       = UAL_PENDING;
    timerCtx.len        = sizeof(ITS_UINT);
    timerCtx.retryCount = UAL_GL_NUM_RETRY;

    memcpy(timerCtx.msg, &asContext->rCtxt, sizeof(ITS_UINT));

    asContext->pendingTimer = TIMERS_StartTimer(UAL_MANAGER_INSTANCE, 
                                                UAL_GL_PEND_TIMER, 
                                                (void *)&timerCtx, 
                                                sizeof(UAL_TimerCtx));

    /* 5) send NTFY messages to Inactive ASPs if any */
    ASPList_Iterate(asContext->aspList);

    aspNode = ASPList_Iterate(asContext->aspList);

    for(; aspNode; aspNode = ASPList_Iterate(NULL))
    {
        if (aspNode->state == UAL_ASP_INACTIVE)
        {
            ret = UAL_SendNotify(aspNode->trId, UAL_ST_TYPE_AS_STAT_CHG,
                                 UAL_ST_ID_AS_PENDING, &asContext->rCtxt, 1, 0);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_StartPendingStateProcedure, Error sending"
                                 " NTFY on trid %d \n", aspNode->trId));
            }
        }
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *
 *    None.      
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    None.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_SendNotify(ITS_USHORT trid, ITS_USHORT type, ITS_USHORT id,
               ITS_UINT *rkArray, int len, ITS_INT aspId)
{
    int ret = ITS_SUCCESS;
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_EVENT msg;
    int ieCount = 0;

    ITS_EVENT_INIT(&msg, UAL_MANAGER_INSTANCE, UAL_MAX_MSG_LEN);

    UAL_DEBUG(("UAL_SendNotify: sending NTFY to trid %0x, "
                 "type=%d id=%d\n", trid, type, id));

    /* build the Notify Message */
    ies[ieCount].param_id = UAL_PRM_MSG_HDR;
    ies[ieCount].param_length =  sizeof(UAL_MSG_HDR);
    ies[ieCount].param_data.msgHeader.msgClass = UAL_CLASS_MGMT;                                     
    ies[ieCount].param_data.msgHeader.msgType = UAL_MSG_NOTIFY;
    ies[ieCount].param_data.msgHeader.version = UAL_GL_VERSION;
    ies[ieCount].param_data.msgHeader.reserved = 0x00;

    ieCount++;

    ies[ieCount].param_id = UAL_PRM_STATUS;
    ies[ieCount].param_length =  sizeof(UAL_STATUS_TYPE);
    ies[ieCount].param_data.statusType.type = type;
    ies[ieCount].param_data.statusType.id = id;

    ieCount++;

    ies[ieCount].param_id = UAL_PRM_ROUT_CTX;
 
    ret = UAL_EncodeRoutingContext(ies[ieCount].param_data.rCtxt.rCtxt,
                                   &(ies[ieCount].param_length),
                                   rkArray, len);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_SendNotify: failed to encode Routing "
                         "Context.\n"));
        return ret;
    }

    ieCount++;

    if(type == UAL_ST_TYPE_OTHER)
    {
         ies[ieCount].param_id = UAL_PRM_ASP_ID;
         ies[ieCount].param_length =  sizeof(UAL_PRM_ASP_ID);
         ies[ieCount].param_data.aspId.aspId = aspId;
         ieCount++;
    }

    /* encode the NOTIFY message */
    ret = UAL_EncodeMsg(ies, ieCount, &msg, &UAL_NTFY_Desc);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_SendNotify: M3UA_EncodeMsg failed code %d.\n",
                         ret));
    }

    ret = TRANSPORT_PutEvent(trid, &msg);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_SendNotify: TRANSPORT_PutEvent failed:"
                         " code %d.\n", ret));
    
    }
    else
    {
        UAL_IncrementMIBStats(trid, UAL_PEG_NOTIFY_SENT_ID);
    }

    return ret;
}

/*.implementat.ion:extern
 ******************************************************************************
 *  Purpose:
 *    This function is used to build and send an ASPUP message over a SCTP
 *    association 
 *     
 *  Input Parameters:
 *
 *    assocRec - a pointer to the ASSOC_Record of the association to send the
 *               message to.     
 *
 *  Input/Output Parameters:
 *
 *    None.      
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS - any other return values would indicate that an error 
 *    occured
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_SendASPUP(ASP_Entry *aspEntry)
{
    int           ret = ITS_SUCCESS, ieCount = 0;
    ITS_UAL_IE    ies[ITS_MAX_UAL_IES];
    ITS_EVENT     msg;
    UAL_TimerCtx  timerCtxt;
    ITS_USHORT    trid  = aspEntry->trId;
    ITS_BOOLEAN   flag  = ITS_TRUE;
    ITS_INT       count = 1; /* Send number of "count" ASP_UPs */

    ITS_C_ASSERT(aspEntry != NULL);

    if (!UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        UAL_DEBUG(("UAL_SendASPUP: Sending ASPUP to trid %d.\n", 
                     aspEntry->trId));
    }

    /* 1) build the ASPUP Message array of ies */
    ies[0].param_id     = UAL_PRM_MSG_HDR;
    ies[0].param_length =  sizeof(UAL_MSG_HDR);

    ies[0].param_data.msgHeader.msgClass = UAL_CLASS_ASPSM;                                            
    ies[0].param_data.msgHeader.msgType  = UAL_MSG_ASPUP;
    ies[0].param_data.msgHeader.version  = UAL_GL_VERSION;
    ies[0].param_data.msgHeader.reserved = 0x00;

    ieCount++;

    if (UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE))
    {
        count = 2; /* Send one ASP_UP to remote
                    * and one to ITSELF
                    */
        msg.src = aspEntry->trId;
    }
    else if (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        ITS_EVENT_INIT(&msg, trid, 0); /* Fake event */
        flag = ITS_FALSE;
    }
    else
    {
        /* Only if it is IPSP double exchange/ASP */
        ITS_EVENT_INIT(&msg, UAL_MANAGER_INSTANCE, 0);
    }

    while (count)
    {
        /*
         * Set ASP ID if the app is not running as IPSP SE server
         */
        if (UAL_GL_ASP_ID!=-1 && !(UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE)))
        {
            /* 1.5) if known put in the ASPID */
            ies[1].param_id     = UAL_PRM_ASP_ID;
            ies[1].param_length = sizeof(UAL_ASP_ID);                       
            ies[1].param_data.aspId.aspId = UAL_GL_ASP_ID;

            ieCount++;
        }

        ITS_EVENT_INIT(&msg, UAL_MANAGER_INSTANCE, UAL_MAX_MSG_LEN);
                         
        /* 2) encode the ASPUP message */
        ret = UAL_EncodeMsg(ies, ieCount, &msg, &UAL_ASPUP_Desc);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_SendASPUP: M3UA_EncodeMsg failed code %d.\n",
                             ret));

            return ret;
        }

        if (flag)
        {
	    /* 3) setup the timer data for retransmission */
	    timerCtxt.type       = UAL_RETRANS;
            timerCtxt.from       = aspEntry->trId;
            timerCtxt.retryCount = UAL_GL_NUM_RETRY;
            timerCtxt.tm         = UAL_MODE_NONE;
            timerCtxt.msgType    = ASP_UP_MSG;
            timerCtxt.ackMsgType = UAL_MSG_ASPUP_ACK;

            ITS_INT xret = UAL_SetTimerMsgData(&timerCtxt, &msg);
            if (xret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_SendASPUP: UAL msg too long for timer."));

                return ret;
            }

            /* 4) send the message to the transport */
            ret = TRANSPORT_PutEvent(trid, &msg);

            /* Timer info in ASP record */
            memcpy(&aspEntry->timerCtx, &timerCtxt, sizeof(UAL_TimerCtx));

            UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_UP_SENT_ID);

            /* 5) start ASPUP_ACK Timer */
            aspEntry->ackTimer[ASP_UP_MSG] = TIMERS_StartTimer(UAL_MANAGER_INSTANCE,
                                                                  UAL_GL_ACK_TIMER,
                                                                  (void *)&timerCtxt,
                                                                  sizeof(UAL_TimerCtx));
        }
        else
        {
            msg.src = trid;
            ret = UAL_ProcessASPUP_IPSP_SE(aspEntry, &msg);

            ITS_EVENT_TERM(&msg);
        }
        
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_SendASPUP: TRANSPORT_PutEvent failed: "
                             "trid %d code %d.\n", aspEntry->trId, ret));

            return ret;
        }
        
        /* IPSP Single exchange.
         * 1. In IPSP server mode put asp_up on ual transport.
         * 2. Set transport ids so that in server mode they won't be
         *    dropped by UAL transport.
         */
        msg.src  = UAL_MANAGER_INSTANCE;
        trid     = aspEntry->trId;
        flag     = ITS_FALSE; /* Do not send second time */
        count--;
    }

    return ret;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *    This function is used to send an ERR message over an SCTP association.
 *     
 *  Input Parameters:
 *
 *    trid - transport id to send the message to.
 *    errorCode - error code to set in the message.
 *     
 *
 *  Input/Output Parameters:
 *
 *    None.      
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS - any other return value indicates that an error occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_SendERR(ITS_USHORT trid, ITS_UINT errorCode, ITS_UAL_IE *moreIes, int size)
{
    int ret = ITS_SUCCESS, i = 0, ieCount = 0;
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_EVENT msg; 

    ITS_EVENT_INIT(&msg, UAL_MANAGER_INSTANCE, UAL_MAX_MSG_LEN); 

    UAL_DEBUG(("UAL_SendERR: sending ERR to trid %d, error "
                     "code %02x.\n", trid, errorCode));

    /* 1) build the ERROR Message */
    ies[0].param_id = UAL_PRM_MSG_HDR;
    ies[0].param_length =  sizeof(UAL_MSG_HDR);
    ies[0].param_data.msgHeader.msgClass = UAL_CLASS_MGMT;                                            
    ies[0].param_data.msgHeader.msgType = UAL_MSG_ERR;
    ies[0].param_data.msgHeader.version = UAL_GL_VERSION;
    ies[0].param_data.msgHeader.reserved = 0x00;

    ieCount++;

    ies[1].param_id = UAL_PRM_ERROR_CODE;
    ies[1].param_length =  sizeof(UAL_ERROR_CODE);
    ies[1].param_data.errCode.eCode = errorCode;
    
    ieCount++;

    /* 2) add in additional ies depending on error codes... */
    for (i = 0; i < size; i++)
    {
        if(moreIes->param_id == UAL_PRM_DIAGNOSTIC)
        {
            memcpy(&ies[i + 2], moreIes, sizeof(UAL_DIAG_INFO));
        }
        else
        {
            memcpy(&ies[i + 2], moreIes, sizeof(ITS_UAL_IE));
        }

        moreIes++;

        ieCount++;
    }

    /* 3) encode the ERROR message */
    ret = UAL_EncodeMsg(ies, ieCount, &msg, &UAL_ERR_Desc);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_SendERR: UAL_EncodeMsg failed code %d.\n", 
                         ret));
        return ret;
    }

    /* 4) send the message */
    ret = TRANSPORT_PutEvent(trid, &msg);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_SendERR: TRANSPORT_PutEvent failed:"
                         " code %d.\n", ret));
    }   
    else
    {
        UAL_IncrementMIBStats(trid, UAL_PEG_ERR_SENT_ID);
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *    This function is used to handle timer events received on the UAL
 *    transport. We differentiate between two types of timer events:
 *    -it is a pending timer; this means that one of the AS we are talking to
 *    was pending and the timer expired. In that case the status of the AS is
 *    marked as Down in the AS Table.
 *    -it is an Ack timer; this means that no response to a message was 
 *    received (ASPUP,DN,ACT,INAC). We then proceed to retransmit that same 
 *    message and restart the timer.
 *   
 *     
 *  Input Parameters:
 *     
 *    td - a pointer to the ITS_TimerData structure containing the timer
 *    message that the function needs to handle.
 *
 *  Input/Output Parameters:
 *      
 *    None.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS - any other return value would indicate an erroe occured.
 *
 *  Notes:
 *
 *    We can have two types of timers: a Pending timer, in that case the
 *    "pending" parameter in the timer context is true, or it can be am
 *    Acknowledgement timer meaning that no response was received for a
 *    previously sent msg. In that case, the timer ctx will contain the 
 *    message to be retransmitted.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Modified function for proper handling
 *                                       of Link Removal at SG, when pending 
 *                                       timer is expired.
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_HandleTimerEvent(ITS_TimerData *td)
{
    UAL_DEBUG(("UAL_HandleTimerEvent Entry"));
    int ret = ITS_SUCCESS;
    UAL_TimerCtx  ctx;
    ITS_EVENT     ualMsg;
    UAL_CB_Context cb_ctxt;

    ualMsg.src = UAL_MANAGER_INSTANCE;

    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    memcpy(&ctx, td->context, sizeof(UAL_TimerCtx));

    UAL_DEBUG(("UAL_HandleTimerEvent\n"));

    if (ctx.type == UAL_PENDING)
    {
        ITS_UINT as;
        RK_Context *asContext = NULL;
        ASPListNode *aspNode = NULL; 
        int inactiveCount = 0; 
        TRANSPORT_Control *tc = NULL;
    
        memcpy(&as, ctx.msg, sizeof(ITS_UINT));

        UAL_DEBUG(("UAL_HandleTimerEvent: Pending timer event Received"
                         " for AS %d.\n", as));

        /* 1) find as Context in AS_Table */
        asContext = RKManager_FindEntry(as);
        if (asContext != NULL)
        {
            /* 2) Remove the route to the pending Queue */
            tc = (TRANSPORT_Control*)asContext->pendingTrans;

            TRANSPORT_SetState(tc, ITS_FALSE);

            UAL_DEBUG(("Checking  linkInfo \n"));
            if(TRANSPORT_SS7_INFO(tc).linkInfo)
            {
                UAL_RemLink(asContext->linkSet, TRANSPORT_SS7_INFO(tc).linkInfo->linkCode);
            }
            else
            {
                UAL_DEBUG(("NULL linkInfo \n"));
            }

            /* 3) reset timer */
            asContext->pendingTimer = 0;

            /* 4) set state to inactive first */
            asContext->state = UAL_AS_INACTIVE;
            
            /* 5) delete the TQUEUE containing the pending messages */
            TQUEUETRAN_DeleteTransport((TQUEUETRAN_Manager*)asContext->pendingTrans);

            asContext->pendingTrans = NULL;

            /* 6) check if any ASP inactive for that AS */
            aspNode = ASPList_Iterate(asContext->aspList);

            for(; aspNode; aspNode = ASPList_Iterate(NULL))
            {
                if (aspNode->state == UAL_ASP_INACTIVE)
                {
                    ret = UAL_SendNotify(aspNode->trId, UAL_ST_TYPE_AS_STAT_CHG,
                                         UAL_ST_ID_AS_INACTIVE, 
                                         &asContext->rCtxt, 1, 0);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_StartPendingStateProcedure, Error "
                                         "sending NTFY on trid %d \n",
                                         aspNode->trId));
                    }
                    
                    inactiveCount++;
                }
                else if (aspNode->state == UAL_ASP_DOWN)
                {
                    if (aspNode->entry)
                    {
                        ret = RKList_RemoveEntry(aspNode->entry->asList, as);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_WARNING(("Unable to find as %d in ASP %d"
                                               " list of AS\n", as,
                                               aspNode->aspInfo.aspid));
                        }
                    }
                }
            }

            /* 7) no ASP inactive, the state of the AS is now down */
            if (inactiveCount == 0)
            {
                UAL_DEBUG(("Setting the AS State to Down"));
                asContext->state = UAL_AS_DOWN;
            }

            UAL_CB_CTXT_TYPE(&cb_ctxt) = UAL_CB_AS_CTXT;
            UAL_CB_CTXT_AS_STATE(&cb_ctxt) = asContext->state;
            UAL_CB_CTXT_RKEY(&cb_ctxt)     = asContext->rCtxt;
            UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = 0;

            CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                      (ITS_POINTER) &cb_ctxt);
        }
        else
        {
            UAL_ERROR(("UAL_HandleTimerEvent: no AS entry for RK %d.\n",
                             as));

            return ret;
        }

    }
    else if (ctx.type == UAL_RETRANS)
    {
        ASP_Entry  *aspRec = NULL;

        UAL_DEBUG(("UAL_HandleTimerEvent: Got a retransmit timer \n"));
        
        /* 1) find ASP entry */
        ret = ASPTable_FindEntry(ctx.from, &aspRec);
        if(aspRec != NULL) 
        {
            if (ctx.retryCount == 0)
            {
                /* No more retransmit !!! */

                UAL_WARNING(("HandleTimerEvent: Reached Max retrans count \n"));

                return ret;
            }

            ITS_EVENT_INIT(&ualMsg, UAL_MANAGER_INSTANCE, ctx.len);

            ctx.retryCount--;
            
            memcpy(ualMsg.data, ctx.msg, ctx.len);
    
            UAL_DEBUG(("UAL_HandleTimerEvent: Retransmitting event\n"));

            /* 2) get the trid and resend the msg on that transport */
            ret = TRANSPORT_PutEvent(ctx.from, &ualMsg);
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleTimerEvent: Could not send event,"
                           " code %d", ret));
                return ret;
            }
            
            /* 3) restart timer and update retry count */
            aspRec->ackTimer[ctx.msgType] = TIMERS_StartTimer(UAL_MANAGER_INSTANCE,
                                                          UAL_GL_ACK_TIMER, 
                                                          (void *)&ctx, 
                                                          sizeof(UAL_TimerCtx));
        }
        else
        {
            if (ctx.retryCount == 0)
            {
                /* TODO: Notify Layer Management that we tried */
            }

            UAL_ERROR(("UAL_HandleTimerEvent: could not find assoc "
                             "record"));

            return ret;
        }
    }
    else if(ctx.type == UAL_DAUD_MESG)
    {
        UAL_DEBUG(("UAL_HandleTimerEvent: Got a Audit timer Expiry\n"));

        ret = AuditTimersTable_TimerExpiry(ctx);
    }	

    UAL_DEBUG(("UAL_HandleTimerEvent Exit"));
    return ret;
}
