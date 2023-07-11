#ifndef __MeSSComponent_h__
#define __MeSSComponent_h__

#include "Component.h"
#include "MeSS.h"

namespace eAccelero
{

class MeSSComponent: public ComponentBase
{
  public:
    static MeSSComponent& Instance()
    {
        return *(static_cast<MeSSComponent*>(m_instance));
    }
    
    MeSSComponent(const char *name, unsigned compId);

    ~MeSSComponent();
    
    virtual void Initialize();
    
    virtual void Terminate();
    
    MeSS& MeSSObj()
    {
        return *m_messObj;
    }
  protected:
    MeSS *m_messObj;
};

} // namepsace eAccelero

#endif // __MeSSComponent_h__