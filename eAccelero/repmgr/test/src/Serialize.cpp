/*********************************-*-H-*-************************************
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

#include "Serialize.h"
#include "Logger.h"


/*Serialize method is used to serialize the Non-POD data structures used by the application
 * It basically converts to a basic string with fields seperated by DELIMETER*
 * Serialize is specific to a structure, If we want to add new structure we need to add a 
 * case to serialize*/
int32_t Serialize::serialize(STRUCT_TYPE strType, void *outData, void *inData)
{

    char tempBuf[10]={'\0'};
    char *out=(char*)outData;
    switch(strType)
    {
	case ERLBF_SESS_INFO:
		/*serialize the SessionInfo structure*/
		strncpy(out,((SessionInfo*)inData)->serverName.c_str(),SERIALIZE_BUF_MAX);

		strcat(out,DELIMITER);

		sprintf(tempBuf,"%u",((SessionInfo*)inData)->counter);
		strcat(out,tempBuf);
		strcat(out,DELIMITER);
		
		sprintf(tempBuf,"%u",((SessionInfo*)inData)->sessionTerminateTimerId);
		strcat(out,tempBuf);
		strcat(out,DELIMITER);


		strcat(out,((((SessionInfo*)inData)->gxSessionFlag) == 1)?"1":"0");	
		strcat(out,DELIMITER);
	
		strcat(out,((((SessionInfo*)inData)->gxxSessionFlag) == 1)?"1":"0");	
		strcat(out,DELIMITER);

		strcat(out,((((SessionInfo*)inData)->rxSessionFlag) == 1)?"1":"0");	
		strcat(out,DELIMITER);

		strcat(out,((((SessionInfo*)inData)->s9SessionFlag) == 1)?"1":"0");	
		strcat(out,DELIMITER);

	//	DLOG_DEBUG("Serialized data: %s",(char*)outData);
		break;

	case ERLBF_SESS_BIND_KEY:
		//serialize the SessionBindingKey structure
		strncpy(out,((((SessionBindingKey*)inData)->isIPv4Address) == 1)?"1":"0",SERIALIZE_BUF_MAX);
		strcat(out,DELIMITER);

		strcat(out,((SessionBindingKey*)inData)->key.c_str());
		strcat(out, DELIMITER);	

		break;

	case ASF:
		break;
	
	case STACK_SESSION_ENTRY:
		break;
	/*Add cases if new structures are to be serialized*/
    }

    
    return 0;
}


/*deserialize method is used to deserialize the data which was serialized with the serialize method
 * This is  specific to a structure type, if new structure to be added a case has to be added */
int32_t Serialize::deserialize(STRUCT_TYPE strType, void *outData,void *inData)
{

    char *in=(char*)inData;
    char *token=NULL;
    switch(strType)
    {
	case ERLBF_SESS_INFO:
        {
		SessionInfo *out=(SessionInfo*)outData;
		/*deserialize the SessionInfo Structure*/
		token=strtok(in,DELIMITER);
		if( token != NULL )
		{
		    out->serverName=token;
		    token=strtok(NULL,DELIMITER);
		}

		if( token != NULL )
	   	{
		    out->counter=(uint32_t)atoi(token);
		    token=strtok(NULL,DELIMITER);
		}

		if( token != NULL)
		{
		    out->sessionTerminateTimerId=(uint32_t)atoi(token);
		    token=strtok(NULL,DELIMITER);
		}

		if( token != NULL)
		{
		    out->gxSessionFlag=atoi(token);
		    token=strtok(NULL,DELIMITER);
		}

		if( token != NULL)
		{
		    out->gxxSessionFlag=atoi(token);
		    token=strtok(NULL,DELIMITER);
		}

		if( token != NULL)
		{
		    out->rxSessionFlag=atoi(token);
		    token=strtok(NULL,DELIMITER);
		}


		if( token != NULL)
		{
		    out->s9SessionFlag=atoi(token);
		    token=strtok(NULL,DELIMITER);
		}

		break;
	}
	case ERLBF_SESS_BIND_KEY:
	{
		SessionBindingKey *out=(SessionBindingKey*)outData;	
		/*deserialize the SessionBindingKey Structure*/
		token=strtok(in,DELIMITER);
		if( token != NULL )
		{
		    out->isIPv4Address=(atoi(token) == 1)?true:false;
		    token=strtok(NULL,DELIMITER);
		}

		if( token != NULL )
		{
		    out->key=token;
		}

		break;
	}
	case ASF:
		break;

	case STACK_SESSION_ENTRY:
		break;
	/*add cases to deserialize new structures*/
    }

    return 0;
}


