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


#if !defined(_MAP_V3_IMSI_WITH_LMSI_H_)
#define _MAP_V3_IMSI_WITH_LMSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_imsi.h>
#include <map_v3_lmsi.h>



namespace map_v3 {



class IMSI_WithLMSI : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::IMSI IMSI;


        typedef map_v3::LMSI LMSI;


////////// End Nested Class(es) //////////

    IMSI_WithLMSI() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    IMSI_WithLMSI(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    IMSI_WithLMSI(const IMSI_WithLMSI& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    IMSI_WithLMSI(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetLmsiStaticDescription();

public:

    virtual ~IMSI_WithLMSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new IMSI_WithLMSI(*this);
    }

    virtual std::string GetName() const
    { return "IMSI_WithLMSI"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetLmsi(LMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    void SetLmsi(const LMSI& element)
    {
        its::AsnObject& asnObject = const_cast<LMSI&>(element);
        asnObject.SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    const LMSI& GetLmsi() const
    {
        return static_cast<const LMSI&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_IMSI_WITH_LMSI_H_)

