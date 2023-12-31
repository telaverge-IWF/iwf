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


#if !defined(_MAP_V1_CALL_BARRED_ERROR_ARG_H_)
#define _MAP_V1_CALL_BARRED_ERROR_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v1 {



class CallBarredErrorArg : public its::AsnEnumerated
{
public:

    CallBarredErrorArg() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    CallBarredErrorArg(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    CallBarredErrorArg(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    CallBarredErrorArg(const CallBarredErrorArg& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    CallBarredErrorArg(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    CallBarredErrorArg(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~CallBarredErrorArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallBarredErrorArg(*this);
    }

    virtual std::string GetName() const
    { return "CallBarredErrorArg"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        CALL_BARRED_ERROR_ARG_BARRING_SERVICE_ACTIVE = 0,
        CALL_BARRED_ERROR_ARG_OPERATOR_BARRING = 1

    };

    void SetBarringServiceActive()
    { _value = 0; }

    bool IsBarringServiceActive() const
    { return _value == 0; }

    void SetOperatorBarring()
    { _value = 1; }

    bool IsOperatorBarring() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V1_CALL_BARRED_ERROR_ARG_H_)

