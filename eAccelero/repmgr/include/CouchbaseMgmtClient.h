/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 * Author: adey
 *
 * Created on June 14, 2012, 9:55 AM
 ****************************************************************************/
#ifndef _COUCHBASE_REST_CLIENT_H
#define _COUCHBASE_REST_CLIENT_H

#include "CouchbaseNode.h"
#include "stdint.h"
#include <vector>
#include <curl/curl.h>
#include <json.h>
#include <Logger.h>


namespace eAccelero {
#define COUCHBASE_PROCY_PORT 11215
#define URL_SIZE 100
#define DHEALTHY "healthy"
#define DWARMUP "warmup"
#define DUNHEALTHY "unhealthy"
#define CB_OP_TIMEOUT 2
    typedef enum _CouchbaseApiError {
        CB_OK,
        CB_GENERIC_ERROR,
        CB_FAILED_TO_CONNECT_TO_SERVER,
        CB_REBALANCE_INPROGRESS,
        CB_HTTP_ER_GT_400,
        CB_LOGIN_DENIED,
        CB_CURL_FAILED_TO_INITIALIZED,
        CB_CURL_REBALANCE_FAILED
    }CouchbaseApiError;

    typedef enum _CouchbaseStatus {
        HEALTHY,
        UNHEALTHY,
        WARMUP
    }CouchbaseStatus;

    typedef struct _CouchbaseConfig {
        std::string hostName;
        uint32_t port;
        std::string adminUserName;
        std::string adminPassword;
        std::string mateHostName;
        std::string mateIP;
    }CouchbaseConfig;

    class CouchbaseMgmtClient {
        public:
            CouchbaseMgmtClient(CouchbaseConfig& config);
            CouchbaseMgmtClient();
            void resetCurlHandle(CURL *curlHandle);
            ~CouchbaseMgmtClient();
            uint32_t Initialize();
        private:
            CouchbaseConfig config;
            void SetCredentials(CURL *curlHandle);
        protected:
            CURL* curlHandle;
            std::string baseURL;
            std::string credentials;
            uint32_t ParseCurlJson(Json::Value *jsonRoot,std::string jsonBuffer);
            uint32_t HandleCurlErrorToCBApiError(CURLcode curlError);
    };

    class CouchbaseClusterMgmtClient:public CouchbaseMgmtClient {
        public:
            CouchbaseClusterMgmtClient(CouchbaseConfig& config);
            ~CouchbaseClusterMgmtClient();
            uint32_t RebalanceCluster(std::vector<CouchbaseNode>& nodes);
	    uint32_t StopRebalance();
            uint32_t CheckRebalanceStatus(double &node1RebalanceStatus,double &node2RebalanceStatus);
            uint32_t AddNodeToCluster(CouchbaseNode node);
            uint32_t FailOverNode(CouchbaseNode node);
            uint32_t FetchClusterStatus(std::vector<CouchbaseNode>& nodes);
            uint32_t PurgeUnwantedData(std::string bucket);
            uint32_t PingNode();
            static std::string response;
        private:
            void parseFetchClusterStatusResponse(std::string sJsonString,std::vector<CouchbaseNode>& nodes);
    };

    class CouchbaseBucketMgmtClient:public CouchbaseMgmtClient {
        public:
            CouchbaseBucketMgmtClient();
            ~CouchbaseBucketMgmtClient();
            uint32_t CreateCouchbaseBucket(std::string BucketName, std::string Password,
                    uint32_t initialSizeInMB, uint32_t noReplicas);
            uint32_t SetBucketQuota(uint32_t sizeInMB);
            uint32_t SetBucketQuota(std::string BucketName,std::string Password,uint32_t sizeInMB);
            uint32_t SetTTLForBucket(uint32_t timeInSecs);
            uint32_t FlushBucket(std::string BucketName);
    };

} //namespace eAccelero

#endif //#ifndef _COUCHBASE_REST_CLIENT_H

