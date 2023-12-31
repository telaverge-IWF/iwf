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


#if !defined(_INAP_CS2_RECEIVED_INFORMATION_ARG_H_)
#define _INAP_CS2_RECEIVED_INFORMATION_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>
#include <AsnBaseString.h>

#include <inap_cs2_digits.h>
#include <IA5String.h>



namespace inap_cs2 {



class ReceivedInformationArg : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::Digits Digits;


    typedef its::IA5String IA5String;


////////// End Nested Class(es) //////////

    ReceivedInformationArg() : its::AsnChoice(false)
    {
        Initialize();
    }

    ReceivedInformationArg(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    ReceivedInformationArg(const ReceivedInformationArg& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    ReceivedInformationArg(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    ReceivedInformationArg(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetDigitsResponseStaticDescription();
    static its::AsnDescObject* GetIA5ResponseStaticDescription();

public:

    virtual ~ReceivedInformationArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReceivedInformationArg(*this);
    }

    virtual std::string GetName() const
    { return "ReceivedInformationArg"; }

    void SetChoiceDigitsResponse(Digits* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetDigitsResponseStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceDigitsResponse(const Digits& choice)
    {
        its::AsnObject& asnObject = const_cast<Digits&>(choice);
        asnObject.SetDescription(GetDigitsResponseStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceDigitsResponse() const
    {
        return Contains(GetDigitsResponseStaticDescription()->TagIdentity());
    }

    const Digits& GetChoiceDigitsResponse() const
    {
        ITS_REQUIRE(ChoiceDigitsResponse());
        return static_cast<const Digits&> (GetChoice());
    }

    void SetChoiceIA5Response(IA5String* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetIA5ResponseStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceIA5Response(const IA5String& choice)
    {
        its::AsnObject& asnObject = const_cast<IA5String&>(choice);
        asnObject.SetDescription(GetIA5ResponseStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceIA5Response() const
    {
        return Contains(GetIA5ResponseStaticDescription()->TagIdentity());
    }

    const IA5String& GetChoiceIA5Response() const
    {
        ITS_REQUIRE(ChoiceIA5Response());
        return static_cast<const IA5String&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_RECEIVED_INFORMATION_ARG_H_)

