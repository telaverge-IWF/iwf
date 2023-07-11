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
 * LOG: $Log: app_dcca.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/11/24 20:15:00  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:50:27  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/27 09:34:12  hbhatnagar
 * LOG: Fix for Bug ID: 4383 and cleaning (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:17  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_dcca.h,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $"

#ifndef __APP_DCCA_H__
#define __APP_DCCA_H__
                                                                                                                             
#include <dia_defines.h>
#include <dia_frame.h>

#ifdef _BCGI
#include <diameter/bcgi/CreditControl.h>
#else
#include <diameter/dcca/CreditControl.h>
#endif

#include <app_trace.h>
#include <app.h>
#include <dcca_stats.h>       

using namespace diameter;
using namespace diameter::base;                                                                                         
using namespace diameter::dcca;

void PopulateMultipleServicesCreditControl(
     MultipleServicesCreditControl &multipleServicesCC , bool isRequest);
void PopulateRequestedServiceUnit(RequestedServiceUnit &requestedServiceUnit);
void PopulateGrantedServiceUnit(GrantedServiceUnit &grantedServiceUnit);
void PopulateUsedServiceUnit(UsedServiceUnit &usedServiceUnit);
void PopulateCostInformation(CostInformation &costInfo);
void PopulateFinalUnitIndication(FinalUnitIndication &finalUnitInd);
void PopulateIPFilterRule(IPFilterRule &ipFltRule);


#endif /* __APP_DCCA_H__ */


