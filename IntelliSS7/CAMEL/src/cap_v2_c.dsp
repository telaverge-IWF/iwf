# Microsoft Developer Studio Project File - Name="cap_v2_c" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cap_v2_c - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cap_v2_c.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cap_v2_c.mak" CFG="cap_v2_c - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cap_v2_c - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cap_v2_c - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cap_v2_c - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "cap_v2_c_Win32_Release"
# PROP Intermediate_Dir "cap_v2_c_Win32_Release"
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
# ADD LIB32 /nologo /out:"..\lib\CAP-V2.lib"

!ELSEIF  "$(CFG)" == "cap_v2_c - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cap_v2_c___Win32_Debug"
# PROP BASE Intermediate_Dir "cap_v2_c___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "cap_v2_c_Win32_Debug"
# PROP Intermediate_Dir "cap_v2_c_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-c" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CAP-V2D.lib"

!ENDIF 

# Begin Target

# Name "cap_v2_c - Win32 Release"
# Name "cap_v2_c - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cap_v2_a_ch_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_additional_calling_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_age_of_location_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_alerting_pattern_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_aoc_before_answer_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_aoc_subsequent_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_application_timer_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_apply_charging_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_apply_charging_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_assist_request_instructions_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_assisting_sspip_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_bcsm_event_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_bearer_capability_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_bothway_through_connection_ind_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cai_gsm0224_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_information_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_information_request_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_reference_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_result_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_called_party_bcd_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_called_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_calling_party_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_calling_partys_category_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_a_ch_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_call_result_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_fci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_sci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cancel_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cause_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cell_id_fixed_length_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cell_id_or_lai_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_collected_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_collected_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_connect_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_connect_to_resource_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_correlation_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_criticality_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_date_and_time_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_destination_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_digits_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_dp_specific_criteria_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_error_treatment_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_establish_temporary_connection_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_event_report_bcsm_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_event_specific_information_bcsm_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_event_type_bcsm_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ext_basic_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ext_bearer_service_code_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ext_teleservice_code_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_extension_container_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_extension_field_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_fci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_furnish_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_generic_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_generic_numbers_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_geographical_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_high_layer_compatibility_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_imsi_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_inband_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_information_to_send_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_initial_dp_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_initial_dp_arg_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_integer4_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_invoke_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ip_routing_address_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ipssp_capabilities_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_isdn_address_string_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_its_feature_class_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_lai_fixed_length_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_leg_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_leg_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_location_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_location_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_message_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_misc_call_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_monitor_mode_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_carrier_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_carrier_selection_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_charge_number_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_oli_info_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_naea_cic_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_not_reachable_reason_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ocsi_applicable_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_original_called_party_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_pcs_extensions_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_play_announcement_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_private_extension_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_private_extension_list_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_prompt_and_collect_user_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_received_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_receiving_side_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_redirecting_party_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_redirection_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_release_call_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_release_if_duration_exceeded_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_request_report_bcsm_event_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_list_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_type_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_type_list_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_value_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_reset_timer_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_scf_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_sci_billing_charging_characteristics_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_send_charging_information_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_sending_side_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_service_interaction_indicators_two_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_service_key_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_specialized_resource_report_arg_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_subscriber_state_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_suppression_of_announcement_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_and_timezone_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_if_no_tariff_switch_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_if_tariff_switch_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_information_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_timer_id_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_timer_value_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_tone_c.c
# End Source File
# Begin Source File

SOURCE=.\cap_v2_variable_part_c.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\cap_v2_a_ch_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_additional_calling_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_age_of_location_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_alerting_pattern_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_aoc_before_answer_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_aoc_subsequent_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_application_timer_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_apply_charging_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_apply_charging_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_assist_request_instructions_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_assisting_sspip_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_bcsm_event_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_bearer_capability_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_bothway_through_connection_ind_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cai_gsm0224_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_information_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_information_request_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_reference_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_result_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_called_party_bcd_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_called_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_calling_party_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_calling_partys_category_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_a_ch_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_call_result_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_fci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_sci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cancel_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cause_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cell_id_fixed_length_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cell_id_or_lai_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_collected_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_collected_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_connect_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_connect_to_resource_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_correlation_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_criticality_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_date_and_time_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_destination_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_digits_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_dp_specific_criteria_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_error_treatment_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_establish_temporary_connection_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_event_report_bcsm_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_event_specific_information_bcsm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_event_type_bcsm_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ext_basic_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ext_bearer_service_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ext_teleservice_code_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_extension_container_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_extension_field_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_fci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_furnish_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_generic_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_generic_numbers_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_geographical_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_high_layer_compatibility_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_imsi_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_inband_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_information_to_send_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_initial_dp_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_initial_dp_arg_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_integer4_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_invoke_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ip_routing_address_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ipssp_capabilities_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_isdn_address_string_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_its_feature_class_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_lai_fixed_length_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_leg_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_leg_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_location_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_location_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_message_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_misc_call_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_monitor_mode_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_carrier_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_carrier_selection_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_charge_number_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_oli_info_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_naea_cic_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_not_reachable_reason_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ocsi_applicable_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_original_called_party_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_pcs_extensions_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_play_announcement_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_private_extension_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_private_extension_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_prompt_and_collect_user_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_received_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_receiving_side_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_redirecting_party_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_redirection_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_release_call_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_release_if_duration_exceeded_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_request_report_bcsm_event_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_type_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_type_list_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_reset_timer_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_scf_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_sci_billing_charging_characteristics_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_send_charging_information_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_sending_side_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_service_interaction_indicators_two_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_service_key_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_specialized_resource_report_arg_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_subscriber_state_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_suppression_of_announcement_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_and_timezone_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_if_no_tariff_switch_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_if_tariff_switch_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_information_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_timer_id_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_timer_value_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_tone_c.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_variable_part_c.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\cap_v2_lrf.asn

!IF  "$(CFG)" == "cap_v2_c - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\cap_v2_lrf.asn

".\cap_v2_additional_calling_party_number_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn cap_v2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "cap_v2_c - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\cap_v2_lrf.asn

".\cap_v2_additional_calling_party_number_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -c -u $(ITS_ROOT)\tools\bin\asncc_useful.asn cap_v2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
