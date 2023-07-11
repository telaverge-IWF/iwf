#
# Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
#
# $Log: win32.mak,v $
# Revision 9.1  2005/03/23 12:51:31  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:49:29  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:08:47  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:13:20  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:20  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:03  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/15 23:57:05  mmiers
#
# Begin round 4.
#
# Revision 1.8  2000/06/15 20:30:02  npopov
# Added deletion of ossmapv4mdd.lib.
#
# Revision 1.7  2000/06/15 20:21:10  npopov
# Updated for testing MAP V4.
#
# Revision 1.6  2000/05/25 21:13:53  npopov
# Added OSS compiler invokation.
#
# Revision 1.5  2000/05/24 17:37:12  npopov
# Changes for building a new OSS MAPV4 library for testing OO C & C++ ASN.1 code.
#
# Revision 1.4  2000/05/04 16:54:50  npopov
# Minor correction for moving the .h files.
#
# Revision 1.3  2000/05/04 13:36:41  npopov
# Fixed the clean target to mot delete map_c.h.
#
# Revision 1.1  2000/04/04 13:24:41  npopov
# Win32 makefile for regression testing
#
#


COMMON_INCLUDE = $(ITS_ROOT)\common\include
COMMON_LIB     = $(ITS_ROOT)\common\lib
GSMMAP_INCLUDE = $(ITS_ROOT)\GSMMAP\include
TCAP_INCLUDE   = $(ITS_ROOT)\TCAP\include
SCCP_INCLUDE   = $(ITS_ROOT)\SCCP\include
MTP3_INCLUDE   = $(ITS_ROOT)\MTP3\include
OSS_INCLUDE    = $(UTIL)\ossasn1\5.1.0\include
IMPLIB         = lib
CC             = cl
LINK           = link
IMPLIB         = lib

!ifndef debug
debug = yes
!endif

!if "$(debug)" == "yes"
!else if "$(debug)" == "no"
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifndef msdebug
msdebug = yes
!endif

!if "$(msdebug)" == "yes"
RTSL = -MTd
RTDL = -MDd
LINKER = -debug
!else
RTSL = -MT
RTDL = -MD
LINKER = -release
!endif

CPU = ix86
POPT = -GB
OOPT = -GF -Gi- -Gm- -GR- -GX- -Gy -Oxsy -Zl

!if "$(debug)" == "yes"
MAINFLAGS = -c -W3 -Od -Z7 $(POPT) -Ze -D_WIN32 -DWIN32 -DCCITT\
		-I$(GSMMAP_INCLUDE) -I$(GSMMAP_INCLUDE)\itu -I$(COMMON_INCLUDE)\
		-I$(COMMON_INCLUDE)\asn-c -I$(TCAP_INCLUDE) -I$(SCCP_INCLUDE)\
		-I$(MTP3_INCLUDE) -I$(OSS_INCLUDE) -I$(COMMON_INCLUDE)\asn-cpp\
		-DDEBUG
CONFLAGS = -pdb:none
LDEBUG   = -debug:full -debugtype:cv $(LINKER)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -I$(GSMMAP_INCLUDE)\
		-I$(GSMMAP_INCLUDE)\itu -I$(COMMON_INCLUDE)\
		-I$(COMMON_INCLUDE)\asn-c -I$(TCAP_INCLUDE) -I$(SCCP_INCLUDE)\
		-I$(MTP3_INCLUDE) -I$(OSS_INCLUDE) -I$(COMMON_INCLUDE)\asn-cpp\
		-DDEBUG
CONFLAGS = -pdb:none
LDEBUG   =  $(LINKER)
!else
!ERROR The macro "debug" incorrectly defined!
!endif

!ifdef t
MTYPE = $(t)
!else
MTYPE = d
mt = d
!endif

!if "$(MTYPE)" == "s"
CFLAGS = $(RTSL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTSL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
TYPE = d
CONLIBS = libcmtd.lib kernel32.lib advapi32.lib
!else
TYPE =
CONLIBS = libcmt.lib kernel32.lib advapi32.lib
!endif
!else if "$(MTYPE)" == "d"
CFLAGS = $(RTDL) $(MAINFLAGS)
CPLUSPLUSFLAGS = $(RTDL) $(MAINFLAGS) -GX
!if "$(msdebug)" == "yes"
CONLIBS = msvcrtd.lib kernel32.lib advapi32.lib ws2_32.lib
TYPE = mdd
!else
CONLIBS = msvcrt.lib kernel32.lib advapi32.lib ws2_32.lib
TYPE = md
!endif
!else
!ERROR The macro "t" incorrectly defined!
!endif

!message Current libraries are: gsmmap$(TYPE).lib, ossigsmmap$(TYPE).lib & iossgsmmap$(TYPE).lib...
!message

GSMMAP_OBJECTS = gsmmap_tables.obj its_gsmmap.obj gsmsms.obj
OSSI_GSMMAP_OBJECTS = gsmmap_tables.obj getpdu.obj gsmmapvn.obj\
			ossi_its_gsmmap.obj gsmsms.obj
OSS_MAPV4_OBJECTS = map_v4_lrfvn.obj getv4pdu.obj
IOSS_GSMMAP_OBJECTS = gsmmap_tables.obj getpdu.obj gsmmapvn.obj\
			ioss_its_gsmmap.obj gsmsms.obj
MAPV4_OBJECTS = map_v4_absent_subscriber_diagnostic_sm_c.obj\
		map_v4_absent_subscriber_param_c.obj\
		map_v4_absent_subscriber_reason_c.obj\
		map_v4_absent_subscriber_sm_param_c.obj\
		map_v4_activate_trace_mode_arg_c.obj\
		map_v4_activate_trace_mode_res_c.obj\
		map_v4_additional_number_c.obj\
		map_v4_address_string_c.obj\
		map_v4_age_of_location_information_c.obj\
		map_v4_alert_reason_c.obj\
		map_v4_alert_service_centre_arg_c.obj\
		map_v4_alerting_pattern_c.obj\
		map_v4_any_time_interrogation_arg_c.obj\
		map_v4_any_time_interrogation_res_c.obj\
		map_v4_apn_c.obj\
		map_v4_asci_call_reference_c.obj\
		map_v4_ati_not_allowed_param_c.obj\
		map_v4_authentication_set_c.obj\
		map_v4_authentication_set_list_c.obj\
		map_v4_basic_service_code_c.obj\
		map_v4_basic_service_criteria_c.obj\
		map_v4_basic_service_group_list_c.obj\
		map_v4_basic_service_list_c.obj\
		map_v4_bearer_serv_not_prov_param_c.obj\
		map_v4_bearer_service_code_c.obj\
		map_v4_bearer_service_list_c.obj\
		map_v4_busy_subscriber_param_c.obj\
		map_v4_call_barred_param_c.obj\
		map_v4_call_barring_cause_c.obj\
		map_v4_call_barring_feature_c.obj\
		map_v4_call_barring_feature_list_c.obj\
		map_v4_call_barring_info_c.obj\
		map_v4_call_direction_c.obj\
		map_v4_call_outcome_c.obj\
		map_v4_call_reference_number_c.obj\
		map_v4_call_report_data_c.obj\
		map_v4_call_type_criteria_c.obj\
		map_v4_camel_capability_handling_c.obj\
		map_v4_camel_info_c.obj\
		map_v4_camel_routing_info_c.obj\
		map_v4_cancel_location_arg_c.obj\
		map_v4_cancel_location_res_c.obj\
		map_v4_cancellation_type_c.obj\
		map_v4_category_c.obj\
		map_v4_ccbs_data_c.obj\
		map_v4_ccbs_feature_c.obj\
		map_v4_ccbs_feature_list_c.obj\
		map_v4_ccbs_index_c.obj\
		map_v4_ccbs_indicators_c.obj\
		map_v4_ccbs_subscriber_status_c.obj\
		map_v4_cell_id_fixed_length_c.obj\
		map_v4_cell_id_or_lai_c.obj\
		map_v4_ciphering_algorithm_c.obj\
		map_v4_cli_restriction_option_c.obj\
		map_v4_codec_info_c.obj\
		map_v4_context_id_c.obj\
		map_v4_context_id_list_c.obj\
		map_v4_cug_check_info_c.obj\
		map_v4_cug_feature_c.obj\
		map_v4_cug_feature_list_c.obj\
		map_v4_cug_index_c.obj\
		map_v4_cug_info_c.obj\
		map_v4_cug_interlock_c.obj\
		map_v4_cug_reject_cause_c.obj\
		map_v4_cug_reject_param_c.obj\
		map_v4_cug_subscription_c.obj\
		map_v4_cug_subscription_list_c.obj\
		map_v4_data_missing_param_c.obj\
		map_v4_deactivate_trace_mode_arg_c.obj\
		map_v4_deactivate_trace_mode_res_c.obj\
		map_v4_default_call_handling_c.obj\
		map_v4_delete_subscriber_data_arg_c.obj\
		map_v4_delete_subscriber_data_res_c.obj\
		map_v4_destination_number_criteria_c.obj\
		map_v4_destination_number_length_list_c.obj\
		map_v4_destination_number_list_c.obj\
		map_v4_emlpp_info_c.obj\
		map_v4_emlpp_priority_c.obj\
		map_v4_equipment_status_c.obj\
		map_v4_erase_cc_entry_arg_c.obj\
		map_v4_erase_cc_entry_res_c.obj\
		map_v4_event_report_data_c.obj\
		map_v4_ext_basic_service_code_c.obj\
		map_v4_ext_basic_service_group_list_c.obj\
		map_v4_ext_bearer_service_code_c.obj\
		map_v4_ext_call_bar_feature_list_c.obj\
		map_v4_ext_call_bar_info_c.obj\
		map_v4_ext_call_barring_feature_c.obj\
		map_v4_ext_forw_feature_c.obj\
		map_v4_ext_forw_feature_list_c.obj\
		map_v4_ext_forw_info_c.obj\
		map_v4_ext_forw_options_c.obj\
		map_v4_ext_no_rep_cond_time_c.obj\
		map_v4_ext_ss_data_c.obj\
		map_v4_ext_ss_info_c.obj\
		map_v4_ext_ss_info_list_c.obj\
		map_v4_ext_ss_status_c.obj\
		map_v4_ext_teleservice_code_c.obj\
		map_v4_extended_routing_info_c.obj\
		map_v4_extensible_call_barred_param_c.obj\
		map_v4_extensible_system_failure_param_c.obj\
		map_v4_extension_container_c.obj\
		map_v4_external_signal_info_c.obj\
		map_v4_facility_not_sup_param_c.obj\
		map_v4_failure_report_arg_c.obj\
		map_v4_failure_report_res_c.obj\
		map_v4_forward_group_call_signalling_arg_c.obj\
		map_v4_forwarding_data_c.obj\
		map_v4_forwarding_failed_param_c.obj\
		map_v4_forwarding_feature_c.obj\
		map_v4_forwarding_feature_list_c.obj\
		map_v4_forwarding_info_c.obj\
		map_v4_forwarding_options_c.obj\
		map_v4_forwarding_reason_c.obj\
		map_v4_forwarding_violation_param_c.obj\
		map_v4_generic_service_info_c.obj\
		map_v4_geographical_information_c.obj\
		map_v4_global_cell_id_c.obj\
		map_v4_gmsc_camel_subscription_info_c.obj\
		map_v4_gprs_data_list_c.obj\
		map_v4_gprs_subscription_data_c.obj\
		map_v4_gprs_subscription_data_withdraw_c.obj\
		map_v4_group_id_c.obj\
		map_v4_group_key_number_c.obj\
		map_v4_gsn_address_c.obj\
		map_v4_guidance_info_c.obj\
		map_v4_hlr_id_c.obj\
		map_v4_hlr_list_c.obj\
		map_v4_identity_c.obj\
		map_v4_illegal_equipment_param_c.obj\
		map_v4_illegal_subscriber_param_c.obj\
		map_v4_imei_c.obj\
		map_v4_imsi_c.obj\
		map_v4_imsi_with_lmsi_c.obj\
		map_v4_incompatible_terminal_param_c.obj\
		map_v4_inform_service_centre_arg_c.obj\
		map_v4_insert_subscriber_data_arg_c.obj\
		map_v4_insert_subscriber_data_res_c.obj\
		map_v4_inter_cug_restrictions_c.obj\
		map_v4_interrogate_ss_res_c.obj\
		map_v4_interrogation_type_c.obj\
		map_v4_intra_cug_options_c.obj\
		map_v4_isdn_address_string_c.obj\
		map_v4_isdn_subaddress_string_c.obj\
		map_v4_its_feature_class_c.obj\
		map_v4_kc_c.obj\
		map_v4_lai_fixed_length_c.obj\
		map_v4_lmsi_c.obj\
		map_v4_location_info_with_lmsi_c.obj\
		map_v4_location_information_c.obj\
		map_v4_location_number_c.obj\
		map_v4_long_term_denial_param_c.obj\
		map_v4_map_accept_info_c.obj\
		map_v4_map_close_info_c.obj\
		map_v4_map_dialogue_pdu_c.obj\
		map_v4_map_open_info_c.obj\
		map_v4_map_provider_abort_info_c.obj\
		map_v4_map_provider_abort_reason_c.obj\
		map_v4_map_refuse_info_c.obj\
		map_v4_map_user_abort_choice_c.obj\
		map_v4_map_user_abort_info_c.obj\
		map_v4_map_user_info_c.obj\
		map_v4_match_type_c.obj\
		map_v4_message_wait_list_full_param_c.obj\
		map_v4_mo_forward_sm_arg_c.obj\
		map_v4_mo_forward_sm_res_c.obj\
		map_v4_monitoring_mode_c.obj\
		map_v4_mt_forward_sm_arg_c.obj\
		map_v4_mt_forward_sm_res_c.obj\
		map_v4_mw_status_c.obj\
		map_v4_naea_cic_c.obj\
		map_v4_naea_preferred_ci_c.obj\
		map_v4_network_access_mode_c.obj\
		map_v4_network_resource_c.obj\
		map_v4_no_group_call_nb_param_c.obj\
		map_v4_no_reply_condition_time_c.obj\
		map_v4_no_roaming_nb_param_c.obj\
		map_v4_no_subscriber_reply_param_c.obj\
		map_v4_not_reachable_reason_c.obj\
		map_v4_note_ms_present_for_gprs_arg_c.obj\
		map_v4_note_ms_present_for_gprs_res_c.obj\
		map_v4_number_changed_param_c.obj\
		map_v4_number_of_forwarding_c.obj\
		map_v4_o_bcsm_camel_tdp_criteria_c.obj\
		map_v4_o_bcsm_camel_tdp_data_c.obj\
		map_v4_o_bcsm_camel_tdp_data_list_c.obj\
		map_v4_o_bcsm_trigger_detection_point_c.obj\
		map_v4_o_csi_c.obj\
		map_v4_odb_data_c.obj\
		map_v4_odb_general_data_c.obj\
		map_v4_odb_hplmn_data_c.obj\
		map_v4_or_not_allowed_param_c.obj\
		map_v4_or_phase_c.obj\
		map_v4_override_category_c.obj\
		map_v4_password_c.obj\
		map_v4_pcs_extensions_c.obj\
		map_v4_pdp_address_c.obj\
		map_v4_pdp_context_c.obj\
		map_v4_pdp_type_c.obj\
		map_v4_prepare_group_call_arg_c.obj\
		map_v4_prepare_group_call_res_c.obj\
		map_v4_prepare_ho_arg_c.obj\
		map_v4_prepare_ho_res_c.obj\
		map_v4_prepare_subsequent_ho_arg_c.obj\
		map_v4_private_extension_c.obj\
		map_v4_private_extension_list_c.obj\
		map_v4_procedure_cancellation_reason_c.obj\
		map_v4_process_group_call_signalling_arg_c.obj\
		map_v4_protocol_id_c.obj\
		map_v4_provide_roaming_number_arg_c.obj\
		map_v4_provide_roaming_number_res_c.obj\
		map_v4_provide_siwfs_number_arg_c.obj\
		map_v4_provide_siwfs_number_res_c.obj\
		map_v4_provide_subscriber_info_arg_c.obj\
		map_v4_provide_subscriber_info_res_c.obj\
		map_v4_purge_ms_arg_c.obj\
		map_v4_purge_ms_res_c.obj\
		map_v4_pw_registration_failure_cause_c.obj\
		map_v4_qo_s_subscribed_c.obj\
		map_v4_rand_c.obj\
		map_v4_ready_for_sm_arg_c.obj\
		map_v4_ready_for_sm_res_c.obj\
		map_v4_reason_c.obj\
		map_v4_regional_subscription_response_c.obj\
		map_v4_register_cc_entry_arg_c.obj\
		map_v4_register_cc_entry_res_c.obj\
		map_v4_register_ss_arg_c.obj\
		map_v4_remote_user_free_arg_c.obj\
		map_v4_remote_user_free_res_c.obj\
		map_v4_report_sm_delivery_status_arg_c.obj\
		map_v4_report_sm_delivery_status_res_c.obj\
		map_v4_reporting_state_c.obj\
		map_v4_requested_info_c.obj\
		map_v4_reset_arg_c.obj\
		map_v4_resource_limitation_param_c.obj\
		map_v4_resource_unavailable_reason_c.obj\
		map_v4_restore_data_arg_c.obj\
		map_v4_restore_data_res_c.obj\
		map_v4_resume_call_handling_arg_c.obj\
		map_v4_resume_call_handling_res_c.obj\
		map_v4_roaming_not_allowed_cause_c.obj\
		map_v4_roaming_not_allowed_param_c.obj\
		map_v4_routing_info_c.obj\
		map_v4_routing_info_for_sm_arg_c.obj\
		map_v4_routing_info_for_sm_res_c.obj\
		map_v4_ruf_outcome_c.obj\
		map_v4_send_authentication_info_arg_c.obj\
		map_v4_send_authentication_info_res_c.obj\
		map_v4_send_group_call_end_signal_arg_c.obj\
		map_v4_send_group_call_end_signal_res_c.obj\
		map_v4_send_identification_res_c.obj\
		map_v4_send_routing_info_arg_c.obj\
		map_v4_send_routing_info_for_gprs_arg_c.obj\
		map_v4_send_routing_info_for_gprs_res_c.obj\
		map_v4_send_routing_info_res_c.obj\
		map_v4_service_indicator_c.obj\
		map_v4_service_key_c.obj\
		map_v4_set_reporting_state_arg_c.obj\
		map_v4_set_reporting_state_res_c.obj\
		map_v4_short_term_denial_param_c.obj\
		map_v4_signal_info_c.obj\
		map_v4_siwfs_signalling_modify_arg_c.obj\
		map_v4_siwfs_signalling_modify_res_c.obj\
		map_v4_sm_delivery_failure_cause_c.obj\
		map_v4_sm_delivery_outcome_c.obj\
		map_v4_sm_enumerated_delivery_failure_cause_c.obj\
		map_v4_sm_rp_da_c.obj\
		map_v4_sm_rp_mti_c.obj\
		map_v4_sm_rp_oa_c.obj\
		map_v4_sm_rp_smea_c.obj\
		map_v4_sres_c.obj\
		map_v4_ss_camel_data_c.obj\
		map_v4_ss_code_c.obj\
		map_v4_ss_csi_c.obj\
		map_v4_ss_data_c.obj\
		map_v4_ss_event_list_c.obj\
		map_v4_ss_event_specification_c.obj\
		map_v4_ss_for_bs_code_c.obj\
		map_v4_ss_incompatibility_cause_c.obj\
		map_v4_ss_info_c.obj\
		map_v4_ss_info_list_c.obj\
		map_v4_ss_invocation_notification_arg_c.obj\
		map_v4_ss_invocation_notification_res_c.obj\
		map_v4_ss_list_c.obj\
		map_v4_ss_status_c.obj\
		map_v4_ss_subscription_option_c.obj\
		map_v4_status_report_arg_c.obj\
		map_v4_status_report_res_c.obj\
		map_v4_sub_busy_for_mt_sms_param_c.obj\
		map_v4_subscriber_data_c.obj\
		map_v4_subscriber_id_c.obj\
		map_v4_subscriber_identity_c.obj\
		map_v4_subscriber_info_c.obj\
		map_v4_subscriber_state_c.obj\
		map_v4_subscriber_status_c.obj\
		map_v4_supported_camel_phases_c.obj\
		map_v4_supported_ccbs_phase_c.obj\
		map_v4_suppression_of_announcement_c.obj\
		map_v4_system_failure_param_c.obj\
		map_v4_t_bcsm_camel_tdp_data_c.obj\
		map_v4_t_bcsm_camel_tdp_data_list_c.obj\
		map_v4_t_bcsm_trigger_detection_point_c.obj\
		map_v4_t_csi_c.obj\
		map_v4_tbcd_string_c.obj\
		map_v4_teleserv_not_prov_param_c.obj\
		map_v4_teleservice_code_c.obj\
		map_v4_teleservice_list_c.obj\
		map_v4_tmsi_c.obj\
		map_v4_trace_reference_c.obj\
		map_v4_trace_type_c.obj\
		map_v4_tracing_buffer_full_param_c.obj\
		map_v4_unexpected_data_param_c.obj\
		map_v4_unidentified_sub_param_c.obj\
		map_v4_unknown_subscriber_diagnostic_c.obj\
		map_v4_unknown_subscriber_param_c.obj\
		map_v4_update_gprs_location_arg_c.obj\
		map_v4_update_gprs_location_res_c.obj\
		map_v4_update_location_arg_c.obj\
		map_v4_update_location_res_c.obj\
		map_v4_ussd_arg_c.obj\
		map_v4_ussd_data_coding_scheme_c.obj\
		map_v4_ussd_res_c.obj\
		map_v4_ussd_string_c.obj\
		map_v4_vbs_data_list_c.obj\
		map_v4_vgcs_data_list_c.obj\
		map_v4_vlr_camel_subscription_info_c.obj\
		map_v4_vlr_capability_c.obj\
		map_v4_voice_broadcast_data_c.obj\
		map_v4_voice_group_call_data_c.obj\
		map_v4_zone_code_c.obj\
		map_v4_zone_code_list_c.obj

MAPV4CPP_OBJECTS = map_v4_absent_subscriber_diagnostic_sm.obj\
		map_v4_absent_subscriber_param.obj\
		map_v4_absent_subscriber_reason.obj\
		map_v4_absent_subscriber_sm_param.obj\
		map_v4_activate_trace_mode_arg.obj\
		map_v4_activate_trace_mode_res.obj\
		map_v4_additional_number.obj\
		map_v4_address_string.obj\
		map_v4_age_of_location_information.obj\
		map_v4_alert_reason.obj\
		map_v4_alert_service_centre_arg.obj\
		map_v4_alerting_pattern.obj\
		map_v4_any_time_interrogation_arg.obj\
		map_v4_any_time_interrogation_res.obj\
		map_v4_apn.obj\
		map_v4_asci_call_reference.obj\
		map_v4_ati_not_allowed_param.obj\
		map_v4_authentication_set.obj\
		map_v4_authentication_set_list.obj\
		map_v4_basic_service_code.obj\
		map_v4_basic_service_criteria.obj\
		map_v4_basic_service_group_list.obj\
		map_v4_basic_service_list.obj\
		map_v4_bearer_serv_not_prov_param.obj\
		map_v4_bearer_service_code.obj\
		map_v4_bearer_service_list.obj\
		map_v4_busy_subscriber_param.obj\
		map_v4_call_barred_param.obj\
		map_v4_call_barring_cause.obj\
		map_v4_call_barring_feature.obj\
		map_v4_call_barring_feature_list.obj\
		map_v4_call_barring_info.obj\
		map_v4_call_direction.obj\
		map_v4_call_outcome.obj\
		map_v4_call_reference_number.obj\
		map_v4_call_report_data.obj\
		map_v4_call_type_criteria.obj\
		map_v4_camel_capability_handling.obj\
		map_v4_camel_info.obj\
		map_v4_camel_routing_info.obj\
		map_v4_cancel_location_arg.obj\
		map_v4_cancel_location_res.obj\
		map_v4_cancellation_type.obj\
		map_v4_category.obj\
		map_v4_ccbs_data.obj\
		map_v4_ccbs_feature.obj\
		map_v4_ccbs_feature_list.obj\
		map_v4_ccbs_index.obj\
		map_v4_ccbs_indicators.obj\
		map_v4_ccbs_subscriber_status.obj\
		map_v4_cell_id_fixed_length.obj\
		map_v4_cell_id_or_lai.obj\
		map_v4_ciphering_algorithm.obj\
		map_v4_cli_restriction_option.obj\
		map_v4_codec_info.obj\
		map_v4_context_id.obj\
		map_v4_context_id_list.obj\
		map_v4_cug_check_info.obj\
		map_v4_cug_feature.obj\
		map_v4_cug_feature_list.obj\
		map_v4_cug_index.obj\
		map_v4_cug_info.obj\
		map_v4_cug_interlock.obj\
		map_v4_cug_reject_cause.obj\
		map_v4_cug_reject_param.obj\
		map_v4_cug_subscription.obj\
		map_v4_cug_subscription_list.obj\
		map_v4_data_missing_param.obj\
		map_v4_deactivate_trace_mode_arg.obj\
		map_v4_deactivate_trace_mode_res.obj\
		map_v4_default_call_handling.obj\
		map_v4_delete_subscriber_data_arg.obj\
		map_v4_delete_subscriber_data_res.obj\
		map_v4_destination_number_criteria.obj\
		map_v4_destination_number_length_list.obj\
		map_v4_destination_number_list.obj\
		map_v4_emlpp_info.obj\
		map_v4_emlpp_priority.obj\
		map_v4_equipment_status.obj\
		map_v4_erase_cc_entry_arg.obj\
		map_v4_erase_cc_entry_res.obj\
		map_v4_event_report_data.obj\
		map_v4_ext_basic_service_code.obj\
		map_v4_ext_basic_service_group_list.obj\
		map_v4_ext_bearer_service_code.obj\
		map_v4_ext_call_bar_feature_list.obj\
		map_v4_ext_call_bar_info.obj\
		map_v4_ext_call_barring_feature.obj\
		map_v4_ext_forw_feature.obj\
		map_v4_ext_forw_feature_list.obj\
		map_v4_ext_forw_info.obj\
		map_v4_ext_forw_options.obj\
		map_v4_ext_no_rep_cond_time.obj\
		map_v4_ext_ss_data.obj\
		map_v4_ext_ss_info.obj\
		map_v4_ext_ss_info_list.obj\
		map_v4_ext_ss_status.obj\
		map_v4_ext_teleservice_code.obj\
		map_v4_extended_routing_info.obj\
		map_v4_extensible_call_barred_param.obj\
		map_v4_extensible_system_failure_param.obj\
		map_v4_extension_container.obj\
		map_v4_external_signal_info.obj\
		map_v4_facility_not_sup_param.obj\
		map_v4_failure_report_arg.obj\
		map_v4_failure_report_res.obj\
		map_v4_forward_group_call_signalling_arg.obj\
		map_v4_forwarding_data.obj\
		map_v4_forwarding_failed_param.obj\
		map_v4_forwarding_feature.obj\
		map_v4_forwarding_feature_list.obj\
		map_v4_forwarding_info.obj\
		map_v4_forwarding_options.obj\
		map_v4_forwarding_reason.obj\
		map_v4_forwarding_violation_param.obj\
		map_v4_generic_service_info.obj\
		map_v4_geographical_information.obj\
		map_v4_global_cell_id.obj\
		map_v4_gmsc_camel_subscription_info.obj\
		map_v4_gprs_data_list.obj\
		map_v4_gprs_subscription_data.obj\
		map_v4_gprs_subscription_data_withdraw.obj\
		map_v4_group_id.obj\
		map_v4_group_key_number.obj\
		map_v4_gsn_address.obj\
		map_v4_guidance_info.obj\
		map_v4_hlr_id.obj\
		map_v4_hlr_list.obj\
		map_v4_identity.obj\
		map_v4_illegal_equipment_param.obj\
		map_v4_illegal_subscriber_param.obj\
		map_v4_imei.obj\
		map_v4_imsi.obj\
		map_v4_imsi_with_lmsi.obj\
		map_v4_incompatible_terminal_param.obj\
		map_v4_inform_service_centre_arg.obj\
		map_v4_insert_subscriber_data_arg.obj\
		map_v4_insert_subscriber_data_res.obj\
		map_v4_inter_cug_restrictions.obj\
		map_v4_interrogate_ss_res.obj\
		map_v4_interrogation_type.obj\
		map_v4_intra_cug_options.obj\
		map_v4_isdn_address_string.obj\
		map_v4_isdn_subaddress_string.obj\
		map_v4_kc.obj\
		map_v4_lai_fixed_length.obj\
		map_v4_lmsi.obj\
		map_v4_location_info_with_lmsi.obj\
		map_v4_location_information.obj\
		map_v4_location_number.obj\
		map_v4_long_term_denial_param.obj\
		map_v4_map_accept_info.obj\
		map_v4_map_close_info.obj\
		map_v4_map_dialogue_pdu.obj\
		map_v4_map_open_info.obj\
		map_v4_map_provider_abort_info.obj\
		map_v4_map_provider_abort_reason.obj\
		map_v4_map_refuse_info.obj\
		map_v4_map_user_abort_choice.obj\
		map_v4_map_user_abort_info.obj\
		map_v4_map_user_info.obj\
		map_v4_match_type.obj\
		map_v4_message_wait_list_full_param.obj\
		map_v4_mo_forward_sm_arg.obj\
		map_v4_mo_forward_sm_res.obj\
		map_v4_monitoring_mode.obj\
		map_v4_mt_forward_sm_arg.obj\
		map_v4_mt_forward_sm_res.obj\
		map_v4_mw_status.obj\
		map_v4_naea_cic.obj\
		map_v4_naea_preferred_ci.obj\
		map_v4_network_access_mode.obj\
		map_v4_network_resource.obj\
		map_v4_no_group_call_nb_param.obj\
		map_v4_no_reply_condition_time.obj\
		map_v4_no_roaming_nb_param.obj\
		map_v4_no_subscriber_reply_param.obj\
		map_v4_not_reachable_reason.obj\
		map_v4_note_ms_present_for_gprs_arg.obj\
		map_v4_note_ms_present_for_gprs_res.obj\
		map_v4_number_changed_param.obj\
		map_v4_number_of_forwarding.obj\
		map_v4_o_bcsm_camel_tdp_criteria.obj\
		map_v4_o_bcsm_camel_tdp_data.obj\
		map_v4_o_bcsm_camel_tdp_data_list.obj\
		map_v4_o_bcsm_trigger_detection_point.obj\
		map_v4_o_csi.obj\
		map_v4_odb_data.obj\
		map_v4_odb_general_data.obj\
		map_v4_odb_hplmn_data.obj\
		map_v4_or_not_allowed_param.obj\
		map_v4_or_phase.obj\
		map_v4_override_category.obj\
		map_v4_password.obj\
		map_v4_pcs_extensions.obj\
		map_v4_pdp_address.obj\
		map_v4_pdp_context.obj\
		map_v4_pdp_type.obj\
		map_v4_prepare_group_call_arg.obj\
		map_v4_prepare_group_call_res.obj\
		map_v4_prepare_ho_arg.obj\
		map_v4_prepare_ho_res.obj\
		map_v4_prepare_subsequent_ho_arg.obj\
		map_v4_private_extension.obj\
		map_v4_private_extension_list.obj\
		map_v4_procedure_cancellation_reason.obj\
		map_v4_process_group_call_signalling_arg.obj\
		map_v4_protocol_id.obj\
		map_v4_provide_roaming_number_arg.obj\
		map_v4_provide_roaming_number_res.obj\
		map_v4_provide_siwfs_number_arg.obj\
		map_v4_provide_siwfs_number_res.obj\
		map_v4_provide_subscriber_info_arg.obj\
		map_v4_provide_subscriber_info_res.obj\
		map_v4_purge_ms_arg.obj\
		map_v4_purge_ms_res.obj\
		map_v4_pw_registration_failure_cause.obj\
		map_v4_qo_s_subscribed.obj\
		map_v4_rand.obj\
		map_v4_ready_for_sm_arg.obj\
		map_v4_ready_for_sm_res.obj\
		map_v4_reason.obj\
		map_v4_regional_subscription_response.obj\
		map_v4_register_cc_entry_arg.obj\
		map_v4_register_cc_entry_res.obj\
		map_v4_register_ss_arg.obj\
		map_v4_remote_user_free_arg.obj\
		map_v4_remote_user_free_res.obj\
		map_v4_report_sm_delivery_status_arg.obj\
		map_v4_report_sm_delivery_status_res.obj\
		map_v4_reporting_state.obj\
		map_v4_requested_info.obj\
		map_v4_reset_arg.obj\
		map_v4_resource_limitation_param.obj\
		map_v4_resource_unavailable_reason.obj\
		map_v4_restore_data_arg.obj\
		map_v4_restore_data_res.obj\
		map_v4_resume_call_handling_arg.obj\
		map_v4_resume_call_handling_res.obj\
		map_v4_roaming_not_allowed_cause.obj\
		map_v4_roaming_not_allowed_param.obj\
		map_v4_routing_info.obj\
		map_v4_routing_info_for_sm_arg.obj\
		map_v4_routing_info_for_sm_res.obj\
		map_v4_ruf_outcome.obj\
		map_v4_send_authentication_info_arg.obj\
		map_v4_send_authentication_info_res.obj\
		map_v4_send_group_call_end_signal_arg.obj\
		map_v4_send_group_call_end_signal_res.obj\
		map_v4_send_identification_res.obj\
		map_v4_send_routing_info_arg.obj\
		map_v4_send_routing_info_for_gprs_arg.obj\
		map_v4_send_routing_info_for_gprs_res.obj\
		map_v4_send_routing_info_res.obj\
		map_v4_service_indicator.obj\
		map_v4_service_key.obj\
		map_v4_set_reporting_state_arg.obj\
		map_v4_set_reporting_state_res.obj\
		map_v4_short_term_denial_param.obj\
		map_v4_signal_info.obj\
		map_v4_siwfs_signalling_modify_arg.obj\
		map_v4_siwfs_signalling_modify_res.obj\
		map_v4_sm_delivery_failure_cause.obj\
		map_v4_sm_delivery_outcome.obj\
		map_v4_sm_enumerated_delivery_failure_cause.obj\
		map_v4_sm_rp_da.obj\
		map_v4_sm_rp_mti.obj\
		map_v4_sm_rp_oa.obj\
		map_v4_sm_rp_smea.obj\
		map_v4_sres.obj\
		map_v4_ss_camel_data.obj\
		map_v4_ss_code.obj\
		map_v4_ss_csi.obj\
		map_v4_ss_data.obj\
		map_v4_ss_event_list.obj\
		map_v4_ss_event_specification.obj\
		map_v4_ss_for_bs_code.obj\
		map_v4_ss_incompatibility_cause.obj\
		map_v4_ss_info.obj\
		map_v4_ss_info_list.obj\
		map_v4_ss_invocation_notification_arg.obj\
		map_v4_ss_invocation_notification_res.obj\
		map_v4_ss_list.obj\
		map_v4_ss_status.obj\
		map_v4_ss_subscription_option.obj\
		map_v4_status_report_arg.obj\
		map_v4_status_report_res.obj\
		map_v4_sub_busy_for_mt_sms_param.obj\
		map_v4_subscriber_data.obj\
		map_v4_subscriber_id.obj\
		map_v4_subscriber_identity.obj\
		map_v4_subscriber_info.obj\
		map_v4_subscriber_state.obj\
		map_v4_subscriber_status.obj\
		map_v4_supported_camel_phases.obj\
		map_v4_supported_ccbs_phase.obj\
		map_v4_suppression_of_announcement.obj\
		map_v4_system_failure_param.obj\
		map_v4_t_bcsm_camel_tdp_data.obj\
		map_v4_t_bcsm_camel_tdp_data_list.obj\
		map_v4_t_bcsm_trigger_detection_point.obj\
		map_v4_t_csi.obj\
		map_v4_tbcd_string.obj\
		map_v4_teleserv_not_prov_param.obj\
		map_v4_teleservice_code.obj\
		map_v4_teleservice_list.obj\
		map_v4_tmsi.obj\
		map_v4_trace_reference.obj\
		map_v4_trace_type.obj\
		map_v4_tracing_buffer_full_param.obj\
		map_v4_unexpected_data_param.obj\
		map_v4_unidentified_sub_param.obj\
		map_v4_unknown_subscriber_diagnostic.obj\
		map_v4_unknown_subscriber_param.obj\
		map_v4_update_gprs_location_arg.obj\
		map_v4_update_gprs_location_res.obj\
		map_v4_update_location_arg.obj\
		map_v4_update_location_res.obj\
		map_v4_user_info_helper.obj\
		map_v4_ussd_arg.obj\
		map_v4_ussd_data_coding_scheme.obj\
		map_v4_ussd_res.obj\
		map_v4_ussd_string.obj\
		map_v4_vbs_data_list.obj\
		map_v4_vgcs_data_list.obj\
		map_v4_vlr_camel_subscription_info.obj\
		map_v4_vlr_capability.obj\
		map_v4_voice_broadcast_data.obj\
		map_v4_voice_group_call_data.obj\
		map_v4_zone_code.obj\
		map_v4_zone_code_list.obj







.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	gsmmap$(TYPE).lib\
	ossigsmmap$(TYPE).lib\
	iossgsmmap$(TYPE).lib\
	ioss_its_gsmmap_prefixed.obj\
	map-v4$(TYPE).lib\
	map-v4++$(TYPE).lib\
	ossmapv4$(TYPE).lib


gsmmap$(TYPE).lib: $(GSMMAP_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(GSMMAP_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
ossigsmmap$(TYPE).lib: $(OSSI_GSMMAP_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OSSI_GSMMAP_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
iossgsmmap$(TYPE).lib: $(IOSS_GSMMAP_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(IOSS_GSMMAP_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
map-v4$(TYPE).lib: $(MAPV4_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(MAPV4_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
map-v4++$(TYPE).lib: $(MAPV4CPP_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(MAPV4CPP_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
ioss_its_gsmmap_prefixed.obj: its_gsmmap.c
		$(CC) $(CFLAGS) -DOSS_DECODE -DRENAME_API -Fo$@ its_gsmmap.c
		mv $@ $(ITS_ROOT)/runtime
gsmmapvn.c: gsmmapvn.asn
		asn1 -ber gsmmapvn.asn
ossmapv4$(TYPE).lib: $(OSS_MAPV4_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OSS_MAPV4_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime


ossi_its_gsmmap.obj: its_gsmmap.c
		$(CC) $(CFLAGS) -DOSS_ENCODE -Fo$@ its_gsmmap.c

ioss_its_gsmmap.obj: its_gsmmap.c
		$(CC) $(CFLAGS) -DOSS_DECODE -Fo$@ its_gsmmap.c

gsmmap_tables.obj: gsmmap_tables.c
gsmmap_tables.c: gsmmap.asn
		sh -c "$(ITS_ROOT)/tools/bin/asnc.exe -A -a -f gsmmap.asn"
		mv gsmmap-types.h ..\include\itu

map_v4_absent_subscriber_diagnostic_sm_c.obj: map_v4_absent_subscriber_diagnostic_sm_c.c
map_v4_absent_subscriber_diagnostic_sm_c.c: map_v4_lrf.asn
		sh -c "$(ITS_ROOT)/tools/bin/asncc_v2.exe -explicitChoice -c -u $(ITS_ROOT)/tools/bin/asncc_useful.asn map_v4_lrf.asn"
		mv map_v4*.h $(ITS_ROOT)/GSMMAP/include/itu

map_v4_absent_subscriber_diagnostic_sm.obj: map_v4_absent_subscriber_diagnostic_sm.cpp
map_v4_absent_subscriber_diagnostic_sm.cpp: map_v4_lrf.asn
		sh -c "$(ITS_ROOT)/tools/bin/asncc_v2.exe -explicitChoice -cpp -cppNamespace map_v4 -xmlCppDoc -u $(ITS_ROOT)/tools/bin/asncc_useful.asn map_v4_lrf.asn"
		mv map_v4*.h $(ITS_ROOT)/GSMMAP/include/itu

map_v4_lrfvn.c: map_v4_lrfvn.asn
		sh -c "asn1.exe -ber -c++ map_v4_lrfvn.asn"
		mv map_v4_lrfvn.h $(ITS_ROOT)/GSMMAP/include/itu


clean:
	@mv map_v4_user_info_helper.cpp map_v4_user_info_helper_cpp
	@mv $(ITS_ROOT)/GSMMAP/include/itu/map_v4_user_info_helper.h $(ITS_ROOT)/GSMMAP/include/itu/map_v4_user_info_helper_h
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist gsmmap_tables.c            rm gsmmap_tables.c
	@if exist $(ITS_ROOT)/GSMMAP/include/itu/gsmmap-types.h rm $(ITS_ROOT)/GSMMAP/include/itu/gsmmap-types.h
	@if exist $(ITS_ROOT)/runtime/gsmmap$(TYPE).lib     rm $(ITS_ROOT)/runtime/gsmmap$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/ossigsmmap$(TYPE).lib rm $(ITS_ROOT)/runtime/ossigsmmap$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/iossgsmmap$(TYPE).lib rm $(ITS_ROOT)/runtime/iossgsmmap$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/ioss_its_gsmmap_prefixed.obj rm $(ITS_ROOT)/runtime/ioss_its_gsmmap_prefixed.obj
	@if exist map_v4*.c                                 rm map_v4*.c
	@if exist map_v4*.cpp                               rm map_v4*.cpp
	@if exist $(ITS_ROOT)/GSMMAP/include/itu/map_v4*.h  rm $(ITS_ROOT)/GSMMAP/include/itu/map_v4*.h
	@if exist $(ITS_ROOT)/runtime/map-v4$(TYPE).lib     rm $(ITS_ROOT)/runtime/map-v4$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/map-v4++$(TYPE).lib   rm $(ITS_ROOT)/runtime/map-v4++$(TYPE).lib
	@mv map_v4_user_info_helper_cpp map_v4_user_info_helper.cpp
	@mv $(ITS_ROOT)/GSMMAP/include/itu/map_v4_user_info_helper_h $(ITS_ROOT)/GSMMAP/include/itu/map_v4_user_info_helper.h
	@if exist $(ITS_ROOT)/runtime/ossmapv4$(TYPE).lib   rm $(ITS_ROOT)/runtime/ossmapv4$(TYPE).lib
	@echo Done

