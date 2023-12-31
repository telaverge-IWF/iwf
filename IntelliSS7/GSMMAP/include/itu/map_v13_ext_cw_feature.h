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


#if !defined(_MAP_V13_EXT_CW_FEATURE_H_)
#define _MAP_V13_EXT_CW_FEATURE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <map_v13_ext_basic_service_code.h>
#include <map_v13_ext_ss_status.h>



namespace map_v13 {



class Ext_CwFeature : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::Ext_BasicServiceCode Ext_BasicServiceCode;


        typedef map_v13::Ext_SS_Status Ext_SS_Status;


////////// End Nested Class(es) //////////

    Ext_CwFeature() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    Ext_CwFeature(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_CwFeature(const Ext_CwFeature& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    Ext_CwFeature(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetBasicServiceStaticDescription();
    static its::AsnDescObject* GetSs_StatusStaticDescription();

public:

    virtual ~Ext_CwFeature()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_CwFeature(*this);
    }

    virtual std::string GetName() const
    { return "Ext_CwFeature"; }

    void SetBasicService(Ext_BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceStaticDescription());
        AddElement(0, element);
    }

    void SetBasicService(const Ext_BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceStaticDescription());
        AddElement(0, element);
    }

    const Ext_BasicServiceCode& GetBasicService() const
    {
        return static_cast<const Ext_BasicServiceCode&> (ElementAt(0));
    }

    void SetSs_Status(Ext_SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(1, element);
    }

    void SetSs_Status(const Ext_SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(1, element);
    }

    const Ext_SS_Status& GetSs_Status() const
    {
        return static_cast<const Ext_SS_Status&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_EXT_CW_FEATURE_H_)

