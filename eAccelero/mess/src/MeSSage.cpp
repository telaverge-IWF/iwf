
#include "MeSS.h"

namespace eAccelero
{

MeSSage* MeSSage::CreateMessage(unsigned payloadSz)
{
    unsigned idx = 0;
    void* ptr = MeSS::MeSSObj().Pool().Alloc(sizeof(MeSSage) + payloadSz, &idx);
    MeSSage *msg = new(ptr) MeSSage();
    
    msg->CorrId() = idx;
    msg->Size()   = sizeof(MeSSage) + payloadSz;
    
    return msg;
}

MeSSage* MeSSage::CreateReqMessage(const MeSSEndpoint &dest,
                    const MessageId &msgId, unsigned payloadSz, void* cookie,
                    MeSSEncodingType encType)
{
    unsigned short inst;
    unsigned idx = 0;
    void* ptr = MeSS::MeSSObj().Pool().Alloc(sizeof(MeSSage) + payloadSz, &idx);
    MeSSage *msg = new(ptr) MeSSage();
    
    msg->m_hdr.version = 1;

    // To provide node level uniqueness for the message id
    msg->Id() = MeSSage::EmbedSrcNodeId(idx, MeSS::MeSSObj().SelfNodeId()); 
    msg->MsgId() = msgId;
    msg->m_hdr.encodingType = encType;
    msg->m_hdr.src = MeSS::MeSSObj().Self();
    msg->m_hdr.reqFlag = 1;
    msg->m_cookie = cookie;
    msg->m_hdr.msgLen = sizeof(MeSSHeader) + payloadSz;
    msg->m_dest = dest;
    
    msg->m_hdr.mcast = 0;
    inst = MESS_ToInst(dest.instance);
    if (inst == MESS_MULTICAST_ACTIVE || 
        inst == MESS_MULTICAST_STANDBY ||
        inst == MESS_MULTICAST_ALL)
    {
        msg->m_hdr.mcast = 1;
    }
    
    msg->m_hdr.src.instance = MESS_ToDMInst(MESS_GetDMOffset(dest.instance), msg->m_hdr.src.instance);
    
#if defined(__LITTLE_ENDIAN)
    msg->m_hdr.endian = 0;
#else
    msg->m_hdr.endian = 1;
#endif
    
    return msg;
}

MeSSage* MeSSage::CreateRespMessage(const MeSSage &req, unsigned payloadSz, 
                    MeSSEncodingType encType)
{
    unsigned idx = 0;
    void* ptr = MeSS::MeSSObj().Pool().Alloc(sizeof(MeSSage) + payloadSz, &idx);
    MeSSage *msg = new(ptr) MeSSage();
    
    msg->m_hdr.version = 1;
    msg->Id() = req.Id();
    msg->MsgId() = req.MsgId();
    msg->m_hdr.encodingType = req.m_hdr.encodingType;
    msg->m_hdr.src = MeSS::MeSSObj().Self();
    msg->m_hdr.reqFlag = 0;
    msg->m_hdr.code = CODE_SUCCESS;
    msg->m_dest = req.m_hdr.src;
    msg->m_hdr.msgLen = sizeof(MeSSHeader) + payloadSz;
    msg->m_hdr.mcast = req.m_hdr.mcast;
    
    msg->m_hdr.src.instance = MESS_ToDMInst(MESS_GetDMOffset(req.m_hdr.src.instance),
                                            msg->m_hdr.src.instance);    
    
#if defined(__LITTLE_ENDIAN)
    msg->m_hdr.endian = 0;
#else
    msg->m_hdr.endian = 1;
#endif

    return msg; 
}

void MeSSage::DestroyMessage(MeSSage *msg)
{
    msg->~MeSSage();
    MeSS::MeSSObj().Pool().Free(msg);
}
    
} // namespace eAccelero
