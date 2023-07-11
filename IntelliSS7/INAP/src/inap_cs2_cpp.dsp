# Microsoft Developer Studio Project File - Name="inap_cs2_cpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=inap_cs2_cpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "inap_cs2_cpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "inap_cs2_cpp.mak" CFG="inap_cs2_cpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "inap_cs2_cpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "inap_cs2_cpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "inap_cs2_cpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\INAP-CS2++.lib"

!ELSEIF  "$(CFG)" == "inap_cs2_cpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "inap_cs2_cpp_Win32_Debug"
# PROP Intermediate_Dir "inap_cs2_cpp_Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Od /I "." /I "..\include\itu" /I "..\..\common\include" /I "..\..\common\include\asn-cpp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\INAP-CS2++D.lib"

!ENDIF 

# Begin Target

# Name "inap_cs2_cpp - Win32 Release"
# Name "inap_cs2_cpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\inap_cpp.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_a_ch_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_access_code.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_account_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_action_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_action_performed.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_actions.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_activable_services.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_activate_service_filtering_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_additional_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_alerting_pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_analyse_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_analysed_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_application_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_apply_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_apply_charging_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_assist_request_instructions_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_assisting_sspip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_attribute_error.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_attribute_error_problem.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_attribute_problem.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_attribute_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_attribute_type_and_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_attribute_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_authorize_termination_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_backward_gvns.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_backward_service_interaction_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_basic_service.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_bcsm_event.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_bcusm_event.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_bearer_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_bearer_capability.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_bothway_through_connection_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_conditions.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_gap_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_information_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_information_request_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_processing_operation_correlation_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_record.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_result.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_segment_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_call_unrelated_dp_specific_common_parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_called_party_business_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_called_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_called_party_subaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_calling_party_business_group_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_calling_party_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_calling_party_subaddress.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_calling_partys_category.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_cancel_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_cancel_status_report_request_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_carrier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_cause_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_cg_encountered.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_charge_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_charging_event.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_charging_parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_collect_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_collected_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_collected_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_collected_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_component_correlation_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_component_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_connect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_connect_to_resource_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_connected_number_treatment_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_constraints.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_continue_with_argument_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_control_condition_by_call_party.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_control_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_correlation_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_counter_and_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_counter_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_counters_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_credit.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_credit_unit.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_criticality_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_csaid.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_currency_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_currency_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_cut_and_paste.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_date_and_time.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_destination_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_disconnect_forward_connection_with_argument_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_disconnect_leg_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_display_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_dp_specific_common_parameters.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_dp_specific_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_duration.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_elementary_message_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_entity_released_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_entry.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_error_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_establish_temporary_connection_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_notification_charging_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_report_bcsm_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_report_facility_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_specific_information_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_specific_information_charging.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_type_bcsm.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_type_bcusm.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_event_type_charging.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_execute_argument.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_execute_result.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_execution_error.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_execution_problem.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_extension_field.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_facility_group.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_facility_group_member.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_facility_selected_and_available_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_failure_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_fci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_feature_code.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_feature_request_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_filtered_call_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_filtering_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_filtering_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_filtering_time_out.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_forward_call_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_forward_gvns.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_forward_service_interaction_ind.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_forwarding_condition.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_furnish_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_gap_criteria.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_gap_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_gap_on_service.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_gap_treatment.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_generic_name.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_generic_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_generic_numbers.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_grants_and_denials.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_high_layer_compatibilities.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_high_layer_compatibility.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_hold_call_in_network_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_hold_cause.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_in_service_compatibility_indication.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_in_service_compatibility_response.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_inband_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_info_to_send.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_info_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_information_to_record.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_information_to_send.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_initial_dp_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_initiate_call_attempt_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_integer4.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_interaction_strategy.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_interval.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_invokable_service.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_invoke_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_ip_available.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_ip_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_ipssp_capabilities.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_isdn_access_related_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_language.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_leg_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_leg_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_location_number.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_mail_box_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_manage_trigger_data_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_manage_trigger_data_result_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_maximum_number_of_counters.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_media.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_merge_call_segments_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_message.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_message_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_message_received_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_mid_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_mid_call_control_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_mid_call_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_mid_call_info_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_misc_call_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_monitor_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_move_call_segments_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_move_leg_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_name.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_name_error.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_name_problem.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_notification.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_notification_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_number_match.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_number_of_digits.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_numbering_plan.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_o_abandon_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_o_answer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_o_called_party_busy_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_o_disconnect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_o_no_answer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_o_suspended_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_operation_code.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_original_called_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_origination_attempt_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_origination_attempt_authorized_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_play_announcement_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_profile_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_prompt_and_collect_user_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_prompt_and_receive_message_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_rdn_sequence.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_reason.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_received_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_received_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_received_status.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_reconnect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_recorded_message_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_redirecting_party_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_redirection_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_registrator_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_relative_distinguished_name.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_release_call_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_report_condition.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_report_utsi_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_current_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_current_status_report_result_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_every_status_change_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_first_status_match_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_notification_charging_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_report_bcsm_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_report_facility_event_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_request_report_utsi_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_information_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_information_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_information_type_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_information_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_notifications.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_utsi.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_requested_utsi_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_reset_timer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_resource_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_resource_status.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_response_condition.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_route_list.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_route_select_failure_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_routing_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_scf_address.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_scf_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_sci_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_select_facility_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_select_route_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_send_charging_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_send_facility_information_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_send_stui_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_service_address_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_service_filtering_response_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_service_interaction_indicators.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_service_interaction_indicators_two.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_service_key.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_service_profile_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_serving_area_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_sf_billing_charging_characteristics.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_specific_input.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_specific_output.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_split_leg_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_status_report_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_subscriber_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_supplementary_services.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_suspend_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_t_answer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_t_busy_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_t_disconnect_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_t_no_answer_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_t_suspended_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_target_line_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_term_attempt_authorized_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_terminal_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_termination_attempt_arg.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_timer_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_timer_value.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_tone.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_tone_id.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_trace_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_trace_item.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_travelling_class_mark.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_trigger_data_identifier.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_trigger_type.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_unavailable_network_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_user_credit.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_user_info.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_user_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_user_interaction_modes.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_usi_information.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_usi_monitor_mode.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_usi_service_indicator.cpp
# End Source File
# Begin Source File

SOURCE=.\inap_cs2_variable_part.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\itu\inap_cpp.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_a_ch_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_access_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_account_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_action_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_action_performed.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_actions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_activable_services.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_activate_service_filtering_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_additional_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_alerting_pattern.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_analyse_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_analysed_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_application_timer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_apply_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_apply_charging_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_assist_request_instructions_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_assisting_sspip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_attribute_error.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_attribute_error_problem.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_attribute_problem.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_attribute_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_attribute_type_and_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_attribute_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_authorize_termination_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_backward_gvns.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_backward_service_interaction_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_basic_service.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_bcsm_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_bcusm_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_bearer_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_bearer_capability.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_bothway_through_connection_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_conditions.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_gap_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_information_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_information_request_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_processing_operation_correlation_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_record.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_segment_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_call_unrelated_dp_specific_common_parameters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_called_party_business_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_called_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_called_party_subaddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_calling_party_business_group_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_calling_party_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_calling_party_subaddress.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_calling_partys_category.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_cancel_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_cancel_status_report_request_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_carrier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_cause_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_cg_encountered.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_charge_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_charging_event.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_charging_parameters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_collect_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_collected_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_collected_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_collected_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_component_correlation_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_component_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_connect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_connect_to_resource_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_connected_number_treatment_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_constraints.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_continue_with_argument_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_control_condition_by_call_party.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_control_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_correlation_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_counter_and_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_counter_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_counters_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_credit.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_credit_unit.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_criticality_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_csaid.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_currency_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_currency_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_cut_and_paste.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_date_and_time.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_destination_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_disconnect_forward_connection_with_argument_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_disconnect_leg_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_display_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_dp_specific_common_parameters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_dp_specific_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_duration.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_elementary_message_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_entity_released_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_entry.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_error_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_establish_temporary_connection_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_notification_charging_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_report_bcsm_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_report_facility_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_specific_information_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_specific_information_charging.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_type_bcsm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_type_bcusm.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_event_type_charging.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_execute_argument.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_execute_result.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_execution_error.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_execution_problem.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_extension_field.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_facility_group.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_facility_group_member.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_facility_selected_and_available_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_failure_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_fci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_feature_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_feature_request_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_filtered_call_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_filtering_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_filtering_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_filtering_time_out.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_forward_call_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_forward_gvns.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_forward_service_interaction_ind.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_forwarding_condition.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_furnish_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_gap_criteria.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_gap_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_gap_on_service.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_gap_treatment.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_generic_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_generic_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_generic_numbers.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_grants_and_denials.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_high_layer_compatibilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_high_layer_compatibility.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_hold_call_in_network_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_hold_cause.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_in_service_compatibility_indication.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_in_service_compatibility_response.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_inband_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_info_to_send.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_info_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_information_to_record.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_information_to_send.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_initial_dp_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_initiate_call_attempt_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_integer4.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_interaction_strategy.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_interval.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_invokable_service.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_invoke_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_ip_available.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_ip_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_ipssp_capabilities.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_isdn_access_related_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_language.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_leg_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_leg_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_location_number.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_mail_box_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_manage_trigger_data_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_manage_trigger_data_result_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_maximum_number_of_counters.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_media.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_merge_call_segments_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_message.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_message_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_message_received_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_mid_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_mid_call_control_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_mid_call_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_mid_call_info_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_misc_call_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_monitor_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_move_call_segments_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_move_leg_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_name_error.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_name_problem.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_notification.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_notification_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_number_match.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_number_of_digits.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_numbering_plan.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_o_abandon_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_o_answer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_o_called_party_busy_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_o_disconnect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_o_no_answer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_o_suspended_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_operation_code.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_original_called_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_origination_attempt_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_origination_attempt_authorized_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_play_announcement_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_profile_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_prompt_and_collect_user_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_prompt_and_receive_message_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_rdn_sequence.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_reason.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_received_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_received_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_received_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_reconnect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_recorded_message_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_redirecting_party_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_redirection_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_registrator_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_relative_distinguished_name.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_release_call_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_report_condition.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_report_utsi_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_current_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_current_status_report_result_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_every_status_change_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_first_status_match_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_notification_charging_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_report_bcsm_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_report_facility_event_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_request_report_utsi_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_information_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_information_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_information_type_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_information_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_notifications.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_utsi.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_requested_utsi_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_reset_timer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_resource_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_resource_status.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_response_condition.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_route_list.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_route_select_failure_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_routing_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_scf_address.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_scf_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_sci_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_select_facility_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_select_route_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_send_charging_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_send_facility_information_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_send_stui_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_service_address_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_service_filtering_response_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_service_interaction_indicators.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_service_interaction_indicators_two.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_service_key.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_service_profile_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_serving_area_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_sf_billing_charging_characteristics.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_specific_input.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_specific_output.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_split_leg_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_status_report_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_subscriber_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_supplementary_services.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_suspend_timer.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_t_answer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_t_busy_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_t_disconnect_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_t_no_answer_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_t_suspended_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_target_line_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_term_attempt_authorized_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_terminal_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_termination_attempt_arg.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_timer_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_timer_value.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_tone.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_tone_id.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_trace_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_trace_item.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_travelling_class_mark.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_trigger_data_identifier.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_trigger_type.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_unavailable_network_resource.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_user_credit.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_user_info.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_user_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_user_interaction_modes.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_usi_information.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_usi_monitor_mode.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_usi_service_indicator.h
# End Source File
# Begin Source File

SOURCE=..\include\itu\inap_cs2_variable_part.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\inap_cs2_lrf.asn

!IF  "$(CFG)" == "inap_cs2_cpp - Win32 Release"

# Begin Custom Build
InputPath=.\inap_cs2_lrf.asn

".\inap_cs2_access_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace inap_cs2 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn inap_cs2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "inap_cs2_cpp - Win32 Debug"

# Begin Custom Build - Compiling ASN.1 file...
InputPath=.\inap_cs2_lrf.asn

".\inap_cs2_access_code.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ITS_ROOT)\tools\bin\asncc_v2 -explicitChoice -cpp -cppNamespace inap_cs2 -xmlCppDoc -u $(ITS_ROOT)\tools\bin\asncc_useful.asn inap_cs2_lrf.asn 
	copy *.h ..\include\itu 
	del *.h 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
