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
 * LOG: Revision 1.1.2.2  2013/03/18 12:25:21  jvikas
 * LOG: Code Changes for CLR/CLA.
 * LOG:
 * LOG: Revision 1.1.2.1  2013/02/12 14:11:30  jvikas
 * LOG: Map Simulator Changes for IWF
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
#ident "$Id: app_msgs.h,v 1.1.2.2 2013/03/18 12:25:21 jvikas Exp $"

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

#define MAX_MSGS_TO_DISPLAY 12

union diameter_message_stats
{
    long m_in;
    long m_out;
};

typedef struct
{
    long m_outMsgs;
    long m_inMsgs;
    long m_lastOutMsgs;
    long m_lastInMsgs;
    long m_successfulCalls;
    long m_failedCalls;
    long m_lastSuccessfulCalls;
    long m_lastFailedCalls;
    union
    {
        struct 
        {
            diameter_message_stats ulr;
            diameter_message_stats ula;
            diameter_message_stats air;
            diameter_message_stats aia;
            diameter_message_stats idr;
            diameter_message_stats ida;
            diameter_message_stats clr;
            diameter_message_stats cla;
        } hlrmap;
    }u;
    string last_processed_sessionId[MAX_MSGS_TO_DISPLAY];
    string last_processed_msgs[MAX_MSGS_TO_DISPLAY];
    int recent_msg_idx;
}ApplicationStats;

extern int displayMode;

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

       virtual void SendPreArrangedEnd(ITS_HANDLE, ITS_USHORT) = 0;

       virtual int SendResponse(ITS_HANDLE, ITS_USHORT, ITS_INT) = 0;

       virtual int SendResponses(TCAP_Dialogue* dlg, TCAP_Component** cpt,
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

       void SendPreArrangedEnd(ITS_HANDLE, ITS_USHORT);

       int SendResponse(ITS_HANDLE, ITS_USHORT, ITS_INT);

       int SendResponses(TCAP_Dialogue* dlg, TCAP_Component** cpt,
                  engine::Worker* work);
       int SendMAPResponse(TCAP_Dialogue *dlg, TCAP_Component *cpt);

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

