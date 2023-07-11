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
 *  ID: $Id: ual_layer_mgnt.c,v 9.10.8.4.40.1 2014/09/16 09:34:54 jsarvesh Exp $
 *
 *  LOG: $Log: ual_layer_mgnt.c,v $
 *  LOG: Revision 9.10.8.4.40.1  2014/09/16 09:34:54  jsarvesh
 *  LOG: Changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.10.8.4.36.1  2014/09/15 07:20:42  jsarvesh
 *  LOG: Changes done for removing Warnings
 *  LOG:
 *  LOG: Revision 9.10.8.4  2010/07/02 11:44:36  chandrashekharbs
 *  LOG: Fix for Issue id 3065
 *  LOG:
 *  LOG: Revision 9.10.8.3  2010/06/25 12:23:12  chandrashekharbs
 *  LOG: Fix for Issue id  2936
 *  LOG:
 *  LOG: Revision 9.10.8.2  2010/06/21 17:13:59  haltaf
 *  LOG: Fix for #3093
 *  LOG:
 *  LOG: Revision 9.10.8.1  2010/03/10 04:45:19  ssingh
 *  LOG: Issue Id: 2349 fix propagated from WNLP project - Redundant Mode
 *  LOG:
 *  LOG: Revision 9.10  2008/06/29 15:16:56  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.9  2008/06/20 10:42:13  mshanmugam
 *  LOG: Accelero CGI Phase I: D0170, D0190
 *  LOG:
 *  LOG: Revision 9.8  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.7.2.9  2008/02/26 04:52:17  clin
 *  LOG: Add modification to support C++ API for ASP
 *  LOG:
 *  LOG: Revision 9.7.2.8  2007/07/10 06:20:04  pspl
 *  LOG: (PSPL, abhijeet) misc change for the error message
 *  LOG:
 *  LOG: Revision 9.7.2.7  2007/07/10 06:05:17  pspl
 *  LOG: (PSPL, Abhijeet) added asp ID to the message that declares error in sending ASPTM in DOWN state
 *  LOG:
 *  LOG: Revision 9.7.2.6  2007/07/05 06:08:07  pspl
 *  LOG: check added for state to ASP_DOWN while sending ASP ACTIVE/INACTIVE Msg (Rajnikant/PSPL)
 *  LOG:
 *  LOG: Revision 9.7.2.5  2007/06/12 08:49:49  pspl
 *  LOG: (PSPL, abhijeet) reverted back the state change to happen except for ASP_UP broadCast
 *  LOG:
 *  LOG: Revision 9.7.2.4  2007/06/05 05:59:23  pspl
 *  LOG: (PSPL, abhijeet) changing of ASP state while sending the ASP_SM / ASP_TM
 *  LOG:                  messages removed. This is being done while processing
 *  LOG: 		 corresponding ACK message.
 *  LOG:
 *  LOG: Revision 9.7.2.3  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.7.2.2  2007/04/26 06:57:05  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - added code to check DecodeMsg() return values and take appropriate action
 *  LOG:
 *  LOG: Revision 9.7.2.1  2007/04/05 14:48:23  pspl
 *  LOG: ackTimer[indexing] changed from trafficMode value to be msgType value being used
 *  LOG:
 *  LOG: Revision 9.7  2007/01/17 09:21:32  yranade
 *  LOG: Warning removals.
 *  LOG:
 *  LOG: Revision 9.6  2005/12/08 03:39:18  clin
 *  LOG: fix bug #2482
 *  LOG:
 *  LOG: Revision 9.5  2005/11/09 20:01:48  cbashyam
 *  LOG: Bug fixes for Bug ID : 2491
 *  LOG: Need to set "remoteInfo.state" for IPSP
 *  LOG:
 *  LOG: Revision 9.4  2005/07/04 03:12:44  randresol
 *  LOG: Make code compatible with ANSI-C
 *  LOG:
 *  LOG: Revision 9.3  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.2  2005/04/07 11:01:26  adutta
 *  LOG: Fix for Bug#1668
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:49  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.3  2005/03/21 13:52:19  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1.4.2.2.1.10.2  2004/12/20 13:39:51  dsatish
 *  LOG: Fix for Bug #1328
 *  LOG:
 *  LOG: Revision 7.1.4.2.2.1.10.1  2004/12/15 13:11:16  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.1.4.2.2.1  2004/05/03 12:52:24  ssingh
 *  LOG: Bug#806/808. changes done to detect (in)valid response to message sent.
 *  LOG:
 *  LOG: Revision 7.1.4.2  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.1.4.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.1.2.1  2002/12/26 23:32:27  lbana
 *  LOG: buge fixes in ual in IPSP mode testing
 *  LOG:
 *  LOG: Revision 6.6  2002/07/22 12:34:25  ngoel
 *  LOG: change state to inactive after sending asp inactive
 *  LOG:
 *  LOG: Revision 6.5  2002/07/12 17:26:41  ngoel
 *  LOG: change by lbana
 *  LOG:
 *  LOG: Revision 6.4  2002/07/10 21:33:43  lbana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 6.3  2002/05/15 16:30:23  lbana
 *  LOG: Compile this file in.
 *  LOG:
 *  LOG: Revision 6.2  2002/05/15 16:26:50  lbana
 *  LOG: forgot to commit this file
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

#include <its_ual.h>
#include <ual_intern.h>

static int UAL_LMHandleTMMsg(ITS_EVENT *UALEvent, ITS_OCTET msgType);

static int UAL_LMHandleSMMsg(ITS_EVENT *UALEvent, ITS_OCTET msgType);

static int UAL_LMHandleRKMMsg(ITS_EVENT *UALEvent, ITS_OCTET msgType);

static int UAL_NotifyUserASRegFailure(ITS_UAL_IE *resultIE, ITS_UINT result); 

/*
 * Handle Layer Management Messages
 */

int
UAL_GetASPState(ITS_USHORT trid, UAL_ASP_STATE *state)
{
    int ret = ITS_SUCCESS;
    ASP_Entry *asp = NULL;

    ret = ASPTable_FindEntry(trid, &asp);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Finding ASP Entry, TRID %d.\n", trid));
        return ITS_ENOTFOUND;
    }

    if (asp != NULL)
    {
        *state = asp->state;
    }
    else
    {
        UAL_ERROR(("Error Finding ASP Entry, TRID %d.\n", trid));
        ret = ITS_ENOTFOUND;
    }

    return ret;
}

ITS_BOOLEAN
UAL_IsRCtxtValid(ITS_UINT rctxt)
{
    ITS_BOOLEAN ret = ITS_FALSE;
    RK_Context*  rk_ctxt = NULL;

    rk_ctxt = RKManager_FindEntry(rctxt);

    if (rk_ctxt != NULL)
    {
        if (UAL_IS_APP_ASP(UAL_GL_ITW_MODE) ||
             (UAL_IS_APP_IPSP(UAL_GL_ITW_MODE) && !(rk_ctxt->isMember)))
        {
            ret = ITS_TRUE; 
        }
    }
    return ret;
}

ITS_OCTET
UAL_GetIntWorkingMode()
{
    return UAL_GL_ITW_MODE;
}


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
UAL_HandleLayerMgntMsg(ITS_EVENT *UALEvent)
{
    int ret = ITS_SUCCESS;
    UAL_MSG_HDR msgHdr;

    /* 1) first get the common message header */
    memcpy(&msgHdr, UALEvent->data, sizeof(UAL_MSG_HDR));

    switch(msgHdr.msgClass)
    {
    case UAL_CLASS_ASPSM:

        UAL_DEBUG(("UAL_HandleLayerMgntMsg: *LM* Recieved UAL State "
                         "Maintenace Msg tpye %02x.\n", 
                         msgHdr.msgType));

        ret = UAL_LMHandleSMMsg(UALEvent, msgHdr.msgType);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleLayerMgntMsg: *LM* Error handling "
                             "ASPSM message\n"));
        }

        break;

    case UAL_CLASS_ASPTM:

        UAL_DEBUG(("UAL_HandleLayerMgntMsg: *LM* Recieved UAL Traffic "
                         "Maintenace Msg tpye %02x.\n", 
                         msgHdr.msgType));

        ret = UAL_LMHandleTMMsg(UALEvent, msgHdr.msgType);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleLayerMgntMsg: *LM* Error handling "
                             "ASPTM message\n"));
        }

        break;

    case UAL_CLASS_RKM:
 
        UAL_DEBUG(("UAL_HandleLayerMgntMsg: *LM* Recieved UAL RKM "
                         " Msg type %02x.\n", msgHdr.msgType));

        /* pass to the RK manager */
        ret = UAL_LMHandleRKMMsg(UALEvent, msgHdr.msgType);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_HandleLayerMgntMsg: *LM* Error handling "
                             "RKM message\n"));
        }

        break;


    default:

        UAL_ERROR(("UAL_HandleLayerMgntMsg: Recieved nknown message:"
                         " Msg tpye %02x.\n", msgHdr.msgType));

        ret = UAL_SendERR(UALEvent->src, UAL_ERR_UNEPECTED_MSG, NULL, 0);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Error Sending ERR Msg.\n"));
        }

        break;
    }

    return ret;
}



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
static int
UAL_LMHandleTMMsg(ITS_EVENT *UALEvent, ITS_OCTET msgType)
{
    int ret = ITS_SUCCESS, ieCount = 0, i = 0, size = 0;
    ITS_UINT rkArray[32], outRKArray[32], outSize = 0;
    ITS_UAL_IE ies[16], *ieTmp = NULL;
    UAL_MSG_DESC *msgDesc = NULL;
    RK_Context *rCtxtEntry = NULL;
    ITS_UINT trafficMode = 1;

    if (msgType == UAL_MSG_ASPIA)
    {
        msgDesc = &UAL_ASPIA_Desc;
    }
    else if (msgType == UAL_MSG_ASPAC)
    {
        msgDesc = &UAL_ASPAC_Desc;
    }
    else
    {
        UAL_ERROR(("Unknown Message Type %d\n", msgType));
    }

    ret = UAL_DecodeMsg(ies, &ieCount, UALEvent, msgDesc);
    CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_DecodeMsg failed error code %d.\n", ret));

        return ret;
    }

    /* get the TrafficMode */
    if (msgType != UAL_MSG_ASPIA)
    {
        ieTmp  = UAL_FindUALIE(ies, ieCount, UAL_PRM_TRAFFIC_MODE);
/* optional parameter
        if (ieTmp == NULL)
        {
            UAL_ERROR(("Missing TrafficMode Parameter\n"));

            return ITS_EMISSMAND;
        }
*/
        if (ieTmp != NULL)
        {
            trafficMode = ieTmp->param_data.trafMode.tm;

            if (!UAL_IS_VALID_TM(trafficMode))
            {
                UAL_ERROR(("Invalid Traffic Mode: %d", trafficMode));

                return ITS_EINVALIDARGS;
            }
        }
    }

    /* Get the Routing Ctxt */
    ieTmp = UAL_FindUALIE(ies, ieCount, UAL_PRM_ROUT_CTX);
/* optional parameter
    if (ieTmp == NULL) 
    {
        UAL_ERROR(("Missing Rctxt Parameter\n"));

        return ITS_EMISSMAND;
    }
*/
    if (ieTmp != NULL)
    {
        ret = UAL_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                       ieTmp->param_length,
                                       rkArray, &size);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Error decoding RTCTX error code %d.\n", ret));
            return ret;
        }

        /* delete from the RK list */
        for (i = 0; i < size; i++)
        {
            /* check if the RK is in the RK_Table */
            rCtxtEntry = RKManager_FindEntry(rkArray[i]);
            if ((rCtxtEntry != NULL))
            {
                if (rCtxtEntry->state == UAL_AS_DOWN)
                {
                    ITS_Class redClass;
                    UAL_WARNING(("Invalid message sent in AS DOWN state.\n "));

                    /* Check if any ASP is in INACTIVE state to send ACT msg
                     * Fix for whizible issue Id: 2349 to allow standby node 
                     * to send ASPACT irrespective of AS State (local) 
                     */
                    redClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME); 
                    if (redClass != NULL)
                    {
                        UAL_DEBUG(("Allow ACT msg ASDOWN state.\n"));
                        outRKArray[outSize] = rkArray[i];
                        outSize++;
                    }
                }
                else
                {
                    outRKArray[outSize] = rkArray[i];
                    outSize++;
                }
            }
            else
            {
                UAL_ERROR(("Invalid RCTXT %d\n", rkArray[i]));

                continue;
            }
        }

        if (!outSize)
        {
            return ret;
        }

        ret = UAL_EncodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                       &ieTmp->param_length, outRKArray,
                                       outSize);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Error Encoding RCTXT \n"));

            return ret;
        }
    } 

    ret = UAL_EncodeMsg(ies, ieCount, UALEvent, msgDesc); 
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Encoding UAL Msg.\n"));

        return ret;   
    }

    if (UALEvent->src != ITS_FIRST_USER_SRC)
    {
        if (msgType == UAL_MSG_ASPIA)
        {
             trafficMode = rCtxtEntry->trafficMode;
             ret = UAL_LMSendASPSMandTMMsg(UALEvent, UAL_ASP_INACTIVE, 
                                           trafficMode);
        }
        else
        {
             ret = UAL_LMSendASPSMandTMMsg(UALEvent, UAL_ASP_ACTIVE, 
                                           trafficMode);
        }
    }
    else
    {
        if (msgType == UAL_MSG_ASPIA)
        {
             trafficMode = rCtxtEntry->trafficMode;
             ret = UAL_BroadCastMsg(UALEvent, UAL_ASP_INACTIVE, trafficMode);
        }
        else
        {
             ret = UAL_BroadCastMsg(UALEvent, UAL_ASP_ACTIVE, trafficMode);
        }
    }

    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Fail to send msg.\n"));
    }

    return ret;
}



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
static int
UAL_LMHandleSMMsg(ITS_EVENT *UALEvent, ITS_OCTET msgType)
{
    int ret = ITS_SUCCESS;

    if (UALEvent->src != ITS_FIRST_USER_SRC)
    {
        if(msgType == UAL_MSG_ASPUP)
        {
            ret = UAL_LMSendASPSMandTMMsg(UALEvent, UAL_ASP_UP, 0);
        }
        else if(msgType == UAL_MSG_ASPDN)
        {
            ret = UAL_LMSendASPSMandTMMsg(UALEvent, UAL_ASP_DOWN, 0);
        }
    }
    else
    {
        if(msgType == UAL_MSG_ASPUP)
        {
            ret = UAL_BroadCastMsg(UALEvent, UAL_ASP_UP, 0);
        }
        else if(msgType == UAL_MSG_ASPDN)
        {
            ret = UAL_BroadCastMsg(UALEvent, UAL_ASP_DOWN, 0);
        }
    }

    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Fail to send msg.\n"));
    }

    return ret;
}



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
static int
UAL_LMHandleRKMMsg(ITS_EVENT *UALEvent, ITS_OCTET msgType)
{
    int ret = ITS_SUCCESS, ieCount = 0, i = 0, sendIECount = 0;
    RK_Context *asCtxt = NULL;
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_UAL_IE sendIEs[ITS_MAX_UAL_IES];
    ROUTE_MatchInfo matchInfo;
    ITS_UINT rCtxt = 0;

    switch (msgType)
    {
    case UAL_MSG_REG_REQ:
    {
        if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
        {
            ret = UAL_DecodeMsg(ies, &ieCount, UALEvent, &UAL_SUA_REGREQ_Desc);
        }
        else
        {
            ret = UAL_DecodeMsg(ies, &ieCount, UALEvent, &UAL_REGREQ_Desc);
        }
        CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to decode msg, "
                             "code %d \n", ret));
            return ret;
        }

        /* copy the common msg header */
        sendIEs[sendIECount] = ies[sendIECount];

        sendIECount++;

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i + 1].param_id  == SUA_PRM_ASP_CAPAB)
            {
                sendIEs[sendIECount] = ies[i + 1];

                sendIECount++;
         
                continue;
            }

            /* skip other ies */
            if ((ies[i + 1].param_id  != UAL_PRM_ROUTING_KEY) &&
                (ies[i + 1].param_id  != SUA_PRM_RKEY ))
            {
                continue;
            }

            asCtxt = (RK_Context*) calloc(1, sizeof(RK_Context));
            if (asCtxt != NULL)
            {
                if (ies[i + 1].param_id  == SUA_PRM_RKEY)
                {
                    ret = UAL_SuaRoutingKeyToRKContext(asCtxt, ies[i + 1].
                                                       param_data.rkData.RKData,
                                                       ies[i + 1].param_length);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_LMHandleRKMMsg: error "
                                         "populating RK Ctxt, code %d \n", 
                                          ret));
                        free(asCtxt);

                        ret = UAL_NotifyUserASRegFailure(&ies[i + 1], 
                                                       UAL_REG_STAT_ERR_INV_RK);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to"
                                             " notify user \n"));
                        }

                        continue;
                    }

                    asCtxt->reqState = UAL_AS_REG;

                    /* set the instance to reply to */
                    asCtxt->instance = UALEvent->src;

                    ret = RKManager_AddEntry(asCtxt->rCtxt, asCtxt);

                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_LMHandleRKMMsg: Could not "
                                        "add RK entry to AS_Table, code %d \n",
                                         ret));
                        free(asCtxt);

                        ret = UAL_NotifyUserASRegFailure(&ies[i + 1],
                                                   UAL_REG_STAT_ERR_UNSUFF_RES);

                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to" 
                                             " notify user \n"));
                        }

                        continue;
                    }

                    sendIEs[sendIECount] = ies[i + 1];

                    sendIECount++;
         
                   continue;
                }

                ret = UAL_RoutingKeyToRKContext(asCtxt, 
                                           ies[i + 1].param_data.rkData.RKData,
                                           ies[i + 1].param_length);

                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("UAL_LMHandleRKMMsg: error "
                                     "populating RK Ctxt, code %d \n", ret));
                    free(asCtxt);

                    ret = UAL_NotifyUserASRegFailure(&ies[i + 1], 
                                                     UAL_REG_STAT_ERR_INV_RK);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to notify"
                                         " user \n"));
                    }

                    continue;
                }

                /* If the existing routing key route style is dpc-ni,*/
                /* and user is trying to register the same routing key with  */
                /* route style dpc-sio. Because ni is the subset of sio, and  */
                /* it's not unique enough to represent a key */
                ret = UAL_CheckRoutingInfoValid(&rCtxt, asCtxt);
                if (ret == ITS_SUCCESS)
                {
                    /* key exists or traffic mode doesn't match */
                    return ret;
                }

                /* Make sure routing key is valid */
		asCtxt->asInfo.type = ROUTING_KEY_ROUTE;
		memcpy(&matchInfo.basic, &asCtxt->asInfo, 
				             sizeof(ROUTE_BasicInfo));
	 	
                matchInfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
		matchInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

		ret = ROUTE_FindRoutingKeyByInfo(&rCtxt, &matchInfo); 

		if (ret == ITS_SUCCESS)
                {
                    UAL_DEBUG(("Routing Key already exists\n"));

		    return ret;
                }

		asCtxt->state = UAL_AS_INACTIVE;
                asCtxt->reqState = UAL_AS_REG;
		asCtxt->isMember = ITS_TRUE;

                /* set the instance to reply to */
                asCtxt->instance = UALEvent->src;

                ret = RKManager_AddEntry(asCtxt->rCtxt, asCtxt);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("UAL_LMHandleRKMMsg: Could not "
                                     "add RK entry to AS_Table, code %d \n",
                                     ret));
                    free(asCtxt);

                    ret = UAL_NotifyUserASRegFailure(&ies[i + 1],
                                                  UAL_REG_STAT_ERR_UNSUFF_RES);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to notify"
                                         " user \n"));
                    }

                    continue;
                }

                sendIEs[sendIECount] = ies[i + 1];

                sendIECount++;
            }
            else
            {
                UAL_ERROR(("UAL_LMHandleRKMMsg: malloc failed !!!! \n"));
            
                return ITS_ENOMEM;
            }
        }


        if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
        {
            ret = UAL_EncodeMsg(sendIEs, sendIECount,UALEvent, 
                                &UAL_SUA_REGREQ_Desc);
        }
        else
        {
            ret = UAL_EncodeMsg(sendIEs, sendIECount,UALEvent, 
                                &UAL_REGREQ_Desc);
        }

        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to encode msg, "
                             "code %d \n", ret));
            return ret;
        }

        ret = UAL_SendRKMMsg(UALEvent, UAL_AS_REG);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMHandleRKMMsg: Error sending REGREQ\n"));
        }

        break;

    }
    case UAL_MSG_DEREG_REQ:
    {
        ITS_UAL_IE *rCtxtIE;

        ret = UAL_DecodeMsg(ies, &ieCount, UALEvent, &UAL_DREGREQ_Desc);
        CHECK_UAL_DECODEMSG_ERROR(UALEvent->src, ret);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to decode msg, "
                             "code %d \n", ret));
            break;
        }
        
        rCtxtIE = UAL_FindUALIE(ies, ieCount, UAL_PRM_ROUT_CTX);
        if (rCtxtIE != NULL)
        {
            ITS_UINT rkArray[UAL_MAX_RCTXT_LEN];
            ITS_UINT validRkArray[UAL_MAX_RCTXT_LEN], numValidRK = 0;
            int i = 0, numRK = 0;
            RK_Context *asCtxt = NULL;

            ret = UAL_DecodeRoutingContext(rCtxtIE->param_data.rCtxt.rCtxt,
                                           rCtxtIE->param_length, rkArray,
                                           &numRK);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_LMHandleRKMMsg: Error decoding RCTXT\n"));

                break;
            }

            for (i = 0; i < numRK; i++)
            {
                asCtxt = RKManager_FindEntry(rkArray[i]);
                if (asCtxt != NULL)
                {
                    asCtxt->reqState = UAL_AS_DREG;
                    asCtxt->instance = UALEvent->src;
                    validRkArray[numValidRK] = rkArray[i];
                    numValidRK++;
                }
                else
                {
                    UAL_ERROR(("UAL_LMHandleRKMMsg: AS Entry not found "
                                     " AS: %d \n", rkArray[i]));

                    continue;
                }
            }

            ret = UAL_EncodeRoutingContext(rCtxtIE->param_data.rCtxt.rCtxt,
                                           &rCtxtIE->param_length, validRkArray, 
                                           numValidRK);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to encode Rctxt, "
                                "code %d \n", ret));
                break;
            }
        }
        else
        {
            UAL_ERROR(("UAL_LMHandleRKMMsg: Missing Rctxt parameter\n"));

            return ITS_EMISSMAND;
        }

        ret = UAL_EncodeMsg(ies, ieCount, UALEvent, &UAL_DREGREQ_Desc);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMHandleRKMMsg: Failed to encode msg, "
                             "code %d \n", ret));
            break;
        }

        ret = UAL_SendRKMMsg(UALEvent, UAL_AS_DREG);
        if (ret != ITS_SUCCESS)
        {
             UAL_ERROR(("UAL_LMHandleRKMMsg: Error Broadcasting "
                              "REGREQ\n"));
        }

        break;
    }
    default:
        UAL_WARNING(("UAL_LMHandleRKMMsg: Got Unknown msg from user, "
                           "type: %d\n", msgType));

        break;
    }

    return ret;
}



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
UAL_LMSendASPSMandTMMsg(ITS_EVENT *UALEvent, UAL_ASP_STATE state,
                         ITS_UINT trafficMode)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT tid = 0;
    ASP_Entry *aspEntry = NULL;
    UAL_TimerCtx timerCtxt;
    ITS_EVENT event;

    tid = UALEvent->src;
    UALEvent->src = UAL_MANAGER_INSTANCE;

    ret = ASPTable_FindEntry(tid, &aspEntry);
    if (ret == ITS_SUCCESS && aspEntry != NULL)
    {
        ITS_OCTET ackMsgType = 0x00;
        /* Assgining default to Down state */
        UAL_SEND_MSG_TYPE msgType = UAL_ASP_DOWN;

        //aspEntry->remoteInfo.state = state;

        timerCtxt.type = UAL_RETRANS;
        timerCtxt.from = aspEntry->trId;
        timerCtxt.retryCount = UAL_GL_NUM_RETRY;
        timerCtxt.tm = UAL_MODE_NONE;

        switch (state)
        {
             case UAL_ASP_UP:
                 UAL_IncrementMIBStats(tid, UAL_PEG_UP_SENT_ID);

                 aspEntry->state = state;
                 ackMsgType = UAL_MSG_ASPUP_ACK;
                 msgType= ASP_UP_MSG;

                 break;

            case UAL_ASP_DOWN:
                 UAL_IncrementMIBStats(tid, UAL_PEG_DN_SENT_ID);

                 aspEntry->state = state;
                 ackMsgType = UAL_MSG_ASPDN_ACK;
                 msgType= ASP_DOWN_MSG;

                 break;

            case UAL_ASP_ACTIVE:
                 if(aspEntry->state == UAL_ASP_DOWN)
                 {
                     UAL_ERROR(("UAL_LMSendASPSMandTMMsg: Can not send "
                                "ASP_ACTIVE in ASP_DOWN state (aspID = %d)\n",
                                aspEntry->aspId));
                     break;
                 }

                 UAL_IncrementMIBStats(tid, UAL_PEG_AC_SENT_ID);

                 aspEntry->state = state;
                 ackMsgType = UAL_MSG_ASPAC_ACK;
                 msgType= ASP_ACTIVE_MSG;

                 break;

            case UAL_ASP_INACTIVE:
                 if(aspEntry->state == UAL_ASP_DOWN)
                 {
                     UAL_ERROR(("UAL_LMSendASPSMandTMMsg: Can not send "
                                "ASP_INACTIVE in ASP_DOWN state (aspID = %d)\n",
                                aspEntry->aspId));
                     break;
                 }

                 UAL_IncrementMIBStats(tid, UAL_PEG_IA_SENT_ID);

                 aspEntry->state = state;
                 ackMsgType = UAL_MSG_ASPIA_ACK;
                 msgType= ASP_INACTIVE_MSG;

                 break;

             default:
                 break;
        }

        timerCtxt.ackMsgType = ackMsgType;
        timerCtxt.msgType = msgType;

        ret = UAL_SetTimerMsgData(&timerCtxt, UALEvent);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMSendASPSMandTMMsg: UAL msg too long for timer."));
        }

        ITS_EVENT_INIT(&event, UALEvent->src, UALEvent->len);

        memcpy(event.data, UALEvent->data, UALEvent->len);

        ret = TRANSPORT_PutEvent(tid, &event);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_LMSendASPSMandTMMsg: TRANSPORT_PutEvent Failed\n"));
        }

        if (trafficMode < UAL_BCST_NO_TIMER)
        {
            aspEntry->ackTimer[msgType] =
                                   TIMERS_StartTimer(UAL_MANAGER_INSTANCE,
                                                     UAL_GL_ACK_TIMER,
                                                     (void *)&timerCtxt,
                                                     sizeof(UAL_TimerCtx));
        }
    }
    else
    {
        UAL_ERROR(("UAL_LMSendASPSMandTMMsg: Could not find ASP_Entry "
                   "on transport %d\n", tid));
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
 * adutta    07-01-2005  BugId:1668      Peg counter implemented for
 *                                       sending asp down/active/inactive 
 *
 *  See Also:
 ******************************************************************************/
int
UAL_BroadCastMsg(ITS_EVENT *UALEvent, UAL_ASP_STATE state, ITS_UINT trafficMode)
{
    int ret = ITS_SUCCESS, size = UAL_MAX_NUM_ASSOC, avail = 0;
    int i = 0;
    ITS_USHORT tridArray[UAL_MAX_NUM_ASSOC];
    ASP_Entry *aspEntry = NULL;
    UAL_TimerCtx timerCtxt;
    ITS_EVENT event;

    UALEvent->src = UAL_MANAGER_INSTANCE;

    ret = ASPTable_GetAllTransportIds(tridArray, size, &avail);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Traversing ASP_Table.\n"));

        return ret;
    }

    for (i = 0; i < avail; i++)
    {
        ret = ASPTable_FindEntry(tridArray[i], &aspEntry);
        if (aspEntry != NULL)
        {
            ITS_OCTET ackMsgType = 0x00;
            /* Assgining default to Down state */
            UAL_SEND_MSG_TYPE msgType = UAL_ASP_DOWN;

	    aspEntry->remoteInfo.state = state;

            timerCtxt.type = UAL_RETRANS;
            timerCtxt.from = aspEntry->trId;
            timerCtxt.retryCount = UAL_GL_NUM_RETRY;
            timerCtxt.tm = UAL_MODE_NONE;

            switch (state)
            {
                case UAL_ASP_ACTIVE:
                    if( aspEntry->state == UAL_ASP_DOWN)
                    {
                        UAL_ERROR(("Can not send ASP_ACTIVE in ASP_DOWN state (aspID=%d)\n", aspEntry->aspId));
                        continue;
                    }

                    if( aspEntry->state == UAL_ASP_ACTIVE)
                    {
                        UAL_ERROR(("Cannot send ASP_ACTIVE in ASP_ACTIVE state (aspID=%d)\n",
                                    aspEntry->aspId));
                        continue;
                    }

                    aspEntry->state = state;
                    UAL_IncrementMIBStats(tridArray[i], UAL_PEG_AC_SENT_ID);
                    ackMsgType = UAL_MSG_ASPAC_ACK;
                    msgType= ASP_ACTIVE_MSG;
                    break;

                case UAL_ASP_UP:
                    UAL_IncrementMIBStats(tridArray[i], UAL_PEG_UP_SENT_ID);
                    ackMsgType = UAL_MSG_ASPUP_ACK;
                    msgType= ASP_UP_MSG;

                    break;

                case UAL_ASP_INACTIVE:
                    if( aspEntry->state == UAL_ASP_DOWN)
                    { 
                        UAL_ERROR(("Can not send ASP_INACTIVE in ASP_DOWN state (aspID=%d)\n", aspEntry->aspId));
                        continue;
                    }

                    if( aspEntry->state == UAL_ASP_INACTIVE)
                    {
                        UAL_ERROR(("Cannot send ASP_INACTIVE in ASP_INACTIVE state (aspID=%d)\n", 
                                    aspEntry->aspId));
                        continue;
                    }

                    /* Checking if ASP_INACTIVE is already sent and *
                     * waiting for ASP_INACTIVE_ACK to receive      *
                     */
                    if (aspEntry->ackTimer[ASP_INACTIVE_MSG] != (ITS_SERIAL)0)
                    {
                        UAL_WARNING(("Already waiting for ASP_INACTIVE_ACK "
                                    "for (aspID=%d)\n", aspEntry->aspId));
                        continue;
                    }

                    /* Updating the state is commented, since when ASP DOWN is sent
                       based on the present state, the ASP will trigger a procedure
                       to return back to its previous state
                       aspEntry->state = state;
                       */ 
                    UAL_IncrementMIBStats(tridArray[i], UAL_PEG_IA_SENT_ID);
                    ackMsgType = UAL_MSG_ASPIA_ACK;
                    msgType= ASP_INACTIVE_MSG;
                    break;

                case UAL_ASP_DOWN:
                    UAL_IncrementMIBStats(tridArray[i], UAL_PEG_DN_SENT_ID);
                    ackMsgType = UAL_MSG_ASPDN_ACK;
                    msgType= ASP_DOWN_MSG;

                    /* Updating the state is commented, since when ASP DOWN is sent
                       based on the present state, the ASP will trigger a procedure
                       to return back to its previous state
                       aspEntry->state = state;
                       */ 
                    break;

                case UAL_ASP_CANT_START:
                    break;
            }

            timerCtxt.ackMsgType = ackMsgType;
	    timerCtxt.msgType = msgType;

            ret = UAL_SetTimerMsgData(&timerCtxt, UALEvent);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL msg too long for timer."));

                continue;
            }

            ITS_EVENT_INIT(&event, UALEvent->src, UALEvent->len);

            memcpy(event.data, UALEvent->data, UALEvent->len);

            ret = TRANSPORT_PutEvent(tridArray[i], &event);
            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("TRANSPORT_PutEvent Failed \n"));
            }

            if (trafficMode < UAL_BCST_NO_TIMER)
            {
                aspEntry->ackTimer[msgType] = 
                                       TIMERS_StartTimer(UAL_MANAGER_INSTANCE,
                                                         UAL_GL_ACK_TIMER,
                                                         (void *)&timerCtxt,
                                                         sizeof(UAL_TimerCtx));
            }
        }
       else
       {
           UAL_ERROR(("Could not find ASP_Entry %d\n", tridArray[i]));
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
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *       rctxt : returns rctxt > 0 if manager allocates succesfully.
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
UAL_RegisterApplicationServer(UAL_AS_DEF *as, ITS_USHORT size, 
                              ITS_USHORT instance, ITS_UINT *rctxt)
{
    int ret = ITS_SUCCESS, i = 0, ieCount = 0;
    ITS_UAL_IE ieArray[ITS_MAX_UAL_IES];
    ITS_EVENT ualEvent;

    ITS_C_ASSERT(as != NULL);

    /* 1) create the common msg Header */

    ieArray[0].param_id = UAL_PRM_MSG_HDR;
    ieArray[0].param_length = sizeof(UAL_MSG_HDR);
    ieArray[0].param_data.msgHeader.msgClass = UAL_CLASS_RKM;
    ieArray[0].param_data.msgHeader.msgType = UAL_MSG_REG_REQ;
    ieArray[0].param_data.msgHeader.version = UAL_GL_VERSION;
    ieArray[0].param_data.msgHeader.reserved = 0x00;

    ieCount++;

    /* 2) build the RKs */
    for (i = 0; i < size; i++)
    {
        if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
        {
             ret = UAL_EncodeSuaRoutingKey(&as[i], &ieArray[i + 1], &rctxt[i]);
        }
        else
        {
            ret = UAL_EncodeRoutingKey(&as[i], &ieArray[i + 1], &rctxt[i]);
        }

        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("UAL_RegisterApplicationServer: Failed to encode "
                             "Routing Key, code: %d\n", ret));

            continue;
        }

        ieCount++;
    }

    if (ieCount == 1)
    {
        UAL_ERROR(("UAL_RegisterApplicationServer: No Routing Key "
                         "provided \n"));

        return ITS_EMISSMAND;
    }

    
    if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
    {
        if (as[0].aspCapab != NULL)
        {
           ieArray[ieCount].param_id = SUA_PRM_ASP_CAPAB;
           ieArray[ieCount].param_length = 4;
           memcpy(&(ieArray[ieCount].param_data), as[0].aspCapab,
                  sizeof(SUA_ASP_CAPAB));
           ieCount++;
        }                                                                      
    }

    ITS_EVENT_INIT(&ualEvent, instance, UAL_MAX_MSG_LEN);

    /* 3) Encode the REG_REQ */
    if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
    {
        ret = UAL_EncodeMsg(ieArray, ieCount, &ualEvent, &UAL_SUA_REGREQ_Desc);
    }
    else
    {
        ret = UAL_EncodeMsg(ieArray, ieCount, &ualEvent, &UAL_REGREQ_Desc);
    }

    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_RegisterApplicationServer: UAL_Encode failed "
                         ", code: %d\n", ret));

        return ret;
    }

    /* 4) send to Layer Management */
    return TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &ualEvent);
}


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
UAL_DeregisterApplicationServer(ITS_UINT *rCtxt, ITS_USHORT size, 
                                ITS_USHORT instance)
{
    int ret = ITS_SUCCESS, ieCount = 0;
    ITS_UAL_IE ieArray[ITS_MAX_UAL_IES];
    ITS_EVENT ualEvent;

    ITS_C_ASSERT(rCtxt != NULL);

    ieArray[0].param_id = UAL_PRM_MSG_HDR;
    ieArray[0].param_length = sizeof(UAL_MSG_HDR);
    ieArray[0].param_data.msgHeader.msgClass = UAL_CLASS_RKM;
    ieArray[0].param_data.msgHeader.msgType = UAL_MSG_DEREG_REQ;
    ieArray[0].param_data.msgHeader.version = UAL_GL_VERSION;
    ieArray[0].param_data.msgHeader.reserved = 0x00;

    ieCount++;

    ieArray[1].param_id = UAL_PRM_ROUT_CTX;

    ret = UAL_EncodeRoutingContext(ieArray[1].param_data.rCtxt.rCtxt,
                                   &ieArray[1].param_length, rCtxt, size); 
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_DeregisterApplicationServer: Failed to encode "
                         "Rctxt, code %d \n", ret));
        return ret;
    }

    ieCount++;
    
    ITS_EVENT_INIT(&ualEvent, instance, UAL_MAX_MSG_LEN);

    ret = UAL_EncodeMsg(ieArray, ieCount, &ualEvent, &UAL_DREGREQ_Desc);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_DeregisterApplicationServer: UAL_Encode failed "
                         ", code: %d\n", ret));

        return ret;
    }

    return TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &ualEvent);
}


int
UAL_NotifyUserASRegFailure(ITS_UAL_IE *resultIE, ITS_UINT result) 
{
    int ret = ITS_SUCCESS, lrkid = 0;
    ITS_UAL_IE ieArray[2];    
    ITS_EVENT resEvent;

    ieArray[0].param_id = UAL_PRM_MSG_HDR;
    ieArray[0].param_length = sizeof(UAL_MSG_HDR);
    ieArray[0].param_data.msgHeader.msgClass = UAL_CLASS_RKM;
    ieArray[0].param_data.msgHeader.msgType = UAL_MSG_REG_RSP;
    ieArray[0].param_data.msgHeader.version = UAL_GL_VERSION;
    ieArray[0].param_data.msgHeader.reserved = 0x00;

    lrkid = UAL_RoutingKeyGetLRKID(resultIE->param_data.rkData.RKData,
                                   resultIE->param_length); 
    if (lrkid)
    {
        UAL_SetRegRes(ieArray[1].param_data.regResult.regRes, lrkid, result, 0); 

        ITS_EVENT_INIT(&resEvent, UAL_MANAGER_INSTANCE, UAL_MAX_MSG_LEN);

        ret = UAL_EncodeMsg(ieArray, 2, &resEvent, &UAL_REGRSP_Desc);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Failed to encode REGRES message \n"));

            return ret;
        }

        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL, 
                                  (ITS_POINTER)&resEvent);
    }          

    return ret;
}

int
UAL_SendRKMMsg(ITS_EVENT *UALEvent, UAL_DYNAMIC_REQ_STATE state)
{
    int ret = ITS_SUCCESS, avail = 0, i = 0;
    ITS_USHORT tridArray[UAL_MAX_NUM_ASSOC];
    ASP_Entry *aspEntry = NULL;

    UALEvent->src = UAL_MANAGER_INSTANCE;


    ret = ASPTable_GetAllTransportIds(tridArray, UAL_MAX_NUM_ASSOC, &avail);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Traversing ASP_Table.\n"));
        return ret;
    }

    for (i = 0; i < avail; i++)
    {
        ret = ASPTable_FindEntry(tridArray[i], &aspEntry);
        if (!aspEntry)
        {
            UAL_ERROR(("Could not find ASP_Entry %d\n", tridArray[i]));
	    return ret;
        }

        ret = TRANSPORT_PutEvent(aspEntry->trId, UALEvent);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("TRANSPORT_PutEvent Failed \n"));
        }
        else
        {
            if (state == UAL_AS_REG)
            {
                UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_REG_REQ_SENT_ID);
            }

	    if (state == UAL_AS_DREG)
            {
                UAL_IncrementMIBStats(aspEntry->trId, UAL_PEG_DEREG_REQ_SENT_ID);
            }
        }
    }

    return ret;
}
