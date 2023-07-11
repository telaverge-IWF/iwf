/****************************************************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: dmc_trans.cpp,v 1.4.50.1 2013/02/27 08:49:07 jvikram Exp $
 *
 * LOG: $Log: dmc_trans.cpp,v $
 * LOG: Revision 1.4.50.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.4  2009/09/17 08:36:29  rajeshak
 * LOG: API to enable/disable DMC hex dump.
 * LOG:
 * LOG: Revision 1.3  2009/05/11 06:43:02  nvijikumar
 * LOG: Re-connect functionality is moved to Application
 * LOG:
 * LOG: Revision 1.2  2009/04/11 05:33:06  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dmc_trans.cpp,v 1.4.50.1 2013/02/27 08:49:07 jvikram Exp $"

#include <its.h>
#include <its++.h>
#include <its_types.h>
#include <its_license.h>
#include <engine++.h>
#include <its_license.h>

/*Just for symbol resolution*/
#include <its_statics.cpp>

#include <arpa/inet.h>

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dmc_trans.h>

//static char* sync_data = "ISS7SSI";
static std::string sync_data = "ISS7SSI";
static ITS_INT   sd_len = 7;
extern ITS_BOOLEAN hexEnabled;

void
PrintEvent(ITS_EVENT *ev)
{
    if (hexEnabled == ITS_TRUE)
    {
        printf(" Event len = %d\n", ev->len);
        printf(" Event src = %d\n", ev->src);
        for(int i=0; i < ev->len; i++)
        {
            if ((i) % 8 == 0)
                printf("\n");
            printf("0x%02x, ",ev->data[i]);
        }
        printf("\n\n");
        fflush(stdout);
    }
}

int
DmcReadWriteUtils::ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT nread = 0, ret =0;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
    ITS_SocketInfo *sockInfo = NULL;

    DMC_TRACE_DBG(("DmcReadWriteUtils::ReadEvent"));
    
    if (handle == NULL)
    {
        DMC_TRACE_ERR(("DmcReadWriteUtils::ReadEvent: handle null"));
        return (ITS_ERCVFAIL);
    }
    sockInfo = (ITS_SocketInfo *)handle;

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
            info.sinfo = sockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(sockInfo, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
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
    nread = SOCK_Read(sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
    nread = SOCK_Read(sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)malloc(evt->len);

    if (evt->data == NULL)
    {
        DMC_TRACE_ERR(("DmcReadWriteUtils::ReadEvent: failed"));
        return (ITS_ENOMEM);
    }
    /* read the data */
    if (evt->len)
    {
        nread = SOCK_Read(sockInfo, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            DMC_TRACE_ERR(("DmcReadWriteUtils::ReadEvent: failed"));
            free(evt->data);
            evt->data = NULL;
            return (ITS_ERCVFAIL);
        }
    }
    return (ITS_SUCCESS);
}

int
DmcReadWriteUtils::WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    ITS_INT nrite;
    ITS_USHORT tmp =0;
    ITS_SocketInfo *sockInfo = NULL;

    DMC_TRACE_DBG(("DmcReadWriteUtils::WriteEvent"));

    if (handle == NULL)
    {
        DMC_TRACE_ERR(("DmcReadWriteUtils::WriteEvent: Handle null"));
        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }
        return (ITS_EINVALIDARGS);
    }
    sockInfo = (ITS_SocketInfo *)handle;

    nrite = SOCK_Write(sockInfo, (char*)sync_data.c_str(), sd_len);
    if (nrite != sd_len)
    {
        DMC_TRACE_ERR(("WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }
        return (ITS_ESENDFAIL);
    }
    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nrite != sizeof(ITS_USHORT))
    {
        DMC_TRACE_ERR(("WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        return (ITS_ESENDFAIL);
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(sockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nrite != sizeof(ITS_USHORT))
    {
        DMC_TRACE_ERR(("WriteEvent: Send fail"));

        /* Free the event*/
        if (evt->data)
        {
            free(evt->data);
            evt->data = NULL;
        }

        return (ITS_ESENDFAIL);
    }

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(sockInfo, (char *)evt->data, evt->len);

        if (nrite != (ITS_INT)evt->len)
        {
            DMC_TRACE_ERR(("DmcReadWriteUtils::WriteEvent: Send fail"));

            /* Free the event*/
            if (evt->data)
            {
                free(evt->data);
                evt->data = NULL;
            }

            return (ITS_ESENDFAIL);
        }
    }
    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data = NULL;
    }
    return (ITS_SUCCESS);
}

int
DmcTransport::Connect()
{
    ITS_INT ret =0;
    ITS_INT repeat_count = 1;
    int    dummy = 1;                    /* for socket option */
    struct linger      linger;           /* for set linger */

    DMC_TRACE_DBG(("Connect"));

    if (isConnUp == ITS_TRUE)
    {
        DMC_TRACE_DBG(("Already Transport is UP\n"));
        return !ITS_SUCCESS;
    }
    else
    {
        ret = SOCK_ClientOpen(&sockInfo,INET_DOMAIN, ipAddr, servPort);
        if (ret != ITS_SUCCESS)
        {
            DMC_TRACE_CRIT(("DmcTransport::Connect: Create client failed"));
            return (ret);
        }

        ret = SOCK_ClientConnect(sockInfo);
        if (ret != ITS_SUCCESS)
        {
            DMC_TRACE_WRN(("Connect: Connect failed....re-trying "
                               "ip addr %s and port %d", ipAddr, servPort));
            SOCK_Close(sockInfo);
            sockInfo = NULL;
            return (ret);
        }
        else
        {
            DMC_TRACE_DBG(("DmcTransport::Connect::Connected to server\n"));
            isConnUp   = ITS_TRUE;
            if (cbFunc != NULL)
            {
                    DMC_CB_INFO cInfo;
                    cInfo.type = DMC_CONNECT;
                    cbFunc(cInfo);
            }
        }
    }
    return (ret);
}

int
DmcTransport::Initialize(const ITS_CHAR *host, ITS_INT port)
{
    int ret = ITS_SUCCESS;

    DMC_TRACE_DBG(("DmcTransport::Initialize"));

    if (host == NULL)
    {
        DMC_TRACE_ERR(("DmcTransport::Initialize: No host configured"));
        return (ITS_EINVALIDARGS);
    }
    if (isInitialized == ITS_TRUE)
    {
        DMC_TRACE_ERR(("DmcTransport::Initialize: Already Initialized"));
        return (!ITS_SUCCESS);
    }

    ipAddr   = strdup(host);
    servPort = port;

    /*
     * Dispatch thread for read
     */
    StartThread();
    isInitialized = ITS_TRUE;

    return ITS_SUCCESS;
}

int
DmcTransport::ReceiveEvent(DM_MSG *msg)
{
    int ret = ITS_SUCCESS;
    ITS_EVENT ev;

    DMC_TRACE_DBG(("DmcTransport::ReceiveEvent"));

    ret = GetNextEvent(&ev);

    if (ret == ITS_SUCCESS)
    {
        ret = DmcCodec::Decode(msg, &ev);
    }
    if (ev.data)
    {
        free(ev.data);
        ev.data = NULL;
    }

    return (ret);
}

void
DmcTransport::ProcessHeartBeat()
{
    ITS_EVENT ev;
    ITS_INT i = 0;
    ITS_INT index = 0;

    DMC_TRACE_DBG(("ProcessHeartBeat"));

    ITS_EVENT_INIT(&ev, DIA_DM_APP_SRC, sizeof(ITS_UINT));

    ev.data[0] = MSG_TYPE_HB;

    for (i = 1; i < sizeof(ITS_UINT); i++)
    {
        ev.data[i] = 0xFF;
    }

    DMC_TRACE_DBG(("\nProcessHeartBeat:: Sending HB ack to server....\n"));    

    if (WriteEvent(sockInfo, &ev) != ITS_SUCCESS)
    {
        DMC_TRACE_ERR(("DmcTransport::Send failed"));
        ITS_EVENT_TERM(&ev);
    }
}

int
DmcTransport::Send(DM_MSG *msg)
{
    int ret = ITS_SUCCESS;
    ITS_EVENT ev;

    DMC_TRACE_DBG(("DmcTransport::Send"));
    if (DmcCodec::Encode(msg, &ev) != ITS_SUCCESS)
    {
        DMC_TRACE_ERR(("DmcTransport::Send Encode failed"));
        ITS_EVENT_TERM(&ev);
        return (!ITS_SUCCESS);
    }
   
    PrintEvent(&ev);

    if (WriteEvent(sockInfo, &ev) != ITS_SUCCESS)
    {
        DMC_TRACE_ERR(("DmcTransport::Send failed"));
        ITS_EVENT_TERM(&ev);
        return (!ITS_SUCCESS);
    }
    return (ret);
}

int
DmcTransport::GetNextEvent(ITS_EVENT *evt)
{
    ITS_INT len = 0, ret;
    void *data = 0;

    DMC_TRACE_DBG(("DmcTransport::GetNextEvent"));
repeat:

    if ((ret = EMLIST_GetNextEventWithTimeOut(taskQue, &data, &len,
                       HMI_GetTimeOutInterval())) != ITS_SUCCESS)
    {
        if (ret == ITS_ETIMEOUT)
        {
            goto repeat;
        }

        if (data != NULL)
        {
            ITS_Free(data);
        }
        return (ret);
    }
    memcpy(evt, data, len);

    if (EMLIST_Lock(taskQue) != ITS_SUCCESS)
    {
        ITS_Free(data);
        return (ITS_EBADMUTEX);
    }

    EMLIST_Unlock(taskQue);
    ITS_Free(data);
    return (ret);
}

int
DmcTransport::PutEvent(ITS_EVENT *evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT index = 0;

    DMC_TRACE_DBG(("DmcTransport::PutEvent"));

    if (EMLIST_Lock(taskQue) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ret = EMLIST_PutEvent(taskQue,(ITS_CHAR*)evt,sizeof(ITS_EVENT));

    EMLIST_Unlock(taskQue);
    return (ret);
}

void
DmcTransport::ReadThread()
{
    ITS_EVENT evt;
    ITS_EVENT reRegevt;
    ITS_INT ret = 0, i = 0;

    while(!_thrExit)
    {
        if (isConnUp != ITS_TRUE)
        {
            sleep(1);
            _thrExit = ITS_FALSE;
            continue;
        }

        ret = ReadEvent(sockInfo,&evt);

        if (ret == ITS_SUCCESS)
        {
            DMC_TRACE_DBG(("\nMessage from server event len:%d\n",evt.len));
            PrintEvent(&evt);
            if (evt.data[0] == MSG_TYPE_HB)
            {
                DMC_TRACE_DBG(("\nMessage HeartBeat Msg received"));
                ProcessHeartBeat();
                continue;
            }
            if (evt.src == DIA_DM_APP_SRC)
            {
                ret = PutEvent(&evt);
                if (ret != ITS_SUCCESS)
                {
                    DMC_TRACE_ERR(("DmcTransport::ReadThread:PutEvent fail"));
                }
            }
        }
        else if (ret == ITS_ENOSOCKET)
        {
            continue;
        }
        else if (ret == ITS_ERCVFAIL)
        {
            DMC_TRACE_ERR(("DmcTransport::ReadThread:connection down"));
            SOCK_Close(sockInfo);
            isConnUp = ITS_FALSE;

            if (cbFunc != NULL)
            {
                DMC_CB_INFO cInfo;
                cInfo.type = DMC_DISCONNECT;
                cbFunc(cInfo);
            }
            else
            {
                DMC_TRACE_WRN(("Callback is not configured"));
            }
        }
    }
    CloseConnection();
}
