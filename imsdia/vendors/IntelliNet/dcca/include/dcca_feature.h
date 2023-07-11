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
 * LOG: $Log: dcca_feature.h,v $
 * LOG: Revision 3.2.22.1.48.1  2014/10/27 08:28:37  pramana
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.2.22.1  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.2.24.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.2  2008/12/12 18:07:05  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.2  2006/11/14 10:24:21  nvijikumar
 * LOG: Define is moved to dia_defines.h file.
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_feature.h,v 3.2.22.1.48.1 2014/10/27 08:28:37 pramana Exp $
 *
 ****************************************************************************/

#ifndef DCCA_FEATURE_H
#define DCCA_FEATURE_H
/**
 * Includes
 */
#include <its++.h>
#include <dia_defines.h>
#include <diameter/Command.h>

/**
 * Defines
 */

/**
 * Access definitions for DIA
 */
/*typedef ITS_INT (*DCCA_ACCESS_FP) (diameter::BaseCommand*, 
                                         ITS_UINT, ITS_UINT, ITS_UINT);
                                         */
typedef ITS_INT (*DCCA_ACCESS_FP) (DIA_BASE_CMD*, 
                                         ITS_UINT, ITS_UINT, ITS_UINT);

extern DCCA_ACCESS_FP DCCAAccessFp;

typedef ITS_INT (*DCCA_ACCESS_IND_FP) (ITS_UINT, ITS_OCTET*, ITS_UINT, ITS_UINT);

extern DCCA_ACCESS_IND_FP DCCAAccessIndFp;

#endif
