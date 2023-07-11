# Microsoft Developer Studio Project File - Name="inap_etsi_cs1_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=inap_etsi_cs1_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "inap_etsi_cs1_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "inap_etsi_cs1_cpp.mak" CFG="inap_etsi_cs1_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "inap_etsi_cs1_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "inap_etsi_cs1_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "inap_etsi_cs1_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "inap_etsi_cs1_cpp_Win32_Release"
# PROP Intermediate_Dir "inap_etsi_cs1_cpp_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\INAP-ETSI-CS1++.lib"

!ELSEIF  "$(CFG)" == "inap_etsi_cs1_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "inap_etsi_cs1_cpp___Win32_Debug"
# PROP BASE Intermediate_Dir "inap_etsi_cs1_cpp___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "inap_etsi_cs1_cpp_Win32_Debug"
# PROP Intermediate_Dir "inap_etsi_cs1_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\INAP-ETSI-CS1++D.lib"

!ENDIF 

# Begin Target

# Name "inap_etsi_cs1_cpp - Win32 Release"
# Name "inap_etsi_cs1_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\inap_etsi_cs1_a_ch_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_activate_service_filtering_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_additional_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_application_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_apply_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_apply_charging_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_assist_request_instructions_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_assisting_sspip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_bcsm_event.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_bearer_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_call_gap_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_call_information_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_call_information_request_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_call_result.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_called_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_calling_partys_category.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_cancel_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_cancel_failed.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_cg_encountered.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_charging_event.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_collect_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_collected_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_collected_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_connect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_connect_to_resource_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_control_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_correlation_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_counter_and_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_counter_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_counters_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_cut_and_paste.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_date_and_time.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_destination_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_display_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_dp_specific_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_duration.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_error_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_establish_temporary_connection_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_event_notification_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_event_report_bcsm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_event_specific_information_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_event_specific_information_charging.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_event_type_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_event_type_charging.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_extension_field.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_fci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_filtered_call_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_filtering_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_filtering_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_filtering_time_out.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_forward_call_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_furnish_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_gap_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_gap_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_gap_on_service.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_gap_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_high_layer_compatibility.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_inband_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_information_to_send.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_initial_dp_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_initiate_call_attempt_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_integer4.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_interval.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_invoke_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_ip_available.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_ip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_ipssp_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_leg_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_leg_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_maximum_number_of_counters.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_message_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_misc_call_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_monitor_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_number_of_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_original_called_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_play_announcement_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_prompt_and_collect_user_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_received_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_redirecting_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_redirection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_release_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_request_notification_charging_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_request_report_bcsm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_requested_info_error.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_requested_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_requested_information_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_requested_information_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_requested_information_type_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_requested_information_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_reset_timer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_route_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_scf_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_sci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_send_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_service_filtering_response_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_service_interaction_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_sf_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_specialized_resource_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_task_refused.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_timer_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_timer_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_tone.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_unavailable_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_etsi_cs1_variable_part.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_a_ch_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_activate_service_filtering_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_additional_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_application_timer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_apply_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_apply_charging_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_assist_request_instructions_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_assisting_sspip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_bcsm_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_bearer_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_call_gap_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_call_information_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_call_information_request_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_call_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_called_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_calling_partys_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_cancel_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_cancel_failed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_cg_encountered.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_charging_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_collect_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_collected_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_collected_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_connect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_connect_to_resource_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_control_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_correlation_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_counter_and_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_counter_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_counters_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_cut_and_paste.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_date_and_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_destination_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_display_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_dp_specific_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_duration.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_error_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_establish_temporary_connection_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_event_notification_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_event_report_bcsm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_event_specific_information_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_event_specific_information_charging.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_event_type_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_event_type_charging.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_extension_field.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_fci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_filtered_call_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_filtering_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_filtering_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_filtering_time_out.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_forward_call_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_furnish_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_gap_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_gap_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_gap_on_service.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_gap_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_high_layer_compatibility.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_inband_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_information_to_send.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_initial_dp_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_initiate_call_attempt_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_integer4.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_interval.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_invoke_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_ip_available.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_ip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_ipssp_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_leg_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_leg_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_maximum_number_of_counters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_message_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_misc_call_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_monitor_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_number_of_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_original_called_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_play_announcement_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_prompt_and_collect_user_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_received_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_redirecting_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_redirection_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_release_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_request_notification_charging_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_request_report_bcsm_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_requested_info_error.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_requested_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_requested_information_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_requested_information_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_requested_information_type_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_requested_information_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_reset_timer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_route_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_scf_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_sci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_send_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_service_filtering_response_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_service_interaction_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_sf_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_specialized_resource_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_task_refused.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_timer_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_timer_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_tone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_unavailable_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_etsi_cs1_variable_part.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\inap_etsi_cs1_lrf.asn

!IF  "$(CFG)" == "inap_etsi_cs1_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\inap_etsi_cs1_lrf.asn

".\inap_etsi_cs1_activate_service_filtering_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace inap_etsi_cs1 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn inap_etsi_cs1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "inap_etsi_cs1_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\inap_etsi_cs1_lrf.asn

".\inap_etsi_cs1_activate_service_filtering_arg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace inap_etsi_cs1 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn inap_etsi_cs1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
