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


#if !defined(_CAP_V3_CONNECTED_NUMBER_TREATMENT_IND_H_)
#define _CAP_V3_CONNECTED_NUMBER_TREATMENT_IND_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace cap_v3 {



class ConnectedNumberTreatmentInd : public its::AsnEnumerated
{
public:

    ConnectedNumberTreatmentInd() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ConnectedNumberTreatmentInd(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ConnectedNumberTreatmentInd(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectedNumberTreatmentInd(const ConnectedNumberTreatmentInd& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ConnectedNumberTreatmentInd(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ConnectedNumberTreatmentInd(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ConnectedNumberTreatmentInd()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ConnectedNumberTreatmentInd(*this);
    }

    virtual std::string GetName() const
    { return "ConnectedNumberTreatmentInd"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        CONNECTED_NUMBER_TREATMENT_IND_NO_IN_IMPACT = 0,
        CONNECTED_NUMBER_TREATMENT_IND_PRESENTATION_RESTRICTED = 1,
        CONNECTED_NUMBER_TREATMENT_IND_PRESENT_CALLED_IN_NUMBER = 2,
        CONNECTED_NUMBER_TREATMENT_IND_PRESENT_CALL_IN_NUMBER_RESTRICTED = 3

    };

    void SetNoINImpact()
    { _value = 0; }

    bool IsNoINImpact() const
    { return _value == 0; }

    void SetPresentationRestricted()
    { _value = 1; }

    bool IsPresentationRestricted() const
    { return _value == 1; }

    void SetPresentCalledINNumber()
    { _value = 2; }

    bool IsPresentCalledINNumber() const
    { return _value == 2; }

    void SetPresentCallINNumberRestricted()
    { _value = 3; }

    bool IsPresentCallINNumberRestricted() const
    { return _value == 3; }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONNECTED_NUMBER_TREATMENT_IND_H_)

