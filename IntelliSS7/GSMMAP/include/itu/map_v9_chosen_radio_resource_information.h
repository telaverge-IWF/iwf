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


#if !defined(_MAP_V9_CHOSEN_RADIO_RESOURCE_INFORMATION_H_)
#define _MAP_V9_CHOSEN_RADIO_RESOURCE_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_chosen_channel_info.h>
#include <map_v9_chosen_speech_version.h>



namespace map_v9 {



class ChosenRadioResourceInformation : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ChosenChannelInfo ChosenChannelInfo;


        typedef map_v9::ChosenSpeechVersion ChosenSpeechVersion;


////////// End Nested Class(es) //////////

    ChosenRadioResourceInformation() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ChosenRadioResourceInformation(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ChosenRadioResourceInformation(const ChosenRadioResourceInformation& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ChosenRadioResourceInformation(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetChosenChannelInfoStaticDescription();
    static its::AsnDescObject* GetChosenSpeechVersionStaticDescription();

public:

    virtual ~ChosenRadioResourceInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ChosenRadioResourceInformation(*this);
    }

    virtual std::string GetName() const
    { return "ChosenRadioResourceInformation"; }

    void SetChosenChannelInfo(ChosenChannelInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChosenChannelInfoStaticDescription());
        AddElement(0, element);
    }

    void SetChosenChannelInfo(const ChosenChannelInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ChosenChannelInfo&>(element);
        asnObject.SetDescription(GetChosenChannelInfoStaticDescription());
        AddElement(0, element);
    }

    bool OptionChosenChannelInfo() const
    {
        return Contains(0);
    }

    const ChosenChannelInfo& GetChosenChannelInfo() const
    {
        ITS_REQUIRE(OptionChosenChannelInfo());
        return static_cast<const ChosenChannelInfo&> (ElementAt(0));
    }

    void SetChosenSpeechVersion(ChosenSpeechVersion* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChosenSpeechVersionStaticDescription());
        AddElement(1, element);
    }

    void SetChosenSpeechVersion(const ChosenSpeechVersion& element)
    {
        its::AsnObject& asnObject = const_cast<ChosenSpeechVersion&>(element);
        asnObject.SetDescription(GetChosenSpeechVersionStaticDescription());
        AddElement(1, element);
    }

    bool OptionChosenSpeechVersion() const
    {
        return Contains(1);
    }

    const ChosenSpeechVersion& GetChosenSpeechVersion() const
    {
        ITS_REQUIRE(OptionChosenSpeechVersion());
        return static_cast<const ChosenSpeechVersion&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_CHOSEN_RADIO_RESOURCE_INFORMATION_H_)

