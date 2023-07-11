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
    
    if (Cmd("ATM", "ActivateTraceModeArg"))
    { 
        ////////////////////////////////////////
        // Avtivate Trace Mode Encode part.
        ActivateTraceModeArg* actTraceModeArg =
                new ActivateTraceModeArg();

        actTraceModeArg->SetImsi(InitializeIMSI()); 
        actTraceModeArg->SetTraceReference(InitializeTraceReference());
        actTraceModeArg->SetTraceType(InitializeTraceType());
        actTraceModeArg->SetOmc_Id(InitializeOmc_Id());
        actTraceModeArg->SetExtensionContainer(InitializeExtensionContainer());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(actTraceModeArg, &octets, str1);

        // Release all allocated memory till current point.
        delete actTraceModeArg;
        actTraceModeArg = NULL;

        ////////////////////////////////////////
        // ActivateTraceModeArg Decode part.

        ActivateTraceModeArg* actTraceModeArgDec =
                new ActivateTraceModeArg();

        MsgDecode(actTraceModeArgDec, octets, str2);

        // Release all allocated memory.
        delete actTraceModeArgDec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("ATMRES", "ActivateTraceModeRes"))
    {
        ////////////////////////////////////////
        // AvtivateTraceModeRes Encode part.

        ActivateTraceModeRes* actTraceModeRes =
                new ActivateTraceModeRes();

        /////// Set extensionContainer    
        actTraceModeRes->SetExtensionContainer(InitializeExtensionContainer());

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(actTraceModeRes, &octets, str1);
    
        // Release all allocated memory till current point.
        delete actTraceModeRes;
        actTraceModeRes = NULL;

        ////////////////////////////////////////
        // ActivateTraceModeRes Decode part.

        ActivateTraceModeRes* actTraceModeResDec =
                new ActivateTraceModeRes();
    
        MsgDecode(actTraceModeResDec, octets, str2);
           
        // Release all allocated memory.
        delete actTraceModeResDec;
        delete octets;

        CompareStrings(str1, str2);
    }

    if (Cmd("DATM", "DeactivateTraceModeArg"))
    {
        ////////////////////////////////////////
        // Deactivate Trace Mode Encode part.

        DeactivateTraceModeArg* deactTraceModeArg =
                new DeactivateTraceModeArg();

        deactTraceModeArg->SetImsi(InitializeIMSI()); 
        deactTraceModeArg->SetTraceReference(InitializeTraceReference());
        deactTraceModeArg->SetExtensionContainer(InitializeExtensionContainer());
    
        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(deactTraceModeArg, &octets, str1);

        // Release all allocated memory till current point.
        delete deactTraceModeArg;
        deactTraceModeArg = NULL;

        ////////////////////////////////////////
        // DeactivateTraceModeArg Decode part.

        DeactivateTraceModeArg* deactTraceModeArgDec =
                new DeactivateTraceModeArg();

        MsgDecode(deactTraceModeArgDec, octets, str2);
       
        // Release all allocated memory.
        delete deactTraceModeArgDec;
        delete octets;

        CompareStrings(str1, str2);
    }


    if (Cmd("DATMRES", "DeactivateTraceModeRes"))
    {    
        ////////////////////////////////////////
        // DeactivateTraceModeRes Encode part.

        DeactivateTraceModeRes* deactTraceModeRes =
                new DeactivateTraceModeRes();

        /////// Set extensionContainer    
        deactTraceModeRes->SetExtensionContainer(InitializeExtensionContainer());

        Octets* octets = NULL;
        string str1, str2;

        MsgEncode(deactTraceModeRes, &octets, str1);
    
        // Release all allocated memory till current point.
        delete deactTraceModeRes;
        deactTraceModeRes = NULL;

        ////////////////////////////////////////
        // ActivateTraceModeRes Decode part.

        DeactivateTraceModeRes* deactTraceModeResDec =
                new DeactivateTraceModeRes();
    
        MsgDecode(deactTraceModeResDec, octets, str2);

        // Release all allocated memory.
        delete deactTraceModeResDec;
        delete octets;

        CompareStrings(str1, str2);
    }
}

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