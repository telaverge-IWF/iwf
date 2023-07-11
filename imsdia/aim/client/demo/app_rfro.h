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
 * LOG: Revision 3.2  2010/06/25 08:25:15  nvijikumar
 * LOG: Updates for release 8
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/11/08 15:02:39  hbhatnagar
 * LOG: Changes to work with DCCA state Machine
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:23:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/06/21 10:11:04  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.2  2006/06/12 08:06:01  kamakshilk
 * LOG: Dia defines and dia Frame header file inclusion removed
 * LOG:
 * LOG: Revision 1.1  2006/06/09 13:40:17  kamakshilk
 * LOG: RfRo functions prototype
 * LOG:
 *
 * ID: $Id: app_rfro.h,v 3.2 2010/06/25 08:25:15 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app_rfro.h,v 3.2 2010/06/25 08:25:15 nvijikumar Exp $"

#ifndef __APP_RFRO_H__
#define __APP_RFRO_H__

#include <diameter/rfro/CreditControl.h>
#include <app.h>

using namespace std;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::rfro;
//using namespace diameter::rfro::ims;

#define INITIAL       1
#define UPDATE        2
#define TERMINATION   3
#define EVENT         4

                                                                                                                             
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


