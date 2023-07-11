#include "PluginObj.h"

using namespace eAccelero;

class TestPlugin: public PluginObject
{
 public:
    TestPlugin()
        : PluginObject("test")
    {
        std::cout << "Inside plugin constructor\n";
    }
    ~TestPlugin()
    {
        std::cout << "Plugin destructor\n";
    }

    void Initialize()
    {
        std::cout << "Inside plugin initialize\n";
    }
    int Configure(void *conf)
    {
        std::cout << "Configure invoked\n";
        return 0;
    }
    void Terminate()
    {
        std::cout << "Inside plugin terminate\n";
    }
};

extern "C" PluginObject* Test_CreatePlugin(std::string pluginType)
{
    return new TestPlugin();
}

