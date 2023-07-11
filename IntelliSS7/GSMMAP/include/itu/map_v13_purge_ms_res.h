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


#if !defined(_MAP_V13_PURGE_MS_RES_H_)
#define _MAP_V13_PURGE_MS_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>

#include <map_v13_extension_container.h>



namespace map_v13 {



class PurgeMS_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class FreezeTMSI : public its::AsnNull
    {
    public:

        FreezeTMSI() : its::AsnNull(false)
        {
            Initialize();
        }

        FreezeTMSI(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        FreezeTMSI(const FreezeTMSI& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        FreezeTMSI(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~FreezeTMSI()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new FreezeTMSI(*this);
        }

        virtual std::string GetName() const
        { return "FreezeTMSI"; }

    };



    class FreezeP_TMSI : public its::AsnNull
    {
    public:

        FreezeP_TMSI() : its::AsnNull(false)
        {
            Initialize();
        }

        FreezeP_TMSI(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        FreezeP_TMSI(const FreezeP_TMSI& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        FreezeP_TMSI(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~FreezeP_TMSI()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new FreezeP_TMSI(*this);
        }

        virtual std::string GetName() const
        { return "FreezeP_TMSI"; }

    };



    class FreezeM_TMSI : public its::AsnNull
    {
    public:

        FreezeM_TMSI() : its::AsnNull(false)
        {
            Initialize();
        }

        FreezeM_TMSI(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        FreezeM_TMSI(const FreezeM_TMSI& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        FreezeM_TMSI(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~FreezeM_TMSI()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new FreezeM_TMSI(*this);
        }

        virtual std::string GetName() const
        { return "FreezeM_TMSI"; }

    };


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    PurgeMS_Res() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    PurgeMS_Res(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    PurgeMS_Res(const PurgeMS_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PurgeMS_Res(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetFreezeTMSIStaticDescription();
    static its::AsnDescObject* GetFreezeP_TMSIStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetFreezeM_TMSIStaticDescription();

public:

    virtual ~PurgeMS_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PurgeMS_Res(*this);
    }

    virtual std::string GetName() const
    { return "PurgeMS_Res"; }

    void SetFreezeTMSI(FreezeTMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetFreezeTMSIStaticDescription());
        AddElement(0, element);
    }

    void SetFreezeTMSI(const FreezeTMSI& element)
    {
        its::AsnObject& asnObject = const_cast<FreezeTMSI&>(element);
        asnObject.SetDescription(GetFreezeTMSIStaticDescription());
        AddElement(0, element);
    }

    bool OptionFreezeTMSI() const
    {
        return Contains(0);
    }

    const FreezeTMSI& GetFreezeTMSI() const
    {
        ITS_REQUIRE(OptionFreezeTMSI());
        return static_cast<const FreezeTMSI&> (ElementAt(0));
    }

    void SetFreezeP_TMSI(FreezeP_TMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetFreezeP_TMSIStaticDescription());
        AddElement(1, element);
    }

    void SetFreezeP_TMSI(const FreezeP_TMSI& element)
    {
        its::AsnObject& asnObject = const_cast<FreezeP_TMSI&>(element);
        asnObject.SetDescription(GetFreezeP_TMSIStaticDescription());
        AddElement(1, element);
    }

    bool OptionFreezeP_TMSI() const
    {
        return Contains(1);
    }

    const FreezeP_TMSI& GetFreezeP_TMSI() const
    {
        ITS_REQUIRE(OptionFreezeP_TMSI());
        return static_cast<const FreezeP_TMSI&> (ElementAt(1));
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

    void SetFreezeM_TMSI(FreezeM_TMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetFreezeM_TMSIStaticDescription());
        AddElement(3, element);
    }

    void SetFreezeM_TMSI(const FreezeM_TMSI& element)
    {
        its::AsnObject& asnObject = const_cast<FreezeM_TMSI&>(element);
        asnObject.SetDescription(GetFreezeM_TMSIStaticDescription());
        AddElement(3, element);
    }

    bool OptionFreezeM_TMSI() const
    {
        return Contains(3);
    }

    const FreezeM_TMSI& GetFreezeM_TMSI() const
    {
        ITS_REQUIRE(OptionFreezeM_TMSI());
        return static_cast<const FreezeM_TMSI&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PURGE_MS_RES_H_)
