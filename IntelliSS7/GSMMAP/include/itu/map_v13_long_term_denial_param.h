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


#if !defined(_MAP_V13_LONG_TERM_DENIAL_PARAM_H_)
#define _MAP_V13_LONG_TERM_DENIAL_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>



namespace map_v13 {



class LongTermDenialParam : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


////////// End Nested Class(es) //////////

    LongTermDenialParam() : its::AsnSequence(0, false)
    {
        Initialize();
    }

    LongTermDenialParam(its::Octets& octets) : its::AsnSequence(0, false)
    {
        Initialize();
        Decode(octets);
    }

    LongTermDenialParam(const LongTermDenialParam& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    LongTermDenialParam(its::AsnDescObject* description) : its::AsnSequence(0, description)
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

    virtual ~LongTermDenialParam()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LongTermDenialParam(*this);
    }

    virtual std::string GetName() const
    { return "LongTermDenialParam"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_LONG_TERM_DENIAL_PARAM_H_)
