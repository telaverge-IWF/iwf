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


#if !defined(_MAP_V9_SS_INCOMPATIBILITY_CAUSE_H_)
#define _MAP_V9_SS_INCOMPATIBILITY_CAUSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>

#include <map_v9_ss_code.h>
#include <map_v9_basic_service_code.h>
#include <map_v9_ss_status.h>



namespace map_v9 {



class SS_IncompatibilityCause : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SS_Code SS_Code;


        typedef map_v9::BasicServiceCode BasicServiceCode;


        typedef map_v9::SS_Status SS_Status;


////////// End Nested Class(es) //////////

    SS_IncompatibilityCause() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    SS_IncompatibilityCause(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    SS_IncompatibilityCause(const SS_IncompatibilityCause& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SS_IncompatibilityCause(its::AsnDescObject* description) : its::AsnSequence(3, description)
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
    static its::AsnDescObject* GetBasicServiceStaticDescription();
    static its::AsnDescObject* GetSs_StatusStaticDescription();

public:

    virtual ~SS_IncompatibilityCause()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_IncompatibilityCause(*this);
    }

    virtual std::string GetName() const
    { return "SS_IncompatibilityCause"; }

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

    void SetBasicService(BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceStaticDescription());
        AddElement(1, element);
    }

    void SetBasicService(const BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceStaticDescription());
        AddElement(1, element);
    }

    bool OptionBasicService() const
    {
        return Contains(1);
    }

    const BasicServiceCode& GetBasicService() const
    {
        ITS_REQUIRE(OptionBasicService());
        return static_cast<const BasicServiceCode&> (ElementAt(1));
    }

    void SetSs_Status(SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(2, element);
    }

    void SetSs_Status(const SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(2, element);
    }

    bool OptionSs_Status() const
    {
        return Contains(2);
    }

    const SS_Status& GetSs_Status() const
    {
        ITS_REQUIRE(OptionSs_Status());
        return static_cast<const SS_Status&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SS_INCOMPATIBILITY_CAUSE_H_)

