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
 * LOG: $Log: itsdiameter.cpp,v $
 * LOG: Revision 3.27.2.1.2.6.6.4.4.1  2013/07/31 07:32:20  vsarath
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 3.27.2.1.2.6.6.4  2013/04/18 07:04:31  jvikram
 * LOG: Included changes relatd to log segregation.
 * LOG:
 * LOG: Revision 3.27.2.1.2.6.6.3  2013/04/04 09:30:20  mallikarjun
 * LOG: MemLeak Fixes
 * LOG:
 * LOG: Revision 3.27.2.1.2.6.6.2  2013/04/04 09:06:11  mallikarjun
 * LOG: MemLeak Fixes Bug 1205 1298
 * LOG:
 * LOG: Revision 3.27.2.1.2.6.6.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.27.2.1.2.6  2012/11/20 17:39:45  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.27.2.1.2.2.12.2  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.27.2.1.2.2  2012/10/03 15:08:43  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.27.2.1.2.1.2.2  2012/09/20 08:18:47  cprem
 * LOG: Added Generic AVP Access and getAvpCount implementation.
 * LOG:
 * LOG: Revision 3.27.2.1.2.1.2.1  2012/09/14 15:48:33  cprem
 * LOG: Added generic AVP access API implementation in CommandImplDerived with
 * LOG: support for fetching multiple occurance AVP's.
 * LOG:
 * LOG: Revision 3.27.2.1.2.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.27.2.2  2012/07/13 11:15:40  ncshivakumar
 * LOG: Modification for Core dump for invalid avp length
 * LOG:
 * LOG: Revision 3.27.2.1  2012/02/15 09:38:13  brajappa
 * LOG: Resolved linked error in gcc O2 option - template functions should be in header files
 * LOG:
 * LOG: Revision 3.27  2011/08/23 06:49:23  vkumara
 * LOG: New API DataToUApp included.
 * LOG:
 * LOG: Revision 3.26  2011/08/23 04:12:18  vkumara
 * LOG: DataToInt is being changed to DataToUInt.
 * LOG: To fix CmdCode decode error for an unsigned values from abnf.
 * LOG: (Extra FF was returning from existing DataToInt ()).
 * LOG:
 * LOG: Revision 3.25  2010/12/02 14:48:07  nvijikumar
 * LOG: Fix for IpFilterRule AVP parsing Issue reported by Motorola PSIG
 * LOG:
 * LOG: Revision 3.24  2010/11/19 16:59:36  nvijikumar
 * LOG: Introduced containsExtra API with index parameter
 * LOG:
 * LOG: Revision 3.23  2010/09/22 05:29:23  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.22  2010/08/19 11:21:27  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.21.2.5  2010/07/15 09:34:20  rajeshak
 * LOG: Fix for HelpDesk Ticket-2399
 * LOG:
 * LOG: Revision 3.21.2.4  2010/06/17 14:50:28  rajeshak
 * LOG: More changes to Multiple Avp Occurrence
 * LOG:
 * LOG: Revision 3.21.2.3  2010/06/17 14:46:10  rajeshak
 * LOG: More changes to Multiple Avp Occurrence
 * LOG:
 * LOG: Revision 3.21.2.2  2010/06/17 04:58:05  rajeshak
 * LOG: Fix for HelpDesk Ticket-2383
 * LOG:
 * LOG: Revision 3.21.2.1  2010/04/26 06:23:29  rajeshak
 * LOG: 1. Porting IP Check changes from 4.2.1
 * LOG: 2. Setting sessionId, OH and OR before throwing exception.
 * LOG:
 * LOG: Revision 3.21  2009/12/19 08:45:59  sureshj
 * LOG: constant values for OH,OR and SessID changes to defined values.
 * LOG:
 * LOG: Revision 3.20  2009/12/19 08:29:27  sureshj
 * LOG: CodecExceptionToApp to provide sessionId, OriginHost, Origin-Realm
 * LOG: to application when missing AVP exception is thrown.
 * LOG:
 * LOG: Revision 3.19  2009/12/08 06:39:41  sureshj
 * LOG: Missing AVP only provides print of offending AVP, but no callback
 * LOG: to application. Motorola ticket 2278.
 * LOG:
 * LOG: Revision 3.18  2009/09/07 10:29:51  rajeshak
 * LOG: Support for Printing Missing Avp
 * LOG:
 * LOG: Revision 3.17  2009/07/24 09:22:18  rajeshak
 * LOG: Changes done for IDC-IDS Heartbeat with Custom AVP in DWR.
 * LOG:
 * LOG: Revision 3.16  2009/07/14 04:17:53  nvijikumar
 * LOG: Modified UTF8Checker Class
 * LOG:
 * LOG: Revision 3.15  2009/03/20 05:46:02  ssaxena
 * LOG: Remove the debug print.
 * LOG:
 * LOG: Revision 3.14  2009/03/19 16:22:15  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 3.13  2009/03/19 13:28:43  sureshj
 * LOG: DIA_VERSION assigned
 * LOG:
 * LOG: Revision 3.12  2009/03/03 11:17:20  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.11  2009/02/19 09:32:22  nvijikumar
 * LOG: 1. Keeping BaseCommand::_enBuf reference as input buffer of the constructor
 * LOG: 2. Provided to API to Set ptr for deletion of encoded buffer
 * LOG:
 * LOG: Revision 3.10  2009/02/03 10:21:11  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.9  2009/01/07 13:09:24  nvijikumar
 * LOG: Removed unwanted printf statement
 * LOG:
 * LOG: Revision 3.8  2009/01/06 10:34:25  nvijikumar
 * LOG: 1. Fix for issue 1374 (Multiple vendorIds add fails)
 * LOG: 2. Introduced seperate funcs to decode Grouped AVPs in BaseCommand
 * LOG:
 * LOG: Revision 3.7  2009/01/03 06:02:23  rajeshak
 * LOG: Fix for 1419 (DCCA issue fix)
 * LOG: Fix for KLOCK Work reported issues
 * LOG:
 * LOG: Revision 3.6  2008/12/18 10:28:59  rajeshak
 * LOG: Made ptype variable (ParserBase*) local to encode and decode function.
 * LOG: Fix for core dump issue in static setup.
 * LOG:
 * LOG: Revision 3.5  2008/12/12 18:30:48  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.3  2008/10/28 12:06:28  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.2.2.1  2008/10/12 11:47:52  nvijikumar
 * LOG: Added code to throw the exceptions at appropriate places. Also fixed the
 * LOG: freeze problem ( infinite loop) problem reported by Bridgewater.
 * LOG:
 * LOG: Revision 3.2  2008/03/31 13:17:13  hbhatnagar
 * LOG: Made changes for ticket 1850 raised by Bridgewater
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.49  2008/03/27 12:14:09  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.31.2.12  2008/01/24 10:37:45  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 1.31.2.11  2007/08/13 09:22:42  hbhatnagar
 * LOG: fix for memory leak in addAVP() APIs.
 * LOG:
 * LOG: Revision 1.31.2.10  2007/05/30 13:54:05  nvijikumar
 * LOG: Modified CodecException to maintain the Error Codes.
 * LOG:
 * LOG: Revision 1.31.2.9  2007/05/18 10:09:45  hbhatnagar
 * LOG: fix for the fqdn in diameter URI Decode.
 * LOG:
 * LOG: Revision 1.31.2.8  2007/04/19 14:12:50  hbhatnagar
 * LOG: Enhancement: Provided API to add and remove AVPs.
 * LOG:
 * LOG: Revision 1.31.2.7  2007/04/11 08:46:40  nvijikumar
 * LOG: Fix crash in getExtra. Check if entry is valid else throw exception.
 * LOG:
 * LOG: Revision 1.31.2.6  2007/04/09 06:48:18  nvijikumar
 * LOG: Fix for Encoding issue for Unsigned64 AVP, Bridgewater reported.
 * LOG:
 * LOG: Revision 1.31.2.5  2007/03/26 12:46:19  nvijikumar
 * LOG: Fix for Bridgewater issue reported on 26th March 07.
 * LOG: AVP Decode failure with OctetString value is empty.
 * LOG:
 * LOG: Revision 1.31.2.4  2007/03/22 10:25:46  tpanda
 * LOG: Minor fix for return values in the Payload class
 * LOG:
 * LOG: Revision 1.31.2.3  2007/03/22 09:18:58  tpanda
 * LOG: Few more changes related to previous commit for extraAttributes
 * LOG:
 * LOG: Revision 1.31.2.2  2007/03/22 08:41:40  tpanda
 * LOG: ExtraAttributes creation based on avpCode and vendorId together
 * LOG:
 * LOG: Revision 1.31.2.1  2007/03/22 07:38:15  nvijikumar
 * LOG: Provided customized AVP(PayloadAvp) for Bridgewater MS-VSA avp issue (Tushar).
 * LOG:
 * LOG: Revision 1.31  2007/02/19 05:20:32  kamakshilk
 * LOG: IPFilterRule encode enhanced
 * LOG:
 * LOG: Revision 1.30  2007/02/01 16:15:42  tpanda
 * LOG: minor corrections to previous fix for BridgeWater
 * LOG:
 * LOG: Revision 1.29  2007/02/01 11:01:41  tpanda
 * LOG: Fix for IPFileterrule decoding (bridgewater issue)
 * LOG:
 * LOG: Revision 1.28  2007/01/04 11:04:42  nvijikumar
 * LOG: Provided Accounting related APIs for ACR.
 * LOG:
 * LOG: Revision 1.27  2006/12/13 12:54:30  tpanda
 * LOG: Fix for server crashing if any app.message received
 * LOG:
 * LOG: Revision 1.26  2006/12/12 16:12:18  tpanda
 * LOG: Minor changes to the previous commit related to IDS
 * LOG:
 * LOG: Revision 1.25  2006/12/12 15:23:16  tpanda
 * LOG: Fix for IDS-crashing if receives peer messages having ext.AVPs
 * LOG:
 * LOG: Revision 1.24  2006/12/04 19:40:35  tpanda
 * LOG: Fix for IDS-crash while sending request with extensible AVPs
 * LOG:
 * LOG: Revision 1.23  2006/11/29 20:24:36  tpanda
 * LOG: appId ,cmdcode removed for extensible AVP addition
 * LOG:
 * LOG: Revision 1.22  2006/11/29 12:04:29  nvijikumar
 * LOG: Fix for addition of Extensible AVP in any order
 * LOG:
 * LOG: Revision 1.21  2006/11/25 03:57:20  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 1.20  2006/11/23 12:13:14  tpanda
 * LOG: Minor fix for dcca related to previous commit for replacing multiple hash defines
 * LOG:
 * LOG: Revision 1.19  2006/11/23 06:31:07  tpanda
 * LOG: getAvpValue api provided for dcca to work properly with no header file dependancy
 * LOG:
 * LOG: Revision 1.18  2006/11/14 02:16:37  tpanda
 * LOG: clientId and sessionIndex also be there in the copy contruct
 * LOG:
 * LOG: Revision 1.17  2006/11/13 14:47:22  tpanda
 * LOG: clientId,sessionIndex moved to implementation object
 * LOG:
 * LOG: Revision 1.16  2006/11/13 05:37:10  tpanda
 * LOG: dictionary extensible AVP encoding/decoding fix
 * LOG:
 * LOG: Revision 1.15  2006/10/30 05:29:56  tpanda
 * LOG: IPFilter rule implementation done
 * LOG:
 * LOG: Revision 1.14  2006/10/27 16:42:25  tpanda
 * LOG: IpFilterrule encoding implemented
 * LOG:
 * LOG: Revision 1.13  2006/10/25 13:25:31  tpanda
 * LOG: For extensible AVP support
 * LOG:
 * LOG: Revision 1.12  2006/10/24 09:01:53  tpanda
 * LOG: Dictionary file related changes
 * LOG:
 * LOG: Revision 1.11  2006/10/17 17:02:24  tpanda
 * LOG: Fix to enable GenericCmd to work with IDS
 * LOG:
 * LOG: Revision 1.10  2006/10/17 05:28:09  tpanda
 * LOG: Fix for Vendor-Specific-App Id crash with no common appId
 * LOG:
 * LOG: Revision 1.9  2006/10/16 11:25:13  tpanda
 * LOG: Desc.Obj checking not mandatory for Gen.Cmd
 * LOG:
 * LOG: Revision 1.8  2006/10/15 22:17:47  tpanda
 * LOG: Fix for crash with new API
 * LOG:
 * LOG: Revision 1.7  2006/10/05 06:06:37  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 1.6  2006/10/03 07:08:11  tpanda
 * LOG: Log feature was missing when commited initially
 * LOG:
 ****************************************************************************/

#include <map>
#include <itsdiameter.h>
#include <dia_defines.h>
#include <dia_trace.h>
#include <dia_cmn.h>
#include <dia_utils.h>
#include <its_dia_config.h>


namespace diameter
{
int Integer32Parser::Decode(const unsigned char* buff, int size, void* val)
{
   unsigned int& intVal = *((unsigned int*)val);
   intVal =  DataToApp((unsigned char*)buff);
   return 0;
}

int Integer32Parser::Encode(String& str, void* val)
{
   unsigned int& intVal = *((unsigned int*)val);
   char temp[4];
   AppToData(temp, intVal);
   str.append(temp, 4);
   return 0;
}

int Integer64Parser::Decode(const unsigned char* buff, int size, void* val)
{
   unsigned long long& intVal = *((unsigned long long*)val);
   intVal =  DataToApp((unsigned char*)buff);
   return 0;
}

int Integer64Parser::Encode(String& str, void* val)
{
   unsigned long long& longlongVal = *((unsigned long long*)val);
   char temp[8];
   AppToData(temp, longlongVal);
   str.append(temp, 8);
   return 0;
}

/**
 * Added definition of Float32Parser's Decode
 */
int
Float32Parser::Decode(const unsigned char* buff, int size, void* val)
{
    float& floatVal = *((float*)val);

    float temp = 0;
    char* p = (char*) &floatVal;
    for (int i = 0; i < 4; i++)
    {
        p[i] = buff[4-i-1] & 0xFFU;
    }
    return 0;
}

/**
 * Added definition of Float32Parser's Encode
 */
int
Float32Parser::Encode(String& str, void* val)
{
    float& floatVal = *((float*)val);
    char temp[4];
    char *p = (char*) &floatVal;
    for(int i=0; i< 4; ++i)
    {
        temp[i] = p[4-i-1]  & 0xFFU;
    }
    str.append(temp, 4);
    return 0;
}

/**
 * Added definition of Float64Parser's Decode
 */
int
Float64Parser::Decode(const unsigned char* buff, int size, void* val)
{
    double& doubleVal = *((double*)val);
    char* p = (char*) &doubleVal;
    for (int i = 0; i < 8; i++)
    {
        p[i] = buff[8-i-1] & 0xFFU;
    }
    return 0;
}

/**
 * Added definition of Float64Parser's Encode
 */
int
Float64Parser::Encode(String& str, void* val)
{
    double& doubleVal = *((double*)val);
    char temp[8];
    char *p = (char*) &doubleVal;
    for(int i=0; i< 8; ++i)
    {
        temp[i] = p[8-i-1]  & 0xFFU;
    }
    str.append(temp, 8);
    return 0;
}

int AddressParser::Decode(const unsigned char* inputBuff, int size, void* val)
{
   Address& addr = *((Address*)val);
   unsigned char* buff = (unsigned char*)inputBuff;
   Address::Family f = (Address::Family)DataToApp(buff);
   Address adr(f, (char*)(buff+2), size-2);
   addr =  adr;
   return 0;
}
int AddressParser::Encode(String& str, void* val)
{
   Address& addr = *((Address*)val);
   char temp[2];
   AppToData(temp, addr.family);
   str.append(temp, 2);
   str.append(addr.value);
   return 0;
}

int 
OctetStringParser::Decode(const unsigned char* buff, int size, void* val)
{
   std::string &str = *((std::string*)val);
   str.assign((char*)buff, size);

   return 0;
}

int
OctetStringParser::Encode(String& str, void* val)
{
   std::string &instr = *((std::string*)val);
   str.append(instr);
   return 0;
}

int
URIParser::Encode(String& str, void* val)
{
   URI &uri = *((URI*)val);
   if(uri.scheme == URI::AAA)
   {
      str.append("aaa://");
   }
   else
   {
      str.append("aaas://");
   }
   str.append(uri.fqdn);
   char temp[8]="";
   sprintf(temp, ":%hd;", uri.port);
   str.append(temp);//port
   switch(uri.transport)
   {
      case URI::TCP:
           str.append("transport=tcp;");
           break;
      case URI::UDP:
           str.append("transport=udp;");
           break;
      default:
           str.append("transport=sctp;");
   }
   switch(uri.protocol)
   {
      case URI::TACACSPLUS:
           str.append("protocol=tacacs+");
           break;
      case URI::RADIUS    :
           str.append("protocol=radius");
           break;
      default:
           str.append("protocol=diameter");
   }
   return 0;
}

int
URIParser::Decode(const unsigned char* inputBuff, int size, void* val)
{
   char* buff = (char*)inputBuff;
   URI &uri = *((URI*)val);
   uri.scheme = URI::AAA;
   if(memcmp(buff, "aaas", 4) == 0)
   {
      uri.scheme = URI::AAAS;
      buff = buff+7;
      size-=7;
   }
   else
   {
      buff = buff + 6;
      size-=6;
   }
   std::string str;
   str.assign(buff, size);
   /* char* buffStr = strchr(str.c_str(), ':') */
   char* buffStr = strchr(buff, ':');
   if(buffStr)
   {
      *buffStr='\0';
      uri.fqdn.assign(buff, strlen(buff));
      buff = buffStr+1;
      buffStr = strchr(buff, ';');
      if(buffStr)
      {
        *buffStr='\0';
        uri.port=atoi(buff);
        buff = buffStr+1;
      }
   }
   if(strstr(str.c_str(), "transport=tcp"))
   {
      uri.transport = URI::TCP;
   }
   else if(strstr(str.c_str(), "transport=udp"))
   {
      uri.transport = URI::UDP;
   }
   else
   {
      uri.transport = URI::SCTP;
   }
   if(strstr(str.c_str(), "protocol=tacacs+"))
   {
      uri.protocol = URI::TACACSPLUS;
   }
   else if(strstr(str.c_str(), "protocol=radius"))
   {
      uri.protocol = URI::RADIUS;
   }
   else
   {
      uri.protocol = URI::DIAMETER;
   }
   return 0;
}

int
UTF8StringParser::Decode(const unsigned char* inputBuff, int size, void* val)
{
   UTF8Validate chk;
   char* buff = (char*)inputBuff;
   if(chk.Validate(buff, size) == 0)
   {
      std::string& str = *((std::string*)val);
      str.assign(buff, size);
   }
   return 0;
}

int
UTF8StringParser::Encode(String& str, void* val)
{
   std::string& strBuff = *((std::string*)val);
   UTF8Validate chk;
   if(chk.Validate(strBuff.c_str(), strBuff.length())==0)
   {
      str.append(strBuff);
   }
   return 0;
}

int
IPFilterRuleParser::Encode(String& str, void* val)
{
   IPFilterRule &ipfltrl = *((IPFilterRule*)val); 
   if (ipfltrl.action == IPFilterRule::PERMIT)
   {
      str.append("permit ");
   }
   else
   {
      str.append("deny ");
   }
   if (ipfltrl.dir == IPFilterRule::IN)
   {
      str.append("in ");
   }
   else
   {
      str.append("out ");
   }
   if (ipfltrl.proto == IPFilterRule::ANY_IP_PROTOCOL)
   {
      str.append("ip ");
   }
   /* Max. possible value is 255 by protocol field*/
   else if(ipfltrl.proto < 999)
   {
      char protoStr[5];
      memset(protoStr, 0, sizeof(protoStr));
      snprintf(protoStr,5, "%d ", ipfltrl.proto);
      str.append(protoStr);
   }
   else
   {
      return -1;
   }
   for(int i =0; i < 2; ++i)
   {
      IPFilterRule::SrcDst* srcdst = NULL;
      if (i == 0)
      {
         srcdst = &ipfltrl.src;
         str.append("from ");
      }
      else
      {
         srcdst = &ipfltrl.dst;
         str.append("to ");
      }
      if (srcdst->modifier == false)
      {
         str.append("!");
      }
      if (srcdst->representation == IPFilterRule::SrcDst::KEYWORD_ANY)
      {
         str.append("any ");
      }
      else if (srcdst->representation
               == IPFilterRule::SrcDst::KEYWORD_ASSIGNED)
      {
         str.append("assigned ");
      }
      else 
      {
         str.append(srcdst->ipno);
         if (srcdst->representation == IPFilterRule::SrcDst::MASK)
         {
           char bitsStr[5];
           memset(bitsStr, 0, sizeof(bitsStr));
           snprintf(bitsStr, 5, "/%u", srcdst->bits);
           str.append(bitsStr);
         }
         str.append(" ");
      }
      for (std::list<ShortRange>::iterator i
          =srcdst->portRangeList.begin();
          i!=srcdst->portRangeList.end();)
      {
         char portStr[12];
         memset(portStr, 0, sizeof(portStr));
         if ((*i).first == (*i).second)
         {
            snprintf(portStr, 12, "%u", (*i).first);
            str.append(portStr);
         }
         else
         {
            snprintf(portStr, 12, "%u-%u", (*i).first, (*i).second);
            str.append(portStr);
         }
         if (++i != srcdst->portRangeList.end())
         {
            str.append(",");
         }
         else
         {
            str.append(" ");
         }
       }
   }
   if (ipfltrl.frag)
   {
      str.append(" frag");
   }
   if (ipfltrl.ipOptionList.size()>0)
   {
      str.append(" ipoptions");
   }
   for (std::list<int>::iterator i=ipfltrl.ipOptionList.begin();
        i!=ipfltrl.ipOptionList.end();)
   {
      bool negation=false;
      int opt = *i;
      if (opt < 0)
      {
         negation=true;
         opt = -opt;
      }
      if (negation)
         str.append("!");
      if (opt == 1)
         str.append("ssrr");
      else if (opt == 2)
         str.append("lsrr");
      else if (opt == 3)
         str.append("rr");
      else if (opt == 4)
         str.append("ts");
      if (++i != ipfltrl.ipOptionList.end())
         str.append(",");
   }

   if (ipfltrl.tcpOptionList.size()>0)
        str.append(" tcpoptions ");

   for (std::list<int>::iterator i=ipfltrl.tcpOptionList.begin();
           i!=ipfltrl.tcpOptionList.end();)
   {
      bool negation=false;
      int opt = *i;
      if (opt < 0)
      {
         negation=true;
         opt = -opt;
      }
      if (negation)
         str.append("!");
      if (opt == 1)
         str.append("mss");
      else if (opt == 2)
         str.append("window");
      else if (opt == 3)
         str.append("sack");
      else if (opt == 4)
         str.append("ts");
      else if (opt == 5)
         str.append("cc");
      if (++i != ipfltrl.tcpOptionList.end())
            str.append(",");
   }

   if (ipfltrl.established)
     str.append(" established");

   if (ipfltrl.setup)
     str.append(" setup");

   if (ipfltrl.tcpFlagList.size()>0)
     str.append(" tcpflags");

   for (std::list<int>::iterator i=ipfltrl.tcpFlagList.begin();
           i!=ipfltrl.tcpFlagList.end();)
   {
      bool negation=false;
      int opt = *i;
      if (opt < 0)
      {
         negation=true;
         opt = -opt;
      }
      if (negation)
         str.append("!");
      if (opt == 1)
         str.append("fin");
      else if (opt == 2)
         str.append("syn");
      else if (opt == 3)
         str.append("rst");
      else if (opt == 4)
         str.append("psh");
      else if (opt == 5)
         str.append("ack");
      else if (opt == 6)
         str.append("urg");
      if (++i != ipfltrl.tcpFlagList.end())
         str.append(",");
   }
   if (ipfltrl.icmpTypeRangeList.size()>0)
      str.append(" icmptypes");

   for (std::list<ByteRange>::iterator i=ipfltrl.icmpTypeRangeList.begin();
        i!=ipfltrl.icmpTypeRangeList.end();)
   {
      char typeStr[8];
      memset(typeStr, 0, sizeof(typeStr));
      if ((*i).first == (*i).second)
         snprintf(typeStr, 8, "%u", (*i).first);
      else
         snprintf(typeStr, 8, "%u-%u", (*i).first, (*i).second);
      str.append(typeStr);
      if (++i != ipfltrl.icmpTypeRangeList.end())
         str.append(",");
   }

   return 0;
}

int
IPFilterRuleParser::Decode(const unsigned char* inputBuff, int size, void* val)
{
   char* buff = (char*)inputBuff;
   char* end  = (char*)(inputBuff+size);
   char* ch = NULL;
   IPFilterRule &ipfltrl = *((IPFilterRule*)val);
   ipfltrl.action = IPFilterRule::DENY;
   if(memcmp(buff, "permit", 6) == 0)
   {
      ipfltrl.action = IPFilterRule::PERMIT;
      buff = buff+7;
      size-=7;
   }
   else
   {
      buff = buff+5;
      size -=5;
   }

   if(memcmp(buff, "in", 2) == 0)
   {
      ipfltrl.dir = IPFilterRule::IN;
      buff = buff+3;
      size-=3;
   }
   else if(memcmp(buff, "out", 3) == 0)
   {
      ipfltrl.dir = IPFilterRule::OUT;
      buff = buff+4;
      size-=4;
   }
   else
   {
      return -1;
   }

   if(memcmp(buff, "ip", 2) == 0)
   {
      ipfltrl.proto = IPFilterRule::ANY_IP_PROTOCOL;
      buff = buff+3;
      size-=3;
   }
   else
   {
      if ((ch = strchr(buff,' ')) &&
         ((unsigned long)ch < (unsigned long)end) &&
         ((ch - buff) <= 3))
      {
         *ch = 0;
          ipfltrl.proto = atoi(buff);
          buff = ch + 1;
      }
      else
      {
          return -1;
      }
   }

   IPFilterRule::SrcDst* srcdst=NULL;
   for(int i =0; i<2; ++i)
   {
      if(memcmp(buff, "from", 4) == 0)
      {
         srcdst = &ipfltrl.src;
         buff = buff+5;
         size-=5;
      }

      if (srcdst == NULL)
      {
          return -1;
      }
      srcdst->modifier = true;
      srcdst->representation = IPFilterRule::SrcDst::EXACT;
      if (memcmp(buff, "!", 1) == 0)
      {
         srcdst->modifier = false;
         buff = buff+1;
         size-=1;
      }
      if (memcmp(buff, "any", 3) == 0)
      {
         srcdst->representation = IPFilterRule::SrcDst::KEYWORD_ANY;
         buff = buff+4;
         size-=4;
      }
      else if (memcmp(buff, "assigned", 8) == 0)
      {
         srcdst->representation = IPFilterRule::SrcDst::KEYWORD_ASSIGNED;
         buff = buff+9;
         size-=9;
      }
      else
      {
         ch = strchr(buff,'/');
         if (ch && ((unsigned long)ch < (unsigned long)end))
         {
            srcdst->representation = IPFilterRule::SrcDst::MASK;
            *ch = 0; 
            srcdst->ipno.append(buff);
            buff = ch + 1;
            srcdst->bits = atoi(buff);
            //buff +=4;
            if ((ch = strchr(buff,' ')) &&
            ((unsigned long)ch < (unsigned long)end))
            {
                *ch = 0;
                buff = ch + 1;
            }
         }
         else if ((ch = strchr(buff,' ')) &&
         ((unsigned long)ch < (unsigned long)end))
         {
            *ch = 0;
            srcdst->ipno.append(buff);
            buff = ch + 1;
         }
         else
         {
            return -1;
         }
      }
      do
        {
           unsigned int port1, port2;
           if (sscanf(buff, "%u-%u", &port1, &port2) == 2)
           {
              char temp[12];
              srcdst->portRangeList.push_back(ShortRange(port1,port2));
              snprintf(temp, 12, "%u-%u",port1, port2);
              buff +=strlen(temp);
              
           }
           else if (sscanf(buff, "%u", &port1) == 1)
           {
              char temp[6];
              srcdst->portRangeList.push_back(ShortRange(port1,port1));
              snprintf(temp, 6, "%u",port1);
              buff +=strlen(temp);
           }
           if (buff[0] == ',' || buff[0] == ' ')
           {
              buff++;
              if (memcmp(buff, "to", strlen("to")) == 0)
              {
                 srcdst = &ipfltrl.dst;
                 buff = buff+3;
                 size-=3;
                 break;
              }
              continue;
           }
           if (memcmp(buff, "frag", strlen("frag")) == 0)
           {
              buff = buff + strlen("frag"); 
           }
           if (memcmp(buff, "ipoptions", strlen("ipoptions")) == 0)
           {
              buff = buff + strlen("ipoptions"); 
              break;
           }
           else
           {
              //error
              return -1;
           }
        }while(true && ((unsigned long) buff < (unsigned long)end)); 
   }
   while ((unsigned long) buff < (unsigned long)end)
   {
     bool negation = false;
     int value;
     if (buff[0] == '!')
     {
        negation = true;
        buff ++;
     }
     if (memcmp(buff,"ssrr", 4) == 0)
     {
        value = (negation ? -1 : 1);
        ipfltrl.ipOptionList.push_back(value);
        buff +=4;
     }
     else if (memcmp(buff,"lsrr", 4) == 0)
     {
        value = (negation ? -2 : 2);
        ipfltrl.ipOptionList.push_back(value);
        buff +=4;
     }
     else if (memcmp(buff,"rr", 2) == 0)
     {
        value = (negation ? -3 : 3);
        ipfltrl.ipOptionList.push_back(value);
        buff +=2;
     }
     else if (memcmp(buff,"ts", 2) == 0)
     {
        value = (negation ? -4 : 4);
        ipfltrl.ipOptionList.push_back(value);
        buff +=2;
     }
     if (buff[0] == ',' || buff[0] == ' ')
     {
        buff++;
        continue;
     }
     else if (memcmp(buff, "tcpoptions", strlen("tcpoptions")) == 0)
     {
        buff = buff + strlen("tcpoptions"); 
        break;
     }
     else
     {
        return -1;
     }
   }
   ipfltrl.established = false;
   ipfltrl.setup = false;
   while (((unsigned long) buff < (unsigned long)end))
   {
     bool negation = false;
     int value;
     if (buff[0] == '!')
     {
        negation = true;
        buff ++;
     }
     if (memcmp(buff,"mss", 3) == 0)
     {
        value = (negation ? -1 : 1);
        ipfltrl.tcpOptionList.push_back(value);
        buff +=3;
     }
     else if (memcmp(buff,"window", 6) == 0)
     {
        value = (negation ? -2 : 2);
        ipfltrl.tcpOptionList.push_back(value);
        buff +=6;
     }
     else if (memcmp(buff,"sack", 4) == 0)
     {
        value = (negation ? -3 : 3);
        ipfltrl.tcpOptionList.push_back(value);
        buff +=4;
     }
     else if (memcmp(buff,"ts", 2) == 0)
     {
        value = (negation ? -4 : 4);
        ipfltrl.tcpOptionList.push_back(value);
        buff +=2;
     }
     else if (memcmp(buff,"cc", 2) == 0)
     {
        value = (negation ? -5 : 5);
        ipfltrl.tcpOptionList.push_back(value);
        buff +=2;
     }
     if (buff[0] == ',' || buff[0] == ' ')
     {
        buff++;
        continue;
     }
     if (memcmp(buff, "established", strlen("established")) == 0)
     {
        ipfltrl.established = true;
        buff +=strlen("established");
     }
     if (memcmp(buff, "setup", strlen("setup")) == 0)
     {
        ipfltrl.established = true;
        buff +=strlen("setup");
     }
     if (memcmp(buff, "tcpflags", strlen("tcpflags")) == 0)
     {
        buff = buff + strlen("tcpflags"); 
        break;
     }
     else
     {
        return -1;
     }
   }
   while (((unsigned long) buff < (unsigned long)end))
   {
     bool negation = false;
     int value;
     if (buff[0] == '!')
     {
        negation = true;
        buff ++;
     }
     if (memcmp(buff,"fin", 3) == 0)
     {
        value = (negation ? -1 : 1);
        ipfltrl.tcpFlagList.push_back(value);
        buff +=3;
     }
     else if (memcmp(buff,"syn", 3) == 0)
     {
        value = (negation ? -2 : 2);
        ipfltrl.tcpFlagList.push_back(value);
        buff +=3;
     }
     else if (memcmp(buff,"rst", 3) == 0)
     {
        value = (negation ? -3 : 3);
        ipfltrl.tcpFlagList.push_back(value);
        buff +=3;
     }
     else if (memcmp(buff,"psh", 3) == 0)
     {
        value = (negation ? -4 : 4);
        ipfltrl.tcpFlagList.push_back(value);
        buff +=3;
     }
     else if (memcmp(buff,"ack", 3) == 0)
     {
        value = (negation ? -5 : 5);
        ipfltrl.tcpFlagList.push_back(value);
        buff +=3;
     }
     else if (memcmp(buff,"urg", 3) == 0)
     {
        value = (negation ? -6 : 6);
        ipfltrl.tcpFlagList.push_back(value);
        buff +=3;
     }
     if (buff[0] == ',' || buff[0] == ' ')
     {
        buff++;
        continue;
     }
     if (memcmp(buff, "icmptypes", strlen("icmptypes")) == 0)
     {
        buff = buff + strlen("icmptypes"); 
        break;
     }
     else
     {
        return -1;
     }
   }
   if (((unsigned long) buff < (unsigned long)end))
   {
      do
        {
           unsigned int rt1, rt2;
           if (sscanf(buff, "%u-%u", &rt1, &rt2) == 2)
           {
              char temp[8];
              ipfltrl.icmpTypeRangeList.push_back(ByteRange(rt1,rt2));
              snprintf(temp, 8, "%u-%u",rt1, rt2);
              buff +=strlen(temp);
           }
           else if (sscanf(buff, "%u", &rt1) == 1)
           {
              char temp[4];
              ipfltrl.icmpTypeRangeList.push_back(ByteRange(rt1,rt1));
              snprintf(temp, 4, "%u",rt1);
              buff +=strlen(temp);
           }
           if (buff[0] == ',' || buff[0] == ' ')
           {
              buff++;
              continue;
           }
           else
           {
              //error
              return -1;
           }
        }while(((unsigned long) buff < (unsigned long)end));
   }
   return 0;
}

AVPContainerDerivedEntry::AVPContainerDerivedEntry(AVP* avp)
{
   if (avp)
   {
      _avpCount=0;
      avpList = (AVP**)
         calloc(10, sizeof(AVP*));
      if (avpList == NULL)
      {
               throw CodecException(__FILE__, __LINE__,"calloc Failed",
                                  ITS_DIA_RESOURCES_EXCEEDED);
      }
      avpList[_avpCount]=avp;
      _avpCount++;
   }
}

AVPContainerDerivedEntry::AVPContainerDerivedEntry()
{
   _avpCount=0;
   avpList   = NULL;
}

AVPContainerDerivedEntry::~AVPContainerDerivedEntry()
{
   releaseEntries();
}

void
AVPContainerDerivedEntry::releaseEntries()
{
    /**
     * This if check is added so that same memory
     * should not be deallocated twice.
     */
    if (_avpCount != 0 )
    {
        for(size_t i=0; i<_avpCount; ++i)
        {
            delete avpList[i];
        }
        free(avpList);
        _avpCount=0;
    }
}

std::ostream&
AVPContainerDerivedEntry::print(std::ostream &out) const
{
   for(size_t i=0; i<_avpCount; ++i)
   {
      out << "    ";
      avpList[i]->print(out);
      out << std::endl;
   }
   return out;
}

const AVP* 
AVPContainerDerivedEntry::getAt(unsigned int index)
{
   if (index < _avpCount)
   {
      return avpList[index];
   }
   return NULL;
}

int 
AVPContainerDerivedEntry::Encode(String& str)
{
   for(unsigned int i=0;i<_avpCount;++i)
   {
       avpList[i]->Encode(str);
   }
   return 0;
}

void 
AVPContainerDerivedEntry::add(AVP* avp)
{
   if (avp)
   {
      if (_avpCount &&
         ((_avpCount % 10) == 0))
      {
         unsigned int index = _avpCount / 10;
         index++;
         avpList = (AVP**)
            realloc(avpList, 10*index*sizeof(AVP*));
         if (avpList == NULL)
         {
             throw CodecException(__FILE__, __LINE__,"Realloc Failed",
                                 ITS_DIA_RESOURCES_EXCEEDED);
         }
      }
      else if(_avpCount == 0)
      {
          avpList = (AVP**)
              calloc(10, sizeof(AVP*));
          if (avpList == NULL)
          {
             throw CodecException(__FILE__, __LINE__,"calloc Failed",
                                 ITS_DIA_RESOURCES_EXCEEDED);
          }
      }
      avpList[_avpCount]=avp;
      _avpCount++;
   }
}

int
AVPContainerDerivedEntry::removeSpecificAvp(const AVP* avp)
{
    if (avp == NULL)
        return -1;

    if (avpList)
    {
        for(size_t i=0; i<_avpCount; ++i)
        {
            if (avpList[i] == avp)
            {    
                delete avpList[i];
                avpList[i] = NULL;
                /**
                 * This for loop is to compress the dynamic array after
                 * one element is removed. All the elements are shifed
                 * to one position less and last one is made NULL.
                 */    
                for (int k=i; k<(_avpCount-1) ;k++)
                {
                    avpList[k] =avpList[k+1];
                } 
                avpList[_avpCount-1] = NULL;
                _avpCount--;
                if (_avpCount == 0)
                {
                    free(avpList);
                    avpList = NULL;
                }
                return 0; 
            }
        } 
    }
    return -1; 
}

AVPContainerDerived::AVPContainerDerived()
{
   _nameObj=NULL;
   _cmdnameObj=NULL;
   _noOfMandAvp=0;
   _baseMandBitMap =0;
   _totalContEntries = 0;
   _totalappBuff = 0;
   avpContDerivedEntryList = NULL;
   appAVPBuffList = NULL;
   _dictEntries   = 0;
   _instCntr      = 0;
}

AVPContainerDerived::~AVPContainerDerived()
{
   releaseEntries();
}

void
AVPContainerDerived::releaseEntries()
{
   for(size_t i=0; i<(_totalContEntries + _dictEntries); ++i)
   {
      delete avpContDerivedEntryList[i];
   }
   //delete appBuff
   for(size_t i=0; i < _totalappBuff; ++i)
   {
      if (appAVPBuffList[i])
      {
         delete appAVPBuffList[i];
      }
   }
   free(avpContDerivedEntryList);
   if (_totalappBuff)
   {
      free(appAVPBuffList);
   }
}

std::ostream&
AVPContainerDerived::printExtras(std::ostream &out) const
{
   if (_dictEntries == 0)
   {
      return out << "(Extras Not Available)"<<endl;
   }
   out << "(Extras Available)"<< endl;
   unsigned int noOfEntries = _dictEntries + _totalContEntries;
   for(size_t i=_totalContEntries; i < noOfEntries; ++i)
   {
      AVPContainerDerivedEntry* entry = avpContDerivedEntryList[i];
      if (entry)
      {
         entry->print(out);
      }
   }
   return out;
}

std::ostream&
AVPContainerDerived::print(std::ostream &out) const
{
   for(size_t i=0; i<_totalContEntries; ++i)
   {
      AVPContainerDerivedEntry* entry = avpContDerivedEntryList[i];
      if (entry)
      {
         entry->print(out);
      }
   }
   return out;
}

AVPContainerDerivedEntry*&
AVPContainerDerived::operator [](unsigned int avpIndex)
{
   if (avpIndex >= (_totalContEntries + _dictEntries))
   {
      if (_totalContEntries || _dictEntries)
      {
        avpContDerivedEntryList = (AVPContainerDerivedEntry**)
           realloc(avpContDerivedEntryList, (avpIndex+1)*sizeof(AVPContainerDerivedEntry*));
        if (avpContDerivedEntryList == NULL)
        {
           throw CodecException(__FILE__, __LINE__,"Realloc Failed",
                               ITS_DIA_RESOURCES_EXCEEDED);
        }
        for (int i = _totalContEntries+_dictEntries;
             i <= avpIndex; ++i)
        {
           avpContDerivedEntryList[i]=NULL;
        }
      }
      else
      {
        avpContDerivedEntryList = (AVPContainerDerivedEntry**)
            calloc(1, sizeof(AVPContainerDerivedEntry*));
        if (avpContDerivedEntryList == NULL)
        {
           throw CodecException(__FILE__, __LINE__,"calloc Failed",
                               ITS_DIA_RESOURCES_EXCEEDED);
        }
      }
      _dictEntries = avpIndex+1-_totalContEntries;
   }

   return avpContDerivedEntryList[avpIndex];
}


void
AVPContainerDerived::SetNameObj(const AttributeName* nameObj)
{
   if (((unsigned long)nameObj) == ((unsigned long)&AttributeName::AVP))
   {
       return;
   }
   _nameObj = nameObj;
   GroupedAttributeName& GroupedObj = *((GroupedAttributeName*)nameObj);
   unsigned int totalNo = GroupedObj.GetMandAttMap().size() + GroupedObj.GetOptAttMap().size();
   if (totalNo)
   {
      avpContDerivedEntryList = (AVPContainerDerivedEntry**)
             calloc(totalNo, sizeof(AVPContainerDerivedEntry*));
      _totalContEntries = totalNo;
   }
}

AVPContainerDerived& 
AVPContainerDerived::SetCmdObj(const CommandAttribute* cmdnameObj)
{
   if (_cmdnameObj)
   {
      return *this;
   }
   if (cmdnameObj)
   {
      SetNoOfContEntry(cmdnameObj->GetTotalNoOfAVPs());
   }
   else
   {
      SetNoOfContEntry(AttributeCodeMap::GetNoOfAVPs());
   }
   _cmdnameObj = cmdnameObj;
   return *this;
}

const AVP&
AVPContainerDerived::getExtra(const AttributeName &name, unsigned index) const
{
   AVPContainerDerivedEntry* entry = NULL;
   if (((unsigned long)&name) == ((unsigned long)&AttributeName::AVP))
   {
      entry = avpContDerivedEntryList[index+_totalContEntries];
      if (entry)
      {
          return *(entry->getAt(0));
      }
   }
   for(int i =_totalContEntries; 
       i < (_totalContEntries + _dictEntries);
       ++i)
   {
       AVPContainerDerivedEntry* entry = avpContDerivedEntryList[i];
       if (entry)
       {
          const AVP* avp = entry->getAt(0);
          const AttributeName& nameObj = avp->name();
          if(((unsigned long)&name) == ((unsigned long)&nameObj))
          {
             return *avp;
          }
       }
   }
   throw CodecException(__FILE__, __LINE__,"Extensible AVP not found at index");
}

const AVP& 
AVPContainerDerived::get(const AttributeName &name, unsigned index) const
{
   unsigned int avpIndex;
   const AVP* avp=NULL;
   if(name.ifBase() ||
      _nameObj)
   {
      avpIndex = name.GetIndex();
   }
   else if(_cmdnameObj)
   {
      //don't increase noOfMandAvp counter here
      //noOfMandAvp incremented only in add function
      bool fMand;
      avpIndex = _cmdnameObj->GetIndex(&name,fMand);
   }
   else
   {
       throw CodecException(__FILE__, __LINE__,"Invalid AvpIndex",
                               ITS_DIA_AVP_UNSUPPORTED);
   }

   AVPContainerDerivedEntry* entry  = avpContDerivedEntryList[avpIndex];
   if (entry)
   {
      avp = entry->getAt(index);
   }
   if (avp == NULL)
   {
      throw NoSuchAttributeException(__FILE__, __LINE__,
                (name), name.GetCode());
   }
   return *avp;
}

const AVP*
AVPContainerDerived::getPtr(const AttributeName &name, unsigned index) const
{
   unsigned int avpIndex;
   const AVP* avp=NULL;
   if(name.ifBase() ||
      _nameObj)
   {
      avpIndex = name.GetIndex();
   }
   else if(_cmdnameObj)
   {
     //don't increase noOfMandAvp counter here
     //noOfMandAvp incremented only in add function
     bool fMand;
     avpIndex = _cmdnameObj->GetIndex(&name,fMand);
   }
   else
   { 
       throw CodecException(__FILE__, __LINE__,"Invalid AvpIndex",
                               ITS_DIA_AVP_UNSUPPORTED);
   }
   AVPContainerDerivedEntry* entry  = avpContDerivedEntryList[avpIndex];
   if (entry)
   {
      avp = entry->getAt(index);
   }
   return avp;
}

void
AVPContainerDerived::SetNoOfContEntry(unsigned int totalNo)
{
   if (_totalContEntries == 0 && totalNo)
   {
       avpContDerivedEntryList = (AVPContainerDerivedEntry**)
              calloc(totalNo, sizeof(AVPContainerDerivedEntry*));
       if (avpContDerivedEntryList == NULL)
       {
           throw CodecException(__FILE__, __LINE__,"calloc Failed",
                               ITS_DIA_RESOURCES_EXCEEDED);
       }
       _totalContEntries = totalNo;
   }
   else if (totalNo > _totalContEntries)
   {
       avpContDerivedEntryList = (AVPContainerDerivedEntry**)
              realloc(avpContDerivedEntryList, totalNo*sizeof(AVPContainerDerivedEntry*));
       if (avpContDerivedEntryList == NULL)
       {
           throw CodecException(__FILE__, __LINE__,"Realloc Failed",
                               ITS_DIA_RESOURCES_EXCEEDED);
       }

       while(_totalContEntries < totalNo)
       {
          avpContDerivedEntryList[_totalContEntries]=NULL;
          _totalContEntries++;
       }
   }
}

AVPContainerDerivedEntry*&
AVPContainerDerived::getAt(unsigned int avpIndex) const
{
   AVPContainerDerived& avpObj =  (AVPContainerDerived&)*this;
   return avpObj[avpIndex];
}

void
AVPContainerDerived::SetAppAVPBuff(unsigned char* buff, unsigned int Size,
             unsigned int offSet,unsigned int avpCode, 
             unsigned int vendorId, DiaHeader& hdr)
{
   if (appAVPBuffList == NULL)
   {
       //allocate for 40 and multiples
       appAVPBuffList = (AVPBuff**)
             calloc(40, sizeof(AVPBuff*));

       if (appAVPBuffList == NULL)
       {
           throw CodecException(__FILE__, __LINE__,"SetAppAVPBuff::Calloc Failed",
                                ITS_DIA_RESOURCES_EXCEEDED);
       }
   }

   AVPBuff* buffObj = new AVPBuff(buff, Size, offSet, avpCode, vendorId, hdr);
   appAVPBuffList[_totalappBuff++] = buffObj;

   //Changed the initial size from 20 to 40
   if ((_totalappBuff % 40) == 0)
   {
      unsigned int index = _totalappBuff / 40;
      index++;

      appAVPBuffList = (AVPBuff**)
           realloc(appAVPBuffList, 40*index*sizeof(AVPBuff*));

      if (appAVPBuffList == NULL)
      {
          throw CodecException(__FILE__, __LINE__,"SetAppAVPBuff::Realloc Failed",
                               ITS_DIA_RESOURCES_EXCEEDED);
      }
   }
}

void
AVPContainerDerived::copy(AVPContainerDerived& entry)
{
   avpContDerivedEntryList = entry.avpContDerivedEntryList;
   appAVPBuffList          = entry.appAVPBuffList;
   _nameObj = entry._nameObj;
   _cmdnameObj = entry._cmdnameObj;
   _noOfMandAvp = entry._noOfMandAvp;
   _baseMandBitMap = entry._baseMandBitMap;
   _totalContEntries = entry._totalContEntries;
   _totalappBuff = entry._totalappBuff;
   _dictEntries  = entry._dictEntries;
   _instCntr     = entry._instCntr;
}

/*
 * Error Type : 1 - Mandatory AVP Missing in Grouped AVP
 *              2 - Base Mandatory AVP Missing in Command
 *              3 - Mandatory AVP Missing in Command
 */
void
AVPContainerDerived::PrintMissingMandAvp(AttributeName* name, unsigned int errType)
{
    cout << "************************************************" << endl;

    if (errType == 1)
    {
        cout << "Mandatory AVP Missing in Grouped AVP"  << endl;
    }
    else if (errType == 2)
    {
        cout << "Base Mandatory AVP Missing in Command" << endl;
    }
    else if (errType == 3)
    {
        cout << "Mandatory AVP Missing in Command"      << endl;
    }
    cout << " AVP Code: " << name->GetCode()            << 
            " AVP Name: " << (AttributeName)*name       << endl;

    cout << "************************************************" << endl;
}

void
AVPContainerDerived::PrintMissingMandAvp()
{
    if (_nameObj)
    {
        GroupedAttributeName& GroupedObj = *((GroupedAttributeName*)_nameObj);

        if (_noOfMandAvp != GroupedObj.GetMandAttMap().size())
        {
            std::map<unsigned int, AttributeName*>::iterator it =
                                     GroupedObj.GetMandAttMap().begin();

            std::map<unsigned int, AttributeName*>::iterator eit =
                                     GroupedObj.GetMandAttMap().end();

            while (it != eit)
            {
                bool ifFound = false;
                unsigned int code = (*it).second->GetCode();

                for (int i=0; i<_totalContEntries; i++)
                {
                    AVPContainerDerivedEntry* entry = 
                                              avpContDerivedEntryList[i];
                    if (entry) 
                    {
                        const AVP* avp = entry->getAt(0);
                        const AttributeName& nameObj = avp->name();
                        unsigned int avpCode  = nameObj.GetCode();

                        if (avpCode == code)
                        { 
                            ifFound = true;
                            break;
                        }
                    }
                }

                if (!ifFound)
                {
                    unsigned int code = (*it).second->GetCode();
                    missingAVPCodes.push_back(code);
                    PrintMissingMandAvp((AttributeName*)(*it).second, 1);
                    //store this avp in a list  
                }
                it++;
            }
        }
    }

    if (_cmdnameObj)
    {
        if ((_baseMandBitMap & _cmdnameObj->GetMandBaseBitMap()) != 
                                            _cmdnameObj->GetMandBaseBitMap())
        {
            std::set<const AttributeName*> _baseAVPs = 
                   ((CommandAttribute*)_cmdnameObj)->GetMandBaseAvpList();

            std::set<const AttributeName*>::const_iterator it =
                                                      _baseAVPs.begin();

            for(; it != _baseAVPs.end(); ++it)
            {
                bool ifFound = false;
                const AttributeName* listName = (*it);
                unsigned int code = listName->GetCode();

                for (int i=0; i<_totalContEntries; i++)
                {
                    AVPContainerDerivedEntry* entry = 
                                       avpContDerivedEntryList[i];

                    if (entry)
                    {
                        const AVP* avp = entry->getAt(0);
                        const AttributeName& nameObj = avp->name();
                        unsigned int avpCode  = nameObj.GetCode();
                        unsigned int venId = nameObj.vendorId();

                        if ((avpCode == code) &&
                            (venId  == listName->vendorId()))
                        {
                            ifFound = true;
                            break;
                        }
                    }
                }

                if (!ifFound)
                {
                    missingAVPCodes.push_back(code);
                    PrintMissingMandAvp((AttributeName*)listName, 2);
                }
            }
        }

        if (_noOfMandAvp != _cmdnameObj->GetNoOfAppMandAVPs())
        {
            std::map<unsigned int, AttributeIndexPair>& _mandAppAVPs =
                     ((CommandAttribute*) _cmdnameObj)->GetMandAppAvpList();

            std::map<unsigned int, AttributeIndexPair>::const_iterator it = 
                                                       _mandAppAVPs.begin();

            for (;it != _mandAppAVPs.end(); it++)
            {
                AttributeIndexPair attrIndxPair = (*it).second;

                bool ifFound = false;
                unsigned int code = attrIndxPair._name->GetCode();
                unsigned int vId = attrIndxPair._name->vendorId();

                for (int i=0; i<_totalContEntries; i++)
                {
                    AVPContainerDerivedEntry* entry =
                                              avpContDerivedEntryList[i];
                    if (entry)
                    {
                        const AVP* avp = entry->getAt(0);
                        const AttributeName& nameObj = avp->name();
                        unsigned int avpCode  = nameObj.GetCode();

                        if (avpCode == code) 
                        {   
                            ifFound = true;
                            break;
                        }
                    }
                }

                for (int i=0; i<_totalappBuff; i++)
                {
                    if (appAVPBuffList[i])
                    {
                        unsigned int avpCode = appAVPBuffList[i]->_avpcode;
                        unsigned int vendId = appAVPBuffList[i]->_vendorId;

                        if ((avpCode == code) && (vendId == vId))
                        {
                            ifFound = true;
                            break;
                        }
                    }
                }

                if (!ifFound)
                {
                    missingAVPCodes.push_back(code);
                    PrintMissingMandAvp((AttributeName*)attrIndxPair._name, 3);
                }
            }
        }
    }
}

bool
AVPContainerDerived::validateMand() const
{
   if (_nameObj)
   {
      //_noOfMandAvp = no of Mand.AVPs in GroupedAVP
      GroupedAttributeName& GroupedObj = *((GroupedAttributeName*)_nameObj);

      return (_noOfMandAvp == GroupedObj.GetMandAttMap().size());
   }
   if (_cmdnameObj)
   {
      //_noOfMandAvp = no of application specific AVPs
      return ((_baseMandBitMap & _cmdnameObj->GetMandBaseBitMap()) &&
             (_noOfMandAvp == _cmdnameObj->GetNoOfAppMandAVPs()));
   }
   return true;
}

void
AVPContainerDerived::add(const AttributeName &name, AVP *value)
{
    unsigned int avpIndex = _dictEntries + _totalContEntries;
    if (avpIndex >= _totalContEntries)
    {
        if (_totalContEntries || _dictEntries)
        {
           avpContDerivedEntryList = (AVPContainerDerivedEntry**)
                realloc(avpContDerivedEntryList, (avpIndex+1)*sizeof(AVPContainerDerivedEntry*));
           if (avpContDerivedEntryList == NULL)
           {
               throw CodecException(__FILE__, __LINE__,"Realloc Failed",
                                   ITS_DIA_RESOURCES_EXCEEDED);
           }
           avpContDerivedEntryList[avpIndex]=NULL;
        }
        else
        {
           avpContDerivedEntryList = (AVPContainerDerivedEntry**)
               calloc(1, sizeof(AVPContainerDerivedEntry*));
           if (avpContDerivedEntryList == NULL)
           {
               throw CodecException(__FILE__, __LINE__,"calloc Failed",
                                   ITS_DIA_RESOURCES_EXCEEDED);
           }
        }
        _dictEntries++;
    }

    AVPContainerDerivedEntry* &entry = getAt(avpIndex);
    if(entry)
    {
        //just delete, overwrite with new values
        entry->releaseEntries();
    }
    else if(entry == NULL)
    {
        AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry();
        entry=avpEntry;
    }
    entry->add(value);
}

const AVP&
AVPContainerDerived::add(const AttributeName &name, const AVP &value, 
                         bool single)
{
    unsigned int avpIndex = name.GetIndex();
    if(_nameObj)
    {
        unsigned int avpCode  = name.GetCode();
        GroupedAttributeName& GroupedObj = *((GroupedAttributeName*)_nameObj);
        std::map<unsigned int, AttributeName*>::iterator it = 
                                     GroupedObj.GetMandAttMap().find(avpCode);
        if(it != GroupedObj.GetMandAttMap().end())
        {
            //only Mandatory AVPs
            avpIndex = (*it).second->GetIndex();
            AVPContainerDerivedEntry* &entry = getAt(avpIndex);
            if (entry == NULL)
            {
                _noOfMandAvp++;
            }
        }
        else if((it = GroupedObj.GetOptAttMap().find(avpCode)) != 
                                              GroupedObj.GetOptAttMap().end())
        {
            //only optional AVPs
            avpIndex = (*it).second->GetIndex();
        }
        else
        {
            //extensible AVPs
            avpIndex = GroupedObj.GetOptAttMap().size() + 
                                GroupedObj.GetMandAttMap().size()+_dictEntries;
        }
    }
    if(_cmdnameObj)
    {
        if(name.ifBase())
        {
            avpIndex = name.GetIndex();
            _baseMandBitMap |= (0x8000000000000000ull >> name.GetIndex());
        }
        else
        {
            bool fMand;
            avpIndex = _cmdnameObj->GetIndex(&value.name(),fMand);
            if(fMand)
            {
                 _noOfMandAvp++;
            }
        }
    }
    if (avpIndex >= (_totalContEntries+_dictEntries))
    {
        if (_totalContEntries || _dictEntries)
        {
            avpContDerivedEntryList = (AVPContainerDerivedEntry**)
              realloc(avpContDerivedEntryList, (avpIndex+1)*sizeof(AVPContainerDerivedEntry*));
           if (avpContDerivedEntryList == NULL)
           {
               throw CodecException(__FILE__, __LINE__,"Realloc Failed",
                                   ITS_DIA_RESOURCES_EXCEEDED);
           }
           for (int i = _totalContEntries+_dictEntries; 
                i <= avpIndex; ++i)
           {
               avpContDerivedEntryList[i]=NULL;
           }
        }
        else
        {
            avpContDerivedEntryList = (AVPContainerDerivedEntry**)
                     calloc(1, sizeof(AVPContainerDerivedEntry*));
            if (avpContDerivedEntryList == NULL)
            {
               throw CodecException(__FILE__, __LINE__,"calloc Failed",
                                  ITS_DIA_RESOURCES_EXCEEDED);
            }
        }
        _dictEntries = avpIndex+1-_totalContEntries;
    }

    AVPContainerDerivedEntry* &entry = getAt(avpIndex);
    if(entry && single)
    {
        entry->releaseEntries();
    }
    else if(entry == NULL)
    {
        AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry();
        entry=avpEntry;
    }
    AVP* avp = value.createCopy();
    if (avp == NULL)
    {
        throw CodecException(__FILE__, __LINE__,"Could not create Object",ITS_DIA_AVP_UNSUPPORTED);
    }
    entry->add(avp);
    const AVP& avpref = (*avp);
    return  avpref;
}

int
AVPContainerDerived::countExtra(const AttributeName &name) const
{
   if (((unsigned long)&name) == ((unsigned long)&AttributeName::AVP))
   {
      return _dictEntries;
   }
   unsigned int dictEntries = 0;
   for(int i =_totalContEntries; 
       i < (_totalContEntries + _dictEntries);
       ++i)
   {
       AVPContainerDerivedEntry* entry = avpContDerivedEntryList[i];
       if (entry)
       {
          const AVP* avp = entry->getAt(0);
          const AttributeName& nameObj = avp->name();
          if(((unsigned long)&name) == ((unsigned long)&nameObj))
          {
             dictEntries++;
          }
       }
   }
   return dictEntries; 
}

int
AVPContainerDerived::count(const AttributeName &name) const
{
     unsigned int avpIndex;
     if(name.ifBase() ||
     _nameObj)
     {
        avpIndex = name.GetIndex();
     }
     else if(_cmdnameObj)
     {
       //don't increase noOfMandAvp counter here
       //noOfMandAvp incremented only in add function
       bool fMand;
       avpIndex = _cmdnameObj->GetIndex(&name,fMand);
     }
     else
     {
         throw CodecException(__FILE__, __LINE__,"Invalid AvpIndex",
                               ITS_DIA_AVP_UNSUPPORTED);
     }

     AVPContainerDerivedEntry* &entry = getAt(avpIndex);
     if(entry)
     {
        return entry->AvpCount();
     }
     else
     {
        return 0;
     }
}

bool
AVPContainerDerived::containsExtra(const AttributeName &name) const
{
   if (((unsigned long)&name) == ((unsigned long)&AttributeName::AVP))
   {
      return _dictEntries ? true : false;
   }
   unsigned int dictEntries = 0;
   for(int i =_totalContEntries; 
       i < (_totalContEntries + _dictEntries);
       ++i)
   {
       AVPContainerDerivedEntry* entry = avpContDerivedEntryList[i];
       if (entry)
       {
          const AVP* avp = entry->getAt(0);
          const AttributeName& nameObj = avp->name();
          if(((unsigned long)&name) == ((unsigned long)&nameObj))
          {
             return true;
          }
       }
   }
   return false;
}

bool
AVPContainerDerived::contains(const AttributeName &name) const
{
     unsigned int avpIndex;
     if(name.ifBase() ||
     _nameObj)
     {
        avpIndex = name.GetIndex();
     }
     else if(_cmdnameObj)
     {
       //don't increase noOfMandAvp counter here
       //noOfMandAvp incremented only in add function
       bool fMand;
       avpIndex = _cmdnameObj->GetIndex(&name,fMand);
     }
     else
     {
         throw CodecException(__FILE__, __LINE__,"Invalid AvpIndex",
                               ITS_DIA_AVP_UNSUPPORTED);
     }

     AVPContainerDerivedEntry* &entry = getAt(avpIndex);
     if(entry)
     {
        return true;
     }
     return false;
}

int
AVPContainerDerived::EncodeAppAVP(String& str)
{
   for(int i=0; (i < _totalappBuff); i++)
   {
      if (appAVPBuffList[i])
      {
         unsigned int avpLen = appAVPBuffList[i]->_size;
         str.append((char*)appAVPBuffList[i]->_buffer, avpLen);
         avpLen = (avpLen %4);
         if(avpLen)
         {
           char temp[3]={0,0,0};
           str.append(temp, 4-avpLen);
         }
      }
   }
   return 0;
}


//return the value for basic avp types based on avpCode
/**
 * Adding the const to the signature (for ticket 1850).
 */
int
AVPContainerDerived::getAvpValue(unsigned int avpCode, void* val, 
                        ValueDiscriminator D, unsigned int venId) const
{
    //application specific avp look up
    //avp lookup if downstream message or message where impl is set
    int i = 0;
    for(; i < _totalContEntries; i++)
    {
       if (avpContDerivedEntryList[i] == NULL)
       {
          continue;
       }
       const AVP* avp = avpContDerivedEntryList[i]->getAt(0);
       if(avp->name().GetCode() == avpCode &&
         ((venId == 0) || (venId == avp->name().vendorId())))
       {
           if (avp->GetType() != D)
           {
              //mismatch in type, please check the type of AVP 
              return -1;
           }
           switch(D)
           {
              case Unsigned32Type   :
              case Integer32Type    :
              case TimeType         :
              case EnumeratedType   :
                  {
                    *((int*)val) = ((Integer32Avp*)avp)->value();
                    return 0;
                  }
              case Integer64Type    :
              case Unsigned64Type   :
                  {
                     *((unsigned long long*)val) = ((Integer64Avp*)avp)->value();
                     return 0;
                  }
              case Float32Type   :
                  {
                      *((float*)val) = ((Float32Avp*)avp)->value();
                      return 0;
                  }
              case Float64Type   :
                  {
                      *((double*)val) = ((Float64Avp*)avp)->value();
                      return 0;
                  }
              case OctetStringType  :
              case IdentityType     :
              case UTF8StringType   :
                  {
                     *((OctetString*)val) = ((OctetStringAvp*)avp)->value();
                     return 0;
                  }
              case AddressType      :
                  {
                     *((Address*)val) = ((AddressAvp*)avp)->value();
                     return 0;
                  }
              case URIType          :
                  {
                     *((URI*)val) = ((URIAvp*)avp)->value();
                     return 0;
                  }
              case IPFilterRuleType :
                  {
                     *((IPFilterRule*)val) = ((IPFilterRuleAvp*)avp)->value();
                     return 0;
                  }
              case GroupedType      :
                  {
                     GroupedAVPImplDerived& gImpl =
                       (GroupedAVPImplDerived&)((GroupedAVP*)val)->getImpl();
                     const GroupedAVPImplDerived& gImplS =
                       (const GroupedAVPImplDerived&)((GroupedAVP*)avp)->getImpl();
                     gImpl = gImplS;
                     return 0;
                  }
              default               :
                   return -1;
           }
           return 0;
       }
    }
    if (i > AttributeCodeMap::GetNoOfAVPs())
    {
        //not found in previous look up, hence no need to lookup again
        return -1;
    }
    //avp lookup if upstream message using generic command
    for(i=0; (i < _totalappBuff); i++)
    {
        if (appAVPBuffList[i] && 
           (avpCode == appAVPBuffList[i]->_avpcode))
        {
           unsigned char* buffer = appAVPBuffList[i]->_buffer + appAVPBuffList[i]->_offset;
           int size = appAVPBuffList[i]->_size - appAVPBuffList[i]->_offset;
           switch(D)
           {
              case OctetStringType  :
              case IdentityType     :
                  {
                    OctetStringParser octStr;
                    return octStr.Decode(buffer, size, val);
                  }
              case Unsigned32Type   :
              case Integer32Type    :
              case TimeType         :
              case EnumeratedType   :
                  {
                    Integer32Parser int32Parser;
                    return int32Parser.Decode(buffer, size, val);
                  }
              case Integer64Type    :
              case Unsigned64Type   :
                  {
                      Integer64Parser int64Parser;
                      return int64Parser.Decode(buffer, size, val);
                  }
              case Float32Type    :
                  {
                      Float32Parser float32Parser;
                      return float32Parser.Decode(buffer, size, val);
                  }
              case Float64Type   :
                  {
                      Float64Parser float64Parser;
                      return float64Parser.Decode(buffer, size, val);
                  }
              case AddressType      :
                  { 
                    AddressParser addParser;
                    return addParser.Decode(buffer, size, val);
                  }
              case URIType          :
                  {
                    URIParser  uriParser;
                    return uriParser.Decode(buffer, size, val);
                  }
              case UTF8StringType   :
                  {
                    UTF8StringParser utf8StrParser;
                    return utf8StrParser.Decode(buffer, size, val);
                  }
              case IPFilterRuleType :
                  {
                    IPFilterRuleParser ipfiltParser;
                    return ipfiltParser.Decode(buffer, size, val);
                  }
              case GroupedType      :
                  {
                    /** get command Attribute to decode grouped AVP
                      may hit performance, better to use APP.API
                      */
                      unsigned int avpCode = appAVPBuffList[i]->_avpcode;
                      unsigned int avpIndex = 0;
                      const CommandAttribute* cmdAtt = _cmdnameObj;
                      bool fMand = false;
                      const AttributeName* name = NULL;
                      DiaHeader& hdr = appAVPBuffList[i]->_hdr;
                      if (_nameObj)
                      {
                         //GroupedAVP inside GroupedAVP
                         GroupedAttributeName* grpNameObj = (GroupedAttributeName*)_nameObj;
                         name = grpNameObj->getAttributeName(avpCode, avpIndex, fMand);
                      }
                      else if(_cmdnameObj == 0)
                      {
                         //get command attribute
                         cmdAtt = CommandAttribute::getCmdAttribute(hdr.appId, hdr.code, hdr.flags.r);
                         if (cmdAtt == NULL)
                         {
                            return -1;
                         }
                         
                         /**
                          * Remove the constness temporarily by using the const_cast to 
                          * call SetCmdObj.
                          * Final fix for ticket 1850 raised by Bridgewater (Hemant)
                          */ 
                         const_cast<AVPContainerDerived*>(this)->SetCmdObj(cmdAtt);
                         // Again adding the constness to this object.
                         const_cast<const AVPContainerDerived*>(this);                          

                      }
                      name = cmdAtt->GetAppAttributeObj(avpCode, venId, avpIndex, fMand);
                      if (name)
                      {
                         DerivedGroupedAVP* grpAVP = new DerivedGroupedAVP(*name, 0);
                         unsigned char* buffer = appAVPBuffList[i]->_buffer + appAVPBuffList[i]->_offset;
                         int size = appAVPBuffList[i]->_size - appAVPBuffList[i]->_offset;
                         grpAVP->Decode(buffer, size, hdr);
                         AVPContainerDerivedEntry* &entry = getAt(avpIndex);
                         if(entry)
                         {
                            entry->add(grpAVP);
                         }
                         else
                         {
                            AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry(grpAVP);
                            entry=avpEntry;
                         }
                         delete appAVPBuffList[i];
                         appAVPBuffList[i] = NULL;
                         GroupedAVPImplDerived& gImpl =
                            (GroupedAVPImplDerived&)((GroupedAVP*)val)->getImpl();
                         const GroupedAVPImplDerived& gImplS =
                            (const GroupedAVPImplDerived&)grpAVP->getImpl();
                         gImpl = gImplS;
                         return 0;
                      }
                      else
                      {
                         return -1;
                      }
                  }
              default               :
                   return -1;
           }
        }
    }
    return -1;
} 

int AVPContainerDerived::getAvpCount(unsigned int avpCode, unsigned int venId)
{
    int i = 0;
	int count = 0;
    for(; i < _totalContEntries; i++)
    {
       if (avpContDerivedEntryList[i] == NULL)
       {
          continue;
       }
       const AVP* avp = avpContDerivedEntryList[i]->getAt(0);
       if(avp->name().GetCode() == avpCode &&
         ((venId == 0) || (venId == avp->name().vendorId())))
       {
		   count = avpContDerivedEntryList[i]->AvpCount();
		   return count;
	   }
	}

	i = 0;
    for(i; (i < _totalappBuff); i++)
    {
        if (appAVPBuffList[i] && 
           (avpCode == appAVPBuffList[i]->_avpcode))
        {
			count++;
        }
    }	
	if(count !=0)
		return count;	
	else
		return -1;
}

//return the value for basic avp types based on avpCode
/**
 * Overloading the getAVPValue for Generic AVP Access).
 */
int
AVPContainerDerived::getAvpValue(unsigned int avpCode,unsigned int index, void* val, 
                        ValueDiscriminator D, unsigned int venId) const
{
    //application specific avp look up
    //avp lookup if downstream message or message where impl is set
    int i = 0;
    for(; i < _totalContEntries; i++)
    {
       if (avpContDerivedEntryList[i] == NULL)
       {
          continue;
       }
       const AVP* avp = avpContDerivedEntryList[i]->getAt(index);
       if((avp!= NULL) && avp->name().GetCode() == avpCode &&
         ((venId == 0) || (venId == avp->name().vendorId())))
       {
           if (avp->GetType() != D)
           {
              //mismatch in type, please check the type of AVP 
              return -1;
           }
           switch(D)
           {
              case Unsigned32Type   :
              case Integer32Type    :
              case TimeType         :
              case EnumeratedType   :
                  {
                    *((int*)val) = ((Integer32Avp*)avp)->value();
                    return 0;
                  }
              case Integer64Type    :
              case Unsigned64Type   :
                  {
                     *((unsigned long long*)val) = ((Integer64Avp*)avp)->value();
                     return 0;
                  }
              case Float32Type   :
                  {
                      *((float*)val) = ((Float32Avp*)avp)->value();
                      return 0;
                  }
              case Float64Type   :
                  {
                      *((double*)val) = ((Float64Avp*)avp)->value();
                      return 0;
                  }
              case OctetStringType  :
              case IdentityType     :
              case UTF8StringType   :
                  {
                     *((OctetString*)val) = ((OctetStringAvp*)avp)->value();
                     return 0;
                  }
              case AddressType      :
                  {
                     *((Address*)val) = ((AddressAvp*)avp)->value();
                     return 0;
                  }
              case URIType          :
                  {
                     *((URI*)val) = ((URIAvp*)avp)->value();
                     return 0;
                  }
              case IPFilterRuleType :
                  {
                     *((IPFilterRule*)val) = ((IPFilterRuleAvp*)avp)->value();
                     return 0;
                  }
              case GroupedType      :
                  {
                     GroupedAVPImplDerived& gImpl =
                       (GroupedAVPImplDerived&)((GroupedAVP*)val)->getImpl();
                     const GroupedAVPImplDerived& gImplS =
                       (const GroupedAVPImplDerived&)((GroupedAVP*)avp)->getImpl();
                     gImpl = gImplS;
                     return 0;
                  }
              default               :
                   return -1;
           }
           return 0;
       }
    }
    //avp lookup if upstream message using generic command
	i = 0;
	int count = 0;
    for(i; (i < _totalappBuff); i++)
	{
		if (appAVPBuffList[i] && 
				(avpCode == appAVPBuffList[i]->_avpcode))
		{
			if(count == index)
			{
				unsigned char* buffer = appAVPBuffList[i]->_buffer + appAVPBuffList[i]->_offset;
				int size = appAVPBuffList[i]->_size - appAVPBuffList[i]->_offset;
				switch(D)
				{
					case OctetStringType  :
					case IdentityType     :
						{
							OctetStringParser octStr;
							return octStr.Decode(buffer, size, val);
						}
					case Unsigned32Type   :
					case Integer32Type    :
					case TimeType         :
					case EnumeratedType   :
						{
							Integer32Parser int32Parser;
							return int32Parser.Decode(buffer, size, val);
						}
					case Integer64Type    :
					case Unsigned64Type   :
						{
							Integer64Parser int64Parser;
							return int64Parser.Decode(buffer, size, val);
						}
					case Float32Type    :
						{
							Float32Parser float32Parser;
							return float32Parser.Decode(buffer, size, val);
						}
					case Float64Type   :
						{
							Float64Parser float64Parser;
							return float64Parser.Decode(buffer, size, val);
						}
					case AddressType      :
						{ 
							AddressParser addParser;
							return addParser.Decode(buffer, size, val);
						}
					case URIType          :
						{
							URIParser  uriParser;
							return uriParser.Decode(buffer, size, val);
						}
					case UTF8StringType   :
						{
							UTF8StringParser utf8StrParser;
							return utf8StrParser.Decode(buffer, size, val);
						}
					case IPFilterRuleType :
						{
							IPFilterRuleParser ipfiltParser;
							return ipfiltParser.Decode(buffer, size, val);
						}
					case GroupedType      :
						{
							/** get command Attribute to decode grouped AVP
							  may hit performance, better to use APP.API
							  */
							unsigned int avpCode = appAVPBuffList[i]->_avpcode;
							unsigned int avpIndex = 0;
							const CommandAttribute* cmdAtt = _cmdnameObj;
							bool fMand = false;
							const AttributeName* name = NULL;
							DiaHeader& hdr = appAVPBuffList[i]->_hdr;
							if (_nameObj)
							{
								//GroupedAVP inside GroupedAVP
								GroupedAttributeName* grpNameObj = (GroupedAttributeName*)_nameObj;
								name = grpNameObj->getAttributeName(avpCode, avpIndex, fMand);
							}
							else if(_cmdnameObj == 0)
							{
								//get command attribute
								cmdAtt = CommandAttribute::getCmdAttribute(hdr.appId, hdr.code, hdr.flags.r);
								if (cmdAtt == NULL)
								{
									return -1;
								}

								/**
								 * Remove the constness temporarily by using the const_cast to 
								 * call SetCmdObj.
								 * Final fix for ticket 1850 raised by Bridgewater (Hemant)
								 */ 
								const_cast<AVPContainerDerived*>(this)->SetCmdObj(cmdAtt);
								// Again adding the constness to this object.
								const_cast<const AVPContainerDerived*>(this);                          

							}
							name = cmdAtt->GetAppAttributeObj(avpCode, venId, avpIndex, fMand);
							if (name)
							{
								DerivedGroupedAVP* grpAVP = new DerivedGroupedAVP(*name, 0);
								unsigned char* buffer = appAVPBuffList[i]->_buffer + appAVPBuffList[i]->_offset;
								int size = appAVPBuffList[i]->_size - appAVPBuffList[i]->_offset;
								grpAVP->Decode(buffer, size, hdr);
								AVPContainerDerivedEntry* &entry = getAt(avpIndex);
								if(entry)
								{
									entry->add(grpAVP);
								}
								else
								{
									AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry(grpAVP);
									entry=avpEntry;
								}
								delete appAVPBuffList[i];
								appAVPBuffList[i] = NULL;
								GroupedAVPImplDerived& gImpl =
									(GroupedAVPImplDerived&)((GroupedAVP*)val)->getImpl();
								const GroupedAVPImplDerived& gImplS =
									(const GroupedAVPImplDerived&)grpAVP->getImpl();
								gImpl = gImplS;
								return 0;
							}
							else
							{
								return -1;
							}
						}
					default               :
						return -1;
				}
			}
			count++;
		}
	}
	return -1;
} 



	void
AVPContainerDerived::DecodeAppAVP()
{
	//Decode only application specific AVPs
	if (_cmdnameObj==NULL)
	{
		//just return, don't do anything
		//isn't an error case for GenericCommand
		return;
	}
	if ((_baseMandBitMap & _cmdnameObj->GetMandBaseBitMap()) != _cmdnameObj->GetMandBaseBitMap())
	{
		//throw error
		PrintMissingMandAvp();

		UTF8String sessId, origHost, origRealm;
		getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
		getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
		getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

		CodecExceptionToApp avpMissingException(__FILE__, __LINE__,
				" Base Mandatory AVP missing in the Command",
				ITS_DIA_MISSING_AVP);
		avpMissingException.SetMissingAvpList(missingAVPCodes);
		avpMissingException.SetSessionId(sessId);
		avpMissingException.SetOriginHost(origHost);
		avpMissingException.SetOriginRealm(origRealm);

		throw avpMissingException;
	}
	unsigned int appAvpDecoded = 0; 
	//application specific avp look up
	for(int i=0; (i < _totalappBuff); i++)
	{
		if (appAVPBuffList[i] == NULL)
		{
			continue;
		}
		unsigned int avpIndex=0;
		bool fMand = false;
		unsigned int avpcode = appAVPBuffList[i]->_avpcode;
		unsigned int venId = appAVPBuffList[i]->_vendorId;
		const AttributeName* name = _cmdnameObj->GetAppAttributeObj(avpcode, venId,avpIndex, fMand);
		if (name == NULL)
		{
			//throw NoSuchAttributeException(__FILE__, __LINE__,
			//          "AVP not found in the Command with code", avpcode);
			//Exceptions shouldn't be thrown for any AVP code not found in the commandAttribute
			//just ignore the buffer, This fix is required for peer messages having extensible
			//AVP and are handled by the stack
			continue;
		}
		if (fMand)
		{
			//increment Mandatory counter
			_noOfMandAvp++;
		}
		appAvpDecoded ++;
		AVP* avpObj = name->getAvpBuilder().build(0);
		unsigned char* buffer = appAVPBuffList[i]->_buffer + appAVPBuffList[i]->_offset;
		int size = appAVPBuffList[i]->_size - appAVPBuffList[i]->_offset;
		DiaHeader& hdr = appAVPBuffList[i]->_hdr;

		try
		{
          avpObj->Decode(buffer, size, hdr);
      }
      catch(CodecExceptionToApp appExp)
      {
          UTF8String sessId, origHost, origRealm;
          std::vector<int> missingAvpList = appExp.getMissingAVPList();
          getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
          getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
          getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

          CodecExceptionToApp avpMissingException(appExp.file(), 
                                              appExp.line(),
                                              appExp.what(),
                                              appExp.errcode());

          avpMissingException.SetMissingAvpList(missingAvpList);
          avpMissingException.SetSessionId(sessId);
          avpMissingException.SetOriginHost(origHost);
          avpMissingException.SetOriginRealm(origRealm);
	  if( NULL != avpObj)
	  {
	    delete avpObj;
	    avpObj=NULL;
          }
          throw avpMissingException;
      }
      catch(...)
      {
	  if( NULL != avpObj)
	  {
	   delete avpObj;
           avpObj=NULL;
          }
          throw;
      }

      AVPContainerDerivedEntry* &entry = getAt(avpIndex);
      if(entry)
      {
         entry->add(avpObj);
      }
      else
      {
         AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry(avpObj);
         entry=avpEntry;
      }
      delete appAVPBuffList[i];
      appAVPBuffList[i] = NULL;
   }
   if ( appAvpDecoded 
   && (appAvpDecoded == _totalappBuff))
   {
     //all app avps are decoded, hence can safely delete
     free(appAVPBuffList);
     _totalappBuff = 0;
   }
   //validate mandatory app avps
   if (_noOfMandAvp != _cmdnameObj->GetNoOfAppMandAVPs())
   {
      //throw error
      PrintMissingMandAvp();      

      UTF8String sessId, origHost, origRealm;
      getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
      getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
      getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

      CodecExceptionToApp avpMissingException(__FILE__, __LINE__,
                                              "Mandatory AVP missing in the Command",
                                              ITS_DIA_MISSING_AVP);

      avpMissingException.SetMissingAvpList(missingAVPCodes);
      avpMissingException.SetSessionId(sessId);
      avpMissingException.SetOriginHost(origHost);
      avpMissingException.SetOriginRealm(origRealm);

      throw avpMissingException;
   }
}

/**
 * Added the overloaded function to check whether AVP exists at particular
 * index. (Partial fix for Bridgewater ticket 2080 )
 */
bool
AVPContainerDerived::containsExtra(unsigned int index) const
{

    int totalIndex = _totalContEntries + index;
    if (totalIndex < _totalContEntries ||
        totalIndex >= (_totalContEntries + _dictEntries))
    {
        return false;
    }
    else
    {
        AVPContainerDerivedEntry* entry = avpContDerivedEntryList[totalIndex];
        if (entry)
        {
            const AVP* avp = entry->getAt(0);
            if (avp != NULL )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}


#if 0
Integer32Parser *int32Parser = (Integer32Parser*) &Integer32Parser();
Integer64Parser *int64Parser = new Integer64Parser();
OctetStringParser *octetStringParser = new OctetStringParser();
UTFStringParser *utf8StringParser = new OctetStringParser();
AddressParser *addressParser = new AddressParser();
URIParser     *uriParser = new URIParser();
IPFilterRuleParser *ipFilterRuleParser = new IPFilterRuleParser();
Float32Parser *float32Parser = new Float32Parser();
Float64Parser *float64Parser = new Float64Parser();
#endif

Integer32Parser int32Parser;
Integer64Parser int64Parser;
OctetStringParser octetStringParser;
UTF8StringParser utf8StringParser;
AddressParser addressParser;
URIParser     uriParser; 
IPFilterRuleParser ipFilterRuleParser; 
Float32Parser float32Parser;
Float64Parser float64Parser;


#if 0
template<typename T, ValueDiscriminator D>
ParserBase* DerivedAVPImplDerived<T,D>::getParseType()
{
   switch(D)
   {
      case Integer32Type  :
      case Unsigned32Type :
      case TimeType       :
      case EnumeratedType :
           return new Integer32Parser();

      case Integer64Type  :
      case Unsigned64Type :
           return new Integer64Parser();

      case OctetStringType :
      case IdentityType    :
           return new OctetStringParser();

      case UTF8StringType :
           return new UTF8StringParser();

      case AddressType    :
           return new AddressParser();

      case URIType        :
           return new URIParser();
      case IPFilterRuleType  :
           return new IPFilterRuleParser();
      case Float32Type     :
           return new Float32Parser();
      case Float64Type     :
           return new Float64Parser();
      default:
           return new OctetStringParser();
   }
}
#endif 

template<typename T, ValueDiscriminator D>
ParserBase* DerivedAVPImplDerived<T,D>::getParseType()
{
   switch(D)
   {
      case Integer32Type  :
      case Unsigned32Type :
      case TimeType       :
      case EnumeratedType :
           return &int32Parser;

      case Integer64Type  :
      case Unsigned64Type :
           return &int64Parser;

      case OctetStringType :
      case IdentityType    :
           return &octetStringParser;

      case UTF8StringType :
           return &utf8StringParser;

      case AddressType    :
           return &addressParser;

      case URIType        :
           return &uriParser;
      case IPFilterRuleType  :
           return &ipFilterRuleParser;
      case Float32Type     :
           return &float32Parser;
      case Float64Type     :
           return &float64Parser;
      default:
           return &octetStringParser;
   }
}
 
template<typename T, ValueDiscriminator D>
int DerivedAVPImplDerived<T,D>::Decode(unsigned char*& buff, unsigned int size)
{
    ParserBase* ptype = getParseType();
    int rc = ptype->Decode(buff, size, &_val);
    buff +=size;
    //delete ptype;
    return rc;
}
 
template<typename T, ValueDiscriminator D>
int DerivedAVPImplDerived<T,D>::Encode(String& str, const AttributeName& _name)
{
   unsigned int oldLen = str.length();
   ParserBase* ptype = getParseType();
   char temp[4]="";
   AppToData(temp, _name.GetCode());
   str.append(temp, 4);//avp code
   memset(temp, 0, 4);
   temp[0] |= (_name.vendorId()  ? 0x80 : 0x00);
   temp[0] |= (_name.ifMandatory()  ? 0x40 : 0x00);
   temp[0] |= (_name.ifEncrypt()  ? 0x20 : 0x00);
   str.append(temp, 4);//avp flag rules and length =0
   if(_name.vendorId())
   {
      AppToData(temp, _name.vendorId());
      str.append(temp, 4);//vendor id
   }
   int rc = ptype->Encode(str, &_val);
   unsigned int avpLen = str.length() - oldLen;
   AppToData(temp, avpLen, 3);
   //str.assign(temp, oldLen+5, 3);
   str.at(oldLen+5)=temp[0];
   str.at(oldLen+6)=temp[1];
   str.at(oldLen+7)=temp[2];
   avpLen = (avpLen %4);
   if(avpLen)
   {
      memset(temp, 0, 3);
      str.append(temp, 4-avpLen);
   }
   //delete ptype;
   return rc;
}

GroupedAVPImpl*
GroupedAVPImpl::acquire(const AttributeName* nameObj) 
{
    return new GroupedAVPImplDerived(nameObj);
}

GroupedAVPImpl* 
GroupedAVPImplDerived::createCopy() const
{
   return new GroupedAVPImplDerived(*this);
}

GroupedAVPImplDerived::~GroupedAVPImplDerived()
{
   unsigned int& instCntr = avpContPtrObj->getInstCnt();
   if (instCntr)
   {
      instCntr--;
   }
   else
   {
      delete avpContPtrObj;
   }
}

GroupedAVPImplDerived::GroupedAVPImplDerived(const GroupedAVPImplDerived& implObj):avpContPtrObj(implObj.avpContPtrObj)
{
   avpContPtrObj->setInstCnt();
}

GroupedAVPImplDerived&
GroupedAVPImplDerived::operator =(const GroupedAVPImplDerived& cImpl)
{
   unsigned int& instCntr = avpContPtrObj->getInstCnt();
   if (instCntr)
   {
      instCntr--;
   }
   else
   {
      delete avpContPtrObj;
   }
   avpContPtrObj = cImpl.avpContPtrObj;
   avpContPtrObj->setInstCnt();
   return *this;
}

int
GroupedAVPImplDerived::Decode(unsigned char*& inputBuff, unsigned int size, DiaHeader& hdr)
{
   unsigned char* buff = (unsigned char*)inputBuff;
   unsigned char* end    = (unsigned char*)(inputBuff+size);
   AVPContainerDerived& avpContObj = (AVPContainerDerived&)*avpContPtrObj;
   GroupedAttributeName& GroupedObj = (GroupedAttributeName&)avpContObj.GetNameObj();
   while((unsigned long)(buff+8) <= (unsigned long)end)
   {
      unsigned int avpCode = DataToApp(buff);
      unsigned int vendorId = 0;
      buff+=4;
      unsigned int avpLen = DataToApp(buff+1, 3);

      UTF8String sessId, origHost, origRealm;

      if((unsigned long)(buff+avpLen-4) > (unsigned long)end)
      {
         CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length", 
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

         avpLenErr.SetSessionId(sessId);
         avpLenErr.SetOriginHost(origHost);
         avpLenErr.SetOriginRealm(origRealm);
         avpLenErr.setGroupedAvpError(true);
         avpLenErr.setGroupedAvpCode(GroupedObj.GetAvpCode());
         throw avpLenErr;
      }
      if(*buff & 0x80)
      {
          if (avpLen < 12)
          {
             CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

             avpLenErr.SetSessionId(sessId);
             avpLenErr.SetOriginHost(origHost);
             avpLenErr.SetOriginRealm(origRealm);
             avpLenErr.setGroupedAvpError(true);
             avpLenErr.setGroupedAvpCode(GroupedObj.GetAvpCode());
             throw avpLenErr;
          }
         //with vendor id;
         buff +=4;
         avpLen -=4;
         vendorId = DataToApp(buff);
      }
      else
      {
          if (avpLen < 8)
          {
              CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);
         
              avpLenErr.SetSessionId(sessId);
              avpLenErr.SetOriginHost(origHost);
              avpLenErr.SetOriginRealm(origRealm);
              avpLenErr.setGroupedAvpError(true);
              avpLenErr.setGroupedAvpCode(GroupedObj.GetAvpCode());
              throw avpLenErr;
          }

      }
      buff +=4;
      avpLen -=8;
      std::map<unsigned int, AttributeName*>::iterator it = GroupedObj.GetMandAttMap().find(avpCode);
      if(it != GroupedObj.GetMandAttMap().end())
      {
         //only Mandatory AVPs
         AttributeName* nameObj = (*it).second;
         unsigned int avpIndex = nameObj->GetIndex();
         AVP* avpObj = nameObj->getAvpBuilder().build(0);
         avpObj->Decode(buff, avpLen, hdr);
         if(avpContObj[avpIndex])
         {
            avpContObj[avpIndex]->add(avpObj);
         }
         else
         {
            AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry(avpObj);
            avpContObj[avpIndex]=avpEntry;
            avpContObj.SetAppMandCounter();
         }
      }
      else if((it = GroupedObj.GetOptAttMap().find(avpCode)) != GroupedObj.GetOptAttMap().end())
      {
         //only optional AVPs
         AttributeName* nameObj = (*it).second;
         unsigned int avpIndex = nameObj->GetIndex();
         AVP* avpObj = nameObj->getAvpBuilder().build(0);
         avpObj->Decode(buff, avpLen, hdr);
         if(avpContObj[avpIndex])
         {
            avpContObj[avpIndex]->add(avpObj);
         }
         else
         {
            AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry(avpObj);
            avpContObj[avpIndex]=avpEntry;
         }
      }
      else 
      {
         //decode extensible AVPs (enable decoding failed typed AVP)
         const AttributeName* name = CommandAttribute::findAttribute(hdr.appId, 
                                                  hdr.code, avpCode, vendorId);
         if (name )
         {
            AVP* avpObj = name->getAvpBuilder().build(0);
            avpObj->Decode(buff, avpLen, hdr);
            avpContObj.add(*name, avpObj);
         }
         else
         {
            //if fails, just skip the buffer
            buff +=avpLen;
         }
      }
      avpLen = (avpLen % 4);
      if (avpLen)
      {
         buff +=(4-avpLen);
      }
   }
   //align buffer to word byte
   inputBuff +=size;
   size = (size % 4);
   if(size)
   {
      inputBuff +=(4-size);
   }
   if(avpContObj.validateMand() == false)
   {
      //mandatory AVP missing
      //throw exception
      avpContObj.PrintMissingMandAvp();
      throw CodecExceptionToApp(__FILE__, __LINE__,"GroupedType AVP Error:Mandatory AVP missing",
                                             avpContObj.missingAVPCodes, ITS_DIA_MISSING_AVP);
   }
   return 0;
}

int
GroupedAVPImplDerived::Encode(String& str)
{
    AVPContainerDerived& avpContObj = (AVPContainerDerived&)*avpContPtrObj;
    const AttributeName &_name = avpContObj.GetNameObj();
    unsigned int oldLen = str.length();
    char temp[4]="";
    AppToData(temp, _name.GetCode());
    str.append(temp, 4);//avp code
    memset(temp, 0, 4);
    temp[0] |= (_name.vendorId()  ? 0x80 : 0x00);
    temp[0] |= (_name.ifMandatory()  ? 0x40 : 0x00);
    temp[0] |= (_name.ifEncrypt()  ? 0x20 : 0x00);
    str.append(temp, 4);//avp flag rules and length =0
    if(_name.vendorId())
    {
       AppToData(temp, _name.vendorId());
       str.append(temp, 4);//vendor id
    }
    //encode AVP
    int totalAVPs = avpContObj.GetNoOfContEntry()+avpContObj.GetNoOfDictEntry();
    for(int i=0; i < totalAVPs;++i)
    {
       if(avpContObj[i])
       {
          avpContObj[i]->Encode(str);
       }
    }
    unsigned int avpLen = str.length() - oldLen;
    AppToData(temp, avpLen, 3);
    //str.assign(temp, oldLen+5, 3);
    str.at(oldLen+5)=temp[0];
    str.at(oldLen+6)=temp[1];
    str.at(oldLen+7)=temp[2];
    avpLen = (avpLen %4);
    if(avpLen)
    {
       memset(temp, 0, 3);
       str.append(temp, 4-avpLen);
    }
    return 0;
}

template <>
DerivedAVPImpl<OctetString, OctetStringType> *DerivedAVPImpl<OctetString, OctetStringType>::acquire(const OctetString &value){
    return new DerivedAVPImplDerived<OctetString, OctetStringType>(value);
}

template <>
DerivedAVPImpl<OctetString, OctetStringType> *DerivedAVPImpl<OctetString, OctetStringType>::acquire()
{
    return new DerivedAVPImplDerived<OctetString, OctetStringType>();
}

template <>
DerivedAVPImpl<Integer32, Integer32Type> *DerivedAVPImpl<Integer32, Integer32Type>::acquire(const Integer32 &value) 
{
    return new DerivedAVPImplDerived<Integer32, Integer32Type>(value);
}

template <>
DerivedAVPImpl<Integer32, Integer32Type> *DerivedAVPImpl<Integer32, Integer32Type>::acquire() 
{
    return new DerivedAVPImplDerived<Integer32, Integer32Type>();
}

template <>
DerivedAVPImpl<Integer64, Integer64Type> *DerivedAVPImpl<Integer64, Integer64Type>::acquire(const Integer64 &value) 
{
    return new DerivedAVPImplDerived<Integer64, Integer64Type>(value);
}

template <>
DerivedAVPImpl<Integer64, Integer64Type> *DerivedAVPImpl<Integer64, Integer64Type>::acquire() 
{
    return new DerivedAVPImplDerived<Integer64, Integer64Type>();
}

template <>
DerivedAVPImpl<Unsigned32, Unsigned32Type> *DerivedAVPImpl<Unsigned32, Unsigned32Type>::acquire(const Unsigned32 &value) 
{
    return new DerivedAVPImplDerived<Unsigned32, Unsigned32Type>(value);
}

template <>
DerivedAVPImpl<Unsigned32, Unsigned32Type> *DerivedAVPImpl<Unsigned32, Unsigned32Type>::acquire() 
{
    return new DerivedAVPImplDerived<Unsigned32, Unsigned32Type>();
}

template <>
DerivedAVPImpl<Unsigned64, Unsigned64Type> *DerivedAVPImpl<Unsigned64, Unsigned64Type>::acquire(const Unsigned64 &value) 
{
    return new DerivedAVPImplDerived<Unsigned64, Unsigned64Type>(value);
}

template <>
DerivedAVPImpl<Unsigned64, Unsigned64Type> *DerivedAVPImpl<Unsigned64, Unsigned64Type>::acquire() 
{
    return new DerivedAVPImplDerived<Unsigned64, Unsigned64Type>();
}

/**
 * Added the definitions for Float32 acquire overloaded function.
 */
template <>
DerivedAVPImpl<Float32, Float32Type> *DerivedAVPImpl<Float32, Float32Type>::acquire(const Float32 &value)
{
    return new DerivedAVPImplDerived<Float32, Float32Type>(value);
}

template <>
DerivedAVPImpl<Float32, Float32Type> *DerivedAVPImpl<Float32, Float32Type>::acquire()
{
    return new DerivedAVPImplDerived<Float32, Float32Type>();
}

/**
 * Added the definitions for Float64 acquire overloaded function.
 */
template <>
DerivedAVPImpl<Float64, Float64Type> *DerivedAVPImpl<Float64, Float64Type>::acquire(const Float64 &value)
{
    return new DerivedAVPImplDerived<Float64, Float64Type>(value);
}

template <>
DerivedAVPImpl<Float64, Float64Type> *DerivedAVPImpl<Float64, Float64Type>::acquire()
{
    return new DerivedAVPImplDerived<Float64, Float64Type>();
}

template <>
DerivedAVPImpl<Address, AddressType> *DerivedAVPImpl<Address, AddressType>::acquire(const Address &value) 
{
    return new DerivedAVPImplDerived<Address, AddressType>(value);
}

template <>
DerivedAVPImpl<Address, AddressType> *DerivedAVPImpl<Address, AddressType>::acquire() 
{
    return new DerivedAVPImplDerived<Address, AddressType>();
}

template <>
DerivedAVPImpl<Time, TimeType> *DerivedAVPImpl<Time, TimeType>::acquire(const Time &value) 
{
    return new DerivedAVPImplDerived<Time, TimeType>(value);
}

template <>
DerivedAVPImpl<Time, TimeType> *DerivedAVPImpl<Time, TimeType>::acquire() 
{
    return new DerivedAVPImplDerived<Time, TimeType>();
}

template <>
DerivedAVPImpl<UTF8String, UTF8StringType> *DerivedAVPImpl<UTF8String, UTF8StringType>::acquire(const UTF8String &value) 
{
    return new DerivedAVPImplDerived<UTF8String, UTF8StringType>(value);
}

template <>
DerivedAVPImpl<UTF8String, UTF8StringType> *DerivedAVPImpl<UTF8String, UTF8StringType>::acquire() 
{
    return new DerivedAVPImplDerived<UTF8String, UTF8StringType>();
}

template <>
DerivedAVPImpl<Identity, IdentityType> *DerivedAVPImpl<Identity, IdentityType>::acquire(const Identity &value) 
{
    return new DerivedAVPImplDerived<Identity, IdentityType>(value);
}

template <>
DerivedAVPImpl<Identity, IdentityType> *DerivedAVPImpl<Identity, IdentityType>::acquire() 
{
    return new DerivedAVPImplDerived<Identity, IdentityType>();
}

template <>
DerivedAVPImpl<URI, URIType> *DerivedAVPImpl<URI, URIType>::acquire(const URI &value) 
{
    return new DerivedAVPImplDerived<URI, URIType>(value);
}

template <>
DerivedAVPImpl<URI, URIType> *DerivedAVPImpl<URI, URIType>::acquire() 
{
    return new DerivedAVPImplDerived<URI, URIType>();
}

template <>
DerivedAVPImpl<IPFilterRule, IPFilterRuleType> *DerivedAVPImpl<IPFilterRule, IPFilterRuleType>::acquire(const IPFilterRule &value) 
{
    return new DerivedAVPImplDerived<IPFilterRule, IPFilterRuleType>(value);
}

template <>
DerivedAVPImpl<IPFilterRule, IPFilterRuleType> *DerivedAVPImpl<IPFilterRule, IPFilterRuleType>::acquire() 
{
    return new DerivedAVPImplDerived<IPFilterRule, IPFilterRuleType>();
}

template <>
DerivedAVPImpl<Enumerated, EnumeratedType> *DerivedAVPImpl<Enumerated, EnumeratedType>::acquire(const Enumerated &value) 
{
    return new DerivedAVPImplDerived<Enumerated, EnumeratedType>(value);
}

template <>
DerivedAVPImpl<Enumerated, EnumeratedType> *DerivedAVPImpl<Enumerated, EnumeratedType>::acquire() 
{
    return new DerivedAVPImplDerived<Enumerated, EnumeratedType>();
}




void GroupedAVPImpl::release(GroupedAVPImpl *grouped) {
#if !defined (__SUNPRO_CC)
DBG_LOG((VENDOR) << "GroupedAVPImpl::release: deleting GroupedAVPAdapter 0x" << std::hex << (unsigned long)grouped << std::dec);
#endif
    delete grouped;
}


void CommandImpl::release(CommandImpl *command) {
#if !defined (__SUNPRO_CC)
DBG_LOG((VENDOR) << "CommandImpl::release: deleting CommandAdapter @ 0x" << std::hex << (unsigned long)command << std::dec);
#endif
    delete command;
}

CommandImpl*
CommandImpl::acquire(bool request, bool proxyable, bool error, bool retrans, 
CommandCode code, ApplicationId appId) 
{
   return new CommandImplDerived(request, proxyable, error, retrans, code, appId);
}

CommandImplDerived::~CommandImplDerived()
{
   unsigned int& instCntr = avpContPtrObj->getInstCnt();
   if (instCntr)
   {
      instCntr--;
   }
   else
   {
      delete avpContPtrObj;
   }
}

CommandImpl* 
CommandImplDerived::createCopy() const
{
   return new CommandImplDerived(*this);
}


CommandImpl*
CommandImpl::decode(const unsigned char *buffer, int size, const CommandAttribute* descObj) 
{
   return new CommandImplDerived(buffer, size, descObj);
}


int
CommandImplDerived::encode(unsigned char * &buffer, int& size) 
{
   try
   {
      size=0;
      //std::string strBuff="";
      String strBuff="";
      AVPContainerDerived& avpContObj = (AVPContainerDerived&)*avpContPtrObj;
      //check for Mandatory AVP
      if(avpContObj.validateMand() == false)
      {
          avpContObj.PrintMissingMandAvp();
          //throw CodecException(__FILE__, __LINE__,"Mandatory AVP Missing", ITS_DIA_MISSING_AVP);
          throw CodecExceptionToApp(__FILE__, __LINE__," Mandatory AVP Missing",
                                    avpContObj.missingAVPCodes, ITS_DIA_MISSING_AVP);
      }
      char temp[4]="";
      temp[0] = DIA_VERSION;
      strBuff.append(temp, 4);//length 3 bytes, intilized to 0
      temp[0]=0;
      temp[0] |= (hdr.flags.r  ? 0x80 : 0x00);
      temp[0] |= (hdr.flags.p  ? 0x40 : 0x00);
      temp[0] |= (hdr.flags.e  ? 0x20 : 0x00);
      temp[0] |= (hdr.flags.t  ? 0x10 : 0x00);
      AppToData(&temp[1], hdr.code, 3);
      strBuff.append(temp, 4);//code,flags
      AppToData(temp, hdr.appId, 4);
      strBuff.append(temp, 4);//app id
      AppToData(temp, hdr.hh, 4);
      strBuff.append(temp, 4);//hop id
      AppToData(temp, hdr.ee, 4);
      strBuff.append(temp, 4);//end -end id

      //encode AVP
      int totalAVPs = avpContObj.GetNoOfContEntry() + avpContObj.GetNoOfDictEntry();
      for(int i=0; i < totalAVPs;++i)
      {
         if(avpContObj[i])
         {
            avpContObj[i]->Encode(strBuff);
         }
      }

      //encode if any app.specific AVPs
      avpContObj.EncodeAppAVP(strBuff);
      //buffer = new unsigned char[strBuff.length()];
      buffer =  (unsigned char*) strBuff.c_str();
      //memcpy(buffer, (unsigned char*)strBuff.c_str(), strBuff.length());
      AppToData((char*)(buffer+1), strBuff.length(), 3);//update length
      size = strBuff.length();
      
   }
   catch(...)
   {
      buffer = NULL;
      size   = 0;
   }
   return 0;
}


CommandImplDerived::CommandImplDerived(Command* cmd)
{
   CommandImplDerived& cImpl = (CommandImplDerived&)cmd->getImpl();
   copy(cImpl);
}

CommandImplDerived::CommandImplDerived(const CommandImplDerived& cImpl):
hdr(cImpl.hdr),avpContPtrObj(cImpl.avpContPtrObj)
{
   avpContPtrObj->setInstCnt();
  _sessIndex             = cImpl._sessIndex;
  _clientId              = cImpl._clientId;
  _userData              = cImpl._userData;
  _storageSpaceAvailable = cImpl._storageSpaceAvailable;
  _lastRecordInStorage   = cImpl._lastRecordInStorage;
  _enBuf                 = cImpl._enBuf;
  _enBufLen              = cImpl._enBufLen;
}

void
CommandImplDerived::copy(const CommandImplDerived& cImpl)
{
   avpContPtrObj         = cImpl.avpContPtrObj;
   hdr                   = cImpl.hdr;
  _sessIndex             = cImpl._sessIndex;
  _clientId              = cImpl._clientId;
  _userData              = cImpl._userData;
  _storageSpaceAvailable = cImpl._storageSpaceAvailable;
  _lastRecordInStorage   = cImpl._lastRecordInStorage;
  _enBuf                 = cImpl._enBuf;
  _enBufLen              = cImpl._enBufLen;
}

void
CommandImplDerived::SetCmdAttribute(const CommandAttribute* cmdnameObj)
{
   avpContPtrObj->SetCmdObj(cmdnameObj);
}

void 
CommandImplDerived::validateApp(const CommandAttribute* descObj)
{
   avpContPtrObj->SetCmdObj(descObj);
   avpContPtrObj->DecodeAppAVP();
}

CommandImplDerived::CommandImplDerived(bool request, bool proxyable, bool error, bool retrans, 
CommandCode code, ApplicationId appId)
{
  //To do
  hdr.ver = 1;
  hdr.length = 0;
  hdr.flags.r = request;
  hdr.flags.p = proxyable;
  hdr.flags.e = error;
  hdr.flags.t = retrans;
  hdr.code    = code;
  hdr.appId   = appId;
  hdr.hh      =0;
  hdr.ee      =0;
  avpContPtrObj = new AVPContainerDerived();
  _sessIndex =0;
  _clientId  =0;
  _userData  = NULL;
  _storageSpaceAvailable = true;
  _lastRecordInStorage   = false;
  _enBuf     = NULL;
  _enBufLen = 0;
}

CommandImplDerived::CommandImplDerived(const unsigned char *inputBuffer, int size, const CommandAttribute* descObj)
{
  _sessIndex =0;
  _clientId  =0;
  _userData  = NULL;
  _storageSpaceAvailable = true;
  _lastRecordInStorage   = false;
  _enBuf     = NULL;
  _enBufLen = 0;

  if (inputBuffer == NULL || size <= 0)
  {
     throw CodecException(__FILE__, __LINE__,"Wrong Command length",ITS_DIA_INVALID_MSG_LENGTH);
  }

  avpContPtrObj = new AVPContainerDerived();
  AVPContainerDerived& avpContObj = (AVPContainerDerived&)*avpContPtrObj;
  avpContObj.SetCmdObj(descObj);
  unsigned char* buffer = (unsigned char *)inputBuffer;
  unsigned char* end    = (unsigned char*)(inputBuffer+size);
  if((unsigned long)(buffer+20) < (unsigned long)end)
  {
     hdr.ver = DataToApp(buffer, 1);
     hdr.length = DataToApp(&buffer[1], 3);
     hdr.flags.r=((buffer[4] & 0x80) ? 1 : 0);
     hdr.flags.p=((buffer[4] & 0x40) ? 1 : 0);
     hdr.flags.e=((buffer[4] & 0x20) ? 1 : 0);
     hdr.flags.t=((buffer[4] & 0x10) ? 1 : 0);
     hdr.code = DataToUApp(&buffer[5], 3);
     hdr.appId = DataToApp(&buffer[8]);
     hdr.hh = DataToApp(&buffer[12]);
     hdr.ee = DataToApp(&buffer[16]);

     buffer +=20;
     //point to the AVP begining
  }
  else
  {
     if (avpContPtrObj)
         delete avpContPtrObj;
     throw CodecException(__FILE__, __LINE__,"Wrong Command Header length",ITS_DIA_INVALID_MSG_LENGTH);
  }
  //check if hdr length is proper &
  //avp length is atleast 8 bytes
  if(hdr.length > size)
  {
     if (avpContPtrObj)
         delete avpContPtrObj;
     throw CodecException(__FILE__, __LINE__,"Wrong Command Header length",ITS_DIA_INVALID_MSG_LENGTH);
  }
  size   -=20;

  //To do decode AVPs
  std::map<unsigned int, AttributeName*>::iterator it;
  CommandAttribute* cmdName = (CommandAttribute*)avpContObj.GetCmdObj();
  unsigned int avpIndex=0;
  bool fMand = false;
  while((unsigned long)(buffer+8) <= (unsigned long)end)//parse AVPs
   {
     const AttributeName* name = NULL;
     unsigned char* startBuff = buffer;
     unsigned int offset      = 8;
     unsigned int avpCode = DataToApp(buffer);
     buffer+=4;
     unsigned int avpLen = DataToApp(buffer+1, 3);
     unsigned int vendorId = 0;
     if((unsigned long)(buffer+avpLen-4) > (unsigned long)end)
     {

        
        if (avpContPtrObj)
        {
            delete avpContPtrObj;
            avpContPtrObj = NULL;
        }
        UTF8String sessId, origHost, origRealm;
        getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
        getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
        getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

        CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

        avpLenErr.SetSessionId(sessId);
        avpLenErr.SetOriginHost(origHost);
        avpLenErr.SetOriginRealm(origRealm);
        throw avpLenErr;
     }
     if(*buffer & 0x80)
     {
       //with vendor id;
       //Added check to see avpLen should not be corrupt for Vendor-Specific AVPs
       if (avpLen < 12)
       {
           if (avpContPtrObj)
           {
                delete avpContPtrObj;
                avpContPtrObj = NULL;
           }
           UTF8String sessId, origHost, origRealm;
           getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
           getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
           getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

           CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

           avpLenErr.SetSessionId(sessId);
           avpLenErr.SetOriginHost(origHost);
           avpLenErr.SetOriginRealm(origRealm);
           
           throw avpLenErr;
       }

       buffer +=4;
       avpLen -=4;
       offset +=4;
       vendorId = DataToApp(buffer);
       //vendor specfic AVPs
       it = AttributeCodeMap::AttributeMap.end();
     }
     else
     {
       //Added check to see avpLen should not be corrupt.
       if (avpLen < 8)
       {
           if (avpContPtrObj)
           {
                delete avpContPtrObj;
                avpContPtrObj = NULL;
            }
           UTF8String sessId, origHost, origRealm;
           getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
           getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
           getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

           CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

           avpLenErr.SetSessionId(sessId);
           avpLenErr.SetOriginHost(origHost);
           avpLenErr.SetOriginRealm(origRealm);

           throw avpLenErr;
       }
       //IETF defined AVPs including base AVPs
       it = AttributeCodeMap::AttributeMap.find(avpCode);
     }
     buffer +=4;
     avpLen -=8;

     if(it != AttributeCodeMap::AttributeMap.end())
     {
       //only BaseAVPs
       name = (*it).second;
       avpIndex = name->GetIndex();
     }
     else if (cmdName)
     {
       //application specific avp look up
       name = cmdName->GetAppAttributeObj(avpCode, vendorId, avpIndex, fMand);
     }
     if (name)
     {
       AVP* avpObj = name->getAvpBuilder().build(0);
       avpObj->Decode(buffer, avpLen, hdr);
       if(avpContObj[avpIndex])
       {
          avpContObj[avpIndex]->add(avpObj);
          //multiOccurAVPCodes.push_back(avpCode);
       }
       else
       {
          AVPContainerDerivedEntry* avpEntry = new AVPContainerDerivedEntry(avpObj);
          avpContObj[avpIndex]=avpEntry;
          if ( name->ifBase())
          {
             avpContObj.SetBaseMandBitMap(avpIndex);
          }
          else if (fMand)
          {
             avpContObj.SetAppMandCounter();
          }
       }
     }
     else
     {
         //dictionary AVPs are decoded in static setup only
         //application specific AVPs //Extensible AVPs
         avpContObj.SetAppAVPBuff(startBuff, avpLen+offset, offset, avpCode,
                                                         vendorId, hdr);
         buffer +=avpLen;
     }
     //align buffer to word byte
     avpLen = (avpLen % 4);
     if(avpLen)
     {
        buffer +=(4-avpLen);
     }

     if (buffer < startBuff)
     {
         if (avpContPtrObj)
        {
         delete avpContPtrObj;
         avpContPtrObj = NULL;
        }
         UTF8String sessId, origHost, origRealm;
         getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
         getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
         getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

         CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

         avpLenErr.SetSessionId(sessId);
         avpLenErr.SetOriginHost(origHost);
         avpLenErr.SetOriginRealm(origRealm);

         throw avpLenErr;
     }

  }
  if(avpContObj.validateMand() == false)
  {
     avpContObj.PrintMissingMandAvp();
      UTF8String sessId, origHost, origRealm;
      getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
      getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
      getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

      CodecExceptionToApp avpMissingException(__FILE__, __LINE__,
                                              "Mandatory AVP missing",
                                              ITS_DIA_MISSING_AVP);

      avpMissingException.SetMissingAvpList(avpContObj.missingAVPCodes);
      avpMissingException.SetSessionId(sessId);
      avpMissingException.SetOriginHost(origHost);
      avpMissingException.SetOriginRealm(origRealm);
     //fix need to free after SetMissingAvpList
     if (avpContPtrObj)
        {
            delete avpContPtrObj;
            avpContPtrObj = NULL;
        }
     //End of changes for CID 11720
      throw avpMissingException;
  }
  /** Commented after discussing with Rajesh */
#if 0
  if ((hdr.code != 257) && !multiOccurAVPCodes.empty())
  {
      UTF8String sessId, origHost, origRealm;
      getAvpValue(SESSID_AVP_CODE, &sessId, UTF8StringType, 0);
      getAvpValue(OHOST_AVP_CODE, &origHost, IdentityType, 0);
      getAvpValue(OREALM_AVP_CODE, &origRealm, IdentityType, 0);

      CodecExceptionToApp avpMultiOccurExcep(__FILE__, __LINE__,
                                              "Multiple Occurrence of AVP", 
                                               ITS_DIA_AVP_MULTI_OCCUR);

      avpMultiOccurExcep.SetMultiOccurrenceAvpList(multiOccurAVPCodes);
      avpMultiOccurExcep.SetSessionId(sessId);
      avpMultiOccurExcep.SetOriginHost(origHost);
      avpMultiOccurExcep.SetOriginRealm(origRealm);
      avpMultiOccurExcep.setCmdCode(hdr.code);

      throw avpMultiOccurExcep;
  }
#endif
}

int
CommandImplDerived::getAvpValue(unsigned int avpCode, void* val, ValueDiscriminator D,
                                unsigned int venId) const
{
   if (avpContPtrObj == NULL)
   {
      return -1;
   }
   return avpContPtrObj->getAvpValue(avpCode,val,D,venId);
}

int
CommandImplDerived::getAvpValue(unsigned int avpCode,unsigned int index, void* val, ValueDiscriminator D,
                                unsigned int venId) const
{
   if (avpContPtrObj == NULL)
   {
      return -1;
   }
   return avpContPtrObj->getAvpValue(avpCode,index,val,D,venId);
}

int
CommandImplDerived::getAvpCount(unsigned int avpCode, unsigned int venId)
{
   if (avpContPtrObj == NULL)
   {
      return -1;
   }
   return avpContPtrObj->getAvpCount(avpCode,venId);
}

const AttributeName& getAttributeObj(unsigned int avpCode, unsigned int venId)
{
   const AttributeName* name = DictAttributeList::_dictAttributeList.getAttribute(avpCode, venId);
   if (name)
   {
      return *name;
   }
   return AttributeName::AVP;
}


OctetStringAvp::OctetStringAvp(unsigned int avpCode, unsigned int venId, const OctetString& value):
DerivedAVP<OctetString, OctetStringType>(getAttributeObj(avpCode, venId), value){}

Integer32Avp::Integer32Avp(unsigned int avpCode, unsigned int venId, const Integer32& value):
DerivedAVP<Integer32, Integer32Type>(getAttributeObj(avpCode, venId), value){}

Integer64Avp::Integer64Avp(unsigned int avpCode, unsigned int venId, const Integer64& value):
DerivedAVP<Integer64, Integer64Type>(getAttributeObj(avpCode, venId), value){}

Unsigned32Avp::Unsigned32Avp(unsigned int avpCode, unsigned int venId, const Unsigned32& value):
DerivedAVP<Unsigned32, Unsigned32Type>(getAttributeObj(avpCode, venId), value){}

Unsigned64Avp::Unsigned64Avp(unsigned int avpCode, unsigned int venId, const Unsigned64& value):
DerivedAVP<Unsigned64, Unsigned64Type>(getAttributeObj(avpCode, venId), value){}

/**
 * Added definition of Constructors for Float32Avp Class
 */
Float32Avp::Float32Avp(unsigned int avpCode, unsigned int venId, const Float32& value):
DerivedAVP<Float32, Float32Type>(getAttributeObj(avpCode, venId), value){}

/**
 * Added definition of Constructors for Float64Avp Class
 */
Float64Avp::Float64Avp(unsigned int avpCode, unsigned int venId, const Float64& value):
DerivedAVP<Float64, Float64Type>(getAttributeObj(avpCode, venId), value){}


AddressAvp::AddressAvp(unsigned int avpCode, unsigned int venId, const Address& value):
DerivedAVP<Address, AddressType>(getAttributeObj(avpCode, venId), value){}

TimeAvp::TimeAvp(unsigned int avpCode, unsigned int venId, const Time& value):
DerivedAVP<Time, TimeType>(getAttributeObj(avpCode, venId), value){}

UTF8StringAvp::UTF8StringAvp(unsigned int avpCode, unsigned int venId, const UTF8String& value):
DerivedAVP<UTF8String, UTF8StringType>(getAttributeObj(avpCode, venId), value){}

IdentityAvp::IdentityAvp(unsigned int avpCode, unsigned int venId, const Identity& value):
DerivedAVP<Identity, IdentityType>(getAttributeObj(avpCode, venId), value){}

URIAvp::URIAvp(unsigned int avpCode, unsigned int venId, const URI& value):
DerivedAVP<URI, URIType>(getAttributeObj(avpCode, venId), value){}

IPFilterRuleAvp::IPFilterRuleAvp (unsigned int avpCode, unsigned int venId, const IPFilterRule& value):
DerivedAVP<IPFilterRule, IPFilterRuleType>(getAttributeObj(avpCode, venId), value){}

EnumeratedAvp::EnumeratedAvp(unsigned int avpCode, unsigned int venId, const Enumerated& value):
DerivedAVP<Enumerated, EnumeratedType>(getAttributeObj(avpCode, venId), value){}

DerivedGroupedAVP::DerivedGroupedAVP(unsigned int avpCode, unsigned int venId):
GroupedAVP(getAttributeObj(avpCode, venId)){}

PayloadAVP::PayloadAVP():GroupedAVP(AttributeName::AVP){}

int
PayloadAVP::Decode(unsigned char*& inputBuff, unsigned int size)
{
      unsigned char* buff = (unsigned char*)inputBuff;
      unsigned char* end    = (unsigned char*)(inputBuff+size);
      DataToAppToData <unsigned int> tempObj;
      AVPContainerDerived& avpContObj = (AVPContainerDerived&)getContainer();
      while((unsigned long)(buff+8) <= (unsigned long)end)
      {
         unsigned int avpCode = tempObj.DataToApp(buff);
         unsigned int vendorId = 0;
         buff+=4;
         unsigned int avpLen = tempObj.DataToApp(buff+1, 3);
         if((unsigned long)(buff+avpLen-4) > (unsigned long)end)
         {
             UTF8String sessId, origHost, origRealm;

             CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

             avpLenErr.SetSessionId(sessId);
             avpLenErr.SetOriginHost(origHost);
             avpLenErr.SetOriginRealm(origRealm);
             throw avpLenErr;
         }
         if(*buff & 0x80)
         {
           //with vendor id;
           buff +=4;
           avpLen -=4;
           vendorId = tempObj.DataToApp(buff);
         }
         buff +=4;
         avpLen -=8;

        //decode extensible AVPs (enable decoding failed typed AVP)
        const AttributeName* name = DictAttributeList::_dictAttributeList.getAttribute(avpCode, vendorId);
        if (name )
        {
           AVP* avpObj = name->getAvpBuilder().build(0);
           DiaHeader hdr;
           avpObj->Decode(buff, avpLen, hdr);
           avpContObj.add(*name, avpObj);
        }
        else
        {
           //if fails, just skip the buffer
           buff +=avpLen;
        }
        avpLen = (avpLen % 4);
        if (avpLen)
        {
           buff +=(4-avpLen);
         }
      }
      return 0;
}

int
PayloadAVP:: Encode(String& str)
{
   //encode AVP
   AVPContainerDerived& avpContObj = (AVPContainerDerived&)getContainer();
   int totalAVPs = avpContObj.GetNoOfContEntry()+avpContObj.GetNoOfDictEntry();
   for(int i= 0; i < totalAVPs;++i)
   {
      if(avpContObj[i])
      {
         avpContObj[i]->Encode(str);
      }
   }
   return 0;
}

int
PayloadAVP::countExtra()
{
   AVPContainerDerived& avpContObj = (AVPContainerDerived&)getContainer();
   return avpContObj.countExtra(AttributeName::AVP);
}

const AVP&
PayloadAVP::getExtra(unsigned int index)
{
   AVPContainerDerived& avpContObj = (AVPContainerDerived&)getContainer();
   return avpContObj.getExtra(AttributeName::AVP, index);
}

const AttributeName&
DerivedGroupedAVP::name() const
{
    AVPContainerDerived& contObj = (AVPContainerDerived&)_inbound.getContainer();
    return contObj.GetNameObj();
}

const AVP&
AVPContainerDerived::addAVP(int attrCode, unsigned int vendorId, void* val, 
                            bool single,  ValueDiscriminator D)
{
    AVP* avp = NULL;
    unsigned int avpIndex = 0;
    const CommandAttribute* cmdAtt = _cmdnameObj;
    bool fMand = false;
    const AttributeName* name = NULL;
    if (_nameObj)
    {
        //GroupedAVP inside GroupedAVP
        GroupedAttributeName* grpNameObj = (GroupedAttributeName*)_nameObj;
        name = grpNameObj->getAttributeName(attrCode, avpIndex, fMand);
    }
    else if(_cmdnameObj)
    {
        name = cmdAtt->GetAppAttributeObj(attrCode, vendorId, avpIndex, fMand);
    }
    if (name == NULL)
    {
        throw CodecException(__FILE__, __LINE__,"No Attribute Object found",ITS_DIA_AVP_UNSUPPORTED);
    }
    switch (D)
    {
        case OctetStringType:
        {
            OctetString& octStr = *((OctetString*)val);
            avp = new OctetStringAvp(*name, octStr);
        }
        break;
        case Integer32Type:
        {
            Integer32& int32 = *((Integer32*)val);
            avp = new Integer32Avp(*name, int32);
        }
        break;
        case Integer64Type:
        {
            Integer64& int64 = *((Integer64*)val);
            avp = new Integer64Avp(*name, int64);
        }
        break;
        case Unsigned32Type:
        {
            Unsigned32& unsigned32 = *((Unsigned32*)val);
            avp = new Unsigned32Avp(*name, unsigned32);
        }
        break;
        case Unsigned64Type:
        {
            Unsigned64& unsigned64 = *((Unsigned64*)val);
            avp = new Unsigned64Avp(*name, unsigned64);
        }
        break;
        case Float32Type:
        {
            Float32& float32 = *((Float32*)val);
            avp = new Float32Avp(*name, float32);
        }
        break;
        case Float64Type:
        {
            Float64& float64 = *((Float64*)val);
            avp = new Float64Avp(*name, float64);
        }
        break;
        case AddressType:
        {
            Address& addr = *((Address*)val);
            avp = new AddressAvp(*name, addr);
        }
        break;
        case TimeType:
        {
            Time& timeObj = *((Time*)val);
            avp = new TimeAvp(*name, timeObj);
        }
        break;
        case URIType:
        {
            URI& uriObj = *((URI*)val);
            avp = new URIAvp(*name, uriObj);
        }
        break;
        case UTF8StringType:
        {
            UTF8String& UTF8StringObj = *((UTF8String*)val);
            avp = new UTF8StringAvp(*name, UTF8StringObj);
        }
        break;
        case IdentityType:
        {
            Identity& IdentityObj = *((Identity*)val);
            avp = new IdentityAvp(*name, IdentityObj);
        }
        break;
        case IPFilterRuleType:
        {
            IPFilterRule& ipfilObj = *((IPFilterRule*)val);
            avp = new IPFilterRuleAvp(*name, ipfilObj);
        }
        break;
        case EnumeratedType:
        {
            Enumerated& enumObj  = *((Enumerated*)val);
            avp = new EnumeratedAvp(*name, enumObj);
        }
        break;
        case GroupedType:
        {
            GroupedAVPImplDerived& gImpl =
                (GroupedAVPImplDerived&)((GroupedAVP*)val)->getImpl();

            DerivedGroupedAVP* grpAVP = new DerivedGroupedAVP(*name, 0);
            GroupedAVPImplDerived& gImplS =
                (GroupedAVPImplDerived&)((GroupedAVP*)grpAVP)->getImpl();
            gImplS = gImpl;
            avp = grpAVP;
        }
        break;
        default :
            throw CodecException(__FILE__, __LINE__,"Type not found",ITS_DIA_AVP_UNSUPPORTED);
    }

    if (avp == NULL)
    {
        //error, avp is null
        throw CodecException(__FILE__, __LINE__,"Unable to create object",ITS_DIA_AVP_UNSUPPORTED);
    }

    //check if vendor id is mathcing
    if (avp->name().vendorId() != vendorId)
    {
         //error, mismatch in vendor id
         throw CodecException(__FILE__, __LINE__,"VendorId mismatch",ITS_DIA_AVP_UNSUPPORTED);
    }

    /*
     * Fix for memory leak 
     */ 
    const AVP& retAvp = add(avp->name(), *avp, single);
    delete avp;
    avp = NULL;
    return retAvp; 
}

const AVP&
AVPContainerDerived::addAVP(const char* AVPName, unsigned int vendorId, 
                            void* val, bool single, ValueDiscriminator D)
{
    AVP* avp = NULL;
    unsigned int avpIndex = 0;
    const CommandAttribute* cmdAtt = _cmdnameObj;
    bool fMand = false;
    const AttributeName* name = NULL;
    if (_nameObj)
    {
        //GroupedAVP inside GroupedAVP
        GroupedAttributeName* grpNameObj = (GroupedAttributeName*)_nameObj;
        name = grpNameObj->getAttributeName(AVPName, avpIndex, fMand);
    }
    else if(_cmdnameObj)
    {
        name = cmdAtt->GetAppAttributeObj(AVPName, vendorId, 
                                                       avpIndex, fMand);
    }

    if (name == NULL)
    {
        throw CodecException(__FILE__, __LINE__,"No Attribute Object found",ITS_DIA_AVP_UNSUPPORTED);
    }

    switch (D)
    {
        case OctetStringType:
        {
            OctetString& octStr = *((OctetString*)val);
            avp = new OctetStringAvp(*name, octStr);
        }
        break;
        case Integer32Type:
        {
            Integer32& int32 = *((Integer32*)val);
            avp = new Integer32Avp(*name, int32);
        }
        break;
        case Integer64Type:
        {
            Integer64& int64 = *((Integer64*)val);
            avp = new Integer64Avp(*name, int64);
        }
        break;
        case Unsigned32Type:
        {
            Unsigned32& unsigned32 = *((Unsigned32*)val);
            avp = new Unsigned32Avp(*name, unsigned32);
        }
        break;
        case Unsigned64Type:
        {
            Unsigned64& unsigned64 = *((Unsigned64*)val);
            avp = new Unsigned64Avp(*name, unsigned64);
        }
        break;
        case Float32Type:
        {
            Float32& float32 = *((Float32*)val);
            avp = new Float32Avp(*name, float32);
        }
        break;
        case Float64Type:
        {
            Float64& float64 = *((Float64*)val);
            avp = new Float64Avp(*name, float64);
        }
        break;
        case AddressType:
        {
            Address& addr = *((Address*)val);
            avp = new AddressAvp(*name, addr);
        }
        break;
        case TimeType:
        {
            Time& timeObj = *((Time*)val);
            avp = new TimeAvp(*name, timeObj);
        }
        break;
        case URIType:
        {
            URI& uriObj = *((URI*)val);
            avp = new URIAvp(*name, uriObj);
        }
        break;
        case UTF8StringType:
        {
            UTF8String& UTF8StringObj = *((UTF8String*)val);
            avp = new UTF8StringAvp(*name, UTF8StringObj);
        }
        break;
        case IdentityType:
        {
            Identity& IdentityObj = *((Identity*)val);
            avp = new IdentityAvp(*name, IdentityObj);
        }
        break;
        case IPFilterRuleType:
        {
            IPFilterRule& ipfilObj = *((IPFilterRule*)val);
            avp = new IPFilterRuleAvp(*name, ipfilObj);
        }
        break;
        case EnumeratedType:
        {
             Enumerated& enumObj  = *((Enumerated*)val);
             avp = new EnumeratedAvp(*name, enumObj);
        }
        break;
        case GroupedType:
        {
            GroupedAVPImplDerived& gImpl =
                (GroupedAVPImplDerived&)((GroupedAVP*)val)->getImpl();

            DerivedGroupedAVP* grpAVP = new DerivedGroupedAVP(*name, 0);
            GroupedAVPImplDerived& gImplS =
                (GroupedAVPImplDerived&)((GroupedAVP*)grpAVP)->getImpl();
            gImplS = gImpl;
            avp = grpAVP;
        }
        break;
        default :
            throw CodecException(__FILE__, __LINE__,"Type not found",ITS_DIA_AVP_UNSUPPORTED);
    }
    if (avp == NULL)
    {
       throw CodecException(__FILE__, __LINE__,"Unable to create object",ITS_DIA_AVP_UNSUPPORTED);
    }
    //check if vendor id is mathcing
    if (avp->name().vendorId() != vendorId)
    {
       //error, mismatch in vendor id
       throw CodecException(__FILE__, __LINE__,"VendorId mismatch",ITS_DIA_AVP_UNSUPPORTED);
    }

    /*
     * Fix for memory leak
     */
    const AVP& retAvp = add(avp->name(), *avp, single);
    delete avp;
    avp = NULL;
    return retAvp; 
}

int
AVPContainerDerived::remove(const AttributeName &name)
{
    unsigned int avpIndex = name.GetIndex();
    if(_nameObj)
    {
        unsigned int avpCode  = name.GetCode();
        GroupedAttributeName& GroupedObj = *((GroupedAttributeName*)_nameObj);
        std::map<unsigned int, AttributeName*>::iterator it = GroupedObj.GetMandAttMap().find(avpCode);
        if(it != GroupedObj.GetMandAttMap().end())
        {
            //only Mandatory AVPs
            _noOfMandAvp--;
            avpIndex = (*it).second->GetIndex();
        }
        else if((it = GroupedObj.GetOptAttMap().find(avpCode)) != GroupedObj.GetOptAttMap().end())
        {
            //only optional AVPs
            avpIndex = (*it).second->GetIndex();
        }
        else
        {
            //extensible AVPs
            avpIndex = GroupedObj.GetOptAttMap().size() + GroupedObj.GetMandAttMap().size()+_dictEntries;
        }
    }
    if(_cmdnameObj)
    {
        if(name.ifBase())
        {
            avpIndex = name.GetIndex();
            _baseMandBitMap &= ~(0x8000000000000000ull >> name.GetIndex());
        }
        else
        {
            bool fMand;
            avpIndex = _cmdnameObj->GetIndex(&name,fMand);
            if(fMand)
            {
                _noOfMandAvp--;
            }
        }
    }

    AVPContainerDerivedEntry* &entry = getAt(avpIndex);
    if(entry)
    {
        /**
         * Release the Entries and delete the object
         * by calling delete
         */
        entry->releaseEntries();
        delete entry;
        entry = NULL;
        return 0;
    }
    return -1;
}

int
AVPContainerDerived::remove(const AttributeName &name, const AVP& avp)
{
    unsigned int avpIndex = name.GetIndex();
    if(_nameObj)
    {
        unsigned int avpCode  = name.GetCode();
        GroupedAttributeName& GroupedObj = *((GroupedAttributeName*)_nameObj);
        std::map<unsigned int, AttributeName*>::iterator it = GroupedObj.GetMandAttMap().find(avpCode);
        if(it != GroupedObj.GetMandAttMap().end())
        {
            //only Mandatory AVPs
            _noOfMandAvp--;
            avpIndex = (*it).second->GetIndex();
        }
        else if((it = GroupedObj.GetOptAttMap().find(avpCode)) != GroupedObj.GetOptAttMap().end())
        {
            //only optional AVPs
            avpIndex = (*it).second->GetIndex();
        }
        else
        {
            //extensible AVPs
            avpIndex = GroupedObj.GetOptAttMap().size() + GroupedObj.GetMandAttMap().size()+_dictEntries;
        }
    }
    if(_cmdnameObj)
    {
       if(name.ifBase())
       {
           avpIndex = name.GetIndex();
           _baseMandBitMap &= ~(0x8000000000000000ull >> name.GetIndex());
       }
       else
       {
           bool fMand;
           avpIndex = _cmdnameObj->GetIndex(&name,fMand);
           if(fMand)
           {
               _noOfMandAvp--;
           }
       }
    }

    AVPContainerDerivedEntry* &entry = getAt(avpIndex);
    if(entry)
    {
        /**
         * removeSpecificAvp is called to remove particular AVP (if entry 
         * consists more than one instances of this AVP).
         */ 
        int ret = entry->removeSpecificAvp(&avp);
        if (entry->AvpCount() == 0)
        {
            /**
             * delete the object by calling delete
             */
            delete entry;
            entry = NULL;
        }
        return ret;
    }
    return -1;
}

int
AVPContainerDerived::removeAVP(int attrCode, unsigned int vendorId)
{
    AVP* avp = NULL;
    unsigned int avpIndex = 0;
    const CommandAttribute* cmdAtt = _cmdnameObj;
    bool fMand = false;
    const AttributeName* name = NULL;
    if (_nameObj)
    {
        //GroupedAVP inside GroupedAVP
        GroupedAttributeName* grpNameObj = (GroupedAttributeName*)_nameObj;
        name = grpNameObj->getAttributeName(attrCode, avpIndex, fMand);
    }
    else if(_cmdnameObj)
    {
        name = cmdAtt->GetAppAttributeObj(attrCode, vendorId, avpIndex, fMand);
    }

    if (name == NULL)
    {
        return -1;
    }
    return (remove(*name));
}

int
AVPContainerDerived::removeAVP(const char* AVPName, unsigned int vendorId)
{
    AVP* avp = NULL;
    unsigned int avpIndex = 0;
    const CommandAttribute* cmdAtt = _cmdnameObj;
    bool fMand = false;
    const AttributeName* name = NULL;
    if (_nameObj)
    {
        //GroupedAVP inside GroupedAVP
        GroupedAttributeName* grpNameObj = (GroupedAttributeName*)_nameObj;
        name = grpNameObj->getAttributeName(AVPName, avpIndex, fMand);
    }
    else if(_cmdnameObj)
    {
        name = cmdAtt->GetAppAttributeObj(AVPName, vendorId, 
                                           avpIndex, fMand);
    }
    if (name == NULL)
    {
        return -1;
    }
    return (remove(*name));
}

BaseCommand::BaseCommand(DIA_GEN_CMD* cmd)
    :_avpBitMap(0),
    _sessIndex(0),
    _clientId(0),
    _proxyCount(0),
    _pxyTotalCount(0),
    _ptrProxyInfo(NULL),
    _routeRecCount(0),
    _routeRecTotalCount(0),
    _ptrRouteRecord(NULL),
    _vendorSpecAppIdCount(0),
    _storageSpaceAvailable(true),
    _lastRecordInStorage(false),
    _userData(NULL),
    _enBuf(NULL),
    _enBufLen(0),
    _ptrRdHost(NULL),
    _rdHostCount(0),
    _rdHostTotalCount(0),
    _bufToDel(NULL)
{

    copyHeader(cmd->getHeader());
    _sessIndex            = cmd->getSessionIndex();
    _storageSpaceAvailable= cmd->IsStorageSpaceAvailable();
    _lastRecordInStorage  = cmd->IsLastRecordInStorage();
    _clientId             = cmd->getClientId();
    _appId.data           = cmd->getApplicationId();

    if (cmd->getResultCode())
    {
        _resultCode.data      = cmd->getResultCode()->value();
        _avpBitMap |= RCODE_AVP_BIT;
    }
    if (cmd->getOriginStateId())
    {
        _originStateId.data = cmd->getOriginStateId()->value();
        _avpBitMap |= OSTATEID_AVP_BIT;
    }
    if (cmd->getSessionId())
    {
        _sessId.data      = cmd->getSessionId()->value();
        _avpBitMap |= SESSID_AVP_BIT;
    }
    if (cmd->getOriginHost())
    {
        _originHost.data  = cmd->getOriginHost()->value();
        _avpBitMap |= OHOST_AVP_BIT;
    }
    if (cmd->getDestinationHost())
    {
        _destHost.data    = cmd->getDestinationHost()->value();
        _avpBitMap |= DHOST_AVP_BIT;
    }
    if (cmd->getDestinationRealm())
    {
        _destRealm.data    = cmd->getDestinationRealm()->value();
        _avpBitMap |= DREALM_AVP_BIT;
    }
    if (cmd->getOriginRealm())
    {
        _originRealm.data = cmd->getOriginRealm()->value();
        _avpBitMap |= OREALM_AVP_BIT;
    }

    //copy route record
    _routeRecCount = cmd->countRouteRecord();
    _routeRecTotalCount = _routeRecCount;
    if(_routeRecCount > 0)
    {
        _ptrRouteRecord = new AVP_STRING[_routeRecCount];
        _avpBitMap |= ROUTE_RECORD_AVP_BIT;
    }
    for (int i = 0; i<_routeRecCount; i++)
    {
        _ptrRouteRecord[i].data = cmd->getRouteRecord(i)->value();
    }
    if (cmd->getVendorId())
    {
        _vendorId.data = cmd->getVendorId()->value();
    }

    //copy vendor specfic app id
    _vendorSpecAppIdCount = cmd->countVendorSpecificApplicationId();
    for (int i=0; i<_vendorSpecAppIdCount; i++)
    {
        const diameter::base::VendorSpecificApplicationId *venId = 
                                    cmd->getVendorSpecificApplicationId(i);

        _vendorSpecificAppId[i].vendorId.data  = venId->getVendorId().value();
        _vendorSpecificAppId[i].vendorIdCount  = venId->countVendorId();

        if (venId->containsAuthApplicationId())
        {
            _vendorSpecificAppId[i].appId.data = 
                                         venId->getAuthApplicationId().value();
            _vendorSpecificAppId[i].type = AUTH_APP;
        }
        else
        {
            _vendorSpecificAppId[i].appId.data = 
                                    venId->getAcctApplicationId().value();
            _vendorSpecificAppId[i].type = ACCT_APP;
        }
    }

    /* Copy Redirect-Host */
    _rdHostCount = cmd->countRedirectHost();
    _rdHostTotalCount = _rdHostCount;
 
    if(_rdHostCount > 0)
    {
        _ptrRdHost = new AVP_URI[_rdHostCount];
    }
 
    for (int i = 0; i<_rdHostCount; i++)
    {
        _ptrRdHost[i].scheme = 
                 (URI_SCHEME)cmd->getRedirectHost(i)->value().scheme;

        _ptrRdHost[i].fqdn.data = 
                 cmd->getRedirectHost(i)->value().fqdn;

        _ptrRdHost[i].port.data = 
                 cmd->getRedirectHost(i)->value().port;

        _ptrRdHost[i].transport = 
                 (URI_TRANSPORT)cmd->getRedirectHost(i)->value().transport;

        _ptrRdHost[i].protocol =  
                 (URI_PROTOCOL)cmd->getRedirectHost(i)->value().protocol;
    }
 
    if (_rdHostCount>0)
    {
        _avpBitMap |= RD_HOST_AVP_BIT;
    }
 
    /* Copy Redirect-Host-Usage */
    if (cmd->getRedirectHostUsage())
    {
        _rdHostUsage.data = cmd->getRedirectHostUsage()->value();
        _avpBitMap |= RD_HOST_USAGE_AVP_BIT;
    }
 
    /* Copy Redirect-Host-Max-Cache-Time */
    if (cmd->getRedirectMaxCacheTime())
    {
        _rdHostUsage.data = cmd->getRedirectMaxCacheTime()->value();
        _avpBitMap |= RD_HOST_CACHE_AVP_BIT;
    }

    if (_vendorSpecAppIdCount >0)
    {
        _avpBitMap |= VENDOR_SPEC_AVP_BIT;
    }

    if (hdr.code == 272)
    {
        int temp;

        /* Fix for Issue 1419 */
        if (cmd->getAvpValue(CCFH_AVP_CODE, &temp, 
                                        diameter::EnumeratedType) == 0)
        {
            _ccFaultHandling.data = temp;
            _avpBitMap |= CCFH_AVP_BIT;
        }

        /* Fix for Issue 1419 */
        if (cmd->getAvpValue(CC_REQUEST_TYPE_AVP_CODE, &temp, 
                                        diameter::EnumeratedType) == 0)
        {
            _ccReqType.data = temp;
            _avpBitMap |= CC_REQ_TYPE_AVP_BIT; 
        }

        /* Fix for Issue 1419 */
        if (cmd->getAvpValue(REQUESTED_ACTION_AVP_CODE, 
                                        &temp, diameter::EnumeratedType) == 0)
        {
            _reqAction.data = temp;
            _avpBitMap |= REQ_ACTION_AVP_BIT;
        }
    }
    else if (hdr.code == 271)
    {
        if (cmd->getAccountingRecordType())
        {
            _acctRecType.data = cmd->getAccountingRecordType()->value();
            _avpBitMap |= ACCT_RECTYPE_AVP_BIT;
        }

        if (cmd->getAccountingRealtimeRequired())
        {
            _acctRealTime.data = cmd->getAccountingRealtimeRequired()->value();
            _avpBitMap |= ACCT_REALTIME_AVP_BIT;
        }

        if (cmd->getAcctInterimInterval())
        {
            _acctInterimInvl.data = cmd->getAcctInterimInterval()->value();
            _avpBitMap |= ACCT_INTERIM_AVP_BIT; 
        }
    }
    else
    {
        if (cmd->getAuthSessionState())
        {
            _authSessState.data = cmd->getAuthSessionState()->value();
            _avpBitMap |= AUTH_SSTATE_AVP_BIT;
        }

        if (cmd->getAuthorizationLifetime())
        {
            _authLifetime.data = cmd->getAuthorizationLifetime()->value();
            _avpBitMap |= AUTH_LTIME_AVP_BIT;
        }

        if (cmd->getAuthGracePeriod())
        {
            _authGracePeriod.data = cmd->getAuthGracePeriod()->value();
            _avpBitMap |= AUTH_GPTIME_AVP_BIT;
        }

        if (cmd->getSessionTimeout())
        {
            _authSessTime.data = cmd->getSessionTimeout()->value();
            _avpBitMap |= AUTH_SESSTIME_AVP_BIT;
        }
    }

    CommandImplDerived& ImplDer = (CommandImplDerived&)cmd->getImpl();
    ITS_EVENT* userEvent = (ITS_EVENT*)ImplDer.getUserData(); 
    if (userEvent)
    {
        ITS_EVENT* evt = new ITS_EVENT;
        evt->data = new ITS_OCTET [userEvent->len];
        evt->len  = userEvent->len;
        memcpy(evt->data, userEvent->data, userEvent->len);
        _userData = (void*) evt;
    }

    ITS_OCTET *buff;
    int len;

    try
    {
        cmd->encode(buff, len);
        _enBuf = (void*) buff;
        _enBufLen = len;
    }
    catch (...)
    {
        printf("Encode failure cought exception\n");
        //throw error
    }

}

BaseCommand::BaseCommand(const unsigned char *inputBuffer, int size)
   :_avpBitMap(0),
    _sessIndex(0),
    _clientId(0),
    _proxyCount(0),
    _pxyTotalCount(0),
    _ptrProxyInfo(NULL),
    _routeRecCount(0),
    _routeRecTotalCount(0),
    _ptrRouteRecord(NULL),
    _vendorSpecAppIdCount(0),
    _userData(NULL),
    _enBuf(NULL),
    _enBufLen(0),
    _storageSpaceAvailable(true),
    _lastRecordInStorage(false),
    _ptrRdHost(NULL),
    _rdHostCount(0),
    _rdHostTotalCount(0),
    _bufToDel(NULL),
    _idcIdsHb(0),
    _globalUniqAddr({0})
{

    if (inputBuffer == NULL || size <= 0)
    {
       throw CodecException(__FILE__, __LINE__,"Wrong Command length",
                            ITS_DIA_INVALID_MSG_LENGTH);
    }

    unsigned char* buffer = (unsigned char *)inputBuffer;
    unsigned char* end    = (unsigned char*)(inputBuffer+size);
    if((unsigned long)(buffer+20) < (unsigned long)end)
    {
       hdr.ver = buffer[0];
       hdr.length = DataToApp(&buffer[1], 3);
       hdr.flags.r=((buffer[4] & 0x80) ? 1 : 0);
       hdr.flags.p=((buffer[4] & 0x40) ? 1 : 0);
       hdr.flags.e=((buffer[4] & 0x20) ? 1 : 0);
       hdr.flags.t=((buffer[4] & 0x10) ? 1 : 0);
       hdr.code = DataToUApp(&buffer[5], 3);
       hdr.appId = DataToApp(&buffer[8], 4);
       hdr.hh = DataToApp(&buffer[12], 4);
       hdr.ee = DataToApp(&buffer[16], 4);
       /* applicationId */
       _appId.data = hdr.appId;

       buffer +=20;
    }
    else
    {
       throw CodecException(__FILE__, __LINE__,"Wrong Command Header length",
                            ITS_DIA_INVALID_MSG_LENGTH);
    }
    if(hdr.length > size)
    {
       throw CodecException(__FILE__, __LINE__,"Wrong Command Header length",
                            ITS_DIA_INVALID_MSG_LENGTH);
    }
    if( (!ITS_SUCCESS) == validateComandCodeandAppId(hdr.appId,hdr.code) )
    {
	throw CodecException(__FILE__, __LINE__,"Wrong Command code",
			    ITS_DIA_CMD_UNSUPPORTED);
    }

    while((unsigned long)(buffer+8) <= (unsigned long)end)//parse AVPs
    {
        unsigned char* startBuff = buffer;
        unsigned int offset      = 8;
        unsigned int avpCode     = DataToApp(buffer, 4);
        buffer+=4;
        unsigned int avpLen   = DataToApp(buffer+1, 3);
        unsigned int vendorId = 0;

        if((unsigned long)(buffer+avpLen-4) > (unsigned long)end)
        {
            UTF8String sessId, origHost, origRealm;

            CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);
            sessId = _sessId.data;
            origHost = _originHost.data;
            origRealm = _originRealm.data;

            avpLenErr.SetSessionId(sessId);
            avpLenErr.SetOriginHost(origHost);
            avpLenErr.SetOriginRealm(origRealm);
            throw avpLenErr;
        }
        if(*buffer & 0x80)
        {
            //with vendor id;
            if (avpLen < 12)
            {
                UTF8String sessId, origHost, origRealm;
                CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

                sessId = _sessId.data;
                origHost = _originHost.data;
                origRealm = _originRealm.data;

                avpLenErr.SetSessionId(sessId);
                avpLenErr.SetOriginHost(origHost);
                avpLenErr.SetOriginRealm(origRealm);
                throw avpLenErr;
            }

            buffer +=4;
            avpLen -=4;
            offset +=4;
        }
        else
        {
            //Added check to see avpLen should not be corrupt.
            if (avpLen < 8)
            {
                UTF8String sessId, origHost, origRealm;
                CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);

                sessId = _sessId.data;
                origHost = _originHost.data;
                origRealm = _originRealm.data;

                avpLenErr.SetSessionId(sessId);
                avpLenErr.SetOriginHost(origHost);
                avpLenErr.SetOriginRealm(origRealm);
                throw avpLenErr;
            }
        }
        buffer +=4;
        avpLen -=8;
        if (avpCode)
        {
            switch(avpCode)
            {
            case SESSID_AVP_CODE:
                _sessId.data.assign((char *)buffer, avpLen);
                _avpBitMap |= SESSID_AVP_BIT;
                break;
            case OHOST_AVP_CODE:
                _originHost.data.assign((char *)buffer, avpLen);
                _avpBitMap |= OHOST_AVP_BIT;
                break;
            case OREALM_AVP_CODE:
                _originRealm.data.assign((char *)buffer, avpLen);
                _avpBitMap |= OREALM_AVP_BIT;
                break;
            case DHOST_AVP_CODE:
                _destHost.data.assign((char *)buffer, avpLen);
                _avpBitMap |= DHOST_AVP_BIT;
                break;
            case DREALM_AVP_CODE:
                _destRealm.data.assign((char *)buffer, avpLen);
                _avpBitMap |= DREALM_AVP_BIT;
                break;
            case OSTATEID_AVP_CODE:
                _originStateId.data = DataToApp((unsigned char*)buffer, avpLen);
                _avpBitMap |= OSTATEID_AVP_BIT;
                break;
            case RCODE_AVP_CODE:
                _resultCode.data = DataToApp((unsigned char*)buffer, avpLen);
                _avpBitMap |= RCODE_AVP_BIT;
                break;
            case ROUTE_RECORD_AVP_CODE:
                DecodeRouteRecordAvp(buffer, avpLen);
                _avpBitMap |= ROUTE_RECORD_AVP_BIT;
                break;
                break;
            case VENDOR_ID_AVP_CODE:
                _vendorId.data = DataToApp((unsigned char*)buffer, avpLen);
                _avpBitMap |= VENDOR_ID_AVP_BIT;
                break;
            case PROXY_INFO_AVP_CODE:
                DecodeProxyInfoAvp(buffer, avpLen);
                _avpBitMap |= PROXY_INFO_AVP_BIT;
                break;
            case VENDOR_SPECIFIC_APP_ID_AVP_CODE:
                DecodeVendorSpecificAvp(buffer, avpLen);
                _avpBitMap |= VENDOR_SPEC_AVP_BIT;
                break;
            case RD_HOST_AVP_CODE:
                BaseCommand::DecodeRedirectHostAvp(buffer, avpLen);
                _avpBitMap |= RD_HOST_AVP_BIT;
                break;
            case RD_HOST_USAGE_AVP_CODE:
                _rdHostUsage.data = DataToApp((unsigned char*)buffer, avpLen);
                _avpBitMap |= RD_HOST_USAGE_AVP_BIT;
                break;
            case RD_HOST_CACHE_AVP_CODE:
                _rdHostCache.data = DataToApp((unsigned char*)buffer, avpLen);
                _avpBitMap |= RD_HOST_CACHE_AVP_BIT;
                break;
            case IDC_IDS_HB_AVP_CODE:
                _idcIdsHb  = DataToApp((unsigned char*)buffer, avpLen);
                _avpBitMap |= IDC_IDS_HB_AVP_BIT;
                break;
            case GLOBAL_UNIQ_ADDR_AVP_CODE:
                BaseCommand::DecodeGlobalUniqAddrAvp(buffer, avpLen);
                _avpBitMap |= GLOBAL_UNIQ_ADDR_AVP_BIT;
                break;
            }
            if (hdr.code == 272)
            {
                /* DCCA */
                switch(avpCode)
                {
                case CC_REQUEST_TYPE_AVP_CODE:
                    _ccReqType.data = 
                                DataToApp((unsigned char*)buffer, avpLen); 
                    _avpBitMap |= CC_REQ_TYPE_AVP_BIT;
                    break;
                case CCFH_AVP_CODE:
                    _ccFaultHandling.data = 
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= CCFH_AVP_BIT;
                    break;
                case REQUESTED_ACTION_AVP_CODE:
                    _reqAction.data = 
                                DataToApp((unsigned char*)buffer,avpLen);
                    _avpBitMap |= REQ_ACTION_AVP_BIT;
                    break;
                }
            }
            else if (hdr.code == 271)
            {
                /* Acct Session */
                switch(avpCode)
                {
                case ACCT_RECTYPE_AVP_CODE:
                    _acctRecType.data = 
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= ACCT_RECTYPE_AVP_BIT;
                    break;
                case ACCT_REALTIME_AVP_CODE:
                    _acctRealTime.data = 
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= ACCT_REALTIME_AVP_BIT;
                    break;
                case ACCT_INTERIM_AVP_CODE:
                    _acctInterimInvl.data = 
                                DataToApp((unsigned char*)buffer,avpLen);
                    _avpBitMap |= ACCT_INTERIM_AVP_BIT;
                    break;
                case ACCT_SESSTIME_AVP_CODE:
                    _acctSessTime.data = 
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= ACCT_SESSTIME_AVP_BIT;
                    break;
                }
            }
            else 
            {
                /* Auth Session */
                switch(avpCode)
                {
                case AUTH_SSTATE_AVP_CODE:
                    _authSessState.data =
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= AUTH_SSTATE_AVP_BIT;
                    break;
                case AUTH_LTIME_AVP_CODE:
                    _authLifetime.data =
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= AUTH_LTIME_AVP_BIT;
                    break;
                case AUTH_GPTIME_AVP_CODE:
                    _authGracePeriod.data =
                                DataToApp((unsigned char*)buffer,avpLen);
                    _avpBitMap |= AUTH_GPTIME_AVP_BIT;
                    break;
                case AUTH_SESSTIME_AVP_CODE:
                    _authSessTime.data =
                                DataToApp((unsigned char*)buffer, avpLen);
                    _avpBitMap |= AUTH_SESSTIME_AVP_BIT;
                    break;
                }
            }

        }
        buffer +=avpLen;
        //align buffer to word byte
        avpLen = (avpLen % 4);
        if(avpLen)
        {
           buffer +=(4-avpLen);
        }
        if (buffer < startBuff)
        {
            UTF8String sessId, origHost, origRealm;
            CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, avpCode);
            sessId = _sessId.data;
            origHost = _originHost.data;
            origRealm = _originRealm.data;
                              
            avpLenErr.SetSessionId(sessId);
            avpLenErr.SetOriginHost(origHost);
            avpLenErr.SetOriginRealm(origRealm);
            throw avpLenErr;
        }
    }
    if ((hdr.code == DIA_MSG_AC) && (NULL == getAccountingRecordType()))
    {
	throw CodecException(__FILE__, __LINE__,"Mandatory Avp Missing ",
                            ITS_DIA_MISSING_AVP);	
    }
    //set encode buff
#if 0
    _enBuf = new ITS_OCTET [size];
    _enBufLen = size;
    memcpy(_enBuf, inputBuffer, size);
#endif
    _enBuf = (void*)inputBuffer;
    _enBufLen = size;
}
void 
BaseCommand::DecodeProxyInfoAvp(const unsigned char *buffer, int avpLen)
{
    PROXY_INFO* ptrPxyInfo = _ptrProxyInfo;
    if (_pxyTotalCount == 0)
    {
        _pxyTotalCount += ALLOC_SIZE;
        _ptrProxyInfo = new PROXY_INFO[ALLOC_SIZE];
    }
    else if (_pxyTotalCount < _proxyCount)
    {
        _pxyTotalCount += ALLOC_SIZE;
        _ptrProxyInfo = new PROXY_INFO[_pxyTotalCount];

        for (int i=0; i<_proxyCount; i++)
        {
            _ptrProxyInfo[i] = ptrPxyInfo[i];
        }
    }

    int tmpCounter = 0;
    unsigned char* pBuf = (unsigned char*)buffer;

    while (tmpCounter < avpLen)
    {
        int mAvpCode = DataToApp((unsigned char*)pBuf, 4);
        char tmpFlg = pBuf[4];
        int mAvpLen = DataToApp((unsigned char*)&pBuf[5], 3);
        int dataIndex = 8;

        mAvpLen -= 8;
        tmpCounter+=8;

        if(mAvpLen > avpLen)
        {
            UTF8String sessId, origHost, origRealm;
            CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, mAvpCode);

            avpLenErr.SetSessionId(sessId);
            avpLenErr.SetOriginHost(origHost);
            avpLenErr.SetOriginRealm(origRealm);
            avpLenErr.setGroupedAvpError(true);
            avpLenErr.setGroupedAvpCode(PROXY_INFO_AVP_CODE);
            throw avpLenErr;
        }

        if ((tmpFlg & 0x80) == 0x80)
        {
            mAvpLen   -= 4;
            tmpCounter+= 4;
            dataIndex += 4;
            if(mAvpLen < 0)
            {
                UTF8String sessId, origHost, origRealm;
                CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, mAvpCode);

                avpLenErr.SetSessionId(sessId);
                avpLenErr.SetOriginHost(origHost);
                avpLenErr.SetOriginRealm(origRealm);
                avpLenErr.setGroupedAvpError(true);
                avpLenErr.setGroupedAvpCode(PROXY_INFO_AVP_CODE);
                throw avpLenErr;
            }
        }

        if (mAvpCode == PROXY_HOST_AVP_CODE)
        {
            _ptrProxyInfo[_proxyCount].pxyHost.data.assign(
                                (char*)&pBuf[dataIndex], mAvpLen);
        }
        else if (mAvpCode == PROXY_STATE_AVP_CODE)
        {
            _ptrProxyInfo[_proxyCount].pxyState.data.assign(
                                (char*)&pBuf[dataIndex], mAvpLen);
        }

        tmpCounter+=mAvpLen;
        pBuf      +=tmpCounter;

        //align buffer to word byte
        mAvpLen = (mAvpLen % 4);
        if(mAvpLen)
        {
           pBuf      +=(4-mAvpLen);
           tmpCounter+=(4-mAvpLen);
        }
    }
    _proxyCount++;
}
void 
BaseCommand::DecodeVendorSpecificAvp(const unsigned char *buffer, int avpLen)
{
    int tmpCounter = 0;
    unsigned char* pBuf = (unsigned char* )buffer;

    if (_vendorSpecAppIdCount >= MAX_LEN) 
        return;

    VENDOR_SPEC_APP_ID* pVendorAppId =
                                &_vendorSpecificAppId[_vendorSpecAppIdCount];

    while ((tmpCounter+8) <= avpLen)
    {
        int mAvpVal=0;
        int mAvpCode = DataToApp(pBuf);
        pBuf += 4;
        char tmpFlg = *pBuf;
        int mAvpLen = DataToApp(pBuf+1, 3);

        mAvpLen -= 8;
        tmpCounter+=8;
        pBuf += 4;

        if(mAvpLen > avpLen)
        {
            UTF8String sessId, origHost, origRealm;
            CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, mAvpCode);
                                     
            avpLenErr.SetSessionId(sessId);
            avpLenErr.SetOriginHost(origHost);
            avpLenErr.SetOriginRealm(origRealm);
            avpLenErr.setGroupedAvpError(true);
            avpLenErr.setGroupedAvpCode(VENDOR_SPECIFIC_APP_ID_AVP_CODE);
            throw avpLenErr;
        }

        if ((tmpFlg & 0x80) == 0x80)
        {
            mAvpLen   -=4;
            tmpCounter+=4;
            pBuf += 4;
            if(mAvpLen < 0)
            {
                UTF8String sessId, origHost, origRealm;
                CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, mAvpCode);

                avpLenErr.SetSessionId(sessId);
                avpLenErr.SetOriginHost(origHost);
                avpLenErr.SetOriginRealm(origRealm);
                avpLenErr.setGroupedAvpError(true);
                avpLenErr.setGroupedAvpCode(VENDOR_SPECIFIC_APP_ID_AVP_CODE);
                throw avpLenErr;
            }
        }

        mAvpVal = DataToApp(pBuf);
        if (mAvpCode == VENDOR_ID_AVP_CODE)
        {
            pVendorAppId->vendorId.data = mAvpVal;
            pVendorAppId->vendorIdCount = 1;
        }
        else if (mAvpCode == AUTH_APP_ID_AVP_CODE)
        {
            pVendorAppId->appId.data = mAvpVal;
            pVendorAppId->type = AUTH_APP;
        }
        else if (mAvpCode == ACCT_APP_ID_AVP_CODE)
        {
            pVendorAppId->appId.data = mAvpVal;
            pVendorAppId->type = ACCT_APP;
        }

        tmpCounter+=mAvpLen;
        pBuf +=mAvpLen;

        //align buffer to word byte
        mAvpLen = (mAvpLen % 4);
        if(mAvpLen)
        {
           pBuf      +=(4-mAvpLen);
           tmpCounter+=(4-mAvpLen);
        }
    }
    _vendorSpecAppIdCount++;
}
void 
BaseCommand::DecodeRouteRecordAvp(const unsigned char *buffer, int avpLen)
{
    AVP_STRING* tmpRouteRec = _ptrRouteRecord;

    if (_routeRecTotalCount == 0)
    {
        _routeRecTotalCount += ALLOC_SIZE;
        _ptrRouteRecord = new AVP_STRING[ALLOC_SIZE];
    }
    else if (_routeRecTotalCount < _routeRecCount)
    {
        _routeRecTotalCount += ALLOC_SIZE;
        _ptrRouteRecord = new AVP_STRING[_routeRecTotalCount];

        for (int i=0; i<_routeRecCount; i++)
        {
            _ptrRouteRecord[i] = tmpRouteRec[i];
        }
                }
    _ptrRouteRecord[_routeRecCount].data.assign((char *)buffer, avpLen);
    _routeRecCount++;
}

void
BaseCommand::DecodeRedirectHostAvp(const unsigned char *buffer, int avpLen)
{
    AVP_URI* tmpRdHost = _ptrRdHost;
 
    /* Memory Allocation */
    if (_rdHostTotalCount == 0)
    {
        _rdHostTotalCount += ALLOC_SIZE;
        _ptrRdHost = new AVP_URI[ALLOC_SIZE];
    }
    else if (_rdHostTotalCount == _rdHostCount)
    {
        _rdHostTotalCount += ALLOC_SIZE;
        _ptrRdHost = new AVP_URI[_rdHostTotalCount];
 
        for (int i=0; i<_rdHostCount; i++)
        {
            _ptrRdHost[i] = tmpRdHost[i];
        }
    }
 
    /* Decoding start here */
    char* buff = (char*)buffer;
    int Len = avpLen;
 
    /* Decoding AVP_URI.scheme */
    if(memcmp(buff, "aaas", 4) == 0)
    {
        _ptrRdHost[_rdHostCount].scheme = AAAS;
        buff += 7;
        Len -= 7;
    }
    else
    {
        _ptrRdHost[_rdHostCount].scheme = AAA;
        buff += 6;
        Len -= 6;
    }
 
    std::string str;
    str.assign(buff, Len);
 
    char* buffStr = strchr(buff, ':');
    if(buffStr)
    {
        /* Decoding AVP_URI.fqdn */
        _ptrRdHost[_rdHostCount].fqdn.data.assign((char const*)buff, (buffStr - buff));
        buff = buffStr+1;
 
        /* Decoding AVP_URI.port */
        buffStr = strchr(buff, ';');
        if(buffStr)
        {
            char temp[8] ="";
            unsigned int portLen = buffStr - buff;
            if (portLen < 8)
                memcpy(temp,buff,portLen);
            else
                memcpy(temp,buff,7);
            
            _ptrRdHost[_rdHostCount].port.data=atoi((const char *)&temp);
            buff = buffStr+1;
       }
    }
 
    /* Decoding AVP_URI.transport */
    if(strstr(str.c_str(), "transport=tcp"))
    {
        _ptrRdHost[_rdHostCount].transport = TCP;
    }
    else if(strstr(str.c_str(), "transport=udp"))
    {
        _ptrRdHost[_rdHostCount].transport = UDP;
    }
    else
    {
        _ptrRdHost[_rdHostCount].transport = SCTP;
    }
 
    /* Decoding AVP_URI.protocol */
    if(strstr(str.c_str(), "protocol=tacacs+"))
    {
        _ptrRdHost[_rdHostCount].protocol = TACACSPLUS;
    }
    else if(strstr(str.c_str(), "protocol=radius"))
    {
        _ptrRdHost[_rdHostCount].protocol = RADIUS;
    }
    else
    {
        _ptrRdHost[_rdHostCount].protocol = DIAMETER;
    }
    _rdHostCount++;
}

void 
BaseCommand::DecodeGlobalUniqAddrAvp(const unsigned char *buffer, int avpLen)
{
    int tmpCounter = 0;
    unsigned char* pBuf = (unsigned char*)buffer;

    while (tmpCounter < avpLen)
    {
        int mAvpCode = DataToApp((unsigned char*)pBuf, 4);
        char tmpFlg = pBuf[4];
        int mAvpLen = DataToApp((unsigned char*)&pBuf[5], 3);
        int dataIndex = 8;

        mAvpLen -= 8;
        tmpCounter+=8;

        if(mAvpLen > avpLen)
        {
            UTF8String sessId, origHost, origRealm;
            CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, mAvpCode);

            avpLenErr.SetSessionId(sessId);
            avpLenErr.SetOriginHost(origHost);
            avpLenErr.SetOriginRealm(origRealm);
            avpLenErr.setGroupedAvpError(true);
            avpLenErr.setGroupedAvpCode(PROXY_INFO_AVP_CODE);
            throw avpLenErr;
        }

        if ((tmpFlg & 0x80) == 0x80)
        {
            mAvpLen   -= 4;
            tmpCounter+= 4;
            dataIndex += 4;
            if(mAvpLen < 0)
            {
                UTF8String sessId, origHost, origRealm;
                CodecException  avpLenErr(__FILE__, __LINE__,"Wrong AVP length",
                                   ITS_DIA_INVALID_AVP_LENGTH, mAvpCode);

                avpLenErr.SetSessionId(sessId);
                avpLenErr.SetOriginHost(origHost);
                avpLenErr.SetOriginRealm(origRealm);
                avpLenErr.setGroupedAvpError(true);
                avpLenErr.setGroupedAvpCode(PROXY_INFO_AVP_CODE);
                throw avpLenErr;
            }
        }

        if (mAvpCode == FRAMED_IP_ADDR_AVP_CODE)
        {
            memcpy(_globalUniqAddr,pBuf+dataIndex, MAX_IP_STR_LEN); 
            break; 
        }

        tmpCounter+=mAvpLen;
        pBuf      +=tmpCounter;

        //align buffer to word byte
        mAvpLen = (mAvpLen % 4);
        if(mAvpLen)
        {
           pBuf      +=(4-mAvpLen);
           tmpCounter+=(4-mAvpLen);
        }
    }
}
int  
BaseCommand::removeAVP(unsigned int code)
{
    bool foundAVP = false;
    unsigned char* buffer = (unsigned char *)_enBuf;
    unsigned char* end    = (unsigned char*)(buffer+_enBufLen);
    unsigned int buffLen = 0;
    unsigned int avpCode = 0;
    unsigned int avpLen = 0;
 
    /* AVP_START_OFFSET or CMD_HDR_SIZE */
    buffer +=20;
    buffLen +=20;
 
    /* Parse AVPs */
    while((unsigned long)(buffer+8) <= (unsigned long)end)
    {
        avpCode = DataToApp(buffer, 4);
        /* 5 - AVP_LEN_OFFSET */
        avpLen = DataToApp(buffer+5, 3);
 
        /* align buffer to word byte */
        int tmp = (avpLen % 4);
        if (tmp)
        {
           avpLen += 4 - tmp;
        }
 
        if(avpCode == code)
        {
            foundAVP = true;
            break;
        }
        else
        {
            buffer += avpLen;
            buffLen += avpLen;
        }
    }
 
    if (foundAVP)
    {
        switch(avpCode)
        {
            case RCODE_AVP_CODE:
            case ROUTE_RECORD_AVP_CODE:
            case PROXY_INFO_AVP_CODE:
            case RD_HOST_AVP_CODE:
            case RD_HOST_USAGE_AVP_CODE:
            case RD_HOST_CACHE_AVP_CODE:
            {
                unsigned char* newEnBuf = 
                                (unsigned char*) malloc(_enBufLen - avpLen);
                if ( newEnBuf != NULL )
                {
                    unsigned char* tmpPtr = newEnBuf;
                    memcpy(tmpPtr, _enBuf, buffLen);
                    memcpy( tmpPtr+buffLen, buffer+avpLen,
                            _enBufLen - (buffLen + avpLen));
                   
                    if (_bufToDel != NULL)
                    {
                        free(_bufToDel);
                        _bufToDel = NULL;
                        _enBuf = newEnBuf;
                    }
                    else if (_enBuf != NULL)
                    {
                        free(_enBuf);
                        _enBuf = newEnBuf;
                    }
 
                    /* update the buffer length */
                    _enBufLen = _enBufLen - avpLen;
 
                    /* update the encoded buffer length */
                    AppToData((char*)&newEnBuf[1], _enBufLen, 3);
                    hdr.length = _enBufLen;
 
                    /* update the avp count and avp bitmap */
                    switch(avpCode)
                    {
                        case RCODE_AVP_CODE:
                        {
                            _avpBitMap &= ~(RCODE_AVP_BIT);
                        }
                        break;
                        case ROUTE_RECORD_AVP_CODE:
                        {
                            _routeRecCount--;
                            if (_routeRecCount == 0 )
                            {
                                _avpBitMap &= ~(ROUTE_RECORD_AVP_BIT);
                            }
                        }
                        break;
                        case PROXY_INFO_AVP_CODE:
                        {
                            _proxyCount--;
                            if (_proxyCount == 0 )
                            {
                                _avpBitMap &= ~(PROXY_INFO_AVP_BIT);
                            }
                        }
                        break;
                        case RD_HOST_AVP_CODE:
                        {
                            _rdHostCount--;
                            if (_rdHostCount == 0 )
                            {
                                _avpBitMap &= ~(RD_HOST_AVP_BIT);
                            }
                        }
                        break;
                        case RD_HOST_USAGE_AVP_CODE:
                        {
                                _avpBitMap &= ~(RD_HOST_USAGE_AVP_BIT);
                        }
                        break;
                        case RD_HOST_CACHE_AVP_CODE:
                        {
                            _avpBitMap &= ~(RD_HOST_CACHE_AVP_BIT);
                        }
                        break;
                    }
                }
                else
                {
                    //throw exception
                    return !ITS_SUCCESS;
                }
            }
            break;
 
            default:
                return !ITS_SUCCESS;
        }                  
        return ITS_SUCCESS;
    }
    else
    {
        return !ITS_SUCCESS;
    }
}

/*.implementation:
 ************************************************************************
 *  Purpose:
 *      To Debug the values inside a AVP_URI.
 *            
 ************************************************************************/

void
BaseCommand::PrintAVPURI(AVP_URI* uri)
{
    printf("\nURI AVP values are\n");
    printf("uri_scheme : %d\n", uri->scheme);
    printf("fqdn       : %s\n", uri->fqdn.value().c_str());
    printf("port       : %d\n", uri->port.value());
    printf("transport  : %d\n", uri->transport);
    printf("portocol   : %d\n", uri->protocol);
}

/*.implementation:
 *************************************************************************
 *     Purpose:
 *       To validate the Application and associated command code.
 *       This function can further be added with Applictio-Id's and 
 *        command code for validation         
 *************************************************************************/
int 
BaseCommand::validateComandCodeandAppId(unsigned int aAppId, unsigned int aCode)
{
   ITS_INT retVal= ITS_SUCCESS;

   if((DIA_MSG_AC == aCode) && (DIA_BASE_ACCOUNTING_APPID != aAppId))
   {
	retVal= (!ITS_SUCCESS);	 
   }
   return retVal;
}

}
