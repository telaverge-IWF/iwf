# Microsoft Developer Studio Project File - Name="map_v2_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=map_v2_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "map_v2_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "map_v2_cpp.mak" CFG="map_v2_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "map_v2_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "map_v2_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "map_v2_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "map_v2_cpp_Win32_Release"
# PROP Intermediate_Dir "map_v2_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V2++.lib"

!ELSEIF  "$(CFG)" == "map_v2_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "map_v2_cpp_Win32_Debug"
# PROP Intermediate_Dir "map_v2_cpp_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\MAP-V2++D.lib"

!ENDIF 

# Begin Target

# Name "map_v2_cpp - Win32 Release"
# Name "map_v2_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\map_v2_activate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_alert_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_alert_service_centre_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_authentication_set.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_authentication_set_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_group_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_basic_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_bearer_service_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_begin_subscriber_activity_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_barring_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_call_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cancel_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_channel_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_classmark_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cli_restriction_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cli_restriction_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_check_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_index.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_interlock.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_reject_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_subscription.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_cug_subscription_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_deactivate_trace_mode_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_delete_subscriber_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_delete_subscriber_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_equipment_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_extensible_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_external_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forward_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_feature.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_feature_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_forwarding_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_global_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_guidance_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_handover_priority.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_handover_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_hlr_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_hlr_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_imei.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_imsi_with_lmsi.cpp
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

SOURCE=.\map_v2_inter_cug_restrictions.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_interrogate_ss_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_intra_cug_options.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_isdn_subaddress_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_kc.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ki.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_location_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_location_info_with_lmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_accept_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_close_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_dialogue_pdu.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_open_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_provider_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_provider_abort_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_refuse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_user_abort_choice.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_user_abort_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_map_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_mw_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_no_reply_condition_time.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_note_internal_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_number_of_forwarding.cpp
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

SOURCE=.\map_v2_override_category.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_password.cpp
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

SOURCE=.\map_v2_prepare_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_prepare_ho_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_prepare_subsequent_ho_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_procedure_cancellation_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_protocol_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_provide_roaming_number_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_purge_ms_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_pw_registration_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_rand.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ready_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_regional_subscription_response.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_register_ss_arg.cpp
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

SOURCE=.\map_v2_resource_unavailable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_restore_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_restore_data_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_roaming_not_allowed_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_for_sm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_routing_info_for_sm_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_authentication_info_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_authentication_info_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_send_identification_res.cpp
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

SOURCE=.\map_v2_signal_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_failure_cause_with_diagnostic.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_delivery_outcome.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_enumerated_delivery_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_rp_da.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sm_rp_oa.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_sres.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_for_bs_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_incompatibility_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_info.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_info_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_subscription_option.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ss_user_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_data.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_subscriber_status.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_tbcd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_teleservice_list.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_tmsi.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_reference.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_subscriber_activity_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_trace_type.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_update_location_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_update_location_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_user_info_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_data_coding_scheme.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_res.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_ussd_string.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_zone_code.cpp
# End Source File
# Begin Source File

SOURCE=.\map_v2_zone_code_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE=..\include\itu\map_v2_user_info_helper.h
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
# End Group
# Begin Source File

SOURCE=.\map_v2_lrf.asn

!IF  "$(CFG)" == "map_v2_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v2_lrf.asn

".\map_v2_activate_trace_mode_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace map_v2 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "map_v2_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\map_v2_lrf.asn

".\map_v2_activate_trace_mode_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace map_v2 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn map_v2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
