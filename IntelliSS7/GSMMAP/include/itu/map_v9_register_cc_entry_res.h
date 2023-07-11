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


#if !defined(_MAP_V9_REGISTER_CC_ENTRY_RES_H_)
#define _MAP_V9_REGISTER_CC_ENTRY_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v9_ccbs_feature.h>



namespace map_v9 {



class RegisterCC_EntryRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::CCBS_Feature CCBS_Feature;


////////// End Nested Class(es) //////////

    RegisterCC_EntryRes() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    RegisterCC_EntryRes(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    RegisterCC_EntryRes(const RegisterCC_EntryRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RegisterCC_EntryRes(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetCcbs_FeatureStaticDescription();

public:

    virtual ~RegisterCC_EntryRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RegisterCC_EntryRes(*this);
    }

    virtual std::string GetName() const
    { return "RegisterCC_EntryRes"; }

    void SetCcbs_Feature(CCBS_Feature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCcbs_FeatureStaticDescription());
        AddElement(0, element);
    }

    void SetCcbs_Feature(const CCBS_Feature& element)
    {
        its::AsnObject& asnObject = const_cast<CCBS_Feature&>(element);
        asnObject.SetDescription(GetCcbs_FeatureStaticDescription());
        AddElement(0, element);
    }

    bool OptionCcbs_Feature() const
    {
        return Contains(0);
    }

    const CCBS_Feature& GetCcbs_Feature() const
    {
        ITS_REQUIRE(OptionCcbs_Feature());
        return static_cast<const CCBS_Feature&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_REGISTER_CC_ENTRY_RES_H_)

