/*********************************-*-Dia-*-**********************************
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
 * LOG: $Log: ro_defines.h,v $
 * LOG: Revision 1.1.4.2  2014/02/12 07:37:16  millayaraja
 * LOG: new interface ro_r10 for IWF
 * LOG:
 * LOG: Revision 1.1.2.2  2013/07/09 11:11:02  jkchaitanya
 * LOG: changes for supporting json configuration for ro_r10 tool
 * LOG:
 * LOG: Revision 1.1.2.1  2013/07/03 06:32:43  jkchaitanya
 * LOG: changes for ro release 10 test tool changes and make file changes
 * LOG:
 * LOG: Revision 1.1.2.1.38.1  2013/06/06 05:51:33  vsarath
 * LOG: Added for the new call flow for load
 * LOG:
 * LOG: Revision 1.1.2.1  2012/07/09 06:00:13  pramana
 * LOG: Added to support release 10 (Bug 49).
 * LOG:
 * LOG: Revision 1.1  2011/03/10 09:27:34  vkumara
 * LOG: Sample Demo for Ro Interface
 * LOG:
 * LOG:
 *
 * ID: $Id: ro_defines.h,v 1.1.4.2 2014/02/12 07:37:16 millayaraja Exp $
 ****************************************************************************/
#ident "$Id: ro_defines.h,v 1.1.4.2 2014/02/12 07:37:16 millayaraja Exp $"

#ifndef _SAMPLE_ROAPP_DEFINE
#define _SAMPLE_ROAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

#include <diameter/ro_r10/CreditControl.h>
#include <diameter/ro_r10/AC.h>
#include <diameter/ro_r10/ReAuth.h>

#include <fstream>
#include <string>
#include <json/json.h>

using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::ro_r10;


/* Defines for ACR */
#define START          1
#define INTERIM        2
#define STOP           3
#define EVENT          4
#define START_AUTHSESS 5
#define EVENT_AUTHSESS 6


/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define RO_INTERFACE_APP_ID      4
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for Ro interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define RO_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For Ro Interface
 **/
#define RO_CC_MSG_CMD_CODE        272
#define RO_AC_MSG_CMD_CODE        271
#define RO_RA_MSG_CMD_CODE        258

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

Json::Value parseS6aConfig();
/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Ro Protocol messages to 
 *      the diameter stack. These will create the appropriate Ro protocol 
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
extern int SendRoCreditControlRequest(int requestType,
                               const diameter::CommandImpl* impl = NULL,
                               std::string aSessIdString = "");
extern int SendRoACRequest(int requestType,const diameter::CommandImpl* impl = NULL);
extern int SendRoRARequest(std::string sessionId = "server@3gpp.org");

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Ro Protocol messages to 
 *      the diameter stack. These will create the appropriate Ro protocol 
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
extern int SendRoCreditControlAnswer(const diameter::CommandImpl* impl );
extern int SendRoACAnswer(const diameter::CommandImpl *impl);
extern int SendRoRAAnswer(const diameter::CommandImpl *impl);

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to populate the Ro Protocol grouped AVPs. 
 *      These will populate the appropriate Ro protocol 
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

