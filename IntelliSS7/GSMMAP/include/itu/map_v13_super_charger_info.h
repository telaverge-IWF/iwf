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


#if !defined(_MAP_V13_SUPER_CHARGER_INFO_H_)
#define _MAP_V13_SUPER_CHARGER_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnNull.h>
#include <AsnOctetString.h>

#include <map_v13_age_indicator.h>



namespace map_v13 {



class SuperChargerInfo : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class SendSubscriberData : public its::AsnNull
    {
    public:

        SendSubscriberData() : its::AsnNull(false)
        {
            Initialize();
        }

        SendSubscriberData(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        SendSubscriberData(const SendSubscriberData& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        SendSubscriberData(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~SendSubscriberData()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SendSubscriberData(*this);
        }

        virtual std::string GetName() const
        { return "SendSubscriberData"; }

    };


        typedef map_v13::AgeIndicator AgeIndicator;


////////// End Nested Class(es) //////////

    SuperChargerInfo() : its::AsnChoice(false)
    {
        Initialize();
    }

    SuperChargerInfo(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SuperChargerInfo(const SuperChargerInfo& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SuperChargerInfo(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SuperChargerInfo(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetSendSubscriberDataStaticDescription();
    static its::AsnDescObject* GetSubscriberDataStoredStaticDescription();

public:

    virtual ~SuperChargerInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SuperChargerInfo(*this);
    }

    virtual std::string GetName() const
    { return "SuperChargerInfo"; }

    void SetChoiceSendSubscriberData(SendSubscriberData* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSendSubscriberDataStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSendSubscriberData(const SendSubscriberData& choice)
    {
        its::AsnObject& asnObject = const_cast<SendSubscriberData&>(choice);
        asnObject.SetDescription(GetSendSubscriberDataStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSendSubscriberData() const
    {
        return Contains(GetSendSubscriberDataStaticDescription()->TagIdentity());
    }

    const SendSubscriberData& GetChoiceSendSubscriberData() const
    {
        ITS_REQUIRE(ChoiceSendSubscriberData());
        return static_cast<const SendSubscriberData&> (GetChoice());
    }

    void SetChoiceSubscriberDataStored(AgeIndicator* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSubscriberDataStoredStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSubscriberDataStored(const AgeIndicator& choice)
    {
        its::AsnObject& asnObject = const_cast<AgeIndicator&>(choice);
        asnObject.SetDescription(GetSubscriberDataStoredStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSubscriberDataStored() const
    {
        return Contains(GetSubscriberDataStoredStaticDescription()->TagIdentity());
    }

    const AgeIndicator& GetChoiceSubscriberDataStored() const
    {
        ITS_REQUIRE(ChoiceSubscriberDataStored());
        return static_cast<const AgeIndicator&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SUPER_CHARGER_INFO_H_)

