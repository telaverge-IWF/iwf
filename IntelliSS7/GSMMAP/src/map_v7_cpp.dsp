# Microsoft Developer Studio Project File - Name="map_v7_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v7_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v7_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v7_cpp.mak" CFG="map_v7_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v7_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v7_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v7_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v7_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v7_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V7++.lib"

!ELSEIF  "$(CFG)" == "map_v7_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v7_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v7_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\MAP-V7++D.lib"

!ENDIF 

# Begin Target

# Name "map_v7_cpp - Win32 Release"
# Name "map_v7_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v7_absent_subscriber_diagnostic_sm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_absent_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_absent_subscriber_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_absent_subscriber_sm_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_access_network_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_access_network_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_activate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_additional_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_age_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_any_time_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_any_time_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_any_time_modification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_any_time_modification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_any_time_subscription_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_any_time_subscription_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_apn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_asci_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ati_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_atm_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_atsi_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_authentication_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_authentication_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_authentication_quintuplet.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_authentication_triplet.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_autn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_auts.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_basic_service_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_bearer_serv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_busy_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_barring_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_direction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_diversion_treatment_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_termination_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_call_type_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_camel_capability_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_camel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_camel_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cancel_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cancellation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cause_value.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_request_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ccbs_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cell_global_id_or_service_area_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cell_global_id_or_service_area_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ciphering_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ck.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cksn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_codec_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_context_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_context_id_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cs_allocation_retention_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_reject_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_current_security_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_d_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_data_missing_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_deactivate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_default_call_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_default_gprs_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_default_sms_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_destination_number_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_destination_number_length_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_destination_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_dp_analysed_info_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_dp_analysed_info_criterium.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_emlpp_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_emlpp_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_encryption_algorithm_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_encryption_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_encryption_key_version_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_erase_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_erase_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_error_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_event_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_call_bar_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_call_bar_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_call_barring_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_forw_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_forw_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_forw_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_forw_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_forwarding_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_no_rep_cond_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_ss_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_extensible_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_extensible_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_external_client.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_external_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_facility_not_sup_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forward_access_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forward_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_failed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_forwarding_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ftn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_generic_service_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_geodetic_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gmlc_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gmlc_restriction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_subscription_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_subscription_data_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gprs_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_group_key_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gsm_security_context_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_hash_algorithm_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_hash_key_version_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_horizontal_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ik.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_illegal_equipment_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_illegal_ss_operation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_illegal_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_imsi_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_incompatible_terminal_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_information_not_available_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_initialisation_vector.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_integrity_protection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_interrogation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ist_alert_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ist_alert_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ist_alert_timer_value.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ist_command_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ist_command_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ist_support_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_key_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ksi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_client_external_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_client_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_client_internal_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_client_name.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_client_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_event.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_privacy_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_privacy_exception_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lcs_qo_s.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_location_estimate_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_location_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_long_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_long_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_identity_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_information_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_lsa_only_access_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_m_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_protected_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_match_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_max_mc_bearers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mc_bearers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mc_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_message_wait_list_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mm_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mm_event_not_supported_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mo_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mo_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mobility_triggers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mode_of_operation.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_modification_instruction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_modification_request_for_cb_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_modification_request_for_cf_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_modification_request_for_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_molr_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_molr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_monitoring_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mt_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mt_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_multicall_bearer_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_naea_preferred_ci.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_name_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_network_access_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_no_group_call_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_no_roaming_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_no_subscriber_reply_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_note_mm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_note_mm_event_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_note_ms_present_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_note_ms_present_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_note_subscriber_data_modified_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_note_subscriber_data_modified_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_notification_to_ms_user.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_number_changed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_number_of_requested_vectors.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_number_portability_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_bcsm_camel_tdp_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_cause_value_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_o_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_odb_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_operation_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_or_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_or_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_original_component_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_password.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_pdp_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_pdp_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_pdp_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_plmn_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_plmn_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_position_method_failure_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_position_method_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_prepare_group_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_prepare_group_call_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_prepare_subsequent_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_process_access_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_process_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_protected_payload.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_protection_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_siwfs_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_siwfs_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_subscriber_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_subscriber_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_provide_subscriber_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_purge_ms_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_quintuplet_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_rab_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_radio_resource_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_re_synchronisation_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ready_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_register_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_register_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_relocation_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_relocation_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_remote_user_free_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_remote_user_free_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_report_sm_delivery_status_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_reporting_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_requested_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_requested_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_requested_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_resource_limitation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_response_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_response_time_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_resume_call_handling_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_rnc_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_roaming_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_routing_info_for_lcs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_routing_info_for_lcs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ruf_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_secure_transport_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_secure_transport_error_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_secure_transport_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_security_header.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_group_call_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_group_call_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_identification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_routing_info_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_routing_info_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_set_reporting_state_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_set_reporting_state_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sgsn_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sgsn_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_short_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_siwfs_signalling_modify_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_siwfs_signalling_modify_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_rp_mti.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sm_rp_smea.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sms_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sms_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sms_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sms_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_specific_csi_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_camel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_event_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_event_specification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_invocation_notification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_invocation_notification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_not_available_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ss_subscription_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_state_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_status_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_sub_busy_for_mt_sms_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_location_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_location_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_super_charger_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_supported_ccbs_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_bcsm_camel_tdp_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_cause_value_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_t_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_target_cell_outside_gca_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_teleserv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_tracing_buffer_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_triplet_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_umts_security_context_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unauthorized_lcs_client_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unauthorized_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unauthorized_requesting_network_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unexpected_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unidentified_sub_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unknown_or_unreachable_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unknown_subscriber_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_unknown_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_update_gprs_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_update_gprs_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_user_info_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_uu_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_uu_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_uui.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_vbs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_vertical_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_vgcs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_vlr_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_voice_broadcast_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_voice_group_call_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_wrong_password_attempts_counter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_xres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v7_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_v7_absent_subscriber_diagnostic_sm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_absent_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_absent_subscriber_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_absent_subscriber_sm_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_access_network_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_access_network_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_activate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_additional_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_age_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_any_time_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_any_time_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_any_time_modification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_any_time_modification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_any_time_subscription_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_any_time_subscription_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_apn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_asci_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ati_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_atm_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_atsi_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_authentication_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_authentication_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_authentication_quintuplet.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_authentication_triplet.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_autn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_auts.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_basic_service_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_bearer_serv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_busy_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_barring_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_direction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_diversion_treatment_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_termination_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_call_type_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_camel_capability_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_camel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_camel_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cancel_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cancellation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cause_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_request_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ccbs_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cell_global_id_or_service_area_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cell_global_id_or_service_area_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ciphering_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ck.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cksn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_codec_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_context_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_context_id_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cs_allocation_retention_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_reject_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_current_security_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_d_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_data_missing_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_deactivate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_default_call_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_default_gprs_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_default_sms_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_destination_number_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_destination_number_length_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_destination_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_dp_analysed_info_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_dp_analysed_info_criterium.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_emlpp_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_emlpp_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_encryption_algorithm_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_encryption_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_encryption_key_version_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_erase_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_erase_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_error_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_event_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_call_bar_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_call_bar_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_call_barring_info_for_cse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_forw_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_forw_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_forw_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_forw_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_forwarding_info_for_cse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_no_rep_cond_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_ss_info_for_cse.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_extended_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_extensible_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_extensible_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_external_client.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_external_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_facility_not_sup_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forward_access_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forward_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_failed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_forwarding_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ftn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_generic_service_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_geodetic_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gmlc_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gmlc_restriction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gmsc_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_subscription_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_subscription_data_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gprs_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_group_key_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gsm_security_context_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_gsn_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_hash_algorithm_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_hash_key_version_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_horizontal_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ik.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_illegal_equipment_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_illegal_ss_operation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_illegal_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_incompatible_terminal_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_information_not_available_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_initialisation_vector.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_integrity_protection_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_interrogation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ist_alert_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ist_alert_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ist_alert_timer_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ist_command_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ist_command_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ist_support_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_key_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ksi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_client_external_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_client_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_client_internal_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_client_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_client_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_location_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_privacy_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_privacy_exception_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lcs_qo_s.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_location_estimate_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_location_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_long_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_long_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_attributes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_identity_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_information_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_lsa_only_access_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_m_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_protected_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_match_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_max_mc_bearers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mc_bearers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mc_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_message_wait_list_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mm_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mm_event_not_supported_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mo_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mo_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mobility_triggers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mode_of_operation.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_modification_instruction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_modification_request_for_cb_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_modification_request_for_cf_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_modification_request_for_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_molr_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_molr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_monitoring_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mt_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mt_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_multicall_bearer_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_naea_preferred_ci.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_name_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_network_access_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_no_group_call_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_no_roaming_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_no_subscriber_reply_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_note_mm_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_note_mm_event_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_note_ms_present_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_note_ms_present_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_note_subscriber_data_modified_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_note_subscriber_data_modified_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_notification_to_ms_user.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_number_changed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_number_of_requested_vectors.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_number_portability_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_bcsm_camel_tdp_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_cause_value_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_o_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_odb_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_operation_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_or_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_or_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_original_component_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_pdp_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_pdp_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_pdp_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_plmn_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_plmn_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_position_method_failure_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_position_method_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_prepare_group_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_prepare_group_call_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_prepare_subsequent_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_process_access_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_process_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_protected_payload.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_protection_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_siwfs_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_siwfs_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_subscriber_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_subscriber_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_subscriber_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_provide_subscriber_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_purge_ms_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_quintuplet_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_rab_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_radio_resource_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_re_synchronisation_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ready_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_register_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_register_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_relocation_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_relocation_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_remote_user_free_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_remote_user_free_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_report_sm_delivery_status_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_reporting_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_requested_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_requested_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_requested_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_resource_limitation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_response_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_response_time_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_resume_call_handling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_resume_call_handling_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_rnc_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_roaming_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_routing_info_for_lcs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_routing_info_for_lcs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ruf_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_secure_transport_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_secure_transport_error_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_secure_transport_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_security_header.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_group_call_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_group_call_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_identification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_routing_info_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_routing_info_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_set_reporting_state_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_set_reporting_state_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sgsn_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sgsn_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_short_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_siwfs_signalling_modify_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_siwfs_signalling_modify_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_rp_mti.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sm_rp_smea.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sms_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sms_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sms_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sms_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_specific_csi_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_camel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_event_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_event_specification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_invocation_notification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_invocation_notification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_not_available_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ss_subscription_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_state_attributes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_status_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_sub_busy_for_mt_sms_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_location_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_location_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_super_charger_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_supported_ccbs_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_bcsm_camel_tdp_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_cause_value_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_t_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_target_cell_outside_gca_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_teleserv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_tracing_buffer_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_triplet_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_umts_security_context_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unauthorized_lcs_client_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unauthorized_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unauthorized_requesting_network_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unexpected_data_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unidentified_sub_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unknown_or_unreachable_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unknown_subscriber_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_unknown_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_update_gprs_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_update_gprs_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_user_info_helper.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_uu_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_uu_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_uui.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_vbs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_vertical_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_vgcs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_vlr_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_vlr_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_voice_broadcast_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_voice_group_call_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_wrong_password_attempts_counter.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_xres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v7_zone_code_list.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v7_lrf.asn

!IF  "$(CFG)" == "map_v7_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v7_lrf.asn

".\map_v7_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v7 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v7_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v7_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v7_lrf.asn

".\map_v7_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v7 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v7_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
