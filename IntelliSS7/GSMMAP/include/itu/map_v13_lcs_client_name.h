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


#if !defined(_MAP_V13_LCS_CLIENT_NAME_H_)
#define _MAP_V13_LCS_CLIENT_NAME_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>

#include <map_v13_ussd_data_coding_scheme.h>
#include <map_v13_name_string.h>
#include <map_v13_lcs_format_indicator.h>



namespace map_v13 {



class LCSClientName : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::USSD_DataCodingScheme USSD_DataCodingScheme;


        typedef map_v13::NameString NameString;


        typedef map_v13::LCS_FormatIndicator LCS_FormatIndicator;


////////// End Nested Class(es) //////////

    LCSClientName() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    LCSClientName(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    LCSClientName(const LCSClientName& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    LCSClientName(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetDataCodingSchemeStaticDescription();
    static its::AsnDescObject* GetNameStringStaticDescription();
    static its::AsnDescObject* GetLcs_FormatIndicatorStaticDescription();

public:

    virtual ~LCSClientName()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LCSClientName(*this);
    }

    virtual std::string GetName() const
    { return "LCSClientName"; }

    void SetDataCodingScheme(USSD_DataCodingScheme* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDataCodingSchemeStaticDescription());
        AddElement(0, element);
    }

    void SetDataCodingScheme(const USSD_DataCodingScheme& element)
    {
        its::AsnObject& asnObject = const_cast<USSD_DataCodingScheme&>(element);
        asnObject.SetDescription(GetDataCodingSchemeStaticDescription());
        AddElement(0, element);
    }

    const USSD_DataCodingScheme& GetDataCodingScheme() const
    {
        return static_cast<const USSD_DataCodingScheme&> (ElementAt(0));
    }

    void SetNameString(NameString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNameStringStaticDescription());
        AddElement(1, element);
    }

    void SetNameString(const NameString& element)
    {
        its::AsnObject& asnObject = const_cast<NameString&>(element);
        asnObject.SetDescription(GetNameStringStaticDescription());
        AddElement(1, element);
    }

    const NameString& GetNameString() const
    {
        return static_cast<const NameString&> (ElementAt(1));
    }

    void SetLcs_FormatIndicator(LCS_FormatIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcs_FormatIndicatorStaticDescription());
        AddElement(2, element);
    }

    void SetLcs_FormatIndicator(const LCS_FormatIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<LCS_FormatIndicator&>(element);
        asnObject.SetDescription(GetLcs_FormatIndicatorStaticDescription());
        AddElement(2, element);
    }

    bool OptionLcs_FormatIndicator() const
    {
        return Contains(2);
    }

    const LCS_FormatIndicator& GetLcs_FormatIndicator() const
    {
        ITS_REQUIRE(OptionLcs_FormatIndicator());
        return static_cast<const LCS_FormatIndicator&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_LCS_CLIENT_NAME_H_)

