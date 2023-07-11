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
 * $Id: serverimpl.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 * $Log: serverimpl.c,v $
 * Revision 9.1  2005/03/23 12:54:27  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 09:41:22  cvsadmin
 * PR6.4.2 sources propagated to Current.
 *
 * Revision 1.1.2.5.6.2  2004/01/27 14:30:59  sjaddu
 * Changes for active-backup configuration.
 *
 * Revision 1.1.2.5.6.1  2004/01/05 10:01:25  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.5.2.5  2003/10/31 06:03:23  sjaddu
 * memset added before getnext event.
 *
 * Revision 1.1.2.5.2.4  2003/09/13 06:42:42  akumar
 * Replaced printf with Trace Macros.
 *
 * Revision 1.1.2.5.2.3  2003/08/29 09:51:31  akumar
 * Modifications for Routing and Deregistration APi.
 *
 * Revision 1.1.2.5.2.2  2003/08/28 15:40:01  sjaddu
 * Bug fix for deregistration ...
 *
 * Revision 1.1.2.5.2.1  2003/08/26 12:48:45  sjaddu
 * Redunadnacy changes done.
 *
 * Revision 1.1.2.5  2003/06/30 05:03:35  sjaddu
 * Modefied send ReserveCIC response.
 *
 * Revision 1.1.2.4  2003/06/25 14:38:12  sjaddu
 * Removed warnings.
 *
 * Revision 1.1.2.3  2003/06/20 11:16:13  sjaddu
 * More testing ..
 *
 * Revision 1.1.2.2  2003/06/18 08:20:18  tsanthosh
 * Added Request & Response functionality.
 *
 * Revision 1.1.2.1  2003/06/05 05:43:46  sjaddu
 * Added first revision of files for isupserver.
 *
 *
 ****************************************************************************/

#include <serverimpl.h>

#if defined(PRC)
#include <china/isup.h>
#elif defined (CCITT)
#include <itu/isup.h>
#elif defined (ANSI)
#include <ansi/isup.h>
#endif

#include <its_hash.h>
#include <its_mutex.h>
#include <stdlib.h>
#include <its_transports.h>
#include <its_ss7_trans.h>
#include <its_redundancy.h>


#if defined(CCITT)
#define SL_HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define SL_HANDLE ISS7_ANSI_Stack
#endif

/*
 * public data
 */
static HASH_Table      __SL_ISUP_routing_info = NULL;
static ITS_MUTEX       __SL_ISUP_hashGate;

/*
 * local data
 */
static ITS_BOOLEAN  initialized = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      We need a decent little hash that's pretty good at eliminating
 *      duplicates.
 *
 *  Input Parameters:
 *      key - key data
 *      klen - key length
 *
 *  Return Value:
 *      hash value
 *
 *  Notes:
 *      if they use a lot of one byte keys they deserve the side effects.
 ****************************************************************************/
static ITS_INT
LocalHashISUP(ITS_OCTET *key, ITS_UINT klen)
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
 *      This function Initializes the hash table and hash mutex.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_Init_HashTables()
{
    int ret;

    if (initialized)
    {
        return (ITS_SUCCESS);
    }

    initialized = ITS_TRUE;

    if ((__SL_ISUP_routing_info = HASH_CreateTable()) == NULL)
    {
        ISUP_ERROR(("SL_Init_HashTable: Create create failed\n"));
        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if ((ret = MUTEX_CreateMutex(&__SL_ISUP_hashGate, 0)) != ITS_SUCCESS)
    {
        ISUP_ERROR(("SL_Init_HashTable: mutex create failed\n"));

        HASH_DeleteTable(__SL_ISUP_routing_info);

        initialized = ITS_FALSE;

        return (ret);
    }

    return (ITS_SUCCESS);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Initializes the hash table and hash mutex.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_Term_HashTables()
{
    if (!initialized || terminated)
    {
        return ITS_SUCCESS;
    }

    terminated = ITS_TRUE;

    HASH_DeleteTable(__SL_ISUP_routing_info);

    MUTEX_DeleteMutex(&__SL_ISUP_hashGate);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Registers the client app
 *
 *  Input Parameters:
 *      sockId - sock desc.
 *      evt    - ITS_EVENT *
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_Register(int sockId, ITS_EVENT *evt)
{
    int ret =0, i =0, j =1;
    MTP3_HEADER mtp3;
    SL_CONNECTION_TYPE type;

    if (evt->data[0] == SL_ISUP_REGISTER_EVENT ||
        evt->data[0] == SL_ISUP_REGISTER_BACKUP_EVENT)
    {
        SL_ISUP_ROUTING_INFO rInfo;
        /* this is number of mtp3 headers*/
        int count = (evt->len - 1)/sizeof(MTP3_HEADER);

        if (evt->data[0] == SL_ISUP_REGISTER_EVENT)
        {
            type = SL_PRIMARY_CONNECTION;
        }
        else
        {
            type = SL_BACKUP_CONNECTION;
        }

        for (i =0; i < count; ++i)
        {
            memset(&mtp3, 0, sizeof(MTP3_HEADER));

            memcpy(&mtp3, &evt->data[j], sizeof(MTP3_HEADER));
            j += sizeof(MTP3_HEADER);
           
            ret = SL_FindISUPRoutingInfo(mtp3, &rInfo); 
            if (ret == ITS_ENOTFOUND)
            {
                ret = SL_AllocISUPRoutingInfo(sockId, mtp3, type);
                if (ret != ITS_SUCCESS) 
                {
                    ISUP_ERROR(("SL_Register: Alloc Failed Fatal"
                               " OPC = %d  DPC %d SIO %d\n",
                                 MTP3_RL_GET_OPC_VALUE(mtp3.label),
                                 MTP3_RL_GET_DPC_VALUE(mtp3.label),
                                 (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));
                }
                else
                {
                    ISUP_DEBUG(("SL_Register:Registered Successfully"
                           " OPC = %d  DPC %d SIO %d\n",
                            MTP3_RL_GET_OPC_VALUE(mtp3.label),
                            MTP3_RL_GET_DPC_VALUE(mtp3.label),
                            (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                            (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));
                }
            }
            else if (ret == ITS_SUCCESS)
            {
                if (type == SL_PRIMARY_CONNECTION)
                {
                    rInfo.primCon.client_id = sockId;
                    rInfo.primCon.isUp      = ITS_TRUE;
                }
                else
                {
                    rInfo.backupCon.client_id = sockId;
                    rInfo.backupCon.isUp      = ITS_TRUE;
                    ISUP_DEBUG(("SL_Register:: Updating back up Info\n"));
                }
                SL_UpdateISUPRoutingInfo(&rInfo);
            }

            /* Send response to the client app */
            ret = SL_SendRegDeregResponse(sockId, mtp3, ret, evt->data[0]);
            if (ret != ITS_SUCCESS) 
            {
                ISUP_DEBUG(("SL_Register :: Failed to Send response\n"));
            }
        }
    }
    else if (evt->data[0] == SL_TCAP_REGISTER_EVENT)
    {

    }
    return ITS_SUCCESS;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function DeRegisters the client app
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      sockId - socket ID
 *      evt    - ITS_EVENT *
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_Deregister(int sockId, ITS_EVENT *evt)
{
    int ret =0, i =0, j =1;
    MTP3_HEADER mtp3;
    SL_CONNECTION_TYPE type;

    if (evt->data[0] == SL_ISUP_DEREGISTER_EVENT ||
        evt->data[0] == SL_ISUP_DEREGISTER_BACKUP_EVENT)
    {
        SL_ISUP_ROUTING_INFO rInfo;

        /* this is number of mtp3 headers*/
        int count = (evt->len - 1)/sizeof(MTP3_HEADER);

        if (evt->data[0] == SL_ISUP_DEREGISTER_EVENT)
        {
            type = SL_PRIMARY_CONNECTION;
        }
        else
        {
            type = SL_BACKUP_CONNECTION;
        }

        for (i =0; i < count; ++i)
        {
            memset(&mtp3, 0, sizeof(MTP3_HEADER));

            memcpy(&mtp3, &evt->data[j],  sizeof(MTP3_HEADER));
            j += sizeof(MTP3_HEADER);
            
            ret = SL_FindISUPRoutingInfo(mtp3, &rInfo);
            if (ret == ITS_ENOTFOUND)
            {
                 ISUP_ERROR(("SL_Deregister: Find rtinfo Failed "
                           " OPC = %d  DPC %d SIO %d\n",
                             MTP3_RL_GET_OPC_VALUE(mtp3.label),
                             MTP3_RL_GET_DPC_VALUE(mtp3.label),
                             (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                             (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));
                 return ret;
            }

            if (type == SL_PRIMARY_CONNECTION)
            {
                rInfo.primCon.isUp = ITS_FALSE;
            }
            else
            {
                rInfo.backupCon.isUp = ITS_FALSE;
            }

            if (rInfo.primCon.isUp == ITS_FALSE &&
                rInfo.backupCon.isUp == ITS_FALSE)
            {
                ret = SL_DelISUPRoutingInfo(sockId, mtp3);
                if (ret != ITS_SUCCESS) 
                {
                        ISUP_ERROR(("SL_Deregister: Deregistration failed"
                              " OPC = %d  DPC %d SIO %d\n",
                              MTP3_RL_GET_OPC_VALUE(mtp3.label),
                              MTP3_RL_GET_DPC_VALUE(mtp3.label),
                              (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                              (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));
                }
                else
                {
                       ISUP_DEBUG(("SL_Deregister: Deregistration success for"
                              "both the connections"
                              " OPC = %d  DPC %d SIO %d\n",
                              MTP3_RL_GET_OPC_VALUE(mtp3.label),
                              MTP3_RL_GET_DPC_VALUE(mtp3.label),
                              (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                              (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));
                }
            }
            else
            {
                SL_UpdateISUPRoutingInfo(&rInfo);
            }

            /*Send response to client app */
            SL_SendRegDeregResponse(sockId, mtp3, ret, evt->data[0]);
        }
    }
    else if (evt->data[0] == SL_TCAP_DEREGISTER_EVENT)
    {

    }
    return ITS_SUCCESS;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function allocates routing entries
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_AllocISUPRoutingInfo(int sockId,
                            MTP3_HEADER mtp3,
                            SL_CONNECTION_TYPE type)
{
    SL_ISUP_ROUTING_INFO *rInfo = NULL;
    ITS_INT hash;
    SL_ISUP_ROUTING_INFO *dummy = NULL;

    if (sockId <= 0)
    {
        ISUP_ERROR(("SL_AllocISUPRoutingInfo :Fatal Error\n"));
        return !ITS_SUCCESS;   
    }

    if (MUTEX_AcquireMutex(&__SL_ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_ERROR((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(mtp3,
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) & 
                     (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(mtp3.label, 0);

    hash = LocalHashISUP((ITS_OCTET *)&mtp3, sizeof(MTP3_HEADER));

    if (HASH_FindEntry(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        SL_ISUP_ROUTING_INFO *tmp = NULL;

        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (memcmp(&mtp3, &tmp->opc_dpc_ni,
                       sizeof(MTP3_HEADER)) == 0)
            {

                MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);

                return (ITS_EINUSE);
            }
        }
    }

    /* else allocate it*/
    if ((rInfo = (SL_ISUP_ROUTING_INFO*)calloc(1, sizeof(SL_ISUP_ROUTING_INFO)))
               == NULL)
    {
        ISUP_ERROR(("SL_AllocISUPRoutingInfo: Fatal Error :::\n"));
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOMEM;
    }

    /* set the values here*/
    rInfo->next = dummy;
    rInfo->opc_dpc_ni = mtp3;
    if (type == SL_PRIMARY_CONNECTION)
    {
        ISUP_DEBUG(("Allocating primary connection Id %d\n", sockId));
        rInfo->primCon.client_id = sockId;
        rInfo->primCon.isUp      = ITS_TRUE;
    }
    else
    {
        ISUP_DEBUG(("Allocating backup connection Id %d\n", sockId));
        rInfo->backupCon.client_id = sockId;
        rInfo->backupCon.isUp      = ITS_TRUE;
    }

    if (HASH_AddEntry(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                      hash, (ITS_POINTER)rInfo) != ITS_SUCCESS)
    {
        free(rInfo);
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return (ITS_ENOMEM);
    }

    MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);

    return ITS_SUCCESS;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function finds routing entries
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_FindISUPRoutingInfo(MTP3_HEADER mtp3, SL_ISUP_ROUTING_INFO *rInfo)
{
    ITS_INT hash;
    SL_ISUP_ROUTING_INFO *dummy =NULL;
    SL_ISUP_ROUTING_INFO *tmp = NULL;
    
    if (MUTEX_AcquireMutex(&__SL_ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_ERROR((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }
    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(mtp3,
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                     (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(mtp3.label, 0);

    hash = LocalHashISUP((ITS_OCTET *)&mtp3, sizeof(MTP3_HEADER));

    if (HASH_FindEntry(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {

        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (memcmp(&mtp3, &tmp->opc_dpc_ni,
                       sizeof(MTP3_HEADER)) == 0)
            {
                break;
            }
        }
    }
    else
    {
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOTFOUND;
    }

    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOMEM;
    } 

    /* Set the values*/
    rInfo->next       = tmp->next;
    rInfo->opc_dpc_ni = tmp->opc_dpc_ni;
    rInfo->primCon    = tmp->primCon;
    rInfo->backupCon  = tmp->backupCon;

    MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function updates routing entries
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_UpdateISUPRoutingInfo(SL_ISUP_ROUTING_INFO *rInfo)
{
    ITS_INT hash;
    SL_ISUP_ROUTING_INFO *dummy =NULL;
    SL_ISUP_ROUTING_INFO *tmp = NULL;
    
    if (MUTEX_AcquireMutex(&__SL_ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_ERROR((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }
    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(rInfo->opc_dpc_ni,
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(rInfo->opc_dpc_ni) &
                     (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(rInfo->opc_dpc_ni.label, 0);

    hash = LocalHashISUP((ITS_OCTET *)&rInfo->opc_dpc_ni, sizeof(MTP3_HEADER));

    if (HASH_FindEntry(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {

        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (memcmp(&rInfo->opc_dpc_ni, &tmp->opc_dpc_ni,
                       sizeof(MTP3_HEADER)) == 0)
            {
                break;
            }
        }
    }
    else
    {
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOTFOUND;
    }

    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOMEM;
    } 

    /* Set the values*/
    tmp->next       = rInfo->next;
    tmp->opc_dpc_ni = rInfo->opc_dpc_ni;
    tmp->primCon    = rInfo->primCon;
    tmp->backupCon  = rInfo->backupCon;

    MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);

    ISUP_DEBUG(("SL_UpdateISUPRoutingInfo:: Updating the routing table\n"));

    return ITS_SUCCESS;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Function for HasjIterate functions, this function deletes the
 *      routing entry from table
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
static int 
SL_ISUPDelIterProc(ITS_INT context, ITS_POINTER data, void *in, void *out)
{
    int ret =0;
    SL_ISUP_ROUTING_INFO *rInfo = NULL;
    ITS_INT *cId = (ITS_INT*)in;

    if (data == NULL)
    {
        return !ITS_SUCCESS;
    }

    rInfo = (SL_ISUP_ROUTING_INFO*)data;

    if (rInfo->primCon.client_id == *cId)
    {
        if (rInfo->backupCon.isUp == ITS_FALSE)
        {
            ret = HASH_DeleteEntry(__SL_ISUP_routing_info, 
                                   SL_ISUP_ROUTING_INFO_RID , context);
            if (ret == ITS_SUCCESS)
            {
                ISUP_DEBUG(("SL_ISUPDelIterProc: Deleting entry for ID %d\n",
                        rInfo->primCon.client_id));
            }
        }
        else 
        {
            ISUP_DEBUG(("SL_ISUPDelIterProc:: Changing primCon to DOWN\n"));
            rInfo->primCon.isUp = ITS_FALSE;
        }
    }
    else if (rInfo->backupCon.client_id == *cId)
    {
        if (rInfo->primCon.isUp == ITS_FALSE)
        {
            ret = HASH_DeleteEntry(__SL_ISUP_routing_info, 
                                   SL_ISUP_ROUTING_INFO_RID , context);
            if (ret == ITS_SUCCESS)
            {
                ISUP_DEBUG(("SL_ISUPDelIterProc: Deleting entry for ID %d\n",
                        rInfo->primCon.client_id));
            }
        }
        else 
        {
            ISUP_DEBUG(("SL_ISUPDelIterProc:: Changing backupCon to DOWN\n"));
            rInfo->backupCon.isUp = ITS_FALSE;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function deletes all routing for pertaining to
 *      one client.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int SL_DeleteClientRoutingInfo(int clientId)
{
    return SL_ISUPRoutingIterate(SL_ISUPDelIterProc, (void*)&clientId, NULL);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      hash Interate function
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
int SL_ISUPRoutingIterate(HASH_IterateEntryProc proc, void *in, void *out)
{
    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__SL_ISUP_hashGate) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    HASH_VTableIterate(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                       (void*)in, (void*)out, proc);

    MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      deletes routing infor for given key value.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
int SL_DelISUPRoutingInfo(int sockId, MTP3_HEADER mtp3)
{
    SL_ISUP_ROUTING_INFO *rInfo = NULL;
    ITS_INT hash, ret = 0;
    SL_ISUP_ROUTING_INFO *tmp;
    SL_ISUP_ROUTING_INFO *tmp1 = NULL;

    if (MUTEX_AcquireMutex(&__SL_ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_ERROR(("\nMUTEX_AcquireMutex failed\n"));
        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(mtp3,
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                     (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(mtp3.label, 0);

    hash = LocalHashISUP((ITS_OCTET *)&mtp3, sizeof(MTP3_HEADER));

    if (HASH_FindEntry(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&rInfo) != ITS_SUCCESS)
    {
        ISUP_WARNING(("SL_DelISUPRoutingInfo: Entry not found"
                          " OPC = %d  DPC %d SIO %d\n",
                          MTP3_RL_GET_OPC_VALUE(mtp3.label),
                          MTP3_RL_GET_DPC_VALUE(mtp3.label),
                          (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                          (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));
           
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOTCONFIG;
    }

    if (rInfo->primCon.client_id == sockId ||
        rInfo->backupCon.client_id == sockId)
    {

        ISUP_DEBUG(("SL_DelISUPRoutingInfo:Deleting Sock Id  %d\n", sockId));
    }
    else
    {
        ISUP_WARNING(("SL_DelISUPRoutingInfo: Sock Id doesn' match %d\n", sockId));
        MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);
        return ITS_ENOTFOUND;
    }

    for (tmp = rInfo; tmp != NULL; tmp = tmp->next)
    {
        if (memcmp(&mtp3, &tmp->opc_dpc_ni,
                   sizeof(MTP3_HEADER)) == 0)
        {
            if (tmp1 == NULL)  
            {
                /* This case if it has only one entry*/
                rInfo = tmp->next;
                ISUP_ERROR(("SL_DelISUPRoutingInfo: Deleting Entry"
                          " OPC = %d  DPC %d SIO %d ID %d\n",
                          MTP3_RL_GET_OPC_VALUE(mtp3.label),
                          MTP3_RL_GET_DPC_VALUE(mtp3.label),
                          (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                          (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),sockId));
           
                break;
            }

            tmp1->next = tmp->next;

            free(tmp);
            ISUP_DEBUG(("SL_DelISUPRoutingInfo: Deleting Entry"
                   " OPC = %d  DPC %d SIO %d ID %d\n",
                   MTP3_RL_GET_OPC_VALUE(mtp3.label),
                   MTP3_RL_GET_DPC_VALUE(mtp3.label),
                   (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
                   (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),sockId));
          
            break;
        }
        else
        {
            tmp1 = tmp;
        }
    } 
        
    if (rInfo == NULL)
    {
        ret = HASH_DeleteEntry(__SL_ISUP_routing_info,
                               SL_ISUP_ROUTING_INFO_RID, hash);
        ISUP_DEBUG(("SL_DelISUPRoutingInfo: Deleting Entry"
               " OPC = %d  DPC %d SIO %d \n",
               MTP3_RL_GET_OPC_VALUE(mtp3.label),
               MTP3_RL_GET_DPC_VALUE(mtp3.label),
               (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))));

    }
    else
    {
        ret = HASH_AddEntry(__SL_ISUP_routing_info, SL_ISUP_ROUTING_INFO_RID,
                          hash, (ITS_POINTER)rInfo);
        ISUP_DEBUG(("SL_DelISUPRoutingInfo: Deleting and Adding Entry"
               " OPC = %d  DPC %d SIO %d ID %d\n",
               MTP3_RL_GET_OPC_VALUE(mtp3.label),
               MTP3_RL_GET_DPC_VALUE(mtp3.label),
               (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3) &
               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)), sockId));

    }

    MUTEX_ReleaseMutex(&__SL_ISUP_hashGate);

    return ret;
}

/*
 * MTP3 Management CallBacks
 */
void
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    /* Do nothing */
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To handle the request for reserve CIC API.
 *
 *  Input Parameters:
 *      handle - The socket instance Id of the server
 *      event  - The event that is received for the request
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_INT SL_HandleReserveCICReq(ITS_UINT handle, ITS_EVENT *event)
{
    ITS_OCTET sio =0, cic_state =0;
    ITS_UINT  opc,dpc;
    ITS_USHORT cic =0;
    ITS_CTXT vcic =0;
    ITS_INT counter=0,ret=0;
    MTP3_HEADER mtp3;


    counter++; /* Data 0 not accessed */

    memset(&mtp3, 0, sizeof(MTP3_HEADER));


    memcpy(&mtp3, &event->data[counter], sizeof(MTP3_HEADER));
    opc = MTP3_RL_GET_OPC_VALUE(mtp3.label);
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3.label);
    sio = MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK);
    counter += sizeof(MTP3_HEADER);

    /* CIC */
    /*memcpy(&cic, &event->data[counter], sizeof(ITS_USHORT));*/
    cic |= event->data[counter++];
    cic |= event->data[counter++] << 8;

    /* Need to call reserve cic api defined in intellinet */
    ret = ISUP_ReserveCIC(SL_HANDLE, sio, opc, 
                               dpc, cic, &cic_state,
                               &vcic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_WARNING(("CIC Reserve fialed For CIC %d  ret = %d\n", cic, ret));
    }

    ISUP_DEBUG(("SL_HandleReserveCICReq: Sending Reserve CIC response"
                " ret = %d to client\n", (int)ret));
    /* Form and Send the response event */
    SL_SendReserveCICResponse(handle, event, ret, cic_state, vcic);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To handle the request for unreserve CIC API.
 *
 *  Input Parameters:
 *      handle - The socket instance Id of the server
 *      event  - The event that is received for the request
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_INT SL_HandleUnReserveCICReq(ITS_UINT handle, ITS_EVENT *event)
{
    ITS_OCTET sio;
    ITS_UINT  opc,dpc;
    ITS_USHORT cic;
    ITS_INT counter=0,ret=0;
    MTP3_HEADER mtp3;

    counter++; /* Data 0 not accessed */

    memset(&mtp3, 0, sizeof(MTP3_HEADER));

    ISUP_DEBUG(("SL_HandleUnReserveCICReq: Function called !!\n"));

    memcpy(&mtp3, &event->data[counter], sizeof(MTP3_HEADER));
    opc = MTP3_RL_GET_OPC_VALUE(mtp3.label);
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3.label);
    sio = MTP3_HDR_GET_SIO(mtp3) & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK);
    counter += sizeof(MTP3_HEADER);

    cic |= event->data[counter++];
    cic |= event->data[counter++] << 8;

    /* Need to call reserve cic api defined in intellinet */
    ret = ISUP_UnReserveCIC(SL_HANDLE, sio, opc, 
                                 dpc, cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_WARNING(("The result of cic = %d and ret = %d\n", cic,ret));
    }
   
    /* Form and Send the response event */
    SL_SendUnReserveCICResponse(handle, event, ret);

    return (ret);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To form the response to the request events.
 *
 *  Input Parameters:
 *      handle - Transport Id to put the response event
 *      event  - The event that is received for the request
 *      ret - Return value of the requested event.
 *      cic_state - The state of the cic
 *      vcic      - VCIC
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_INT SL_SendReserveCICResponse(ITS_UINT handle, ITS_EVENT *event, 
                                  ITS_UINT ret, ITS_OCTET cic_state, 
                                  ITS_CTXT vcic)
{
    ITS_INT len = 0;
    ITS_EVENT responseEv;

    ITS_EVENT_INIT(&responseEv, ITS_ISUP_SRC, MTP2_MAX_MSG_SIZE);

    responseEv.data[len++] = SL_ISUP_RESERVE_CIC_RESP;

    memcpy(&responseEv.data[len], &event->data[len], sizeof(MTP3_HEADER));
    len += sizeof(MTP3_HEADER);

    /* CIC */
    memcpy(&responseEv.data[len], &event->data[len], sizeof(ITS_USHORT));
    len += sizeof(ITS_USHORT);

    /* Cic state */
    responseEv.data[len++]  = cic_state;

    /* VCIC */
    ITS_SET_CTXT(&responseEv.data[len], vcic);
    len += sizeof(ITS_CTXT);

    /* Return value of Reserve_CIC Api */
    responseEv.data[len++] =  ret & 0xFFU;
    responseEv.data[len++] =  (ret >> 8) & 0xFFU;
    responseEv.data[len++] =  (ret >> 16) & 0xFFU;
    responseEv.data[len++] =  (ret >> 24) & 0xFFU;

    responseEv.len = len;
    
    ISUP_DEBUG(("SL_SendReserveCICResponse: Sending Reserve CIC"
                " Response ret =%d to client\n", (int)ret));

    /* Send back response to client app */
    TRANSPORT_PutEvent(handle, &responseEv);

    return(ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To form the response to the request events.
 *
 *  Input Parameters:
 *      handle - Transport Id to put the response event
 *      event  - The event that is received for the request
 *      ret - Return value of the requested event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_INT SL_SendUnReserveCICResponse(ITS_UINT handle, ITS_EVENT *event, 
                                    ITS_UINT ret)
{
    ITS_INT len = 0;
    ITS_EVENT responseEv;

    ITS_EVENT_INIT(&responseEv, ITS_ISUP_SRC, MTP2_MAX_MSG_SIZE);

    responseEv.data[len++] = SL_ISUP_UNRESERVE_CIC_RESP;

    memcpy(&responseEv.data[len], &event->data[len], sizeof(MTP3_HEADER));
    len += sizeof(MTP3_HEADER);

    /* CIC */
    memcpy(&responseEv.data[len], &event->data[len], sizeof(ITS_USHORT));
    len += sizeof(ITS_USHORT);

    responseEv.data[len++] = ret & 0xFFU;
    responseEv.data[len++] = (ret >> 8) & 0xFFU;
    responseEv.data[len++] = (ret >> 16) & 0xFFU;
    responseEv.data[len++] = (ret >> 24) & 0xFFU;

    responseEv.len = len;

    ISUP_DEBUG(("SL_SendUnReserveCICResponse: Sending UnReserve"
                " CIC Response ret = %d to client\n", (int)ret));
    /* Send back response to client app */
    TRANSPORT_PutEvent(handle, &responseEv);

    return(ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To form the response to the request events.
 *
 *  Input Parameters:
 *      ev  - The event that is received for the request
 *      responseEv - The event which has response to the request for reserveCIC.
 *      ret - Return value of the requested event.
 *      cic_state - The state of the cic
 *      vcic      - VCIC
 *      eventType - The type of requested event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_INT SL_SendRegDeregResponse(int sockId, MTP3_HEADER mtp3,
                                ITS_UINT ret, ITS_INT eventType)
{
    ITS_EVENT responseEv;
    ITS_INT len = 0;
    

    ITS_EVENT_INIT(&responseEv, ITS_ISUP_SRC, MTP2_MAX_MSG_SIZE);

    if(eventType == SL_ISUP_REGISTER_EVENT || 
       eventType == SL_ISUP_REGISTER_BACKUP_EVENT)
    {
         responseEv.data[len++] = SL_ISUP_REGISTER_RESP; 
    }
    else
    {
         responseEv.data[len++] = SL_ISUP_DEREGISTER_RESP;
    }

    /* Copy MTP3_HEADER */
    memcpy(&responseEv.data[len], &mtp3, sizeof(MTP3_HEADER));
    len += sizeof(MTP3_HEADER);

    /* Include return value of registration or deregistration */
    responseEv.data[len++] = ret & 0xFFU;
    responseEv.data[len++] = (ret >> 8)  & 0xFFU;
    responseEv.data[len++] = (ret >> 16) & 0xFFU;
    responseEv.data[len++] = (ret >> 24) & 0xFFU;

    responseEv.len = len;

    ISUP_DEBUG(("SL_SendRegDeregResponse: Sending response ret = %d\n", (int)ret));

    /* Send Event to client App */
    TRANSPORT_PutEvent(sockId, &responseEv);

    return(ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Handle state change event
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_INT SL_HandleStateChangeEventFromApp(ITS_EVENT *event)
{
    ITS_NODE_STATE type = event->data[1];

    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    ISUP_DEBUG(("SL_HandleStateChangeEventFromApp:: Received \n"));

    if (redunClass == NULL)
    {
        ISUP_ERROR(("Some thing wrong with APP, we are running as stub"));
        return !ITS_SUCCESS;
    }
    else
    {
        if (REDUNDANCY_CONFIGURED_TYPE(redunClass) == ITS_ACTIVE_ACTIVE)
        {
            ISUP_ERROR(("Received state change, not allowd in active-active"));
            return !ITS_SUCCESS;
        }
    }
            
    if (REDUNDANCY_GET_NODE_STATE(redunClass) == ITS_STATE_BACKUP &&
                                                type == ITS_STATE_PRIMARY)
    {
        ISUP_CRITICAL(("Received state change, becomming active"));
        REDUNDANCY_CHANGE_NODE_STATE_PROC(redunClass)();
        return ITS_SUCCESS;
    }

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Iterate proc to send state change event to apps
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
static int 
SL_SendStateChangeEventProc(ITS_INT context, ITS_POINTER data,  
                            void *in, void *out)
{
    int ret =0;
    SL_ISUP_ROUTING_INFO *rInfo = NULL;
    ITS_EVENT *event = (ITS_EVENT*)in;
    ITS_USHORT dest =0;
    ITS_EVENT  evt;

    if (data == NULL)
    {
        return !ITS_SUCCESS;
    }

    rInfo = (SL_ISUP_ROUTING_INFO*)data;

    if (rInfo->primCon.isUp)
    {
        dest = rInfo->primCon.client_id;
    }
    else if (rInfo->backupCon.isUp)
    {
        dest = rInfo->backupCon.client_id;
    }
    else
    {
        return ret;
    }

    ITS_EVENT_INIT(&evt, event->src, event->len); 

    memcpy(evt.data, event->data, event->len);

    ISUP_DEBUG(("SL_SendStateChangeEventProc::  TRANSPORT_PutEvent\n"));
    
    return TRANSPORT_PutEvent(dest, &evt); 
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Handle state change event from stack
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_USHORT SL_HandleStateChangeEventFromStack(ITS_EVENT *evt)
{
    ISUP_DEBUG(("SL_HandleStateChangeEventFromStack:: Hanlding\n"));
    return SL_ISUPRoutingIterate(SL_SendStateChangeEventProc,
                                 (void*)evt, NULL);
}
