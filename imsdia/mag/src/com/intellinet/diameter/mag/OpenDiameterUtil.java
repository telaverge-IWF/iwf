package com.intellinet.diameter.mag;

import com.intellinet.diameter.mag.node.*;


public class OpenDiameterUtil {
    public static String getDictionaryTypeName(PAvpType node) {
        if (node instanceof AOctetStringAvpType) {
            return "OctetString";
        } else if (node instanceof AInteger32AvpType) {
            return "Integer32";
        } else if (node instanceof AInteger64AvpType) {
            return "Integer64";
        } else if (node instanceof AUnsigned32AvpType) {
            return "Unsigned32";
        } else if (node instanceof AUnsigned64AvpType) {
            return "Unsigned64";
        } else if (node instanceof AFloat32AvpType) {
            return "Float32";
        } else if (node instanceof AFloat64AvpType) {
            return "Float64";
        } else if (node instanceof AAddressAvpType) {
            return "Address";
        } else if (node instanceof ATimeAvpType) {
            return "Time";
        } else if (node instanceof AUtf8StringAvpType) {
            return "UTF8String";
        } else if (node instanceof ADiameterIdAvpType) {
            return "DiameterIdentity";
        } else if (node instanceof ADiameterUriAvpType) {
            return "DiameterURI";
        } else if (node instanceof AIpFilterRuleAvpType) {
            return "IPFilterRule";
        //} else if (node instanceof AQosFilterRuleAvpType) {
        //    return "QoSFilterRule";
        } else if (node instanceof AEnumeratedAvpType) {
            return "Enumerated";
        } else if (node instanceof AGroupedAvpType) {
            return "Grouped";
        } else {
            throw new RuntimeException("Unknow AVP type [" + node.getClass().getName() + "]");
        }
    }

    public static String getCxxTypeName(PAvpType node) {
        if (node instanceof AOctetStringAvpType) {
            return "OctetString";
        } else if (node instanceof AInteger32AvpType) {
            return "Integer32";
        } else if (node instanceof AInteger64AvpType) {
            return "Integer64";
        } else if (node instanceof AUnsigned32AvpType) {
            return "Unsigned32";
        } else if (node instanceof AUnsigned64AvpType) {
            return "Unsigned64";
        } else if (node instanceof AFloat32AvpType) {
            return "Float32";
        } else if (node instanceof AFloat64AvpType) {
            return "Float64";
        } else if (node instanceof AAddressAvpType) {
            return "Address";
        } else if (node instanceof ATimeAvpType) {
            return "Time";
        } else if (node instanceof AUtf8StringAvpType) {
            return "UTF8String";
        } else if (node instanceof ADiameterIdAvpType) {
            return "Identity";
        } else if (node instanceof ADiameterUriAvpType) {
            return "URI";
        } else if (node instanceof AIpFilterRuleAvpType) {
            return "IPFilterRule";
        //} else if (node instanceof AQosFilterRuleAvpType) {
        //    return "QoSFilterRule";
        } else if (node instanceof AEnumeratedAvpType) {
            return "Enumerated";
        } else if (node instanceof AGroupedAvpType) {
            return "Grouped";
        } else {
            throw new RuntimeException("Unknow AVP type [" + node.getClass().getName() + "]");
        }
    }

    public static String getJavaValueTypeName(PAvpType node) {
        if (node instanceof AOctetStringAvpType) {
            return "String";
        } else if (node instanceof AInteger32AvpType) {
            return "Integer";
        } else if (node instanceof AInteger64AvpType) {
            return "Long";
        } else if (node instanceof AUnsigned32AvpType) {
            return "Integer";
        } else if (node instanceof AUnsigned64AvpType) {
            return "Long";
        } else if (node instanceof AFloat32AvpType) {
            return "Float32";
        } else if (node instanceof AFloat64AvpType) {
            return "Float64";
        } else if (node instanceof AAddressAvpType) {
            return "Address";
        } else if (node instanceof ATimeAvpType) {
            return "Integer";
        } else if (node instanceof AUtf8StringAvpType) {
            return "String";
        } else if (node instanceof ADiameterIdAvpType) {
            return "String";
        } else if (node instanceof ADiameterUriAvpType) {
            return "URI";
        } else if (node instanceof AIpFilterRuleAvpType) {
            return "IPFilterRule";
        //} else if (node instanceof AQosFilterRuleAvpType) {
        //    return "QoSFilterRule";
        } else if (node instanceof AEnumeratedAvpType) {
            return "Integer";
        } else if (node instanceof AGroupedAvpType) {
            return "Grouped";
        } else {
            throw new RuntimeException("Unknow AVP type [" + node.getClass().getName() + "]");
        }
    }

/*
    public static String getCxxTypeID(PAvpType node) {
        if (node instanceof AOctetStringAvpType) {
            return "AAA_AVP_STRING_TYPE";
        } else if (node instanceof AInteger32AvpType) {
            return "AAA_AVP_INTEGER32_TYPE";
        } else if (node instanceof AInteger64AvpType) {
            return "AAA_AVP_INTEGER64_TYPE";
        } else if (node instanceof AUnsigned32AvpType) {
            return "AAA_AVP_UINTEGER32_TYPE";
        } else if (node instanceof AUnsigned64AvpType) {
            return "AAA_AVP_UINTEGER64_TYPE";
        } else if (node instanceof AFloat32AvpType) {
            return "Float32";
        } else if (node instanceof AFloat64AvpType) {
            return "Float64";
        } else if (node instanceof AAddressAvpType) {
            return "AAA_AVP_ADDRESS_TYPE";
        } else if (node instanceof ATimeAvpType) {
            return "AAA_AVP_TIME_TYPE";
        } else if (node instanceof AUtf8StringAvpType) {
            return "AAA_AVP_UTF8_STRING_TYPE";
        } else if (node instanceof ADiameterIdAvpType) {
            return "AAA_AVP_DIAMID_TYPE";
        } else if (node instanceof ADiameterUriAvpType) {
            return "AAA_AVP_DIAMURI_TYPE";
        } else if (node instanceof AIpFilterRuleAvpType) {
            return "AAA_AVP_IPFILTER_RULE_TYPE";
        //} else if (node instanceof AQosFilterRuleAvpType) {
        //    return "QoSFilterRule";
        } else if (node instanceof AEnumeratedAvpType) {
            return "AAA_AVP_ENUM_TYPE";
        } else if (node instanceof AGroupedAvpType) {
            return "AAA_AVP_GROUPED_TYPE";
        } else {
            throw new RuntimeException("Unknow AVP type [" + node.getClass().getName() + "]");
        }
    }
*/

    public static String getCxxParserName(PAvpType node) {
        if (node instanceof AOctetStringAvpType) {
            return "OctetstringParser";
        } else if (node instanceof AInteger32AvpType) {
            return "Integer32Parser";
        } else if (node instanceof AInteger64AvpType) {
            return "Integer64Parser";
        } else if (node instanceof AUnsigned32AvpType) {
            return "Integer32Parser";
        } else if (node instanceof AUnsigned64AvpType) {
            return "Integer64Parser";
        } else if (node instanceof AFloat32AvpType) {
            return "Float32";
        } else if (node instanceof AFloat64AvpType) {
            return "Float64";
        } else if (node instanceof AAddressAvpType) {
            return "AddressParser";
        } else if (node instanceof ATimeAvpType) {
            return "Integer32Parser";
        } else if (node instanceof AUtf8StringAvpType) {
            return "Utf8stringParser";
        } else if (node instanceof ADiameterIdAvpType) {
            return "DiamidentParser";
        } else if (node instanceof ADiameterUriAvpType) {
            return "DiamuriParser";
        } else if (node instanceof AIpFilterRuleAvpType) {
            return "IPFilterRuleParser";
        //} else if (node instanceof AQosFilterRuleAvpType) {
        //    return "QoSFilterRule";
        } else if (node instanceof AEnumeratedAvpType) {
            return "Integer32Parser";
        } else if (node instanceof AGroupedAvpType) {
            return "GroupedParser";
        } else {
            throw new RuntimeException("Unknow AVP type [" + node.getClass().getName() + "]");
        }
    }
}
