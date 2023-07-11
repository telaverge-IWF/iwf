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


#if !defined(_MAP_V13_UMTS_SECURITY_CONTEXT_DATA_H_)
#define _MAP_V13_UMTS_SECURITY_CONTEXT_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v13_ck.h>
#include <map_v13_ik.h>
#include <map_v13_ksi.h>



namespace map_v13 {



class UMTS_SecurityContextData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::CK CK;


        typedef map_v13::IK IK;


        typedef map_v13::KSI KSI;


////////// End Nested Class(es) //////////

    UMTS_SecurityContextData() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    UMTS_SecurityContextData(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    UMTS_SecurityContextData(const UMTS_SecurityContextData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    UMTS_SecurityContextData(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetCkStaticDescription();
    static its::AsnDescObject* GetIkStaticDescription();
    static its::AsnDescObject* GetKsiStaticDescription();

public:

    virtual ~UMTS_SecurityContextData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UMTS_SecurityContextData(*this);
    }

    virtual std::string GetName() const
    { return "UMTS_SecurityContextData"; }

    void SetCk(CK* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCkStaticDescription());
        AddElement(0, element);
    }

    void SetCk(const CK& element)
    {
        its::AsnObject& asnObject = const_cast<CK&>(element);
        asnObject.SetDescription(GetCkStaticDescription());
        AddElement(0, element);
    }

    const CK& GetCk() const
    {
        return static_cast<const CK&> (ElementAt(0));
    }

    void SetIk(IK* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIkStaticDescription());
        AddElement(1, element);
    }

    void SetIk(const IK& element)
    {
        its::AsnObject& asnObject = const_cast<IK&>(element);
        asnObject.SetDescription(GetIkStaticDescription());
        AddElement(1, element);
    }

    const IK& GetIk() const
    {
        return static_cast<const IK&> (ElementAt(1));
    }

    void SetKsi(KSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetKsiStaticDescription());
        AddElement(2, element);
    }

    void SetKsi(const KSI& element)
    {
        its::AsnObject& asnObject = const_cast<KSI&>(element);
        asnObject.SetDescription(GetKsiStaticDescription());
        AddElement(2, element);
    }

    const KSI& GetKsi() const
    {
        return static_cast<const KSI&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_UMTS_SECURITY_CONTEXT_DATA_H_)
