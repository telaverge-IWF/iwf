
#include "CouchbaseMgmtClient.h"
using namespace eAccelero;

int main()
{
 CouchbaseConfig config;
 config.hostName = "10.1.4.41";
 config.port = 8091;
 config.adminUserName = "Administrator";
 config.adminPassword = "mlb303hp2";
 CouchbaseClusterMgmtClient* client = new CouchbaseClusterMgmtClient(config);
    std::vector<Node> nodes;
    client->Initialize();
    client->FetchClusterStatus(nodes);
}
