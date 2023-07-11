# Microsoft Developer Studio Project File - Name="map_v6_to_v1_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v6_to_v1_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v6_to_v1_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v6_to_v1_cpp.mak" CFG="map_v6_to_v1_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v6_to_v1_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v6_to_v1_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v6_to_v1_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v6_to_v1_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v6_to_v1_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V6-TO-V1++.lib"

!ELSEIF  "$(CFG)" == "map_v6_to_v1_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "map_v6_to_v1_cpp___Win32_Debug"
# PROP BASE Intermediate_Dir "map_v6_to_v1_cpp___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v6_to_v1_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v6_to_v1_cpp_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V6-TO-V1++D.lib"

!ENDIF 

# Begin Target

# Name "map_v6_to_v1_cpp - Win32 Release"
# Name "map_v6_to_v1_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_common_absent_subscriber_diagnostic_sm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_absent_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_absent_subscriber_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_absent_subscriber_sm_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_activate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_additional_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_age_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_any_time_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_any_time_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_apn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_asci_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ati_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_authentication_set.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_basic_service_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_bearer_serv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_begin_subscriber_activity_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_busy_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_direction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_call_type_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_camel_capability_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_camel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_camel_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cancel_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cancellation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_request_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ccbs_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cell_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cell_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_channel_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ciphering_algorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cli_restriction_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_codec_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_context_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_context_id_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_reject_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_data_missing_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_deactivate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_default_call_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_default_gprs_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_default_sms_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_destination_number_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_destination_number_length_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_destination_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_emlpp_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_emlpp_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_erase_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_erase_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_event_report_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_call_bar_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_call_bar_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_forw_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_forw_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_forw_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_forw_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_no_rep_cond_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_extensible_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_extensible_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_external_client.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_external_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_facility_not_sup_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forward_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_failed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_forwarding_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ftn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_generic_service_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gmlc_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gmlc_restriction.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_subscription_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_subscription_data_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gprs_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_group_key_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_handover_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_handover_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_horizontal_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_illegal_equipment_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_illegal_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_imsi_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_incompatible_terminal_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_interrogation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ist_support_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ki.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_client_external_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_client_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_client_internal_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_client_name.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_client_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_event.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_privacy_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_privacy_exception_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lcs_qo_s.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_location_estimate_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_location_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_long_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_identity_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_information_withdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_lsa_only_access_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_match_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_max_mc_bearers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_mc_bearers.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_message_wait_list_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_mo_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_mo_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_molr_class.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_molr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_monitoring_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_mt_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_mt_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_naea_preferred_ci.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_name_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_network_access_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_no_group_call_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_no_roaming_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_no_subscriber_reply_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_note_ms_present_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_note_ms_present_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_notification_to_ms_user.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_number_changed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_number_portability_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_o_bcsm_camel_tdp_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_o_bcsm_camel_tdp_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_o_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_o_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_o_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_o_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_or_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_or_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_password.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_pdp_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_pdp_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_pdp_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_plmn_client_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_prepare_group_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_prepare_group_call_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_process_group_call_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_siwfs_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_siwfs_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_subscriber_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_subscriber_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_provide_subscriber_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_purge_ms_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_qo_s_subscribed.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ready_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_register_cc_entry_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_register_cc_entry_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_remote_user_free_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_remote_user_free_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_report_sm_delivery_status_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_reporting_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_requested_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_resource_limitation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_response_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_response_time_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_resume_call_handling_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_roaming_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_routing_info_for_lcs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_routing_info_for_lcs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ruf_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_group_call_end_signal_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_group_call_end_signal_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_routing_info_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_routing_info_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_set_reporting_state_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_set_reporting_state_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sgsn_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sgsn_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_short_term_denial_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_siwfs_signalling_modify_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_siwfs_signalling_modify_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_rp_mti.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sm_rp_smea.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sms_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sms_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sms_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sms_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_camel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_event_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_event_specification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_invocation_notification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_invocation_notification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ss_user_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_status_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_sub_busy_for_mt_sms_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_location_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_location_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_super_charger_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_supported_ccbs_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_t_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_t_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_t_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_t_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_teleserv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_tracing_buffer_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unauthorized_lcs_client_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unauthorized_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unauthorized_requesting_network_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unexpected_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unidentified_sub_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unknown_or_unreachable_lcs_client_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unknown_subscriber_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_unknown_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_update_gprs_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_update_gprs_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_user_info_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_uu_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_uu_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_uui.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_vbs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_vertical_accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_vgcs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_vlr_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_voice_broadcast_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_voice_group_call_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_common_zone_code_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_absent_subscriber_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_access_connection_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_activate_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_activate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_alert_service_center_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_attach_imsi_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_authenticate_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_authenticate_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_authentication_set.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barred_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_date_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_duration.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_charge.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_charging_unit.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_check_imei_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_check_imei_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ciphering_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cksn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_classmark_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cm_service_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_complete_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_connect_to_following_address_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_facilities.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_reject_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_deactivate_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_deactivate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_deregister_mobile_subscriber_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_detach_imsi_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_equip_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_erase_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_erase_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_access_signaling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_new_tmsi_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_short_message_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_ss_notification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_get_password_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_get_password_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_hunt_group_access_selection_order.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_impossible_call_completion_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_interrogate_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_invoke_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_invoke_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_l_ms_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_loc_area_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_map_abort_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_maximum_conferees_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_note_internal_handover.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_note_ms_present_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_number_of_conferees.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_packet_data_volume.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_page_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_password_registration_failure_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_handover_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_handover_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_subsequent_handover_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_subsequent_handover_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_access_request_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_access_request_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_access_signaling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_unstructured_ss_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_unstructured_ss_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_provide_imsi_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_password_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_password_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_request_parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_request_parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_search_for_mobile_subscriber_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_search_for_mobile_subscriber_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_handover_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_info_for_incoming_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_info_for_outgoing_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_parameters_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_parameters_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_information_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sent_parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sent_parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_set_ciphering_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_set_message_waiting_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_delivery_failure_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_rp_ui.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_charging_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_charging_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_code_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_error_status_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_incompatibility_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_notification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_request.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_subscription_violation_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_system_failure_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_trace_subscriber_activity_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_update_location_area_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_user_to_user_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_classmark_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_extensible_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_note_internal_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_perform_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_perform_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_perform_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_request_parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_request_parameter_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_parameters_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sent_parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sent_parameter_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_failure_cause_with_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_subscriber_activity_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_apn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_failure_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_failure_report_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gprs_subscription_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_gsn_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_note_ms_present_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_address.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_pdp_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_for_gprs_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_send_routing_info_for_gprs_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v4_update_gprs_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_position_method_failure_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_position_method_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v5_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_access_network_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_access_network_signal_info.cpp
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

SOURCE=.\map_v6_call_barring_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_diversion_treatment_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_call_termination_indicator.cpp
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

SOURCE=.\map_v6_cause_value.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cell_global_id_or_service_area_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cell_global_id_or_service_area_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ck.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cksn.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_cs_allocation_retention_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_current_security_context.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_d_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_dp_analysed_info_criteria_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_dp_analysed_info_criterium.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_encryption_protection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_call_barring_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_forwarding_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ext_ss_info_for_cse.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_forward_access_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_geodetic_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_gsm_security_context_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ik.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_illegal_ss_operation_param.cpp
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

SOURCE=.\map_v6_ksi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_m_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mc_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mm_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_mm_event_not_supported_param.cpp
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

SOURCE=.\map_v6_multicall_bearer_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_mm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_mm_event_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_subscriber_data_modified_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_note_subscriber_data_modified_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_number_of_requested_vectors.cpp
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

SOURCE=.\map_v6_odb_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_position_method_failure_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_position_method_failure_param.cpp
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

SOURCE=.\map_v6_process_access_signalling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_quintuplet_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_rab_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_radio_resource_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_re_synchronisation_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_relocation_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_relocation_number_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_requested_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_requested_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_rnc_id.cpp
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

SOURCE=.\map_v6_send_identification_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_not_available_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_ss_subscription_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_subscriber_info.cpp
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

SOURCE=.\map_v6_triplet_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_type_of_modification.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_umts_security_context_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_wrong_password_attempts_counter.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v6_xres.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_common_absent_subscriber_diagnostic_sm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_absent_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_absent_subscriber_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_absent_subscriber_sm_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_activate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_additional_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_age_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_any_time_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_any_time_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_apn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_asci_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ati_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_authentication_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_basic_service_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_bearer_serv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_begin_subscriber_activity_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_busy_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_direction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_call_type_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_camel_capability_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_camel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_camel_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cancel_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cancellation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_request_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ccbs_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cell_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cell_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_channel_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ciphering_algorithm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cli_restriction_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_codec_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_context_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_context_id_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_reject_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_data_missing_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_deactivate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_default_call_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_default_gprs_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_default_sms_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_destination_number_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_destination_number_length_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_destination_number_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_emlpp_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_emlpp_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_erase_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_erase_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_event_report_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_call_bar_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_call_bar_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_forw_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_forw_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_forw_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_forw_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_no_rep_cond_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_extended_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_extensible_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_extensible_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_external_client.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_external_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_facility_not_sup_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_failure_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_failure_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forward_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_failed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_forwarding_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ftn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_generic_service_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gmlc_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gmlc_restriction.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gmsc_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_subscription_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_subscription_data_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gprs_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_group_key_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_gsn_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_handover_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_handover_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_horizontal_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_illegal_equipment_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_illegal_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_incompatible_terminal_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_interrogation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ist_support_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ki.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_client_external_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_client_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_client_internal_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_client_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_client_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_location_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_privacy_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_privacy_exception_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lcs_qo_s.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_location_estimate_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_location_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_long_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_attributes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_identity_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_information_withdraw.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_lsa_only_access_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_match_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_max_mc_bearers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_mc_bearers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_message_wait_list_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_mo_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_mo_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_molr_class.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_molr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_monitoring_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_mt_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_mt_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_naea_preferred_ci.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_name_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_network_access_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_no_group_call_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_no_roaming_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_no_subscriber_reply_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_note_ms_present_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_note_ms_present_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_notification_to_ms_user.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_number_changed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_number_portability_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_o_bcsm_camel_tdp_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_o_bcsm_camel_tdp_criteria_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_o_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_o_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_o_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_o_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_or_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_or_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_pdp_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_pdp_context.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_pdp_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_plmn_client_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_prepare_group_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_prepare_group_call_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_process_group_call_signalling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_siwfs_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_siwfs_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_subscriber_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_subscriber_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_subscriber_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_provide_subscriber_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_purge_ms_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_qo_s_subscribed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ready_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_register_cc_entry_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_register_cc_entry_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_remote_user_free_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_remote_user_free_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_report_sm_delivery_status_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_reporting_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_requested_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_resource_limitation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_response_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_response_time_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_resume_call_handling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_resume_call_handling_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_roaming_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_routing_info_for_lcs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_routing_info_for_lcs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ruf_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_group_call_end_signal_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_group_call_end_signal_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_routing_info_for_gprs_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_routing_info_for_gprs_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_set_reporting_state_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_set_reporting_state_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sgsn_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sgsn_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_short_term_denial_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_siwfs_signalling_modify_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_siwfs_signalling_modify_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_rp_mti.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sm_rp_smea.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sms_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sms_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sms_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sms_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_camel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_event_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_event_specification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_invocation_notification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_invocation_notification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ss_user_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_status_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_sub_busy_for_mt_sms_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_location_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_location_report_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_super_charger_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_supported_ccbs_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_t_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_t_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_t_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_t_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_teleserv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_tracing_buffer_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unauthorized_lcs_client_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unauthorized_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unauthorized_requesting_network_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unexpected_data_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unidentified_sub_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unknown_or_unreachable_lcs_client_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unknown_subscriber_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_unknown_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_update_gprs_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_update_gprs_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_user_info_helper.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_uu_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_uu_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_uui.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_vbs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_vertical_accuracy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_vgcs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_vlr_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_vlr_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_voice_broadcast_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_voice_group_call_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_common_zone_code_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_absent_subscriber_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_access_connection_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_activate_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_activate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_alert_service_center_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_attach_imsi_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_authenticate_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_authenticate_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_authentication_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_begin_subscriber_activity_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barred_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_date_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_duration.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_channel_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_charge.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_charging_unit.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_check_imei_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_check_imei_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ciphering_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cksn.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_classmark_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cm_service_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_complete_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_connect_to_following_address_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_facilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_reject_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deactivate_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deactivate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deregister_mobile_subscriber_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_detach_imsi_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_equip_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_erase_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_erase_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_access_signaling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_new_tmsi_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_short_message_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_ss_notification_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_get_password_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_get_password_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_handover_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_handover_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_hunt_group_access_selection_order.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_impossible_call_completion_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_interrogate_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_invoke_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_invoke_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ki.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_l_ms_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_loc_area_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_location_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_map_abort_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_maximum_conferees_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_note_internal_handover.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_note_ms_present_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_number_of_conferees.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_packet_data_volume.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_page_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_password_registration_failure_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_handover_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_handover_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_subsequent_handover_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_subsequent_handover_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_access_request_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_access_request_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_access_signaling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_unstructured_ss_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_unstructured_ss_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_provide_imsi_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_password_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_password_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_request_parameter.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_request_parameters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_search_for_mobile_subscriber_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_search_for_mobile_subscriber_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_handover_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_info_for_incoming_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_info_for_outgoing_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_parameters_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_parameters_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_information_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sent_parameter.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sent_parameters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_set_ciphering_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_set_message_waiting_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_delivery_failure_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_rp_ui.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_charging_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_charging_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_code_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_error_status_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_incompatibility_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_notification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_request.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_subscription_violation_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_user_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_system_failure_error_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_trace_subscriber_activity_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_update_location_area_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_user_to_user_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_authentication_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_begin_subscriber_activity_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_channel_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_classmark_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cli_restriction_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_extensible_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_handover_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_handover_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ki.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_location_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_note_internal_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_perform_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_perform_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_perform_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_request_parameter.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_request_parameter_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_parameters_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sent_parameter.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sent_parameter_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_delivery_failure_cause_with_diagnostic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_user_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_trace_subscriber_activity_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_zone_code_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_absent_subscriber_diagnostic_sm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_absent_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_absent_subscriber_sm_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_activate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_activate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_alert_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_alert_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_any_time_interrogation_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_any_time_interrogation_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ati_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_authentication_set.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_authentication_set_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_basic_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_bearer_serv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_bearer_service_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_busy_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_call_barring_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_call_barring_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_call_barring_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_camel_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_camel_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cancel_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cell_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cell_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cli_restriction_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cli_restriction_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_check_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_index.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_interlock.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_reject_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_reject_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_subscription.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_cug_subscription_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_data_missing_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_deactivate_trace_mode_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_deactivate_trace_mode_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_default_call_handling.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_delete_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_delete_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_emlpp_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_emlpp_priority.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_equipment_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_basic_service_group_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_call_bar_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_call_bar_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_call_barring_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_forw_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_forw_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_forw_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_forw_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_no_rep_cond_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_extended_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_extensible_call_barred_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_extensible_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_external_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_facility_not_sup_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_failed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_feature.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_feature_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_forwarding_violation_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_generic_service_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_global_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_gmsc_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_guidance_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_hlr_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_hlr_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_illegal_equipment_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_illegal_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_imei.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_imsi_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_inform_service_centre_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_insert_subscriber_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_insert_subscriber_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_inter_cug_restrictions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_interrogate_ss_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_interrogation_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_intra_cug_options.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_isdn_subaddress_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_kc.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_location_info_with_lmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_accept_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_close_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_dialogue_pdu.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_open_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_provider_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_provider_abort_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_refuse_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_user_abort_choice.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_user_abort_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_map_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_message_wait_list_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_mo_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_mo_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_mt_forward_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_mt_forward_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_mw_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_no_reply_condition_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_no_roaming_nb_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_no_subscriber_reply_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_number_changed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_number_of_forwarding.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_o_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_o_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_o_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_o_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_odb_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_odb_general_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_odb_hplmn_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_or_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_or_phase.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_override_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_password.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_prepare_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_prepare_ho_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_prepare_subsequent_ho_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_procedure_cancellation_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_protocol_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_provide_roaming_number_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_provide_roaming_number_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_provide_subscriber_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_provide_subscriber_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_purge_ms_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_pw_registration_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_rand.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ready_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_regional_subscription_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_register_ss_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_report_sm_delivery_status_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_report_sm_delivery_status_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_requested_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_reset_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_resource_unavailable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_restore_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_restore_data_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_resume_call_handling_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_resume_call_handling_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_roaming_not_allowed_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_roaming_not_allowed_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_routing_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_routing_info_for_sm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_routing_info_for_sm_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_send_authentication_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_send_authentication_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_send_identification_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_send_routing_info_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_send_routing_info_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_signal_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sm_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sm_delivery_outcome.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sm_enumerated_delivery_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sm_rp_da.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sm_rp_oa.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sres.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_for_bs_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_incompatibility_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_info_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ss_subscription_option.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_sub_busy_for_mt_sms_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_subscriber_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_subscriber_identity.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_subscriber_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_subscriber_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_supported_camel_phases.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_system_failure_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_t_bcsm_camel_tdp_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_t_bcsm_camel_tdp_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_t_bcsm_trigger_detection_point.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_t_csi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_tbcd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_teleserv_not_prov_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_teleservice_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_tmsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_trace_reference.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_trace_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_tracing_buffer_full_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_unexpected_data_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_unidentified_sub_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_unknown_subscriber_param.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_update_location_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_update_location_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ussd_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ussd_data_coding_scheme.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ussd_res.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_ussd_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_vbs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_vgcs_data_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_vlr_camel_subscription_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_voice_broadcast_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_voice_group_call_data.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_zone_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v3_zone_code_list.h
# End Source File
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

SOURCE=..\include\itu\map_v6_encryption_protection_information.h
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

SOURCE=..\include\itu\map_v6_radio_resource_information.h
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

SOURCE=..\include\itu\map_v6_type_of_modification.h
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

SOURCE=.\map_v1_lrf.asn
# End Source File
# Begin Source File

SOURCE=.\map_v2_lrf.asn
# End Source File
# Begin Source File

SOURCE=.\map_v3_lrf.asn
# End Source File
# Begin Source File

SOURCE=.\map_v4_lrf.asn
# End Source File
# Begin Source File

SOURCE=.\map_v5_lrf.asn
# End Source File
# Begin Source File

SOURCE=.\map_v6_lrf.asn

!IF  "$(CFG)" == "map_v6_to_v1_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v6_lrf.asn

".\map_common_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppMerge -cppMergeWithExtensions -cppMergeModuleName MAP-COMMON -cppMergeNamespace map_common -cppMergeGenerateAllHeaders -cppNamespace map_v6 -cppNamespace map_v5 -cppNamespace map_v4 -cppNamespace map_v3 -cppNamespace map_v2 -cppNamespace map_v1 -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v6_lrf.asn map_v5_lrf.asn map_v4_lrf.asn map_v3_lrf.asn map_v2_lrf.asn map_v1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v6_to_v1_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v6_lrf.asn

".\map_common_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppMerge -cppMergeWithExtensions -cppMergeModuleName MAP-COMMON -cppMergeNamespace map_common -cppMergeGenerateAllHeaders -cppNamespace map_v6 -cppNamespace map_v5 -cppNamespace map_v4 -cppNamespace map_v3 -cppNamespace map_v2 -cppNamespace map_v1 -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v6_lrf.asn map_v5_lrf.asn map_v4_lrf.asn map_v3_lrf.asn map_v2_lrf.asn map_v1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
