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


#include <inap_cs2_bcsm_event.h>

#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>
#include <AsnDescChoice.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type EventTypeBCSM is a reference => no code generated.

// Type MonitorMode is a reference => no code generated.

// Type LegID is a reference => no code generated.

// Type DpSpecificCriteria is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* BCSMEvent::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(4);

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

        staticDesc.SetCloneForFactory(new BCSMEvent(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetEventTypeBCSMStaticDescription();
        staticDesc._elementVect[1] = GetMonitorModeStaticDescription();
        staticDesc._elementVect[2] = GetLegIDStaticDescription();
        staticDesc._elementVect[3] = GetDpSpecificCriteriaStaticDescription();
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
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        staticDesc._valueSet.insert(6);
        staticDesc._valueSet.insert(7);
        staticDesc._valueSet.insert(8);
        staticDesc._valueSet.insert(9);
        staticDesc._valueSet.insert(10);
        staticDesc._valueSet.insert(12);
        staticDesc._valueSet.insert(13);
        staticDesc._valueSet.insert(14);
        staticDesc._valueSet.insert(15);
        staticDesc._valueSet.insert(16);
        staticDesc._valueSet.insert(17);
        staticDesc._valueSet.insert(18);
        staticDesc._valueSet.insert(19);
        staticDesc._valueSet.insert(20);
        staticDesc._valueSet.insert(21);
        staticDesc._valueSet.insert(22);
        staticDesc._valueSet.insert(23);
        staticDesc._valueSet.insert(24);
        staticDesc._valueSet.insert(25);
        staticDesc._valueSet.insert(26);
        staticDesc._valueSet.insert(27);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"origAttemptAuthorized", 1}, {"collectedInfo", 2}, {"analysedInformation", 3}, {"routeSelectFailure", 4}, {"oCalledPartyBusy", 5}, {"oNoAnswer", 6}, {"oAnswer", 7}, {"oMidCall", 8}, {"oDisconnect", 9}, {"oAbandon", 10}, {"termAttemptAuthorized", 12}, {"tBusy", 13}, {"tNoAnswer", 14}, {"tAnswer", 15}, {"tMidCall", 16}, {"tDisconnect", 17}, {"tAbandon", 18}, {"oTermSeized", 19}, {"oSuspended", 20}, {"tSuspended", 21}, {"origAttempt", 22}, {"termAttempt", 23}, {"oReAnswer", 24}, {"tReAnswer", 25}, {"facilitySelectedAndAvailable", 26}, {"callAccepted", 27}, {NULL, 0}};
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

AsnDescObject* BCSMEvent::GetDpSpecificCriteriaStaticDescription()
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
        staticDesc.SetCloneForFactory(new DpSpecificCriteria(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 30));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(DpSpecificCriteria::GetNumberOfDigitsStaticDescription());
        staticDesc._choiceList.push_back(DpSpecificCriteria::GetApplicationTimerStaticDescription());
        staticDesc._choiceList.push_back(DpSpecificCriteria::GetMidCallControlInfoStaticDescription());
        staticDesc.SetNamedTypeName("dpSpecificCriteria");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





