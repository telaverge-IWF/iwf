/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: Implementation.h,v $
 * LOG: Revision 3.2.24.2.26.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.2.24.2  2012/10/03 16:27:35  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.2.24.1  2012/10/01 09:01:07  rsanjay
 * LOG:  opendiameter code removal changes:bugzilla-id 300
 * LOG:
 * LOG: Revision 3.2.30.2  2012/09/20 07:42:01  cprem
 * LOG: Added a new generic AVP access function getAvpCount .
 * LOG:
 * LOG: Revision 3.2.30.1  2012/09/14 15:44:10  cprem
 * LOG: Generic AVP access API is provided in CommandImpl class.
 * LOG:
 * LOG: Revision 3.2  2008/12/11 14:22:45  rajeshak
 * LOG: Replaced stl string with own String class (Hemant,Rajesh)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.7  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.5.4.1  2008/01/24 10:34:11  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 2.5  2007/01/04 10:59:26  nvijikumar
 * LOG: Provoded Accountaing related APIs.
 * LOG:
 * LOG: Revision 2.4  2006/11/13 14:44:53  tpanda
 * LOG: clientId,sessionIndex moved to implementation object
 * LOG:
 * LOG: Revision 2.3  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:50:43  tpanda
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.4  2006/10/05 05:39:58  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 2.3  2006/09/19 06:04:51  tpanda
 * LOG: Val is splitted. Encoding/Decoding functionality moved to vendor
 * LOG:
 * LOG: Revision 2.2  2006/09/13 16:01:04  tpanda
 * LOG: Changes made to make application decoding working
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.6  2006/06/21 10:26:35  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.5  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Implementation.h,v 3.2.24.2.26.1 2013/02/27 08:49:07 jvikram Exp $
 ****************************************************************************/

#ifndef _IMPLEMENTATION_H_
#define _IMPLEMENTATION_H_

#include <diameter/Types.h>

namespace diameter {

class AVP;
class AttributeName;

/**
 * An AbstractValueImpl serves as the base class of all ValueImpl<> classes.
 */
class AVPImpl {
public:
    virtual ~AVPImpl() {}
};

template <typename T, ValueDiscriminator D>
class DerivedAVPImpl: public AVPImpl {
public:
    /**
     * Gets AVP value.
     */
    virtual const T &get() const = 0;

    /**
     * Sets AVP value.
     */
    virtual void set(const T &) = 0;

    /**
     * Acquires a concrete instance of this type.
     */
    static DerivedAVPImpl<T, D> *acquire(const T &);
    /**
     * Acquires a concrete instance of this type.
     */
    static DerivedAVPImpl<T, D> *acquire();
    /**
      *
      */
    virtual ~DerivedAVPImpl(){}
    virtual int Decode(unsigned char*& inputBuff, unsigned int size)
    {return 0;}
    virtual int Encode(String& str, const AttributeName& _name)
    {return 0;}

    /**
     * Releases a concrete instance of this type.
     */
    static void release(DerivedAVPImpl<T, D> *);
};

template <> DerivedAVPImpl<OctetString, OctetStringType> *DerivedAVPImpl<OctetString, OctetStringType>::acquire(const OctetString &);
template <> DerivedAVPImpl<OctetString, OctetStringType> *DerivedAVPImpl<OctetString, OctetStringType>::acquire();
template <> DerivedAVPImpl<Integer32, Integer32Type> *DerivedAVPImpl<Integer32, Integer32Type>::acquire(const Integer32 &);
template <> DerivedAVPImpl<Integer32, Integer32Type> *DerivedAVPImpl<Integer32, Integer32Type>::acquire();
template <> DerivedAVPImpl<Integer64, Integer64Type> *DerivedAVPImpl<Integer64, Integer64Type>::acquire(const Integer64 &);
template <> DerivedAVPImpl<Integer64, Integer64Type> *DerivedAVPImpl<Integer64, Integer64Type>::acquire();
template <> DerivedAVPImpl<Unsigned32, Unsigned32Type> *DerivedAVPImpl<Unsigned32, Unsigned32Type>::acquire(const Unsigned32 &);
template <> DerivedAVPImpl<Unsigned32, Unsigned32Type> *DerivedAVPImpl<Unsigned32, Unsigned32Type>::acquire();
template <> DerivedAVPImpl<Unsigned64, Unsigned64Type> *DerivedAVPImpl<Unsigned64, Unsigned64Type>::acquire(const Unsigned64 &);
template <> DerivedAVPImpl<Unsigned64, Unsigned64Type> *DerivedAVPImpl<Unsigned64, Unsigned64Type>::acquire();

/**
 * Added declaration of acquire for Float32 and Float64 types
 */
template <> DerivedAVPImpl<Float32, Float32Type> *DerivedAVPImpl<Float32, Float32Type>::acquire(const Float32 &);
template <> DerivedAVPImpl<Float32, Float32Type> *DerivedAVPImpl<Float32, Float32Type>::acquire();

template <> DerivedAVPImpl<Float64, Float64Type> *DerivedAVPImpl<Float64, Float64Type>::acquire(const Float64 &);
template <> DerivedAVPImpl<Float64, Float64Type> *DerivedAVPImpl<Float64, Float64Type>::acquire();

template <> DerivedAVPImpl<Address, AddressType> *DerivedAVPImpl<Address, AddressType>::acquire(const Address &);
template <> DerivedAVPImpl<Address, AddressType> *DerivedAVPImpl<Address, AddressType>::acquire();
template <> DerivedAVPImpl<Time, TimeType> *DerivedAVPImpl<Time, TimeType>::acquire(const Time &);
template <> DerivedAVPImpl<Time, TimeType> *DerivedAVPImpl<Time, TimeType>::acquire();
template <> DerivedAVPImpl<UTF8String, UTF8StringType> *DerivedAVPImpl<UTF8String, UTF8StringType>::acquire(const UTF8String &);
template <> DerivedAVPImpl<UTF8String, UTF8StringType> *DerivedAVPImpl<UTF8String, UTF8StringType>::acquire();
template <> DerivedAVPImpl<Identity, IdentityType> *DerivedAVPImpl<Identity, IdentityType>::acquire(const Identity &);
template <> DerivedAVPImpl<Identity, IdentityType> *DerivedAVPImpl<Identity, IdentityType>::acquire();
template <> DerivedAVPImpl<URI, URIType> *DerivedAVPImpl<URI, URIType>::acquire(const URI &);
template <> DerivedAVPImpl<URI, URIType> *DerivedAVPImpl<URI, URIType>::acquire();
template <> DerivedAVPImpl<IPFilterRule, IPFilterRuleType> *DerivedAVPImpl<IPFilterRule, IPFilterRuleType>::acquire(const IPFilterRule &);
template <> DerivedAVPImpl<IPFilterRule, IPFilterRuleType> *DerivedAVPImpl<IPFilterRule, IPFilterRuleType>::acquire();
template <> DerivedAVPImpl<Enumerated, EnumeratedType> *DerivedAVPImpl<Enumerated, EnumeratedType>::acquire(const Enumerated &);
template <> DerivedAVPImpl<Enumerated, EnumeratedType> *DerivedAVPImpl<Enumerated, EnumeratedType>::acquire();

template <typename T, ValueDiscriminator D> void DerivedAVPImpl<T, D>::release(DerivedAVPImpl<T, D> *impl) {
#ifdef DEBUG
#ifdef DEBUG_VAL
std::cout << "DerivedAVPImpl<T, D>::release: deleting DerivedAVPImpl<T, D> @ 0x" << std::hex << (unsigned long)impl << std::dec << std::endl;
#endif
#endif
    delete impl;
}

/**
  *Forward declaration of CommandAttribute
  */
class CommandAttribute;
struct Dia_Flags
{
   unsigned char r:1;
   unsigned char p:1;
   unsigned char e:1;
   unsigned char t:1;
   unsigned char rsvd:4;
};

typedef struct
{
   unsigned char ver;
   unsigned int length;
   struct Dia_Flags flags;
   unsigned int code;
   unsigned int appId;
   unsigned int hh;
   unsigned int ee;
}DiaHeader;

class AVPContainer;

/**
 * Implementation of GroupedAVP
 */
class GroupedAVPImpl: public AVPImpl {
public:
    virtual ~GroupedAVPImpl() {}

    virtual const AVPContainer &getContainer() const = 0;

    virtual AVPContainer &getContainer() = 0;

    /**
     * Acquires a concrete instance of this type.
     */
    static GroupedAVPImpl *acquire();

    /**
     * Releases a concrete instance of this type.
     */
    static void release(GroupedAVPImpl *);

    /**
     * Acquires a concrete instance of this type.
     */
    static GroupedAVPImpl *acquire(const AttributeName* nameObj);
    /**
     * Validate
     */
    virtual bool validate() const{return true;}
    /**
      *print
      */
    virtual std::ostream &print(std::ostream &out) const
    { return out;}
    virtual int Decode(unsigned char*& inputBuff, unsigned int size, DiaHeader& hdr)
    {return 0;}
    virtual int Encode(String& str)
    {return 0;}
    virtual GroupedAVPImpl* createCopy() const=0;
};


/**
 * Implementation of Command
 */
class CommandImpl {
public:
    virtual ~CommandImpl() {}

    virtual bool isRequest() const = 0;

    virtual bool isProxyable() const = 0;

    virtual bool isError() const = 0;

    virtual bool isRetransmit() const = 0;

    virtual const char *getCommandName() const = 0;

    virtual CommandCode getCommandCode() const = 0;

    virtual ApplicationId getApplicationId() const = 0;

    virtual const AVPContainer &getContainer() const = 0;

    virtual AVPContainer &getContainer() = 0;
    virtual int encode(unsigned char *&, int&) = 0;
    static CommandImpl *decode(const unsigned char *, int, const CommandAttribute*);
    virtual void validateApp(const CommandAttribute* descObj=NULL){}
    virtual void SetCmdAttribute(const CommandAttribute* descObj){}
    virtual DiaHeader& getHeader()=0;
    virtual CommandImpl* createCopy() const=0;
    //following API is for stack,
    virtual unsigned int& getClientId()=0;
    //following API is for stack,
    virtual unsigned int& getSessionIndex()=0;

   // following API is for stack Accounting SM 
    virtual bool& IsStorageSpaceAvailable()=0;
    virtual bool& IsLastRecordInStorage()=0;

    //Fixing - Missing return statement
	//Following is the generic AVP Access API.
	virtual int getAvpValue(unsigned int avpCode, unsigned int index ,void* val, 
                   ValueDiscriminator D, unsigned int venId=0) const { return 0;};

	virtual int getAvpCount(unsigned int avpCode, unsigned int venId=0) { return
0;};

    static CommandImpl *acquire(bool request, bool proxyable, bool error, bool retrans, CommandCode code, ApplicationId appId);

    static void release(CommandImpl *);
};

}

#endif//_IMPLEMENTATION_H_
