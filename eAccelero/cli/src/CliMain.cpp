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

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "dq_cli.h"
#include <pthread.h>
#include <stdlib.h>
#include "cmd_utils.h"
#include "CliParser.h"
#include "CliRegister.h"
#include "CliCallback.h"


#define CLITEST_PORT                8000
#define MODE_CONFIG_INT             10

#define CLI_MESS_PORT_MIN 9000
#define CLI_MESS_PORT_MAX 10000
#define IWF_CLI_LISTEN_QUEUE_LEN 50

unsigned int regular_count = 0;
unsigned int debug_regular = 0;

const char DREVer[] =DRE_VER;

extern "C" void* ConfigFetchThread(void *args);
extern "C" void* MeSSThread(void *args);
extern "C" void sig_handler(int sigVal);
extern "C" void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);
extern "C" void cli_commands_init(struct cli_def *cli);
extern "C" int idle_timeout(struct cli_def *cli);
extern "C" int regular_callback(struct cli_def *cli);
extern "C" void TerminateCmnMgmtMeSS();
int adduser(struct cli_def *cli,unsigned char *user,unsigned char *passwd);
int deleteuser(struct cli_def *cli,unsigned char *user,unsigned char *passwd);

/*********************************************************************************************



 *********************************************************************************************/
void cli_commands_init(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    dre_cli_init(cli);

    iwf_cli_init(cli);

    repmgr_cli_init(cli);

    avamgr_cli_init(cli);
    CLI_DEBUG_LOG(" Exited ");
}

int check_auth(char *username, char *password)
{
    CLI_DEBUG_LOG(" Entered ");
    if (strcasecmp(username, "fred") != 0)
        return CLI_ERROR;
    if (strcasecmp(password, "nerk") != 0)
        return CLI_ERROR;
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int regular_callback(struct cli_def *cli)
{
    regular_count++;
    if (debug_regular)
    {
        cli_print(cli, (char *)"Regular callback - %u times so far", regular_count);
        cli_reprompt(cli);
    }
    return CLI_OK;
}

int check_enable(char *password)
{
    return !strcasecmp(password, "imsdia");
}

int idle_timeout(struct cli_def *cli)
{
    cli_print(cli, (char *)"Custom idle timeout");
    CLI_NOTICE_LOG("Custom idle timeout");
    return CLI_QUIT;
}


/*********************************************************************************************



 *********************************************************************************************/
int main(int argc,char* argv[])
{
    int s, x;
    int ret=0;
    struct sockaddr_in addr;
    int on = 1;
    void* (*ptr)(void *args);
    CliArgs *cmdLine = (CliArgs*)malloc(sizeof(CliArgs));
    cmdLine->argc = argc;
    cmdLine->argv = argv;
    void *args = (void*)cmdLine;

    pthread_t threads=0;
    pthread_t cfgFetchThread=0;
    pthread_attr_t        attr; 
    int generated_portnum = CLI_MESS_PORT_MIN;
    if (argc >= 2 && argv[1] && !strcmp(argv[1], "--version")) 
    {
        printf("Diametriq DRE %s\n", DREVer);
        exit(0);
    }
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, sig_handler);

    pthread_create(&threads,NULL,MeSSThread,(void*)args);

    //pthread_detach(threads);
    sleep(2);

    pthread_create(&cfgFetchThread, NULL, ConfigFetchThread, NULL);
    pthread_detach(cfgFetchThread);

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
     
    if ((setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) == -1 )||
            (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(int)) == -1 ))
    {
        perror("SetSocketOpt");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(CLITEST_PORT);
    
    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    
    if (listen(s, IWF_CLI_LISTEN_QUEUE_LEN) < 0)
    {
        perror("listen");
        return 1;
    }

    pthread_attr_init(&attr);


    /* Multithreading for each CLI connection */

    while(1)
    {
        struct thread_args thr_args;
        struct sockaddr_in client_addr;
        pthread_t cli_threads = 0;
        socklen_t len = sizeof(addr);

        memset(&client_addr, 0, sizeof(client_addr));

        if((x = accept(s,(struct sockaddr*) &client_addr, &len)) == -1)
        {
            perror("accept");
	    ret=1;
            break;
        }

        thr_args.socket = x;
        thr_args.recv_port = generated_portnum;
        if (getpeername(x, (struct sockaddr *) &addr, &len) >= 0)
        {
            thr_args.socket = x;
            thr_args.recv_port = generated_portnum;
        }
        else
        {
            perror("getpeername");
	    ret=1;
            break;
        }

        ptr = cli_loop;

        pthread_create(&cli_threads,&attr,ptr,(void*)&thr_args);
        pthread_detach(cli_threads);

        if(generated_portnum == CLI_MESS_PORT_MAX) {
            generated_portnum = CLI_MESS_PORT_MIN;
        }else{
            generated_portnum++;
        }
        continue;
    }

    pthread_join(threads, NULL);    
    TerminateCmnMgmtMeSS();


    return ret;

}

