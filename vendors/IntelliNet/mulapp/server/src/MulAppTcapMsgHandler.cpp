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
 * ID: $Id: MulAppTcapMsgHandler.cpp,v 1.1 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: MulAppTcapMsgHandler.cpp,v $
 * LOG: Revision 1.1  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <math.h>
#include <iostream>
#include <MulAppTcapMsgHandler.h>
#include <its_redundancy.h>

#define SL_ROUTING_INFO_LID 1
#define SL_ROUTING_INFO_DID 2

#define TCAP_ADD_ENTRY 1
#define TCAP_REMOVE_ENTRY 2
#define TCAP_ADD_DOWN_ENTRY 3
#define TCAP_REMOVE_DOWN_ENTRY 4

typedef struct _didInfo
{
    ITS_CTXT did;
    ITS_CTXT lid;
    ITS_UINT cid;
}DIDInfo;

TcapMsgHandler::TcapMsgHandler()
{
    TCAP_primQueue = MQUEUE_Create();

    ITS_THROW_ASSERT (TCAP_primQueue != NULL);

    _SL_TCAP_did_info = HASH_CreateTable();

    ITS_THROW_ASSERT (_SL_TCAP_did_info != NULL);

    _SL_TCAP_lid_info = HASH_CreateTable();

    ITS_THROW_ASSERT (_SL_TCAP_lid_info != NULL);

    didcidMutex_ = new its::Mutex(0);

    cHandler_ = ClientHandler::GetClientHandler();

    redunClass = NULL;
    redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);
}

TcapMsgHandler::~TcapMsgHandler()
{
    delete didcidMutex_;
    cHandler_ = NULL;

    HASH_DeleteTable(_SL_TCAP_did_info);
    HASH_DeleteTable(_SL_TCAP_lid_info);
}

int TcapMsgHandler::ProcessAppMsg(MABCL_MESSAGE* msg)
{
    TCAP_DLG dlg;
    ITS_CTXT dlgId = 0;
    TCAP_CPT cpt[MAX_NUM_CPT];
    ITS_OCTET numCpts = 0;
    ITS_INT ret = ITS_SUCCESS;

    ret = DecodeDlgComponent(&dlg, &dlgId, cpt, &numCpts, 
             msg->u.tcapInfo.data,msg->u.tcapInfo.len);

    if (ret == ITS_SUCCESS)
    {
        ITS_CTXT did = dlgId;
        
#if defined(ANSI)
        if ((dlg.ptype != TCAP_PT_TC_UNI_ANSI) && (dlgId < MAX_NUM_LID))
#elif defined(CCITT)
        if ((dlg.ptype != TCAP_PT_TC_UNI_CCITT) && (dlgId < MAX_NUM_LID))
#endif
        {
#if defined (CCITT)
            if (dlg.ptype == TCAP_PT_TC_BEGIN_CCITT)
#elif defined (ANSI)
            if ((dlg.ptype == TCAP_PT_TC_QUERY_W_PERM_ANSI) ||
                (dlg.ptype == TCAP_PT_TC_QUERY_WO_PERM_ANSI))
#endif
            {
                TCAP_AllocateDialogueId(SL_HANDLE, &did);

                if (redunClass)
                {
                    ITS_EVENT ev;
                    ITS_EVENT_INIT(&ev, ITS_MAB_SRC, 9);
                    ev.data[0] = TCAP_ADD_ENTRY;
                    ev.data[1] = (did & 0xff00) >> 8;
                    ev.data[2] = (did & 0xff);
                    ev.data[3] = (dlgId & 0xff00) >> 8;
                    ev.data[4] = (dlgId & 0xff);
                    ev.data[5] = (msg->clientID & 0xff000000) >> 24;
                    ev.data[6] = (msg->clientID & 0x00ff0000) >> 16;
                    ev.data[7] = (msg->clientID & 0x0000ff00) >> 8;
                    ev.data[8] = (msg->clientID & 0x000000ff);

                    if (DSM_MulticastStackEventToFtGroupMembers(
                        DSM_Mtp3FtGroupId,
                        ev,
                        ITS_MAB_SRC,
                        ITS_MAB_SRC) != ITS_SUCCESS )
                    {
                        printf("Error in Mutlicasting message\n");
                    }
                }
                else
                {
                    AddEntry(did, dlgId, msg->clientID);
                }
            }
#if defined(CCITT)
            else if ((dlg.ptype == TCAP_PT_TC_END_CCITT) || 
                     (dlg.ptype == TCAP_PT_TC_P_ABORT_CCITT) ||
                     (dlg.ptype == TCAP_PT_TC_U_ABORT_CCITT))
#elif defined(ANSI)
            else if ((dlg.ptype == TCAP_PT_TC_RESP_ANSI) || 
                     (dlg.ptype == TCAP_PT_TC_ABORT_ANSI))
#endif
            {
                if (redunClass)
                {
                    ITS_EVENT ev;
                    ITS_EVENT_INIT(&ev, ITS_MAB_SRC, 9);
                    ev.data[0] = TCAP_REMOVE_ENTRY;
                    ev.data[1] = (did & 0xff00) >> 8;
                    ev.data[2] = (did & 0xff);
                    ev.data[3] = (dlgId & 0xff00) >> 8;
                    ev.data[4] = (dlgId & 0xff);
                    ev.data[5] = (msg->clientID & 0xff000000) >> 24;
                    ev.data[6] = (msg->clientID & 0x00ff0000) >> 16;
                    ev.data[7] = (msg->clientID & 0x0000ff00) >> 8;
                    ev.data[8] = (msg->clientID & 0x000000ff);
                    
                    if (DSM_MulticastStackEventToFtGroupMembers(
                        DSM_Mtp3FtGroupId,
                        ev,
                        ITS_MAB_SRC,
                        ITS_MAB_SRC) != ITS_SUCCESS )
                    {
                        printf("Error in Mutlicasting message\n");
                    }
                }
                else
                {
                    RemoveEntry(did, dlgId, msg->clientID);
                }
            }
            else
            {
                DIDInfo* didInfo = NULL;
                ITS_INT hash = 0;
                ITS_OCTET key[6];

                memcpy(key, &msg->clientID, 4);
                memcpy(key + 4, &dlgId, sizeof(ITS_CTXT));
                hash = LocalHashKey(key, 6);
                
                ret = HASH_FindEntry(_SL_TCAP_lid_info, SL_ROUTING_INFO_LID,
                    hash, (ITS_POINTER *)&didInfo);
                
                did = didInfo->did;
            }
        }
#if defined(ANSI)
        else if ((dlg.ptype == TCAP_PT_TC_UNI_ANSI) && (dlgId < MAX_NUM_LID))
#elif defined(CCITT)
        else if ((dlg.ptype == TCAP_PT_TC_UNI_CCITT) && (dlgId < MAX_NUM_LID))
#endif
        {
            TCAP_AllocateDialogueId(SL_HANDLE, &did);
        }
        else
        {
#if defined(CCITT)
            if ((dlg.ptype == TCAP_PT_TC_END_CCITT) || 
                     (dlg.ptype == TCAP_PT_TC_P_ABORT_CCITT) ||
                     (dlg.ptype == TCAP_PT_TC_U_ABORT_CCITT))
#elif defined(ANSI)
            if ((dlg.ptype == TCAP_PT_TC_RESP_ANSI) || 
                     (dlg.ptype == TCAP_PT_TC_ABORT_ANSI))
#endif
            {
                if (redunClass)
                {
                    ITS_EVENT ev;
                    ITS_EVENT_INIT(&ev, ITS_MAB_SRC, 7);
                    ev.data[0] = TCAP_REMOVE_DOWN_ENTRY;
                    ev.data[1] = (did & 0xff00) >> 8;
                    ev.data[2] = (did & 0xff);
                    ev.data[3] = (msg->clientID & 0xff000000) >> 24;
                    ev.data[4] = (msg->clientID & 0x00ff0000) >> 16;
                    ev.data[5] = (msg->clientID & 0x0000ff00) >> 8;
                    ev.data[6] = (msg->clientID & 0x000000ff);
                    
                    if (DSM_MulticastStackEventToFtGroupMembers(
                        DSM_Mtp3FtGroupId,
                        ev,
                        ITS_MAB_SRC,
                        ITS_MAB_SRC) != ITS_SUCCESS )
                    {
                        printf("Error in Mutlicasting message\n");
                    }
                }
                else
                {
                    RemoveDownEntry(did, msg->clientID);
                }
            }
        }

        ITS_HDR hdr;
        hdr.context.dialogue_id = did;
        
        for (int i = 0; i < numCpts; i++)
        {
#ifdef CCITT
            cpt[i].u.invoke.opClass = 1;
#endif
            TCAP_SendComponent(SL_HANDLE, &hdr, &cpt[i]);
        }

        TCAP_SendDialogue(SL_HANDLE, &hdr, &dlg);
    }

    return ret;
}

int TcapMsgHandler::ProcessStackMsg(its::ITS_Event* evt)
{
    ITS_HDR hdr;

    if (TCAP_MSG_TYPE(&evt->GetEvent()) == ITS_TCAP_DLG)
    {
        TCAP_DLG dlg;

        ITS_EVENT ev;
        ITS_EVENT_INIT(&ev, evt->GetSource(), sizeof(TCAP_DLG)+sizeof(ITS_CTXT) + 1);

        memset (&dlg, 0, sizeof(TCAP_DLG));
        TCAP_ReceiveDialogue(SL_HANDLE, &evt->GetEvent(), &hdr, &dlg);

        TCAP_EncodeDlg(hdr.context.dialogue_id, &dlg, &ev); 
        TCAP_StoreTcapEvent(&ev);
#ifdef ANSI
        if ((dlg.ptype == TCAP_PT_TC_ABORT_ANSI) || 
            (dlg.ptype == TCAP_PT_TC_NOTICE_ANSI))
#elif defined (CCITT)
        if ((dlg.ptype == TCAP_PT_TC_P_ABORT_CCITT) || 
            (dlg.ptype == TCAP_PT_TC_U_ABORT_CCITT) ||
            (dlg.ptype == TCAP_PT_TC_NOTICE_CCITT))
#endif
        {
            EncodeMsgtoClient(hdr.context.dialogue_id);
        }

    }
    else if (TCAP_MSG_TYPE(&evt->GetEvent()) == ITS_TCAP_CPT)
    {
        TCAP_CPT cpt;
        int numCpt = 0, pos = 0;
        memset (&cpt, 0, sizeof(TCAP_CPT));

        ITS_EVENT ev;
        ITS_EVENT_INIT(&ev, evt->GetSource(), sizeof(TCAP_CPT)+sizeof(ITS_CTXT) + 1);

        TCAP_ReceiveComponent(SL_HANDLE, &evt->GetEvent(), &hdr, &cpt);

        TCAP_EncodeCpt(hdr.context.dialogue_id, &cpt, &ev);
        TCAP_StoreTcapEvent(&ev);
        
        if (cpt.last_component)
        {
            printf("encoding Msg to Client\n");
            EncodeMsgtoClient(hdr.context.dialogue_id);
        }
    }

    return ITS_SUCCESS;
}

int TcapMsgHandler::ProcessGcsMsg(ITS_EVENT* event)
{
    ITS_USHORT did = 0;
    ITS_USHORT lid = 0;
    ITS_UINT cid = 0;
    
    if (event->data[0] == TCAP_ADD_ENTRY)
    {
        did = (event->data[1] << 8) | event->data[2];
        lid = (event->data[3] << 8) | event->data[4];
        cid = (event->data[5] << 24) | (event->data[6] << 16) |
            (event->data[7] << 8) | (event->data[8]);
        AddEntry(did, lid, cid);
    }
    else if (event->data[0] == TCAP_REMOVE_ENTRY)
    {
        did = (event->data[1] << 8) | event->data[2];
        lid = (event->data[3] << 8) | event->data[4];
        cid = (event->data[5] << 24) | (event->data[6] << 16) |
            (event->data[7] << 8) | (event->data[8]);
        RemoveEntry(did, lid, cid);
    }
    else if (event->data[0] == TCAP_ADD_DOWN_ENTRY)
    {
        did = (event->data[1] << 8) | event->data[2];
        cid = (event->data[5] << 24) | (event->data[6] << 16) |
            (event->data[7] << 8) | (event->data[8]);
        AddDownEntry(did, cid);
    }
    else if (event->data[0] == TCAP_REMOVE_DOWN_ENTRY)
    {
        did = (event->data[1] << 8) | event->data[2];
        cid = (event->data[3] << 24) | (event->data[4] << 16) |
            (event->data[5] << 8) | (event->data[6]);
        RemoveDownEntry(did, cid);
    }

    return ITS_SUCCESS;
}

ITS_INT
TcapMsgHandler::LocalHashKey(ITS_OCTET *key, ITS_UINT klen)
{
    ITS_INT ret = 131;
    ITS_UINT i;

    for (i = 0; i < klen; i++)
    {
        if (key[i])
        {
            ret *= (key[i] << 3) | 1;
        }
        else
        {
            ret *= ret;
        }
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Storing TCAP components/dialogue in queue to be packed 
 *     and sent on receiving DLG/CPT request
 * 
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITS_INT
TcapMsgHandler::TCAP_StoreTcapEvent(ITS_EVENT *event)
{
    ITS_INT ret = ITS_SUCCESS;
    ret = MQUEUE_Enqueue(TCAP_primQueue, event, sizeof(ITS_EVENT));
    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Get the  TCAP components from the queue 
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITS_INT
TcapMsgHandler::TCAP_GetComponentFromQ(ITS_CTXT did, ITS_OCTET* data, ITS_USHORT *len)
{
    ITS_INT ret = ITS_SUCCESS;

    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;

    TCAP_CPT cpt;
    ITS_UINT  cpLen = 0;

    *len = 0;

    MQUEUE_Lock(TCAP_primQueue);

    for (entry = LIST_TAIL(TCAP_primQueue);
         entry != NULL;
         entry = prev)
    {
        ITS_CTXT cdid;
        ev = (ITS_EVENT *)entry->data;
        if ( ev->data == NULL)
        {
            continue;
        }

        memcpy(&cdid , &ev->data[1], sizeof(ITS_CTXT));

        if (ev->data[0] == ITS_TCAP_CPT && cdid == did)
        {
            MQUEUE_RemoveNoLock(TCAP_primQueue, entry);

            memcpy(&cpt, &ev->data[1 + sizeof(ITS_CTXT)], 
                   sizeof(TCAP_CPT));

            #if defined(ANSI) 
              ret = TCAP_CvtCPTToData_ANSI(&cpt, data + *len, &cpLen);
            #else
              ret = TCAP_CvtCPTToData_CCITT(&cpt, data + *len, &cpLen);
            #endif

            *len += cpLen;

            if (ret != ITS_SUCCESS)
            {
               printf("TCAP_CvtCPTToData Encode failed\n");

               len = 0;
            }
              
            prev = entry->prev;

            ITS_EVENT_TERM(ev);
            ITS_Free(entry->data);
            ITS_Free(entry);
        }
        else
        {
            prev = entry->prev;
        } 
    }

    MQUEUE_Unlock(TCAP_primQueue);
    
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Get the  TCAP Dialogue from the queue 
 *     
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITS_INT
TcapMsgHandler::TCAP_GetDialogueFromQ(ITS_CTXT did, TCAP_DLG *dlg)
{
    int ret = !ITS_SUCCESS;
    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;

    MQUEUE_Lock(TCAP_primQueue);

    for (entry = LIST_TAIL(TCAP_primQueue);
         entry != NULL;
         entry = prev)
    {
        ITS_CTXT cdid;
        ev = (ITS_EVENT *)entry->data;
        if ( ev->data == NULL)
        {
            continue;
        }

        memcpy(&cdid , &ev->data[1], sizeof(ITS_CTXT));

        if (ev->data[0] == ITS_TCAP_DLG && cdid == did)
        {
            MQUEUE_RemoveNoLock(TCAP_primQueue, entry);

            memcpy(dlg, &ev->data[1 + sizeof(ITS_CTXT)], 
                   sizeof(TCAP_DLG));

            prev = entry->prev;

            ITS_EVENT_TERM(ev);
            ITS_Free(entry->data);
            ITS_Free(entry);
            ret = ITS_SUCCESS;
            break;
        }
        else
        {
            prev = entry->prev;
        } 
    }

    MQUEUE_Unlock(TCAP_primQueue);
    
    return ret;
}

ITS_INT
TcapMsgHandler::TCAP_EncodeCpt(ITS_CTXT dlgId,
               TCAP_CPT *cpt,
               ITS_EVENT *ev)
{
    ITS_INT index = 0;

    ev->data[index++] = ITS_TCAP_CPT;
    memcpy(&ev->data[index], &dlgId, sizeof(ITS_CTXT));
    index = index + sizeof(ITS_CTXT);

    memcpy(&ev->data[index], cpt, sizeof(TCAP_CPT));
    index = index + sizeof(TCAP_CPT);

    ev->len = index;

    return ITS_SUCCESS;
}

ITS_INT
TcapMsgHandler::TCAP_EncodeDlg(ITS_CTXT  dlgId,
               TCAP_DLG  *dlg,
               ITS_EVENT *ev)
{
    ITS_INT index = 0;

    ev->data[index++] = ITS_TCAP_DLG;
    memcpy(&ev->data[index], &dlgId, sizeof(ITS_CTXT));
    index = index + sizeof(ITS_CTXT);

    memcpy(&ev->data[index], dlg, sizeof(TCAP_DLG));
    index = index + sizeof(TCAP_DLG);

    ev->len = index;

    return ITS_SUCCESS;
}


int TcapMsgHandler::EncodeMsgtoClient(ITS_CTXT did)
{
    TCAP_DLG dlg;
    ITS_CTXT dlgid = did;
    MABCL_MESSAGE msg;
    ITS_OCTET dlgData[512];
    ITS_OCTET cptData[512];
    ITS_USHORT cptDataLen = 0;
    ITS_UINT dlgDataLen = 0;
    ITS_UINT dlgLen = 0;
    ITS_INT ret = ITS_SUCCESS;

    int cid = 0;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    if (TCAP_GetDialogueFromQ(did, &dlg) == ITS_SUCCESS)
    {
#if defined(ANSI)
    if ((dlg.ptype != TCAP_PT_TC_UNI_ANSI) && (did < MAX_NUM_LID))
#elif defined(CCITT)
    if ((dlg.ptype != TCAP_PT_TC_UNI_CCITT) && (did < MAX_NUM_LID))
#endif
    {
        DIDInfo* didInfo = NULL;
        int hash = LocalHashKey((ITS_OCTET*)&did, 2);
        ret = HASH_FindEntry(_SL_TCAP_did_info, SL_ROUTING_INFO_DID,
                    hash, (ITS_POINTER *)&didInfo);
        if (ret == ITS_SUCCESS)
        {
            cid = didInfo->cid;
            dlgid = didInfo->lid;
        }

#if defined (CCITT)
        if ((dlg.ptype == TCAP_PT_TC_END_CCITT) || 
            (dlg.ptype == TCAP_PT_TC_P_ABORT_CCITT) ||
            (dlg.ptype == TCAP_PT_TC_U_ABORT_CCITT))
#elif defined (ANSI)
        if ((dlg.ptype == TCAP_PT_TC_RESP_ANSI) || 
            (dlg.ptype == TCAP_PT_TC_ABORT_ANSI))
#endif
        {
            if (redunClass)
            {
                ITS_EVENT ev;
                ITS_EVENT_INIT(&ev, ITS_MAB_SRC, 9);
                ev.data[0] = TCAP_REMOVE_ENTRY;
                ev.data[1] = (did & 0xff00) >> 8;
                ev.data[2] = (did & 0xff);
                ev.data[3] = (dlgid & 0xff00) >> 8;
                ev.data[4] = (dlgid & 0xff);
                ev.data[5] = (cid & 0xff000000) >> 24;
                ev.data[6] = (cid & 0x00ff0000) >> 16;
                ev.data[7] = (cid & 0x0000ff00) >> 8;
                ev.data[8] = (cid & 0x000000ff);
                
                
                if (DSM_MulticastStackEventToFtGroupMembers(
                    DSM_Mtp3FtGroupId,
                    ev,
                    ITS_MAB_SRC,
                    ITS_MAB_SRC) != ITS_SUCCESS )
                {
                    printf("Error in Mutlicasting message\n");
                }
            }
            else
            {
                RemoveEntry(did, dlgid, cid);
            }
        }
    }
    else
    {
#if defined(ANSI)
        if (dlg.ptype == TCAP_PT_TC_UNI_ANSI)
#elif defined(CCITT)
        if (dlg.ptype == TCAP_PT_TC_UNI_CCITT)
#endif
        {
            MABCL_TCAP tcapRInfo;
            
            tcapRInfo.dpc = dlg.u.begin.opc;
            tcapRInfo.lpc = dlg.u.begin.dpc;
#if defined (ANSI)
            tcapRInfo.ssn = dlg.u.begin.dest_addr.data[1];
#elif defined (CCITT)
            tcapRInfo.ssn = dlg.u.begin.dest_addr.data[3];
#endif
            tcapRInfo.ltid = did;
            
            
            cid = cHandler_->FindBestTCAPClient(&tcapRInfo);
        }
#if defined (CCITT)
        else if ((did > MAX_NUM_LID) && (dlg.ptype == TCAP_PT_TC_BEGIN_CCITT))
#elif defined (ANSI)
        else if ((did > MAX_NUM_LID) && 
            ((dlg.ptype == TCAP_PT_TC_QUERY_W_PERM_ANSI) ||
            (dlg.ptype == TCAP_PT_TC_QUERY_WO_PERM_ANSI)))
#endif
        {
            MABCL_TCAP tcapRInfo;
            
            tcapRInfo.dpc = dlg.u.begin.opc;
            tcapRInfo.lpc = dlg.u.begin.dpc;
#if defined (ANSI)
            tcapRInfo.ssn = dlg.u.begin.dest_addr.data[1];
#elif defined (CCITT)
            tcapRInfo.ssn = dlg.u.begin.dest_addr.data[3];
#endif
            tcapRInfo.ltid = did;
            
            
            cid = cHandler_->FindBestTCAPClient(&tcapRInfo);
            
            if (cid)
            {
                if (redunClass)
                {
                    ITS_EVENT ev;
                    ITS_EVENT_INIT(&ev, ITS_MAB_SRC, 7);
                    ev.data[0] = TCAP_ADD_DOWN_ENTRY;
                    ev.data[1] = (did & 0xff00) >> 8;
                    ev.data[2] = (did & 0xff);
                    ev.data[3] = (cid & 0xff000000) >> 24;
                    ev.data[4] = (cid & 0x00ff0000) >> 16;
                    ev.data[5] = (cid & 0x0000ff00) >> 8;
                    ev.data[6] = (cid & 0x000000ff);
                    
                    if (DSM_MulticastStackEventToFtGroupMembers(
                        DSM_Mtp3FtGroupId,
                        ev,
                        ITS_MAB_SRC,
                        ITS_MAB_SRC) != ITS_SUCCESS )
                    {
                        printf("Error in Mutlicasting message\n");
                    }
                }
                else
                {
                    AddDownEntry(did, cid);
                }
            }
        }
#if defined (CCITT)
        else if ((did > MAX_NUM_LID) && 
            ((dlg.ptype == TCAP_PT_TC_END_CCITT) || 
            (dlg.ptype == TCAP_PT_TC_P_ABORT_CCITT) ||
            (dlg.ptype == TCAP_PT_TC_U_ABORT_CCITT)))
#elif defined (ANSI)
            else if ((did > MAX_NUM_LID) && 
            ((dlg.ptype == TCAP_PT_TC_RESP_ANSI) || 
            (dlg.ptype == TCAP_PT_TC_ABORT_ANSI)))
#endif
        {
            if (cid)
            {
                if (redunClass)
                {
                    ITS_EVENT ev;
                    ITS_EVENT_INIT(&ev, ITS_MAB_SRC, 7);
                    ev.data[0] = TCAP_REMOVE_DOWN_ENTRY;
                    ev.data[1] = (did & 0xff00) >> 8;
                    ev.data[2] = (did & 0xff);
                    ev.data[3] = (cid & 0xff000000) >> 24;
                    ev.data[4] = (cid & 0x00ff0000) >> 16;
                    ev.data[5] = (cid & 0x0000ff00) >> 8;
                    ev.data[6] = (cid & 0x000000ff);
                    
                    if (DSM_MulticastStackEventToFtGroupMembers(
                        DSM_Mtp3FtGroupId,
                        ev,
                        ITS_MAB_SRC,
                        ITS_MAB_SRC) != ITS_SUCCESS )
                    {
                        printf("Error in Mutlicasting message\n");
                    }
                }
                else
                {
                    RemoveDownEntry(did, cid);
                }
            }
        }
        else
        {
            didcidMutex_->Acquire();
            DIDCIDMap::iterator iter = didcidMap_.find(did);
            if (iter != didcidMap_.end())
                cid = iter->second;
            didcidMutex_->Release();
        }
    }
    }

    dlgData[dlgDataLen++] = dlgid & 0xff;
    dlgData[dlgDataLen++] = (dlgid & 0xff00) >> 8;

    dlgData[dlgDataLen++] = dlg.ptype;

    cptDataLen = 0;

#ifdef ANSI
    if ((dlg.ptype != TCAP_PT_TC_ABORT_ANSI) || 
        (dlg.ptype != TCAP_PT_TC_NOTICE_ANSI))
#elif defined (CCITT)
    if ((dlg.ptype != TCAP_PT_TC_P_ABORT_CCITT) || 
        (dlg.ptype != TCAP_PT_TC_U_ABORT_CCITT) ||
        (dlg.ptype != TCAP_PT_TC_NOTICE_CCITT))
#endif
    {
        TCAP_GetComponentFromQ(did, cptData, &cptDataLen);
    }


    switch(dlg.ptype)
    {
        case TCPPT_TC_UNI:
        {
           /* qos parameter */ 
           memcpy(&dlgData[dlgDataLen], 
                  &dlg.u.uni.qos, sizeof(DLG_QOS));
           dlgDataLen = dlgDataLen +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           dlgData[dlgDataLen++] = dlg.u.uni.orig_addr.len & 0x00FF;
           dlgData[dlgDataLen++] = (dlg.u.uni.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&dlgData[dlgDataLen], 
                  dlg.u.uni.orig_addr.data,
                  dlg.u.uni.orig_addr.len); 

           dlgDataLen = dlgDataLen + dlg.u.uni.orig_addr.len; 

           /* copy the len of dest addr */
           dlgData[dlgDataLen++] = dlg.u.uni.dest_addr.len & 0x00FF;
           dlgData[dlgDataLen++] = (dlg.u.uni.dest_addr.len & 0xFF00) >> 8;

           /* copy dest addr */ 
           memcpy(&dlgData[dlgDataLen], 
                  dlg.u.uni.dest_addr.data,
                  dlg.u.uni.dest_addr.len); 

           dlgDataLen = dlgDataLen + dlg.u.uni.dest_addr.len; 

           /* copy the opc */ 
           memcpy(&dlgData[dlgDataLen],
                  &dlg.u.uni.opc,
                  sizeof(MTP3_POINT_CODE));

           dlgDataLen = dlgDataLen + sizeof(MTP3_POINT_CODE);

           /* copy the dpc */ 
           memcpy(&dlgData[dlgDataLen],
                  &dlg.u.uni.dpc,
                  sizeof(MTP3_POINT_CODE));

           dlgDataLen = dlgDataLen + sizeof(MTP3_POINT_CODE);
           break;
        }     
#if defined (ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#elif defined (CCITT)
        case TCAP_PT_TC_BEGIN_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlgData[dlgDataLen], 
                  &dlg.u.begin.qos, sizeof(DLG_QOS));
           dlgDataLen = dlgDataLen +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           dlgData[dlgDataLen++] = dlg.u.begin.orig_addr.len & 0x00FF;
           dlgData[dlgDataLen++] = (dlg.u.begin.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&dlgData[dlgDataLen], 
                  dlg.u.begin.orig_addr.data,
                  dlg.u.begin.orig_addr.len); 

           dlgDataLen = dlgDataLen + dlg.u.begin.orig_addr.len; 

           /* copy the len of dest addr */
           dlgData[dlgDataLen++] = dlg.u.begin.dest_addr.len & 0x00FF;
           dlgData[dlgDataLen++] = (dlg.u.begin.dest_addr.len & 0xFF00) >> 8;

           /* copy dest addr */ 
           memcpy(&dlgData[dlgDataLen], 
                  dlg.u.begin.dest_addr.data,
                  dlg.u.begin.dest_addr.len); 

           dlgDataLen = dlgDataLen + dlg.u.begin.dest_addr.len; 

           /* copy the opc */ 
           memcpy(&dlgData[dlgDataLen],
                  &dlg.u.begin.opc,
                  sizeof(MTP3_POINT_CODE));

           dlgDataLen = dlgDataLen + sizeof(MTP3_POINT_CODE);

           /* copy the dpc */ 
           memcpy(&dlgData[dlgDataLen],
                  &dlg.u.begin.dpc,
                  sizeof(MTP3_POINT_CODE));

           dlgDataLen = dlgDataLen + sizeof(MTP3_POINT_CODE); 
           break;
        }     
#if defined (ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#elif defined (CCITT)
        case TCAP_PT_TC_CONTINUE_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlgData[dlgDataLen], 
                  &dlg.u.cont.qos, sizeof(DLG_QOS));
           dlgDataLen = dlgDataLen +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           dlgData[dlgDataLen++] = dlg.u.cont.orig_addr.len & 0x00FF;
           dlgData[dlgDataLen++] = (dlg.u.cont.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&dlgData[dlgDataLen], 
                  dlg.u.cont.orig_addr.data,
                  dlg.u.cont.orig_addr.len); 

           dlgDataLen = dlgDataLen + dlg.u.cont.orig_addr.len; 

           /* copy the opc */ 
           memcpy(&dlgData[dlgDataLen],
                  &dlg.u.cont.opc,
                  sizeof(MTP3_POINT_CODE));

           dlgDataLen = dlgDataLen + sizeof(MTP3_POINT_CODE);
           break;
        }     
#if defined (ANSI)
        case TCPPT_TC_RESP:
#elif defined (CCITT)
        case TCAP_PT_TC_END_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlgData[dlgDataLen], 
                  &dlg.u.end.qos, sizeof(DLG_QOS));
           dlgDataLen = dlgDataLen +  sizeof(DLG_QOS);

           break;
        }
#if defined (ANSI)
        case TCPPT_TC_ABORT:
        case TCAP_PT_TC_NOTICE_ANSI:
#elif defined (CCITT)
        case TCAP_PT_TC_P_ABORT_CCITT:
        case TCAP_PT_TC_U_ABORT_CCITT:
        case TCAP_PT_TC_NOTICE_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlgData[dlgDataLen], 
                  &dlg.u.abort.qos, sizeof(DLG_QOS));
           dlgDataLen = dlgDataLen +  sizeof(DLG_QOS);

           break;
        }
    }

#if defined(ANSI)
    ret = TCAP_CvtDLGToData_ANSI(&dlg, &dlgData[dlgDataLen], 
        &dlgLen, cptData, cptDataLen,0, 0); 
#else
    ret = TCAP_CvtDLGToData_CCITT(&dlg, &dlgData[dlgDataLen], 
        &dlgLen, cptData, cptDataLen, 0, 0, 0, 0); 
#endif

    dlgDataLen += dlgLen;

    if (!dlgDataLen)
        return !ITS_SUCCESS;

    msg.u.tcapInfo.data = (ITS_OCTET*)malloc(dlgDataLen);
    memcpy(msg.u.tcapInfo.data, dlgData, dlgDataLen);
    msg.u.tcapInfo.len = dlgDataLen;

    printf("encoding msg to client : %d\n",cid);

    if (cid)
    {
        msg.clientID = cid;
        msg.msg_type = TCAP_MSG;
        
        cHandler_->SendMsg(&msg);
    }

    return ITS_SUCCESS;
}

int
TcapMsgHandler::UpdateAddrsAndQOS(TCAP_DLG *dlg, SCCP_ADDR origaddr, 
                        SCCP_ADDR destaddr, DLG_QOS qos, 
                        MTP3_POINT_CODE * opc, MTP3_POINT_CODE *dpc)
{
    switch(dlg->ptype)
    {
        case TCPPT_TC_UNI:
        {
           /* qos parameter */ 
           memcpy(&dlg->u.uni.qos, &qos, sizeof(DLG_QOS));

           /* copy the origaddr */
           dlg->u.uni.orig_addr.len = origaddr.len;
           memcpy(dlg->u.uni.orig_addr.data,
                   origaddr.data,
                   origaddr.len); 

           /* copy the destaddr */
           dlg->u.uni.dest_addr.len = destaddr.len;
           memcpy(dlg->u.uni.dest_addr.data,
                   destaddr.data,
                   destaddr.len); 

           /* copy the opc */ 
           memcpy(dlg->u.uni.opc.data,
                  opc,
                  sizeof(MTP3_POINT_CODE)); 

           /* copy the dpc */ 
           memcpy(dlg->u.uni.dpc.data,
                  dpc,
                  sizeof(MTP3_POINT_CODE)); 


           break;
        }
#if defined (ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#elif defined (CCITT)
        case TCAP_PT_TC_BEGIN_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlg->u.begin.qos, &qos, sizeof(DLG_QOS));

           /* copy the origaddr */
           dlg->u.begin.orig_addr.len = origaddr.len;
           memcpy(dlg->u.begin.orig_addr.data,
                   origaddr.data,
                   origaddr.len); 

           /* copy the destaddr */
           dlg->u.begin.dest_addr.len = destaddr.len;
           memcpy(dlg->u.begin.dest_addr.data,
                   destaddr.data,
                   destaddr.len); 

           /* copy the opc */ 
           memcpy(dlg->u.begin.opc.data,
                  opc, sizeof(MTP3_POINT_CODE)); 

           /* copy the dpc */ 
           memcpy(dlg->u.begin.dpc.data,
                  dpc, sizeof(MTP3_POINT_CODE)); 

           break;
        }     
#if defined (ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#elif defined (CCITT)
        case TCAP_PT_TC_CONTINUE_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlg->u.cont.qos, &qos, sizeof(DLG_QOS));

           /* copy the origaddr */
           dlg->u.cont.orig_addr.len = origaddr.len;
           memcpy(dlg->u.cont.orig_addr.data,
                   origaddr.data,
                   origaddr.len); 

           /* copy the opc */ 
           memcpy(dlg->u.cont.opc.data,
                  opc,
                  sizeof(MTP3_POINT_CODE)); 

           break;
        }
#if defined (ANSI)
        case TCPPT_TC_RESP:
#elif defined (CCITT)
        case TCAP_PT_TC_END_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlg->u.end.qos, &qos, sizeof(DLG_QOS));

           break;
        }
#if defined (ANSI)
        case TCPPT_TC_ABORT:
        case TCAP_PT_TC_NOTICE_ANSI:
#elif defined (CCITT)
        case TCAP_PT_TC_P_ABORT_CCITT:
        case TCAP_PT_TC_U_ABORT_CCITT:
        case TCAP_PT_TC_NOTICE_CCITT:
#endif
        {
           /* qos parameter */ 
           memcpy(&dlg->u.abort.qos, &qos, sizeof(DLG_QOS));

           break;
        }
    }
    return ITS_SUCCESS;
}

int
TcapMsgHandler::DecodeDlgComponent(TCAP_DLG  *dlg, ITS_CTXT *dlgid, 
                      TCAP_CPT  *cpt,  ITS_OCTET  *numCpts,
                      ITS_OCTET* tcapdata, ITS_UINT len)
{
    ITS_INT counter = 0;
    ITS_OCTET ptype = 0;
    SCCP_ADDR origaddr;
    SCCP_ADDR destaddr;
    ITS_INT ret = 0;

    ITS_OCTET *tp = NULL, *dp = NULL, *cp = NULL;
    ITS_BOOLEAN cpPresent = ITS_FALSE;   
    ITS_BOOLEAN isUNI = ITS_FALSE;
    DLG_QOS qos;

    ITS_OCTET *cpData, *comp;
    ITS_UINT cpTag, cpLen, cTag, cLen;
    ITS_UINT cptsLen = 0;
    ITS_INT extCptOctets = 0;
    ITS_OCTET index = 0;
    MTP3_POINT_CODE opc;
    MTP3_POINT_CODE dpc;

    counter = 0;
    *dlgid = 0;
    
    for(index = 0; index<sizeof(ITS_CTXT); index++)  
    {
      *dlgid |= tcapdata[counter++] << (8 * index);
    }

    /*extract the pkg type */
    ptype = (ITS_OCTET)tcapdata[counter++];

    /* qos parameter */ 
    memcpy(&qos, &tcapdata[counter],sizeof(DLG_QOS));
    counter = counter + sizeof(DLG_QOS);

    switch(ptype)
    {
#if defined (ANSI)
        case TCAP_PT_TC_UNI_ANSI:
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#elif defined (CCITT)
        case TCAP_PT_TC_UNI_CCITT:
        case TCAP_PT_TC_BEGIN_CCITT:
#endif
        {
            /* copy the len of orig addr */
            origaddr.len = tcapdata[counter++];
            origaddr.len |= tcapdata[counter++] << 8;  
            
            /* copy orig addr */ 
            memcpy(origaddr.data,
                   &tcapdata[counter],
                   origaddr.len);

            counter = counter + origaddr.len;  

            /* copy the len of dest addr */
            destaddr.len = tcapdata[counter++];
            destaddr.len |= tcapdata[counter++] << 8;  
               
            /* copy dest addr */ 
            memcpy(destaddr.data,
                   &tcapdata[counter],
                   destaddr.len);

            counter = counter + destaddr.len;  

            /* copy the opc */ 
            memcpy(&opc, &tcapdata[counter],
                   sizeof(MTP3_POINT_CODE));

            counter = counter + sizeof(MTP3_POINT_CODE);  

            /* copy the dpc */ 
            memcpy(&dpc, &tcapdata[counter],
                   sizeof(MTP3_POINT_CODE));

            counter = counter + sizeof(MTP3_POINT_CODE);  

            break;
        }     
#if defined (ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#elif defined (CCITT)
        case TCAP_PT_TC_CONTINUE_CCITT:
#endif
        {
            /* copy the len of orig addr */
            origaddr.len = tcapdata[counter++];
            origaddr.len |= tcapdata[counter++] << 8;  
            
            /* copy orig addr */ 
            memcpy(origaddr.data,
                   &tcapdata[counter],
                   origaddr.len);
                   counter = counter + origaddr.len;  

            /* copy the opc */ 
            memcpy(&opc, &tcapdata[counter],
                   sizeof(MTP3_POINT_CODE));

            counter = counter + sizeof(MTP3_POINT_CODE);  
        }     
    } 

    /*parse the dlg/component */
    #if defined(ANSI)
      ret = TCAP_FindParts_ANSI(&tcapdata[counter], (len - counter), 
                              &tp, &dp, &cp); 
    #else
      ret = TCAP_FindParts_CCITT(&tcapdata[counter], (len - counter), 
                                 &tp, &dp, &cp); 
    #endif

    if (cp != NULL && cp[0] == CSEQ_IDENT)
    {
        cpPresent = ITS_TRUE;
    }

    #if defined(ANSI)
       ret = TCAP_CvtDataToDLG_ANSI(dlg, &ptype, tp, dp, 
                                    cpPresent, (len - counter));
    #else            
       ret = TCAP_CvtDataToDLG_CCITT(dlg, &ptype, tp, dp, 
                                     cpPresent, (len - counter),0);
    #endif

    /* Update the address and QOS info */
    ret = UpdateAddrsAndQOS(dlg, origaddr, destaddr, 
                                  qos, &opc, &dpc);

    /*
     * uni(s) do not get a transaction context, nor do invokes
     * that they carry get an invoke context.
     */
    if (ptype == TCPPT_TC_UNI)
    {
        isUNI = ITS_TRUE;
    }

     /* cp --> Component Portion */
                                                                                
    cpData = cp;
#if defined (ANSI)
    if (ptype != TCAP_PT_TC_ABORT_ANSI && cp != NULL)
#elif defined (CCITT)
    if (((ptype != TCAP_PT_TC_P_ABORT_CCITT) || 
         (ptype == TCAP_PT_TC_U_ABORT_CCITT)) && (cp != NULL))
#endif
    {
        /* Get Compnt Sequence Tag */
        cpData += TCAP_GetTag(cpData, &cpTag, tp + (len - counter));
                                                                                
        /* Get Component Sequence length cpLen */
        cpData += TCAP_GetLength(cpData, &cpLen, tp + (len - counter), 
                                 ITS_TRUE);
                                                                                
        if((cpLen == 0) || ((cpData[0] == 0) && (cpData[1] == 0)))
        {
            if(isUNI)
            {
                /* error Handling */
            }
        }
                                                                                
        /* cpData:Component Sequence :: Parse Components one by one  */
        while (cpData < (cp + cpLen) && cpData[0] != 0 && cpData[1] != 0)
        {
            extCptOctets = 0;
            comp = cpData;
                                                                                
            /* Get Component Type Identifier */
            comp += TCAP_GetTag(comp, &cTag, tp + (len - counter));
                                                                                
            /* Get Component Length */
            extCptOctets = TCAP_GetLength(comp, &cLen, 
                                          tp + (len - counter), ITS_TRUE);
            comp += extCptOctets;
 
            #if defined(ANSI)
              ret = TCAP_CvtDataToCPT_ANSI(cpt, comp, cTag, cLen);
            #else
              ret = TCAP_CvtDataToCPT_CCITT(cpt, comp, cTag, cLen);
            #endif 

            *numCpts = *numCpts + 1;
            cptsLen += cLen + extCptOctets;
                                                                                
            if (cptsLen + *numCpts == cpLen)
            {
                cpt->last_component = 1;
            }
            else
            {
                cpt++; 
            }
          
             /* Move to next Component cLen Previous component Length*/
            cpData = comp + cLen;
        }
    }

    return ITS_SUCCESS;
}



int TcapMsgHandler::AddEntry(ITS_USHORT did, ITS_USHORT lid, ITS_UINT cid)
{
    ITS_OCTET key[6];
    ITS_INT hash = 0;
    ITS_INT ret = ITS_SUCCESS;
    
    printf("Add Entry\n");

    memcpy(key, &cid, 4);
    memcpy(key + 4, &lid, sizeof(ITS_CTXT));
    hash = LocalHashKey(key, 6);

    DIDInfo* didInfo1 = (DIDInfo*)malloc(sizeof(DIDInfo));
    didInfo1->cid = cid;
    didInfo1->lid = lid;
    didInfo1->did = did;
    
    ret = HASH_AddEntry(_SL_TCAP_lid_info, SL_ROUTING_INFO_LID,
        hash, (ITS_POINTER)didInfo1);

    if (ret == ITS_SUCCESS)
    {
        hash = LocalHashKey((ITS_OCTET*)&did, 2);
        
        DIDInfo* didInfo2 = (DIDInfo*)malloc(sizeof(DIDInfo));
        didInfo2->cid = cid;
        didInfo2->lid = lid;
        didInfo2->did = did;
        
        ret = HASH_AddEntry(_SL_TCAP_did_info, SL_ROUTING_INFO_DID,
            hash, (ITS_POINTER)didInfo2);
    }

    return ret;
}

int TcapMsgHandler::AddDownEntry(ITS_USHORT did, ITS_UINT cid)
{
    printf("Add Down Entry\n");
    didcidMutex_->Acquire();
    didcidMap_.insert(DIDCIDMap::value_type(did, cid));
    didcidMutex_->Release();

    return ITS_SUCCESS;
}

int TcapMsgHandler::RemoveEntry(ITS_USHORT did, ITS_USHORT lid, ITS_UINT cid)
{
    DIDInfo* didInfo = NULL;
    ITS_INT hash = 0;
    ITS_OCTET key[6];
    ITS_INT ret = ITS_SUCCESS;
 
    printf("Remove Entry\n");

    memcpy(key, &cid, 4);
    memcpy(key + 4, &lid, sizeof(ITS_CTXT));
    hash = LocalHashKey(key, 6);
    
    ret = HASH_FindEntry(_SL_TCAP_lid_info, SL_ROUTING_INFO_LID,
        hash, (ITS_POINTER *)&didInfo);
    
    if (ret == ITS_SUCCESS)
    {
        did = didInfo->did;
        
        ret = HASH_DeleteEntry(_SL_TCAP_lid_info, SL_ROUTING_INFO_LID, hash);
        
        hash = LocalHashKey((ITS_OCTET*)&did, 2);
        ret = HASH_DeleteEntry(_SL_TCAP_did_info, SL_ROUTING_INFO_DID, hash);
    }

    return ret;
}

int TcapMsgHandler::RemoveDownEntry(ITS_USHORT did, ITS_UINT cid)
{
    printf("Remove Down Entry\n");

    didcidMutex_->Acquire();
    DIDCIDMap::iterator iter = didcidMap_.find(did);
    if (iter != didcidMap_.end())
    {
        cid = iter->second;
        didcidMap_.erase(iter);
    }
    didcidMutex_->Release();

    return ITS_SUCCESS;
}

