#!/bin/bash

my="mysql  --host=localhost --user=root --password=intelliss7 --database=DIAMETRIQ -se"
echo "**************************"
echo "CURRENT TABLES IN DATABASE"
echo "**************************"
${my} "show tables"

${my} "truncate table LocalHostConfigT"

${my} "truncate table DynamicDiscoveryT"

${my} "truncate table DefaultRouteT"

${my} "truncate table RealmRoutingT"

${my} "truncate table PeerGlobalConfigT"

${my} "truncate table PeerT"

${my} "truncate table AvailabilityManagerConfigT"

${my} "truncate table PeerTimersT"

${my} "truncate table ReplicationManagerConfigT"

${my} "truncate table UserT"

${my} "truncate table LB_ALGORITHM_TB"

${my} "truncate table APPLICATION_GRP_TB"

${my} "truncate table ASF_CONFIGURATION_TB"

${my} "truncate table FEATURE_TB"

echo "------------------------------------------------------"
echo "SUCCESFULLY ERASED ALL THE ENTRIES IN FOLLOWING TABLES"
echo "------------------------------------------------------"

${my} "show tables"



