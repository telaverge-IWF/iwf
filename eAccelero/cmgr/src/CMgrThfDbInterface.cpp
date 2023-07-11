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
#include "ErrorResp.h"

using namespace std;
extern std::map<int,std::string> errorMap;


void CMgrDbInterface::mysql_set_error_for_Thf_Config_Reqs(THFResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Thf_Config_Reqs(::THFVHost *req, THFResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_vhost())
        err->add_variables(req->vhost());

    if(req->has_vrealm())
        err->add_variables(req->vrealm());

    if(iReturn == ADD_THF_VHOST_ERR_MAX_COUNT_REACHED)
    {
        char sStr[10];
        snprintf(sStr,10,"%d",MAX_VHOST_SUPPORTED);
        err->add_variables(sStr);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Thf_Config_Reqs(::THFRealm *req, THFResp *resp,DbStatus_e iReturn, int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_realmname())
        err->add_variables(req->realmname());

    if(iIndex != -1)
    {
        THFAction *localTHFAction = NULL;
        localTHFAction = req->mutable_otherrealm(iIndex);
        if(localTHFAction->has_realmname())
            err->add_variables(localTHFAction->realmname());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Thf_Config_Reqs(THFReq *req, THFResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Thf_Enable_Get_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_Thf_Create_Select_Query(req,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_THF_ERR_DB_ERROR;

        mysql_set_error_for_Thf_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_Thf_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {
        mysql_set_error_for_Thf_Config_Reqs(req,resp,iReturn);
        delete pRes;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;

    }

    delete pRes;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_Realm_Get_Config_Reqs_when_OtherRealm_size_is_zero(THFReq *req,THFResp *resp)
{
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;

	DLOG_NONE(" > %s ",__FUNCTION__);
        int iCount = req->realms_size();
	DLOG_NONE("req->realms_size()=%d",req->realms_size());
	for(int i=0; i<iCount; i++)
	{
		DLOG_NONE("req->realms_size()=%d",req->realms_size());
		::THFRealm* localThfRealm = req->mutable_realms(i);
		sql_THFRealm_Create_Select_Query(localThfRealm,sStatement,-1);
		DLOG_NONE("%s",sStatement);

		if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
		{
			if(pRes != NULL)
			{
				delete pRes;
			}

			DLOG_ERROR("Query Execution Failed: %s",sStatement);

			if(iReturn == DRE_DB_FAIL)
				iReturn = GET_THF_REALM_ERR_DB_ERROR;

			mysql_set_error_for_Thf_Config_Reqs(localThfRealm,resp,iReturn,-1);
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}

		if((iReturn = mysql_THFRealm_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
		{
			mysql_set_error_for_Thf_Config_Reqs(localThfRealm,resp,iReturn,-1);
			delete pRes;
			DLOG_NONE(" < %s ",__FUNCTION__);
			return iReturn;
		}
		delete pRes;
	}
	DLOG_NONE(" < %s ",__FUNCTION__);
	return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_Realm_Get_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = req->realms_size();

    DLOG_DEBUG(" %s: Realm size = %d",__FUNCTION__,iCount);
    for(int i=0; i<iCount; i++)
    {
        ::THFRealm* localThfRealm = req->mutable_realms(i);

        int iOtherRealm = localThfRealm->otherrealm_size();
    	DLOG_NONE("iOtherRealm = %d",iOtherRealm);

        for(int j=0;j<iOtherRealm;j++)
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            pRes = NULL;
            sql_THFRealm_Create_Select_Query(localThfRealm,sStatement,j);
    	    DLOG_NONE("%s",sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(localThfRealm,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_THFRealm_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_Thf_Config_Reqs(localThfRealm,resp,iReturn,j);
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
	    }
	    delete pRes;
	}
	if(iOtherRealm == 0)
	{
		mysql_Thf_Realm_Get_Config_Reqs_when_OtherRealm_size_is_zero(req,resp);
	}
    }

    ::THFRealm lTHFRealm;
    if(iCount == 0)
    {
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pRes = NULL;
        sql_THFRealm_Create_Select_Query(&lTHFRealm,sStatement,-1);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_THF_REALM_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(&lTHFRealm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        // if((iReturn = mysql_THFRealm_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        // {
        //     mysql_set_error_for_Thf_Config_Reqs(&lTHFRealm,resp,iReturn);
        //     delete pRes;
        //     DLOG_NONE(" < %s ",__FUNCTION__);
        //     return iReturn;
        // }
        mysql_THFRealm_resultset_to_protoBuff(pRes,resp);
        delete pRes;
        mysql_Thf_VHost_Get_Config_Reqs(req,resp);
        mysql_Thf_Enable_Get_Config_Reqs(req,resp);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_THFRealm_resultset_to_protoBuff(sql::ResultSet *pRes,THFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_THF_REALM_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
           mysql_check_and_add_THFRealm_resultset(pRes,resp);

        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

void CMgrDbInterface::mysql_check_and_add_THFRealm_resultset(sql::ResultSet *pRes,THFResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iRealmCount = resp->realms_size();
    DLOG_DEBUG(" %s: realms_size = %d ",__FUNCTION__,iRealmCount);

    for(int j=0;j<iRealmCount; j++)
    {
        ::THFRealm* localRealmObj = resp->mutable_realms(j);

        if(localRealmObj->realmname() == pRes->getString("TARGET_REALM"))
        {
            mysql_add_THFRealm_resultset_with_otherrealm(pRes,localRealmObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }

    mysql_add_THFRealm_resultset(pRes,resp);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_add_THFRealm_resultset(sql::ResultSet *pRes,THFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::THFRealm* localRealmObj = resp->add_realms();

    if(!pRes->isNull("TARGET_REALM"))
        localRealmObj->set_realmname(pRes->getString("TARGET_REALM"));

    mysql_add_THFRealm_resultset_with_otherrealm(pRes,localRealmObj);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_add_THFRealm_resultset_with_otherrealm(sql::ResultSet *pRes,::THFRealm *localRealmObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::THFAction* pTHFAction = localRealmObj->add_otherrealm();

    if(!pRes->isNull("OTHER_REALM"))
    {
        pTHFAction->set_realmname(pRes->getString("OTHER_REALM"));
    }

    if(!pRes->isNull("ACTION"))
    {
        if(pRes->getString("ACTION") == "expose-to")
        {
            pTHFAction->set_action(THFAction_Action_ExposeTo);
        }
        else if(pRes->getString("ACTION") == "hide-from")
        {
            pTHFAction->set_action(THFAction_Action_HideFrom);
        }
    }

    if(!pRes->isNull("EXPOSED_AVP"))
    {
        pTHFAction->set_exposedavps(pRes->getInt64("EXPOSED_AVP"));
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Thf_VHost_Get_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = req->vhosts_size();
    DLOG_DEBUG(" %s: Host size = %d",__FUNCTION__,iCount);
    for(int i=0; i<iCount; i++)
    {
        THFVHost *localThfVHost = req->mutable_vhosts(i);
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        pRes = NULL;

        sql_THFHosts_Create_Select_Query(localThfVHost,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_THF_VHOST_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(localThfVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_THFVHost_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Thf_Config_Reqs(localThfVHost,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }
    delete pRes;

    ::THFVHost lTHFVHost;
    if(iCount == 0)
    {
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        pRes = NULL;

        sql_THFHosts_Create_Select_Query(&lTHFVHost,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_THF_VHOST_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(&lTHFVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_THFVHost_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Thf_Config_Reqs(&lTHFVHost,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_THFVHost_resultset_to_protoBuff(sql::ResultSet *pRes,THFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_THF_VHOST_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            ::THFVHost *pTHFVHost = resp->add_vhosts();
            if(!pRes->isNull("VHOST"))
            {
                pTHFVHost->set_vhost(pRes->getString("VHOST"));
            }

            if(!pRes->isNull("VREALM"))
            {
                pTHFVHost->set_vrealm(pRes->getString("VREALM"));
            }

        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_Thf_Enable_Set_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_Thf_Create_Check_Modifcation_Query(req,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_THF_ERR_DB_ERROR;

        mysql_set_error_for_Thf_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_Thf_Create_Add_Query(req,sStatement);
    }
    else // MOD
    {
        sql_Thf_Create_Mod_Query(req,sStatement);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_THF_ERR_DB_ERROR;

        mysql_set_error_for_Thf_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_defaultBehaviour_Set_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_Thf_Create_Check_Modifcation_Query(req,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_THF_DEFAULT_BEHAV_ERR_DB_ERROR;

        mysql_set_error_for_Thf_Config_Reqs(req,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_Thf_Create_Add_Query(req,sStatement);
    }
    else // MOD
    {
        sql_Thf_Create_Mod_Query(req,sStatement);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_THF_DEFAULT_BEHAV_ERR_DB_ERROR;

        mysql_set_error_for_Thf_Config_Reqs(resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_Realm_Add_Validation(::THFRealm *pTHFRealm,THFResp *resp,int iIndex)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    {
        sql_THFRealm_Create_Validation_Query_for_Realm(pTHFRealm->realmname(),sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_THF_REALM_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,iIndex);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            iReturn = ADD_THF_REALM_REALM_NOT_PRESENT;
            mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,iIndex);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;

    }

    {
        THFAction *localTHFAction = NULL;
        pRes = NULL;

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        localTHFAction = pTHFRealm->mutable_otherrealm(iIndex);
        sql_THFRealm_Create_Validation_Query_for_Realm(localTHFAction->realmname(),sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_THF_REALM_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,iIndex);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            iReturn = ADD_THF_REALM_OTHER_REALM_NOT_PRESENT;
            mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,iIndex);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_Thf_Realmaction_Add_Validation(::THFRealm *pTHFRealm,THFResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int action;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iFlag = 0;

    int iOtherRealm = pTHFRealm->otherrealm_size();
    for(int i=0;i<iOtherRealm;i++)
    {

        THFAction *localTHFAction = NULL;
        localTHFAction = pTHFRealm->mutable_otherrealm(i);

        // Commenting this block, as part of bug fix for 5685.
        /*if(pTHFRealm->has_realmname() && localTHFAction->has_realmname())
        {
            if(pTHFRealm->realmname().compare(localTHFAction->realmname()) == 0)
            {
                iReturn = ADD_THF_REALM_ERR_TARGET_AND_OTHER_REALM_NAME_IS_SAME;
                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }*/

        if(iFlag==0)
        {
            action = (int)localTHFAction->action();
            iFlag = 1;
        }

        if(localTHFAction->action() != action)
        {
            iReturn = ADD_THF_REALM_ERR_MIXED_ACTION_NOT_POSSIBLE;
            mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_Realm_Add_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iRealmCount = req->realms_size();
    DLOG_DEBUG("iRealmCount = %d ",iRealmCount);

    for(int i=0;i<iRealmCount;i++)
    {
        ::THFRealm *pTHFRealm = req->mutable_realms(i);

        if((iReturn = mysql_Thf_Realmaction_Add_Validation(pTHFRealm,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        int iOtherRealm = pTHFRealm->otherrealm_size();
        for(int j=0;j<iOtherRealm;j++)
        {
            if((iReturn = mysql_Thf_Realm_Add_Validation(pTHFRealm,resp,i)) != DRE_DB_SUCCESS)
            {
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;
            sql_THFRealm_Create_Check_Modifcation_Query(pTHFRealm,sStatement,j);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_THFRealm_Create_Add_Query(pTHFRealm,sStatement,j);
            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");
                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,ADD_THF_REALM_ERR_ALREADY_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_THF_REALM_ERR_ALREADY_PRESENT;

            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_vhost_Add_Validation(THFVHost *pTHFVHost)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    THFVHost localTHFVHostObj;

    sql_THFHosts_Create_Select_Query(&localTHFVHostObj,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_THF_VHOST_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->rowsCount() >= MAX_VHOST_SUPPORTED) // ADD
    {
        delete pRes;
        iReturn = ADD_THF_VHOST_ERR_MAX_COUNT_REACHED;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_vhost_Add_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iVhostCount = req->vhosts_size();
    DLOG_DEBUG("iVhostCount= %d ",iVhostCount);

    for(int i=0;i<iVhostCount;i++)
    {
        pRes = NULL;
        ::THFVHost *pTHFVHost = req->mutable_vhosts(i);

        if((iReturn = mysql_Thf_vhost_Add_Validation(pTHFVHost)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("vhost Maximum Count Reached");
            mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        sql_THFHosts_Create_Check_Modifcation_Query(pTHFVHost,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_THF_VHOST_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_THFHosts_Create_Add_Query(pTHFVHost,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,ADD_THF_VHOST_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_THF_VHOST_ERR_ALREADY_PRESENT;

        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_THF_VHOST_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_Realm_Del_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = req->realms_size();
    DLOG_DEBUG(" %s: Req Size = %d ",__FUNCTION__,iCount);
    for(int i=0; i<iCount; i++)
    {
        ::THFRealm* pTHFRealm = req->mutable_realms(i);

        int iOtherRealm = pTHFRealm->otherrealm_size();
        for(int j=0; j<iOtherRealm; j++)
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;
            sql_THFRealm_Create_Check_Modifcation_Query(pTHFRealm,sStatement,j);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,DEL_THF_REALM_ERR_NO_DATA_PRESENT,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_THF_REALM_ERR_NO_DATA_PRESENT;
            }
            else
            {
                sql_THFRealm_Create_Delete_Query(pTHFRealm,sStatement,j);
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;

            }

        }

        if(iOtherRealm == 0)
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;
            sql_THFRealm_Create_Check_Modifcation_Query(pTHFRealm,sStatement,-1);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,DEL_THF_REALM_ERR_NO_DATA_PRESENT,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_THF_REALM_ERR_NO_DATA_PRESENT;
            }
            else
            {
                sql_THFRealm_Create_Delete_Query(pTHFRealm,sStatement,-1);
            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_THF_REALM_ERR_DB_ERROR;

                mysql_set_error_for_Thf_Config_Reqs(pTHFRealm,resp,iReturn,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;

            }

        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Thf_Vhost_Del_Config_Reqs(THFReq *req,THFResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iVhostCount = req->vhosts_size();
    DLOG_DEBUG("iVhostCount= %d ",iVhostCount);

    for(int i=0;i<iVhostCount;i++)
    {
        pRes = NULL;

        ::THFVHost *pTHFVHost = req->mutable_vhosts(i);
        sql_THFHosts_Create_Check_Modifcation_Query(pTHFVHost,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_THF_VHOST_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,DEL_THF_VHOST_ERR_NO_DATA_PRESENT);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_THF_VHOST_ERR_NO_DATA_PRESENT;
        }
        else // MOD
        {
            sql_THFHosts_Create_Delete_Query(pTHFVHost,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_THF_VHOST_ERR_DB_ERROR;

            mysql_set_error_for_Thf_Config_Reqs(pTHFVHost,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_Thf_resultset_to_protoBuff(sql::ResultSet *pRes,THFResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_THF_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("CONFIG_NAME"))
            {
                DLOG_NONE(" CONFIG_NAME = %d",pRes->getInt64("CONFIG_NAME"));
                DLOG_NONE(" CONFIG_NAME = %s",pRes->getString("CONFIG_NAME").c_str());
                if(pRes->getString("CONFIG_NAME") == "enable")
                {
                    if(!pRes->isNull("VALUE"))
                    {
                        if(pRes->getString("VALUE") == "true")
                            resp->set_enablethf(true);
                        else if(pRes->getString("VALUE") == "false")
                            resp->set_enablethf(false);
                    }
                }

                if(pRes->getString("CONFIG_NAME") == "default-behaviour")
                {
                    if(!pRes->isNull("VALUE"))
                    {
                        if(pRes->getString("VALUE") == "expose")
                            resp->set_defaultexpose(true);
                        else if(pRes->getString("VALUE") == "hide")
                            resp->set_defaultexpose(false);
                    }
                }
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

