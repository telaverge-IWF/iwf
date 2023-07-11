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
#include<stdarg.h>
#include "cmd_utils.h"
#include "LibCli.h"
#include "CliParser.h"
#include "CliRegister.h"
#include "CliCallback.h"
#include <stdint.h>


/* Local Function Declarations */
static unsigned char cmd_stringParser(const char *buf, char *opString, unsigned char parseLevel);
static int parse_range(char *bufPtr, Parser **parserPtr, uint8_t rangeIndex);
static int cmd_parser(Parser *ptrToParser,const char *cmd_str, va_list vp);
static void free_cmdParser(Parser *cmdParser);

// Child level Indicater
static unsigned char cmdLevelIndex = 0;
// parameter count indicater for each child level 
static unsigned char argLevel = 0;



/*********************************************************************************************
 * FUNCTION NAME    : AddCLI
 * DESCRIPTION      : This is the api to other modules to add a new command. Function generates
 *          the command parameter as tokens in the parsing structure and calls registration
 *          function to generate a cli tree out of these tokans
 *
 * SIDE EFFECTS     : Adds a command into cli tree
 *********************************************************************************************/

int Add_CLI(struct cli_def *cli, int (*funCalllback)(struct cli_def *, char *commad, char **argv, int), 
        unsigned int interfaceId, unsigned int methodId, unsigned short Cli_Id, char const* cmd_str, ...)
{
    Parser cmdParser;
    char buff[120] = {0};
    unsigned short argCount = 0;        
    va_list argList;

    cmdLevelIndex = 0;
    argLevel = 0;
    // Tokans storing structure 
    memset((char *)&cmdParser,0, sizeof(Parser));
    memset((char *)&buff[0], 0, 120);

    // Help Strings 
    va_start(argList, cmd_str);

    cmdParser.callback = funCalllback;
    cmdParser.Cmd_Id = Cli_Id; 

    //Parse the command string into tokans and match its help strings
    argCount = cmd_parser(&cmdParser, cmd_str, argList);
    cmdParser.noOfArgs = argCount;


    va_end(argList);

    //Insert the command into cli tree
    register_user_commands(cli, &cmdParser);

    /* Free the memory allocated for the parser structure */
    free_cmdParser(&cmdParser);

    return 0;
}


/*********************************************************************************************



 *********************************************************************************************/

static int cmd_parser(Parser *cmdParser, const char *cmd_str, va_list vp)
{
    char buff[120] = {0};
    char *tmpPtr = NULL;
    unsigned char retVal;
    unsigned short argCount = 0;        
    unsigned char optionFlag = false;

    memset((char *)&buff[0], 0, 120);

    if(!(cmdParser->fullCmdString = strdup(cmd_str)))
        return FAILURE;

    //Send third parameter as 1 for the first call from AddCLI
    //buff carries the next token in the command string
    retVal = cmd_stringParser(cmd_str,&buff[0],1);

    if(!(cmdParser->command = strdup(buff)))
        return FAILURE;

    //tokans are stored in two dimentional array to indicate child or options to the same child
    if(!(cmdParser->chldCommands[cmdLevelIndex][argLevel] = strdup(buff)))
        return FAILURE;

    //Help strings
    tmpPtr = va_arg(vp, char *);


    if(!(cmdParser->helpStrings[(cmdLevelIndex * MAX_CHILD_COMMAND) + argLevel] = strdup(tmpPtr)))
        return FAILURE;

    argCount++;

    //If more than one word is present in the command string enter this block
    if(CMD_WITH_ARGS == retVal){
        /* Parse till end of the full command string and all help strings */
        for( ; *buff != '\0'; )
        {
            //Read next token string, send third parameter as 2 for the subsequent calls
            //buff carries the next token in the command string
            retVal = cmd_stringParser(cmd_str,&buff[0],2);
            if(retVal == CMD_NO_ARGS)
                continue;

            //Handling optional parameters
            else if(retVal == CMD_OPTIONAL){
                optionFlag = true;
                continue;
            }

            //Help strings
            tmpPtr = va_arg(vp, char *);

            //It is a command parameter
            if(CMD_CHILD == retVal){

                if(!(cmdParser->chldCommands[cmdLevelIndex][argLevel] = strdup(buff)))
                    return FAILURE;

                if(!(cmdParser->helpStrings[(cmdLevelIndex * MAX_CHILD_COMMAND) + argLevel] = strdup(tmpPtr)))
                    return FAILURE;

                cmdParser->optionalFlag[(cmdLevelIndex * MAX_CHILD_COMMAND) + argLevel] = optionFlag; 

                //Optional parameter
                if(optionFlag == true){
                    optionFlag = false;
                    argLevel = 0;
                    cmdLevelIndex++;
                }else {
                    argLevel++;
                }
                argCount++;
            }
            //This is a range token
            else if(CMD_RANGE == retVal){

                parse_range(buff, &cmdParser, argLevel);
                if(!(cmdParser->range_help[(cmdLevelIndex * MAX_CHILD_COMMAND) + argLevel] = strdup(tmpPtr)))
                    return FAILURE;

                if(!(cmdParser->helpStrings[(cmdLevelIndex * MAX_CHILD_COMMAND) + argLevel] = strdup(tmpPtr)))
                    return FAILURE;

                argLevel++;
                argCount++;
            }
        }
    }
    else{
    }
    //argCount is not used
    return argCount;
}


/*********************************************************************************************



 *********************************************************************************************/

static int parse_range(char *bufPtr, Parser **parserPtr, uint8_t rangeIndex)
{
    char localBuf[20] = {0};
    uint8_t index = 0;
    uint8_t c;
    long long Val;


    /* Copy the range values in string for the display purpose */ 
    for(; bufPtr[index] != '\0'; ++index)
    {
        localBuf[index] = bufPtr[index];
    }

    if(!((*parserPtr)->rangeString[cmdLevelIndex][rangeIndex] = strdup(bufPtr)))
        return FAILURE;

    //The range string, in the format of "<0-...>" is also made as a command parameter 
    if(!((*parserPtr)->chldCommands[cmdLevelIndex][rangeIndex] = strdup(bufPtr)))
        return FAILURE;

    index = 0;  
    for(c = 0; c < 2; c++)
    {
        while((*bufPtr != '-') && *bufPtr != '\0')
        {
            if(*bufPtr == ' ')
            {
                bufPtr++;
                continue;
            }
            localBuf[index++] = *bufPtr++;
        }
        localBuf[index++] = '\0';

        Val = atoll(&localBuf[0]);
        if(c == 0)
            (*parserPtr)->lower_limit[cmdLevelIndex][rangeIndex] = Val;
        //Upper limit value
        else
            (*parserPtr)->upper_limit[cmdLevelIndex][rangeIndex] = Val;

        if(*bufPtr == '-')
        {
            bufPtr++;
            index = 0;
        }

    }

    return SUCCESS;
}


/*********************************************************************************************



 *********************************************************************************************/

unsigned char cmd_stringParser(const char *buf, char *opString, unsigned char parseLevel)
{


    static char* trackPtr = NULL;
    char string[80] = {0};
    unsigned char loopIndex = 0;
    unsigned char buffIndex = 0;
    unsigned char retVal = 0;
    static unsigned char childFlag;
    static unsigned char bracketOpen;
    static unsigned char optionFlag;


    switch(parseLevel)
    {
        case 1:
            childFlag = TRUE;
            cmdLevelIndex = 0;
            bracketOpen = false;
            optionFlag - false;

            //Discard leading white spaces
            while(buf[loopIndex] == ' ') loopIndex++;

            //Copy the word
            for(; buf[loopIndex] != '\0'; loopIndex++){

                if((buf[loopIndex] == ' ') || (buf[loopIndex] == '(') || (buf[loopIndex] == '<'))
                    break;
                string[buffIndex++] = buf[loopIndex];
            }

            string[buffIndex] = '\0';
            //Next command token
            strcpy(opString, string);
            //Pointer is pointing to the next character after the extracted token
            trackPtr = (char *) &buf[loopIndex];

            //One word command, (No second parameter for this command)
            if(buf[loopIndex] == '\0')
                return CMD_NO_ARGS;
            //Command has next orguments    
            return CMD_WITH_ARGS;
            break;

        case 2:
            //Discard leading white spaces
            while(*trackPtr == ' ') trackPtr++;

            //Copy the word
            for(; trackPtr[loopIndex] != '\0'; loopIndex++){

                if((trackPtr[loopIndex] == ' ') || (trackPtr[loopIndex] == '(') || 
                        (trackPtr[loopIndex] == ')') || (trackPtr[loopIndex] == '|'))
                    break;
                string[buffIndex++] = trackPtr[loopIndex];
            }

            //Command End
            if((trackPtr[loopIndex] == '\0') && (buffIndex == 0))
            {
                opString[buffIndex] = '\0';
                return CMD_END;
            }
            //Pointer is pointing to the next character after the extracted token
            trackPtr = trackPtr + loopIndex;
            //Increment the childlevel count
            if((buffIndex != 0) && (childFlag == TRUE)){
                cmdLevelIndex++;
                argLevel = 0;
            }
            //Command Options
            if(*trackPtr == '('){
                childFlag = FALSE;
                cmdLevelIndex++;
                argLevel = 0;
                bracketOpen = true;
            }
            //Command options end   
            else if((*trackPtr == ')') && (buffIndex == 0)){
                childFlag = TRUE;
                bracketOpen = false;
                optionFlag = false;
            }
            if((buffIndex == 0)){
                //This parameter is Optional
                if((bracketOpen == true) && (*trackPtr == '|')){

                    trackPtr++;
                    optionFlag = true;
                    return CMD_OPTIONAL;
                }else if(loopIndex == 0)
                    trackPtr++;

                if(*trackPtr == '\0'){
                    opString[0] = '\0';
                    return CMD_END;
                }
                return CMD_NO_ARGS;
            }

            bracketOpen = false;
            string[buffIndex] = '\0';
            //Output: command token
            strcpy(opString, string);

            //It is a range
            if(opString[0] == '<')
                return CMD_RANGE;

            return CMD_CHILD;
            //          return retVal;

            break;
    }
    return retVal;
}


/*********************************************************************************************



 *********************************************************************************************/

static void free_cmdParser(Parser *cmdParser)
{

    unsigned char i, j;

    /* Free all the allocated memories for the parser structure */
    free_z(cmdParser->command);
    free_z(cmdParser->fullCmdString);

    for(i = 0; i < MAX_PARENT_LEVEL; i++)
        for(j = 0; j < MAX_CHILD_COMMAND; j++)
        {
            free_z(cmdParser->chldCommands[i][j]);
            free_z(cmdParser->rangeString[i][j]);
            free_z(cmdParser->helpStrings[(i * MAX_CHILD_COMMAND) + j]);
            free_z(cmdParser->range_help[(i * MAX_CHILD_COMMAND) + j]);
        }   

}
