/*******************************-*-CPP-*-***********************************
 *                                                                          *
 *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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

#include "pbReplicationUtils.h"
#include <sstream>

int ReplicableData::CreateEntryInReplica(std::string replicaName, std::string sessionKey, uint32_t expiryTime)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::CreateEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("CreateEntryInReplica => replicaName :%s, sessionKey :%s, replicableData :%s", replicaName.c_str(),
                                                            sessionKey.c_str(), replicableData->DebugString().c_str());

    char data [MAX_PB_DATA_LEN] = {0};
    int size = replicableData->ByteSize();
    // Serialize to an array.
    replicableData->SerializeToArray(data, size);

    CLOG_DEBUG("replicableData size :%d", size);
    //CLOG_DEBUG("Serialized replicableData in char array :%s", data);
    //CLOG_DEBUG("Serialized replicableData in  :%s", replicableData->DebugString().c_str());

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        repClient->ReplicateNewEntry(replicaName, sessionKey, data, size, expiryTime);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not replicating  :%s", sessionKey.c_str());
    }

    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::CreateEntryInReplica() <<<<<<<<<<");

    return PB_REPL_UTILS_SUCCESS;
}

int ReplicableData::UpdateEntryInReplica(std::string replicaName, std::string sessionKey, uint32_t expiryTime)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::UpdateEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("UpdateEntryInReplica => replicaName :%s, sessionKey :%s, replicableData :%s", replicaName.c_str(),
                                                            sessionKey.c_str(), replicableData->DebugString().c_str());

    int size = replicableData->ByteSize();

    if(size <= MAX_PB_DATA_LEN) {
    	    char  data[MAX_PB_DATA_LEN] = {0};
	    // Serialize to an array.
	    replicableData->SerializeToArray(data, size);

	    CLOG_DEBUG("replicableData size :%d", size);
	    //CLOG_DEBUG("Serialized replicableData in char array :%s", data);
	    //CLOG_DEBUG("Serialized replicableData in  :%s", replicableData->DebugString().c_str());

	    ReplicationClient* repClient = ReplicationClient::GetInstance();
	    if (repClient)
	    {
		    repClient->ReplicateUpdatedEntry(replicaName, sessionKey, data, size, expiryTime);
	    }
	    else
	    {
		    CLOG_DEBUG("Replication not initialized, not replicating  :%s", sessionKey.c_str());
	    }
    } else {
	CLOG_ERROR("Replication Data is not updated for sessionKey :%s as data size %d is more than %d", sessionKey.c_str(), size, MAX_PB_DATA_LEN);
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::UpdateEntryInReplica() <<<<<<<<<<");

    return PB_REPL_UTILS_SUCCESS;
}

int ReplicableData::DeleteEntryInReplica(std::string replicaName, std::string sessionKey)
{
    int retVal = PB_REPL_UTILS_SUCCESS;

    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::DeleteEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("DeleteEntryInReplica => replicaName :%s, sessionKey :%s", replicaName.c_str(),
                                                                        sessionKey.c_str());
    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        retVal = repClient->ReplicateDeletedEntry(replicaName, sessionKey);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not deleting  :%s", sessionKey.c_str());
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::DeleteEntryInReplica() <<<<<<<<<<");

    return retVal;
}

int ReplicableData::FetchEntryInReplica(std::string replicaName, std::string sessionKey)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::FetchEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("FetchEntryInReplica => replicaName :%s, sessionKey :%s", replicaName.c_str(),
                                                            sessionKey.c_str());

    uint32_t length;
    char data[(MAX_PB_DATA_LEN * MAX_PB_ENTRIES)] = {0};
    int result = PB_REPL_UTILS_SUCCESS;

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        if((result = repClient->GetReplicatedEntry(replicaName, sessionKey, data, &length)) == PB_REPL_UTILS_SUCCESS)
        {
            CLOG_DEBUG("GOT :%s", data);

            // deserialization.
            replicableData->ParseFromArray(data, length);
            CLOG_DEBUG("Success on FetchEntryInReplica => length :%d replicableData :%s", length, replicableData->DebugString().c_str());
        }
        else
        {
            CLOG_DEBUG("Failure on FetchEntryInReplica");
        }
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not fetching  :%s", sessionKey.c_str());
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::FetchEntryInReplica() <<<<<<<<<<");

    return result;
}

int ReplicableData::CreateTransactionEntryInReplica(std::string replicaName, uint32_t indexKey, std::string repData)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::CreateTransactionEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("CreateTransactionEntryInReplica => replicaName :%s, IndexKey :%d, replicableData :%s", replicaName.c_str(),
                                                            indexKey, repData.c_str());

    uint32_t size = repData.length(); 
    std::stringstream strKey;
    strKey<<indexKey;

    //CLOG_DEBUG("IndexKey in string %s",strKey.str().c_str());
    
    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        repClient->ReplicateNewEntry(replicaName, strKey.str(), (void*)repData.c_str(), size);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not replicating  :%d", indexKey);
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::CreateTransactionEntryInReplica() <<<<<<<<<<");

    return PB_REPL_UTILS_SUCCESS;
}

int ReplicableData::UpdateTransactionEntryInReplica(std::string replicaName, uint32_t indexKey, std::string repData, uint32_t expiry)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::UpdateTransactionEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("UpdateTransactionEntryInReplica => replicaName :%s, IndexKey :%d, replicableData :%s", replicaName.c_str(),
                                                            indexKey, repData.c_str());

    uint32_t size = repData.length(); 
    std::stringstream strKey;
    strKey<<indexKey;

    //CLOG_DEBUG("IndexKey in string %s",strKey.str().c_str());
    
    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        repClient->ReplicateNewEntry(replicaName, strKey.str(), (void*)repData.c_str(), size, expiry);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not updating  :%d", indexKey);
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::UpdateTransactionEntryInReplica() <<<<<<<<<<");

    return PB_REPL_UTILS_SUCCESS;

}

int ReplicableData::DeleteTransactionEntryInReplica(std::string replicaName, uint32_t indexKey)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::DeleteTransactionEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("DeleteTransactionEntryInReplica => replicaName :%s, indexKey :%d", replicaName.c_str(),
                                                                        indexKey);
    int retVal = PB_REPL_UTILS_SUCCESS;

    std::stringstream strKey;
    strKey<<indexKey;

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        retVal = repClient->ReplicateDeletedEntry(replicaName, strKey.str());
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not deleting  :%d", indexKey);
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::DeleteTransactionEntryInReplica() <<<<<<<<<<");

    return retVal;

}
int ReplicableData::FetchTransactionEntryInReplica(std::string replicaName, uint32_t indexKey, std::string repData)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::FetchTransactionEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("FetchTransactionEntryInReplica => replicaName :%s, indexKey :%d", replicaName.c_str(),
                                                            indexKey);
#if 0
    uint32_t length;
    char data[(MAX_PB_DATA_LEN * MAX_PB_ENTRIES)] = {0};
    int result = PB_REPL_UTILS_SUCCESS;
    std::stringstream strKey;
    strKey<<indexKey;

    if((result = ReplicationClient::GetInstance()->GetReplicatedEntry(replicaName, strKey.str(),
                    data, &length)) == PB_REPL_UTILS_SUCCESS)
    {
        CLOG_DEBUG("GOT :%s", data);

        // deserialization.
        repData.assign(data,length);
        CLOG_DEBUG("Success on FetchEntryInReplica => length :%d replicableData :%s", length, replicableData->DebugString().c_str());
    }
    else
    {
        CLOG_DEBUG("Failure on FetchEntryInReplica");
    }

    CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::FetchEntryInReplica() <<<<<<<<<<");
#endif
    return 0;
}

int ReplicableData::FetchBulkEntriesInReplica(std::string replicaName,int32_t start, int32_t end,std::vector<std::string> &outData)
{
    int result= PB_REPL_UTILS_SUCCESS;

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        if(((result=repClient->GetBulkReplicatedEntries(replicaName,start,end,outData)) == PB_REPL_UTILS_SUCCESS) || (result == REPL_KEY_ENOENT))
        {
            CLOG_DEBUG("BUlk Fetch Success!");
        }
        else
        {   
            CLOG_ERROR("Failed to Bulk Fetch! [error : %d]", result);
        }
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not bulk fetching  :%s", replicaName.c_str());
    }

    return result;
}

int ReplicableData::FetchCommonEntryFromReplica(std::string replicaName, std::string key, std::string& repData)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::FetchCommonEntryFromReplica() >>>>>>>>>>");

    CLOG_DEBUG("FetchCommonEntryFromReplica => replicaName :%s, key :%s", replicaName.c_str(),
                                                            key.c_str());

    uint32_t length;
    char data[(MAX_PB_DATA_LEN * MAX_PB_ENTRIES)] = {0};
    int result = PB_REPL_UTILS_SUCCESS;

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        if((result = repClient->GetReplicatedEntry(replicaName, key, data, &length)) == PB_REPL_UTILS_SUCCESS)
        {
            // deserialization.
            repData = data;
            CLOG_DEBUG("Success on FetchEntryInReplica => length :%d replicableData :%s", length, data);
        }
        else
        {
            CLOG_DEBUG("Failure on FetchEntryInReplica");
        }
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not fetching  :%s", key.c_str());
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::FetchCommonEntryFromReplica() <<<<<<<<<<");

    return result;
}

int ReplicableData::CreateCommonEntryInReplica(std::string replicaName, std::string key, std::string& repData)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::CreateCommonEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("CreateCommonEntryInReplica => replicaName :%s, key :%s, replicableData :%s", replicaName.c_str(),
                                                            key.c_str(), repData.c_str());

    uint32_t size = repData.length(); 

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        repClient->ReplicateNewEntry(replicaName, key, (void*)repData.c_str(), size);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not replicating  :%s", key.c_str());
    }

    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::CreateCommonEntryInReplica() <<<<<<<<<<");

    return PB_REPL_UTILS_SUCCESS;
}

int ReplicableData::UpdateCommonEntryInReplica(std::string replicaName, std::string key, std::string& repData, uint32_t expiry)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::UpdateCommonEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("UpdateCommonEntryInReplica => replicaName :%s, Key :%s, replicableData :%s", replicaName.c_str(),
                                                            key.c_str(), repData.c_str());

    uint32_t size = repData.length(); 

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        repClient->ReplicateNewEntry(replicaName, key, (void*)repData.c_str(), size, expiry);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not updating  :%s", key.c_str());
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::UpdateCommonEntryInReplica() <<<<<<<<<<");

    return PB_REPL_UTILS_SUCCESS;

}

int ReplicableData::DeleteCommonEntryInReplica(std::string replicaName, std::string key)
{
    //CLOG_DEBUG(" >>>>>>>>>> Entered ReplicableData::DeleteCommonEntryInReplica() >>>>>>>>>>");

    CLOG_DEBUG("DeleteCommonEntryInReplica => replicaName :%s, key :%s", replicaName.c_str(),
                                                                        key.c_str());
    int retVal = PB_REPL_UTILS_SUCCESS;

    ReplicationClient* repClient = ReplicationClient::GetInstance();
    if (repClient)
    {
        retVal = repClient->ReplicateDeletedEntry(replicaName, key);
    }
    else
    {
        CLOG_DEBUG("Replication not initialized, not deleting  :%s", key.c_str());
    }


    //CLOG_DEBUG(" <<<<<<<<<< Exiting ReplicableData::DeleteCommonEntryInReplica() <<<<<<<<<<");

    return retVal;

}



