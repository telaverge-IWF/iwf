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


#if !defined(_CAP_V3_GPRS_QO_S_H_)
#define _CAP_V3_GPRS_QO_S_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <cap_v3_qo_s_subscribed.h>
#include <cap_v3_ext_qo_s_subscribed.h>



namespace cap_v3 {



class GPRS_QoS : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::QoS_Subscribed QoS_Subscribed;


        typedef cap_v3::Ext_QoS_Subscribed Ext_QoS_Subscribed;


////////// End Nested Class(es) //////////

    GPRS_QoS() : its::AsnChoice(false)
    {
        Initialize();
    }

    GPRS_QoS(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    GPRS_QoS(const GPRS_QoS& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    GPRS_QoS(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    GPRS_QoS(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetShort_QoS_formatStaticDescription();
    static its::AsnDescObject* GetLong_QoS_formatStaticDescription();

public:

    virtual ~GPRS_QoS()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GPRS_QoS(*this);
    }

    virtual std::string GetName() const
    { return "GPRS_QoS"; }

    void SetChoiceShort_QoS_format(QoS_Subscribed* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetShort_QoS_formatStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceShort_QoS_format(const QoS_Subscribed& choice)
    {
        its::AsnObject& asnObject = const_cast<QoS_Subscribed&>(choice);
        asnObject.SetDescription(GetShort_QoS_formatStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceShort_QoS_format() const
    {
        return Contains(GetShort_QoS_formatStaticDescription()->TagIdentity());
    }

    const QoS_Subscribed& GetChoiceShort_QoS_format() const
    {
        ITS_REQUIRE(ChoiceShort_QoS_format());
        return static_cast<const QoS_Subscribed&> (GetChoice());
    }

    void SetChoiceLong_QoS_format(Ext_QoS_Subscribed* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetLong_QoS_formatStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceLong_QoS_format(const Ext_QoS_Subscribed& choice)
    {
        its::AsnObject& asnObject = const_cast<Ext_QoS_Subscribed&>(choice);
        asnObject.SetDescription(GetLong_QoS_formatStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceLong_QoS_format() const
    {
        return Contains(GetLong_QoS_formatStaticDescription()->TagIdentity());
    }

    const Ext_QoS_Subscribed& GetChoiceLong_QoS_format() const
    {
        ITS_REQUIRE(ChoiceLong_QoS_format());
        return static_cast<const Ext_QoS_Subscribed&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_GPRS_QO_S_H_)
