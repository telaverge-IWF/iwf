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


#if !defined(_INAP_CS2_SERVICE_INTERACTION_INDICATORS_TWO_H_)
#define _INAP_CS2_SERVICE_INTERACTION_INDICATORS_TWO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBoolean.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>

#include <inap_cs2_forward_service_interaction_ind.h>
#include <inap_cs2_backward_service_interaction_ind.h>
#include <inap_cs2_bothway_through_connection_ind.h>
#include <inap_cs2_suspend_timer.h>
#include <inap_cs2_connected_number_treatment_ind.h>



namespace inap_cs2 {



class ServiceInteractionIndicatorsTwo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class SuppressCallDiversionNotification : public its::AsnBoolean
    {
    public:

        SuppressCallDiversionNotification(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        SuppressCallDiversionNotification(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        SuppressCallDiversionNotification(const SuppressCallDiversionNotification& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        SuppressCallDiversionNotification(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        SuppressCallDiversionNotification(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~SuppressCallDiversionNotification()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SuppressCallDiversionNotification(*this);
        }

        virtual std::string GetName() const
        { return "SuppressCallDiversionNotification"; }

    };



    class SuppressCallTransferNotification : public its::AsnBoolean
    {
    public:

        SuppressCallTransferNotification(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        SuppressCallTransferNotification(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        SuppressCallTransferNotification(const SuppressCallTransferNotification& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        SuppressCallTransferNotification(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        SuppressCallTransferNotification(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~SuppressCallTransferNotification()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SuppressCallTransferNotification(*this);
        }

        virtual std::string GetName() const
        { return "SuppressCallTransferNotification"; }

    };



    class AllowCdINNoPresentationInd : public its::AsnBoolean
    {
    public:

        AllowCdINNoPresentationInd(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        AllowCdINNoPresentationInd(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        AllowCdINNoPresentationInd(const AllowCdINNoPresentationInd& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        AllowCdINNoPresentationInd(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        AllowCdINNoPresentationInd(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~AllowCdINNoPresentationInd()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new AllowCdINNoPresentationInd(*this);
        }

        virtual std::string GetName() const
        { return "AllowCdINNoPresentationInd"; }

    };



    class UserDialogueDurationInd : public its::AsnBoolean
    {
    public:

        UserDialogueDurationInd(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        UserDialogueDurationInd(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        UserDialogueDurationInd(const UserDialogueDurationInd& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        UserDialogueDurationInd(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        UserDialogueDurationInd(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~UserDialogueDurationInd()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new UserDialogueDurationInd(*this);
        }

        virtual std::string GetName() const
        { return "UserDialogueDurationInd"; }

    };


        typedef inap_cs2::ForwardServiceInteractionInd ForwardServiceInteractionInd;


        typedef inap_cs2::BackwardServiceInteractionInd BackwardServiceInteractionInd;


        typedef inap_cs2::BothwayThroughConnectionInd BothwayThroughConnectionInd;


        typedef inap_cs2::SuspendTimer SuspendTimer;


        typedef inap_cs2::ConnectedNumberTreatmentInd ConnectedNumberTreatmentInd;


////////// End Nested Class(es) //////////

    ServiceInteractionIndicatorsTwo() : its::AsnSequence(9, false)
    {
        Initialize();
    }

    ServiceInteractionIndicatorsTwo(its::Octets& octets) : its::AsnSequence(9, false)
    {
        Initialize();
        Decode(octets);
    }

    ServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ServiceInteractionIndicatorsTwo(its::AsnDescObject* description) : its::AsnSequence(9, description)
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

    static its::AsnDescObject* GetForwardServiceInteractionIndStaticDescription();
    static its::AsnDescObject* GetBackwardServiceInteractionIndStaticDescription();
    static its::AsnDescObject* GetBothwayThroughConnectionIndStaticDescription();
    static its::AsnDescObject* GetSuspendTimerStaticDescription();
    static its::AsnDescObject* GetConnectedNumberTreatmentIndStaticDescription();
    static its::AsnDescObject* GetSuppressCallDiversionNotificationStaticDescription();
    static its::AsnDescObject* GetSuppressCallTransferNotificationStaticDescription();
    static its::AsnDescObject* GetAllowCdINNoPresentationIndStaticDescription();
    static its::AsnDescObject* GetUserDialogueDurationIndStaticDescription();

public:

    virtual ~ServiceInteractionIndicatorsTwo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ServiceInteractionIndicatorsTwo(*this);
    }

    virtual std::string GetName() const
    { return "ServiceInteractionIndicatorsTwo"; }

    void SetForwardServiceInteractionInd(ForwardServiceInteractionInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardServiceInteractionIndStaticDescription());
        AddElement(0, element);
    }

    void SetForwardServiceInteractionInd(const ForwardServiceInteractionInd& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardServiceInteractionInd&>(element);
        asnObject.SetDescription(GetForwardServiceInteractionIndStaticDescription());
        AddElement(0, element);
    }

    bool OptionForwardServiceInteractionInd() const
    {
        return Contains(0);
    }

    const ForwardServiceInteractionInd& GetForwardServiceInteractionInd() const
    {
        ITS_REQUIRE(OptionForwardServiceInteractionInd());
        return static_cast<const ForwardServiceInteractionInd&> (ElementAt(0));
    }

    void SetBackwardServiceInteractionInd(BackwardServiceInteractionInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBackwardServiceInteractionIndStaticDescription());
        AddElement(1, element);
    }

    void SetBackwardServiceInteractionInd(const BackwardServiceInteractionInd& element)
    {
        its::AsnObject& asnObject = const_cast<BackwardServiceInteractionInd&>(element);
        asnObject.SetDescription(GetBackwardServiceInteractionIndStaticDescription());
        AddElement(1, element);
    }

    bool OptionBackwardServiceInteractionInd() const
    {
        return Contains(1);
    }

    const BackwardServiceInteractionInd& GetBackwardServiceInteractionInd() const
    {
        ITS_REQUIRE(OptionBackwardServiceInteractionInd());
        return static_cast<const BackwardServiceInteractionInd&> (ElementAt(1));
    }

    void SetBothwayThroughConnectionInd(BothwayThroughConnectionInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBothwayThroughConnectionIndStaticDescription());
        AddElement(2, element);
    }

    void SetBothwayThroughConnectionInd(const BothwayThroughConnectionInd& element)
    {
        its::AsnObject& asnObject = const_cast<BothwayThroughConnectionInd&>(element);
        asnObject.SetDescription(GetBothwayThroughConnectionIndStaticDescription());
        AddElement(2, element);
    }

    bool OptionBothwayThroughConnectionInd() const
    {
        return Contains(2);
    }

    const BothwayThroughConnectionInd& GetBothwayThroughConnectionInd() const
    {
        ITS_REQUIRE(OptionBothwayThroughConnectionInd());
        return static_cast<const BothwayThroughConnectionInd&> (ElementAt(2));
    }

    void SetSuspendTimer(SuspendTimer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuspendTimerStaticDescription());
        AddElement(3, element);
    }

    void SetSuspendTimer(const SuspendTimer& element)
    {
        its::AsnObject& asnObject = const_cast<SuspendTimer&>(element);
        asnObject.SetDescription(GetSuspendTimerStaticDescription());
        AddElement(3, element);
    }

    bool OptionSuspendTimer() const
    {
        return Contains(3);
    }

    const SuspendTimer& GetSuspendTimer() const
    {
        ITS_REQUIRE(OptionSuspendTimer());
        return static_cast<const SuspendTimer&> (ElementAt(3));
    }

    void SetConnectedNumberTreatmentInd(ConnectedNumberTreatmentInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetConnectedNumberTreatmentIndStaticDescription());
        AddElement(4, element);
    }

    void SetConnectedNumberTreatmentInd(const ConnectedNumberTreatmentInd& element)
    {
        its::AsnObject& asnObject = const_cast<ConnectedNumberTreatmentInd&>(element);
        asnObject.SetDescription(GetConnectedNumberTreatmentIndStaticDescription());
        AddElement(4, element);
    }

    bool OptionConnectedNumberTreatmentInd() const
    {
        return Contains(4);
    }

    const ConnectedNumberTreatmentInd& GetConnectedNumberTreatmentInd() const
    {
        ITS_REQUIRE(OptionConnectedNumberTreatmentInd());
        return static_cast<const ConnectedNumberTreatmentInd&> (ElementAt(4));
    }

    void SetSuppressCallDiversionNotification(SuppressCallDiversionNotification* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppressCallDiversionNotificationStaticDescription());
        AddElement(5, element);
    }

    void SetSuppressCallDiversionNotification(const SuppressCallDiversionNotification& element)
    {
        its::AsnObject& asnObject = const_cast<SuppressCallDiversionNotification&>(element);
        asnObject.SetDescription(GetSuppressCallDiversionNotificationStaticDescription());
        AddElement(5, element);
    }

    bool OptionSuppressCallDiversionNotification() const
    {
        return Contains(5);
    }

    const SuppressCallDiversionNotification& GetSuppressCallDiversionNotification() const
    {
        ITS_REQUIRE(OptionSuppressCallDiversionNotification());
        return static_cast<const SuppressCallDiversionNotification&> (ElementAt(5));
    }

    void SetSuppressCallTransferNotification(SuppressCallTransferNotification* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppressCallTransferNotificationStaticDescription());
        AddElement(6, element);
    }

    void SetSuppressCallTransferNotification(const SuppressCallTransferNotification& element)
    {
        its::AsnObject& asnObject = const_cast<SuppressCallTransferNotification&>(element);
        asnObject.SetDescription(GetSuppressCallTransferNotificationStaticDescription());
        AddElement(6, element);
    }

    bool OptionSuppressCallTransferNotification() const
    {
        return Contains(6);
    }

    const SuppressCallTransferNotification& GetSuppressCallTransferNotification() const
    {
        ITS_REQUIRE(OptionSuppressCallTransferNotification());
        return static_cast<const SuppressCallTransferNotification&> (ElementAt(6));
    }

    void SetAllowCdINNoPresentationInd(AllowCdINNoPresentationInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAllowCdINNoPresentationIndStaticDescription());
        AddElement(7, element);
    }

    void SetAllowCdINNoPresentationInd(const AllowCdINNoPresentationInd& element)
    {
        its::AsnObject& asnObject = const_cast<AllowCdINNoPresentationInd&>(element);
        asnObject.SetDescription(GetAllowCdINNoPresentationIndStaticDescription());
        AddElement(7, element);
    }

    bool OptionAllowCdINNoPresentationInd() const
    {
        return Contains(7);
    }

    const AllowCdINNoPresentationInd& GetAllowCdINNoPresentationInd() const
    {
        ITS_REQUIRE(OptionAllowCdINNoPresentationInd());
        return static_cast<const AllowCdINNoPresentationInd&> (ElementAt(7));
    }

    void SetUserDialogueDurationInd(UserDialogueDurationInd* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUserDialogueDurationIndStaticDescription());
        AddElement(8, element);
    }

    void SetUserDialogueDurationInd(const UserDialogueDurationInd& element)
    {
        its::AsnObject& asnObject = const_cast<UserDialogueDurationInd&>(element);
        asnObject.SetDescription(GetUserDialogueDurationIndStaticDescription());
        AddElement(8, element);
    }

    const UserDialogueDurationInd& GetUserDialogueDurationInd() const
    {
        return static_cast<const UserDialogueDurationInd&> (ElementAt(8));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_SERVICE_INTERACTION_INDICATORS_TWO_H_)

