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


#include <map_v13_failure_cause_param.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v13;



AsnDescObject* FailureCauseParam::GetStaticDescription()
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
        staticDesc.SetCloneForFactory(new FailureCauseParam(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._clauseExtensible = true;
        staticDesc._valueSet.insert(0);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"limitReachedOnNumberOfConcurrentLocationRequests", 0}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("FailureCauseParam");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long FailureCauseParam::Get(const std::string& valueName) const
{
    if (valueName == "limitReachedOnNumberOfConcurrentLocationRequests")
    {
        return 0;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string FailureCauseParam::Get(long value) const
{
    if (value == 0)
    {
        return "limitReachedOnNumberOfConcurrentLocationRequests";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string FailureCauseParam::GetExt(long value) const
{
    return "";
}





