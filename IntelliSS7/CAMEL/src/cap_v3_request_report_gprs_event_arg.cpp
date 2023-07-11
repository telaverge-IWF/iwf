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


#include <cap_v3_request_report_gprs_event_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescSequenceOf.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace cap_v3;




////////// Begin Nested Class(es) //////////


// Type GPRS_ReferenceNumber is a reference => no code generated.



////////// Begin Nested Class //////////


// Type GPRSEvent is a reference => no code generated.

////////// End Nested Class //////////

AsnDescObject* RequestReportGPRSEventArg::GPRSEvents::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_CAMEL) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new GPRSEvents(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = GetGPRSEventStaticDescription();
        staticDesc.SetNamedTypeName("gPRSEvents");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestReportGPRSEventArg::GPRSEvents::GetGPRSEventStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRSEvent(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GPRSEvent::GetGPRSEventTypeStaticDescription();
        staticDesc._elementVect[1] = GPRSEvent::GetMonitorModeStaticDescription();
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}


// Type PDPID is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* RequestReportGPRSEventArg::GetStaticDescription()
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

        staticDesc.SetCloneForFactory(new RequestReportGPRSEventArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetGPRS_ReferenceNumberStaticDescription();
        staticDesc._elementVect[1] = GetGPRSEventsStaticDescription();
        staticDesc._elementVect[2] = GetPDPIDStaticDescription();
        staticDesc.SetTypeName("RequestReportGPRSEventArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestReportGPRSEventArg::GetGPRS_ReferenceNumberStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRS_ReferenceNumber(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 0));
        staticDesc._elementVect[0] = GPRS_ReferenceNumber::GetGPRS_ReferenceStaticDescription();
        staticDesc._elementVect[1] = GPRS_ReferenceNumber::GetGprsSSF_AddressStaticDescription();
        staticDesc.SetNamedTypeName("gPRS-ReferenceNumber");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestReportGPRSEventArg::GetGPRSEventsStaticDescription()
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
        staticDesc.SetCloneForFactory(new GPRSEvents(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 10;
        staticDesc._element = GPRSEvents::GetGPRSEventStaticDescription();
        staticDesc.SetNamedTypeName("gPRSEvents");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* RequestReportGPRSEventArg::GetPDPIDStaticDescription()
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
        staticDesc.SetCloneForFactory(new PDPID(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 1;
        staticDesc.SetNamedTypeName("pDPID");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





