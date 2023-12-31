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


#if !defined(_MAP_V9_PREPARE_SUBSEQUENT_HO_ARG_H_)
#define _MAP_V9_PREPARE_SUBSEQUENT_HO_ARG_H_

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
#include <AsnInteger.h>

#include <map_v9_global_cell_id.h>
#include <map_v9_isdn_address_string.h>
#include <map_v9_rnc_id.h>
#include <map_v9_access_network_signal_info.h>
#include <map_v9_rab_id.h>
#include <map_v9_extension_container.h>
#include <map_v9_geran_classmark.h>



namespace map_v9 {



class PrepareSubsequentHO_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Rab_ConfigurationIndicator : public its::AsnNull
    {
    public:

        Rab_ConfigurationIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        Rab_ConfigurationIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Rab_ConfigurationIndicator(const Rab_ConfigurationIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Rab_ConfigurationIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Rab_ConfigurationIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Rab_ConfigurationIndicator(*this);
        }

        virtual std::string GetName() const
        { return "Rab_ConfigurationIndicator"; }

    };


        typedef map_v9::GlobalCellId GlobalCellId;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::RNCId RNCId;


        typedef map_v9::AccessNetworkSignalInfo AccessNetworkSignalInfo;


        typedef map_v9::RAB_Id RAB_Id;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::GERAN_Classmark GERAN_Classmark;


////////// End Nested Class(es) //////////

    PrepareSubsequentHO_Arg() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    PrepareSubsequentHO_Arg(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    PrepareSubsequentHO_Arg(const PrepareSubsequentHO_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PrepareSubsequentHO_Arg(its::AsnDescObject* description) : its::AsnSequence(8, description)
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
    static its::AsnDescObject* GetTargetMSC_NumberStaticDescription();
    static its::AsnDescObject* GetTargetRNCIdStaticDescription();
    static its::AsnDescObject* GetAn_APDUStaticDescription();
    static its::AsnDescObject* GetSelectedRab_IdStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetGeran_classmarkStaticDescription();
    static its::AsnDescObject* GetRab_ConfigurationIndicatorStaticDescription();

public:

    virtual ~PrepareSubsequentHO_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PrepareSubsequentHO_Arg(*this);
    }

    virtual std::string GetName() const
    { return "PrepareSubsequentHO_Arg"; }

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

    void SetTargetMSC_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetMSC_NumberStaticDescription());
        AddElement(1, element);
    }

    void SetTargetMSC_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetTargetMSC_NumberStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetTargetMSC_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetTargetRNCId(RNCId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetRNCIdStaticDescription());
        AddElement(2, element);
    }

    void SetTargetRNCId(const RNCId& element)
    {
        its::AsnObject& asnObject = const_cast<RNCId&>(element);
        asnObject.SetDescription(GetTargetRNCIdStaticDescription());
        AddElement(2, element);
    }

    bool OptionTargetRNCId() const
    {
        return Contains(2);
    }

    const RNCId& GetTargetRNCId() const
    {
        ITS_REQUIRE(OptionTargetRNCId());
        return static_cast<const RNCId&> (ElementAt(2));
    }

    void SetAn_APDU(AccessNetworkSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAn_APDUStaticDescription());
        AddElement(3, element);
    }

    void SetAn_APDU(const AccessNetworkSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<AccessNetworkSignalInfo&>(element);
        asnObject.SetDescription(GetAn_APDUStaticDescription());
        AddElement(3, element);
    }

    bool OptionAn_APDU() const
    {
        return Contains(3);
    }

    const AccessNetworkSignalInfo& GetAn_APDU() const
    {
        ITS_REQUIRE(OptionAn_APDU());
        return static_cast<const AccessNetworkSignalInfo&> (ElementAt(3));
    }

    void SetSelectedRab_Id(RAB_Id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSelectedRab_IdStaticDescription());
        AddElement(4, element);
    }

    void SetSelectedRab_Id(const RAB_Id& element)
    {
        its::AsnObject& asnObject = const_cast<RAB_Id&>(element);
        asnObject.SetDescription(GetSelectedRab_IdStaticDescription());
        AddElement(4, element);
    }

    bool OptionSelectedRab_Id() const
    {
        return Contains(4);
    }

    const RAB_Id& GetSelectedRab_Id() const
    {
        ITS_REQUIRE(OptionSelectedRab_Id());
        return static_cast<const RAB_Id&> (ElementAt(4));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(5, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(5, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(5);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(5));
    }

    void SetGeran_classmark(GERAN_Classmark* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGeran_classmarkStaticDescription());
        AddElement(6, element);
    }

    void SetGeran_classmark(const GERAN_Classmark& element)
    {
        its::AsnObject& asnObject = const_cast<GERAN_Classmark&>(element);
        asnObject.SetDescription(GetGeran_classmarkStaticDescription());
        AddElement(6, element);
    }

    bool OptionGeran_classmark() const
    {
        return Contains(6);
    }

    const GERAN_Classmark& GetGeran_classmark() const
    {
        ITS_REQUIRE(OptionGeran_classmark());
        return static_cast<const GERAN_Classmark&> (ElementAt(6));
    }

    void SetRab_ConfigurationIndicator(Rab_ConfigurationIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRab_ConfigurationIndicatorStaticDescription());
        AddElement(7, element);
    }

    void SetRab_ConfigurationIndicator(const Rab_ConfigurationIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<Rab_ConfigurationIndicator&>(element);
        asnObject.SetDescription(GetRab_ConfigurationIndicatorStaticDescription());
        AddElement(7, element);
    }

    bool OptionRab_ConfigurationIndicator() const
    {
        return Contains(7);
    }

    const Rab_ConfigurationIndicator& GetRab_ConfigurationIndicator() const
    {
        ITS_REQUIRE(OptionRab_ConfigurationIndicator());
        return static_cast<const Rab_ConfigurationIndicator&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_PREPARE_SUBSEQUENT_HO_ARG_H_)

