/*********************************-*-C-*-************************************
 *                                                                           *
 *           Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                 *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                           *
 *    This product and related documentation is protected by copyright and   *
 *    distributed under licenses restricting its use, copying, distribution  *
 *    and decompilation.  No part of this product or related documentation   *
 *    may be reproduced in any form by any means without prior written       *
 *    authorization of Diametriq and its licensors, if any.                  *
 *                                                                           *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *    government is subject to restrictions as set forth in subparagraph     *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                           *
 *****************************************************************************/


#ifndef QUERY_PB_H
#define QUERY_PB_H

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

//#include <LocalHostConfigTPB.h>
#include <LocalHostConfigTPB.h>
#include <LocalHostTAndTransportTPB.h>
#include <LocalHostConfigSingleRow.h>
#include <LocalTransportTPB.h>
#include <PeerTAndTimersTPB.h>
#include <PeerTPB.h>
#include <PeerTimersTPB.h>
#include <RealmRoutingTPB.h>
#if 0
#include <DefaultRouteTPeerPB.h>
#endif
#include <DefaultRouteTRealmPB.h>
#include <RealmTPB.h>
#include <RealmRoutingTAndDefaultRouteTPB.h>
#include <RealmTRealmRoutingTAndDefaultRouteTPB.h>
#include <PeerDictionaryMapTPB.h>
#include <DictionaryTPB.h>
#include <DictionaryTPeerPB.h>
#include <PeerGroupMapTLbAlgorithmTPB.h>
#include <LbAlgorithmTPB.h>
#include <PeerGroupTPB.h>
#include <PeerGroupMapTPB.h>
#include <UserTPB.h>
#include <UserTAndRoleTPB.h>
#include <LoggingConfigTPB.h>
#include <TracingTPB.h>
#include <TracingFilterTPB.h>
#include <AvailabilityManagerConfigTPB.h>
#include <TLSConfigTPB.h>
#include <StackGeneralConfigTPB.h>
#include <SCTPConfigTPB.h>
#include <CipherSuiteTPB.h>
#include <TrustedCATPB.h>
#include <ApplicationGroupTPB.h>
#include <ApplicationGroupTAndLbAlgorithmTPB.h>
#include <AsfConfigTPB.h>
#include <MultiHomingTPB.h>
#include <PeerMultiHomingTPB.h>
#include <StaticRouteTPB.h>
#include <StaticRouteTAndPeerTPB.h>
#include <ThfTPB.h>
#include <ThfRealmTPB.h>
#include <ThfVHostsTPB.h>
#include <CmfDiaPeerTemplateTPB.h>
#include <CmfDiaRealmTemplateTPB.h>
#include <UserDetailTPB.h>
#include <RoleTPB.h>
#include <PrevilegeTPB.h>
#include <RolePrevilegeMapTPB.h>
#include <EmailServerTPB.h>
#include <IdentityServerTPB.h>
#include <EmailContentTPB.h>
#include <TransformPluginTPB.h>
#include <CongestionRulesTPB.h>
#include <CMFTriggerTPB.h>
#include <CMFActionsTPB.h>
#include <CMFLevelTPB.h>
#include <CMFTriggerActionMapTPB.h>
#include <CMFDiaCCPriorityTPB.h>
#include <CMFDiaAppIdPriorityTPB.h>
#include <SDTFRulesTPB.h>
#include <LocalTransportTagTPB.h>
#include <FeatureStatusTPB.h>

class Query_PB : public LocalHostConfigTPBQuery,
    public LocalTransportTPBQuery,
    public LocalHostTAndTransportTPBQuery,
    public LocalHostConfigSingleRowTPBQuery,
    public PeerTAndTimerTPBQuery,
    public PeerTPBQuery,
    public PeerTimersTPBQuery,
    public RealmRoutingTPBQuery,
    public DefaultRouteTRealmPBQuery,
    public RealmTPBQuery,
    public RealmRoutingTAndDefaultRouteTPBQuery,
    public RealmTRealmRoutingTAndDefaultRouteTPBQuery,
    public PeerGroupMapAndPeerGrpAndLbAlgorithmTPBQuery,
    public LbAlgorithmTPBQuery,
    public PeerGroupTPBQuery,
    public PeerGroupMapTPBQuery,
    public PeerDictionaryMapTPBQuery,
    public DictionaryTPBQuery,
    public DictionaryTPeerPBQuery,
    public UserTPBQuery,
    public UserTAndRoleTPBQuery,
    public LoggingConfigTPBQuery,
    public TracingTPBQuery,
    public TracingFilterTPBQuery,
    public TrustedCAConfigTPBQuery,
    public CipherSuiteConfigTPBQuery,
    public SCTPConfigTPBQuery,
    public StackGeneralConfigTPBQuery,
    public TLSConfigTPBQuery,
    public ASFTPBQuery,
    public ASFTAndLbAlgoPBQuery,
    public ASFConfigTPBQuery,
    public MultiHomingTPBQuery,
    public PeerMultiHomingTPBQuery,
    public StaticRouteTPBQuery,
    public StaticRouteTAndPeerTPBQuery,
    public ThfTPBQuery,
    public THFRealmTPBQuery,
    public THFVHostsTPBQuery,
    public CmfDiaPeerTemplateTPBQuery,
    public CmfDiaRealmTemplateTPBQuery,
    public UserDetailTPBQuery,
    public RoleTPBQuery,
    public PrevilegeTPBQuery,
    public RolePrevilegeMapTPBQuery,
    public EmailServerTPBQuery,
    public IdentityServerTPBQuery,
    public EmailContentTPBQuery,
    public TransformPluginTPBQuery,
    public AvailabilityManagerConfigTPBQuery,
    public CongestionRulesTPBQuery,
    public CmfTriggerTPBQuery,
    public CmfActionTPBQuery,
    public CmfLevelTPBQuery,
    public CmfTriggerActionMappingTPBQuery,
    public CmfDiaCCPriorityTPBQuery,
    public CmfDiaAppIdPriorityTPBQuery,
    public SDTFRulesTPBQuery,
    public LocalTransportTagTPBQuery,
    public FeatureStatusTPBQuery {};
#endif
