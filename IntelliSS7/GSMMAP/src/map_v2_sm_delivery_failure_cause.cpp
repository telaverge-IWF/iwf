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


#include <map_v2_sm_delivery_failure_cause.h>

#include <AsnDescChoice.h>
#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>


using namespace its;
using namespace map_v2;




////////// Begin Nested Class(es) //////////


// Type SM_DeliveryFailureCauseWithDiagnostic is a reference => no code generated.

// Type SM_EnumeratedDeliveryFailureCause is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* SM_DeliveryFailureCause::GetStaticDescription()
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
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new SM_DeliveryFailureCause(&staticDesc));
        staticDesc._choiceList.push_back(GetSm_DeliveryFailureCauseWithDiagnosticStaticDescription());
        staticDesc._choiceList.push_back(GetSm_EnumeratedDeliveryFailureCauseStaticDescription());
        staticDesc.SetTypeName("SM-DeliveryFailureCause");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* SM_DeliveryFailureCause::GetSm_DeliveryFailureCauseWithDiagnosticStaticDescription()
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
        staticDesc.SetCloneForFactory(new SM_DeliveryFailureCauseWithDiagnostic(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = SM_DeliveryFailureCauseWithDiagnostic::GetSm_EnumeratedDeliveryFailureCauseStaticDescription();
        staticDesc._elementVect[1] = SM_DeliveryFailureCauseWithDiagnostic::GetDiagnosticInfoStaticDescription();
        staticDesc.SetNamedTypeName("sm-DeliveryFailureCauseWithDiagnostic");
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





