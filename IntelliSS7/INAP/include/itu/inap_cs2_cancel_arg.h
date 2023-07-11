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


#if !defined(_INAP_CS2_CANCEL_ARG_H_)
#define _INAP_CS2_CANCEL_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnNull.h>
#include <AsnSequence.h>
#include <AsnInteger.h>

#include <inap_cs2_invoke_id.h>
#include <inap_cs2_call_segment_id.h>



namespace inap_cs2 {



class CancelArg : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class AllRequests : public its::AsnNull
    {
    public:

        AllRequests() : its::AsnNull(false)
        {
            Initialize();
        }

        AllRequests(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        AllRequests(const AllRequests& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        AllRequests(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~AllRequests()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new AllRequests(*this);
        }

        virtual std::string GetName() const
        { return "AllRequests"; }

    };



    class CallSegmentToCancel : public its::AsnSequence
    {
    public:


    ////////// Begin Nested Class(es) //////////


            typedef inap_cs2::InvokeID InvokeID;


            typedef inap_cs2::CallSegmentID CallSegmentID;


    ////////// End Nested Class(es) //////////

        CallSegmentToCancel() : its::AsnSequence(2, false)
        {
            Initialize();
        }

        CallSegmentToCancel(its::Octets& octets) : its::AsnSequence(2, false)
        {
            Initialize();
            Decode(octets);
        }

        CallSegmentToCancel(const CallSegmentToCancel& rhs) : its::AsnSequence(rhs)
        {
            // Nothing to do.
        }

        CallSegmentToCancel(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

        static its::AsnDescObject* GetInvokeIDStaticDescription();
        static its::AsnDescObject* GetCallSegmentIDStaticDescription();

    public:

        virtual ~CallSegmentToCancel()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CallSegmentToCancel(*this);
        }

        virtual std::string GetName() const
        { return "CallSegmentToCancel"; }

        void SetInvokeID(InvokeID* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetInvokeIDStaticDescription());
            AddElement(0, element);
        }

        void SetInvokeID(const InvokeID& element)
        {
            its::AsnObject& asnObject = const_cast<InvokeID&>(element);
            asnObject.SetDescription(GetInvokeIDStaticDescription());
            AddElement(0, element);
        }

        const InvokeID& GetInvokeID() const
        {
            return static_cast<const InvokeID&> (ElementAt(0));
        }

        void SetCallSegmentID(CallSegmentID* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetCallSegmentIDStaticDescription());
            AddElement(1, element);
        }

        void SetCallSegmentID(const CallSegmentID& element)
        {
            its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
            asnObject.SetDescription(GetCallSegmentIDStaticDescription());
            AddElement(1, element);
        }

        const CallSegmentID& GetCallSegmentID() const
        {
            return static_cast<const CallSegmentID&> (ElementAt(1));
        }

    };


        typedef inap_cs2::InvokeID InvokeID;


////////// End Nested Class(es) //////////

    CancelArg() : its::AsnChoice(false)
    {
        Initialize();
    }

    CancelArg(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    CancelArg(const CancelArg& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    CancelArg(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    CancelArg(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetInvokeIDStaticDescription();
    static its::AsnDescObject* GetAllRequestsStaticDescription();
    static its::AsnDescObject* GetCallSegmentToCancelStaticDescription();

public:

    virtual ~CancelArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CancelArg(*this);
    }

    virtual std::string GetName() const
    { return "CancelArg"; }

    void SetChoiceInvokeID(InvokeID* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetInvokeIDStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceInvokeID(const InvokeID& choice)
    {
        its::AsnObject& asnObject = const_cast<InvokeID&>(choice);
        asnObject.SetDescription(GetInvokeIDStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceInvokeID() const
    {
        return Contains(GetInvokeIDStaticDescription()->TagIdentity());
    }

    const InvokeID& GetChoiceInvokeID() const
    {
        ITS_REQUIRE(ChoiceInvokeID());
        return static_cast<const InvokeID&> (GetChoice());
    }

    void SetChoiceAllRequests(AllRequests* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetAllRequestsStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceAllRequests(const AllRequests& choice)
    {
        its::AsnObject& asnObject = const_cast<AllRequests&>(choice);
        asnObject.SetDescription(GetAllRequestsStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceAllRequests() const
    {
        return Contains(GetAllRequestsStaticDescription()->TagIdentity());
    }

    const AllRequests& GetChoiceAllRequests() const
    {
        ITS_REQUIRE(ChoiceAllRequests());
        return static_cast<const AllRequests&> (GetChoice());
    }

    void SetChoiceCallSegmentToCancel(CallSegmentToCancel* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCallSegmentToCancelStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCallSegmentToCancel(const CallSegmentToCancel& choice)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentToCancel&>(choice);
        asnObject.SetDescription(GetCallSegmentToCancelStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCallSegmentToCancel() const
    {
        return Contains(GetCallSegmentToCancelStaticDescription()->TagIdentity());
    }

    const CallSegmentToCancel& GetChoiceCallSegmentToCancel() const
    {
        ITS_REQUIRE(ChoiceCallSegmentToCancel());
        return static_cast<const CallSegmentToCancel&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CANCEL_ARG_H_)

