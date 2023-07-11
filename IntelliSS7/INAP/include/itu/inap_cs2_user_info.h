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


#if !defined(_INAP_CS2_USER_INFO_H_)
#define _INAP_CS2_USER_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <inap_cs2_user_information.h>



namespace inap_cs2 {



class UserInfo : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef inap_cs2::UserInformation UserInformation;


////////// End Nested Class //////////

    UserInfo() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    UserInfo(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    UserInfo(const UserInfo& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    UserInfo(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetUserInformationStaticDescription();

public:

    virtual ~UserInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UserInfo(*this);
    }

    virtual std::string GetName() const
    { return "UserInfo"; }

    void AddElement(UserInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUserInformationStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const UserInformation& element)
    {
        its::AsnObject& asnObject = const_cast<UserInformation&>(element);
        asnObject.SetDescription(GetUserInformationStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const UserInformation& ElementAt(int index) const
    {
        return static_cast<const UserInformation&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_USER_INFO_H_)

