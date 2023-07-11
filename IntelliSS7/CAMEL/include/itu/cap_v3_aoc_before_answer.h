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


#if !defined(_CAP_V3_AOC_BEFORE_ANSWER_H_)
#define _CAP_V3_AOC_BEFORE_ANSWER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <cap_v3_cai_gsm0224.h>
#include <cap_v3_aoc_subsequent.h>



namespace cap_v3 {



class AOCBeforeAnswer : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::CAI_GSM0224 CAI_GSM0224;


        typedef cap_v3::AOCSubsequent AOCSubsequent;


////////// End Nested Class(es) //////////

    AOCBeforeAnswer() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    AOCBeforeAnswer(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    AOCBeforeAnswer(const AOCBeforeAnswer& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AOCBeforeAnswer(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetAOCInitialStaticDescription();
    static its::AsnDescObject* GetAOCSubsequentStaticDescription();

public:

    virtual ~AOCBeforeAnswer()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AOCBeforeAnswer(*this);
    }

    virtual std::string GetName() const
    { return "AOCBeforeAnswer"; }

    void SetAOCInitial(CAI_GSM0224* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAOCInitialStaticDescription());
        AddElement(0, element);
    }

    void SetAOCInitial(const CAI_GSM0224& element)
    {
        its::AsnObject& asnObject = const_cast<CAI_GSM0224&>(element);
        asnObject.SetDescription(GetAOCInitialStaticDescription());
        AddElement(0, element);
    }

    const CAI_GSM0224& GetAOCInitial() const
    {
        return static_cast<const CAI_GSM0224&> (ElementAt(0));
    }

    void SetAOCSubsequent(AOCSubsequent* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAOCSubsequentStaticDescription());
        AddElement(1, element);
    }

    void SetAOCSubsequent(const AOCSubsequent& element)
    {
        its::AsnObject& asnObject = const_cast<AOCSubsequent&>(element);
        asnObject.SetDescription(GetAOCSubsequentStaticDescription());
        AddElement(1, element);
    }

    bool OptionAOCSubsequent() const
    {
        return Contains(1);
    }

    const AOCSubsequent& GetAOCSubsequent() const
    {
        ITS_REQUIRE(OptionAOCSubsequent());
        return static_cast<const AOCSubsequent&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_AOC_BEFORE_ANSWER_H_)
