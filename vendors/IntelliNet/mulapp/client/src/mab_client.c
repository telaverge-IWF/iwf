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
 * ID: $Id: mab_client.c,v 1.5 2005/06/17 09:06:41 adutta Exp $
 *
 * LOG: $Log: mab_client.c,v $
 * LOG: Revision 1.5  2005/06/17 09:06:41  adutta
 * LOG: Fixed issue #1991
 * LOG:
 * LOG: Revision 1.4  2005/06/10 11:17:10  adutta
 * LOG: Fix for issue# 1916/1925/1980/1984
 * LOG:
 * LOG: Revision 1.3  2005/06/02 13:49:30  adutta
 * LOG: Changes done for redundancy.
 * LOG:
 * LOG: Revision 1.2  2005/05/31 11:09:21  adutta
 * LOG: Fix for Deregister msg encoding.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#include<mab_client.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

MABCL_DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* MTP3_PRC_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* ISUP_PRC_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_PRC_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_PRC_GlobalTitleTranslator = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_PRC_SSNRoutingCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* MTP3_TTC_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* ISUP_TTC_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_TTC_ManagementCallbacks = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_TTC_GlobalTitleTranslator = NULL;
MABCL_DLLAPI CALLBACK_Manager* SCCP_TTC_SSNRoutingCallbacks = NULL;


#if defined(CCITT)
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#elif defined(ANSI)
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#endif

static char* sync_data = "ISS7SSI";
static ITS_INT   sd_len = 7;

ITS_MUTEX hashLock;
ITS_MUTEX regLock;

MABCL_DLLAPI MABCL_CONNECTION MAB_Connection;
MLIST_Manager *TCAP_primQueue;
MABCL_DLLAPI ITS_HANDLE ISS7_Stack = (ITS_HANDLE)&MAB_Connection;

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is used when we are inserting the connection info 
 *      in to the hash table with glgid as the key.
 *
 *  Input Parameters:
 *      dlgid- key. cInfo- connection info.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/
ITS_INT MABCL_AddTCAPEntry(ITS_OCTET ptype, ITS_CTXT dlgid ,ITS_INT cInfo)
{
    ITS_USHORT *connInfo = NULL;
    ITS_BOOLEAN flag = ITS_FALSE;
    ITS_INT ret;

    MUTEX_AcquireMutex(&hashLock);

    ret = HASH_FindEntry(_CL_CTXT_info,
                         CL_ROUTING_INFO,
                         dlgid,
                         (ITS_POINTER *)&connInfo);

    if (ret == ITS_SUCCESS)
    {
        flag = ITS_TRUE;
    }

    switch(ptype)
    {
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_BEGIN:
#elif defined(ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#endif

#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_CONTINUE:
#elif defined(ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#endif
        {
            if (flag == ITS_FALSE)
            {
                connInfo = (ITS_USHORT *)malloc(sizeof(ITS_USHORT));

                *connInfo = cInfo;


                ret = HASH_AddEntry(_CL_CTXT_info,
                                CL_ROUTING_INFO,
                                dlgid,
                                (ITS_POINTER)connInfo);
            }

            break;
        }

#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_END:
#elif defined(ANSI)
        case TCPPT_TC_RESP:
#endif

#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_U_ABORT:
#elif defined(ANSI)
        case TCPPT_TC_ABORT:
#endif
        default:
        {
             if (flag)
             {
                 ret = HASH_DeleteEntry(_CL_CTXT_info,
                                    CL_ROUTING_INFO, dlgid);
             }
             break;
        }
     }
     MUTEX_ReleaseMutex(&hashLock);

}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is used when we are inserting the connection info 
 *      in to the hash table with cic as the key.
 *
 *  Input Parameters:
 *      cic key. cInfo - connnection info.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 **************************************************************************/
MABCL_DLLAPI ITS_INT 
MABCL_AddISUPEntry(ITS_OCTET mtype, ITS_CTXT cic, ITS_INT cInfo)
{
    ITS_USHORT *connInfo = NULL;
    ITS_INT ret;
    ITS_BOOLEAN flag = ITS_FALSE;

    MUTEX_AcquireMutex(&hashLock);

    ret = HASH_FindEntry(_CL_CTXT_info,
                         CL_ROUTING_INFO,
                         cic,
                         (ITS_POINTER *)&connInfo);

    if (ret == ITS_SUCCESS)
    {
        flag = ITS_TRUE;
    }

    switch(mtype)
    {
        case ISUP_MSG_REL:
        case ISUP_MSG_RLC:
        case ISUP_MSG_GRS:
        case ISUP_MSG_RSC:
             break;
        default:
        {
             if (flag == ITS_FALSE)
             {
                 connInfo = (ITS_USHORT *)malloc(sizeof(ITS_USHORT));

                 *connInfo = cInfo;

                 ret = HASH_AddEntry(_CL_CTXT_info,
                                   CL_ROUTING_INFO,
                                   cic, (ITS_POINTER)connInfo);
             }
        }
    }

    MUTEX_ReleaseMutex(&hashLock);
    return ITS_SUCCESS;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is called when hash table 
 *      entries is to be updated to the connection given in the "in" param.
 *      in  0 - for primary connection 1 - backup connection.
 *  Input Parameters:
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/

MABCL_DLLAPI ITS_INT 
MABCL_UpdateEntryProc(ITS_INT context, ITS_POINTER data,
                               void *in, void *out)
{
    ITS_OCTET *tmp = (ITS_OCTET *)in;

    *data = *tmp;
    return ITS_SUCCESS;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is called when hash table
 *      entries is to be deleted.  
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/

MABCL_DLLAPI ITS_INT 
MABCL_DeleteEntryProc(ITS_INT context, ITS_POINTER data,
                               void *in, void *out)
{
    HASH_DeleteEntry(_CL_CTXT_info , CL_ROUTING_INFO, context);

    ITS_Free(data);

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is wrapper function for update hash function.
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/

MABCL_DLLAPI ITS_INT
MABCL_UpdateHashEntry(ITS_OCTET type)
{
   /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&hashLock) != ITS_SUCCESS)
    {
        printf("\nCouldn't acquire mutex.\n");
        return;
    }
    HASH_VTableIterate(_CL_CTXT_info ,CL_ROUTING_INFO, &type,
                       NULL, MABCL_UpdateEntryProc);

    MUTEX_ReleaseMutex(&hashLock);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This function is wrapper function for delete hash function.
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *
 *  See Also:
 *
 *************************************************************************/

MABCL_DLLAPI ITS_INT
MABCL_DeleteHashEntry()
{
   /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&hashLock) != ITS_SUCCESS)
    {
        printf("\nCouldn't acquire mutex.\n");
        return;
    }

    HASH_VTableIterate(_CL_CTXT_info ,CL_ROUTING_INFO , NULL,
                       NULL, MABCL_DeleteEntryProc);

    MUTEX_ReleaseMutex(&hashLock);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method sends the event to server 
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *  This method decides on which connection it should put the event,
 *  it always try to send on the primary connection in case of failure
 *  of primary connection only it sends on backup connection alternatively.  
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT 
MABCL_SendEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    MABCL_CONNECTION *conn = NULL; 
    ITS_INT ret = 0, index = 0; 
    ITS_CTXT hash;
    ITS_USHORT *connInfo = NULL;
    ITS_BOOLEAN flag = ITS_TRUE;
    ITS_USHORT ptype;

    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    printf("MABCL_SendEvent:: sending event..... \n");
    printf("\n");
    for(index =0;index < evt->len;index++)
    {
        if ((index + 1) % 16 == 0) printf("\n");
        printf("%02x ",evt->data[index]);
    }
    printf("\n");
       
    conn = (MABCL_CONNECTION*)handle;

    /* Do the find in hash table depending on the context.
     * If no entry for the context then its a new transaction/call
     * else send the event on the available info in the hash table
     */

    if( evt->src == MABCL_TCAP_SRC )
    {
        memcpy(&hash, &evt->data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET)],
                              sizeof(ITS_CTXT));
        ptype = evt->data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET) +
                            sizeof(ITS_CTXT)];
    }
    else if(evt->src == MABCL_ISUP_SRC)
    {
        /* Event encoded: client id, msg type, usr data, header, cic isup msg */
        memcpy(&hash, &evt->data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET)
                  + 1 + sizeof(MTP3_HEADER)],sizeof(ITS_USHORT));
        ptype = evt->data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET) +
                          sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) +
                          sizeof(ITS_USHORT)];
    }

    MUTEX_AcquireMutex(&hashLock);
    /* Now find the entry using the hash */
    ret = HASH_FindEntry(_CL_CTXT_info, CL_ROUTING_INFO,
                 hash,(ITS_POINTER *)&connInfo);

    if( ret != ITS_SUCCESS )
    {
        if(conn->backupInfo.isPrimary == ITS_TRUE)
        {
            flag = ITS_FALSE;
        }
        else if((conn->primaryInfo.isPrimary == ITS_FALSE) &&
                (conn->backupInfo.isPrimary == ITS_FALSE))
        {
            printf("MABCL_SendEvent:: failed all connection down\n");
            MUTEX_ReleaseMutex(&hashLock);
            return ret;
        }
    }
    else
    {
        /* if conninfo ==0 write into primary else to backup */
        if (*connInfo == 1 )
        {
            flag = ITS_FALSE;
        }

        if(evt->src == MABCL_TCAP_SRC)
        {
            switch(ptype)
            {
#if defined (ANSI)
                case TCPPT_TC_RESP:
#elif defined (CCITT)
                case TCAP_PT_TC_END_CCITT:
#endif
#if defined (ANSI)
                case TCPPT_TC_ABORT:
#elif defined (CCITT)
                case TCAP_PT_TC_P_ABORT_CCITT:
                case TCAP_PT_TC_U_ABORT_CCITT:
#endif
                {
                    ret = HASH_DeleteEntry(_CL_CTXT_info,
                                      CL_ROUTING_INFO, hash);
                }
                break;
            }
        }
        else if(evt->src == MABCL_ISUP_SRC)
        {
            switch(ptype)
            {
                case ISUP_MSG_GRS:
                case ISUP_MSG_RSC:
                case ISUP_MSG_REL:
                case ISUP_MSG_RLC:
                {
                    ret = HASH_DeleteEntry(_CL_CTXT_info,
                                      CL_ROUTING_INFO, hash);
                }
            }
        }
    }

    if (((conn->primaryInfo.thrInfo.isRunning == ITS_TRUE) ||
        (conn->backupInfo.thrInfo.isRunning == ITS_FALSE))
           && (conn->primaryInfo.isPrimary == ITS_TRUE ))
    {
        ret = MABCL_WriteEvent(&conn->primaryInfo, evt);
        if (ret != ITS_SUCCESS)
        {
            printf("MABCL_SendEvent:: Write event prim conn failed\n");
        }
    }
    else
    {
        ret = MABCL_WriteEvent(&conn->backupInfo, evt);
        if (ret != ITS_SUCCESS)
        {
            printf("MABCL_SendEvent::Write even backup conn failed\n");
        }
    }

    MUTEX_ReleaseMutex(&hashLock);

    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method write the data to socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt - event to be send
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS on success
 *
 *  Notes:
 *   
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT nrite;
    ITS_USHORT tmp =0;
    MABCL_CONNECTION_INFO *conInfo = NULL; 

    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    conInfo = (MABCL_CONNECTION_INFO*)handle;

    if (!conInfo->isUp)
    {
        return ITS_ESENDFAIL;
    }

    MUTEX_AcquireMutex(&conInfo->writeLock);

    nrite = SOCK_Write(conInfo->sockInfo, sync_data, sd_len); 
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->writeLock);
        return ITS_ESENDFAIL;
    }

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(conInfo->sockInfo, (char *)evt->data, evt->len);

        if (nrite != (ITS_INT)evt->len)
        {
            MUTEX_ReleaseMutex(&conInfo->writeLock);
            return (ITS_ESENDFAIL);
        }
    }
   
    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data =0;
    }
    MUTEX_ReleaseMutex(&conInfo->writeLock);
    return ITS_SUCCESS;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method gives the info whether either of the socket is up.
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
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
MABCL_IsRegistered(ITS_HANDLE handle)
{
   MABCL_CONNECTION *conInfo = NULL;
     
   conInfo = (MABCL_CONNECTION *)handle;

   if(conInfo->primaryInfo.isUp) 
   {
       switch(conInfo->primaryInfo.regStatus)
       {
           case INIT:
           case FAILURE:
                return !ITS_SUCCESS;
                break;
           case SUCCESS:
                return ITS_SUCCESS;
                break;
       }  
   }
   else
   {
       if(conInfo->backupInfo.isUp)
       {
           switch(conInfo->backupInfo.regStatus)
           {
               case INIT:
               case FAILURE:
                    return !ITS_SUCCESS;
                    break;
               case SUCCESS:
                    return ITS_SUCCESS;
                    break;
           }
       }
   }   
   return !ITS_SUCCESS;
} 

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method Reads the data from server
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt    -  event 
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *      evt - type ITS_EVENT *.
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
MABCL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT nread = 0, ret =0;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
    MABCL_CONNECTION_INFO *conInfo = NULL; 

    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    conInfo = (MABCL_CONNECTION_INFO*)handle;
    if (conInfo == NULL)
    {
        return ITS_ERCVFAIL;
    }

    MUTEX_AcquireMutex(&conInfo->readLock);

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = conInfo->sockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&conInfo->readLock);
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                if (conInfo->isUp == ITS_FALSE)
                {
                    MUTEX_ReleaseMutex(&conInfo->readLock);
                    return ITS_ENOSOCKET;
                }
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(conInfo->sockInfo, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&conInfo->readLock);
            return (ITS_ERCVFAIL);
        }

        if (buf != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* Here we are so successfully received ISS7SSI*/ 

    /* read the source */
    nread = SOCK_Read(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
    nread = SOCK_Read(conInfo->sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&conInfo->readLock);
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
        nread = SOCK_Read(conInfo->sockInfo, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&conInfo->readLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&conInfo->readLock);
    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles the cleint specific events
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
MABCL_HandleClientEvent(ITS_EVENT *evt)
{
    printf("---Unexpected client msg received from server---\n");
    return ITS_SUCCESS;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method connects to the server.
 *      socket
 *
 *  Input Parameters:
 *      info  -   of type MABCL_CONNECTION_INFO
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *      This function doesn't return until it connects to the server.
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT 
MABCL_Connect(MABCL_CONNECTION_INFO *info)
{
    ITS_INT ret =0;
    ITS_INT repeat_count = 1;

    while(1)
    {
        if (info->isClose == ITS_TRUE)
        {
            return ITS_ECONNECTFAIL; 
        }

        ret = SOCK_ClientOpen(&info->sockInfo,
                              INET_DOMAIN,
                              info->ipAddr,
                              info->port);
        if (ret != ITS_SUCCESS)
        {
            printf("Create client failed fatal error: %d \n", ret);
            exit(1);
        }

        ret = SOCK_ClientConnect(info->sockInfo);
        if (ret != ITS_SUCCESS)
        {
            printf("Client connect failed server IP addr %s and port# %d\n",
                    info->ipAddr, info->port);
            SOCK_Close(info->sockInfo);
            info->sockInfo = NULL;
#ifdef WIN32
	    Sleep(SOC_CONNECT_INTERVAL);
#else
            sleep(SOC_CONNECT_INTERVAL);
#endif
            repeat_count++;
        }
        else
        {   
            info->isUp = ITS_TRUE;
            printf("MABCL_Connect:: Client connected to server\n");
            break;
        }
    }
    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method puts the event on to the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type MABCL_CONNECTION
 *      evt   -   of type ITS_EVENT
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT 
MABCL_PutEventOnTaskQue(MABCL_TRANS_QUE *taskTran, ITS_EVENT *evt)
{
    ITS_INT ret =0;
    ITS_INT index =0;
    if (EMLIST_Lock(taskTran->taskQue) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }
    
    if(evt->src != ITS_TCAP_SRC )
    {
        printf("Data written to the T Queue.\n");
        for (index =0; index< evt->len;index ++)
        printf("%02x ",evt->data[index]);
    }
    
    printf("\n");   
    ret = EMLIST_PutEvent(taskTran->taskQue,  (char *)evt, sizeof(ITS_EVENT));
    ++taskTran->noCurrEnts;

    EMLIST_Unlock(taskTran->taskQue);
    
    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrieves the event from the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type MABCL_CONNECTION
 *      
 *  Output Parameters:
 *      evt   -   of type ITS_EVENT
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT 
MABCL_GetEventFromTaskQue(MABCL_TRANS_QUE *taskTran, ITS_EVENT *evt)
{
    ITS_INT len = 0, ret;
    void *data = 0;

repeat:

    if ((ret = EMLIST_GetNextEventWithTimeOut(taskTran->taskQue,
                       &data, &len,
                       HMI_GetTimeOutInterval())) != ITS_SUCCESS)
    {
        if (ret == ITS_ETIMEOUT)
        {
            goto repeat;
        }

        return (ret);
    }

    memcpy(evt, data, len);

    if (EMLIST_Lock(taskTran->taskQue) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    --taskTran->noCurrEnts;

    EMLIST_Unlock(taskTran->taskQue);

    ITS_Free(data);

    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method closes the socket connection with server based on 
 *      the Connection type.
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      type - MABCL_CONNECTION_TYPE 0 - primary  1- Backup.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_CloseCon(ITS_HANDLE handle , MABCL_CONNECTION_TYPE type)
{
    MABCL_CONNECTION *conn = NULL;
    if (handle == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    conn = (MABCL_CONNECTION*)handle;

    if(type == MABCL_PRIMARY_CONNECTION)
    {
        if (conn->primaryInfo.isUp)
        {
            /* acquire lock */
            MUTEX_AcquireMutex(&regLock);
            SOCK_Close(conn->primaryInfo.sockInfo);
            conn->primaryInfo.sockInfo = NULL;
            conn->primaryInfo.isClose = ITS_TRUE;
            THREAD_DeleteThread(&conn->primaryInfo.thrInfo.info);
            MABCL_CloseConnection(MABCL_PRIMARY_CONNECTION);
            /* release lock */
            MUTEX_ReleaseMutex(&regLock);
        }
    }
    else 
    {
        if (conn->backupInfo.isUp)
        {
            /* acquire lock */
            MUTEX_AcquireMutex(&regLock);
            SOCK_Close(conn->backupInfo.sockInfo);
            conn->backupInfo.sockInfo = NULL;
            conn->backupInfo.isClose = ITS_TRUE;
            THREAD_DeleteThread(&conn->backupInfo.thrInfo.info);
            MABCL_CloseConnection(MABCL_BACKUP_CONNECTION);
            /* release lock */
            MUTEX_ReleaseMutex(&regLock);
        }
    }

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for primary connection.
 *
 *  Input Parameters:
 *      void  *  -   not used 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
#ifdef WIN32
static unsigned __stdcall 
#else
static void *
#endif
PrimaryThreadFunction(void *v)
{
    ITS_EVENT evt;
    ITS_EVENT reRegevt;
    ITS_INT ret =0, i = 0;

    memset(&evt, 0, sizeof(ITS_EVENT));
    while(MAB_Connection.primaryInfo.thrInfo.isRunning)
    {
        ret = MABCL_ReadEvent(&MAB_Connection.primaryInfo, &evt);
        if (ret == ITS_SUCCESS)
        {
            printf("Message from server event len:%d\n",evt.len);
            for(i=0;i<evt.len;i++)
            {
                if ((i + 1) % 16 == 0) printf("\n");
                printf("%02x ",evt.data[i]);
            }
            printf("\n");

            /* if event src is TCAP break the dlg/components */
            if (evt.src == MABCL_TCAP_SRC)
            {
                TCAP_DLG dlg;
                TCAP_CPT cpt[MAX_NUM_CPT];
                ITS_CTXT dlgid;
                ITS_EVENT dlgevt;
                ITS_EVENT cmpevt[MAX_NUM_CPT];
                ITS_OCTET numCpts = 0;
                ITS_INT index = 0;
                ITS_INT compindex = 0;

                ret = MABCL_GetDlgComponent(&dlg, &dlgid, cpt, 
                                   &numCpts, &evt.data[DLG_ID_OFFSET],
                                   (evt.len - (sizeof(ITS_ULONG) +
                                   sizeof(ITS_OCTET)))); 
                                           
                ITS_EVENT_TERM(&evt);

                MABCL_AddTCAPEntry(dlg.ptype, dlgid, 0);

                /* check if ptype is 0 means L-CANCEL*/
                if (dlg.ptype)
                {

                    if (TCAP_VendorDialogueSanityCheck(&dlg) != 
                        ITS_SUCCESS) 
                    {
                        continue;
                    }

                    ITS_EVENT_INIT(&dlgevt, ITS_TCAP_SRC, 
                                  sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                                  sizeof(TCAP_DLG));

                    dlgevt.data[index++] = ITS_TCAP_DLG;

                    /* fill the dialogue id */
                    memcpy(&dlgevt.data[index], &dlgid, sizeof(ITS_CTXT));

                    index = index + sizeof(ITS_CTXT);

                    /* copy the Dialogue */ 
                    memcpy(&dlgevt.data[index],&dlg,sizeof(TCAP_DLG));
                    index = index + sizeof(TCAP_DLG);
                    dlgevt.len = index; 

                    ret = MABCL_PutEventOnTaskQue(&MAB_Connection.taskTrans,
                                                 &dlgevt);
                    if (ret != ITS_SUCCESS)
                    {
                        printf("Some problem in puting the event on to list\n");
                    }
                }

                for (compindex = 0; compindex < numCpts;++compindex)
                {
                    index = 0;
                    if (TCAP_VendorComponentSanityCheck(&cpt[compindex])
                                        != ITS_SUCCESS)
                    {
                        continue;
                    }

                    cmpevt[compindex].data = 
                           (ITS_OCTET*) malloc(sizeof(TCAP_CPT) +
                           sizeof(ITS_OCTET) +
                           sizeof(ITS_CTXT));

                    cmpevt[compindex].data[index++] = ITS_TCAP_CPT;

                    /* fill the dialogue id */
                    memcpy(&cmpevt[compindex].data[index], 
                              &dlgid, sizeof(ITS_CTXT));

                    index = index + sizeof(ITS_CTXT);

                    /* fill the component */
                    memcpy(&cmpevt[compindex].data[index], 
                           &cpt[compindex],
                           sizeof(TCAP_CPT));

                    index = index + sizeof(TCAP_CPT);

                    cmpevt[compindex].len = index;
                    cmpevt[compindex].src = ITS_TCAP_SRC;

                    /* send the component evt */
                    ret = MABCL_PutEventOnTaskQue(
                             &MAB_Connection.taskTrans,
                             &cmpevt[compindex]);

                    if (ret != ITS_SUCCESS)
                    {
                        printf("Error puting event on to list\n");
                    }
                }
            }
            else
            {
                if (evt.data[sizeof(ITS_ULONG)] == REGISTER_ACK_MSG ||
                    evt.data[sizeof(ITS_ULONG)]  == DERGISTER_ACK_MSG) 
                {
                    MAB_Connection.primaryInfo.regStatus = 
                    evt.data[sizeof(ITS_ULONG)+ 
                           sizeof(ITS_OCTET) + sizeof(ITS_OCTET)];
                } 
                else if (evt.data[sizeof(ITS_ULONG)] == ISUP_MSG)
                {
                    ITS_OCTET msgType;
                    ITS_CTXT cic;
                    msgType = evt.data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET)];
                    memcpy(&cic,&evt.data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET)
                                       + sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
                                                              sizeof(ITS_USHORT));

                    MABCL_AddISUPEntry(msgType, cic , 0);
                }
                ret = MABCL_PutEventOnTaskQue(&MAB_Connection.taskTrans, &evt);
                if (ret != ITS_SUCCESS)
                {
                    printf("Some problem in puting the event on to list\n");
                }
            }
        }
        else if (ret == ITS_ENOSOCKET)
        {
            continue;
        }
        else if (ret == ITS_ERCVFAIL)
        {
            SOCK_Close(MAB_Connection.primaryInfo.sockInfo);
            MAB_Connection.primaryInfo.sockInfo = NULL;
            MAB_Connection.primaryInfo.isPrimary = ITS_FALSE;
            if (MAB_Connection.backupInfo.isUp)
            {
                MAB_Connection.backupInfo.isPrimary = ITS_TRUE;
                //update all the entry with backup
                MABCL_UpdateHashEntry(1);
            }
            else
            {
                //delete all entry in hash tables
                MABCL_DeleteHashEntry();
            }

            /* Try to reconnect */
            ret = MABCL_Connect(&MAB_Connection.primaryInfo);
            if (ret != ITS_SUCCESS)
            {
                if (ret == ITS_ENOSOCKET)
                {
                    printf("Attempt to reconnect failed check server\n");
                    printf("Server IP Addr %s and Port# %d\n",
                            MAB_Connection.primaryInfo.ipAddr,
                            MAB_Connection.primaryInfo.port);
                    MABCL_CloseConnection(MABCL_PRIMARY_CONNECTION);
                    THREAD_DeleteThread(&MAB_Connection.primaryInfo.thrInfo.info);
#ifdef WIN32
		    return 0;
#else
                    return NULL;
#endif
                }
                else if (ret == ITS_ECONNECTFAIL)
                {
                    continue;
                }
                else
                {
                    printf("We have major problem here ---\n");
#ifdef WIN32
		    return 0;
#else
                    return NULL;
#endif
                }
            }
            else
            {
                printf(" Primary connection reconnected \n");

                MUTEX_AcquireMutex(&regLock);

                if(MAB_Connection.regInfoLen && 
                   MAB_Connection.reRegInfo != NULL)
                {

                    ITS_EVENT_INIT(&reRegevt, MABCL_APP_SRC,
                             MAB_Connection.regInfoLen);

                    memcpy(reRegevt.data, MAB_Connection.reRegInfo, 
                             MAB_Connection.regInfoLen);

                    ret= MABCL_WriteEvent((ITS_HANDLE*)&MAB_Connection.primaryInfo,
                                       &reRegevt);

                    if (ret != ITS_SUCCESS)
                    {
                        printf("Primary conn rereg failed ret %d\n", ret);
                    }
                    else
                    {
                        printf("Primary conn rereg written successfully\n");
                    }
                }

                MUTEX_ReleaseMutex(&regLock);

                /* Extra check for non redundant */
                if(MAB_Connection.backupInfo.isUp == ITS_FALSE)
                {
                    MAB_Connection.primaryInfo.isPrimary = ITS_TRUE;
                }

                continue;
            }
        } 
    }
    MUTEX_AcquireMutex(&regLock);

    if(MAB_Connection.primaryInfo.sockInfo)
    {
        SOCK_Close(MAB_Connection.primaryInfo.sockInfo);
        MAB_Connection.primaryInfo.sockInfo = NULL;
    }
    if(MAB_Connection.primaryInfo.thrInfo.isRunning)
    {
        THREAD_DeleteThread(&MAB_Connection.primaryInfo.thrInfo.info);
    }
    MABCL_CloseConnection(MABCL_PRIMARY_CONNECTION); 

    MUTEX_ReleaseMutex(&regLock);
    printf("Thread exiting for primary connection\n");
#ifdef WIN32
		    return 0;
#else
                    return NULL;
#endif
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is thread function for backup connection.
 *
 *  Input Parameters:
 *      void  *  -   not used 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/

 
#ifdef WIN32
unsigned __stdcall 
#else
static void *
#endif
BackupThreadFunction(void *v)
{
    ITS_EVENT evt;
    ITS_EVENT reRegevt;
    ITS_INT ret =0, i = 0;
    
    memset(&evt, 0, sizeof(ITS_EVENT));
    while(MAB_Connection.backupInfo.thrInfo.isRunning)
    {
        ret = MABCL_ReadEvent(&MAB_Connection.backupInfo, &evt);
        if (ret == ITS_SUCCESS)
        {
            printf("Message from server event len:%d\n",evt.len);
            printf("\n");
            for(i=0;i<evt.len;i++)
            {
                if ((i + 1) % 16 == 0) printf("\n");
                printf("%02x ",evt.data[i]);
            }
            printf("\n");
            /* if event src is TCAP break the dlg/components */
            if (evt.src == MABCL_TCAP_SRC)
            {
                TCAP_DLG dlg;
                TCAP_CPT cpt[MAX_NUM_CPT];
                ITS_CTXT dlgid;
                ITS_EVENT dlgevt;
                ITS_EVENT cmpevt[MAX_NUM_CPT];
                ITS_OCTET numCpts = 0;
                ITS_INT index = 0;
                ITS_INT compindex = 0;


                ret = MABCL_GetDlgComponent(&dlg, &dlgid, cpt, 
                                  &numCpts, &evt.data[DLG_ID_OFFSET],
                                  (evt.len - (sizeof(ITS_ULONG) +
                                  sizeof(ITS_OCTET)))); 

                ITS_EVENT_TERM(&evt);

                MABCL_AddTCAPEntry(dlg.ptype, dlgid, 1);
                /* check if ptype is 0 means L-CANCEL*/
                if (dlg.ptype)
                {

                    if (TCAP_VendorDialogueSanityCheck(&dlg) != 
                                                   ITS_SUCCESS) 
                    {
                        continue;
                    }

                    ITS_EVENT_INIT(&dlgevt, ITS_TCAP_SRC, 
                                   sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                                   sizeof(TCAP_DLG));

                    dlgevt.data[index++] = ITS_TCAP_DLG;

                    /* fill the dialogue id */
                    memcpy(&dlgevt.data[index], &dlgid, sizeof(ITS_CTXT));

                    index = index + sizeof(ITS_CTXT);

                    /* copy the Dialogue */ 
                    memcpy(&dlgevt.data[index],&dlg,sizeof(TCAP_DLG));
                    index = index + sizeof(TCAP_DLG);
                    dlgevt.len = index; 

                    ret = MABCL_PutEventOnTaskQue(&MAB_Connection.taskTrans,
                                                 &dlgevt);
                    if (ret != ITS_SUCCESS)
                    {
                        printf("Some problem in puting the event on to list\n");
                    }
                }

                for (compindex = 0; compindex < numCpts;++compindex)
                {
                    index = 0;
                    if (TCAP_VendorComponentSanityCheck(&cpt[compindex])
                                                          != ITS_SUCCESS)
                    {
                        continue;
                    }

                    cmpevt[compindex].data = 
                           (ITS_OCTET*) malloc(sizeof(TCAP_CPT) +
                           sizeof(ITS_OCTET) +
                           sizeof(ITS_CTXT));

                    cmpevt[compindex].data[index++] = ITS_TCAP_CPT;

                    /* fill the dialogue id */
                    memcpy(&cmpevt[compindex].data[index], 
                                         &dlgid, sizeof(ITS_CTXT));

                    index = index + sizeof(ITS_CTXT);

                    /* fill the component */
                    memcpy(&cmpevt[compindex].data[index], 
                                          &cpt[compindex],
                                         sizeof(TCAP_CPT));

                    index = index + sizeof(TCAP_CPT);

                    cmpevt[compindex].len = index;
                    cmpevt[compindex].src = ITS_TCAP_SRC;

                    /* send the component evt */
                    ret = MABCL_PutEventOnTaskQue(
                              &MAB_Connection.taskTrans,
                             &cmpevt[compindex]);

                    if (ret != ITS_SUCCESS)
                    {
                        printf("Error puting event on to list\n");
                    }
                }
            }
            else
            {
                if (evt.data[sizeof(ITS_ULONG)] == REGISTER_ACK_MSG ||
                     evt.data[sizeof(ITS_ULONG)]  == DERGISTER_ACK_MSG) 
                {
                    MAB_Connection.backupInfo.regStatus = 
                    evt.data[sizeof(ITS_ULONG)+ 
                           sizeof(ITS_OCTET) + sizeof(ITS_OCTET)];
                } 
                else if (evt.data[sizeof(ITS_ULONG)] == ISUP_MSG)
                {
                    ITS_OCTET msgType;
                    ITS_CTXT cic;
                    msgType = evt.data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET)];
                    memcpy(&cic,&evt.data[sizeof(ITS_ULONG) + sizeof(ITS_OCTET) +
                                   sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
                                   sizeof(ITS_USHORT));

                    MABCL_AddISUPEntry(msgType, cic , 1);
                }

                ret = MABCL_PutEventOnTaskQue(&MAB_Connection.taskTrans, &evt);
                if (ret != ITS_SUCCESS)
                {
                    printf("Some problem in puting the event on to list\n");
                }
            }

        }
        else if (ret == ITS_ENOSOCKET)
        {
            continue;
        }
        else if (ret == ITS_ERCVFAIL)
        {
            SOCK_Close(MAB_Connection.backupInfo.sockInfo);
            MAB_Connection.backupInfo.sockInfo = NULL;
            MAB_Connection.backupInfo.isPrimary = ITS_FALSE;

            if (MAB_Connection.primaryInfo.isUp)
            {
                MAB_Connection.primaryInfo.isPrimary = ITS_TRUE;
                //update all the entry with backup
                MABCL_UpdateHashEntry(0);
            }
            else
            {
                //delete all entry in hash tables
                MABCL_DeleteHashEntry();
            }

            ret = MABCL_Connect(&MAB_Connection.backupInfo);
            if (ret != ITS_SUCCESS)
            {
                if (ret == ITS_ENOSOCKET)
                {
                    printf("Attempt to reconnect failed check server\n");
                    printf("Server IP Addr %s and Port# %d\n",
                            MAB_Connection.backupInfo.ipAddr,
                            MAB_Connection.backupInfo.port);
                    MABCL_CloseConnection(MABCL_BACKUP_CONNECTION);
                    THREAD_DeleteThread(&MAB_Connection.backupInfo.thrInfo.info);
#ifdef WIN32
		    return 0;
#else
                    return NULL;
#endif
                }
                else if (ret == ITS_ECONNECTFAIL)
                {
                    continue;
                }
                else
                {
                    printf("We have major problem here ---\n");
#ifdef WIN32
		    return 0;
#else
                    return NULL;
#endif
                }
            }
            else
            {
                printf(" Backup connection reconnected \n");

                MUTEX_AcquireMutex(&regLock);

                if(MAB_Connection.regInfoLen &&
                   MAB_Connection.reRegInfo != NULL)
                {
                    ITS_EVENT_INIT(&reRegevt, MABCL_APP_SRC,
                                  MAB_Connection.regInfoLen);

                    memcpy(reRegevt.data, MAB_Connection.reRegInfo,
                           MAB_Connection.regInfoLen);

                    ret = MABCL_WriteEvent((ITS_HANDLE*)&MAB_Connection.backupInfo,
                                        &reRegevt);

                    if (ret != ITS_SUCCESS)
                    {
                        printf("Backup conn rereg failed ret %d\n", ret);
                    }
                    else
                    {
                        printf("Backup conn rereg written successfully\n");
                    }
                }

                MUTEX_ReleaseMutex(&regLock);

                /* Extra check for non redundant */
                if(MAB_Connection.primaryInfo.isUp == ITS_FALSE)
                {
                    MAB_Connection.backupInfo.isPrimary = ITS_TRUE;
                }
                continue;
            }
        } 
    }
    MUTEX_AcquireMutex(&regLock);
    if(MAB_Connection.backupInfo.sockInfo)
    {
        SOCK_Close(MAB_Connection.backupInfo.sockInfo);
        MAB_Connection.backupInfo.sockInfo = NULL;
    }
    if (MAB_Connection.backupInfo.thrInfo.isRunning)
    {
        THREAD_DeleteThread(&MAB_Connection.backupInfo.thrInfo.info);
    }
    MABCL_CloseConnection(MABCL_BACKUP_CONNECTION);
    MUTEX_ReleaseMutex(&regLock);

    printf("Thread exiting for backup connection\n");
#ifdef WIN32
		    return 0;
#else
                    return NULL;
#endif
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method pre intializes 
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs int if ITS_SUCCESS 
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_PreInitialize(ITS_HANDLE *handle)
{
    ITS_INT ret =0;

    /* Create hash table for storing the context and transport instance */
    _CL_CTXT_info = HASH_CreateTable();

    if(_CL_CTXT_info == NULL)
    {
        printf("Failed to create hashtable!\n");
        exit(1);
    }

    /*primary initialization*/
    MAB_Connection.primaryInfo.thrInfo.func = PrimaryThreadFunction;
    MAB_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    MAB_Connection.primaryInfo.isUp = ITS_FALSE;
    MAB_Connection.primaryInfo.isInitialized = ITS_FALSE;
    MAB_Connection.primaryInfo.isClose = ITS_FALSE;
    MAB_Connection.primaryInfo.sockInfo = NULL;
    MAB_Connection.primaryInfo.isPrimary = ITS_TRUE;

    if (MUTEX_CreateMutex(&MAB_Connection.primaryInfo.readLock, 0) != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&MAB_Connection.primaryInfo.writeLock, 0) != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&hashLock, 0) != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&regLock, 0) != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    /*Back up initialization*/
    MAB_Connection.backupInfo.thrInfo.func = BackupThreadFunction;
    MAB_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    MAB_Connection.backupInfo.isUp = ITS_FALSE;
    MAB_Connection.backupInfo.isInitialized = ITS_FALSE;
    MAB_Connection.backupInfo.isClose = ITS_FALSE;
    MAB_Connection.backupInfo.sockInfo = NULL;
    MAB_Connection.backupInfo.isPrimary = ITS_FALSE;
    if (MUTEX_CreateMutex(&MAB_Connection.backupInfo.readLock, 0) 
        != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (MUTEX_CreateMutex(&MAB_Connection.backupInfo.writeLock, 0) 
        != ITS_SUCCESS)
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    /* Create Task Que for client */
    MAB_Connection.taskTrans.taskQue = EMLIST_Create();

    /* Create the TCAP prim queue */
    if ((TCAP_primQueue = MQUEUE_Create()) == NULL)
    {
        printf("Failed to create TCAP queue!\n");
        exit (1);
    }

    MAB_Connection.ltid = 1;
    MAB_Connection.utid = MAX_NUM_LID;
    MAB_Connection.clid = 0;
    MAB_Connection.reRegInfo = NULL;
    MAB_Connection.regInfoLen = 0;

    *handle = MABCL_GetHandle();

    return ret;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method creates a client stream socket and connects to the server
 *      socket
 *
 *  Input Parameters:
 *      host  - host machine IP address.
 *      port  - port number of the server
 *      type - MABCL_CONNECTION_TYPE 0- primary 1-Backup.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns int. 
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_Initialize(const char *host, ITS_INT port, 
                 MABCL_CONNECTION_TYPE type)
{
    ITS_INT ret =0;
    if (host == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    if (type == MABCL_PRIMARY_CONNECTION)
    {
        if (MAB_Connection.primaryInfo.isInitialized == ITS_TRUE)
        {
            printf("Client already connected on this connection\n");
            return ITS_EINUSE;
        }

        memcpy(&MAB_Connection.primaryInfo.ipAddr, host, strlen(host));
        MAB_Connection.primaryInfo.port = port;
        MAB_Connection.primaryInfo.isClose = ITS_FALSE;

        ret = MABCL_Connect(&MAB_Connection.primaryInfo);
        if (ret == ITS_SUCCESS)
        {
            printf("Client successfully connected\n");
        }
        else if (ret == ITS_ENOSOCKET)
        {
            printf("Attempt to connect to server failed check\n");
            printf("Server IP Addr %s and Port# %d\n",
                    MAB_Connection.primaryInfo.ipAddr,
                    MAB_Connection.primaryInfo.port);

            MABCL_CloseConnection(MABCL_PRIMARY_CONNECTION);
            return ret;
        }
        else
        {
            printf("We have major problem here in init---\n");
            return ret;
        }

        MAB_Connection.primaryInfo.isUp = ITS_TRUE;
        MAB_Connection.primaryInfo.thrInfo.isRunning = ITS_TRUE;
        THREAD_CreateThread(&MAB_Connection.primaryInfo.thrInfo.info,
                            0,
                            MAB_Connection.primaryInfo.thrInfo.func,
                            NULL,
                            ITS_TRUE);
        MAB_Connection.primaryInfo.isInitialized = ITS_TRUE;
        MAB_Connection.primaryInfo.isPrimary = ITS_TRUE;

            
    }
    else if (type == MABCL_BACKUP_CONNECTION)
    {
        if (MAB_Connection.backupInfo.isInitialized == ITS_TRUE)
        {
            printf("Client already connected on this connection\n");
            return ITS_EINUSE;
        }

        memcpy(&MAB_Connection.backupInfo.ipAddr, host, strlen(host));
        MAB_Connection.backupInfo.port = port;
        MAB_Connection.backupInfo.isClose = ITS_FALSE;

        ret = MABCL_Connect(&MAB_Connection.backupInfo);
        if (ret == ITS_SUCCESS)
        {
            printf("Client successfully connected\n");
        }
        else if (ret == ITS_ENOSOCKET)
        {
            printf("Attempt to connect to server failed check\n");
            printf("Server IP Addr %s and Port# %d\n",
                    MAB_Connection.backupInfo.ipAddr,
                    MAB_Connection.backupInfo.port);

            MABCL_CloseConnection(MABCL_BACKUP_CONNECTION);
            return ret;
        }
        else
        {
            printf("We have major problem here ---\n");
            return ret;
        }

        if (MAB_Connection.backupInfo.sockInfo == NULL)
        {
            return ITS_ENOSOCKET;
        }

        MAB_Connection.backupInfo.isUp = ITS_TRUE;
        MAB_Connection.backupInfo.thrInfo.isRunning = ITS_TRUE;
        THREAD_CreateThread(&MAB_Connection.backupInfo.thrInfo.info,
                            0,
                            MAB_Connection.backupInfo.thrInfo.func,
                            NULL,
                            ITS_TRUE);
        MAB_Connection.backupInfo.isInitialized = ITS_TRUE;
        MAB_Connection.backupInfo.isPrimary = ITS_TRUE;

    }

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method do the clean up job
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI void
MABCL_Terminate()
{
    MAB_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    MAB_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;

    MUTEX_DeleteMutex(&MAB_Connection.primaryInfo.readLock); 
    MUTEX_DeleteMutex(&MAB_Connection.primaryInfo.writeLock); 
    
    MUTEX_DeleteMutex(&MAB_Connection.backupInfo.readLock); 
    MUTEX_DeleteMutex(&MAB_Connection.backupInfo.writeLock); 

    EMLIST_Delete(MAB_Connection.taskTrans.taskQue);

    if (MAB_Connection.primaryInfo.sockInfo)
    {
        printf("Closing primary connection \n");
        MABCL_CloseConnection(MABCL_PRIMARY_CONNECTION);
    }

    if (MAB_Connection.backupInfo.sockInfo)
    {
        printf("Closing back up connection \n");
        MABCL_CloseConnection(MABCL_BACKUP_CONNECTION);
    }

    MQUEUE_Delete(TCAP_primQueue); 

    printf("------ Terminating client application -----\n");
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method registers the routing info with server.
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      msg - MABCL_MESSAGE structure pointer which contains 
 *                          Deregistration information.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_Register(ITS_HANDLE handle, MABCL_MESSAGE *msg)
{
    ITS_EVENT primevt;
    ITS_EVENT bckevt;
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT index = 0;
    /* validate the msg */
    if (MABCL_ValidateContext(&msg->u.regInfo) !=
        ITS_SUCCESS)
    {
        printf("MABCL_Register: validation failed ret\n");
        return !ITS_SUCCESS;
    }
 
    if (MAB_Connection.primaryInfo.isUp == ITS_TRUE)
    {
        /* form a register event and send to server*/
       
        ITS_EVENT_INIT(&primevt, MABCL_APP_SRC, sizeof(MABCL_MESSAGE));

        if(MABCL_Encode(msg, &primevt)!= ITS_SUCCESS)
        {
            printf(" Encode failure.....\n");
            return !ITS_SUCCESS;
        };

        printf("MABCL_Register Event:: %s sending event..... \n",
                MAB_Connection.primaryInfo.ipAddr);
                                                                                
        printf("\n"); 
        for(index =0;index < primevt.len;index++)
        {   
            if ((index + 1) % 16 == 0) printf("\n");
            printf("%02x ",primevt.data[index]);
        }
        printf("\n");

        /* making a copy of evt for reregistering purpose */

        MUTEX_AcquireMutex(&regLock);

        if (MAB_Connection.regInfoLen)
        {
            MAB_Connection.regInfoLen = 0;
        }

        if(MAB_Connection.reRegInfo != NULL)
        {
           free(MAB_Connection.reRegInfo);
           MAB_Connection.reRegInfo = NULL;
        }
         
        MAB_Connection.reRegInfo = (ITS_OCTET *)malloc(primevt.len);
        MAB_Connection.regInfoLen = primevt.len;
        memcpy(MAB_Connection.reRegInfo, primevt.data, primevt.len);
 
        MUTEX_ReleaseMutex(&regLock);

        ret = MABCL_WriteEvent((ITS_HANDLE*)&MAB_Connection.primaryInfo, 
                                                               &primevt);

        if (ret != ITS_SUCCESS)
        {
            printf("MABCL_Register:primary conn reg failed ret %d\n", ret);
        }
        else
        {
            printf("MABCL_Register: registration info written successfully.\n");
        }
    }
    else
    {
        printf("Registration failed, check IP config for prim conn \n");

        ret = !ITS_SUCCESS;
    }

    if (MAB_Connection.backupInfo.sockInfo != NULL)
    {
        if (MAB_Connection.backupInfo.isUp == ITS_TRUE)
        {
            /* form a register event and send to server*/
            ITS_EVENT_INIT(&bckevt, MABCL_APP_SRC, (sizeof(MABCL_MESSAGE)) );

            if(MABCL_Encode(msg, &bckevt)!= ITS_SUCCESS)
            {
                printf(" Encode failure.....\n");
                return !ITS_SUCCESS;
            };

            printf("MABCL_Register Event:: %s sending event..... \n",
                   MAB_Connection.backupInfo.ipAddr);
            printf("\n");                                                          
            for(index =0;index < bckevt.len;index++)
            {
                if ((index + 1) % 16 == 0) printf("\n");
                printf("%02x ",bckevt.data[index]);
            }
            printf("\n");

            if (MAB_Connection.primaryInfo.isUp == ITS_FALSE) 
            {
               MUTEX_AcquireMutex(&regLock);

               if (MAB_Connection.regInfoLen)
               {
                  MAB_Connection.regInfoLen = 0;
               }

               if(MAB_Connection.reRegInfo != NULL)
               {
                  free(MAB_Connection.reRegInfo);
                  MAB_Connection.reRegInfo = NULL;
               }
         
               /* making a copy of evt for reregistering purpose */
               MAB_Connection.reRegInfo =(ITS_OCTET *)malloc(bckevt.len);
               MAB_Connection.regInfoLen = bckevt.len;
               memcpy(MAB_Connection.reRegInfo, bckevt.data, bckevt.len);

               MUTEX_ReleaseMutex(&regLock);
            } 

            ret = MABCL_WriteEvent((ITS_HANDLE*)&MAB_Connection.backupInfo,
                                                                &bckevt);
            if (ret != ITS_SUCCESS)
            {
                printf("MABCL_Register:backup conn reg failed ret %d\n", ret);
            }
            else
            {
                printf("MABCL_Register:registration info written success.\n");
            }

        }
        else
        {
            printf("Registration failed, check IP config for backup conn \n");

            ret = !ITS_SUCCESS;
 
        }
    }
    /* copy the ltid & utid to the handle object for the 
     * future use in allocate did */

    if(msg->u.regInfo.routing_criteria == MABCL_TCAP_RT_TID_RANGE)
    {
         MAB_Connection.ltid = msg->u.regInfo.u.tcap.ltid;
         MAB_Connection.utid = msg->u.regInfo.u.tcap.utid;
    }
    

    MAB_Connection.clid = msg->clientID; 
    return ret;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method deregerters the routing info with the server
 *      socket
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      msg - MABCL_MESSAGE structure pointer which contains 
 *                          Deregistration information.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_Deregister(ITS_HANDLE handle, MABCL_MESSAGE *msg)
{
    ITS_EVENT evt;
    ITS_INT index = 0;
                                                                                
    /* form a Deregister event and send to server for primary conn */

    if (MAB_Connection.primaryInfo.isUp)
    {
        ITS_EVENT_INIT(&evt, MABCL_APP_SRC, sizeof(MABCL_MESSAGE));
        if(MABCL_Encode(msg, &evt) == ITS_SUCCESS)
        { 
            printf("MABCL_Deregister Event:: %s sending event..... \n",
                  MAB_Connection.primaryInfo.ipAddr);
            printf("\n");                                                         
            for(index =0;index < evt.len;index++)
            {
                if ((index + 1) % 16 == 0) printf("\n");
                printf("%02x ",evt.data[index]);
            }
            printf("\n");
            MABCL_WriteEvent((ITS_HANDLE*)&MAB_Connection.primaryInfo,
                                                               &evt);
        }
    }
                                                                                
    /* form a Deregister event and send to server for backup conn */
                                                                                
    if (MAB_Connection.backupInfo.isUp)
    {
        ITS_EVENT_INIT(&evt, MABCL_APP_SRC, sizeof(MABCL_MESSAGE));
        if(MABCL_Encode(msg, &evt) == ITS_SUCCESS)
        {
            printf("MABCL_Deregister Event:: %s sending event..... \n",
                                  MAB_Connection.backupInfo.ipAddr);
            printf("\n");                                                                      for(index =0;index < evt.len;index++)
            {
                if ((index + 1) % 16 == 0) printf("\n");
                printf("%02x ",evt.data[index]);
            }
            printf("\n");
            MABCL_WriteEvent((ITS_HANDLE*)&MAB_Connection.backupInfo,
                           &evt);
        }
    }

    MUTEX_AcquireMutex(&regLock);

    if (MAB_Connection.regInfoLen)
    {
        MAB_Connection.regInfoLen = 0;
    }

    if(MAB_Connection.reRegInfo != NULL)
    {
        free(MAB_Connection.reRegInfo);
        MAB_Connection.reRegInfo = NULL; 
    }

    MUTEX_ReleaseMutex(&regLock);

    return ITS_SUCCESS;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrives new event comming from server
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      evt    - ITS_EVENT * 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS if succeeds else returns ITS_ERCVFAIL
 *
 *  Notes:
 *      It retrun ITS_ERCVFAIL if it lost connection with server
 *      in that case user supposed to re Initialize the connection
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT ret =0;
    MABCL_CONNECTION *conn = (MABCL_CONNECTION*)handle;
    ITS_EVENT clevt;

    ITS_EVENT_INIT(&clevt, 1, MAX_TCAP_MSG_EVT);

    if (conn == NULL)
    {
        printf("connection NULL\n"); 
        return ITS_EINVALIDARGS;
    }

    ret = MABCL_GetEventFromTaskQue(&conn->taskTrans, &clevt);
    if (ret != ITS_SUCCESS)
    {
        printf("Failed to receive event from QUE ret %d\n",ret);
        return ret;
    }

    /* check the data ptr */
    if (clevt.data)
    {  
        switch(clevt.data[sizeof(ITS_ULONG)])
        {
            /* If ISUP strip the client id and message */
            case ISUP_MSG:
            {
                GetISUPEvent(evt , clevt.data , clevt.len); 
                evt->src = ITS_ISUP_SRC;
                break;
            }  

            default:
            {
                ITS_EVENT_INIT(evt, clevt.src , clevt.len);
                memcpy(evt->data, clevt.data, clevt.len); 
                break; 
            } 
        }

       /* Terminate the event */ 
       ITS_EVENT_TERM(&clevt);
    }
    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method closes the socket connection with server, this is for the
 *      user to close connection with one server and establish conn with new,
 *      or may be swap the connection ie primary to backup or vice-versa.
 *
 *  Input Parameters:
 *      type MABCL_CONNECTION_TYPE 0-Primary 1- Backup.
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_CloseConnection(MABCL_CONNECTION_TYPE type)
{
    if (type == MABCL_PRIMARY_CONNECTION)
    {
        MAB_Connection.primaryInfo.isUp = ITS_FALSE;
        MAB_Connection.primaryInfo.isInitialized = ITS_FALSE;
        MAB_Connection.primaryInfo.thrInfo.isRunning = ITS_FALSE;
    }
    else if (type == MABCL_BACKUP_CONNECTION)
    {
        MAB_Connection.backupInfo.isUp = ITS_FALSE;
        MAB_Connection.backupInfo.isInitialized = ITS_FALSE;
        MAB_Connection.backupInfo.thrInfo.isRunning = ITS_FALSE;
    }
    else
    {
        printf("\n Error::Unrecognised connection type %d\n", type);
        return !ITS_SUCCESS;
    }

    return ITS_SUCCESS;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method fills the event structure from the buffer. 
 *
 *  Input Parameters:
 *      buf  This is the data part after lenth. 
 *      len  This is the length read from the socket 
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
ITS_INT
GetISUPEvent(ITS_EVENT *evt, ITS_OCTET *buf, ITS_USHORT len)
{
    ITS_EVENT_INIT(evt, ITS_ISUP_ANSI_SRC , 
                   len - (sizeof(ITS_ULONG) + sizeof(ITS_OCTET)));

    memcpy(evt->data, buf + (sizeof(ITS_ULONG) + sizeof(ITS_OCTET)), 
           len - (sizeof(ITS_ULONG) + sizeof(ITS_OCTET)));

    return ITS_SUCCESS; 
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method validates whether the context infomation provided 
 *      is correct or not depending on the routing criteria.
 *
 *  Input Parameters:
 *      reginfo - pointer to the register info structure.
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
ITS_INT
MABCL_ValidateContext(MABCL_REGISTER *reginfo)
{
    ITS_INT ret = !ITS_SUCCESS;

    switch(reginfo->routing_criteria)
    {
        case MABCL_TCAP_RT_DID_EVEN:
        case MABCL_TCAP_RT_DID_ODD:
        { 
             ret = ITS_SUCCESS;
             break; 
        }
        case MABCL_TCAP_RT_TID_RANGE:
        { 
             if((reginfo->u.tcap.ltid != 0) && (reginfo->u.tcap.utid != 0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_TCAP_RT_LPC_DPC_LSSN:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.tcap.lpc) != 0 ) &&
                (MTP3_PC_GET_VALUE(reginfo->u.tcap.dpc) != 0) &&
                                  (reginfo->u.tcap.ssn != 0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_TCAP_RT_LPC_LSSN:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.tcap.lpc) != 0 )
                                && (reginfo->u.tcap.ssn != 0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_TCAP_RT_LSSN:
        {
             if(reginfo->u.tcap.ssn != 0) 
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_TCAP_RT_LPC:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.tcap.lpc) != 0)) 
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_TCAP_RT_DPC:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.tcap.dpc) != 0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_ISUP_RT_LPC_CIC_RANGE:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.isup.lpc) != 0) && 
                (reginfo->u.isup.lcic !=0) && (reginfo->u.isup.ucic !=0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_ISUP_RT_DPC_CIC_RANGE:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.isup.dpc) != 0) && 
                (reginfo->u.isup.lcic !=0) && (reginfo->u.isup.ucic !=0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_ISUP_RT_LPC:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.isup.lpc)  != 0)) 
             {
                 ret = ITS_SUCCESS;
             }
             break;
        }
        case MABCL_ISUP_RT_DPC:
        {
             if((MTP3_PC_GET_VALUE(reginfo->u.isup.dpc) != 0))
             {
                 ret = ITS_SUCCESS;
             }
             break;
        } 
    }
    return ret;
} 
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method returns the ISS7_Stack
 *  Input Parameters:
 *      None.
 *  Output Parameters:
 *
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_HANDLE
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_HANDLE
MABCL_GetHandle()
{
  return ISS7_Stack; 
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method creates the Prim Queue.
 *
 *  Input Parameters:
 *      None.
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
MABCL_CreateCompDlgQ()
{
    /* Create the TCAP prim queue */
    if ((TCAP_primQueue = MQUEUE_Create()) == NULL)
    {
      printf("Failed to create TCAP queue!\n");
      return !ITS_SUCCESS;
    }
    return ITS_SUCCESS; 
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method delets the Prim Queue.
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
MABCL_DLLAPI void 
MABCL_DeleteCompDlgQ()
{
    MQUEUE_Delete(TCAP_primQueue); 
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method gives the fill the registration return info.
 *  Input Parameters:
 *      reginfo - pointer to the register info structure.
 *      event - pointer to the input event.
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
MABCL_ReceiveRegisterIndication(ITS_HANDLE handle, 
                                ITS_EVENT  *event,
                                MABCL_REGISTER_ACK *regInfo)
{
  ITS_INT   ret = ITS_SUCCESS;
  ITS_OCTET offset = sizeof(ITS_ULONG) + sizeof(ITS_OCTET);

  memcpy(regInfo, &event->data[offset], sizeof(MABCL_REGISTER_ACK)); 

  return ret;
} 

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method gives the fill the deregistration return info.
 *  Input Parameters:
 *      reginfo - pointer to the register info structure.
 *      event - pointer to the input event.
 *
 *  Input Parameters:
 *      reginfo - pointer to the deregister info structure.
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
MABCL_ReceiveDeRegisterIndication(ITS_HANDLE handle, 
                                  ITS_EVENT  *event,
                                  MABCL_DEREGISTER_ACK *regInfo)
{
  ITS_INT ret = ITS_SUCCESS;
  ITS_OCTET offset = sizeof(ITS_ULONG) + sizeof(ITS_OCTET);

  memcpy(regInfo, &event->data[offset], sizeof(MABCL_DEREGISTER_ACK)); 

  return ret;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method fills the dialog and component structures.
 *  Input Parameters:
 *      dlg, cpt, dlgid, numCpts, data, len.
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
MABCL_GetDlgComponent(TCAP_DLG  *dlg, ITS_CTXT *dlgid, 
                      TCAP_CPT  *cpt, ITS_OCTET  *numCpts,
                      ITS_OCTET *data,ITS_USHORT len)
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
    origaddr.len = 0;
    destaddr.len = 0;
    *dlgid = 0;
    
    for(index = 0; index<sizeof(ITS_CTXT); ++index)  
    {
        *dlgid |= data[counter++] << (8 * index);
    }

    /*extract the pkg type */
    ptype = data[counter++];

    if (ptype)
    {
        /* qos parameter */ 
        memcpy(&qos, &data[counter],sizeof(DLG_QOS));
        counter = counter + sizeof(DLG_QOS);
    }

    switch(ptype)
    {
        case TCPPT_TC_UNI:
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_BEGIN:
#elif defined(ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
#endif
        {
            /* copy the len of orig addr */
            origaddr.len |= data[counter++];
            origaddr.len |= data[counter++] << 8;  
            
            /* copy orig addr */ 
            memcpy(origaddr.data,
                   &data[counter],
                   origaddr.len);

            counter = counter + origaddr.len;  

            /* copy the len of dest addr */
            destaddr.len |= data[counter++];
            destaddr.len |= data[counter++] << 8;  
               
            /* copy dest addr */ 
            memcpy(destaddr.data,
                   &data[counter],
                   destaddr.len);

            counter = counter + destaddr.len;  

            /* copy the opc */ 
            memcpy(&opc, &data[counter],
                   sizeof(MTP3_POINT_CODE));

            counter = counter + sizeof(MTP3_POINT_CODE);  

            /* copy the dpc */ 
            memcpy(&dpc, &data[counter],
                   sizeof(MTP3_POINT_CODE));

            counter = counter + sizeof(MTP3_POINT_CODE);  

            break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_CONTINUE:
#elif defined(ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
#endif
        {
            /* copy the len of orig addr */
            origaddr.len |= data[counter++];
            origaddr.len |= data[counter++] << 8;  
            
            /* copy orig addr */ 
            memcpy(origaddr.data,
                   &data[counter],
                   origaddr.len);
                   counter = counter + origaddr.len;  

            /* copy the opc */ 
            memcpy(&opc, &data[counter],
                   sizeof(MTP3_POINT_CODE));

            counter = counter + sizeof(MTP3_POINT_CODE);  
        }     
    } 

    if (ptype)
    {

    /*parse the dlg/component */
#if defined(ANSI)
        ret = TCAP_FindParts_ANSI(&data[counter], (len - counter), &tp, &dp, &cp); 
#else
        ret = TCAP_FindParts_CCITT(&data[counter], (len - counter), &tp, &dp, &cp); 
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
                                     cpPresent, (len - counter), 0);
#endif

        /* Update the address and QOS info */
        ret = MABCL_UpdateAddrsAndQOS(dlg, origaddr, destaddr, 
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
    }
    else
    {
        cpData = &data[counter];
    }
   
     
#if defined(CCITT) || defined(PRC)
        if (ptype != TCPPT_TC_U_ABORT && cp != NULL)
#elif defined(ANSI)
        if (ptype != TCPPT_TC_ABORT && cp != NULL)
#endif
    {
        /* Get Compnt Sequence Tag */
        cpData += TCAP_GetTag(cpData, &cpTag, tp + (len - counter));
                                                                                
        /* Get Component Sequence length cpLen */
        cpData += TCAP_GetLength(cpData, &cpLen, 
                  tp + (len - counter), ITS_TRUE);

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
                                          tp + (len - counter) , ITS_TRUE);
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

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method updates the Addresses..
 *  Input Parameters:
 *      dlg Dialog pointer.
 *      origaddr  Origination address.
 *      destaddr  Destination address.
 *      opc 
 *      dpc 
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
MABCL_UpdateAddrsAndQOS(TCAP_DLG *dlg, SCCP_ADDR origaddr, 
                        SCCP_ADDR destaddr, DLG_QOS qos, 
                        MTP3_POINT_CODE *opc, MTP3_POINT_CODE *dpc)
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
            memcpy(&dlg->u.uni.opc,
                          opc,
                    sizeof(MTP3_POINT_CODE)); 

            /* copy the dpc */ 
            memcpy(&dlg->u.uni.dpc,
                   dpc,
                   sizeof(MTP3_POINT_CODE)); 


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
            memcpy(&dlg->u.begin.opc,
                  opc, sizeof(MTP3_POINT_CODE)); 

            /* copy the dpc */ 
            memcpy(&dlg->u.begin.dpc,
                  dpc, sizeof(MTP3_POINT_CODE)); 

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
            memcpy(&dlg->u.cont.qos, &qos, sizeof(DLG_QOS));

            /* copy the origaddr */
            dlg->u.cont.orig_addr.len = origaddr.len;
            memcpy(dlg->u.cont.orig_addr.data,
                   origaddr.data,
                   origaddr.len); 

            /* copy the opc */ 
            memcpy(&dlg->u.cont.opc,
                  opc,
                  sizeof(MTP3_POINT_CODE)); 

            break;
        }     
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_END:
#elif defined(ANSI)
        case TCPPT_TC_RESP:
#endif
        {
            /* qos parameter */ 
            memcpy(&dlg->u.end.qos, &qos, sizeof(DLG_QOS));

            break;
        }
#if defined(CCITT) || defined(PRC)
        case TCPPT_TC_U_ABORT:
#elif defined(ANSI)
        case TCPPT_TC_ABORT:
#endif
        {
            /* qos parameter */ 
            memcpy(&dlg->u.abort.qos, &qos, sizeof(DLG_QOS));

            break;
        }
    }
    return ITS_SUCCESS;
}
