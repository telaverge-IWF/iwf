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

#include "LibCli.h"
#include "cmd_utils.h"
#include "CliParser.h"
#include "CliStrings.h"
#include "CliRegister.h"
#include "CliCallback.h"


static struct cli_command * register_cmd_recursive(struct cli_def *cli, Parser *ptrCmdParser, struct cli_command *c, int parentLevel, int childStart);


/*******************************************************************************************



 *********************************************************************************************/

static int find_commoncommands(struct cli_command *p, Parser *ptrCmdParser, struct cli_command **common, int parent, int *findcount)
{

    if(ptrCmdParser->chldCommands[parent][0])
    {
        for(; p; p = p->next)
        {
            if(strcmp(ptrCmdParser->chldCommands[parent][0], p->command) == 0)
            {
                *common = p;
                *findcount = parent + 1;

                if(p->children)
                    find_commoncommands(p->children, ptrCmdParser, common, parent + 1, findcount);
            }
        }
    }
    return 0;
}

/*******************************************************************************************



 *********************************************************************************************/

int register_user_commands(struct cli_def *cli, Parser *ptrCmdParser)
{
    //struct cli_def *cli;
    struct cli_command *c, *edt, *edt_2, *edt_3, *edt_4, *edt_5, *edt_6, *edt_7, *edt_8, *edt_9, *edt_10, 
                       *edt_11, *edt_12, *edt_13, *edt_14, *edt_15, *edt_16, *edt_17, *edt_18, *edt_19, *edt_20,
                       *edt_21, *edt_22, *edt_23, *edt_24, *edt_25, *edt_26;
    struct cli_command *common = NULL;
    int loopIndex = 0;
    int parentIndex = 0;
    int findCount = 0;

    int parentL2, parentL3, parentL4, parentL5, parentL6, parentL7, parentL8, parentL9, parentL10, parentL11, parentL12,
        parentL13, parentL14, parentL15, parentL16, parentL17, parentL18, parentL19, parentL20,
        parentL21, parentL22, parentL23, parentL24, parentL25, parentL26;
    int i;


    /* Search for the end of command */

    find_commoncommands(cli->commands, ptrCmdParser, &common, 0, &findCount);

    if(common)
    {
        parentIndex = findCount -1;
        c = common;
    }
    else
        c = register_cmd_recursive(cli, ptrCmdParser, NULL, 0, 0);


    /* First Level parent */
    /* This condition is to avoid to register last node itself as the the parent node */
    if((parentIndex + 1) < MAX_PARENT_LEVEL)
        i = parentIndex + 1;
    else
        i = parentIndex;

    if(ptrCmdParser->chldCommands[i][loopIndex] != NULL){

        for( ; loopIndex < MAX_CHILD_COMMAND; loopIndex++)
        {
            if(ptrCmdParser->chldCommands[parentIndex + 1][loopIndex] != NULL){

                edt = register_cmd_recursive(cli, ptrCmdParser, c, parentIndex + 1, loopIndex);

                /* Second Level parent */
                for(parentL2 = 0; (parentL2 < MAX_CHILD_COMMAND) && (parentIndex + 2) < MAX_PARENT_LEVEL; parentL2++)
                {
                    if(ptrCmdParser->chldCommands[parentIndex + 2][parentL2] != NULL){

                        edt_2 = register_cmd_recursive(cli, ptrCmdParser, edt, (parentIndex + 2), parentL2);

                        /* Third Level parent*/
                        for(parentL3 = 0; (parentL3 < MAX_CHILD_COMMAND) && (parentIndex + 3) < MAX_PARENT_LEVEL; parentL3++)
                        {
                            if(ptrCmdParser->chldCommands[parentIndex + 3][parentL3] != NULL){

                                edt_3 = register_cmd_recursive(cli, ptrCmdParser, edt_2, (parentIndex + 3), parentL3);
                                /* Fourth Level Parent */

                                for(parentL4 = 0; (parentL4 < MAX_CHILD_COMMAND) && (parentIndex + 4) < MAX_PARENT_LEVEL; parentL4++)
                                {
                                    /* Fifth Level Parent */        
                                    if(ptrCmdParser->chldCommands[parentIndex + 4][parentL4] != NULL){

                                        edt_4 = register_cmd_recursive(cli, ptrCmdParser, edt_3, (parentIndex + 4), parentL4);

                                        for(parentL5 = 0; (parentL5 < MAX_CHILD_COMMAND) && (parentIndex + 5) < MAX_PARENT_LEVEL; parentL5++)
                                        {
                                            if(ptrCmdParser->chldCommands[parentIndex + 5][parentL5] != NULL){

                                                edt_5 = register_cmd_recursive(cli, ptrCmdParser, edt_4, (parentIndex + 5), parentL5);

                                                for(parentL6 = 0; (parentL6 < MAX_CHILD_COMMAND) && (parentIndex + 6) < MAX_PARENT_LEVEL; parentL6++)
                                                {
                                                    if(ptrCmdParser->chldCommands[parentIndex + 6][parentL6] != NULL){

                                                        edt_6 = register_cmd_recursive(cli, ptrCmdParser, edt_5, (parentIndex + 6), parentL6);

                                                        for(parentL7 = 0; (parentL7 < MAX_CHILD_COMMAND) && (parentIndex + 7) < MAX_PARENT_LEVEL; parentL7++)
                                                        {
                                                            if(ptrCmdParser->chldCommands[parentIndex + 7][parentL7] != NULL){

                                                                edt_7 = register_cmd_recursive(cli, ptrCmdParser, edt_6, (parentIndex + 7), parentL7);
                                                                for(parentL8 = 0; (parentL8 < MAX_CHILD_COMMAND) && (parentIndex + 8) < MAX_PARENT_LEVEL; parentL8++)
                                                                {
                                                                    if(ptrCmdParser->chldCommands[parentIndex + 8][parentL8] != NULL){
                                                                        edt_8 = register_cmd_recursive(cli, ptrCmdParser, edt_7, (parentIndex + 8), parentL8);

                                                                        for(parentL9 = 0; (parentL9 < MAX_CHILD_COMMAND) && (parentIndex + 9) < MAX_PARENT_LEVEL; parentL9++)
                                                                        {
                                                                            if(ptrCmdParser->chldCommands[parentIndex + 9][parentL9] != NULL){
                                                                                edt_9 = register_cmd_recursive(cli, ptrCmdParser, edt_8, (parentIndex + 9), parentL9);

                                                                                for(parentL10 = 0; (parentL10 < MAX_CHILD_COMMAND) && (parentIndex + 10) < MAX_PARENT_LEVEL; parentL10++)
                                                                                {
                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 10][parentL10] != NULL){
                                                                                        edt_10 = register_cmd_recursive(cli, ptrCmdParser, edt_9, (parentIndex + 10), parentL10);

                                                                                        for(parentL11 = 0; (parentL11 < MAX_CHILD_COMMAND) && (parentIndex + 11) < MAX_PARENT_LEVEL; parentL11++)
                                                                                        {
                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 11][parentL11] != NULL){
                                                                                                edt_11 = register_cmd_recursive(cli, ptrCmdParser, edt_10, (parentIndex + 11), parentL11);

                                                                                                for(parentL12 = 0; (parentL12 < MAX_CHILD_COMMAND) && (parentIndex + 12) < MAX_PARENT_LEVEL; parentL12++)
                                                                                                {
                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 12][parentL12] != NULL){
                                                                                                        edt_12 = register_cmd_recursive(cli, ptrCmdParser, edt_11, (parentIndex + 12), parentL12);

                                                                                                        for(parentL13 = 0; (parentL13 < MAX_CHILD_COMMAND) && (parentIndex + 13) < MAX_PARENT_LEVEL; parentL13++)
                                                                                                        {
                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 13][parentL13] != NULL){
                                                                                                                edt_13 = register_cmd_recursive(cli, ptrCmdParser, edt_12, (parentIndex + 13), parentL13);

                                                                                                                for(parentL14 = 0; (parentL14 < MAX_CHILD_COMMAND) && (parentIndex + 14) < MAX_PARENT_LEVEL; parentL14++)
                                                                                                                {
                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 14][parentL14] != NULL){
                                                                                                                        edt_14 = register_cmd_recursive(cli, ptrCmdParser, edt_13, (parentIndex + 14), parentL14);

                                                                                                                        for(parentL15 = 0; (parentL15 < MAX_CHILD_COMMAND) && (parentIndex + 15) < MAX_PARENT_LEVEL; parentL15++)
                                                                                                                        {
                                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 15][parentL15] != NULL){
                                                                                                                                edt_15 = register_cmd_recursive(cli, ptrCmdParser, edt_14, (parentIndex + 15), parentL15);

                                                                                                                                for(parentL16 = 0; (parentL16 < MAX_CHILD_COMMAND) && (parentIndex + 16) < MAX_PARENT_LEVEL; parentL16++)
                                                                                                                                {
                                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 16][parentL16] != NULL){
                                                                                                                                        edt_16 = register_cmd_recursive(cli, ptrCmdParser, edt_15, (parentIndex + 16), parentL16);

                                                                                                                                        for(parentL17 = 0; (parentL17 < MAX_CHILD_COMMAND) && (parentIndex + 17) < MAX_PARENT_LEVEL; parentL17++)
                                                                                                                                        {
                                                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 17][parentL17] != NULL){
                                                                                                                                                edt_17 = register_cmd_recursive(cli, ptrCmdParser, edt_16, (parentIndex + 17), parentL17);

                                                                                                                                                for(parentL18 = 0; (parentL18 < MAX_CHILD_COMMAND) && (parentIndex + 18) < MAX_PARENT_LEVEL; parentL18++)
                                                                                                                                                {
                                                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 18][parentL18] != NULL){
                                                                                                                                                        edt_18 = register_cmd_recursive(cli, ptrCmdParser, edt_17, (parentIndex + 18), parentL18);

                                                                                                                                                        for(parentL19 = 0; (parentL19 < MAX_CHILD_COMMAND) && (parentIndex + 19) < MAX_PARENT_LEVEL; parentL19++)
                                                                                                                                                        {
                                                                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 19][parentL19] != NULL){
                                                                                                                                                                edt_19 = register_cmd_recursive(cli, ptrCmdParser, edt_18, (parentIndex + 19), parentL19);

                                                                                                                                                                for(parentL20 = 0; (parentL20 < MAX_CHILD_COMMAND) && (parentIndex + 20) < MAX_PARENT_LEVEL; parentL20++)
                                                                                                                                                                {
                                                                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 20][parentL20] != NULL){
                                                                                                                                                                        edt_20 = register_cmd_recursive(cli, ptrCmdParser, edt_19, (parentIndex + 20), parentL20);

                                                                                                                                                                        for(parentL21 = 0; (parentL21 < MAX_CHILD_COMMAND) && (parentIndex + 21) < MAX_PARENT_LEVEL; parentL21++)
                                                                                                                                                                        {
                                                                                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 21][parentL21] != NULL){
                                                                                                                                                                                edt_21 = register_cmd_recursive(cli, ptrCmdParser, edt_20, (parentIndex + 21), parentL21);

                                                                                                                                                                                for(parentL22 = 0; (parentL22 < MAX_CHILD_COMMAND) && (parentIndex + 22) < MAX_PARENT_LEVEL; parentL22++)
                                                                                                                                                                                {
                                                                                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 22][parentL22] != NULL){
                                                                                                                                                                                        edt_22 = register_cmd_recursive(cli, ptrCmdParser, edt_21, (parentIndex + 22), parentL22);

                                                                                                                                                                                        for(parentL23 = 0; (parentL23 < MAX_CHILD_COMMAND) && (parentIndex + 23) < MAX_PARENT_LEVEL; parentL23++)
                                                                                                                                                                                        {
                                                                                                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 23][parentL23] != NULL){
                                                                                                                                                                                                edt_23 = register_cmd_recursive(cli, ptrCmdParser, edt_22, (parentIndex + 23), parentL23);

                                                                                                                                                                                                for(parentL24 = 0; (parentL24 < MAX_CHILD_COMMAND) && (parentIndex + 24) < MAX_PARENT_LEVEL; parentL24++)
                                                                                                                                                                                                {
                                                                                                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 24][parentL24] != NULL){
                                                                                                                                                                                                        edt_24 = register_cmd_recursive(cli, ptrCmdParser, edt_23, (parentIndex + 24), parentL24);

                                                                                                                                                                                                        for(parentL25 = 0; (parentL25 < MAX_CHILD_COMMAND) && (parentIndex + 25) < MAX_PARENT_LEVEL; parentL25++)
                                                                                                                                                                                                        {
                                                                                                                                                                                                            if(ptrCmdParser->chldCommands[parentIndex + 25][parentL25] != NULL){
                                                                                                                                                                                                                edt_25 = register_cmd_recursive(cli, ptrCmdParser, edt_24, (parentIndex + 25), parentL25);

                                                                                                                                                                                                                for(parentL26 = 0; (parentL26 < MAX_CHILD_COMMAND) && (parentIndex + 26) < MAX_PARENT_LEVEL; parentL26++)
                                                                                                                                                                                                                {
                                                                                                                                                                                                                    if(ptrCmdParser->chldCommands[parentIndex + 26][parentL26] != NULL)
                                                                                                                                                                                                                        edt_26 = register_cmd_recursive(cli, ptrCmdParser, edt_25, (parentIndex + 26), parentL26);

                                                                                                                                                                                                                    else
                                                                                                                                                                                                                        break;
                                                                                                                                                                                                                }
                                                                                                                                                                                                            }
                                                                                                                                                                                                            else
                                                                                                                                                                                                                break;
                                                                                                                                                                                                        }
                                                                                                                                                                                                    }
                                                                                                                                                                                                    else
                                                                                                                                                                                                        break;

                                                                                                                                                                                                }
                                                                                                                                                                                            }
                                                                                                                                                                                            else
                                                                                                                                                                                                break;
                                                                                                                                                                                        }
                                                                                                                                                                                    }
                                                                                                                                                                                    else
                                                                                                                                                                                        break;
                                                                                                                                                                                }
                                                                                                                                                                            }
                                                                                                                                                                            else
                                                                                                                                                                                break;
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                    else
                                                                                                                                                                        break;
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                            else
                                                                                                                                                                break;
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                    else
                                                                                                                                                        break;
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            else
                                                                                                                                                break;
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    else
                                                                                                                                        break;
                                                                                                                                }
                                                                                                                            }
                                                                                                                            else
                                                                                                                                break;
                                                                                                                        }
                                                                                                                    }
                                                                                                                    else
                                                                                                                        break;
                                                                                                                }
                                                                                                            }
                                                                                                            else
                                                                                                                break;
                                                                                                        }
                                                                                                    }
                                                                                                    else
                                                                                                        break;

                                                                                                }
                                                                                            }
                                                                                            else
                                                                                                break;
                                                                                        }
                                                                                    }
                                                                                    else
                                                                                        break;
                                                                                }
                                                                            }
                                                                            else
                                                                                break;

                                                                        }
                                                                    }
                                                                    else
                                                                        break;
                                                                }
                                                            }   
                                                            else
                                                                break;
                                                        }
                                                    }
                                                    else
                                                        break;
                                                }
                                            }
                                            else
                                                break;
                                        }
                                    }
                                    else
                                        break;
                                }
                            }
                            else
                                break;
                        }
                    }
                    else
                        break;
                }
            }
            else
                break;
        }
    }


    return SUCCESS;

}


/*******************************************************************************************



 *********************************************************************************************/
static struct cli_command * register_cmd_recursive(struct cli_def *cli, Parser *ptrCmdParser, struct cli_command *c, int parentLevel, int childStart)
{
    struct cli_command *edt;

    if(parentLevel >= MAX_PARENT_LEVEL)
        return c;

    if(childStart >= MAX_CHILD_COMMAND )
        return c;



    edt = cli_register_command(cli, c, ptrCmdParser->chldCommands[parentLevel][childStart],
            ptrCmdParser->callback, ptrCmdParser->privilege, MODE_ANY,
            ptrCmdParser->helpStrings[(parentLevel * MAX_CHILD_COMMAND) + childStart]);

    edt->optionalFlag = ptrCmdParser->optionalFlag[(parentLevel * MAX_CHILD_COMMAND) + childStart];
    edt->cmdId = ptrCmdParser->Cmd_Id;
    /* Register range related parameters */
    if(ptrCmdParser->rangeString[parentLevel][childStart] != NULL)
    {
        edt->range_string = strdup(ptrCmdParser->rangeString[parentLevel][childStart]);
        edt->range_help = strdup(ptrCmdParser->range_help[(parentLevel * MAX_CHILD_COMMAND) + childStart]);
        edt->range[0][0] = ptrCmdParser->lower_limit[parentLevel][childStart];
        edt->range[0][1] = ptrCmdParser->upper_limit[parentLevel][childStart];
    }

    return edt;
}

/*******************************************************************************************



 *********************************************************************************************/
void cli_install(struct cli_def *cli, int mode, int prev, int cmd_enumId)
{
    struct cli_command *c;
    do{
        cli->searchCmd = NULL;
        search_cmd_onId(cli, cli->commands, cmd_enumId);
        c = cli->searchCmd;

        if(c)
        {
            c->privilege = prev;
            c->mode = mode;
        }
    }while(c);
}
