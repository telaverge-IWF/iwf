#include <UnitTest.h>
#include "tools.h"

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

class GSMMAP_SM_UnitTest : public UnitTest
{
public:
    GSMMAP_SM_UnitTest() : UnitTest("GSMMAP_SM_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void
GSMMAP_SM_UnitTest::DoCommand(istream& cmdLine)
{
    
    if (Cmd("RIS", "RoutingInfoForSM_Arg"))
    { 
        ////////////////////////////////////////
        // RoutingInfoForSM_Arge Encode part.
        RoutingInfoForSM_Arg* enc = new RoutingInfoForSM_Arg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetGprsSupportIndicator(InitializeGprsSupportIndicator());
        enc->SetMsisdn(InitializeMsisdn());
        enc->SetServiceCentreAddress(InitializeServiceCentreAddress());
        enc->SetSm_RP_MTI(InitializeSm_RP_MTI());
        enc->SetSm_RP_PRI(InitializeSm_RP_PRI());
        enc->SetSm_RP_SMEA(InitializeSm_RP_SMEA());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // RoutingInfoForSM_Arg Decode part.
        RoutingInfoForSM_Arg* dec = new RoutingInfoForSM_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RISRES", "RoutingInfoForSM_Res"))
    { 
        ////////////////////////////////////////
        // RoutingInfoForSM_Res Encode part.
        RoutingInfoForSM_Res* enc = new RoutingInfoForSM_Res();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetLocationInfoWithLMSI(InitializeLocationInfoWithLMSI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // RoutingInfoForSM_Res Decode part.
        RoutingInfoForSM_Res* dec = new RoutingInfoForSM_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("MOFSM", "MO_ForwardSM_Arg"))
    { 
        ////////////////////////////////////////
        // MO_ForwardSM_Arg Encode part.
        MO_ForwardSM_Arg* enc = new MO_ForwardSM_Arg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetSm_RP_DA(InitializeSm_RP_DA());
        enc->SetSm_RP_OA(InitializeSm_RP_OA());
        enc->SetSm_RP_UI(InitializeSm_RP_UI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // MO_ForwardSM_Arg Decode part.
        MO_ForwardSM_Arg* dec = new MO_ForwardSM_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("MOFSMRES", "MO_ForwardSM_Res"))
    { 
        ////////////////////////////////////////
        // MO_ForwardSM_Res Encode part.
        MO_ForwardSM_Res* enc = new MO_ForwardSM_Res();

        enc->SetExtensionContainer(InitializeExtensionContainer());        
        enc->SetSm_RP_UI(InitializeSm_RP_UI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // MO_ForwardSM_Res Decode part.
        MO_ForwardSM_Res* dec = new MO_ForwardSM_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RSMDS", "ReportSM_DeliveryStatusArg"))
    { 
        ////////////////////////////////////////
        // ReportSM_DeliveryStatusArg Encode part.
        ReportSM_DeliveryStatusArg* enc = new ReportSM_DeliveryStatusArg();

        enc->SetAbsentSubscriberDiagnosticSM
            (InitializeAbsentSubscriberDiagnosticSM());
        enc->SetAdditionalAbsentSubscriberDiagnosticSM
            (InitializeAbsentSubscriberDiagnosticSM());
        enc->SetAdditionalSM_DeliveryOutcome(InitializeSM_DeliveryOutcome());
        enc->SetDeliveryOutcomeIndicator
            (InitializeDeliveryOutcomeIndicator());
        enc->SetExtensionContainer(InitializeExtensionContainer());        
        //enc->SetGprsSupportIndicator(InitializeGprsSupportIndicator());
        enc->SetMsisdn(InitializeMsisdn());
        enc->SetServiceCentreAddress(InitializeServiceCentreAddress());
        enc->SetSm_DeliveryOutcome(InitializeSM_DeliveryOutcome());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // ReportSM_DeliveryStatusArg Decode part.
        ReportSM_DeliveryStatusArg* dec = new ReportSM_DeliveryStatusArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RSMDSRES", "ReportSM_DeliveryStatusRes"))
    { 
        ////////////////////////////////////////
        // ReportSM_DeliveryStatusRes Encode part.
        ReportSM_DeliveryStatusRes* enc = new ReportSM_DeliveryStatusRes();
        
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetStoredMSISDN(InitializeISDN_AddressString());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // ReportSM_DeliveryStatusRes Decode part.
        ReportSM_DeliveryStatusRes* dec = new ReportSM_DeliveryStatusRes();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RFSM", "ReadyForSM_Arg"))
    { 
        ////////////////////////////////////////
        // ReadyForSM_Arg Encode part.
        ReadyForSM_Arg* enc = new ReadyForSM_Arg();
        
        enc->SetAlertReason(InitializeAlertReason());
        enc->SetAlertReasonIndicator(InitializeAlertReasonIndicator());
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // ReadyForSM_Arg Decode part.
        ReadyForSM_Arg* dec = new ReadyForSM_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RFSMRES", "ReadyForSM_Res"))
    { 
        ////////////////////////////////////////
        // ReadyForSM_Res Encode part.
        ReadyForSM_Res* enc = new ReadyForSM_Res();
        
        enc->SetExtensionContainer(InitializeExtensionContainer());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // ReadyForSM_Res Decode part.
        ReadyForSM_Res* dec = new ReadyForSM_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("MTFSM", "MT_ForwardSM_Arg"))
    { 
        ////////////////////////////////////////
        // MT_ForwardSM_Arg Encode part.
        MT_ForwardSM_Arg* enc = new MT_ForwardSM_Arg();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetMoreMessagesToSend(InitializeMoreMessagesToSend());
        enc->SetSm_RP_DA(InitializeSm_RP_DA());
        enc->SetSm_RP_OA(InitializeSm_RP_OA());
        enc->SetSm_RP_UI(InitializeSm_RP_UI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // MT_ForwardSM_Arg Decode part.
        MT_ForwardSM_Arg* dec = new MT_ForwardSM_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("MTFSMRES", "MT_ForwardSM_Res"))
    { 
        ////////////////////////////////////////
        // MT_ForwardSM_Res Encode part.
        MT_ForwardSM_Res* enc = new MT_ForwardSM_Res();

        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetSm_RP_UI(InitializeSm_RP_UI());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // MT_ForwardSM_Res Decode part.
        MT_ForwardSM_Res* dec = new MT_ForwardSM_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("ASC", "AlertServiceCentreArg"))
    { 
        ////////////////////////////////////////
        // AlertServiceCentreArg Encode part.
        AlertServiceCentreArg* enc = new AlertServiceCentreArg();

        enc->SetMsisdn(InitializeMsisdn());
        enc->SetServiceCentreAddress(InitializeServiceCentreAddress());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // AlertServiceCentreArg Decode part.
        AlertServiceCentreArg* dec = new AlertServiceCentreArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("ISC", "InformServiceCentreArg"))
    { 
        ////////////////////////////////////////
        // InformServiceCentreArg Encode part.
        InformServiceCentreArg* enc = new InformServiceCentreArg();

        enc->SetStoredMSISDN(InitializeMsisdn());
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetMw_Status(InitializeMW_Status());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // InformServiceCentreArg Decode part.
        InformServiceCentreArg* dec = new InformServiceCentreArg();

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
    GSMMAP_SM_UnitTest test;

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