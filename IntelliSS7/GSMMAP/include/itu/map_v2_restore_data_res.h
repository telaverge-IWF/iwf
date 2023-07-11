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


#if !defined(_MAP_V2_RESTORE_DATA_RES_H_)
#define _MAP_V2_RESTORE_DATA_RES_H_

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

#include <map_v2_isdn_address_string.h>



namespace map_v2 {



class RestoreDataRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class MsNotReachable : public its::AsnNull
    {
    public:

        MsNotReachable() : its::AsnNull(false)
        {
            Initialize();
        }

        MsNotReachable(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        MsNotReachable(const MsNotReachable& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        MsNotReachable(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~MsNotReachable()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new MsNotReachable(*this);
        }

        virtual std::string GetName() const
        { return "MsNotReachable"; }

    };


        typedef map_v2::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    RestoreDataRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RestoreDataRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RestoreDataRes(const RestoreDataRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RestoreDataRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetHlr_NumberStaticDescription();
    static its::AsnDescObject* GetMsNotReachableStaticDescription();

public:

    virtual ~RestoreDataRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RestoreDataRes(*this);
    }

    virtual std::string GetName() const
    { return "RestoreDataRes"; }

    void SetHlr_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHlr_NumberStaticDescription());
        AddElement(0, element);
    }

    void SetHlr_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetHlr_NumberStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetHlr_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetMsNotReachable(MsNotReachable* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsNotReachableStaticDescription());
        AddElement(1, element);
    }

    void SetMsNotReachable(const MsNotReachable& element)
    {
        its::AsnObject& asnObject = const_cast<MsNotReachable&>(element);
        asnObject.SetDescription(GetMsNotReachableStaticDescription());
        AddElement(1, element);
    }

    bool OptionMsNotReachable() const
    {
        return Contains(1);
    }

    const MsNotReachable& GetMsNotReachable() const
    {
        ITS_REQUIRE(OptionMsNotReachable());
        return static_cast<const MsNotReachable&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_RESTORE_DATA_RES_H_)
