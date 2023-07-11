#ifndef __MeSSDef_h__
#define __MeSSDef_h__

namespace eAccelero
{

#define MESS_MIN_ACTIVE_INSTANCE    0
#define MESS_MAX_ACTIVE_INSTANCE    8191        // 0x1FFF
#define MESS_MIN_STANDBY_INSTANCE   8192        // 0x2000
#define MESS_MAX_INSTANCES          16383       // 0x3FFF
#define MESS_MAX_STANDBY_INSTANCE   MESS_MAX_INSTANCES

#define MESS_MIN_RDM_INSTANCE       (MESS_MAX_STANDBY_INSTANCE+1)   // 0x4000
#define MESS_MAX_RDM_INSTANCE       (MESS_MIN_RDM_INSTANCE | MESS_MAX_STANDBY_INSTANCE) // 0x7FFF

#define MESS_MIN_DGM_INSTANCE       (MESS_MAX_RDM_INSTANCE + 1)     // 0x8000
#define MESS_MAX_DGM_INSTANCE       (MESS_MIN_DGM_INSTANCE | MESS_MAX_STANDBY_INSTANCE) // 0xBFFF

#define TIPC_MAX_INST   (0x7FFFFFFF)

#define MESS_MULTICAST_ACTIVE   MESS_MAX_ACTIVE_INSTANCE
#define MESS_MULTICAST_STANDBY  MESS_MAX_STANDBY_INSTANCE
#define MESS_MULTICAST_ALL      (0xFFFF)

#define MESS_DM_INST_MASK   (MESS_MIN_RDM_INSTANCE|MESS_MIN_DGM_INSTANCE)
#define MESS_INST_MASK      (~(MESS_DM_INST_MASK))

inline unsigned short MESS_ToDMInst(unsigned short offset, unsigned short inst)
{
    return (offset | inst);
}

inline unsigned short MESS_ToRdmInst(unsigned short inst)
{
    return MESS_ToDMInst(MESS_MIN_RDM_INSTANCE, inst);
}

inline unsigned short MESS_ToDgmInst(unsigned short inst)
{
    return MESS_ToDMInst(MESS_MIN_DGM_INSTANCE, inst);
}

inline unsigned short MESS_ToInst(unsigned short dmInst)
{
    return (MESS_INST_MASK & dmInst);
}

inline bool MESS_ISActiveInst(unsigned short inst)
{
    return (inst <= MESS_MAX_ACTIVE_INSTANCE);
}

inline bool MESS_ISStandbyInst(unsigned short inst)
{
    return (inst >= MESS_MIN_STANDBY_INSTANCE && inst <= MESS_MAX_STANDBY_INSTANCE);
}

inline bool MESS_ISRdmInst(unsigned short inst)
{
    return (MESS_MIN_RDM_INSTANCE & inst);
}

inline bool MESS_ISDgmInst(unsigned short inst)
{
    return (MESS_MIN_DGM_INSTANCE & inst);
}

inline unsigned short MESS_GetDMOffset(unsigned short inst)
{
    return (MESS_DM_INST_MASK & inst);
}

// Exception definition
EACC_DEFINE_EXCEPTION_CLASS(MeSSException, Exception, "MeSS Exception")
// Args are log_level, descr, errCode
#define MeSSExceptionLog(_level, _descr, ...) \
            GEN_EXCEPTION_LOG(eAccelero::MeSSException,\
                              _descr,\
                              &eAccelero::ComponentBase::Instance().GetLogger(),\
                              _level,\
                              ##__VA_ARGS__)

// TODO seperate logger for MeSS
                              
} // namespace eAccelero

#endif // __MeSSDef_h__