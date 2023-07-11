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


#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

//#include "libcli.h"
//#include "cli_api.h"



#define SUCCESS     0
#define FAILURE     -1

#define CMD_NO_ARGS     0x00
#define CMD_WITH_ARGS   0x01
#define CMD_CHILD   0x02
#define CMD_RANGE   0x03
#define CMD_END     0x04
#define CMD_OPTIONAL  0x05

#define MAX_CHILD_COMMAND   10
#define MAX_PARENT_LEVEL        30  
#define USER_INPUT_IND      "WORD"

typedef struct _t_parser
{
    char *command;
    char *fullCmdString;
    int (*callback)(struct cli_def *, char *, char **, int);
    int privilege;
    unsigned int Cmd_Id;
    int mode;
    int noOfArgs;
    char *chldCommands[MAX_PARENT_LEVEL][MAX_CHILD_COMMAND];
    long long lower_limit[MAX_PARENT_LEVEL][MAX_CHILD_COMMAND];
    long long upper_limit[MAX_PARENT_LEVEL][MAX_CHILD_COMMAND];
    int optionalFlag[MAX_PARENT_LEVEL * MAX_CHILD_COMMAND];
    char *rangeString[MAX_PARENT_LEVEL][MAX_CHILD_COMMAND];
    char *helpStrings[MAX_PARENT_LEVEL * MAX_CHILD_COMMAND];
    char *range_help[MAX_PARENT_LEVEL * MAX_CHILD_COMMAND];
}Parser;


#endif

