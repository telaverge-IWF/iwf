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


#include <map_v13_logging_duration.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* LoggingDuration::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new LoggingDuration(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"d600sec", 0}, {"d1200sec", 1}, {"d2400sec", 2}, {"d3600sec", 3}, {"d5400sec", 4}, {"d7200sec", 5}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("LoggingDuration");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long LoggingDuration::Get(const std::string& valueName) const
{
    if (valueName == "d600sec")
    {
        return 0;
    }
    else if (valueName == "d1200sec")
    {
        return 1;
    }
    else if (valueName == "d2400sec")
    {
        return 2;
    }
    else if (valueName == "d3600sec")
    {
        return 3;
    }
    else if (valueName == "d5400sec")
    {
        return 4;
    }
    else if (valueName == "d7200sec")
    {
        return 5;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string LoggingDuration::Get(long value) const
{
    if (value == 0)
    {
        return "d600sec";
    }
    else if (value == 1)
    {
        return "d1200sec";
    }
    else if (value == 2)
    {
        return "d2400sec";
    }
    else if (value == 3)
    {
        return "d3600sec";
    }
    else if (value == 4)
    {
        return "d5400sec";
    }
    else if (value == 5)
    {
        return "d7200sec";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string LoggingDuration::GetExt(long value) const
{
    return "";
}





