# Microsoft Developer Studio Project File - Name="map_v1_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v1_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v1_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v1_c.mak" CFG="map_v1_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v1_c - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v1_c - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v1_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v1_c_Win32_Release"
# PROP Intermediate_Dir "map_v1_c_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V1.lib"

!ELSEIF  "$(CFG)" == "map_v1_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "map_v1_c___Win32_Debug"
# PROP BASE Intermediate_Dir "map_v1_c___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v1_c_Win32_Debug"
# PROP Intermediate_Dir "map_v1_c_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V1D.lib"

!ENDIF 

# Begin Target

# Name "map_v1_c - Win32 Release"
# Name "map_v1_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v1_absent_subscriber_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_access_connection_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_activate_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_activate_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_activate_trace_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_alert_service_center_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_attach_imsi_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_authenticate_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_authenticate_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_authentication_set_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_basic_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_bearer_service_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_begin_subscriber_activity_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barred_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barring_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barring_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_barring_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_date_time_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_duration_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_reference_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_call_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cancel_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_category_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_channel_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_charge_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_charging_unit_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_check_imei_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_check_imei_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ciphering_mode_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cksn_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_classmark_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cm_service_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_complete_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_connect_to_following_address_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_facilities_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_index_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_interlock_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_cug_reject_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_deactivate_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_deactivate_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_deactivate_trace_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_delete_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_deregister_mobile_subscriber_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_detach_imsi_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_equip_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_erase_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_erase_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_external_signal_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_access_signaling_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_new_tmsi_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_short_message_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forward_ss_notification_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_feature_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_feature_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_forwarding_options_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_get_password_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_get_password_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_global_cell_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_guidance_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_handover_priority_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_handover_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_hlr_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_hlr_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_hunt_group_access_selection_order_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_imei_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_impossible_call_completion_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_imsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_insert_subscriber_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_interrogate_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_interrogate_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_invoke_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_invoke_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_isdn_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_kc_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ki_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_l_ms_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_loc_area_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_location_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_map_abort_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_maximum_conferees_number_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_network_resource_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_no_reply_condition_time_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_note_internal_handover_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_note_ms_present_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_number_of_conferees_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_number_of_forwarding_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_packet_data_volume_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_page_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_password_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_password_registration_failure_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_handover_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_handover_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_subsequent_handover_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_perform_subsequent_handover_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_access_request_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_access_request_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_access_signaling_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_unstructured_ss_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_process_unstructured_ss_data_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_protocol_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_provide_imsi_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_provide_roaming_number_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_provide_roaming_number_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_rand_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_password_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_password_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_ss_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_register_ss_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_request_parameter_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_request_parameters_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_reset_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_search_for_mobile_subscriber_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_search_for_mobile_subscriber_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_handover_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_info_for_incoming_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_info_for_outgoing_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_parameters_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_parameters_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_info_for_sm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_info_for_sm_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_send_routing_information_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sent_parameter_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sent_parameters_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_set_ciphering_mode_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_set_message_waiting_data_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_signal_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_delivery_failure_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_rp_da_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_rp_oa_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sm_rp_ui_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_sres_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_charging_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_charging_info_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_code_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_data_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_error_status_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_incompatibility_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_info_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_information_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_notification_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_request_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_subscription_option_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_subscription_violation_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_user_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_data_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_id_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_status_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_system_failure_error_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_tbcd_string_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_teleservice_list_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_tmsi_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_trace_reference_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_trace_subscriber_activity_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_trace_type_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_update_location_area_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_update_location_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_update_location_res_c.c
# End Source File
# Begin Source File

SOURCE=.\map_v1_user_to_user_service_indicator_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\map_v1_absent_subscriber_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_access_connection_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_activate_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_activate_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_activate_trace_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_alert_service_center_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_attach_imsi_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_authenticate_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_authenticate_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_authentication_set_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_basic_service_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_bearer_service_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_begin_subscriber_activity_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barred_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barring_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barring_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_barring_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_date_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_duration_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_reference_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_call_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cancel_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_channel_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_charge_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_charging_unit_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_check_imei_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_check_imei_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ciphering_mode_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cksn_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_classmark_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cm_service_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_complete_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_connect_to_following_address_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_facilities_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_index_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_interlock_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_cug_reject_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deactivate_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deactivate_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deactivate_trace_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_delete_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_deregister_mobile_subscriber_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_detach_imsi_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_equip_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_erase_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_erase_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_external_signal_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_access_signaling_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_new_tmsi_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_short_message_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forward_ss_notification_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_feature_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_feature_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_forwarding_options_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_get_password_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_get_password_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_global_cell_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_guidance_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_handover_priority_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_handover_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_hlr_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_hlr_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_hunt_group_access_selection_order_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_imei_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_impossible_call_completion_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_imsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_insert_subscriber_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_interrogate_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_interrogate_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_invoke_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_invoke_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_isdn_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_kc_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ki_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_l_ms_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_loc_area_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_location_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_map_abort_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_maximum_conferees_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_network_resource_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_no_reply_condition_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_note_internal_handover_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_note_ms_present_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_number_of_conferees_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_number_of_forwarding_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_packet_data_volume_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_page_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_password_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_password_registration_failure_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_handover_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_handover_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_subsequent_handover_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_perform_subsequent_handover_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_access_request_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_access_request_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_access_signaling_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_unstructured_ss_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_process_unstructured_ss_data_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_protocol_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_provide_imsi_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_provide_roaming_number_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_provide_roaming_number_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_rand_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_password_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_password_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_ss_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_register_ss_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_request_parameter_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_request_parameters_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_reset_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_search_for_mobile_subscriber_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_search_for_mobile_subscriber_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_handover_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_info_for_incoming_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_info_for_outgoing_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_parameters_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_parameters_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_info_for_sm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_info_for_sm_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_send_routing_information_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sent_parameter_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sent_parameters_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_set_ciphering_mode_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_set_message_waiting_data_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_signal_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_delivery_failure_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_rp_da_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_rp_oa_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sm_rp_ui_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_sres_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_charging_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_charging_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_code_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_data_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_error_status_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_incompatibility_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_info_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_notification_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_request_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_subscription_option_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_subscription_violation_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_ss_user_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_subscriber_data_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_subscriber_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_subscriber_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_system_failure_error_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_tbcd_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_teleservice_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_tmsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_trace_reference_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_trace_subscriber_activity_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_trace_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_update_location_area_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_update_location_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_update_location_res_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\map_v1_user_to_user_service_indicator_c.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\map_v1_lrf.asn

!IF  "$(CFG)" == "map_v1_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v1_lrf.asn

".\map_v1_activate_ss_arg_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v1_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v1_lrf.asn

".\map_v1_activate_ss_arg_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
