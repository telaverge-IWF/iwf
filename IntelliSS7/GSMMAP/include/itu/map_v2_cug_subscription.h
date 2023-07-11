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


#if !defined(_MAP_V2_CUG_SUBSCRIPTION_H_)
#define _MAP_V2_CUG_SUBSCRIPTION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>
#include <AsnSequenceOf.h>

#include <map_v2_cug_index.h>
#include <map_v2_cug_interlock.h>
#include <map_v2_intra_cug_options.h>
#include <map_v2_basic_service_group_list.h>



namespace map_v2 {



class CUG_Subscription : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::CUG_Index CUG_Index;


        typedef map_v2::CUG_Interlock CUG_Interlock;


        typedef map_v2::IntraCUG_Options IntraCUG_Options;


        typedef map_v2::BasicServiceGroupList BasicServiceGroupList;


////////// End Nested Class(es) //////////

    CUG_Subscription() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    CUG_Subscription(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_Subscription(const CUG_Subscription& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CUG_Subscription(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetCug_IndexStaticDescription();
    static its::AsnDescObject* GetCug_InterlockStaticDescription();
    static its::AsnDescObject* GetIntraCUG_OptionsStaticDescription();
    static its::AsnDescObject* GetBasicServiceGroupListStaticDescription();

public:

    virtual ~CUG_Subscription()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_Subscription(*this);
    }

    virtual std::string GetName() const
    { return "CUG_Subscription"; }

    void SetCug_Index(CUG_Index* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_IndexStaticDescription());
        AddElement(0, element);
    }

    void SetCug_Index(const CUG_Index& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Index&>(element);
        asnObject.SetDescription(GetCug_IndexStaticDescription());
        AddElement(0, element);
    }

    const CUG_Index& GetCug_Index() const
    {
        return static_cast<const CUG_Index&> (ElementAt(0));
    }

    void SetCug_Interlock(CUG_Interlock* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_InterlockStaticDescription());
        AddElement(1, element);
    }

    void SetCug_Interlock(const CUG_Interlock& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Interlock&>(element);
        asnObject.SetDescription(GetCug_InterlockStaticDescription());
        AddElement(1, element);
    }

    const CUG_Interlock& GetCug_Interlock() const
    {
        return static_cast<const CUG_Interlock&> (ElementAt(1));
    }

    void SetIntraCUG_Options(IntraCUG_Options* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIntraCUG_OptionsStaticDescription());
        AddElement(2, element);
    }

    void SetIntraCUG_Options(const IntraCUG_Options& element)
    {
        its::AsnObject& asnObject = const_cast<IntraCUG_Options&>(element);
        asnObject.SetDescription(GetIntraCUG_OptionsStaticDescription());
        AddElement(2, element);
    }

    const IntraCUG_Options& GetIntraCUG_Options() const
    {
        return static_cast<const IntraCUG_Options&> (ElementAt(2));
    }

    void SetBasicServiceGroupList(BasicServiceGroupList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceGroupListStaticDescription());
        AddElement(3, element);
    }

    void SetBasicServiceGroupList(const BasicServiceGroupList& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceGroupList&>(element);
        asnObject.SetDescription(GetBasicServiceGroupListStaticDescription());
        AddElement(3, element);
    }

    bool OptionBasicServiceGroupList() const
    {
        return Contains(3);
    }

    const BasicServiceGroupList& GetBasicServiceGroupList() const
    {
        ITS_REQUIRE(OptionBasicServiceGroupList());
        return static_cast<const BasicServiceGroupList&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_CUG_SUBSCRIPTION_H_)
