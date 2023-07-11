# Microsoft Developer Studio Project File - Name="map_v4_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v4_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v4_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v4_c.mak" CFG="map_v4_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v4_c - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v4_c - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v4_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v4_c_Win32_Release"
# PROP Intermediate_Dir "map_v4_c_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V4.lib"

!ELSEIF  "$(CFG)" == "map_v4_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v4_c_Win32_Debug"
# PROP Intermediate_Dir "map_v4_c_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-c" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\MAP-V4D.lib"

!ENDIF 

# Begin Target

# Name "map_v4_c - Win32 Release"
# Name "map_v4_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_diagnostic_sm_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_sm_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_activate_trace_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_activate_trace_mode_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_additional_number_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_age_of_location_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_alert_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_alert_service_centre_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_alerting_pattern_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_any_time_interrogation_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_any_time_interrogation_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_apn_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_asci_call_reference_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ati_not_allowed_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_authentication_set_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_authentication_set_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_group_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_serv_not_prov_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_busy_subscriber_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barred_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_direction_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_outcome_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_reference_number_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_report_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_type_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_camel_capability_handling_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_camel_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_camel_routing_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancel_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancel_location_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancellation_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_index_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_indicators_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_subscriber_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cell_id_fixed_length_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cell_id_or_lai_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ciphering_algorithm_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cli_restriction_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_codec_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_context_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_context_id_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_check_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_index_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_interlock_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_reject_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_reject_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_data_missing_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_deactivate_trace_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_deactivate_trace_mode_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_default_call_handling_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_delete_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_delete_subscriber_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_destination_number_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_destination_number_length_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_destination_number_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_emlpp_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_emlpp_priority_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_equipment_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_erase_cc_entry_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_erase_cc_entry_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_event_report_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_basic_service_group_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_call_bar_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_call_bar_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_call_barring_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_no_rep_cond_time_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_info_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_extended_routing_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_extensible_call_barred_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_extensible_system_failure_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_extension_container_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_external_signal_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_facility_not_sup_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_failure_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_failure_report_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forward_group_call_signalling_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_failed_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_violation_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_generic_service_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_geographical_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_global_cell_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_gmsc_camel_subscription_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_data_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_subscription_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_subscription_data_withdraw_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_group_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_group_key_number_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_gsn_address_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_guidance_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_hlr_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_hlr_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_identity_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_illegal_equipment_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_illegal_subscriber_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_imei_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi_with_lmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_incompatible_terminal_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_inform_service_centre_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_inter_cug_restrictions_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_interrogate_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_interrogation_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_intra_cug_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_subaddress_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_kc_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_lai_fixed_length_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_lmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_location_info_with_lmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_location_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_location_number_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_long_term_denial_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_accept_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_close_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_dialogue_pdu_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_open_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_provider_abort_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_provider_abort_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_refuse_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_user_abort_choice_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_user_abort_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_user_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_match_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_message_wait_list_full_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_mo_forward_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_mo_forward_sm_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_monitoring_mode_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_mt_forward_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_mt_forward_sm_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_mw_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_naea_cic_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_naea_preferred_ci_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_network_access_mode_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_network_resource_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_group_call_nb_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_reply_condition_time_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_roaming_nb_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_subscriber_reply_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_not_reachable_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_note_ms_present_for_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_note_ms_present_for_gprs_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_number_changed_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_number_of_forwarding_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_camel_tdp_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_camel_tdp_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_camel_tdp_data_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_trigger_detection_point_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_csi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_general_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_hplmn_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_or_not_allowed_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_or_phase_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_override_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_password_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_pcs_extensions_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_address_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_context_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_group_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_group_call_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_ho_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_subsequent_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_private_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_private_extension_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_procedure_cancellation_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_process_group_call_signalling_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_protocol_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_roaming_number_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_roaming_number_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_siwfs_number_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_siwfs_number_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_subscriber_info_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_subscriber_info_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_purge_ms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_purge_ms_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_pw_registration_failure_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_qo_s_subscribed_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_rand_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ready_for_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ready_for_sm_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_regional_subscription_response_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_register_cc_entry_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_register_cc_entry_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_register_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_remote_user_free_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_remote_user_free_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_report_sm_delivery_status_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_report_sm_delivery_status_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_reporting_state_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_requested_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_reset_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_resource_limitation_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_resource_unavailable_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_restore_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_restore_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_resume_call_handling_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_resume_call_handling_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_roaming_not_allowed_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_roaming_not_allowed_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_routing_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_routing_info_for_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_routing_info_for_sm_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ruf_outcome_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_authentication_info_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_authentication_info_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_group_call_end_signal_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_group_call_end_signal_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_identification_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_for_gprs_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_for_gprs_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_service_indicator_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_service_key_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_set_reporting_state_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_set_reporting_state_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_short_term_denial_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_signal_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_siwfs_signalling_modify_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_siwfs_signalling_modify_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_delivery_failure_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_delivery_outcome_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_enumerated_delivery_failure_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_da_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_mti_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_oa_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_smea_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sres_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_camel_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_csi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_event_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_event_specification_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_for_bs_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_incompatibility_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_invocation_notification_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_invocation_notification_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_subscription_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_status_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_status_report_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_sub_busy_for_mt_sms_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_identity_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_state_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_supported_camel_phases_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_supported_ccbs_phase_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_suppression_of_announcement_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_system_failure_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_bcsm_camel_tdp_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_bcsm_camel_tdp_data_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_bcsm_trigger_detection_point_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_csi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_tbcd_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleserv_not_prov_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_tmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_trace_reference_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_trace_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_tracing_buffer_full_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_unexpected_data_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_unidentified_sub_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_unknown_subscriber_diagnostic_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_unknown_subscriber_param_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_gprs_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_gprs_location_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_location_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_data_coding_scheme_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_vbs_data_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_vgcs_data_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_vlr_camel_subscription_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_vlr_capability_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_voice_broadcast_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_voice_group_call_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_list_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_diagnostic_sm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_sm_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_activate_trace_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_activate_trace_mode_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_additional_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_age_of_location_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_alert_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_alert_service_centre_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_alerting_pattern_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_any_time_interrogation_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_any_time_interrogation_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_apn_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_asci_call_reference_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ati_not_allowed_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_authentication_set_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_authentication_set_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_group_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_bearer_serv_not_prov_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_bearer_service_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_busy_subscriber_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barred_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_direction_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_outcome_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_reference_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_report_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_type_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_camel_capability_handling_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_camel_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_camel_routing_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cancel_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cancel_location_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cancellation_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_index_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_indicators_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_subscriber_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cell_id_fixed_length_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cell_id_or_lai_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ciphering_algorithm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cli_restriction_option_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_codec_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_context_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_context_id_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_check_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_index_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_interlock_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_reject_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_reject_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_subscription_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_subscription_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_data_missing_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_deactivate_trace_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_deactivate_trace_mode_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_default_call_handling_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_delete_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_delete_subscriber_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_destination_number_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_destination_number_length_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_destination_number_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_emlpp_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_emlpp_priority_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_equipment_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_erase_cc_entry_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_erase_cc_entry_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_event_report_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_basic_service_group_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_call_bar_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_call_bar_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_call_barring_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_no_rep_cond_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_info_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extended_routing_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extensible_call_barred_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extensible_system_failure_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extension_container_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_external_signal_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_facility_not_sup_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_failure_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_failure_report_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forward_group_call_signalling_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_failed_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_violation_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_generic_service_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_geographical_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_global_cell_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gmsc_camel_subscription_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gprs_data_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gprs_subscription_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gprs_subscription_data_withdraw_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_group_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_group_key_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gsn_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_guidance_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_hlr_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_hlr_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_identity_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_illegal_equipment_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_illegal_subscriber_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_imei_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_imsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_imsi_with_lmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_incompatible_terminal_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_inform_service_centre_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_insert_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_insert_subscriber_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_inter_cug_restrictions_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_interrogate_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_interrogation_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_intra_cug_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_isdn_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_isdn_subaddress_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_kc_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_lai_fixed_length_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_lmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_location_info_with_lmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_location_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_location_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_long_term_denial_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_accept_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_close_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_dialogue_pdu_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_open_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_provider_abort_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_provider_abort_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_refuse_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_user_abort_choice_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_user_abort_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_user_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_match_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_message_wait_list_full_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mo_forward_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mo_forward_sm_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_monitoring_mode_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mt_forward_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mt_forward_sm_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mw_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_naea_cic_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_naea_preferred_ci_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_network_access_mode_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_network_resource_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_group_call_nb_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_reply_condition_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_roaming_nb_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_subscriber_reply_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_not_reachable_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_note_ms_present_for_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_note_ms_present_for_gprs_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_number_changed_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_number_of_forwarding_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_camel_tdp_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_camel_tdp_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_camel_tdp_data_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_trigger_detection_point_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_csi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_odb_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_odb_general_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_odb_hplmn_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_or_not_allowed_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_or_phase_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_override_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_password_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pcs_extensions_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pdp_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pdp_context_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pdp_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_group_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_group_call_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_ho_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_subsequent_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_private_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_private_extension_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_procedure_cancellation_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_process_group_call_signalling_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_protocol_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_roaming_number_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_roaming_number_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_siwfs_number_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_siwfs_number_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_subscriber_info_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_subscriber_info_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_purge_ms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_purge_ms_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pw_registration_failure_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_qo_s_subscribed_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_rand_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ready_for_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ready_for_sm_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_regional_subscription_response_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_register_cc_entry_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_register_cc_entry_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_register_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_remote_user_free_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_remote_user_free_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_report_sm_delivery_status_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_report_sm_delivery_status_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_reporting_state_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_requested_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_reset_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resource_limitation_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resource_unavailable_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_restore_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_restore_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resume_call_handling_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resume_call_handling_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_roaming_not_allowed_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_roaming_not_allowed_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_routing_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_routing_info_for_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_routing_info_for_sm_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ruf_outcome_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_authentication_info_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_authentication_info_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_group_call_end_signal_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_group_call_end_signal_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_identification_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_for_gprs_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_for_gprs_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_service_indicator_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_service_key_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_set_reporting_state_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_set_reporting_state_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_short_term_denial_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_signal_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_siwfs_signalling_modify_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_siwfs_signalling_modify_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_delivery_failure_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_delivery_outcome_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_enumerated_delivery_failure_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_da_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_mti_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_oa_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_smea_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sres_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_camel_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_csi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_event_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_event_specification_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_for_bs_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_incompatibility_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_info_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_invocation_notification_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_invocation_notification_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_subscription_option_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_status_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_status_report_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sub_busy_for_mt_sms_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_identity_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_state_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_supported_camel_phases_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_supported_ccbs_phase_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_suppression_of_announcement_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_system_failure_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_bcsm_camel_tdp_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_bcsm_camel_tdp_data_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_bcsm_trigger_detection_point_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_csi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_tbcd_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_teleserv_not_prov_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_teleservice_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_tmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_trace_reference_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_trace_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_tracing_buffer_full_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unexpected_data_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unidentified_sub_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unknown_subscriber_diagnostic_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unknown_subscriber_param_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_gprs_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_gprs_location_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_location_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_data_coding_scheme_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vbs_data_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vgcs_data_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vlr_camel_subscription_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vlr_capability_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_voice_broadcast_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_voice_group_call_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_zone_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_zone_code_list_c.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v4_lrf.asn

!IF  "$(CFG)" == "map_v4_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v4_lrf.asn

".\map_v4_absent_subscriber_diagnostic_sm_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v4_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v4_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v4_lrf.asn

".\map_v4_absent_subscriber_diagnostic_sm_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v4_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
