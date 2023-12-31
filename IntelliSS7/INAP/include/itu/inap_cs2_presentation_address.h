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


#if !defined(_INAP_CS2_PRESENTATION_ADDRESS_H_)
#define _INAP_CS2_PRESENTATION_ADDRESS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnSetOf.h>



namespace inap_cs2 {



class PresentationAddress : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class PSelector : public its::AsnOctetString
    {
    public:

        PSelector() : its::AsnOctetString(false)
        {
            Initialize();
        }

        PSelector(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        PSelector(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        PSelector(const PSelector& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        PSelector(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        PSelector(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~PSelector()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new PSelector(*this);
        }

        virtual std::string GetName() const
        { return "PSelector"; }

    };



    class SSelector : public its::AsnOctetString
    {
    public:

        SSelector() : its::AsnOctetString(false)
        {
            Initialize();
        }

        SSelector(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        SSelector(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        SSelector(const SSelector& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        SSelector(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        SSelector(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~SSelector()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SSelector(*this);
        }

        virtual std::string GetName() const
        { return "SSelector"; }

    };



    class TSelector : public its::AsnOctetString
    {
    public:

        TSelector() : its::AsnOctetString(false)
        {
            Initialize();
        }

        TSelector(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        TSelector(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        TSelector(const TSelector& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        TSelector(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        TSelector(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~TSelector()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new TSelector(*this);
        }

        virtual std::string GetName() const
        { return "TSelector"; }

    };



    class NAddresses : public its::AsnSetOf
    {
    public:


    ////////// Begin Nested Class //////////



        class OCTETSTRING : public its::AsnOctetString
        {
        public:

            OCTETSTRING() : its::AsnOctetString(false)
            {
                Initialize();
            }

            OCTETSTRING(const std::vector<byte>& array) : its::AsnOctetString(array, false)
            {
                Initialize();
            }

            OCTETSTRING(its::Octets& octets) : its::AsnOctetString(false)
            {
                Initialize();
                Decode(octets);
            }

            OCTETSTRING(const OCTETSTRING& rhs) : its::AsnOctetString(rhs)
            {
                // Nothing to do.
            }

            OCTETSTRING(its::AsnDescObject* description) : its::AsnOctetString(description)
            {
                // Nothing to do.
            }

            OCTETSTRING(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

            virtual ~OCTETSTRING()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new OCTETSTRING(*this);
            }

            virtual std::string GetName() const
            { return "OCTETSTRING"; }

        };


    ////////// End Nested Class //////////

        NAddresses() : its::AsnSetOf(false)
        {
            Initialize();
        }

        NAddresses(its::Octets& octets) : its::AsnSetOf(false)
        {
            Initialize();
            Decode(octets);
        }

        NAddresses(const NAddresses& rhs) : its::AsnSetOf(rhs)
        {
            // Nothing to do.
        }

        NAddresses(its::AsnDescObject* description) : its::AsnSetOf(description)
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

        static its::AsnDescObject* GetOCTETSTRINGStaticDescription();

    public:

        virtual ~NAddresses()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NAddresses(*this);
        }

        virtual std::string GetName() const
        { return "NAddresses"; }

        void AddElement(OCTETSTRING* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetOCTETSTRINGStaticDescription());
            AsnSetOf::AddElement(element);
        }

        void AddElement(const OCTETSTRING& element)
        {
            its::AsnObject& asnObject = const_cast<OCTETSTRING&>(element);
            asnObject.SetDescription(GetOCTETSTRINGStaticDescription());
            AsnSetOf::AddElement(element);
        }

        const OCTETSTRING& ElementAt(int index) const
        {
            return static_cast<const OCTETSTRING&> (AsnSetOf::ElementAt(index));
        }

    };


////////// End Nested Class(es) //////////

    PresentationAddress() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    PresentationAddress(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    PresentationAddress(const PresentationAddress& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PresentationAddress(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetPSelectorStaticDescription();
    static its::AsnDescObject* GetSSelectorStaticDescription();
    static its::AsnDescObject* GetTSelectorStaticDescription();
    static its::AsnDescObject* GetNAddressesStaticDescription();

public:

    virtual ~PresentationAddress()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PresentationAddress(*this);
    }

    virtual std::string GetName() const
    { return "PresentationAddress"; }

    void SetPSelector(PSelector* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPSelectorStaticDescription());
        AddElement(0, element);
    }

    void SetPSelector(const PSelector& element)
    {
        its::AsnObject& asnObject = const_cast<PSelector&>(element);
        asnObject.SetDescription(GetPSelectorStaticDescription());
        AddElement(0, element);
    }

    bool OptionPSelector() const
    {
        return Contains(0);
    }

    const PSelector& GetPSelector() const
    {
        ITS_REQUIRE(OptionPSelector());
        return static_cast<const PSelector&> (ElementAt(0));
    }

    void SetSSelector(SSelector* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSSelectorStaticDescription());
        AddElement(1, element);
    }

    void SetSSelector(const SSelector& element)
    {
        its::AsnObject& asnObject = const_cast<SSelector&>(element);
        asnObject.SetDescription(GetSSelectorStaticDescription());
        AddElement(1, element);
    }

    bool OptionSSelector() const
    {
        return Contains(1);
    }

    const SSelector& GetSSelector() const
    {
        ITS_REQUIRE(OptionSSelector());
        return static_cast<const SSelector&> (ElementAt(1));
    }

    void SetTSelector(TSelector* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTSelectorStaticDescription());
        AddElement(2, element);
    }

    void SetTSelector(const TSelector& element)
    {
        its::AsnObject& asnObject = const_cast<TSelector&>(element);
        asnObject.SetDescription(GetTSelectorStaticDescription());
        AddElement(2, element);
    }

    bool OptionTSelector() const
    {
        return Contains(2);
    }

    const TSelector& GetTSelector() const
    {
        ITS_REQUIRE(OptionTSelector());
        return static_cast<const TSelector&> (ElementAt(2));
    }

    void SetNAddresses(NAddresses* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNAddressesStaticDescription());
        AddElement(3, element);
    }

    void SetNAddresses(const NAddresses& element)
    {
        its::AsnObject& asnObject = const_cast<NAddresses&>(element);
        asnObject.SetDescription(GetNAddressesStaticDescription());
        AddElement(3, element);
    }

    const NAddresses& GetNAddresses() const
    {
        return static_cast<const NAddresses&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_PRESENTATION_ADDRESS_H_)

