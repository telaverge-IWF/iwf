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


#if !defined(_MAP_V13_PS_SUBSCRIBER_STATE_H_)
#define _MAP_V13_PS_SUBSCRIBER_STATE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnNull.h>
#include <AsnSequenceOf.h>
#include <AsnEnumerated.h>

#include <map_v13_pdp_context_info_list.h>
#include <map_v13_not_reachable_reason.h>



namespace map_v13 {



class PS_SubscriberState : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class NotProvidedFromSGSNorMME : public its::AsnNull
    {
    public:

        NotProvidedFromSGSNorMME() : its::AsnNull(false)
        {
            Initialize();
        }

        NotProvidedFromSGSNorMME(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        NotProvidedFromSGSNorMME(const NotProvidedFromSGSNorMME& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        NotProvidedFromSGSNorMME(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~NotProvidedFromSGSNorMME()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NotProvidedFromSGSNorMME(*this);
        }

        virtual std::string GetName() const
        { return "NotProvidedFromSGSNorMME"; }

    };



    class Ps_Detached : public its::AsnNull
    {
    public:

        Ps_Detached() : its::AsnNull(false)
        {
            Initialize();
        }

        Ps_Detached(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Ps_Detached(const Ps_Detached& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Ps_Detached(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Ps_Detached()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Ps_Detached(*this);
        }

        virtual std::string GetName() const
        { return "Ps_Detached"; }

    };



    class Ps_AttachedNotReachableForPaging : public its::AsnNull
    {
    public:

        Ps_AttachedNotReachableForPaging() : its::AsnNull(false)
        {
            Initialize();
        }

        Ps_AttachedNotReachableForPaging(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Ps_AttachedNotReachableForPaging(const Ps_AttachedNotReachableForPaging& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Ps_AttachedNotReachableForPaging(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Ps_AttachedNotReachableForPaging()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Ps_AttachedNotReachableForPaging(*this);
        }

        virtual std::string GetName() const
        { return "Ps_AttachedNotReachableForPaging"; }

    };



    class Ps_AttachedReachableForPaging : public its::AsnNull
    {
    public:

        Ps_AttachedReachableForPaging() : its::AsnNull(false)
        {
            Initialize();
        }

        Ps_AttachedReachableForPaging(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Ps_AttachedReachableForPaging(const Ps_AttachedReachableForPaging& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Ps_AttachedReachableForPaging(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Ps_AttachedReachableForPaging()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Ps_AttachedReachableForPaging(*this);
        }

        virtual std::string GetName() const
        { return "Ps_AttachedReachableForPaging"; }

    };


        typedef map_v13::PDP_ContextInfoList PDP_ContextInfoList;


        typedef map_v13::NotReachableReason NotReachableReason;


////////// End Nested Class(es) //////////

    PS_SubscriberState() : its::AsnChoice(false)
    {
        Initialize();
    }

    PS_SubscriberState(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    PS_SubscriberState(const PS_SubscriberState& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    PS_SubscriberState(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    PS_SubscriberState(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetNotProvidedFromSGSNorMMEStaticDescription();
    static its::AsnDescObject* GetPs_DetachedStaticDescription();
    static its::AsnDescObject* GetPs_AttachedNotReachableForPagingStaticDescription();
    static its::AsnDescObject* GetPs_AttachedReachableForPagingStaticDescription();
    static its::AsnDescObject* GetPs_PDP_ActiveNotReachableForPagingStaticDescription();
    static its::AsnDescObject* GetPs_PDP_ActiveReachableForPagingStaticDescription();
    static its::AsnDescObject* GetNetDetNotReachableStaticDescription();

public:

    virtual ~PS_SubscriberState()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PS_SubscriberState(*this);
    }

    virtual std::string GetName() const
    { return "PS_SubscriberState"; }

    void SetChoiceNotProvidedFromSGSNorMME(NotProvidedFromSGSNorMME* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetNotProvidedFromSGSNorMMEStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceNotProvidedFromSGSNorMME(const NotProvidedFromSGSNorMME& choice)
    {
        its::AsnObject& asnObject = const_cast<NotProvidedFromSGSNorMME&>(choice);
        asnObject.SetDescription(GetNotProvidedFromSGSNorMMEStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceNotProvidedFromSGSNorMME() const
    {
        return Contains(GetNotProvidedFromSGSNorMMEStaticDescription()->TagIdentity());
    }

    const NotProvidedFromSGSNorMME& GetChoiceNotProvidedFromSGSNorMME() const
    {
        ITS_REQUIRE(ChoiceNotProvidedFromSGSNorMME());
        return static_cast<const NotProvidedFromSGSNorMME&> (GetChoice());
    }

    void SetChoicePs_Detached(Ps_Detached* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPs_DetachedStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePs_Detached(const Ps_Detached& choice)
    {
        its::AsnObject& asnObject = const_cast<Ps_Detached&>(choice);
        asnObject.SetDescription(GetPs_DetachedStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePs_Detached() const
    {
        return Contains(GetPs_DetachedStaticDescription()->TagIdentity());
    }

    const Ps_Detached& GetChoicePs_Detached() const
    {
        ITS_REQUIRE(ChoicePs_Detached());
        return static_cast<const Ps_Detached&> (GetChoice());
    }

    void SetChoicePs_AttachedNotReachableForPaging(Ps_AttachedNotReachableForPaging* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPs_AttachedNotReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePs_AttachedNotReachableForPaging(const Ps_AttachedNotReachableForPaging& choice)
    {
        its::AsnObject& asnObject = const_cast<Ps_AttachedNotReachableForPaging&>(choice);
        asnObject.SetDescription(GetPs_AttachedNotReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePs_AttachedNotReachableForPaging() const
    {
        return Contains(GetPs_AttachedNotReachableForPagingStaticDescription()->TagIdentity());
    }

    const Ps_AttachedNotReachableForPaging& GetChoicePs_AttachedNotReachableForPaging() const
    {
        ITS_REQUIRE(ChoicePs_AttachedNotReachableForPaging());
        return static_cast<const Ps_AttachedNotReachableForPaging&> (GetChoice());
    }

    void SetChoicePs_AttachedReachableForPaging(Ps_AttachedReachableForPaging* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPs_AttachedReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePs_AttachedReachableForPaging(const Ps_AttachedReachableForPaging& choice)
    {
        its::AsnObject& asnObject = const_cast<Ps_AttachedReachableForPaging&>(choice);
        asnObject.SetDescription(GetPs_AttachedReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePs_AttachedReachableForPaging() const
    {
        return Contains(GetPs_AttachedReachableForPagingStaticDescription()->TagIdentity());
    }

    const Ps_AttachedReachableForPaging& GetChoicePs_AttachedReachableForPaging() const
    {
        ITS_REQUIRE(ChoicePs_AttachedReachableForPaging());
        return static_cast<const Ps_AttachedReachableForPaging&> (GetChoice());
    }

    void SetChoicePs_PDP_ActiveNotReachableForPaging(PDP_ContextInfoList* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPs_PDP_ActiveNotReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePs_PDP_ActiveNotReachableForPaging(const PDP_ContextInfoList& choice)
    {
        its::AsnObject& asnObject = const_cast<PDP_ContextInfoList&>(choice);
        asnObject.SetDescription(GetPs_PDP_ActiveNotReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePs_PDP_ActiveNotReachableForPaging() const
    {
        return Contains(GetPs_PDP_ActiveNotReachableForPagingStaticDescription()->TagIdentity());
    }

    const PDP_ContextInfoList& GetChoicePs_PDP_ActiveNotReachableForPaging() const
    {
        ITS_REQUIRE(ChoicePs_PDP_ActiveNotReachableForPaging());
        return static_cast<const PDP_ContextInfoList&> (GetChoice());
    }

    void SetChoicePs_PDP_ActiveReachableForPaging(PDP_ContextInfoList* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPs_PDP_ActiveReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePs_PDP_ActiveReachableForPaging(const PDP_ContextInfoList& choice)
    {
        its::AsnObject& asnObject = const_cast<PDP_ContextInfoList&>(choice);
        asnObject.SetDescription(GetPs_PDP_ActiveReachableForPagingStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePs_PDP_ActiveReachableForPaging() const
    {
        return Contains(GetPs_PDP_ActiveReachableForPagingStaticDescription()->TagIdentity());
    }

    const PDP_ContextInfoList& GetChoicePs_PDP_ActiveReachableForPaging() const
    {
        ITS_REQUIRE(ChoicePs_PDP_ActiveReachableForPaging());
        return static_cast<const PDP_ContextInfoList&> (GetChoice());
    }

    void SetChoiceNetDetNotReachable(NotReachableReason* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetNetDetNotReachableStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceNetDetNotReachable(const NotReachableReason& choice)
    {
        its::AsnObject& asnObject = const_cast<NotReachableReason&>(choice);
        asnObject.SetDescription(GetNetDetNotReachableStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceNetDetNotReachable() const
    {
        return Contains(GetNetDetNotReachableStaticDescription()->TagIdentity());
    }

    const NotReachableReason& GetChoiceNetDetNotReachable() const
    {
        ITS_REQUIRE(ChoiceNetDetNotReachable());
        return static_cast<const NotReachableReason&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PS_SUBSCRIBER_STATE_H_)

