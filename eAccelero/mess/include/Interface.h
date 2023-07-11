#ifndef __EACC_Interface_h__
#define __EACC_Interface_h__

#include "Transceiver.h"
#include<string>

namespace eAccelero
{

class MethodBase
{
 public:
    virtual ~MethodBase()
    {
    }
    virtual int Invoke(Transceiver *sock, MeSSage *in) = 0;
    virtual MethodBase* Duplicate() const = 0;
 protected:
    MethodBase()
    {
    }
};

class Interface;

template <typename Req, typename Resp>
struct FlatEncodingTraits
{
    typedef Req*  ReqT;
    typedef Resp* RespT;

    static inline Req* GetPtr(Req *req)
    {
        return req;
    }
};

struct FlatEncodingPolicy
{
    template <typename Req>
    static int DecodeIn(MeSSage *in, Req &req)
    {
        if(((in->Hdr().encodingType) & PROTOBUF_ENCODING) == 0)
        {
            req = (Req)in->Payload();
        }
        else
        {
            throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, "Expected Flat encoding policy");
        }
        return 0;
    }

    template <typename Resp>
    static Resp CreateResp(MeSSage *in, Resp &resp, MeSSage *&out)
    {
        out = MeSSage::CreateRespMessage(*in, sizeof(*resp));
        return (Resp)out->Payload();
    }

    template <typename Resp>
    static int
    EncodeOut(MeSSage *in, Resp &resp, MeSSage *&out)
    {
        // Do nothing
        return 0;
    } 
};

template <typename Req, typename Resp>
struct PBEncodingTraits
{
    typedef Req  ReqT;
    typedef Resp RespT;

    static inline Req* GetPtr(Req &req)
    {
        return &req;
    }
};

struct PBEncodingPolicy
{
    template <typename Req>
    static int DecodeIn(MeSSage *in, Req &req);

    template <typename Resp>
    static int EncodeOut(MeSSage *in, Resp &resp, MeSSage *&out);

    template <typename Resp>
    static Resp* CreateResp(MeSSage *in, Resp &resp, MeSSage *&out)
    {
        return &resp;
    }
};

template <typename C, typename Req, typename Resp, 
          template<typename RQ=Req, typename RS=Resp> class ETraits = FlatEncodingTraits,
          typename EPolicy = FlatEncodingPolicy>
class MethodSlot: public MethodBase
{
 public:
    typedef int (C::*Method)(Req*, Resp*);

    MethodSlot(C *obj, Method cbk)
        : m_obj(obj),
          m_cbk(cbk)
    {
    }

    int Invoke(Transceiver *sock, MeSSage *in)
    {
        int ret = 0;
        if (m_obj && m_cbk)
        {
            typename ETraits<>::ReqT  req;
            typename ETraits<>::RespT resp;
            MeSSage *out;

            ret = EPolicy::DecodeIn(in, req);
            if (ret)
            {
                return ret;
            }

            Req* reqPtr = ETraits<>::GetPtr(req);
            Resp* respPtr = EPolicy::CreateResp(in, resp, out);

            ret = (m_obj->*m_cbk)(reqPtr, respPtr);

            EPolicy::EncodeOut(in, resp, out);
            sock->Send(out);
        }
        return ret;
    }

    MethodBase* Duplicate() const
    {
        return new MethodSlot(m_obj, m_cbk);
    }

 private:
    C *m_obj;
    Method m_cbk; 
};

template <typename C, typename Resp, 
          template<typename RQ=Resp, typename RS=Resp> class ETraits = FlatEncodingTraits,
          typename EPolicy = FlatEncodingPolicy>
class CallbackSlot: public MethodBase
{
 public:
    typedef int (C::*Method)(Resp*);

    CallbackSlot(C *obj, Method cbk)
        : m_obj(obj),
          m_cbk(cbk)
    {
    }

    int Invoke(Transceiver *sock, MeSSage *in)
    {
        (void)sock;
        if (m_obj && m_cbk)
        {
            typename ETraits<>::RespT resp;
            Resp* respPtr = NULL;

            if (in && (in->Hdr().code == 0))
            {
                int ret;
                ret = EPolicy::DecodeIn(in, resp);
                if (ret)
                {
                    // Not decoded, ignored for a callback.
                    return ret;
                }
                respPtr = ETraits<>::GetPtr(resp);
            }

            return (m_obj->*m_cbk)(respPtr);
        }
        return 0;
    }

    MethodBase* Duplicate() const
    {
        return new CallbackSlot(m_obj, m_cbk);
    }

 private:
    C *m_obj;
    Method m_cbk;    
};

class Interface
{
  public:
    enum
    {
        MAX_METHODS = 256
    };
    enum RetType
    {
        Success,
        MethodNotImpl,
        InterfaceNotImpl,
        DecodeFailure
    };
        
    Interface(unsigned interfaceId)
        : m_ifId(interfaceId)
    {
        for (int i = 0; i < MAX_METHODS; i++)
            m_methods[i] = NULL;
    }
    virtual ~Interface()
    {
        for (int i = 0; i < MAX_METHODS; i++)
        {
            if (m_methods[i]) delete m_methods[i];
        }
    }
    virtual void RegisterMethods() = 0;
    
    void RegisterMethod(unsigned methodId, const MethodBase &method)
    {
        if (methodId >= MAX_METHODS)
        {
            std::stringstream out;
            out << "MethodId " << m_ifId << ":" << methodId << " exceeded the limits";
            throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, out.str().c_str());
        }
        if (m_methods[methodId])
        {
            std::stringstream out;
            out << "MethodId " << m_ifId << ":" << methodId << " already registered";
            throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, out.str().c_str());
        }
        m_methods[methodId] = method.Duplicate();
    }
    RetType Invoke(unsigned methodId, Transceiver *sock, MeSSage *in)
    {
        if (m_methods[methodId] == NULL)
            return MethodNotImpl;
        
        return (RetType)(m_methods[methodId]->Invoke(sock, in));
    }
    unsigned InterfaceId()
    {
        return m_ifId;
    }
  protected:
    unsigned m_ifId;
    MethodBase *m_methods[MAX_METHODS];
};

template <typename Req>
int PBEncodingPolicy::DecodeIn(MeSSage *in, Req &req)
{
    if((in->Hdr().encodingType) & PROTOBUF_ENCODING)
    {
        bool ret = req.ParseFromArray(in->Payload(), in->Len() - sizeof(MeSSHeader));
        if (!ret)
        {
            // Parsing failed, return error
            return Interface::DecodeFailure;
        }
    }
    else
    {
        throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, "Expected ProtoBuf encoding policy");
    }
    return 0;
}

template <typename Resp>
int PBEncodingPolicy::EncodeOut(MeSSage *in, Resp &resp, MeSSage *&out)
{
    unsigned sz = resp.ByteSize();
    out = MeSSage::CreateRespMessage(*in, sz, PROTOBUF_ENCODING);
    bool ret = resp.SerializeToArray(out->Payload(), sz);
    if (!ret)
    {
        throw MeSSExceptionLog(Logger::EACC_LOG_CRITICAL, 
                "Protobuf Encode failed!");
    }

    return 0;
} 
 
}

#endif // __EACC_Interface_h__
