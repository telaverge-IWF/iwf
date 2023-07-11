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


#if !defined(_MAP_V3_VGCS_DATA_LIST_H_)
#define _MAP_V3_VGCS_DATA_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v3_voice_group_call_data.h>



namespace map_v3 {



class VGCSDataList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v3::VoiceGroupCallData VoiceGroupCallData;


////////// End Nested Class //////////

    VGCSDataList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    VGCSDataList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    VGCSDataList(const VGCSDataList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    VGCSDataList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetVoiceGroupCallDataStaticDescription();

public:

    virtual ~VGCSDataList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new VGCSDataList(*this);
    }

    virtual std::string GetName() const
    { return "VGCSDataList"; }

    void AddElement(VoiceGroupCallData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVoiceGroupCallDataStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const VoiceGroupCallData& element)
    {
        its::AsnObject& asnObject = const_cast<VoiceGroupCallData&>(element);
        asnObject.SetDescription(GetVoiceGroupCallDataStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const VoiceGroupCallData& ElementAt(int index) const
    {
        return static_cast<const VoiceGroupCallData&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_VGCS_DATA_LIST_H_)
