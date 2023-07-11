# Microsoft Developer Studio Project File - Name="map_v3_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v3_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v3_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v3_cpp.mak" CFG="map_v3_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v3_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v3_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v3_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v3_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v3_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V3++.lib"

!ELSEIF  "$(CFG)" == "map_v3_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v3_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v3_cpp_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V3++D.lib"

!ENDIF 

# Begin Target

# Name "map_v3_cpp - Win32 Release"
# Name "map_v3_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v3_absent_subscriber_diagnostic_sm.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_absent_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_absent_subscriber_sm_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_activate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_any_time_interrogation_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_any_time_interrogation_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ati_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_authentication_set.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_bearer_serv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_busy_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_camel_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_camel_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cell_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cell_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cli_restriction_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_reject_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_data_missing_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_deactivate_trace_mode_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_default_call_handling.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_emlpp_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_emlpp_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_call_bar_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_call_bar_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_forw_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_forw_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_forw_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_forw_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_no_rep_cond_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_extended_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_extensible_call_barred_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_extensible_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_facility_not_sup_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_failed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_forwarding_violation_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_gmsc_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_illegal_equipment_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_illegal_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_imsi_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_inform_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_insert_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_insert_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_interrogation_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_message_wait_list_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_mo_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_mo_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_mt_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_mt_forward_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_no_roaming_nb_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_no_subscriber_reply_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_number_changed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_o_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_o_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_o_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_o_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_odb_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_odb_general_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_odb_hplmn_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_or_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_or_phase.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_password.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_provide_roaming_number_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_provide_subscriber_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_provide_subscriber_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_register_ss_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_report_sm_delivery_status_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_report_sm_delivery_status_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_requested_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_reset_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_resume_call_handling_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_resume_call_handling_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_roaming_not_allowed_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_send_identification_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_send_routing_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_send_routing_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_sub_busy_for_mt_sms_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_subscriber_identity.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_subscriber_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_supported_camel_phases.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_system_failure_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_t_bcsm_camel_tdp_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_t_bcsm_camel_tdp_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_t_bcsm_trigger_detection_point.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_t_csi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_teleserv_not_prov_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_tracing_buffer_full_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_unexpected_data_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_unidentified_sub_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_unknown_subscriber_param.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_user_info_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_vbs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_vgcs_data_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_vlr_camel_subscription_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_voice_broadcast_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_voice_group_call_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v3_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE=..\include\itu\map_v3_user_info_helper.h
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
# End Group
# Begin Source File

SOURCE=.\map_v3_lrf.asn

!IF  "$(CFG)" == "map_v3_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v3_lrf.asn

".\map_v3_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v3 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v3_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v3_cpp - Win32 Debug"

# PROP Intermediate_Dir "map_v3_cpp_Win32_Debug"
# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v3_lrf.asn

".\map_v3_absent_subscriber_diagnostic_sm.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2  -explicitChoice -cpp -cppNamespace map_v3 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v3_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
