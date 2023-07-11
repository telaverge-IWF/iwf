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


#if !defined(_MAP_V13_CLIR_DATA_H_)
#define _MAP_V13_CLIR_DATA_H_

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
#include <AsnEnumerated.h>

#include <map_v13_ext_ss_status.h>
#include <map_v13_cli_restriction_option.h>



namespace map_v13 {



class ClirData : public its::AsnSequence
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


        typedef map_v13::Ext_SS_Status Ext_SS_Status;


        typedef map_v13::CliRestrictionOption CliRestrictionOption;


////////// End Nested Class(es) //////////

    ClirData() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ClirData(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ClirData(const ClirData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ClirData(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSs_StatusStaticDescription();
    static its::AsnDescObject* GetCliRestrictionOptionStaticDescription();
    static its::AsnDescObject* GetNotificationToCSEStaticDescription();

public:

    virtual ~ClirData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ClirData(*this);
    }

    virtual std::string GetName() const
    { return "ClirData"; }

    void SetSs_Status(Ext_SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Status(const Ext_SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    const Ext_SS_Status& GetSs_Status() const
    {
        return static_cast<const Ext_SS_Status&> (ElementAt(0));
    }

    void SetCliRestrictionOption(CliRestrictionOption* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCliRestrictionOptionStaticDescription());
        AddElement(1, element);
    }

    void SetCliRestrictionOption(const CliRestrictionOption& element)
    {
        its::AsnObject& asnObject = const_cast<CliRestrictionOption&>(element);
        asnObject.SetDescription(GetCliRestrictionOptionStaticDescription());
        AddElement(1, element);
    }

    bool OptionCliRestrictionOption() const
    {
        return Contains(1);
    }

    const CliRestrictionOption& GetCliRestrictionOption() const
    {
        ITS_REQUIRE(OptionCliRestrictionOption());
        return static_cast<const CliRestrictionOption&> (ElementAt(1));
    }

    void SetNotificationToCSE(NotificationToCSE* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(2, element);
    }

    void SetNotificationToCSE(const NotificationToCSE& element)
    {
        its::AsnObject& asnObject = const_cast<NotificationToCSE&>(element);
        asnObject.SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(2, element);
    }

    bool OptionNotificationToCSE() const
    {
        return Contains(2);
    }

    const NotificationToCSE& GetNotificationToCSE() const
    {
        ITS_REQUIRE(OptionNotificationToCSE());
        return static_cast<const NotificationToCSE&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_CLIR_DATA_H_)

