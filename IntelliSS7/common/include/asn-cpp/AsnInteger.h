///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: AsnInteger.h,v $
// LOG: Revision 9.2  2007/01/10 11:15:05  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.2  2005/10/06 12:13:52  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
// LOG:
// LOG: Revision 9.1.10.1  2005/09/06 09:15:59  mmanikandan
// LOG: Support for ASN.1 PER.
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:53  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:57  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.6  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.5  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:23:28  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:03:21  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnInteger class definition.
//

#if !defined(_ASN_INTEGER_H_)
#define _ASN_INTEGER_H_

#ident "$Id: AsnInteger.h,v 9.2 2007/01/10 11:15:05 yranade Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <Tag.h>
#include <Length.h>
#include <AsnObject.h>
#include <AsnDescInteger.h>

namespace its {

class AsnInteger : public AsnObject
{
public: 

    AsnInteger(long value, bool initialize = true)
    :   _value(value), _signedInt(true)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnInteger(
        Octets& octets,
        const AsnOptions& asnOptions = AsnOptions(),
        bool initialize = true)
    :   _value(0), _signedInt(true) 
    {
        if (initialize)
        {
            Initialize();
        }

        Decode(octets, asnOptions);
    }

    AsnInteger(bool initialize = true)
    :   _value(0), _signedInt(true)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnInteger(const AsnInteger& rhs)
    :   AsnObject(rhs)
    {
        _value = rhs._value;
    }

    AsnInteger(AsnDescObject* description)
    :   _value(0), _signedInt(true) 
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    AsnInteger(AsnDescObject* description, long value)
    :   _value(value), _signedInt(true)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

protected:

    void 
    Initialize()
    {
        ITS_ASSERT(_description == NULL);
        _description = GetStaticDescription();
    }

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~AsnInteger()
    {
        // Nothing to do.
    }

    AsnInteger& 
    operator=(const AsnInteger& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            Assign(rhs);
            _value = rhs._value;
            return *this;
        }
    }

    bool 
    operator==(const AsnInteger& rhs) const
    { 
        return Equals(rhs); 
    }

    long 
    GetValue() const
    { 
        return _value; 
    }

    void 
    SetValue(long value)
    { 
        _value = value; 
    }

    const AsnDescInteger& 
    GetDescription() const
    {
        return *static_cast<AsnDescInteger*>(_description);
    }

    void 
    SetDescription(AsnDescInteger* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    static Tag* 
    GetUniversalTag()
    {
        return new Tag(
            Tag::ASN_CLASS_UNIVERSAL,
            Tag::ASN_PRIMITIVE,
            Tag::ASN_INTEGER);
    }

    virtual AsnObject* 
    Clone() const
    { 
        return new AsnInteger(*this); 
    }

    virtual bool Equals(const AsnObject& rhs) const;

    virtual std::string 
    GetName() const
    { 
        return "INTEGER"; 
    }

    virtual std::string 
    GetBaseName() const
    { 
        return "INTEGER"; 
    }

    virtual void Print(std::ostream& os, size_t level = 0) const;

    void
    SetUInteger()
    {
       _signedInt=false;
    }
    
    bool
    IfSigned()
    {
        return _signedInt;
    }

public: // Pseudo-protected.

    virtual Octets* InternalEncodeBer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodeBer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual int EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description);

    virtual int DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description);

    virtual Characters* InternalEncodeToXml(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodeFromXml(
                            Characters& characters,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

protected:

    void EncodeCheck(const AsnOptions& asnOptions);
    void DecodeCheck(Octets& octets, const AsnOptions& asnOptions);
    void DecodeCheck(Characters& characters, const AsnOptions& asnOptions);

    long _value;
    bool _signedInt;
};

} // namespace its.

#endif // !defined(_ASN_INTEGER_H_)
