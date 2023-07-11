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


#include <cap_v1_bcsm_event.h>

#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace cap_v1;




////////// Begin Nested Class(es) //////////


// Type EventTypeBCSM is a reference => no code generated.

// Type MonitorMode is a reference => no code generated.

// Type LegID is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* BCSMEvent::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(3);

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

        staticDesc.SetCloneForFactory(new BCSMEvent(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetEventTypeBCSMStaticDescription();
        staticDesc._elementVect[1] = GetMonitorModeStaticDescription();
        staticDesc._elementVect[2] = GetLegIDStaticDescription();
        staticDesc.SetTypeName("BCSMEvent");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* BCSMEvent::GetEventTypeBCSMStaticDescription()
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
        staticDesc.SetCloneForFactory(new EventTypeBCSM(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(7);
        staticDesc._valueSet.insert(9);
        staticDesc._valueSet.insert(12);
        staticDesc._valueSet.insert(15);
        staticDesc._valueSet.insert(17);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"collectedInfo", 2}, {"oAnswer", 7}, {"oDisconnect", 9}, {"termAttemptAuthorized", 12}, {"tAnswer", 15}, {"tDisconnect", 17}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("eventTypeBCSM");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* BCSMEvent::GetMonitorModeStaticDescription()
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
        staticDesc.SetCloneForFactory(new MonitorMode(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"interrupted", 0}, {"notifyAndContinue", 1}, {"transparent", 2}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("monitorMode");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* BCSMEvent::GetLegIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescChoice staticDesc;

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
        staticDesc.SetCloneForFactory(new LegID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(LegID::GetSendingSideIDStaticDescription());
        staticDesc._choiceList.push_back(LegID::GetReceivingSideIDStaticDescription());
        staticDesc.SetNamedTypeName("legID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





