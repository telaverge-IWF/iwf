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


#if !defined(_MAP_V9_PROVIDE_SUBSCRIBER_LOCATION_RES_H_)
#define _MAP_V9_PROVIDE_SUBSCRIBER_LOCATION_RES_H_

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
#include <AsnChoice.h>
#include <AsnEnumerated.h>

#include <map_v9_ext_geographical_information.h>
#include <map_v9_age_of_location_information.h>
#include <map_v9_extension_container.h>
#include <map_v9_add_geographical_information.h>
#include <map_v9_positioning_data_information.h>
#include <map_v9_utran_positioning_data_info.h>
#include <map_v9_cell_global_id_or_service_area_id_or_lai.h>
#include <map_v9_accuracy_fulfilment_indicator.h>



namespace map_v9 {



class ProvideSubscriberLocation_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Deferredmt_lrResponseIndicator : public its::AsnNull
    {
    public:

        Deferredmt_lrResponseIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        Deferredmt_lrResponseIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Deferredmt_lrResponseIndicator(const Deferredmt_lrResponseIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Deferredmt_lrResponseIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Deferredmt_lrResponseIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Deferredmt_lrResponseIndicator(*this);
        }

        virtual std::string GetName() const
        { return "Deferredmt_lrResponseIndicator"; }

    };



    class Sai_Present : public its::AsnNull
    {
    public:

        Sai_Present() : its::AsnNull(false)
        {
            Initialize();
        }

        Sai_Present(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Sai_Present(const Sai_Present& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Sai_Present(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Sai_Present()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Sai_Present(*this);
        }

        virtual std::string GetName() const
        { return "Sai_Present"; }

    };


        typedef map_v9::Ext_GeographicalInformation Ext_GeographicalInformation;


        typedef map_v9::AgeOfLocationInformation AgeOfLocationInformation;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::Add_GeographicalInformation Add_GeographicalInformation;


        typedef map_v9::PositioningDataInformation PositioningDataInformation;


        typedef map_v9::UtranPositioningDataInfo UtranPositioningDataInfo;


        typedef map_v9::CellGlobalIdOrServiceAreaIdOrLAI CellGlobalIdOrServiceAreaIdOrLAI;


        typedef map_v9::AccuracyFulfilmentIndicator AccuracyFulfilmentIndicator;


////////// End Nested Class(es) //////////

    ProvideSubscriberLocation_Res() : its::AsnSequence(10, false)
    {
        Initialize();
    }

    ProvideSubscriberLocation_Res(its::Octets& octets) : its::AsnSequence(10, false)
    {
        Initialize();
        Decode(octets);
    }

    ProvideSubscriberLocation_Res(const ProvideSubscriberLocation_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProvideSubscriberLocation_Res(its::AsnDescObject* description) : its::AsnSequence(10, description)
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

    static its::AsnDescObject* GetLocationEstimateStaticDescription();
    static its::AsnDescObject* GetAgeOfLocationEstimateStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetAdd_LocationEstimateStaticDescription();
    static its::AsnDescObject* GetDeferredmt_lrResponseIndicatorStaticDescription();
    static its::AsnDescObject* GetGeranPositioningDataStaticDescription();
    static its::AsnDescObject* GetUtranPositioningDataStaticDescription();
    static its::AsnDescObject* GetCellIdOrSaiStaticDescription();
    static its::AsnDescObject* GetSai_PresentStaticDescription();
    static its::AsnDescObject* GetAccuracyFulfilmentIndicatorStaticDescription();

public:

    virtual ~ProvideSubscriberLocation_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProvideSubscriberLocation_Res(*this);
    }

    virtual std::string GetName() const
    { return "ProvideSubscriberLocation_Res"; }

    void SetLocationEstimate(Ext_GeographicalInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationEstimateStaticDescription());
        AddElement(0, element);
    }

    void SetLocationEstimate(const Ext_GeographicalInformation& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_GeographicalInformation&>(element);
        asnObject.SetDescription(GetLocationEstimateStaticDescription());
        AddElement(0, element);
    }

    const Ext_GeographicalInformation& GetLocationEstimate() const
    {
        return static_cast<const Ext_GeographicalInformation&> (ElementAt(0));
    }

    void SetAgeOfLocationEstimate(AgeOfLocationInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAgeOfLocationEstimateStaticDescription());
        AddElement(1, element);
    }

    void SetAgeOfLocationEstimate(const AgeOfLocationInformation& element)
    {
        its::AsnObject& asnObject = const_cast<AgeOfLocationInformation&>(element);
        asnObject.SetDescription(GetAgeOfLocationEstimateStaticDescription());
        AddElement(1, element);
    }

    bool OptionAgeOfLocationEstimate() const
    {
        return Contains(1);
    }

    const AgeOfLocationInformation& GetAgeOfLocationEstimate() const
    {
        ITS_REQUIRE(OptionAgeOfLocationEstimate());
        return static_cast<const AgeOfLocationInformation&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

    void SetAdd_LocationEstimate(Add_GeographicalInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdd_LocationEstimateStaticDescription());
        AddElement(3, element);
    }

    void SetAdd_LocationEstimate(const Add_GeographicalInformation& element)
    {
        its::AsnObject& asnObject = const_cast<Add_GeographicalInformation&>(element);
        asnObject.SetDescription(GetAdd_LocationEstimateStaticDescription());
        AddElement(3, element);
    }

    bool OptionAdd_LocationEstimate() const
    {
        return Contains(3);
    }

    const Add_GeographicalInformation& GetAdd_LocationEstimate() const
    {
        ITS_REQUIRE(OptionAdd_LocationEstimate());
        return static_cast<const Add_GeographicalInformation&> (ElementAt(3));
    }

    void SetDeferredmt_lrResponseIndicator(Deferredmt_lrResponseIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDeferredmt_lrResponseIndicatorStaticDescription());
        AddElement(4, element);
    }

    void SetDeferredmt_lrResponseIndicator(const Deferredmt_lrResponseIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<Deferredmt_lrResponseIndicator&>(element);
        asnObject.SetDescription(GetDeferredmt_lrResponseIndicatorStaticDescription());
        AddElement(4, element);
    }

    bool OptionDeferredmt_lrResponseIndicator() const
    {
        return Contains(4);
    }

    const Deferredmt_lrResponseIndicator& GetDeferredmt_lrResponseIndicator() const
    {
        ITS_REQUIRE(OptionDeferredmt_lrResponseIndicator());
        return static_cast<const Deferredmt_lrResponseIndicator&> (ElementAt(4));
    }

    void SetGeranPositioningData(PositioningDataInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGeranPositioningDataStaticDescription());
        AddElement(5, element);
    }

    void SetGeranPositioningData(const PositioningDataInformation& element)
    {
        its::AsnObject& asnObject = const_cast<PositioningDataInformation&>(element);
        asnObject.SetDescription(GetGeranPositioningDataStaticDescription());
        AddElement(5, element);
    }

    bool OptionGeranPositioningData() const
    {
        return Contains(5);
    }

    const PositioningDataInformation& GetGeranPositioningData() const
    {
        ITS_REQUIRE(OptionGeranPositioningData());
        return static_cast<const PositioningDataInformation&> (ElementAt(5));
    }

    void SetUtranPositioningData(UtranPositioningDataInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUtranPositioningDataStaticDescription());
        AddElement(6, element);
    }

    void SetUtranPositioningData(const UtranPositioningDataInfo& element)
    {
        its::AsnObject& asnObject = const_cast<UtranPositioningDataInfo&>(element);
        asnObject.SetDescription(GetUtranPositioningDataStaticDescription());
        AddElement(6, element);
    }

    bool OptionUtranPositioningData() const
    {
        return Contains(6);
    }

    const UtranPositioningDataInfo& GetUtranPositioningData() const
    {
        ITS_REQUIRE(OptionUtranPositioningData());
        return static_cast<const UtranPositioningDataInfo&> (ElementAt(6));
    }

    void SetCellIdOrSai(CellGlobalIdOrServiceAreaIdOrLAI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCellIdOrSaiStaticDescription());
        AddElement(7, element);
    }

    void SetCellIdOrSai(const CellGlobalIdOrServiceAreaIdOrLAI& element)
    {
        its::AsnObject& asnObject = const_cast<CellGlobalIdOrServiceAreaIdOrLAI&>(element);
        asnObject.SetDescription(GetCellIdOrSaiStaticDescription());
        AddElement(7, element);
    }

    bool OptionCellIdOrSai() const
    {
        return Contains(7);
    }

    const CellGlobalIdOrServiceAreaIdOrLAI& GetCellIdOrSai() const
    {
        ITS_REQUIRE(OptionCellIdOrSai());
        return static_cast<const CellGlobalIdOrServiceAreaIdOrLAI&> (ElementAt(7));
    }

    void SetSai_Present(Sai_Present* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSai_PresentStaticDescription());
        AddElement(8, element);
    }

    void SetSai_Present(const Sai_Present& element)
    {
        its::AsnObject& asnObject = const_cast<Sai_Present&>(element);
        asnObject.SetDescription(GetSai_PresentStaticDescription());
        AddElement(8, element);
    }

    bool OptionSai_Present() const
    {
        return Contains(8);
    }

    const Sai_Present& GetSai_Present() const
    {
        ITS_REQUIRE(OptionSai_Present());
        return static_cast<const Sai_Present&> (ElementAt(8));
    }

    void SetAccuracyFulfilmentIndicator(AccuracyFulfilmentIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAccuracyFulfilmentIndicatorStaticDescription());
        AddElement(9, element);
    }

    void SetAccuracyFulfilmentIndicator(const AccuracyFulfilmentIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<AccuracyFulfilmentIndicator&>(element);
        asnObject.SetDescription(GetAccuracyFulfilmentIndicatorStaticDescription());
        AddElement(9, element);
    }

    bool OptionAccuracyFulfilmentIndicator() const
    {
        return Contains(9);
    }

    const AccuracyFulfilmentIndicator& GetAccuracyFulfilmentIndicator() const
    {
        ITS_REQUIRE(OptionAccuracyFulfilmentIndicator());
        return static_cast<const AccuracyFulfilmentIndicator&> (ElementAt(9));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_PROVIDE_SUBSCRIBER_LOCATION_RES_H_)

