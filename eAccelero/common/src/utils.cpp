/*********************************-*-CPP-*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************/
#include <string>
#include <iostream>
#include "Common.pb.h"
#include "CommonStructure.h"
#include "utils.h"
#include "ConfigReader.h"


using namespace std;

map<string,string> errorMsgMap;

void fillParamsInMsg(ErrorDetails& err,string* errMsg)
{
    string temp;
    int index = 0;
    size_t found;
    int pos = 0;
    for(;index < err.variables_size() ; index ++)
    {
        found = errMsg->find_first_of("{");       
        if(found ==string::npos)
        {
            //Couldn't find any more vars to replace.
            break;
        }
        //TODO: For now only single digit variable indexes are suported.
        pos = atoi(&(*errMsg)[found+1]);
        if(pos < err.variables_size())
        {
            errMsg->replace(found,3,err.variables(pos).c_str(),err.variables(pos).length());
        }
        else
        {
            //If variable is not passed from backend then replace with blank string.
            string dummy("");
            errMsg->replace(found,3,dummy.c_str(),dummy.length());
        }
    }
}

void formErrorMessage(ErrorDetails& err,AllResponses* resp)
{
    string errorMsg;
    if(err.has_errormsgkey())
    {
        errorMsg = errorMsgMap[err.errormsgkey()];
    }
    else
    {
        //Key is not returned from Backend. Showing Default Error Msg.
        errorMsg = "";
    }

    //Fill in the params from the ErrorResp into the Error Message.
    fillParamsInMsg(err,&errorMsg);

    //Copy the error msg into the resp structure.
    strncpy(resp->payload,errorMsg.c_str(),MAX_PAYLOAD_LEN - 1);
}


int populateErrorMap(string resourceFile)
{
    bool isSuccess = false;
    ConfigReader cfgReader(resourceFile.c_str(),isSuccess);
    if(isSuccess)
    {
        errorMsgMap = cfgReader.getConfigMap(); 
    }
    else
    {
        perror("Failed to open Resources File");
        return -1;
    }
    return 0;
}

