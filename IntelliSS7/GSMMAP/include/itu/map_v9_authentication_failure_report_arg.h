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


#if !defined(_MAP_V9_AUTHENTICATION_FAILURE_REPORT_ARG_H_)
#define _MAP_V9_AUTHENTICATION_FAILURE_REPORT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBoolean.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>

#include <map_v9_imsi.h>
#include <map_v9_failure_cause.h>
#include <map_v9_extension_container.h>
#include <map_v9_access_type.h>
#include <map_v9_rand.h>
#include <map_v9_isdn_address_string.h>



namespace map_v9 {



class AuthenticationFailureReportArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Re_attempt : public its::AsnBoolean
    {
    public:

        Re_attempt(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        Re_attempt(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        Re_attempt(const Re_attempt& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        Re_attempt(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        Re_attempt(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~Re_attempt()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Re_attempt(*this);
        }

        virtual std::string GetName() const
        { return "Re_attempt"; }

    };


        typedef map_v9::IMSI IMSI;


        typedef map_v9::FailureCause FailureCause;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::AccessType AccessType;


        typedef map_v9::RAND RAND;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    AuthenticationFailureReportArg() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    AuthenticationFailureReportArg(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    AuthenticationFailureReportArg(const AuthenticationFailureReportArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AuthenticationFailureReportArg(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetFailureCauseStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetRe_attemptStaticDescription();
    static its::AsnDescObject* GetAccessTypeStaticDescription();
    static its::AsnDescObject* GetRandStaticDescription();
    static its::AsnDescObject* GetVlr_NumberStaticDescription();
    static its::AsnDescObject* GetSgsn_NumberStaticDescription();

public:

    virtual ~AuthenticationFailureReportArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AuthenticationFailureReportArg(*this);
    }

    virtual std::string GetName() const
    { return "AuthenticationFailureReportArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetFailureCause(FailureCause* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetFailureCauseStaticDescription());
        AddElement(1, element);
    }

    void SetFailureCause(const FailureCause& element)
    {
        its::AsnObject& asnObject = const_cast<FailureCause&>(element);
        asnObject.SetDescription(GetFailureCauseStaticDescription());
        AddElement(1, element);
    }

    const FailureCause& GetFailureCause() const
    {
        return static_cast<const FailureCause&> (ElementAt(1));
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

    void SetRe_attempt(Re_attempt* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRe_attemptStaticDescription());
        AddElement(3, element);
    }

    void SetRe_attempt(const Re_attempt& element)
    {
        its::AsnObject& asnObject = const_cast<Re_attempt&>(element);
        asnObject.SetDescription(GetRe_attemptStaticDescription());
        AddElement(3, element);
    }

    bool OptionRe_attempt() const
    {
        return Contains(3);
    }

    const Re_attempt& GetRe_attempt() const
    {
        ITS_REQUIRE(OptionRe_attempt());
        return static_cast<const Re_attempt&> (ElementAt(3));
    }

    void SetAccessType(AccessType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAccessTypeStaticDescription());
        AddElement(4, element);
    }

    void SetAccessType(const AccessType& element)
    {
        its::AsnObject& asnObject = const_cast<AccessType&>(element);
        asnObject.SetDescription(GetAccessTypeStaticDescription());
        AddElement(4, element);
    }

    bool OptionAccessType() const
    {
        return Contains(4);
    }

    const AccessType& GetAccessType() const
    {
        ITS_REQUIRE(OptionAccessType());
        return static_cast<const AccessType&> (ElementAt(4));
    }

    void SetRand(RAND* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRandStaticDescription());
        AddElement(5, element);
    }

    void SetRand(const RAND& element)
    {
        its::AsnObject& asnObject = const_cast<RAND&>(element);
        asnObject.SetDescription(GetRandStaticDescription());
        AddElement(5, element);
    }

    bool OptionRand() const
    {
        return Contains(5);
    }

    const RAND& GetRand() const
    {
        ITS_REQUIRE(OptionRand());
        return static_cast<const RAND&> (ElementAt(5));
    }

    void SetVlr_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVlr_NumberStaticDescription());
        AddElement(6, element);
    }

    void SetVlr_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetVlr_NumberStaticDescription());
        AddElement(6, element);
    }

    bool OptionVlr_Number() const
    {
        return Contains(6);
    }

    const ISDN_AddressString& GetVlr_Number() const
    {
        ITS_REQUIRE(OptionVlr_Number());
        return static_cast<const ISDN_AddressString&> (ElementAt(6));
    }

    void SetSgsn_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSgsn_NumberStaticDescription());
        AddElement(7, element);
    }

    void SetSgsn_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetSgsn_NumberStaticDescription());
        AddElement(7, element);
    }

    bool OptionSgsn_Number() const
    {
        return Contains(7);
    }

    const ISDN_AddressString& GetSgsn_Number() const
    {
        ITS_REQUIRE(OptionSgsn_Number());
        return static_cast<const ISDN_AddressString&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_AUTHENTICATION_FAILURE_REPORT_ARG_H_)

