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


#if !defined(_MAP_V9_ORIGINAL_COMPONENT_IDENTIFIER_H_)
#define _MAP_V9_ORIGINAL_COMPONENT_IDENTIFIER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnNull.h>

#include <map_v9_operation_code.h>
#include <map_v9_error_code.h>



namespace map_v9 {



class OriginalComponentIdentifier : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class UserInfo : public its::AsnNull
    {
    public:

        UserInfo() : its::AsnNull(false)
        {
            Initialize();
        }

        UserInfo(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        UserInfo(const UserInfo& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        UserInfo(its::AsnDescObject* description) : its::AsnNull(description)
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

    };


        typedef map_v9::OperationCode OperationCode;


        typedef map_v9::ErrorCode ErrorCode;


////////// End Nested Class(es) //////////

    OriginalComponentIdentifier() : its::AsnChoice(false)
    {
        Initialize();
    }

    OriginalComponentIdentifier(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    OriginalComponentIdentifier(const OriginalComponentIdentifier& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    OriginalComponentIdentifier(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    OriginalComponentIdentifier(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetOperationCodeStaticDescription();
    static its::AsnDescObject* GetErrorCodeStaticDescription();
    static its::AsnDescObject* GetUserInfoStaticDescription();

public:

    virtual ~OriginalComponentIdentifier()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new OriginalComponentIdentifier(*this);
    }

    virtual std::string GetName() const
    { return "OriginalComponentIdentifier"; }

    void SetChoiceOperationCode(OperationCode* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetOperationCodeStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceOperationCode(const OperationCode& choice)
    {
        its::AsnObject& asnObject = const_cast<OperationCode&>(choice);
        asnObject.SetDescription(GetOperationCodeStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceOperationCode() const
    {
        return Contains(GetOperationCodeStaticDescription()->TagIdentity());
    }

    const OperationCode& GetChoiceOperationCode() const
    {
        ITS_REQUIRE(ChoiceOperationCode());
        return static_cast<const OperationCode&> (GetChoice());
    }

    void SetChoiceErrorCode(ErrorCode* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetErrorCodeStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceErrorCode(const ErrorCode& choice)
    {
        its::AsnObject& asnObject = const_cast<ErrorCode&>(choice);
        asnObject.SetDescription(GetErrorCodeStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceErrorCode() const
    {
        return Contains(GetErrorCodeStaticDescription()->TagIdentity());
    }

    const ErrorCode& GetChoiceErrorCode() const
    {
        ITS_REQUIRE(ChoiceErrorCode());
        return static_cast<const ErrorCode&> (GetChoice());
    }

    void SetChoiceUserInfo(UserInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetUserInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceUserInfo(const UserInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<UserInfo&>(choice);
        asnObject.SetDescription(GetUserInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceUserInfo() const
    {
        return Contains(GetUserInfoStaticDescription()->TagIdentity());
    }

    const UserInfo& GetChoiceUserInfo() const
    {
        ITS_REQUIRE(ChoiceUserInfo());
        return static_cast<const UserInfo&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_ORIGINAL_COMPONENT_IDENTIFIER_H_)

