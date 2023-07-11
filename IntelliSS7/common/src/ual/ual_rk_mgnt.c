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
 *  ID: $Id: ual_rk_mgnt.c,v 9.11.52.1 2014/11/17 04:59:50 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_rk_mgnt.c,v $
 *  LOG: Revision 9.11.52.1  2014/11/17 04:59:50  jkchaitanya
 *  LOG: changes for HA Bug Fixes
 *  LOG:
 *  LOG: Revision 9.11  2008/06/30 14:05:26  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.10  2008/06/29 15:17:20  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.9  2008/05/25 17:11:25  kramesh
 *  LOG: Whizible Bug ID 932. Incorrect Routing Key printing.
 *  LOG:
 *  LOG: Revision 9.8  2008/05/01 16:18:31  kramesh
 *  LOG: Propagated Bridgeport issue 1541. Routing Key more than 255.
 *  LOG:
 *  LOG: Revision 9.7  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.6.2.3  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.6.2.2  2007/04/26 06:57:23  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - added code to check DecodeMsg() return values and take appropriate action
 *  LOG: - raised 4026 alarm (for invalid msgType)
 *  LOG:
 *  LOG: Revision 9.6.2.1  2007/04/05 14:42:34  pspl
 *  LOG: peg count increments replaced by the call to UAL_IncrementMIBStats()
 *  LOG:
 *  LOG: Revision 9.6  2005/12/09 00:52:29  cbashyam
 *  LOG: Bug fixes for Bug ID : 2520
 *  LOG:
 *  LOG: Revision 9.5  2005/12/08 03:40:04  clin
 *  LOG: fix bug #2482
 *  LOG:
 *  LOG: Revision 9.4  2005/11/30 23:49:56  clin
 *  LOG: remove warning.
 *  LOG:
 *  LOG: Revision 9.3  2005/07/04 03:12:44  randresol
 *  LOG: Make code compatible with ANSI-C
 *  LOG:
 *  LOG: Revision 9.2  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:49  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:19  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1.4.1.2.1.10.2  2005/01/04 14:56:34  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.1.4.1.2.1.10.1  2004/12/15 13:15:37  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.1.4.1.2.1  2004/05/03 12:56:46  ssingh
 *  LOG: BUG #786/795/796/797 fixes for Registration and Deregistration of RKey.
 *  LOG:
 *  LOG: Revision 7.1.4.1  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.4  2002/07/08 18:18:30  ngoel
 *  LOG: add ual alarms
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

static void
UAL_SetDeRegRes(ITS_OCTET *resultData, ITS_UINT rCtxt, ITS_UINT status);
static int 
UAL_GetDeregRes(ITS_OCTET *resultData, ITS_UINT *rCtxt, ITS_UINT *status);

/*
 *
 * Dynamic registration procedures.
 *
 */



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_HandleRKMMsg(ITS_EVENT *UALEvent, ITS_USHORT msgType, ASP_Entry *aspEntry)
{
    int ret = ITS_SUCCESS, recIECount = 0, sendIECount = 1, i = 0;
    ITS_UAL_IE recIE[ITS_MAX_UAL_IES];
    ITS_UAL_IE sendIE[ITS_MAX_UAL_IES];
    RK_Context *asCtxt = NULL;
    ITS_EVENT rEvent;
    ITS_OCTET aspCapabIndex = ITS_MAX_UAL_IES;
    UAL_CB_Context cb_ctxt;
    ITS_UINT localRkId = 0, result = 0, rCtxt = 0;
    ITS_UAL_IE diagnInfo;

    ITS_EVENT_INIT(&rEvent, UAL_MANAGER_INSTANCE, 256);
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));


    switch (msgType)
    {
    case UAL_MSG_REG_REQ:
    {
        UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_REG_REQ_RECV_ID);

        if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
        {
            ret = UAL_DecodeMsg(recIE, &recIECount, UALEvent, 
                                &UAL_SUA_REGREQ_Desc);
        }
        else
        {
            ret = UAL_DecodeMsg(recIE, &recIECount, UALEvent, &UAL_REGREQ_Desc);
        }
        CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Error decoding message \n"));

            return ret;
        }

        UAL_Alarm(4018, __FILE__, __LINE__, NULL);

        sendIE[0].param_id = UAL_PRM_MSG_HDR;
        sendIE[0].param_length = sizeof(UAL_MSG_HDR);
        sendIE[0].param_data.msgHeader.msgClass = UAL_CLASS_RKM;
        sendIE[0].param_data.msgHeader.msgType = UAL_MSG_REG_RSP;
        sendIE[0].param_data.msgHeader.version = UAL_GL_VERSION;
        sendIE[0].param_data.msgHeader.reserved = 0x00;


        for (i = 1; i < recIECount; i++)
        {
            if (recIE[i].param_id  == SUA_PRM_ASP_CAPAB)
            {
                aspCapabIndex = i;
            }
        }
        
        for (i = 1; i < recIECount; i++)
        {
            /* skip other ies */
            if ((recIE[i].param_id  != UAL_PRM_ROUTING_KEY) &&
               (recIE[i].param_id  != SUA_PRM_RKEY))
            {
                continue;
            }

            asCtxt = (RK_Context *)calloc(1, sizeof(RK_Context));

            if (asCtxt != NULL)
            {
                if ( recIE[i].param_id  == SUA_PRM_RKEY)
                {
                    sendIE[i].param_id = SUA_PRM_REG_RES;
                    sendIE[i].param_length = SUA_MAX_REG_RES_LEN;

                    ret = UAL_SuaRoutingKeyToRKContext(asCtxt, 
                                          recIE[i].param_data.rkData.RKData,
                                          recIE[i].param_length);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_HandleRKMMsg: error "
                                         "populating RK Ctxt, code %d \n", 
                                         ret));

                        UAL_SetSuaRegRes(sendIE[i].param_data.regResult.
                                         regRes, asCtxt->rCtxt, 
                                         UAL_REG_STAT_ERR_UNSUFF_RES, 0);
                        continue;
                    }

                    UAL_CheckNewSuaRoutingKeyValid(asCtxt, 
                                             sendIE[i].param_data.regResult.
                                             regRes);

                    sendIECount++;

                    if ( aspCapabIndex != ITS_MAX_UAL_IES)
                    {
                        memcpy(&asCtxt->aspCapab, &(recIE[aspCapabIndex].
                              param_data), recIE[aspCapabIndex].param_length);
                    }
                    continue;
                }

                sendIE[i].param_id = UAL_PRM_REG_RES;
                sendIE[i].param_length = UAL_MAX_REG_RES_LEN;

                ret = UAL_RoutingKeyToRKContext(asCtxt, 
                                                recIE[i].param_data.rkData.RKData,
                                                recIE[i].param_length);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("UAL_HandleRKMMsg: error "
                                     "populating RK Ctxt, code %d \n", ret));

                    UAL_SetRegRes(sendIE[i].param_data.regResult.regRes,
                                  asCtxt->rCtxt, UAL_REG_STAT_ERR_UNSUFF_RES,
                                  0);
                    continue;
                }

                asCtxt->reqState = UAL_AS_REG;

                ret = UAL_CheckNewRoutingKeyValid(asCtxt, 
                                         sendIE[i].param_data.regResult.regRes);
            }
            else
            {
                UAL_ERROR(("UAL_HandleRKMMsg: malloc failed !!!! \n"));
   
                return ITS_ENOMEM;
            }

            sendIECount++;

            if (ret == ITS_EDUPLENTRY)
            {
                continue;
            }
            else if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleRKMMsg: Unsupported Traffic Mode\n"));

                UAL_SetRegRes(sendIE[i].param_data.regResult.regRes,
                               asCtxt->rCtxt, UAL_REG_STAT_ERR_INVALID_THM, 0);


                UAL_SendERR(aspEntry->trId, UAL_ERR_UNSU_THM, 0, 0);

                return (!ITS_SUCCESS);
            }

            ret = UAL_GetRegRes(sendIE[i].param_data.regResult.regRes,
                                sendIE[i].param_length, &localRkId,
                                &result, &rCtxt);

            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleRKMMsg: Error decoding RegRes\n"));
                continue;
            }
            else
            {
                if (result == UAL_REG_STAT_SUCCESS)
                {
                    RK_Context *matchAsEntry = NULL;

                    matchAsEntry = RKManager_FindEntry(rCtxt);
                    if (matchAsEntry != NULL)
                    {
                        matchAsEntry->isMember = ITS_FALSE;

                        matchAsEntry->state = UAL_AS_INACTIVE;

                        UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_DYNAMIC_CTXT;
                        UAL_CB_CTXT_DYNAMIC_REQ_STATE(&cb_ctxt) 
                                                    = matchAsEntry->reqState;
                        UAL_CB_CTXT_RKEY(&cb_ctxt)     = matchAsEntry->rCtxt;
			UAL_CB_CTXT_DYNAMIC_REG_STATUS(&cb_ctxt) = result;
			UAL_CB_CTXT_DYNAMIC_DPC(&cb_ctxt) = 
				                    matchAsEntry->asInfo.dpc;
                        UAL_CB_CTXT_DYNAMIC_SIO(&cb_ctxt) = 
			                    matchAsEntry->asInfo.criteria.sio; 
                        UAL_CB_CTXT_DYNAMIC_TM(&cb_ctxt) = 
			                    matchAsEntry->trafficMode;
                        UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = aspEntry->trId;
                                                                                
                        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                                  (ITS_POINTER) &cb_ctxt);
                    }
                }
		else
                {
		    UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_DYNAMIC_CTXT;
                    UAL_CB_CTXT_DYNAMIC_REQ_STATE(&cb_ctxt) = asCtxt->reqState;
		    UAL_CB_CTXT_RKEY(&cb_ctxt)     = localRkId;
                    UAL_CB_CTXT_DYNAMIC_REG_STATUS(&cb_ctxt) = result;
                    UAL_CB_CTXT_DYNAMIC_DPC(&cb_ctxt) = asCtxt->asInfo.dpc;
                    UAL_CB_CTXT_DYNAMIC_SIO(&cb_ctxt) = 
			                          asCtxt->asInfo.criteria.sio;
                    UAL_CB_CTXT_DYNAMIC_TM(&cb_ctxt) = asCtxt->trafficMode;

		    CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
					      (ITS_POINTER) &cb_ctxt);
                }
            }
        }

        if (aspEntry->remoteInfo.state != UAL_ASP_ACTIVE)
        {
            aspEntry->remoteInfo.state = UAL_ASP_INACTIVE;
        }

       /* send the REGRSP message */
       if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
       {
            ret = UAL_EncodeMsg(sendIE, sendIECount, &rEvent, 
                                &UAL_SUA_REGRSP_Desc);
        }
        else
        {
            ret = UAL_EncodeMsg(sendIE, sendIECount, &rEvent, 
                                &UAL_REGRSP_Desc);
        }

        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Failed to encode REGREQ Msg, "
                             "code %d \n", ret));

            return ret;
        }

        UALEvent->src = UAL_MANAGER_INSTANCE;

        ret = TRANSPORT_PutEvent(aspEntry->trId, &rEvent);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Failed to PutEvent, code %d\n",
                             ret));
        }
        else
        {
            UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_REG_RSP_SENT_ID);
            ret = UAL_SendNotify(aspEntry->trId,
                                 UAL_ST_TYPE_AS_STAT_CHG,
                                 UAL_ST_ID_AS_INACTIVE,
                                 &asCtxt->rCtxt, 1, 0);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Error sending NTFY, AS_INACTIVE\n"));
            }
        }

        break;
    }
    case UAL_MSG_REG_RSP:
    {
        ITS_UINT localRCtxt = 0, result = 0, rCtxt = 0;
        RK_Context *asCtxt = NULL;

        UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_REG_RSP_RECV_ID);

        if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
        {
             ret = UAL_DecodeMsg(recIE, &recIECount, UALEvent, 
                                 &UAL_SUA_REGRSP_Desc);
        }
        else
        {
            ret = UAL_DecodeMsg(recIE, &recIECount, UALEvent, &UAL_REGRSP_Desc);
        }
        CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Error decoding message \n"));

            return ret;
        }

        UAL_Alarm(4017, __FILE__, __LINE__, NULL);

        for (i = 0; i < recIECount; i++)
        {
            /* skip other ies */
            if (recIE[i + 1].param_id  != UAL_PRM_REG_RES  &&
                recIE[i + 1].param_id  != SUA_PRM_REG_RES)
            {
                continue;
            }

            if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
            {
                ret = UAL_GetSuaRegRes(recIE[i + 1].param_data.regResult.regRes,
                                    recIE[i + 1].param_length, &localRCtxt, 
                                    &result, &rCtxt);
            }
            else
            {
                ret = UAL_GetRegRes(recIE[i + 1].param_data.regResult.regRes,
                                    recIE[i + 1].param_length, &localRCtxt, 
                                    &result, &rCtxt);
            }

            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleRKMMsg: Error decoding RegRes\n"));

                continue;
            }

            asCtxt = RKManager_FindEntry(localRCtxt);
            if (asCtxt != NULL)
            {
                if (result == UAL_REG_STAT_SUCCESS && 
                    asCtxt->reqState == UAL_AS_REG)
                {
                    RK_Context *newRKEntry = NULL;
                    RKListNode asAspEntry;
		    ROUTE_MatchInfo *matchInfo = NULL;
 
                    /* Add local Route for the new AS */
                    
                    asCtxt->state = UAL_AS_INACTIVE;

                    if (asCtxt->rCtxt != rCtxt)
                    {
                        newRKEntry = (RK_Context*)calloc(1, sizeof(RK_Context));

                        memcpy(newRKEntry, asCtxt, sizeof(RK_Context));

                        newRKEntry->rCtxt = rCtxt;

                        ret = RKManager_AddEntry(rCtxt, newRKEntry);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleRKMMsg: Error adding AS "
                                             "entry %u \n", asCtxt->rCtxt));
                            continue;
                        }

                        ret = RKManager_RemoveEntry(asCtxt);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleRKMMsg: Error removing AS "
                                             "entry %u \n", asCtxt->rCtxt));
                            continue;
                        }
                    }
                    else 
                    {
                        newRKEntry = asCtxt; 
                    }

		    matchInfo = calloc(1, sizeof(ROUTE_MatchInfo));
		    if (matchInfo != NULL)
                    {
                         memcpy(&matchInfo->basic, &asCtxt->asInfo, 
					      sizeof(ROUTE_BasicInfo));

			 matchInfo->basic.type = ROUTING_KEY_ROUTE;
			 matchInfo->basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
			 matchInfo->rkey = rCtxt;
			 matchInfo->linkSet = newRKEntry->linkSet;

			 ret = ROUTE_AddRoutingKeyInfo(rCtxt, matchInfo);
                         if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("Error adding new Routing Key %u\n",
                                         asCtxt->rCtxt));
			     return ret;
                         }

			 ret = UAL_AddLinkSetAndDestination(newRKEntry);
			 if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("Error adding Linkset and destination"
                                        " for AS %u\n", asCtxt->rCtxt));
			     return ret;
                         }
                    }

                    asAspEntry.rCtxt = rCtxt;
                    asAspEntry.entry = newRKEntry;

                    ret = RKList_AddEntry(aspEntry->asList, &asAspEntry);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("Error adding entry to AS list for AS %u\n",
                                         rCtxt));
                        continue;
                    }

                    UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_DYNAMIC_CTXT;
                    UAL_CB_CTXT_DYNAMIC_REQ_STATE(&cb_ctxt) 
                                                   = newRKEntry->reqState;
                    UAL_CB_CTXT_RKEY(&cb_ctxt)     = newRKEntry->rCtxt;
                    UAL_CB_CTXT_DYNAMIC_REG_STATUS(&cb_ctxt) = result;
                    UAL_CB_CTXT_DYNAMIC_DPC(&cb_ctxt) = newRKEntry->asInfo.dpc;
                    UAL_CB_CTXT_DYNAMIC_SIO(&cb_ctxt) = 
			                       newRKEntry->asInfo.criteria.sio;
                    UAL_CB_CTXT_DYNAMIC_TM(&cb_ctxt) = newRKEntry->trafficMode;

                    CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                              (ITS_POINTER) &cb_ctxt);
                }
                else
                {
                    UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_DYNAMIC_CTXT;
                    UAL_CB_CTXT_DYNAMIC_REQ_STATE(&cb_ctxt) = asCtxt->reqState;
                    UAL_CB_CTXT_RKEY(&cb_ctxt)     = localRCtxt;
                    UAL_CB_CTXT_DYNAMIC_REG_STATUS(&cb_ctxt) = result;
                    UAL_CB_CTXT_DYNAMIC_DPC(&cb_ctxt) = asCtxt->asInfo.dpc;
                    UAL_CB_CTXT_DYNAMIC_SIO(&cb_ctxt) = 
			                        asCtxt->asInfo.criteria.sio;
                    UAL_CB_CTXT_DYNAMIC_TM(&cb_ctxt) = asCtxt->trafficMode;

                    CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                              (ITS_POINTER) &cb_ctxt);

                    ret = RKManager_RemoveEntry(asCtxt);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_HandleRKMMsg: Error removing AS "
                                         "entry %u \n", asCtxt->rCtxt));
                        continue;
                    }                    

                }
            }
            else
            {
                UAL_ERROR(("UAL_HandleRKMMsg: No AS Record found AS "
                                 " %d \n", localRCtxt));
                continue;
            } 
        }

        /* TODO Send a notification to the user via callback */
        break;
    }
    case UAL_MSG_DEREG_REQ:
    {
        ITS_UAL_IE *rCtxtIE = NULL;
        ITS_UINT rkArray[UAL_MAX_RCTXT_LEN];
        RK_Context *asEntry = NULL;
        ASPListNode *aspList = NULL;
        ITS_USHORT trid = UALEvent->src;
        int numRK = 0;
        /*SS7_LinkPtr linkPtr = NULL;*/

        UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_DEREG_REQ_RECV_ID);

        ret = UAL_DecodeMsg(recIE, &recIECount, UALEvent, &UAL_DREGREQ_Desc);
        CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Failed to decode msg, "
                             "code %d \n", ret));
            break;
        }

        UAL_Alarm(4020, __FILE__, __LINE__, NULL);

        rCtxtIE = UAL_FindUALIE(recIE, recIECount, UAL_PRM_ROUT_CTX);
        if (rCtxtIE != NULL)
        {
            ret = UAL_DecodeRoutingContext(rCtxtIE->param_data.rCtxt.rCtxt,
                                           rCtxtIE->param_length, rkArray,
                                           &numRK);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_HandleRKMMsg: Error decoding RCTXT\n"));

                break;
            }

            sendIE[0].param_id = UAL_PRM_MSG_HDR;
            sendIE[0].param_length = sizeof(UAL_MSG_HDR);
            sendIE[0].param_data.msgHeader.msgClass = UAL_CLASS_RKM;
            sendIE[0].param_data.msgHeader.msgType = UAL_MSG_DEREG_RSP;
            sendIE[0].param_data.msgHeader.version = UAL_GL_VERSION;
            sendIE[0].param_data.msgHeader.reserved = 0x00;

            for (i = 0; i < numRK; i++)
            {
                /*ITS_OCTET linkSet, linkCode;*/
                RKListNode* rkNode = NULL;
		int numASP = 0; 

                sendIE[i + 1].param_id = UAL_PRM_DREG_RES;
                sendIE[i + 1].param_length = UAL_MAX_DREG_RES_LEN;
 
                asEntry = RKManager_FindEntry(rkArray[i]);
                if (asEntry == NULL)
                {
                    UAL_ERROR(("UAL_HandleRKMMsg: AS Entry Not Found %d\n",
                                     rkArray[i]));
                    UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                    rkArray[i], UAL_DREG_STAT_INV_RCTXT);

                    sendIECount++;

                    continue;
                }

                /* make sure the ASP is registered for the AS */
                aspList = ASPList_FindEntry(asEntry->aspList, UALEvent->src);
                if (aspList == NULL)
                {
                    UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                    rkArray[i], UAL_DREG_STAT_NOT_REG);
                    sendIECount++;

                    continue;
                }
 
                /* find the link that needs to be removed */
                rkNode = RKList_FindEntry(aspList->entry->asList, asEntry->rCtxt);
                if (rkNode == NULL)
                {
                    UAL_ERROR(("Entry for AS %u not found in AS list for trid %d.\n",
                                     asEntry->rCtxt, aspList->trId));

                    UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                    rkArray[i], UAL_DREG_STAT_NOT_REG);
                    sendIECount++;

                    continue;
                }

                if (aspList->state == UAL_ASP_ACTIVE)
                {
                    /* ASP still ACTIVE for given Routing Key */
                    /* Deregistration can't be allowed for ACTIVE ASPs */

                    UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                    rkArray[i], 
                                    UAL_DREG_STAT_ASP_ACT_FOR_RCTX);
                    sendIECount++;

                    continue;
                }

                ret = ASPList_RemoveEntry(asEntry->aspList, UALEvent->src);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error removing entry. ret = %d\n", ret));
                }

                ret = RKList_RemoveEntry(aspList->entry->asList, 
				         asEntry->rCtxt);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error removing entry. ret = %d\n", ret));
                }

		aspList = ASPList_Iterate(asEntry->aspList);
		if (aspList != NULL)
                {
                    for(; aspList; aspList = ASPList_Iterate(NULL))
                    {
                        if (aspList->trId != 0 && aspList->entry != NULL)
                        {
                            numASP++;
                        }
                    }
                }

                /* we delete RK only if no registered ASP is active for given RK */
		/* only one asp in asplist */
		if (numASP == 0)
                {

                if ((asEntry->state == UAL_AS_INACTIVE) ||
                    (asEntry->state == UAL_AS_DOWN))
                {
                    ret = ROUTE_DeleteRoutingKey(rkArray[i]);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                        rkArray[i], UAL_DREG_STAT_ERR_UNKNOWN);
                        sendIECount++;

                        continue;
                    }
                
                    ret = RKManager_RemoveEntry(asEntry);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                        rkArray[i], UAL_DREG_STAT_NOT_REG);
                        sendIECount++;

                        continue;
                    }
                }
                }

                UAL_SetDeRegRes(sendIE[i + 1].param_data.deregRes.derRes,
                                rkArray[i], UAL_DREG_STAT_SUCCESS);
                sendIECount++;
            }
        }
        else
        {
            /* we should not go here Decode should have failed !!! */
            UAL_ERROR(("UAL_HandleRKMMsg: Missing RCtxt Parameter,\n"));

            return ITS_EMISSMAND;
        }

        /* encode the DREGRSP message */
        ret = UAL_EncodeMsg(sendIE, sendIECount, &rEvent, &UAL_DREGRSP_Desc);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Failed to encode DREGRSP Msg, "
                             "code %d \n", ret));

            return ret;
        }

        UALEvent->src = UAL_MANAGER_INSTANCE;

        ret = TRANSPORT_PutEvent(trid, &rEvent);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Failed to PutEvent, code %d\n",
                             ret));
        }
        else
        {
            UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_DEREG_RSP_SENT_ID);
        }

        break;
    }
    case UAL_MSG_DEREG_RSP:
    {
        RK_Context *asEntry = NULL;
        ITS_UINT rCtxt = 0, status = 0;

        UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_DEREG_RSP_RECV_ID);

        ret = UAL_DecodeMsg(recIE, &recIECount, UALEvent, &UAL_DREGRSP_Desc);
        CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleRKMMsg: Failed to decode msg, "
                             "code %d \n", ret));
            break;
        }
        UAL_Alarm(4019, __FILE__, __LINE__, NULL); 

        for (i = 0; i < recIECount; i++)
        {
            if (recIE[i].param_id != UAL_PRM_DREG_RES)
            {
                continue;
            }
 
            ret = UAL_GetDeregRes(recIE[i].param_data.deregRes.derRes, &rCtxt, &status);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Error Decoding Dereg Result\n"));

                continue; 
            }
         
            asEntry = RKManager_FindEntry(rCtxt);
            if (asEntry == NULL)
            {
                UAL_ERROR(("Error Finding AS Entry %u\n", rCtxt));
 
                continue;
            }

            if (status == UAL_DREG_STAT_SUCCESS)
            {
                if (asEntry->reqState == UAL_AS_DREG)
                {
                    ret = ROUTE_DeleteRoutingKey(rCtxt);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("Error Removing Routing Key %u\n", rCtxt));
                                                                               
                        continue;
                    }

                    ret = RKManager_RemoveEntry(asEntry);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("Error Removing AS Entry %u\n", rCtxt));
 
                        continue;
                    }
                }
                else
                {
                    continue;
                    /* TODO just log error */
                }

                /* aslo remove from the list of AS for that association */
                ret = RKList_RemoveEntry(aspEntry->asList, rCtxt);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error removing AS entry from AS list.\n"));
              
                    continue;
                }  

                /* Finally we need to remove the local route that was added */

            }    
            else
            {
                UAL_WARNING(("Deregistration for Context %u failed, reason: %d\n",
                                   rCtxt, status)); 
            }

            UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_DYNAMIC_CTXT;
            UAL_CB_CTXT_DYNAMIC_REQ_STATE(&cb_ctxt) = asEntry->reqState;
            UAL_CB_CTXT_RKEY(&cb_ctxt)     = asEntry->rCtxt;
            UAL_CB_CTXT_DYNAMIC_REG_STATUS(&cb_ctxt) = status;
            UAL_CB_CTXT_DYNAMIC_DPC(&cb_ctxt) = asEntry->asInfo.dpc;
            UAL_CB_CTXT_DYNAMIC_SIO(&cb_ctxt) = asEntry->asInfo.criteria.sio;
            UAL_CB_CTXT_DYNAMIC_TM(&cb_ctxt) = asEntry->trafficMode;

            CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                      (ITS_POINTER) &cb_ctxt);

        }

        break;
    }
    default:

        /* ignore the message */
        UAL_ERROR(("UAL_HandleRKMMsg: Received invalid Msg Type: " "%02x.\n", msgType));
        UAL_Alarm(4026, __FILE__, __LINE__, "TransportId %x", aspEntry->trId);

        /*Build and send Diagnostic Info param*/
        diagnInfo.param_id = UAL_PRM_DIAGNOSTIC;
        if (UALEvent->len < UAL_MAX_DIAG_INFO_LEN)
        {
          diagnInfo.param_length = UALEvent->len;
          memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                  UALEvent->data, UALEvent->len);
        }
        else
        {
          diagnInfo.param_length = UAL_MAX_DIAG_INFO_LEN;
          memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                UALEvent->data, UAL_MAX_DIAG_INFO_LEN);
        }
        ret = UAL_SendERR(aspEntry->trId, UAL_ERR_UNSUP_MSG_TYPE,
               &diagnInfo, 1);
        break;
    }

    return ret;
}


int
UAL_CheckNewRoutingKeyValid(RK_Context *asCtxt, ITS_OCTET *resultData)
{
    UAL_DEBUG(("UAL_CheckNewRoutingKeyValid Entry"));
    ITS_UINT rCtxt = 0, localKey = 0, localRkid = 0;
    int ret = ITS_SUCCESS; 
    ROUTE_MatchInfo localRInfo;
    RK_Context *asEntry = NULL;

    ITS_C_ASSERT(asCtxt != NULL);

    /* we do not support broadcast for now */ 
    if (asCtxt->trafficMode == UAL_BROADCAST_MODE)
    {
        UAL_SetRegRes(resultData, asCtxt->rCtxt, 
                      UAL_REG_STAT_ERR_INVALID_THM, 0);
        return !(ITS_SUCCESS);
    }

    asCtxt->asInfo.type = ROUTING_KEY_ROUTE;

    memcpy(&localRInfo.basic, &asCtxt->asInfo, sizeof(ROUTE_BasicInfo));

    localRInfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
    localRInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

    /* we do that for now but we better have our own function later */
    ret = ROUTE_FindRoutingKeyByInfo(&localKey, &localRInfo);

    if (ret != ITS_SUCCESS)
    {
        ret = UAL_CheckRoutingInfoValid(&localKey, asCtxt);
        if (ret == ITS_SUCCESS)
        {
            localRkid = asCtxt->rCtxt; /* store received local-RK-Identifier
                                          before we store the allocated
                                          routing context value */ 

            /* Key already exists, reply with success */
            UAL_SetRegRes(resultData, localRkid, 
                          UAL_REG_STAT_SUCCESS, localKey);

            return (ITS_EDUPLENTRY);
        }

        ROUTE_MatchInfo *matchInfo = NULL;

        ret = UAL_AllocateLocalRKId(&rCtxt);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_CheckNewRoutingKeyValid: error "
                             "allocating local RK indentifier, "
                             "code: %d \n", ret));

            UAL_SetRegRes(resultData, asCtxt->rCtxt, 
                          UAL_REG_STAT_ERR_UNSUFF_RES, 0);
            
            return ret;
            
        }
    
        ret = RKManager_AddEntry(rCtxt, asCtxt);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_CheckNewRoutingKeyValid: Could not "
                             "add RK entry to AS_Table, code %d \n",
                             ret));

            UAL_SetRegRes(resultData, asCtxt->rCtxt, 
                          UAL_REG_STAT_ERR_UNSUFF_RES, 0);
            return ret;
        }

        matchInfo = calloc(1, sizeof(ROUTE_MatchInfo));
        if (matchInfo != NULL)
        {
            memcpy(&matchInfo->basic, &asCtxt->asInfo, sizeof(ROUTE_BasicInfo));

            matchInfo->basic.type = ROUTING_KEY_ROUTE;
            matchInfo->basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
            matchInfo->rkey = rCtxt;
            matchInfo->linkSet = asCtxt->linkSet;

            ret = ROUTE_AddRoutingKeyInfo(rCtxt, matchInfo);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Error adding new Routing Key %u\n", 
                                 asCtxt->rCtxt));
            
                return ret; 
            }
        }
        else
        {
            UAL_ERROR(("The World Is On Fire... calloc Failed !!!\n"));

            UAL_SetRegRes(resultData, asCtxt->rCtxt, 
                          UAL_REG_STAT_ERR_UNSUFF_RES, 0);

            return !(ITS_SUCCESS);
        }

        ret = UAL_AddLinkSetAndDestination(asCtxt);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Error adding Linkset and Destination for AS %u\n",
                             asCtxt->rCtxt));

            UAL_SetRegRes(resultData, asCtxt->rCtxt, 
                          UAL_REG_STAT_ERR_UNSUFF_RES, 0);

            return ret;

        }

        asCtxt->state = UAL_AS_DOWN;
        localRkid = asCtxt->rCtxt; /* store received local-RK-Identifier
                                      before we store the allocated
                                      routing context value */ 
        asCtxt->rCtxt = rCtxt;
        localKey = rCtxt;
    }
    else
    {
        localRkid = asCtxt->rCtxt; /* store received local-RK-Identifier
                                      before we store the allocated
                                      routing context value */

        asEntry = RKManager_FindEntry(localKey);

        if(asEntry->trafficMode != asCtxt->trafficMode)
        {
            return (!ITS_SUCCESS);
        }
        else
        {
            ret = ITS_EDUPLENTRY;
        }
    }
    
    /* Key already exists, reply with success */ 
    UAL_SetRegRes(resultData, localRkid, 
                  UAL_REG_STAT_SUCCESS, localKey);
  
    UAL_DEBUG(("UAL_CheckNewRoutingKeyValid Exit"));
    return ret;
}


void
UAL_CheckNewSuaRoutingKeyValid(RK_Context *asCtxt, ITS_OCTET *resultData)
{
    ITS_USHORT routeExist = ITS_NO_SRC;
    ITS_UINT rCtxt = 0;
    int ret = ITS_SUCCESS; 
    ROUTE_MatchInfo localRInfo;
 
    ITS_C_ASSERT(asCtxt != NULL);

    /* we do not support broadcast for now */
    if (asCtxt->trafficMode == UAL_BROADCAST_MODE)
    {
        UAL_SetSuaRegRes(resultData, asCtxt->rCtxt, 
                         UAL_REG_STAT_ERR_INVALID_THM, 0);
        return;
    }

    asCtxt->asInfo.type = REMOTE_ROUTE;

    memcpy(&localRInfo.basic, &asCtxt->asInfo, sizeof(ROUTE_BasicInfo));

    routeExist = ROUTE_RouteContextInfoExists(&localRInfo);
    if (routeExist == ITS_NO_SRC)
    {
        ROUTE_MatchInfo *matchInfo = NULL;

        ret = UAL_AllocateLocalRKId(&rCtxt);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_CheckNewRoutingKeyValid: error "
                             "allocating local RK indentifier, "
                             "code: %d \n", ret));

            UAL_SetSuaRegRes(resultData, asCtxt->rCtxt, 
                             UAL_REG_STAT_ERR_UNSUFF_RES, 0);
            
            return;
            
        }

        UAL_SetSuaRegRes(resultData,
                         asCtxt->rCtxt, UAL_REG_STAT_SUCCESS,
                         rCtxt);
    
        ret = RKManager_AddEntry(rCtxt, asCtxt);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_CheckNewRoutingKeyValid: Could not "
                             "add RK entry to AS_Table, code %d \n",
                             ret));

            UAL_SetSuaRegRes(resultData, asCtxt->rCtxt, 
                             UAL_REG_STAT_ERR_UNSUFF_RES, 0);
            return;
        }

        matchInfo = calloc(1, sizeof(ROUTE_MatchInfo));
 
        if (matchInfo != NULL)
        {
            memcpy(&matchInfo->basic, &asCtxt->asInfo, sizeof(ROUTE_BasicInfo));

            matchInfo->basic.type = ROUTING_KEY_ROUTE;
            matchInfo->rkey = rCtxt;
            matchInfo->linkSet = asCtxt->linkSet;

            ret = ROUTE_AddRoutingKeyInfo(rCtxt, matchInfo);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Error adding new Routing Key %u\n", 
                                 asCtxt->rCtxt));
                
                return; 
            }
        }
        else
        {
            UAL_ERROR(("The World Is On Fire... calloc Failed !!!\n"));

            return;
        }

        ret = UAL_AddLinkSetAndDestination(asCtxt);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Error adding Linkset and Destination for AS %u\n",
                             asCtxt->rCtxt));

            UAL_SetRegRes(resultData, asCtxt->rCtxt, 
                          UAL_REG_STAT_ERR_UNSUFF_RES, 0);

            return;

        }

        asCtxt->state = UAL_AS_INACTIVE;
        asCtxt->rCtxt = rCtxt;
    }
    else
    {
        UAL_SetSuaRegRes(resultData, asCtxt->rCtxt, 
                         UAL_REG_STAT_ERR_NO_SUP_UNI_RK, 0);
    }

    return;
}

static void
UAL_SetDeRegRes(ITS_OCTET *resultData, ITS_UINT rCtxt, ITS_UINT status)
{
    ITS_USHORT tag, len = 8;

    ITS_C_ASSERT(resultData != NULL);

    len = SOCK_HToNS(len);;
    status =  SOCK_HToNL(status);
    rCtxt = SOCK_HToNL(rCtxt);

    tag = SOCK_HToNS(UAL_PRM_ROUT_CTX);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &rCtxt, sizeof(ITS_UINT));
    resultData += sizeof(rCtxt);

    tag = SOCK_HToNS(UAL_PRM_DREG_STATUS);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &status, sizeof(ITS_UINT));
    resultData += sizeof(status);

    return;
}

static int 
UAL_GetDeregRes(ITS_OCTET *resultData, ITS_UINT *rCtxt, ITS_UINT *status)
{
    ITS_USHORT tag;
    int ret = ITS_SUCCESS, i = 0;

    for (i = 0; i < 2; i++) 
    {
        memcpy(&tag, resultData, sizeof(ITS_USHORT));

        tag = SOCK_NToHS(tag);

        resultData += (2 * sizeof(ITS_USHORT));

        switch(tag)
        {
        case UAL_PRM_ROUT_CTX:

            memcpy(rCtxt, resultData, sizeof(ITS_UINT));

            *rCtxt = SOCK_NToHL(*rCtxt);

            break;

        case UAL_PRM_DREG_STATUS:

            memcpy(status, resultData, sizeof(ITS_UINT));

            *status = SOCK_NToHL(*status);

            break;

        default:

            UAL_ERROR(("Unexpected parameter in DEREG_RESULT\n"));
            return -1;  
        }

        resultData +=  sizeof(ITS_UINT);
    }

    return ret;
}


void
UAL_SetRegRes(ITS_OCTET *resultData, ITS_UINT localRCtxt, ITS_UINT result,
              ITS_UINT rCtxt)
{
    ITS_USHORT tag, len = 8;

    ITS_C_ASSERT(resultData != NULL);

    len = SOCK_HToNS(len);
    localRCtxt = SOCK_HToNL(localRCtxt);
    result =  SOCK_HToNL(result);
    rCtxt = SOCK_HToNL(rCtxt);

    tag = SOCK_HToNS(UAL_PRM_LRK_ID);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &localRCtxt, sizeof(ITS_UINT));
    resultData += sizeof(localRCtxt);

    tag = SOCK_HToNS(UAL_PRM_REG_STATUS);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &result, sizeof(ITS_UINT));
    resultData += sizeof(result);

    tag = SOCK_HToNS(UAL_PRM_ROUT_CTX);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &rCtxt, sizeof(ITS_UINT));

    return;
}



void
UAL_SetSuaRegRes(ITS_OCTET *resultData, ITS_UINT localRCtxt, ITS_UINT result,
                 ITS_UINT rCtxt)
{
    ITS_USHORT tag, len = 8;

    ITS_C_ASSERT(resultData != NULL);

    len = SOCK_HToNS(len);

    localRCtxt = SOCK_HToNL(localRCtxt);
    result =  SOCK_HToNL(result);
    rCtxt = SOCK_HToNL(rCtxt);

    tag = SOCK_HToNS(SUA_PRM_LOCAL_RKID);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &localRCtxt, sizeof(ITS_UINT));
    resultData += sizeof(localRCtxt);

    tag = SOCK_HToNS(SUA_PRM_REG_STATUS);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &result, sizeof(ITS_UINT));
    resultData += sizeof(result);

    tag = SOCK_HToNS(UAL_PRM_ROUT_CTX);
    memcpy(resultData, &tag, sizeof(tag));
    resultData += sizeof(tag);
    memcpy(resultData, &len, sizeof(len));
    resultData += sizeof(len);
    memcpy(resultData, &rCtxt, sizeof(ITS_UINT));

    return;
}


int
UAL_GetRegRes(ITS_OCTET *resultData, int size, ITS_UINT *localRCtxt, 
              ITS_UINT *result, ITS_UINT *rCtxt)
{
    ITS_USHORT tag;
    int ret = ITS_SUCCESS, i = 0;

    ITS_C_ASSERT((resultData != NULL) && (localRCtxt != NULL) &&
                 (result != NULL) && (rCtxt != NULL));

    if (size != UAL_MAX_REG_RES_LEN)
    {
        return ITS_EINVLEN;
    }

    for (i = 0; i < 3; i++) 
    {
        memcpy(&tag, resultData, sizeof(ITS_USHORT));

        tag = SOCK_NToHS(tag);

        resultData += (2 * sizeof(ITS_USHORT));

        switch(tag)
        {
        case UAL_PRM_LRK_ID:

            memcpy(localRCtxt, resultData, sizeof(ITS_UINT));

            *localRCtxt = SOCK_NToHL(*localRCtxt);

            break;

        case UAL_PRM_REG_STATUS:

            memcpy(result, resultData, sizeof(ITS_UINT));

            *result = SOCK_NToHL(*result);

            break;

        case UAL_PRM_ROUT_CTX:

            memcpy(rCtxt, resultData, sizeof(ITS_UINT));

            *rCtxt = SOCK_NToHL(*rCtxt);

            break;

        default:

            return ITS_EMISSMAND;

            break;

        }

        resultData +=  sizeof(ITS_UINT);
    }
    return ret;

}


int
UAL_GetSuaRegRes(ITS_OCTET *resultData, int size, ITS_UINT *localRCtxt, 
              ITS_UINT *result, ITS_UINT *rCtxt)
{
    ITS_USHORT tag;
    int ret = ITS_SUCCESS, i = 0;

    ITS_C_ASSERT((resultData != NULL) && (localRCtxt != NULL) &&
                 (result != NULL) && (rCtxt != NULL));

    if (size != SUA_MAX_REG_RES_LEN)
    {
        return ITS_EINVLEN;
    }

     /*memcpy(localRCtxt, resultData, sizeof(ITS_UINT));

     *localRCtxt = SOCK_NToHL(*localRCtxt);

     resultData +=  sizeof(ITS_UINT);*/

    for (i = 0; i < 3; i++) 
    {
        memcpy(&tag, resultData, sizeof(ITS_USHORT));

        tag = SOCK_NToHS(tag);

        resultData += (2 * sizeof(ITS_USHORT));

        switch(tag)
        {
        case SUA_PRM_LOCAL_RKID :

             memcpy(localRCtxt, resultData, sizeof(ITS_UINT));

            *localRCtxt = SOCK_NToHL(*localRCtxt);

        break;

        case SUA_PRM_REG_STATUS:

            memcpy(result, resultData, sizeof(ITS_UINT));

            *result = SOCK_NToHL(*rCtxt);
            
            break;

        case UAL_PRM_ROUT_CTX:

            memcpy(rCtxt, resultData, sizeof(ITS_UINT));

            *rCtxt = SOCK_NToHL(*rCtxt);

            break;

        default:

            return ITS_EMISSMAND;

            break;

        }

        resultData +=  sizeof(ITS_UINT);
    }
    return ret;

}
typedef struct UAL_FindRoutingKeyInfo_hash_iterative_proc_input
{
    ITS_UINT*     rkey;
    RK_Context*   asCtxt;
} UAL_FindRoutingKeyInfo_hash_iterative_proc_input;
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
UAL_FindRoutingKeyInfo_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
    ITS_UINT *rkey = ((UAL_FindRoutingKeyInfo_hash_iterative_proc_input *)in)->rkey;
    RK_Context* asCtxt = ((UAL_FindRoutingKeyInfo_hash_iterative_proc_input *)in)->asCtxt;
    RK_Context *tempEntry = (RK_Context *)data;

    if ((asCtxt->asInfo.dpc == tempEntry->asInfo.dpc &&
	 asCtxt->asInfo.criteria.sio == tempEntry->asInfo.criteria.sio))
	{
		*rkey = tempEntry->rCtxt;
		*((ITS_BOOLEAN *)out) = ITS_TRUE;
		// return failure to make Iterate function break from for loop
		return !ITS_SUCCESS;
	}
	else
	{
		return ITS_SUCCESS;
	}
    
}
int
UAL_FindRoutingKeyInfo(ITS_UINT *rkey, RK_Context *asCtxt)
{
    int dummy_ret, ret = !ITS_SUCCESS;
    ITS_BOOLEAN found = ITS_FALSE;

    UAL_FindRoutingKeyInfo_hash_iterative_proc_input in;	
	in.rkey   = rkey;
	in.asCtxt = asCtxt;
    dummy_ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, &in,
		       &found, UAL_FindRoutingKeyInfo_hash_iterative_proc);
	if (found == ITS_TRUE)
	{
		ret = ITS_SUCCESS;
	}
	
    return ret;
}
