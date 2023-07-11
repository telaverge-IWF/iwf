
#include <json/json.h>
#include <string>
#include <fstream>

using namespace Json;


int main()
{
    Reader r;
    Value root;
    std::ifstream doc("test.json");

    r.parse(doc, root);

    std::cout << root["realm-table"][0]["realm"].asString() << std::endl;
    std::cout << root["realm-table"][0]["apps"][1]["lb-algo"].asString() << std::endl;

    const Value realmEntries = root["realm-table"];
    for(unsigned i = 0; i < realmEntries.size() ; i++)
    {
        std::cout << "Realm <" << realmEntries[i]["realm"].asString() << "> "
                  << "apps";
        const Value apps = realmEntries[i]["apps"];
        std::cout << " <" << apps.size() << "> [";
        for (unsigned j = 0; j < apps.size(); j++)
        {
            std::cout << apps[j]["application-id"].asInt() << ", ";
        }
        std::cout << "]\n";
    }

    return 0;
}

