#include <stdio.h>
#include <sip_defines.h>
#include <sip.h>

int
APP_Send180Ringing(ITS_HANDLE handle, SIP_MSG *msg)
{
    int ret;
    SIP_MSG *msgRing;
    SIP_HOST_INFO fromHostInfo, toHostInfo;
    SIP_URI_OBJ fromUri, toUri;

    printf("\nInside APP_Send180Ringing function \n");

    /* Build 180 Ringing and send to SIP stack */
    SIP_InitMsg(&msgRing);
    ret = SIP_SetStartLine(msgRing, "SIP/2.0", 180, "Ringing", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("HandleINVITEIndication:: SIP_SetStartLine fail \n");
        return ret;
    }

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(msgRing, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(msgRing, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    SIP_SetCallidHeader(msgRing, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(msgRing, msg->cseq.number, msg->cseq.method);

    ret = SIP_SendResponse(handle, msgRing);
    if (ret == ITS_SUCCESS)
    {
        printf("180 Ringing msg sent successfully to Stack\n");
    }

    /* Free Received msg */

    return ITS_SUCCESS;
}

int
APP_Send200Ok(ITS_HANDLE handle, SIP_MSG *msg)
{
    int ret;
    SIP_MSG *msgOk;
    SIP_HOST_INFO fromHostInfo, toHostInfo;
    SIP_URI_OBJ fromUri, toUri;

    printf("\nInside APP_Send200Ok function \n");

    /* Build 200 OK and send to SIP stack */
    SIP_InitMsg(&msgOk);
    ret = SIP_SetStartLine(msgOk, "SIP/2.0", 200, "Ok", NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("APP_Send200Ok:: SIP_SetStartLine fail \n");
        return ret;
    }

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(msgOk, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);
    
    /* Set Uri for To Header */ 
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(msgOk, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    SIP_SetCallidHeader(msgOk, msg->callId.number, msg->callId.host);

    SIP_SetCseqHeader(msgOk, msg->cseq.number, msg->cseq.method);
    
    /* Set Content type and content length aswell for 200 OK
    SIP_SetContentlenHeader(msgOk, msg->contentLen.value);  */

    ret = SIP_SendResponse(handle, msgOk);
    if (ret == ITS_SUCCESS)
    {
        printf("200 Ok msg sent successfully to Stack\n");
    }
    
    /* Free Received msg */

    return ITS_SUCCESS;
}   

int
APP_SendAck(ITS_HANDLE handle, SIP_MSG *msg)
{
    SIP_MSG *ack;
    int ret = 0, pos = 0;
    ITS_CHAR *data = NULL;
    SIP_HOST_INFO fromHostInfo, toHostInfo, *host;
    SIP_URI_OBJ uri, fromUri, toUri;
    SIP_HOST_INFO hostInfo;
    ITS_CHAR *version, *protocol;
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;
    SIP_GENERIC_PARAM *genParam[3];



    printf("APP_SendAck:: Inside APP_SendAck() func\n");

    SIP_InitMsg(&ack);

    /* start line must */

    /* Set hostInfo for the startline  lxserver here */
    SIP_SetHostinfo(&hostInfo, 1, "172.16.5.2", "5061");

    /* Set req URI for the startline */
    /* FIXME - Get these things from contact header */
    SIP_SetUri(&uri, "sip", "bob", NULL, &hostInfo);

    SIP_SetStartLine(ack, msg->sipVersion, 0, NULL, "ACK", &uri);

    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(ack, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(ack, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(msg->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
        SIP_SetViaHeader(ack, version, protocol, host,
                         numViaparams, *genParam);
        }
        else
        {
        SIP_SetViaHeader(ack, version, protocol, host,
                         0, NULL);
        }
        pos++;
    }

    SIP_SetCallidHeader(ack, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(ack, msg->cseq.number, "ACK");

    ret = SIP_Encode(ack, &data);
    if (ret != ITS_SUCCESS)
    {
        printf("SIP_Encode Failed for ACK msg, reason=%d\n", ret);
        return ret;
    }

    /*send event to stack */

    ret = SIP_SendRequest(handle, ack);
    if (ret == ITS_SUCCESS)
    {
        printf("ACK MESSAGE Successfuly Sent to STACK\n");
    }

    return ret;
}

int
APP_Send3XX(ITS_HANDLE handle, SIP_MSG *msg)
{
    int ret, pos = 0;
    SIP_MSG *msg3xx;
    SIP_HOST_INFO fromHostInfo, toHostInfo, contactHostInfo, *host;
    SIP_URI_OBJ fromUri, toUri, contactUri;
    SIP_GENERIC_PARAM *genParam[3];
    ITS_CHAR *version, *protocol;
    SIP_VIA_HDR *sipVia;
    ITS_USHORT numViaparams;


    printf("\nInside APP_Send3XX function \n");

    /* Build 3xx and send to SIP stack */
    SIP_InitMsg(&msg3xx);
    ret = SIP_SetStartLine(msg3xx, "SIP/2.0", 302, "Moved Temporarily",
                           NULL, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("APP_Send3XX:: SIP_SetStartLine fail, ErrCode %d \n", ret);
        return ret;
    }
    /* Set Uri for From Header */
    SIP_SetHostinfo(&fromHostInfo, msg->from.url.hostInfo.type,
                    msg->from.url.hostInfo.address,
                    msg->from.url.hostInfo.port);
    SIP_SetUri(&fromUri, msg->from.url.scheme, msg->from.url.userName,
               msg->from.url.password, &fromHostInfo);
    SIP_SetFromHeader(msg3xx, &fromUri, msg->from.displayName, NULL,
                      msg->from.numGenparams, NULL);

    /* Set Uri for To Header */
    SIP_SetHostinfo(&toHostInfo, msg->to.url.hostInfo.type,
                    msg->to.url.hostInfo.address,
                    msg->to.url.hostInfo.port);
    SIP_SetUri(&toUri, msg->to.url.scheme, msg->to.url.userName,
               msg->to.url.password, &toHostInfo);
    SIP_SetToHeader(msg3xx, &toUri, msg->to.displayName, NULL,
                      msg->to.numGenparams, NULL);

    SIP_SetCallidHeader(msg3xx, msg->callId.number, msg->callId.host);
    SIP_SetCseqHeader(msg3xx, msg->cseq.number, msg->cseq.method);
    
    /* Send Contact(s), Add carefully */

    SIP_SetHostinfo(&contactHostInfo, SIP_HOST_TYPE_HOSTNAME,
                    "intellinet-india.com", NULL);
    SIP_SetUri(&contactUri, "sip", "227", NULL, &contactHostInfo);
    SIP_SetContactHeader(msg3xx, &contactUri, "Arun", NULL, 0, NULL);


    /* Get Vias one by one and put in trying msg */
    while (!SIP_LISTEol(msg->vias, pos))
    {
        sipVia = (SIP_VIA_HDR *) SIP_ListGet(msg->vias, pos);
        SIP_GetViaHeader(sipVia, &version, &protocol, &host,
                         &numViaparams, genParam);
        if (numViaparams != 0)
        {
        SIP_SetViaHeader(msg3xx, version, protocol, host,
                         numViaparams, *genParam);
        }
        else
        {
        SIP_SetViaHeader(msg3xx, version, protocol, host,
                         0, NULL);
        }
        pos++;
    }

    /* Set Content type and content length aswell for 200 OK
    SIP_SetContentlenHeader(msg3xx, msg->contentLen.value);  */

    ret = SIP_SendResponse(handle, msg3xx);
    if (ret == ITS_SUCCESS)
    {
        printf("302 moved temp msg sent successfully to Stack\n");
    }
    /* Free Received msg */

    return ITS_SUCCESS;
}

