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


#include <cap_v2_bothway_through_connection_ind.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace cap_v2;



AsnDescObject* BothwayThroughConnectionInd::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new BothwayThroughConnectionInd(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"bothwayPathRequired", 0}, {"bothwayPathNotRequired", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("BothwayThroughConnectionInd");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long BothwayThroughConnectionInd::Get(const std::string& valueName) const
{
    if (valueName == "bothwayPathRequired")
    {
        return 0;
    }
    else if (valueName == "bothwayPathNotRequired")
    {
        return 1;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string BothwayThroughConnectionInd::Get(long value) const
{
    if (value == 0)
    {
        return "bothwayPathRequired";
    }
    else if (value == 1)
    {
        return "bothwayPathNotRequired";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string BothwayThroughConnectionInd::GetExt(long value) const
{
    return "";
}





