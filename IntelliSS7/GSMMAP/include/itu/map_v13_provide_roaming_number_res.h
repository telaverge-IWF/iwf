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


#if !defined(_MAP_V13_PROVIDE_ROAMING_NUMBER_RES_H_)
#define _MAP_V13_PROVIDE_ROAMING_NUMBER_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnOctetString.h>

#include <map_v13_isdn_address_string.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class ProvideRoamingNumberRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class ReleaseResourcesSupported : public its::AsnNull
    {
    public:

        ReleaseResourcesSupported() : its::AsnNull(false)
        {
            Initialize();
        }

        ReleaseResourcesSupported(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        ReleaseResourcesSupported(const ReleaseResourcesSupported& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        ReleaseResourcesSupported(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~ReleaseResourcesSupported()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ReleaseResourcesSupported(*this);
        }

        virtual std::string GetName() const
        { return "ReleaseResourcesSupported"; }

    };


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ProvideRoamingNumberRes() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ProvideRoamingNumberRes(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ProvideRoamingNumberRes(const ProvideRoamingNumberRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProvideRoamingNumberRes(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetRoamingNumberStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetReleaseResourcesSupportedStaticDescription();
    static its::AsnDescObject* GetVmsc_AddressStaticDescription();

public:

    virtual ~ProvideRoamingNumberRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProvideRoamingNumberRes(*this);
    }

    virtual std::string GetName() const
    { return "ProvideRoamingNumberRes"; }

    void SetRoamingNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRoamingNumberStaticDescription());
        AddElement(0, element);
    }

    void SetRoamingNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetRoamingNumberStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetRoamingNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(1);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(1));
    }

    void SetReleaseResourcesSupported(ReleaseResourcesSupported* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReleaseResourcesSupportedStaticDescription());
        AddElement(2, element);
    }

    void SetReleaseResourcesSupported(const ReleaseResourcesSupported& element)
    {
        its::AsnObject& asnObject = const_cast<ReleaseResourcesSupported&>(element);
        asnObject.SetDescription(GetReleaseResourcesSupportedStaticDescription());
        AddElement(2, element);
    }

    bool OptionReleaseResourcesSupported() const
    {
        return Contains(2);
    }

    const ReleaseResourcesSupported& GetReleaseResourcesSupported() const
    {
        ITS_REQUIRE(OptionReleaseResourcesSupported());
        return static_cast<const ReleaseResourcesSupported&> (ElementAt(2));
    }

    void SetVmsc_Address(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVmsc_AddressStaticDescription());
        AddElement(3, element);
    }

    void SetVmsc_Address(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetVmsc_AddressStaticDescription());
        AddElement(3, element);
    }

    bool OptionVmsc_Address() const
    {
        return Contains(3);
    }

    const ISDN_AddressString& GetVmsc_Address() const
    {
        ITS_REQUIRE(OptionVmsc_Address());
        return static_cast<const ISDN_AddressString&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PROVIDE_ROAMING_NUMBER_RES_H_)

