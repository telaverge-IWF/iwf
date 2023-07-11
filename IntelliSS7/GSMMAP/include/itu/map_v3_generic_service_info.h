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


#if !defined(_MAP_V3_GENERIC_SERVICE_INFO_H_)
#define _MAP_V3_GENERIC_SERVICE_INFO_H_

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

#include <map_v3_ss_status.h>
#include <map_v3_cli_restriction_option.h>



namespace map_v3 {



class GenericServiceInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::SS_Status SS_Status;


        typedef map_v3::CliRestrictionOption CliRestrictionOption;


////////// End Nested Class(es) //////////

    GenericServiceInfo() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    GenericServiceInfo(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    GenericServiceInfo(const GenericServiceInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    GenericServiceInfo(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSs_StatusStaticDescription();
    static its::AsnDescObject* GetCliRestrictionOptionStaticDescription();

public:

    virtual ~GenericServiceInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GenericServiceInfo(*this);
    }

    virtual std::string GetName() const
    { return "GenericServiceInfo"; }

    void SetSs_Status(SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Status(const SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    const SS_Status& GetSs_Status() const
    {
        return static_cast<const SS_Status&> (ElementAt(0));
    }

    void SetCliRestrictionOption(CliRestrictionOption* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCliRestrictionOptionStaticDescription());
        AddElement(1, element);
    }

    void SetCliRestrictionOption(const CliRestrictionOption& element)
    {
        its::AsnObject& asnObject = const_cast<CliRestrictionOption&>(element);
        asnObject.SetDescription(GetCliRestrictionOptionStaticDescription());
        AddElement(1, element);
    }

    bool OptionCliRestrictionOption() const
    {
        return Contains(1);
    }

    const CliRestrictionOption& GetCliRestrictionOption() const
    {
        ITS_REQUIRE(OptionCliRestrictionOption());
        return static_cast<const CliRestrictionOption&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_GENERIC_SERVICE_INFO_H_)
