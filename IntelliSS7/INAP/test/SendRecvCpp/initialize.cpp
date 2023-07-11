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


#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif

#include <its++.h>

#include <asn-cpp/Asn.h>
#include <AsnObject.h>
#include <AsnException.h>

#include "initialize.h"
#include "SendRecv.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
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
    be->SetLegID(InitializeLegID());
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

    // Create a digits object
    cpn = new CalledPartyNumber(ArrayToVector(array, ARRAY_SIZE(array)));
    return cpn;
}


CallingPartyBusinessGroupID* InitializeCallingPartyBusinessGroupID()
{
    byte array[] = { 0x11 };

    CallingPartyBusinessGroupID* cpbgid =
        new CallingPartyBusinessGroupID(ArrayToVector(array,
                                                      ARRAY_SIZE(array)));
    return cpbgid;
}


CallingPartysCategory* InitializeCallingPartysCategory()
{
    byte array[] = { 0x22 };

    CallingPartysCategory* cpc =
        new CallingPartysCategory(ArrayToVector(array, ARRAY_SIZE(array)));

    return cpc;
}


CallingPartySubaddress* InitializeCallingPartySubaddress()
{
    byte array[] = { 0x33 };

    CallingPartySubaddress* cps =
        new CallingPartySubaddress(ArrayToVector(array, ARRAY_SIZE(array)));

    return cps;
}


CallingPartyNumber* InitializeCallingPartyNumber()
{
    byte array[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };
    CallingPartyNumber *cpn;

    // Create a digits object
    cpn = new CallingPartyNumber(ArrayToVector(array, ARRAY_SIZE(array)));
    return cpn;
}


Cause* InitializeCause()
{
    byte array[] = { 0x11, 0x22, 0x33, 0x44 };
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


DpSpecificCriteria* InitializeDpSpecificCriteria()
{
    long val = 0, choice = 0;
    DpSpecificCriteria* dsc = new DpSpecificCriteria();

    // Ask user to select DpSpecificCriteria
    cout << "Select DpSpecificCriteria:" << endl;
    cout << "[0] NumberOfDigits" << endl;
    cout << "[1] ApplicationTimer" << endl;
    cout << endl;
    cout << "-> ";
    choice = getSelection(0, 1);

    // Determine what the user selected
    if (val == 0)
    {
        // User selected number of digits

        // Ask user to enter number of digits
        cout << "Enter NumberOfDigits, integer [1..255]: ";
        val = getSelection(1, 255);
        dsc->SetChoiceNumberOfDigits(val);
        cout << endl;
    }
    else
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


EventSpecificInformationBCSM* InitializeEventSpecificInformationBCSM()
{   
    EventSpecificInformationBCSM* esib =
        new EventSpecificInformationBCSM();

    esib->SetChoiceCollectedInfoSpecificInfo
        (InitializeEventSpecificInformationBCSM_CollectedInfoSpecificInfo());

    return esib;
}


EventSpecificInformationBCSM::CollectedInfoSpecificInfo*
InitializeEventSpecificInformationBCSM_CollectedInfoSpecificInfo()
{
    EventSpecificInformationBCSM::CollectedInfoSpecificInfo* cis =
        new EventSpecificInformationBCSM::CollectedInfoSpecificInfo();

    cis->SetCalledPartynumber(InitializeCalledPartyNumber());

    return cis;
}


EventTypeBCSM* InitializeEventTypeBCSM()
{
    EventTypeBCSM *etbcsm = new EventTypeBCSM();

    etbcsm->SetTBusy();

    return etbcsm;
}


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


ForwardingCondition* InitializeForwardingCondition()
{
    ForwardingCondition* fc = new ForwardingCondition();

    fc->SetAny();

    return fc;
}


GapCriteria* InitializeGapCriteria()
{
    int gapCriteriaChoice = 0;
    GapCriteria *gc = new GapCriteria();
    GapCriteria gapCriteria;
    GapOnService gapOnService;
    long serviceKey = 0;
    long dpCriteriaChoice = 0;
    EventTypeBCSM *dpCriteria;
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

        // dpCriteria
        cout << "Select DpCriteria:" << endl;
        cout << "------------------" << endl;
        cout << "[ 1] origAttemptAuthorized" << endl;
        cout << "[ 2] collectedInfo" << endl;
        cout << "[ 3] analysedInformation" << endl;
        cout << "[ 4] routeSelectFailure" << endl;
        cout << "[ 5] oCalledPartyBusy" << endl;
        cout << "[ 6] oNoAnswer" << endl;
        cout << "[ 7] oAnswer" << endl;
        cout << "[ 8] oMidCall" << endl;
        cout << "[ 9] oDisconnect" << endl;
        cout << "[10] oAbandon" << endl;
        cout << "[12] termAttemptAuthorized" << endl;
        cout << "[13] tBusy" << endl;
        cout << "[14] tNoAnswer" << endl;
        cout << "[15] tAnswer" << endl;
        cout << "[16] tMidCall" << endl;
        cout << "[17] tDisconnect" << endl;
        cout << "[18] tAbandon" << endl;
        cout << endl;
        dpCriteriaChoice = getSelection(1, 18);

        // Create a new dpCriteria object using the choice made by the user
        dpCriteria = new EventTypeBCSM(dpCriteriaChoice);
        gapOnService.SetDpCriteria(dpCriteria);

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

        // Location Number
        callingAddressAndService.SetLocationNumber(InitializeLocationNumber());

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
    gos->SetDpCriteria(InitializeEventTypeBCSM());

    return gos;
}


GapTreatment* InitializeGapTreatment()
{
    GapTreatment* gt = new GapTreatment();

    gt->SetChoiceBoth(InitializeGapTreatment_Both());

    return gt;
}


GapTreatment::Both* InitializeGapTreatment_Both()
{
    GapTreatment::Both* b = new GapTreatment::Both();

    // Set parameters
    b->SetInformationToSend(InitializeInformationToSend());
    b->SetReleaseCause(InitializeCause());

    return b;
}


InformationToSend* InitializeInformationToSend()
{
    InformationToSend* its = new InformationToSend();

    its->SetChoiceTone(InitializeTone());

    return its;
}


InitialDPArg::Extensions* InitializeInitialDPArg_Extensions()
{
    InitialDPArg::Extensions* ext = new InitialDPArg::Extensions();

    ext->AddElement(InitializeExtensionField());

    return ext;
}


Integer4* InitializeInteger4()
{
    long valparam = 11;

    Integer4* integer4 = new Integer4(valparam);

    return integer4;
}


Integer4* InitializeServiceKey()
{
    long serviceKeyVal = 0;
    Integer4 *serviceKey;

    cout << "Enter a ServiceKey, integer[0..2147483647]: ";
    cin >> serviceKeyVal;
    cout << endl;

    serviceKey = new Integer4(serviceKeyVal);
    return serviceKey;
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


LegID* InitializeLegID()
{
    LegID* lid = new LegID();

    lid->SetChoiceSendingSideID(InitializeLegType());
    return lid;
}


LegType* InitializeLegType()
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

    mm->SetMonitorModeInterrupted();

    return mm;
}


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


RequestedInformation* InitializeRequestedInformation()
{
    RequestedInformation* ri = new RequestedInformation();

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
    cout << "[ 2] CallConnectedElapsedTime" << endl;
    cout << "[ 3] CalledAddress" << endl;
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


ResourceID* InitializeResourceID()
{
    ResourceID* rid = new ResourceID();

    rid->SetChoiceTrunkGroupID(InitializeResourceID_TrunkGroupID());

    return rid;
}


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


ScfID* InitializeScfID()
{
    byte array[] = { 0x11, 0x22, 0x33, 0x44 };

    ScfID* sid = new ScfID(ArrayToVector(array, ARRAY_SIZE(array)));

    return sid;
}


Tone* InitializeTone()
{
    long toneIdVal = 0, durationVal = 0;
    Tone *t = new Tone();

    // Ask user to enter a toneId
    cout << "Enter ToneID, integer [0..2147483647]: ";
    cin >> toneIdVal;
    t->SetToneID(toneIdVal);

    // Ask user to enter a duration value
    cout << "Enter Duration, integer [0..2147483647]: ";
    cin >> durationVal;
    t->SetDuration(durationVal);
    cout << endl;
    return t;
}
