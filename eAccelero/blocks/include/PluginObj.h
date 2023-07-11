#ifndef __EACC_PluginObj_h__
#define __EACC_PluginObj_h__

#include "Exception.h"
#include <string.h>
#include <dlfcn.h>
#include "Ref.h"

namespace eAccelero
{

EACC_DEFINE_EXCEPTION_CLASS(PluginException, Exception, "Plugin Exception")

class PluginObject;

typedef PluginObject* (*CreatePluginFunc)(std::string pluginType);

class PluginLoader
{
 public:
    const static unsigned DEFAULT_DL_FLAGS = RTLD_GLOBAL | RTLD_NOW;

    static void SetPluginDir(std::string pluginDir)
    {
        m_pluginDir = pluginDir;
    }

    // Plugin Type can be "dict" or "xform" currently
    // Flags can be RTLD_LAZY, RTLD_NOW, 
    //  RTLD_GLOBAL, RTLD_LOCAL, RTLD_NODELETE, RTLD_NOLOAD, RTLD_DEEPBIND
    static PluginObject* LoadPlugin(std::string pluginName, 
                                    std::string pluginType,
                                    unsigned flags = DEFAULT_DL_FLAGS);

    static void UnloadPlugin(PluginObject* plugin);

    static void* ResolveSymbol(PluginObject* plugin, std::string funcName);
 private:
    static std::string m_pluginDir;
};

struct PluginObjRP;

class PluginObject: public RefObj<>
{
 public:
    PluginObject(std::string name)
        : m_pluginName(name)
    {
    }
    virtual ~PluginObject()
    {
    }

    virtual void Initialize() = 0;

    virtual int Configure(void* conf) = 0;

    virtual void Terminate() = 0;

    const std::string& GetPluginName()
    {
        return m_pluginName;
    }

    friend class PluginLoader;
    friend class PluginObjRP;
 protected:
    void* GetPluginHandle()
    {
        return m_dlHandle;
    }
    void SetPluginHandle(void *handle)
    {
        m_dlHandle = handle;
    }

    void* m_dlHandle;
    std::string m_pluginName;
};

struct PluginObjRP
{
    static int Release(PluginObject* obj)
    {
        void* dlHandle = obj->GetPluginHandle();
        if (obj->Release() == 0)
        {
            // the object is deleted, unload the plugin then
            dlclose(dlHandle);
            return 0;
        }
        return 1;
    }
};

typedef Reference<PluginObject, PluginObjRP> PluginObjectRef;

inline void* PluginLoader::ResolveSymbol(PluginObject* plugin, std::string funcName)
{
    void* ret = dlsym(plugin->GetPluginHandle(), funcName.c_str());
    if (ret == NULL)
    {
        throw PluginException("Unable to resolve symbol");
    }

    return ret;
}

} // namespace eAccelero

#endif // __EACC_PluginObj_h__

