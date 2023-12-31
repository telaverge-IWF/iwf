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


#if !defined(_MAP_V9_CODEC_LIST_H_)
#define _MAP_V9_CODEC_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_codec.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class CodecList : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::Codec Codec;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    CodecList() : its::AsnSequence(9, false)
    {
        Initialize();
    }

    CodecList(its::Octets& octets) : its::AsnSequence(9, false)
    {
        Initialize();
        Decode(octets);
    }

    CodecList(const CodecList& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CodecList(its::AsnDescObject* description) : its::AsnSequence(9, description)
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

    static its::AsnDescObject* GetCodec1StaticDescription();
    static its::AsnDescObject* GetCodec2StaticDescription();
    static its::AsnDescObject* GetCodec3StaticDescription();
    static its::AsnDescObject* GetCodec4StaticDescription();
    static its::AsnDescObject* GetCodec5StaticDescription();
    static its::AsnDescObject* GetCodec6StaticDescription();
    static its::AsnDescObject* GetCodec7StaticDescription();
    static its::AsnDescObject* GetCodec8StaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~CodecList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CodecList(*this);
    }

    virtual std::string GetName() const
    { return "CodecList"; }

    void SetCodec1(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec1StaticDescription());
        AddElement(0, element);
    }

    void SetCodec1(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec1StaticDescription());
        AddElement(0, element);
    }

    const Codec& GetCodec1() const
    {
        return static_cast<const Codec&> (ElementAt(0));
    }

    void SetCodec2(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec2StaticDescription());
        AddElement(1, element);
    }

    void SetCodec2(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec2StaticDescription());
        AddElement(1, element);
    }

    bool OptionCodec2() const
    {
        return Contains(1);
    }

    const Codec& GetCodec2() const
    {
        ITS_REQUIRE(OptionCodec2());
        return static_cast<const Codec&> (ElementAt(1));
    }

    void SetCodec3(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec3StaticDescription());
        AddElement(2, element);
    }

    void SetCodec3(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec3StaticDescription());
        AddElement(2, element);
    }

    bool OptionCodec3() const
    {
        return Contains(2);
    }

    const Codec& GetCodec3() const
    {
        ITS_REQUIRE(OptionCodec3());
        return static_cast<const Codec&> (ElementAt(2));
    }

    void SetCodec4(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec4StaticDescription());
        AddElement(3, element);
    }

    void SetCodec4(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec4StaticDescription());
        AddElement(3, element);
    }

    bool OptionCodec4() const
    {
        return Contains(3);
    }

    const Codec& GetCodec4() const
    {
        ITS_REQUIRE(OptionCodec4());
        return static_cast<const Codec&> (ElementAt(3));
    }

    void SetCodec5(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec5StaticDescription());
        AddElement(4, element);
    }

    void SetCodec5(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec5StaticDescription());
        AddElement(4, element);
    }

    bool OptionCodec5() const
    {
        return Contains(4);
    }

    const Codec& GetCodec5() const
    {
        ITS_REQUIRE(OptionCodec5());
        return static_cast<const Codec&> (ElementAt(4));
    }

    void SetCodec6(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec6StaticDescription());
        AddElement(5, element);
    }

    void SetCodec6(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec6StaticDescription());
        AddElement(5, element);
    }

    bool OptionCodec6() const
    {
        return Contains(5);
    }

    const Codec& GetCodec6() const
    {
        ITS_REQUIRE(OptionCodec6());
        return static_cast<const Codec&> (ElementAt(5));
    }

    void SetCodec7(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec7StaticDescription());
        AddElement(6, element);
    }

    void SetCodec7(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec7StaticDescription());
        AddElement(6, element);
    }

    bool OptionCodec7() const
    {
        return Contains(6);
    }

    const Codec& GetCodec7() const
    {
        ITS_REQUIRE(OptionCodec7());
        return static_cast<const Codec&> (ElementAt(6));
    }

    void SetCodec8(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCodec8StaticDescription());
        AddElement(7, element);
    }

    void SetCodec8(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCodec8StaticDescription());
        AddElement(7, element);
    }

    bool OptionCodec8() const
    {
        return Contains(7);
    }

    const Codec& GetCodec8() const
    {
        ITS_REQUIRE(OptionCodec8());
        return static_cast<const Codec&> (ElementAt(7));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(8, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(8, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(8);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(8));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_CODEC_LIST_H_)

