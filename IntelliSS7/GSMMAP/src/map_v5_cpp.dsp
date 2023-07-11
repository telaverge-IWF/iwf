# Microsoft Developer Studio Project File - Name="map_v5_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v5_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v5_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v5_cpp.mak" CFG="map_v5_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v5_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v5_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v5_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v5_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v5_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V5++.lib"

!ELSEIF  "$(CFG)" == "map_v5_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v5_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v5_cpp_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V5++D.lib"

!ENDIF 

# Begin Target

# Name "map_v5_cpp - Win32 Release"
# Name "map_v5_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v5_absent_subscriber_diagnostic_sm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_absent_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_absent_subscriber_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_absent_subscriber_sm_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_activate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_additional_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_any_time_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_any_time_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_apn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_asci_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ati_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_authentication_set.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_basic_service_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_bearer_serv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_busy_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_direction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_call_type_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_camel_capability_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_camel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_camel_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cancel_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cancellation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ccbs_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ccbs_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ccbs_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ccbs_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ccbs_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ccbs_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cell_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cell_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ciphering_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_codec_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_context_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_context_id_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_reject_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_data_missing_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_deactivate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_default_call_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_destination_number_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_destination_number_length_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_destination_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_emlpp_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_emlpp_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_erase_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_erase_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_event_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_call_bar_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_call_bar_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_forw_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_forw_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_forw_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_forw_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_no_rep_cond_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_extensible_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_extensible_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_external_client.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_external_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_facility_not_sup_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forward_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_failed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_forwarding_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_generic_service_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gmlc_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gmlc_restriction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gprs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gprs_subscription_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gprs_subscription_data_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_group_key_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_horizontal_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_illegal_equipment_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_illegal_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_imsi_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_incompatible_terminal_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_interrogation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_client_external_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_client_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_client_internal_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_client_name.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_client_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_event.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_privacy_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_privacy_exception_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lcs_qo_s.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_location_estimate_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_location_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_long_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_identity_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_information_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_lsa_only_access_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_match_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_message_wait_list_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_mo_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_mo_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_molr_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_molr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_monitoring_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_mt_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_mt_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_naea_preferred_ci.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_name_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_network_access_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_no_group_call_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_no_roaming_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_no_subscriber_reply_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_note_ms_present_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_note_ms_present_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_notification_to_ms_user.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_number_changed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_number_portability_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_o_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_o_bcsm_camel_tdp_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_o_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_o_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_o_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_o_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_or_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_or_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_password.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_pdp_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_pdp_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_pdp_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_plmn_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_position_method_failure_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_position_method_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_prepare_group_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_prepare_group_call_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_process_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_siwfs_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_siwfs_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_subscriber_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_subscriber_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_provide_subscriber_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_purge_ms_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ready_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_register_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_register_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_remote_user_free_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_remote_user_free_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_report_sm_delivery_status_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_reporting_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_requested_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_resource_limitation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_response_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_response_time_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_resume_call_handling_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_roaming_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_routing_info_for_lcs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_routing_info_for_lcs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ruf_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_group_call_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_group_call_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_routing_info_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_routing_info_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_set_reporting_state_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_set_reporting_state_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sgsn_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_short_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_siwfs_signalling_modify_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_siwfs_signalling_modify_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_rp_mti.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sm_rp_smea.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_camel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_event_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_event_specification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_invocation_notification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_invocation_notification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_status_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_sub_busy_for_mt_sms_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_location_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_location_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_supported_ccbs_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_t_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_t_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_t_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_t_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_teleserv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_tracing_buffer_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unauthorized_lcs_client_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unauthorized_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unauthorized_requesting_network_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unexpected_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unidentified_sub_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unknown_or_unreachable_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unknown_subscriber_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_unknown_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_update_gprs_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_update_gprs_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_uu_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_uu_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_uui.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_vbs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_vertical_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_vgcs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_vlr_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_voice_broadcast_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_voice_group_call_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_cpp.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_absent_subscriber_diagnostic_sm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_absent_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_absent_subscriber_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_absent_subscriber_sm_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_activate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_additional_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_any_time_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_any_time_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_apn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_asci_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ati_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_authentication_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_basic_service_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_bearer_serv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_busy_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_direction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_call_type_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_camel_capability_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_camel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_camel_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cancel_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cancellation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ccbs_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ccbs_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ccbs_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ccbs_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ccbs_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ccbs_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cell_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cell_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ciphering_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_codec_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_context_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_context_id_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_reject_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_data_missing_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_deactivate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_default_call_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_destination_number_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_destination_number_length_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_destination_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_emlpp_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_emlpp_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_erase_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_erase_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_event_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_call_bar_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_call_bar_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_forw_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_forw_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_forw_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_forw_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_no_rep_cond_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_extended_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_extensible_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_extensible_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_external_client.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_external_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_facility_not_sup_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forward_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_failed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_forwarding_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_generic_service_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gmlc_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gmlc_restriction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gmsc_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gprs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gprs_subscription_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gprs_subscription_data_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_group_key_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_gsn_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_horizontal_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_illegal_equipment_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_illegal_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_incompatible_terminal_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_interrogation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_client_external_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_client_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_client_internal_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_client_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_client_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_location_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_privacy_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_privacy_exception_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lcs_qo_s.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_location_estimate_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_location_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_long_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_attributes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_identity_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_information_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_lsa_only_access_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_match_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_message_wait_list_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_mo_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_mo_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_molr_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_molr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_monitoring_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_mt_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_mt_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_naea_preferred_ci.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_name_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_network_access_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_no_group_call_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_no_roaming_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_no_subscriber_reply_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_note_ms_present_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_note_ms_present_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_notification_to_ms_user.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_number_changed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_number_portability_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_o_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_o_bcsm_camel_tdp_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_o_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_o_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_o_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_o_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_or_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_or_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_pdp_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_pdp_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_pdp_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_plmn_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_position_method_failure_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_position_method_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_prepare_group_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_prepare_group_call_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_process_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_siwfs_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_siwfs_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_subscriber_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_subscriber_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_subscriber_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_provide_subscriber_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_purge_ms_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ready_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_register_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_register_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_remote_user_free_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_remote_user_free_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_report_sm_delivery_status_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_reporting_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_requested_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_resource_limitation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_response_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_response_time_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_resume_call_handling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_resume_call_handling_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_roaming_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_routing_info_for_lcs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_routing_info_for_lcs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ruf_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_group_call_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_group_call_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_routing_info_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_routing_info_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_set_reporting_state_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_set_reporting_state_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sgsn_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_short_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_siwfs_signalling_modify_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_siwfs_signalling_modify_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_rp_mti.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sm_rp_smea.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_camel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_event_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_event_specification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_invocation_notification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_invocation_notification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_status_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_sub_busy_for_mt_sms_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_location_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_location_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_supported_ccbs_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_t_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_t_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_t_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_t_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_teleserv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_tracing_buffer_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unauthorized_lcs_client_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unauthorized_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unauthorized_requesting_network_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unexpected_data_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unidentified_sub_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unknown_or_unreachable_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unknown_subscriber_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_unknown_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_update_gprs_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_update_gprs_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_uu_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_uu_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_uui.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_vbs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_vertical_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_vgcs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_vlr_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_vlr_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_voice_broadcast_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_voice_group_call_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v5_zone_code_list.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v5_lrf.asn

!IF  "$(CFG)" == "map_v5_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v5_lrf.asn

".\map_v5_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v5 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v5_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v5_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v5_lrf.asn

".\map_v5_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp  -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v5_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
