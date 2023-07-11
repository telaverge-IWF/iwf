
/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

/*
 *******************************************************************************
 *      
 *      
 *******************************************************************************
 *     
 *      PROJECT         : DRE
 *      FILE            : MeSSInterface.c
 *      MODULE          : cli
 *      ENGINEER        : Ananth, Prabhakar, Krishna 
 *      DESCRIPTION     : The file contains function for forwarding
 *      configuration request to individual modules by calling MESS methods.
 *      HISTORY         : <Initial Implementation>
 *      
 *******************************************************************************
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>

#include "LibCli.h"
#include "cmd_utils.h"
#include "CliParser.h"
#include "CliRegister.h"
#include "CliCallback.h"
#include "CommonStructure.h"

#define MAXEVENTS 4
#define MAX_EVENTS 10

extern void SendConfigRequest(int port,char* buf,int len,int cmdID,int interfaceID);
extern int printcli(struct cli_def *cli,void* buf);
extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);

/*******************************************************************************
 * Function name         : send_receive_data
 * return                : 
 * arguments             : pointer to cli definition strucutre
 * Description           : Forwards user configuration request to individual
 * modules by calling MESS methods. After send the request it waits on the UDP
 * socket for the response.
 *
 * Notes                 : This is the synchronous implentation of req and
 * response. If asynchronous is required, epoll mechanism can be used for
 * multiplexing across telnet client TCP socket and UDP socket. For doing this
 * epoll mechanism can be moved to LibCli.c
 *******************************************************************************/

//int send_receive_data(struct cli_def *cli,char *buf[],int len,int cmdID)
int send_receive_data(struct cli_def *cli,void *buf,int len,int cmdID,int interfaceID)
{
    CLI_DEBUG_LOG(" Entered ");
    int sock;
    unsigned int addr_len, bytes_read;
    char recv_data[MAX_PAYLOAD_LEN];
    struct sockaddr_in client_addr;

    sock = cli->recv_sock;

    addr_len = sizeof(struct sockaddr);

    SendConfigRequest(cli->server_addr.sin_port,buf,len,cmdID,interfaceID);
    bytes_read = recvfrom(sock,recv_data,MAX_PAYLOAD_LEN,0,(struct sockaddr *)&client_addr, &addr_len);

    printcli(cli,(void*)&recv_data);

    CLI_DEBUG_LOG(" Exited ");
    return 0;
}
