//
// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).
//
// Do not edit!
//
//
//
// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.
//
//


#include <map_v3_protocol_id.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v3;



AsnDescObject* ProtocolId::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new ProtocolId(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"gsm-0408", 1}, {"gsm-0806", 2}, {"gsm-BSSMAP", 3}, {"ets-300102-1", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("ProtocolId");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long ProtocolId::Get(const std::string& valueName) const
{
    if (valueName == "gsm-0408")
    {
        return 1;
    }
    else if (valueName == "gsm-0806")
    {
        return 2;
    }
    else if (valueName == "gsm-BSSMAP")
    {
        return 3;
    }
    else if (valueName == "ets-300102-1")
    {
        return 4;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string ProtocolId::Get(long value) const
{
    if (value == 1)
    {
        return "gsm-0408";
    }
    else if (value == 2)
    {
        return "gsm-0806";
    }
    else if (value == 3)
    {
        return "gsm-BSSMAP";
    }
    else if (value == 4)
    {
        return "ets-300102-1";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string ProtocolId::GetExt(long value) const
{
    return "";
}




