////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: cap_asncc_codec.cpp,v 9.1 2005/03/23 12:51:15 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <its++.h>

#include <iostream>

#include <cap_asncc_codec.h>

#include <Asn.h>
#include <AsnException.h>


#include <cap_v3_a_ch_billing_charging_characteristics.h>
#include <cap_v3_access_point_name.h>
#include <cap_v3_activity_test_gprs_arg.h>
#include <cap_v3_additional_calling_party_number.h>
#include <cap_v3_age_of_location_information.h>
#include <cap_v3_alerting_pattern.h>
#include <cap_v3_aoc_before_answer.h>
#include <cap_v3_aoc_subsequent.h>
#include <cap_v3_aocgprs.h>
#include <cap_v3_append_free_format_data.h>
#include <cap_v3_application_timer.h>
#include <cap_v3_apply_charging_arg.h>
#include <cap_v3_apply_charging_gprs_arg.h>
#include <cap_v3_apply_charging_report_arg.h>
#include <cap_v3_apply_charging_report_gprs_arg.h>
#include <cap_v3_assist_request_instructions_arg.h>
#include <cap_v3_assisting_sspip_routing_address.h>
#include <cap_v3_backward_service_interaction_ind.h>
#include <cap_v3_bcsm_event.h>
#include <cap_v3_bearer_capability.h>
#include <cap_v3_bothway_through_connection_ind.h>
#include <cap_v3_cai_gsm0224.h>
#include <cap_v3_call_gap_arg.h>
#include <cap_v3_call_information_report_arg.h>
#include <cap_v3_call_information_request_arg.h>
#include <cap_v3_call_reference_number.h>
#include <cap_v3_call_result.h>
#include <cap_v3_called_party_bcd_number.h>
#include <cap_v3_called_party_number.h>
#include <cap_v3_calling_party_number.h>
#include <cap_v3_calling_partys_category.h>
#include <cap_v3_camel_a_ch_billing_charging_characteristics.h>
#include <cap_v3_camel_call_result.h>
#include <cap_v3_camel_fci_billing_charging_characteristics.h>
#include <cap_v3_camel_fcigprs_billing_charging_characteristics.h>
#include <cap_v3_camel_fcisms_billing_charging_characteristics.h>
#include <cap_v3_camel_sci_billing_charging_characteristics.h>
#include <cap_v3_camel_scigprs_billing_charging_characteristics.h>
#include <cap_v3_cancel_arg.h>
#include <cap_v3_cancel_failed.h>
#include <cap_v3_cancel_gprs_arg.h>
#include <cap_v3_cause.h>
#include <cap_v3_cell_global_id_or_service_area_id_fixed_length.h>
#include <cap_v3_cell_global_id_or_service_area_id_or_lai.h>
#include <cap_v3_cg_encountered.h>
#include <cap_v3_charging_characteristics.h>
#include <cap_v3_charging_result.h>
#include <cap_v3_collected_digits.h>
#include <cap_v3_collected_info.h>
#include <cap_v3_connect_arg.h>
#include <cap_v3_connect_arg_extension.h>
#include <cap_v3_connect_gprs_arg.h>
#include <cap_v3_connect_sms_arg.h>
#include <cap_v3_connect_to_resource_arg.h>
#include <cap_v3_connected_number_treatment_ind.h>
#include <cap_v3_continue_gprs_arg.h>
#include <cap_v3_continue_with_argument_arg.h>
#include <cap_v3_continue_with_argument_arg_extension.h>
#include <cap_v3_control_type.h>
#include <cap_v3_correlation_id.h>
#include <cap_v3_criticality_type.h>
#include <cap_v3_cug_index.h>
#include <cap_v3_cug_interlock.h>
#include <cap_v3_date_and_time.h>
#include <cap_v3_destination_routing_address.h>
#include <cap_v3_digits.h>
#include <cap_v3_dp_specific_criteria.h>
#include <cap_v3_duration.h>
#include <cap_v3_elapsed_time.h>
#include <cap_v3_entity_released_gprs_arg.h>
#include <cap_v3_error_treatment.h>
#include <cap_v3_establish_temporary_connection_arg.h>
#include <cap_v3_event_report_bcsm_arg.h>
#include <cap_v3_event_report_gprs_arg.h>
#include <cap_v3_event_report_sms_arg.h>
#include <cap_v3_event_specific_information_bcsm.h>
#include <cap_v3_event_specific_information_sms.h>
#include <cap_v3_event_type_bcsm.h>
#include <cap_v3_event_type_sms.h>
#include <cap_v3_ext_basic_service_code.h>
#include <cap_v3_ext_bearer_service_code.h>
#include <cap_v3_ext_teleservice_code.h>
#include <cap_v3_extension_container.h>
#include <cap_v3_extension_field.h>
#include <cap_v3_fci_billing_charging_characteristics.h>
#include <cap_v3_fcigprs_billing_charging_characteristics.h>
#include <cap_v3_fcisms_billing_charging_characteristics.h>
#include <cap_v3_forward_service_interaction_ind.h>
#include <cap_v3_furnish_charging_information_arg.h>
#include <cap_v3_furnish_charging_information_gprs_arg.h>
#include <cap_v3_furnish_charging_information_sms_arg.h>
#include <cap_v3_gap_criteria.h>
#include <cap_v3_gap_indicators.h>
#include <cap_v3_gap_on_service.h>
#include <cap_v3_gap_treatment.h>
#include <cap_v3_generic_number.h>
#include <cap_v3_generic_numbers.h>
#include <cap_v3_geodetic_information.h>
#include <cap_v3_geographical_information.h>
#include <cap_v3_gprs_cause.h>
#include <cap_v3_gprs_charging_id.h>
#include <cap_v3_gprs_event.h>
#include <cap_v3_gprs_event_specific_information.h>
#include <cap_v3_gprs_event_type.h>
#include <cap_v3_gprs_reference_number.h>
#include <cap_v3_gprsms_class.h>
#include <cap_v3_high_layer_compatibility.h>
#include <cap_v3_imsi.h>
#include <cap_v3_inband_info.h>
#include <cap_v3_information_to_send.h>
#include <cap_v3_initial_dp_arg.h>
#include <cap_v3_initial_dp_arg_extension.h>
#include <cap_v3_initial_dpgprs_arg.h>
#include <cap_v3_initial_dpsms_arg.h>
#include <cap_v3_initiating_entity.h>
#include <cap_v3_integer4.h>
#include <cap_v3_interval.h>
#include <cap_v3_invoke_id.h>
#include <cap_v3_ip_routing_address.h>
#include <cap_v3_ipssp_capabilities.h>
#include <cap_v3_isdn_address_string.h>
#include <cap_v3_lai_fixed_length.h>
#include <cap_v3_leg_id.h>
#include <cap_v3_leg_type.h>
#include <cap_v3_location_information.h>
#include <cap_v3_location_information_gprs.h>
#include <cap_v3_location_number.h>
#include <cap_v3_lsa_identity.h>
#include <cap_v3_message_id.h>
#include <cap_v3_misc_call_info.h>
#include <cap_v3_monitor_mode.h>
#include <cap_v3_ms_network_capability.h>
#include <cap_v3_ms_radio_access_capability.h>
#include <cap_v3_na_carrier_information.h>
#include <cap_v3_na_carrier_selection_info.h>
#include <cap_v3_na_charge_number.h>
#include <cap_v3_na_info.h>
#include <cap_v3_na_oli_info.h>
#include <cap_v3_naea_cic.h>
#include <cap_v3_not_reachable_reason.h>
#include <cap_v3_ocsi_applicable.h>
#include <cap_v3_original_called_party_id.h>
#include <cap_v3_pcs_extensions.h>
#include <cap_v3_pdp_type.h>
#include <cap_v3_pdpid.h>
#include <cap_v3_play_announcement_arg.h>
#include <cap_v3_private_extension.h>
#include <cap_v3_private_extension_list.h>
#include <cap_v3_prompt_and_collect_user_information_arg.h>
#include <cap_v3_quality_of_service.h>
#include <cap_v3_ra_identity.h>
#include <cap_v3_received_information_arg.h>
#include <cap_v3_receiving_side_id.h>
#include <cap_v3_redirecting_party_id.h>
#include <cap_v3_redirection_information.h>
#include <cap_v3_release_call_arg.h>
#include <cap_v3_release_gprs_arg.h>
#include <cap_v3_release_sms_arg.h>
#include <cap_v3_request_report_bcsm_event_arg.h>
#include <cap_v3_request_report_gprs_event_arg.h>
#include <cap_v3_request_report_sms_event_arg.h>
#include <cap_v3_requested_info_error.h>
#include <cap_v3_requested_information.h>
#include <cap_v3_requested_information_list.h>
#include <cap_v3_requested_information_type.h>
#include <cap_v3_requested_information_type_list.h>
#include <cap_v3_requested_information_value.h>
#include <cap_v3_reset_timer_arg.h>
#include <cap_v3_reset_timer_gprs_arg.h>
#include <cap_v3_reset_timer_sms_arg.h>
#include <cap_v3_rp_cause.h>
#include <cap_v3_scf_id.h>
#include <cap_v3_sci_billing_charging_characteristics.h>
#include <cap_v3_scigprs_billing_charging_characteristics.h>
#include <cap_v3_send_charging_information_arg.h>
#include <cap_v3_send_charging_information_gprs_arg.h>
#include <cap_v3_sending_side_id.h>
#include <cap_v3_service_interaction_indicators_two.h>
#include <cap_v3_service_key.h>
#include <cap_v3_sgsn_capabilities.h>
#include <cap_v3_sms_cause.h>
#include <cap_v3_sms_event.h>
#include <cap_v3_specialized_resource_report_arg.h>
#include <cap_v3_subscriber_state.h>
#include <cap_v3_suppression_of_announcement.h>
#include <cap_v3_task_refused.h>
#include <cap_v3_tc_invoke_id_set.h>
#include <cap_v3_time_and_timezone.h>
#include <cap_v3_time_if_no_tariff_switch.h>
#include <cap_v3_time_if_tariff_switch.h>
#include <cap_v3_time_information.h>
#include <cap_v3_timer_id.h>
#include <cap_v3_timer_value.h>
#include <cap_v3_tone.h>
#include <cap_v3_tp_data_coding_scheme.h>
#include <cap_v3_tp_protocol_identifier.h>
#include <cap_v3_tp_short_message_submission_info.h>
#include <cap_v3_tp_validity_period.h>
#include <cap_v3_transferred_volume.h>
#include <cap_v3_unavailable_network_resource.h>
#include <cap_v3_variable_part.h>

using namespace std;
using namespace its;
using namespace cap_v3;


int 
AsnCC_EncodeApplyChargingArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ApplyChargingArg* applyChargingArg = reinterpret_cast<ApplyChargingArg *>(data);

    try 
    {
    	octets = applyChargingArg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete applyChargingArg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeApplyChargingArg(unsigned char* encoded, size_t size, void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ApplyChargingArg* applyChargingArg = new ApplyChargingArg();

    try 
    {
	    applyChargingArg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *applyChargingArg;

    delete octets;

    *data = applyChargingArg;

    return ITS_SUCCESS;
}



int 
AsnCC_EncodeCAMEL_AChBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_AChBillingChargingCharacteristics* achbillChargingArg = reinterpret_cast<CAMEL_AChBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = achbillChargingArg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete achbillChargingArg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_AChBillingChargingCharacteristics(
                                               unsigned char* encoded, 
                                               size_t size, 
                                               void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_AChBillingChargingCharacteristics* achbillChargingArg = new CAMEL_AChBillingChargingCharacteristics();

    try 
    {
	    achbillChargingArg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *achbillChargingArg;

    delete octets;

    *data = achbillChargingArg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeCAMEL_CallResult(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_CallResult* callresult = reinterpret_cast<CAMEL_CallResult *>(data);

    try 
    {
    	octets = callresult->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete callresult;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_CallResult(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_CallResult* callresult = new CAMEL_CallResult();

    try 
    {
	    callresult->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *callresult;

    delete octets;

    *data = callresult;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeCAMEL_FCIBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_FCIBillingChargingCharacteristics* fcibillCharging = reinterpret_cast<CAMEL_FCIBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = fcibillCharging->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete fcibillCharging;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_FCIBillingChargingCharacteristics(
                                               unsigned char* encoded, 
                                               size_t size, 
                                               void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_FCIBillingChargingCharacteristics* fcibillCharging = new CAMEL_FCIBillingChargingCharacteristics();

    try 
    {
	    fcibillCharging->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *fcibillCharging;

    delete octets;

    *data = fcibillCharging;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_FCIGPRSBillingChargingCharacteristics* fcigprsbill = reinterpret_cast<CAMEL_FCIGPRSBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = fcigprsbill->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete fcigprsbill;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_FCIGPRSBillingChargingCharacteristics(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_FCIGPRSBillingChargingCharacteristics* fcigprsbill = new CAMEL_FCIGPRSBillingChargingCharacteristics();

    try 
    {
	    fcigprsbill->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *fcigprsbill;

    delete octets;

    *data = fcigprsbill;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeCAMEL_FCISMSBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_FCISMSBillingChargingCharacteristics* fcismsbill = reinterpret_cast<CAMEL_FCISMSBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = fcismsbill->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete fcismsbill;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_FCISMSBillingChargingCharacteristics(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_FCISMSBillingChargingCharacteristics* fcismsbill = new CAMEL_FCISMSBillingChargingCharacteristics();

    try 
    {
	    fcismsbill->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *fcismsbill;

    delete octets;

    *data = fcismsbill;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeCAMEL_SCIBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_SCIBillingChargingCharacteristics* scismsbill = reinterpret_cast<CAMEL_SCIBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = scismsbill->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete scismsbill;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_SCIBillingChargingCharacteristics(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_SCIBillingChargingCharacteristics* scismsbill = new CAMEL_SCIBillingChargingCharacteristics();

    try 
    {
	    scismsbill->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *scismsbill;

    delete octets;

    *data = scismsbill;

    return ITS_SUCCESS;
}



int 
AsnCC_EncodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CAMEL_SCIGPRSBillingChargingCharacteristics* scigprbill = reinterpret_cast<CAMEL_SCIGPRSBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = scigprbill->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete scigprbill;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCAMEL_SCIGPRSBillingChargingCharacteristics(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CAMEL_SCIGPRSBillingChargingCharacteristics* scigprbill = new CAMEL_SCIGPRSBillingChargingCharacteristics();

    try 
    {
	    scigprbill->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *scigprbill;

    delete octets;

    *data = scigprbill;

    return ITS_SUCCESS;
}



int 
AsnCC_EncodeUnavailableNetworkResource(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	UnavailableNetworkResource* unavnetrsc = reinterpret_cast<UnavailableNetworkResource *>(data);

    try 
    {
    	octets = unavnetrsc->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete unavnetrsc;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeUnavailableNetworkResource(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    UnavailableNetworkResource* unavnetrsc = new UnavailableNetworkResource();

    try 
    {
	    unavnetrsc->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *unavnetrsc;

    delete octets;

    *data = unavnetrsc;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeCancelFailed(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CancelFailed* canfld = reinterpret_cast<CancelFailed *>(data);

    try 
    {
    	octets = canfld->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete canfld;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCancelFailed(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CancelFailed* canfld = new CancelFailed();

    try 
    {
	    canfld->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *canfld;

    delete octets;

    *data = canfld;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeRequestedInfoError(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	RequestedInfoError* rqinfer = reinterpret_cast<RequestedInfoError *>(data);

    try 
    {
    	octets = rqinfer->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete rqinfer;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeRequestedInfoError(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    RequestedInfoError* rqinfer = new RequestedInfoError();

    try 
    {
	    rqinfer->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *rqinfer;

    delete octets;

    *data = rqinfer;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeTaskRefused(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	RequestedInfoError* rqinfer = reinterpret_cast<RequestedInfoError *>(data);

    try 
    {
    	octets = rqinfer->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete rqinfer;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeTaskRefused(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    TaskRefused* rqinfer = new TaskRefused();

    try 
    {
	    rqinfer->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *rqinfer;

    delete octets;

    *data = rqinfer;

    return ITS_SUCCESS;
}




int 
AsnCC_EncodeApplyChargingReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CallResult* callres = reinterpret_cast<CallResult *>(data);

    try 
    {
    	octets = callres->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete callres;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeApplyChargingReportArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CallResult* callres = new CallResult();

    try 
    {
	    callres->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *callres;

    delete octets;

    *data = callres;

    return ITS_SUCCESS;
}






int 
AsnCC_EncodeAssistRequestInstructionsArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	AssistRequestInstructionsArg* asreinarg = reinterpret_cast<AssistRequestInstructionsArg *>(data);

    try 
    {
    	octets = asreinarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete asreinarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeAssistRequestInstructionsArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    AssistRequestInstructionsArg* asreinarg = new AssistRequestInstructionsArg();

    try 
    {
	    asreinarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *asreinarg;

    delete octets;

    *data = asreinarg;

    return ITS_SUCCESS;
}



int 
AsnCC_EncodeCallGapArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CallGapArg* callgaparg = reinterpret_cast<CallGapArg *>(data);

    try 
    {
    	octets = callgaparg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete callgaparg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCallGapArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CallGapArg* callgaparg = new CallGapArg();

    try 
    {
	    callgaparg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *callgaparg;

    delete octets;

    *data = callgaparg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeCallInformationReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CallInformationReportArg* callinfarg = reinterpret_cast<CallInformationReportArg *>(data);

    try 
    {
    	octets = callinfarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete callinfarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCallInformationReportArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CallInformationReportArg* callinfarg = new CallInformationReportArg();

    try 
    {
	    callinfarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *callinfarg;

    delete octets;

    *data = callinfarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeCallInformationRequestArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CallInformationRequestArg* callinfreqarg = reinterpret_cast<CallInformationRequestArg *>(data);

    try 
    {
    	octets = callinfreqarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete callinfreqarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCallInformationRequestArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CallInformationRequestArg* callinfreqarg = new CallInformationRequestArg();

    try 
    {
	    callinfreqarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *callinfreqarg;

    delete octets;

    *data = callinfreqarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeCancelArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CancelArg* cancelarg = reinterpret_cast<CancelArg *>(data);

    try 
    {
    	octets = cancelarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete cancelarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCancelArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CancelArg* cancelarg = new CancelArg();

    try 
    {
	    cancelarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *cancelarg;

    delete octets;

    *data = cancelarg;

    return ITS_SUCCESS;
}



int 
AsnCC_EncodeConnectArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ConnectArg* connectarg = reinterpret_cast<ConnectArg *>(data);

    try 
    {
    	octets = connectarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete connectarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeConnectArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ConnectArg* connectarg = new ConnectArg();

    try 
    {
	    connectarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *connectarg;

    delete octets;

    *data = connectarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeConnectToResourceArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ConnectToResourceArg* connectrscarg = reinterpret_cast<ConnectToResourceArg *>(data);

    try 
    {
    	octets = connectrscarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete connectrscarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeConnectToResourceArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ConnectToResourceArg* connectrscarg = new ConnectToResourceArg();

    try 
    {
	    connectrscarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *connectrscarg;

    delete octets;

    *data = connectrscarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeContinueWithArgumentArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ContinueWithArgumentArg* contarg = reinterpret_cast<ContinueWithArgumentArg *>(data);

    try 
    {
    	octets = contarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete contarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeContinueWithArgumentArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ContinueWithArgumentArg* contarg = new ContinueWithArgumentArg();

    try 
    {
	    contarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *contarg;

    delete octets;

    *data = contarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeEstablishTemporaryConnectionArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	EstablishTemporaryConnectionArg* esttemparg = reinterpret_cast<EstablishTemporaryConnectionArg *>(data);

    try 
    {
    	octets = esttemparg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete esttemparg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeEstablishTemporaryConnectionArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    EstablishTemporaryConnectionArg* esttemparg = new EstablishTemporaryConnectionArg();

    try 
    {
	    esttemparg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *esttemparg;

    delete octets;

    *data = esttemparg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeEventReportBCSMArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	EventReportBCSMArg* eventarg = reinterpret_cast<EventReportBCSMArg *>(data);

    try 
    {
    	octets = eventarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete eventarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeEventReportBCSMArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    EventReportBCSMArg* eventarg = new EventReportBCSMArg();

    try 
    {
	    eventarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *eventarg;

    delete octets;

    *data = eventarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeFurnishChargingInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	FCIBillingChargingCharacteristics* furchinfoarg = reinterpret_cast<FCIBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = furchinfoarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete furchinfoarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeFurnishChargingInformationArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    FCIBillingChargingCharacteristics* furchinfoarg = new FCIBillingChargingCharacteristics();

    try 
    {
	    furchinfoarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *furchinfoarg;

    delete octets;

    *data = furchinfoarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeInitialDPArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	InitialDPArg* initdparg = reinterpret_cast<InitialDPArg *>(data);

    try 
    {
    	octets = initdparg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete initdparg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeInitialDPArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    InitialDPArg* initdparg = new InitialDPArg();

    try 
    {
	    initdparg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *initdparg;

    delete octets;

    *data = initdparg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeReleaseCallArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	Cause* relscallparg = reinterpret_cast<Cause *>(data);

    try 
    {
    	octets = relscallparg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete relscallparg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeReleaseCallArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    Cause* relscallparg = new Cause();

    try 
    {
	    relscallparg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *relscallparg;

    delete octets;

    *data = relscallparg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeRequestReportBCSMEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	RequestReportBCSMEventArg* reqbcmsevparg = reinterpret_cast<RequestReportBCSMEventArg *>(data);

    try 
    {
    	octets = reqbcmsevparg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete reqbcmsevparg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeRequestReportBCSMEventArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    RequestReportBCSMEventArg* reqbcmsevparg = new RequestReportBCSMEventArg();

    try 
    {
	    reqbcmsevparg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *reqbcmsevparg;

    delete octets;

    *data = reqbcmsevparg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeResetTimerArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ResetTimerArg* resetarg = reinterpret_cast<ResetTimerArg *>(data);

    try 
    {
    	octets = resetarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete resetarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeResetTimerArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ResetTimerArg* resetarg = new ResetTimerArg();

    try 
    {
	    resetarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *resetarg;

    delete octets;

    *data = resetarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeSendChargingInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	SendChargingInformationArg* sendchinfoarg = reinterpret_cast<SendChargingInformationArg *>(data);

    try 
    {
    	octets = sendchinfoarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete sendchinfoarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeSendChargingInformationArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    SendChargingInformationArg* sendchinfoarg = new SendChargingInformationArg();

    try 
    {
	    sendchinfoarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *sendchinfoarg;

    delete octets;

    *data = sendchinfoarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodePlayAnnouncementArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	PlayAnnouncementArg* playarg = reinterpret_cast<PlayAnnouncementArg *>(data);

    try 
    {
    	octets = playarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete playarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodePlayAnnouncementArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    PlayAnnouncementArg* playarg = new PlayAnnouncementArg();

    try 
    {
	    playarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *playarg;

    delete octets;

    *data = playarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodePromptAndCollectUserInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	PromptAndCollectUserInformationArg* prmtcollctarg = reinterpret_cast<PromptAndCollectUserInformationArg *>(data);

    try 
    {
    	octets = prmtcollctarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete prmtcollctarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodePromptAndCollectUserInformationArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    PromptAndCollectUserInformationArg* prmtcollctarg = new PromptAndCollectUserInformationArg();

    try 
    {
	    prmtcollctarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *prmtcollctarg;

    delete octets;

    *data = prmtcollctarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeReceivedInformationArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ReceivedInformationArg* recdinfoarg = reinterpret_cast<ReceivedInformationArg *>(data);

    try 
    {
    	octets = recdinfoarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete recdinfoarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeReceivedInformationArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ReceivedInformationArg* recdinfoarg = new ReceivedInformationArg();

    try 
    {
	    recdinfoarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *recdinfoarg;

    delete octets;

    *data = recdinfoarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeSpecializedResourceReportArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	SpecializedResourceReportArg* specresarg = reinterpret_cast<SpecializedResourceReportArg *>(data);

    try 
    {
    	octets = specresarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete specresarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeSpecializedResourceReportArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    SpecializedResourceReportArg* specresarg = new SpecializedResourceReportArg();

    try 
    {
	    specresarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *specresarg;

    delete octets;

    *data = specresarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeConnectSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ConnectSMSArg* connectsmsarg = reinterpret_cast<ConnectSMSArg *>(data);

    try 
    {
    	octets = connectsmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete connectsmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeConnectSMSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ConnectSMSArg* connectsmsarg = new ConnectSMSArg();

    try 
    {
	    connectsmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *connectsmsarg;

    delete octets;

    *data = connectsmsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeEventReportSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	EventReportSMSArg* eventreptsmsarg = reinterpret_cast<EventReportSMSArg *>(data);

    try 
    {
    	octets = eventreptsmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete eventreptsmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeEventReportSMSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    EventReportSMSArg* eventreptsmsarg = new EventReportSMSArg();

    try 
    {
	    eventreptsmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *eventreptsmsarg;

    delete octets;

    *data = eventreptsmsarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeFurnishChargingInformationSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	FCISMSBillingChargingCharacteristics* furnishchinfosmsarg = reinterpret_cast<FCISMSBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = furnishchinfosmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete furnishchinfosmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeFurnishChargingInformationSMSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    FCISMSBillingChargingCharacteristics* furnishchinfosmsarg = new FCISMSBillingChargingCharacteristics();

    try 
    {
	    furnishchinfosmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *furnishchinfosmsarg;

    delete octets;

    *data = furnishchinfosmsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeInitialDPSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	InitialDPSMSArg* initialdpsmsarg = reinterpret_cast<InitialDPSMSArg *>(data);

    try 
    {
    	octets = initialdpsmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete initialdpsmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeInitialDPSMSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    InitialDPSMSArg* initialdpsmsarg = new InitialDPSMSArg();

    try 
    {
	    initialdpsmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *initialdpsmsarg;

    delete octets;

    *data = initialdpsmsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeReleaseSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	RPCause* releasesmsarg = reinterpret_cast<RPCause *>(data);

    try 
    {
    	octets = releasesmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete releasesmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeReleaseSMSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    RPCause* releasesmsarg = new RPCause();

    try 
    {
	    releasesmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *releasesmsarg;

    delete octets;

    *data = releasesmsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeRequestReportSMSEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	RequestReportSMSEventArg* reqreportsmsarg = reinterpret_cast<RequestReportSMSEventArg *>(data);

    try 
    {
    	octets = reqreportsmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete reqreportsmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeRequestReportSMSEventArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    RequestReportSMSEventArg* reqreportsmsarg = new RequestReportSMSEventArg();

    try 
    {
	    reqreportsmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *reqreportsmsarg;

    delete octets;

    *data = reqreportsmsarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeResetTimerSMSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ResetTimerSMSArg* resettimersmsarg = reinterpret_cast<ResetTimerSMSArg *>(data);

    try 
    {
    	octets = resettimersmsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete resettimersmsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeResetTimerSMSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ResetTimerSMSArg* resettimersmsarg = new ResetTimerSMSArg();

    try 
    {
	    resettimersmsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *resettimersmsarg;

    delete octets;

    *data = resettimersmsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeActivityTestGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ActivityTestGPRSArg* activitytestgprsarg = reinterpret_cast<ActivityTestGPRSArg *>(data);

    try 
    {
    	octets = activitytestgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete activitytestgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeActivityTestGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ActivityTestGPRSArg* activitytestgprsarg = new ActivityTestGPRSArg();

    try 
    {
	    activitytestgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *activitytestgprsarg;

    delete octets;

    *data = activitytestgprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeApplyChargingGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ApplyChargingGPRSArg* applycharginggprsarg = reinterpret_cast<ApplyChargingGPRSArg *>(data);

    try 
    {
    	octets = applycharginggprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete applycharginggprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeApplyChargingGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ApplyChargingGPRSArg* applycharginggprsarg = new ApplyChargingGPRSArg();

    try 
    {
	    applycharginggprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *applycharginggprsarg;

    delete octets;

    *data = applycharginggprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeApplyChargingReportGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ApplyChargingReportGPRSArg* applychargingreptgprsarg = reinterpret_cast<ApplyChargingReportGPRSArg *>(data);

    try 
    {
    	octets = applychargingreptgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete applychargingreptgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeApplyChargingReportGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ApplyChargingReportGPRSArg* applychargingreptgprsarg = new ApplyChargingReportGPRSArg();

    try 
    {
	    applychargingreptgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *applychargingreptgprsarg;

    delete octets;

    *data = applychargingreptgprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeCancelGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	CancelGPRSArg* cancelgprsarg = reinterpret_cast<CancelGPRSArg *>(data);

    try 
    {
    	octets = cancelgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete cancelgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeCancelGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    CancelGPRSArg* cancelgprsarg = new CancelGPRSArg();

    try 
    {
	    cancelgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *cancelgprsarg;

    delete octets;

    *data = cancelgprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeConnectGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ConnectGPRSArg* connectgprsarg = reinterpret_cast<ConnectGPRSArg *>(data);

    try 
    {
    	octets = connectgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete connectgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeConnectGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ConnectGPRSArg* connectgprsarg = new ConnectGPRSArg();

    try 
    {
	    connectgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *connectgprsarg;

    delete octets;

    *data = connectgprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeContinueGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ContinueGPRSArg* continuegprsarg = reinterpret_cast<ContinueGPRSArg *>(data);

    try 
    {
    	octets = continuegprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete continuegprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeContinueGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ContinueGPRSArg* continuegprsarg = new ContinueGPRSArg();

    try 
    {
	    continuegprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *continuegprsarg;

    delete octets;

    *data = continuegprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeEntityReleasedGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	EntityReleasedGPRSArg* entityrelgprsarg = reinterpret_cast<EntityReleasedGPRSArg *>(data);

    try 
    {
    	octets = entityrelgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete entityrelgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeEntityReleasedGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    EntityReleasedGPRSArg* entityrelgprsarg = new EntityReleasedGPRSArg();

    try 
    {
	    entityrelgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *entityrelgprsarg;

    delete octets;

    *data = entityrelgprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeFurnishChargingInformationGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	FCIGPRSBillingChargingCharacteristics* furnishchinfogprsarg = reinterpret_cast<FCIGPRSBillingChargingCharacteristics *>(data);

    try 
    {
    	octets = furnishchinfogprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete furnishchinfogprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeFurnishChargingInformationGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    FCIGPRSBillingChargingCharacteristics* furnishchinfogprsarg = new FCIGPRSBillingChargingCharacteristics();

    try 
    {
	    furnishchinfogprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *furnishchinfogprsarg;

    delete octets;

    *data = furnishchinfogprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeInitialDPGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	InitialDPGPRSArg* initialdpgprsarg = reinterpret_cast<InitialDPGPRSArg *>(data);

    try 
    {
    	octets = initialdpgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete initialdpgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeInitialDPGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    InitialDPGPRSArg* initialdpgprsarg = new InitialDPGPRSArg();

    try 
    {
	    initialdpgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *initialdpgprsarg;

    delete octets;

    *data = initialdpgprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeReleaseGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ReleaseGPRSArg* releasegprsarg = reinterpret_cast<ReleaseGPRSArg *>(data);

    try 
    {
    	octets = releasegprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete releasegprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeReleaseGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ReleaseGPRSArg* releasegprsarg = new ReleaseGPRSArg();

    try 
    {
	    releasegprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *releasegprsarg;

    delete octets;

    *data = releasegprsarg;

    return ITS_SUCCESS;
}

int 
AsnCC_EncodeEventReportGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	EventReportGPRSArg* eventreportgprsarg = reinterpret_cast<EventReportGPRSArg *>(data);

    try 
    {
    	octets = eventreportgprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete eventreportgprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeEventReportGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    EventReportGPRSArg* eventreportgprsarg = new EventReportGPRSArg();

    try 
    {
	    eventreportgprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *eventreportgprsarg;

    delete octets;

    *data = eventreportgprsarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeRequestReportGPRSEventArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	RequestReportGPRSEventArg* reqreportgprseventarg = reinterpret_cast<RequestReportGPRSEventArg *>(data);

    try 
    {
    	octets = reqreportgprseventarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete reqreportgprseventarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeRequestReportGPRSEventArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    RequestReportGPRSEventArg* reqreportgprseventarg = new RequestReportGPRSEventArg();

    try 
    {
	    reqreportgprseventarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *reqreportgprseventarg;

    delete octets;

    *data = reqreportgprseventarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeResetTimerGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	ResetTimerGPRSArg* resettimergprsarg = reinterpret_cast<ResetTimerGPRSArg *>(data);

    try 
    {
    	octets = resettimergprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete resettimergprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeResetTimerGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    ResetTimerGPRSArg* resettimergprsarg = new ResetTimerGPRSArg();

    try 
    {
	    resettimergprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *resettimergprsarg;

    delete octets;

    *data = resettimergprsarg;

    return ITS_SUCCESS;
}


int 
AsnCC_EncodeSendChargingInformationGPRSArg(
                        void* data, 
                        unsigned char** encoded, 
                        size_t* size, 
                        size_t valueNumber)
{
    ITS_REQUIRE(data != NULL);
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(size != NULL);

    Octets *octets = NULL;

	SendChargingInformationGPRSArg* sendingchinfogprsarg = reinterpret_cast<SendChargingInformationGPRSArg *>(data);

    try 
    {
    	octets = sendingchinfogprsarg->Encode();
    }
    catch (AsnEncodeError &encodeError) 
    {
	    cout << endl << encodeError.GetDescription() << endl;

	    throw encodeError;
    }

    cout << "\n\tPrinting encoded PDU...\n" << endl;
    cout << *octets;


    *encoded = (ITS_OCTET *)calloc(octets->GetLength(), sizeof(ITS_OCTET));

    *size = octets->GetLength();

    memcpy(*encoded, octets->GetArray().begin(), *size);

    delete sendingchinfogprsarg;
    delete octets;

    return ITS_SUCCESS;
}



int 
AsnCC_DecodeSendChargingInformationGPRSArg(
                        unsigned char* encoded, 
                        size_t size, 
                        void** data)
{
    ITS_REQUIRE(encoded != NULL);
    ITS_REQUIRE(data != NULL);

    vector<byte> encodedVect(encoded, encoded + size);

    Octets *octets = new Octets(encodedVect);

    SendChargingInformationGPRSArg* sendingchinfogprsarg = new SendChargingInformationGPRSArg();

    try 
    {
	    sendingchinfogprsarg->Decode(*octets);
    }
    catch (AsnDecodeError &decodeError) 
    {
	    cout << endl << decodeError.GetDescription() << endl;

        throw decodeError;
    }

    cout << "\n\tPrinting decoded PDU...\n" << endl;

    cout << *sendingchinfogprsarg;

    delete octets;

    *data = sendingchinfogprsarg;

    return ITS_SUCCESS;
}


