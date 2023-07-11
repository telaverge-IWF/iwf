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


#if !defined(_MAP_V3_USSD_ARG_H_)
#define _MAP_V3_USSD_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_ussd_data_coding_scheme.h>
#include <map_v3_ussd_string.h>



namespace map_v3 {



class USSD_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::USSD_DataCodingScheme USSD_DataCodingScheme;


        typedef map_v3::USSD_String USSD_String;


////////// End Nested Class(es) //////////

    USSD_Arg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    USSD_Arg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    USSD_Arg(const USSD_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    USSD_Arg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetUssd_DataCodingSchemeStaticDescription();
    static its::AsnDescObject* GetUssd_StringStaticDescription();

public:

    virtual ~USSD_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new USSD_Arg(*this);
    }

    virtual std::string GetName() const
    { return "USSD_Arg"; }

    void SetUssd_DataCodingScheme(USSD_DataCodingScheme* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUssd_DataCodingSchemeStaticDescription());
        AddElement(0, element);
    }

    void SetUssd_DataCodingScheme(const USSD_DataCodingScheme& element)
    {
        its::AsnObject& asnObject = const_cast<USSD_DataCodingScheme&>(element);
        asnObject.SetDescription(GetUssd_DataCodingSchemeStaticDescription());
        AddElement(0, element);
    }

    const USSD_DataCodingScheme& GetUssd_DataCodingScheme() const
    {
        return static_cast<const USSD_DataCodingScheme&> (ElementAt(0));
    }

    void SetUssd_String(USSD_String* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUssd_StringStaticDescription());
        AddElement(1, element);
    }

    void SetUssd_String(const USSD_String& element)
    {
        its::AsnObject& asnObject = const_cast<USSD_String&>(element);
        asnObject.SetDescription(GetUssd_StringStaticDescription());
        AddElement(1, element);
    }

    const USSD_String& GetUssd_String() const
    {
        return static_cast<const USSD_String&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_USSD_ARG_H_)

