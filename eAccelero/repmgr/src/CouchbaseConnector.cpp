/*********************************-*-CPP-*-************************************
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

#include "ReplicationConnector.h"
#include "Thread.h"
#include "Logger.h"
#include "ReplicationErrors.h"
#include "ReplicationClient.h"
#define BULK_FETCH 1
#define BULK_FETCH_REPLICA_APPEND 2


eAccelero::ThreadSpec<CouchbaseBuffer> CouchbaseConnector::cbBuffer;;
eAccelero::ThreadSpec<uint32_t> CouchbaseConnector::dataLen;
eAccelero::ThreadSpec<int32_t> CouchbaseConnector::m_ResultCode;
eAccelero::ThreadSpec<int32_t> CouchbaseConnector::m_BulkFetchStatus;
eAccelero::ThreadSpec<int32_t> CouchbaseConnector::m_atleastOneErrorOccurred;
//eAccelero::ThreadSpec<std::vector<std::string>> CouchbaseConnector::bulkData;
std::vector<std::string> CouchbaseConnector::bulkData;
void CouchbaseErrorCbk(lcb_t instance, lcb_error_t error, const char *errinfo)
{
    CLOG_ERROR("ERROR: %s (0x%x), %s",
            lcb_strerror(instance, error), error, errinfo);
    CouchbaseConnector::SetTsErrorCode((int32_t)error);
}

/*Couchbase Read callback method,*/
void CouchbaseGetEntryCbk(lcb_t instance, const void *cookie, lcb_error_t error,
        const lcb_get_resp_t *item)
{
    /*On error set the Error code*/
    if (error == LCB_SUCCESS)
    {

        //
        if(cookie && (((*((int32_t*) cookie)) == BULK_FETCH) ||(cookie && (*((int32_t*) cookie)) == BULK_FETCH_REPLICA_APPEND)))
        {

            if(*CouchbaseConnector::m_BulkFetchStatus != LCB_SUCCESS && *CouchbaseConnector::m_BulkFetchStatus != LCB_KEY_ENOENT)
            {
                // if one of the fetches fails we dont have to do anything for the rest of the fetches
                return;
            }
            CouchbaseConnector::SetBulkFetchStatus(LCB_SUCCESS);
            //DLOG_DEBUG("BULK FETCH");
            *CouchbaseConnector::m_BulkFetchStatus=(int32_t)LCB_SUCCESS;
            CLOG_DEBUG("BULK FETCH=%d",*CouchbaseConnector::m_BulkFetchStatus);
            if( ((*((int32_t*) cookie)) == BULK_FETCH))
            {

                std::string dataStr((char*)item->v.v0.bytes,(char*)item->v.v0.bytes+item->v.v0.nbytes);
            
                CouchbaseConnector::bulkData.push_back(dataStr);
            }
            else
            {
                CLOG_DEBUG("BULK FETCH WITH APPEND");
                //DLOG_DEBUG("BULK FETCH WITH APPEND");
                std::string dataStr((char*)item->v.v0.bytes,(char*)item->v.v0.bytes+item->v.v0.nbytes);
                std::string appendStr="IwfFsmState";
                appendStr.append(dataStr);
                CouchbaseConnector::bulkData.push_back(appendStr);

            }
        }
        else
        {
            CLOG_DEBUG("SINGLE FETCH");
            //copy the data got to a variable
            //  memcpy(*CouchbaseConnector::data,item->v.v0.bytes ,item->v.v0.nbytes);

            memcpy(CouchbaseConnector::cbBuffer->dataBuffer,item->v.v0.bytes ,item->v.v0.nbytes);
            //set the length
            CouchbaseConnector::SetTsDataLen(item->v.v0.nbytes);
        }
        CLOG_DEBUG("CouchbaseGetEntryCbk: key=%s,data=%s,dataLen=%d, tsDataLen=%d",item->v.v0.key,
                item->v.v0.bytes,item->v.v0.nbytes,*CouchbaseConnector::dataLen);
        CouchbaseConnector::SetTsErrorCode((int32_t)error);

    }
    else
    {
        CouchbaseConnector::SetTsDataLen(0);
        if( error != LCB_KEY_ENOENT )
        {
            *CouchbaseConnector::m_atleastOneErrorOccurred = error;
            CLOG_ERROR( "GET ERROR: %s (0x%x)",
                    lcb_strerror(instance, error), error);
        }
        if(cookie && ((*((int32_t*) cookie)) == BULK_FETCH))
        {
            
            CouchbaseConnector::SetBulkFetchStatus((int32_t)error);
        }
        else if(cookie && ((*((int32_t*) cookie)) == BULK_FETCH_REPLICA_APPEND))
        {
            //if one of the previous fetches are success dont set the error
            if( *CouchbaseConnector::m_BulkFetchStatus != LCB_SUCCESS)
            {
                CouchbaseConnector::SetBulkFetchStatus((int32_t)error);
            }
        }
        else
        {
            CouchbaseConnector::SetTsErrorCode((int32_t)error);
        }
    }
    (void)cookie;
}

/*Couchbase callback method for write/update*/
void CouchbaseNewEntryCbk(lcb_t instance, const void *cookie,
        lcb_storage_t operation,
        lcb_error_t error,
        const lcb_store_resp_t *item)
{

    if (error != LCB_SUCCESS)
    {
        if( operation == LCB_ADD )
        {
            DLOG_ERROR("Key=%s STORE ERROR: %s (0x%x)\n",item->v.v0.key,
                    lcb_strerror(instance, error), error);
        }
        else
            if( operation == LCB_REPLACE )
            {
                DLOG_ERROR("Key=%s UPDATE ERROR: %s (0x%x)\n",item->v.v0.key,
                        lcb_strerror(instance, error), error);

            }
            else
                if( operation == LCB_SET)
                {

                    DLOG_ERROR("Key=%s UPDATE ERROR: %s (0x%x)\n",item->v.v0.key,
                            lcb_strerror(instance, error), error);
                }
                else
                {
                    DLOG_ERROR("Key=%s STORE/UPDATE ERROR: %s (0x%x)\n",item->v.v0.key,
                            lcb_strerror(instance, error), error);

                }
    }
    else
    {

        CLOG_DEBUG("CouchbaseCreateEntryCbk: key=%s",item->v.v0.key);

    }
    /*Set the result code*/
    CouchbaseConnector::SetTsErrorCode((int32_t)error);
    (void)cookie;
    (void)operation;


}

/*Couchbase callback method for delete operation*/
void CouchbaseRemoveEntryCbk(lcb_t instance,
        const void* cookie,
        lcb_error_t error,
        const lcb_remove_resp_t * item)
{
    if( error != LCB_SUCCESS)
    {
        DLOG_ERROR("Key=%s DELETE ERROR: %s (0x%x)\n",item->v.v0.key,
                lcb_strerror(instance, error), error);
    }
    else
    {
        DLOG_DEBUG("key=%s DELETE SUCCESS",item->v.v0.key);
    }
    /*Set the result code*/
    CouchbaseConnector::SetTsErrorCode((int32_t)error);
    (void)cookie;
}


/*A callback which will be called when there is a configuration change
 * in the cluster*/
void ConfigCbk(lcb_t instance,lcb_configuration_t config)
{
    if(config == LCB_CONFIGURATION_NEW)
    {
        CLOG_DEBUG("NEW CONFIGURATION RECEIVED\n");
    }

    if(config == LCB_CONFIGURATION_CHANGED )
    {
        CLOG_DEBUG("CHANGED CONFIGURATION RECEIVED\n");
    }

    if(config == LCB_CONFIGURATION_UNCHANGED)
    {
        CLOG_DEBUG("CONFIGURATION UNCHANGED\n");
    }


}

/*Attempts connection to the specified server*/
int32_t CouchbaseConnector::Connect()
{

    *CouchbaseConnector::m_ResultCode=SUCCESS;
    lcb_error_t err;
    struct lcb_create_st create_options;
    struct lcb_create_io_ops_st io_opts;

    io_opts.version = 0;
    io_opts.v.v0.type = LCB_IO_OPS_DEFAULT;
    io_opts.v.v0.cookie = NULL;

    memset(&create_options, 0, sizeof(create_options));
    err = lcb_create_io_ops(&create_options.v.v0.io, &io_opts);
    if (err != LCB_SUCCESS)
    {
        DLOG_ERROR("Failed to create IO instance: %s",
                lcb_strerror(NULL, err));
        return err;
    }

    create_options.v.v0.host=serverAddress.c_str();
    //    create_options.v.v0.user = userName.c_str();
    create_options.v.v0.bucket = bucketName.c_str();
    create_options.v.v0.passwd = password.c_str();

    err = lcb_create(&instance, &create_options);
    if (err != LCB_SUCCESS)
    {
        DLOG_ERROR("Failed to create libcouchbase instance: %s",
                lcb_strerror(NULL, err));
        return err;
    }

    (void)lcb_set_error_callback(instance,CouchbaseErrorCbk);
    /* Initiate the connect sequence in libcouchbase */
    if ((err = lcb_connect(instance)) != LCB_SUCCESS)
    {
        DLOG_ERROR("Failed to initiate connect: %s",
                lcb_strerror(NULL, err));
        lcb_destroy(instance);
        return err;
    }
    else
    {
        DLOG_INFO("Initiating connection to couchbase server:<%s>,bucket:<%s>",serverAddress.c_str(),bucketName.c_str());
    }

    lcb_wait(instance);

    /*set the mode to synchronous if syncMode is set to true*/
    if(syncMode)
    {
        DLOG_DEBUG("Setting ReplicationConnector %p to synchronous mode",this);
        lcb_behavior_set_syncmode(instance, LCB_SYNCHRONOUS);
    }


    /*Register the callback functions*/
    (void)lcb_set_get_callback(instance, CouchbaseGetEntryCbk);
    (void)lcb_set_store_callback(instance, CouchbaseNewEntryCbk);
    (void)lcb_set_remove_callback(instance, CouchbaseRemoveEntryCbk);
    (void)lcb_set_configuration_callback(instance,ConfigCbk);
    lcb_wait(instance);
    if( *CouchbaseConnector::m_ResultCode != SUCCESS)
    {
        return *CouchbaseConnector::m_ResultCode;
    }
    else
    {
        return LCB_SUCCESS;
    }
}


int32_t CouchbaseConnector::Disconnect()
{
    if(connState == DISCONNECTED)
    {
        CLOG_WARNING("Connection %p is already disconnected!",this);
        return LCB_SUCCESS;
    }
    CLOG_DEBUG("Disconnecting connection %p", this);
    lcb_destroy(instance);
    connState=DISCONNECTED;
    return LCB_SUCCESS;
}

int32_t CouchbaseConnector::CreateEntry(std::string key, void *entry, uint32_t entryLen,bool lcbWait, uint32_t expiryTime)
{
    if(connState == DISCONNECTED)
    {
        CLOG_ERROR("Connection inactive!");
        return !LCB_SUCCESS;
    }

    int32_t ret=LCB_SUCCESS;
    lcb_store_cmd_t cmd;
    const lcb_store_cmd_t *commands[1];
    lcb_error_t err;
    /*Prepare the command for insert operation*/
    commands[0] = &cmd;
    memset(&cmd, 0, sizeof(cmd));
    //cmd.v.v0.operation = LCB_ADD;
    cmd.v.v0.operation = LCB_SET;
    cmd.v.v0.key = key.c_str();
    cmd.v.v0.nkey = key.length();
    cmd.v.v0.bytes = entry;
    cmd.v.v0.nbytes = entryLen;
    // Set the Time to live for the entry
    cmd.v.v0.exptime = expiryTime;
    /*If previous operation failed, call lcb_wait which will slow down the operations*/
    if( *m_ResultCode != LCB_SUCCESS)
    {
        if( (*m_ResultCode == LCB_NETWORK_ERROR) || (*m_ResultCode == LCB_ETIMEDOUT) ||
                *m_ResultCode == LCB_CONNECT_ERROR)
        {
            lcb_wait(instance);
        }
    }

    err = lcb_store(instance, NULL, 1, commands);
    if (err != LCB_SUCCESS)
    {
        DLOG_ERROR("Failed to create entry for key %s: %s",key.c_str(), lcb_strerror(NULL, err));
        return err;
    }

    if(lcbWait)
    {
        lcb_wait(instance);
    }


    if( *m_ResultCode == LCB_SUCCESS)
    {
	ret=*m_ResultCode;
    }
    else
    {
	ret=*m_ResultCode;
    }


    if( *m_ResultCode == LCB_SUCCESS)
    {
    }
    else
    {
    }


    return ret;
}

int32_t CouchbaseConnector::SetOperationTimeout(int32_t uSecTimeout)
{
    CLOG_DEBUG("Set operation timeout for %p to %d usec",this,uSecTimeout);
//    lcb_set_timeout(instance, uSecTimeout);
    return 0;
}

int32_t CouchbaseConnector::UpdateEntry(std::string key, void *entry, uint32_t entryLen,bool lcbWait, uint32_t expiryTime)
{
    if(connState == DISCONNECTED)
    {
        CLOG_ERROR("Connection inactive!");
        return !LCB_SUCCESS;
    }

    int32_t ret=LCB_SUCCESS;
    lcb_store_cmd_t cmd;
    const lcb_store_cmd_t *commands[1];
    lcb_error_t err;
    /*Prepare the commad for update operation*/
    commands[0] = &cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.v.v0.operation = LCB_SET;
    cmd.v.v0.key = key.c_str();
    cmd.v.v0.nkey = key.length();
    cmd.v.v0.bytes = entry;
    cmd.v.v0.nbytes = entryLen;
    // Set the Time to live for the entry
    cmd.v.v0.exptime = expiryTime;
    /*If there is any error with the previous operation call lcb_wait and slow down*/
    if( *m_ResultCode != LCB_SUCCESS)
    {
        if( (*m_ResultCode == LCB_NETWORK_ERROR) || (*m_ResultCode == LCB_ETIMEDOUT) ||
                *m_ResultCode == LCB_CONNECT_ERROR)
        {
            lcb_wait(instance);
        }
    }

    err = lcb_store(instance, NULL, 1, commands);
    if (err != LCB_SUCCESS)
    {
        DLOG_ERROR("Failed to update entry for key %s: %s",key.c_str(), lcb_strerror(NULL, err));


        return err;
    }

    if(lcbWait)
    {
        lcb_wait(instance);
    }

    if( *m_ResultCode == LCB_SUCCESS)
    {
	ret=*m_ResultCode;
    }
    else
    {
	ret=*m_ResultCode;
    }

    if( *m_ResultCode == LCB_SUCCESS)
    {
    }
    else
    {
    }

    return ret;
}

int32_t CouchbaseConnector::DeleteEntry(std::string key,bool lcbWait)
{
    if(connState == DISCONNECTED)
    {
        CLOG_ERROR("Connection inactive!");
        return !LCB_SUCCESS;
    }

    int32_t ret=LCB_SUCCESS;
    lcb_error_t err;
    /*prepare the remove command from the passed key string*/
    lcb_remove_cmd_t cmd;
    const lcb_remove_cmd_t *commands[1];
    commands[0] = &cmd;
    cmd.v.v0.key = key.c_str();
    cmd.v.v0.nkey = key.length();
    /*If previous operation failed, call lcb_wait which will slow down the operations*/
    if( *m_ResultCode != LCB_SUCCESS)
    {
        if( (*m_ResultCode == LCB_NETWORK_ERROR) || (*m_ResultCode == LCB_ETIMEDOUT) ||
                *m_ResultCode == LCB_CONNECT_ERROR)
        {
            lcb_wait(instance);
        }
    }
    DLOG_DEBUG("cmd.v.v0.key =%s",cmd.v.v0.key);
    DLOG_DEBUG("Length cmd.v.v0.nkey=%d",cmd.v.v0.nkey);
    err = lcb_remove(instance, NULL, 1, commands);
    if (err != LCB_SUCCESS)
    {

        DLOG_ERROR("Failed to delete entry for key %s: %s",key.c_str(), lcb_strerror(NULL, err));
        return err;
    }

    if(lcbWait)
    {
        lcb_wait(instance);
    }


    if( *m_ResultCode == LCB_SUCCESS)
    {
        ret=*m_ResultCode;
    }
    else
    {
        ret=*m_ResultCode;
    }

    return ret;
}

int32_t CouchbaseConnector::GetBulkEntries(std::vector<std::string> &keys, std::vector<std::string> &outData,bool appendReplicaName)
{
    int32_t cookie=BULK_FETCH;
    *m_BulkFetchStatus=(int32_t)LCB_KEY_ENOENT;
    *m_atleastOneErrorOccurred = LCB_SUCCESS;

    if(appendReplicaName)
    {
        cookie=BULK_FETCH_REPLICA_APPEND;
    }
    CouchbaseConnector::bulkData.clear();
    if(connState == DISCONNECTED)
    {
        CLOG_ERROR("Connection %p inactive!",this);
        return !LCB_SUCCESS;
    }

    //Serialize deserializeObj;
    //int32_t ret=LCB_SUCCESS;
    lcb_error_t err;
    lcb_get_cmd_t cmd[MAX_BULK_FETCH_SIZE];
    /*Prepare the command for read operation*/
    const lcb_get_cmd_t *commands[MAX_BULK_FETCH_SIZE];

    CLOG_DEBUG("Key Size=%d",keys.size());
    for(uint32_t i=0 ; i<keys.size(); i++)
    {
        //CLOG_DEBUG("i=%d, str=%s len=%d",i,keys[i].c_str(),keys[i].length());
        
        commands[i] = &cmd[i];
        memset(&cmd[i], 0, sizeof(cmd[i]));
        cmd[i].v.v0.key = keys[i].c_str();
        cmd[i].v.v0.nkey = keys[i].length();

    }
        /*If previous operation failed, call lcb_wait which will slow down the operations*/
    if( *m_ResultCode != LCB_SUCCESS)
    {
        if( (*m_ResultCode == LCB_NETWORK_ERROR) || (*m_ResultCode == LCB_ETIMEDOUT) ||
                *m_ResultCode == LCB_CONNECT_ERROR)
        {
            lcb_wait(instance);
        }
    }

    err = lcb_get(instance, &cookie, keys.size(), commands);
    if (err != LCB_SUCCESS)
    {
        if(err != LCB_KEY_ENOENT)
        {
            CLOG_ERROR("Failed to get entry %s", lcb_strerror(NULL, err));
            if(*m_BulkFetchStatus != LCB_SUCCESS && *m_BulkFetchStatus != LCB_KEY_ENOENT)
            {
                //*outEntryLen=0;
                CLOG_DEBUG("res=%d",*m_BulkFetchStatus);
                return *m_BulkFetchStatus;
            }
        }

        //CLOG_DEBUG("%s: %s",key.c_str(), lcb_strerror(NULL, err));
    }
    lcb_wait(instance);

    if(*m_BulkFetchStatus != LCB_SUCCESS && *m_BulkFetchStatus != LCB_KEY_ENOENT)
    {
        //*outEntryLen=0;
        CLOG_DEBUG("res=%d",*m_BulkFetchStatus);
        return *m_BulkFetchStatus;
    }

    if (*m_atleastOneErrorOccurred)
    {
        return *m_atleastOneErrorOccurred;
    }

    //memcpy(outEntry,cbBuffer->dataBuffer,dataLen);
    //*outEntryLen=dataLen;
    outData=CouchbaseConnector::bulkData;
    return *m_BulkFetchStatus;

}


int32_t CouchbaseConnector::GetEntry(std::string key, void *outEntry, uint32_t *outEntryLen)
{
    if(connState == DISCONNECTED)
    {
        CLOG_ERROR("Connection inactive!");
        return !LCB_SUCCESS;
    }

    //Serialize deserializeObj;
    int32_t ret=LCB_SUCCESS;
    lcb_error_t err;
    lcb_get_cmd_t cmd;
    /*Prepare the command for read operation*/
    const lcb_get_cmd_t *commands[1];
    commands[0] = &cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.v.v0.key = key.c_str();
    cmd.v.v0.nkey = key.length();
    /*If previous operation failed, call lcb_wait which will slow down the operations*/
    if( *m_ResultCode != LCB_SUCCESS)
    {
        if( (*m_ResultCode == LCB_NETWORK_ERROR) || (*m_ResultCode == LCB_ETIMEDOUT) ||
                *m_ResultCode == LCB_CONNECT_ERROR)
        {
            lcb_wait(instance);
        }
    }

    err = lcb_get(instance, NULL, 1, commands);
    if (err != LCB_SUCCESS)
    {
        if(err != LCB_KEY_ENOENT)
        {
            CLOG_ERROR("Failed to get entry for key %s: %s",key.c_str(), lcb_strerror(NULL, err));
        }

        CLOG_DEBUG("%s: %s",key.c_str(), lcb_strerror(NULL, err));
        return err;
    }
    //lcb_wait(instance);

    if(*m_ResultCode != SUCCESS)
    {

        *outEntryLen=0;
        CLOG_DEBUG("res=%d",*m_ResultCode);
        return *m_ResultCode;
    }

    CLOG_DEBUG("-DataLen=%d",*dataLen);
    memcpy(outEntry,cbBuffer->dataBuffer,*dataLen);
    *outEntryLen=*dataLen;

    return ret;

}

//overloaded method for Non POD data
int32_t CouchbaseConnector::GetEntry(std::string key, std::string &outEntry, uint32_t *outEntryLen)
{
    if(connState == DISCONNECTED)
    {
        CLOG_ERROR("Connection inactive!");
        return !LCB_SUCCESS;
    }

    //Serialize deserializeObj;
    int32_t ret=LCB_SUCCESS;
    lcb_error_t err;
    lcb_get_cmd_t cmd;
    /*Prepare the command for read operation*/
    const lcb_get_cmd_t *commands[1];
    commands[0] = &cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.v.v0.key = key.c_str();
    cmd.v.v0.nkey = key.length();
    /*If previous operation failed, call lcb_wait which will slow down the operations*/
    if( *m_ResultCode != LCB_SUCCESS)
    {
        if( (*m_ResultCode == LCB_NETWORK_ERROR) || (*m_ResultCode == LCB_ETIMEDOUT) ||
                *m_ResultCode == LCB_CONNECT_ERROR)
        {
            lcb_wait(instance);
        }
    }

    err = lcb_get(instance, NULL, 1, commands);
    if (err != LCB_SUCCESS)
    {
        if(err != LCB_KEY_ENOENT)
        {
            CLOG_ERROR("Failed to get entry for key %s: %s",key.c_str(), lcb_strerror(NULL, err));
        }
        return err;
    }
    //lcb_wait(instance);

    if(*m_ResultCode != SUCCESS)
    {

        *outEntryLen=0;
        return *m_ResultCode;
    }

    outEntry=(char*)cbBuffer->dataBuffer;
    *outEntryLen=*dataLen;

    return ret;

}



/*Function to get the list of all the servers in the cluster*/
int32_t CouchbaseConnector::GetServerList(std::string &serverList)
{

    DLOG_DEBUG("Getting server list from the cluster...");
    int ret=SUCCESS;
    if((ret=Connect())!= SUCCESS)
    {
        DLOG_ERROR("Connection failed to the cluster!");
        return ret;
    }
    else
    {
        SetConnectionState(CONNECTED);
    }

    const char *const *servers = lcb_get_server_list(instance);

    for (int ii = 0; servers[ii] != NULL; ii++)
    {
        serverList.append( servers[ii]) ;
        serverList.append(";");
    }

    return ret;
}










