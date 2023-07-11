# Microsoft Developer Studio Project File - Name="cap_v3_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cap_v3_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cap_v3_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cap_v3_c.mak" CFG="cap_v3_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cap_v3_c - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cap_v3_c - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cap_v3_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "cap_v3_c_Win32_Release"
# PROP Intermediate_Dir "cap_v3_c_Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-c" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CAP-V3.lib"

!ELSEIF  "$(CFG)" == "cap_v3_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cap_v3_c___Win32_Debug"
# PROP BASE Intermediate_Dir "cap_v3_c___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "cap_v3_c_Win32_Debug"
# PROP Intermediate_Dir "cap_v3_c_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-c" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CAP-V3D.lib"

!ENDIF 

# Begin Target

# Name "cap_v3_c - Win32 Release"
# Name "cap_v3_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cap_v3_a_ch_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_access_point_name_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_activity_test_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_additional_calling_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_age_of_location_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_alerting_pattern_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_aoc_before_answer_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_aoc_subsequent_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_aocgprs_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_append_free_format_data_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_application_timer_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_apply_charging_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_apply_charging_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_apply_charging_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_apply_charging_report_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_assist_request_instructions_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_assisting_sspip_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_backward_service_interaction_ind_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_basic_gap_criteria_c.c 
# End Source File
# Begin Source File

SOURCE=.\cap_v3_bcsm_event_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_bearer_capability_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_bothway_through_connection_ind_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cai_gsm0224_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_call_gap_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_call_information_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_call_information_request_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_call_reference_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_call_result_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_called_party_bcd_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_called_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_calling_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_calling_partys_category_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_a_ch_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_call_result_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_fci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_fcigprs_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_fcisms_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_sci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_camel_scigprs_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cancel_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cancel_failed_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cancel_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_carrier_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cell_global_id_or_service_area_id_fixed_length_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cell_global_id_or_service_area_id_or_lai_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cg_encountered_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_charging_result_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_collected_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_collected_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_connect_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_connect_arg_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_connect_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_connect_sms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_connect_to_resource_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_connected_number_treatment_ind_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_continue_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_continue_with_argument_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_continue_with_argument_arg_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_control_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_correlation_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_criticality_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cug_index_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_cug_interlock_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_date_and_time_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_destination_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_dp_specific_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_duration_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_elapsed_time_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_elapsed_time_roll_over_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_end_user_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_entity_released_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_error_treatment_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_establish_temporary_connection_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_report_bcsm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_report_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_report_sms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_specific_information_bcsm_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_specific_information_sms_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_type_bcsm_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_event_type_sms_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ext_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ext_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ext_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ext_qo_s_subscribed_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_extension_container_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_extension_field_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_fci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_fcigprs_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_fcisms_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_forward_service_interaction_ind_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_furnish_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_furnish_charging_information_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_furnish_charging_information_sms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gap_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gap_indicators_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gap_on_service_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gap_treatment_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_generic_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_generic_numbers_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_geodetic_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_geographical_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_charging_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_event_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_event_specific_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_event_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_qo_s_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprs_reference_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gprsms_class_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_gsn_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_high_layer_compatibility_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_imsi_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_inband_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_information_to_send_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_initial_dp_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_initial_dp_arg_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_initial_dpgprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_initial_dpsms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_initiating_entity_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_integer4_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_interval_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_invoke_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ip_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ipssp_capabilities_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_isdn_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_lai_fixed_length_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_leg_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_leg_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_location_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_location_information_gprs_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_location_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_lsa_identity_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_message_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_misc_call_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_monitor_mode_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ms_network_capability_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ms_radio_access_capability_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_na_carrier_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_na_carrier_selection_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_na_charge_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_na_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_na_oli_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_naea_cic_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_not_reachable_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ocsi_applicable_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_original_called_party_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_pcs_extensions_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_pdp_initiation_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_pdp_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_pdpid_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_play_announcement_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_private_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_private_extension_list_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_prompt_and_collect_user_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_quality_of_service_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_qo_s_subscribed_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_ra_identity_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_received_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_receiving_side_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_redirecting_party_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_redirection_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_release_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_release_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_release_sms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_request_report_bcsm_event_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_request_report_gprs_event_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_request_report_sms_event_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_requested_info_error_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_requested_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_requested_information_list_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_requested_information_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_requested_information_type_list_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_requested_information_value_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_reset_timer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_reset_timer_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_reset_timer_sms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_rp_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_scf_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_sci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_charge_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_scigprs_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_send_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_send_charging_information_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_sending_side_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_service_interaction_indicators_two_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_service_key_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_sgsn_capabilities_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_sms_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_sms_event_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_specialized_resource_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_subscriber_state_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_suppression_of_announcement_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_task_refused_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_tc_invoke_id_set_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_time_and_timezone_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_time_if_no_tariff_switch_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_time_if_tariff_switch_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_time_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_timer_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_timer_value_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_tone_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_tp_data_coding_scheme_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_tp_protocol_identifier_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_tp_short_message_submission_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_tp_validity_period_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_transferred_volume_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_transferred_volume_roll_over_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_unavailable_network_resource_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v3_variable_part_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\cap_v3_a_ch_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_charge_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_access_point_name_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_activity_test_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_additional_calling_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_age_of_location_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_alerting_pattern_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_aoc_before_answer_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_aoc_subsequent_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_aocgprs_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_append_free_format_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_application_timer_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_apply_charging_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_apply_charging_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_apply_charging_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_apply_charging_report_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_assist_request_instructions_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_assisting_sspip_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_backward_service_interaction_ind_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_basic_gap_criteria_c.h 
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_bcsm_event_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_bearer_capability_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_bothway_through_connection_ind_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cai_gsm0224_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_call_gap_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_call_information_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_call_information_request_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_call_reference_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_call_result_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_called_party_bcd_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_called_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_calling_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_calling_partys_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_a_ch_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_call_result_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_fci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_fcigprs_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_fcisms_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_sci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_camel_scigprs_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cancel_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cancel_failed_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cancel_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_carrier_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cell_global_id_or_service_area_id_fixed_length_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cell_global_id_or_service_area_id_or_lai_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cg_encountered_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_charging_result_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_collected_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_collected_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_connect_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_connect_arg_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_connect_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_connect_sms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_connect_to_resource_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_connected_number_treatment_ind_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_continue_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_continue_with_argument_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_continue_with_argument_arg_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_control_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_correlation_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_criticality_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cug_index_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_cug_interlock_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_date_and_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_destination_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_dp_specific_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_duration_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_elapsed_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_elapsed_time_roll_over_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_end_user_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_entity_released_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_error_treatment_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_establish_temporary_connection_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_report_bcsm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_report_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_report_sms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_specific_information_bcsm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_specific_information_sms_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_type_bcsm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_event_type_sms_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ext_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ext_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ext_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ext_qo_s_subscribed_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_extension_container_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_extension_field_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_fci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_fcigprs_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_fcisms_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_forward_service_interaction_ind_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_furnish_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_furnish_charging_information_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_furnish_charging_information_sms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gap_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gap_indicators_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gap_on_service_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gap_treatment_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_generic_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_generic_numbers_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_geodetic_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_geographical_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_charging_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_event_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_event_specific_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_event_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_qo_s_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprs_reference_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gprsms_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_gsn_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_high_layer_compatibility_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_imsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_inband_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_information_to_send_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_initial_dp_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_initial_dp_arg_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_initial_dpgprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_initial_dpsms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_initiating_entity_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_integer4_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_interval_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_invoke_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ip_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ipssp_capabilities_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_isdn_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_lai_fixed_length_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_leg_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_leg_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_location_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_location_information_gprs_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_location_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_lsa_identity_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_message_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_misc_call_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_monitor_mode_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ms_network_capability_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ms_radio_access_capability_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_na_carrier_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_na_carrier_selection_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_na_charge_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_na_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_na_oli_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_naea_cic_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_not_reachable_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ocsi_applicable_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_original_called_party_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_pcs_extensions_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_pdp_initiation_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_pdp_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_pdpid_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_play_announcement_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_private_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_private_extension_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_prompt_and_collect_user_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_quality_of_service_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_qo_s_subscribed_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_ra_identity_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_received_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_receiving_side_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_redirecting_party_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_redirection_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_release_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_release_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_release_sms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_request_report_bcsm_event_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_request_report_gprs_event_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_request_report_sms_event_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_requested_info_error_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_requested_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_requested_information_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_requested_information_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_requested_information_type_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_requested_information_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_reset_timer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_reset_timer_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_reset_timer_sms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_rp_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_scf_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_sci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_scigprs_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_send_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_send_charging_information_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_sending_side_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_service_interaction_indicators_two_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_service_key_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_sgsn_capabilities_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_sms_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_sms_event_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_specialized_resource_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_subscriber_state_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_suppression_of_announcement_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_task_refused_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_tc_invoke_id_set_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_time_and_timezone_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_time_if_no_tariff_switch_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_time_if_tariff_switch_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_time_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_timer_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_timer_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_tone_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_tp_data_coding_scheme_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_tp_protocol_identifier_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_tp_short_message_submission_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_tp_validity_period_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_transferred_volume_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_transferred_volume_roll_over_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_unavailable_network_resource_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v3_variable_part_c.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\cap_v3_lrf.asn

!IF  "$(CFG)" == "cap_v3_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\cap_v3_lrf.asn

".\cap_v3_a_ch_billing_charging_characteristics_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -xmlCDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn cap_v3_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "cap_v3_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\cap_v3_lrf.asn

".\cap_v3_a_ch_billing_charging_characteristics_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -xmlCDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn cap_v3_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
