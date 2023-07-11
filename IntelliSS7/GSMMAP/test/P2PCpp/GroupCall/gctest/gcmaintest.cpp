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
     if (Cmd("PGCA", "PrepareGroupCallArg"))
    {
        ///////////////////////////////////////////////////
        // Activate PrepareGroupCallArg Encode part.

        PrepareGroupCallArg*  pgc_arg= new PrepareGroupCallArg();

        // Set message parameters
        pgc_arg->SetTeleservice(InitializeExt_TeleserviceCode());
        pgc_arg->SetAsciCallReference(InitializeAsciCallReference());
        pgc_arg->SetCodec_Info(InitializeCODEC_Info());
        pgc_arg->SetCipheringAlgorithm(InitializeCipheringAlgorithm());
        pgc_arg->SetGroupKeyNumber(InitializeGroupKeyNumber());
        pgc_arg->SetGroupKey(InitializeKc());
        pgc_arg->SetPriority(InitializeEmlpp_Priority());
        pgc_arg->SetUplinkFree(InitializeUplinkFree());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(pgc_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete pgc_arg;
        pgc_arg = NULL;

        ////////////////////////////////////////
        // PrepareGroupCallArg Decode part.

        PrepareGroupCallArg* pgc_arg_dec = new PrepareGroupCallArg();

        MsgDecode(pgc_arg_dec, octets, str2);

        // Release all allocated memory.
        delete pgc_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    
    
    if (Cmd("PGCR", "PrepareGroupCallRes"))
    {

        ///////////////////////////////////////////////////
        // Activate PrepareGroupCallRes Encode part.

        PrepareGroupCallRes* pgc_res = new PrepareGroupCallRes();

        // Set message parameters
        pgc_res->SetGroupCallNumber(InitializeISDN_AddressString());
        //ExtensionContainer, not used


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(pgc_res, &octets, str1);

        // Release all allocated memory till current point.
        delete pgc_res;
        pgc_res = NULL;

        ////////////////////////////////////////
        // PrepareGroupCallRes Decode part.

        PrepareGroupCallRes* pgc_res_dec = new PrepareGroupCallRes();

        MsgDecode(pgc_res_dec, octets, str2);

        // Release all allocated memory.
        delete pgc_res_dec;
        delete octets;

        CompareStrings(str1, str2);

    }


    if (Cmd("SGCESA", "SendGroupCallEndSignalArg"))
    {

        ///////////////////////////////////////////////////
        // Activate SendGroupCallEndSignalArg Encode part.

        SendGroupCallEndSignalArg* sgces_arg = new SendGroupCallEndSignalArg();

        // Set message parameters
        sgces_arg->SetImsi(InitializeIMSI());
        //ExtensionContainer, not used


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sgces_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete sgces_arg;
        sgces_arg = NULL;

        ////////////////////////////////////////
        // SendGroupCallEndSignalArg Decode part.

        SendGroupCallEndSignalArg* sgces_arg_dec =
            new SendGroupCallEndSignalArg();

        MsgDecode(sgces_arg_dec, octets, str2);

        // Release all allocated memory.
        delete sgces_arg_dec;
        delete octets;

        CompareStrings(str1, str2);
    }

    
    if (Cmd("SGCESR", "SendGroupCallEndSignalRes"))
    {

        ///////////////////////////////////////////////////
        // Activate SendGroupCallEndSignalRes Encode part.

        SendGroupCallEndSignalRes* sgces_res = new SendGroupCallEndSignalRes();

        // Set message parameters
        sgces_res->SetExtensionContainer(InitializeExtensionContainer());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(sgces_res, &octets, str1);

        // Release all allocated memory till current point.
        delete sgces_res;
        sgces_res = NULL;

        ////////////////////////////////////////
        // SendGroupCallEndSignalRes Decode part.

        SendGroupCallEndSignalRes* sgces_res_dec =
            new SendGroupCallEndSignalRes();

        MsgDecode(sgces_res_dec, octets, str2);

        // Release all allocated memory.
        delete sgces_res_dec;
        delete octets;

        CompareStrings(str1, str2);

    }


    if (Cmd("FGCSA", "ForwardGroupCallSignallingArg"))
    {

        ///////////////////////////////////////////////////
        // Activate ForwardGroupCallSignallingArg Encode part.

        ForwardGroupCallSignallingArg* fgcs_arg =
            new ForwardGroupCallSignallingArg();

        // Set message parameters
        fgcs_arg->SetImsi(InitializeIMSI());
        fgcs_arg->SetUplinkRequestAck(InitializeFGCSAUplinkRequestAck());
        fgcs_arg->SetUplinkReleaseIndication
            (InitializeFGCSAUplinkReleaseIndication());
        fgcs_arg->SetUplinkRejectCommand(InitializeFGCSAUplinkRejectCommand());
        fgcs_arg->SetUplinkSeizedCommand(InitializeFGCSAUplinkSeizedCommand());
        fgcs_arg->SetUplinkReleaseCommand
            (InitializeFGCSAUplinkReleaseCommand());


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(fgcs_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete fgcs_arg;
        fgcs_arg = NULL;

        ////////////////////////////////////////
        // ForwardGroupCallSignallingArg Decode part.

        ForwardGroupCallSignallingArg* fgcs_arg_dec =
            new ForwardGroupCallSignallingArg();

        MsgDecode(fgcs_arg_dec, octets, str2);

        // Release all allocated memory.
        delete fgcs_arg_dec;
        delete octets;

        CompareStrings(str1, str2);

    }

    
    if (Cmd("PGCSA", "ProcessGroupCallSignallingArg"))
    {

        ///////////////////////////////////////////////////
        // Activate ProcessGroupCallSignallingArg Encode part.

        ProcessGroupCallSignallingArg* pgcs_arg =
            new ProcessGroupCallSignallingArg();

        // Set message parameters
        pgcs_arg->SetUplinkRequest(InitializePGCSAUplinkRequest());
        pgcs_arg->SetUplinkReleaseIndication
            (InitializePGCSAUplinkReleaseIndication());
        pgcs_arg->SetReleaseGroupCall(InitializePGCSAReleaseGroupCall());
        // ExtensionContainer, not used


        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(pgcs_arg, &octets, str1);

        // Release all allocated memory till current point.
        delete pgcs_arg;
        pgcs_arg = NULL;

        ////////////////////////////////////////
        // ProcessGroupCallSignallingArg Decode part.

        ProcessGroupCallSignallingArg* pgcs_arg_dec =
            new ProcessGroupCallSignallingArg();

        MsgDecode(pgcs_arg_dec, octets, str2);

        // Release all allocated memory.
        delete pgcs_arg_dec;
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