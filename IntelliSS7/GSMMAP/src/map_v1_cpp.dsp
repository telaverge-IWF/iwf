# Microsoft Developer Studio Project File - Name="map_v1_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v1_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v1_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v1_cpp.mak" CFG="map_v1_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v1_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v1_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v1_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v1_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v1_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V1++.lib"

!ELSEIF  "$(CFG)" == "map_v1_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "map_v1_cpp___Win32_Debug"
# PROP BASE Intermediate_Dir "map_v1_cpp___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v1_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v1_cpp_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V1++D.lib"

!ENDIF 

# Begin Target

# Name "map_v1_cpp - Win32 Release"
# Name "map_v1_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=.\map_v1_address_string.cpp
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

SOURCE=.\map_v1_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_begin_subscriber_activity_arg.cpp
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

SOURCE=.\map_v1_call_reference.cpp
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

SOURCE=.\map_v1_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_channel_type.cpp
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

SOURCE=.\map_v1_cug_interlock.cpp
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

SOURCE=.\map_v1_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_get_password_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_get_password_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_handover_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_handover_type.cpp
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

SOURCE=.\map_v1_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_impossible_call_completion_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_imsi.cpp
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

SOURCE=.\map_v1_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ki.cpp
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

SOURCE=.\map_v1_no_reply_condition_time.cpp
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

SOURCE=.\map_v1_number_of_forwarding.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_packet_data_volume.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_page_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_password.cpp
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

SOURCE=.\map_v1_signal_info.cpp
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

SOURCE=.\map_v1_ss_code.cpp
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

SOURCE=.\map_v1_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_subscription_violation_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_ss_user_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_system_failure_error_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v1_trace_reference.cpp
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
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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
# End Group
# Begin Source File

SOURCE=.\map_v1_lrf.asn

!IF  "$(CFG)" == "map_v1_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v1_lrf.asn

".\map_v1_activate_ss_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -cppNamespace map_v1 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v1_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v1_lrf.asn

".\map_v1_activate_ss_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -cpp -cppNamespace map_v1 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
