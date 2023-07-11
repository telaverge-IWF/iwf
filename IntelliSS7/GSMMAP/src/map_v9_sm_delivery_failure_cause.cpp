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


#include <map_v9_sm_delivery_failure_cause.h>

#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type SM_EnumeratedDeliveryFailureCause is a reference => no code generated.

// Type SignalInfo is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SM_DeliveryFailureCause::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new SM_DeliveryFailureCause(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetSm_EnumeratedDeliveryFailureCauseStaticDescription();
        staticDesc._elementVect[1] = GetDiagnosticInfoStaticDescription();
        staticDesc._elementVect[2] = GetExtensionContainerStaticDescription();
        staticDesc.SetTypeName("SM-DeliveryFailureCause");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SM_DeliveryFailureCause::GetSm_EnumeratedDeliveryFailureCauseStaticDescription()
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
        staticDesc.SetCloneForFactory(new SM_EnumeratedDeliveryFailureCause(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(4);
        staticDesc._valueSet.insert(5);
        staticDesc._valueSet.insert(6);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"memoryCapacityExceeded", 0}, {"equipmentProtocolError", 1}, {"equipmentNotSM-Equipped", 2}, {"unknownServiceCentre", 3}, {"sc-Congestion", 4}, {"invalidSME-Address", 5}, {"subscriberNotSC-Subscriber", 6}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("sm-EnumeratedDeliveryFailureCause");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SM_DeliveryFailureCause::GetDiagnosticInfoStaticDescription()
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
        staticDesc.SetCloneForFactory(new SignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 200;
        staticDesc.SetNamedTypeName("diagnosticInfo");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SM_DeliveryFailureCause::GetExtensionContainerStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExtensionContainer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExtensionContainer::GetPrivateExtensionListStaticDescription();
        staticDesc._elementVect[1] = ExtensionContainer::GetPcs_ExtensionsStaticDescription();
        staticDesc.SetNamedTypeName("extensionContainer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




