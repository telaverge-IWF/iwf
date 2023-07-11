
#include <its++.h>
#include <UnitTest.h>

#include "tools.h"


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)


// Define INAP unit test class
class INAP_UnitTest : public UnitTest
{
public:
    INAP_UnitTest() : UnitTest("INAP_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};


/*********************************************************************
 * C++ INAP Unit Tester:
 *
 * Purpose:
 *
 *     Tests if encoded message matches decoded message.
 *
 * Method:
 *
 *     The following steps are done for each INAP message in this test program
 *
 *     1) Create a pointer to an INAP Message object
 *     2) Set the parameters for the object
 *     3) Encode an INAP message and store the encoded message in an Octets object
 *        by making a call to:
 *
 *          MsgEncode(AsnObject* p, Octets** octets, string& str)
 *
 *        The message before encoding is stored in string1 for later comparison
 *
 *     4) Release allocated memory
 *     5) Create a new pointer to an INAP Message object to store the decoded
 *        message
 *     6) Decode the encoded message store in an octets object by calling
 *
 *          MsgDecode(AsnObject* p, Octets** octets, string& str)
 *
 *        and store the result in an INAP message object. The INAP message
 *        object is then stored in string2
 *     7) Release allocated memory
 *     8) Compare string1 and string 2
 *
 * Note:
 *
 *     Some optional parameters were were not set in this test program.
 *
 *********************************************************************/

void
INAP_UnitTest::DoCommand(istream& cmdLine)
{

    if (Cmd("IDPA", "InitialDPArg"))
    {

        //////////////////////////////////////////////
        // InitialDPArg Encoding Part

        // Create a pointer to an InitialDPArg object
        InitialDPArg* idp_arg = new InitialDPArg(true);

        // Set message parameters
        idp_arg->SetServiceKey(InitializeServiceKey());
        idp_arg->SetDialledDigits(InitializeCalledPartyNumber());
        idp_arg->SetCalledPartyNumber(InitializeCalledPartyNumber());
        idp_arg->SetCallingPartyNumber(InitializeCallingPartyNumber());
        idp_arg->SetCallingPartyBusinessGroupID
            (InitializeCallingPartyBusinessGroupID());
        idp_arg->SetCallingPartysCategory(InitializeCallingPartysCategory());
        idp_arg->SetCallingPartySubaddress(InitializeCallingPartySubaddress());
        idp_arg->SetCGEncountered(InitializeCGEncountered());
        // IPSSPCapabilities
        // IPAvailable
        // LocationNumber
        idp_arg->SetMiscCallInfo(InitializeMiscCallInfo());
        // OriginalCalledPartyID
        // ServiceProfileIdentifier
        // TerminalType

        // NOTE: Not included for now because the data types this function can
        // take as arguments are operator defined
        // idp_arg->SetExtensions(InitializeInitialDPArg_Extensions());

        // TriggerType
        // HighLayerCompatibility
        // ServiceInteractionIndicators
        idp_arg->SetAdditionalCallingPartyNumber
            (InitializeAdditionalCallingPartyNumber());
        // ForwardCallIndicators
        idp_arg->SetBearerCapability(InitializeBearerCapability());
        idp_arg->SetEventTypeBCSM(InitializeEventTypeBCSM());
        // RedirectingPartyID
        // RedirectionInformation


        Octets* octets = NULL;
        string str1, str2;

        // Encodes the message from the idp_arg object into octets for transmission
        MsgEncode(idp_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete idp_arg;
        idp_arg = NULL;

        ////////////////////////////////////////
        // InitialDPArg Decode part.

        InitialDPArg* idp_arg_dec = new InitialDPArg();

        // Decodes the message from octets to 
        MsgDecode(idp_arg_dec, octets, str2);

        // Release all allocated memory.
        delete idp_arg_dec;
        delete octets;

        // Compare the encoded message and decoded message if they are identical,
        // To verify that the message sent is the same as the message received
        CompareStrings(str1, str2);
    }

    
    if (Cmd("CA", "ConnectArg"))
    {

        //////////////////////////////////////////////
        // ConnectArg Encoding Part

        ConnectArg* c_arg = new ConnectArg();

        // Set Parameters
        c_arg->SetDestinationRoutingAddress
            (InitializeDestinationRoutingAddress());
        c_arg->SetAlertingPattern(InitializeAlertingPattern());
        c_arg->SetCorrelationID(InitializeCorrelationID());
        c_arg->SetCutAndPaste(InitializeCutAndPaste());
        c_arg->SetForwardingCondition(InitializeForwardingCondition());
        // ISDNAccessRelatedInformation
        // OriginalCalledPartyID
        c_arg->SetRouteList(InitializeRouteList());
        c_arg->SetScfID(InitializeScfID());
        c_arg->SetTravellingClassMark(InitializeLocationNumber());

        // NOTE: Not included for now because the types are operator defined
        //c_arg->SetExtensions(InitializeConnectArg_Extensions());

        // Carrier
        // ServiceInteractionIndicators
        c_arg->SetCallingPartyNumber(InitializeCallingPartyNumber());
        c_arg->SetCallingPartysCategory(InitializeCallingPartysCategory());
        // RedirectingPartyID
        // RedirectionInformation


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(c_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete c_arg;
        c_arg = NULL;

        ////////////////////////////////////////
        // ConnectArg Decode part.

        ConnectArg* c_arg_dec = new ConnectArg();

        MsgDecode(c_arg_dec, octets, str2);

        // Release all allocated memory.
        delete c_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RRBEA", "RequestReportBCSMEventArg"))
    {

        //////////////////////////////////////////////
        // RequestReportBCSMEventArg Encoding Part

        RequestReportBCSMEventArg* rrbe_arg = new RequestReportBCSMEventArg();

        // Set Parameters
        rrbe_arg->SetBcsmEvents
            (InitializeRequestReportBCSMEventArg_BcsmEvents());
        rrbe_arg->SetBcsmEventCorrelationID(InitializeDigits());
        // Extensions


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(rrbe_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete rrbe_arg;
        rrbe_arg = NULL;

        ////////////////////////////////////////
        // RequestReportBCSMEventArg Decode part.

        RequestReportBCSMEventArg* rrbe_arg_dec =
            new RequestReportBCSMEventArg();

        MsgDecode(rrbe_arg_dec, octets, str2);

        // Release all allocated memory.
        delete rrbe_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ERBA", "EventReportBCSMArg"))
    {

        //////////////////////////////////////////////
        // EventReportBCSMArg Encoding Part

        EventReportBCSMArg* erb_arg = new EventReportBCSMArg();

        // Set Parameters
        erb_arg->SetEventTypeBCSM(InitializeEventTypeBCSM());
        erb_arg->SetBcsmEventCorrelationID(InitializeDigits());
        erb_arg->SetEventSpecificInformationBCSM
            (InitializeEventSpecificInformationBCSM());
        erb_arg->SetLegID(InitializeLegID());
        erb_arg->SetMiscCallInfo(InitializeMiscCallInfo());
        // Extensions


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(erb_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete erb_arg;
        erb_arg = NULL;

        ////////////////////////////////////////
        // EventReportBCSMArg Decode part.

        EventReportBCSMArg* erb_arg_dec = new EventReportBCSMArg();

        MsgDecode(erb_arg_dec, octets, str2);

        // Release all allocated memory.
        delete erb_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RESCRA", "RequestEveryStatusChangeReportArg"))
    {

        //////////////////////////////////////////////
        // RequestEveryStatusChangeReportArg Encoding Part

        RequestEveryStatusChangeReportArg* rescr_arg =
            new RequestEveryStatusChangeReportArg();

        // Set Parameters
        rescr_arg->SetResourceID(InitializeResourceID());
        rescr_arg->SetCorrelationID(InitializeCorrelationID());
        rescr_arg->SetMonitorDuration(InitializeDuration());
        // Extensions


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(rescr_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete rescr_arg;
        rescr_arg = NULL;

        ////////////////////////////////////////
        // RequestEveryStatusChangeReportArg Decode part.

        RequestEveryStatusChangeReportArg* rescr_arg_dec =
            new RequestEveryStatusChangeReportArg();

        MsgDecode(rescr_arg_dec, octets, str2);

        // Release all allocated memory.
        delete rescr_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SRA", "StatusReportArg"))
    {

        //////////////////////////////////////////////
        // StatusReportArg Encoding Part

        StatusReportArg* sr_arg =
            new StatusReportArg();

        // Set Parameters
        sr_arg->SetResourceStatus(InitializeResourceStatus());
        sr_arg->SetCorrelationID(InitializeCorrelationID());
        sr_arg->SetResourceID(InitializeResourceID());
        // Extensions
        sr_arg->SetReportCondition(InitializeReportCondition());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sr_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete sr_arg;
        sr_arg = NULL;

        ////////////////////////////////////////
        // StatusReportArg Decode part.

        StatusReportArg* sr_arg_dec = new StatusReportArg();

        MsgDecode(sr_arg_dec, octets, str2);

        // Release all allocated memory.
        delete sr_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("CSRRA", "CancelStatusReportRequestArg"))
    {

        //////////////////////////////////////////////
        // CancelStatusReportRequestArg Encoding Part

        CancelStatusReportRequestArg* csrr_arg =
            new CancelStatusReportRequestArg();

        // Set Parameters
        csrr_arg->SetResourceID(InitializeResourceID());
        // Extensions


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(csrr_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete csrr_arg;
        csrr_arg = NULL;

        ////////////////////////////////////////
        // CancelStatusReportRequestArg Decode part.

        CancelStatusReportRequestArg* csrr_arg_dec =
            new CancelStatusReportRequestArg();

        MsgDecode(csrr_arg_dec, octets, str2);

        // Release all allocated memory.
        delete csrr_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    
    if (Cmd("RFSMRA", "RequestFirstStatusMatchReportArg"))
    {

        //////////////////////////////////////////////
        // RequestFirstStatusMatchReportArg Encoding Part

        RequestFirstStatusMatchReportArg* rfsmr_arg =
            new RequestFirstStatusMatchReportArg();

        // Set Parameters
        rfsmr_arg->SetResourceID(InitializeResourceID());
        rfsmr_arg->SetResourceStatus(InitializeResourceStatus());
        rfsmr_arg->SetCorrelationID(InitializeCorrelationID());
        rfsmr_arg->SetMonitorDuration(InitializeDuration());
        // Extensions
        rfsmr_arg->SetBearerCapability(InitializeBearerCapability());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(rfsmr_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete rfsmr_arg;
        rfsmr_arg = NULL;

        ////////////////////////////////////////
        // RequestFirstStatusMatchReportArg Decode part.

        RequestFirstStatusMatchReportArg* rfsmr_arg_dec =
            new RequestFirstStatusMatchReportArg();

        MsgDecode(rfsmr_arg_dec, octets, str2);

        // Release all allocated memory.
        delete rfsmr_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RCSRRA", "RequestCurrentStatusReportResultArg"))
    {

        //////////////////////////////////////////////
        // RequestCurrentStatusReportResultArg Encoding Part

        RequestCurrentStatusReportResultArg* rcsrr_arg =
            new RequestCurrentStatusReportResultArg();

        // Set Parameters
        rcsrr_arg->SetResourceStatus(InitializeResourceStatus());
        rcsrr_arg->SetResourceID(InitializeResourceID());
        // Extensions


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(rcsrr_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete rcsrr_arg;
        rcsrr_arg = NULL;

        ////////////////////////////////////////
        // RequestCurrentStatusReportResultArg Decode part.

        RequestCurrentStatusReportResultArg* rcsrr_arg_dec =
            new RequestCurrentStatusReportResultArg();

        MsgDecode(rcsrr_arg_dec, octets, str2);

        // Release all allocated memory.
        delete rcsrr_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("CGA", "CallGapArg"))
    {

        //////////////////////////////////////////////
        // CallGapArg Encoding Part

        CallGapArg* cg_arg = new CallGapArg();

        // Set Parameters
        cg_arg->SetGapCriteria(InitializeGapCriteria());
        cg_arg->SetGapIndicators(InitializeGapIndicators());
        cg_arg->SetControlType(InitializeControlType());
        cg_arg->SetGapTreatment(InitializeGapTreatment());
        // Extensions
        

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(cg_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete cg_arg;
        cg_arg = NULL;

        ////////////////////////////////////////
        // CallGapArg Decode part.

        CallGapArg* cg_arg_dec = new CallGapArg();

        MsgDecode(cg_arg_dec, octets, str2);

        // Release all allocated memory.
        delete cg_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("CIREQA", "CallInformationRequestArg"))
    {

        //////////////////////////////////////////////
        // CallInformationRequestArg Encoding Part

        CallInformationRequestArg* cireq_arg = new CallInformationRequestArg();

        // Set Parameters
        cireq_arg->SetRequestedInformationTypeList
            (InitializeRequestedInformationTypeList());
        cireq_arg->SetCorrelationID(InitializeCorrelationID());
        // Extensions
        

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(cireq_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete cireq_arg;
        cireq_arg = NULL;

        ////////////////////////////////////////
        // CallInformationRequestArg Decode part.

        CallInformationRequestArg* cireq_arg_dec =
            new CallInformationRequestArg();

        MsgDecode(cireq_arg_dec, octets, str2);

        // Release all allocated memory.
        delete cireq_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }
 
    
    if (Cmd("CIREPA", "CallInformationReportArg"))
    {

        //////////////////////////////////////////////
        // CallInformationReportArg Encoding Part

        CallInformationReportArg* cirep_arg = new CallInformationReportArg();

        // Set Parameters
        cirep_arg->SetRequestedInformationList
            (InitializeRequestedInformationList());
        cirep_arg->SetCorrelationID(InitializeCorrelationID());
        // Extensions
        

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(cirep_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete cirep_arg;
        cirep_arg = NULL;

        ////////////////////////////////////////
        // CallInformationReportArg Decode part.

        CallInformationReportArg* cirep_arg_dec =
            new CallInformationReportArg();

        MsgDecode(cirep_arg_dec, octets, str2);

        // Release all allocated memory.
        delete cirep_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

}


/*****************************************************************
 * Main
 *****************************************************************/
int
main(int argc, char **argv)
{
    INAP_UnitTest test;

    try
    {
        // Execute unit tester
        test.ExecuteCommandsFromStream();
    }
    catch (ITS_GenericException& exp)
    {
        // Print ITS exception that occur during encoding/decoding
        cout << endl << exp.GetDescription() << endl;
    }
    return 0;
}
