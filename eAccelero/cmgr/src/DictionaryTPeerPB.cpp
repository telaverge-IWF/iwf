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


#include <CMgrDbInterface.h>

using namespace std;

#if 0
void DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Create_Check_Modifcation_Query(PeerConfig *DictionaryPeerConfigReq,char *pStatement,int iIndex)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from DICTIONARY_TB");
}

void DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Create_Add_Query(PeerConfig *DictionaryPeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}


void DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Create_Mod_Query(PeerConfig *DictionaryPeerConfigReq,char *pStatement,int iIndex)
{

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

void DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Create_Delete_Query(PeerConfig *DictionaryPeerConfigReq,char *pStatement,int iIndex)
{
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
}

DbStatus_e DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Payload_Validation(PeerConfig *DictionaryPeerConfigReq,int iIndex)
{

    DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);
    return DRE_DB_SUCCESS;
}


DbStatus_e DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Check_All_Invalid(PeerConfig *DictionaryPeerConfigReq,int iIndex)
{
    return DRE_DB_SUCCESS;
}

#endif

void DictionaryTPeerPBQuery::sql_DictionaryPeerConfig_Create_Select_Query(PeerConfig *DictionaryPeerConfigReq,char *pStatement,int iIndex)
{
#if 0
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};
#endif

    string sDictionaryName;
    DLOG_NONE("> %s",__FUNCTION__);
    DLOG_DEBUG("DictionaryPeerConfigReq->dictionaryname_size() = %d, iIndex= %d",DictionaryPeerConfigReq->dictionaryname_size(),iIndex);    
    if(DictionaryPeerConfigReq->dictionaryname_size() > iIndex && iIndex > -1)
    {
        sDictionaryName = DictionaryPeerConfigReq->dictionaryname(iIndex);
    }
    else
    {
        DLOG_WARNING("DictionaryName  Object will be NULL, DictionaryPeerConfigReq->dictionaryname_size() = %d, iIndex= %d",DictionaryPeerConfigReq->dictionaryname_size(),iIndex);    
	    DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select DICTIONARY_ID,APP_TYPE from  DICTIONARY_TB where DICTIONARY_NAME= '%s'",sDictionaryName.c_str()); 
    DLOG_NONE("< %s",__FUNCTION__);
}



