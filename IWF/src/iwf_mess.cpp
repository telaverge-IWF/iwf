#include <fstream>
#include <unordered_map>

#include "its++.h"
#include "its_timers.h"
#include "engine++.h"

#include "HAMeSSComponent.h"
#include "iwf_mess.h"
#include <dia_peer_table.h>
#include "its.h"
#include "MeSSDef.h"
#include "ErrorResp.h"
#include "IwfErrorResp.h"
#include "iwf.h"
#include "iwf_transport_controller.h"

using namespace its;
using namespace engine;
using namespace std;
using namespace eAccelero;

#define BASE_INTERFACE_APP_ID    0
#define ITS_AS_SRC   (0xFFF1U)

std::map<int,std::string> IwfMeSS::errorMap;

void IwfMeSS::Run(void* arg)
{
    Init(3, m_argv);
    CLOG_DEBUG("Staring IwfMeSS thread");
    m_cond.signal();
    HAMeSSComponent::Run();
    exit(0);
}

int IwfMeSS::ProcessComponentStatusUpdate(uint16_t componentId, 
        eAccelero::HAComponentStatus newStatus)
{
    //If CMGR is initialized then signal IWF to proceed with Config fetch.
    if(componentId == COMP_CONFIG_MANAGER && newStatus == 
            COMPONENT_STATUS_INITIALIZED)
    {    
        CLOG_DEBUG("Going ahead with initializtion since received an update that CMGR is initialized.");
        IwfController::SetUpdateFromAvaMgr(componentId,newStatus);
    }    
    return 0;
}

void IwfMeSS::PopulateErrorMap()
{

    IwfMeSS::errorMap[MOD_PEER_ERR_PEER_STATICALLY_CONFIGURED]=std::string("mod.peer.err.peer.statically.configured");
    IwfMeSS::errorMap[MOD_PEER_ERR_PEER_IN_OPEN_STATE]=std::string("mod.peer.err.peer.in.open.state");
    IwfMeSS::errorMap[SET_PEER_ERR_MAX_TRANSPORTS_REACHED]=std::string("set.peer.err.max.transports.reached");
    IwfMeSS::errorMap[SET_PEERSTATUS_ERR_PEER_NOT_IN_CLOSED_STATE]=std::string("set.peerstatus.err.peer.not.in.closed.state");
    IwfMeSS::errorMap[SET_PEERSTATUS_ERR_DISC_FAIL_SENDING_DPR_FAILED]=std::string("set.peerstatus.err.disc.fail.sending.dpr.failed");
    IwfMeSS::errorMap[DEL_PEER_ERR_PEER_CONFIGURED_IN_FILE]=std::string("del.peer.err.peer.configured.in.file");
    IwfMeSS::errorMap[DEL_PEER_ERR_PEER_NOT_IN_CLOSED_STATE]=std::string("del.peer.err.peer.not.in.closed.state");
    IwfMeSS::errorMap[MOD_REALM_ERR_CANNOT_MODIFY_REALM]=std::string("mod.realm.err.cannot.modify.realm");
    IwfMeSS::errorMap[MOD_REALM_ERR_REALM_NOT_PRESENT]=std::string("mod.realm.err.realm.not.present");
    IwfMeSS::errorMap[SET_REALM_ERR_INVALID_REALM]=std::string("set.realm.err.invalid.realm");
    IwfMeSS::errorMap[SET_DEST_ERR_REALM_NOT_PRESENT]=std::string("set.dest.err.realm.not.present");
    IwfMeSS::errorMap[SET_DEST_ERR_MAX_NO_OF_DEST_PER_REALM_REACHED]=std::string("set.dest.err.max.no.of.dest.per.realm.reached");
    IwfMeSS::errorMap[DEL_REALM_ERR_CANNOT_MODIFY_REALM_IN_XML]=std::string("del.realm.err.cannot.modify.realm.in.config.file");
    IwfMeSS::errorMap[DEL_DEST_ERR_COMB_APPID_VENDID_PRIORITY_NOT_FOUND]=std::string("del.dest.err.comb.AppId.VendId.Priority.not.found");
    IwfMeSS::errorMap[ADD_DICTID_ERR_LOAD_DICTIONARY_FAILED]=std::string("add.dictid.err.load.dictionary.failed");
    IwfMeSS::errorMap[ADD_DICTID_ERR_INVALID_DICT_COUNT]=std::string("add.dictid.err.invalid.dict.count");
    IwfMeSS::errorMap[ADD_DICTID_ERR_PEER_NOT_PRESENT]=std::string("add.dictid.err.peer.not.present");

    IwfMeSS::errorMap[DEL_SECONDARYIP_ERR_PEER_NOT_IN_CLOSED_STATE]=std::string("del.secondaryip.err.peer.not.in.closed.state");
    IwfMeSS::errorMap[DEL_SECONDARYIP_ERR_NOT_ALL_PARAMETERS_PRESENT]=std::string("del.secondaryip.err.not.all.parameters.present");
    IwfMeSS::errorMap[DEL_SECONDARYIP_ERR_UNKNOWN_PEER]=std::string("del.secondaryip.err.unknown.peer");
    IwfMeSS::errorMap[MOD_PEER_ERR_PEER_MAX_SEC_IPS_CONFIGURED]=std::string("mod.peer.err.peer.max.sec.ips.configured");
    IwfMeSS::errorMap[MOD_STATIC_ROUTING_MANDATORY_DESTHOST_PEERNAME_MISSING]=std::string("mod.static.routing.mandatory.desthost.peername.missing");
    IwfMeSS::errorMap[MOD_STATIC_ROUTING_ERR_ROUTE_NOT_PRESENT]=std::string("mod.static.routing.err.route.not.present");
    IwfMeSS::errorMap[ADD_STATIC_ROUTING_ERR_ROUTE_ALREADY_PRESENT]=std::string("add.static.routing.err.route.already.present");
    IwfMeSS::errorMap[ADD_STATIC_ROUTING_MANDATORY_PARAMETERS_MISSING]=std::string("add.static.routing.err.mandatory.parameter.missing");
    IwfMeSS::errorMap[DEL_STATIC_ROUTING_ERR_ROUTE_DOESNT_EXIST]=std::string("del.static.routing.err.route.doesnt.exist");
    IwfMeSS::errorMap[DEL_STATIC_ROUTING_MANDATORY_DESTHOST_PEERNAME_MISSING]=std::string("del.static.routing.mandatory.desthost.peername.missing");

    /* Sigtran and IWF application Error Codes */
    IwfMeSS::errorMap[MOD_LOCALHOST_ERR_SSN_NOT_PRESENT]=std::string("mod.localhost.err.ssn.not.present");
    IwfMeSS::errorMap[MOD_LOCALHOST_ERR_DATA_NOT_SET]=std::string("mod.localhost.err.data.not.set");
    IwfMeSS::errorMap[MOD_LOCALHOST_ERR_SSN_HOSTID_ALREADY_MAPPED]=std::string("mod.localhost.err.ssn.hostid.already.mapped");
    IwfMeSS::errorMap[SET_LOCALHOST_ERR_SSN_NOT_PRESENT]=std::string("set.localhost.err.ssn.not.present");
    IwfMeSS::errorMap[SET_LOCALHOST_ERR_DATA_NOT_SET]=std::string("set.localhost.err.data.not.set");
    IwfMeSS::errorMap[SET_LOCALHOST_ERR_SSN_HOSTID_ALREADY_MAPPED]=std::string("set.localhost.err.ssn.hostid.already.mapped");
    IwfMeSS::errorMap[DEL_SCTPENDPOINT_ERR_NOT_PRESENT]=std::string("del.sctpendpoint.err.not.present");
    IwfMeSS::errorMap[DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION]=std::string("del.sctpendpoint.err.used.in.association");
    IwfMeSS::errorMap[DEL_SCTPENDPOINT_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MULTIHOMING_IP]=std::string("del.sctpendpoint.err.used.in.association.and.association.in.multihoming.ip");
    IwfMeSS::errorMap[MOD_SCTPENDPOINT_ERR_NOT_PRESENT]=std::string("mod.sctpendpoint.err.not.present");
    IwfMeSS::errorMap[MOD_SCTPENDPOINT_ERR_IP_PORT_ALREADY_PRESENT]=std::string("mod.sctpendpoint.err.ip.port.already.present");
    IwfMeSS::errorMap[MOD_SCTPENDPOINT_ERR_ASSOCIATION_IN_ACTIVE_STATE]=std::string("mod.sctpendpoint.err.association.in.active.state");
    IwfMeSS::errorMap[MOD_SCTPENDPOINT_ERR_DATA_NOT_SET]=std::string("mod.sctpendpoint.err.data.not.set");
    IwfMeSS::errorMap[ADD_SCTPENDPOINT_ERR_ALREADY_PRESENT]=std::string("add.sctpendpoint.err.already.present");
    IwfMeSS::errorMap[ADD_SCTPENDPOINT_ERR_IP_PORT_ALREADY_PRESENT]=std::string("add.sctpendpoint.err.ip.port.already.present");
    IwfMeSS::errorMap[ADD_SCTPENDPOINT_ERR_DATA_NOT_SET]=std::string("add.sctpendpoint.err.data.not.set");
    IwfMeSS::errorMap[DEL_SCTPPROFILE_ERR_NOT_PRESENT]=std::string("del.sctpprofile.err.not.present");
    IwfMeSS::errorMap[DEL_SCTPPROFILE_ERR_USER_CANNOT_DELETE_DEFAULT_CONFIGURATION]=std::string("del.sctpprofile.err.user.cannot.delete.default.configuration");
    IwfMeSS::errorMap[DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION]=std::string("del.sctpprofile.err.used.in.association");
    IwfMeSS::errorMap[DEL_SCTPPROFILE_ERR_USED_IN_ASSOCIATION_AND_ASSOCIATION_IN_MUTIHOMING_IP]=std::string("del.sctpprofile.err.used.in.association.and.association.in.mutihoming.ip");
    IwfMeSS::errorMap[MOD_SCTPPROFILE_ERR_NOT_PRESENT]=std::string("mod.sctpprofile.err.not.present");
    IwfMeSS::errorMap[MOD_SCTPPROFILE_ERR_ASSOCIATION_IN_ACTIVE_STATE]=std::string("mod.sctpprofile.err.association.in.active.state");
    IwfMeSS::errorMap[ADD_SCTPPROFILE_ERR_ALREADY_PRESENT]=std::string("add.sctpprofile.err.already.present");
    IwfMeSS::errorMap[DEL_ASSOCIATIONSET_ERR_NO_PRESENT]=std::string("del.associationset.err.no.present");
    IwfMeSS::errorMap[DEL_ASSOCIATIONSET_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE]=std::string("del.associationset.err.associationset.in.active.state");
    IwfMeSS::errorMap[DEL_ASSOCIATIONSET_ERR_USED_IN_ROUTE]=std::string("del.associationset.err.used.in.route");
    IwfMeSS::errorMap[DEL_ASSOCIATIONSET_ERR_IS_ASSOCIATED]=std::string("del.associationset.err.is.associated");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_NO_PRESENT]=std::string("mod.associationset.err.no.present");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_ASSOCIATIONSET_IN_ACTIVE_STATE]=std::string("mod.associationset.err.associationset.in.active.state");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_ALREADY_ENABLED]=std::string("mod.associationset.err.already.enabled");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_NOT_CONTAIN_ANY_ASSOCIATION]=std::string("mod.associationset.err.not.contain.any.association");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_ALREADY_PRESENT]=std::string("add.associationset.err.already.present");
    IwfMeSS::errorMap[GET_ASSOCIATIONSET_ERR_NO_DATA]=std::string("get.associationset.err.no.data");
    IwfMeSS::errorMap[GET_ASSOCIATIONSET_MAPPING_ERR_NO_DATA]=std::string("get.associationset.mapping.err.no.data");
    IwfMeSS::errorMap[DEL_ASSOCIATION_ERR_NOT_PRESENT]=std::string("del.association.err.not.present");
    IwfMeSS::errorMap[DEL_ASSOCIATION_ERR_ASSOCIATION_IN_ACTIVE_STATE]=std::string("del.association.err.association.in.active.state");
    IwfMeSS::errorMap[DEL_ASSOCIATION_ERR_USED_IN_MULTIHOMING_IP]=std::string("del.association.err.used.in.multihoming.ip");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_NOT_PRESENT]=std::string("mod.association.err.not.present");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_ASSOCIATION_IN_ACTIVE_STATE]=std::string("mod.association.err.association.in.active.state");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT]=std::string("mod.association.err.sctp.profile.not.present");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT]=std::string("mod.association.err.sctp.end.point.not.present");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_MAX_MULTIHOMING_IP]=std::string("mod.association.err.max.multihoming.ip");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_ALREADY_ENABLED]=std::string("mod.association.err.already.enabled");
    IwfMeSS::errorMap[MOD_ASSOCIATION_ERR_NOT_ASSOCIATED_TO_ANY_ASSOCIATIONSET]=std::string("mod.association.err.not.associated.to.any.associationset");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_ALREADY_PRESENT]=std::string("add.association.err.already.present");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT]=std::string("add.association.err.sctp.profile.not.present");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT]=std::string("add.association.err.sctp.end.point.not.present");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_MAX_MULTIHOMING_IP]=std::string("add.association.err.max.multihoming.ip");
    IwfMeSS::errorMap[DEL_MULTIHOMINGIP_ERR_NOT_PRESENT]=std::string("del.multihomingip.err.not.present");
    IwfMeSS::errorMap[DEL_MULTIHOMINGIP_ERR_ASSOCIATION_IN_ACTIVE_STATE]=std::string("del.multihomingip.err.association.in.active.state");
    IwfMeSS::errorMap[DEL_DESTINATION_ERR_NOT_PRESENT]=std::string("del.destination.err.not.present");
    IwfMeSS::errorMap[DEL_DESTINATION_ERR_USED_IN_ROUTE]=std::string("del.destination.err.used.in.route");
    IwfMeSS::errorMap[DEL_DESTINATION_ERR_USED_IN_TRANSLATOR_RULE]=std::string("del.destination.err.used.in.translator.rule");
    IwfMeSS::errorMap[MOD_DESTINATION_ERR_NOT_PRESENT]=std::string("mod.destination.err.not.present");
    IwfMeSS::errorMap[ADD_DESTINATION_ERR_ALREADY_PRESENT]=std::string("add.destination.err.already.present");
    IwfMeSS::errorMap[DEL_ROUTE_ERR_ROUTE_NOT_PRESENT]=std::string("del.route.err.route.not.present");
    IwfMeSS::errorMap[DEL_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT]=std::string("del.route.err.association.set.not.present");
    IwfMeSS::errorMap[DEL_ROUTE_ERR_DESTINATION_NOT_PRESENT]=std::string("del.route.err.destination.not.present");
    IwfMeSS::errorMap[DEL_ROUTE_ERR_ASSOCIATION_SET_IN_ACTIVE_STATE]=std::string("del.route.err.association.set.in.active.state");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_ROUTE_NOT_PRESENT]=std::string("mod.route.err.route.not.present");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT]=std::string("mod.route.err.association.set.not.present");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_DESTINATION_NOT_PRESENT]=std::string("mod.route.err.destination.not.present");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_ASSOCIATION_NOT_PRESENT]=std::string("mod.route.err.association.not.present");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_ASSOCIATION_SET_ALREADY_HAVE_ROUTE]=std::string("mod.route.err.association.set.already.have.route");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_DESTINATION_ALREADY_USED_IN_ROUTE]=std::string("mod.route.err.destination.already.used.in.route");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_ASSOCIATION_SET_IN_ACTIVE_STATE]=std::string("mod.route.err.association.set.in.active.state");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_ROUTE_ALREADY_PRESENT]=std::string("add.route.err.route.already.present");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT]=std::string("add.route.err.association.set.not.present");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_DESTINATION_NOT_PRESENT]=std::string("add.route.err.destination.not.present");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_ASSOCIATION_NOT_PRESENT]=std::string("add.route.err.association.not.present");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_DESTINATION_ALREADY_USED_IN_ROUTE]=std::string("add.route.err.destination.already.used.in.route");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_ASSOCIATION_SET_ALREADY_HAVE_ROUTE]=std::string("add.route.err.association.set.already.have.route");
    IwfMeSS::errorMap[DEL_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT]=std::string("del.transrules.err.trans.rule.not.present");
    IwfMeSS::errorMap[DEL_TRANSRULES_ERR_TRANSLATOR_NOT_PRESENT]=std::string("del.transrules.err.translator.not.present");
    IwfMeSS::errorMap[DEL_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT]=std::string("del.transrules.err.translatortype.not.present");
    IwfMeSS::errorMap[DEL_TRANSRULES_ERR_MISSING_MANDATORY_PARAM]=std::string("del.transrules.err.missing.mandatory.param");
    IwfMeSS::errorMap[MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT]=std::string("mod.transrules.err.trans.rule.not.present");
    IwfMeSS::errorMap[MOD_TRANSRULES_ERR_TRANSLATOR_NOT_PRESENT]=std::string("mod.transrules.err.translator.not.present");
    IwfMeSS::errorMap[MOD_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT]=std::string("mod.transrules.err.translatortype.not.present");
    IwfMeSS::errorMap[MOD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM]=std::string("mod.transrules.err.missing.mandatory.param");
    IwfMeSS::errorMap[ADD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT]=std::string("add.transrules.err.trans.rule.not.present");
    IwfMeSS::errorMap[ADD_TRANSRULES_ERR_TRANS_RULE_ALREADY_PRESENT]=std::string("add.transrules.err.trans.rule.already.present");
    IwfMeSS::errorMap[ADD_TRANSRULES_ERR_TRANSLATOR_NOT_PRESENT]=std::string("add.transrules.err.translator.not.present");
    IwfMeSS::errorMap[ADD_TRANSRULES_ERR_TRANSLATORTYPE_NOT_PRESENT]=std::string("add.transrules.err.translatortype.not.present");
    IwfMeSS::errorMap[ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM]=std::string("add.transrules.err.missing.mandatory.param");
    IwfMeSS::errorMap[DEL_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT]=std::string("del.maps6aconfig.err.translator.mapping.not.present");
    IwfMeSS::errorMap[DEL_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT]=std::string("del.maps6aconfig.err.translator.not.present");
    IwfMeSS::errorMap[MOD_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT]=std::string("mod.maps6aconfig.err.translator.mapping.not.present");
    IwfMeSS::errorMap[MOD_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT]=std::string("mod.maps6aconfig.err.translator.not.present");
    IwfMeSS::errorMap[MOD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT]=std::string("mod.maps6aconfig.err.data.not.present");
    IwfMeSS::errorMap[ADD_MAPS6ACONFIG_ERR_TRANSLATOR_MAPPING_ALREADY_PRESENT]=std::string("add.maps6aconfig.err.translator.mapping.already.present");
    IwfMeSS::errorMap[ADD_MAPS6ACONFIG_ERR_TRANSLATOR_NOT_PRESENT]=std::string("add.maps6aconfig.err.translator.not.present");
    IwfMeSS::errorMap[ADD_MAPS6ACONFIG_ERR_DATA_NOT_PRESENT]=std::string("add.maps6aconfig.err.data.not.present");
    IwfMeSS::errorMap[DEL_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT]=std::string("del.s6amapconfig.err.translator.mapping.not.present");
    IwfMeSS::errorMap[DEL_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT]=std::string("del.s6amapconfig.err.translator.not.present");
    IwfMeSS::errorMap[DEL_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT]=std::string("del.s6amapconfig.err.s6amap.sgsn.already.present");
    IwfMeSS::errorMap[MOD_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_NOT_PRESENT]=std::string("mod.s6amapconfig.err.translator.mapping.not.present");
    IwfMeSS::errorMap[MOD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT]=std::string("mod.s6amapconfig.err.translator.not.present");
    IwfMeSS::errorMap[MOD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT]=std::string("mod.s6amapconfig.err.s6amap.sgsn.already.present");
    IwfMeSS::errorMap[ADD_S6AMAPCONFIG_ERR_TRANSLATOR_MAPPING_ALREADY_PRESENT]=std::string("add.s6amapconfig.err.translator.mapping.already.present");
    IwfMeSS::errorMap[ADD_S6AMAPCONFIG_ERR_TRANSLATOR_NOT_PRESENT]=std::string("add.s6amapconfig.err.translator.not.present");
    IwfMeSS::errorMap[ADD_S6AMAPCONFIG_ERR_S6AMAP_SGSN_ALREADY_PRESENT]=std::string("add.s6amapconfig.err.s6amap.sgsn.already.present");
    IwfMeSS::errorMap[DEL_CAPROIDPSMSCONFIG_ERR_CONFIG_NOT_PRESENT]=std::string("del.caproidpsmsconfig.err.config.not.present");
    IwfMeSS::errorMap[MOD_CAPROIDPSMSCONFIG_ERR_CONFIG_NOT_PRESENT]=std::string("mod.caproidpsmsconfig.err.config.not.present");
    IwfMeSS::errorMap[ADD_CAPROIDPSMSCONFIG_ERR_CONFIG_ALREADY_PRESENT]=std::string("add.caproidpsmsconfig.err.config.already.present");
    IwfMeSS::errorMap[DEL_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT]=std::string("del.caproidpconfig.err.config.not.present");
    IwfMeSS::errorMap[MOD_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT]=std::string("mod.caproidpconfig.err.config.not.present");
    IwfMeSS::errorMap[ADD_CAPROIDPCONFIG_ERR_CONFIG_NOT_PRESENT]=std::string("add.caproidpconfig.err.config.not.present");

    /* New Error Added */
    IwfMeSS::errorMap[SET_LOCALHOST_ERR_MISSING_MANDATORY_PARAM]=std::string("add.localhost.err.missing.mandatory.param");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_MISSING_MANDATORY_PARAM]=std::string("add.associationset.err.missing.mandatory.param");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_NI_NOT_SAME_AS_LOCAL_NI]=std::string("add.associationset.err.ni.not.same.as.local.ni");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND]=std::string("add.associationset.err.failed.at.backend");
    IwfMeSS::errorMap[DEL_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND]=std::string("del.associationset.err.failed.at.backend");
    IwfMeSS::errorMap[ADD_ROUTINGKEYROUTE_ERR_FAILED_AT_BACKEND]=std::string("add.routingkeyroute.err.failed.at.backend");
    IwfMeSS::errorMap[ADD_UALCONFIG_ERR_ADD_GENERAL_CONFIG_FAILED_AT_BACKEND]=std::string("add.ualconfig.add.general.config.failed.at.backend");
    IwfMeSS::errorMap[ADD_UALCONFIG_ERR_MISSING_MANDATORY_PARAM]=std::string("add.ualconfig.err.missing.mandatory.param");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_INVALID_TRAFFIC_MODE]=std::string("add.associationset.err.invalid.traffic.mode");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_COULD_NOT_OBTAIN_ROUTINGKEYINFO]=std::string("add.associationset.err.could.not.obtain.routingkeyinfo");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_UNABLE_TO_CREATE_APPLICATION_SERVER]=std::string("add.associationset.err.unable.to.create.application.server");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_CREATE_APPLICATION_SERVER_FAILED_TO_ADD_LINKSET_AND_DESTINATION]=std::string("add.associationset.err.create.application.server.failed.to.add.linkset.and.destination");
    IwfMeSS::errorMap[ADD_ASSOCIATIONSET_ERR_CREATE_APPLICATION_SERVER_PROCESS_FAILED]=std::string("add.ualconfig.err.create.application.server.process.failed");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_FAILED_TO_ADD_LOCAL_ENDPOINT]=std::string("add.association.err.failed.to.add.local.transport");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_FAILED_INVALID_LOCAL_ENDPOINT_IP]=std::string("add.association.err.failed.to.add.local.transport.invalid.ip");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_FAILED_TO_ADD_REMOTE_ENDPOINT]=std::string("add.association.err.failed.to.add.remote.transport");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_TRANSPORT_INSTANCE_NOT_FOUND]=std::string("add.association.err.transport.instance.not.found");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_LINKSET_NOT_FOUND]=std::string("add.association.err.linkset.not.found");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_ASSOCIATION_NOT_FOUND_IN_ASSOCIATIONSET_AFTER_ADDITION]=std::string("add.association.err.association.not.found.in.associationset.after.addition");
    IwfMeSS::errorMap[ADD_ASSOCIATION_ERR_MISSING_MANDATORY_PARAM]=std::string("add.association.err.missing.mandatory.param");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_MISSING_MANDATORY_PARAM]=std::string("add.route.err.missing.mandatory.param");
    IwfMeSS::errorMap[ADD_DESTINATION_ERR_MISSING_MANDATORY_PARAM]=std::string("add.destination.err.missing.mandatory.param");
    IwfMeSS::errorMap[DEL_SCTPENDPOINT_NOT_SUPPORTED]=std::string("del.sctp.endpoint.not.supported");
    IwfMeSS::errorMap[MOD_SCTPENDPOINT_NOT_SUPPORTED]=std::string("mod.sctp.endpoint.not.supported");
    IwfMeSS::errorMap[DEL_SCTPPROFILE_NOT_SUPPORTED]=std::string("del.sctp.profile.not.supported");
    IwfMeSS::errorMap[MOD_SCTPPROFILE_NOT_SUPPORTED]=std::string("del.sctp.profile.not.supported");
    IwfMeSS::errorMap[DEL_ASSOCIATIONSET_NOT_SUPPORTED]=std::string("del.associationset.not.supported");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_NOT_SUPPORTED]=std::string("mod.associationset.not.supported");
    IwfMeSS::errorMap[DEL_ASSOCIATION_NOT_SUPPORTED]=std::string("del.association.not.supported");
    IwfMeSS::errorMap[MOD_ASSOCIATION_NOT_SUPPORTED]=std::string("mod.association.not.supported");
    IwfMeSS::errorMap[DEL_DESTINATION_NOT_SUPPORTED]=std::string("del.destination.not.supported");
    IwfMeSS::errorMap[MOD_DESTINATION_NOT_SUPPORTED]=std::string("mod.destination.not.supported");

    IwfMeSS::errorMap[MOD_ROUTE_ERR_MISSING_MANDATORY_PARAMETER]=std::string("mod.route.err.missing.mandatory.parameter");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_ROUTE_NOT_PRESENT]=std::string("mod.route.err.route.not.present");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_MISSING_DEST_INFO]=std::string("mod.route.err.missing.dest.info");
    IwfMeSS::errorMap[DEL_ROUTE_ERR_POINTCODE_OR_SSN_NOT_PRESENT_IN_DEST_INFO]=std::string("del.route.err.pointcode.or.ssn.not.present.in.dest.info");
    IwfMeSS::errorMap[DEL_ROUTE_ERR_PRIORITY_NOT_PRESENT]=std::string("del.route.err.priority.not.present");
    IwfMeSS::errorMap[MOD_ROUTE_ERR_GENERIC_ERROR]=std::string("mod.route.err.generic.error");
    IwfMeSS::errorMap[ADD_ROUTE_ERR_GENERIC_ERROR]=std::string("add.route.err.generic.error");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND]=std::string("modify.associationset.err.failed.at.backend");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_GENERIC_ERROR]=std::string("mod.associationset.err.generic.error");
    IwfMeSS::errorMap[MOD_ASSOCIATIONSET_ERR_NI_NOT_SAME_AS_LOCAL_NI]=std::string("mod.associationset.err.ni.not.same.as.local.ni");
    IwfMeSS::errorMap[ADD_DCCA_DEST_ERR_ENDPOINT_ALREADY_PRESENT]=std::string("add.dcca.dest.err.endpoint.already.present");
    IwfMeSS::errorMap[DEL_DCCA_DEST_ERR_ENDPOINT_NOT_PRESENT]=std::string("del.dcca.dest.err.endpoint.not.present");
    IwfMeSS::errorMap[ADD_DCCA_DEST_ERR_DATA_NOT_SET]=std::string("add.dcca.dest.err.data.not.set");

    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_CALL_TYPE_NOT_PRESENT]=std::string("add.protocol.action.err.call.type.not.present");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_NOT_PRESENT]=std::string("add.protocol.action.err.call.scenario.not.present");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_EVENT_TYPE_MANDATORY_PARAM_MISSING]=std::string("add.protocol.action.err.event.type.mandatory.param.missing");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_ARM_DATA_MANDATORY_PARAM_MISSING]=std::string("add.protocol.action.err.arm.data.mandatory.param.missing");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_MANDATORY_PARAM_MISSING]=std::string("add.protocol.action.err.call.scenario.mandatory.param.missing");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_MSGDET_NOT_PRESENT]=std::string("add.protocol.action.err.msgdet.not.present");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT]=std::string("add.protocol.action.err.protactcfg.not.present");
    IwfMeSS::errorMap[ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_MANDATORY_PARAM_MISSING]=std::string("add.protocol.action.err.protactcfg.mandatory.param.missing");
}

void IwfMeSS:: SetLogLevel(unsigned int level)
{
    CLOG_DEBUG("Settting Diameter Stack Log level to %d",level);
    this->GetLogger().SetLevel((Logger::Level)level);
}

int IwfMeSS::ProcessAvailabilityStatusResetPostFunc(bool switchOver)
{

    CLOG_DEBUG(">>>>IwfMeSS::ProcessAvailabilityStatusResetPostFunc");
    uint16_t newInstanceId = MeSSObj().Self().instance;
    //DREController::Instance().UpdateInstanceId(newInstanceId);

    if(MESS_ISActiveInst(newInstanceId))
    {    
        //IWFController::GoActive();
        //Bring up IWF transports since instance has become Active.
        iwf::IWFTransportController::SetTransportStatus(true);
    
    }    
    else if(MESS_ISStandbyInst(newInstanceId))
    {    
        //IWFController::GoStandby();
        //Bring down IWF transports since instance has become Standby.
        iwf::IWFTransportController::SetTransportStatus(false);
    }    
    return 0;
}
