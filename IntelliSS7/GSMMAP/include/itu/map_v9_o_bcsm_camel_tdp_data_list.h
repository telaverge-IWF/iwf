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


#if !defined(_MAP_V9_O_BCSM_CAMEL_TDP_DATA_LIST_H_)
#define _MAP_V9_O_BCSM_CAMEL_TDP_DATA_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v9_o_bcsm_camel_tdp_data.h>



namespace map_v9 {



class O_BcsmCamelTDPDataList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::O_BcsmCamelTDPData O_BcsmCamelTDPData;


////////// End Nested Class //////////

    O_BcsmCamelTDPDataList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    O_BcsmCamelTDPDataList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    O_BcsmCamelTDPDataList(const O_BcsmCamelTDPDataList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    O_BcsmCamelTDPDataList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetO_BcsmCamelTDPDataStaticDescription();

public:

    virtual ~O_BcsmCamelTDPDataList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new O_BcsmCamelTDPDataList(*this);
    }

    virtual std::string GetName() const
    { return "O_BcsmCamelTDPDataList"; }

    void AddElement(O_BcsmCamelTDPData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetO_BcsmCamelTDPDataStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const O_BcsmCamelTDPData& element)
    {
        its::AsnObject& asnObject = const_cast<O_BcsmCamelTDPData&>(element);
        asnObject.SetDescription(GetO_BcsmCamelTDPDataStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const O_BcsmCamelTDPData& ElementAt(int index) const
    {
        return static_cast<const O_BcsmCamelTDPData&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_O_BCSM_CAMEL_TDP_DATA_LIST_H_)

