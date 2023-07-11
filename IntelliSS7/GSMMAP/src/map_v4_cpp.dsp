# Microsoft Developer Studio Project File - Name="map_v4_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v4_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v4_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v4_cpp.mak" CFG="map_v4_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v4_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v4_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v4_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v4_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v4_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V4++.lib"

!ELSEIF  "$(CFG)" == "map_v4_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v4_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v4_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# SUBTRACT CPP /Z<none>
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\MAP-V4++D.lib"

!ENDIF 

# Begin Target

# Name "map_v4_cpp - Win32 Release"
# Name "map_v4_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_diagnostic_sm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_absent_subscriber_sm_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_activate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_additional_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_any_time_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_any_time_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_apn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_asci_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ati_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_authentication_set.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_serv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_busy_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_direction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_call_type_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_camel_capability_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_camel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_camel_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancel_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancellation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ccbs_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cell_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cell_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ciphering_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_codec_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_context_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_context_id_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_reject_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_data_missing_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_deactivate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_default_call_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_destination_number_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_destination_number_length_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_destination_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_emlpp_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_emlpp_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_erase_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_erase_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_event_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_call_bar_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_call_bar_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_forw_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_no_rep_cond_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_extensible_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_extensible_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_facility_not_sup_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forward_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_failed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_forwarding_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_generic_service_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_subscription_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_subscription_data_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_group_key_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_illegal_equipment_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_illegal_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_imsi_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_incompatible_terminal_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_interrogation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_long_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_match_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_message_wait_list_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_mo_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_mo_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_monitoring_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_mt_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_mt_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_naea_preferred_ci.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_network_access_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_group_call_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_roaming_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_no_subscriber_reply_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_note_ms_present_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_note_ms_present_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_number_changed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_o_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_or_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_or_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_password.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_group_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_group_call_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_process_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_siwfs_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_siwfs_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_subscriber_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_purge_ms_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ready_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_register_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_register_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_remote_user_free_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_remote_user_free_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_report_sm_delivery_status_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_reporting_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_requested_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_resource_limitation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_resume_call_handling_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_roaming_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ruf_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_group_call_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_group_call_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_set_reporting_state_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_set_reporting_state_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_short_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_siwfs_signalling_modify_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_siwfs_signalling_modify_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_mti.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sm_rp_smea.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_camel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_event_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_event_specification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_invocation_notification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_invocation_notification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_status_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_sub_busy_for_mt_sms_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_supported_ccbs_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_t_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleserv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_tracing_buffer_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_unexpected_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_unidentified_sub_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_unknown_subscriber_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_unknown_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_gprs_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_gprs_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_user_info_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_vbs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_vgcs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_vlr_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_voice_broadcast_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_voice_group_call_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_diagnostic_sm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_absent_subscriber_sm_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_activate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_additional_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_any_time_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_any_time_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_apn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_asci_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ati_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_authentication_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_bearer_serv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_busy_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_direction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_call_type_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_camel_capability_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_camel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_camel_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cancel_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cancellation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ccbs_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cell_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cell_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ciphering_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_codec_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_context_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_context_id_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_reject_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_data_missing_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_deactivate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_default_call_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_destination_number_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_destination_number_length_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_destination_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_emlpp_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_emlpp_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_erase_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_erase_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_event_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_call_bar_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_call_bar_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_forw_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_no_rep_cond_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extended_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extensible_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extensible_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_facility_not_sup_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forward_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_failed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_forwarding_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_generic_service_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gmsc_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gprs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gprs_subscription_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gprs_subscription_data_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_group_key_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_gsn_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_illegal_equipment_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_illegal_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_incompatible_terminal_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_interrogation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_long_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_match_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_message_wait_list_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mo_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mo_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_monitoring_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mt_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mt_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_naea_preferred_ci.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_network_access_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_group_call_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_roaming_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_no_subscriber_reply_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_note_ms_present_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_note_ms_present_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_number_changed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_o_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_or_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_or_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pdp_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pdp_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pdp_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_group_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_group_call_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_process_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_siwfs_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_siwfs_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_subscriber_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_provide_subscriber_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_purge_ms_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ready_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_register_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_register_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_remote_user_free_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_remote_user_free_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_report_sm_delivery_status_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_reporting_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_requested_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resource_limitation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resume_call_handling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_resume_call_handling_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_roaming_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ruf_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_group_call_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_group_call_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_set_reporting_state_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_set_reporting_state_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_short_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_siwfs_signalling_modify_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_siwfs_signalling_modify_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_mti.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sm_rp_smea.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_camel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_event_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_event_specification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_invocation_notification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_invocation_notification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_status_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_sub_busy_for_mt_sms_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_supported_ccbs_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_t_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_teleserv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_tracing_buffer_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unexpected_data_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unidentified_sub_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unknown_subscriber_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_unknown_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_gprs_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_gprs_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_user_info_helper.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vbs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vgcs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vlr_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_vlr_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_voice_broadcast_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_voice_group_call_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v4_zone_code_list.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v4_lrf.asn

!IF  "$(CFG)" == "map_v4_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v4_lrf.asn

".\map_v4_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace map_v4 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v4_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v4_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v4_lrf.asn

".\map_v4_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v4 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v4_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
