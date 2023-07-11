/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: MulAppTcapMsgHandler.h,v 1.1 2005/07/05 11:30:55 mmanikandan Exp $
 *
 * LOG: $Log: MulAppTcapMsgHandler.h,v $
 * LOG: Revision 1.1  2005/07/05 11:30:55  mmanikandan
 * LOG: Changes for ISUP Redundancy.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _TCAP_MSG_HANDLER_CLIENT_H_
#define _TCAP_MSG_HANDLER_CLIENT_H_

#include <MsgHandlerClient.h>
#include <its_mlist.h>
#include <tcap++.h>

class TcapMsgHandler : public MsgHandlerClient
{
public:
    TcapMsgHandler();
    ~TcapMsgHandler();

    int ProcessAppMsg(MABCL_MESSAGE* msg);
    int ProcessStackMsg(its::ITS_Event* evt);

    int ProcessGcsMsg(ITS_EVENT* evt);
    
private:

    int LocalHashKey(ITS_OCTET *key, ITS_UINT klen);
    int TCAP_StoreTcapEvent(ITS_EVENT *event);
    int TCAP_GetComponentFromQ(ITS_CTXT did, ITS_OCTET* data, ITS_USHORT *len);
    int TCAP_GetDialogueFromQ(ITS_CTXT did, TCAP_DLG *dlg);
    int TCAP_EncodeCpt(ITS_CTXT dlgId, TCAP_CPT *cpt, ITS_EVENT *ev);
    int TCAP_EncodeDlg(ITS_CTXT  dlgId, TCAP_DLG  *dlg, ITS_EVENT *ev);
    int EncodeMsgtoClient(ITS_CTXT did);
    int UpdateAddrsAndQOS(TCAP_DLG *dlg, SCCP_ADDR origaddr, 
                        SCCP_ADDR destaddr, DLG_QOS qos, 
                        MTP3_POINT_CODE * opc, MTP3_POINT_CODE *dpc);
    int DecodeDlgComponent(TCAP_DLG  *dlg, ITS_CTXT *dlgid, 
                      TCAP_CPT  *cpt,  ITS_OCTET  *numCpts,
                      ITS_OCTET *tcapdata, ITS_UINT len);
    int AddEntry(ITS_USHORT did, ITS_USHORT lid, ITS_UINT cid);
    int RemoveEntry(ITS_USHORT did, ITS_USHORT lid, ITS_UINT cid);

    int AddDownEntry(ITS_USHORT did, ITS_UINT cid);
    int RemoveDownEntry(ITS_USHORT did, ITS_UINT cid);

    MLIST_Manager *TCAP_primQueue;

    HASH_Table      _SL_TCAP_did_info;
    HASH_Table      _SL_TCAP_lid_info;

    typedef std::map<ITS_UINT, ITS_UINT> DIDCIDMap;
    DIDCIDMap didcidMap_;
    its::Mutex* didcidMutex_;

    ClientHandler* cHandler_;

    ITS_Class redunClass;
};

#endif

