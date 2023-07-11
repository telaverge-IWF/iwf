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
 * LOG: Revision 1.1.2.2.14.1  2014/09/22 04:58:54  jkchaitanya
 * LOG: changes for enhancement bugs 5045, 5053
 * LOG:
 * LOG: Revision 1.1.2.2  2013/08/29 08:46:44  jkchaitanya
 * LOG: changes after merging sarvesh changes for dividing SendMapResponse and SendCapResponse from map to capsim directory
 * LOG:
 * LOG: Revision 1.1.2.1  2013/08/21 12:14:15  jkchaitanya
 * LOG: sub directories in capsim
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
#ident "$Id: app_msgs.h,v 1.1.2.2.14.1 2014/09/22 04:58:54 jkchaitanya Exp $"

#ifndef TCAP_MSGS_H
#define TCAP_MSGS_H

#include <iostream>
#include <its++.h>
#include <its_mutex.h>
#include <tcap++.h>
#include <its_trace.h>
#include <app_trace.h>
#include <its_worker.h>

#include <fstream>
#include <string>

using namespace its;
using namespace std;


typedef enum _msgType
{
    CAP_OPEN_REQUEST = 0,
}MSG_TYPE;


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

       virtual void IncrementImsi(int opCode) = 0;

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

       void IncrementImsi(int opCode);

       int SendMAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
               engine::Worker* work);

       int SendCAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
               engine::Worker* work);

       int SendEventReportBCSMArgInTcCont(TCAP_Dialogue *dlg, bool sendERBinTcContAgain = false);
    
       int SendApplyChargingReportArgInTcCont(TCAP_Dialogue *dlg, bool sendACRinTcContAgain = false);

       int SendERBandACRInTcEnd(TCAP_Dialogue *dlg);

       int SendEventReportBCSMArgInTcEnd(TCAP_Dialogue *dlg);

       int SendEventReportSMSArginTcEnd(TCAP_Dialogue *dlg);

       int SendApplyChargingReportInTcEnd(TCAP_Dialogue *dlg);
        
       void BuildAndSendERBandACRinTcCont(TCAP_Dialogue *dlg, bool receivedonlyACH = false);

       void BuildAndSendERBandACRinTcEnd(TCAP_Dialogue *dlg);

       int SendResponseForInitialCase(TCAP_Dialogue *dlg);

       int SendResponseForUpdateCase(TCAP_Dialogue *dlg);

       void BuildTCAPErrorCpt(TCAP_Dialogue *dlg, ITS_OCTET invokeId, TCAP_Error **tcapErr, ITS_OCTET errVal);
       int SendResponses(TCAP_Dialogue *dlg, TCAP_Component *cpt);

       void InitExternals();

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
       static void RegisterSCTPTransCallback(ITS_POINTER, ITS_POINTER, ITS_POINTER);

       static void RegisterMTP3TransCallback(ITS_POINTER, ITS_POINTER, ITS_POINTER);

       static void DumpRoutingTable();

};

#endif

