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
 * $Id: tcap_serverimpl.c,v 9.1 2005/03/23 12:55:02 cvsadmin Exp $
 *
 * $Log: tcap_serverimpl.c,v $
 * Revision 9.1  2005/03/23 12:55:02  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.6  2003/10/22 06:05:58  ssingh
 * Changes done to handle LID table finding based on DID and
 * DID to LID table entry for appInitiated message on receive
 * of Dialouge from Client. LID to DID structure changed.
 *
 * Revision 1.5  2003/10/15 04:53:42  sswami
 * Error Handling for Registration/Deregistration functions.
 * Implementation of Deregistration function.
 *
 * Revision 1.4  2003/10/11 09:55:42  ssingh
 * Code changes done for Application initiated and response
 * from Remote for Application Initiated message.
 *
 * Revision 1.3  2003/10/10 05:08:48  vjatti
 * Changed the return type to ITS_OCTET for GetRouteStyle.
 *
 * Revision 1.2  2003/10/09 12:54:09  ssingh
 * Changes done for Alloc and Find Routing Info.
 *
 * Revision 1.1  2003/10/07 12:29:18  sswami
 * Multiple TCAP applications binding initial commits
 *
 *
 ****************************************************************************/

#include <tcap_serverimpl.h>

#if defined(PRC)
#include <china/isup.h>
#include <china/tcap.h>
#elif defined (CCITT)
#include <itu/isup.h>
#include <itu/tcap.h>
#elif defined (ANSI)
#include <ansi/isup.h>
#include <ansi/tcap.h>
#endif

#include <its_hash.h>
#include <its_mutex.h>
#include <stdlib.h>
#include <its_transports.h>
#include <its_ss7_trans.h>


#if defined(CCITT)
#define SL_HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define SL_HANDLE ISS7_ANSI_Stack
#endif

/*
 * public data
 */
static HASH_Table      __SL_TCAP_routing_info = NULL;
static HASH_Table      __SL_TCAP_lid_to_did = NULL;
static HASH_Table      __SL_TCAP_did_to_lid = NULL;
static ITS_MUTEX       __SL_TCAP_Route_hashGate;
static ITS_MUTEX       __SL_TCAP_LID_hashGate;
static ITS_MUTEX       __SL_TCAP_DID_hashGate;

/*
 * local data
 */
static ITS_BOOLEAN  initialized = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;

static int SL_FindClientIterProc (ITS_INT context, ITS_POINTER data, void* in, void* out);

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
LocalHashTCAP(ITS_OCTET *key, ITS_UINT klen)
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

    if ((__SL_TCAP_routing_info = HASH_CreateTable()) == NULL)
    {
        printf("SL_Init_HashTable: Create create failed\n");
        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if ((__SL_TCAP_lid_to_did = HASH_CreateTable()) == NULL)
    {
        printf("SL_Init_HashTable: did table Create failed\n");
        initialized = ITS_FALSE;
        return (ITS_ENOMEM);
    }

    if ((__SL_TCAP_did_to_lid = HASH_CreateTable()) == NULL)
    {
        printf("SL_Init_HashTable: lid table Create failed\n");
        initialized = ITS_FALSE;
        return (ITS_ENOMEM);
    }

    if ((ret = MUTEX_CreateMutex(&__SL_TCAP_Route_hashGate, 0)) != ITS_SUCCESS) 
    {
        printf("SL_Init_HashTable: mutex create failed\n");

        HASH_DeleteTable(__SL_TCAP_routing_info);

        initialized = ITS_FALSE;

        return (ret);
    }

    if ((ret = MUTEX_CreateMutex(&__SL_TCAP_LID_hashGate, 0)) != ITS_SUCCESS) 
    {
        printf("SL_Init_HashTable: mutex create failed\n");

        HASH_DeleteTable(__SL_TCAP_lid_to_did);

        initialized = ITS_FALSE;

        return (ret);
    }

    if ((ret = MUTEX_CreateMutex(&__SL_TCAP_DID_hashGate, 0)) != ITS_SUCCESS) 
    {
        printf("SL_Init_HashTable: mutex create failed\n");

        HASH_DeleteTable(__SL_TCAP_did_to_lid);

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

    HASH_DeleteTable(__SL_TCAP_routing_info);
    HASH_DeleteTable(__SL_TCAP_lid_to_did);
    HASH_DeleteTable(__SL_TCAP_did_to_lid);
    MUTEX_DeleteMutex(&__SL_TCAP_Route_hashGate);
    MUTEX_DeleteMutex(&__SL_TCAP_LID_hashGate);
    MUTEX_DeleteMutex(&__SL_TCAP_DID_hashGate);

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
    SL_ROUTE_KEY rKey;    
    ITS_OCTET    route_style;

#if 0
    /* For Unit Testing */
    SL_TCAP_ROUTING_INFO test;
#endif

    /* this is number of routing keys*/
    int count = (evt->len - 1)/sizeof(SL_ROUTE_KEY);

    for (i =0; i < count; ++i)
    {
        memset(&rKey, 0, sizeof(SL_ROUTE_KEY));
        memcpy(&rKey, &evt->data[j],  sizeof(SL_ROUTE_KEY));
        j += sizeof(SL_ROUTE_KEY);
         
        /* Get the Routing Style */
        route_style = GetRouteStyle(style); 
        if (rKey.route_style != route_style)
        { 
            printf("SL_Register: ERROR !!!Routing style mismatch\n" 
                   "Requested = %d Configured= %d\n",
                    rKey.route_style, route_style);

            printf("SL_Register: Registration Failed\n");
            rKey.route_style = route_style;
            ret = ITS_ENOTFOUND;
        }
        else
        {
            ret = SL_AllocTCAPRoutingInfo(sockId, rKey);
            if (ret != ITS_SUCCESS)
            {
                printf("SL_Register: Alloc Failed Fatal"
                       "OPC = %d  DPC %d SIO %d\n",
                       MTP3_RL_GET_OPC_VALUE(rKey),
                       MTP3_RL_GET_DPC_VALUE(rKey),
                       (ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
                       (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
            } 
            else
            {
                /* Display the Registration Info based on Style */
                SL_PrintRouteStyle(rKey);
            }

#if 0   
            /* For Unit Testing */
            ret = SL_FindTCAPRoutingInfo(rKey, &test, route_style); 
            if (ret == ITS_SUCCESS)
            {
                printf("Routing Info is = OPC = %d DPC = %d SIO = %d SSN = %d\n"
                        "Client Id is = %d\n", 
                         MTP3_RL_GET_OPC_VALUE(test.rKey), 
                         MTP3_RL_GET_DPC_VALUE(test.rKey), 
                         test.rKey.sio,test.rKey.ssn, test.client_id);  
            }
             
#endif
        } /* End of else */

        /* Send the Response to the Client */
        SL_SendRegDeregResponse(sockId, rKey, ret, evt->data[0]);
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
    SL_TCAP_ROUTING_INFO *rInfo;
    SL_TCAP_ROUTING_INFO **tmp;
    SL_TCAP_ROUTING_INFO *tmp2;
    SL_ROUTE_KEY         rkey;
    ITS_INT hash;
    int ret = ITS_SUCCESS;

    printf("SL_Deregister::");

    /* acquire mutex */
    if (MUTEX_AcquireMutex(&__SL_TCAP_Route_hashGate) != ITS_SUCCESS)
    {
        printf("Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    memcpy(&rkey, &evt->data[1],  sizeof(SL_ROUTE_KEY));

    hash = LocalHashTCAP((ITS_OCTET *)&rkey, sizeof(SL_ROUTE_KEY));

    /* Find entry */
    if (HASH_FindEntry(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&rInfo) == ITS_SUCCESS)
    {
        for(tmp = &rInfo; *tmp != NULL; )
        {
            if(memcmp(&rkey, &(*tmp)->rKey, sizeof(SL_ROUTE_KEY)) == 0)
            {
                tmp2 = *tmp;
                *tmp = (*tmp)->next;
                free(tmp2);
            }
            else
            {
                tmp = &(*tmp)->next;
            }
        }

        /* Delete entry */
        if ( rInfo == NULL)
        {
            ret = HASH_DeleteEntry(__SL_TCAP_routing_info,
                                   SL_TCAP_ROUTING_INFO_RID,
                                   hash);
            printf("Deleting entries\n");
        }
        printf("Client ID  =%d OPC = %d DPC = %d SIO = %d SSN = %d \n",sockId,
                MTP3_RL_GET_OPC_VALUE(rkey),
                MTP3_RL_GET_DPC_VALUE(rkey),
                rkey.sio, rkey.ssn);
    }
    else
    {
        printf("Entry not found\n");

        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        ret = ITS_ENOTCONFIG;
    }

    /* Send response to the client app */
    SL_SendRegDeregResponse(sockId, rkey, ret, evt->data[0]);
    MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
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
int SL_AllocTCAPRoutingInfo(int sockId, SL_ROUTE_KEY rKey) 
{
    SL_TCAP_ROUTING_INFO *rInfo = NULL;
    ITS_INT hash;
    SL_TCAP_ROUTING_INFO *dummy = NULL;
    SL_TCAP_ROUTING_INFO *tmp = NULL;

    if (sockId <= 0)
    {
        printf("SL_AllocTCAPRoutingInfo :Fatal Error\n");
        return !ITS_SUCCESS;
    }

    if (MUTEX_AcquireMutex(&__SL_TCAP_Route_hashGate) != ITS_SUCCESS)
    {
        printf(": Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    switch (rKey.route_style)
    {
    case DPC: 
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        rKey.ssn = 0;
        rKey.sio = 0;
        break;
    
    case SSN:
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        MTP3_RL_SET_DPC_VALUE(rKey,0);
        rKey.sio = 0;
        break;

    case OPC_DPC:
        rKey.ssn = 0;
        rKey.sio = 0;
        break;

    case DPC_SIO:
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        rKey.ssn = 0;
        MTP3_HDR_SET_SIO(rKey,(ITS_OCTET) (MTP3_HDR_GET_SIO(rKey) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

    case DPC_SSN:
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        rKey.sio = 0;
        break;

    case OPC_DPC_SIO:
        MTP3_HDR_SET_SIO(rKey,(ITS_OCTET) (MTP3_HDR_GET_SIO(rKey) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        rKey.ssn = 0;
        break;

    case OPC_DPC_SSN:
        rKey.sio = 0;
        break;

    case OPC_DPC_SIO_SSN:
        MTP3_HDR_SET_SIO(rKey,(ITS_OCTET) (MTP3_HDR_GET_SIO(rKey) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

     default:
        printf("\n Invalid Routing Style\n");
        return(!ITS_SUCCESS);
    } 

    hash = LocalHashTCAP((ITS_OCTET *)&rKey, sizeof(rKey));

    if (HASH_FindEntry(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (memcmp(&rKey, &tmp->rKey, sizeof(rKey)) == 0)
            {
                MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);

                return (ITS_EINUSE);
            }
        }
    }
    /* else allocate it*/
    if ((rInfo = (SL_TCAP_ROUTING_INFO*)
                    calloc(1, sizeof(SL_TCAP_ROUTING_INFO))) == NULL)
    {
        printf("SL_AllocTCAPRoutingInfo: Fatal Error :::\n");
        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return ITS_ENOMEM;
    }

    /* set the values here*/
    rInfo->rKey = rKey;
    memcpy(&rInfo->rKey, &rKey, sizeof(rInfo->rKey));
    rInfo->client_id = sockId;
    rInfo->next = dummy;

    if (HASH_AddEntry(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                      hash, (ITS_POINTER)rInfo) != ITS_SUCCESS)
    {
        free(rInfo);
        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return (ITS_ENOMEM);
    }
    MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);

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
int 
SL_FindTCAPRoutingInfo(SL_ROUTE_KEY rKey, SL_TCAP_ROUTING_INFO *rInfo )
{
    ITS_INT hash;
    SL_TCAP_ROUTING_INFO *dummy =NULL;
    SL_TCAP_ROUTING_INFO *tmp = NULL;

    if (MUTEX_AcquireMutex(&__SL_TCAP_Route_hashGate) != ITS_SUCCESS)
    {
        printf(": Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    switch (rKey.route_style)
    {
    case DPC:
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        rKey.ssn = 0;
        rKey.sio = 0;
        break;

    case SSN:
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        MTP3_RL_SET_DPC_VALUE(rKey,0);
        rKey.sio = 0;
        break;

    case OPC_DPC:
        /* form the Routing Key here */
        rKey.ssn = 0;
        rKey.sio = 0;
        break;

    case DPC_SIO:
        /* form the Routing Key here */
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        MTP3_HDR_SET_SIO(rKey,(ITS_OCTET) (MTP3_HDR_GET_SIO(rKey) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))); 
        rKey.ssn = 0;
        break;

    case DPC_SSN:
        MTP3_RL_SET_OPC_VALUE(rKey,0);
        rKey.sio = 0;
        break;

    case OPC_DPC_SIO:
        MTP3_HDR_SET_SIO(rKey,(ITS_OCTET) (MTP3_HDR_GET_SIO(rKey) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))); 
        rKey.ssn = 0;
        break;

    case OPC_DPC_SSN:
        rKey.sio = 0;
        break;

    case OPC_DPC_SIO_SSN:
        MTP3_HDR_SET_SIO(rKey,(ITS_OCTET) (MTP3_HDR_GET_SIO(rKey) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK))); 
        break;

     default:
        printf("\n Invalid Routing Style\n");
            MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return(!ITS_SUCCESS);
    }

    hash = LocalHashTCAP((ITS_OCTET *)&rKey, sizeof(rKey));
    if (HASH_FindEntry(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {

        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (memcmp(&rKey, &tmp->rKey, sizeof(rKey)) == 0)
            {
                break;
            }
        }
    }
    else
    {
        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return ITS_ENOTFOUND;
    }

    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return ITS_ENOMEM;
    }

    /* Set the values*/
    rInfo->next = tmp->next;
    memcpy(&rInfo->rKey, &tmp->rKey, sizeof(rInfo->rKey));
    rInfo->client_id  = tmp->client_id;

    MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
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
static int SL_TCAPDelIterProc(ITS_INT context, ITS_POINTER data, 
                               void *in, void *out)
{
    int ret =0;
    SL_TCAP_ROUTING_INFO *rInfo = NULL;
    ITS_INT *cId = (ITS_INT*)in;

    if (data == NULL)
    {
        return !ITS_SUCCESS;
    }

    rInfo = (SL_TCAP_ROUTING_INFO*)data;

    if (rInfo->client_id == *cId)
    {
        ret = HASH_DeleteEntry(__SL_TCAP_routing_info, 
                               SL_TCAP_ROUTING_INFO_RID , context);
        if (ret == ITS_SUCCESS)
        {
            printf("SL_TCAPDelIterProc: Deleting entry for Client ID %d\n",
                    rInfo->client_id);
            printf("Deleting the Routing Info :OPC = %d DPC = %d  SIO = %d "
                    " SSN = %d ", MTP3_RL_GET_OPC_VALUE(rInfo->rKey),
                    MTP3_RL_GET_DPC_VALUE(rInfo->rKey),rInfo->rKey.sio,
                    rInfo->rKey.ssn);
            printf("\n Client Application Deregistred or Terminated\n");
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
    return SL_TCAPRoutingIterate(SL_TCAPDelIterProc, (void*)&clientId, NULL);
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
int SL_TCAPRoutingIterate(HASH_IterateEntryProc proc, void *in, void *out)
{
    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__SL_TCAP_Route_hashGate) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    HASH_VTableIterate(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                       (void*)in, (void*)out, proc);

    MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);

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
int SL_DelTCAPRoutingInfo(int sockId, SL_ROUTE_KEY rKey)
{
    SL_TCAP_ROUTING_INFO *rInfo = NULL;
    ITS_INT hash, ret = 0;
    SL_TCAP_ROUTING_INFO *tmp;
    SL_TCAP_ROUTING_INFO *tmp1 = NULL;

    if (MUTEX_AcquireMutex(&__SL_TCAP_Route_hashGate) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&rKey,
                          sizeof(rKey));

    if (HASH_FindEntry(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                       hash, (ITS_POINTER *)&rInfo) != ITS_SUCCESS)
    {
        printf("SL_DelTCAPRoutingInfo: Entry not found"
               " OPC = %d  DPC %d SIO %d\n",
               MTP3_RL_GET_OPC_VALUE(rKey),
               MTP3_RL_GET_DPC_VALUE(rKey),
               (ITS_OCTET)(MTP3_HDR_GET_SIO (rKey) &
               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return ITS_ENOTCONFIG;
    }

    if (rInfo->client_id != sockId)
    {
        printf("SL_DelTCAPRoutingInfo: Sock Id doesn' match %d\n", sockId);
        MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);
        return ITS_ENOTFOUND;
    }

    for (tmp = rInfo; tmp != NULL; tmp = tmp->next)
    {
        if (memcmp(&rKey, &tmp->rKey, sizeof(rKey)) == 0)
        {
            if (tmp1 == NULL)
            {
                /* This case if it has only one entry*/
                rInfo = tmp->next;
                printf("SL_DelTCAPRoutingInfo: Deleting Entry"
                     " OPC = %d  DPC %d SIO %d ID %d\n",
                     MTP3_RL_GET_OPC_VALUE(rKey),
                     MTP3_RL_GET_DPC_VALUE(rKey),
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
                     (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),sockId);

                break;
            }

            tmp1->next = tmp->next;

            free(tmp);
            printf("SL_DelTCAPRoutingInfo: Deleting Entry"
                   " OPC = %d  DPC %d SIO %d ID %d\n",
                   MTP3_RL_GET_OPC_VALUE(rKey),
                   MTP3_RL_GET_DPC_VALUE(rKey),
                   (ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
                   (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),sockId);
            break;
        }
        else
        {
            tmp1 = tmp;
        }
    }
       
    if (rInfo == NULL)
    {
        ret = HASH_DeleteEntry(__SL_TCAP_routing_info,
                               SL_TCAP_ROUTING_INFO_RID, hash);
        printf("SL_DelTCAPRoutingInfo: Deleting Entry"
               " OPC = %d  DPC %d SIO %d \n",
               MTP3_RL_GET_OPC_VALUE(rKey),
               MTP3_RL_GET_DPC_VALUE(rKey),
               (ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
    }
    else
    {
        ret = HASH_AddEntry(__SL_TCAP_routing_info, SL_TCAP_ROUTING_INFO_RID,
                          hash, (ITS_POINTER)rInfo);
        printf("SL_DelTCAPRoutingInfo: Deleting and Adding Entry"
               " OPC = %d  DPC %d SIO %d \n",
               MTP3_RL_GET_OPC_VALUE(rKey),
               MTP3_RL_GET_DPC_VALUE(rKey),
               (ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    }

    MUTEX_ReleaseMutex(&__SL_TCAP_Route_hashGate);

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
ITS_INT SL_SendRegDeregResponse(int sockId, SL_ROUTE_KEY rKey,
                                ITS_UINT ret, ITS_INT eventType)
{
    ITS_EVENT responseEv;
    ITS_INT len = 0;
    

    ITS_EVENT_INIT(&responseEv, ITS_TCAP_SRC, MTP2_MAX_MSG_SIZE);

    if(eventType == SL_TCAP_REGISTER_EVENT)
    {
         responseEv.data[len++] = SL_TCAP_REGISTER_RESP; 
    }
    else
    {
         responseEv.data[len++] = SL_TCAP_DEREGISTER_RESP;
    }

    /* Copy routing info */
    memcpy(&responseEv.data[len], &rKey, sizeof(SL_ROUTE_KEY));
    len += sizeof(SL_ROUTE_KEY);

    /* Include return value of registration or deregistration */
    responseEv.data[len++] = ret & 0xFFU;
    responseEv.data[len++] = (ret >> 8)  & 0xFFU;
    responseEv.data[len++] = (ret >> 16) & 0xFFU;
    responseEv.data[len++] = (ret >> 24) & 0xFFU;

    responseEv.len = len;

    printf("SL_SendRegDeregResponse: Sending response ret = %d\n", (int)ret);

    /* Send Event to client App */
    TRANSPORT_PutEvent(sockId, &responseEv);

    return(ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Gets the routing style
 *
 *  Input Value :Routing key
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
ITS_OCTET
GetRouteStyle(char* style)
{
    ITS_OCTET route_style;

    if(strcmp(style,ROUTE_DPC_STRING) == 0)
    route_style = DPC;
    else if(strcmp(style,ROUTE_SSN_STRING) == 0)
    route_style = SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_STRING) == 0)
    route_style = OPC_DPC;
    else if(strcmp(style,ROUTE_DPC_SIO_STRING) == 0)
    route_style = DPC_SIO;
    else if(strcmp(style,ROUTE_DPC_SSN_STRING) == 0)
    route_style = DPC_SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_SIO_STRING) == 0)
    route_style = OPC_DPC_SIO;
    else if(strcmp(style,ROUTE_OPC_DPC_SSN_STRING) == 0)
    route_style = OPC_DPC_SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_SIO_SSN_STRING) == 0)
    route_style = OPC_DPC_SIO_SSN;
    return route_style;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Prints the routing style
 *
 *  Input Value :Routing key
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/

void 
SL_PrintRouteStyle(SL_ROUTE_KEY rKey)
{
    printf("SL_Register:Registered Successfully\n");

    switch (rKey.route_style)
    {
    case DPC:
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        break;

    case SSN:
        printf("SSN = %d\n", rKey.ssn);
        break;

    case OPC_DPC:
        printf("OPC = %d\n", MTP3_RL_GET_OPC_VALUE(rKey));
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        break;

    case DPC_SIO:
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        printf("SIO = %d\n",(ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
                             (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

    case DPC_SSN:
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        printf("SSN = %d\n", rKey.ssn);
        break;

    case OPC_DPC_SIO:
        printf("OPC = %d\n", MTP3_RL_GET_OPC_VALUE(rKey));
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        printf("SIO = %d\n",(ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
                             (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

    case OPC_DPC_SSN:
        printf("OPC = %d\n", MTP3_RL_GET_OPC_VALUE(rKey));
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        printf("SSN = %d\n", rKey.ssn);
        break;

    case OPC_DPC_SIO_SSN:
        printf("OPC = %d\n", MTP3_RL_GET_OPC_VALUE(rKey));
        printf("DPC = %d\n", MTP3_RL_GET_DPC_VALUE(rKey));
        printf("SIO = %d\n",(ITS_OCTET)(MTP3_HDR_GET_SIO(rKey) &
                             (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        printf("SSN = %d\n", rKey.ssn);
        break;

    default:
        break;
    }
}

/* ------------------------------- starts here -------------------*/

void
TCAP_SendDidAllocResp(ITS_CTXT did, SL_ROUTE_KEY rKey)
{
    SL_TCAP_ROUTING_INFO rInfo;
    ITS_EVENT event;
    int ret;

    ITS_EVENT_INIT(&event, SL_SRC_SERVER, 10);

    event.data[0] = SL_TCAP_ALLOC_DID_RESP;

    ret = SL_FindTCAPRoutingInfo(rKey, &rInfo);

    if (ret != ITS_SUCCESS)
    {
        printf("\n Couldn't get route info\n");
    }

    ITS_SET_CTXT(&event.data[1], did);

    TRANSPORT_PutEvent(rInfo.client_id, &event);

}

int SL_AllocTCAPLidToDid (ITS_CTXT did, SL_LID_XPORT_ID lidXportKey)
{
    SL_TCAP_LID_TO_DID_INFO *lidToDidInfo = NULL;
    SL_TCAP_LID_TO_DID_INFO *dummy = NULL;
    SL_TCAP_LID_TO_DID_INFO *tmp = NULL;
    ITS_INT hash;

    if (MUTEX_AcquireMutex(&__SL_TCAP_LID_hashGate) != ITS_SUCCESS)
    {
        printf(": Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&lidXportKey, sizeof(SL_LID_XPORT_ID));

    /* find entry */
    if (HASH_FindEntry(__SL_TCAP_lid_to_did, SL_TCAP_LID_TO_DID_TABLE_ID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
           if(memcmp(&lidXportKey, &tmp->lidXportKey,
                                        sizeof(SL_LID_XPORT_ID)) == 0)
           {
              MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);

              return (ITS_EINUSE);
           }
        }
    }

    /* allocate memory */
    if ((lidToDidInfo = (SL_TCAP_LID_TO_DID_INFO *)
            calloc(1, sizeof(SL_TCAP_LID_TO_DID_INFO))) == NULL)
    {
        printf (": Couldn't calloc.\n");
        MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
        return ITS_ENOMEM;
    }

    lidToDidInfo -> next = dummy;
    memcpy(&lidToDidInfo->lidXportKey, &lidXportKey, sizeof(SL_LID_XPORT_ID));
    lidToDidInfo -> did = did;
    lidToDidInfo -> clientId = lidXportKey.client_id;

    if (HASH_AddEntry(__SL_TCAP_lid_to_did, SL_TCAP_LID_TO_DID_TABLE_ID,
                       hash, (ITS_POINTER)lidToDidInfo) != ITS_SUCCESS)
    {
        free(lidToDidInfo);
        MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
        return (ITS_ENOMEM);
    }
    MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
    return ITS_SUCCESS;
}

int
SL_FindTCAPLidToDid (SL_TCAP_LID_TO_DID_INFO *lidToDidInfo,
                               SL_LID_XPORT_ID lidXportKey)
{
    SL_TCAP_LID_TO_DID_INFO *dummy = NULL;
    SL_TCAP_LID_TO_DID_INFO *tmp = NULL;
    ITS_INT hash;

    if (MUTEX_AcquireMutex(&__SL_TCAP_LID_hashGate) != ITS_SUCCESS)
    {
        printf(": Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&lidXportKey, sizeof(SL_LID_XPORT_ID));

    /* find entry */
    if (HASH_FindEntry(__SL_TCAP_lid_to_did, SL_TCAP_LID_TO_DID_TABLE_ID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
           if(memcmp(&lidXportKey, &tmp->lidXportKey,
                                      sizeof(SL_LID_XPORT_ID)) == 0)
           {
              break;
           }
        }
    }
    else
    {
            MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
            return ITS_ENOTFOUND;
    }

    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
        return ITS_ENOMEM;
    }

    /* set Values */
    lidToDidInfo -> next = tmp -> next;
    memcpy(&lidToDidInfo->lidXportKey, &tmp->lidXportKey,
                                          sizeof(SL_LID_XPORT_ID));
    lidToDidInfo -> did = tmp->did;
    lidToDidInfo -> clientId = tmp->clientId;

    MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
    return ITS_SUCCESS;
}


int SL_AllocTCAPDidToLid(SL_LID_XPORT_ID lidXport, ITS_CTXT didKey)
{
    SL_TCAP_DID_TO_LID_INFO *didToLidInfo = NULL;
    SL_TCAP_DID_TO_LID_INFO *dummy = NULL;
    SL_TCAP_DID_TO_LID_INFO *tmp = NULL;
    ITS_INT hash;

    if (MUTEX_AcquireMutex(&__SL_TCAP_DID_hashGate) != ITS_SUCCESS)
    {
        printf(": Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&didKey, sizeof(ITS_CTXT));

    /* find entry */
    if (HASH_FindEntry(__SL_TCAP_did_to_lid, SL_TCAP_DID_TO_LID_TABLE_ID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
           if(memcmp(&didKey, &tmp->didKey, sizeof(didKey)) == 0)
           {
              MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);

              return (ITS_EINUSE);
           }
        }
    }

    /* allocate memory */
    if ((didToLidInfo = (SL_TCAP_DID_TO_LID_INFO *)
            calloc(1, sizeof(SL_TCAP_DID_TO_LID_INFO))) == NULL)
    {
        printf (": Couldn't calloc.\n");
        MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
        return ITS_ENOMEM;
    }

    didToLidInfo -> next = dummy;
    memcpy(&didToLidInfo->didKey, &didKey, sizeof(ITS_CTXT));
    didToLidInfo -> lidXport = lidXport;
    //didToLidInfo -> toDelete = toDelete;

    if (HASH_AddEntry(__SL_TCAP_did_to_lid, SL_TCAP_DID_TO_LID_TABLE_ID,
                       hash, (ITS_POINTER)didToLidInfo) != ITS_SUCCESS)
    {
        free(didToLidInfo);
        MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
        return (ITS_ENOMEM);
    }
    MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
    return ITS_SUCCESS;
}

int
SL_FindTCAPDidToLid (SL_TCAP_DID_TO_LID_INFO *didToLidInfo, ITS_CTXT didKey)
{
    SL_TCAP_DID_TO_LID_INFO *dummy = NULL;
    SL_TCAP_DID_TO_LID_INFO *tmp = NULL;
    ITS_INT hash;

    if (MUTEX_AcquireMutex(&__SL_TCAP_DID_hashGate) != ITS_SUCCESS)
    {
        printf(": Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&didKey, sizeof(ITS_CTXT));

    /* find entry */
    if (HASH_FindEntry(__SL_TCAP_did_to_lid, SL_TCAP_DID_TO_LID_TABLE_ID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
           if(memcmp(&didKey, &tmp->didKey, sizeof(didKey)) == 0)
           {
              break;
           }
        }
    }
    else
    {
            MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
            return ITS_ENOTFOUND;
    }

    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
        return ITS_ENOMEM;
    }

    /* Set Values */
    didToLidInfo -> next = tmp -> next;
    memcpy(&didToLidInfo->didKey, &tmp->didKey, sizeof(ITS_CTXT));
    didToLidInfo -> lidXport = tmp->lidXport;
    //didToLidInfo -> toDelete = tmp->toDelete;

    MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
    return ITS_SUCCESS;
}

/* Delete Entry in the table for this client */
int
SL_DeleteTCAPLidToDid(SL_LID_XPORT_ID lidXportKey)
{
    SL_TCAP_LID_TO_DID_INFO *lidToDidInfo;
    SL_TCAP_LID_TO_DID_INFO **tmp;
    SL_TCAP_LID_TO_DID_INFO *tmp2;
    ITS_INT hash;

    int ret = ITS_SUCCESS;

    /* acquire mutex */
    if (MUTEX_AcquireMutex(&__SL_TCAP_LID_hashGate) != ITS_SUCCESS)
    {
        printf("Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&lidXportKey, sizeof(SL_LID_XPORT_ID));

    /* find entry */
    if (HASH_FindEntry(__SL_TCAP_lid_to_did, SL_TCAP_LID_TO_DID_TABLE_ID,
                       hash, (ITS_POINTER *)&lidToDidInfo) == ITS_SUCCESS)
    {
        for(tmp = &lidToDidInfo; *tmp != NULL; )
        {
           if(memcmp(&lidXportKey, &(*tmp)->lidXportKey,
                                           sizeof(SL_LID_XPORT_ID)) == 0)
           {
              tmp2 = *tmp;
              *tmp = (*tmp)->next;
              free(tmp2);
           }
           else
           {
              tmp = &(*tmp)->next;
           }
        }

        /* delete entry */
        if ( lidToDidInfo == NULL)
        {
            ret = HASH_DeleteEntry(__SL_TCAP_lid_to_did,
                                   SL_TCAP_LID_TO_DID_TABLE_ID,
                                   hash);
        }
    }
    else
    {
        printf("Entry not found\n");

        MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
        return ITS_ENOTCONFIG;
    }

    MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);
    return (ret);
}


/* Delete Entry in the table for this client */
int SL_DeleteTCAPDidToLid(ITS_CTXT didKey)
{
    SL_TCAP_DID_TO_LID_INFO *didToLidInfo;
    SL_TCAP_DID_TO_LID_INFO **tmp;
    SL_TCAP_DID_TO_LID_INFO *tmp2;
    ITS_INT hash;

    int ret = ITS_SUCCESS;

    /* acquire mutex */
    if (MUTEX_AcquireMutex(&__SL_TCAP_DID_hashGate) != ITS_SUCCESS)
    {
        printf("Couldn't acquire mutex.\n");

        return ITS_EBADMUTEX;
    }

    hash = LocalHashTCAP((ITS_OCTET *)&didKey, sizeof(ITS_CTXT));

    /* find entry */
    if (HASH_FindEntry(__SL_TCAP_did_to_lid, SL_TCAP_DID_TO_LID_TABLE_ID,
                       hash, (ITS_POINTER *)&didToLidInfo) == ITS_SUCCESS)
    {
        for(tmp = &didToLidInfo; *tmp != NULL; )
        {
           if(memcmp(&didKey, &(*tmp)->didKey, sizeof(ITS_CTXT)) == 0)
           {
              tmp2 = *tmp;
              *tmp = (*tmp)->next;
              free(tmp2);
           }
           else
           {
              tmp = &(*tmp)->next;
           }
        }

        /* delete entry */
        if ( didToLidInfo == NULL)
        {
            ret = HASH_DeleteEntry(__SL_TCAP_did_to_lid,
                                   SL_TCAP_DID_TO_LID_TABLE_ID,
                                   hash);
        }
    }
    else
    {
        printf("Entry not found\n");

        MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
        return ITS_ENOTCONFIG;
    }

    MUTEX_ReleaseMutex(&__SL_TCAP_DID_hashGate);
    return (ret);
}

int SL_FindClientRoutingInfo(ITS_CTXT did, ITS_USHORT *socketId)
{
    int ret = ITS_SUCCESS;
    
    if (MUTEX_AcquireMutex(&__SL_TCAP_LID_hashGate) != ITS_SUCCESS)
    {
        return ITS_EBADMUTEX;
    }

    ret = HASH_VTableIterate(__SL_TCAP_lid_to_did, 
                             SL_TCAP_LID_TO_DID_TABLE_ID, 
                             &did,  socketId, SL_FindClientIterProc);

    *socketId = *((ITS_USHORT *) socketId);

    MUTEX_ReleaseMutex(&__SL_TCAP_LID_hashGate);

    return ret;
}

static int SL_FindClientIterProc (ITS_INT context, ITS_POINTER data, 
                                  void *in, void *out)
{
    int ret         = 0;
    ITS_CTXT *did   =  in;
    ITS_USHORT *sockId = out;
    
    SL_TCAP_LID_TO_DID_INFO  *lidInfo = NULL;
    
    if (data == NULL)
    {  
        return !ITS_SUCCESS;
    }

    lidInfo = (SL_TCAP_LID_TO_DID_INFO *) data;
    
    if (lidInfo->did == *did)
    {
        *sockId  = lidInfo->clientId;

        TCAP_DEBUG (("Match found for Did = %d, clientId = %d\n", 
                                            lidInfo->did, *sockId));

        return ITS_SUCCESS;
    }
          
    return (ret= ITS_ENOTFOUND);
}

/* ------------------------------- ends here -------------------*/
