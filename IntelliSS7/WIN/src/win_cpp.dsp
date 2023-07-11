# Microsoft Developer Studio Project File - Name="win_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=win_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "win_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "win_cpp.mak" CFG="win_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "win_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "win_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "win_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "win_cpp_Win32_Release"
# PROP Intermediate_Dir "win_cpp_Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include\ansi" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\WIN++.lib"

!ELSEIF  "$(CFG)" == "win_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "win_cpp_Win32_Debug"
# PROP Intermediate_Dir "win_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Od /I "..\include\ansi" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# SUBTRACT CPP /Z<none>
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\WIN++D.lib"

!ENDIF 

# Begin Target

# Name "win_cpp - Win32 Release"
# Name "win_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\win_access_denied_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\win_action_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_alert_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_all_or_none.cpp
# End Source File
# Begin Source File

SOURCE=.\win_analyzed_information_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_analyzed_information_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_announcement_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_announcement_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_availability_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_billing_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_border_cell_access.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_digits1.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_digits2.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_name.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_number_digits1.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_number_digits2.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_number_string1.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_number_string2.cpp
# End Source File
# Begin Source File

SOURCE=.\win_calling_party_subaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\win_carrier_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_cdma_private_long_code_mask.cpp
# End Source File
# Begin Source File

SOURCE=.\win_cdma_slot_cycle_index.cpp
# End Source File
# Begin Source File

SOURCE=.\win_cdma_station_class_mark.cpp
# End Source File
# Begin Source File

SOURCE=.\win_change.cpp
# End Source File
# Begin Source File

SOURCE=.\win_conditionally_denied_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\win_conference_calling_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_connect_resource_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_connection_failure_report_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_control_channel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_access_element.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_access_element_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_base_key.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_result.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_update_result.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_update_result_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_data_value.cpp
# End Source File
# Begin Source File

SOURCE=.\win_destination_address.cpp
# End Source File
# Begin Source File

SOURCE=.\win_destination_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_digit_collection_control.cpp
# End Source File
# Begin Source File

SOURCE=.\win_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_digits_carrier.cpp
# End Source File
# Begin Source File

SOURCE=.\win_digits_destination.cpp
# End Source File
# Begin Source File

SOURCE=.\win_display_text.cpp
# End Source File
# Begin Source File

SOURCE=.\win_dmh_account_code_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_dmh_alternate_billing_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_dmh_billing_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_dmh_redirection_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_electronic_serial_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_execute_script.cpp
# End Source File
# Begin Source File

SOURCE=.\win_extended_mscid.cpp
# End Source File
# Begin Source File

SOURCE=.\win_extended_system_my_type_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_facility_selected_and_available_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_facility_selected_and_available_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\win_failure_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_feature_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_feature_request_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_feature_result.cpp
# End Source File
# Begin Source File

SOURCE=.\win_global_title.cpp
# End Source File
# Begin Source File

SOURCE=.\win_group_information.cpp
# End Source File
# Begin Source File

SOURCE=.\win_inter_msc_circuit_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_inter_system_page_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_inter_system_setup_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_intersystem_termination.cpp
# End Source File
# Begin Source File

SOURCE=.\win_leg_information.cpp
# End Source File
# Begin Source File

SOURCE=.\win_local_termination.cpp
# End Source File
# Begin Source File

SOURCE=.\win_location_area_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_location_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_location_request_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_mobile_directory_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_mobile_identification_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_modification_request.cpp
# End Source File
# Begin Source File

SOURCE=.\win_modification_request_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_modification_result.cpp
# End Source File
# Begin Source File

SOURCE=.\win_modification_result_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_modify_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_modify_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_msc_identification_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_mscid.cpp
# End Source File
# Begin Source File

SOURCE=.\win_mscin.cpp
# End Source File
# Begin Source File

SOURCE=.\win_no_answer_time.cpp
# End Source File
# Begin Source File

SOURCE=.\win_one_time_feature_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_origination_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_origination_request_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_origination_triggers.cpp
# End Source File
# Begin Source File

SOURCE=.\win_paca_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_page_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_pc_ssn.cpp
# End Source File
# Begin Source File

SOURCE=.\win_pilot_billing_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_pilot_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_preferred_language_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_private_specialized_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\win_pstn_termination.cpp
# End Source File
# Begin Source File

SOURCE=.\win_qualification_information_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_qualification_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_received_signal_quality.cpp
# End Source File
# Begin Source File

SOURCE=.\win_redirecting_number_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_redirecting_number_string.cpp
# End Source File
# Begin Source File

SOURCE=.\win_redirecting_party_name.cpp
# End Source File
# Begin Source File

SOURCE=.\win_redirecting_subaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\win_redirection_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\win_registration_notification_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_report_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_resume_pic.cpp
# End Source File
# Begin Source File

SOURCE=.\win_routing_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\win_routing_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_script_argument.cpp
# End Source File
# Begin Source File

SOURCE=.\win_script_name.cpp
# End Source File
# Begin Source File

SOURCE=.\win_script_result.cpp
# End Source File
# Begin Source File

SOURCE=.\win_search_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_search_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_seize_resource_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_seize_resource_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_sender_identification_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_data_access_element.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_data_access_element_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_data_result.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_data_result_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_service_request_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_serving_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_signal_quality.cpp
# End Source File
# Begin Source File

SOURCE=.\win_signaling_message_encryption_key.cpp
# End Source File
# Begin Source File

SOURCE=.\win_sms_address.cpp
# End Source File
# Begin Source File

SOURCE=.\win_sms_message_waiting_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_specialized_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\win_spini_triggers.cpp
# End Source File
# Begin Source File

SOURCE=.\win_spinipin.cpp
# End Source File
# Begin Source File

SOURCE=.\win_srf_directive_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_srf_directive_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_ssd_not_shared.cpp
# End Source File
# Begin Source File

SOURCE=.\win_ssd_update_report.cpp
# End Source File
# Begin Source File

SOURCE=.\win_station_class_mark.cpp
# End Source File
# Begin Source File

SOURCE=.\win_system_access_data.cpp
# End Source File
# Begin Source File

SOURCE=.\win_system_access_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_system_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\win_system_my_type_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_t_busy_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_t_no_answer_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_t_no_answer_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_target_cell_id.cpp
# End Source File
# Begin Source File

SOURCE=.\win_target_measurement_information.cpp
# End Source File
# Begin Source File

SOURCE=.\win_target_measurement_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_tbusy_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_tdma_burst_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_tdma_call_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\win_tdma_channel_data.cpp
# End Source File
# Begin Source File

SOURCE=.\win_terminal_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_termination_access_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_termination_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_termination_restriction_code.cpp
# End Source File
# Begin Source File

SOURCE=.\win_termination_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\win_termination_triggers.cpp
# End Source File
# Begin Source File

SOURCE=.\win_time_date_offset.cpp
# End Source File
# Begin Source File

SOURCE=.\win_transaction_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\win_transfer_to_number_request_il.cpp
# End Source File
# Begin Source File

SOURCE=.\win_trigger_address_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_trigger_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\win_trigger_list.cpp
# End Source File
# Begin Source File

SOURCE=.\win_trigger_type.cpp
# End Source File
# Begin Source File

SOURCE=.\win_trunk_status.cpp
# End Source File
# Begin Source File

SOURCE=.\win_unsolicited_response_rrl.cpp
# End Source File
# Begin Source File

SOURCE=.\win_update_count.cpp
# End Source File
# Begin Source File

SOURCE=.\win_usage_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\win_voice_mailbox_number.cpp
# End Source File
# Begin Source File

SOURCE=.\win_voice_mailbox_pin.cpp
# End Source File
# Begin Source File

SOURCE=.\win_voice_privacy_mask.cpp
# End Source File
# Begin Source File

SOURCE=.\win_win_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\win_win_operations_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\win_win_trigger_list.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\ansi\win_access_denied_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_action_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_alert_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_all_or_none.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_analyzed_information_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_analyzed_information_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_announcement_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_announcement_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_availability_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_billing_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_border_cell_access.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_digits1.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_digits2.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_name.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_number_digits1.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_number_digits2.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_number_string1.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_number_string2.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_calling_party_subaddress.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_carrier_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_cdma_private_long_code_mask.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_cdma_slot_cycle_index.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_cdma_station_class_mark.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_change.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_conditionally_denied_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_conference_calling_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_connect_resource_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_connection_failure_report_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_control_channel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_access_element.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_access_element_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_base_key.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_result.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_update_result.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_update_result_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_data_value.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_destination_address.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_destination_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_digit_collection_control.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_digits_carrier.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_digits_destination.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_display_text.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_dmh_account_code_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_dmh_alternate_billing_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_dmh_billing_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_dmh_redirection_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_electronic_serial_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_execute_script.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_extended_mscid.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_extended_system_my_type_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_facility_selected_and_available_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_facility_selected_and_available_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_failure_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_feature_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_feature_request_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_feature_result.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_global_title.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_group_information.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_inter_msc_circuit_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_inter_system_page_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_inter_system_setup_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_intersystem_termination.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_leg_information.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_local_termination.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_location_area_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_location_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_location_request_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_mobile_directory_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_mobile_identification_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_modification_request.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_modification_request_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_modification_result.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_modification_result_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_modify_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_modify_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_msc_identification_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_mscid.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_mscin.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_no_answer_time.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_one_time_feature_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_origination_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_origination_request_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_origination_triggers.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_paca_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_page_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_pc_ssn.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_pilot_billing_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_pilot_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_preferred_language_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_private_specialized_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_pstn_termination.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_qualification_information_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_qualification_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_received_signal_quality.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_redirecting_number_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_redirecting_number_string.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_redirecting_party_name.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_redirecting_subaddress.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_redirection_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_registration_notification_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_report_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_resume_pic.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_routing_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_routing_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_script_argument.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_script_name.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_script_result.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_search_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_search_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_seize_resource_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_seize_resource_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_sender_identification_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_data_access_element.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_data_access_element_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_data_result.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_data_result_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_service_request_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_serving_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_signal_quality.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_signaling_message_encryption_key.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_sms_address.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_sms_message_waiting_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_specialized_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_spini_triggers.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_spinipin.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_srf_directive_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_srf_directive_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_ssd_not_shared.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_ssd_update_report.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_station_class_mark.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_system_access_data.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_system_access_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_system_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_system_my_type_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_t_busy_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_t_no_answer_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_t_no_answer_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_target_cell_id.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_target_measurement_information.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_target_measurement_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_tbusy_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_tdma_burst_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_tdma_call_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_tdma_channel_data.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_terminal_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_termination_access_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_termination_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_termination_restriction_code.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_termination_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_termination_triggers.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_time_date_offset.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_transaction_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_transfer_to_number_request_il.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_trigger_address_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_trigger_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_trigger_list.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_trigger_type.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_trunk_status.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_unsolicited_response_rrl.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_update_count.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_usage_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_voice_mailbox_number.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_voice_mailbox_pin.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_voice_privacy_mask.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_win_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_win_operations_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\ansi\win_win_trigger_list.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\win_lrf.asn

!IF  "$(CFG)" == "win_cpp - Win32 Release"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\win_lrf.asn

".\win_access_denied_reason.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -f -explicitChoice -cpp -cppNamespace win -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn win_lrf.asn 
	copy *.h ..\include\ansi 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "win_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\win_lrf.asn

".\win_access_denied_reason.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -f -explicitChoice -cpp -cppNamespace win -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn win_lrf.asn 
	copy *.h ..\include\ansi 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
