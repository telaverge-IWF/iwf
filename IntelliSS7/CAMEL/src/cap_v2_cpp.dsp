# Microsoft Developer Studio Project File - Name="cap_v2_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cap_v2_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cap_v2_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cap_v2_cpp.mak" CFG="cap_v2_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cap_v2_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cap_v2_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cap_v2_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "cap_v2_cpp_Win32_Release"
# PROP Intermediate_Dir "cap_v2_cpp_Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "ITS_IMPLEMENTATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CAP-V2++.lib"

!ELSEIF  "$(CFG)" == "cap_v2_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "cap_v2_cpp_Win32_Debug"
# PROP Intermediate_Dir "cap_v2_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Od /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "ITS_IMPLEMENTATION" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\CAP-V2++D.lib"

!ENDIF 

# Begin Target

# Name "cap_v2_cpp - Win32 Release"
# Name "cap_v2_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cap_init.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_a_ch_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_additional_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_age_of_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_aoc_before_answer.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_aoc_subsequent.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_application_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_apply_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_apply_charging_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_assist_request_instructions_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_assisting_sspip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_bcsm_event.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_bearer_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_bothway_through_connection_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cai_gsm0224.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_information_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_information_request_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_reference_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_call_result.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_called_party_bcd_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_called_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_calling_partys_category.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_a_ch_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_call_result.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_fci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_camel_sci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cancel_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cell_id_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_cell_id_or_lai.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_collected_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_collected_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_connect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_connect_to_resource_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_correlation_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_criticality_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_date_and_time.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_destination_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_dp_specific_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_error_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_establish_temporary_connection_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_event_report_bcsm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_event_specific_information_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_event_type_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ext_basic_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ext_bearer_service_code.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ext_teleservice_code.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_extension_container.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_extension_field.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_fci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_furnish_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_generic_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_generic_numbers.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_geographical_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_high_layer_compatibility.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_imsi.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_inband_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_information_to_send.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_initial_dp_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_initial_dp_arg_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_integer4.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_invoke_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ipssp_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_isdn_address_string.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_lai_fixed_length.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_leg_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_leg_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_location_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_message_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_misc_call_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_monitor_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_carrier_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_carrier_selection_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_charge_number.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_na_oli_info.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_naea_cic.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_not_reachable_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_ocsi_applicable.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_original_called_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_pcs_extensions.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_play_announcement_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_private_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_private_extension_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_prompt_and_collect_user_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_received_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_receiving_side_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_redirecting_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_redirection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_release_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_release_if_duration_exceeded.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_request_report_bcsm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_type.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_type_list.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_requested_information_value.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_reset_timer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_scf_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_sci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_send_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_sending_side_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_service_interaction_indicators_two.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_specialized_resource_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_subscriber_state.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_suppression_of_announcement.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_and_timezone.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_if_no_tariff_switch.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_if_tariff_switch.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_time_information.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_timer_id.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_timer_value.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_tone.cpp
# End Source File
# Begin Source File

SOURCE=.\cap_v2_variable_part.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\cap_cpp.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_a_ch_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_additional_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_age_of_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_aoc_before_answer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_aoc_subsequent.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_application_timer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_apply_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_apply_charging_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_assist_request_instructions_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_assisting_sspip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_bcsm_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_bearer_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_bothway_through_connection_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cai_gsm0224.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_information_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_information_request_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_reference_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_call_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_called_party_bcd_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_called_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_calling_partys_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_a_ch_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_call_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_fci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_camel_sci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cancel_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cell_id_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_cell_id_or_lai.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_collected_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_collected_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_connect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_connect_to_resource_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_correlation_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_criticality_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_date_and_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_destination_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_dp_specific_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_error_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_establish_temporary_connection_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_event_report_bcsm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_event_specific_information_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_event_type_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ext_basic_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ext_bearer_service_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ext_teleservice_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_extension_container.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_extension_field.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_fci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_furnish_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_generic_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_generic_numbers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_geographical_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_high_layer_compatibility.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_imsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_inband_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_information_to_send.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_initial_dp_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_initial_dp_arg_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_integer4.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_invoke_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ipssp_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_isdn_address_string.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_lai_fixed_length.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_leg_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_leg_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_location_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_message_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_misc_call_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_monitor_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_carrier_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_carrier_selection_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_charge_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_na_oli_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_naea_cic.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_not_reachable_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_ocsi_applicable.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_original_called_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_pcs_extensions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_play_announcement_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_private_extension.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_private_extension_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_prompt_and_collect_user_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_received_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_receiving_side_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_redirecting_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_redirection_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_release_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_release_if_duration_exceeded.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_request_report_bcsm_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_type_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_requested_information_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_reset_timer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_scf_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_sci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_send_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_sending_side_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_service_interaction_indicators_two.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_specialized_resource_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_subscriber_state.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_suppression_of_announcement.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_and_timezone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_if_no_tariff_switch.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_if_tariff_switch.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_time_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_timer_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_timer_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_tone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\cap_v2_variable_part.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\cap_v2_lrf.asn
# End Source File
# End Target
# End Project
