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


#include <CMgrIwfDbInterface.h>

using namespace std;

void IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Create_Check_Modifcation_Query(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select IWF_SIGTRAN_DESTINATION_ID from IWF_SIGTRAN_DESTINATION_TB where DEST_NAME = '%s'",IwfSigtranDestinationConfigReq->destinationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Create_Add_Query(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq,char *pStatement)
{
    char sFieldName[MAX_STATEMENT_SIZE]  = {0};
    char sFieldValue[MAX_STATEMENT_SIZE] = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into IWF_SIGTRAN_DESTINATION_TB"); 
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(DEST_NAME");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"('%s'",IwfSigtranDestinationConfigReq->destinationname().c_str());

    if(IwfSigtranDestinationConfigReq->has_protocolfamily())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",IWF_PROTOCOL_FAMILY_ID");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",(select IWF_PROTOCOL_FAMILY_ID from IWF_PROTOCOL_FAMILY_TB where FAMILY_NAME = '%s')",IwfSigtranDestinationConfigReq -> protocolfamily().c_str());
    }

    if(IwfSigtranDestinationConfigReq->has_addressstyle())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ADDRESS_STYLE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranDestinationConfigReq -> addressstyle().c_str());
    }

    if(IwfSigtranDestinationConfigReq->has_addresstype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ADDRESS_TYPE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranDestinationConfigReq -> addresstype().c_str());
    }

    if(IwfSigtranDestinationConfigReq->has_pointcode())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",POINTCODE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq->pointcode());
    }

    if(IwfSigtranDestinationConfigReq->has_networkindicator())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NI");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> networkindicator());
    }

    if(IwfSigtranDestinationConfigReq->has_ssn())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SSN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> ssn());
    }

    if(IwfSigtranDestinationConfigReq->has_gti())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",GTI");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> gti());
    }

    if(IwfSigtranDestinationConfigReq->has_translationtype())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",TRANSLATION_TYPE");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> translationtype());
    }

    if(IwfSigtranDestinationConfigReq->has_numberingplan())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NUMBERING_PLAN");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> numberingplan());
    }

    if(IwfSigtranDestinationConfigReq->has_encodingscheme())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",ENCODING_SCHEME");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> encodingscheme());
    }

    if(IwfSigtranDestinationConfigReq->has_natureofaddrind())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",NATURE_OF_ADDRESS_INDICATOR");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> natureofaddrind());
    }

    if(IwfSigtranDestinationConfigReq->has_sio())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",SIO");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",%d",IwfSigtranDestinationConfigReq -> sio());
    }

    if(IwfSigtranDestinationConfigReq->has_gtaddrdigits())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,",GT_ADDR_DIGITS");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,",'%s'",IwfSigtranDestinationConfigReq -> gtaddrdigits().c_str());
    }

    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Create_Mod_Query(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update IWF_SIGTRAN_DESTINATION_TB set "); 

    if(IwfSigtranDestinationConfigReq -> has_protocolfamily())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"IWF_PROTOCOL_FAMILY_ID = (select IWF_PROTOCOL_FAMILY_ID from IWF_PROTOCOL_FAMILY_TB where FAMILY_NAME = '%s'),",IwfSigtranDestinationConfigReq->protocolfamily().c_str());
    }
#if 1
    if(IwfSigtranDestinationConfigReq-> has_addressstyle())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ADDRESS_STYLE= '%s',",IwfSigtranDestinationConfigReq -> addressstyle().c_str());
    }
#endif
    if(IwfSigtranDestinationConfigReq-> has_addresstype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ADDRESS_TYPE= '%s',",IwfSigtranDestinationConfigReq -> addresstype().c_str());
    }

    if(IwfSigtranDestinationConfigReq -> has_pointcode())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"POINTCODE= %d,",IwfSigtranDestinationConfigReq -> pointcode());
    }

    if(IwfSigtranDestinationConfigReq -> has_networkindicator())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NI= %d,",IwfSigtranDestinationConfigReq -> networkindicator());
    }

    if(IwfSigtranDestinationConfigReq -> has_ssn())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SSN= %d,",IwfSigtranDestinationConfigReq -> ssn());
    }

    if(IwfSigtranDestinationConfigReq -> has_gti())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"GTI= %d,",IwfSigtranDestinationConfigReq -> gti());
    }

    if(IwfSigtranDestinationConfigReq -> has_translationtype())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TRANSLATION_TYPE= %d,",IwfSigtranDestinationConfigReq -> translationtype());
    }

    if(IwfSigtranDestinationConfigReq -> has_numberingplan())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NUMBERING_PLAN= %d,",IwfSigtranDestinationConfigReq -> numberingplan());
    }
    
    if(IwfSigtranDestinationConfigReq -> has_encodingscheme())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ENCODING_SCHEME= %d,",IwfSigtranDestinationConfigReq -> encodingscheme());
    }

    if(IwfSigtranDestinationConfigReq -> has_natureofaddrind())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NATURE_OF_ADDRESS_INDICATOR= %d,",IwfSigtranDestinationConfigReq -> natureofaddrind());
    }

    if(IwfSigtranDestinationConfigReq -> has_sio())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"SIO= %d,",IwfSigtranDestinationConfigReq -> sio());
    }

    if(IwfSigtranDestinationConfigReq -> has_gtaddrdigits())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"GT_ADDR_DIGITS= '%s',",IwfSigtranDestinationConfigReq -> gtaddrdigits().c_str());
    }

    pStatement[strlen(pStatement) -1] = ' ';
    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where DEST_NAME='%s' ",IwfSigtranDestinationConfigReq -> destinationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

void IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Create_Delete_Query(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq,char *pStatement)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from IWF_SIGTRAN_DESTINATION_TB where DEST_NAME='%s'",IwfSigtranDestinationConfigReq -> destinationname().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Payload_Validation(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(!IwfSigtranDestinationConfigReq->has_destinationname())
    {
        DLOG_ERROR("Primary Key destination_name is not set in the request");
        return IWF_DB_FAIL;
    }

    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}


void IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Create_Select_Query(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq,char *pStatement)
{
    int iFlag = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from IWF_SIGTRAN_DESTINATION_TB "); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(IwfSigtranDestinationConfigReq-> has_destinationid())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_SIGTRAN_DESTINATION_ID= %d and ",IwfSigtranDestinationConfigReq -> destinationid());
    }

    if(IwfSigtranDestinationConfigReq-> has_destinationname())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"DEST_NAME= '%s' and ",IwfSigtranDestinationConfigReq -> destinationname().c_str());
    }

    if(IwfSigtranDestinationConfigReq -> has_protocolfamily())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"IWF_PROTOCOL_FAMILY_ID = (select IWF_PROTOCOL_FAMILY_ID from IWF_PROTOCOL_FAMILY_TB where FAMILY_NAME = '%s') and ",IwfSigtranDestinationConfigReq->protocolfamily().c_str());
    }
#if 1
    if(IwfSigtranDestinationConfigReq-> has_addressstyle())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ADDRESS_STYLE= '%s' and ",IwfSigtranDestinationConfigReq -> addressstyle().c_str());
    }
#endif
    if(IwfSigtranDestinationConfigReq-> has_addresstype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ADDRESS_TYPE= '%s' and ",IwfSigtranDestinationConfigReq -> addresstype().c_str());
    }

    if(IwfSigtranDestinationConfigReq -> has_pointcode())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"POINTCODE= %d and ",IwfSigtranDestinationConfigReq -> pointcode());
    }

    if(IwfSigtranDestinationConfigReq -> has_networkindicator())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NI= %d and ",IwfSigtranDestinationConfigReq -> networkindicator());
    }

    if(IwfSigtranDestinationConfigReq -> has_ssn())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SSN= %d and ",IwfSigtranDestinationConfigReq -> ssn());
    }

    if(IwfSigtranDestinationConfigReq -> has_gti())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"GTI= %d and ",IwfSigtranDestinationConfigReq -> gti());
    }

    if(IwfSigtranDestinationConfigReq -> has_translationtype())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TRANSLATION_TYPE= %d and ",IwfSigtranDestinationConfigReq -> translationtype());
    }

    if(IwfSigtranDestinationConfigReq -> has_numberingplan())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NUMBERING_PLAN= %d and ",IwfSigtranDestinationConfigReq -> numberingplan());
    }

    if(IwfSigtranDestinationConfigReq -> has_encodingscheme())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ENCODING_SCHEME= %d and ",IwfSigtranDestinationConfigReq -> encodingscheme());
    }

    if(IwfSigtranDestinationConfigReq -> has_natureofaddrind())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NATURE_OF_ADDRESS_INDICATOR= %d and ",IwfSigtranDestinationConfigReq -> natureofaddrind());
    }

    if(IwfSigtranDestinationConfigReq -> has_sio())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"SIO= %d and ",IwfSigtranDestinationConfigReq -> sio());
    }

    if(IwfSigtranDestinationConfigReq -> has_gtaddrdigits())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"GT_ADDR_DIGITS= '%s' and ",IwfSigtranDestinationConfigReq -> gtaddrdigits().c_str());
    }

    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }

    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}

DbStatus_e IWFSigtranDestinationTPBQuery::sql_IWFSigtranDestination_Check_All_Invalid(IwfSigtranDestinationConfig *IwfSigtranDestinationConfigReq)
{
    DLOG_NONE(" > %s ",__FUNCTION__,__LINE__);

    if(IwfSigtranDestinationConfigReq -> has_destinationname())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_protocolfamily())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_addressstyle())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_addresstype())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_pointcode())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_networkindicator())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_ssn())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_gti())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_translationtype())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_numberingplan())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_encodingscheme())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_natureofaddrind())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_sio())
    {
        return IWF_DB_FAIL;
    }
    if(IwfSigtranDestinationConfigReq -> has_gtaddrdigits())
    {
        return IWF_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return IWF_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__,__LINE__);
}
