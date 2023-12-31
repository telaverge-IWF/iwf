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


#if !defined(_CAP_V2_SPECIALIZED_RESOURCE_REPORT_ARG_H_)
#define _CAP_V2_SPECIALIZED_RESOURCE_REPORT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnNull.h>



namespace cap_v2 {



class SpecializedResourceReportArg : public its::AsnNull
{
public:

    SpecializedResourceReportArg() : its::AsnNull(false)
    {
        Initialize();
    }

    SpecializedResourceReportArg(its::Octets& octets) : its::AsnNull(false)
    {
        Initialize();
        Decode(octets);
    }

    SpecializedResourceReportArg(const SpecializedResourceReportArg& rhs) : its::AsnNull(rhs)
    {
        // Nothing to do.
    }

    SpecializedResourceReportArg(its::AsnDescObject* description) : its::AsnNull(description)
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

    virtual ~SpecializedResourceReportArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SpecializedResourceReportArg(*this);
    }

    virtual std::string GetName() const
    { return "SpecializedResourceReportArg"; }

};



} // namespace.

#endif    // !defined(_CAP_V2_SPECIALIZED_RESOURCE_REPORT_ARG_H_)

