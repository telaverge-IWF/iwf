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


#if !defined(_MAP_V13_GPRS_SUBSCRIPTION_DATA_H_)
#define _MAP_V13_GPRS_SUBSCRIPTION_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v13_gprs_data_list.h>
#include <map_v13_extension_container.h>
#include <map_v13_apn_oi_replacement.h>



namespace map_v13 {



class GPRSSubscriptionData : public its::AsnSequence
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


        typedef map_v13::GPRSDataList GPRSDataList;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::APN_OI_Replacement APN_OI_Replacement;


////////// End Nested Class(es) //////////

    GPRSSubscriptionData() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    GPRSSubscriptionData(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    GPRSSubscriptionData(const GPRSSubscriptionData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    GPRSSubscriptionData(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetGprsDataListStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetApn_oi_ReplacementStaticDescription();

public:

    virtual ~GPRSSubscriptionData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GPRSSubscriptionData(*this);
    }

    virtual std::string GetName() const
    { return "GPRSSubscriptionData"; }

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

    void SetGprsDataList(GPRSDataList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGprsDataListStaticDescription());
        AddElement(1, element);
    }

    void SetGprsDataList(const GPRSDataList& element)
    {
        its::AsnObject& asnObject = const_cast<GPRSDataList&>(element);
        asnObject.SetDescription(GetGprsDataListStaticDescription());
        AddElement(1, element);
    }

    const GPRSDataList& GetGprsDataList() const
    {
        return static_cast<const GPRSDataList&> (ElementAt(1));
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

    void SetApn_oi_Replacement(APN_OI_Replacement* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetApn_oi_ReplacementStaticDescription());
        AddElement(3, element);
    }

    void SetApn_oi_Replacement(const APN_OI_Replacement& element)
    {
        its::AsnObject& asnObject = const_cast<APN_OI_Replacement&>(element);
        asnObject.SetDescription(GetApn_oi_ReplacementStaticDescription());
        AddElement(3, element);
    }

    bool OptionApn_oi_Replacement() const
    {
        return Contains(3);
    }

    const APN_OI_Replacement& GetApn_oi_Replacement() const
    {
        ITS_REQUIRE(OptionApn_oi_Replacement());
        return static_cast<const APN_OI_Replacement&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_GPRS_SUBSCRIPTION_DATA_H_)
