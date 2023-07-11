#include <UnitTest.h>
#include "tools.h"

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif


class GSMMAP_UnitTest : public UnitTest
{
public:
    GSMMAP_UnitTest() : UnitTest("GSMMAP_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void
GSMMAP_UnitTest::DoCommand(istream& cmdLine)
{

     if (Cmd("SRIA", "SendRoutingInfoArg"))
    {
        ///////////////////////////////////////////////////
        // Activate SendRoutingInformationArg Encode part.

        SendRoutingInfoArg* sendRoutingInfoArg = new SendRoutingInfoArg();

        // Set parameters
        sendRoutingInfoArg->SetMsisdn(InitializeISDN_AddressString());
        sendRoutingInfoArg->SetCug_CheckInfo(InitializeCUG_CheckInfo());
        sendRoutingInfoArg->SetNumberOfForwarding
            (InitializeNumberOfForwarding());
        sendRoutingInfoArg->SetInterrogationType
            (InitializeInterrogationType());
        sendRoutingInfoArg->SetOr_Interrogation(InitializeOr_Interrogation());
        sendRoutingInfoArg->SetOr_Capability(InitializeOrCapability());
        sendRoutingInfoArg->SetGmsc_Address(InitializeISDN_AddressString());
        sendRoutingInfoArg->SetCallReferenceNumber
            (InitializeCallReferenceNumber());
        sendRoutingInfoArg->SetForwardingReason(InitializeForwardingReason());
        sendRoutingInfoArg->SetBasicServiceGroup
            (InitializeBasicServiceGroup());
        sendRoutingInfoArg->SetNetworkSignalInfo
            (InitializeNetworkSignalInfo2());
        sendRoutingInfoArg->SetCamelInfo(InitializeCamelInfo());
        sendRoutingInfoArg->SetSuppressionOfAnnouncement
            (InitializeSuppressionOfAnnouncement());
        sendRoutingInfoArg->SetAlertingPattern(InitializeAlertingPattern());
        sendRoutingInfoArg->SetCcbs_Call(InitializeCcbs_Call());
        sendRoutingInfoArg->SetSupportedCCBS_Phase
            (InitializeSupportedCCBS_Phase());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sendRoutingInfoArg, &octets, str1);

        // Release all allocated memory till current point.
        delete sendRoutingInfoArg;
        sendRoutingInfoArg = NULL;

        ////////////////////////////////////////
        // SendRoutingInfoArg Decode part.

        SendRoutingInfoArg* sendRoutingInfoArgDec =
                new SendRoutingInfoArg();

        MsgDecode(sendRoutingInfoArgDec, octets, str2);

        // Release all allocated memory.
        delete sendRoutingInfoArgDec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("SRIR", "SendRoutingInfoRes"))
    {
        ///////////////////////////////////////////////////
        // Activate SendRoutingInformationRes Encode part.

        SendRoutingInfoRes* sendRoutingInfoRes = new SendRoutingInfoRes();

        // Set parameters
        sendRoutingInfoRes->SetImsi(InitializeIMSI());
        sendRoutingInfoRes->SetExtendedRoutingInfo(InitializeExtendedRoutingInfo());
        sendRoutingInfoRes->SetCug_CheckInfo(InitializeCUG_CheckInfo());
        sendRoutingInfoRes->SetCugSubscriptionFlag(InitializeCugSubscriptionFlag());
        sendRoutingInfoRes->SetSubscriberInfo(InitializeSubscriberInfo());
        sendRoutingInfoRes->SetSs_List(InitializeSS_List());
        sendRoutingInfoRes->SetBasicService(InitializeExt_BasicServiceCode());
        sendRoutingInfoRes->SetForwardingInterrogationRequired
            (InitializeForwardingInterrogationRequired());
        sendRoutingInfoRes->SetVmsc_Address(InitializeVmsc_Address());
        //extensionContainer
        sendRoutingInfoRes->SetNaea_PreferredCI(InitializeNaea_PreferredCI());
        sendRoutingInfoRes->SetCcbs_Indicators(InitializeCCBS_Indicators());

        
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sendRoutingInfoRes, &octets, str1);

        // Release all allocated memory till current point.
        delete sendRoutingInfoRes;
        sendRoutingInfoRes = NULL;

        ////////////////////////////////////////
        // SendRoutingInfoArg Decode part.

        SendRoutingInfoRes* sendRoutingInfoResDec =
                new SendRoutingInfoRes();

        MsgDecode(sendRoutingInfoResDec, octets, str2);

        // Release all allocated memory.
        delete sendRoutingInfoResDec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("PRNA", "ProvideRoamingNumberArg"))
    {
        ///////////////////////////////////////////////////
        // Activate ProvideRoamingNumberArg Encode part.

        ProvideRoamingNumberArg* prn_arg = new ProvideRoamingNumberArg();

        // Set parameters
        prn_arg->SetImsi(InitializeIMSI());        
        prn_arg->SetMsc_Number(InitializeMsc_Number());       
        prn_arg->SetMsisdn(InitializeMsisdn());
        prn_arg->SetLmsi(InitializeLMSI());
        prn_arg->SetGsm_BearerCapability(InitializeGsm_BearerCapability());
        prn_arg->SetNetworkSignalInfo(InitializeNetworkSignalInfo());
        prn_arg->SetSuppressionOfAnnouncement
            (InitializeSuppressionOfAnnouncement());
        prn_arg->SetGmsc_Address(InitializeISDN_AddressString());
        prn_arg->SetCallReferenceNumber(InitializeCallReferenceNumber());
        prn_arg->SetOr_Interrogation(InitializePRNAOr_Interrogation());
        //extensionContainer not used
        prn_arg->SetAlertingPattern(InitializeAlertingPattern());
        prn_arg->SetCcbs_Call(InitializePRNACcbs_Call());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(prn_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete prn_arg;
        prn_arg = NULL;

        ////////////////////////////////////////
        // ProvideRoamingNumberArg Decode part.

        ProvideRoamingNumberArg* prn_arg_dec =
                new ProvideRoamingNumberArg();

        MsgDecode(prn_arg_dec, octets, str2);

        // Release all allocated memory.
        delete prn_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("PRNR", "ProvideRoamingNumberRes"))
    {
        ///////////////////////////////////////////////////
        // Activate ProvideRoamingNumberRes Encode part.

        ProvideRoamingNumberRes* prn_res = new ProvideRoamingNumberRes();

        // Set parameters
        prn_res->SetRoamingNumber(InitializeRoamingNumber());
        // extensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(prn_res, &octets, str1);

        // Release all allocated memory till current point.
        delete prn_res;
        prn_res = NULL;

        ////////////////////////////////////////
        // ProvideRoamingNumberRes Decode part.

        ProvideRoamingNumberRes* prn_res_dec =
                new ProvideRoamingNumberRes();

        MsgDecode(prn_res_dec, octets, str2);

        // Release all allocated memory.
        delete prn_res_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("SRSA", "SetReportingStateArg"))
    {
        ///////////////////////////////////////////////////
        // Activate SetReportingStateArg Encode part.

        SetReportingStateArg* srs_arg = new SetReportingStateArg();

        // Set parameters
        srs_arg->SetImsi(InitializeIMSI());
        srs_arg->SetLmsi(InitializeLMSI());
        srs_arg->SetCcbs_Monitoring(InitializeReportingState());
        // extensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(srs_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete srs_arg;
        srs_arg = NULL;

        ////////////////////////////////////////
        // SetReportingStateArg Decode part.

        SetReportingStateArg* srs_arg_dec = new SetReportingStateArg();

        MsgDecode(srs_arg_dec, octets, str2);

        // Release all allocated memory.
        delete srs_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }
    
    if (Cmd("SRSR", "SetReportingStateRes"))
    {
        ///////////////////////////////////////////////////
        // Activate SetReportingStateRes Encode part.

        SetReportingStateRes* srs_res = new SetReportingStateRes();

        // Set parameters
        srs_res->SetCcbs_SubscriberStatus(InitializeCCBS_SubscriberStatus());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(srs_res, &octets, str1);

        // Release all allocated memory till current point.
        delete srs_res;
        srs_res = NULL;

        ////////////////////////////////////////
        // SetReportingStateRes Decode part.

        SetReportingStateRes* srs_res_dec = new SetReportingStateRes();

        MsgDecode(srs_res_dec, octets, str2);

        // Release all allocated memory.
        delete srs_res_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("SRA", "StatusReportArg"))
    {
        ///////////////////////////////////////////////////
        // Activate StatusReportArg Encode part.

        StatusReportArg* sr_arg = new StatusReportArg();

        // Set parameters
        sr_arg->SetImsi(InitializeIMSI());
        sr_arg->SetEventReportData(InitializeEventReportData());
        sr_arg->SetCallReportdata(InitializeCallReportData());
        //extensionContainer

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

    if (Cmd("SRR", "StatusReportRes"))
    {
        ///////////////////////////////////////////////////
        // Activate StatusReportArg Encode part.

        StatusReportRes* sr_res = new StatusReportRes();

        // Set parameters
        // extension container, not really used
        sr_res->SetExtensionContainer(InitializeExtensionContainer());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sr_res, &octets, str1);

        // Release all allocated memory till current point.
        delete sr_res;
        sr_res = NULL;

        ////////////////////////////////////////
        // StatusReportRes Decode part.

        StatusReportRes* sr_res_dec = new StatusReportRes();

        MsgDecode(sr_res_dec, octets, str2);

        // Release all allocated memory.
        delete sr_res_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    
    if (Cmd("RUFA", "RemoteUserFreeArg"))
    {
        ///////////////////////////////////////////////////
        // Activate RemoteUserFreeArg Encode part.

        RemoteUserFreeArg* ruf_arg = new RemoteUserFreeArg();

        // Set message parameters
        ruf_arg->SetImsi(InitializeIMSI());
        ruf_arg->SetCallInfo(InitializeExternalSignalInfo());
        ruf_arg->SetCcbs_Feature(InitializeCcbs_Feature());
        ruf_arg->SetTranslatedB_Number(InitializeISDN_AddressString());
        ruf_arg->SetReplaceB_Number(InitializeReplaceB_Number());
        ruf_arg->SetAlertingPattern(InitializeAlertingPattern());
	    // extensionContainer not used


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(ruf_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete ruf_arg;
        ruf_arg = NULL;

        ////////////////////////////////////////
        // RemoteUserFreeArg Decode part.

        RemoteUserFreeArg* ruf_arg_dec = new RemoteUserFreeArg();

        MsgDecode(ruf_arg_dec, octets, str2);

        // Release all allocated memory.
        delete ruf_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("RUFR", "RemoteUserFreeRes"))
    {
        ///////////////////////////////////////////////////
        // Activate RemoteUserFreeRes Encode part.

        RemoteUserFreeRes* ruf_res = new RemoteUserFreeRes();

        // Set message parameters
        ruf_res->SetRuf_Outcome(InitializeRUF_Outcome());
	    // extensionContainer not used


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(ruf_res, &octets, str1);

        // Release all allocated memory till current point.
        delete ruf_res;
        ruf_res = NULL;

        ////////////////////////////////////////
        // RemoteUserFreeRes Decode part.

        RemoteUserFreeRes* ruf_res_dec = new RemoteUserFreeRes();

        MsgDecode(ruf_res_dec, octets, str2);

        // Release all allocated memory.
        delete ruf_res_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SMA", "SIWFSSignallingModifyArg"))
    {
        ///////////////////////////////////////////////////
        // Activate SIWFSSignallingModifyArg Encode part.

        SIWFSSignallingModifyArg* sm_arg = new SIWFSSignallingModifyArg();

        // Set message parameters
        sm_arg->SetChannelType(InitializeExternalSignalInfo());
        sm_arg->SetChosenChannel(InitializeExternalSignalInfo());
        //ExtensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sm_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete sm_arg;
        sm_arg = NULL;

        ////////////////////////////////////////
        // SIWFSSignallingModifyArg Decode part.

        SIWFSSignallingModifyArg* sm_arg_dec = new SIWFSSignallingModifyArg();

        MsgDecode(sm_arg_dec, octets, str2);

        // Release all allocated memory.
        delete sm_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SMR", "SIWFSSignallingModifyRes"))
    {
        ///////////////////////////////////////////////////
        // Activate SIWFSSignallingModifyRes Encode part.

        SIWFSSignallingModifyRes* sm_res = new SIWFSSignallingModifyRes();

        // Set message parameters
        sm_res->SetChosenChannel(InitializeExternalSignalInfo());
        //ExtensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sm_res, &octets, str1);

        // Release all allocated memory till current point.
        delete sm_res;
        sm_res = NULL;

        ////////////////////////////////////////
        // SIWFSSignallingModifyRes Decode part.

        SIWFSSignallingModifyRes* sm_res_dec = new SIWFSSignallingModifyRes();

        MsgDecode(sm_res_dec, octets, str2);

        // Release all allocated memory.
        delete sm_res_dec;
        delete octets;

        CompareStrings(str1, str2);
    }
    

    // ProvideSIWFSNumberArg
    if (Cmd("PSNA", "ProvideSIWFSNumberArg"))
    {
        ///////////////////////////////////////////////////
        // Activate ProvideSIWFSNumberArg Encode part.

        ProvideSIWFSNumberArg* psn_arg = new ProvideSIWFSNumberArg();

        // Set message parameters
        psn_arg->SetGsm_BearerCapability(InitializeExternalSignalInfo());
        psn_arg->SetIsdn_BearerCapability(InitializeExternalSignalInfo());
        psn_arg->SetCall_Direction(InitializeCallDirection());
        psn_arg->SetB_Subscriber_Address(InitializeISDN_AddressString());
        psn_arg->SetChosenChannel(InitializeExternalSignalInfo());
        psn_arg->SetLowerLayerCompatibility(InitializeExternalSignalInfo());
        psn_arg->SetHighLayerCompatibility(InitializeExternalSignalInfo());
        //ExtensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(psn_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete psn_arg;
        psn_arg = NULL;

        ////////////////////////////////////////
        // ProvideSIWFSNumberArg Decode part.

        ProvideSIWFSNumberArg* psn_arg_dec = new ProvideSIWFSNumberArg();

        MsgDecode(psn_arg_dec, octets, str2);

        // Release all allocated memory.
        delete psn_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }
    
    
    // ProvideSIWFSNumberRes
    if (Cmd("PSNR", "ProvideSIWFSNumberRes"))
    {
        ///////////////////////////////////////////////////
        // Activate ProvideSIWFSNumberRes Encode part.

        ProvideSIWFSNumberRes* psn_res = new ProvideSIWFSNumberRes();

        // Set message parameters
        psn_res->SetSIWFSNumber(InitializeISDN_AddressString());
        // ExtensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(psn_res, &octets, str1);

        // Release all allocated memory till current point.
        delete psn_res;
        psn_res = NULL;

        ////////////////////////////////////////
        // ProvideSIWFSNumberRes Decode part.

        ProvideSIWFSNumberRes* psn_res_dec = new ProvideSIWFSNumberRes();

        MsgDecode(psn_res_dec, octets, str2);

        // Release all allocated memory.
        delete psn_res_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    
    // ResumeCallHandlingArg
    if (Cmd("RCHA", "ResumeCallHandlingArg"))
    {
        ///////////////////////////////////////////////////
        // Activate ResumeCallHandlingArg Encode part.

        ResumeCallHandlingArg* rch_arg = new ResumeCallHandlingArg();

        // Set message parameters
        rch_arg->SetCallReferenceNumber(InitializeCallReferenceNumber());
        rch_arg->SetBasicServiceGroup(InitializeBasicServiceGroup());
        rch_arg->SetForwardingData(InitializeForwardingData());
        rch_arg->SetImsi(InitializeIMSI());
        rch_arg->SetCug_CheckInfo(InitializeCUG_CheckInfo());
        rch_arg->SetO_CSI(InitializeO_CSI());
        rch_arg->SetCcbs_Possible(InitializeRCHACcbs_Possible());
        //ExtensionContainer


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(rch_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete rch_arg;
        rch_arg = NULL;

        ////////////////////////////////////////
        // ResumeCallHandlingArg Decode part.

        ResumeCallHandlingArg* rch_arg_dec = new ResumeCallHandlingArg();

        MsgDecode(rch_arg_dec, octets, str2);

        // Release all allocated memory.
        delete rch_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    // ResumeCallHandlingRes
    if (Cmd("RCHR", "ResumeCallHandlingRes"))
    {
        ///////////////////////////////////////////////////
        // Activate ResumeCallHandlingRes Encode part.

        ResumeCallHandlingRes* rch_res = new ResumeCallHandlingRes();

        // Set message parameters
        // ExtensionContainer, not really used
        rch_res->SetExtensionContainer(InitializeExtensionContainer());
        

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(rch_res, &octets, str1);

        // Release all allocated memory till current point.
        delete rch_res;
        rch_res = NULL;

        ////////////////////////////////////////
        // ResumeCallHandlingArg Decode part.

        ResumeCallHandlingRes* rch_res_dec = new ResumeCallHandlingRes();

        MsgDecode(rch_res_dec, octets, str2);

        // Release all allocated memory.
        delete rch_res_dec;
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
    GSMMAP_UnitTest test;

    try
    {
        test.ExecuteCommandsFromStream();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;
    }
    return 0;
}