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


#include "MysqlInterfacePB.h"

using namespace std;
using namespace eAccelero;

MysqlInterfacePB::MysqlInterfacePB(string sHostName,string sUserName,string sPassword,string sDataBase,ConfigManagerAlarms *pConfigManagerAlarms)
{
    DLOG_NONE("%s:%d",__FUNCTION__,__LINE__);

    m_ConfigManagerAlarms = pConfigManagerAlarms;

    cur_con=NULL;
    for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
    {
        connectionlist[i].con = NULL;
        connectionlist[i].status = true;
    }

    try
    {

        DLOG_INFO("%s:%d Started Creating Connnection to Mysql",__FUNCTION__,__LINE__);
        driver = sql::mysql::get_driver_instance();

        connection_properties["hostName"]=sHostName;
        connection_properties["userName"]=sUserName;
        connection_properties["password"]=sPassword;
        connection_properties["OPT_RECONNECT"]=true;
        connection_properties["schema"]=sDataBase;

        for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
        {
            DLOG_INFO("%s:%d Created Mysql connection :%d",__FUNCTION__,__LINE__,i+1);
            connectionlist[i].con = driver->connect(connection_properties);
            connectionlist[i].status = false;
                DLOG_NONE("Connection %p - status[%d] %d ",connectionlist[i].con,i,connectionlist[i].status);
        }

        DLOG_INFO("%s:%d Mysql Conncection is ready",__FUNCTION__,__LINE__);
        mysql_conn_pool_status = true;
        connectedToLocalHost = true;
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        try
        {
            sHostName=LOCAL_HOST_IP;
            connection_properties["hostName"]=sHostName;
            DLOG_DEBUG("Connecting to 127.0.0.1");
            for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
            {
                DLOG_INFO("%s:%d Created Mysql connection :%d",__FUNCTION__,__LINE__,i+1);
                connectionlist[i].con = driver->connect(connection_properties);
                connectionlist[i].status = false;
                DLOG_NONE("Connection %p - status[%d] %d ",connectionlist[i].con,i,connectionlist[i].status);
            }

            DLOG_INFO("%s:%d Mysql Conncection is ready",__FUNCTION__,__LINE__);
            mysql_conn_pool_status = true;
            connectedToLocalHost = true;

        }
        catch(sql::SQLException &e)
        {
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());

        exit(0);
    }
    }
    DLOG_DEBUG("Reached End!");
    DLOG_NONE("%s:%d",__FUNCTION__,__LINE__);
}

MysqlInterfacePB::~MysqlInterfacePB()
{
    PRINTF("%s:%d\n",__FUNCTION__,__LINE__);

    mysql_close_all_connection();

    PRINTF("%s:%d\n",__FUNCTION__,__LINE__);
}

DbStatus_e MysqlInterfacePB::mysql_close_all_connection()
{
    DLOG_NONE(" > %s \n",__FUNCTION__);
    int iFailed = 0;
    int iSuccess = 0;

    if(!mysql_conn_pool_status)
        return DRE_DB_SUCCESS;

    mysql_conn_pool_status = false;
    for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
    {
        try
        {
            if(connectionlist[i].con)
            {
                connectionlist[i].con->close();
                connectionlist[i].status = false;
                delete connectionlist[i].con;
                connectionlist[i].con = NULL;

            }
            else
            {
                DLOG_DEBUG("Connection object is not set");
            }
            iSuccess++;
        }
        catch (sql::SQLException &e)
        {
            DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
            DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
            iFailed++;
        }
    }

    if(!iFailed)
        DLOG_CRITICAL("Failed to close %d Number of Mysql Connection",iFailed);

    DLOG_INFO("Successfully closed %d Number of Mysql Connection",iSuccess);

    DLOG_NONE(" < %s \n",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

int MysqlInterfacePB::mysql_reconnect_connection()
{
    DLOG_DEBUG(">>> MysqlInterfacePB::mysql_reconnect_connection >>>");
    DLOG_NONE(" > %s \n",__FUNCTION__);
    int iSuccess = 0;

    mysql_close_all_connection();
    try
    {
        if(!driver)
            driver = sql::mysql::get_driver_instance();

        for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
        {
            connectionlist[i].con = driver->connect(connection_properties);
            connectionlist[i].status = false;
            DLOG_NONE("Connection %p - status[%d] %d ",connectionlist[i].con,i,connectionlist[i].status);
            iSuccess++;
        }


    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
    }

    if (iSuccess)
        mysql_conn_pool_status = true;

    DLOG_NONE(" < %s \n",__FUNCTION__);
    DLOG_DEBUG("<<<< MysqlInterfacePB::mysql_reconnect_connection <<<<");
    return iSuccess;
}

DbStatus_e MysqlInterfacePB::mysql_set_current_connection()
{
    int iFlag = 0;
    DLOG_NONE(" > %s \n",__FUNCTION__);
    if (!mysql_conn_pool_status)
    {
        if(mysql_reconnect_connection()  == 0)
        {
            DLOG_ERROR("Failed to get the Connection from the Connection Pool ");
            DLOG_NONE(" < %s \n",__FUNCTION__);
            return DRE_DB_FAIL;
        }
    }

    for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
    {
        DLOG_NONE("Connection %p - status[%d] %d ",connectionlist[i].con,i,connectionlist[i].status);
        if(!connectionlist[i].status)
        {
            iFlag = 1;
            cur_con = connectionlist[i].con;
            connectionlist[i].status = true;
            break;
        }
    }

    if(!iFlag)
    {
        DLOG_ERROR("Failed to get the Connection from the Connection Pool ");
        DLOG_NONE(" < %s \n",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    else
    {
        DLOG_NONE(" < %s \n",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }
}


void MysqlInterfacePB::mysql_release_current_connection()
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    try
    {
        for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
        {
            if(connectionlist[i].con == cur_con && connectionlist[i].status)
            {
                connectionlist[i].status = false;

                if(!cur_con->isClosed())
                    cur_con->setAutoCommit(true);

                cur_con = NULL;
                break;
            }
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
    }
    DLOG_NONE(" < %s \n",__FUNCTION__);
}


DbStatus_e MysqlInterfacePB::mysql_unset_connection(sql::Connection *con)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);
    int iFlag = 0;
    for(int i=0;i<MAX_MYSQL_CONNECTION;i++)
    {
        if(connectionlist[i].status)
        {
            if(connectionlist[i].con == con)
            {
                iFlag = 1;
                try
                {
                    con->setAutoCommit(true);
                }
                catch (sql::SQLException &e)
                {

                    DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
                    DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
                }
                connectionlist[i].status = false;
                break;
            }
        }
    }

    if(!iFlag)
    {
        DLOG_ERROR("Failed to release the Connection from the Connection Pool ");
        DLOG_NONE(" < %s \n",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    else
    {
        DLOG_NONE(" < %s \n",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }
}

void* MysqlInterfacePB::mysql_get_current_connection()
{
    DLOG_NONE(" > %s \n",__FUNCTION__);
    return (void*)cur_con;
    DLOG_NONE(" < %s \n",__FUNCTION__);
}

DbStatus_e MysqlInterfacePB::mysql_exec_commit(void *conFromCookie)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);
    try
    {
        sql::Connection *con = (sql::Connection*)conFromCookie;

        /* Validation: Status of the connection taken from cookie
         */
        int iFlag = 0;
        for(int iIndex = 0; iIndex<MAX_MYSQL_CONNECTION; iIndex++)
        {
            if(con == connectionlist[iIndex].con)
            {
                iFlag = 1;
                if(connectionlist[iIndex].status == false)
                {
                    DLOG_DEBUG("%s:%d MySQL went down\n",__FUNCTION__,__LINE__);
                    return DRE_DB_FAIL;
                }
                else
                {
                    break;
                }
            }
        }

        if(!iFlag)
        {
            DLOG_WARNING("Connection is deleted..");
            return DRE_DB_FAIL;
        }

        if(!con->isClosed())
            con->commit();
        else
        {
            DLOG_ERROR("Connection is Closed");
            return DRE_DB_FAIL;
        }

        if(mysql_unset_connection(con) == DRE_DB_SUCCESS)
            DLOG_INFO("%s:%d Successfully unset connection flag\n",__FUNCTION__,__LINE__);
        else
            DLOG_ERROR("%s:%d falied to unset connection flag\n",__FUNCTION__,__LINE__);


    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s \n",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s \n",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e MysqlInterfacePB::mysql_exec_rollback(void *conFromCookie)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);
    try
    {
        sql::Connection *con = (sql::Connection*)conFromCookie;

        /* Validation: Status of the connection taken from cookie
         */
        int iFlag = 0;
        for(int iIndex = 0; iIndex<MAX_MYSQL_CONNECTION; iIndex++)
        {
            if(con == connectionlist[iIndex].con)
            {
                iFlag = 1;
                if(connectionlist[iIndex].status == false)
                {
                    DLOG_DEBUG("%s:%d MySQL went down\n",__FUNCTION__,__LINE__);
                    return DRE_DB_FAIL;
                }
                else
                {
                    break;
                }
            }
        }

        if(!iFlag)
        {
            DLOG_WARNING("Connection is deleted..");
            return DRE_DB_FAIL;
        }

        if(!con->isClosed())
            con->rollback();
        else
        {
            DLOG_ERROR("Connection is Closed");
            return DRE_DB_FAIL;
        }

        if(mysql_unset_connection(con) == DRE_DB_SUCCESS)
            DLOG_INFO("%s:%d Successfully unset connection flag\n",__FUNCTION__,__LINE__);
        else
            DLOG_ERROR("%s:%d falied to unset connection flag\n",__FUNCTION__,__LINE__);
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());

        DLOG_NONE(" < %s \n",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s \n",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e MysqlInterfacePB::mysql_exec_set_query(char *pStatement)
{
    sql::Statement              *pStmt =  NULL;
    static int iRecursiveCount = 0;


    DLOG_NONE(" > %s \n",__FUNCTION__);
    try
    {
        DLOG_INFO("Query Statement: %s\n",pStatement);
        cur_con->setAutoCommit(false);
        pStmt   = cur_con->createStatement();

        if(pStmt != NULL)
        {
            pStmt->execute(pStatement);
            delete pStmt;
        }
        else
        {
            DLOG_CRITICAL("Database Connection is Invalid");
            iRecursiveCount = 0;
            return DRE_DB_FAIL;
        }

    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());

        if(mysql_check_error_code(e.getErrorCode()) == DRE_DB_FAIL)
        {
            if(iRecursiveCount == MAX_RETRY_CONNECTION)
            {
                    iRecursiveCount = 0;
                    return CONFIG_COMMON_ERR_DB_CONNECTION_REESTABLISH;
            }

            if(mysql_reconnect_connection() == 0)
            {
                DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
                DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
                iRecursiveCount = 0;
                return CONFIG_COMMON_ERR_DB_CONNECTION_FAILED;
            }
            else
            {
                DLOG_INFO("Mysql Reconnect Successfull, Execute command once again !!!!");
                mysql_release_current_connection();
                mysql_set_current_connection();
                iRecursiveCount++;
                return mysql_exec_set_query(pStatement);
            }
        }

        if (pStmt != NULL)
            delete pStmt;

        DLOG_NONE(" < %s \n",__FUNCTION__);
        iRecursiveCount = 0;
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s \n",__FUNCTION__);
    iRecursiveCount = 0;
    return DRE_DB_SUCCESS;
}

DbStatus_e MysqlInterfacePB::mysql_exec_and_check_get_query(char *pStatement)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if((iReturn = mysql_exec_get_query(pStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",pStatement);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(pRes->rowsCount() == 0)
    {
        DLOG_DEBUG(" set iReturn to DRE_DB_FAIL %s ",__FUNCTION__);
        iReturn =  DRE_DB_FAIL;
    }
    else
    {
        DLOG_DEBUG(" set iReturn to DRE_DB_SUCCESS %s ",__FUNCTION__);
        iReturn =  DRE_DB_SUCCESS;
    }

    delete pRes;
    DLOG_NONE(" < %s \n",__FUNCTION__);
    return iReturn;
}

DbStatus_e MysqlInterfacePB::mysql_exec_get_query(char *pStatement,sql::ResultSet **pRes,void *connFromCookie)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    sql::PreparedStatement              *pPreStmt = NULL;
    static int iRecursiveCount = 0;
    sql::Connection *con;

    if(connFromCookie != NULL)
    {
        con  = (sql::Connection*)connFromCookie;
        DLOG_DEBUG(" Taking Conn from the variable ");

    }
    else
    {
        DLOG_DEBUG(" Connection should already set..");
        con = cur_con;
    }

    /* Validation: Status of the connection taken from cookie
    */
    int iFlag = 0;
    for(int iIndex = 0; iIndex<MAX_MYSQL_CONNECTION; iIndex++)
    {
        if(con == connectionlist[iIndex].con)
        {
            iFlag = 1;
            if(connectionlist[iIndex].status == false)
            {
                DLOG_DEBUG("%s:%d MySQL went down\n",__FUNCTION__,__LINE__);
                return DRE_DB_FAIL;
            }
            else
            {
                break;
            }
        }
    }

    if(!iFlag)
    {
        DLOG_WARNING("Connection is deleted..");
        return DRE_DB_FAIL;
    }


    try
    {
        DLOG_INFO("Query Statement: %s\n",pStatement);
        pPreStmt    = con->prepareStatement(pStatement);

        if(pPreStmt!= NULL)
        {
            *pRes       = pPreStmt->executeQuery();
            pPreStmt->close();
            delete pPreStmt;
        }
        else
        {
            DLOG_CRITICAL("Database Connection is Invalid");
            DLOG_NONE(" < %s \n",__FUNCTION__);
            iRecursiveCount = 0;
            return DRE_DB_FAIL;
        }

    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());

        if(mysql_check_error_code(e.getErrorCode()) == DRE_DB_FAIL)
        {
            if(iRecursiveCount == MAX_RETRY_CONNECTION)
            {
                    iRecursiveCount = 0;
                    return CONFIG_COMMON_ERR_DB_CONNECTION_REESTABLISH;
            }

            if(mysql_reconnect_connection() == 0)
            {
                DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
                DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
                iRecursiveCount = 0;
                return CONFIG_COMMON_ERR_DB_CONNECTION_FAILED;
            }
            else
            {
                DLOG_INFO("Mysql Reconnect Successfull, Execute command once again !!!!");
                mysql_release_current_connection();
                mysql_set_current_connection();
                iRecursiveCount++;
                return mysql_exec_get_query(pStatement,pRes,connFromCookie);
            }
        }

        if (pPreStmt != NULL)
        {
            pPreStmt->close();
            delete pPreStmt;
        }
        DLOG_NONE(" < %s \n",__FUNCTION__);
        iRecursiveCount = 0;
        return DRE_DB_FAIL;
    }


    DLOG_NONE(" < %s \n",__FUNCTION__);
    iRecursiveCount = 0;
    return DRE_DB_SUCCESS;
}


DbStatus_e MysqlInterfacePB::mysql_exec_set_query_for_user_table(char *pStatement,istringstream *encryptPassword,bool PasswordIsSet)
{
    sql::PreparedStatement              *pPreStmt = NULL;
    static int iRecursiveCount = 0;

    DLOG_NONE(" > %s \n",__FUNCTION__);
    try
    {
        DLOG_INFO("Query Statement: %s\n",pStatement);
        cur_con->setAutoCommit(false);
        pPreStmt    = cur_con->prepareStatement(pStatement);
        if(pPreStmt!= NULL)
        {
            if(PasswordIsSet)
                pPreStmt->setBlob(1,encryptPassword);

            pPreStmt->execute();
            pPreStmt->close();
            delete pPreStmt;
        }
        else
        {
            DLOG_CRITICAL("Database Connection is Invalid");
            DLOG_NONE(" < %s \n",__FUNCTION__);
            iRecursiveCount = 0;
            return DRE_DB_FAIL;
        }

        DLOG_NONE("%s:%d \n",__FUNCTION__,__LINE__);

    }
    catch (sql::SQLException &e)
    {

        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());

        if(mysql_check_error_code(e.getErrorCode()) == DRE_DB_FAIL)
        {
            if(iRecursiveCount == MAX_RETRY_CONNECTION)
            {
                    iRecursiveCount = 0;
                    return CONFIG_COMMON_ERR_DB_CONNECTION_REESTABLISH;
            }

            if(mysql_reconnect_connection() == 0)
            {
                DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
                DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
                iRecursiveCount = 0;
                return CONFIG_COMMON_ERR_DB_CONNECTION_FAILED;
            }
            else
            {
                DLOG_INFO("Mysql Reconnect Successfull, Execute command once again !!!!");
                mysql_release_current_connection();
                mysql_set_current_connection();
                iRecursiveCount++;
                return mysql_exec_set_query_for_user_table(pStatement,encryptPassword,PasswordIsSet);
            }
        }

        if (pPreStmt != NULL)
        {
            pPreStmt->close();
            delete pPreStmt;
        }

        DLOG_NONE(" < %s \n",__FUNCTION__);
        iRecursiveCount = 0;
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s \n",__FUNCTION__);
    iRecursiveCount = 0;
    return DRE_DB_SUCCESS;
}

DbStatus_e MysqlInterfacePB::mysql_exec_get_query_for_user_table(char *pStatement,sql::ResultSet **pRes,istringstream *encryptPassword,bool PasswordIsSet)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    sql::PreparedStatement              *pPreStmt = NULL;
    static int iRecursiveCount = 0;

    try
    {
        DLOG_INFO("Query Statement: %s\n",pStatement);
        pPreStmt    = cur_con->prepareStatement(pStatement);

        if(pPreStmt!= NULL)
        {
            if(PasswordIsSet)
                pPreStmt->setBlob(1,encryptPassword);

            *pRes       = pPreStmt->executeQuery();
            pPreStmt->close();
            delete pPreStmt;
        }
        else
        {
            DLOG_CRITICAL("Database Connection is Invalid");
            DLOG_NONE(" < %s \n",__FUNCTION__);
            iRecursiveCount = 0;
            return DRE_DB_FAIL;
        }


    }
    catch (sql::SQLException &e)
    {

        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        if(mysql_check_error_code(e.getErrorCode()) == DRE_DB_FAIL)
        {
            if(iRecursiveCount == MAX_RETRY_CONNECTION)
            {
                    iRecursiveCount = 0;
                    return CONFIG_COMMON_ERR_DB_CONNECTION_REESTABLISH;
            }

            if(mysql_reconnect_connection() == 0)
            {
                DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
                DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
                iRecursiveCount = 0;
                return CONFIG_COMMON_ERR_DB_CONNECTION_FAILED;
            }
            else
            {
                DLOG_INFO("Mysql Reconnect Successfull, Execute command once again !!!!");
                mysql_release_current_connection();
                mysql_set_current_connection();
                iRecursiveCount++;
                return mysql_exec_get_query_for_user_table(pStatement,pRes,encryptPassword,PasswordIsSet);
            }
        }

        if (pPreStmt != NULL)
        {
            pPreStmt->close();
            delete pPreStmt;
        }
        DLOG_NONE(" < %s \n",__FUNCTION__);
        iRecursiveCount = 0;
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s \n",__FUNCTION__);
    iRecursiveCount = 0;
    return DRE_DB_SUCCESS;
}

DbStatus_e MysqlInterfacePB::mysql_exec_get_resultset_count(char *pStatement,sql::ResultSet **pRes,int *iCount)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if((iReturn = mysql_exec_get_query(pStatement,pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)
        {
            delete pRes;
            pRes = NULL;
        }
        DLOG_ERROR("Query Execution Failed %s",pStatement);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    *iCount = (*pRes)->rowsCount();
    DLOG_DEBUG("Query Execution iCount = %d",*iCount);

    DLOG_NONE(" > %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e MysqlInterfacePB::mysql_check_error_code(int iMysqlErrorCode)
{
    DLOG_NONE(" > %s \n",__FUNCTION__);

    if(iMysqlErrorCode == 2002)
            return DRE_DB_FAIL;
    else if(iMysqlErrorCode == 2003)
            return DRE_DB_FAIL;
    else if(iMysqlErrorCode == 2005)
            return DRE_DB_FAIL;
    else if(iMysqlErrorCode == 2006)
            return DRE_DB_FAIL;
    else if(iMysqlErrorCode == 2013)
            return DRE_DB_FAIL;
    else if(iMysqlErrorCode == 2048)
            return DRE_DB_FAIL;
    else if(iMysqlErrorCode == 2055)
            return DRE_DB_FAIL;
    else
            return DRE_DB_SUCCESS;
    DLOG_NONE(" < %s \n",__FUNCTION__);
}

void MysqlInterfacePB::mysql_set_connection_hostname(std::string hostname)
{
        DLOG_DEBUG("RESETTING CONNECTION HOSTNAME:%s",hostname.c_str());
            connection_properties.erase("hostName");
                connection_properties["hostName"]=hostname;
}

bool MysqlInterfacePB::isConnectedToLocalHost()
{
        return connectedToLocalHost;
}

void MysqlInterfacePB::setLocalHostConnectionFlag(bool isLocal)
{
        connectedToLocalHost=isLocal;
}

