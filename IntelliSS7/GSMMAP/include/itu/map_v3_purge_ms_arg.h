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


#if !defined(_MAP_V3_PURGE_MS_ARG_H_)
#define _MAP_V3_PURGE_MS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_imsi.h>
#include <map_v3_isdn_address_string.h>



namespace map_v3 {



class PurgeMS_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::IMSI IMSI;


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    PurgeMS_Arg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    PurgeMS_Arg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    PurgeMS_Arg(const PurgeMS_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PurgeMS_Arg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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
    static its::AsnDescObject* GetVlr_NumberStaticDescription();

public:

    virtual ~PurgeMS_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PurgeMS_Arg(*this);
    }

    virtual std::string GetName() const
    { return "PurgeMS_Arg"; }

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

    void SetVlr_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVlr_NumberStaticDescription());
        AddElement(1, element);
    }

    void SetVlr_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetVlr_NumberStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetVlr_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_PURGE_MS_ARG_H_)

