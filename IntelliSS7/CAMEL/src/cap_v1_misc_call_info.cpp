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


#include <cap_v1_misc_call_info.h>

#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>


using namespace its;
using namespace cap_v1;




////////// Begin Nested Class(es) //////////



AsnDescObject* MiscCallInfo::MessageType::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new MessageType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"request", 0}, {"notification", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetNamedTypeName("messageType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long MiscCallInfo::MessageType::Get(const std::string& valueName) const
{
    if (valueName == "request")
    {
        return 0;
    }
    else if (valueName == "notification")
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

std::string MiscCallInfo::MessageType::Get(long value) const
{
    if (value == 0)
    {
        return "request";
    }
    else if (value == 1)
    {
        return "notification";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string MiscCallInfo::MessageType::GetExt(long value) const
{
    return "";
}



AsnDescObject* MiscCallInfo::DpAssignment::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new DpAssignment(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"individualLine", 0}, {"groupBased", 1}, {"officeBased", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetNamedTypeName("dpAssignment");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long MiscCallInfo::DpAssignment::Get(const std::string& valueName) const
{
    if (valueName == "individualLine")
    {
        return 0;
    }
    else if (valueName == "groupBased")
    {
        return 1;
    }
    else if (valueName == "officeBased")
    {
        return 2;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string MiscCallInfo::DpAssignment::Get(long value) const
{
    if (value == 0)
    {
        return "individualLine";
    }
    else if (value == 1)
    {
        return "groupBased";
    }
    else if (value == 2)
    {
        return "officeBased";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string MiscCallInfo::DpAssignment::GetExt(long value) const
{
    return "";
}


////////// End Nested Class(es) //////////

AsnDescObject* MiscCallInfo::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(2);

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

        staticDesc.SetCloneForFactory(new MiscCallInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetMessageTypeStaticDescription();
        staticDesc._elementVect[1] = GetDpAssignmentStaticDescription();
        staticDesc.SetTypeName("MiscCallInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MiscCallInfo::GetMessageTypeStaticDescription()
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
        staticDesc.SetCloneForFactory(new MessageType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"request", 0}, {"notification", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("messageType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* MiscCallInfo::GetDpAssignmentStaticDescription()
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
        staticDesc.SetCloneForFactory(new DpAssignment(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"individualLine", 0}, {"groupBased", 1}, {"officeBased", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("dpAssignment");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




