/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: app_msgs.h,v $
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5.2.2.4.5  2015/05/25 05:12:17  jkchaitanya
 * LOG: Cap-Ro test tool enhancement to support automatic user configuration mode for automation purpose, Review 4059
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5.2.2.4.4  2015/04/29 06:35:57  rsanjay
 * LOG:  Map Tool Message implementation Multiple ISD Send Routing info Send Routing Info-SM Provide Roaming Number Update location Messages are implemented newly
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5.2.2.4.3  2014/12/16 05:40:13  jkchaitanya
 * LOG: changes merged from TSL branch
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5.2.2.2.1  2014/12/10 10:48:55  kpnithin
 * LOG: changes for bug 5688
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5.2.2  2014/07/15 05:07:27  jkchaitanya
 * LOG: changes merged from VOICE branch for UDTS message changes
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5.2.1  2014/06/27 10:16:42  jkchaitanya
 * LOG: changes for InvokeId release and send UAbort option to user
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.5  2014/06/11 09:11:27  jkchaitanya
 * LOG: changes for giving option to send ERB or ACR in a single dialogue first
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.4  2014/05/06 13:11:02  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.3  2014/04/09 11:12:23  jkchaitanya
 * LOG: changes for msc to support TcapResult and TcapError messages and for bug 3510
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.2  2014/03/25 10:19:11  jkchaitanya
 * LOG: changes for msc tool to support all the callflows for TSL
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1.6.1  2014/03/13 10:14:17  jsarvesh
 * LOG: Implementation for Voice CallFlows
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6.2.1  2013/12/31 04:44:00  millayaraja
 * LOG: merged code from B-IWF-0100-01 to B-IWF-0100-02 with GTT support
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.6  2013/08/29 06:06:59  jsarvesh
 * LOG: Changes done for Conflicts in OpCodes and encoding of PDN_GW_Update
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.5  2013/08/12 15:35:14  jkchaitanya
 * LOG: changes to enhance cap tool for bug 1896
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.4  2013/08/02 06:51:36  jkchaitanya
 * LOG: changes for tool enhancements
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.3  2013/07/29 12:27:45  jkchaitanya
 * LOG: changes for sms support messages in cap tool and asn
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.2  2013/07/16 07:06:15  jkchaitanya
 * LOG: changes for review comments and release call decode
 * LOG:
 * LOG: Revision 1.1.1.1.2.3.2.1  2013/07/09 11:26:31  jkchaitanya
 * LOG: changes for cap tool enhancement
 * LOG:
 * LOG: Revision 1.1.1.1.2.3  2013/06/10 07:07:55  jsarvesh
 * LOG: enhanced for Load Run from MAP-Tool
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/03/08 04:17:59  jsarvesh
 * LOG: implementation for map message through json
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/02/22 19:59:13  lakshman
 * LOG: add gtt test info.
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/03 02:44:43  lakshman
 * LOG: update tcap tests - add gprs and randomize responses.
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_msgs.h,v 1.1.1.1.2.3.2.6.2.1.6.5.2.2.4.5 2015/05/25 05:12:17 jkchaitanya Exp $"

#ifndef TCAP_MSGS_H
#define TCAP_MSGS_H

#include <iostream>
#include <its++.h>
#include <its_mutex.h>
#include <tcap++.h>
#include <its_trace.h>
#include <app_trace.h>
#include <its_worker.h>
#include "app_timer.h"
#include <mutex>
#include <unordered_map> 
#include <fstream>
#include <string>

using namespace its;
using namespace std;


typedef enum _msgType
{
    CAP_OPEN_REQUEST = 0,
}MSG_TYPE;

typedef enum callflowstate
{
    CANCEL_LOC_REC = 0,
    INSERT_SUB_REC,
    DELETE_SUB_REC,

}CALLFLOW_STATE;

struct CallContext {
    int ivkId;
    int currentState;
    int callFlowId;
};

typedef struct _UserAutoData {
    int opc;
    int dpc;
    bool pc;
    int destinationSSN;
    int sourceSSN;
    int gtt;
    bool setInternationalRouting;
    
    int transactionType;
    int operationClass;
    int operation;
}UserAutoData;

std::unordered_map <ITS_CTXT, CallContext> gCallFlowState;
std::mutex gMtx;


#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))

#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))

class TransportState {
    public:
       TransportState() {
          mtx = new Mutex(0);
          numUpTrans = 0;
       }
       ~TransportState() {
          delete mtx;
       }
       bool SetTransportStateUP(ITS_USHORT inst) {
           bool ret = false;
           if(mtx->Acquire() == ITS_SUCCESS) {
               numUpTrans++; ret = true;

               mtx->Release();
           }
           return ret;
       }
       bool SetTransportStateDOWN(ITS_USHORT inst) {
          bool ret = false;
          if(mtx->Acquire() == ITS_SUCCESS) {
              numUpTrans--; ret = true;

              mtx->Release();
          }
          return ret;
       }
       ITS_USHORT GetNumOfUPTransports() {
           ITS_USHORT ret = 0;
           if(mtx->Acquire() == ITS_SUCCESS) {
               ret = numUpTrans;

               mtx->Release();
           }
           return ret;
       }

    private:
       Mutex *mtx;
       ITS_USHORT        numUpTrans;
};


class TCAPMsgs
{
   public:
       TCAPMsgs();

       ~TCAPMsgs();

       virtual void HandleTimeout(STimerContext& timerCtxt)=0;

       virtual int HandleMessage(engine::Worker *work, its::ITS_Event&)=0;

       virtual void PrintComponentType(ITS_USHORT compType)=0;

       virtual void PrintDialogueType(ITS_USHORT compType)=0;

       virtual void SetSCCPAddress() = 0;

       void SendMsgs(ITS_HANDLE hdl, ITS_INT choice);

       virtual void InteractiveSendUniDlg(ITS_HANDLE hdl) = 0;

       virtual void InteractiveSendAbort(ITS_HANDLE hdl) = 0;

       virtual void InteractiveSendBeginDlg(ITS_HANDLE hdl) = 0;

       virtual void InteractiveSendEnd(ITS_HANDLE hdl) = 0;

       virtual void InteractiveSendContinue(ITS_HANDLE hdl) = 0;

       virtual void InteractiveSendPreArrangedEnd(ITS_HANDLE) = 0;

       void GenerateLoad(ITS_HANDLE);

       virtual 
       void SendBeginDlg(ITS_HANDLE, int, ITS_BOOLEAN addR = ITS_TRUE) = 0;

       virtual 
       void SendBeginDlg(ITS_HANDLE, int, ITS_BOOLEAN addR = ITS_TRUE, int opCode = -1) = 0;

       virtual void SendPreArrangedEnd(ITS_HANDLE, ITS_USHORT) = 0;

       virtual int SendResponse(ITS_HANDLE, ITS_USHORT, ITS_INT) = 0;

       virtual int SendMAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
                  engine::Worker* work) = 0;

       virtual int SendCAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
                  engine::Worker* work) = 0;

       int  GetInvokeID() const;

       void DeleteApplicationRoute(ITS_USHORT, ITS_USHORT);

       void Print(const char*);

       virtual void InitExternals() = 0;

   private:

       void Lock();

       void UnLock();

       its::Mutex* lockFile;

       std::ofstream* output; 
};

#if defined(DEF_CCITT) || defined (CCITT)
class ITUTcapMsgs : public TCAPMsgs
{
   public:

       static ITUTcapMsgs * GetItuInstance();

       int HandleMessage(engine::Worker *work, its::ITS_Event&);

       void SetSCCPAddress();

       void PrintComponentType(ITS_USHORT compType);

       void PrintDialogueType(ITS_USHORT compType);

       void InteractiveSendUniDlg(ITS_HANDLE hdl);

       void InteractiveSendAbort(ITS_HANDLE hdl);

       void InteractiveSendBeginDlg(ITS_HANDLE hdl);

       void InteractiveSendEnd(ITS_HANDLE hdl);

       void InteractiveSendContinue(ITS_HANDLE hdl);

       void InteractiveSendPreArrangedEnd(ITS_HANDLE);

       void SendBeginDlg(ITS_HANDLE, int, ITS_BOOLEAN addR = ITS_TRUE);

       void SendBeginDlg(ITS_HANDLE, int, ITS_BOOLEAN addR = ITS_TRUE, int opCode = -1);

       void SendPreArrangedEnd(ITS_HANDLE, ITS_USHORT);

       int SendResponse(ITS_HANDLE, ITS_USHORT, ITS_INT);
       
       int SendInsertSubscriberDataMultiple(TCAP_Dialogue *dlg, TCAP_Component *cpt);

       int SendMAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
                  engine::Worker* work);

       int SendCAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
                  engine::Worker* work);
        
       int SendEventReportBCSMArgInTcCont(TCAP_Dialogue *dlg);
    
       int SendApplyChargingReportArgInTcCont(TCAP_Dialogue *dlg);

       int SendERBandACRInTcEnd(TCAP_Dialogue *dlg, bool sendACRFirst = false);

       int SendERBandACRInTcCont(TCAP_Dialogue *dlg, bool sendACRFirst = false);

       int SendEventReportBCSMArgInTcEnd(TCAP_Dialogue *dlg);

       int SendEventReportSMSArginTcEnd(TCAP_Dialogue *dlg);

       int SendApplyChargingReportInTcEnd(TCAP_Dialogue *dlg);
        
       void BuildAndSendERBandACRinTcCont(TCAP_Dialogue *dlg, bool receivedonlyACH = false);
    
       int SendInsertSubscriberDataResult(ITS_UINT dlgId);
       int SendCancelLocationResult(ITS_UINT dlgId,int invoke_id);
       int SendDeleteSubscriberDataResult(ITS_UINT dlgId, int invoke_id);
       
       std::string GetStrTimerType(ETimerType& timerType);

       void BuildAndSendERBandACRinTcEnd(TCAP_Dialogue *dlg);

       void BuildTCAPErrorCpt(TCAP_Dialogue *dlg, ITS_OCTET invokeId, TCAP_Error **tcapErr, ITS_OCTET errVal);
       int SendTcapAbort(TCAP_Dialogue *dlg);
       int SendTcapAbortMap(ITS_UINT dlgId);
       int SendResponses(TCAP_Dialogue *dlg, TCAP_Component *cpt);
       int SendActivityResponseInTcCont(TCAP_Dialogue *dlg);
       int SendERBInReturnResultLastInCont(TCAP_Dialogue *dlg);
       int SendERBInReturnResultLastInEnd(TCAP_Dialogue *dlg);
       int SendTcapErrorInContinue(TCAP_Dialogue *dlg);
       int SendTcapErrorInEnd(TCAP_Dialogue *dlg);
       void ReleaseInvokeId(ITS_CTXT dialogueId, ITS_OCTET invokeId, bool isOutGoingMsg = false);
       int SendTcapUAbort(TCAP_Dialogue *dlg);
       int BuildUDTSMessage(TCAP_Dialogue *dlg);
       void InitExternals();
       void StartTimerHandling(ITS_UINT dlgId, ETimerType timerType, int32_t sleep_value);
       void HandleTimeout(STimerContext& timerCtxt);
       void SendResponseOnTimeOutCancelLocation(ITS_CTXT dlgId, int sleep_value, int get_invokeid);
       void SendResponseOnTimeOutInsertSubscriberData(ITS_CTXT dlgId,int sleep_value,int get_invokeid);
       void SendResponseOnTimeOutDeleteSubscriberData(ITS_CTXT dlgId,int sleep_value,int get_invokeid);
   private:
       ITUTcapMsgs(){};

       ~ITUTcapMsgs(){};
};
#endif


class TCAPUtils
{
   public:
       TCAPUtils(){};

       ~TCAPUtils(){};

       static int GetVariantType();

       static void ConvertStringToOctets(ITS_OCTET*, std::string&,
                                         int&, ITS_BOOLEAN&);

       static void ConvertStringToOctets(ITS_OCTET*, char*,
                                         int&, ITS_BOOLEAN&);

       static void ConvertOctsToString(char**, ITS_OCTET*,
                                       int len, ITS_BOOLEAN);

       static void RegisterGTTCallback(ITS_POINTER, ITS_POINTER, ITS_POINTER);
      
#ifndef USE_ANSI_SCCP 
#if 1
       static void RegisterSCCPGTTCallback(ITS_POINTER, ITS_POINTER, ITS_POINTER);
#endif
#endif
       static void RegisterSCTPTransCallback(ITS_POINTER, ITS_POINTER, ITS_POINTER);

       static void RegisterMTP3TransCallback(ITS_POINTER, ITS_POINTER, ITS_POINTER);

       static void DumpRoutingTable();

};

#endif

