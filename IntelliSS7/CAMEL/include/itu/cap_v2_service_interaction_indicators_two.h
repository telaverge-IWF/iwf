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


#if !defined(_CAP_V2_SERVICE_INTERACTION_INDICATORS_TWO_H_)
#define _CAP_V2_SERVICE_INTERACTION_INDICATORS_TWO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <cap_v2_bothway_through_connection_ind.h>



namespace cap_v2 {



class ServiceInteractionIndicatorsTwo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v2::BothwayThroughConnectionInd BothwayThroughConnectionInd;


////////// End Nested Class(es) //////////

    ServiceInteractionIndicatorsTwo() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    ServiceInteractionIndicatorsTwo(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    ServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ServiceInteractionIndicatorsTwo(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetBothwayThroughConnectionIndStaticDescription();

public:

    virtual ~ServiceInteractionIndicatorsTwo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ServiceInteractionIndicatorsTwo(*this);
    }

    virtual std::string GetName() const
    { return "ServiceInteractionIndicatorsTwo"; }

    void SetBothwayThroughConnectionInd(BothwayThroughConnectionInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBothwayThroughConnectionIndStaticDescription());
        AddElement(0, element);
    }

    void SetBothwayThroughConnectionInd(const BothwayThroughConnectionInd& element)
    {
        its::AsnObject& asnObject = const_cast<BothwayThroughConnectionInd&>(element);
        asnObject.SetDescription(GetBothwayThroughConnectionIndStaticDescription());
        AddElement(0, element);
    }

    bool OptionBothwayThroughConnectionInd() const
    {
        return Contains(0);
    }

    const BothwayThroughConnectionInd& GetBothwayThroughConnectionInd() const
    {
        ITS_REQUIRE(OptionBothwayThroughConnectionInd());
        return static_cast<const BothwayThroughConnectionInd&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_SERVICE_INTERACTION_INDICATORS_TWO_H_)

