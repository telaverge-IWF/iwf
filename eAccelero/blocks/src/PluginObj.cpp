#include "PluginObj.h"
#include <sstream>

using namespace eAccelero;

std::string PluginLoader::m_pluginDir;

PluginObject* PluginLoader::LoadPlugin(std::string pluginName, 
                            std::string pluginType,
                            unsigned flags)
{
    void *dlHandle = NULL;
    std::stringstream pluginPath;
    
    pluginPath <<  m_pluginDir << "lib" << pluginName << ".so";

    dlHandle = dlopen(pluginPath.str().c_str(), flags);
    if (dlHandle == NULL)
    {
        std::stringstream exMsg;
        exMsg << "Plugin open failed- " << dlerror();
        throw PluginException(exMsg.str().c_str());
    }

    std::stringstream createFuncStr;
    createFuncStr << pluginName << "_CreatePlugin";
    CreatePluginFunc funcPtr = (CreatePluginFunc)dlsym(dlHandle,
                                             createFuncStr.str().c_str());
    if (funcPtr == NULL)
    {
        std::stringstream exMsg;
        exMsg << createFuncStr.str() << " not found- " << dlerror();
        throw PluginException(exMsg.str().c_str());
    }

    PluginObject *plugin = (*funcPtr)(pluginType);
    if (plugin == NULL)
    {
        throw PluginException("Unable to create plugin object");
    }
    plugin->SetPluginHandle(dlHandle);

    return plugin;
}

void PluginLoader::UnloadPlugin(PluginObject* plugin)
{
    if (plugin->GetPluginHandle())
    {
        void *pluginHandle = plugin->GetPluginHandle();
        delete plugin;
        dlclose(pluginHandle);
    }
}

