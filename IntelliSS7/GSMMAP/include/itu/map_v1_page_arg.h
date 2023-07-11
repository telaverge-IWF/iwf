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


#if !defined(_MAP_V1_PAGE_ARG_H_)
#define _MAP_V1_PAGE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v1_imsi.h>
#include <map_v1_tmsi.h>
#include <map_v1_loc_area_id.h>



namespace map_v1 {



class PageArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::IMSI IMSI;


        typedef map_v1::TMSI TMSI;


        typedef map_v1::LocAreaId LocAreaId;


////////// End Nested Class(es) //////////

    PageArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    PageArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    PageArg(const PageArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PageArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetTmsiStaticDescription();
    static its::AsnDescObject* GetLocAreaIdStaticDescription();

public:

    virtual ~PageArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PageArg(*this);
    }

    virtual std::string GetName() const
    { return "PageArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetTmsi(TMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTmsiStaticDescription());
        AddElement(1, element);
    }

    void SetTmsi(const TMSI& element)
    {
        its::AsnObject& asnObject = const_cast<TMSI&>(element);
        asnObject.SetDescription(GetTmsiStaticDescription());
        AddElement(1, element);
    }

    bool OptionTmsi() const
    {
        return Contains(1);
    }

    const TMSI& GetTmsi() const
    {
        ITS_REQUIRE(OptionTmsi());
        return static_cast<const TMSI&> (ElementAt(1));
    }

    void SetLocAreaId(LocAreaId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocAreaIdStaticDescription());
        AddElement(2, element);
    }

    void SetLocAreaId(const LocAreaId& element)
    {
        its::AsnObject& asnObject = const_cast<LocAreaId&>(element);
        asnObject.SetDescription(GetLocAreaIdStaticDescription());
        AddElement(2, element);
    }

    const LocAreaId& GetLocAreaId() const
    {
        return static_cast<const LocAreaId&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_PAGE_ARG_H_)

