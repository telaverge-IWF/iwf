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


#if !defined(_CAP_V3_QUALITY_OF_SERVICE_H_)
#define _CAP_V3_QUALITY_OF_SERVICE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>

#include <cap_v3_gprs_qo_s.h>



namespace cap_v3 {



class QualityOfService : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::GPRS_QoS GPRS_QoS;


////////// End Nested Class(es) //////////

    QualityOfService() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    QualityOfService(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    QualityOfService(const QualityOfService& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    QualityOfService(its::AsnDescObject* description) : its::AsnSequence(3, description)
    {
        // Nothing to do.
    }

protected:

    void Initialize()
    {
        _description = GetStaticDescription();
    }

public:

    static its::AsnDescObject* GetStaticDescription();

    static its::AsnDescObject* GetRequested_QoSStaticDescription();
    static its::AsnDescObject* GetSubscribed_QoSStaticDescription();
    static its::AsnDescObject* GetNegotiated_QoSStaticDescription();

public:

    virtual ~QualityOfService()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new QualityOfService(*this);
    }

    virtual std::string GetName() const
    { return "QualityOfService"; }

    void SetRequested_QoS(GPRS_QoS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequested_QoSStaticDescription());
        AddElement(0, element);
    }

    void SetRequested_QoS(const GPRS_QoS& element)
    {
        its::AsnObject& asnObject = const_cast<GPRS_QoS&>(element);
        asnObject.SetDescription(GetRequested_QoSStaticDescription());
        AddElement(0, element);
    }

    bool OptionRequested_QoS() const
    {
        return Contains(0);
    }

    const GPRS_QoS& GetRequested_QoS() const
    {
        ITS_REQUIRE(OptionRequested_QoS());
        return static_cast<const GPRS_QoS&> (ElementAt(0));
    }

    void SetSubscribed_QoS(GPRS_QoS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSubscribed_QoSStaticDescription());
        AddElement(1, element);
    }

    void SetSubscribed_QoS(const GPRS_QoS& element)
    {
        its::AsnObject& asnObject = const_cast<GPRS_QoS&>(element);
        asnObject.SetDescription(GetSubscribed_QoSStaticDescription());
        AddElement(1, element);
    }

    bool OptionSubscribed_QoS() const
    {
        return Contains(1);
    }

    const GPRS_QoS& GetSubscribed_QoS() const
    {
        ITS_REQUIRE(OptionSubscribed_QoS());
        return static_cast<const GPRS_QoS&> (ElementAt(1));
    }

    void SetNegotiated_QoS(GPRS_QoS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNegotiated_QoSStaticDescription());
        AddElement(2, element);
    }

    void SetNegotiated_QoS(const GPRS_QoS& element)
    {
        its::AsnObject& asnObject = const_cast<GPRS_QoS&>(element);
        asnObject.SetDescription(GetNegotiated_QoSStaticDescription());
        AddElement(2, element);
    }

    bool OptionNegotiated_QoS() const
    {
        return Contains(2);
    }

    const GPRS_QoS& GetNegotiated_QoS() const
    {
        ITS_REQUIRE(OptionNegotiated_QoS());
        return static_cast<const GPRS_QoS&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_QUALITY_OF_SERVICE_H_)

