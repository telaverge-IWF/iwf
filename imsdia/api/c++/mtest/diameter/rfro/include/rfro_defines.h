/*********************************-*-Dia-*-**********************************
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
 * LOG: $Log: rfro_defines.h,v $
 * LOG: Revision 3.2  2010/06/24 08:37:04  nvijikumar
 * LOG: removed ims name space
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:42:08  kamakshilk
 * LOG: RfRo interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: rfro_defines.h,v 3.2 2010/06/24 08:37:04 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: rfro_defines.h,v 3.2 2010/06/24 08:37:04 nvijikumar Exp $"

#ifndef _SAMPLE_RFROAPP_DEFINE
#define _SAMPLE_RFROAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

#include <diameter/rfro/CreditControl.h>
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::rfro;
//using namespace diameter::rfro::ims;

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define RFRO_INTERFACE_APP_ID    4
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for RfRo interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define RFRO_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For RfRo Interface
 **/
#define RFRO_CC_MSG_CMD_CODE        272
#define RFRO_AC_MSG_CMD_CODE        271

#define INITIAL       1
#define UPDATE        2
#define TERMINATION   3
#define EVENT         4

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to display the menu options for the
 *      respective protocol interface.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the option selected.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int DisplayAppMenu();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the RfRo Protocol messages to 
 *      the diameter stack. These will create the appropriate RfRo protocol 
 *      Request Command objects, populate the AVPs and sends the 
 *      message to the stack.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int SendCreditControlRequestInitial();
extern int SendRfRoCreditControlRequest(int requestType,
                               const diameter::CommandImpl* impl = NULL);
extern int SendRfRoACRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the RfRo Protocol messages to 
 *      the diameter stack. These will create the appropriate RfRo protocol 
 *      Answer Command objects, populate the AVPs and sends the 
 *      message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int SendRfRoCreditControlAnswer(const diameter::CommandImpl* impl );
extern int SendRfRoACAnswer(const diameter::CommandImpl *impl);

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to populate the RfRo Protocol grouped AVPs. 
 *      These will populate the appropriate RfRo protocol 
 *      grouped AVPs and returns the AVP objects. 
 *
 *  Input Parameters:
 *      : Reference to the grouped AVP object which needs to be populated.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
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

#endif

