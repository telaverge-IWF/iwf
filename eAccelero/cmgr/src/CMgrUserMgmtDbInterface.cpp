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


#include "CMgrDbInterface.h"

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_RolePrevilegeMap_Config_Reqs(Role *pRole,UserDetailResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pRole->has_rolename())
        err->add_variables(pRole->rolename());

    if(iIndex != -1)
    {
        ::Previlages *pPrevilages =  pRole->mutable_previlagesdetails();
        ::Previlage* pPrevilage = pPrevilages->mutable_previlageinfo(iIndex);
        if(pPrevilage->has_previlagename())
            err->add_variables(pPrevilage->previlagename());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Previlages_Config_Reqs(Previlages *req,UserDetailResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());


    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_Previlage_Config_Reqs(Previlage *req,UserDetailResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());


    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_EmailServer_Config_Reqs(EmailServer *req,EmailServerResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_hostname())
        err->add_variables(req->hostname());
    if(req->has_portnumber())
    {
        char sPort[10];
        snprintf(sPort,10,"%d",req->portnumber());
        err->add_variables(sPort);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_set_error_for_EmailContent_Config_Reqs(EmailContent *req,EmailContentResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_emailcontentfor())
        err->add_variables(req->emailcontentfor());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void CMgrDbInterface::mysql_set_error_for_UserDetail_Config_Reqs(UserDetail *req,UserDetailResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(req->has_username())
        err->add_variables(req->username());

    if(iReturn == ADD_USER_ERR_MAX_ALLOWED_USER_COUNT_ALREADY_REACHED)
    {
		char sCount[20];
		snprintf(sCount,20,"%d",MAX_USER_ALLOWED);
        err->add_variables(sCount);
    }
    if(req->has_roledetails())
    {
        ::Role *localRole = req->mutable_roledetails();
        if(localRole->has_rolename())
            err->add_variables(localRole->rolename());

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Role_Config_Reqs(Role *pRole,UserDetailResp *resp,DbStatus_e iReturn,string sVariable)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (resp->errordetails_size() > 0)
    {
        DLOG_DEBUG("Already Added the Error %s ",__FUNCTION__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pRole->has_rolename())
        err->add_variables(pRole->rolename());

    if(iReturn == DEL_ROLE_ERR_USED_IN_USER)
        err->add_variables(sVariable);

    if(iReturn == ADD_ROLE_ERR_SAME_PREVILEGE_SET_ALREADY_PRESENT)
        err->add_variables(sVariable);

    if(iReturn == MOD_ROLE_ERR_SAME_PREVILEGE_SET_ALREADY_PRESENT)
        err->add_variables(sVariable);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_UserDetailResp_Config_Reqs(UserDetailResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_EmailContentResp_Config_Reqs(EmailContentResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_EmailServerResp_Config_Reqs(EmailServerResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_User_Config_Reqs(UserInfo *pUserConfig,UserResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pUserConfig->has_username())
        err->add_variables(pUserConfig->username());

    ::Group* localGroup = pUserConfig->mutable_usergroup();
    if(localGroup->has_groupname())
        err->add_variables(localGroup->groupname());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_UserDetail_Add_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::UserDetails *localUsers;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_usersinfo())
    {
        localUsers = req->mutable_usersinfo();
        iCount = localUsers->userinfo_size();

        if(iCount == 0)
            return ADD_USER_ERR_NO_DATA_PRESENT;
    }
    else
    {
        return ADD_USER_ERR_NO_DATA_PRESENT;
    }

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserDetail *pUserDetail = localUsers->mutable_userinfo(i);

        if((iReturn = mysql_User_Add_validation(pUserDetail)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE("Add User Validation Failed");
            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_UserDetails_Create_Check_Modifcation_Query(pUserDetail,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {

            if((iReturn = mysql_User_set_UserID(pUserDetail)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_USER_ERR_DB_ERROR;
                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            sql_UserDetails_Create_Add_Query(pUserDetail,sStatement);
        }
        else // MOD
        {
            delete pRes;
            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,ADD_USER_ERR_USERNAME_ALREADY_PRESENT);
            DLOG_ERROR("Record Already Present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_USER_ERR_USERNAME_ALREADY_PRESENT;
        }

        delete pRes;

        if(pUserDetail->has_password())
        {
            string str(pUserDetail->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;


}

DbStatus_e CMgrDbInterface::mysql_UserDetail_Mod_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::UserDetails *localUsers;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_usersinfo())
    {
        localUsers = req->mutable_usersinfo();
        iCount = localUsers->userinfo_size();

        if(iCount == 0)
            return MOD_USER_ERR_NO_DATA_PRESENT;
    }
    else
    {
        return MOD_USER_ERR_NO_DATA_PRESENT;
    }

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserDetail *pUserDetail = localUsers->mutable_userinfo(i);

        if((iReturn = mysql_User_Mod_validation(pUserDetail)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_UserDetails_Create_Check_Modifcation_Query(pUserDetail,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_USER_ERR_DB_ERROR;

            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,MOD_USER_ERR_USERNAME_NOT_PRESENT);
            DLOG_ERROR("Record Already Present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_USER_ERR_USERNAME_NOT_PRESENT;

        }
        else // MOD
        {
            mysql_User_set_ModifiedBy_And_CreatedBy(pUserDetail);
            sql_UserDetails_Create_Mod_Query(pUserDetail,sStatement);
        }

        delete pRes;

        if(pUserDetail->has_password())
        {
            string str(pUserDetail->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;


}

DbStatus_e CMgrDbInterface::mysql_UserDetail_Del_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::UserDetails *localUsers;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_usersinfo())
    {
        localUsers = req->mutable_usersinfo();
        iCount = localUsers->userinfo_size();

        if(iCount == 0)
            return DEL_USER_ERR_NO_DATA_PRESENT;
    }
    else
    {
        return DEL_USER_ERR_NO_DATA_PRESENT;
    }

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserDetail *pUserDetail = localUsers->mutable_userinfo(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_UserDetails_Create_Check_Modifcation_Query(pUserDetail,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_USER_ERR_DB_ERROR;

            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,DEL_USER_ERR_USERNAME_NOT_PRESENT);
            DLOG_ERROR("Record not Present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_USER_ERR_USERNAME_NOT_PRESENT;

        }
        else // MOD
        {
            sql_UserDetails_Create_Delete_Query(pUserDetail,sStatement);
        }

        delete pRes;

        if(pUserDetail->has_password())
        {
            string str(pUserDetail->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;


}

DbStatus_e CMgrDbInterface::mysql_UserRolePrivilegeMapping_Del_Config_Reqs(Role *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    Previlages *pPrevilages = req->mutable_previlagesdetails();
    iCount = pPrevilages->previlageinfo_size();

    for(int i=0;i<iCount;i++)
    {

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_RolePrevilegeMap_Create_Check_Modifcation_Query(req,sStatement,i);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ROLEPRIVILEGE_MAPPING_ERR_DB_ERROR;

            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,DEL_ROLEPRIVILEGE_MAPPING_NOT_PRESENT,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ROLEPRIVILEGE_MAPPING_NOT_PRESENT;

        }
        else // MOD
        {
            sql_RolePrevilegeMap_Create_Delete_Query(req,sStatement,i);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ROLEPRIVILEGE_MAPPING_ERR_DB_ERROR;

            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    if(iCount == 0)
    {
        sql_RolePrevilegeMap_Create_Delete_Query(req,sStatement,-1);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ROLEPRIVILEGE_MAPPING_ERR_DB_ERROR;

            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,iReturn,-1);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_UserRolePrivilegeMapping_Add_Config_Reqs(Role *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::Previlages *pPrevilages;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_previlagesdetails())
    {
        pPrevilages= req->mutable_previlagesdetails();
        iCount = pPrevilages->previlageinfo_size();

        if(iCount == 0)
            return ADD_ROLEPRIVILEGE_MAPPING_NO_DATA_PRESENT;
    }
    else
    {
        return ADD_ROLEPRIVILEGE_MAPPING_NO_DATA_PRESENT;
    }

    for(int i=0;i<iCount;i++)
    {

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_RolePrevilegeMap_Create_Check_Modifcation_Query(req,sStatement,i);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ROLEPRIVILEGE_MAPPING_ERR_DB_ERROR;

            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_RolePrevilegeMap_Create_Add_Query(req,sStatement,i);
        }
        else // MOD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,ADD_ROLEPRIVILEGE_MAPPING_ALREADY_PRESENT,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ROLEPRIVILEGE_MAPPING_ALREADY_PRESENT;
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ROLEPRIVILEGE_MAPPING_ERR_DB_ERROR;

            mysql_set_error_for_RolePrevilegeMap_Config_Reqs(req,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_UserRole_Add_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::Roles *pRoles;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_rolesinfo())
    {
        pRoles = req->mutable_rolesinfo();
        iCount = pRoles->roleinfo_size();

        if(iCount == 0)
            return ADD_ROLE_NO_DATA_PRESENT;
    }
    else
    {
        return ADD_ROLE_NO_DATA_PRESENT;
    }

    for(int i=0;i<iCount;i++)
    {
        ::Role* pRole = pRoles->mutable_roleinfo(i);

        if((iReturn = mysql_RolePrevilageMapping_Add_validation(pRole,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_Role_Create_Check_Modifcation_Query(pRole,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            if((iReturn = mysql_Role_set_RoleID(pRole)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_USER_ERR_DB_ERROR;

                mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            sql_Role_Create_Add_Query(pRole,sStatement);
        }
        else // MOD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_Role_Config_Reqs(pRole,resp,ADD_ROLE_ERR_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_ROLE_ERR_ALREADY_PRESENT;
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        iReturn = mysql_UserRolePrivilegeMapping_Add_Config_Reqs(pRole,resp);
        if(iReturn == ADD_ROLEPRIVILEGE_MAPPING_NO_DATA_PRESENT)
            iReturn = DRE_DB_SUCCESS;
        if(iReturn != DRE_DB_SUCCESS)
            return iReturn;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_Role_Del_Validation(Role *pRole,UserDetailResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;


    sql_Role_Create_Validation_Query_for_User(pRole,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_USER_ERR_DB_ERROR;

        mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->rowsCount() > 0) // ADD
    {
        string sUserName;
        if(pRes->next())
        {
            if(!pRes->isNull("UserName"))
            {
                sUserName = pRes->getString("UserName");
            }
        }
        delete pRes;
        DLOG_ERROR("Record is present ");
        iReturn = DEL_ROLE_ERR_USED_IN_USER;
        mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn,sUserName);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_UserRole_Del_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::Roles *pRoles;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_rolesinfo())
    {
        pRoles = req->mutable_rolesinfo();
        iCount = pRoles->roleinfo_size();

        if(iCount == 0)
            return DEL_ROLE_NO_DATA_PRESENT;
    }
    else
    {
        return DEL_ROLE_NO_DATA_PRESENT;
    }

    for(int i=0;i<iCount;i++)
    {
        ::Role* pRole = pRoles->mutable_roleinfo(i);

        if((iReturn = mysql_Role_Del_Validation(pRole,resp)) != DRE_DB_SUCCESS)
        {
            return iReturn;
        }
        Role localRole;
        localRole.set_rolename(pRole->rolename());
        iReturn = mysql_UserRolePrivilegeMapping_Del_Config_Reqs(&localRole,resp);
        if(iReturn == DEL_ROLEPRIVILEGE_MAPPING_NO_DATA_PRESENT)
            iReturn = DRE_DB_SUCCESS;
        if(iReturn != DRE_DB_SUCCESS)
            return iReturn;


        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_Role_Create_Check_Modifcation_Query(pRole,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_Role_Config_Reqs(pRole,resp,DEL_ROLE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ROLE_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_Role_Create_Delete_Query(pRole,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_EmailServer_Del_Config_Reqs(EmailServerReq *req, EmailServerResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    iCount = req->emailservers_size();
    if(iCount == 0)
        return DEL_EMAILSERVER_NO_DATA_PRESENT;

    for(int i=0;i<iCount;i++)
    {
        ::EmailServer* pEmailServer = req->mutable_emailservers(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_EmailServer_Create_Check_Modifcation_Query(pEmailServer,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_EMAILSERVER_ERR_DB_ERROR;

            mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,DEL_EMAILSERVER_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_EMAILSERVER_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_EmailServer_Create_Delete_Query(pEmailServer,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_EMAILSERVER_ERR_DB_ERROR;

            mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_EmailServer_Set_Config_Reqs(EmailServerReq *req, EmailServerResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    iCount = req->emailservers_size();
    if(iCount == 0)
        return MOD_EMAILSERVER_NO_DATA_PRESENT;

    for(int i=0;i<iCount;i++)
    {
        ::EmailServer* pEmailServer = req->mutable_emailservers(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_EmailServer_Create_Check_Modifcation_Query(pEmailServer,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_EMAILSERVER_ERR_DB_ERROR;

            mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_EmailServer_Create_Add_Query(pEmailServer,sStatement);
        }
        else // MOD
        {
            sql_EmailServer_Create_Mod_Query(pEmailServer,sStatement);
        }


        delete pRes;
        if(pEmailServer->has_password())
        {
            string str(pEmailServer->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_EMAILSERVER_ERR_DB_ERROR;

                mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
        else
        {
            string str("nothing",16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_EMAILSERVER_ERR_DB_ERROR;

                mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }


    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_EmailContent_Mod_Config_Reqs(EmailContentReq *req, EmailContentResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    iCount = req->emailcontents_size();
    if(iCount == 0)
        return MOD_EMAILCONTENT_NO_DATA_PRESENT;

    for(int i=0;i<iCount;i++)
    {
        ::EmailContent* pEmailContent = req->mutable_emailcontents(i);

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_EmailContent_Create_Check_Modifcation_Query(pEmailContent,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_EMAILCONTENT_ERR_DB_ERROR;

            mysql_set_error_for_EmailContent_Config_Reqs(pEmailContent,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_EmailContent_Config_Reqs(pEmailContent,resp,MOD_EMAILCONTENT_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_EMAILCONTENT_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_EmailContent_Create_Mod_Query(pEmailContent,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_EMAILCONTENT_ERR_DB_ERROR;

            mysql_set_error_for_EmailContent_Config_Reqs(pEmailContent,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_RoleName_Modification(::Role *pRole,UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    Role LocalRole;
    LocalRole.set_roleid(pRole->roleid());
    sql_Role_Create_Select_Query(&LocalRole,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_ROLE_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->rowsCount() == 0)
    {
        delete pRes;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_ROLE_ERR_NOT_PRESENT;
    }

    delete pRes;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRole->has_rolename())
    {
        Role LocalRole;
        LocalRole.set_rolename(pRole->rolename());
        sql_Role_Create_Select_Query(&LocalRole,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ROLE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        DLOG_NONE("pRes->rowsCount() = %d ",pRes->rowsCount());
        if(pRes->rowsCount() != 0)
        {
            if(pRes->next())
            {
                unsigned int roleid = pRes->getUInt("ROLE_ID");
                if(roleid != pRole->roleid())
                {

                    delete pRes;
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_ROLE_ERR_ROLNAME_ALREADY_PRESENT;
                }
            }
        }

        delete pRes;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        LocalRole.set_rolename(pRole->rolename());
        LocalRole.set_roleid(pRole->roleid());
        sql_Role_Create_Mod_Query(&LocalRole,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_UserRole_Mod_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;
    ::Roles *pRoles;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_rolesinfo())
    {
        pRoles = req->mutable_rolesinfo();
        iCount = pRoles->roleinfo_size();

        if(iCount == 0)
            return MOD_ROLE_NO_DATA_PRESENT;
    }
    else
    {
        return MOD_ROLE_NO_DATA_PRESENT;
    }

    for(int i=0;i<iCount;i++)
    {

        ::Role* pRole = pRoles->mutable_roleinfo(i);

        if((iReturn = mysql_RoleName_Modification(pRole,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_RolePrevilageMapping_Mod_validation(pRole,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_Role_Create_Check_Modifcation_Query(pRole,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {

            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_Role_Config_Reqs(pRole,resp,MOD_ROLE_ERR_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_ROLE_ERR_NOT_PRESENT;

        }
        else // MOD
        {
            sql_Role_Create_Mod_Query(pRole,sStatement);
        }


        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_ROLE_ERR_DB_ERROR;

            mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        Role localRole;
        localRole.set_rolename(pRole->rolename());
        iReturn = mysql_UserRolePrivilegeMapping_Del_Config_Reqs(&localRole,resp);
        if(iReturn == DEL_ROLEPRIVILEGE_MAPPING_NO_DATA_PRESENT)
            iReturn = DRE_DB_SUCCESS;
        if(iReturn != DRE_DB_SUCCESS)
            return iReturn;

        iReturn = mysql_UserRolePrivilegeMapping_Add_Config_Reqs(pRole,resp);
        if(iReturn == ADD_ROLEPRIVILEGE_MAPPING_NO_DATA_PRESENT)
            iReturn = DRE_DB_SUCCESS;
        if(iReturn != DRE_DB_SUCCESS)
            return iReturn;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_PrevilegeMapping_resultset_to_protoBuff(Role *pRole)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_DEBUG("Role = %s",pRole->DebugString().c_str());

    sql_RolePrevilegeMap_Create_Select_Query(pRole,sStatement,-1);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_PREVILEGE_MAPPING_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PREVILEGE_MAPPING_NO_DATA_PRESENT;
        }

        Previlages *pPrevilages = pRole->mutable_previlagesdetails();
        while(pRes->next())
        {
            Previlage *pPrevilage = pPrevilages->add_previlageinfo();

            if(!pRes->isNull("PRIVILEGE_ID"))
                pPrevilage->set_previlageid(pRes->getInt("PRIVILEGE_ID"));

            mysql_Previlege_resultset_to_protoBuff(pPrevilage);
        }
    }
    catch (sql::SQLException &e)
    {
        delete pRes;
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_Previleges_resultset_to_protoBuff(Previlages *pPrevilages)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    Previlage lPrevilage;
    sql_Previlege_Create_Select_Query(&lPrevilage,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_PREVILEGE_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PREVILEGE_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            Previlage *pPrevilage = pPrevilages->add_previlageinfo();
            if(!pRes->isNull("PRIVILEGE_ID"))
                pPrevilage->set_previlageid(pRes->getInt("PRIVILEGE_ID"));
            if(!pRes->isNull("PRIVILEGE_NAME"))
                pPrevilage->set_previlagename(pRes->getString("PRIVILEGE_NAME"));
            if(!pRes->isNull("PRIVILEGE_DISCRIPTION"))
                pPrevilage->set_previlagedesc(pRes->getString("PRIVILEGE_DISCRIPTION"));
        }
    }
    catch (sql::SQLException &e)
    {
        delete pRes;
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_Previlege_resultset_to_protoBuff(Previlage *pPrevilage)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_Previlege_Create_Select_Query(pPrevilage,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {

        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_PREVILEGE_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PREVILEGE_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("PRIVILEGE_NAME"))
                pPrevilage->set_previlagename(pRes->getString("PRIVILEGE_NAME"));
            if(!pRes->isNull("PRIVILEGE_DISCRIPTION"))
                pPrevilage->set_previlagedesc(pRes->getString("PRIVILEGE_DISCRIPTION"));
        }
    }
    catch (sql::SQLException &e)
    {
        delete pRes;
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_Role_resultset_to_protoBuff(sql::ResultSet *pRes,UserDetailResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_ROLE_NO_DATA_PRESENT;
        }

        ::Roles *pRoles = resp->mutable_rolesinfo();

        while(pRes->next())
        {
            ::Role* pRole = pRoles->add_roleinfo();

            if(!pRes->isNull("ROLE"))
                pRole->set_rolename(pRes->getString("ROLE"));

            if(!pRes->isNull("ROLE_STATUS"))
                pRole->set_rolestatus(pRes->getInt("ROLE_STATUS"));

            if(!pRes->isNull("ROLE_ID"))
                pRole->set_roleid(pRes->getInt("ROLE_ID"));

            mysql_PrevilegeMapping_resultset_to_protoBuff(pRole);
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

DbStatus_e CMgrDbInterface::mysql_UserDetail_resultset_to_protoBuff(sql::ResultSet *pRes,UserDetailResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_USER_ERR_NO_DATA_PRESENT;
        }

        UserDetails *pUserDetails = resp->mutable_usersinfo();
        while(pRes->next())
        {
            UserDetail* pUserDetail = pUserDetails->add_userinfo();

            if(!pRes->isNull("UserID"))
                pUserDetail->set_userid(pRes->getInt("UserID"));

            if(!pRes->isNull("UserName"))
                pUserDetail->set_username(pRes->getString("UserName"));

            if(!pRes->isNull("FirstName"))
                pUserDetail->set_firstname(pRes->getString("FirstName"));

            if(!pRes->isNull("LastName"))
                pUserDetail->set_lastname(pRes->getString("LastName"));

            if(!pRes->isNull("Email"))
                pUserDetail->set_email(pRes->getString("Email"));

            if(!pRes->isNull("status"))
                pUserDetail->set_userstatus(pRes->getInt("status"));

            if(!pRes->isNull("UserType"))
                pUserDetail->set_usertype(pRes->getString("UserType"));

            if(!pRes->isNull("LastLogin"))
                pUserDetail->set_lastlogin(pRes->getString("LastLogin"));

            if(!pRes->isNull("CreatedBy"))
                pUserDetail->set_createdbyid(pRes->getInt("CreatedBy"));

            if(!pRes->isNull("CreationTime"))
                pUserDetail->set_creationtime(pRes->getString("CreationTime"));

            if(!pRes->isNull("ModifiedBy"))
                pUserDetail->set_modifiedbyid(pRes->getInt("ModifiedBy"));

            if(!pRes->isNull("ModificationTime"))
                pUserDetail->set_modificationtime(pRes->getString("ModificationTime"));

            if(!pRes->isNull("PasswordStatus"))
                pUserDetail->set_passwordstatus(pRes->getInt("PasswordStatus"));

            mysql_FetchAndFill_UserDetail(pUserDetail);
            std::istream *blobstream;
            if(!pRes->isNull("Password"))
            {
                blobstream = pRes->getBlob("Password");
                char str[20];
                blobstream->read((char *)&str,16);
                pUserDetail->set_password((void *)&str,16);
                delete blobstream;
            }

            if(!pRes->isNull("RoleID"))
            {
                Role *pRole = pUserDetail->mutable_roledetails();
                pRole->set_roleid(pRes->getInt("RoleID"));
                //mysql_UserRole_Get_Config_Reqs(pRole,resp);
                mysql_FetchAndFill_UserRole(pRole,resp);
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

DbStatus_e CMgrDbInterface::mysql_EmailServer_resultset_to_protoBuff(sql::ResultSet *pRes,EmailServerResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_EMAILSERVER_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            EmailServer* pEmailServer = resp->add_emailservers();

            if(!pRes->isNull("HOSTNAME"))
                pEmailServer->set_hostname(pRes->getString("HOSTNAME"));

            if(!pRes->isNull("PORT_NUMBER"))
                pEmailServer->set_portnumber(pRes->getInt("PORT_NUMBER"));

            if(!pRes->isNull("SYSTEM_EMAIL"))
                pEmailServer->set_systememail(pRes->getString("SYSTEM_EMAIL"));

            std::istream *blobstream;
            if(!pRes->isNull("Password"))
            {
                blobstream = pRes->getBlob("Password");
                char str[20];
                blobstream->read((char *)&str,16);
                pEmailServer->set_password((void *)&str,16);
                delete blobstream;
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

DbStatus_e CMgrDbInterface::mysql_EmailContent_resultset_to_protoBuff(sql::ResultSet *pRes,EmailContentResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_EMAILCONTENT_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            EmailContent* pEmailContent = resp->add_emailcontents();

            if(!pRes->isNull("EMAIL_CONTENT_FOR"))
                pEmailContent->set_emailcontentfor(pRes->getString("EMAIL_CONTENT_FOR"));

            if(!pRes->isNull("EMAIL_STATUS"))
                pEmailContent->set_emailstatus(pRes->getInt("EMAIL_STATUS"));

            if(!pRes->isNull("MESSAGE"))
                pEmailContent->set_message(pRes->getString("MESSAGE"));

            if(!pRes->isNull("SUBJECT"))
                pEmailContent->set_subject(pRes->getString("SUBJECT"));
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

DbStatus_e CMgrDbInterface::mysql_Previlage_GetConfig_Reqs(UserDetailReq *req,UserDetailResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);

    Previlages *pPrevilages = req->mutable_previlageinfo();
    iCount = pPrevilages->previlageinfo_size();
    DLOG_NONE(" Previlages Count : %d ",iCount);
    if(iCount > 0)
    {
        for(int i=0;i<iCount;i++)
        {
            Previlage *pPrevilage = pPrevilages->mutable_previlageinfo(i);
            Previlages *pLocalPrevilages = resp->mutable_previlageinfo();
            Previlage *pLocalPrevilage = pLocalPrevilages->add_previlageinfo();
            pLocalPrevilage->set_previlagename(pPrevilage->previlagename());
            if((iReturn = mysql_Previlege_resultset_to_protoBuff(pLocalPrevilage)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_Previlage_Config_Reqs(pPrevilage,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }
    }
    else
    {
        Previlages *pLocalPrevilages = resp->mutable_previlageinfo();
        if((iReturn = mysql_Previleges_resultset_to_protoBuff(pPrevilages)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Previlages_Config_Reqs(pLocalPrevilages,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_EmailServer_Get_Config_Reqs(EmailServerReq *req, EmailServerResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    iCount = req->emailservers_size();
    if(iCount > 0)
    {
        for(int i=0;i<iCount;i++)
        {
            ::EmailServer* pEmailServer = req->mutable_emailservers(i);

            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_EmailServer_Create_Select_Query(pEmailServer,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {

                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_EMAILSERVER_ERR_DB_ERROR;

                mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_EmailServer_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_EmailServer_Config_Reqs(pEmailServer,resp,iReturn);
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;

        }

    }
    else
    {
        ::EmailServer EmailServerObj;

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_EmailServer_Create_Select_Query(&EmailServerObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_EMAILSERVER_ERR_DB_ERROR;

            mysql_set_error_for_EmailServer_Config_Reqs(&EmailServerObj,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_EmailServer_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_EmailServer_Config_Reqs(&EmailServerObj,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;

    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}
DbStatus_e CMgrDbInterface::mysql_EmailContent_Get_Config_Reqs(EmailContentReq *req, EmailContentResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    iCount = req->emailcontents_size();
    if(iCount > 0)
    {
        for(int i=0;i<iCount;i++)
        {
            ::EmailContent* pEmailContent = req->mutable_emailcontents(i);

            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_EmailContent_Create_Select_Query(pEmailContent,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {

                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_EMAILCONTENT_ERR_DB_ERROR;

                mysql_set_error_for_EmailContent_Config_Reqs(pEmailContent,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_EmailContent_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                if(iReturn == GET_EMAILCONTENT_NO_DATA_PRESENT)
                    iReturn = GET_EMAILCONTENT_DATA_NOT_PRESENT;
                mysql_set_error_for_EmailContent_Config_Reqs(pEmailContent,resp,iReturn);
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;

        }

    }
    else
    {
        ::EmailContent EmailContentObj;

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_EmailContent_Create_Select_Query(&EmailContentObj,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {

            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_EMAILCONTENT_ERR_DB_ERROR;

            mysql_set_error_for_EmailContent_Config_Reqs(&EmailContentObj,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_EmailContent_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_EmailContent_Config_Reqs(&EmailContentObj,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;

    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_FetchAndFill_UserDetail(UserDetail *pUserDetail)
{

    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pUserDetail->has_createdbyid())
    {
        UserDetail LocalUserDetail;
        LocalUserDetail.set_userid(pUserDetail->createdbyid());
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_ROLE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());

            if(pRes->next())
            {
                if(!pRes->isNull("UserName"))
                    pUserDetail->set_createdby(pRes->getString("UserName"));
            }
            delete pRes;
        }
        catch (sql::SQLException &e)
        {
            delete pRes;
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_FAIL;
        }
    }

    if(pUserDetail->has_modifiedbyid())
    {
        UserDetail LocalUserDetail;
        LocalUserDetail.set_userid(pUserDetail->modifiedbyid());
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_ROLE_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());

            if(pRes->next())
            {
                if(!pRes->isNull("UserName"))
                    pUserDetail->set_modifiedby(pRes->getString("UserName"));
            }
            delete pRes;
        }
        catch (sql::SQLException &e)
        {
            delete pRes;
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_FAIL;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_FetchAndFill_UserRole(::Role *pRole, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_Role_Create_Select_Query(pRole,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_ROLE_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_ROLE_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            if(!pRes->isNull("ROLE"))
                pRole->set_rolename(pRes->getString("ROLE"));

            if(!pRes->isNull("ROLE_STATUS"))
                pRole->set_rolestatus(pRes->getInt("ROLE_STATUS"));

            if(!pRes->isNull("ROLE_ID"))
                pRole->set_roleid(pRes->getInt("ROLE_ID"));

            mysql_PrevilegeMapping_resultset_to_protoBuff(pRole);
        }
    }
    catch (sql::SQLException &e)
    {
        delete pRes;
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_UserRole_Get_Config_Reqs(::Role *pRole, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_Role_Create_Select_Query(pRole,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_ROLE_ERR_DB_ERROR;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_Role_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    delete pRes;


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_UserRole_Get_Config_Reqs(::Roles *pRoles, UserDetailResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    iCount = pRoles->roleinfo_size();

    if(iCount > 0)
    {
        for(int i=0;i<iCount;i++)
        {
            ::Role* pRole = pRoles->mutable_roleinfo(i);
            if((iReturn = mysql_UserRole_Get_Config_Reqs(pRole,resp)) != DRE_DB_SUCCESS)
            {
                if(iReturn == GET_ROLE_NO_DATA_PRESENT)
                    iReturn = GET_ROLE_DATA_NOT_PRESENT;
                mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }
    else
    {
        ::Role RoleObj;
        if((iReturn = mysql_UserRole_Get_Config_Reqs(&RoleObj,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Role_Config_Reqs(&RoleObj,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_UserRole_Get_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::Roles *pRoles;

    DLOG_NONE(" > %s ",__FUNCTION__);
    pRoles = req->mutable_rolesinfo();
    if((iReturn = mysql_UserRole_Get_Config_Reqs(pRoles,resp)) != DRE_DB_SUCCESS)
    {
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_UserDetail_Get_Config_Reqs(UserDetailReq *req, UserDetailResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    UserDetails *pUserDetails = req->mutable_usersinfo();
    iCount = pUserDetails->userinfo_size();

    if(iCount > 0)
    {
        for(int i=0;i<iCount;i++)
        {
            ::UserDetail* pUserDetail = pUserDetails->mutable_userinfo(i);


            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_UserDetails_Create_Select_Query(pUserDetail,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_USER_ERR_DB_ERROR;

                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_UserDetail_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_UserDetail_Config_Reqs(pUserDetail,resp,iReturn);
                delete pRes;
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
            delete pRes;

        }

    }
    else
    {
        ::UserDetail LocalUserDetail;


        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_USER_ERR_DB_ERROR;

            mysql_set_error_for_UserDetail_Config_Reqs(&LocalUserDetail,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_UserDetail_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_UserDetail_Config_Reqs(&LocalUserDetail,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }
    return DRE_DB_SUCCESS;
    DLOG_NONE(" < %s ",__FUNCTION__);

}

DbStatus_e CMgrDbInterface::mysql_User_Get_Config_Reqs(UserReq *req, UserResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    UserInfo localUserConfig;
    Users *localUsers;

    int iCount;

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(req->has_user())
    {
        localUsers = req->mutable_user();
        iCount = localUsers->userdata_size();
    }
    else
        iCount = 0;

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserInfo *pUserConfig = localUsers->mutable_userdata(i);

        sql_User_Create_Select_Query(pUserConfig,sStatement);

        pRes = NULL;
        if(pUserConfig->has_password())
        {
            string str(pUserConfig->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_get_query_for_user_table(sStatement,&pRes,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_get_query_for_user_table(sStatement,&pRes,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

        if((iReturn = mysql_User_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iCount == 0)
    {
        UserInfo *pUserConfig = &localUserConfig;

        istringstream  bInStream("nothing",ios_base::in);
        sql_User_Create_Select_Query(pUserConfig,sStatement);
        if ((iReturn = m_dbHandle.mysql_exec_get_query_for_user_table(sStatement,&pRes,&bInStream,false)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_USER_ERR_DB_ERROR;

            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            return iReturn;
        }

        if((iReturn = mysql_User_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_User_resultset_to_protoBuff(sql::ResultSet *pRes,UserResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_USER_ERR_NO_DATA_PRESENT;
        }

        ::Users* localUsers = resp->mutable_user();

        while(pRes->next())
        {
            ::UserInfo* pLocalUserInfo = localUsers->add_userdata();

            if(!pRes->isNull("Username"))
                pLocalUserInfo->set_username(pRes->getString("Username"));

            std::istream *blobstream;
            if(!pRes->isNull("Password"))
            {
                blobstream = pRes->getBlob("Password");
                char str[20];
                blobstream->read((char *)&str,16);
                pLocalUserInfo->set_password((void *)&str,16);
                delete blobstream;
            }

            if(!pRes->isNull("ROLE"))
            {
                Group *localGroup = pLocalUserInfo->mutable_usergroup();
                localGroup->set_groupname(pRes->getString("ROLE"));
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

DbStatus_e CMgrDbInterface::mysql_User_Mod_validation(::UserDetail *pUserInfo)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    ::Role* localRole = pUserInfo->mutable_roledetails();
    if(localRole->has_rolename())
    {
        sql_RoleDetails_Create_Validation_Query_for_Role(pUserInfo,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_USER_ERR_INVALID_ROLE;

        }

        if(iReturn == DRE_DB_SUCCESS)
        {
            Role lRole;
            lRole.set_rolename(localRole->rolename());
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            sql_RolePrevilegeMap_Create_Check_Modifcation_Query(&lRole,sStatement,-1);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_USER_ERR_DB_ERROR;

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_USER_ERR_PRIVILEGE_NOT_CONFIGURED;
            }
            delete pRes;
        }
    }

    /*
     * Validation to check username and email is already present in the database
     * Fetch the data from the DB with the username and email, compare the userid
     * with the userid in the request, if both id are same. return success
     * if userid are different return ERROR.
     *
     */
    {
        pRes = NULL;
        UserDetail lUserDetail;
        lUserDetail.set_username(pUserInfo->username());

        sql_UserDetails_Create_Select_Query(&lUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("UserID") && pRes->getUInt("UserID") != pUserInfo->userid())
                {
                    delete pRes;
                    DLOG_ERROR("Record already present ");
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return MOD_USER_ERR_USERNAME_ALREADY_PRESENT;
                }
            }
        }
        delete pRes;

#if 0
        pRes = NULL;
        lUserDetail.clear_username();
        lUserDetail.set_email(pUserInfo->email());

        sql_UserDetails_Create_Select_Query(&lUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() > 0)
        {
            if(pRes->next())
            {
                if(!pRes->isNull("UserID"))
                {
                    if(pRes->getUInt("UserID") != pUserInfo->userid())
                    {
                        delete pRes;
                        DLOG_ERROR("Record already present ");
                        DLOG_NONE(" < %s ",__FUNCTION__);
                        return MOD_USER_ERR_EMAIL_ALREADY_PRESENT;
                    }
                }
            }
        }
        delete pRes;
#endif
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Role_set_RoleID(::Role *pRole)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    sql_Role_Create_MaxId_Query(sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->next())
    {
        if(!pRes->isNull("max(ROLE_ID)"))
        {
            int Maxid = pRes->getInt("max(ROLE_ID)");
            pRole->set_roleid(Maxid + 1);
        }
    }
    delete pRes;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_User_set_ModifiedBy_And_CreatedBy(::UserDetail *pUserInfo)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    UserDetail LocalUserDetail;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pUserInfo->has_modifiedby())
    {
        LocalUserDetail.set_username(pUserInfo->modifiedby());
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            if(pRes->next()) // ADD
            {
                if(!pRes->isNull("UserID"))
                {
                    DLOG_DEBUG(" %s: UserID = %d ",__FUNCTION__,pRes->getInt("UserID"));
                    pUserInfo->set_modifiedbyid(pRes->getInt("UserID"));
                }
            }
            delete pRes;
        }
        catch (sql::SQLException &e)
        {
            delete pRes;
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_FAIL;
        }

    }


    if(pUserInfo->has_createdby())
    {
        pRes = NULL;
        LocalUserDetail.set_username(pUserInfo->createdby());
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        try
        {
            DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            if(pRes->next()) // ADD
            {
                if(!pRes->isNull("UserID"))
                {
                    DLOG_DEBUG(" %s: UserID = %d ",__FUNCTION__,pRes->getInt("UserID"));
                    pUserInfo->set_createdbyid(pRes->getInt("UserID"));
                }
            }
            delete pRes;
        }
        catch (sql::SQLException &e)
        {
            delete pRes;
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_FAIL;
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_User_set_UserID(::UserDetail *pUserInfo)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    sql_UserDetails_Create_MaxId_Query(sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->next())
    {
        if(!pRes->isNull("max(UserID)"))
        {
            int Maxid = pRes->getInt("max(UserID)");
            pUserInfo->set_userid(Maxid + 1);
        }
    }

    delete pRes;
    mysql_User_set_ModifiedBy_And_CreatedBy(pUserInfo);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_User_Add_validation(::UserDetail *pUserInfo)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    {
        /* Validation for users max count, should not go beyond what is allowed
         */
        UserDetail LocalUserDetail;

        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() >= MAX_USER_ALLOWED) // ADD
        {
            delete pRes;
            DLOG_ERROR("Maximum user count reached, no more users allowed");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_USER_ERR_MAX_ALLOWED_USER_COUNT_ALREADY_REACHED;
        }

        delete pRes;

        /* Validation user name, should be unique in UserTable.
         */
        pRes = NULL;
        LocalUserDetail.set_username(pUserInfo->username());
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present ");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_USER_ERR_USERNAME_ALREADY_PRESENT;
        }
        delete pRes;

        /* Validation for email, should be unique in userTable.
         */
#if 0
        pRes = NULL;
        LocalUserDetail.clear_username();
        LocalUserDetail.set_email(pUserInfo->email());
        sql_UserDetails_Create_Select_Query(&LocalUserDetail,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() > 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_USER_ERR_EMAIL_ALREADY_PRESENT;
        }
        delete pRes;
#endif
    }

    ::Role* localRole = pUserInfo->mutable_roledetails();
    if(localRole->has_rolename())
    {
        sql_RoleDetails_Create_Validation_Query_for_Role(pUserInfo,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_INVALID_ROLE;

        }

        if(iReturn == DRE_DB_SUCCESS)
        {
            pRes = NULL;
            Role lRole;
            lRole.set_rolename(localRole->rolename());
            memset(sStatement,0,MAX_STATEMENT_SIZE);

            sql_RolePrevilegeMap_Create_Check_Modifcation_Query(&lRole,sStatement,-1);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_USER_ERR_DB_ERROR;

                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_USER_ERR_PRIVILEGE_NOT_CONFIGURED;
            }
            delete pRes;
        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_User_Add_validation(::UserInfo *pUserInfo)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    ::Group* localGroup = pUserInfo->mutable_usergroup();
    if(localGroup->has_groupname())
    {
        sql_Role_Create_Validation_Query_for_Role(pUserInfo,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_INVALID_ROLE;

        }
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_RolePrevilageMapping_Add_validation(::Role *pRole,UserDetailResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);

    Previlages *pActualPrevilages = pRole->mutable_previlagesdetails();
    int iActualCount = pActualPrevilages->previlageinfo_size();
    DLOG_DEBUG("iActualCount = %d",iActualCount);

    if(iActualCount == 0)
    {
        DLOG_NONE("Adding Role without previlage is allowed");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }

    Roles localRoles;
    UserDetailResp localresp;
    mysql_UserRole_Get_Config_Reqs(&localRoles,&localresp);

    localRoles = localresp.rolesinfo();
    int iCount = localRoles.roleinfo_size();
    DLOG_DEBUG("iCount = %d",iCount);
    for(int i=0;i<iCount;i++)
    {
        Role *pLocalRole = localRoles.mutable_roleinfo(i);

        string sRoleName = "";
        sRoleName = pLocalRole->rolename();

        Previlages *pPrevilages = pLocalRole->mutable_previlagesdetails();
        int jCount = pPrevilages->previlageinfo_size();
        DLOG_DEBUG("jCount = %d",jCount);
        if(jCount != iActualCount)
        {
            DLOG_DEBUG("jCount %d iActualCount %d, counts are not same so previlages will be different.. so skipping",jCount,iActualCount);
            continue;
        }

        int iFlag=-1;
        for(int j=0;j<jCount;j++)
        {
            Previlage *pPrevilage = pPrevilages->mutable_previlageinfo(j);
            iFlag = 0;
            for(int k=0;k<iActualCount;k++)
            {
                Previlage *pActualPrevilage = pActualPrevilages->mutable_previlageinfo(k);
                DLOG_DEBUG(" pActualPrevilage->previlagename %s - pPrevilage->previlagename() same ",pActualPrevilage->previlagename().c_str(),pPrevilage->previlagename().c_str());
                if(pActualPrevilage->previlagename() == pPrevilage->previlagename())
                {
                    DLOG_DEBUG(" pActualPrevilage->previlagename %s - pPrevilage->previlagename() same ",pActualPrevilage->previlagename().c_str(),pPrevilage->previlagename().c_str());
                    iFlag = 1;
                    break;
                }
            }
            if(iFlag == 0)
                break;
        }
        if(iFlag == 0)
            continue;

        //if it reach here means.. iFlag is set for all the previlage
        //so returning
        mysql_set_error_for_Role_Config_Reqs(pRole,resp,ADD_ROLE_ERR_SAME_PREVILEGE_SET_ALREADY_PRESENT,sRoleName);

        return ADD_ROLE_ERR_SAME_PREVILEGE_SET_ALREADY_PRESENT;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_RolePrevilageMapping_NoPrevilage_validation(::Role *pRole,UserDetailResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_Role_Create_Validation_Query_for_User(pRole,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_USER_ERR_DB_ERROR;

        mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->rowsCount() > 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record is present ");
        iReturn = MOD_ROLE_ERR_DEL_ALL_PREVILAGE_IN_USE;
        mysql_set_error_for_Role_Config_Reqs(pRole,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    delete pRes;


    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_RolePrevilageMapping_Mod_validation(::Role *pRole,UserDetailResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    Previlages *pActualPrevilages = pRole->mutable_previlagesdetails();
    int iActualCount = pActualPrevilages->previlageinfo_size();

    if(iActualCount == 0)
    {
        if((iReturn = mysql_RolePrevilageMapping_NoPrevilage_validation(pRole,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE("Modifing Role without previlage is not allowed, if Role is used in user");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        DLOG_NONE("Modifing Role without previlage is allowed, if Role is not used in any User");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }

    Roles localRoles;
    UserDetailResp localresp;
    mysql_UserRole_Get_Config_Reqs(&localRoles,&localresp);

    localRoles = localresp.rolesinfo();
    int iCount = localRoles.roleinfo_size();
    DLOG_DEBUG("iCount = %d",iCount);
    for(int i=0;i<iCount;i++)
    {
        Role *pLocalRole = localRoles.mutable_roleinfo(i);


        if(pLocalRole->rolename() == pRole->rolename())
        {
            DLOG_DEBUG("Rolename are same.. so skiping");
            continue;
        }

        string sRoleName = "";
        sRoleName = pLocalRole->rolename();

        Previlages *pPrevilages = pLocalRole->mutable_previlagesdetails();
        int jCount = pPrevilages->previlageinfo_size();
        DLOG_DEBUG("jCount = %d",jCount);
        if(jCount != iActualCount)
        {
            DLOG_DEBUG("jCount %d iActualCount %d, counts are not same so previlages will be different.. so skipping",jCount,iActualCount);
            continue;
        }

        int iFlag=-1;
        for(int j=0;j<jCount;j++)
        {
            Previlage *pPrevilage = pPrevilages->mutable_previlageinfo(j);
            iFlag = 0;
            for(int k=0;k<iActualCount;k++)
            {
                Previlage *pActualPrevilage = pActualPrevilages->mutable_previlageinfo(k);
                DLOG_DEBUG(" pActualPrevilage->previlagename %s - pPrevilage->previlagename() same ",pActualPrevilage->previlagename().c_str(),pPrevilage->previlagename().c_str());
                if(pActualPrevilage->previlagename() == pPrevilage->previlagename())
                {
                    DLOG_DEBUG(" pActualPrevilage->previlagename %s - pPrevilage->previlagename() ",pActualPrevilage->previlagename().c_str(),pPrevilage->previlagename().c_str());
                    iFlag = 1;
                    break;
                }
            }
            if(iFlag == 0)
                break;
        }
        if(iFlag == 0)
            continue;

        //if it reach here means.. iFlag is set for all the previlage
        //so returning
        mysql_set_error_for_Role_Config_Reqs(pRole,resp,MOD_ROLE_ERR_SAME_PREVILEGE_SET_ALREADY_PRESENT,sRoleName);
        return MOD_ROLE_ERR_SAME_PREVILEGE_SET_ALREADY_PRESENT;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_User_Add_Config_Reqs(UserReq *req, UserResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;

    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    UserInfo localUserConfig;
    Users *localUsers;

    int iCount;

    DLOG_NONE(" < %s ",__FUNCTION__);
    if(req->has_user())
    {
        localUsers = req->mutable_user();
        iCount = localUsers->userdata_size();
    }
    else
        iCount = 0;

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserInfo *pUserConfig = localUsers->mutable_userdata(i);

        if((iReturn = mysql_User_Add_validation(pUserConfig)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_User_Create_Check_Modifcation_Query(pUserConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_USER_ERR_DB_ERROR;

            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {
            sql_User_Create_Add_Query(pUserConfig,sStatement);
        }
        else // MOD
        {
            delete pRes;
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,ADD_USER_ERR_USERNAME_ALREADY_PRESENT);
            DLOG_ERROR("Record Already Present");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_USER_ERR_USERNAME_ALREADY_PRESENT;
        }

        delete pRes;

        if(pUserConfig->has_password())
        {
            string str(pUserConfig->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_User_Del_Config_Reqs(UserReq *req, UserResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    UserInfo localUserConfig;
    Users *localUsers;

    int iCount;

    DLOG_NONE(" < %s ",__FUNCTION__);
    if(req->has_user())
    {
        localUsers = req->mutable_user();
        iCount = localUsers->userdata_size();
    }
    else
        iCount = 0;

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserInfo *pUserConfig = localUsers->mutable_userdata(i);


        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_User_Create_Check_Modifcation_Query(pUserConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_USER_ERR_DB_ERROR;

            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,DEL_USER_ERR_USERNAME_NOT_PRESENT);
            DLOG_ERROR("Record is not present ");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_USER_ERR_USERNAME_NOT_PRESENT;
        }
        else // MOD
        {
            sql_User_Create_Delete_Query(pUserConfig,sStatement);
        }

        delete pRes;

        if(pUserConfig->has_password())
        {
            string str(pUserConfig->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_User_Mod_validation(::UserInfo *pUserInfo)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    ::Group* localGroup = pUserInfo->mutable_usergroup();
    if(localGroup->has_groupname())
    {
        sql_Role_Create_Validation_Query_for_Role(pUserInfo,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_USER_ERR_INVALID_ROLE;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_User_Mod_Config_Reqs(UserReq *req, UserResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    UserInfo localUserConfig;
    Users *localUsers;

    int iCount;

    if(req->has_user())
    {
        localUsers = req->mutable_user();
        iCount = localUsers->userdata_size();
    }
    else
        iCount = 0;

    DLOG_DEBUG(" %s: user req size  = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        UserInfo *pUserConfig = localUsers->mutable_userdata(i);

        if((iReturn = mysql_User_Mod_validation(pUserConfig)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_User_Create_Check_Modifcation_Query(pUserConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_USER_ERR_DB_ERROR;

            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,MOD_USER_ERR_USERNAME_NOT_PRESENT);
            DLOG_ERROR("Record is not present ");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_USER_ERR_USERNAME_NOT_PRESENT;
        }
        else // MOD
        {
            sql_User_Create_Mod_Query(pUserConfig,sStatement);
        }

        delete pRes;

        if(pUserConfig->has_password())
        {
            string str(pUserConfig->password().c_str(),16);
            istringstream  bInStream(str,ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,true)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

        }
        else
        {
            istringstream  bInStream("nothing",ios_base::in);
            if ((iReturn = m_dbHandle.mysql_exec_set_query_for_user_table(sStatement,&bInStream,false)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_USER_ERR_DB_ERROR;

                mysql_set_error_for_User_Config_Reqs(pUserConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

