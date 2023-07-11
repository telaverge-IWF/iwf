/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: ssg_statistics.cpp,v 1.1.1.1.2.1.2.2.2.1.6.1.8.4 2020/04/23 13:45:37 jkchaitanya Exp $
 *
 *  LOG: $Log: ssg_statistics.cpp,v $
 *  LOG: Revision 1.1.1.1.2.1.2.2.2.1.6.1.8.4  2020/04/23 13:45:37  jkchaitanya
 *  LOG: added Actitivy test stats
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.2.2.1.6.1.8.3  2014/12/03 09:26:18  mhimanshu
 *  LOG: stats implementation at MML - diaS6aStats and activeSubscribers
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.2.2.1.6.1.8.2  2014/12/02 12:39:01  jkchaitanya
 *  LOG: changes for stats enhancement for TcapError count for all the translators
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.2.2.1.6.1.8.1  2014/12/02 05:44:50  jkchaitanya
 *  LOG: changes for updating stats for incomming components
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.2.2.1.6.1  2014/04/07 04:48:09  jkchaitanya
 *  LOG: changes for stats update for connect message
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.2.2.1  2014/01/23 09:51:20  jkchaitanya
 *  LOG: changes for merging iwf code from poc to productization
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.2  2013/10/04 13:43:07  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1.2.1  2013/09/06 11:43:06  jkchaitanya
 *  LOG: changes for IWF stats for cap-ro messages
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/06/19 12:39:42  jsarvesh
 *  LOG: MML implementation for IWF Statistics
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:36  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2012/12/18 16:11:58  brajappa
 *  LOG: Initial IWF branch creation and linux compilation changes
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 ****************************************************************************/
#ident "$Id: ssg_statistics.cpp,v 1.1.1.1.2.1.2.2.2.1.6.1.8.4 2020/04/23 13:45:37 jkchaitanya Exp $"

#include <iostream>
#include <iomanip>

#ifdef ITU
#undef ITU
#endif

#ifndef CCITT
#define CCITT
#endif

#include <ssg_statistics.h>
#include <sys/time.h>
#include "iwf_prot_utils.h"

SsgStackStatistics mapStats;
//HipStats *Stats;

/*.implementation:static
 ****************************************************************************
 *  Purpose: to clear the statistics
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics:: clearstatistics()
{
   Lock();

   _sendAuthInfo_arg_sent         =0;
   _sendAuthInfo_arg_rcvd         =0;
   _sendAuthInfo_res_rcvd         =0;
   _sendAuthInfo_res_sent         =0;
   _sendAuthInfo_error_rcvd       =0;
   _sendAuthInfo_error_sent       =0;
   _sendAuthInfo_timeout          =0;
   _sendAuthInfo_other_error      =0;

   _routingInfoForGPRS_arg_sent            =0;
   _routingInfoForGPRS_arg_rcvd            =0;
   _routingInfoForGPRS_res_rcvd            =0;
   _routingInfoForGPRS_res_sent            =0;
   _routingInfoForGPRS_error_rcvd          =0;
   _routingInfoForGPRS_error_sent          =0;
   _routingInfoForGPRS_timeout             =0;
   _routingInfoForGPRS_other_error         =0;

   _updateGprsLocation_arg_sent    =0;
   _updateGprsLocation_arg_rcvd    =0;
   _updateGprsLocation_res_rcvd    =0;
   _updateGprsLocation_res_sent    =0;
   _updateGprsLocation_error_rcvd  =0;
   _updateGprsLocation_error_sent  =0;
   _updateGprsLocation_timeout     =0;
   _updateGprsLocation_other_error =0;

   _readyforsm_arg_sent         =0;
   _readyforsm_arg_rcvd         =0;
   _readyforsm_res_rcvd         =0;
   _readyforsm_res_sent         =0;
   _readyforsm_error_rcvd       =0;
   _readyforsm_error_sent       =0;
   _readyforsm_timeout          =0;
   _readyforsm_other_error      =0;

   _purgems_arg_sent    =0;
   _purgems_arg_rcvd    =0;
   _purgems_res_rcvd    =0;
   _purgems_res_sent    =0;
   _purgems_error_rcvd  =0;
   _purgems_error_sent  =0;
   _purgems_timeout     =0;
   _purgems_other_error =0;

   _restoreData_arg_sent              =0;
   _restoreData_arg_rcvd              =0;
   _restoreData_res_rcvd              =0;
   _restoreData_res_sent              =0;
   _restoreData_error_rcvd            =0;
   _restoreData_error_sent            =0;
   _restoreData_timeout               =0;
   _restoreData_other_error           =0;

   _insertSubsData_arg_sent         =0;
   _insertSubsData_arg_rcvd         =0;
   _insertSubsData_res_rcvd         =0;
   _insertSubsData_res_sent         =0;
   _insertSubsData_error_rcvd       =0;
   _insertSubsData_error_sent       =0;
   _insertSubsData_timeout          =0;
   _insertSubsData_other_error      =0;

   _deleteSubsData_arg_sent         =0;
   _deleteSubsData_arg_rcvd         =0;
   _deleteSubsData_res_rcvd         =0;
   _deleteSubsData_res_sent         =0;
   _deleteSubsData_error_rcvd       =0;
   _deleteSubsData_error_sent       =0;
   _deleteSubsData_timeout          =0;
   _deleteSubsData_other_error      =0;

   _provideSubsData_arg_sent    =0;
   _provideSubsData_arg_rcvd    =0;
   _provideSubsData_res_rcvd    =0;
   _provideSubsData_res_sent    =0;
   _provideSubsData_error_rcvd  =0;
   _provideSubsData_error_sent  =0;
   _provideSubsData_timeout     =0;
   _provideSubsData_other_error =0;

   _reset_arg_sent    =0;
   _reset_arg_rcvd    =0;
   _reset_res_rcvd    =0;
   _reset_res_sent    =0;
   _reset_error_rcvd  =0;
   _reset_error_sent  =0;
   _reset_timeout     =0;
   _reset_other_error =0;

   _cancellocation_arg_sent    =0;
   _cancellocation_arg_rcvd    =0;
   _cancellocation_res_rcvd    =0;
   _cancellocation_res_sent    =0;
   _cancellocation_error_rcvd  =0;
   _cancellocation_error_sent  =0;
   _cancellocation_timeout     =0;
   _cancellocation_other_error =0;

   _activatetracemode_arg_sent    =0;
   _activatetracemode_arg_rcvd    =0;
   _activatetracemode_res_rcvd    =0;
   _activatetracemode_res_sent    =0;
   _activatetracemode_error_rcvd  =0;
   _activatetracemode_error_sent  =0;
   _activatetracemode_timeout     =0;
   _activatetracemode_other_error =0;

   _deactivatetracemode_arg_sent    =0;
   _deactivatetracemode_arg_rcvd    =0;
   _deactivatetracemode_res_rcvd    =0;
   _deactivatetracemode_res_sent    =0;
   _deactivatetracemode_error_rcvd  =0;
   _deactivatetracemode_error_sent  =0;
   _deactivatetracemode_timeout     =0;
   _deactivatetracemode_other_error =0;

   _total_number_msg_sent                 =0;
   _total_number_msg_rcvd                 =0;
   _total_number_res_rcvd                 =0;
   _total_number_res_sent                 =0;
   _total_number_error_rcvd               =0;
   _total_number_error_sent               =0;
   _total_number_timeout                  =0;
   _total_number_other_error              =0;

   _initialdp_arg_rcvd                  = 0;
   _initialdpsms_arg_rcvd               = 0;
   _eventreportbcsm_arg_rcvd            = 0;
   _eventreportsms_arg_rcvd             = 0;
   _applychargingreport_arg_rcvd        = 0;
   _requestreportbcsmevent_arg_sent     = 0;
   _requestreportsmsevent_arg_sent      = 0;
   _applycharging_arg_sent              = 0;
   _continue_arg_sent                   = 0;
   _connect_arg_sent                    = 0;
   _continue_sms_arg_sent               = 0;
   _release_arg_sent                    = 0;
   _release_sms_arg_sent                = 0;
   _activity_test_sent			= 0;
   _activity_resp_rcvd			= 0;

   _number_of_tcap_components_sent      = 0;
   _number_of_tcap_components_received  = 0;
   _number_of_tcap_error_components_sent = 0;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoArgSent()
{
   if (_sendAuthInfo_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _sendAuthInfo_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoArgRecvd()
{
   if (_sendAuthInfo_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _sendAuthInfo_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoResRecvd()
{
   if (_sendAuthInfo_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _sendAuthInfo_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoResSent()
{
   if (_sendAuthInfo_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _sendAuthInfo_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoTimeOut()
{
   if (_sendAuthInfo_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _sendAuthInfo_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoErrorRecvd()
{
   if (_sendAuthInfo_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _sendAuthInfo_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoErrorSent()
{
   if (_sendAuthInfo_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _sendAuthInfo_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::SendAuthInfoOtherError()
{
   if (_sendAuthInfo_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _sendAuthInfo_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataArgSent()
{
   if (_insertSubsData_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _insertSubsData_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataArgRecvd()
{
   if (_insertSubsData_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _insertSubsData_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataResRecvd()
{
   if (_insertSubsData_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _insertSubsData_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataResSent()
{
   if (_insertSubsData_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _insertSubsData_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataTimeOut()
{
   if (_insertSubsData_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _insertSubsData_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataErrorRecvd()
{
   if (_insertSubsData_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _insertSubsData_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataErrorSent()
{
   if (_insertSubsData_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _insertSubsData_error_sent++;
   _total_number_error_sent++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::InsertSubsDataOtherError()
{
   if (_insertSubsData_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _insertSubsData_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataArgSent()
{
   if (_deleteSubsData_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deleteSubsData_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataArgRecvd()
{
   if (_deleteSubsData_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deleteSubsData_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataResRecvd()
{
   if (_deleteSubsData_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deleteSubsData_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataResSent()
{
   if (_deleteSubsData_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deleteSubsData_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataTimeOut()
{
   if (_deleteSubsData_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deleteSubsData_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataErrorRecvd()
{
   if (_deleteSubsData_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deleteSubsData_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataErrorSent()
{
   if (_deleteSubsData_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deleteSubsData_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeleteSubsDataOtherError()
{
   if (_deleteSubsData_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deleteSubsData_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationArgSent()
{
   if (_cancellocation_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _cancellocation_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationArgRecvd()
{
   if (_cancellocation_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _cancellocation_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationResRecvd()
{
   if (_cancellocation_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _cancellocation_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationResSent()
{
   if (_cancellocation_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _cancellocation_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationTimeOut()
{
   if (_cancellocation_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _cancellocation_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationErrorRecvd()
{
   if (_cancellocation_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _cancellocation_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationErrorSent()
{
   if (_cancellocation_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _cancellocation_error_sent++;
   _total_number_error_sent++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::CancelLocationOtherError()
{
   if (_cancellocation_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _cancellocation_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeArgSent()
{
   if (_activatetracemode_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _activatetracemode_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeArgRecvd()
{
   if (_activatetracemode_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _activatetracemode_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeResRecvd()
{
   if (_activatetracemode_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _activatetracemode_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeResSent()
{
   if (_activatetracemode_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _activatetracemode_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeTimeOut()
{
   if (_activatetracemode_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _activatetracemode_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeErrorRecvd()
{
   if (_activatetracemode_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _activatetracemode_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeErrorSent()
{
   if (_activatetracemode_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _activatetracemode_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ActivateTraceModeOtherError()
{
   if (_activatetracemode_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _activatetracemode_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeArgSent()
{
   if (_deactivatetracemode_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deactivatetracemode_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeArgRecvd()
{
   if (_deactivatetracemode_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deactivatetracemode_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeResRecvd()
{
   if (_deactivatetracemode_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deactivatetracemode_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeResSent()
{
   if (_deactivatetracemode_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _deactivatetracemode_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeTimeOut()
{
   if (_deactivatetracemode_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deactivatetracemode_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeErrorRecvd()
{
   if (_deactivatetracemode_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deactivatetracemode_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeErrorSent()
{
   if (_deactivatetracemode_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deactivatetracemode_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::DeActivateTraceModeOtherError()
{
   if (_deactivatetracemode_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _deactivatetracemode_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataArgSent()
{
   if (_provideSubsData_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _provideSubsData_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataArgRecvd()
{
   if (_provideSubsData_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _provideSubsData_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataResRecvd()
{
   if (_provideSubsData_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _provideSubsData_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataResSent()
{
   if (_provideSubsData_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _provideSubsData_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataTimeOut()
{
   if (_provideSubsData_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _provideSubsData_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataErrorRecvd()
{
   if (_provideSubsData_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _provideSubsData_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataErrorSent()
{
   if (_provideSubsData_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _provideSubsData_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ProvideSubsDataOtherError()
{
   if (_provideSubsData_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _provideSubsData_other_error++;
   _total_number_other_error++;
   Unlock();
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetArgSent()
{
   if (_reset_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _reset_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetArgRecvd()
{
   if (_reset_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _reset_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetResRecvd()
{
   if (_reset_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _reset_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetResSent()
{
   if (_reset_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _reset_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetTimeOut()
{
   if (_reset_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _reset_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetErrorRecvd()
{
   if (_reset_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _reset_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetErrorSent()
{
   if (_reset_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _reset_error_sent++;
   _total_number_error_sent++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetOtherError()
{
   if (_reset_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _reset_other_error++;
   _total_number_other_error++;
   Unlock();
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMArgSent()
{
   if (_readyforsm_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _readyforsm_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMArgRecvd()
{
   if (_readyforsm_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _readyforsm_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Res Rcvd peg
 *             when RETURN_RESULT is recvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMResRecvd()
{
   if (_readyforsm_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _readyforsm_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments the Any Time Argument Arg Sent peg
 *        when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMResSent()
{
   if (_readyforsm_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _readyforsm_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation TimeOut peg
 *        when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMTimeOut()
{
   if (_readyforsm_timeout > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _readyforsm_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMErrorRecvd()
{
   if (_readyforsm_error_rcvd > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _readyforsm_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMErrorSent()
{
   if (_readyforsm_error_sent > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _readyforsm_error_sent++;
   _total_number_error_sent++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Any Time Interrogation Error peg
 *             when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ReadyForSMOtherError()
{
   if (_readyforsm_other_error > MAX_STAT_VAL)
   {
       clearstatistics();
   }
   Lock();
   _readyforsm_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Arg Sent peg
 *             when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSArgSent()
{
   if (_routingInfoForGPRS_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Arg Sent peg
 *             when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSArgRecvd()
{
   if (_routingInfoForGPRS_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Res Recvd peg
 *        when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSResRecvd()
{
   if (_routingInfoForGPRS_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Res Recvd peg
 *        when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSResSent()
{
   if (_routingInfoForGPRS_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS TimeOut peg
 *            when L_CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSTimeOut()
{
   if (_routingInfoForGPRS_timeout > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Error  peg
 *            RETURN_ERROR     is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSErrorRecvd()
{
   if (_routingInfoForGPRS_error_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Error  peg
 *            RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSErrorSent()
{
   if (_routingInfoForGPRS_error_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_error_sent++;
   _total_number_error_sent++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Routing Info For LCS Error  peg
 *            RETURN_REJECT/ABORT/NOTICE     is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RoutingInfoForGPRSOtherError()
{
   if (_routingInfoForGPRS_other_error > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _routingInfoForGPRS_other_error++;
   _total_number_other_error++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Arg Sent  peg
 *        when INVOKE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationArgSent()
{
   if (_updateGprsLocation_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Arg Sent  peg
 *        when INVOKE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationArgRecvd()
{
   if (_updateGprsLocation_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Res Recvd  peg
 *        when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationResRecvd()
{
   if (_updateGprsLocation_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Res Recvd  peg
 *        when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationResSent()
{
   if (_updateGprsLocation_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location TimeOut  peg
 *        CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationTimeOut()
{
   if (_updateGprsLocation_timeout > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Error  peg
 *            when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationErrorRecvd()
{
   if (_updateGprsLocation_error_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Error  peg
 *            when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationErrorSent()
{
   if (_updateGprsLocation_error_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_error_sent++;
   _total_number_error_sent++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Other Error  peg
 *            when RETURN_REJECT/ABORT/NOTICE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::UpdateGprsLocationOtherError()
{
   if (_updateGprsLocation_other_error > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _updateGprsLocation_other_error++;
   _total_number_other_error++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Arg Sent  peg
 *        when INVOKE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSArgSent()
{
   if (_purgems_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Arg Sent  peg
 *        when INVOKE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSArgRecvd()
{
   if (_purgems_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Res Recvd  peg
 *        when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSResRecvd()
{
   if (_purgems_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Res Recvd  peg
 *        when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSResSent()
{
   if (_purgems_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location TimeOut  peg
 *        CANCEL is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSTimeOut()
{
   if (_purgems_timeout > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Error  peg
 *            when RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSErrorRecvd()
{
   if (_purgems_error_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Error  peg
 *            when RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSErrorSent()
{
   if (_purgems_error_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments Provide Subscriber Location Other Error  peg
 *            when RETURN_REJECT/ABORT/NOTICE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::PurgeMSOtherError()
{
   if (_purgems_other_error > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _purgems_other_error++;
   _total_number_other_error++;
   Unlock();
}
/*
 ****************************************************************************
 *  Purpose: increments RestoreData Arg Sent peg
 *            when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataArgSent()
{
   if (_restoreData_arg_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_arg_sent++;
   _total_number_msg_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Arg Sent peg
 *            when INVOKE to be sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataArgRecvd()
{
   if (_restoreData_arg_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_arg_rcvd++;
   _total_number_msg_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Res Recvd peg
 *                  when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataResRecvd()
{
   if (_restoreData_res_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_res_rcvd++;
   _total_number_res_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Res Recvd peg
 *                  when RETURN_RESULT is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataResSent()
{
   if (_restoreData_res_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_res_sent++;
   _total_number_res_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Timeout peg
 *            when CANCLE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataTimeOut()
{
   if (_restoreData_timeout > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_timeout++;
   _total_number_timeout++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Error peg
 *        when     RETURN_ERROR is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataErrorRecvd()
{
   if (_restoreData_error_rcvd > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_error_rcvd++;
   _total_number_error_rcvd++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Error peg
 *        when     RETURN_ERROR is sent
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataErrorSent()
{
   if (_restoreData_error_sent > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_error_sent++;
   _total_number_error_sent++;
   Unlock();
}

/*
 ****************************************************************************
 *  Purpose: increments RestoreData Error peg
 *        when RETURN_REJECT/ABORT/NOTICE is rcvd
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::RestoreDataOtherError()
{
   if (_restoreData_other_error > MAX_STAT_VAL)
   {
      clearstatistics();
   }
   Lock();
   _restoreData_other_error++;
   _total_number_other_error++;
   Unlock();
}

void SsgStackStatistics::InitialDPArgRecvd()
{
    if (_initialdp_arg_rcvd > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _initialdp_arg_rcvd++;
    _total_number_msg_rcvd++;
    Unlock();

}

void SsgStackStatistics::InitialDPSMSArgRecvd()
{
    if (_initialdpsms_arg_rcvd > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _initialdpsms_arg_rcvd++;
    _total_number_msg_rcvd++;
    Unlock();

}

void SsgStackStatistics::EventReportBCSMArgRecvd()
{
    if (_eventreportbcsm_arg_rcvd > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _eventreportbcsm_arg_rcvd++;
    _total_number_msg_rcvd++;
    Unlock();

}

void SsgStackStatistics::EventReportSMSArgRecvd()
{
    if (_eventreportsms_arg_rcvd > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _eventreportsms_arg_rcvd++;
    _total_number_msg_rcvd++;
    Unlock();

}

void SsgStackStatistics::ApplyChargingReportArgRecvd()
{
    if (_applychargingreport_arg_rcvd > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _applychargingreport_arg_rcvd++;
    _total_number_msg_rcvd++;
    Unlock();

}

void SsgStackStatistics::RequestReportBCSMEventArgSent()
{
    if (_requestreportbcsmevent_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _requestreportbcsmevent_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::RequestReportSMSEventArgSent()
{
    if (_requestreportsmsevent_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _requestreportsmsevent_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ApplyChargingArgSent()
{
    if (_applycharging_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _applycharging_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ConnectArgSent()
{
    if (_connect_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _connect_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ContinueArgSent()
{
    if (_continue_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _continue_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ContinueSMSArgSent()
{
    if (_continue_sms_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _continue_sms_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ReleaseArgSent()
{
    if (_release_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _release_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ReleaseSMSArgSent()
{
    if (_release_sms_arg_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _release_sms_arg_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ActivityTestSent()
{
    if (_activity_test_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _activity_test_sent++;
    _total_number_msg_sent++;
    Unlock();

}

void SsgStackStatistics::ActivityRespRecvd()
{
    if (_activity_resp_rcvd > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _activity_resp_rcvd++;
    _total_number_msg_rcvd++;
    Unlock();

}

void SsgStackStatistics::NumberofTcapComponentsSent()
{
    if (_number_of_tcap_components_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _number_of_tcap_components_sent++;
    Unlock();
}

void SsgStackStatistics::IncrementCurrentActiveSubscriberCount()
{
    if (_number_of_current_active_subscriber > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _number_of_current_active_subscriber++;
    Unlock();
}

void SsgStackStatistics::DecrementCurrentActiveSubscriberCount()
{
    if(_number_of_current_active_subscriber > 0)
    {
        Lock();
        _number_of_current_active_subscriber--;
        Unlock();
    }
}

void SsgStackStatistics::NumberofTcapComponentsReceived()
{
    if (_number_of_tcap_components_received > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _number_of_tcap_components_received++;
    Unlock();
}

void SsgStackStatistics::NumberofTcapErrorComponentsSent()
{
    if (_number_of_tcap_error_components_sent > MAX_STAT_VAL)
    {
        clearstatistics();
    }
    Lock();
    _number_of_tcap_error_components_sent++;
    _total_number_error_sent = _number_of_tcap_error_components_sent;
    Unlock();
}
/*
 ****************************************************************************
 *  Purpose: resets all the statistcs
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::ResetAll()
{
   clearstatistics();
}

/*
 ****************************************************************************
 *  Purpose: prints all the statistcs
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
 *  See Also:
 ****************************************************************************/
void SsgStackStatistics::Print(std::ostream& os)
{
   struct timeval ts;
   time_t curtime;
   char buffer[30];
   gettimeofday(&ts, NULL);
   curtime=ts.tv_sec;
   strftime(buffer,30,"%m-%d-%Y  %T",localtime(&curtime));

   os << "----------------------------------------------------------------------------------------" << endl;
   os << " -- Tcap Msg Stats -- at " <<  buffer  << endl;
   os << "----------------------------------------------------------------------------------------" << endl;
   os << " Message    : ArgOut  |  ArgIn  |  ResIn  |  ResOut  |  ErrIn  |  ErrOut  |  TimeOut  |  OthrErr  |" << endl;
   os << "----------------------------------------------------------------------------------------" << endl;

   os << " SAI 	    : "<< setw(8)<< _sendAuthInfo_arg_sent<<"|"
                         << setw(8)<< _sendAuthInfo_arg_rcvd<<"|"
                         << setw(8)<< _sendAuthInfo_res_rcvd<<"|"
                         << setw(8)<< _sendAuthInfo_res_sent<<"|"
                         << setw(8)<< _sendAuthInfo_error_rcvd<< "|"
                         << setw(8)<< _sendAuthInfo_error_sent<< "|"
                         << setw(8)<< _sendAuthInfo_timeout<<"|"
                         << setw(8)<< _sendAuthInfo_other_error<<"|"<<endl;

   os << " RTI-GPRS   : "<< setw(8)<< _routingInfoForGPRS_arg_sent<<"|"
                         << setw(8)<< _routingInfoForGPRS_arg_rcvd<<"|"
                         << setw(8)<< _routingInfoForGPRS_res_rcvd<<"|"
                         << setw(8)<< _routingInfoForGPRS_res_sent<<"|"
                         << setw(8)<< _routingInfoForGPRS_error_rcvd<< "|"
                         << setw(8)<< _routingInfoForGPRS_error_sent<< "|"
                         << setw(8)<< _routingInfoForGPRS_timeout<<"|"
                         << setw(8)<< _routingInfoForGPRS_other_error<<"|"<<endl;

   os << " UGL        : "<< setw(8)<< _updateGprsLocation_arg_sent<<"|"
                         << setw(8)<< _updateGprsLocation_arg_rcvd<<"|"
                         << setw(8)<< _updateGprsLocation_res_rcvd<<"|"
                         << setw(8)<< _updateGprsLocation_res_sent<<"|"
                         << setw(8)<< _updateGprsLocation_error_rcvd<< "|"
                         << setw(8)<< _updateGprsLocation_error_sent<< "|"
                         << setw(8)<< _updateGprsLocation_timeout<<"|"
                         << setw(8)<< _updateGprsLocation_other_error<<"|"<<endl;

   os << " ReadyForSM : "<< setw(8)<< _readyforsm_arg_sent<<"|"
                         << setw(8)<< _readyforsm_arg_rcvd<<"|"
                         << setw(8)<< _readyforsm_res_rcvd<<"|"
                         << setw(8)<< _readyforsm_res_sent<<"|"
                         << setw(8)<< _readyforsm_error_rcvd<< "|"
                         << setw(8)<< _readyforsm_error_sent<< "|"
                         << setw(8)<< _readyforsm_timeout<<"|"
                         << setw(8)<< _readyforsm_other_error<<"|"<<endl;

   os << " PurgeMS    : "<< setw(8)<< _purgems_arg_sent<<"|"
                         << setw(8)<< _purgems_arg_rcvd<<"|"
                         << setw(8)<< _purgems_res_rcvd<<"|"
                         << setw(8)<< _purgems_res_sent<<"|"
                         << setw(8)<< _purgems_error_rcvd<< "|"
                         << setw(8)<< _purgems_error_sent<< "|"
                         << setw(8)<< _purgems_timeout<<"|"
                         << setw(8)<< _purgems_other_error<<"|"<<endl;

   os << " ProSubData : "<< setw(8)<< _provideSubsData_arg_sent<<"|"
                         << setw(8)<< _provideSubsData_arg_rcvd<<"|"
                         << setw(8)<< _provideSubsData_res_rcvd<<"|"
                         << setw(8)<< _provideSubsData_res_sent<<"|"
                         << setw(8)<< _provideSubsData_error_rcvd<< "|"
                         << setw(8)<< _provideSubsData_error_sent<< "|"
                         << setw(8)<< _provideSubsData_timeout<<"|"
                         << setw(8)<< _provideSubsData_other_error<<"|"<<endl;

   os << " InsSubData : "<< setw(8)<< _insertSubsData_arg_sent<<"|"
                         << setw(8)<< _insertSubsData_arg_rcvd<<"|"
                         << setw(8)<< _insertSubsData_res_rcvd<<"|"
                         << setw(8)<< _insertSubsData_res_sent<<"|"
                         << setw(8)<< _insertSubsData_error_rcvd<< "|"
                         << setw(8)<< _insertSubsData_error_sent<< "|"
                         << setw(8)<< _insertSubsData_timeout<<"|"
                         << setw(8)<< _insertSubsData_other_error<<"|"<<endl;

   os << " DelSubData : "<< setw(8)<< _deleteSubsData_arg_sent<<"|"
                         << setw(8)<< _deleteSubsData_arg_rcvd<<"|"
                         << setw(8)<< _deleteSubsData_res_rcvd<<"|"
                         << setw(8)<< _deleteSubsData_res_sent<<"|"
                         << setw(8)<< _deleteSubsData_error_rcvd<< "|"
                         << setw(8)<< _deleteSubsData_error_sent<< "|"
                         << setw(8)<< _deleteSubsData_timeout<<"|"
                         << setw(8)<< _deleteSubsData_other_error<<"|"<<endl;

   os << " CancelLoca : "<< setw(8)<< _cancellocation_arg_sent<<"|"
                         << setw(8)<< _cancellocation_arg_rcvd<<"|"
                         << setw(8)<< _cancellocation_res_rcvd<<"|"
                         << setw(8)<< _cancellocation_res_sent<<"|"
                         << setw(8)<< _cancellocation_error_rcvd<< "|"
                         << setw(8)<< _cancellocation_error_sent<< "|"
                         << setw(8)<< _cancellocation_timeout<<"|"
                         << setw(8)<< _cancellocation_other_error<<"|"<<endl;

   os << " Reset      : "<< setw(8)<< _reset_arg_sent<<"|"
                         << setw(8)<< _reset_arg_rcvd<<"|"
                         << setw(8)<< _reset_res_rcvd<<"|"
                         << setw(8)<< _reset_res_sent<<"|"
                         << setw(8)<< _reset_error_rcvd<< "|"
                         << setw(8)<< _reset_error_sent<< "|"
                         << setw(8)<< _reset_timeout<<"|"
                         << setw(8)<< _reset_other_error<<"|"<<endl;

   os << " ActTraMode : "<< setw(8)<< _activatetracemode_arg_sent<<"|"
                         << setw(8)<< _activatetracemode_arg_rcvd<<"|"
                         << setw(8)<< _activatetracemode_res_rcvd<<"|"
                         << setw(8)<< _activatetracemode_res_sent<<"|"
                         << setw(8)<< _activatetracemode_error_rcvd<< "|"
                         << setw(8)<< _activatetracemode_error_sent<< "|"
                         << setw(8)<< _activatetracemode_timeout<<"|"
                         << setw(8)<< _activatetracemode_other_error<<"|"<<endl;

   os << " DeAcTraMode: "<< setw(8)<< _deactivatetracemode_arg_sent<<"|"
                         << setw(8)<< _deactivatetracemode_arg_rcvd<<"|"
                         << setw(8)<< _deactivatetracemode_res_rcvd<<"|"
                         << setw(8)<< _deactivatetracemode_res_sent<<"|"
                         << setw(8)<< _deactivatetracemode_error_rcvd<< "|"
                         << setw(8)<< _deactivatetracemode_error_sent<< "|"
                         << setw(8)<< _deactivatetracemode_timeout<<"|"
                         << setw(8)<< _deactivatetracemode_other_error<<"|"<<endl;

   os << " RD         : "<< setw(8)<< _restoreData_arg_sent<<"|"
                         << setw(8)<< _restoreData_arg_rcvd<<"|"
                         << setw(8)<< _restoreData_res_rcvd<<"|"
                         << setw(8)<< _restoreData_res_sent<<"|"
                         << setw(8)<< _restoreData_error_rcvd<< "|"
                         << setw(8)<< _restoreData_error_sent<< "|"
                         << setw(8)<< _restoreData_timeout<<"|"
                         << setw(8)<< _restoreData_other_error<<"|"<<endl;

   os << " IDP        : "<< setw(8)<< "-" <<"|"
                         << setw(8)<< _initialdp_arg_rcvd <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " RRBCSM     : "<< setw(8)<< _requestreportbcsmevent_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ACH        : "<< setw(8)<< _applycharging_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " Continue   : "<< setw(8)<< _continue_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " Connect    : "<< setw(8)<< _connect_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ERBCSM     : "<< setw(8)<< "-" <<"|"
                         << setw(8)<< _eventreportbcsm_arg_rcvd <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ACR        : "<< setw(8)<< "-" <<"|"
                         << setw(8)<< _applychargingreport_arg_rcvd <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " REL        : "<< setw(8)<<  _release_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " IDPSMS     : "<< setw(8)<< "-" <<"|"
                         << setw(8)<< _initialdpsms_arg_rcvd <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " RRSMS      : "<< setw(8)<< _requestreportsmsevent_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ContSMS    : "<< setw(8)<< _continue_sms_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ERSMS      : "<< setw(8)<< "-" <<"|"
                         << setw(8)<< _eventreportsms_arg_rcvd <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " RELSMS     : "<< setw(8)<<  _release_sms_arg_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ActTest    : "<< setw(8)<<  _activity_test_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " ActResp    : "<< setw(8)<< "-" <<"|"
                         << setw(8)<< _activity_resp_rcvd <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " Total      : "<< setw(8)<< _total_number_msg_sent<<"|"
                         << setw(8)<< _total_number_msg_rcvd<<"|"
                         << setw(8)<< _total_number_res_rcvd<<"|"
                         << setw(8)<< _total_number_res_sent<<"|"
                         << setw(8)<< _total_number_error_rcvd<< "|"
                         << setw(8)<< _total_number_error_sent<< "|"
                         << setw(8)<< _total_number_timeout<<"|"
                         << setw(8)<< _total_number_other_error<<"|"<<endl;
   os << "----------------------------------------------------------------------------------------" << endl;

   os << " TcComp Rcvd: "<< setw(8)<< "-" <<"|"
                         << setw(8)<<  _number_of_tcap_components_received <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;

   os << " TcComp Sent: "<< setw(8)<<  _number_of_tcap_components_sent <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"
                         << setw(8)<< "-" <<"|"<<endl;
   os << "----------------------------------------------------------------------------------------" << endl;

}

void SsgStackStatistics::PrintActiveSubscribers(std::ostream& os)
{
    os << " Current Active Subscribers      : " << _number_of_current_active_subscriber << endl;
}
