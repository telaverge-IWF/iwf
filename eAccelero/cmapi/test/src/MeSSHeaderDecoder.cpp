#include <MeSSage.h>
#include <iostream>
#include <iomanip>
#include <string.h>

#include "Allocator.h"
#include "AvaMgr_def.h"

using namespace eAccelero;

void PrintMeSSHeader(std::ostream& os, MeSSHeader& header)
{
    unsigned allocIdx = MeSSage::ExtractAllocId(header.tid);
    os << "  Version: " << (unsigned)header.version;
    os << "  Len: " << header.msgLen << std::endl;
    os << "  Code: " << (unsigned)header.code
       << "  MCast: " << (unsigned)header.mcast
       << "  Req: " << (unsigned)header.reqFlag
       << "  Enc: " << (unsigned)header.encodingType
       << "  Endian: " << (unsigned)header.endian << std::endl;
    os << "  MethodId: " << header.msgId.methodId
       << "  InterfaceId: " << header.msgId.interfaceId << std::endl;
    os << "  TID: " << header.tid
       << " (0x" << std::hex << header.tid << std::dec << ")"
       << " NodeId: " << MeSSage::ExtractSrcNodeId(header.tid)
       << " Bin: " << IndexAllocatorImpl::GetUserBits(allocIdx)
       << " Gen: " << (unsigned)IndexAllocatorImpl::GetGen(allocIdx)
       << " Idx: " << IndexAllocatorImpl::GetIdx(allocIdx) << std::endl;
    os << "  Source: [ " << header.src.compId << ", " 
       << header.src.instance << " ]"
       << "  Inst: " << header.src.instance - MESS_MIN_RDM_INSTANCE
       << std::endl;
}

static inline unsigned ToDigit(char c)
{
    if (isdigit(c))
    {
        return c - '0';
    }
    else
    {
        return 10 + tolower(c) - 'a';
    }
}

void PrintBuffer(uint8_t *buf, int len)
{
    for (int i = 0; i < len; i++)
    {
        std::cout << std::hex << (unsigned)buf[i] << " ";
    }
    std::cout << std::dec<< std::endl;
}

void PrintPBMessage(const google::protobuf::Message& msg)
{
    using google::protobuf::Reflection;
    using google::protobuf::Message;
    using google::protobuf::FieldDescriptor;

    std::vector<const FieldDescriptor*> fields;
    std::vector<const FieldDescriptor*>::iterator it;

    const Reflection *refl = msg.GetReflection();
    refl->ListFields(msg, &fields);

    for (it = fields.begin(); it != fields.end(); it++)
    {
        const FieldDescriptor* fd = (*it);
        std::cout << fd->full_name() << " = ";
        switch(fd->type())
        {
            case FieldDescriptor::TYPE_INT32:
                std::cout << refl->GetInt32(msg, fd) << std::endl;
                break;
            case FieldDescriptor::TYPE_UINT32:
                std::cout << refl->GetUInt32(msg, fd) << std::endl;
                break;
            case FieldDescriptor::TYPE_STRING:
                std::cout << refl->GetString(msg, fd) << std::endl;
                break;
            case FieldDescriptor::TYPE_FIXED32:
                std::cout << refl->GetUInt32(msg, fd) << std::endl;
                break;
            case FieldDescriptor::TYPE_BOOL:
                std::cout << refl->GetBool(msg, fd) << std::endl;
                break;
            case FieldDescriptor::TYPE_ENUM:
                std::cout << refl->GetEnum(msg, fd)->number() << std::endl;
                break;
            case FieldDescriptor::TYPE_MESSAGE:
                if (!fd->is_repeated())
                {
                    PrintPBMessage(refl->GetMessage(msg, fd));
                }
                else
                {
                }
                break;
            case FieldDescriptor::TYPE_INT64:
                std::cout << refl->GetInt64(msg, fd) << std::endl;
                break;
            case FieldDescriptor::TYPE_UINT64:
                std::cout << refl->GetUInt64(msg, fd) << std::endl;
                break;
            default:
                std::cout << " --- Unhandled Field type ---\n";
        }
    }

}

void PrintPB(google::protobuf::Message& msg, uint8_t *buf, int len)
{
    //bool res = true;
    bool res = msg.ParseFromArray(buf,len);
    if (!res)
    {
        std::cout << "ERROR: Decoding protocol buffer message failed\n";
        return;
    }

    PrintPBMessage(msg);
}

void PrintMessage(MeSSHeader& hdr, uint8_t *buf, int len)
{
    std::cout << "Buffer Len: " << len << std::endl;

    if (hdr.msgId.interfaceId == I_AVAMGRPEERSTATUSINTERFACE &&
        hdr.msgId.methodId == M_AVAMGRPEERSTATUSINTERFACE_AVAILABILITYPEERPINGREQUEST)
    {
        if (hdr.reqFlag)
        {
            PeerPingReq req;
            PrintPB(req, buf, len);
        }
        else
        {
            PeerPingResp resp;
#if 0
            bool res = resp.ParseFromArray(buf,len);
            if (!res)
            {
                std::cout << "ERROR: Decoding protocol buffer message failed\n";
                return;
            }
#endif
            PrintPB(resp, buf, len);
        }
    }
}

int main()
{
    char strBuffer[1024*16];
    uint8_t buffer[1024*16];
    std::cout << "Enter the buffer: " << std::endl;
    std::cin.get(strBuffer, 1024);

    unsigned j = 0;
    for (unsigned i = 0; i < strlen(strBuffer); i++)
    {
        if (strBuffer[i] == ' ') continue; // skip space
        if (strBuffer[i] == ':') continue; // delimiter as :
        buffer[j++] = (ToDigit(strBuffer[i]) << 4) |
                    ToDigit(strBuffer[i+1]); 
        i++;
    }

    //std::cout << "Input Buffer: \n";
    //PrintBuffer(buffer, j);

    std::cout << "\nMeSS Header Details:\n";
    MeSSHeader* hdr = (MeSSHeader*)buffer;
    PrintMeSSHeader(std::cout, *hdr);

    PrintMessage(*hdr, buffer + sizeof(MeSSHeader),
                 hdr->msgLen - sizeof(MeSSHeader));

    return 0;
}

