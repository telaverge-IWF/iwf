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


#if !defined(_MAP_V1_SS_SUBSCRIPTION_OPTION_H_)
#define _MAP_V1_SS_SUBSCRIPTION_OPTION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnBoolean.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>
#include <AsnEnumerated.h>

#include <map_v1_user_to_user_service_indicator.h>
#include <map_v1_maximum_conferees_number.h>
#include <map_v1_hunt_group_access_selection_order.h>



namespace map_v1 {



class SS_SubscriptionOption : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class PerCallBasis : public its::AsnBoolean
    {
    public:

        PerCallBasis(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        PerCallBasis(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        PerCallBasis(const PerCallBasis& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        PerCallBasis(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        PerCallBasis(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~PerCallBasis()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new PerCallBasis(*this);
        }

        virtual std::string GetName() const
        { return "PerCallBasis"; }

    };



    class NotificationToHeldRetrievedParty : public its::AsnBoolean
    {
    public:

        NotificationToHeldRetrievedParty(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        NotificationToHeldRetrievedParty(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        NotificationToHeldRetrievedParty(const NotificationToHeldRetrievedParty& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        NotificationToHeldRetrievedParty(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        NotificationToHeldRetrievedParty(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~NotificationToHeldRetrievedParty()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NotificationToHeldRetrievedParty(*this);
        }

        virtual std::string GetName() const
        { return "NotificationToHeldRetrievedParty"; }

    };


        typedef map_v1::UserToUserServiceIndicator UserToUserServiceIndicator;


        typedef map_v1::MaximumConfereesNumber MaximumConfereesNumber;


        typedef map_v1::HuntGroupAccessSelectionOrder HuntGroupAccessSelectionOrder;


////////// End Nested Class(es) //////////

    SS_SubscriptionOption() : its::AsnChoice(false)
    {
        Initialize();
    }

    SS_SubscriptionOption(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SS_SubscriptionOption(const SS_SubscriptionOption& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SS_SubscriptionOption(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SS_SubscriptionOption(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetPerCallBasisStaticDescription();
    static its::AsnDescObject* GetNotificationToHeldRetrievedPartyStaticDescription();
    static its::AsnDescObject* GetUserToUserServiceIndicatorStaticDescription();
    static its::AsnDescObject* GetMaximumConfereesNumberStaticDescription();
    static its::AsnDescObject* GetHuntGroupAccessSelectionOrderStaticDescription();

public:

    virtual ~SS_SubscriptionOption()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_SubscriptionOption(*this);
    }

    virtual std::string GetName() const
    { return "SS_SubscriptionOption"; }

    void SetChoicePerCallBasis(PerCallBasis* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPerCallBasisStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePerCallBasis(const PerCallBasis& choice)
    {
        its::AsnObject& asnObject = const_cast<PerCallBasis&>(choice);
        asnObject.SetDescription(GetPerCallBasisStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePerCallBasis() const
    {
        return Contains(GetPerCallBasisStaticDescription()->TagIdentity());
    }

    const PerCallBasis& GetChoicePerCallBasis() const
    {
        ITS_REQUIRE(ChoicePerCallBasis());
        return static_cast<const PerCallBasis&> (GetChoice());
    }

    void SetChoiceNotificationToHeldRetrievedParty(NotificationToHeldRetrievedParty* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetNotificationToHeldRetrievedPartyStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceNotificationToHeldRetrievedParty(const NotificationToHeldRetrievedParty& choice)
    {
        its::AsnObject& asnObject = const_cast<NotificationToHeldRetrievedParty&>(choice);
        asnObject.SetDescription(GetNotificationToHeldRetrievedPartyStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceNotificationToHeldRetrievedParty() const
    {
        return Contains(GetNotificationToHeldRetrievedPartyStaticDescription()->TagIdentity());
    }

    const NotificationToHeldRetrievedParty& GetChoiceNotificationToHeldRetrievedParty() const
    {
        ITS_REQUIRE(ChoiceNotificationToHeldRetrievedParty());
        return static_cast<const NotificationToHeldRetrievedParty&> (GetChoice());
    }

    void SetChoiceUserToUserServiceIndicator(UserToUserServiceIndicator* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetUserToUserServiceIndicatorStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceUserToUserServiceIndicator(const UserToUserServiceIndicator& choice)
    {
        its::AsnObject& asnObject = const_cast<UserToUserServiceIndicator&>(choice);
        asnObject.SetDescription(GetUserToUserServiceIndicatorStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceUserToUserServiceIndicator() const
    {
        return Contains(GetUserToUserServiceIndicatorStaticDescription()->TagIdentity());
    }

    const UserToUserServiceIndicator& GetChoiceUserToUserServiceIndicator() const
    {
        ITS_REQUIRE(ChoiceUserToUserServiceIndicator());
        return static_cast<const UserToUserServiceIndicator&> (GetChoice());
    }

    void SetChoiceMaximumConfereesNumber(MaximumConfereesNumber* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetMaximumConfereesNumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceMaximumConfereesNumber(const MaximumConfereesNumber& choice)
    {
        its::AsnObject& asnObject = const_cast<MaximumConfereesNumber&>(choice);
        asnObject.SetDescription(GetMaximumConfereesNumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceMaximumConfereesNumber() const
    {
        return Contains(GetMaximumConfereesNumberStaticDescription()->TagIdentity());
    }

    const MaximumConfereesNumber& GetChoiceMaximumConfereesNumber() const
    {
        ITS_REQUIRE(ChoiceMaximumConfereesNumber());
        return static_cast<const MaximumConfereesNumber&> (GetChoice());
    }

    void SetChoiceHuntGroupAccessSelectionOrder(HuntGroupAccessSelectionOrder* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetHuntGroupAccessSelectionOrderStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceHuntGroupAccessSelectionOrder(const HuntGroupAccessSelectionOrder& choice)
    {
        its::AsnObject& asnObject = const_cast<HuntGroupAccessSelectionOrder&>(choice);
        asnObject.SetDescription(GetHuntGroupAccessSelectionOrderStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceHuntGroupAccessSelectionOrder() const
    {
        return Contains(GetHuntGroupAccessSelectionOrderStaticDescription()->TagIdentity());
    }

    const HuntGroupAccessSelectionOrder& GetChoiceHuntGroupAccessSelectionOrder() const
    {
        ITS_REQUIRE(ChoiceHuntGroupAccessSelectionOrder());
        return static_cast<const HuntGroupAccessSelectionOrder&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_SS_SUBSCRIPTION_OPTION_H_)

