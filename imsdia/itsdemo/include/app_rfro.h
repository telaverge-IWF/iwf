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
 * LOG: $Log: app_rfro.h,v $
 * LOG: Revision 3.2  2010/06/24 08:20:12  nvijikumar
 * LOG: ims namespace removed
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.4  2006/11/22 10:55:46  hbhatnagar
 * LOG: transferred the definitions to app.h
 * LOG:
 * LOG: Revision 1.3  2006/10/30 15:30:30  hbhatnagar
 * LOG: changes made for dcca
 * LOG:
 * LOG: Revision 1.2  2006/10/17 09:18:40  yranade
 * LOG: Cleanup logs.
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * ID: $Id: app_rfro.h,v 3.2 2010/06/24 08:20:12 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app_rfro.h,v 3.2 2010/06/24 08:20:12 nvijikumar Exp $"

#ifndef __APP_RFRO_H__
#define __APP_RFRO_H__
                                                                                                                             
#include <dia_defines.h>
#include <dia_frame.h>
#include <diameter/rfro/CreditControl.h>
#include <app_trace.h>
#include <app.h>
#include <app_stats.h>
                                                                                                                             
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rfro;
//using namespace diameter::rfro::ims;
//using namespace diameter::rfro::ietf;
                                                                                                                             
void PopulateMultipleServicesCreditControl(
     MultipleServicesCreditControl &multipleServicesCC , bool isRequest);
void PopulateRequestedServiceUnit(RequestedServiceUnit &requestedServiceUnit);
void PopulateGrantedServiceUnit(GrantedServiceUnit &grantedServiceUnit);
void PopulateUsedServiceUnit(UsedServiceUnit &usedServiceUnit);
void PopulateCostInformation(CostInformation &costInfo);
void PopulateFinalUnitIndication(FinalUnitIndication &finalUnitInd);
void PopulateIPFilterRule(IPFilterRule &ipFltRule);
void PopulatePSFurnishChargingInformation
          (PSFurnishChargingInformation &psFurnishChrgInfo);

void PopulateServiceInformation(ServiceInformation &serviceInfo);
void PopulatePSInformation(PSInformation &psInfo);
void PopulateWLANInformation(WLANInformation &wlanInfo);

void PopulateIMSInformation(IMSInformation &imsInfo);
void PopulateMessageBody(MessageBody &mmContentType);
void PopulateEventType(EventType &eventType);
void PopulateApplicationServerInformation(ApplicationServerInformation
              &appServerInfo);
void PopulateSDPMediaComponent(SDPMediaComponent &mmContentType);
void PopulateServerCapabilities(ServerCapabilities &mmContentType);

void PopulateMMSInformation(MMSInformation &mmsInfo);
void PopulateOriginatorAddress(OriginatorAddress &originatorAddr);
void PopulateRecipientAddress(RecipientAddress &recipientAddr);
void PopulateMMContentType(MMContentType &mmContentType);

void PopulateLCSInformation(LCSInformation &lcsInfo);
void PopulateLCSClientID(LCSClientID &lcsClientId);

void PopulatePoCInformation(PoCInformation &pocInfo);
void PopulateMBMSInformation(MBMSInformation &mbmsInfo);

#endif /* __APP_RFRO_H__ */


