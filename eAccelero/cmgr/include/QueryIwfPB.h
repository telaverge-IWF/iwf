/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#ifndef QUERY_IWF_PB_H
#define QUERY_IWF_PB_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <driver.h>
#include <string.h>
#include <stdio.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <CommonStructure.h>
#include <config.h>

#include "iwfconfig_def.h"

#include <IWFLocalConfigTPB.h>
#include <IWFLocalSSNMappingTPB.h>
#include <IWFLocalSSNTPB.h>
#include <IWFProtocolFamilyTPB.h>
#include <IWFSigtranAssociationTPB.h>
#include <IWFSigtranAssocSetTPB.h>
#include <IWFSigtranMultihomingTPB.h>
#include <IWFSigtranDestinationTPB.h>
#include <IWFTranslatorRuleTPB.h>
#include <IWFSigtranSCTPProfileTPB.h>
#include <IWFSctpEndpointTPB.h>
#include <IWFSigtranAssocSetMappingTPB.h>
#include <IWFSigtranRemoteRouteTPB.h>
#include <IWFTranslatorTypeTPB.h>
#include <IWFTranslatorTPB.h>
#include <IWFMapS6aConfigTPB.h>
#include <IWFS6aMapConfigTPB.h>
#include <IWFCapRoConfigTPB.h>
#include <CapRoIdpConfigTPB.h>
#include <ExtTeleserviceToServiceIdMapTPB.h>
#include <ExtBearerserviceToServiceIdMapTPB.h>
#include <CapRoIdpSmsConfigTPB.h>
#include <IWFS6aMapSgsnAddrMapTPB.h>
#include <IWFTimerTPB.h>
#include <IWFSigtranAssocAssocSetMappingTPB.h>
#include <RealmTPB.h>
#include <IWFSigtranUalManagerTPB.h>
#include <IWFTranslatorRuleVplmnIdTPB.h>
#include <IWFMapS6aVplmnIdTPB.h>
#include <IWFMapS6aVplmnIdSgsnMapTPB.h>
#include <IWFFeatureTPB.h>
#include <IWFDccaGeneralTPB.h>
#include <IWFDccaEndPointsTPB.h>
#include <IWFProtocolActionTPB.h>
#include <IWFCallScenarioMappingTPB.h>
#include <IWFEventTypeMappingTPB.h>
#include <IWFEventTypeDetailsTPB.h>
#include <IWFS6aMapSgsnPrefixMapTPB.h>

class QueryIwf_PB: 
    public IWFLocalConfigTPBQuery,
    public IWFLocalSSNTPBQuery,
    public IWFProtocolFamilyTPBQuery,
    public IWFLocalSSNMappingTPBQuery,
    public IWFSigtranAssociationTPBQuery, 
    public IWFSigtranAssocSetTPBQuery,
    public IWFSigtranMultihomingTPBQuery,
    public IWFSigtranRemoteRouteTPBQuery,
    public IWFSigtranDestinationTPBQuery,
    public IWFSigtranSCTPProfileTPBQuery,
    public IWFSctpEndpointTPBQuery,
    public IWFTranslatorTypeTPBQuery,
    public IWFTranslatorTPBQuery,
    public IWFSigtranAssocSetMappingTPBQuery,
    public IWFMapS6aConfigTPBQuery,
    public IWFS6aMapConfigTPBQuery,
    public IWFCapRoConfigTPBQuery,
    public CapRoIdpConfigTPBQuery,
    public ExtTeleserviceToServiceIdMapTPBQuery,
    public ExtBearerserviceToServiceIdMapTPBQuery,
    public CapRoIdpSmsConfigTPBQuery,
    public IWFS6aMapSgsnAddrMapTPBQuery,
    public IWFTimerTPBQuery,
    public IWFFeatureTPBQuery,
    public IWFDccaGeneralTPBQuery,
    public IWFDccaEndPointsTPBQuery,
    public IWFSigtranAssocAndAssocSetTPBQuery,
    public RealmTPBQuery,
    public IWFTranslatorRuleTPBQuery,
    public IWFSigtranUalManagerTPBQuery,
    public IWFTranslatorRuleVplmnIdTPBQuery,
    public IWFMapS6aVplmnIdTPBQuery,
    public IWFMapS6aVplmnIdSgsnMapTPBQuery,
    public IWFCallScenarioMappingTPBQuery,
    public IWFEventTypeDetailsTPBQuery,
    public IWFEventTypeMappingTPBQuery,
    public IWFProtocolActionTPBQuery,
    public IWFS6aMapSgsnPrefixMapTPBQuery{};
    


#endif

