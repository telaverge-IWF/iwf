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


#if !defined(_CAP_V3_CANCEL_FAILED_H_)
#define _CAP_V3_CANCEL_FAILED_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>

#include <cap_v3_invoke_id.h>



namespace cap_v3 {



class CancelFailed : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Problem : public its::AsnEnumerated
    {
    public:

        Problem() : its::AsnEnumerated(false)
        {
            Initialize();
        }

        Problem(long value) : its::AsnEnumerated(value, false)
        {
            Initialize();
        }

        Problem(its::Octets& octets) : its::AsnEnumerated(false)
        {
            Initialize();
            Decode(octets);
        }

        Problem(const Problem& rhs) : its::AsnEnumerated(rhs)
        {
            // Nothing to do.
        }

        Problem(its::AsnDescObject* description) : its::AsnEnumerated(description)
        {
            // Nothing to do.
        }

        Problem(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

        virtual ~Problem()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Problem(*this);
        }

        virtual std::string GetName() const
        { return "Problem"; }

        virtual long Get(const std::string& valueName) const;

        virtual std::string Get(long value) const;

        virtual std::string GetExt(long value) const;

        enum {
            PROBLEM_UNKNOWN_OPERATION = 0,
            PROBLEM_TOO_LATE = 1,
            PROBLEM_OPERATION_NOT_CANCELLABLE = 2

        };

        void SetUnknownOperation()
        { _value = 0; }

        bool IsUnknownOperation() const
        { return _value == 0; }

        void SetTooLate()
        { _value = 1; }

        bool IsTooLate() const
        { return _value == 1; }

        void SetOperationNotCancellable()
        { _value = 2; }

        bool IsOperationNotCancellable() const
        { return _value == 2; }

    };


        typedef cap_v3::InvokeID InvokeID;


////////// End Nested Class(es) //////////

    CancelFailed() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    CancelFailed(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    CancelFailed(const CancelFailed& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CancelFailed(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetProblemStaticDescription();
    static its::AsnDescObject* GetOperationStaticDescription();

public:

    virtual ~CancelFailed()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CancelFailed(*this);
    }

    virtual std::string GetName() const
    { return "CancelFailed"; }

    void SetProblem(Problem* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProblemStaticDescription());
        AddElement(0, element);
    }

    void SetProblem(const Problem& element)
    {
        its::AsnObject& asnObject = const_cast<Problem&>(element);
        asnObject.SetDescription(GetProblemStaticDescription());
        AddElement(0, element);
    }

    const Problem& GetProblem() const
    {
        return static_cast<const Problem&> (ElementAt(0));
    }

    void SetOperation(InvokeID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOperationStaticDescription());
        AddElement(1, element);
    }

    void SetOperation(const InvokeID& element)
    {
        its::AsnObject& asnObject = const_cast<InvokeID&>(element);
        asnObject.SetDescription(GetOperationStaticDescription());
        AddElement(1, element);
    }

    const InvokeID& GetOperation() const
    {
        return static_cast<const InvokeID&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CANCEL_FAILED_H_)

