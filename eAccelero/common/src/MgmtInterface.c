#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "CommonStructure.h"
extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);
/*******************************************************************************
 * Function name         : sendtomgmt
 * return                : 
 * arguments             : 
 * Description           : 
 * Notes                 : 
 *******************************************************************************/

int SendResponseToMgmt2(void *result,int port)
{
    CLI_DEBUG_LOG(" Entered ");
    int sock;
    unsigned int bytes_sent;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char send_data[MAX_PAYLOAD_LEN];
    NoResponse rsp;
    memset(&rsp,0,sizeof(NoResponse));


    memset(send_data,0,sizeof(send_data));
    host = (struct hostent *) gethostbyname((char *)"127.0.0.1");


    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        CLI_CRITICAL_LOG("Socket Exception");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);

    if(result){
        memcpy(send_data,result,MAX_PAYLOAD_LEN);
    }else{
        rsp.cmd_id = -1;
        strcpy(rsp.msg,"Error: No Response Recieved to CLI");
        CLI_CRITICAL_LOG("Error: No Response Recieved to CLI");
        memcpy(send_data,&rsp,sizeof(rsp));
    }
    bytes_sent = sendto(sock, send_data, MAX_PAYLOAD_LEN, 0,
            (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    close(sock);

    CLI_DEBUG_LOG(" Exited ");
    return 0;

}
int SendResponseToMgmt(void *result,int *port)
{
    CLI_DEBUG_LOG(" Entered ");
    int sock;
    unsigned int bytes_sent;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char send_data[MAX_PAYLOAD_LEN];
    NoResponse rsp;
    memset(&rsp,0,sizeof(NoResponse));

    memset(send_data,0,sizeof(send_data));
    host = (struct hostent *) gethostbyname((char *)"127.0.0.1");


    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        CLI_CRITICAL_LOG("Socket Exception");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ((int)*port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);

    if(port != NULL)
        free(port);
    port = NULL;

    if(result){
        memcpy(send_data,result,MAX_PAYLOAD_LEN);
    }else{
        rsp.cmd_id = -1;
        strcpy(rsp.msg,"Error: No Response Received to CLI");
        CLI_CRITICAL_LOG("Error: No Response Received to CLI");
        memcpy(send_data,&rsp,sizeof(rsp));

    }

     bytes_sent = sendto(sock, send_data, MAX_PAYLOAD_LEN, 0,
            (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    close(sock);

    CLI_DEBUG_LOG(" Exited ");
    return 0;

}
