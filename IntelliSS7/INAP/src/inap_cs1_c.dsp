# Microsoft Developer Studio Project File - Name="inap_cs1_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=inap_cs1_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "inap_cs1_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "inap_cs1_c.mak" CFG="inap_cs1_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "inap_cs1_c - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "inap_cs1_c - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "inap_cs1_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "inap_cs1_c_Win32_Release"
# PROP Intermediate_Dir "inap_cs1_c_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\INAP-CS1.lib"

!ELSEIF  "$(CFG)" == "inap_cs1_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "inap_cs1_c___Win32_Debug"
# PROP BASE Intermediate_Dir "inap_cs1_c___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "inap_cs1_c_Win32_Debug"
# PROP Intermediate_Dir "inap_cs1_c_Win32_Debug"
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
# ADD LIB32 /nologo /out:"..\lib\INAP-CS1D.lib"

!ENDIF 

# Begin Target

# Name "inap_cs1_c - Win32 Release"
# Name "inap_cs1_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\inap_cs1_a_ch_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_access_code_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_activate_service_filtering_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_additional_calling_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_alerting_pattern_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_analyse_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_analysed_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_application_timer_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_apply_charging_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_apply_charging_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_assist_request_instructions_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_assisting_sspip_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_bcsm_event_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_bearer_capability_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_call_gap_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_call_information_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_call_information_request_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_call_result_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_called_party_business_group_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_called_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_called_party_subaddress_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_calling_party_business_group_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_calling_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_calling_party_subaddress_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_calling_partys_category_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_cancel_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_cancel_status_report_request_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_carrier_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_cg_encountered_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_charge_number_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_charging_event_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_collect_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_collected_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_collected_info_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_collected_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_connect_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_connect_to_resource_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_control_type_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_correlation_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_counter_and_value_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_counter_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_counters_value_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_cut_and_paste_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_date_and_time_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_destination_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_display_information_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_dp_specific_common_parameters_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_dp_specific_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_duration_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_error_treatment_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_establish_temporary_connection_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_event_notification_charging_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_event_report_bcsm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_event_specific_information_bcsm_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_event_specific_information_charging_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_event_type_bcsm_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_event_type_charging_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_extension_field_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_facility_group_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_facility_group_member_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_fci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_feature_code_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_feature_request_indicator_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_filtered_call_treatment_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_filtering_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_filtering_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_filtering_time_out_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_forward_call_indicators_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_forwarding_condition_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_furnish_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_gap_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_gap_indicators_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_gap_on_service_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_gap_treatment_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_high_layer_compatibility_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_hold_call_in_network_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_hold_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_inband_info_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_information_to_send_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_initial_dp_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_initiate_call_attempt_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_integer4_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_interval_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_invoke_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_ip_available_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_ip_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_ipssp_capabilities_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_isdn_access_related_information_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_leg_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_leg_type_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_location_number_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_maximum_number_of_counters_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_message_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_mid_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_misc_call_info_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_monitor_mode_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_number_of_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_numbering_plan_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_o_answer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_o_called_party_busy_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_o_disconnect_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_o_no_answer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_original_called_party_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_origination_attempt_authorized_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_play_announcement_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_prompt_and_collect_user_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_received_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_redirecting_party_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_redirection_information_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_release_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_report_condition_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_request_current_status_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_request_current_status_report_result_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_request_every_status_change_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_request_first_status_match_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_request_notification_charging_event_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_request_report_bcsm_event_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_requested_information_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_requested_information_list_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_requested_information_type_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_requested_information_type_list_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_requested_information_value_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_reset_timer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_resource_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_resource_status_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_response_condition_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_route_list_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_route_select_failure_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_scf_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_sci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_select_facility_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_select_route_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_send_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_service_address_information_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_service_filtering_response_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_service_interaction_indicators_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_service_key_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_service_profile_identifier_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_serving_area_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_sf_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_specialized_resource_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_status_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_t_answer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_t_busy_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_t_disconnect_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_t_no_answer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_term_attempt_authorized_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_terminal_type_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_timer_id_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_timer_value_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_tone_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_travelling_class_mark_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_trigger_type_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_unavailable_network_resource_c.c
# End Source File
# Begin Source File

SOURCE=.\inap_cs1_variable_part_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\inap_cs1_a_ch_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_access_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_activate_service_filtering_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_additional_calling_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_alerting_pattern_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_analyse_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_analysed_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_application_timer_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_apply_charging_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_apply_charging_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_assist_request_instructions_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_assisting_sspip_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_bcsm_event_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_bearer_capability_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_call_gap_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_call_information_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_call_information_request_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_call_result_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_called_party_business_group_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_called_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_called_party_subaddress_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_calling_party_business_group_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_calling_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_calling_party_subaddress_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_calling_partys_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_cancel_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_cancel_status_report_request_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_carrier_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_cg_encountered_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_charge_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_charging_event_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_collect_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_collected_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_collected_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_collected_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_connect_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_connect_to_resource_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_control_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_correlation_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_counter_and_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_counter_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_counters_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_cut_and_paste_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_date_and_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_destination_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_display_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_dp_specific_common_parameters_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_dp_specific_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_duration_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_error_treatment_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_establish_temporary_connection_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_event_notification_charging_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_event_report_bcsm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_event_specific_information_bcsm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_event_specific_information_charging_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_event_type_bcsm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_event_type_charging_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_extension_field_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_facility_group_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_facility_group_member_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_fci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_feature_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_feature_request_indicator_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_filtered_call_treatment_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_filtering_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_filtering_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_filtering_time_out_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_forward_call_indicators_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_forwarding_condition_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_furnish_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_gap_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_gap_indicators_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_gap_on_service_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_gap_treatment_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_high_layer_compatibility_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_hold_call_in_network_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_hold_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_inband_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_information_to_send_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_initial_dp_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_initiate_call_attempt_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_integer4_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_interval_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_invoke_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_ip_available_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_ip_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_ipssp_capabilities_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_isdn_access_related_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_leg_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_leg_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_location_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_maximum_number_of_counters_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_message_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_mid_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_misc_call_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_monitor_mode_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_number_of_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_numbering_plan_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_o_answer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_o_called_party_busy_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_o_disconnect_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_o_no_answer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_original_called_party_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_origination_attempt_authorized_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_play_announcement_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_prompt_and_collect_user_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_received_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_redirecting_party_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_redirection_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_release_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_report_condition_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_request_current_status_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_request_current_status_report_result_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_request_every_status_change_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_request_first_status_match_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_request_notification_charging_event_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_request_report_bcsm_event_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_requested_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_requested_information_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_requested_information_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_requested_information_type_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_requested_information_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_reset_timer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_resource_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_resource_status_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_response_condition_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_route_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_route_select_failure_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_scf_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_sci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_select_facility_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_select_route_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_send_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_service_address_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_service_filtering_response_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_service_interaction_indicators_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_service_key_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_service_profile_identifier_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_serving_area_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_sf_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_specialized_resource_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_status_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_t_answer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_t_busy_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_t_disconnect_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_t_no_answer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_term_attempt_authorized_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_terminal_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_timer_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_timer_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_tone_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_travelling_class_mark_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_trigger_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_unavailable_network_resource_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs1_variable_part_c.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\inap_cs1_lrf.asn

!IF  "$(CFG)" == "inap_cs1_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\inap_cs1_lrf.asn

".\inap_cs1_access_code_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn inap_cs1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "inap_cs1_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\inap_cs1_lrf.asn

".\inap_cs1_access_code_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn inap_cs1_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
