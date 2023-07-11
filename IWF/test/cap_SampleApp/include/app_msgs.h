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
 * LOG: Revision 1.1.2.1  2014/07/29 09:49:58  jkchaitanya
 * LOG: added a new directory cap_sample useful for load testing
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
#ident "$Id: app_msgs.h,v 1.1.2.1 2014/07/29 09:49:58 jkchaitanya Exp $"

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
#include <app_cmn.h>

using namespace its;
using namespace std;
#if defined(USE_CAP_V3)
#include <cap_v3_called_party_number.h>
using namespace cap_v3;
#endif



typedef enum _msgType
{
    CAP_OPEN_REQUEST = 0,
}MSG_TYPE;


#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))

#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))

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


       int SendCAPResponse(TCAP_Dialogue* dlg, TCAP_Component** cpt,
                  engine::Worker* work);
        
       int SendResponses(TCAP_Dialogue *dlg, TCAP_Component *cpt);

	   void BuildACinTcCont(ITS_CTXT dlgId, TCAP_Component *in_cpt);
	   void SendRRBAchContinTcCont(ITS_CTXT dlgId,ITS_ByteArray& app_ctxt, bool isSMSIdp = false);
	   void SendRRBConnectInTcCont(ITS_CTXT dlgId,ITS_ByteArray& app_ctxt,cap_v3::CalledPartyNumber& CdPtyNo);
	   void SendMultiCmptInTcCont(TcapCptList& cmptLst, ITS_CTXT dlgId, ITS_ByteArray& app_ctxt);
	   int ValidateERBArgs(TCAP_Component *cpt);
	   int ValidateIDPArgs(TCAP_Component *cpt, int& version);
	   int ValidateIDPSMSArgs(TCAP_Component *cpt);
	   void SendTCapErrResp(TCAP_Dialogue *dlg, TCAP_Component *cmpt, int& capErrVal);
	   void SendRelease(int& relValue,ITS_CTXT dialogueID);
	   void SendTcEnd(TCAP_Component *&cpt, ITS_CTXT dialogueID);	   
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

