////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: cap_cpp.cpp,v 9.1.102.1 2014/03/14 10:40:31 jsarvesh Exp $
//
// LOG: $LOG: $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 CAMEL C++ API common source (all versions of CAMEL).
//
//  o   Application Context Helper function implementations.
//

#include <cap_cpp.h>

#include <Octets.h>
#include <Length.h>
#include <AsnException.h>
#include <AsnObjectIdentifier.h>

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_NAMESPACE)

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode the given CAMEL Application Context.
 *
 *  Input Parameters:
 *      CAP_AC acName - ENUM value of CAMEL Application context.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      vector<byte> - Encoded bytes of the given Application Context.
 *
 ****************************************************************************/

std::vector<byte> 
cap::EncodeApplicationContext(CAP_AC acName)
{
    vector<long> cptArray;

    cptArray.push_back(OID_CPT_CCITT);
    cptArray.push_back(OID_CPT_IDEN_ORG);
    cptArray.push_back(OID_CPT_ETSI);
    cptArray.push_back(OID_CPT_MOBILE_DOMAIN);
    cptArray.push_back(OID_CPT_UMTS_NETWORK);

    switch (acName)
    {
        case CAPV1_gsmSSF_to_gsmSCF_AC:
        {
            cptArray.push_back(OID_CPT_CAP1_AC);
            cptArray.push_back(CAPV1_GSMSSF_TO_GSMSCF);
            cptArray.push_back(CAPV1_VERSION);
            break;
        }
        case CAPV2_gsmSSF_to_gsmSCF_AC:
        {
            cptArray.push_back(OID_CPT_CAP2_AC);
            cptArray.push_back(CAPV2_GSMSSF_TO_GSMSCF);
            cptArray.push_back(CAPV2_VERSION);
            break;
        }
        case CAPV2_assist_gsmSSF_to_gsmSCF_AC:
        {
            cptArray.push_back(OID_CPT_CAP2_AC);
            cptArray.push_back(CAPV2_ASSIST_GSMSSF_TO_GSMSCF);
            cptArray.push_back(CAPV2_VERSION);
            break;
        }
        case CAPV2_gsmSRF_to_gsmSCF_AC:
        {
            cptArray.push_back(OID_CPT_CAP2_AC);
            cptArray.push_back(CAPV2_GSMSRF_TO_GSMSCF);
            cptArray.push_back(CAPV2_VERSION);
            break;
        }
        case CAPV3_capssf_scfGeneric_AC:
        {
            cptArray.push_back(OID_CPT_CAP3OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV3_CAPSSF_SCFGENERIC);
            break;
        }
        case CAPV3_capssf_scfAssistHandoff_AC:
        {
            cptArray.push_back(OID_CPT_CAP3OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV3_CAPSSF_SCFASSISTHO);
            break;
        }
        case CAPV3_gsmSRF_gsmSCF_AC:
        {
            cptArray.push_back(OID_CPT_CAP3);
            cptArray.push_back(CAP_AC_ID_AC);
            cptArray.push_back(CAPV3_GSMSRF_GSMSCF);
            break;
        }
        case CAPV3_cap3_sms_AC:
        {
            cptArray.push_back(OID_CPT_CAP3OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV3_SMS);
            break;
        }
        case CAPV3_cap3_gprsSSF_gsmSCF_AC:
        { 
            cptArray.push_back(OID_CPT_CAP3OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV3_GPRSSSF_GSMSCF);
            break;
        }
        case CAPV3_cap3_gsmSCF_gprsSSF_AC:
        {
            cptArray.push_back(OID_CPT_CAP3OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV3_GSMSCF_GPRSSSF);
            break;
        }
        case CAPV4_capssf_scfGeneric_AC:
        {
            cptArray.push_back(OID_CPT_CAP4OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV4_CAPSSF_SCFGENERIC);
            break;
        }
        case CAPV4_capssf_scfAssistHandoff_AC:
        {
            cptArray.push_back(OID_CPT_CAP4OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV4_CAPSSF_SCFASSISTHO);
            break;
        }
        case CAPV4_capscf_ssfGeneric_AC:
        {
            cptArray.push_back(OID_CPT_CAP4OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV4_CAPSCF_SSFGENERIC);
            break;
        }
        case CAPV4_gsmSRF_gsmSCF_AC:
        {
            cptArray.push_back(OID_CPT_CAP4);
            cptArray.push_back(CAP_AC_ID_AC);
            cptArray.push_back(CAPV4_GSMSRF_GSMSCF);
            break;
        }
        case CAPV4_cap4_sms_AC:
        { 
            cptArray.push_back(OID_CPT_CAP4OE);
            cptArray.push_back(CAP_AC_ID_ACE);
            cptArray.push_back(CAPV4_SMS);
            break; 
        }
        default:
        {
            cptArray.clear();
            break;
        }
    }

    vector<byte> result;

    if (cptArray.size() != 0)
    {
        try
        {
            AsnObjectIdentifier objectIdentifier;

            objectIdentifier.SetArray(cptArray);

            Octets* octets = NULL;
            octets = objectIdentifier.Encode();

            if (octets)
            {
                Tag tag(*octets);
                Length length(*octets);   
                result = octets->GetArrayWithOffset();
                delete octets;
            }
        }
        catch (its::AsnEncodeError& err)
        {
            result.clear();
        }
    }

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Decode the given bytes and return the CAMEL Application context.
 *
 *  Input Parameters:
 *      vector<byte> - Bytes to be decoded.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      CAP_AC - ENUM value of CAMEL Application context.
 *
 ****************************************************************************/

cap::CAP_AC
cap::DecodeApplicationContext(vector<byte>& encodedVec)
{
    cap::CAP_AC acName = UNKNOWN;

    Tag* tag = NULL;
    Octets* tagOctets = NULL;
    Octets* lengthOctets = NULL;
    Octets* octets = NULL;

    std::vector<long> result;

    try
    {
        Octets valOctets(encodedVec);

        tag = AsnObjectIdentifier::GetUniversalTag();
        tagOctets = tag->Encode();

        Length length(valOctets.GetLength());
        lengthOctets = length.Encode();

        octets = new Octets();

        *octets += *tagOctets;
        *octets += *lengthOctets;
        *octets += valOctets;

        AsnObjectIdentifier objectIdentifier;
        objectIdentifier.Decode(*octets);

        result = objectIdentifier.GetArray();
    }
    catch (its::AsnDecodeError& err)
    {
        result.clear();

        if (octets)
            delete octets;
        if (lengthOctets)
            delete lengthOctets;
        if (tagOctets)
            delete tagOctets;
        if (tag)
            delete tag;
    }

    ITS_INT count = 0;
    ITS_UINT rec = 0;

    if (result.size() < 8)
    {
        return acName;
    }

    if ((result[0] == OID_CPT_CCITT) &&
        (result[1] == OID_CPT_IDEN_ORG) &&
        (result[2] == OID_CPT_ETSI) &&
        (result[3] == OID_CPT_MOBILE_DOMAIN) &&
        (result[4] == OID_CPT_UMTS_NETWORK))
    {
        switch (result[5])
        {
            case OID_CPT_CAP1_AC:
            {
                if (result[6] == CAPV1_GSMSSF_TO_GSMSCF)
                {
                    if (result[7] == CAPV1_VERSION)
                    {
                        acName = CAPV1_gsmSSF_to_gsmSCF_AC;
                    }
                    else if (result[7] == CAPV2_VERSION)
                    {
                        acName = CAPV2_gsmSSF_to_gsmSCF_AC;
                    }
                }
                else if (result[6] == CAPV2_ASSIST_GSMSSF_TO_GSMSCF)
                {
                    acName = CAPV2_assist_gsmSSF_to_gsmSCF_AC;
                }
                else if (result[6] == CAPV2_GSMSRF_TO_GSMSCF)
                {
                    acName = CAPV2_gsmSRF_to_gsmSCF_AC;
                }
               
                break;
            }
            case OID_CPT_CAP3:
            case OID_CPT_CAP3OE:
            {
                if (result[6] == CAP_AC_ID_AC)
                {
                    switch (result[7])
                    {
                        case CAPV3_CAPSSF_SCFGENERIC:
                        {
                            acName = CAPV3_capssf_scfGeneric_AC;
                            break;
                        }
                        case CAPV3_CAPSSF_SCFASSISTHO:
                        {
                            acName = CAPV3_capssf_scfAssistHandoff_AC;
                            break;
                        }
                        case CAPV3_GSMSRF_GSMSCF:
                        {
                            acName = CAPV3_gsmSRF_gsmSCF_AC;
                            break;
                        }
                        case CAPV3_SMS:
                        {
                            acName = CAPV3_cap3_sms_AC;
                            break;
                        }
                        case CAPV3_GPRSSSF_GSMSCF:
                        {
                            acName = CAPV3_cap3_gprsSSF_gsmSCF_AC;
                            break;
                        }
                        case CAPV3_GSMSCF_GPRSSSF:
                        {
                            acName = CAPV3_cap3_gsmSCF_gprsSSF_AC;
                            break;
                        }
                    }
                }
                break;
            }
            case OID_CPT_CAP4:
            case OID_CPT_CAP4OE:
            {
                if (result[6] == CAP_AC_ID_AC)
                {
                    switch (result[7])
                    {
                        case CAPV4_CAPSSF_SCFGENERIC:
                        {
                            acName = CAPV4_capssf_scfGeneric_AC;
                            break;
                        }
                        case CAPV4_CAPSSF_SCFASSISTHO:
                        {
                            acName = CAPV4_capssf_scfAssistHandoff_AC;
                            break;
                        }
                        case CAPV4_CAPSCF_SSFGENERIC:
                        {
                            acName = CAPV4_capscf_ssfGeneric_AC;
                            break;
                        }
                        case CAPV4_GSMSRF_GSMSCF:
                        {
                            acName = CAPV4_gsmSRF_gsmSCF_AC;
                            break;
                        }
                        case CAPV4_SMS:
                        {
                            acName = CAPV4_cap4_sms_AC;
                            break;
                        }
                    }
                }
                break;
            }
        }
    }

    delete octets;
    delete lengthOctets;
    delete tagOctets;
    delete tag;

    return acName;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Encode the given Application context vector.
 *
 *  Input Parameters:
 *      vector<long> - List of values specified in the standard.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      vector<byte> - Application context Encoded bytes.
 *
 ****************************************************************************/

std::vector<byte>
cap::EncodeApplicationContextVector(vector<long>& ac)
{
    vector<byte> result;

    if (ac.size() == 0)
    {
        return result;
    }

    try
    {
        AsnObjectIdentifier objectIdentifier;
        objectIdentifier.SetArray(ac);
        Octets* octets = objectIdentifier.Encode();
        Tag tag(*octets);
        Length length(*octets);
        result = octets->GetArrayWithOffset();
        delete octets;
    }
    catch(its::AsnEncodeError& err)
    {
        result.clear();
    }

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Decode the given Application context Encoded bytes and returns
 *      the vector of values as specified in the standard.
 *
 *  Input Parameters:
 *      vector<byte> - Application context Encoded bytes.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      vector<long> - List of values specified in the standard.
 *
 ****************************************************************************/

vector<long>
cap::DecodeApplicationContextVector(vector<byte>& ac)
{
    Tag* tag = NULL;
    Octets* tagOctets = NULL;
    Octets* lengthOctets = NULL;
    Octets* octets = NULL;

    std::vector<long> result;

    try
    {
        Octets valOctets(ac);

        tag = AsnObjectIdentifier::GetUniversalTag();
        tagOctets = tag->Encode();

        Length length(valOctets.GetLength());
        lengthOctets = length.Encode();

        octets = new Octets();

        *octets += *tagOctets;
        *octets += *lengthOctets;
        *octets += valOctets;

        AsnObjectIdentifier objectIdentifier;
        objectIdentifier.Decode(*octets);

        result = objectIdentifier.GetArray();
    }
    catch (its::AsnDecodeError& err)
    {
        result.clear();
        if (octets)
            delete octets;
        if (lengthOctets)
            delete lengthOctets;
        if (tagOctets)
            delete tagOctets;
        if (tag)
            delete tag;
    }

    return result;
}

