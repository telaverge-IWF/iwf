# Microsoft Developer Studio Project File - Name="cap_v4_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cap_v4_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cap_v4_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cap_v4_cpp.mak" CFG="cap_v4_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cap_v4_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cap_v4_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cap_v4_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "cap_v4_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "cap_v4_cpp_Win32_Debug"
# PROP Intermediate_Dir "cap_v4_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CAP-V4++D.lib"

!ENDIF 

# Begin Target

# Name "cap_v4_cpp - Win32 Release"
# Name "cap_v4_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cap_v4_a_ch_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_a_ch_charging_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_access_point_name.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_additional_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_aoc_before_answer.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_aoc_subsequent.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_aocgprs.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_append_free_format_data.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_application_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_apply_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_apply_charging_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_apply_charging_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_apply_charging_report_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_assist_request_instructions_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_assisting_sspip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_audible_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_backward_service_interaction_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_basic_gap_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_bcsm_event.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_bcsm_failure.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_bearer_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_bothway_through_connection_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_burst.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_burst_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cai_gsm0224.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_gap_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_information_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_information_request_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_result.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_segment_failure.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_segment_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_call_segment_to_cancel.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_called_party_bcd_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_called_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_calling_partys_category.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_a_ch_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_call_result.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_fci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_fcigprs_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_fcisms_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_sci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_camel_scigprs_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cancel_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cancel_failed.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cancel_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cap_u_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_carrier.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cell_global_id_or_service_area_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cell_global_id_or_service_area_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cg_encountered.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_charge_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_charge_units_component.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_charge_units_total.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_charging_result.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_charging_roll_over.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_collected_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_collected_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_compound_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_connect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_connect_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_connect_sms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_connect_to_resource_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_connected_number_treatment_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_continue_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_continue_with_argument_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_continue_with_argument_arg_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_control_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_correlation_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_criticality_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_date_and_time.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_destination_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_disconnect_forward_connection_with_argument_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_disconnect_leg_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_dp_specific_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_duration.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_elapsed_time.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_elapsed_time_roll_over.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_end_user_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_entity_released_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_entity_released_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_error_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_establish_temporary_connection_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_evalues_and_tsw.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_evalues_component.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_evalues_total.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_notification_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_report_bcsm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_report_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_report_sms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_specific_charging_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_specific_information_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_specific_information_sms.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_type_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_type_charging_plmn.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_event_type_sms.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ext_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_extension_field.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_fci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_fcigprs_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_fcisms_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_forward_service_interaction_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_furnish_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_furnish_charging_information_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_furnish_charging_information_sms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gap_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gap_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gap_on_service.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gap_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_generic_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_generic_numbers.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_geodetic_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_charging_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_event.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_event_specific_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_event_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_qo_s.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprs_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gprsms_class.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_high_layer_compatibility.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_inband_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_info_charge_units_components.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_info_charge_units_total.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_info_evalue_components.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_info_evalue_total.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_information_to_send.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initial_dp_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initial_dp_arg_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initial_dpgprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initial_dpsms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initiate_call_attempt_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initiate_call_attempt_res.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_initiating_entity.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_integer4.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_interval.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_invoke_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ipssp_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_leg_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_leg_or_call_segment.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_leg_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_location_information_gprs.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_lsa_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_message_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_mid_call_control_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_misc_call_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_mo_sms_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_monitor_component.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_monitor_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_move_leg_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ms_classmark2.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ms_network_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ms_radio_access_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_mt_sms_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_na_oli_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ocsi_applicable.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_original_called_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_pdp_initiation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_pdpid.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_play_announcement_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_play_tone_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_prompt_and_collect_user_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_quality_of_service.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_ra_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_received_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_receiving_side_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_redirecting_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_redirection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_release_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_release_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_release_sms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_reporting_condition_evalue.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_reporting_condition_units.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_request_notification_charging_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_request_report_bcsm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_request_report_gprs_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_request_report_sms_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_requested_info_error.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_requested_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_requested_information_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_requested_information_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_requested_information_type_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_requested_information_value.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_reset_timer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_reset_timer_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_reset_timer_sms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_rp_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_scf_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_sci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_scigprs_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_send_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_send_charging_information_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_sending_side_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_service_interaction_indicators_two.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_sgsn_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_sms_event.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_specialized_resource_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_split_leg_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_supported_camel4_subsets.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tariff_switch_interval.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_task_refused.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tc_invoke_id_set.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_time_and_timezone.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_time_if_no_tariff_switch.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_time_if_tariff_switch.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_time_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_timer_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_timer_value.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tone.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tp_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tp_protocol_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tp_short_message_specific_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_tp_validity_period.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_transferred_volume.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_transferred_volume_roll_over.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_unavailable_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_units.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v4_variable_part.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\cap_v4_a_ch_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_a_ch_charging_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_access_point_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_additional_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_aoc_before_answer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_aoc_subsequent.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_aocgprs.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_append_free_format_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_application_timer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_apply_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_apply_charging_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_apply_charging_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_apply_charging_report_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_assist_request_instructions_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_assisting_sspip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_audible_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_backward_service_interaction_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_basic_gap_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_bcsm_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_bcsm_failure.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_bearer_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_bothway_through_connection_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_burst.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_burst_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cai_gsm0224.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_gap_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_information_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_information_request_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_segment_failure.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_segment_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_call_segment_to_cancel.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_called_party_bcd_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_called_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_calling_partys_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_a_ch_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_call_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_fci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_fcigprs_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_fcisms_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_sci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_camel_scigprs_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cancel_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cancel_failed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cancel_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cap_u_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_carrier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cell_global_id_or_service_area_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cell_global_id_or_service_area_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cg_encountered.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_charge_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_charge_units_component.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_charge_units_total.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_charging_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_charging_roll_over.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_collected_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_collected_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_compound_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_connect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_connect_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_connect_sms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_connect_to_resource_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_connected_number_treatment_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_continue_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_continue_with_argument_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_continue_with_argument_arg_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_control_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_correlation_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_criticality_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_date_and_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_destination_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_disconnect_forward_connection_with_argument_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_disconnect_leg_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_dp_specific_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_duration.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_elapsed_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_elapsed_time_roll_over.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_end_user_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_entity_released_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_entity_released_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_error_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_establish_temporary_connection_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_evalues_and_tsw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_evalues_component.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_evalues_total.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_notification_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_report_bcsm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_report_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_report_sms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_specific_charging_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_specific_information_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_specific_information_sms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_type_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_type_charging_plmn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_event_type_sms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ext_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_extension_field.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_fci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_fcigprs_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_fcisms_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_forward_service_interaction_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_furnish_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_furnish_charging_information_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_furnish_charging_information_sms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gap_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gap_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gap_on_service.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gap_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_generic_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_generic_numbers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_geodetic_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_charging_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_event_specific_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_event_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_qo_s.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprs_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gprsms_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_gsn_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_high_layer_compatibility.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_inband_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_info_charge_units_components.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_info_charge_units_total.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_info_evalue_components.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_info_evalue_total.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_information_to_send.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initial_dp_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initial_dp_arg_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initial_dpgprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initial_dpsms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initiate_call_attempt_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initiate_call_attempt_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_initiating_entity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_integer4.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_interval.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_invoke_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ipssp_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_leg_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_leg_or_call_segment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_leg_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_location_information_gprs.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_lsa_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_message_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_mid_call_control_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_misc_call_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_mo_sms_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_monitor_component.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_monitor_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_move_leg_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ms_classmark2.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ms_network_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ms_radio_access_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_mt_sms_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_na_oli_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ocsi_applicable.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_original_called_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_pdp_initiation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_pdpid.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_play_announcement_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_play_tone_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_prompt_and_collect_user_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_quality_of_service.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_ra_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_received_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_receiving_side_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_redirecting_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_redirection_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_release_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_release_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_release_sms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_reporting_condition_evalue.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_reporting_condition_units.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_request_notification_charging_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_request_report_bcsm_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_request_report_gprs_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_request_report_sms_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_requested_info_error.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_requested_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_requested_information_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_requested_information_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_requested_information_type_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_requested_information_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_reset_timer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_reset_timer_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_reset_timer_sms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_rp_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_scf_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_sci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_scigprs_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_send_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_send_charging_information_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_sending_side_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_service_interaction_indicators_two.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_sgsn_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_sms_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_specialized_resource_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_split_leg_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_supported_camel4_subsets.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tariff_switch_interval.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_task_refused.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tc_invoke_id_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_time_and_timezone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_time_if_no_tariff_switch.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_time_if_tariff_switch.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_time_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_timer_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_timer_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tp_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tp_protocol_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tp_short_message_specific_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_tp_validity_period.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_transferred_volume.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_transferred_volume_roll_over.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_unavailable_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_units.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v4_variable_part.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\cap_v4_lrf.asn

!IF  "$(CFG)" == "cap_v4_cpp - Win32 Release"

!ELSEIF  "$(CFG)" == "cap_v4_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=..\cap_v4_lrf.asn

".\cap_v4_a_ch_billing_charging_characteristics.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace cap_v4 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn cap_v4_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
