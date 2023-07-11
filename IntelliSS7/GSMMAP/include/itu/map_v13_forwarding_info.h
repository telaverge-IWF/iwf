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


#if !defined(_MAP_V13_FORWARDING_INFO_H_)
#define _MAP_V13_FORWARDING_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>

#include <map_v13_ss_code.h>
#include <map_v13_forwarding_feature_list.h>



namespace map_v13 {



class ForwardingInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::SS_Code SS_Code;


        typedef map_v13::ForwardingFeatureList ForwardingFeatureList;


////////// End Nested Class(es) //////////

    ForwardingInfo() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ForwardingInfo(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingInfo(const ForwardingInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ForwardingInfo(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSs_CodeStaticDescription();
    static its::AsnDescObject* GetForwardingFeatureListStaticDescription();

public:

    virtual ~ForwardingInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardingInfo(*this);
    }

    virtual std::string GetName() const
    { return "ForwardingInfo"; }

    void SetSs_Code(SS_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Code(const SS_Code& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Code&>(element);
        asnObject.SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    bool OptionSs_Code() const
    {
        return Contains(0);
    }

    const SS_Code& GetSs_Code() const
    {
        ITS_REQUIRE(OptionSs_Code());
        return static_cast<const SS_Code&> (ElementAt(0));
    }

    void SetForwardingFeatureList(ForwardingFeatureList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingFeatureListStaticDescription());
        AddElement(1, element);
    }

    void SetForwardingFeatureList(const ForwardingFeatureList& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingFeatureList&>(element);
        asnObject.SetDescription(GetForwardingFeatureListStaticDescription());
        AddElement(1, element);
    }

    const ForwardingFeatureList& GetForwardingFeatureList() const
    {
        return static_cast<const ForwardingFeatureList&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_FORWARDING_INFO_H_)

