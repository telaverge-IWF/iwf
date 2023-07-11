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


#include <inap_cs2_requested_utsi.h>

#include <AsnDescSequence.h>
#include <AsnDescOctetString.h>
#include <AsnDescEnumerated.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type USIServiceIndicator is a reference => no code generated.

// Type USIMonitorMode is a reference => no code generated.

// Type LegID is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* RequestedUTSI::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new RequestedUTSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetUSIServiceIndicatorStaticDescription();
        staticDesc._elementVect[1] = GetUSImonitorModeStaticDescription();
        staticDesc._elementVect[2] = GetLegIDStaticDescription();
        staticDesc.SetTypeName("RequestedUTSI");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestedUTSI::GetUSIServiceIndicatorStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new USIServiceIndicator(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 15;
        staticDesc.SetNamedTypeName("uSIServiceIndicator");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestedUTSI::GetUSImonitorModeStaticDescription()
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
        staticDesc.SetCloneForFactory(new USIMonitorMode(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"monitoringActive", 0}, {"monitoringInactive", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("uSImonitorMode");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestedUTSI::GetLegIDStaticDescription()
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
        staticDesc._clauseDefault = true;
        {
            LegID* legId = new LegID(&staticDesc);
            std::vector<byte> array;
            array.push_back(0x01U);
            LegType* legType = new LegType(array);
            legId->SetChoiceSendingSideID(legType);
            staticDesc.SetCloneForDefaultFactory(legId);
        }
        staticDesc._choiceList.push_back(LegID::GetSendingSideIDStaticDescription());
        staticDesc._choiceList.push_back(LegID::GetReceivingSideIDStaticDescription());
        staticDesc.SetNamedTypeName("legID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





