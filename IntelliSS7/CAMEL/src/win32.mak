#
# Copyright (C) 2000-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: win32.mak,v 9.1 2005/03/23 12:51:14 cvsadmin Exp $
#
# $Log: win32.mak,v $
# Revision 9.1  2005/03/23 12:51:14  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:49:17  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:08:40  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:13:18  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:14  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:53:01  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/15 23:56:29  mmiers
#
# Begin round 4.
#
# Revision 1.1  2000/06/22 19:34:35  npopov
# Created the Win32 makefile for building the CAMEL libraries for testing.
#
#
#


COMMON_INCLUDE = $(ITS_ROOT)\common\include
COMMON_LIB     = $(ITS_ROOT)\common\lib
CAMEL_INCLUDE  = $(ITS_ROOT)\CAMEL\include
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
		-I$(CAMEL_INCLUDE) -I$(CAMEL_INCLUDE)\itu -I$(COMMON_INCLUDE)\
		-I$(COMMON_INCLUDE)\asn-c -I$(TCAP_INCLUDE) -I$(SCCP_INCLUDE)\
		-I$(MTP3_INCLUDE) -I$(OSS_INCLUDE) -I$(COMMON_INCLUDE)\asn-cpp\
		-DDEBUG
CONFLAGS = -pdb:none
LDEBUG   = -debug:full -debugtype:cv $(LINKER)
!else if "$(debug)" == "no"
MAINFLAGS = -c -W3 $(OOPT) $(POPT) -Ze -D_WIN32 -DWIN32 -I$(CAMEL_INCLUDE)\
		-I$(CAMEL_INCLUDE)\itu -I$(COMMON_INCLUDE)\
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


OSS_CAPV3_OBJECTS = cap_v3_lrfvn.obj getv3pdu.obj
CAPV3_OBJECTS = cap_v3_a_ch_billing_charging_characteristics_c.obj\
		cap_v3_access_point_name_c.obj\
		cap_v3_activity_test_gprs_arg_c.obj\
		cap_v3_additional_calling_party_number_c.obj\
		cap_v3_age_of_location_information_c.obj\
		cap_v3_alerting_pattern_c.obj\
		cap_v3_aoc_before_answer_c.obj\
		cap_v3_aoc_subsequent_c.obj\
		cap_v3_aocgprs_c.obj\
		cap_v3_append_free_format_data_c.obj\
		cap_v3_application_timer_c.obj\
		cap_v3_apply_charging_arg_c.obj\
		cap_v3_apply_charging_gprs_arg_c.obj\
		cap_v3_apply_charging_report_arg_c.obj\
		cap_v3_apply_charging_report_gprs_arg_c.obj\
		cap_v3_assist_request_instructions_arg_c.obj\
		cap_v3_assisting_sspip_routing_address_c.obj\
		cap_v3_backward_service_interaction_ind_c.obj\
		cap_v3_bcsm_event_c.obj\
		cap_v3_bearer_capability_c.obj\
		cap_v3_bothway_through_connection_ind_c.obj\
		cap_v3_cai_gsm0224_c.obj\
		cap_v3_call_gap_arg_c.obj\
		cap_v3_call_information_report_arg_c.obj\
		cap_v3_call_information_request_arg_c.obj\
		cap_v3_call_reference_number_c.obj\
		cap_v3_call_result_c.obj\
		cap_v3_called_party_bcd_number_c.obj\
		cap_v3_called_party_number_c.obj\
		cap_v3_calling_party_number_c.obj\
		cap_v3_calling_partys_category_c.obj\
		cap_v3_camel_a_ch_billing_charging_characteristics_c.obj\
		cap_v3_camel_call_result_c.obj\
		cap_v3_camel_fci_billing_charging_characteristics_c.obj\
		cap_v3_camel_fcigprs_billing_charging_characteristics_c.obj\
		cap_v3_camel_fcisms_billing_charging_characteristics_c.obj\
		cap_v3_camel_sci_billing_charging_characteristics_c.obj\
		cap_v3_camel_scigprs_billing_charging_characteristics_c.obj\
		cap_v3_cancel_arg_c.obj\
		cap_v3_cancel_failed_c.obj\
		cap_v3_cancel_gprs_arg_c.obj\
		cap_v3_cause_c.obj\
		cap_v3_cell_global_id_or_service_area_id_fixed_length_c.obj\
		cap_v3_cell_global_id_or_service_area_id_or_lai_c.obj\
		cap_v3_cg_encountered_c.obj\
		cap_v3_charging_characteristics_c.obj\
		cap_v3_charging_result_c.obj\
		cap_v3_collected_digits_c.obj\
		cap_v3_collected_info_c.obj\
		cap_v3_connect_arg_c.obj\
		cap_v3_connect_arg_extension_c.obj\
		cap_v3_connect_gprs_arg_c.obj\
		cap_v3_connect_sms_arg_c.obj\
		cap_v3_connect_to_resource_arg_c.obj\
		cap_v3_connected_number_treatment_ind_c.obj\
		cap_v3_continue_gprs_arg_c.obj\
		cap_v3_continue_with_argument_arg_c.obj\
		cap_v3_continue_with_argument_arg_extension_c.obj\
		cap_v3_control_type_c.obj\
		cap_v3_correlation_id_c.obj\
		cap_v3_criticality_type_c.obj\
		cap_v3_cug_index_c.obj\
		cap_v3_cug_interlock_c.obj\
		cap_v3_date_and_time_c.obj\
		cap_v3_destination_routing_address_c.obj\
		cap_v3_digits_c.obj\
		cap_v3_dp_specific_criteria_c.obj\
		cap_v3_duration_c.obj\
		cap_v3_elapsed_time_c.obj\
		cap_v3_entity_released_gprs_arg_c.obj\
		cap_v3_error_treatment_c.obj\
		cap_v3_establish_temporary_connection_arg_c.obj\
		cap_v3_event_report_bcsm_arg_c.obj\
		cap_v3_event_report_gprs_arg_c.obj\
		cap_v3_event_report_sms_arg_c.obj\
		cap_v3_event_specific_information_bcsm_c.obj\
		cap_v3_event_specific_information_sms_c.obj\
		cap_v3_event_type_bcsm_c.obj\
		cap_v3_event_type_sms_c.obj\
		cap_v3_ext_basic_service_code_c.obj\
		cap_v3_ext_bearer_service_code_c.obj\
		cap_v3_ext_teleservice_code_c.obj\
		cap_v3_extension_container_c.obj\
		cap_v3_extension_field_c.obj\
		cap_v3_fci_billing_charging_characteristics_c.obj\
		cap_v3_fcigprs_billing_charging_characteristics_c.obj\
		cap_v3_fcisms_billing_charging_characteristics_c.obj\
		cap_v3_forward_service_interaction_ind_c.obj\
		cap_v3_furnish_charging_information_arg_c.obj\
		cap_v3_furnish_charging_information_gprs_arg_c.obj\
		cap_v3_furnish_charging_information_sms_arg_c.obj\
		cap_v3_gap_criteria_c.obj\
		cap_v3_gap_indicators_c.obj\
		cap_v3_gap_on_service_c.obj\
		cap_v3_gap_treatment_c.obj\
		cap_v3_generic_number_c.obj\
		cap_v3_generic_numbers_c.obj\
		cap_v3_geodetic_information_c.obj\
		cap_v3_geographical_information_c.obj\
		cap_v3_gprs_cause_c.obj\
		cap_v3_gprs_charging_id_c.obj\
		cap_v3_gprs_event_c.obj\
		cap_v3_gprs_event_specific_information_c.obj\
		cap_v3_gprs_event_type_c.obj\
		cap_v3_gprs_reference_number_c.obj\
		cap_v3_gprsms_class_c.obj\
		cap_v3_high_layer_compatibility_c.obj\
		cap_v3_imsi_c.obj\
		cap_v3_inband_info_c.obj\
		cap_v3_information_to_send_c.obj\
		cap_v3_initial_dp_arg_c.obj\
		cap_v3_initial_dp_arg_extension_c.obj\
		cap_v3_initial_dpgprs_arg_c.obj\
		cap_v3_initial_dpsms_arg_c.obj\
		cap_v3_initiating_entity_c.obj\
		cap_v3_integer4_c.obj\
		cap_v3_interval_c.obj\
		cap_v3_invoke_id_c.obj\
		cap_v3_ip_routing_address_c.obj\
		cap_v3_ipssp_capabilities_c.obj\
		cap_v3_isdn_address_string_c.obj\
		cap_v3_lai_fixed_length_c.obj\
		cap_v3_leg_id_c.obj\
		cap_v3_leg_type_c.obj\
		cap_v3_location_information_c.obj\
		cap_v3_location_information_gprs_c.obj\
		cap_v3_location_number_c.obj\
		cap_v3_lsa_identity_c.obj\
		cap_v3_message_id_c.obj\
		cap_v3_misc_call_info_c.obj\
		cap_v3_monitor_mode_c.obj\
		cap_v3_ms_network_capability_c.obj\
		cap_v3_ms_radio_access_capability_c.obj\
		cap_v3_na_carrier_information_c.obj\
		cap_v3_na_carrier_selection_info_c.obj\
		cap_v3_na_charge_number_c.obj\
		cap_v3_na_info_c.obj\
		cap_v3_na_oli_info_c.obj\
		cap_v3_naea_cic_c.obj\
		cap_v3_not_reachable_reason_c.obj\
		cap_v3_ocsi_applicable_c.obj\
		cap_v3_original_called_party_id_c.obj\
		cap_v3_pcs_extensions_c.obj\
		cap_v3_pdp_type_c.obj\
		cap_v3_pdpid_c.obj\
		cap_v3_play_announcement_arg_c.obj\
		cap_v3_private_extension_c.obj\
		cap_v3_private_extension_list_c.obj\
		cap_v3_prompt_and_collect_user_information_arg_c.obj\
		cap_v3_quality_of_service_c.obj\
		cap_v3_ra_identity_c.obj\
		cap_v3_received_information_arg_c.obj\
		cap_v3_receiving_side_id_c.obj\
		cap_v3_redirecting_party_id_c.obj\
		cap_v3_redirection_information_c.obj\
		cap_v3_release_call_arg_c.obj\
		cap_v3_release_gprs_arg_c.obj\
		cap_v3_release_sms_arg_c.obj\
		cap_v3_request_report_bcsm_event_arg_c.obj\
		cap_v3_request_report_gprs_event_arg_c.obj\
		cap_v3_request_report_sms_event_arg_c.obj\
		cap_v3_requested_info_error_c.obj\
		cap_v3_requested_information_c.obj\
		cap_v3_requested_information_list_c.obj\
		cap_v3_requested_information_type_c.obj\
		cap_v3_requested_information_type_list_c.obj\
		cap_v3_requested_information_value_c.obj\
		cap_v3_reset_timer_arg_c.obj\
		cap_v3_reset_timer_gprs_arg_c.obj\
		cap_v3_reset_timer_sms_arg_c.obj\
		cap_v3_rp_cause_c.obj\
		cap_v3_scf_id_c.obj\
		cap_v3_sci_billing_charging_characteristics_c.obj\
		cap_v3_scigprs_billing_charging_characteristics_c.obj\
		cap_v3_send_charging_information_arg_c.obj\
		cap_v3_send_charging_information_gprs_arg_c.obj\
		cap_v3_sending_side_id_c.obj\
		cap_v3_service_interaction_indicators_two_c.obj\
		cap_v3_service_key_c.obj\
		cap_v3_sgsn_capabilities_c.obj\
		cap_v3_sms_cause_c.obj\
		cap_v3_sms_event_c.obj\
		cap_v3_specialized_resource_report_arg_c.obj\
		cap_v3_subscriber_state_c.obj\
		cap_v3_suppression_of_announcement_c.obj\
		cap_v3_task_refused_c.obj\
		cap_v3_tc_invoke_id_set_c.obj\
		cap_v3_time_and_timezone_c.obj\
		cap_v3_time_if_no_tariff_switch_c.obj\
		cap_v3_time_if_tariff_switch_c.obj\
		cap_v3_time_information_c.obj\
		cap_v3_timer_id_c.obj\
		cap_v3_timer_value_c.obj\
		cap_v3_tone_c.obj\
		cap_v3_tp_data_coding_scheme_c.obj\
		cap_v3_tp_protocol_identifier_c.obj\
		cap_v3_tp_short_message_submission_info_c.obj\
		cap_v3_tp_validity_period_c.obj\
		cap_v3_transferred_volume_c.obj\
		cap_v3_unavailable_network_resource_c.obj\
		cap_v3_variable_part_c.obj


CAPV3CPP_OBJECTS = cap_v3_a_ch_billing_charging_characteristics.obj\
		cap_v3_access_point_name.obj\
		cap_v3_activity_test_gprs_arg.obj\
		cap_v3_additional_calling_party_number.obj\
		cap_v3_age_of_location_information.obj\
		cap_v3_alerting_pattern.obj\
		cap_v3_aoc_before_answer.obj\
		cap_v3_aoc_subsequent.obj\
		cap_v3_aocgprs.obj\
		cap_v3_append_free_format_data.obj\
		cap_v3_application_timer.obj\
		cap_v3_apply_charging_arg.obj\
		cap_v3_apply_charging_gprs_arg.obj\
		cap_v3_apply_charging_report_arg.obj\
		cap_v3_apply_charging_report_gprs_arg.obj\
		cap_v3_assist_request_instructions_arg.obj\
		cap_v3_assisting_sspip_routing_address.obj\
		cap_v3_backward_service_interaction_ind.obj\
		cap_v3_bcsm_event.obj\
		cap_v3_bearer_capability.obj\
		cap_v3_bothway_through_connection_ind.obj\
		cap_v3_cai_gsm0224.obj\
		cap_v3_call_gap_arg.obj\
		cap_v3_call_information_report_arg.obj\
		cap_v3_call_information_request_arg.obj\
		cap_v3_call_reference_number.obj\
		cap_v3_call_result.obj\
		cap_v3_called_party_bcd_number.obj\
		cap_v3_called_party_number.obj\
		cap_v3_calling_party_number.obj\
		cap_v3_calling_partys_category.obj\
		cap_v3_camel_a_ch_billing_charging_characteristics.obj\
		cap_v3_camel_call_result.obj\
		cap_v3_camel_fci_billing_charging_characteristics.obj\
		cap_v3_camel_fcigprs_billing_charging_characteristics.obj\
		cap_v3_camel_fcisms_billing_charging_characteristics.obj\
		cap_v3_camel_sci_billing_charging_characteristics.obj\
		cap_v3_camel_scigprs_billing_charging_characteristics.obj\
		cap_v3_cancel_arg.obj\
		cap_v3_cancel_failed.obj\
		cap_v3_cancel_gprs_arg.obj\
		cap_v3_cause.obj\
		cap_v3_cell_global_id_or_service_area_id_fixed_length.obj\
		cap_v3_cell_global_id_or_service_area_id_or_lai.obj\
		cap_v3_cg_encountered.obj\
		cap_v3_charging_characteristics.obj\
		cap_v3_charging_result.obj\
		cap_v3_collected_digits.obj\
		cap_v3_collected_info.obj\
		cap_v3_connect_arg.obj\
		cap_v3_connect_arg_extension.obj\
		cap_v3_connect_gprs_arg.obj\
		cap_v3_connect_sms_arg.obj\
		cap_v3_connect_to_resource_arg.obj\
		cap_v3_connected_number_treatment_ind.obj\
		cap_v3_continue_gprs_arg.obj\
		cap_v3_continue_with_argument_arg.obj\
		cap_v3_continue_with_argument_arg_extension.obj\
		cap_v3_control_type.obj\
		cap_v3_correlation_id.obj\
		cap_v3_criticality_type.obj\
		cap_v3_cug_index.obj\
		cap_v3_cug_interlock.obj\
		cap_v3_date_and_time.obj\
		cap_v3_destination_routing_address.obj\
		cap_v3_digits.obj\
		cap_v3_dp_specific_criteria.obj\
		cap_v3_duration.obj\
		cap_v3_elapsed_time.obj\
		cap_v3_entity_released_gprs_arg.obj\
		cap_v3_error_treatment.obj\
		cap_v3_establish_temporary_connection_arg.obj\
		cap_v3_event_report_bcsm_arg.obj\
		cap_v3_event_report_gprs_arg.obj\
		cap_v3_event_report_sms_arg.obj\
		cap_v3_event_specific_information_bcsm.obj\
		cap_v3_event_specific_information_sms.obj\
		cap_v3_event_type_bcsm.obj\
		cap_v3_event_type_sms.obj\
		cap_v3_ext_basic_service_code.obj\
		cap_v3_ext_bearer_service_code.obj\
		cap_v3_ext_teleservice_code.obj\
		cap_v3_extension_container.obj\
		cap_v3_extension_field.obj\
		cap_v3_fci_billing_charging_characteristics.obj\
		cap_v3_fcigprs_billing_charging_characteristics.obj\
		cap_v3_fcisms_billing_charging_characteristics.obj\
		cap_v3_forward_service_interaction_ind.obj\
		cap_v3_furnish_charging_information_arg.obj\
		cap_v3_furnish_charging_information_gprs_arg.obj\
		cap_v3_furnish_charging_information_sms_arg.obj\
		cap_v3_gap_criteria.obj\
		cap_v3_gap_indicators.obj\
		cap_v3_gap_on_service.obj\
		cap_v3_gap_treatment.obj\
		cap_v3_generic_number.obj\
		cap_v3_generic_numbers.obj\
		cap_v3_geodetic_information.obj\
		cap_v3_geographical_information.obj\
		cap_v3_gprs_cause.obj\
		cap_v3_gprs_charging_id.obj\
		cap_v3_gprs_event.obj\
		cap_v3_gprs_event_specific_information.obj\
		cap_v3_gprs_event_type.obj\
		cap_v3_gprs_reference_number.obj\
		cap_v3_gprsms_class.obj\
		cap_v3_high_layer_compatibility.obj\
		cap_v3_imsi.obj\
		cap_v3_inband_info.obj\
		cap_v3_information_to_send.obj\
		cap_v3_initial_dp_arg.obj\
		cap_v3_initial_dp_arg_extension.obj\
		cap_v3_initial_dpgprs_arg.obj\
		cap_v3_initial_dpsms_arg.obj\
		cap_v3_initiating_entity.obj\
		cap_v3_integer4.obj\
		cap_v3_interval.obj\
		cap_v3_invoke_id.obj\
		cap_v3_ip_routing_address.obj\
		cap_v3_ipssp_capabilities.obj\
		cap_v3_isdn_address_string.obj\
		cap_v3_lai_fixed_length.obj\
		cap_v3_leg_id.obj\
		cap_v3_leg_type.obj\
		cap_v3_location_information.obj\
		cap_v3_location_information_gprs.obj\
		cap_v3_location_number.obj\
		cap_v3_lsa_identity.obj\
		cap_v3_message_id.obj\
		cap_v3_misc_call_info.obj\
		cap_v3_monitor_mode.obj\
		cap_v3_ms_network_capability.obj\
		cap_v3_ms_radio_access_capability.obj\
		cap_v3_na_carrier_information.obj\
		cap_v3_na_carrier_selection_info.obj\
		cap_v3_na_charge_number.obj\
		cap_v3_na_info.obj\
		cap_v3_na_oli_info.obj\
		cap_v3_naea_cic.obj\
		cap_v3_not_reachable_reason.obj\
		cap_v3_ocsi_applicable.obj\
		cap_v3_original_called_party_id.obj\
		cap_v3_pcs_extensions.obj\
		cap_v3_pdp_type.obj\
		cap_v3_pdpid.obj\
		cap_v3_play_announcement_arg.obj\
		cap_v3_private_extension.obj\
		cap_v3_private_extension_list.obj\
		cap_v3_prompt_and_collect_user_information_arg.obj\
		cap_v3_quality_of_service.obj\
		cap_v3_ra_identity.obj\
		cap_v3_received_information_arg.obj\
		cap_v3_receiving_side_id.obj\
		cap_v3_redirecting_party_id.obj\
		cap_v3_redirection_information.obj\
		cap_v3_release_call_arg.obj\
		cap_v3_release_gprs_arg.obj\
		cap_v3_release_sms_arg.obj\
		cap_v3_request_report_bcsm_event_arg.obj\
		cap_v3_request_report_gprs_event_arg.obj\
		cap_v3_request_report_sms_event_arg.obj\
		cap_v3_requested_info_error.obj\
		cap_v3_requested_information.obj\
		cap_v3_requested_information_list.obj\
		cap_v3_requested_information_type.obj\
		cap_v3_requested_information_type_list.obj\
		cap_v3_requested_information_value.obj\
		cap_v3_reset_timer_arg.obj\
		cap_v3_reset_timer_gprs_arg.obj\
		cap_v3_reset_timer_sms_arg.obj\
		cap_v3_rp_cause.obj\
		cap_v3_scf_id.obj\
		cap_v3_sci_billing_charging_characteristics.obj\
		cap_v3_scigprs_billing_charging_characteristics.obj\
		cap_v3_send_charging_information_arg.obj\
		cap_v3_send_charging_information_gprs_arg.obj\
		cap_v3_sending_side_id.obj\
		cap_v3_service_interaction_indicators_two.obj\
		cap_v3_service_key.obj\
		cap_v3_sgsn_capabilities.obj\
		cap_v3_sms_cause.obj\
		cap_v3_sms_event.obj\
		cap_v3_specialized_resource_report_arg.obj\
		cap_v3_subscriber_state.obj\
		cap_v3_suppression_of_announcement.obj\
		cap_v3_task_refused.obj\
		cap_v3_tc_invoke_id_set.obj\
		cap_v3_time_and_timezone.obj\
		cap_v3_time_if_no_tariff_switch.obj\
		cap_v3_time_if_tariff_switch.obj\
		cap_v3_time_information.obj\
		cap_v3_timer_id.obj\
		cap_v3_timer_value.obj\
		cap_v3_tone.obj\
		cap_v3_tp_data_coding_scheme.obj\
		cap_v3_tp_protocol_identifier.obj\
		cap_v3_tp_short_message_submission_info.obj\
		cap_v3_tp_validity_period.obj\
		cap_v3_transferred_volume.obj\
		cap_v3_unavailable_network_resource.obj\
		cap_v3_variable_part.obj




.c.obj::
	$(CC) $(CFLAGS) $<
.cpp.obj::
	$(CC) $(CPLUSPLUSFLAGS) $<



all:	cap-v3$(TYPE).lib\
	cap-v3++$(TYPE).lib\
	osscapv3$(TYPE).lib


cap-v3$(TYPE).lib: $(CAPV3_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(CAPV3_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
cap-v3++$(TYPE).lib: $(CAPV3CPP_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(CAPV3CPP_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime
osscapv3$(TYPE).lib: $(OSS_CAPV3_OBJECTS)
		$(IMPLIB) -machine:$(CPU) -out:$@ $(OSS_CAPV3_OBJECTS)
		mv $@ $(ITS_ROOT)/runtime


cap_v3_a_ch_billing_charging_characteristics_c.obj: cap_v3_a_ch_billing_charging_characteristics_c.c
cap_v3_a_ch_billing_charging_characteristics_c.c: cap_v3_lrf.asn
		sh -c "$(ITS_ROOT)/tools/bin/asncc_v2.exe -explicitChoice -c -xmlCDoc -u $(ITS_ROOT)/tools/bin/asncc_useful.asn cap_v3_lrf.asn"
		mv cap_v3*.h $(ITS_ROOT)/CAMEL/include/itu

cap_v3_a_ch_billing_charging_characteristics.obj: cap_v3_a_ch_billing_charging_characteristics.cpp
cap_v3_a_ch_billing_charging_characteristics.cpp: cap_v3_lrf.asn
		sh -c "$(ITS_ROOT)/tools/bin/asncc_v2.exe -explicitChoice -cpp -cppNamespace cap_v3 -xmlCppDoc -u $(ITS_ROOT)/tools/bin/asncc_useful.asn cap_v3_lrf.asn"
		mv cap_v3*.h $(ITS_ROOT)/CAMEL/include/itu

cap_v3_lrfvn.c: cap_v3_lrfvn.asn
		sh -c "asn1.exe -ber -c -nounique cap_v3_lrfvn.asn"
		mv cap_v3_lrfvn.h $(ITS_ROOT)/CAMEL/include/itu


clean:
	@if exist *.obj                      rm *.obj
	@if exist *.pdb                      rm *.pdb
	@if exist cap_v3*.c                                 rm cap_v3*.c
	@if exist cap_v3*.cpp                               rm cap_v3*.cpp
	@if exist $(ITS_ROOT)/CAMEL/include/itu/cap_v3*.h  rm $(ITS_ROOT)/CAMEL/include/itu/cap_v3*.h
	@if exist $(ITS_ROOT)/runtime/cap-v3$(TYPE).lib     rm $(ITS_ROOT)/runtime/cap-v3$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/cap-v3++$(TYPE).lib   rm $(ITS_ROOT)/runtime/cap-v3++$(TYPE).lib
	@if exist $(ITS_ROOT)/runtime/osscapv3$(TYPE).lib   rm $(ITS_ROOT)/runtime/osscapv3$(TYPE).lib
	@echo Done

