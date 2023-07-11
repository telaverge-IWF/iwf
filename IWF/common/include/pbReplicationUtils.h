/********************************-*-H-*-************************************
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

#ifndef _PB_REPL_UTILS_H_
#define _PB_REPL_UTILS_H_

#include <google/protobuf/message.h>
#include "ReplicationClient.h"
#include "Component.h"

// NOTE : MAX_PB_DATA_LEN is size of protocol buffer class pbSessionInfoDetails.
// It can grow, if we add any entries in pbSessionInfoDetails class.
// Length is increased from 1024 to 2048 as replication data can be more due to the repeated field timers in pbSessionInfoDetails
#define MAX_PB_DATA_LEN 2048

// NOTE : Currently it is taken as max 5 entries, can be varied as per requirement.
#define MAX_PB_ENTRIES 5

#define PB_REPL_UTILS_SUCCESS 0
#define PB_REPL_UTILS_FAILURE -1

class ReplicableData
{
 protected:
     google::protobuf::Message *replicableData;
 public:
     ReplicableData(google::protobuf::Message *data) : replicableData(data)
     {
         // constructor
     };

     int CreateEntryInReplica(std::string replicaName, std::string sessionKey, uint32_t expiryTime = 0);

     int UpdateEntryInReplica(std::string replicaName, std::string sessionKey, uint32_t expiryTime = 0);

     static int DeleteEntryInReplica(std::string replicaName, std::string sessionKey);

     int FetchEntryInReplica(std::string replicaName, std::string sessionKey);

     static int CreateTransactionEntryInReplica(std::string replicaName, uint32_t indexKey, std::string repData);

     static int UpdateTransactionEntryInReplica(std::string replicaName, uint32_t indexKey, std::string repData, uint32_t expiryTime = 0);

     static int DeleteTransactionEntryInReplica(std::string replicaName, uint32_t indexKey);

     static int FetchTransactionEntryInReplica(std::string replicaName, uint32_t indexKey, std::string repData);
 
     static int FetchBulkEntriesInReplica(std::string replicaName,int32_t start, int32_t end,std::vector<std::string> &outData);

     static int CreateCommonEntryInReplica(std::string replicaName, std::string key, std::string& repData);

     static int UpdateCommonEntryInReplica(std::string replicaName, std::string indexKey, std::string& repData, uint32_t expiryTime = 0);

     static int DeleteCommonEntryInReplica(std::string replicaName, std::string indexKey);

     static int FetchCommonEntryFromReplica(std::string replicaName, std::string indexKey, std::string& repData);
};

#endif
