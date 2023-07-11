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
 * ID: $Id: mab_isup_client.c,v 1.2 2005/05/26 11:12:54 mmanikandan Exp $
 *
 * LOG: $Log: mab_isup_client.c,v $
 * LOG: Revision 1.2  2005/05/26 11:12:54  mmanikandan
 * LOG: Support for CCITT.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#include <mab_isup_client.h>

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles reserve cic response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      ev    - ITS_EVENT * 
 *      reserveCic - ReserveCIC entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the return value ReserveCIC Api
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReceiveReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                 MABCL_ISUP_RSV_CIC_ENTRY *reserveCic)
{
    ITS_INT counter =1;

    memcpy(&reserveCic->mtp3, &ev->data[1], sizeof(MTP3_HEADER));

    counter += sizeof(MTP3_HEADER);
    
    reserveCic->cic = 0;
    reserveCic->cic |= ev->data[counter++];
    reserveCic->cic |= ev->data[counter++] << 8;

    reserveCic->cic_state = ev->data[counter++];

    reserveCic->vcic =  ITS_GET_CTXT(&ev->data[counter]);
    counter += sizeof(ITS_CTXT);

    reserveCic->ret = 0;
    reserveCic->ret |= ev->data[counter++];
    reserveCic->ret |= ev->data[counter++] << 8;
    reserveCic->ret |= ev->data[counter++] << 16;
    reserveCic->ret |= ev->data[counter++] << 24;

    return (reserveCic->ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles unreserveCic response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      ev    - ITS_EVENT * 
 *      unreserveCic - UnreserveCic Entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the return value UnReserveCIC Api
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReceiveUnReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                   MABCL_ISUP_UNRSV_CIC_ENTRY *unreserveCic)
{
    ITS_INT counter =1;

    memset(unreserveCic, 0, sizeof(MABCL_ISUP_UNRSV_CIC_ENTRY));

    memcpy(&unreserveCic->mtp3, &ev->data[1], sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);


    unreserveCic->cic |= ev->data[counter++];
    unreserveCic->cic |= ev->data[counter++] << 8;

    unreserveCic->ret = 0;
    unreserveCic->ret |= ev->data[counter++];
    unreserveCic->ret |= ev->data[counter++] << 8;
    unreserveCic->ret |= ev->data[counter++] << 16;
    unreserveCic->ret |= ev->data[counter++] << 24;

    return (unreserveCic->ret);
}

#if defined (ANSI)

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method encodes and sends the isup message to server
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_SendEvent_ANSI(ITS_HANDLE handle, ITS_OCTET type,
                    ITS_HDR *hdr, ITS_ISUP_IE_ANSI *ies,
                    ITS_INT ieCount, ISUP_MSG_DESC *desc)
{

    ITS_INT ret = ITS_SUCCESS;
    ITS_INT  i, j;
    ITS_ISUP_IE temp_ies[ITS_MAX_ISUP_IES];
    ITS_INT  index = 0; 
    ITS_EVENT evt,isupevt;
    MABCL_CONNECTION *conn = NULL;
    ITS_ULONG clid = 0; 

    ITS_EVENT_INIT(&evt, 1, (MTP2_MAX_MSG_SIZE +  
                    sizeof(ITS_ULONG) + sizeof(ITS_OCTET)));

    ITS_EVENT_INIT(&isupevt, 1, MTP2_MAX_MSG_SIZE);

    conn = (MABCL_CONNECTION*)handle;
    
    if (conn)
    {
        clid = conn->clid;  
    }

    evt.data[index++] = clid & 0x000000FF;
    evt.data[index++] = (clid & 0x0000FF00) >> 8;
    evt.data[index++] = (clid & 0x00FF0000) >> 16;
    evt.data[index++] = (clid & 0xFF000000) >> 24;

    /* fill the message type */ 
    evt.data[index++] = ISUP_MSG; 

    /* find the routing label, if present */
    for (i = 0, j = 0; i < ieCount; i++)
    {
        if (ies[i].param_id != ISUP_PRM_ROUTING_LABEL)
        {
            temp_ies[j++] = ies[i];
        }
    }

    ret = ISUP_MessageSanityCheck_ANSI(type, temp_ies, j, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    ret = ISUP_EncodeMTP3(ies, ieCount, type, &isupevt, hdr, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

   /* copy the payload */
    memcpy(&evt.data[index], isupevt.data, isupevt.len);
    
    /* free isup event */ 
    ITS_EVENT_TERM(&isupevt);
   
    index = index + isupevt.len;

    evt.len = index; 

    /* Fill the event src as from application*/
    evt.src = MABCL_ISUP_SRC;
    
    ret = MABCL_SendEvent(handle, &evt);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&evt);
    }
    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method decodes the evet and returns ISUP IEs.
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                       ITS_HDR *hdr, ITS_ISUP_IE_ANSI *ies,
                       ITS_INT *ieCount, ISUP_MSG_DESC *desc)

{
    ITS_INT ret = 0, i;
    hdr->type = ITS_ISUP;

    /* Get cic from event */

    hdr->context.cic = ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)];
    hdr->context.cic |= (ev->data[sizeof(ITS_OCTET) + sizeof(ITS_OCTET) +
                         sizeof(ITS_CTXT)] << 8);

    /* let remove the vcic and pass it on to the Decode func*/
    memmove( &ev->data[sizeof(ITS_OCTET)],
             &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
             ev->len - sizeof(ITS_CTXT));

    ev->len -=  sizeof(ITS_CTXT);

    ret = ISUP_DecodeMTP3(ies, ieCount, ev, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* These ies already includes the mtp3 header*/

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method reserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReserveCIC_ANSI(ITS_HANDLE h,
                     ITS_OCTET sio,
                     ITS_UINT  opc,
                     ITS_UINT  dpc,
                     ITS_USHORT cic,
                     ITS_OCTET* cic_state,
                     ITS_CTXT *vcic)
{
    /* Need to form an event out of these data */
    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter = 0;
    ITS_ULONG clid = 0;
    MABCL_CONNECTION *conn = NULL;
    ITS_EVENT_INIT(&event, MABCL_ISUP_SRC, sizeof(MTP3_HEADER) +
                   sizeof(ITS_USHORT) + 1 + sizeof(ITS_ULONG) + 
                   sizeof(ITS_OCTET));

    conn = (MABCL_CONNECTION*)h;

    if (conn)
    {
        clid = conn->clid;  
    }

    event.data[counter++] = clid & 0x000000FF;
    event.data[counter++] = (clid & 0x0000FF00) >> 8;
    event.data[counter++] = (clid & 0x00FF0000) >> 16;
    event.data[counter++] = (clid & 0xFF000000) >> 24;
    
    /* encode isup msg */
    event.data[counter] = ISUP_RSV_CIC_MSG;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return MABCL_SendEvent(h, &event);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method unreserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_UnReserveCIC_ANSI(ITS_HANDLE  h,
                       ITS_OCTET   sio,
                       ITS_UINT    opc,
                       ITS_UINT    dpc,
                       ITS_USHORT  cic)

{
    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter = 0;
    ITS_ULONG clid = 0;
    MABCL_CONNECTION *conn = NULL;
    ITS_EVENT_INIT(&event, MABCL_ISUP_SRC, sizeof(MTP3_HEADER) +
                   sizeof(ITS_USHORT) + 1 + sizeof(ITS_ULONG) + 
                   sizeof(ITS_OCTET));

    conn = (MABCL_CONNECTION*)h;
    if (conn)
    {
        clid = conn->clid;  
    }

    event.data[counter++] = clid & 0x000000FF;
    event.data[counter++] = (clid & 0x0000FF00) >> 8;
    event.data[counter++] = (clid & 0x00FF0000) >> 16;
    event.data[counter++] = (clid & 0xFF000000) >> 24;
    
    event.data[counter] = ISUP_URSV_CIC_MSG;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return MABCL_SendEvent(h, &event);
}

#endif

#if defined(CCITT)

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method encodes and sends the isup message to server
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_SendEvent_CCITT(ITS_HANDLE handle, ITS_OCTET type,
                     ITS_HDR *hdr, ITS_ISUP_IE_CCITT *ies,
                     ITS_INT ieCount, ISUP_MSG_DESC *desc)
{

    ITS_INT ret = ITS_SUCCESS;
    ITS_INT  i = 0, j = 0;
    ITS_ISUP_IE temp_ies[ITS_MAX_ISUP_IES];
    ITS_EVENT evt,isupevt;
    ITS_INT index = 0;
    ITS_ULONG clid = 0;
    MABCL_CONNECTION *conn = NULL;
    ITS_EVENT_INIT(&evt, 1, MTP2_MAX_MSG_SIZE + 
                  sizeof(ITS_ULONG) + sizeof(ITS_OCTET));

    ITS_EVENT_INIT(&isupevt, 1, MTP2_MAX_MSG_SIZE);

    conn = (MABCL_CONNECTION*)handle;
    if (conn)
    {
        clid = conn->clid;  
    }
    
    evt.data[index++] = clid & 0x000000FF;
    evt.data[index++] = (clid & 0x0000FF00) >> 8;
    evt.data[index++] = (clid & 0x00FF0000) >> 16;
    evt.data[index++] = (clid & 0xFF000000) >> 24;

    /* fill the message type */ 
    evt.data[index++] = ISUP_MSG; 

    /* find the routing label, if present */
    for (i = 0, j = 0; i < ieCount; i++)
    {
        if (ies[i].param_id != ISUP_PRM_ROUTING_LABEL)
        {
            temp_ies[j++] = ies[i];
        }
    }

    ret = ISUP_MessageSanityCheck_CCITT(type, temp_ies, j, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    ret = ISUP_EncodeMTP3(ies, ieCount, type, &isupevt, hdr, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

   /* copy the payload */
    memcpy(&evt.data[index], isupevt.data, isupevt.len);

    /* free isup event */ 
    ITS_EVENT_TERM(&isupevt);
   
    index = index + isupevt.len;

    evt.len = index; 

    /* Fill the event src as from application*/
    evt.src = MABCL_ISUP_SRC;

    ret = MABCL_SendEvent(handle, &evt);

    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&evt);
    }
    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method decodes the evet and returns ISUP IEs.
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                        ITS_HDR *hdr, ITS_ISUP_IE_CCITT *ies,
                        ITS_INT *ieCount, ISUP_MSG_DESC *desc)

{
    ITS_INT ret = 0;
    hdr->type = ITS_ISUP;

    /* Get cic from event */
    hdr->context.cic |= ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)];
    hdr->context.cic |= (ev->data[sizeof(ITS_OCTET) + sizeof(ITS_OCTET) +
                         sizeof(ITS_CTXT)] << 8);

    /* let remove the vcic and pass it on to the Decode func*/
    memmove( &ev->data[sizeof(ITS_OCTET)],
             &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
             ev->len - sizeof(ITS_CTXT));

    ev->len -=  sizeof(ITS_CTXT);

    ret = ISUP_DecodeMTP3(ies, ieCount, ev, desc);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* These ies already includes the mtp3 header*/

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method reserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReserveCIC_CCITT(ITS_HANDLE h,
                      ITS_OCTET sio,
                      ITS_UINT  opc,
                      ITS_UINT  dpc,
                      ITS_USHORT cic,
                      ITS_OCTET* cic_state,
                      ITS_CTXT *vcic)
{
    /* Need to form an event out of these data */
    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter = 0;
    ITS_ULONG clid = 0;
    MABCL_CONNECTION *conn;

    ITS_EVENT_INIT(&event, MABCL_ISUP_SRC, sizeof(MTP3_HEADER) +
                   sizeof(ITS_USHORT) + 1 + sizeof(ITS_ULONG) + 
                   sizeof(ITS_OCTET));

    conn = (MABCL_CONNECTION*)h;

    if (conn)
    {
        clid = conn->clid;  
    }

    event.data[counter++] = clid & 0x000000FF;
    event.data[counter++] = (clid & 0x0000FF00) >> 8;
    event.data[counter++] = (clid & 0x00FF0000) >> 16;
    event.data[counter++] = (clid & 0xFF000000) >> 24;
    
    event.data[counter] = ISUP_RSV_CIC_MSG;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return MABCL_SendEvent(h, &event);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method unreserves the cic
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_UnReserveCIC_CCITT(ITS_HANDLE h,
                        ITS_OCTET sio,
                        ITS_UINT opc,
                        ITS_UINT dpc,
                        ITS_USHORT cic)

{

    ITS_EVENT event;
    MTP3_HEADER mtp3;
    ITS_INT counter = 0;
    ITS_ULONG clid = 0;
    MABCL_CONNECTION *conn =NULL;

    ITS_EVENT_INIT(&event, MABCL_ISUP_SRC, sizeof(MTP3_HEADER) +
                   sizeof(ITS_USHORT) + 1 + sizeof(ITS_ULONG) + 
                   sizeof(ITS_OCTET));

    conn = (MABCL_CONNECTION*)h;
    if (conn)
    {
        clid = conn->clid;  
    }

    event.data[counter++] = clid & 0x000000FF;
    event.data[counter++] = (clid & 0x0000FF00) >> 8;
    event.data[counter++] = (clid & 0x00FF0000) >> 16;
    event.data[counter++] = (clid & 0xFF000000) >> 24;
    
    event.data[counter] = ISUP_URSV_CIC_MSG;

    counter++;

    memset(&mtp3, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
    mtp3.sio = sio;

    memcpy(&event.data[counter], &mtp3, sizeof(MTP3_HEADER));
    counter += sizeof(MTP3_HEADER);

    event.data[counter++] = cic & 0xFFU;
    event.data[counter++] = (cic >> 8) & 0xFFU;

    /* Event Length */
    event.len = counter;

    /* Call Write Event */
    return MABCL_SendEvent(h, &event);
}
#endif
