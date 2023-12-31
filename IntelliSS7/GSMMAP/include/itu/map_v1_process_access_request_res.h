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


#if !defined(_MAP_V1_PROCESS_ACCESS_REQUEST_RES_H_)
#define _MAP_V1_PROCESS_ACCESS_REQUEST_RES_H_

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
#include <map_v1_isdn_address_string.h>



namespace map_v1 {



class ProcessAccessRequestRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::IMSI IMSI;


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    ProcessAccessRequestRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ProcessAccessRequestRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ProcessAccessRequestRes(const ProcessAccessRequestRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProcessAccessRequestRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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
    static its::AsnDescObject* GetMsIsdnStaticDescription();

public:

    virtual ~ProcessAccessRequestRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProcessAccessRequestRes(*this);
    }

    virtual std::string GetName() const
    { return "ProcessAccessRequestRes"; }

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

    void SetMsIsdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsIsdnStaticDescription());
        AddElement(1, element);
    }

    void SetMsIsdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsIsdnStaticDescription());
        AddElement(1, element);
    }

    bool OptionMsIsdn() const
    {
        return Contains(1);
    }

    const ISDN_AddressString& GetMsIsdn() const
    {
        ITS_REQUIRE(OptionMsIsdn());
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_PROCESS_ACCESS_REQUEST_RES_H_)

