/********************************-*-CPP-*-***********************************
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
 * LOG: $Log: Types.cpp,v $
 * LOG: Revision 3.3.20.2.12.1.2.1  2014/07/15 06:53:37  jsarvesh
 * LOG: Changes done for encoding E164 format of Address Class
 * LOG:
 * LOG: Revision 3.3.20.2.12.1  2014/02/12 07:10:09  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.3.20.2  2012/11/26 05:28:10  mallikarjun
 * LOG: Bug-515-Changes
 * LOG:
 * LOG: Revision 3.3.20.1  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.3  2009/03/03 11:12:54  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.2  2008/12/11 14:23:46  rajeshak
 * LOG: Replaced stl string with own String class (Hemant,Rajesh)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.8  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.4.2.2  2007/05/21 10:10:05  hbhatnagar
 * LOG: type casted the pair to int in operator<< function for proper printing.
 * LOG:
 * LOG: Revision 2.4.2.1  2007/05/21 10:04:20  hbhatnagar
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.4  2007/03/02 06:04:09  nvijikumar
 * LOG: Reverting back the JAVA changes which are committed before Branch tag.
 * LOG:
 * LOG: Revision 2.3  2007/02/26 08:08:28  sumag
 * LOG: t
 * LOG: :q
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:53:10  kamakshilk
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.8  2006/08/25 02:25:07  brianhu
 * LOG: Prevent buffer overrun in commmand encode; Improved IPFilterRule.toString()
 * LOG:
 * LOG: Revision 1.7  2006/06/21 10:22:24  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.6  2006/06/21 10:12:32  kamakshilk
 * LOG: included copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Types.cpp,v 3.3.20.2.12.1.2.1 2014/07/15 06:53:37 jsarvesh Exp $
 ****************************************************************************/
#ident "$Id: Types.cpp,v 3.3.20.2.12.1.2.1 2014/07/15 06:53:37 jsarvesh Exp $"

#include <diameter/Types.h>
#include <list>
#include <cstdlib>
#include <arpa/inet.h>

namespace diameter {

template <typename T>
static std::ostream &operator<<(std::ostream &out, const std::list<T> &list) {
    for (typename std::list<T>::const_iterator it = list.begin(); it != list.end(); ++it) {
        out << *it << ',';
    }
    return out;
}

template <typename T1, typename T2>
static std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &range) {
    /**
     * type casted the pair to int for printing
     */
    return out << '(' << (int) range.first << "-" << (int) range.second << ')';
}

/////////////
// Address //
/////////////

Address::Address(Address::Family f, const std::string &v) {
    char buffer[INET6_ADDRSTRLEN];
    int domain, len, ret;

    if( !v.empty())
    {
        family = f;
        switch(f) {
            case Address::E164 :
                {
                    value.assign(v.begin(), v.end());
                }
                break;
            case Address::IPV4 :
                {
                    domain = AF_INET;
                    len = sizeof(struct in_addr); // should be 4
                }
                break;
            case Address::IPV6 :
                {
                    domain = AF_INET6;
                    len = sizeof(struct in6_addr); // shoud be 16
                }
                break;
            default :
                {
                    throw "Unknown Address format";
                }
                break;
        }
        if(f == Address::IPV4 || f == Address::IPV6)
        {
            ret = inet_pton(domain, v.c_str(), buffer);
            if (ret <= 0)
            {
                throw "IP Presentation to Network conversion failed";
            }

            value.assign(buffer, len);
        }
    }
    else
    {
        throw "IP Address is Empty";
    }
}

std::ostream &operator<<(std::ostream &out, const Address &address) {
    int domain = 0;

    out << "address<";
    switch (address.family) {
    case Address::IPV4:
        out << "IPV4";
        domain = AF_INET;
        break;
    case Address::IPV6:
        out << "IPV6";
        domain = AF_INET6;
        break;
    case Address::NASP:
        out << "NASP";
        break;
    case Address::HDLC:
        out << "NASP";
        break;
    case Address::BBN:
        out << "BBN";
        break;
    case Address::IEEE_802:
        out << "IEEE_802";
        break;
    case Address::E163:
        out << "E163";
        break;
    case Address::E164:
        out << "E164";
        break;
    case Address::F69:
        out << "F69";
        break;
    case Address::X121:
        out << "X121";
        break;
    case Address::IPX:
        out << "IPX";
        break;
    case Address::APPLETALK:
        out << "APPLETALK";
        break;
    case Address::DECIV:
        out << "DECIV";
        break;
    case Address::BANYAN:
        out << "BANYAN";
        break;
    case Address::E164_NSAP:
        out << "E164_NSAP";
        break;
    case Address::DNS:
        out << "DNS";
        break;
    case Address::DN:
        out << "DN";
        break;
    case Address::AS:
        out << "AS";
        break;
    case Address::XTP4:
        out << "XTP4";
        break;
    case Address::XTP6:
        out << "XTP6";
        break;
    case Address::XTP:
        out << "XTP";
        break;
    case Address::FBRCH_PORT:
        out << "FBRCH_PORT";
        break;
    case Address::FBRCH_NODE:
        out << "FBRCH_NODE";
        break;
    case Address::GWID:
        out << "GWID";
        break;
    default:
        out << "(unknown)";
        break;
    }

    if (domain == AF_INET || domain == AF_INET6)
    {
        char buffer[INET6_ADDRSTRLEN] = {0};
        inet_ntop(domain, address.value.c_str(), buffer, INET6_ADDRSTRLEN);
        out << "-" << buffer << ">";
    }

    return out;

}

std::ostream &operator<<(std::ostream &out, const IPFilterRule::SrcDst &srcdst) {
    out << (srcdst.modifier ? ' ' : '!')
        << "representation:";
    switch (srcdst.representation) {
    case IPFilterRule::SrcDst::EXACT:
        out << "EXACT";
        break;
    case IPFilterRule::SrcDst::MASK:
        out << "MASK";
        break;
    case IPFilterRule::SrcDst::KEYWORD_ANY:
        out << "KEYWORD-ANY";
        break;
    case IPFilterRule::SrcDst::KEYWORD_ASSIGNED:
        out << "KEYWORD-ASSIGNED";
        break;
    }
    out << ";ip:" << srcdst.ipno
        << ";bits:0x" << std::hex << (int)srcdst.bits << std::dec
        << ";port-range-list:<" << srcdst.portRangeList << '>';
    return out;
}

/////////
// URI //
/////////

std::ostream &operator<<(std::ostream &out, const URI::Scheme &scheme) {
    switch (scheme) {
    case URI::AAA:
        return out << "aaa";
    case URI::AAAS:
        return out << "aaas";
    default:
        return out;
    }
}

std::ostream &operator<<(std::ostream &out, const URI::Transport &trans) {
    switch (trans) {
    case URI::SCTP:
        return out << "sctp";
    case URI::TCP:
        return out << "tcp";
    case URI::UDP:
        return out << "udp";
    default:
        return out << "(unknown)";
    }
}

std::ostream &operator<<(std::ostream &out, const URI::Protocol &prot) {
    switch (prot) {
    case URI::DIAMETER:
        return out << "diameter";
    case URI::RADIUS:
        return out << "radius";
    case URI::TACACSPLUS:
        return out << "tacacs+";
    default:
        return out;
    }
}

std::ostream &operator<<(std::ostream &out, const URI &uri) {
    return out << uri.scheme << "://" << uri.fqdn << ':' << uri.port << ";transport=" << uri.transport << ";protocol=" << uri.protocol;
}

std::ostream &operator<<(std::ostream &out, const IPFilterRule &rule) {
    out << (rule.action == IPFilterRule::PERMIT ? "permit" : "deny") << ' '
        << (rule.dir == IPFilterRule::IN ? "in" : "out") << ' '
        << "protocol=" << (int)rule.proto
        << ";src:" << rule.src
        << ";dst:" << rule.dst
        << ";fragment?" << rule.frag
        << ";ip-options:" << rule.ipOptionList
        << ";tcp-options:" << rule.tcpOptionList
        << ";established?" << rule.established
        << ";setup?" << rule.setup
        << ";tcp-flags:" << rule.tcpFlagList
        << ";icmp-type-ranges:" << rule.icmpTypeRangeList;
    return out;
}

ostream& operator<< (ostream& out, String& s)
{
    out << s.data();
    return out;
}

String& operator+= (String& str1,std::string  str)
{
  str1.append(str);
  return str1;
}


}
