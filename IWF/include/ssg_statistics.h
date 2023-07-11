/*********************************-*--H--*-**********************************
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
 *  ID: $Id: ssg_statistics.h,v 1.1.1.1.2.2.2.2.2.1.6.1.8.5 2020/04/23 13:45:37 jkchaitanya Exp $
 *
 *  LOG: $Log: ssg_statistics.h,v $
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1.6.1.8.5  2020/04/23 13:45:37  jkchaitanya
 *  LOG: added Actitivy test stats
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1.6.1.8.4  2015/03/03 14:32:50  mhimanshu
 *  LOG: Changes done as part of bug 6361 fix, Review 3702
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1.6.1.8.3  2014/12/03 09:21:38  mhimanshu
 *  LOG: stats implementation at MML - diaS6aStats and activeSubscribers
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1.6.1.8.2  2014/12/02 12:39:01  jkchaitanya
 *  LOG: changes for stats enhancement for TcapError count for all the translators
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1.6.1.8.1  2014/12/02 05:44:50  jkchaitanya
 *  LOG: changes for updating stats for incomming components
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1.6.1  2014/04/07 04:48:09  jkchaitanya
 *  LOG: changes for stats update for connect message
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2.2.1  2014/01/23 09:51:20  jkchaitanya
 *  LOG: changes for merging iwf code from poc to productization
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.2  2013/10/04 13:48:37  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2.2.1  2013/09/06 11:43:06  jkchaitanya
 *  LOG: changes for IWF stats for cap-ro messages
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.2  2013/06/19 12:40:52  jsarvesh
 *  LOG: MML implementation for IWF Statistics
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/05/20 08:56:41  jvikram
 *  LOG: Corrected Coverity Issues
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:35  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 ****************************************************************************/
#ident "$Id: ssg_statistics.h,v 1.1.1.1.2.2.2.2.2.1.6.1.8.5 2020/04/23 13:45:37 jkchaitanya Exp $"

#if !defined(_SSG_STATS_H)
#define _SSG_STATS_H

#include <its++.h>
#include <iostream>
#include <its_mutex.h>

#if defined(ITS_STD_NAMESPACE)
#ifdef GCC_LESS_THAN_4_3
#include <map>
using namespace std;
#else
using namespace std;
#endif
using namespace its;
#endif

#define  MAX_STAT_VAL 0x80000000

/** Interface:
 *      Abstract SsgStats Class
 *
 *  Purpose:
 *      SsgStats class forms the Base Class to encapsulate all Ssg stack
 *      pegs and statistics. Individual Modules inherit from this base class
 *      and implement their layer specific pegs and statistics.
 **/
class SsgStats
{

public:
    SsgStats()
        :lock(0),
        _total_number_msg_sent(0),
        _total_number_msg_rcvd(0),
        _total_number_res_rcvd(0),
        _total_number_res_sent(0),
        _total_number_error_rcvd(0),
        _total_number_error_sent(0),
        _total_number_timeout(0),
        _total_number_other_error(0)
        {}

    virtual ~SsgStats(){}

    virtual void Print(std::ostream& os)= 0;

    virtual void ResetAll()  = 0;

    void Lock() const
    {
       int res = const_cast<its::ITS_Mutex&>(lock).Acquire();
       if (res != ITS_SUCCESS)
       {
          ITS_THROW_ERROR(res);
       }
    }


    void Unlock() const
    {
       int res = const_cast<its::ITS_Mutex&>(lock).Release();
       if (res != ITS_SUCCESS)
       {
          ITS_THROW_ERROR(res);
       }
    }

protected:
    its::ITS_Mutex lock;
    ITS_UINT _total_number_msg_sent;
    ITS_UINT _total_number_msg_rcvd;
    ITS_UINT _total_number_res_rcvd;
    ITS_UINT _total_number_res_sent;
    ITS_UINT _total_number_error_rcvd;
    ITS_UINT _total_number_error_sent;
    ITS_UINT _total_number_timeout;
    ITS_UINT _total_number_other_error;

private:

};

class SsgStackStatistics;
extern SsgStackStatistics ssgStats;

// Statistics Table
class SsgStackStatistics: public SsgStats
{
public:
    SsgStackStatistics()
    {
       _sendAuthInfo_arg_rcvd       =0;
       _sendAuthInfo_arg_sent       =0;
       _sendAuthInfo_res_rcvd       =0;
       _sendAuthInfo_res_sent       =0;
       _sendAuthInfo_error_rcvd     =0;
       _sendAuthInfo_error_sent     =0;
       _sendAuthInfo_timeout        =0;
       _sendAuthInfo_other_error    =0;    // RR/RE/Abort case


       _routingInfoForGPRS_arg_sent          =0;
       _routingInfoForGPRS_arg_rcvd          =0;
       _routingInfoForGPRS_res_rcvd          =0;
       _routingInfoForGPRS_res_sent          =0;
       _routingInfoForGPRS_error_rcvd        =0;
       _routingInfoForGPRS_error_sent        =0;
       _routingInfoForGPRS_timeout           =0;
       _routingInfoForGPRS_other_error       =0;    // RR/RE/Abort case

       _updateGprsLocation_arg_sent    =0;
       _updateGprsLocation_arg_rcvd    =0;
       _updateGprsLocation_res_rcvd    =0;
       _updateGprsLocation_res_sent    =0;
       _updateGprsLocation_error_rcvd  =0;
       _updateGprsLocation_error_sent  =0;
       _updateGprsLocation_timeout     =0;
       _updateGprsLocation_other_error =0;    // RR/RE/Abort case

       _purgems_arg_sent    =0;
       _purgems_arg_rcvd    =0;
       _purgems_res_rcvd    =0;
       _purgems_res_sent    =0;
       _purgems_error_rcvd  =0;
       _purgems_error_sent  =0;
       _purgems_timeout     =0;
       _purgems_other_error =0;    // RR/RE/Abort case

       _restoreData_arg_sent            =0;
       _restoreData_arg_rcvd            =0;
       _restoreData_res_rcvd            =0;
       _restoreData_res_sent            =0;
       _restoreData_error_rcvd          =0;
       _restoreData_error_sent          =0;
       _restoreData_timeout             =0;
       _restoreData_other_error         =0;

       _insertSubsData_arg_sent         =0;
       _insertSubsData_arg_rcvd         =0;
       _insertSubsData_res_rcvd         =0;
       _insertSubsData_res_sent         =0;
       _insertSubsData_error_rcvd       =0;
       _insertSubsData_error_sent       =0;
       _insertSubsData_timeout          =0;
       _insertSubsData_other_error      =0;    // RR/RE/Abort case

       _deleteSubsData_arg_sent         =0;
       _deleteSubsData_arg_rcvd         =0;
       _deleteSubsData_res_rcvd         =0;
       _deleteSubsData_res_sent         =0;
       _deleteSubsData_error_rcvd       =0;
       _deleteSubsData_error_sent       =0;
       _deleteSubsData_timeout          =0;
       _deleteSubsData_other_error      =0;    // RR/RE/Abort case

       _provideSubsData_arg_sent    =0;
       _provideSubsData_arg_rcvd    =0;
       _provideSubsData_res_rcvd    =0;
       _provideSubsData_res_sent    =0;
       _provideSubsData_error_rcvd  =0;
       _provideSubsData_error_sent  =0;
       _provideSubsData_timeout     =0;
       _provideSubsData_other_error =0;    // RR/RE/Abort case

       _reset_arg_sent    =0;
       _reset_arg_rcvd    =0;
       _reset_res_rcvd    =0;
       _reset_res_sent    =0;
       _reset_error_rcvd  =0;
       _reset_error_sent  =0;
       _reset_timeout     =0;
       _reset_other_error =0;    // RR/RE/Abort case

       _cancellocation_arg_sent    =0;
       _cancellocation_arg_rcvd    =0;
       _cancellocation_res_rcvd    =0;
       _cancellocation_res_sent    =0;
       _cancellocation_error_rcvd  =0;
       _cancellocation_error_sent  =0;
       _cancellocation_timeout     =0;
       _cancellocation_other_error =0;    // RR/RE/Abort case

       _activatetracemode_arg_sent    =0;
       _activatetracemode_arg_rcvd    =0;
       _activatetracemode_res_rcvd    =0;
       _activatetracemode_res_sent    =0;
       _activatetracemode_error_rcvd  =0;
       _activatetracemode_error_sent  =0;
       _activatetracemode_timeout     =0;
       _activatetracemode_other_error =0;    // RR/RE/Abort case

       _deactivatetracemode_arg_sent    =0;
       _deactivatetracemode_arg_rcvd    =0;
       _deactivatetracemode_res_rcvd    =0;
       _deactivatetracemode_res_sent    =0;
       _deactivatetracemode_error_rcvd  =0;
       _deactivatetracemode_error_sent  =0;
       _deactivatetracemode_timeout     =0;
       _deactivatetracemode_other_error =0;    // RR/RE/Abort case

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
    _activity_test_sent		            = 0;
    _activity_resp_rcvd 		    = 0;

       _number_of_tcap_components_sent      = 0;
       _number_of_tcap_components_received  = 0;
       _number_of_tcap_error_components_sent = 0;
       _number_of_current_active_subscriber = 0;
    }

    ~SsgStackStatistics()
    {
    };

    void clearstatistics();
    void SendAuthInfoArgSent();
    void SendAuthInfoArgRecvd();
    void SendAuthInfoResRecvd();
    void SendAuthInfoResSent();
    void SendAuthInfoTimeOut();
    void SendAuthInfoErrorRecvd();
    void SendAuthInfoErrorSent();
    void SendAuthInfoOtherError();
    void RoutingInfoForGPRSArgSent();
    void RoutingInfoForGPRSArgRecvd();
    void RoutingInfoForGPRSResRecvd();
    void RoutingInfoForGPRSResSent();
    void RoutingInfoForGPRSTimeOut();
    void RoutingInfoForGPRSErrorRecvd();
    void RoutingInfoForGPRSErrorSent();
    void RoutingInfoForGPRSOtherError();
    void UpdateGprsLocationArgSent();
    void UpdateGprsLocationArgRecvd();
    void UpdateGprsLocationResRecvd();
    void UpdateGprsLocationResSent();
    void UpdateGprsLocationTimeOut();
    void UpdateGprsLocationErrorRecvd();
    void UpdateGprsLocationErrorSent();
    void UpdateGprsLocationOtherError();
    void ReadyForSMArgSent();
    void ReadyForSMArgRecvd();
    void ReadyForSMResRecvd();
    void ReadyForSMResSent();
    void ReadyForSMTimeOut();
    void ReadyForSMErrorRecvd();
    void ReadyForSMErrorSent();
    void ReadyForSMOtherError();
    void ActivateTraceModeArgSent();
    void ActivateTraceModeArgRecvd();
    void ActivateTraceModeResRecvd();
    void ActivateTraceModeResSent();
    void ActivateTraceModeTimeOut();
    void ActivateTraceModeErrorRecvd();
    void ActivateTraceModeErrorSent();
    void ActivateTraceModeOtherError();
    void DeActivateTraceModeArgSent();
    void DeActivateTraceModeArgRecvd();
    void DeActivateTraceModeResRecvd();
    void DeActivateTraceModeResSent();
    void DeActivateTraceModeTimeOut();
    void DeActivateTraceModeErrorRecvd();
    void DeActivateTraceModeErrorSent();
    void DeActivateTraceModeOtherError();
    void ResetArgSent();
    void ResetArgRecvd();
    void ResetResRecvd();
    void ResetResSent();
    void ResetTimeOut();
    void ResetErrorRecvd();
    void ResetErrorSent();
    void ResetOtherError();
    void PurgeMSArgSent();
    void PurgeMSArgRecvd();
    void PurgeMSResRecvd();
    void PurgeMSResSent();
    void PurgeMSTimeOut();
    void PurgeMSErrorRecvd();
    void PurgeMSErrorSent();
    void PurgeMSOtherError();
    void RestoreDataArgSent();
    void RestoreDataArgRecvd();
    void RestoreDataResRecvd();
    void RestoreDataResSent();
    void RestoreDataTimeOut();
    void RestoreDataErrorRecvd();
    void RestoreDataErrorSent();
    void RestoreDataOtherError();
    void InsertSubsDataArgSent();
    void InsertSubsDataArgRecvd();
    void InsertSubsDataResRecvd();
    void InsertSubsDataResSent();
    void InsertSubsDataTimeOut();
    void InsertSubsDataErrorRecvd();
    void InsertSubsDataErrorSent();
    void InsertSubsDataOtherError();
    void DeleteSubsDataArgSent();
    void DeleteSubsDataArgRecvd();
    void DeleteSubsDataResRecvd();
    void DeleteSubsDataResSent();
    void DeleteSubsDataTimeOut();
    void DeleteSubsDataErrorRecvd();
    void DeleteSubsDataErrorSent();
    void DeleteSubsDataOtherError();
    void ProvideSubsDataArgSent();
    void ProvideSubsDataArgRecvd();
    void ProvideSubsDataResRecvd();
    void ProvideSubsDataResSent();
    void ProvideSubsDataTimeOut();
    void ProvideSubsDataErrorRecvd();
    void ProvideSubsDataErrorSent();
    void ProvideSubsDataOtherError();
    void CancelLocationArgSent();
    void CancelLocationArgRecvd();
    void CancelLocationResRecvd();
    void CancelLocationResSent();
    void CancelLocationTimeOut();
    void CancelLocationErrorRecvd();
    void CancelLocationErrorSent();
    void CancelLocationOtherError();
    void InitialDPArgRecvd();
    void InitialDPSMSArgRecvd();
    void EventReportBCSMArgRecvd();
    void EventReportSMSArgRecvd();
    void ApplyChargingReportArgRecvd();
    void RequestReportBCSMEventArgSent();
    void RequestReportSMSEventArgSent();
    void ApplyChargingArgSent();
    void ContinueArgSent();
    void ConnectArgSent();
    void ContinueSMSArgSent();
    void ReleaseArgSent();
    void ReleaseSMSArgSent();
    void ActivityTestSent();
    void ActivityRespRecvd();
    void NumberofTcapComponentsSent();
    void NumberofTcapComponentsReceived();
    void NumberofTcapErrorComponentsSent();
    void ResetAll();
    void Print(std::ostream& os);
    void PrintActiveSubscribers(std::ostream& os);
    void IncrementCurrentActiveSubscriberCount();
    void DecrementCurrentActiveSubscriberCount();

protected:

    ITS_UINT _sendAuthInfo_arg_sent;
    ITS_UINT _sendAuthInfo_arg_rcvd;
    ITS_UINT _sendAuthInfo_res_rcvd;
    ITS_UINT _sendAuthInfo_res_sent;
    ITS_UINT _sendAuthInfo_error_rcvd;
    ITS_UINT _sendAuthInfo_error_sent;
    ITS_UINT _sendAuthInfo_timeout;
    ITS_UINT _sendAuthInfo_other_error;      // RR/RE/Abort case

    ITS_UINT _routingInfoForGPRS_arg_sent;
    ITS_UINT _routingInfoForGPRS_arg_rcvd;
    ITS_UINT _routingInfoForGPRS_res_rcvd;
    ITS_UINT _routingInfoForGPRS_res_sent;
    ITS_UINT _routingInfoForGPRS_error_rcvd;
    ITS_UINT _routingInfoForGPRS_error_sent;
    ITS_UINT _routingInfoForGPRS_timeout;
    ITS_UINT _routingInfoForGPRS_other_error;  	     // RR/RE/Abort  case

    ITS_UINT _updateGprsLocation_arg_sent;
    ITS_UINT _updateGprsLocation_arg_rcvd;
    ITS_UINT _updateGprsLocation_res_rcvd;
    ITS_UINT _updateGprsLocation_res_sent;
    ITS_UINT _updateGprsLocation_error_rcvd;
    ITS_UINT _updateGprsLocation_error_sent;
    ITS_UINT _updateGprsLocation_timeout;
    ITS_UINT _updateGprsLocation_other_error; // RR/RE/Abort case

    ITS_UINT _readyforsm_arg_sent;
    ITS_UINT _readyforsm_arg_rcvd;
    ITS_UINT _readyforsm_res_rcvd;
    ITS_UINT _readyforsm_res_sent;
    ITS_UINT _readyforsm_error_rcvd;
    ITS_UINT _readyforsm_error_sent;
    ITS_UINT _readyforsm_timeout;
    ITS_UINT _readyforsm_other_error;      // RR/RE/Abort case

    ITS_UINT _purgems_arg_sent;
    ITS_UINT _purgems_arg_rcvd;
    ITS_UINT _purgems_res_rcvd;
    ITS_UINT _purgems_res_sent;
    ITS_UINT _purgems_error_rcvd;
    ITS_UINT _purgems_error_sent;
    ITS_UINT _purgems_timeout;
    ITS_UINT _purgems_other_error; // RR/RE/Abort case

    ITS_UINT _restoreData_arg_sent;
    ITS_UINT _restoreData_arg_rcvd;
    ITS_UINT _restoreData_res_rcvd;
    ITS_UINT _restoreData_res_sent;
    ITS_UINT _restoreData_error_rcvd;
    ITS_UINT _restoreData_error_sent;
    ITS_UINT _restoreData_timeout;
    ITS_UINT _restoreData_other_error;           // RR/RE/Abort case

    ITS_UINT _insertSubsData_arg_sent;
    ITS_UINT _insertSubsData_arg_rcvd;
    ITS_UINT _insertSubsData_res_rcvd;
    ITS_UINT _insertSubsData_res_sent;
    ITS_UINT _insertSubsData_error_rcvd;
    ITS_UINT _insertSubsData_error_sent;
    ITS_UINT _insertSubsData_timeout;
    ITS_UINT _insertSubsData_other_error;           // RR/RE/Abort case

    ITS_UINT _deleteSubsData_arg_sent;
    ITS_UINT _deleteSubsData_arg_rcvd;
    ITS_UINT _deleteSubsData_res_rcvd;
    ITS_UINT _deleteSubsData_res_sent;
    ITS_UINT _deleteSubsData_error_rcvd;
    ITS_UINT _deleteSubsData_error_sent;
    ITS_UINT _deleteSubsData_timeout;
    ITS_UINT _deleteSubsData_other_error;           // RR/RE/Abort case

    ITS_UINT _cancellocation_arg_sent;
    ITS_UINT _cancellocation_arg_rcvd;
    ITS_UINT _cancellocation_res_rcvd;
    ITS_UINT _cancellocation_res_sent;
    ITS_UINT _cancellocation_error_rcvd;
    ITS_UINT _cancellocation_error_sent;
    ITS_UINT _cancellocation_timeout;
    ITS_UINT _cancellocation_other_error;           // RR/RE/Abort case

    ITS_UINT _provideSubsData_arg_sent;
    ITS_UINT _provideSubsData_arg_rcvd;
    ITS_UINT _provideSubsData_res_rcvd;
    ITS_UINT _provideSubsData_res_sent;
    ITS_UINT _provideSubsData_error_rcvd;
    ITS_UINT _provideSubsData_error_sent;
    ITS_UINT _provideSubsData_timeout;
    ITS_UINT _provideSubsData_other_error;           // RR/RE/Abort case

    ITS_UINT _reset_arg_sent;
    ITS_UINT _reset_arg_rcvd;
    ITS_UINT _reset_res_rcvd;
    ITS_UINT _reset_res_sent;
    ITS_UINT _reset_error_rcvd;
    ITS_UINT _reset_error_sent;
    ITS_UINT _reset_timeout;
    ITS_UINT _reset_other_error;           // RR/RE/Abort case

    ITS_UINT _activatetracemode_arg_sent;
    ITS_UINT _activatetracemode_arg_rcvd;
    ITS_UINT _activatetracemode_res_rcvd;
    ITS_UINT _activatetracemode_res_sent;
    ITS_UINT _activatetracemode_error_rcvd;
    ITS_UINT _activatetracemode_error_sent;
    ITS_UINT _activatetracemode_timeout;
    ITS_UINT _activatetracemode_other_error;           // RR/RE/Abort case

    ITS_UINT _deactivatetracemode_arg_sent;
    ITS_UINT _deactivatetracemode_arg_rcvd;
    ITS_UINT _deactivatetracemode_res_rcvd;
    ITS_UINT _deactivatetracemode_res_sent;
    ITS_UINT _deactivatetracemode_error_rcvd;
    ITS_UINT _deactivatetracemode_error_sent;
    ITS_UINT _deactivatetracemode_timeout;
    ITS_UINT _deactivatetracemode_other_error;           // RR/RE/Abort case

    ITS_UINT _initialdp_arg_rcvd;
    ITS_UINT _initialdpsms_arg_rcvd;
    ITS_UINT _eventreportbcsm_arg_rcvd;
    ITS_UINT _eventreportsms_arg_rcvd;
    ITS_UINT _applychargingreport_arg_rcvd;
    ITS_UINT _requestreportbcsmevent_arg_sent;
    ITS_UINT _requestreportsmsevent_arg_sent;
    ITS_UINT _applycharging_arg_sent;
    ITS_UINT _continue_arg_sent;
    ITS_UINT _connect_arg_sent;
    ITS_UINT _continue_sms_arg_sent;
    ITS_UINT _release_arg_sent;
    ITS_UINT _release_sms_arg_sent;
    ITS_UINT _activity_test_sent;
    ITS_UINT _activity_resp_rcvd;

    ITS_UINT _number_of_tcap_components_sent;
    ITS_UINT _number_of_current_active_subscriber;
    ITS_UINT _number_of_tcap_components_received;
    ITS_UINT _number_of_tcap_error_components_sent;
};


#define UPDATE_SSG_STATS_SAI_ARG_SENT \
    (mapStats).SendAuthInfoArgSent()

#define UPDATE_SSG_STATS_SAI_ARG_RECVD \
    (mapStats).SendAuthInfoArgRecvd()

#define UPDATE_SSG_STATS_SAI_RES_RECVD \
    (mapStats).SendAuthInfoResRecvd()

#define UPDATE_SSG_STATS_SAI_RES_SENT \
    (mapStats).SendAuthInfoResSent()

#define UPDATE_SSG_STATS_SAI_TIMEOUT \
    (mapStats).SendAuthInfoTimeOut()

#define UPDATE_SSG_STATS_SAI_ERROR_RECVD \
    (mapStats).SendAuthInfoErrorRecvd()

#define UPDATE_SSG_STATS_SAI_ERROR_SENT \
    (mapStats).SendAuthInfoErrorSent()

#define UPDATE_SSG_STATS_SAI_REJECT_RECVD \
    (mapStats).SendAuthInfoOtherError()

#define UPDATE_SSG_STATS_SAI_ABORT_RECVD \
    (mapStats).SendAuthInfoOtherError()

#define UPDATE_SSG_STATS_SAI_NOTICE_RECVD \
    (mapStats).SendAuthInfoOtherError()

#define UPDATE_SSG_STATS_SAI_OTHER_ERROR \
    (mapStats).SendAuthInfoOtherError()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_ARG_SENT \
    (mapStats).RoutingInfoForGPRSArgSent()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_ARG_RECVD \
    (mapStats).RoutingInfoForGPRSArgRecvd()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_RES_RECVD \
    (mapStats).RoutingInfoForGPRSResRecvd()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_RES_SENT \
    (mapStats).RoutingInfoForGPRSResSent()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_TIMEOUT \
    (mapStats).RoutingInfoForGPRSTimeOut()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_ERROR_RECVD \
    (mapStats).RoutingInfoForGPRSErrorRecvd()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_ERROR_SENT \
    (mapStats).RoutingInfoForGPRSErrorSent()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_REJECT_RECVD \
    (mapStats).RoutingInfoForGPRSOtherError()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_ABORT_RECVD \
    (mapStats).RoutingInfoForGPRSOtherError()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_NOTICE_RECVD \
    (mapStats).RoutingInfoForGPRSOtherError()

#define UPDATE_SSG_STATS_RI_FOR_GPRS_OTHER_ERROR \
    (mapStats).RoutingInfoForGPRSOtherError()

#define UPDATE_SSG_STATS_UGL_ARG_SENT \
    (mapStats).UpdateGprsLocationArgSent()

#define UPDATE_SSG_STATS_UGL_ARG_RECVD \
    (mapStats).UpdateGprsLocationArgRecvd()

#define UPDATE_SSG_STATS_UGL_RES_RECVD \
    (mapStats).UpdateGprsLocationResRecvd()

#define UPDATE_SSG_STATS_UGL_RES_SENT \
    (mapStats).UpdateGprsLocationResSent()

#define UPDATE_SSG_STATS_UGL_TIMEOUT \
    (mapStats).UpdateGprsLocationTimeOut()

#define UPDATE_SSG_STATS_UGL_ERROR_RECVD \
    (mapStats).UpdateGprsLocationErrorRecvd()

#define UPDATE_SSG_STATS_UGL_ERROR_SENT \
    (mapStats).UpdateGprsLocationErrorSent()

#define UPDATE_SSG_STATS_UGL_REJECT_RECVD \
    (mapStats).UpdateGprsLocationOtherError()

#define UPDATE_SSG_STATS_UGL_ABORT_RECVD \
    (mapStats).UpdateGprsLocationOtherError()

#define UPDATE_SSG_STATS_UGL_NOTICE_RECVD \
    (mapStats).UpdateGprsLocationOtherError()

#define UPDATE_SSG_STATS_UGL_OTHER_ERROR \
    (mapStats).UpdateGprsLocationOtherError()

#define UPDATE_SSG_STATS_READY_FOR_SM_ARG_SENT \
    (mapStats).ReadyForSMArgSent()

#define UPDATE_SSG_STATS_READY_FOR_SM_ARG_RECVD \
    (mapStats).ReadyForSMArgRecvd()

#define UPDATE_SSG_STATS_READY_FOR_SM_RECVD \
    (mapStats).ReadyForSMResRecvd()

#define UPDATE_SSG_STATS_READY_FOR_SM_RES_SENT \
    (mapStats).ReadyForSMResSent()

#define UPDATE_SSG_STATS_READY_FOR_SM_TIMEOUT \
    (mapStats).ReadyForSMTimeOut()

#define UPDATE_SSG_STATS_READY_FOR_SM_ERROR_RECVD \
    (mapStats).ReadyForSMErrorRecvd()

#define UPDATE_SSG_STATS_READY_FOR_SM_ERROR_SENT \
    (mapStats).ReadyForSMErrorSent()

#define UPDATE_SSG_STATS_READY_FOR_SM_REJECT_RECVD \
    (mapStats).ReadyForSMOtherError()

#define UPDATE_SSG_STATS_READY_FOR_SM_ABORT_RECVD \
    (mapStats).ReadyForSMOtherError()

#define UPDATE_SSG_STATS_READY_FOR_SM_NOTICE_RECVD \
    (mapStats).ReadyForSMOtherError()

#define UPDATE_SSG_STATS_READY_FOR_SM_OTHER_ERROR \
    (mapStats).ReadyForSMOtherError()

#define UPDATE_SSG_STATS_RSR_ARG_SENT \
    (mapStats).ResetArgSent()

#define UPDATE_SSG_STATS_RSR_ARG_RECVD \
    (mapStats).ResetArgRecvd()

#define UPDATE_SSG_STATS_RSR_RES_RECVD \
    (mapStats).ResetResRecvd()

#define UPDATE_SSG_STATS_RSR_RES_SENT \
    (mapStats).ResetResSent()

#define UPDATE_SSG_STATS_RSR_TIMEOUT \
    (mapStats).ResetTimeOut()

#define UPDATE_SSG_STATS_RSR_ERROR_RECVD \
    (mapStats).ResetErrorRecvd()

#define UPDATE_SSG_STATS_RSR_ERROR_SENT \
    (mapStats).ResetErrorSent()

#define UPDATE_SSG_STATS_RSR_REJECT_RECVD \
    (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_RSR_ABORT_RECVD \
    (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_RSR_NOTICE_RECVD \
    (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_RSR_OTHER_ERROR \
    (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_PURGE_ARG_SENT \
    (mapStats).PurgeMSArgSent()

#define UPDATE_SSG_STATS_PURGE_ARG_RECVD \
    (mapStats).PurgeMSArgRecvd()

#define UPDATE_SSG_STATS_PURGE_RES_RECVD \
    (mapStats).PurgeMSResRecvd()

#define UPDATE_SSG_STATS_PURGE_RES_SENT \
    (mapStats).PurgeMSResSent()

#define UPDATE_SSG_STATS_PURGE_TIMEOUT \
    (mapStats).PurgeMSTimeOut()

#define UPDATE_SSG_STATS_PURGE_ERROR_RECVD \
    (mapStats).PurgeMSErrorRecvd()

#define UPDATE_SSG_STATS_PURGE_ERROR_SENT \
    (mapStats).PurgeMSErrorSent()

#define UPDATE_SSG_STATS_PURGE_REJECT_RECVD \
    (mapStats).PurgeMSOtherError()

#define UPDATE_SSG_STATS_PURGE_ABORT_RECVD \
    (mapStats).PurgeMSOtherError()

#define UPDATE_SSG_STATS_PURGE_NOTICE_RECVD \
    (mapStats).PurgeMSOtherError()

#define UPDATE_SSG_STATS_PURGE_OTHER_ERROR \
    (mapStats).PurgeMSOtherError()

#define UPDATE_SSG_STATS_RD_ARG_SENT \
    (mapStats).RestoreDataArgSent()

#define UPDATE_SSG_STATS_RD_ARG_RECVD \
    (mapStats).RestoreDataArgRecvd()

#define UPDATE_SSG_STATS_RD_RES_RECVD \
    (mapStats).RestoreDataResRecvd()

#define UPDATE_SSG_STATS_RD_RES_SENT \
    (mapStats).RestoreDataResSent()

#define UPDATE_SSG_STATS_RD_TIMEOUT \
    (mapStats).RestoreDataTimeOut()

#define UPDATE_SSG_STATS_RD_ERROR_RECVD \
    (mapStats).RestoreDataErrorRecvd()

#define UPDATE_SSG_STATS_RD_ERROR_SENT \
    (mapStats).RestoreDataErrorSent()

#define UPDATE_SSG_STATS_RD_REJECT_RECVD \
    (mapStats).RestoreDataOtherError()

#define UPDATE_SSG_STATS_RD_ABORT_RECVD \
    (mapStats).RestoreDataOtherError()

#define UPDATE_SSG_STATS_RD_NOTICE_RECVD \
    (mapStats).RestoreDataOtherError()

#define UPDATE_SSG_STATS_RD_OTHER_ERROR \
    (mapStats).RestoreDataOtherError()

#define UPDATE_SSG_STATS_ISD_ARG_SENT \
        (mapStats).InsertSubsDataArgSent()

#define UPDATE_SSG_STATS_ISD_ARG_RECVD \
        (mapStats).InsertSubsDataArgRecvd()

#define UPDATE_SSG_STATS_ISD_RES_RECVD \
        (mapStats).InsertSubsDataResRecvd()

#define UPDATE_SSG_STATS_ISD_RES_SENT \
        (mapStats).InsertSubsDataResSent()

#define UPDATE_SSG_STATS_ISD_TIMEOUT \
        (mapStats).InsertSubsDataTimeOut()

#define UPDATE_SSG_STATS_ISD_ERROR_RECVD \
        (mapStats).InsertSubsDataErrorRecvd()

#define UPDATE_SSG_STATS_ISD_ERROR_SENT \
        (mapStats).InsertSubsDataErrorSent()

#define UPDATE_SSG_STATS_ISD_REJECT_RECVD \
        (mapStats).InsertSubsDataOtherError()

#define UPDATE_SSG_STATS_ISD_ABORT_RECVD \
        (mapStats).InsertSubsDataOtherError()

#define UPDATE_SSG_STATS_ISD_NOTICE_RECVD \
        (mapStats).InsertSubsDataOtherError()

#define UPDATE_SSG_STATS_ISD_OTHER_ERROR \
        (mapStats).InsertSubsDataOtherError()

#define UPDATE_SSG_STATS_DSD_ARG_SENT \
        (mapStats).DeleteSubsDataArgSent()

#define UPDATE_SSG_STATS_DSD_ARG_RECVD \
        (mapStats).DeleteSubsDataArgRecvd()

#define UPDATE_SSG_STATS_DSD_RES_RECVD \
        (mapStats).DeleteSubsDataResRecvd()

#define UPDATE_SSG_STATS_DSD_RES_SENT \
        (mapStats).DeleteSubsDataResSent()

#define UPDATE_SSG_STATS_DSD_TIMEOUT \
        (mapStats).DeleteSubsDataTimeOut()

#define UPDATE_SSG_STATS_DSD_ERROR_RECVD \
        (mapStats).DeleteSubsDataErrorRecvd()

#define UPDATE_SSG_STATS_DSD_ERROR_SENT \
        (mapStats).DeleteSubsDataErrorSent()

#define UPDATE_SSG_STATS_DSD_REJECT_RECVD \
        (mapStats).DeleteSubsDataOtherError()

#define UPDATE_SSG_STATS_DSD_ABORT_RECVD \
        (mapStats).DeleteSubsDataOtherError()

#define UPDATE_SSG_STATS_DSD_NOTICE_RECVD \
        (mapStats).DeleteSubsDataOtherError()

#define UPDATE_SSG_STATS_DSD_OTHER_ERROR \
        (mapStats).DeleteSubsDataOtherError()

#define UPDATE_SSG_STATS_PSD_ARG_SENT \
        (mapStats).ProvideSubsDataArgSent()

#define UPDATE_SSG_STATS_PSD_ARG_RECVD \
        (mapStats).ProvideSubsDataArgRecvd()

#define UPDATE_SSG_STATS_PSD_RES_RECVD \
        (mapStats).ProvideSubsDataResRecvd()

#define UPDATE_SSG_STATS_PSD_RES_SENT \
        (mapStats).ProvideSubsDataResSent()

#define UPDATE_SSG_STATS_PSD_TIMEOUT \
        (mapStats).ProvideSubsDataTimeOut()

#define UPDATE_SSG_STATS_PSD_ERROR_RECVD \
        (mapStats).ProvideSubsDataErrorRecvd()

#define UPDATE_SSG_STATS_PSD_ERROR_Sent \
        (mapStats).ProvideSubsDataErrorSent()

#define UPDATE_SSG_STATS_PSD_REJECT_RECVD \
        (mapStats).ProvideSubsDataOtherError()

#define UPDATE_SSG_STATS_PSD_ABORT_RECVD \
        (mapStats).ProvideSubsDataOtherError()

#define UPDATE_SSG_STATS_PSD_NOTICE_RECVD \
        (mapStats).ProvideSubsDataOtherError()

#define UPDATE_SSG_STATS_PSD_OTHER_ERROR \
        (mapStats).ProvideSubsDataOtherError()

#define UPDATE_SSG_STATS_CLR_ARG_SENT \
        (mapStats).CancelLocationArgSent()

#define UPDATE_SSG_STATS_CLR_ARG_RECVD \
        (mapStats).CancelLocationArgRecvd()

#define UPDATE_SSG_STATS_CLR_RES_RECVD \
        (mapStats).CancelLocationResRecvd()

#define UPDATE_SSG_STATS_CLR_RES_SENT \
        (mapStats).CancelLocationResSent()

#define UPDATE_SSG_STATS_CLR_TIMEOUT \
        (mapStats).CancelLocationTimeOut()

#define UPDATE_SSG_STATS_CLR_ERROR_RECVD \
        (mapStats).CancelLocationErrorRecvd()

#define UPDATE_SSG_STATS_CLR_ERROR_SENT \
        (mapStats).CancelLocationErrorSent()

#define UPDATE_SSG_STATS_CLR_REJECT_RECVD \
        (mapStats).CancelLocationOtherError()

#define UPDATE_SSG_STATS_CLR_ABORT_RECVD \
        (mapStats).CancelLocationOtherError()

#define UPDATE_SSG_STATS_CLR_NOTICE_RECVD \
        (mapStats).CancelLocationOtherError()

#define UPDATE_SSG_STATS_CLR_OTHER_ERROR \
        (mapStats).CancelLocationOtherError()

#define UPDATE_SSG_STATS_RESET_ARG_SENT \
        (mapStats).ResetArgSent()

#define UPDATE_SSG_STATS_RESET_ARG_RECVD \
        (mapStats).ResetArgRecvd()

#define UPDATE_SSG_STATS_RESET_RES_RECVD \
        (mapStats).ResetResRecvd()

#define UPDATE_SSG_STATS_RESET_RES_SENT \
        (mapStats).ResetResSent()

#define UPDATE_SSG_STATS_RESET_TIMEOUT \
        (mapStats).ResetTimeOut()

#define UPDATE_SSG_STATS_RESET_ERROR_RECVD \
        (mapStats).ResetErrorRecvd()

#define UPDATE_SSG_STATS_RESET_ERROR_SENT \
        (mapStats).ResetErrorSent()

#define UPDATE_SSG_STATS_RESET_REJECT_RECVD \
        (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_RESET_ABORT_RECVD \
        (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_RESET_NOTICE_RECVD \
        (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_RESET_OTHER_ERROR \
        (mapStats).ResetOtherError()

#define UPDATE_SSG_STATS_ATM_ARG_SENT \
        (mapStats).ActivateTraceModeArgSent()

#define UPDATE_SSG_STATS_ATM_ARG_RECVD \
        (mapStats).ActivateTraceModeArgRecvd()

#define UPDATE_SSG_STATS_ATM_RES_RECVD \
        (mapStats).ActivateTraceModeResRecvd()

#define UPDATE_SSG_STATS_ATM_RES_SENT \
        (mapStats).ActivateTraceModeResSent()

#define UPDATE_SSG_STATS_ATM_TIMEOUT \
        (mapStats).ActivateTraceModeTimeOut()

#define UPDATE_SSG_STATS_ATM_ERROR_RECVD \
        (mapStats).ActivateTraceModeErrorRecvd()

#define UPDATE_SSG_STATS_ATM_ERROR_SENT \
        (mapStats).ActivateTraceModeErrorSent()

#define UPDATE_SSG_STATS_ATM_REJECT_RECVD \
        (mapStats).ActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_ATM_ABORT_RECVD \
        (mapStats).ActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_ATM_NOTICE_RECVD \
        (mapStats).ActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_ATM_OTHER_ERROR \
        (mapStats).ActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_DATM_ARG_SENT \
        (mapStats).DeActivateTraceModeArgSent()

#define UPDATE_SSG_STATS_DATM_ARG_RECVD \
        (mapStats).DeActivateTraceModeArgRecvd()

#define UPDATE_SSG_STATS_DATM_RES_RECVD \
        (mapStats).DeActivateTraceModeResRecvd()

#define UPDATE_SSG_STATS_DATM_RES_SENT \
        (mapStats).DeActivateTraceModeResSent()

#define UPDATE_SSG_STATS_DATM_TIMEOUT \
        (mapStats).DeActivateTraceModeTimeOut()

#define UPDATE_SSG_STATS_DATM_ERROR_RECVD \
        (mapStats).DeActivateTraceModeErrorRecvd()

#define UPDATE_SSG_STATS_DATM_ERROR_SENT \
        (mapStats).DeActivateTraceModeErrorSent()

#define UPDATE_SSG_STATS_DATM_REJECT_RECVD \
        (mapStats).DeActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_DATM_ABORT_RECVD \
        (mapStats).DeActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_DATM_NOTICE_RECVD \
        (mapStats).DeActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_DATM_OTHER_ERROR \
        (mapStats).DeActivateTraceModeOtherError()

#define UPDATE_SSG_STATS_IDP_ARG_RECVD \
        (mapStats).InitialDPArgRecvd()

#define UPDATE_SSG_STATS_IDP_SMS_ARG_RECVD \
        (mapStats).InitialDPSMSArgRecvd()

#define UPDATE_SSG_STATS_ERBCSM_ARG_RECVD \
        (mapStats).EventReportBCSMArgRecvd()

#define UPDATE_SSG_STATS_ERSMS_ARG_RECVD \
        (mapStats).EventReportSMSArgRecvd()

#define UPDATE_SSG_STATS_ACR_ARG_RECVD \
        (mapStats).ApplyChargingReportArgRecvd()

#define UPDATE_SSG_STATS_RRBCSM_ARG_SENT \
        (mapStats).RequestReportBCSMEventArgSent()

#define UPDATE_SSG_STATS_RRSMS_ARG_SENT \
        (mapStats).RequestReportSMSEventArgSent()

#define UPDATE_SSG_STATS_AC_ARG_SENT \
        (mapStats).ApplyChargingArgSent()

#define UPDATE_SSG_STATS_CONTINUE_ARG_SENT \
        (mapStats).ContinueArgSent()

#define UPDATE_SSG_STATS_CONNECT_ARG_SENT \
        (mapStats).ConnectArgSent()

#define UPDATE_SSG_STATS_CONTINUE_SMS_ARG_SENT \
        (mapStats).ContinueSMSArgSent()

#define UPDATE_SSG_STATS_REL_ARG_SENT \
        (mapStats).ReleaseArgSent()

#define UPDATE_SSG_STATS_RELSMS_ARG_SENT \
        (mapStats).ReleaseSMSArgSent()

#define UPDATE_SSG_STATS_ACT_TEST_SENT \
        (mapStats).ActivityTestSent()

#define UPDATE_SSG_STATS_ACT_RESP_RECVD \
        (mapStats).ActivityRespRecvd()

#define UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT \
        (mapStats).NumberofTcapComponentsSent()

#define INCREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS \
        (mapStats).IncrementCurrentActiveSubscriberCount()

#define DECREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS \
        (mapStats).DecrementCurrentActiveSubscriberCount()

#define UPDATE_SSG_STATS_NUM_OF_TCCOMP_RCVD \
        (mapStats).NumberofTcapComponentsReceived()

#define UPDATE_SSG_STATS_NUM_OF_TCCOMP_ERR_SENT \
        (mapStats).NumberofTcapErrorComponentsSent()

#endif
