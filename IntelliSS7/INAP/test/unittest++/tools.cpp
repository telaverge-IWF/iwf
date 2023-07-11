
#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif

#include <its++.h>

#include <Asn.h>
#include <AsnObject.h>
#include <AsnException.h>

#include "tools.h"

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

    sprintf(strBuf, "%02X", b);

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


/************************************************************************
 * Initialize Functions:
 *
 * The functions below are not the same as the Initialize methods in certain
 * INAP classes. The functions below are used to set the parameters of INAP
 * message classes to actual values the objects can have, not set the values
 * to zero or null.
 * 
 * The InitializeXXX() functions populates the parameters of an object of
 * a specific class and returns a pointer to that object. Objects of
 * the same class will have the same values for their member variables if
 * the InitializeXX() function for that class is used.
 *
 * The InitializeXXX() function for classes that contain member variables
 * defined by another class will include calls to InitializeXXX() functions
 * to populate those member variables.
 *
 * Check the following InitializeXXX() functions for explanations of general
 * case functions:
 *
 *    InitializeAdditionalCallingPartyNumber()
 *    InitializeApplicationTimer()
 *    InitializeBCSMEvent()
 *    InitializeCGEncountered()
 *    InitializeConnectArg_Extensions()
 *    InitializeRouteList()
 *
 * Other InitializeXXX() functions are variations of the functions listed
 * above.
 * 
 ************************************************************************/

AdditionalCallingPartyNumber* InitializeAdditionalCallingPartyNumber()
{
    // Value to set an AdditionalCallingPartyNumber from a
    // byte array to be converted into a vector
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    // Create a vector using the byte array and pass the result to a
    // constructor function for the class AdditionalCallingPartyNumber
    AdditionalCallingPartyNumber* acpn =
        new AdditionalCallingPartyNumber(ArrayToVector(array,
                                                       ARRAY_SIZE(array)));

    // Return pointer to AdditionalCallingPartyNumber
    return acpn;
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
    long valparam = 11;

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
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    CalledPartyNumber* cpn =
        new CalledPartyNumber(ArrayToVector(array, ARRAY_SIZE(array)));

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
    byte array[] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

    CallingPartyNumber* cpn =
        new CallingPartyNumber(ArrayToVector(array, ARRAY_SIZE(array)));

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
    // Create a pointer to a CGEncountered object
    CGEncountered* cge = new CGEncountered();

    // Set the value for this CGEncountered object
    cge->SetManualCGencountered();

    // Return pointer to CGEncountered
    return cge;
}


ConnectArg::Extensions* InitializeConnectArg_Extensions()
{
    // Create a pointer to an Extensions object
    // The class definition for the Extensions object is implemented
    // as public in the class ConnectArg
    // Extensions is also defined inside other INAP message class definitions
    // Extensions is a list of ExtensionField objects
    ConnectArg::Extensions* ext = new ConnectArg::Extensions();

    // Add an ExtensionField object to Extensions
    ext->AddElement(InitializeExtensionField());

    // Return pointer to Extensions
    return ext;
}


ControlType* InitializeControlType()
{
    ControlType* ct = new ControlType();

    ct->SetDestinationOverload();

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
    long valparam = 1;

    CutAndPaste* cap = new CutAndPaste(valparam);

    return cap;
}


DestinationRoutingAddress* InitializeDestinationRoutingAddress()
{
    // DestinationRoutingAddress is a list of CalledPartyNumber's

    DestinationRoutingAddress* dra = new DestinationRoutingAddress();

    dra->AddElement(InitializeCalledPartyNumber());

    return dra;
}


Digits* InitializeDigits()
{
    byte array[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    Digits* digits = new Digits(ArrayToVector(array, ARRAY_SIZE(array)));

    return digits;
}


DpSpecificCriteria* InitializeDpSpecificCriteria()
{
    DpSpecificCriteria* dsc = new DpSpecificCriteria();

    dsc->SetChoiceApplicationTimer(InitializeApplicationTimer());

    return dsc;
}


Duration* InitializeDuration()
{
    long val = 11;

    Duration* md = new Duration(val);

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
    EventTypeBCSM* etbcsm = new EventTypeBCSM();

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
    GapCriteria* gc = new GapCriteria();

    gc->SetChoiceGapOnService(InitializeGapOnService());

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
    return InitializeInteger4();
}


Interval* InitializeInterval()
{
    long val = 22;

    Interval* i = new Interval(val);

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
    MiscCallInfo* mci = new MiscCallInfo();

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
    ReportCondition* rc = new ReportCondition();

    rc->SetCanceled();

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
    RequestedInformationType* rit = new RequestedInformationType();

    rit->SetCallConnectedElapsedTime();

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
    long valparam = 3;

    ResourceID::TrunkGroupID* tgid = new ResourceID::TrunkGroupID(valparam);

    return tgid;
}


ResourceStatus* InitializeResourceStatus()
{
    ResourceStatus* rs = new ResourceStatus();

    rs->SetBusy();

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
    Tone* t = new Tone();

    t->SetToneID(InitializeInteger4());
    t->SetDuration(InitializeInteger4());

    return t;
}
