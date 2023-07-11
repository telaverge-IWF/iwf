#ifndef QUERY_H
#define QUERY_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <CommonStructure.h>
#include <config.h>

#include <AvailabilityManagerConfigT.h>
#include <DefaultRouteT.h>
#include <DynamicDiscoveryT.h>
#include <LocalHostConfigT.h>
#include <PeerGlobalConfigT.h>
#include <PeerT.h>
#include <PeerTimersT.h>
#include <RealmRoutingT.h>
#include <ReplicationManagerConfigT.h>
#include <UserT.h>
#include <AsfT.h>
#include <AsfConfigT.h>
#include <AsfFeatureT.h>
#include <PeerDictionaryMapT.h>


class Query : protected AvailabilityManagerConfigTQuery, protected DefaultRouteTQuery, protected DynamicDiscoveryTQuery, protected LocalHostConfigTQuery, protected PeerGlobalConfigTQuery, protected PeerTQuery, protected PeerTimersTQuery,protected PeerDictionaryMapTQuery, protected RealmRoutingTQuery, protected ReplicationManagerConfigTQuery,protected AsfTQuery,protected AsfConfigTQuery,protected AsfFeatureTQuery, protected UserTQuery {};

#endif
