#ifndef __EACC_MeSSage_h__
#define __EACC_MeSSage_h__

#include "TimeVal.h"
#include "MeSSDef.h"

namespace eAccelero
{

struct MeSSEndpoint
{
    uint16_t compId;
    uint16_t instance;
};

union MessageId
{
    struct {
        uint32_t methodId:8;
        uint32_t interfaceId:24;
    };
    uint32_t msgId;
};

inline MessageId MakeMsgId(unsigned iface, unsigned method)
{
    MessageId ret;
    ret.interfaceId = iface;
    ret.methodId = method;    
    return ret;
}

inline unsigned METoInt(const MeSSEndpoint &e)
{
    return *(unsigned*)(MeSSEndpoint*)(&e);
}

enum MeSSEncodingType
{
    FLAT_ENCODING, // base on endianess, directly copied to structs
    PROTOBUF_ENCODING, // for variable length data and options message fields
};
enum MeSSErrorCode
{
    CODE_SUCCESS,
    CODE_INVALID_MESSAGE,       // Interface/method not implemented/registered by component
    CODE_INCOMPATABLE_VERSION,
    CODE_DECODE_ERROR,          // Error in decoding the message
};

struct MeSSHeader
{
    uint8_t version;
    struct
    {
        uint8_t code:3;         // Response code, 0 on success
        uint8_t mcast:1;
        uint8_t reqFlag:1;
        uint8_t encodingType:2;
        uint8_t endian:1;
    };
    uint32_t msgLen:16; // Including the header

    MessageId    msgId;
    uint32_t     tid;   // transaction id
    MeSSEndpoint src;
};

class MeSSage
{
   public:

    enum Flags
    {
        STATE_PENDING_SEND = 1,
        STATE_PENDING_RESP = (1 << 1),
    };

    enum 
    {
        MESS_TID_NODE_ID_SHIFT = 22,
        MESS_TID_NODE_ID_MASK  = (0xF << MESS_TID_NODE_ID_SHIFT)
    };

    static MeSSage* CreateMessage(unsigned payloadSz);
    static MeSSage* CreateReqMessage(const MeSSEndpoint &dest, const MessageId &msgId, 
                        unsigned payloadSz, void *cookie = NULL,
                        MeSSEncodingType encType = FLAT_ENCODING);
    static MeSSage* CreateRespMessage(const MeSSage &req, unsigned payloadSz, 
                        MeSSEncodingType encType = FLAT_ENCODING);                        

    static void DestroyMessage(MeSSage *msg);
    
    const unsigned Len() const
    {
        return m_hdr.msgLen;
    }
    const void* Payload() const
    {
        return (const void*)m_payload;
    }
    void* Payload()
    {
        return (void*)m_payload;
    }
    const unsigned& Id() const
    {
        return m_hdr.tid;
    }
    unsigned& Id()
    {
        return m_hdr.tid;
    }
    const MessageId& MsgId() const
    {
        return m_hdr.msgId;
    }
    MessageId& MsgId()
    {
        return m_hdr.msgId;
    }    
    unsigned& CorrId()
    {
        return m_recv.corrId;
    }
    const unsigned& CorrId() const
    {
        return m_recv.corrId;
    }    
    unsigned& Size()
    {
        return m_recv.bufSz;
    }
    const unsigned& Size() const
    {
        return m_recv.bufSz;
    }
    void* Buffer()
    {
        return (void*)(&m_hdr);
    }
    const MeSSHeader& Hdr() const
    {
        return m_hdr;
    }
    MeSSHeader& Hdr()
    {
        return m_hdr;
    }
    bool IsRequest()
    {
        return (m_hdr.reqFlag == 1);
    }
    const MeSSEndpoint& Dest() const
    {
        return m_dest;
    }
    TimeVal& Tstamp()
    {
        return m_tstamp;
    }
    const TimeVal& Tstamp() const
    {
        return m_tstamp;
    }
    void* Cookie()
    {
        return m_cookie;
    }

    bool IsPendingSend()
    {
        return (m_flags & STATE_PENDING_SEND);
    }
    bool IsPendingResp()
    {
        return (m_flags & STATE_PENDING_RESP);
    }
    void ClearPendingSend()
    {
        m_flags &= ~STATE_PENDING_SEND;
    }
    void ClearPendingResp()
    {
        m_flags &= ~STATE_PENDING_RESP;
    }
    void SetPendingSend()
    {
        this->ClearPendingResp();
        m_flags |= STATE_PENDING_SEND;
    }
    void SetPendingResp()
    {
        this->ClearPendingSend();
        m_flags |= STATE_PENDING_RESP;
    }

    static unsigned ExtractSrcNodeId(unsigned idx)
    {
        return (idx & MESS_TID_NODE_ID_MASK) >> MESS_TID_NODE_ID_SHIFT;
    }
    static unsigned EmbedSrcNodeId(unsigned idx, unsigned nodeId)
    {
        idx |= (nodeId << MESS_TID_NODE_ID_SHIFT);
        return idx;
    }

    // Transaction id - Node id
    static unsigned ExtractAllocId(unsigned idx)
    {
        return (idx & ~MESS_TID_NODE_ID_MASK);
    }
 protected:
    friend class MeSSageQ;
    friend class Transceiver;
    
    void Unlink()
    {
        if (this->m_prev)
        {
            EACC_ASSERT((this->m_prev->m_next == this));
            this->m_prev->m_next = this->m_next;
        }
        if (this->m_next)
        {
            EACC_ASSERT((this->m_next->m_prev == this));
            this->m_next->m_prev = this->m_prev;
        }

        this->m_next = NULL;
        this->m_prev = NULL;
    }
 
    MeSSage()
        : m_next(NULL),
          m_prev(NULL)
    {
        
    }
    
    ~MeSSage()
    {
    
    }
    
    MeSSage* m_next;
    MeSSage* m_prev;
    TimeVal  m_tstamp; // Sent or received timestamp, used for expiry
    MeSSEndpoint m_dest;
    unsigned m_flags;
    
    union
    {
        void *m_cookie;     // used for sent messages, for the callback
        struct 
        {
            unsigned corrId;  // used for received messges
            unsigned bufSz;   // used for received messages
        }m_recv;
    };
    
    MeSSHeader m_hdr;
    unsigned char m_payload[0];
    // Followed by the actual message buffer
};

} // namespace eAccelero

#endif // __EACC_MeSSage_h__
