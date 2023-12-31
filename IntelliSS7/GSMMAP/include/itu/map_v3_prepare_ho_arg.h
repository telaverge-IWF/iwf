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


#if !defined(_MAP_V3_PREPARE_HO_ARG_H_)
#define _MAP_V3_PREPARE_HO_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnOctetString.h>

#include <map_v3_global_cell_id.h>
#include <map_v3_external_signal_info.h>



namespace map_v3 {



class PrepareHO_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Ho_NumberNotRequired : public its::AsnNull
    {
    public:

        Ho_NumberNotRequired() : its::AsnNull(false)
        {
            Initialize();
        }

        Ho_NumberNotRequired(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Ho_NumberNotRequired(const Ho_NumberNotRequired& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Ho_NumberNotRequired(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Ho_NumberNotRequired()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Ho_NumberNotRequired(*this);
        }

        virtual std::string GetName() const
        { return "Ho_NumberNotRequired"; }

    };


        typedef map_v3::GlobalCellId GlobalCellId;


        typedef map_v3::ExternalSignalInfo ExternalSignalInfo;


////////// End Nested Class(es) //////////

    PrepareHO_Arg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    PrepareHO_Arg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    PrepareHO_Arg(const PrepareHO_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PrepareHO_Arg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetTargetCellIdStaticDescription();
    static its::AsnDescObject* GetHo_NumberNotRequiredStaticDescription();
    static its::AsnDescObject* GetBss_APDUStaticDescription();

public:

    virtual ~PrepareHO_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PrepareHO_Arg(*this);
    }

    virtual std::string GetName() const
    { return "PrepareHO_Arg"; }

    void SetTargetCellId(GlobalCellId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetCellIdStaticDescription());
        AddElement(0, element);
    }

    void SetTargetCellId(const GlobalCellId& element)
    {
        its::AsnObject& asnObject = const_cast<GlobalCellId&>(element);
        asnObject.SetDescription(GetTargetCellIdStaticDescription());
        AddElement(0, element);
    }

    bool OptionTargetCellId() const
    {
        return Contains(0);
    }

    const GlobalCellId& GetTargetCellId() const
    {
        ITS_REQUIRE(OptionTargetCellId());
        return static_cast<const GlobalCellId&> (ElementAt(0));
    }

    void SetHo_NumberNotRequired(Ho_NumberNotRequired* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHo_NumberNotRequiredStaticDescription());
        AddElement(1, element);
    }

    void SetHo_NumberNotRequired(const Ho_NumberNotRequired& element)
    {
        its::AsnObject& asnObject = const_cast<Ho_NumberNotRequired&>(element);
        asnObject.SetDescription(GetHo_NumberNotRequiredStaticDescription());
        AddElement(1, element);
    }

    bool OptionHo_NumberNotRequired() const
    {
        return Contains(1);
    }

    const Ho_NumberNotRequired& GetHo_NumberNotRequired() const
    {
        ITS_REQUIRE(OptionHo_NumberNotRequired());
        return static_cast<const Ho_NumberNotRequired&> (ElementAt(1));
    }

    void SetBss_APDU(ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBss_APDUStaticDescription());
        AddElement(2, element);
    }

    void SetBss_APDU(const ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetBss_APDUStaticDescription());
        AddElement(2, element);
    }

    bool OptionBss_APDU() const
    {
        return Contains(2);
    }

    const ExternalSignalInfo& GetBss_APDU() const
    {
        ITS_REQUIRE(OptionBss_APDU());
        return static_cast<const ExternalSignalInfo&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_PREPARE_HO_ARG_H_)

