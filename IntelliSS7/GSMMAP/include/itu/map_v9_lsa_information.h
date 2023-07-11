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


#if !defined(_MAP_V9_LSA_INFORMATION_H_)
#define _MAP_V9_LSA_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnEnumerated.h>
#include <AsnSequenceOf.h>

#include <map_v9_lsa_only_access_indicator.h>
#include <map_v9_lsa_data_list.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class LSAInformation : public its::AsnSequence
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


        typedef map_v9::LSAOnlyAccessIndicator LSAOnlyAccessIndicator;


        typedef map_v9::LSADataList LSADataList;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    LSAInformation() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    LSAInformation(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    LSAInformation(const LSAInformation& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    LSAInformation(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetCompleteDataListIncludedStaticDescription();
    static its::AsnDescObject* GetLsaOnlyAccessIndicatorStaticDescription();
    static its::AsnDescObject* GetLsaDataListStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~LSAInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LSAInformation(*this);
    }

    virtual std::string GetName() const
    { return "LSAInformation"; }

    void SetCompleteDataListIncluded(CompleteDataListIncluded* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCompleteDataListIncludedStaticDescription());
        AddElement(0, element);
    }

    void SetCompleteDataListIncluded(const CompleteDataListIncluded& element)
    {
        its::AsnObject& asnObject = const_cast<CompleteDataListIncluded&>(element);
        asnObject.SetDescription(GetCompleteDataListIncludedStaticDescription());
        AddElement(0, element);
    }

    bool OptionCompleteDataListIncluded() const
    {
        return Contains(0);
    }

    const CompleteDataListIncluded& GetCompleteDataListIncluded() const
    {
        ITS_REQUIRE(OptionCompleteDataListIncluded());
        return static_cast<const CompleteDataListIncluded&> (ElementAt(0));
    }

    void SetLsaOnlyAccessIndicator(LSAOnlyAccessIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLsaOnlyAccessIndicatorStaticDescription());
        AddElement(1, element);
    }

    void SetLsaOnlyAccessIndicator(const LSAOnlyAccessIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<LSAOnlyAccessIndicator&>(element);
        asnObject.SetDescription(GetLsaOnlyAccessIndicatorStaticDescription());
        AddElement(1, element);
    }

    bool OptionLsaOnlyAccessIndicator() const
    {
        return Contains(1);
    }

    const LSAOnlyAccessIndicator& GetLsaOnlyAccessIndicator() const
    {
        ITS_REQUIRE(OptionLsaOnlyAccessIndicator());
        return static_cast<const LSAOnlyAccessIndicator&> (ElementAt(1));
    }

    void SetLsaDataList(LSADataList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLsaDataListStaticDescription());
        AddElement(2, element);
    }

    void SetLsaDataList(const LSADataList& element)
    {
        its::AsnObject& asnObject = const_cast<LSADataList&>(element);
        asnObject.SetDescription(GetLsaDataListStaticDescription());
        AddElement(2, element);
    }

    bool OptionLsaDataList() const
    {
        return Contains(2);
    }

    const LSADataList& GetLsaDataList() const
    {
        ITS_REQUIRE(OptionLsaDataList());
        return static_cast<const LSADataList&> (ElementAt(2));
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

#endif    // !defined(_MAP_V9_LSA_INFORMATION_H_)

