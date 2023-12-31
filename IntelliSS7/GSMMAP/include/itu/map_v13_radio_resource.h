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


#if !defined(_MAP_V13_RADIO_RESOURCE_H_)
#define _MAP_V13_RADIO_RESOURCE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <map_v13_radio_resource_information.h>
#include <map_v13_rab_id.h>



namespace map_v13 {



class RadioResource : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::RadioResourceInformation RadioResourceInformation;


        typedef map_v13::RAB_Id RAB_Id;


////////// End Nested Class(es) //////////

    RadioResource() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RadioResource(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RadioResource(const RadioResource& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RadioResource(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetRadioResourceInformationStaticDescription();
    static its::AsnDescObject* GetRab_IdStaticDescription();

public:

    virtual ~RadioResource()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RadioResource(*this);
    }

    virtual std::string GetName() const
    { return "RadioResource"; }

    void SetRadioResourceInformation(RadioResourceInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRadioResourceInformationStaticDescription());
        AddElement(0, element);
    }

    void SetRadioResourceInformation(const RadioResourceInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RadioResourceInformation&>(element);
        asnObject.SetDescription(GetRadioResourceInformationStaticDescription());
        AddElement(0, element);
    }

    const RadioResourceInformation& GetRadioResourceInformation() const
    {
        return static_cast<const RadioResourceInformation&> (ElementAt(0));
    }

    void SetRab_Id(RAB_Id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRab_IdStaticDescription());
        AddElement(1, element);
    }

    void SetRab_Id(const RAB_Id& element)
    {
        its::AsnObject& asnObject = const_cast<RAB_Id&>(element);
        asnObject.SetDescription(GetRab_IdStaticDescription());
        AddElement(1, element);
    }

    const RAB_Id& GetRab_Id() const
    {
        return static_cast<const RAB_Id&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_RADIO_RESOURCE_H_)

