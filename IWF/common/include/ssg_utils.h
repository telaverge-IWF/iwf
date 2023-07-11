/*********************************-*-H-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 * ID: $Id: ssg_utils.h,v 1.1.1.1 2013/01/09 16:41:38 brajappa Exp $
 *
 * LOG: $Log: ssg_utils.h,v $
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:38  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 ****************************************************************************/

#ifndef SSG_UTILS_H
#define SSG_UTILS_H

#include <ssg_defines.h>
#include <ssg_trace.h>
#include <Asn.h>
#include <AsnException.h>
#include <AsnObject.h>
#include <Octets.h>

void PrintEvent(ITS_EVENT* evt);
void PrintHex(const unsigned char*data, int len);

#define MAX_AC_NAME 7

class SsgUtils
{
public:
    SsgUtils() {}

    ~SsgUtils() {}

    static void ConvertOctsToString(char** str, ITS_OCTET* octs,
                                    int len, ITS_BOOLEAN eFlag);

    static void ConvertBCDToAscii(char* asciidata, char* bcddata,
                                                 ITS_INT bcdlen);

    static void ConvertAsciiToBCD(ITS_OCTET* bcgarr, ITS_OCTET *asciidata,
                                                        ITS_INT asciilen);

    static void ConvertStringToOctets(ITS_OCTET* octs, std::string& str,
                                  int& gtt_len, ITS_BOOLEAN& eFlag);

    static void ConvertStringToOctets(ITS_OCTET* octs, char* str,
                                  int& gtt_len, ITS_BOOLEAN& eFlag);
    static void ConvertToByteArray(ByteArray &array, char *digits, 
                                          ITS_OCTET npnValue = 0);

    static void ConvertToFixedByteArray(ByteArray &array, char *digits,int len,
                                           ITS_OCTET npnValue = 0);

    static void ConvertToMSCIDByteArray(ByteArray &array, char *digits);
    
     static void ConvertToMINByteArray(ByteArray &array, char *digits);

    static int CompareStrings(const string& s1, const string& s2);
 
    static void DecodeIsdnString(std::vector<ITS_OCTET> isdnData, 
				    char *digits);

    static void DecodeLocationNumber(std::vector<ITS_OCTET> locationData, 
				    char *digits);
    static void DecodeBCDString(std::vector<ITS_OCTET> isdnData, 
				    char *digits);
    static void EncodeSsgMsg(AsnObject* p, Octets** octets);
};
#endif
