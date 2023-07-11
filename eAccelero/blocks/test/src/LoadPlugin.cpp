#include "PluginObj.h"
#include <sstream>
#include <stdlib.h>

using namespace eAccelero;

int main()
{
    std::stringstream dir;
    dir << getenv("EACC_ROOT") << "/blocks/test/lib/debug/";

    std::cout << "Loading plugin from " << dir.str() << std::endl;

    PluginLoader::SetPluginDir(dir.str());

    PluginObjectRef holder;

    {
        PluginObjectRef obj = PluginLoader::LoadPlugin("Test", "dict");

        holder = obj;

        obj->Initialize();
        obj->Terminate();
    }
    
    //PluginLoader::UnloadPlugin(obj);
    std::cout << "Terminating program...\n";

    return 0;
}

