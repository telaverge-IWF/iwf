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


#if !defined(_MAP_V13_MSISDN_BS_LIST_H_)
#define _MAP_V13_MSISDN_BS_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_msisdn_bs.h>



namespace map_v13 {



class MSISDN_BS_List : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::MSISDN_BS MSISDN_BS;


////////// End Nested Class //////////

    MSISDN_BS_List() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    MSISDN_BS_List(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    MSISDN_BS_List(const MSISDN_BS_List& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    MSISDN_BS_List(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetMSISDN_BSStaticDescription();

public:

    virtual ~MSISDN_BS_List()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MSISDN_BS_List(*this);
    }

    virtual std::string GetName() const
    { return "MSISDN_BS_List"; }

    void AddElement(MSISDN_BS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMSISDN_BSStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const MSISDN_BS& element)
    {
        its::AsnObject& asnObject = const_cast<MSISDN_BS&>(element);
        asnObject.SetDescription(GetMSISDN_BSStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const MSISDN_BS& ElementAt(int index) const
    {
        return static_cast<const MSISDN_BS&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_MSISDN_BS_LIST_H_)

