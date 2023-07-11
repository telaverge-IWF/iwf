/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_dict_parse.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.3  2006/11/07 11:18:38  kamakshilk
 * LOG: codec library separated from stack library
 * LOG:
 * LOG: Revision 1.2  2006/10/25 13:25:31  tpanda
 * LOG: For extensible AVP support
 * LOG:
 * LOG: Revision 1.1  2006/10/05 06:15:50  tpanda
 * LOG: Enable dictionary parsing for extensible AVPs
 * LOG:
 * ID: $Id: dia_dict_parse.h,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dia_dict_parse.h,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $"

#ifndef DIA_DICT_PARSER_H_
#define DIA_DICT_PARSER_H_

#include <map>

#include <its_types.h>

#define DIA_DICT_STRING                  "dictionary"
#define DIA_DICT_CMD_STRING              "command"
#define DIA_DICT_NAME_STRING             "name"
#define DIA_DICT_CODE_STRING             "code"
#define DIA_DICT_APPID_STRING            "appId"
#define DIA_DICT_AVPINDEX_STRING         "avpIndex"

#define DIA_DICT_REQ_STRING              "req"
#define DIA_DICT_ANS_STRING              "ans"
#define DIA_DICT_AVPRULE_STRING          "avprule"

#define DIA_DICT_AVP_STRING              "avp"
#define DIA_DICT_MAND_STRING             "mand"
#define DIA_DICT_ENCR_STRING             "encr"
#define DIA_DICT_VENID_STRING            "venId"
#define DIA_DICT_TYPE_STRING             "type"
#define DIA_DICT_REQUIRED_STRING         "required"
#define DIA_DICT_OPTIONAL_STRING         "optional"

void DiaDictParserInitialize(const char* filename="dictionary.xml");


#endif


