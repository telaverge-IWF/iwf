/* ********************************-*-H-*-************************************
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

#ifndef __IWF_STATE_REPLICATION_H__
#define __IWF_STATE_REPLICATION_H__

#include <string>

#define REPL_SYNC_TPOOL_SIZE 4
#define REPL_ASYNC_POOL_SIZE 4

//Configuration defaults
#define DEFAULT_COUCHBASE_HOST_NAME "localhost"
#define DEFAULT_COUCHBASE_PORT 8091
#define DEFAULT_COUCHBASE_PASSWORD "diametriq@123"
#define DEFAULT_BUCKET_ITEMS 10000
#define DEFAULT_BUCKET_TTL 0
#define DEFAULT_RETRY_CONN_MAX 100

//Return Codes for errors
#define REPL_CONFIG_PARSE_FAILED -1
#define REPL_CLINT_INIT_FAILED -2

namespace iwf {
    class IWFStateReplication {
        public:
            static int Initialize(std::string repConfigFile,ReplicationStatusCbk replStatusCbk);

        private:
            static int ParseReplicationConfig(std::string configFile);
            static int ParseCouchbaseCfg();
            static std::map<std::string, std::string> m_objConfigReaderMap;
            static CouchbaseConnectorBean connDetails;
            //static std::vector<ReplicaBean> replicas;
            static int syncThreadPoolSize;
            static int asyncThreadPoolSize;

    };

}//namespace iwf

#endif //#ifndef __IWF_STATE_REPLICATION_H__
