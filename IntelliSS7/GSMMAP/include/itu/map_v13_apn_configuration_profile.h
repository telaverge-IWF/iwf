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


#if !defined(_MAP_V13_APN_CONFIGURATION_PROFILE_H_)
#define _MAP_V13_APN_CONFIGURATION_PROFILE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnInteger.h>
#include <AsnSequenceOf.h>

#include <map_v13_context_id.h>
#include <map_v13_eps_data_list.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class APN_ConfigurationProfile : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class CompleteDataListIncluded : public its::AsnNull
    {
    public:

        CompleteDataListIncluded() : its::AsnNull(false)
        {
            Initialize();
        }

        CompleteDataListIncluded(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        CompleteDataListIncluded(const CompleteDataListIncluded& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        CompleteDataListIncluded(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~CompleteDataListIncluded()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CompleteDataListIncluded(*this);
        }

        virtual std::string GetName() const
        { return "CompleteDataListIncluded"; }

    };


        typedef map_v13::ContextId ContextId;


        typedef map_v13::EPS_DataList EPS_DataList;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    APN_ConfigurationProfile() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    APN_ConfigurationProfile(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    APN_ConfigurationProfile(const APN_ConfigurationProfile& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    APN_ConfigurationProfile(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetDefaultContextStaticDescription();
    static its::AsnDescObject* GetCompleteDataListIncludedStaticDescription();
    static its::AsnDescObject* GetEpsDataListStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~APN_ConfigurationProfile()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new APN_ConfigurationProfile(*this);
    }

    virtual std::string GetName() const
    { return "APN_ConfigurationProfile"; }

    void SetDefaultContext(ContextId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDefaultContextStaticDescription());
        AddElement(0, element);
    }

    void SetDefaultContext(const ContextId& element)
    {
        its::AsnObject& asnObject = const_cast<ContextId&>(element);
        asnObject.SetDescription(GetDefaultContextStaticDescription());
        AddElement(0, element);
    }

    const ContextId& GetDefaultContext() const
    {
        return static_cast<const ContextId&> (ElementAt(0));
    }

    void SetCompleteDataListIncluded(CompleteDataListIncluded* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCompleteDataListIncludedStaticDescription());
        AddElement(1, element);
    }

    void SetCompleteDataListIncluded(const CompleteDataListIncluded& element)
    {
        its::AsnObject& asnObject = const_cast<CompleteDataListIncluded&>(element);
        asnObject.SetDescription(GetCompleteDataListIncludedStaticDescription());
        AddElement(1, element);
    }

    bool OptionCompleteDataListIncluded() const
    {
        return Contains(1);
    }

    const CompleteDataListIncluded& GetCompleteDataListIncluded() const
    {
        ITS_REQUIRE(OptionCompleteDataListIncluded());
        return static_cast<const CompleteDataListIncluded&> (ElementAt(1));
    }

    void SetEpsDataList(EPS_DataList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEpsDataListStaticDescription());
        AddElement(2, element);
    }

    void SetEpsDataList(const EPS_DataList& element)
    {
        its::AsnObject& asnObject = const_cast<EPS_DataList&>(element);
        asnObject.SetDescription(GetEpsDataListStaticDescription());
        AddElement(2, element);
    }

    const EPS_DataList& GetEpsDataList() const
    {
        return static_cast<const EPS_DataList&> (ElementAt(2));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(3);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_APN_CONFIGURATION_PROFILE_H_)

