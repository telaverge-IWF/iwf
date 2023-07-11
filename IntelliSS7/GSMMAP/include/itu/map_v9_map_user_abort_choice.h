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


#if !defined(_MAP_V9_MAP_USER_ABORT_CHOICE_H_)
#define _MAP_V9_MAP_USER_ABORT_CHOICE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnNull.h>
#include <AsnEnumerated.h>

#include <map_v9_resource_unavailable_reason.h>
#include <map_v9_procedure_cancellation_reason.h>



namespace map_v9 {



class MAP_UserAbortChoice : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class UserSpecificReason : public its::AsnNull
    {
    public:

        UserSpecificReason() : its::AsnNull(false)
        {
            Initialize();
        }

        UserSpecificReason(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        UserSpecificReason(const UserSpecificReason& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        UserSpecificReason(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~UserSpecificReason()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new UserSpecificReason(*this);
        }

        virtual std::string GetName() const
        { return "UserSpecificReason"; }

    };



    class UserResourceLimitation : public its::AsnNull
    {
    public:

        UserResourceLimitation() : its::AsnNull(false)
        {
            Initialize();
        }

        UserResourceLimitation(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        UserResourceLimitation(const UserResourceLimitation& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        UserResourceLimitation(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~UserResourceLimitation()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new UserResourceLimitation(*this);
        }

        virtual std::string GetName() const
        { return "UserResourceLimitation"; }

    };


        typedef map_v9::ResourceUnavailableReason ResourceUnavailableReason;


        typedef map_v9::ProcedureCancellationReason ProcedureCancellationReason;


////////// End Nested Class(es) //////////

    MAP_UserAbortChoice() : its::AsnChoice(false)
    {
        Initialize();
    }

    MAP_UserAbortChoice(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    MAP_UserAbortChoice(const MAP_UserAbortChoice& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    MAP_UserAbortChoice(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    MAP_UserAbortChoice(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetUserSpecificReasonStaticDescription();
    static its::AsnDescObject* GetUserResourceLimitationStaticDescription();
    static its::AsnDescObject* GetResourceUnavailableStaticDescription();
    static its::AsnDescObject* GetApplicationProcedureCancellationStaticDescription();

public:

    virtual ~MAP_UserAbortChoice()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MAP_UserAbortChoice(*this);
    }

    virtual std::string GetName() const
    { return "MAP_UserAbortChoice"; }

    void SetChoiceUserSpecificReason(UserSpecificReason* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetUserSpecificReasonStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceUserSpecificReason(const UserSpecificReason& choice)
    {
        its::AsnObject& asnObject = const_cast<UserSpecificReason&>(choice);
        asnObject.SetDescription(GetUserSpecificReasonStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceUserSpecificReason() const
    {
        return Contains(GetUserSpecificReasonStaticDescription()->TagIdentity());
    }

    const UserSpecificReason& GetChoiceUserSpecificReason() const
    {
        ITS_REQUIRE(ChoiceUserSpecificReason());
        return static_cast<const UserSpecificReason&> (GetChoice());
    }

    void SetChoiceUserResourceLimitation(UserResourceLimitation* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetUserResourceLimitationStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceUserResourceLimitation(const UserResourceLimitation& choice)
    {
        its::AsnObject& asnObject = const_cast<UserResourceLimitation&>(choice);
        asnObject.SetDescription(GetUserResourceLimitationStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceUserResourceLimitation() const
    {
        return Contains(GetUserResourceLimitationStaticDescription()->TagIdentity());
    }

    const UserResourceLimitation& GetChoiceUserResourceLimitation() const
    {
        ITS_REQUIRE(ChoiceUserResourceLimitation());
        return static_cast<const UserResourceLimitation&> (GetChoice());
    }

    void SetChoiceResourceUnavailable(ResourceUnavailableReason* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetResourceUnavailableStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceResourceUnavailable(const ResourceUnavailableReason& choice)
    {
        its::AsnObject& asnObject = const_cast<ResourceUnavailableReason&>(choice);
        asnObject.SetDescription(GetResourceUnavailableStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceResourceUnavailable() const
    {
        return Contains(GetResourceUnavailableStaticDescription()->TagIdentity());
    }

    const ResourceUnavailableReason& GetChoiceResourceUnavailable() const
    {
        ITS_REQUIRE(ChoiceResourceUnavailable());
        return static_cast<const ResourceUnavailableReason&> (GetChoice());
    }

    void SetChoiceApplicationProcedureCancellation(ProcedureCancellationReason* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetApplicationProcedureCancellationStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceApplicationProcedureCancellation(const ProcedureCancellationReason& choice)
    {
        its::AsnObject& asnObject = const_cast<ProcedureCancellationReason&>(choice);
        asnObject.SetDescription(GetApplicationProcedureCancellationStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceApplicationProcedureCancellation() const
    {
        return Contains(GetApplicationProcedureCancellationStaticDescription()->TagIdentity());
    }

    const ProcedureCancellationReason& GetChoiceApplicationProcedureCancellation() const
    {
        ITS_REQUIRE(ChoiceApplicationProcedureCancellation());
        return static_cast<const ProcedureCancellationReason&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_MAP_USER_ABORT_CHOICE_H_)

