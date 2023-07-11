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


#if !defined(_MAP_V13_SYSTEM_FAILURE_PARAM_H_)
#define _MAP_V13_SYSTEM_FAILURE_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnEnumerated.h>
#include <AsnSequence.h>

#include <map_v13_network_resource.h>
#include <map_v13_extensible_system_failure_param.h>



namespace map_v13 {



class SystemFailureParam : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::NetworkResource NetworkResource;


        typedef map_v13::ExtensibleSystemFailureParam ExtensibleSystemFailureParam;


////////// End Nested Class(es) //////////

    SystemFailureParam() : its::AsnChoice(false)
    {
        Initialize();
    }

    SystemFailureParam(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SystemFailureParam(const SystemFailureParam& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SystemFailureParam(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SystemFailureParam(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetNetworkResourceStaticDescription();
    static its::AsnDescObject* GetExtensibleSystemFailureParamStaticDescription();

public:

    virtual ~SystemFailureParam()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SystemFailureParam(*this);
    }

    virtual std::string GetName() const
    { return "SystemFailureParam"; }

    void SetChoiceNetworkResource(NetworkResource* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetNetworkResourceStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceNetworkResource(const NetworkResource& choice)
    {
        its::AsnObject& asnObject = const_cast<NetworkResource&>(choice);
        asnObject.SetDescription(GetNetworkResourceStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceNetworkResource() const
    {
        return Contains(GetNetworkResourceStaticDescription()->TagIdentity());
    }

    const NetworkResource& GetChoiceNetworkResource() const
    {
        ITS_REQUIRE(ChoiceNetworkResource());
        return static_cast<const NetworkResource&> (GetChoice());
    }

    void SetChoiceExtensibleSystemFailureParam(ExtensibleSystemFailureParam* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetExtensibleSystemFailureParamStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceExtensibleSystemFailureParam(const ExtensibleSystemFailureParam& choice)
    {
        its::AsnObject& asnObject = const_cast<ExtensibleSystemFailureParam&>(choice);
        asnObject.SetDescription(GetExtensibleSystemFailureParamStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceExtensibleSystemFailureParam() const
    {
        return Contains(GetExtensibleSystemFailureParamStaticDescription()->TagIdentity());
    }

    const ExtensibleSystemFailureParam& GetChoiceExtensibleSystemFailureParam() const
    {
        ITS_REQUIRE(ChoiceExtensibleSystemFailureParam());
        return static_cast<const ExtensibleSystemFailureParam&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SYSTEM_FAILURE_PARAM_H_)

