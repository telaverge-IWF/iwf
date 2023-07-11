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


#if !defined(_MAP_V13_CALL_WAITING_DATA_H_)
#define _MAP_V13_CALL_WAITING_DATA_H_

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

#include <map_v13_ext_cw_feature_list.h>



namespace map_v13 {



class CallWaitingData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class NotificationToCSE : public its::AsnNull
    {
    public:

        NotificationToCSE() : its::AsnNull(false)
        {
            Initialize();
        }

        NotificationToCSE(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        NotificationToCSE(const NotificationToCSE& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        NotificationToCSE(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~NotificationToCSE()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NotificationToCSE(*this);
        }

        virtual std::string GetName() const
        { return "NotificationToCSE"; }

    };


        typedef map_v13::Ext_CwFeatureList Ext_CwFeatureList;


////////// End Nested Class(es) //////////

    CallWaitingData() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    CallWaitingData(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    CallWaitingData(const CallWaitingData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CallWaitingData(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetCwFeatureListStaticDescription();
    static its::AsnDescObject* GetNotificationToCSEStaticDescription();

public:

    virtual ~CallWaitingData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallWaitingData(*this);
    }

    virtual std::string GetName() const
    { return "CallWaitingData"; }

    void SetCwFeatureList(Ext_CwFeatureList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCwFeatureListStaticDescription());
        AddElement(0, element);
    }

    void SetCwFeatureList(const Ext_CwFeatureList& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_CwFeatureList&>(element);
        asnObject.SetDescription(GetCwFeatureListStaticDescription());
        AddElement(0, element);
    }

    const Ext_CwFeatureList& GetCwFeatureList() const
    {
        return static_cast<const Ext_CwFeatureList&> (ElementAt(0));
    }

    void SetNotificationToCSE(NotificationToCSE* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(1, element);
    }

    void SetNotificationToCSE(const NotificationToCSE& element)
    {
        its::AsnObject& asnObject = const_cast<NotificationToCSE&>(element);
        asnObject.SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(1, element);
    }

    bool OptionNotificationToCSE() const
    {
        return Contains(1);
    }

    const NotificationToCSE& GetNotificationToCSE() const
    {
        ITS_REQUIRE(OptionNotificationToCSE());
        return static_cast<const NotificationToCSE&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_CALL_WAITING_DATA_H_)
