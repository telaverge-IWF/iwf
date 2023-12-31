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


#if !defined(_MAP_V3_DELETE_SUBSCRIBER_DATA_ARG_H_)
#define _MAP_V3_DELETE_SUBSCRIBER_DATA_ARG_H_

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
#include <AsnSequenceOf.h>

#include <map_v3_imsi.h>
#include <map_v3_basic_service_list.h>
#include <map_v3_ss_list.h>
#include <map_v3_zone_code.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class DeleteSubscriberDataArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class RoamingRestrictionDueToUnsupportedFeature : public its::AsnNull
    {
    public:

        RoamingRestrictionDueToUnsupportedFeature() : its::AsnNull(false)
        {
            Initialize();
        }

        RoamingRestrictionDueToUnsupportedFeature(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        RoamingRestrictionDueToUnsupportedFeature(const RoamingRestrictionDueToUnsupportedFeature& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        RoamingRestrictionDueToUnsupportedFeature(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~RoamingRestrictionDueToUnsupportedFeature()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new RoamingRestrictionDueToUnsupportedFeature(*this);
        }

        virtual std::string GetName() const
        { return "RoamingRestrictionDueToUnsupportedFeature"; }

    };



    class VbsGroupIndication : public its::AsnNull
    {
    public:

        VbsGroupIndication() : its::AsnNull(false)
        {
            Initialize();
        }

        VbsGroupIndication(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        VbsGroupIndication(const VbsGroupIndication& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        VbsGroupIndication(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~VbsGroupIndication()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new VbsGroupIndication(*this);
        }

        virtual std::string GetName() const
        { return "VbsGroupIndication"; }

    };



    class VgcsGroupIndication : public its::AsnNull
    {
    public:

        VgcsGroupIndication() : its::AsnNull(false)
        {
            Initialize();
        }

        VgcsGroupIndication(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        VgcsGroupIndication(const VgcsGroupIndication& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        VgcsGroupIndication(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~VgcsGroupIndication()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new VgcsGroupIndication(*this);
        }

        virtual std::string GetName() const
        { return "VgcsGroupIndication"; }

    };



    class CamelSubscriptionInfoWithdraw : public its::AsnNull
    {
    public:

        CamelSubscriptionInfoWithdraw() : its::AsnNull(false)
        {
            Initialize();
        }

        CamelSubscriptionInfoWithdraw(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        CamelSubscriptionInfoWithdraw(const CamelSubscriptionInfoWithdraw& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        CamelSubscriptionInfoWithdraw(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~CamelSubscriptionInfoWithdraw()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CamelSubscriptionInfoWithdraw(*this);
        }

        virtual std::string GetName() const
        { return "CamelSubscriptionInfoWithdraw"; }

    };


        typedef map_v3::IMSI IMSI;


        typedef map_v3::BasicServiceList BasicServiceList;


        typedef map_v3::SS_List SS_List;


        typedef map_v3::ZoneCode ZoneCode;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    DeleteSubscriberDataArg() : its::AsnSequence(9, false)
    {
        Initialize();
    }

    DeleteSubscriberDataArg(its::Octets& octets) : its::AsnSequence(9, false)
    {
        Initialize();
        Decode(octets);
    }

    DeleteSubscriberDataArg(const DeleteSubscriberDataArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    DeleteSubscriberDataArg(its::AsnDescObject* description) : its::AsnSequence(9, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetBasicServiceListStaticDescription();
    static its::AsnDescObject* GetSs_ListStaticDescription();
    static its::AsnDescObject* GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription();
    static its::AsnDescObject* GetRegionalSubscriptionIdentifierStaticDescription();
    static its::AsnDescObject* GetVbsGroupIndicationStaticDescription();
    static its::AsnDescObject* GetVgcsGroupIndicationStaticDescription();
    static its::AsnDescObject* GetCamelSubscriptionInfoWithdrawStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~DeleteSubscriberDataArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DeleteSubscriberDataArg(*this);
    }

    virtual std::string GetName() const
    { return "DeleteSubscriberDataArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetBasicServiceList(BasicServiceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceListStaticDescription());
        AddElement(1, element);
    }

    void SetBasicServiceList(const BasicServiceList& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceList&>(element);
        asnObject.SetDescription(GetBasicServiceListStaticDescription());
        AddElement(1, element);
    }

    bool OptionBasicServiceList() const
    {
        return Contains(1);
    }

    const BasicServiceList& GetBasicServiceList() const
    {
        ITS_REQUIRE(OptionBasicServiceList());
        return static_cast<const BasicServiceList&> (ElementAt(1));
    }

    void SetSs_List(SS_List* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_ListStaticDescription());
        AddElement(2, element);
    }

    void SetSs_List(const SS_List& element)
    {
        its::AsnObject& asnObject = const_cast<SS_List&>(element);
        asnObject.SetDescription(GetSs_ListStaticDescription());
        AddElement(2, element);
    }

    bool OptionSs_List() const
    {
        return Contains(2);
    }

    const SS_List& GetSs_List() const
    {
        ITS_REQUIRE(OptionSs_List());
        return static_cast<const SS_List&> (ElementAt(2));
    }

    void SetRoamingRestrictionDueToUnsupportedFeature(RoamingRestrictionDueToUnsupportedFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription());
        AddElement(3, element);
    }

    void SetRoamingRestrictionDueToUnsupportedFeature(const RoamingRestrictionDueToUnsupportedFeature& element)
    {
        its::AsnObject& asnObject = const_cast<RoamingRestrictionDueToUnsupportedFeature&>(element);
        asnObject.SetDescription(GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription());
        AddElement(3, element);
    }

    bool OptionRoamingRestrictionDueToUnsupportedFeature() const
    {
        return Contains(3);
    }

    const RoamingRestrictionDueToUnsupportedFeature& GetRoamingRestrictionDueToUnsupportedFeature() const
    {
        ITS_REQUIRE(OptionRoamingRestrictionDueToUnsupportedFeature());
        return static_cast<const RoamingRestrictionDueToUnsupportedFeature&> (ElementAt(3));
    }

    void SetRegionalSubscriptionIdentifier(ZoneCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRegionalSubscriptionIdentifierStaticDescription());
        AddElement(4, element);
    }

    void SetRegionalSubscriptionIdentifier(const ZoneCode& element)
    {
        its::AsnObject& asnObject = const_cast<ZoneCode&>(element);
        asnObject.SetDescription(GetRegionalSubscriptionIdentifierStaticDescription());
        AddElement(4, element);
    }

    bool OptionRegionalSubscriptionIdentifier() const
    {
        return Contains(4);
    }

    const ZoneCode& GetRegionalSubscriptionIdentifier() const
    {
        ITS_REQUIRE(OptionRegionalSubscriptionIdentifier());
        return static_cast<const ZoneCode&> (ElementAt(4));
    }

    void SetVbsGroupIndication(VbsGroupIndication* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVbsGroupIndicationStaticDescription());
        AddElement(5, element);
    }

    void SetVbsGroupIndication(const VbsGroupIndication& element)
    {
        its::AsnObject& asnObject = const_cast<VbsGroupIndication&>(element);
        asnObject.SetDescription(GetVbsGroupIndicationStaticDescription());
        AddElement(5, element);
    }

    bool OptionVbsGroupIndication() const
    {
        return Contains(5);
    }

    const VbsGroupIndication& GetVbsGroupIndication() const
    {
        ITS_REQUIRE(OptionVbsGroupIndication());
        return static_cast<const VbsGroupIndication&> (ElementAt(5));
    }

    void SetVgcsGroupIndication(VgcsGroupIndication* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVgcsGroupIndicationStaticDescription());
        AddElement(6, element);
    }

    void SetVgcsGroupIndication(const VgcsGroupIndication& element)
    {
        its::AsnObject& asnObject = const_cast<VgcsGroupIndication&>(element);
        asnObject.SetDescription(GetVgcsGroupIndicationStaticDescription());
        AddElement(6, element);
    }

    bool OptionVgcsGroupIndication() const
    {
        return Contains(6);
    }

    const VgcsGroupIndication& GetVgcsGroupIndication() const
    {
        ITS_REQUIRE(OptionVgcsGroupIndication());
        return static_cast<const VgcsGroupIndication&> (ElementAt(6));
    }

    void SetCamelSubscriptionInfoWithdraw(CamelSubscriptionInfoWithdraw* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCamelSubscriptionInfoWithdrawStaticDescription());
        AddElement(7, element);
    }

    void SetCamelSubscriptionInfoWithdraw(const CamelSubscriptionInfoWithdraw& element)
    {
        its::AsnObject& asnObject = const_cast<CamelSubscriptionInfoWithdraw&>(element);
        asnObject.SetDescription(GetCamelSubscriptionInfoWithdrawStaticDescription());
        AddElement(7, element);
    }

    bool OptionCamelSubscriptionInfoWithdraw() const
    {
        return Contains(7);
    }

    const CamelSubscriptionInfoWithdraw& GetCamelSubscriptionInfoWithdraw() const
    {
        ITS_REQUIRE(OptionCamelSubscriptionInfoWithdraw());
        return static_cast<const CamelSubscriptionInfoWithdraw&> (ElementAt(7));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(8, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(8, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(8);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(8));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_DELETE_SUBSCRIBER_DATA_ARG_H_)

