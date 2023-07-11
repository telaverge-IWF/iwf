/*
 ****************************************************************************
 * DISCLAIMER:
 *
 * INTELLINET DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * INTELLINET BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *  
 ****************************************************************************/
#include <its++.h>

#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif


#include <itu/sccp.h>
#include <itu/tcap.h>
#include <tcap++.h>
#include <sccp++.h>

#include <Asn.h>
#include <AsnObject.h>
#include <AsnException.h>

/*
#include "initialize.h"
#include "SendRecv.h"
*/

/*
#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif
*/
#include <cap_cpp.h>
#include "initialize.h"
#include "SendRecv.h"

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace cap;
using namespace cap_v3;
#endif    // defined(ITS_NAMESPACE)


// Helper operator<< to print content of vector of bytes.
static std::string ByteToHexString(byte b)
{
    char strBuf[3];

    sprintf(strBuf, "%02x", b);

    return strBuf;
}

std::ostream& operator<< (std::ostream& os, const std::vector<byte>& vect)
{
    os << "{ ";

    for (int i = 0; i < vect.size(); i++)
    {
        os << "0x" << ByteToHexString(vect[i]).c_str();
        
        if (i != vect.size() - 1)
        {
            os << ",";
        }

        os << " ";
    }

    os << "}";

    return os;
}

//////////////////////////////////////////////////////////////////
//
//      Message Encode and Decode general functions
//
///////////////////////////////////////////////////////////////////
void MsgEncode(AsnObject* p, Octets** octets, string& str)
{
    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl << *p << endl;
    }

    ostrstream oss;
    oss << *p << '\0';

    str = oss.str();

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 BER.
    Octets* tmpOctets;

    tmpOctets = p->Encode();

#if 0
    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during encoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }
#endif


    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << endl << *tmpOctets << endl;
    }

    *octets = tmpOctets;
}



void MsgDecode(AsnObject* p, Octets* octets, string& str)
{
    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    
    // Decoding using ASN.1 BER.
    try
    {
        p->Decode(*octets);
    }
    catch (AsnDecodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during decoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    ////////////////////////////////////////////////////////
    // Print ASN.1 value after decoding.
    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value after decoding..." << endl;
        cout << endl << *p << endl;
    }

    ostrstream oss;
    oss << *p << '\0';

    str = oss.str();
}


// Compare string1 and string2, where one string contains an INAP message
// before encoding and the other string containing a message after decoding
void CompareStrings(const string& str1, const string& str2)
{
    if (str1 == str2)
    {
        cout << "Parameters before encoding and after decoding are IDENTICAL." 
             << endl << endl;
    }
    else
    {
        cout << "Parameters before encoding and after decoding are DIFFERENT." 
             << endl << endl;
    }
}

void
getCharDigits(byte *byteArray, int len)
{
    char digitStr[100] = "\0";

    // Initialize bytearray
    memset((char*)&byteArray, 0, len);

    // Ask the user to enter digist
    cout << "Enter up to " << len << " Digits:" << endl;
    cin >> digitStr;

    // Determine the number of digits the user entered
    len = strlen(digitStr);

    // Convert ascii values of digits into bytes
    // Convert the ascii character for each digit into a numerical
    // respresentation of each digit
    for (int i = 0; i < len; i++)
    {
        byteArray[i] = digitStr[i] - 0x30;
    }
}


/************************************************************************
 * Initialize Functions:
 *
 * The functions below are not the same as the Initialize methods in certain
 * INAP classes. The functions below are used to set the parameters of INAP
 * message classes to actual values the objects can have, not set the values
 * to zero or null. Some of the initialize functions will prompt the user to
 * provide data to set the parameters of an object.
 * 
 * The InitializeXXX() functions populates the parameters of an object of
 * a specific class and returns a pointer to that object. Objects of
 * the same class will have the same values for their member variables if
 * the InitializeXXX() function for that class is used and if that function
 * does not prompt the user for data.
 *
 * The InitializeXXX() function for classes that contain member variables
 * defined by another class will include calls to InitializeXXX() functions
 * to populate those member variables.
 *
 ************************************************************************/

AChBillingChargingCharacteristics* InitializeAChBillingChargingCharacteristics()
{
	// add switch for various options later
	byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    AChBillingChargingCharacteristics* ach =
        new AChBillingChargingCharacteristics(ArrayToVector(array, ARRAY_SIZE(array)));

    return ach;
}


AdditionalCallingPartyNumber* InitializeAdditionalCallingPartyNumber()
{
    // Return pointer to AdditionalCallingPartyNumber
    return InitializeDigits();
}


AlertingPattern* InitializeAlertingPattern()
{
    byte array[] = { 0x01, 0x02, 0x03 };

    AlertingPattern* ap =
        new AlertingPattern(ArrayToVector(array, ARRAY_SIZE(array)));

    return ap;
}


ApplicationTimer* InitializeApplicationTimer()
{
    // Value to set an ApplicationTimer object
    long valparam = 0;

    cout << "Enter ApplicationTimer, integer [0..2047]: ";
    cin >> valparam;
    cout << endl;

    // Create a pointer to an ApplicationTimer object
    ApplicationTimer* at = new ApplicationTimer(valparam);

    // Return pointer to ApplicationTimer
    return at;
}


BCSMEvent* InitializeBCSMEvent()
{
    // Create a pointer to a BCSMEvent
    BCSMEvent* be = new BCSMEvent();

    // Set parameters for this object using InitializeXXX() functions
    // for those parameters
    be->SetEventTypeBCSM(InitializeEventTypeBCSM());
    be->SetMonitorMode(InitializeMonitorMode());
    be->SetLegID(InitializeReceivingLegID());
    be->SetDpSpecificCriteria(InitializeDpSpecificCriteria());

    // Return the pointer to BCSMEvent
    return be;
}


BearerCapability* InitializeBearerCapability()
{
    BearerCapability* bc = new BearerCapability();

    bc->SetChoiceBearerCap(InitializeBearerCapability_BearerCap());

    return bc;
}


BearerCapability::BearerCap* InitializeBearerCapability_BearerCap()
{
    byte array[] = { 0x11, 0x22 };

    BearerCapability::BearerCap* bc =
        new BearerCapability::BearerCap(ArrayToVector(array,
                                                      ARRAY_SIZE(array)));
    return bc;
}

CalledPartyNumber* InitializeCalledPartyNumber()
{
    byte array[] = { 0x09, 0x08, 0x02, 0x07, 0x07, 0x02, 0x03 };
    CalledPartyNumber *cpn;

    // Create a CalledPartyNumber object
    cpn = new CalledPartyNumber(ArrayToVector(array, ARRAY_SIZE(array)));
    return cpn;
}

/*
CallingPartyBusinessGroupID* InitializeCallingPartyBusinessGroupID()
{
    byte array[] = { 0x11 };

    CallingPartyBusinessGroupID* cpbgid =
        new CallingPartyBusinessGroupID(ArrayToVector(array,
                                                      ARRAY_SIZE(array)));
    return cpbgid;
}
*/

CallingPartysCategory* InitializeCallingPartysCategory()
{
    byte array[] = { 0x22 };

    CallingPartysCategory* cpc =
        new CallingPartysCategory(ArrayToVector(array, ARRAY_SIZE(array)));

    return cpc;
}

/*
CallingPartySubaddress* InitializeCallingPartySubaddress()
{
    byte array[] = { 0x33 };

    CallingPartySubaddress* cps =
        new CallingPartySubaddress(ArrayToVector(array, ARRAY_SIZE(array)));

    return cps;
}
*/

CallingPartyNumber* InitializeCallingPartyNumber()
{
    byte array[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };
    CallingPartyNumber *cpn;

    // Create a digits object
    cpn = new CallingPartyNumber(ArrayToVector(array, ARRAY_SIZE(array)));
    return cpn;
}


CallResult* InitializeCallResult()
{
		// add switch for various options later
	byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
					 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c};

    CallResult* callResult =
        new CallResult(ArrayToVector(array, ARRAY_SIZE(array)));

    return callResult;
}

Cause* InitializeCause()
{
    byte array[] = { 0x11, 0x22};
    Cause* c = new Cause(ArrayToVector(array, ARRAY_SIZE(array)));
    return c;
}


CGEncountered* InitializeCGEncountered()
{
    long val = 0;
    CGEncountered *cge = new CGEncountered();

    // Ask user to select a value for CGEncountered
    cout << "Select CGEncountered:" << endl;
    cout << "[0] noCGencountered" << endl;
    cout << "[1] manualCGencountered" << endl;
    cout << "[2] scpOverload" << endl;
    cout << endl;
    cout << "-> ";
    cin >> val;
    cout << endl;

    // Set the value for this CGEncountered object
    cge = new CGEncountered(val);
    return cge;
}


CollectedDigits* InitializeCollectedDigits()
{
	
    CollectedDigits* cd = new CollectedDigits();
	cd->SetMinimumNbOfDigits(InitializeMinimumNbOfDigits());
	cd->SetMaximumNbOfDigits(InitializeMaximumNbOfDigits());
	/*
	cd->SetEndOfReplyDigit(InitializeEndOfReplyDigit());
	cd->SetCancelDigit(InitializeCancelDigit());
	cd->SetStartDigit(InitializeStartDigit());
	cd->SetFirstDigitTimeOut(InitializeFirstDigitTimeOut());
	cd->SetInterDigitTimeOut(InitializeInterDigitTimeOut());
    */
	cd->SetErrorTreatment(InitializeErrorTreatment());
	cd->SetInterruptableAnnInd(InitializeInterruptableAnnInd());
	cd->SetVoiceInformation(InitializeVoiceInformation());
	cd->SetVoiceBack(InitializeVoiceBack());

	return cd;
}

CollectedInfo* InitializeCollectedInfo()
{
	
    CollectedInfo* ci = new CollectedInfo();
	ci->SetChoiceCollectedDigits(InitializeCollectedDigits());
    return ci;
}

/*
ConnectArg::Extensions* InitializeConnectArg_Extensions()
{
    // Create a pointer to an Extensions object
    // The class definition for the Extensions object is implemented
    // as public in the class ConnectArg
    // Extensions is also defined inside other INAP message class definitions
    // Extensions is a list of ExtensionField objects
    ConnectArg::Extensions *ext = new ConnectArg::Extensions();

    // Add an ExtensionField object to Extensions
    ext->AddElement(InitializeExtensionField());
    return ext;
}
*/

ControlType* InitializeControlType()
{
    long valparam = 0;
    ControlType* ct;

    // Ask user to select a controltype
    cout << "Select ControlType:" << endl;
    cout << "-------------------" << endl;
    cout << "[0] sCPOverloaded" << endl;
    cout << "[1] manuallyInitiated" << endl;
    cout << "[2] destinationOverload" << endl;
    cout << endl;
    cout << "-> ";
    cin >> valparam;
    cout << endl;

    // create a controltype object using the user selection
    ct = new ControlType(valparam);
    return ct;
}

CorrelationID* InitializeCorrelationID()
{
    byte array[] = { 0x02, 0x03, 0x04, 0x05, 0x06 };

    CorrelationID* cid =
        new CorrelationID(ArrayToVector(array, ARRAY_SIZE(array)));

    return cid;
}

/*
CutAndPaste* InitializeCutAndPaste()
{
    long valparam;
    CutAndPaste* cap;

    // Ask user to enter an integer between 0-22
    cout << "Enter CutAndPaste, integer [0..22]: ";
    valparam = getSelection(0, 22);
    cout << endl;

    // Create a CutAndPaste object
    cap = new CutAndPaste(valparam);
    return cap;
}
*/

DestinationRoutingAddress* InitializeDestinationRoutingAddress()
{
    // DestinationRoutingAddress is a list of CalledPartyNumber's
    DestinationRoutingAddress* dra = new DestinationRoutingAddress();

    // Add a routing number to the list
    dra->AddElement(InitializeCalledPartyNumber());
    return dra;
}

Digits*
InitializeDigits()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    Digits *digits;

    // Create a digits object
    digits = new Digits(ArrayToVector(array, ARRAY_SIZE(array)));
    return digits;
}

PlayAnnouncementArg::DisconnectFromIPForbidden* InitializeDisconnectFromIPForbidden()
{
    
	PlayAnnouncementArg::DisconnectFromIPForbidden* dip = 
		new PlayAnnouncementArg::DisconnectFromIPForbidden(true);

    return dip;
}

PromptAndCollectUserInformationArg::DisconnectFromIPForbidden* 
InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden()
{
    
	PromptAndCollectUserInformationArg::DisconnectFromIPForbidden* dip = 
		new PromptAndCollectUserInformationArg::DisconnectFromIPForbidden(true);

    return dip;
}


DpSpecificCriteria* InitializeDpSpecificCriteria()
{
    
    DpSpecificCriteria* dsc = new DpSpecificCriteria();

    {
        // User selected application timer
        dsc->SetChoiceApplicationTimer(InitializeApplicationTimer());
    }
    return dsc;
}

Duration* InitializeDuration()
{
    long val = 0;
    Duration* md;

    // Ask user to enter duration time
    cout << "Enter duration, integer [-2..86400]: ";
    cin >> val;
    cout << endl;
    md = new Duration(val);
    return md;
}

ErrorTreatment* InitializeErrorTreatment()
{
	ErrorTreatment* et = new ErrorTreatment();
	et->SetHelp();

	return et;
}

EventSpecificInformationBCSM* InitializeEventSpecificInformationBCSM()
{   
    EventSpecificInformationBCSM* esib =
        new EventSpecificInformationBCSM();

    esib->SetChoiceRouteSelectFailureSpecificInfo
        (InitializeEventSpecificInformationBCSM_RouteSelectFailureSpecificInfo());

    return esib;
}


EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo*
InitializeEventSpecificInformationBCSM_RouteSelectFailureSpecificInfo()
{
    EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo* rsf =
        new EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo();

    rsf->SetFailureCause(InitializeCause());

    return rsf;
}


EventTypeBCSM* InitializeEventTypeBCSM()
{
    EventTypeBCSM *etbcsm = new EventTypeBCSM();
    etbcsm->SetTBusy();


    return etbcsm;
}

/*
ExtensionField* InitializeExtensionField()
{
    ExtensionField* ef = new ExtensionField();

    // Set parameters
    ef->SetCriticality(InitializeExtensionField_Criticality());
    ef->SetType(InitializeExtensionField_Type());
    ef->SetValue(InitializeExtensionField_Value());

    return ef;
}


ExtensionField::Criticality* InitializeExtensionField_Criticality()
{
    ExtensionField::Criticality* crit = new ExtensionField::Criticality();

    crit->SetCriticalityAbort();

    return crit;
}


ExtensionField::Type* InitializeExtensionField_Type()
{
    long valparam = 1;

    ExtensionField::Type* ef_t = new ExtensionField::Type(valparam);

    return ef_t;
}


ExtensionField::Value* InitializeExtensionField_Value()
{
    long val = 11;

    AsnInteger* asnInt = new AsnInteger(val);
    ExtensionField::Value* ef_v = new ExtensionField::Value(asnInt);

    return ef_v;
}
*/

FCIBillingChargingCharacteristics*
InitializeFCIBillingChargingCharacteristics()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    
	FCIBillingChargingCharacteristics* FCIbcc =
			new FCIBillingChargingCharacteristics(ArrayToVector(array, ARRAY_SIZE(array)));
    
    return FCIbcc;
}

/*
ForwardingCondition* InitializeForwardingCondition()
{
    ForwardingCondition* fc = new ForwardingCondition();

    fc->SetAny();

    return fc;
}
*/

ForwardServiceInteractionInd*  InitializeForwardServiceInteractionInd()
{
    ForwardServiceInteractionInd* fsi 
				= new ForwardServiceInteractionInd;

	byte cnfTreatmentIndicatorarray[] = { 0x01 };
	byte divTreatmentIndicatorarray[] = { 0x01 };
	byte cmpTreatmentIndicatorarray[] = { 0x01 };
    byte cprTreatmentIndicatorarray[] = { 0x01 };

	ForwardServiceInteractionInd:: ConferenceTreatmentIndicator* cti=
        new ForwardServiceInteractionInd:: ConferenceTreatmentIndicator(ArrayToVector(cnfTreatmentIndicatorarray,
																	ARRAY_SIZE(cnfTreatmentIndicatorarray)));
	ForwardServiceInteractionInd:: CallDiversionTreatmentIndicator* cdti=
        new ForwardServiceInteractionInd:: CallDiversionTreatmentIndicator(ArrayToVector(divTreatmentIndicatorarray, 
																  ARRAY_SIZE(divTreatmentIndicatorarray)));
	ForwardServiceInteractionInd:: CallCompletionTreatmentIndicator* ccti =
        new ForwardServiceInteractionInd:: CallCompletionTreatmentIndicator(ArrayToVector(cmpTreatmentIndicatorarray, 
																   ARRAY_SIZE(cmpTreatmentIndicatorarray)));
    ForwardServiceInteractionInd:: CallingPartyRestrictionIndicator* cpri =
        new ForwardServiceInteractionInd:: CallingPartyRestrictionIndicator(ArrayToVector(cprTreatmentIndicatorarray, 
																   ARRAY_SIZE(cprTreatmentIndicatorarray)));
	
    
    // Add the 4 objects to fsi ptr.
    fsi->SetConferenceTreatmentIndicator(cti);
    fsi->SetCallDiversionTreatmentIndicator(cdti);
    fsi->SetCallCompletionTreatmentIndicator(ccti);
    fsi->SetCallingPartyRestrictionIndicator(cpri);

	// populate other optional parameters later
	return fsi;
}

GapCriteria* InitializeGapCriteria()
{
    int gapCriteriaChoice = 0;
    GapCriteria *gc = new GapCriteria();
    GapCriteria gapCriteria;
    GapOnService gapOnService;
    long serviceKey = 0;
    long dpCriteriaChoice = 0;
    /* EventTypeBCSM *dpCriteria; */
    GapCriteria::CalledAddressAndService calledAddressAndService;
    GapCriteria::CallingAddressAndService callingAddressAndService;

    // GapCriteria
    cout << "Setting GapCriteria: (MANDATORY)" << endl;
    cout << "--------------------------------" << endl;

    // Ask user to select GapCriteria
    cout << "Select GapCriteria:" << endl;
    cout << "-------------------" << endl;
    cout << "[1] CalledAddressValue" << endl;
    cout << "[2] GapOnService" << endl;
    cout << "[3] CalledAddressAndService" << endl;
    cout << "[4] CallingAddressAndService" << endl;
    cout << endl;
    
    // Get user selection for gapCriteria
    gapCriteriaChoice = getSelection(1, 4);
    cout << endl;

    // Determine which gapCriteria the user selected
    switch (gapCriteriaChoice)
    {
    case 1:
        // CalledAddressValue
        gc->SetChoiceCalledAddressValue(InitializeDigits());
        break;

    case 2:
        // GapOnService
        cout << "Setting GapOnService:" << endl;
        cout << "---------------------" << endl;
        cout << endl;

        // ServiceKey
        gapOnService.SetServiceKey(InitializeServiceKey());

        // Select GapOnService for gapCriteria
        gc->SetChoiceGapOnService(gapOnService);
        break;

    case 3:
        // CalledAddressAndService

        // CalledAddressValue
        calledAddressAndService.SetCalledAddressValue(InitializeDigits());

        // ServiceKey
        calledAddressAndService.SetServiceKey(InitializeServiceKey());
        
        // Select CalledAddressAndService for gapCriteria
        gc->SetChoiceCalledAddressAndService(calledAddressAndService);
        break;

    case 4:
        // CallingAddressAndService

        // CallingAddressValue
        callingAddressAndService.SetCallingAddressValue(InitializeDigits());

        // ServiceKey
        callingAddressAndService.SetServiceKey(serviceKey);

        // Select CallingAddressAndService for gapCriteria
        gc->SetChoiceCallingAddressAndService(callingAddressAndService);
        break;
    }

    return gc;
}


GapIndicators* InitializeGapIndicators()
{
    GapIndicators* gi = new GapIndicators();

    // Set parameters
    gi->SetDuration(InitializeDuration());
    gi->SetGapInterval(InitializeInterval());

    return gi;
}


GapOnService* InitializeGapOnService()
{
    GapOnService* gos = new GapOnService();

    // Set Parameters
    gos->SetServiceKey(InitializeServiceKey());

    return gos;
}


GapTreatment* InitializeGapTreatment()
{
    GapTreatment* gt = new GapTreatment();
	int val;

	// Ask user to select reportcondition
    cout << "Select Gap Treatment:" << endl;
    cout << "-----------------------" << endl;
    cout << "[0] InformationToSend" << endl;
    cout << "[1] ReleaseCause" << endl;
    cout << endl;
    cout << "-> ";
    cin >> val;
    cout << endl;
    
	if (val ==0)
		gt->SetChoiceInformationToSend(InitializeInformationToSend());
	else
		gt->SetChoiceReleaseCause(InitializeCause());

    return gt;
}

/*
GapTreatment::Both* InitializeGapTreatment_Both()
{
    GapTreatment::Both* b = new GapTreatment::Both();

    // Set parameters
    b->SetInformationToSend(InitializeInformationToSend());
    b->SetReleaseCause(InitializeCause());

    return b;
}
*/

InformationToSend* InitializeInformationToSend()
{
    InformationToSend* its = new InformationToSend();

    its->SetChoiceTone(InitializeTone());

    return its;
}

/*
InitialDPArg::Extensions* InitializeInitialDPArg_Extensions()
{
    InitialDPArg::Extensions* ext = new InitialDPArg::Extensions();

    ext->AddElement(InitializeExtensionField());

    return ext;
}
*/

Integer4* InitializeInteger4()
{
    long valparam = 11;

    Integer4* integer4 = new Integer4(valparam);

    return integer4;
}

/*
Integer4* InitializeToneId()
{
    long valparam;

	// Ask user to enter duration time
    cout << "Enter duration, integer [-2..86400]: ";
    cin >> valparam;
    cout << endl;
    Integer4* toneId = new Integer4(valparam);

    return toneId;
}

Integer4* InitializeDuration()
{
    long valparam ;

	// Ask user to enter duration time
    cout << "Enter duration, integer [-2..86400]: ";
    cin >> valparam;
    cout << endl;

    Integer4* duration = new Integer4(valparam);

    return duration;
}
*/



CollectedDigits::InterruptableAnnInd* InitializeInterruptableAnnInd()
{
	CollectedDigits::InterruptableAnnInd* iai
		= new CollectedDigits::InterruptableAnnInd(true);

	return iai;
}


Interval* InitializeInterval()
{
    long val = 0;
    Interval *i;

    // Ask user to provide interval value
    cout << "Enter Interval, integer [-1..32000]: ";
    cin >> val;
    cout << endl;

    i = new Interval(val);
    return i;
}


LegID* InitializeReceivingLegID()
{
    LegID* lid = new LegID();

    lid->SetChoiceReceivingSideID(InitializeReceivingLegType());
    return lid;
}

LegID* InitializeSendingLegID()
{
    LegID* lid = new LegID();

    lid->SetChoiceSendingSideID(InitializeSendingLegType());
    return lid;
}

LegType* InitializeReceivingLegType()
{
    byte array[] = { 0x02 };

    LegType* lt = new LegType(ArrayToVector(array, ARRAY_SIZE(array)));
    return lt;
}

LegType* InitializeSendingLegType()
{
    byte array[] = { 0x01 };

    LegType* lt = new LegType(ArrayToVector(array, ARRAY_SIZE(array)));
    return lt;
}

LocationNumber* InitializeLocationNumber()
{
    byte array[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

    LocationNumber* ln = 
        new LocationNumber(ArrayToVector(array, ARRAY_SIZE(array)));
    
    return ln;
}

CollectedDigits::MinimumNbOfDigits* InitializeMinimumNbOfDigits()
{
    long valparam;
    CollectedDigits::MinimumNbOfDigits* mnd;

    // Ask user to enter an integer between 1-30
    cout << "Enter minimum number of digits, integer [1..30]: ";
    valparam = getSelection(1, 30);
    cout << endl;

    mnd = new CollectedDigits::MinimumNbOfDigits(valparam);
    return mnd;
}

CollectedDigits::MaximumNbOfDigits* InitializeMaximumNbOfDigits()
{
    long valparam;
    CollectedDigits::MaximumNbOfDigits* mxd;

    // Ask user to enter an integer between 1-30
    cout << "Enter maximum number of digits, integer [1..30]: ";
    valparam = getSelection(1, 30);
    cout << endl;

    mxd = new CollectedDigits::MaximumNbOfDigits(valparam);
    return mxd;
}

MiscCallInfo* InitializeMiscCallInfo()
{
    MiscCallInfo *mci = new MiscCallInfo();

    // Set parameters
    mci->SetDpAssignment(InitializeMiscCallInfo_DpAssignment());
    mci->SetMessageType(InitializeMiscCallInfo_MessageType());

    return mci;
}


MiscCallInfo::DpAssignment* InitializeMiscCallInfo_DpAssignment()
{
    MiscCallInfo::DpAssignment* dpa = new MiscCallInfo::DpAssignment();

    dpa->SetGroupBased();

    return dpa;
}


MiscCallInfo::MessageType* InitializeMiscCallInfo_MessageType()
{
    MiscCallInfo::MessageType* mt = new MiscCallInfo::MessageType();

    mt->SetRequest();

    return mt;
}


MonitorMode* InitializeMonitorMode()
{
    MonitorMode* mm = new MonitorMode();

    mm->SetInterrupted();

    return mm;
}

/*
ReportCondition* InitializeReportCondition()
{
    long val = 0;
    ReportCondition *rc;

    // Ask user to select reportcondition
    cout << "Select ReportCondition:" << endl;
    cout << "-----------------------" << endl;
    cout << "[0] statusReport" << endl;
    cout << "[1] timerExpired" << endl;
    cout << "[2] canceled" << endl;
    cout << endl;
    cout << "-> ";
    cin >> val;
    cout << endl;
    
    rc = new ReportCondition(val);
    return rc;
}
*/

OriginalCalledPartyID* InitializeOriginalCalledPartyID()
{
	byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    
    // Create a digits object
    OriginalCalledPartyID* originalCalledPartyID = new OriginalCalledPartyID(ArrayToVector(array, ARRAY_SIZE(array)));
    return originalCalledPartyID;
}

PlayAnnouncementArg::RequestAnnouncementComplete* InitializeRequestAnnouncementComplete()
{
	
	PlayAnnouncementArg::RequestAnnouncementComplete* rac = 
		new PlayAnnouncementArg::RequestAnnouncementComplete(false);

    return rac;
}

RequestedInformation* InitializeRequestedInformation()
{
	RequestedInformation* ri =
		new RequestedInformation();

    // Set parameters
    ri->SetRequestedInformationType(InitializeRequestedInformationType());
    ri->SetRequestedInformationValue(InitializeRequestedInformationValue());

    return ri;
}

RequestedInformationList* InitializeRequestedInformationList()
{
    RequestedInformationList* ril = new RequestedInformationList();

    ril->AddElement(InitializeRequestedInformation());

    return ril;
}


RequestedInformationType* InitializeRequestedInformationType()
{
    long ritVal = 0;
    RequestedInformationType* rit;

    // RequestedInformationType
    // Ask user to select RequestedInformationType value
    cout << "Select RequestedInformationType Value:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "[ 0] CallAttemptElapsedTime" << endl;
    cout << "[ 1] CallStopTime" << endl;
    cout << "[30] ReleaseCause" << endl;
    cout << endl;
    cout << "-> ";
    cin >> ritVal;
    cout << endl;

    // Set the enumerated value for RequestedInformationType using the user
    // selected value
    rit = new RequestedInformationType(ritVal);
    return rit;
}


RequestedInformationTypeList* InitializeRequestedInformationTypeList()
{
    RequestedInformationTypeList* ritl = new RequestedInformationTypeList();

    ritl->AddElement(InitializeRequestedInformationType());

    return ritl;
}


RequestedInformationValue* InitializeRequestedInformationValue()
{
    RequestedInformationValue* riv = new RequestedInformationValue();

    riv->SetChoiceReleaseCauseValue(InitializeCause());

    return riv;
}


RequestReportBCSMEventArg::BcsmEvents*
InitializeRequestReportBCSMEventArg_BcsmEvents()
{
    RequestReportBCSMEventArg::BcsmEvents* be =
        new RequestReportBCSMEventArg::BcsmEvents();

    be->AddElement(InitializeBCSMEvent());

    return be;
}

/*
ResourceID::TrunkGroupID* InitializeResourceID_TrunkGroupID()
{
    long val = 0;
    ResourceID::TrunkGroupID *tgid;

    // Ask user to select trunkgroup
    cout << "Enter TrunkGroupID, integer: ";
    cin >> val;

    cout << endl;
    tgid = new ResourceID::TrunkGroupID(val);
    return tgid;
}
*/

ConnectToResourceArg::ResourceAddress* InitializeResourceAddress()
{
    long val = 0;
    ConnectToResourceArg::ResourceAddress *ra;

    ra = new ConnectToResourceArg::ResourceAddress();
	ra->SetChoiceIpRoutingAddress(InitializeCalledPartyNumber());
    return ra;
}

/*
ResourceStatus* InitializeResourceStatus()
{
    long val = 0;
    ResourceStatus *rs;

    cout << "Select ResourceStatus:" << endl;
    cout << "----------------------" << endl;
    cout << "[0] Busy" << endl;
    cout << "[1] Idle" << endl;
    cout << endl;
    cout << "-> ";
    cin >> val;
    cout << endl;

    rs = new ResourceStatus(val);
    return rs;
}


RouteList* InitializeRouteList()
{
    // Create 3 byte arrays to be converted into RouteList::OCTETSTRING
    byte array1[] = { 0x01, 0x02, 0x03 };
    byte array2[] = { 0x11, 0x22, 0x33, 0x44 };
    byte array3[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

    // Create pointers to RouteList::OCTETSTRING objects
    RouteList::OCTETSTRING* os1 =
        new RouteList::OCTETSTRING(ArrayToVector(array1, ARRAY_SIZE(array1)));
    RouteList::OCTETSTRING* os2 =
        new RouteList::OCTETSTRING(ArrayToVector(array2, ARRAY_SIZE(array2)));
    RouteList::OCTETSTRING* os3 =
        new RouteList::OCTETSTRING(ArrayToVector(array3, ARRAY_SIZE(array3)));

    // Create a pointer to a RouteList object
    RouteList* rl = new RouteList();
    
    // Add the 3 RouteList::OCTETSTRING objects to RouteList
    rl->AddElement(os1);
    rl->AddElement(os2);
    rl->AddElement(os3);

    // return the pointer to RouteList
    return rl;
}
*/

SCIBillingChargingCharacteristics* InitializeSciBillingChargingCharacteristics()
{
	byte array1[] = { 0x11, 0x22, 0x33, 0x44 };

	SCIBillingChargingCharacteristics* scibcc = 
		new SCIBillingChargingCharacteristics(ArrayToVector(array1, ARRAY_SIZE(array1)));

	return scibcc;
}

ScfID* InitializeScfID()
{
    byte array[] = { 0x11, 0x22, 0x33, 0x44 };

    ScfID* sid = new ScfID(ArrayToVector(array, ARRAY_SIZE(array)));

    return sid;
}



ServiceInteractionIndicatorsTwo* InitializeServiceInteractionIndicatorsTwo()
{
	ServiceInteractionIndicatorsTwo* si2 
				= new ServiceInteractionIndicatorsTwo;

	byte holdTreatmentIndicatorarray[] = { 0x01 };
	byte cwTreatmentIndicatorarray[] = { 0x01 };
	byte ectTreatmentIndicatorarray[] = { 0x01 };
    long valparm = 1;

	ServiceInteractionIndicatorsTwo:: HoldTreatmentIndicator* hti=
        new ServiceInteractionIndicatorsTwo::HoldTreatmentIndicator(ArrayToVector(holdTreatmentIndicatorarray,
																	ARRAY_SIZE(holdTreatmentIndicatorarray)));
	ServiceInteractionIndicatorsTwo:: CwTreatmentIndicator* cwti=
        new ServiceInteractionIndicatorsTwo::CwTreatmentIndicator(ArrayToVector(cwTreatmentIndicatorarray, 
																  ARRAY_SIZE(cwTreatmentIndicatorarray)));
	ServiceInteractionIndicatorsTwo:: EctTreatmentIndicator* ecti =
        new ServiceInteractionIndicatorsTwo::EctTreatmentIndicator(ArrayToVector(ectTreatmentIndicatorarray, 
																   ARRAY_SIZE(ectTreatmentIndicatorarray)));
    ConnectedNumberTreatmentInd* cnti =
        new ConnectedNumberTreatmentInd(valparm);
	
    
    // Add the objects to si2 ptr.
    si2->SetHoldTreatmentIndicator(hti);
    si2->SetCwTreatmentIndicator(cwti);
    si2->SetEctTreatmentIndicator(ecti);
    si2->SetConnectedNumberTreatmentInd(cnti);
    si2->SetForwardServiceInteractionInd(InitializeForwardServiceInteractionInd());

	// populate other optional parameters later
	return si2;

}

ServiceKey* InitializeServiceKey()
{
    long serviceKeyVal = 0;
    ServiceKey *serviceKey;

    cout << "Enter a ServiceKey, integer[0..2147483647]: ";
    cin >> serviceKeyVal;
    cout << endl;

    serviceKey = new ServiceKey(serviceKeyVal);
    return serviceKey;
}

TimerID* InitializeTimerID()
{
	TimerID* tid = new TimerID();
	tid->SetTssf();

	return tid;
}


Tone* InitializeTone()
{
    
    Tone *t = new Tone;

	// Ask user to enter tone-id
    t->SetToneID(InitializeInteger4());

    // Ask user to enter an optional  duration value
    
    t->SetDuration(InitializeInteger4());
    cout << endl;
    return t;
}

CollectedDigits::VoiceInformation* InitializeVoiceInformation()
{
	CollectedDigits::VoiceInformation* vi
		= new CollectedDigits::VoiceInformation(true);


	return vi;
}

CollectedDigits::VoiceBack* InitializeVoiceBack()
{
	CollectedDigits::VoiceBack* vb
		= new CollectedDigits::VoiceBack(false);


	return vb;
}