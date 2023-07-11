/*********************************-*-C++-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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


#include "CMgrLock.h"
using namespace std;

int CnfLockMgr::CMgr_ReleaseLock(int RequestID,void *connFromCookie)
{
    DLOG_NONE(" > %s",__FUNCTION__);
    string tableName;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    tableName = CMgr_GetTable(RequestID);
    if(tableName.compare("empty") != 0)
    {
        if((iReturn = CMgr_ReleaseMysqlLock(tableName,connFromCookie)) != DRE_DB_SUCCESS)
        {
            return iReturn;
        }
    }
    else
    {
        DLOG_CRITICAL(" %s: TableMap is not created for the Request ID = %d ",__FUNCTION__,RequestID);
        return GET_LOCK_ERR_TABLE_MAP_NOT_CREATED;
    }
    DLOG_NONE(" < %s",__FUNCTION__);
    return iReturn;
}

int CnfLockMgr::CMgr_GetLock(int RequestID)
{
	DLOG_NONE(" > %s",__FUNCTION__);
	string tableName;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;

	tableName = CMgr_GetTable(RequestID);
	if(tableName.compare("empty") != 0)
	{
		DLOG_DEBUG(" %s: TableMap is created for the Request ID = %d ",__FUNCTION__,RequestID);
		if((iReturn = CMgr_GetMysqlLock(tableName)) != DRE_DB_SUCCESS)
		{
			return iReturn;
		}
	}
	else
	{
		DLOG_CRITICAL(" %s: TableMap is not created for the Request ID = %d ",__FUNCTION__,RequestID);
		return GET_LOCK_ERR_TABLE_MAP_NOT_CREATED;
	}
	DLOG_NONE(" < %s",__FUNCTION__);
	return iReturn;
}

int CnfLockMgr::CMgr_ReleaseMysqlLock(string tableName,void *connFromCookie)
{
	DLOG_NONE(" > %s",__FUNCTION__);
	sql::ResultSet *pRes = NULL;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	char sResStatement[MAX_STATEMENT_SIZE] = {0};

	memset(sStatement,0,MAX_STATEMENT_SIZE);
	memset(sResStatement,0,MAX_STATEMENT_SIZE);

	snprintf(sStatement,MAX_STATEMENT_SIZE,"SELECT RELEASE_LOCK('%s')",tableName.c_str());
	snprintf(sResStatement,MAX_STATEMENT_SIZE,"RELEASE_LOCK('%s')",tableName.c_str());
	if(connFromCookie == NULL)
	{
		DLOG_DEBUG(" %s: connFromCookie is NULL ",__FUNCTION__);
		if((iReturn=m_dbHandle->mysql_exec_get_query(sStatement,&pRes))!= DRE_DB_SUCCESS)
		{
			if(pRes != NULL)
			{
				delete pRes;
			}
			DLOG_DEBUG("Query Execution Failed");
			DLOG_NONE(" < %s",__FUNCTION__);
			return DRE_DB_FAIL;
		}
	}
	else
	{
		DLOG_DEBUG(" %s: connFromCookie is NOT NULL ",__FUNCTION__);
		if((iReturn=m_dbHandle->mysql_exec_get_query(sStatement,&pRes,connFromCookie))!= DRE_DB_SUCCESS)
		{
			if(pRes != NULL)
			{
				delete pRes;
			}
			DLOG_DEBUG("Query Execution Failed");
			DLOG_NONE(" < %s",__FUNCTION__);

			return DRE_DB_FAIL;
		}
	}
	if(pRes->next())
	{
		if(!pRes->isNull(sResStatement))
		{
			if(pRes->getInt(sResStatement) == 1)
			{
				DLOG_DEBUG(" %s: Lock Successfully released ",__FUNCTION__);
				iReturn = DRE_DB_SUCCESS;
			}
			else
			{
				DLOG_DEBUG(" %s: Lock Failed to release",__FUNCTION__);
				iReturn = DRE_DB_FAIL;
			}
		}
		else
		{
			DLOG_DEBUG(" %s: Can't be Unlocked ",__FUNCTION__);
			iReturn = DRE_DB_FAIL;
		}
	}
	else
	{
		DLOG_DEBUG(" %s: Lock is not created for table",__FUNCTION__);
		iReturn = DRE_DB_SUCCESS;
	}
	delete pRes;
	DLOG_NONE(" < %s",__FUNCTION__);
	return iReturn;
}

int CnfLockMgr::CMgr_GetMysqlLock(string tableName)
{
	DLOG_NONE(" > %s",__FUNCTION__);
	sql::ResultSet *pRes = NULL;
	DbStatus_e iReturn =  DRE_DB_SUCCESS;
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	char sResStatement[MAX_STATEMENT_SIZE] = {0};

	memset(sStatement,0,MAX_STATEMENT_SIZE);
	memset(sResStatement,0,MAX_STATEMENT_SIZE);
	snprintf(sStatement,MAX_STATEMENT_SIZE,"SELECT GET_LOCK('%s',1)",tableName.c_str());
	snprintf(sResStatement,MAX_STATEMENT_SIZE,"GET_LOCK('%s',1)",tableName.c_str());
	if((iReturn=m_dbHandle->mysql_exec_get_query(sStatement,&pRes)) !=  DRE_DB_SUCCESS)
	{
		if(pRes != NULL)
		{
			delete pRes;
		}

		if(iReturn == DRE_DB_FAIL)
			iReturn = GET_LOCK_ERR_DB_ERROR;
		DLOG_NONE(" < %s",__FUNCTION__);
		return GET_LOCK_ERR_DB_ERROR;
	}
	DLOG_NONE("sResStatement:%s",sResStatement);

	if(pRes->next())
	{
		if(!pRes->isNull(sResStatement))
		{
			if(pRes->getInt(sResStatement) != 1)
			{
				DLOG_NONE(" %s : MySQL Lock Can not be aquired (Already Taken)",__FUNCTION__);
				delete pRes;
                return GET_LOCK_ERR_RESOURSE_BUSY;
			}
		}
		DLOG_NONE(" %s : MySQL Lock aquired ",__FUNCTION__);
	}
    delete pRes;

	DLOG_NONE(" < %s",__FUNCTION__);
	return iReturn;
}

string CnfLockMgr::CMgr_GetTable(int RequestID)
{
	DLOG_NONE(" > %s",__FUNCTION__);
	string empty = "empty";
	ReqIdToTableMap::iterator it = m_RTMap.find(RequestID);
	if(it == m_RTMap.end())
	{
		DLOG_NONE(" < %s",__FUNCTION__);
		return empty;
	}
	DLOG_NONE(" < %s",__FUNCTION__);
	return (*it).second;
}

