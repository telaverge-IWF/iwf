#include <UnitTest.h>
#include "tools.h"

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

class GSMMAP_SS_UnitTest : public UnitTest
{
public:
    GSMMAP_SS_UnitTest() : UnitTest("GSMMAP_SS_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void
GSMMAP_SS_UnitTest::DoCommand(istream& cmdLine)
{
    // Arg for: EraseSS, ActivateSS, DeactivateSS, InterrogateSS
    if (Cmd("SSBS", "SS_ForBS_Code"))
    { 
        ////////////////////////////////////////
        // SS_ForBS_Code Encode part.
        SS_ForBS_Code* enc = new SS_ForBS_Code();

        enc->SetSs_Code(InitializeSS_Code()); 
        enc->SetBasicService(InitializeBasicService());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // SS_ForBS_Code Decode part.

        SS_ForBS_Code* dec = new SS_ForBS_Code();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }
    
    if (Cmd("RSS", "RegisterSS_Arg"))
    { 
        ////////////////////////////////////////
        // RegisterSS_Arg Encode part.
        RegisterSS_Arg* regSSArg = new RegisterSS_Arg();

        regSSArg->SetSs_Code(InitializeSS_Code()); 
        regSSArg->SetBasicService(InitializeBasicService());
        regSSArg->SetForwardedToNumber(IntializeForwardedToNumber());
        regSSArg->SetForwardedToSubaddress(IntializeForwardedToSubaddress());
        regSSArg->SetNoReplyConditionTime(InitializeNoReplyConditionTime());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(regSSArg, &octets, str1);

        // Release all allocated memory till current point.
        delete regSSArg;
        regSSArg = NULL;

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        RegisterSS_Arg* regSSDec =
                new RegisterSS_Arg();

        MsgDecode(regSSDec, octets, str2);

        // Release all allocated memory.
        delete regSSDec;
        delete octets;

        CompareStrings(str1, str2);
    }


    // Res for:RegisterSS, EraseSS, ActivateSS, DeactivateSS 
    if (Cmd("SSINFO", "SS_Info"))
    { 
        ////////////////////////////////////////
        // SS_Info Encode part.
        SS_Info* enc = new SS_Info();

        enc->SetChoiceSs_Data(InitializeSS_Data()); 
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // SS_ForBS_Code Decode part.

        SS_Info* dec = new SS_Info();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    // Arg for RegisterPassword
    if (Cmd("SSCODE", "SS_Code"))
    { 
        ////////////////////////////////////////
        // SS_Code Encode part.        
        byte arr[] = { 0x33U };

        SS_Code* enc = new SS_Code(ArrayToVector(arr, ARRAY_SIZE(arr)));

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL;

        ////////////////////////////////////////
        // SS_Code Decode part.
        SS_Code* dec = new SS_Code();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    // Res for RegisterPassword
    if (Cmd("PW", "Password"))
    { 
    }


    if (Cmd("ISSRES", "InterrogateSS_Res"))
    { 
        ////////////////////////////////////////
        // RegisterCC_EntryRes Encode part.
        InterrogateSS_Res* enc = new InterrogateSS_Res();

        enc->SetChoiceSs_Status(InitializeSS_Status());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        InterrogateSS_Res* dec = new InterrogateSS_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RCCE", "RegisterCC_EntryArg"))
    { 
        ////////////////////////////////////////
        // RegisterCC_EntryArg Encode part.
        RegisterCC_EntryArg* regCCArg = new RegisterCC_EntryArg();

        regCCArg->SetSs_Code(InitializeSS_Code()); 
        regCCArg->SetCcbs_Data(InitializeCcbs_Data());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(regCCArg, &octets, str1);

        // Release all allocated memory till current point.
        delete regCCArg;
        regCCArg = NULL; 

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        RegisterCC_EntryArg* regCCDec =
                new RegisterCC_EntryArg();

        MsgDecode(regCCDec, octets, str2);

        // Release all allocated memory.
        delete regCCDec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("RCCERES", "RegisterCC_EntryRes"))
    { 
        ////////////////////////////////////////
        // RegisterCC_EntryRes Encode part.
        RegisterCC_EntryRes* regCCRes = new RegisterCC_EntryRes();

        regCCRes->SetCcbs_Feature(InitializeCcbs_Feature());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(regCCRes, &octets, str1);

        // Release all allocated memory till current point.
        delete regCCRes;
        regCCRes = NULL; 

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        RegisterCC_EntryRes* regCCResDec =
                new RegisterCC_EntryRes();

        MsgDecode(regCCResDec, octets, str2);

        // Release all allocated memory.
        delete regCCResDec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ECCE", "EraseCC_EntryArg"))
    { 
        ////////////////////////////////////////
        // EraseCC_EntryArg Encode part.
        EraseCC_EntryArg* eCCe = new EraseCC_EntryArg();

        eCCe->SetCcbs_Index(InitializeCcbs_Index());
        eCCe->SetSs_Code(InitializeSS_Code());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(eCCe, &octets, str1);

        // Release all allocated memory till current point.
        delete eCCe;
        eCCe = NULL; 

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        EraseCC_EntryArg* eCCRes =
                new EraseCC_EntryArg();

        MsgDecode(eCCRes, octets, str2);

        // Release all allocated memory.
        delete eCCRes;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("ECCERES", "EraseCC_EntryRes"))
    { 
        ////////////////////////////////////////
        // EraseCC_EntryRes Encode part.
        EraseCC_EntryRes* eCCeRes = new EraseCC_EntryRes();

        eCCeRes->SetSs_Status(InitializeSS_Status());
        eCCeRes->SetSs_Code(InitializeSS_Code());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(eCCeRes, &octets, str1);

        // Release all allocated memory till current point.
        delete eCCeRes;
        eCCeRes = NULL; 

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        EraseCC_EntryRes* eCCResDec =
                new EraseCC_EntryRes();

        MsgDecode(eCCResDec, octets, str2);

        // Release all allocated memory.
        delete eCCResDec;
        delete octets;

        CompareStrings(str1, str2);
    }


    // Arg for GetPassword
    if (Cmd("GI", "GuidanceInfo"))
    { 
        ////////////////////////////////////////
        // GuidanceInfo Encode part.
        GuidanceInfo* enc = new GuidanceInfo();

        enc->SetEnterNewPW();
        enc->SetEnterNewPW_Again();
        enc->SetEnterPW();
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // GuidanceInfo Decode part.

        GuidanceInfo* dec = new GuidanceInfo();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }



    // Arg for ProcessUnstructuredSS_Request / UnstructuredSS_Request /
    //         UnstructuredSS_Notify
    if (Cmd("USSD", "USSD_Arg"))
    { 
        ////////////////////////////////////////
        // USSD_Arg Encode part.
        USSD_Arg* enc = new USSD_Arg();

        enc->SetAlertingPattern(InitializeAlertingPattern());
        enc->SetUssd_DataCodingScheme(InitializeUssd_DataCodingScheme());
        enc->SetUssd_String(InitializeUssd_String());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // USSD_Arg Decode part.

        USSD_Arg* dec = new USSD_Arg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    // Res for ProcessUnstructuredSS_Request, UnstructuredSS_Request
    if (Cmd("USSDRES", "USSD_Res"))
    { 
        ////////////////////////////////////////
        // USSD_Res Encode part.
        USSD_Res* enc = new USSD_Res();
        
        enc->SetUssd_DataCodingScheme(InitializeUssd_DataCodingScheme());
        enc->SetUssd_String(InitializeUssd_String());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // USSD_Res Decode part.
        USSD_Res* dec = new USSD_Res();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SSIN", "SS_InvocationNotificationArg"))
    { 
        ////////////////////////////////////////
        // SS_InvocationNotificationArg Encode part.
        SS_InvocationNotificationArg* enc = new SS_InvocationNotificationArg();
        
        enc->SetExtensionContainer(InitializeExtensionContainer());
        enc->SetImsi(InitializeIMSI());
        enc->SetMsisdn(InitializeMsisdn());
        enc->SetSs_Event(InitializeSS_Code());
        enc->SetSs_EventSpecification(InitializeSS_EventSpecification());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // SS_InvocationNotificationArg Decode part.
        SS_InvocationNotificationArg* dec = new SS_InvocationNotificationArg();

        MsgDecode(dec, octets, str2);

        // Release all allocated memory.
        delete dec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("SSINRES", "SS_InvocationNotificationRes"))
    { 
        ////////////////////////////////////////
        // SS_InvocationNotificationRes Encode part.
        SS_InvocationNotificationRes* enc = new SS_InvocationNotificationRes();
        
        enc->SetExtensionContainer(InitializeExtensionContainer());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(enc, &octets, str1);

        // Release all allocated memory till current point.
        delete enc;
        enc = NULL; 

        ////////////////////////////////////////
        // SS_InvocationNotificationRes Decode part.
        SS_InvocationNotificationRes* dec = new SS_InvocationNotificationRes();

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
    GSMMAP_SS_UnitTest test;

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