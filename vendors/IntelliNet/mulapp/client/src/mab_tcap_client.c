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
 * ID: $Id: mab_tcap_client.c,v 1.1 2005/05/25 10:13:58 mmanikandan Exp $
 *
 * LOG: $Log: mab_tcap_client.c,v $
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#include <mab_tcap_client.h>

extern MLIST_Manager *TCAP_primQueue;
static ITS_CTXT nextDID = 1;

/****************************** ANSI VERSION *******************************/

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
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
MABCL_DLLAPI ITS_INT
TCAP_AllocateDialogueId_ANSI(ITS_HANDLE handle ,ITS_CTXT *did)
{
    if (nextDID >= MAX_NUM_LID)
    {
        nextDID = 1;
    }
    *did = nextDID;

    nextDID++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an SCCP message
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
 *      None.
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
SCCP_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                       ITS_SCCP_IE *ies, ITS_INT *ieCount,
                       SCCP_MSG_DESC *desc)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an SCCP message.
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
 *      None.
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
SCCP_SendEvent_ANSI(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                    ITS_SCCP_IE *ies, ITS_INT ieCount,
                    SCCP_MSG_DESC *desc)
{
    return (ITS_SUCCESS);
}
                                                                                

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP component.
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
MABCL_DLLAPI ITS_INT TCAP_SendComponent_ANSI(ITS_HANDLE handle,
                                      ITS_HDR* hdr,
                                      TCAP_CPT* cpt)
{
    ITS_EVENT ev;
    ITS_INT ret = 0;

    ITS_EVENT_INIT(&ev, MABCL_TCAP_SRC, MAX_CPT_SIZE);

    TCAP_EncodeCpt(hdr->context.dialogue_id , cpt, &ev);

    /* store components */ 
    ret = TCAP_StoreTcapEvent(&ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP dialogue.
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
MABCL_DLLAPI ITS_INT
TCAP_SendDialogue_ANSI(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    ITS_EVENT ev;
    ITS_INT   ret = 0; 
    ITS_ULONG clientid = 0;
    MABCL_CONNECTION *conn = NULL;

    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC, MAX_TCAP_MSG_EVT);

    conn = (MABCL_CONNECTION*)handle;
    
    if (conn)
    {
        clientid = conn->clid;
    }

    TCAP_EncodeDlgCptFrame(clientid , TCAP_MSG, 
                           hdr->context.dialogue_id, 
                           dlg, &ev);
    
    /* Fill the event src as from application*/
    ev.src = MABCL_TCAP_SRC;

    ret = MABCL_SendEvent(handle, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive TCAP component.
 *
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
MABCL_DLLAPI ITS_INT
TCAP_ReceiveComponent_ANSI(ITS_HANDLE handle, ITS_EVENT *event,
                           ITS_HDR *hdr, TCAP_CPT *cpt)
{
    hdr->type = ITS_TCAP_ANSI;
    memcpy(&hdr->context.dialogue_id, &event->data[1],sizeof(ITS_CTXT));
    //hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);
                                                                                
    memcpy(cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));
                                                                                
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP dialogue.
 *
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
MABCL_DLLAPI ITS_INT
TCAP_ReceiveDialogue_ANSI(ITS_HANDLE handle, ITS_EVENT *event,
                          ITS_HDR *hdr, TCAP_DLG *dlg)
{
    hdr->type = ITS_TCAP_ANSI;
    //hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);
    memcpy(&hdr->context.dialogue_id, &event->data[1],sizeof(ITS_CTXT));
                                                                                
    memcpy(dlg, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_DLG));
                                                                                
    return (ITS_SUCCESS);
}

/****************************** CCITT VERSION *******************************/

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate TCAP dialogueId.
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
MABCL_DLLAPI ITS_INT
TCAP_AllocateDialogueId_CCITT(ITS_HANDLE handle ,ITS_CTXT *did)
{
    if (nextDID >= MAX_NUM_LID)
    {
        nextDID = 1;
    }
    *did = nextDID;

    nextDID++;

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an SCCP message
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
 *      None.
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
SCCP_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                       ITS_SCCP_IE *ies, ITS_INT *ieCount,
                       SCCP_MSG_DESC *desc)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an SCCP message.
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
 *      None.
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
SCCP_SendEvent_CCITT(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                    ITS_SCCP_IE *ies, ITS_INT ieCount,
                    SCCP_MSG_DESC *desc)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP component.
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
MABCL_DLLAPI ITS_INT TCAP_SendComponent_CCITT(ITS_HANDLE handle,
                                       ITS_HDR* hdr,
                                       TCAP_CPT* cpt)
{
    ITS_EVENT ev;
    ITS_INT ret = 0;

    ITS_EVENT_INIT(&ev, MABCL_TCAP_SRC, MAX_CPT_SIZE);

    TCAP_EncodeCpt(hdr->context.dialogue_id , cpt, &ev);

    /* store components */ 
    ret = TCAP_StoreTcapEvent(&ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP dialogue.
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
MABCL_DLLAPI ITS_INT
TCAP_SendDialogue_CCITT(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    ITS_EVENT ev;
    ITS_INT   ret = 0; 
    ITS_ULONG clientid = 0;
    MABCL_CONNECTION *conn = NULL;

    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC, MAX_TCAP_MSG_EVT);

    conn = (MABCL_CONNECTION*)handle;

    if (conn)
    {
        clientid = conn->clid;
    }
    
    TCAP_EncodeDlgCptFrame(clientid , TCAP_MSG, 
                           hdr->context.dialogue_id, 
                           dlg, &ev);
    
    /* Fill the event src as from application*/
    ev.src = MABCL_TCAP_SRC;

    ret = MABCL_SendEvent(handle, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP component.
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
MABCL_DLLAPI ITS_INT
TCAP_ReceiveComponent_CCITT(ITS_HANDLE handle, ITS_EVENT *event,
                            ITS_HDR *hdr, TCAP_CPT *cpt)
{
    hdr->type = ITS_TCAP_CCITT;
   // hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);
    memcpy(&hdr->context.dialogue_id, &event->data[1],sizeof(ITS_CTXT));
                                                                                
    memcpy(cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));
                                                                                
    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP dialogue
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
MABCL_DLLAPI ITS_INT
TCAP_ReceiveDialogue_CCITT(ITS_HANDLE handle, ITS_EVENT *event,
                           ITS_HDR *hdr, TCAP_DLG *dlg)
{
    hdr->type = ITS_TCAP_CCITT;
    memcpy(&hdr->context.dialogue_id, &event->data[1],sizeof(ITS_CTXT));
    //hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);
                                                                                
    memcpy(dlg, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_DLG));
                                                                                
    return (ITS_SUCCESS);
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
MABCL_DLLAPI ITS_INT
TCAP_StoreTcapEvent(ITS_EVENT *event)
{
    ITS_INT ret;
    ret = MQUEUE_Enqueue(TCAP_primQueue, event, sizeof(ITS_EVENT));
    if (ret != ITS_SUCCESS)
    {
        /* Unable to Enqueue to TCAP primQueue */
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
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
MABCL_DLLAPI ITS_INT
TCAP_GetComponentFromQ(ITS_CTXT did, ITS_EVENT *evPtr)
{
    ITS_BOOLEAN isComp = ITS_FALSE;
    ITS_INT ret = ITS_SUCCESS;

    QUEUE_Msg *entry, *prev = NULL;
    ITS_EVENT *ev;

    TCAP_CPT cpt;
    ITS_INT  noCpts = 0;
    ITS_OCTET cp[MAX_TCAP_CPT_SIZE];
    ITS_OCTET cpList[MAX_TCAP_CPT_SIZE * MAX_NO_OF_TCAP_CPTS];
    ITS_UINT  cpLen = 0, cptsLen = 0;

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
              ret = TCAP_CvtCPTToData_ANSI(&cpt, cp, &cpLen);
            #else
              ret = TCAP_CvtCPTToData_CCITT(&cpt, cp, &cpLen);
            #endif

            if (ret != ITS_SUCCESS)
            {
               printf("TCAP_CvtCPTToData Encode failed\n");
            }
            else
            {
               noCpts++;
               if (noCpts > 1)
               {
                  memmove(&cpList[cpLen], cpList, cptsLen);
               }
               memcpy(cpList, cp, cpLen);
               cptsLen += (cpLen);

               isComp = ITS_TRUE;
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

    /*set the number of components*/
    if (isComp)
    {
        memcpy(evPtr->data, cpList, cptsLen);
        evPtr->len = cptsLen;
    }    
    else
    {
        evPtr->len = 0;
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
MABCL_DLLAPI ITS_INT
TCAP_GetDialogueFromQ(ITS_CTXT did, TCAP_DLG *dlg)
{
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
 *     Encode component 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeCpt(ITS_CTXT dlgId,
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

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode dialogue 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeDlg(ITS_CTXT  dlgId,
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

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode Dlg and components to Msg frame 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeDlgCptFrame(ITS_ULONG clid , ITS_OCTET msgType,
                       ITS_CTXT dlgid,  TCAP_DLG *dlg, 
                       ITS_EVENT *ev)
{
    ITS_INT index = 0;
    ITS_INT i = 0;
    ITS_INT ret = ITS_SUCCESS; 
    ITS_EVENT cptev;
    ITS_EVENT_INIT(&cptev, ITS_TCAP_SRC, MAX_NUM_CPT_SIZE);
    ITS_OCTET tp[MAX_TCAP_TRANS_SIZE];
    ITS_UINT tpLen = 0;
    ITS_CTXT dialogId = 0;

    /* copy the clientid */
    ev->data[index++] = clid & 0x000000FF;
    ev->data[index++] = (clid & 0x0000FF00) >> 8;
    ev->data[index++] = (clid & 0x00FF0000) >> 16;
    ev->data[index++] = (clid & 0xFF000000) >> 24;

    /* copy the message type */ 
    ev->data[index++] = msgType;

    /* copy the dlgid */
    dialogId = dlgid;
    for(i = 0 ;i <sizeof(ITS_CTXT);++i)
    {
       ev->data[index++] = (dialogId & 0xFF);
       dialogId = dialogId >> 8;
    }
   
    /* copy the pkage type*/
    ev->data[index++] = (ITS_OCTET)dlg->ptype;

    /*based on pkage type encode SCCP_ORIG,
     * SCCP_DEST, OPC,DPC */

    switch(dlg->ptype)
    {
        case TCPPT_TC_UNI:
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg->u.uni.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           ev->data[index++] = dlg->u.uni.orig_addr.len & 0x00FF;
           ev->data[index++] = (dlg->u.uni.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&ev->data[index], 
                  dlg->u.uni.orig_addr.data,
                  dlg->u.uni.orig_addr.len); 

           index = index + dlg->u.uni.orig_addr.len; 

           /* copy the len of dest addr */
           ev->data[index++] = dlg->u.uni.dest_addr.len & 0x00FF;
           ev->data[index++] = (dlg->u.uni.dest_addr.len & 0xFF00) >> 8;

           /* copy dest addr */ 
           memcpy(&ev->data[index], 
                  dlg->u.uni.dest_addr.data,
                  dlg->u.uni.dest_addr.len); 

           index = index + dlg->u.uni.dest_addr.len; 

           /* copy the opc */ 
           memcpy(&ev->data[index],
                  &dlg->u.uni.opc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);

           /* copy the dpc */ 
           memcpy(&ev->data[index],
                  &dlg->u.uni.dpc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);
           break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_BEGIN:
#elif defined(ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg->u.begin.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           ev->data[index++] = dlg->u.begin.orig_addr.len & 0x00FF;
           ev->data[index++] = (dlg->u.begin.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&ev->data[index], 
                  dlg->u.begin.orig_addr.data,
                  dlg->u.begin.orig_addr.len); 

           index = index + dlg->u.begin.orig_addr.len; 

           /* copy the len of dest addr */
           ev->data[index++] = dlg->u.begin.dest_addr.len & 0x00FF;
           ev->data[index++] = (dlg->u.begin.dest_addr.len & 0xFF00) >> 8;

           /* copy dest addr */ 
           memcpy(&ev->data[index], 
                  dlg->u.begin.dest_addr.data,
                  dlg->u.begin.dest_addr.len); 

           index = index + dlg->u.begin.dest_addr.len; 

           /* copy the opc */ 
           memcpy(&ev->data[index],
                  &dlg->u.begin.opc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);

           /* copy the dpc */ 
           memcpy(&ev->data[index],
                  &dlg->u.begin.dpc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE); 
           break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_CONTINUE:
#elif defined(ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg->u.cont.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);
           /* qos parameter */ 

           /* copy the len of orig addr */
           ev->data[index++] = dlg->u.cont.orig_addr.len & 0x00FF;
           ev->data[index++] = (dlg->u.cont.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&ev->data[index], 
                  dlg->u.cont.orig_addr.data,
                  dlg->u.cont.orig_addr.len); 

           index = index + dlg->u.cont.orig_addr.len; 

           /* copy the opc */ 
           memcpy(&ev->data[index],
                  &dlg->u.cont.opc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);
           break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_END:
#elif defined(ANSI)
        case TCPPT_TC_RESP:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg->u.end.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           break;
        }
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_U_ABORT:
#elif defined(ANSI)
        case TCPPT_TC_ABORT:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg->u.abort.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           break;
        }
    }

    /* Get all the components */
    ret = TCAP_GetComponentFromQ(dlgid , &cptev); 

    /* check if cpt present */
    if (cptev.len)
    {
       #if defined(ANSI)
         ret = TCAP_CvtDLGToData_ANSI(dlg, tp, 
                                      &tpLen, cptev.data, 
                                      cptev.len,0, 0); 
       #else
         ret = TCAP_CvtDLGToData_CCITT(dlg, tp, 
                                      &tpLen, cptev.data, 
                                      cptev.len, 0, 0, 0, 0); 
       #endif
    }
    else
    {
       #if defined(ANSI)
         ret = TCAP_CvtDLGToData_ANSI(dlg, tp, 
                                      &tpLen, NULL, 
                                      0, 0, 0); 
       #else
         ret = TCAP_CvtDLGToData_CCITT(dlg, tp, 
                                      &tpLen, NULL, 
                                      0, 0, 0, 0, 0); 
       #endif
    }

    /* copy the encoded buffer */
    memcpy(&ev->data[index], tp ,tpLen);

    index = index + tpLen;

    ITS_EVENT_TERM(&cptev);

    /* Fill the vent src as from application*/
    ev->len = index;

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     Encode Dlg and components to Msg frame 
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
MABCL_DLLAPI ITS_INT
TCAP_EncodeMsgFrame(ITS_ULONG clid , ITS_OCTET msgType,
                    ITS_CTXT dlgid,  TCAP_CPT *cpt,
                    ITS_EVENT *ev)
{
    ITS_INT index = 0;
    ITS_INT i = 0;
    ITS_INT ret = ITS_SUCCESS; 
    TCAP_DLG  dlg;
    ITS_EVENT cptev;
    ITS_INT compIndex = 0;
    ITS_OCTET cp[MAX_TCAP_CPT_SIZE];
    ITS_OCTET cpList[MAX_TCAP_CPT_SIZE * MAX_NO_OF_TCAP_CPTS];
    ITS_OCTET tp[MAX_TCAP_TRANS_SIZE];
    ITS_UINT  tpLen = 0, cpLen = 0;
    ITS_CTXT dialogId = 0;

    ITS_EVENT_INIT(&cptev, ITS_TCAP_SRC, MAX_NUM_CPT_SIZE);

    /* copy the clientid */
    ev->data[index++] = clid & 0x000000FF;
    ev->data[index++] = (clid & 0x0000FF00) >> 8;
    ev->data[index++] = (clid & 0x00FF0000) >> 16;
    ev->data[index++] = (clid & 0xFF000000) >> 24;

    /* copy the message type */ 
    ev->data[index++] = msgType;

    /* copy the dlgid */
    dialogId = dlgid; 
    for(i = 0 ;i <sizeof(ITS_CTXT);++i)
    {
       ev->data[index++] = (dialogId & 0xFF);
       dialogId = dialogId >> 8;
    }

    /* Get the Dialogue */
    ret = TCAP_GetDialogueFromQ(dlgid , &dlg); 

    /* copy the pkage type*/
    ev->data[index++] = (ITS_OCTET)dlg.ptype;

    /*based on pkage type encode SCCP_ORIG,
     * SCCP_DEST, OPC,DPC */

    switch(dlg.ptype)
    {
        case TCPPT_TC_UNI:
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg.u.uni.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           ev->data[index++] = dlg.u.uni.orig_addr.len & 0x00FF;
           ev->data[index++] = (dlg.u.uni.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&ev->data[index], 
                  dlg.u.uni.orig_addr.data,
                  dlg.u.uni.orig_addr.len); 

           index = index + dlg.u.uni.orig_addr.len; 

           /* copy the len of dest addr */
           ev->data[index++] = dlg.u.uni.dest_addr.len & 0x00FF;
           ev->data[index++] = (dlg.u.uni.dest_addr.len & 0xFF00) >> 8;

           /* copy dest addr */ 
           memcpy(&ev->data[index], 
                  dlg.u.uni.dest_addr.data,
                  dlg.u.uni.dest_addr.len); 

           index = index + dlg.u.uni.dest_addr.len; 

           /* copy the opc */ 
           memcpy(&ev->data[index],
                  &dlg.u.uni.opc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);

           /* copy the dpc */ 
           memcpy(&ev->data[index],
                  &dlg.u.uni.dpc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);
           break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_BEGIN:
#elif defined(ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg.u.begin.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           ev->data[index++] = dlg.u.begin.orig_addr.len & 0x00FF;
           ev->data[index++] = (dlg.u.begin.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&ev->data[index], 
                  dlg.u.begin.orig_addr.data,
                  dlg.u.begin.orig_addr.len); 

           index = index + dlg.u.begin.orig_addr.len; 

           /* copy the len of dest addr */
           ev->data[index++] = dlg.u.begin.dest_addr.len & 0x00FF;
           ev->data[index++] = (dlg.u.begin.dest_addr.len & 0xFF00) >> 8;

           /* copy dest addr */ 
           memcpy(&ev->data[index], 
                  dlg.u.begin.dest_addr.data,
                  dlg.u.begin.dest_addr.len); 

           index = index + dlg.u.begin.dest_addr.len; 

           /* copy the opc */ 
           memcpy(&ev->data[index],
                  &dlg.u.begin.opc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);

           /* copy the dpc */ 
           memcpy(&ev->data[index],
                  &dlg.u.begin.dpc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE); 
           break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_CONTINUE:
#elif defined(ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg.u.cont.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           /* copy the len of orig addr */
           ev->data[index++] = dlg.u.cont.orig_addr.len & 0x00FF;
           ev->data[index++] = (dlg.u.cont.orig_addr.len & 0xFF00) >> 8;

           /* copy orig addr */ 
           memcpy(&ev->data[index], 
                  dlg.u.cont.orig_addr.data,
                  dlg.u.cont.orig_addr.len); 

           index = index + dlg.u.cont.orig_addr.len; 

           /* copy the opc */ 
           memcpy(&ev->data[index],
                  &dlg.u.cont.opc,
                  sizeof(MTP3_POINT_CODE));

           index = index + sizeof(MTP3_POINT_CODE);
           break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_END:
#elif defined(ANSI)
        case TCPPT_TC_RESP:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg.u.end.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           break;
        }
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_U_ABORT:
#elif defined(ANSI)
        case TCPPT_TC_ABORT:
#endif
        {
           /* qos parameter */ 
           memcpy(&ev->data[index], 
                  &dlg.u.abort.qos, sizeof(DLG_QOS));
           index = index +  sizeof(DLG_QOS);

           break;
        }
    }
    
    /* Get all the components */
    ret = TCAP_GetComponentFromQ(dlgid , &cptev); 

    /* check if cpt present */
    if (cptev.len)
    {
        memcpy(cpList ,cptev.data , cptev.len); 
        compIndex = cptev.len;
    }

    ITS_EVENT_TERM(&cptev);

    #if defined(ANSI) 
       ret = TCAP_CvtCPTToData_ANSI(cpt, cp, &cpLen);
    #else
       ret = TCAP_CvtCPTToData_CCITT(cpt, cp, &cpLen);
    #endif

    if (ret != ITS_SUCCESS)
    {
       printf("TCAP_CvtCPTToData Encode failed\n");
    }

    /* check if cpt present */
    if (cpLen)
    {
       memcpy(&cpList[compIndex], cp, cpLen);

       cpLen = cpLen + cptev.len; 

       #if defined(ANSI)
         ret = TCAP_CvtDLGToData_ANSI(&dlg, tp, 
                                      &tpLen, cpList, 
                                      cpLen, 0, 0); 
       #else
         ret = TCAP_CvtDLGToData_CCITT(&dlg, tp, 
                                       &tpLen, cpList, 
                                       cpLen, 0, 0, 0, 0); 
       #endif
    }
    else
    {
       #if defined(ANSI)
         ret = TCAP_CvtDLGToData_ANSI(&dlg, tp, 
                                      &tpLen, NULL, 
                                      0, 0, 0); 
       #else
         ret = TCAP_CvtDLGToData_CCITT(&dlg, tp, 
                                      &tpLen, NULL, 
                                      0, 0, 0, 0, 0); 
       #endif
    }

    /* copy the encoded buffer */
    memcpy(&ev->data[index], tp ,tpLen);

    index = index + tpLen;

    /* Fill the vent src as from application*/
    ev->len = index;

    return ret;
}
