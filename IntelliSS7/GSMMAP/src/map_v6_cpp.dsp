# Microsoft Developer Studio Project File - Name="map_v6_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v6_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v6_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v6_cpp.mak" CFG="map_v6_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v6_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v6_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v6_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v6_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v6_cpp_Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\MAP-V6++.lib"

!ELSEIF  "$(CFG)" == "map_v6_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v6_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v6_cpp_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V6++D.lib"

!ENDIF 

# Begin Target

# Name "map_v6_cpp - Win32 Release"
# Name "map_v6_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v6_absent_subscriber_diagnostic_sm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_absent_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_absent_subscriber_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_absent_subscriber_sm_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_access_network_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_access_network_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_activate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_add_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_additional_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_age_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_allowed_gsm_algorithms.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_allowed_umts_algorithms.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_any_time_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_any_time_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_any_time_modification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_any_time_modification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_any_time_subscription_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_any_time_subscription_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_apn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_asci_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ati_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_atm_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_atsi_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_authentication_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_authentication_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_authentication_quintuplet.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_authentication_triplet.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_autn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_auts.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_basic_service_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_bearer_serv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_busy_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_barring_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_direction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_diversion_treatment_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_termination_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_type_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_camel_capability_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_camel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_camel_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cancel_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cancellation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cause_value.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_request_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ccbs_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cell_global_id_or_service_area_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cell_global_id_or_service_area_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_chosen_channel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_chosen_encryption_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_chosen_integrity_protection_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_chosen_radio_resource_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_chosen_speech_version.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ciphering_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ck.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cksn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_codec_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_context_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_context_id_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cs_allocation_retention_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_reject_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_current_security_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_d_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_data_missing_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_deactivate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_default_call_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_default_gprs_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_default_sms_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_destination_number_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_destination_number_length_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_destination_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_dp_analysed_info_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_dp_analysed_info_criterium.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_emlpp_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_emlpp_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_encryption_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_erase_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_erase_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_event_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_call_bar_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_call_bar_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_call_barring_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_forw_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_forw_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_forw_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_forw_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_forwarding_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_no_rep_cond_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_ss_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_extensible_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_extensible_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_external_client.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_external_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_facility_not_sup_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forward_access_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forward_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_failed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forwarding_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ftn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_generic_service_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_geodetic_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gmlc_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gmlc_restriction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_subscription_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_subscription_data_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gprs_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_group_key_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gsm_security_context_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_horizontal_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ik.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_illegal_equipment_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_illegal_ss_operation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_illegal_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_imsi_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_incompatible_terminal_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_information_not_available_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_integrity_protection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_interrogation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ist_alert_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ist_alert_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ist_alert_timer_value.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ist_command_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ist_command_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ist_support_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_key_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ksi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_client_external_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_client_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_client_internal_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_client_name.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_client_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_event.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_privacy_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_privacy_exception_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lcs_qo_s.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_location_estimate_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_location_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_long_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_long_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_identity_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_information_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_lsa_only_access_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_m_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_match_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_max_mc_bearers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mc_bearers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mc_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_message_wait_list_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mm_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mm_event_not_supported_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mo_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mo_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mobility_triggers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_modification_instruction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_modification_request_for_cb_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_modification_request_for_cf_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_modification_request_for_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_molr_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_molr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_monitoring_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mt_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mt_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_multicall_bearer_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_naea_preferred_ci.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_name_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_network_access_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_no_group_call_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_no_roaming_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_no_subscriber_reply_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_mm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_mm_event_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_ms_present_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_ms_present_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_subscriber_data_modified_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_subscriber_data_modified_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_notification_to_ms_user.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_number_changed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_number_of_requested_vectors.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_number_portability_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_bcsm_camel_tdp_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_cause_value_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_o_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_odb_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_or_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_or_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_password.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_pdp_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_pdp_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_pdp_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_permitted_encryption_algorithms.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_permitted_integrity_protection_algorithms.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_plmn_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_position_method_failure_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_position_method_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_prepare_group_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_prepare_group_call_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_prepare_subsequent_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_process_access_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_process_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_siwfs_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_siwfs_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_subscriber_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_subscriber_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_subscriber_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_purge_ms_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_quintuplet_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_rab_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_radio_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_radio_resource_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_radio_resource_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_re_synchronisation_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ready_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_register_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_register_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_relocation_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_relocation_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_remote_user_free_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_remote_user_free_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_report_sm_delivery_status_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_reporting_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_requested_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_requested_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_requested_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_resource_limitation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_response_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_response_time_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_resume_call_handling_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_rnc_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_roaming_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_routing_info_for_lcs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_routing_info_for_lcs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ruf_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_selected_gsm_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_selected_umts_algorithms.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_group_call_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_group_call_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_identification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_routing_info_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_routing_info_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_set_reporting_state_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_set_reporting_state_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sgsn_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sgsn_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_short_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_siwfs_signalling_modify_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_siwfs_signalling_modify_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_rp_mti.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sm_rp_smea.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sms_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sms_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sms_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sms_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_specific_csi_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_camel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_event_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_event_specification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_invocation_notification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_invocation_notification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_not_available_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_subscription_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_state_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_status_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_sub_busy_for_mt_sms_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_location_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_location_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_super_charger_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_supported_ccbs_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_supported_gad_shapes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_bcsm_camel_tdp_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_cause_value_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_t_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_target_cell_outside_gca_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_teleserv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_tracing_buffer_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_triplet_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_umts_security_context_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unauthorized_lcs_client_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unauthorized_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unauthorized_requesting_network_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unexpected_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unidentified_sub_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unknown_or_unreachable_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unknown_subscriber_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_unknown_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_update_gprs_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_update_gprs_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_user_info_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_uu_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_uu_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_uui.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_vbs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_vertical_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_vgcs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_vlr_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_voice_broadcast_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_voice_group_call_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_wrong_password_attempts_counter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_xres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_v6_absent_subscriber_diagnostic_sm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_absent_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_absent_subscriber_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_absent_subscriber_sm_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_access_network_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_access_network_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_activate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_add_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_additional_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_age_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_allowed_gsm_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_allowed_umts_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_any_time_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_any_time_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_any_time_modification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_any_time_modification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_any_time_subscription_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_any_time_subscription_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_apn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_asci_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ati_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_atm_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_atsi_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_authentication_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_authentication_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_authentication_quintuplet.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_authentication_triplet.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_autn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_auts.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_basic_service_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_bearer_serv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_busy_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_barring_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_direction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_diversion_treatment_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_termination_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_call_type_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_camel_capability_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_camel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_camel_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cancel_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cancellation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cause_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_request_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ccbs_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cell_global_id_or_service_area_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cell_global_id_or_service_area_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_chosen_channel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_chosen_encryption_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_chosen_integrity_protection_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_chosen_radio_resource_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_chosen_speech_version.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ciphering_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ck.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cksn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_codec_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_context_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_context_id_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cs_allocation_retention_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_reject_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_current_security_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_d_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_data_missing_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_deactivate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_default_call_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_default_gprs_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_default_sms_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_destination_number_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_destination_number_length_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_destination_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_dp_analysed_info_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_dp_analysed_info_criterium.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_emlpp_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_emlpp_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_encryption_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_erase_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_erase_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_event_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_call_bar_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_call_bar_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_call_barring_info_for_cse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_forw_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_forw_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_forw_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_forw_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_forwarding_info_for_cse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_no_rep_cond_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_ss_info_for_cse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_extended_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_extensible_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_extensible_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_external_client.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_external_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_facility_not_sup_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forward_access_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forward_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_failed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_forwarding_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ftn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_generic_service_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_geodetic_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gmlc_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gmlc_restriction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gmsc_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_subscription_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_subscription_data_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gprs_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_group_key_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gsm_security_context_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_gsn_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_horizontal_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ik.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_illegal_equipment_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_illegal_ss_operation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_illegal_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_incompatible_terminal_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_information_not_available_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_integrity_protection_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_interrogation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ist_alert_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ist_alert_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ist_alert_timer_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ist_command_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ist_command_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ist_support_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_key_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ksi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_client_external_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_client_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_client_internal_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_client_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_client_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_location_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_privacy_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_privacy_exception_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lcs_qo_s.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_location_estimate_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_location_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_long_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_long_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_attributes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_identity_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_information_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_lsa_only_access_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_m_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_match_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_max_mc_bearers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mc_bearers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mc_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_message_wait_list_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mm_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mm_event_not_supported_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mo_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mo_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mobility_triggers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_modification_instruction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_modification_request_for_cb_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_modification_request_for_cf_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_modification_request_for_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_molr_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_molr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_monitoring_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mt_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mt_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_multicall_bearer_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_naea_preferred_ci.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_name_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_network_access_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_no_group_call_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_no_roaming_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_no_subscriber_reply_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_note_mm_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_note_mm_event_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_note_ms_present_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_note_ms_present_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_note_subscriber_data_modified_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_note_subscriber_data_modified_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_notification_to_ms_user.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_number_changed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_number_of_requested_vectors.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_number_portability_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_bcsm_camel_tdp_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_cause_value_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_o_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_odb_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_or_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_or_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_pdp_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_pdp_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_pdp_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_permitted_encryption_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_permitted_integrity_protection_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_plmn_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_position_method_failure_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_position_method_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_prepare_group_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_prepare_group_call_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_prepare_subsequent_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_process_access_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_process_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_siwfs_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_siwfs_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_subscriber_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_subscriber_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_subscriber_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_provide_subscriber_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_purge_ms_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_quintuplet_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_rab_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_radio_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_radio_resource_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_radio_resource_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_re_synchronisation_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ready_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_register_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_register_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_relocation_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_relocation_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_remote_user_free_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_remote_user_free_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_report_sm_delivery_status_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_reporting_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_requested_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_requested_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_requested_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_resource_limitation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_response_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_response_time_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_resume_call_handling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_resume_call_handling_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_rnc_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_roaming_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_routing_info_for_lcs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_routing_info_for_lcs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ruf_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_selected_gsm_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_selected_umts_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_group_call_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_group_call_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_identification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_routing_info_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_routing_info_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_set_reporting_state_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_set_reporting_state_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sgsn_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sgsn_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_short_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_siwfs_signalling_modify_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_siwfs_signalling_modify_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_rp_mti.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sm_rp_smea.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sms_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sms_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sms_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sms_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_specific_csi_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_camel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_event_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_event_specification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_invocation_notification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_invocation_notification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_not_available_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ss_subscription_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_state_attributes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_status_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_sub_busy_for_mt_sms_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_location_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_location_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_super_charger_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_supported_ccbs_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_supported_gad_shapes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_bcsm_camel_tdp_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_cause_value_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_t_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_target_cell_outside_gca_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_teleserv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_tracing_buffer_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_triplet_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_umts_security_context_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unauthorized_lcs_client_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unauthorized_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unauthorized_requesting_network_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unexpected_data_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unidentified_sub_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unknown_or_unreachable_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unknown_subscriber_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_unknown_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_update_gprs_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_update_gprs_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_user_info_helper.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_uu_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_uu_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_uui.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_vbs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_vertical_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_vgcs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_vlr_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_vlr_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_voice_broadcast_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_voice_group_call_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_wrong_password_attempts_counter.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_xres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v6_zone_code_list.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v6_lrf.asn

!IF  "$(CFG)" == "map_v6_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v6_lrf.asn

".\map_v6_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v6 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v6_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v6_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v6_lrf.asn

".\map_v6_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v6 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v6_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
