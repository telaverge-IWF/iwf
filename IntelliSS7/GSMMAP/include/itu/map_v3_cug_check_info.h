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


#if !defined(_MAP_V3_CUG_CHECK_INFO_H_)
#define _MAP_V3_CUG_CHECK_INFO_H_

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

#include <map_v3_cug_interlock.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class CUG_CheckInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Cug_OutgoingAccess : public its::AsnNull
    {
    public:

        Cug_OutgoingAccess() : its::AsnNull(false)
        {
            Initialize();
        }

        Cug_OutgoingAccess(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Cug_OutgoingAccess(const Cug_OutgoingAccess& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Cug_OutgoingAccess(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Cug_OutgoingAccess()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Cug_OutgoingAccess(*this);
        }

        virtual std::string GetName() const
        { return "Cug_OutgoingAccess"; }

    };


        typedef map_v3::CUG_Interlock CUG_Interlock;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    CUG_CheckInfo() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    CUG_CheckInfo(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_CheckInfo(const CUG_CheckInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CUG_CheckInfo(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetCug_InterlockStaticDescription();
    static its::AsnDescObject* GetCug_OutgoingAccessStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~CUG_CheckInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_CheckInfo(*this);
    }

    virtual std::string GetName() const
    { return "CUG_CheckInfo"; }

    void SetCug_Interlock(CUG_Interlock* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_InterlockStaticDescription());
        AddElement(0, element);
    }

    void SetCug_Interlock(const CUG_Interlock& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Interlock&>(element);
        asnObject.SetDescription(GetCug_InterlockStaticDescription());
        AddElement(0, element);
    }

    const CUG_Interlock& GetCug_Interlock() const
    {
        return static_cast<const CUG_Interlock&> (ElementAt(0));
    }

    void SetCug_OutgoingAccess(Cug_OutgoingAccess* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(1, element);
    }

    void SetCug_OutgoingAccess(const Cug_OutgoingAccess& element)
    {
        its::AsnObject& asnObject = const_cast<Cug_OutgoingAccess&>(element);
        asnObject.SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(1, element);
    }

    bool OptionCug_OutgoingAccess() const
    {
        return Contains(1);
    }

    const Cug_OutgoingAccess& GetCug_OutgoingAccess() const
    {
        ITS_REQUIRE(OptionCug_OutgoingAccess());
        return static_cast<const Cug_OutgoingAccess&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_CUG_CHECK_INFO_H_)

