
#include "MeSSComponent.h"

namespace eAccelero
{

MeSSComponent::MeSSComponent(const char *name, unsigned compId)
    : ComponentBase(name, compId),
      m_messObj(new MeSS(*this))
{

}

MeSSComponent::~MeSSComponent()
{
    
}

void MeSSComponent::Initialize()
{
    ComponentBase::Initialize();
    
    // Init code
    m_messObj->MeSSThread() = ThisThread::Self();
}

void MeSSComponent::Terminate()
{
    // Terminate code
    
    ComponentBase::Terminate();
}

} // namespace eAccelero
