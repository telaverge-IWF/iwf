#include <UnitTest.h>
#include "tools.h"

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

class GSMMAP_MS_UnitTest : public UnitTest
{
public:
    GSMMAP_MS_UnitTest() : UnitTest("GSMMAP_MS_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void
GSMMAP_MS_UnitTest::DoCommand(istream& cmdLine)
{
    if (Cmd("CL", "CancelLocationArg"))
    { 
        ////////////////////////////////////////
        // CancelLocationArg Encode part.
        CancelLocationArg* enc = new CancelLocationArg();

        enc->SetCancellationType(InitializeCancellationType());
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetIdentity(InitializeIdentity());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // CancelLocationArg Decode part.
        CancelLocationArg* dec = new CancelLocationArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("CLRES", "CancelLocationRes"))
    { 
        ////////////////////////////////////////
        // CancelLocationRes Encode part.
        CancelLocationRes* enc = new CancelLocationRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // CancelLocationRes Decode part.
        CancelLocationRes* dec = new CancelLocationRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    // Arg for SendIdentification
    if (Cmd("TMSI", "TMSI"))
    { 
        ////////////////////////////////////////
        // TMSI Encode part.
        byte arr[] = { 0x01, 0x03 };

        TMSI* enc = new TMSI(ArrayToVector(arr, ARRAY_SIZE(arr)));
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // TMSI Decode part.
        TMSI* dec = new TMSI();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("SIRES", "SendIdentificationRes"))
    { 
        ////////////////////////////////////////
        // SendIdentificationRes Encode part.
        SendIdentificationRes* enc = new SendIdentificationRes();

        enc->SetAuthenticationSetList(InitializeAuthenticationSetList());
        enc->SetImsi(InitializeIMSI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // SendIdentificationRes Decode part.
        SendIdentificationRes* dec = new SendIdentificationRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("PMS", "PurgeMS_Arg"))
    { 
        ////////////////////////////////////////
        // PurgeMS_Arg Encode part.
        PurgeMS_Arg* enc = new PurgeMS_Arg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetSgsn_Number(InitializeSgsn_Number());
        enc->SetVlr_Number(InitializeVlr_Number());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // PurgeMS_Arg Decode part.
        PurgeMS_Arg* dec = new PurgeMS_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("PMSRES", "PurgeMS_Res"))
    { 
        ////////////////////////////////////////
        // PurgeMS_Res Encode part.
        PurgeMS_Res* enc = new PurgeMS_Res();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetFreezeTMSI(InitializeFreezeTMSI());
        enc->SetFreezeP_TMSI(InitializeFreezeP_TMSI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // PurgeMS_Arg Decode part.
        PurgeMS_Res* dec = new PurgeMS_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("UGL", "UpdateGprsLocationArg"))
    { 
        ////////////////////////////////////////
        // UpdateGprsLocationArg Encode part.
        UpdateGprsLocationArg* enc = new UpdateGprsLocationArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetSgsn_Address(InitializeSgsn_Address());
        enc->SetSgsn_Number(InitializeSgsn_Number());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // UpdateGprsLocationArg Decode part.
        UpdateGprsLocationArg* dec = new UpdateGprsLocationArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("UGLRES", "UpdateGprsLocationRes"))
    { 
        ////////////////////////////////////////
        // UpdateGprsLocationRes Encode part.
        UpdateGprsLocationRes* enc = new UpdateGprsLocationRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetHlr_Number(InitializeHlr_Number());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // UpdateGprsLocationRes Decode part.
        UpdateGprsLocationRes* dec = new UpdateGprsLocationRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("PHO", "PrepareHO_Arg"))
    { 
        ////////////////////////////////////////
        // PrepareHO_Arg Encode part.
        PrepareHO_Arg* enc = new PrepareHO_Arg();

        enc->SetBss_APDU(InitializeBss_APDU());
        enc->SetHo_NumberNotRequired(InitializeHo_NumberNotRequired());
        enc->SetTargetCellId(InitializeTargetCellId());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // PrepareHO_Arg Decode part.
        PrepareHO_Arg* dec = new PrepareHO_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("PHORES", "PrepareHO_Res"))
    { 
        ////////////////////////////////////////
        // PrepareHO_Res Encode part.
        PrepareHO_Res* enc = new PrepareHO_Res();

        enc->SetBss_APDU(InitializeBss_APDU());
        enc->SetHandoverNumber(InitializeHandoverNumber());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // PrepareHO_Res Decode part.
        PrepareHO_Res* dec = new PrepareHO_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    // Arg: SendEndSignal, ProcessAccessSignaling, ForwardAccessSignaling
    if (Cmd("ESI", "ExternalSignalInfo"))
    { 
        ////////////////////////////////////////
        // ExternalSignalInfo Encode part.
        ExternalSignalInfo* enc = new ExternalSignalInfo();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetProtocolId(InitializeProtocolId());
        enc->SetSignalInfo(InitializeSignalInfo());
        

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // ExternalSignalInfo Decode part.
        ExternalSignalInfo* dec = new ExternalSignalInfo();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("PSHO", "PrepareSubsequentHO_Arg"))
    { 
        ////////////////////////////////////////
        // PrepareSubsequentHO_Arg Encode part.
        PrepareSubsequentHO_Arg* enc = new PrepareSubsequentHO_Arg();

        enc->SetBss_APDU(InitializeBss_APDU());
        enc->SetTargetCellId(InitializeTargetCellId());
        enc->SetTargetMSC_Number(InitializeTargetMSC_Number());
        

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // PrepareSubsequentHO_Arg Decode part.
        PrepareSubsequentHO_Arg* dec = new PrepareSubsequentHO_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SAI", "SendAuthenticationInfoArg(IMSI)"))
    { 
        ////////////////////////////////////////
        // SendAuthenticationInfoArg Encode part.
        byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

        IMSI* enc = new IMSI(ArrayToVector(arr, ARRAY_SIZE(arr)));

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // SendAuthenticationInfoArg Decode part.
        IMSI* dec = new IMSI();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SAIRES", "SendAuthenticationInfoRes(AuthenticationSetList)"))
    { 
        ////////////////////////////////////////
        // AuthenticationSetList Encode part.
        AuthenticationSetList* enc = new AuthenticationSetList();

        enc->AddElement(InitializeAuthenticationSet());
        enc->AddElement(InitializeAuthenticationSet());
        enc->AddElement(InitializeAuthenticationSet());

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // AuthenticationSetList Decode part.
        AuthenticationSetList* dec = new AuthenticationSetList();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("CIMEI", "CheckIMEI(IMEI)"))
    { 
        ////////////////////////////////////////
        // CheckIMEI Encode part.
        byte arr[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

        IMEI* enc = new IMEI(ArrayToVector(arr, ARRAY_SIZE(arr)));


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // CheckIMEI Decode part.
        IMEI* dec = new IMEI();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("CIMEIRES", "CheckIMEIRes(EquipmentStatus)"))
    { 
        ////////////////////////////////////////
        // EquipmentStatus Encode part.
        EquipmentStatus* enc = new EquipmentStatus();

        enc->SetWhiteListed();

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // EquipmentStatus Decode part.
        EquipmentStatus* dec = new EquipmentStatus();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ISD", "InsertSubscriberDataArg"))
    { 
        ////////////////////////////////////////
        // InsertSubscriberDataArg Encode part.
        InsertSubscriberDataArg* enc = new InsertSubscriberDataArg();

        enc->SetBearerServiceList(InitializeBearerServiceList());
        enc->SetCategory(InitializeCategory());
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetGprsSubscriptionData(InitializeGprsSubscriptionData());
        enc->SetImsi(InitializeIMSI());
        enc->SetMsisdn(InitializeMsisdn());
        enc->SetNaea_PreferredCI(InitializeNaea_PreferredCI());
        enc->SetNetworkAccessMode(InitializeNetworkAccessMode());
        enc->SetOdb_Data(InitializeODB_Data());
        enc->SetProvisionedSS(InitializeProvisionedSS());
        enc->SetRegionalSubscriptionData(InitializeRegionalSubscriptionData());
        enc->SetTeleserviceList(InitializeTeleserviceList());
        enc->SetVbsSubscriptionData(InitializeVbsSubscriptionData());
        enc->SetVgcsSubscriptionData(InitializeVgcsSubscriptionData());
        enc->SetVlrCamelSubscriptionInfo(InitializeVlrCamelSubscriptionInfo());
        enc->SetRoamingRestrictedInSgsnDueToUnsupportedFeature(
            InitializeRoamingRestrictedInSgsnDueToUnsupportedFeature());
        enc->SetRoamingRestrictionDueToUnsupportedFeature(
            InitializeRoamingRestrictionDueToUnsupportedFeature());
        enc->SetSubscriberStatus(InitializeSubscriberStatus());
        
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // InsertSubscriberDataArg Decode part.
        InsertSubscriberDataArg* dec = new InsertSubscriberDataArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    
    
    if (Cmd("ISDRES", "InsertSubscriberDataRes"))
    { 
        ////////////////////////////////////////
        // InsertSubscriberDataRes Encode part.
        InsertSubscriberDataRes* enc = new InsertSubscriberDataRes();

        enc->SetBearerServiceList(InitializeBearerServiceList());
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetOdb_GeneralData(InitializeODB_GeneralData());
        enc->SetRegionalSubscriptionResponse
            (InitializeRegionalSubscriptionResponse());
        enc->SetTeleserviceList(InitializeTeleserviceList());        
        enc->SetSupportedCamelPhases(InitializeSupportedCamelPhases());
        enc->SetSs_List(InitializeSS_List());
        
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // InsertSubscriberDataRes Decode part.
        InsertSubscriberDataRes* dec = new InsertSubscriberDataRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("DSD", "DeleteSubscriberDataArg"))
    { 
        ////////////////////////////////////////
        // DeleteSubscriberDataArg Encode part.
        DeleteSubscriberDataArg* enc = new DeleteSubscriberDataArg();

        enc->SetBasicServiceList(InitializeBasicServiceList());
        enc->SetCamelSubscriptionInfoWithdraw
            (InitializeCamelSubscriptionInfoWithdraw());
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetGprsSubscriptionDataWithdraw
            (InitializeGprsSubscriptionDataWithdraw());
        enc->SetImsi(InitializeIMSI());
        enc->SetRegionalSubscriptionIdentifier
            (InitializeRegionalSubscriptionIdentifier());
        enc->SetRoamingRestrictedInSgsnDueToUnsuppportedFeature
             (InitializeRoamingRestrictedInSgsnDueToUnsuppportedFeature());
        //enc->SetRoamingRestrictionDueToUnsupportedFeature
        //     (InitializeRoamingRestrictionDueToUnsupportedFeature());
        enc->SetSs_List(InitializeSS_List());
        enc->SetVbsGroupIndication(InitializeVbsGroupIndication());
        enc->SetVgcsGroupIndication(InitializeVgcsGroupIndication());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // DeleteSubscriberDataArg Decode part.
        DeleteSubscriberDataArg* dec = new DeleteSubscriberDataArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("DSDRES", "DeleteSubscriberDataRes"))
    { 
        ////////////////////////////////////////
        // DeleteSubscriberDataRes Encode part.
        DeleteSubscriberDataRes* enc = new DeleteSubscriberDataRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetRegionalSubscriptionResponse
            (InitializeRegionalSubscriptionResponse());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // DeleteSubscriberDataRes Decode part.
        DeleteSubscriberDataRes* dec = new DeleteSubscriberDataRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("RS", "ResetArg"))
    { 
        ////////////////////////////////////////
        // ResetArg Encode part.
        ResetArg* enc = new ResetArg();

        enc->SetHlr_List(InitializeHLR_List());
        enc->SetHlr_Number(InitializeHlr_Number());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // ResetArg Decode part.
        ResetArg* dec = new ResetArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("RD", "RestoreDataArg"))
    { 
        ////////////////////////////////////////
        // RestoreDataArg Encode part.
        RestoreDataArg* enc = new RestoreDataArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetLmsi(InitializeLMSI());
        enc->SetVlr_Capability(InitializeVLR_Capability());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // RestoreDataArg Decode part.
        RestoreDataArg* dec = new RestoreDataArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RDRES", "RestoreDataRes"))
    { 
        ////////////////////////////////////////
        // RestoreDataRes Encode part.
        RestoreDataRes* enc = new RestoreDataRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetHlr_Number(InitializeHlr_Number());
        enc->SetMsNotReachable(InitializeMsNotReachable());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // RestoreDataRes Decode part.
        RestoreDataRes* dec = new RestoreDataRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("PSI", "ProvideSubscriberInfoArg"))
    { 
        ////////////////////////////////////////
        // ProvideSubscriberInfoArg Encode part.
        ProvideSubscriberInfoArg* enc = new ProvideSubscriberInfoArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetLmsi(InitializeLMSI());
        enc->SetRequestedInfo(InitializeRequestedInfo());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // ProvideSubscriberInfoArg Decode part.
        ProvideSubscriberInfoArg* dec = new ProvideSubscriberInfoArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("PSIRES", "ProvideSubscriberInfoRes"))
    { 
        ////////////////////////////////////////
        // ProvideSubscriberInfoRes Encode part.
        ProvideSubscriberInfoRes* enc = new ProvideSubscriberInfoRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetSubscriberInfo(InitializeSubscriberInfo());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // ProvideSubscriberInfoRes Decode part.
        ProvideSubscriberInfoRes* dec = new ProvideSubscriberInfoRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("SRIG", "SendRoutingInfoForGprsArg"))
    { 
        ////////////////////////////////////////
        // SendRoutingInfoForGprsArg Encode part.
        SendRoutingInfoForGprsArg* enc = new SendRoutingInfoForGprsArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetGgsn_Address(InitializeGgsn_Address());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // SendRoutingInfoForGprsArg Decode part.
        SendRoutingInfoForGprsArg* dec = new SendRoutingInfoForGprsArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SRIGRES", "SendRoutingInfoForGprsRes"))
    { 
        ////////////////////////////////////////
        // SendRoutingInfoForGprsRes Encode part.
        SendRoutingInfoForGprsRes* enc = new SendRoutingInfoForGprsRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetMobileNotReachableReason(InitializeMobileNotReachableReason());
        enc->SetGgsn_Address(InitializeGgsn_Address());
        enc->SetSgsn_Address(InitializeSgsn_Address());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // SendRoutingInfoForGprsRes Decode part.
        SendRoutingInfoForGprsRes* dec = new SendRoutingInfoForGprsRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("FR", "FailureReportArg"))
    { 
        ////////////////////////////////////////
        // FailureReportArg Encode part.
        FailureReportArg* enc = new FailureReportArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetGgsn_Address(InitializeGgsn_Address());
        enc->SetGgsn_Number(InitializeGgsn_Number());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // FailureReportArg Decode part.
        FailureReportArg* dec = new FailureReportArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("FRRES", "FailureReportRes"))
    { 
        ////////////////////////////////////////
        // FailureReportRes Encode part.
        FailureReportRes* enc = new FailureReportRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // FailureReportRes Decode part.
        FailureReportRes* dec = new FailureReportRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("NMPG", "NoteMsPresentForGprsArg"))
    { 
        ////////////////////////////////////////
        // NoteMsPresentForGprsArg Encode part.
        NoteMsPresentForGprsArg* enc = new NoteMsPresentForGprsArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetGgsn_Address(InitializeGgsn_Address());
        enc->SetSgsn_Address(InitializeSgsn_Address());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // NoteMsPresentForGprsArg Decode part.
        NoteMsPresentForGprsArg* dec = new NoteMsPresentForGprsArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("NMPGRES", "NoteMsPresentForGprsRes"))
    { 
        ////////////////////////////////////////
        // NoteMsPresentForGprsRes Encode part.
        NoteMsPresentForGprsRes* enc = new NoteMsPresentForGprsRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // NoteMsPresentForGprsRes Decode part.
        NoteMsPresentForGprsRes* dec = new NoteMsPresentForGprsRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("UL", "UpdateLocationArg"))
    { 
        ////////////////////////////////////////
        // UpdateLocationArg Encode part.
        UpdateLocationArg* enc = new UpdateLocationArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetLmsi(InitializeLMSI());
        enc->SetVlr_Capability(InitializeVLR_Capability());
        enc->SetMsc_Number(InitializeMsc_Number());
        enc->SetVlr_Number(InitializeVlr_Number());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // UpdateLocationArg Decode part.
        UpdateLocationArg* dec = new UpdateLocationArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ULRES", "UpdateLocationRes"))
    { 
        ////////////////////////////////////////
        // UpdateLocationRes Encode part.
        UpdateLocationRes* enc = new UpdateLocationRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetHlr_Number(InitializeHlr_Number());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // UpdateLocationRes Decode part.
        UpdateLocationRes* dec = new UpdateLocationRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ATI", "AnyTimeInterrogationArg"))
    { 
        ////////////////////////////////////////
        // AnyTimeInterrogationArg Encode part.
        AnyTimeInterrogationArg* enc = new AnyTimeInterrogationArg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetGsmSCF_Address(InitializeGsmSCF_Address());
        enc->SetRequestedInfo(InitializeRequestedInfo());
        enc->SetSubscriberIdentity(InitializeSubscriberIdentity());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // AnyTimeInterrogationArg Decode part.
        AnyTimeInterrogationArg* dec = new AnyTimeInterrogationArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ATIRES", "AnyTimeInterrogationRes"))
    { 
        ////////////////////////////////////////
        // AnyTimeInterrogationRes Encode part.
        AnyTimeInterrogationRes* enc = new AnyTimeInterrogationRes();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetSubscriberInfo(InitializeSubscriberInfo());
                
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // AnyTimeInterrogationRes Decode part.
        AnyTimeInterrogationRes* dec = new AnyTimeInterrogationRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }
}

int
main(int argc, char **argv)
{
    GSMMAP_MS_UnitTest test;

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