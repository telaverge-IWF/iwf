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


#if !defined(_MAP_V13_IST_ALERT_RES_H_)
#define _MAP_V13_IST_ALERT_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnInteger.h>
#include <AsnEnumerated.h>

#include <map_v13_ist_alert_timer_value.h>
#include <map_v13_call_termination_indicator.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class IST_AlertRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class IstInformationWithdraw : public its::AsnNull
    {
    public:

        IstInformationWithdraw() : its::AsnNull(false)
        {
            Initialize();
        }

        IstInformationWithdraw(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        IstInformationWithdraw(const IstInformationWithdraw& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        IstInformationWithdraw(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~IstInformationWithdraw()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new IstInformationWithdraw(*this);
        }

        virtual std::string GetName() const
        { return "IstInformationWithdraw"; }

    };


        typedef map_v13::IST_AlertTimerValue IST_AlertTimerValue;


        typedef map_v13::CallTerminationIndicator CallTerminationIndicator;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    IST_AlertRes() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    IST_AlertRes(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    IST_AlertRes(const IST_AlertRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    IST_AlertRes(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetIstAlertTimerStaticDescription();
    static its::AsnDescObject* GetIstInformationWithdrawStaticDescription();
    static its::AsnDescObject* GetCallTerminationIndicatorStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~IST_AlertRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new IST_AlertRes(*this);
    }

    virtual std::string GetName() const
    { return "IST_AlertRes"; }

    void SetIstAlertTimer(IST_AlertTimerValue* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIstAlertTimerStaticDescription());
        AddElement(0, element);
    }

    void SetIstAlertTimer(const IST_AlertTimerValue& element)
    {
        its::AsnObject& asnObject = const_cast<IST_AlertTimerValue&>(element);
        asnObject.SetDescription(GetIstAlertTimerStaticDescription());
        AddElement(0, element);
    }

    bool OptionIstAlertTimer() const
    {
        return Contains(0);
    }

    const IST_AlertTimerValue& GetIstAlertTimer() const
    {
        ITS_REQUIRE(OptionIstAlertTimer());
        return static_cast<const IST_AlertTimerValue&> (ElementAt(0));
    }

    void SetIstInformationWithdraw(IstInformationWithdraw* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIstInformationWithdrawStaticDescription());
        AddElement(1, element);
    }

    void SetIstInformationWithdraw(const IstInformationWithdraw& element)
    {
        its::AsnObject& asnObject = const_cast<IstInformationWithdraw&>(element);
        asnObject.SetDescription(GetIstInformationWithdrawStaticDescription());
        AddElement(1, element);
    }

    bool OptionIstInformationWithdraw() const
    {
        return Contains(1);
    }

    const IstInformationWithdraw& GetIstInformationWithdraw() const
    {
        ITS_REQUIRE(OptionIstInformationWithdraw());
        return static_cast<const IstInformationWithdraw&> (ElementAt(1));
    }

    void SetCallTerminationIndicator(CallTerminationIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallTerminationIndicatorStaticDescription());
        AddElement(2, element);
    }

    void SetCallTerminationIndicator(const CallTerminationIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<CallTerminationIndicator&>(element);
        asnObject.SetDescription(GetCallTerminationIndicatorStaticDescription());
        AddElement(2, element);
    }

    bool OptionCallTerminationIndicator() const
    {
        return Contains(2);
    }

    const CallTerminationIndicator& GetCallTerminationIndicator() const
    {
        ITS_REQUIRE(OptionCallTerminationIndicator());
        return static_cast<const CallTerminationIndicator&> (ElementAt(2));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(3);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_IST_ALERT_RES_H_)

