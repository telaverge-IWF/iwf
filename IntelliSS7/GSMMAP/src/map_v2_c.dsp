# Microsoft Developer Studio Project File - Name="map_v2_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v2_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v2_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v2_c.mak" CFG="map_v2_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v2_c - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v2_c - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v2_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v2_c_Win32_Release"
# PROP Intermediate_Dir "map_v2_c_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V2.lib"

!ELSEIF  "$(CFG)" == "map_v2_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "map_v2_c___Win32_Debug"
# PROP BASE Intermediate_Dir "map_v2_c___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v2_c_Win32_Debug"
# PROP Intermediate_Dir "map_v2_c_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V2D.lib"

!ENDIF 

# Begin Target

# Name "map_v2_c - Win32 Release"
# Name "map_v2_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v2_activate_trace_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_alert_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_alert_service_centre_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_authentication_set_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_authentication_set_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_group_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_bearer_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_begin_subscriber_activity_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_reference_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cancel_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_channel_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_classmark_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cli_restriction_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cli_restriction_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_check_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_index_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_interlock_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_reject_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_subscription_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_subscription_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_deactivate_trace_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_delete_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_delete_subscriber_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_equipment_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_extensible_update_location_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_external_signal_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_forward_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_global_cell_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_guidance_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_handover_priority_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_handover_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_hlr_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_hlr_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_imei_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_imsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_imsi_with_lmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_inform_service_centre_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_insert_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_insert_subscriber_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_inter_cug_restrictions_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_interrogate_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_intra_cug_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_isdn_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_isdn_subaddress_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_kc_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ki_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_lmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_location_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_location_info_with_lmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_accept_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_close_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_dialogue_pdu_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_open_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_provider_abort_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_provider_abort_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_refuse_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_user_abort_choice_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_user_abort_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_mw_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_network_resource_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_no_reply_condition_time_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_note_internal_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_number_of_forwarding_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_odb_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_odb_general_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_odb_hplmn_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_override_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_password_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_perform_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_perform_ho_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_perform_subsequent_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_prepare_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_prepare_ho_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_prepare_subsequent_ho_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_procedure_cancellation_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_protocol_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_provide_roaming_number_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_purge_ms_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_pw_registration_failure_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_rand_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ready_for_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_regional_subscription_response_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_register_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_report_sm_delivery_status_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_request_parameter_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_request_parameter_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_reset_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_resource_unavailable_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_restore_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_restore_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_roaming_not_allowed_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_for_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_for_sm_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_authentication_info_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_authentication_info_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_identification_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_parameters_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_routing_info_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_routing_info_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sent_parameter_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sent_parameter_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_signal_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_failure_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_failure_cause_with_diagnostic_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_outcome_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_enumerated_delivery_failure_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_rp_da_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_rp_oa_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_sres_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_for_bs_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_incompatibility_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_info_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_subscription_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_user_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_tbcd_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_teleservice_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_tmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_reference_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_subscriber_activity_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_update_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_update_location_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_data_coding_scheme_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_zone_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v2_zone_code_list_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_v2_activate_trace_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_alert_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_alert_service_centre_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_authentication_set_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_authentication_set_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_basic_service_group_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_basic_service_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_bearer_service_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_begin_subscriber_activity_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_barring_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_call_reference_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cancel_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_channel_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_classmark_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cli_restriction_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cli_restriction_option_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_check_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_index_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_interlock_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_reject_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_subscription_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_cug_subscription_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_deactivate_trace_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_delete_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_delete_subscriber_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_equipment_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_extensible_update_location_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_external_signal_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forward_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_forwarding_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_global_cell_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_guidance_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_handover_priority_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_handover_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_hlr_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_hlr_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_imei_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_imsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_imsi_with_lmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_inform_service_centre_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_insert_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_insert_subscriber_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_inter_cug_restrictions_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_interrogate_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_intra_cug_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_isdn_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_isdn_subaddress_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_kc_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ki_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_lmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_location_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_location_info_with_lmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_accept_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_close_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_dialogue_pdu_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_open_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_provider_abort_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_provider_abort_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_refuse_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_user_abort_choice_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_map_user_abort_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_mw_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_network_resource_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_no_reply_condition_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_note_internal_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_number_of_forwarding_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_odb_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_odb_general_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_odb_hplmn_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_override_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_password_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_perform_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_perform_ho_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_perform_subsequent_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_prepare_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_prepare_ho_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_prepare_subsequent_ho_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_procedure_cancellation_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_protocol_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_provide_roaming_number_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_purge_ms_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_pw_registration_failure_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_rand_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ready_for_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_regional_subscription_response_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_register_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_report_sm_delivery_status_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_request_parameter_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_request_parameter_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_reset_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_resource_unavailable_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_restore_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_restore_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_roaming_not_allowed_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_routing_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_routing_info_for_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_routing_info_for_sm_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_authentication_info_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_authentication_info_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_identification_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_parameters_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_routing_info_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_send_routing_info_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sent_parameter_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sent_parameter_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_signal_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_delivery_failure_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_delivery_failure_cause_with_diagnostic_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_delivery_outcome_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_enumerated_delivery_failure_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_rp_da_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sm_rp_oa_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_sres_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_for_bs_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_incompatibility_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_info_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_subscription_option_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ss_user_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_subscriber_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_subscriber_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_subscriber_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_tbcd_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_teleservice_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_tmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_trace_reference_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_trace_subscriber_activity_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_trace_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_update_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_update_location_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_data_coding_scheme_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_ussd_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_zone_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v2_zone_code_list_c.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v2_lrf.asn

!IF  "$(CFG)" == "map_v2_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v2_lrf.asn

".\map_v2_activate_trace_mode_arg_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v2_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v2_lrf.asn

".\map_v2_activate_trace_mode_arg_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
