/*********************************-*-C-*-************************************
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
 *
 * LOG: $Log: app_const.h,v $
 * LOG: Revision 1.1.2.1  2013/08/21 12:14:15  jkchaitanya
 * LOG: sub directories in capsim
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/06/10 07:07:55  jsarvesh
 * LOG: enhanced for Load Run from MAP-Tool
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/02/14 09:55:16  brajappa
 * LOG: ISD sending withing UGLA is handled through command line, handling readyForSM
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_const.h,v 1.1.2.1 2013/08/21 12:14:15 jkchaitanya Exp $"

#ifndef _TEST_CONST_H
#define _TEST_CONST_H

#include <its.h>
#include <strings.h>
#include <string.h>

enum VariantSet
{
    APP_ANSI=1,
    APP_CCITT
};

/* TCAP SRC same as stack */
#define APP_TCAP_CCITT_SRC          (0xFFFCU)
#define APP_TCAP_ANSI_SRC           (0xFFFDU)


#define SEND_UNI           1 
#define SEND_BEGIN         2
#define SEND_END           3
#define SEND_CONTINUE      4
#define SEND_ABORT         5
#define DUMP_RT            6
#define SEND_PRE_END       7
#define SEND_LOOP          8


#define SEND_VALID_CHOICE(x)     ((x >= 0) && (x <= 19))
#define VALID_MODE_CHOICE(x)     ((x >= 1) && (x <= 2))

#define CONFIG_SSN            254

#define ISG_CONFIG_SRC        0x83U
#define CONFIG_DIRECTIVE      0x61U
#define CONFIG_DIRECTIVE_LAST 0x62U
#define CONFIG_CONNECT        0x64U
#define CONFIG_ADD_IMSI       0x66U
#define SGAP_POINT_CODE       0x72U
#define SGAP_GTS              0x75U

//update location arg  len=32.
#define LOC_ARG_LEN 137
//Subscriber arg.
#define SUB_ARG_LEN 144
//Authenticationarg
#define AUTH_ARG_LEN 68

enum ApplicationMode
{
    UNIT_TEST = 1,
    LOAD_TEST = 2
};


namespace itstest
{
      extern ITS_UINT    opc;

      extern ITS_UINT    dpc;

      extern ITS_UINT    apc;

      extern ITS_USHORT  ossn;

      extern ITS_USHORT  dssn;

      extern ITS_BOOLEAN routeType;

      extern char* oE164;

      extern char* dE164;

      extern ITS_INT     oE164_len;

      extern ITS_INT     dE164_len;

      extern ITS_INT     isSender;

      extern ITS_INT     numThreads;

      extern bool        noISD;

      extern ITS_OCTET   AC_NAME[];

      extern ITS_OCTET   USER_INFO[];

      extern ITS_OCTET   LocationArg[];

      extern ITS_OCTET   AuthenticationArg[];

      extern ITS_OCTET   SubscribeArg[];

      extern ITS_OCTET   octs185[];

      extern ITS_UINT    borderMask;

      extern ITS_BOOLEAN interactive;
     
      extern ITS_INT     numMsgs;

      extern time_t      startTime;

      extern time_t      stopTime;

      extern int         msgCount;

      extern bool        enableTrace;

      extern ApplicationMode appMode;

      static inline void setOPC(ITS_UINT pc)
      {
          itstest::opc = pc;
      }

      static inline void setDPC(ITS_UINT pc)
      {
          itstest::dpc = pc;
      }

      static inline void setAPC(ITS_UINT pc)
      {
          itstest::apc = pc;
      }

      static inline void setOSSN(ITS_USHORT ssn)
      {
          itstest::ossn = ssn;
      }

      static inline void setDSSN(ITS_USHORT ssn)
      {
          itstest::dssn = ssn;
      }

      static inline void setNumThreads(ITS_INT num)
      {
          itstest::numThreads = num;
      }

      static inline void setSender()
      {
           itstest::isSender = 1;
      }

      static inline void setOE164(char* str)
      {
           itstest::oE164 = strdup(str);

           itstest::oE164_len = strlen(str);
      }

      static inline void setDE164(char* str)
      {
           itstest::dE164 = strdup(str);

           itstest::dE164_len = strlen(str);
      }

      static inline void setRouteByGTT()
      {
          itstest::routeType = ITS_FALSE;
      }

      static inline void setNumMsgs(ITS_INT num)
      {
           itstest::numMsgs = num;
      }

      ITS_INT PrintMenu();
      ITS_INT GetOption();
      ITS_INT PrintSCCPMenu();
      ITS_INT PrintSCCPResponsesMenu();
};

#endif
