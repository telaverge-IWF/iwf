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


#if !defined(_MAP_V13_EPS_DATA_LIST_H_)
#define _MAP_V13_EPS_DATA_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_apn_configuration.h>



namespace map_v13 {



class EPS_DataList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::APN_Configuration APN_Configuration;


////////// End Nested Class //////////

    EPS_DataList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    EPS_DataList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    EPS_DataList(const EPS_DataList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    EPS_DataList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetAPN_ConfigurationStaticDescription();

public:

    virtual ~EPS_DataList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EPS_DataList(*this);
    }

    virtual std::string GetName() const
    { return "EPS_DataList"; }

    void AddElement(APN_Configuration* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAPN_ConfigurationStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const APN_Configuration& element)
    {
        its::AsnObject& asnObject = const_cast<APN_Configuration&>(element);
        asnObject.SetDescription(GetAPN_ConfigurationStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const APN_Configuration& ElementAt(int index) const
    {
        return static_cast<const APN_Configuration&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_EPS_DATA_LIST_H_)

