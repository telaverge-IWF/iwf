/* ********************************-*-H-*-**************************************
 *       Copyright 2012 Diametriq, LLC All Rights Reserved.                    *
 *           Manufactured in the United States of America.                     *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.          *
 *                                                                             *
 *    This product and related documentation is protected by copyright and     *
 *    distributed under licenses restricting its use, copying, distribution    *
 *    and decompilation.  No part of this product or related documentation     *
 *    may be reproduced in any form by any means without prior written         *
 *    authorization of Diametriq and its licensors, if any.                    *
 *                                                                             *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *    government is subject to restrictions as set forth in subparagraph       *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                             * 
 * *****************************************************************************/

#ifndef __DIA_STACK_STATISTICS_H__
#define __DIA_STACK_STATISTICS_H__

#include "Statistics.h"
#include "GenericStatsCounter.h"
#include "MsgStatsCounter.h"

//Macros for Peer General Statistics
#define DIA_INC_PEER_CER_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].IncrementRxReqCount(); \

#define DIA_INC_PEER_CER_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].IncrementTxReqCount(); \

#define DIA_INC_PEER_CEA_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].IncrementRxRspCount(); \

#define DIA_INC_PEER_CEA_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].IncrementTxRspCount(); \

#define DIA_GET_PEER_CER_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].GetRxReqCount(); \

#define DIA_GET_PEER_CER_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].GetTxReqCount(); \

#define DIA_GET_PEER_CEA_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].GetRxRspCount(); \

#define DIA_GET_PEER_CEA_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].GetTxRspCount(); \

#define DIA_RESET_PEER_CE_COUNTER(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).CEMsgs[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_DPR_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].IncrementRxReqCount(); \

#define DIA_INC_PEER_DPR_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].IncrementTxReqCount(); \

#define DIA_INC_PEER_DPA_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].IncrementRxRspCount(); \

#define DIA_INC_PEER_DPA_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].IncrementTxRspCount(); \

#define DIA_GET_PEER_DPR_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].GetRxReqCount(); \

#define DIA_GET_PEER_DPR_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].GetTxReqCount(); \

#define DIA_GET_PEER_DPA_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].GetRxRspCount(); \

#define DIA_GET_PEER_DPA_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].GetTxRspCount(); \

#define DIA_RESET_PEER_DP_COUNTER(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DPMsgs[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_DWR_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].IncrementRxReqCount(); \

#define DIA_INC_PEER_DWR_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].IncrementTxReqCount(); \

#define DIA_INC_PEER_DWA_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].IncrementRxRspCount(); \

#define DIA_INC_PEER_DWA_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].IncrementTxRspCount(); \

#define DIA_GET_PEER_DWR_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].GetRxReqCount(); \

#define DIA_GET_PEER_DWR_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].GetTxReqCount(); \

#define DIA_GET_PEER_DWA_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].GetRxRspCount(); \

#define DIA_GET_PEER_DWA_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].GetTxRspCount(); \

#define DIA_RESET_PEER_DW_COUNTER(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).DWMsgs[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_TOTAL_REQUEST_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].IncrementRxReqCount(); \

#define DIA_INC_PEER_TOTAL_REQUEST_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].IncrementTxReqCount(); \

#define DIA_INC_PEER_TOTAL_RESPONSE_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].IncrementRxRspCount(); \

#define DIA_INC_PEER_TOTAL_RESPONSE_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].IncrementTxRspCount(); \

#define DIA_GET_PEER_TOTAL_REQUEST_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].GetRxReqCount(); \

#define DIA_GET_PEER_TOTAL_REQUEST_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].GetTxReqCount(); \

#define DIA_GET_PEER_TOTAL_RESPONSE_RECEIVED(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].GetRxRspCount(); \

#define DIA_GET_PEER_TOTAL_RESPONSE_SENT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].GetTxRspCount(); \

#define DIA_RESET_PEER_TOTAL_MSG_COUNTER(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).TotalMsgs[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_RETRANSMIT_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).retransmitMsgs[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_RETRANSMIT_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).retransmitMsgs[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_RETRANSMIT_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerGeneralStats).retransmitMsgs[eAccelero::StatsIndex].Reset(); \

//Macro for Peer Error Stats
#define DIA_INC_PEER_UNABLE_TO_DELIVER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unableToDeliver[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_UNABLE_TO_DELIVER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unableToDeliver[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_UNABLE_TO_DELIVER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unableToDeliver[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_REALM_NOT_SERVED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).realmNotServed[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_REALM_NOT_SERVED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).realmNotServed[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_REALM_NOT_SERVED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).realmNotServed[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_UNKNOWN_PEER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unknownPeer[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_UNKNOWN_PEER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unknownPeer[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_UNKNOWN_PEER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unknownPeer[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_UNKNOWN_SESSION_ID_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unknownSessionId[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_UNKNOWN_SESSION_ID_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unknownSessionId[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_UNKNOWN_SESSION_ID_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).unknownSessionId[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_INVALID_AVP_VALUE_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidAvpValue[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_INVALID_AVP_VALUE_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidAvpValue[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_INVALID_AVP_VALUE_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidAvpValue[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_MISSING_AVP_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).missingAvp[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_MISSING_AVP_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).missingAvp[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_MISSING_AVP_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).missingAvp[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_NO_COMMON_APP_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).noCommonApp[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_NO_COMMON_APP_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).noCommonApp[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_NO_COMMON_APP_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).noCommonApp[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_INVALID_AVP_LENGTH_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidAvpLength[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_INVALID_AVP_LENGTH_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidAvpLength[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_INVALID_AVP_LENGTH_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidAvpLength[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_INVALID_MESSAGE_LENGTH_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidMsgLength[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_INVALID_MESSAGE_LENGTH_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidMsgLength[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_INVALID_MESSAGE_LENGTH_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).invalidMsgLength[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_LOOP_DETECTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).loopDetected[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_LOOP_DETECTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).loopDetected[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_LOOP_DETECTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).loopDetected[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_APP_UNSUPPORTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).appUnsupported[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_APP_UNSUPPORTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).appUnsupported[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_APP_UNSUPPORTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).appUnsupported[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_OTHER_ERRORS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).otherErrors[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_OTHER_ERRORS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).otherErrors[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_OTHER_ERRORS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerErrorStats).otherErrors[eAccelero::StatsIndex].Reset(); \

/* Start of Shiva' changes */
#define DIA_INC_PEER_CONNECTION_ATTEMPTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionAttempt[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_ATTEMPTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionAttempt[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_ATTEMPTED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionAttempt[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_RETRIES_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionRetry[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_RETRIES_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionRetry[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_RETRIES_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionRetry[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_CONNECTION_SUCCESS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionSuccess[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_CONNECTION_SUCCESS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionSuccess[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_CONNECTION_SUCCESS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionSuccess[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_CONNECTION_FAILED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionFailed[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_CONNECTION_FAILED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionFailed[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_CONNECTION_FAILED_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionFailed[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_ABNORMAL_DISCONNECT_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).abnormalDisconnect[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_ABNORMAL_DISCONNECT_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).abnormalDisconnect[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_ABNORMAL_DISCONNECT_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).abnormalDisconnect[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_CLOSE_BY_PEER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionCloseByPeer[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_CLOSE_BY_PEER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionCloseByPeer[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_CLOSE_BY_PEER_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionCloseByPeer[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionCloseByDre[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionCloseByDre[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_CLOSE_BY_DRE_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).connectionCloseByDre[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_SOCKET_BIND_SUCCESS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).socketBindSuccess[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_SOCKET_BIND_SUCCESS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).socketBindSuccess[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_SOCKET_BIND_SUCCESS_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).socketBindSuccess[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_SOCKET_BIND_FAIL_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).socketBindFail[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_SOCKET_BIND_FAIL_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).socketBindFail[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_SOCKET_BIND_FAIL_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).socketBindFail[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).totalTransportDown[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).totalTransportDown[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_CONNECTION_TOTAL_TRANSPORT_DOWN_COUNT(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).totalTransportDown[eAccelero::StatsIndex].Reset(); \

#define DIA_GET_PEER_MSG_REJECTED_BY_RATE_LIMITING_FACTOR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfMsgsRejectedByRateLimitingFilter[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_MSG_REJECTED_BY_RATE_LIMITING_FACTOR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfMsgsRejectedByRateLimitingFilter[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_MSG_REJECTED_BY_RATE_LIMITING_FACTOR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfMsgsRejectedByRateLimitingFilter[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_RCVD_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRRcvdWithCauseDoNotWantToTalkToYou[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_RCVD_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRRcvdWithCauseDoNotWantToTalkToYou[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_RCVD_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRRcvdWithCauseDoNotWantToTalkToYou[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_RCVD_DPR_WITH_CAUSE_BUSY(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRRcvdWithCauseBusy[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_RCVD_DPR_WITH_CAUSE_BUSY(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRRcvdWithCauseBusy[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_RCVD_DPR_WITH_CAUSE_BUSY(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRRcvdWithCauseBusy[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_SENT_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRSentWithCauseDoNotWantToTalkToYou[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_SENT_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRSentWithCauseDoNotWantToTalkToYou[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_SENT_DPR_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRSentWithCauseDoNotWantToTalkToYou[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_SENT_DPR_WITH_CAUSE_BUSY(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRSentWithCauseBusy[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_SENT_DPR_WITH_CAUSE_BUSY(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRSentWithCauseBusy[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_SENT_DPR_WITH_CAUSE_BUSY(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesDPRSentWithCauseBusy[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_SENT_CUR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesCURSent[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_SENT_CUR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesCURSent[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_SENT_CUR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesCURSent[eAccelero::StatsIndex].Increment(); \

#define DIA_GET_PEER_RCVD_CUR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesCURRcvd[eAccelero::StatsIndex].GetCount(); \

#define DIA_RESET_PEER_RCVD_CUR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesCURRcvd[eAccelero::StatsIndex].Reset(); \

#define DIA_INC_PEER_RCVD_CUR(peerEntry) \
    ((DIA_PE_STATS(peerEntry)).m_peerTransportStats).noOfTimesCURRcvd[eAccelero::StatsIndex].Increment(); \

class DiaPeerGeneralStats
{
public :
    //Peer General Statistics
    eAccelero::MsgStatsCounter CEMsgs[EACC_MAX_THREADS];
    eAccelero::MsgStatsCounter DWMsgs[EACC_MAX_THREADS];
    eAccelero::MsgStatsCounter DPMsgs[EACC_MAX_THREADS];
    eAccelero::MsgStatsCounter TotalMsgs[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter retrasmitMsgs[EACC_MAX_THREADS];
};

class DiaPeerErrorStats
{
public :
    //Generated Error Statistics
    eAccelero::GenericStatsCounter unableToDeliver[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter realmNotServed[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter unknownPeer[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter unknownSessionId[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter invalidAvpValue[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter missingAvp[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noCommonApp[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter invalidAvpLength[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter invalidMsgLength[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter loopDetected[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter appUnsupported[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter otherErrors[EACC_MAX_THREADS];

};

class DiaPeerTransportStats
{
public :
    eAccelero::GenericStatsCounter connectionAttempt[EACC_MAX_THREADS];
    //eAccelero::GenericStatsCounter connectionRetry[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter connectionSuccess[EACC_MAX_THREADS];
    //eAccelero::GenericStatsCounter connectionReject[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter connectionFailed[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter abnormalDisconnect[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter connectionCloseByPeer[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter connectionCloseByDre[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter socketBindSuccess[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter socketBindFail[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter totalTransportDown[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfMsgsRejectedByRateLimitingFilter[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfTimesDPRRcvdWithCauseDoNotWantToTalkToYou[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfTimesDPRRcvdWithCauseBusy[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfTimesDPRSentWithCauseDoNotWantToTalkToYou[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfTimesDPRSentWithCauseBusy[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfTimesCURSent[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter noOfTimesCURRcvd[EACC_MAX_THREADS];


};

class DiaStackPeerStats 
{
public :
    
    //constructor
    DiaStackPeerStats(){ }

    //Peer General Stats
    DiaPeerGeneralStats m_peerGeneralStats;
    //Peer Error Stats
    DiaPeerErrorStats m_peerErrorStats;
    //Peer Transport Stats
    DiaPeerTransportStats m_peerTransportStats;
};

#endif
