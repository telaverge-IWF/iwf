//
// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).
//
// Do not edit!
//
//
//
// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.
//
//


#include <inap_cs2_trigger_type.h>

#include <AsnDescEnumerated.h>


using namespace its;
using namespace inap_cs2;



AsnDescObject* TriggerType::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        if (CheckLicense(ITS_LIC_CAP_INAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new TriggerType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        staticDesc._valueSet.insert(2);
        staticDesc._valueSet.insert(3);
        staticDesc._valueSet.insert(12);
        staticDesc._valueSet.insert(13);
        staticDesc._valueSet.insert(14);
        staticDesc._valueSet.insert(17);
        staticDesc._valueSet.insert(18);
        staticDesc._valueSet.insert(25);
        staticDesc._valueSet.insert(26);
        staticDesc._valueSet.insert(27);
        staticDesc._valueSet.insert(29);
        staticDesc._valueSet.insert(30);
        staticDesc._valueSet.insert(31);
        staticDesc._valueSet.insert(32);
        staticDesc._valueSet.insert(33);
        staticDesc._valueSet.insert(34);
        staticDesc._valueSet.insert(35);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"featureActivation", 0}, {"verticalServiceCode", 1}, {"customizedAccess", 2}, {"customizedIntercom", 3}, {"emergencyService", 12}, {"aFR", 13}, {"sharedIOTrunk", 14}, {"offHookDelay", 17}, {"channelSetupPRI", 18}, {"tNoAnswer", 25}, {"tBusy", 26}, {"oCalledPartyBusy", 27}, {"oNoAnswer", 29}, {"originationAttemptAuthorized", 30}, {"oAnswer", 31}, {"oDisconnect", 32}, {"termAttemptAuthorized", 33}, {"tAnswer", 34}, {"tDisconnect", 35}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        static AsnDescEnumerated::NamedNumber namedNumberExtList[] = {{NULL, 0}};
        staticDesc.SetNamedNumberExtList(namedNumberExtList);
        staticDesc.SetTypeName("TriggerType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

long TriggerType::Get(const std::string& valueName) const
{
    if (valueName == "featureActivation")
    {
        return 0;
    }
    else if (valueName == "verticalServiceCode")
    {
        return 1;
    }
    else if (valueName == "customizedAccess")
    {
        return 2;
    }
    else if (valueName == "customizedIntercom")
    {
        return 3;
    }
    else if (valueName == "emergencyService")
    {
        return 12;
    }
    else if (valueName == "aFR")
    {
        return 13;
    }
    else if (valueName == "sharedIOTrunk")
    {
        return 14;
    }
    else if (valueName == "offHookDelay")
    {
        return 17;
    }
    else if (valueName == "channelSetupPRI")
    {
        return 18;
    }
    else if (valueName == "tNoAnswer")
    {
        return 25;
    }
    else if (valueName == "tBusy")
    {
        return 26;
    }
    else if (valueName == "oCalledPartyBusy")
    {
        return 27;
    }
    else if (valueName == "oNoAnswer")
    {
        return 29;
    }
    else if (valueName == "originationAttemptAuthorized")
    {
        return 30;
    }
    else if (valueName == "oAnswer")
    {
        return 31;
    }
    else if (valueName == "oDisconnect")
    {
        return 32;
    }
    else if (valueName == "termAttemptAuthorized")
    {
        return 33;
    }
    else if (valueName == "tAnswer")
    {
        return 34;
    }
    else if (valueName == "tDisconnect")
    {
        return 35;
    }
    else
    {
        bool invalid_value_name = false;
        ITS_ASSERT(invalid_value_name);

        return 0;
    }
}

std::string TriggerType::Get(long value) const
{
    if (value == 0)
    {
        return "featureActivation";
    }
    else if (value == 1)
    {
        return "verticalServiceCode";
    }
    else if (value == 2)
    {
        return "customizedAccess";
    }
    else if (value == 3)
    {
        return "customizedIntercom";
    }
    else if (value == 12)
    {
        return "emergencyService";
    }
    else if (value == 13)
    {
        return "aFR";
    }
    else if (value == 14)
    {
        return "sharedIOTrunk";
    }
    else if (value == 17)
    {
        return "offHookDelay";
    }
    else if (value == 18)
    {
        return "channelSetupPRI";
    }
    else if (value == 25)
    {
        return "tNoAnswer";
    }
    else if (value == 26)
    {
        return "tBusy";
    }
    else if (value == 27)
    {
        return "oCalledPartyBusy";
    }
    else if (value == 29)
    {
        return "oNoAnswer";
    }
    else if (value == 30)
    {
        return "originationAttemptAuthorized";
    }
    else if (value == 31)
    {
        return "oAnswer";
    }
    else if (value == 32)
    {
        return "oDisconnect";
    }
    else if (value == 33)
    {
        return "termAttemptAuthorized";
    }
    else if (value == 34)
    {
        return "tAnswer";
    }
    else if (value == 35)
    {
        return "tDisconnect";
    }
    else
    {
        bool invalid_value = false;
        ITS_ASSERT(invalid_value);

        return "";
    }
}

std::string TriggerType::GetExt(long value) const
{
    return "";
}





