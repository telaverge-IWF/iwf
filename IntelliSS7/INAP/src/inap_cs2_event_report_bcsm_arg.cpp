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


#include <inap_cs2_event_report_bcsm_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescEnumerated.h>
#include <AsnDescOctetString.h>
#include <AsnDescChoice.h>
#include <AsnDescInteger.h>


using namespace its;
using namespace inap_cs2;




////////// Begin Nested Class(es) //////////


// Type EventTypeBCSM is a reference => no code generated.

// Type CorrelationID is a reference => no code generated.

// Type EventSpecificInformationBCSM is a reference => no code generated.

// Type LegID is a reference => no code generated.

// Type MiscCallInfo is a reference => no code generated.



////////// Begin Nested Class //////////


// Type ExtensionField is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* EventReportBCSMArg::Extensions::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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

        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::Extensions::GetExtensionFieldStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExtensionField(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = ExtensionField::GetTypeStaticDescription();
        staticDesc._elementVect[1] = ExtensionField::GetCriticalityStaticDescription();
        staticDesc._elementVect[2] = ExtensionField::GetValueStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type ComponentType is a reference => no code generated.

// Type ComponentCorrelationID is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* EventReportBCSMArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(8);

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

        staticDesc.SetCloneForFactory(new EventReportBCSMArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetEventTypeBCSMStaticDescription();
        staticDesc._elementVect[1] = GetBcsmEventCorrelationIDStaticDescription();
        staticDesc._elementVect[2] = GetEventSpecificInformationBCSMStaticDescription();
        staticDesc._elementVect[3] = GetLegIDStaticDescription();
        staticDesc._elementVect[4] = GetMiscCallInfoStaticDescription();
        staticDesc._elementVect[5] = GetExtensionsStaticDescription();
        staticDesc._elementVect[6] = GetComponentTypeStaticDescription();
        staticDesc._elementVect[7] = GetComponentCorrelationIDStaticDescription();
        staticDesc.SetTypeName("EventReportBCSMArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::GetEventTypeBCSMStaticDescription()
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

AsnDescObject* EventReportBCSMArg::GetBcsmEventCorrelationIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new CorrelationID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 0;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("bcsmEventCorrelationID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::GetEventSpecificInformationBCSMStaticDescription()
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
        staticDesc.SetCloneForFactory(new EventSpecificInformationBCSM(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetCollectedInfoSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetAnalysedInfoSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetRouteSelectFailureSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOCalledPartyBusySpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetONoAnswerSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOAnswerSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOMidCallSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetODisconnectSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTBusySpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTNoAnswerSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTAnswerSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTMidCallSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTDisconnectSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOTermSeizedSpecificInfoStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOSuspendedStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTSuspendedStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOrigAttemptAuthorizedStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOReAnswerStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTReAnswerStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetFacilitySelectedAndAvailableStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetCallAcceptedStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetOAbandonStaticDescription());
        staticDesc._choiceList.push_back(EventSpecificInformationBCSM::GetTAbandonStaticDescription());
        staticDesc.SetNamedTypeName("eventSpecificInformationBCSM");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::GetLegIDStaticDescription()
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
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 3));
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

AsnDescObject* EventReportBCSMArg::GetMiscCallInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new MiscCallInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
        staticDesc._clauseDefault = true;
        {
            MiscCallInfo* miscCallInfo = new MiscCallInfo(&staticDesc);
            MiscCallInfo::MessageType* messageType = new MiscCallInfo::MessageType((long)0);
            miscCallInfo->SetMessageType(messageType);
            staticDesc.SetCloneForDefaultFactory(miscCallInfo);
        }
        staticDesc._elementVect[0] = MiscCallInfo::GetMessageTypeStaticDescription();
        staticDesc._elementVect[1] = MiscCallInfo::GetDpAssignmentStaticDescription();
        staticDesc.SetNamedTypeName("miscCallInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::GetExtensionsStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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
        staticDesc.SetCloneForFactory(new Extensions(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc._element = Extensions::GetExtensionFieldStaticDescription();
        staticDesc.SetNamedTypeName("extensions");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::GetComponentTypeStaticDescription()
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
        staticDesc.SetCloneForFactory(new ComponentType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 6));
        staticDesc._clauseOptional = true;
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"any", 0}, {"invoke", 1}, {"rResult", 2}, {"rError", 3}, {"rReject", 4}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("componentType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* EventReportBCSMArg::GetComponentCorrelationIDStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new ComponentCorrelationID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 8));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("componentCorrelationID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





