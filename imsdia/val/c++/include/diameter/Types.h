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
 * LOG: $Log: Types.h,v $
 * LOG: Revision 3.8.40.1.8.1.2.1  2014/08/26 10:27:38  pramana
 * LOG: Compilation warning fixes in imsdia
 * LOG:
 * LOG: Revision 3.8.40.1.8.1  2014/02/12 07:09:05  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.8.40.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.8  2011/10/14 10:39:55  rajeshak
 * LOG: Removing OSS finding
 * LOG:
 * LOG: Revision 3.7  2010/10/11 05:12:56  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.6  2010/09/20 09:04:26  nvijikumar
 * LOG: Compilation issue fix
 * LOG:
 * LOG: Revision 3.5  2010/09/20 06:32:49  nvijikumar
 * LOG: STLPORT4 support
 * LOG:
 * LOG: Revision 3.4  2009/09/17 14:03:10  rajeshak
 * LOG: Fix for Help desk ticket 2216 (Encoding problem with octestring)
 * LOG: Using length() instead of strlen().
 * LOG:
 * LOG: Revision 3.3  2009/03/19 11:31:24  rajeshak
 * LOG: Provided API to free buffer.
 * LOG:
 * LOG: Revision 3.2  2008/12/11 14:22:45  rajeshak
 * LOG: Replaced stl string with own String class (Hemant,Rajesh)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.9  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.5.2.1  2008/01/24 10:34:11  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 2.5  2007/03/02 06:04:09  nvijikumar
 * LOG: Reverting back the JAVA changes which are committed before Branch tag.
 * LOG:
 * LOG: Revision 2.4  2007/02/26 08:08:28  sumag
 * LOG: t
 * LOG: :q
 * LOG:
 * LOG: Revision 2.3  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:50:43  tpanda
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.8  2006/07/28 11:45:18  kamakshilk
 * LOG: URI::Transport enum change
 * LOG:
 * LOG: Revision 1.7  2006/07/25 13:59:12  brianhu
 * LOG: Fixed bad initializers in URI constructor.
 * LOG:
 * LOG: Revision 1.6  2006/06/21 10:26:35  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.5  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Types.h,v 3.8.40.1.8.1.2.1 2014/08/26 10:27:38 pramana Exp $
 ****************************************************************************/
#ident "$Id: Types.h,v 3.8.40.1.8.1.2.1 2014/08/26 10:27:38 pramana Exp $"

#ifndef _TYPES_H_
#define _TYPES_H_

#include <utility>
#include <list>
#include <strings.h>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string.h>
#include <cstring>

//
// This file defines the basic data types for the API users to "present" AVP values to the Diameter API.
// This types do not have to be bitwise compatible with the implementation's data representation.
//

using namespace std;

namespace diameter {

class UnknownTypeException;

typedef unsigned char Byte;

//class ByteRangeImpl;

typedef std::pair<Byte, Byte> ByteRange;
/*
struct ByteRange: public std::pair<Byte, Byte> {
    ByteRange &operator=(const ByteRangeImpl &impl);
};
*/

typedef unsigned short Short;

//class ShortRangeImpl;

typedef std::pair<Short, Short> ShortRange;
/*
struct ShortRange: public std::pair<Short, Short> {
    ShortRange &operator=(const ShortRangeImpl &impl);
};
*/

enum ValueDiscriminator {
    OctetStringType,
    Integer32Type,
    Integer64Type,
    Unsigned32Type,
    Unsigned64Type,
    Float32Type,
    Float64Type,
    AddressType,
    TimeType,
    URIType,
    UTF8StringType,
    IdentityType,
    IPFilterRuleType,
    //QoSFilterRuleType,
    EnumeratedType,
    GroupedType
};

/**
 * Diameter OctetString
 */
typedef std::string OctetString;

/**
 * Diameter Integer32
 */
typedef int Integer32;

/**
 * Diameter Integer64
 */
typedef long long Integer64;

/**
 * Diameter Unsigned32
 */
typedef unsigned int Unsigned32;

/**
 * Diameter Unsigned64
 */
typedef unsigned long long Unsigned64;

/**
 * Diameter Float32
 */
typedef float Float32;

/**
 * Diameter Float64
 */
typedef double Float64;

class AddressImpl;

/** 
 * Char Array
 */
const std::string sDigits("0123456789ABCDEF");

/**
 * Diameter Address
 */
class Address {
public:
    enum Family {
        RESERVED    = 0,   // Reserved
        IPV4        = 1,   // IP (IP version 4)
        IPV6        = 2,   // IP6 (IP version 6)
        NASP        = 3,   // NSAP
        HDLC        = 4,   // HDLC (8-bit multidrop)
        BBN         = 5,   // 5    BBN 1822
        IEEE_802    = 6,   // 802 (includes all 802 media plus Ethernet "canonical format")
        E163        = 7,   // E.163
        E164        = 8,   // E.164 (SMDS, Frame Relay, ATM)
        F69         = 9,   // F.69 (Telex)
        X121        = 10,  // X.121 (X.25, Frame Relay)
        IPX         = 11,  // IPX
        APPLETALK   = 12,  // Appletalk
        DECIV       = 13,  // Decnet IV
        BANYAN      = 14,  // Banyan Vines
        E164_NSAP   = 15,  // E.164 with NSAP format subaddress
        DNS         = 16,  // DNS (Domain Name System)
        DN          = 17,  // Distinguished Name
        AS          = 18,  // AS Number
        XTP4        = 19,  // XTP over IP version 4
        XTP6        = 20,  // XTP over IP version 6
        XTP         = 21,  // XTP native mode XTP
        FBRCH_PORT  = 22,  // Fibre Channel World-Wide Port Name
        FBRCH_NODE  = 23,  // Fibre Channel World-Wide Node Name
        GWID        = 24   // GWID
    };

    Family family;
    OctetString value;

    /**
     * Constructs an Address to have the given network protocol family and address value.
     */
    Address(Family f, const std::string &v);

    /**
     * Constructs an Address to have the given network protocol family and address value.
     */
    Address(Family f, const char v[], int len) {
        family = f;
        value.assign(v, len);
    }

    /**
     * Constructs an Address from its counterpart in the implementation.
     *
     * This method is to be implemented in the DIP adaptation.
     */
    Address(const AddressImpl &);

    Address &operator=(const AddressImpl &);
    
    Address():family(IPV4){}

    /**
     * converts address in printable format
     *
     */
    const char* getAddress(char* buff)
    {
        *buff='\0';
        if (value.length() > 0)
        {
            switch(family)
            {
                case diameter::Address::IPV4:
                    {
                        buff[0] = value.at(0);
                        int len = value.length();
                        for (int i = 1; i < len; ++i)
                        {
                            buff[i]   = '.';
                            buff[i+1] = value.at(i);
                        }
                        break;
                    }
                case diameter::Address::E164:
                    {
                        int bIdx;
                        bool odd = false;
                        std::string e164 = "";
                        int len = value.length();
                        if (((unsigned char)value[len-1] & 0x0F) == 0x0F)
                            odd = true;
                        for (bIdx = 0; bIdx < len; bIdx++)
                        {
                            e164 += sDigits[((unsigned char)value[bIdx] >> 4)];
                            if (odd && (bIdx == len -1))
                            {
                                break;
                            }
                            e164 += sDigits[((unsigned char)value[bIdx] & 0x0F)];
                        }

                        e164.copy(buff, e164.length());
                        break;
                    }
                default:
                    break;
            }
            return buff;
        }
        return NULL;
    }
};
std::ostream &operator<<(std::ostream &, const Address &);

/**
 * Diameter Time
 */
typedef unsigned int Time;

class URIImpl;

/**
 * Diameter URI
 */
class URI {
public:
    enum Scheme {
        AAA = 0,
        AAAS
    };

    enum Transport {
        TCP = 0,
        SCTP,
        UDP
    };

    enum Protocol {
        DIAMETER = 0,
        RADIUS,
        TACACSPLUS
    };

    std::string fqdn;
    Scheme scheme:2;
    Short port;
    Transport transport:2;
    Protocol protocol:2;

    URI(const std::string &f, Scheme s = AAA, Short p = 3868, Transport trans = TCP, Protocol prot = DIAMETER)
    : fqdn(f), scheme(s), port(p), transport(trans), protocol(prot)
    {}

    URI(const URIImpl &);

    URI &operator=(const URIImpl &);

    URI():scheme(AAA),port(0),transport(TCP),protocol(DIAMETER){}
};
std::ostream &operator<<(std::ostream &, const URI::Transport &);
std::ostream &operator<<(std::ostream &, const URI::Protocol &);
std::ostream &operator<<(std::ostream &, const URI &);


/**
 * Diameter UTF8String
 */
typedef OctetString UTF8String;


/**
 * Diameter Identity
 */
typedef UTF8String Identity;

class IPFilterRuleImpl;

/**
 * Diameter IPFilterRule
 */
class IPFilterRule {
public:
    class SrcDst {
    public:
        /**
         * When representation is EXACT, only ipno is used. When representation
         * is MASK, ipno and bits are used.  For other represntations, both ipno
         * and bits are not used.
         */
        enum Representation {
            EXACT,
            MASK,
            KEYWORD_ANY,
            KEYWORD_ASSIGNED
        };

        bool modifier; /*! Modifier '!' maps to false */
        Representation representation;
        UTF8String ipno;
        Byte bits;
        std::list<ShortRange> portRangeList;   /*! list of port ranges. */

        SrcDst(Representation repr = EXACT, UTF8String ipno = std::string(), Byte bits = 0, bool mod = true)
        : modifier(mod), representation(repr), ipno(ipno), bits(bits)
        {}
    };

    enum Action {
        PERMIT = 0,
        DENY   = 1
    };

    enum Direction {
        IN  = 0,
        OUT = 1
    };

    enum ProtocolConstant {
        ANY_IP_PROTOCOL = 0
    };

    Action action;
    Direction dir;

    /* The value 0 means it matches with any IP protocol */
    Byte proto; 
    SrcDst src, dst;

    // options:
    bool frag; 
    bool setup; 
    bool established; 

    /* IP Options */
    std::list<int> ipOptionList; 

    /* TCP Options */
    std::list<int> tcpOptionList; 

    /* TCP Flags */
    std::list<int> tcpFlagList; 
    std::list<ByteRange> icmpTypeRangeList; 

    /**
     * Constructs an IPFilterRule with default settings.
     */
    IPFilterRule()
    : action(DENY), dir(IN), proto(ANY_IP_PROTOCOL), frag(false), setup(false), established(false) {}

    IPFilterRule(const IPFilterRuleImpl &);

    IPFilterRule &operator=(const IPFilterRuleImpl &);
};
std::ostream &operator<<(std::ostream &, const IPFilterRule::SrcDst &);
std::ostream &operator<<(std::ostream &, const IPFilterRule &);

//QoSFilterRule

/**
 * Diameter Enumerated
 */
typedef int Enumerated;


/**
 * Diameter Grouped
 */
//typedef ? Grouped;


typedef unsigned int CommandCode;

typedef unsigned int ApplicationId;

class String
{
    public:
    
        String()
	{
	    len = 0;
        totalLen = 0;
        __data = NULL;
	}
        String(const char* cs)
	{
	    init(cs);
	}

        String(const string& str)
	{
            init(str.c_str(), str.length());
	}
        String(const String& s)
	{
	    init(s.data(), s.length());
	}
    
    ~String()
    {
    }
        void append(const char* cs)
	{
	    resizeIf(cs);
	}

        void append(const char* cs, int index)
        {
            resizeIf(cs, index);
        }

        void append(const String& s)
	{
	    resizeIf(s.data(), s.length());
	}
        void append(const string& str)
	{
            resizeIf(str.c_str(), str.length());
	}

        int length() const
        {
            return len; 
        }

        void Free()
        {
            if(len > 0)
            { 
                free(__data);
                __data = NULL;
                len = 0;
            }
        }

        const char *c_str()
        {
            return data();
        }

        char& at(int loc)
        {
            if (loc <= totalLen)
                return *(__data + loc);
            //else
                //throw UnknownTypeException(__FILE__, __LINE__,"Location Exceeds capacity");

            //Warning Fix: control reaches end of non-void function
            return *(__data + totalLen);
        }
        //String& operator+=(std::string str); 
    protected:

        void init(const char* cs)
	{
	    len = strlen(cs);
        //Fixing Out-of-bounds access
	    __data = (char*) malloc(len+1);
        memset(__data, 0, len+1);
            memcpy(__data, cs, len);
	    size() = len;
	}

        void init(const char* cs, int length)
        {
            len = length; 
            __data = (char*) malloc(len);
            memcpy(__data, cs, len);
            size() = len;
        }

	bool resizeIf(const char* res)
	{
	    int rLen = strlen(res);
	    if (len + rLen > size())
	    {
	        size() += (resizeValue > rLen ? resizeValue : rLen);
		char* __tmp = (char*) malloc(size());
		memcpy(__tmp, __data, len);
		memcpy(__tmp + len, res, rLen);
                free((char*) __data);
		__data = __tmp;
		len += rLen;
		return true;
	    }
	    memcpy(__data + len, res, rLen);
	    len += rLen;
	    return false;
	}

        bool resizeIf(const char* res, int index)
        {
            //int rLen = strlen(res);
            int rLen = index;
            if (len + rLen > size())
            {
                size() += (resizeValue > rLen ? resizeValue : rLen);
                char* __tmp = (char*) malloc(size());
                memcpy(__tmp, __data, len);
                memcpy(__tmp + len, res, rLen);
                free((char*) __data);
                __data = __tmp;
                len += rLen;
                return true;
            }
            memcpy(__data + len, res, rLen);
            len += rLen;
            return false;
        }

	const char* data() const
	{
	    return __data;
	}
	const char* data() 
	{
	    return __data;
	}

   private:
        int size() const
	{
	    return totalLen;
	}
        int& size()
	{
	    return totalLen;
	}
        static const int resizeValue = 1024;
        char* __data;
	int len;
	int totalLen;

        friend ostream& operator<< (ostream& out, String&); 

};

}

#endif//_TYPES_H_
