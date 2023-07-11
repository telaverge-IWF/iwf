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
//  ID: $Id: inap_cpp.cpp,v 9.1 2005/03/23 12:51:43 cvsadmin Exp $
//
// LOG: $LOG: $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 INAP C++ API common source (all versions of INAP).
//
//  o   Application Context Helper function implementations.
//

#include <inap_cpp.h>
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
 *      Encode the given INAP Application Context.
 *
 *  Input Parameters:
 *      INAP_AC acName - ENUM value of INAP Application context.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      vector<byte> - Encoded bytes of the given Application Context.
 *
 ****************************************************************************/

vector<byte>
inap::EncodeApplicationContext(INAP_AC acName)
{
    vector<long> cs1Array;
    vector<long> cs2Array;

    cs1Array.push_back(OID_CPT_CCITT);
    cs1Array.push_back(OID_CPT_RECOMMENDATION);
    cs1Array.push_back(OID_CPT_Q);
    cs1Array.push_back(OID_CPT_Q1218);

    cs2Array.push_back(OID_CPT_CCITT);
    cs2Array.push_back(OID_CPT_RECOMMENDATION);
    cs2Array.push_back(OID_CPT_Q);
    cs2Array.push_back(OID_CPT_Q1228);
    cs2Array.push_back(OID_CPT_CS2);
    cs2Array.push_back(OID_CPT_AC);

    switch (acName)
    {
        case IN_CS1_SSF_to_SCF_Generic_AC:
        case IN_CS1_SSF_to_SCF_DPspecific_AC:
        case IN_CS1_assist_handoff_SSF_to_SCF_AC:
        case IN_CS1_SRF_to_SCF_AC:
        case IN_CS1_SCF_to_SSF_Generic_AC:
        case IN_CS1_SCF_to_SSF_DPspecific_AC:
        case IN_CS1_SCF_to_SSF_traffic_management_AC:
        case IN_CS1_SCF_to_SSF_service_management_AC:
        case IN_CS1_SSF_to_SCF_service_management_AC:
        case IN_CS1_SCF_to_SSF_status_reporting_AC:
        {
            cs1Array.push_back(OID_SCF_SSF_SRF_OBJECTS);
            cs1Array.push_back(acName - CS1_START);
            cs1Array.push_back(OID_VERSION);

            cs2Array.clear();
            break;
        }
        case id_ac_directoryAccessAC:
        {
            cs1Array.push_back(OID_CPT_SDF_OBJECTS);
            cs1Array.push_back(OID_CPT_AC);
            cs1Array.push_back(acName - CS1_START);

            cs2Array.clear();
            break;
        }
        case id_ac_indirectoryAccessAC:
        case id_ac_indirectoryAccessWith3seAC:
        case id_ac_inExtendedDirectoryAccessAC:
        case id_ac_cs2_ssf_scfGenericAC:
        case id_ac_cs2_ssf_scfDPSpecificAC:
        case id_ac_cs2_ssf_scfAssistHandoffAC:
        case id_ac_cs2_ssf_scfServiceManagementAC:
        case id_ac_cs2_scf_ssfGenericAC:
        case id_ac_cs2_scf_ssfDPSpecificAC:
        case id_ac_cs2_scf_ssfTrafficManagementAC:
        case id_ac_cs2_scf_ssfServiceManagementAC:
        case id_ac_cs2_scf_ssfStatusReportingAC:
        case id_ac_cs2_scf_ssfTriggerManagementAC:
        case id_ac_srf_scf:
        case id_ac_indirectorySystemAC:
        case id_ac_inShadowSupplierInitiatedAC:
        case id_ac_inShadowConsumerInitiatedAC:
        case id_ac_indirectorySystemWith3seAC:
        case id_ac_inShadowSupplierInitiatedWith3seAC:
        case id_ac_inShadowConsumerInitiatedWith3seAC:
        case id_ac_scf_scfOperationsAC:
        case id_ac_distributedSCFSystemAC:
        case id_ac_scf_scfOperationsWith3seAC:
        case id_ac_distributedSCFSystemWith3seAC:
        case id_ac_scf_cusf:
        case id_ac_cusf_scf:
        case id_ac_inExtendedDirectoryAccessWith3seAC:
        {
            cs2Array.push_back(acName - CS2_START);

            cs1Array.clear();
            break;
        }
        default:
        {
            cs1Array.clear();
            cs2Array.clear();
            break;
        }
    }

    vector<byte> result;

    try
    {
        AsnObjectIdentifier objectIdentifier;

        if (cs1Array.size() > 0)
        {
            objectIdentifier.SetArray(cs1Array);
        }
        else if (cs2Array.size() > 0)
        {
            objectIdentifier.SetArray(cs2Array);
        }
        else
        {
            return result;
        }
       
        Octets* octets = objectIdentifier.Encode();
        Tag tag(*octets);
        Length length(*octets);
        result = octets->GetArrayWithOffset();
        delete octets;
    }
    catch (its::AsnEncodeError& err)
    {
        result.clear();
    }

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Decode the given bytes and return the INAP Application context.
 *
 *  Input Parameters:
 *      vector<byte> - Bytes to be decoded.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      INAP_AC - ENUM value of INAP Application context.
 *
 ****************************************************************************/

inap::INAP_AC
inap::DecodeApplicationContext(vector<byte>& encodedVec)
{
    inap::INAP_AC acName = UNKNOWN;

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

    if (result.size() < 6)
    {
        return acName;
    }

    if (result[count++] == OID_CPT_CCITT)
    {
        if (result[count++] == OID_CPT_RECOMMENDATION)
        {
            if (result[count++] == OID_CPT_Q)
            {
                if (result[count] == OID_CPT_Q1228)
                {
                    count++;
                    if ((result[count] == OID_CPT_CS2) && 
                        (result[count+1] == OID_CPT_AC))
                    {
                        count+=2;
                        if (result.size() > count)
                        {
                            acName = (inap::INAP_AC)(result[count] + CS2_START);
                        }
                    } 
                }
                else if (result[count] == OID_CPT_Q1218)
                {
                    count++;
                    if (result[count] == OID_SCF_SSF_SRF_OBJECTS) 
                    {
                        count++;
                        acName = (inap::INAP_AC)(result[count] + CS1_START);
                    }
                    else if (result[count] == OID_CPT_SDF_OBJECTS)
                    {
                        count++;
                        if (result[count] == OID_CPT_AC)
                        {
                            count++;
                            if (result.size() > count)
                            {
                                acName = (inap::INAP_AC)(result[count] + CS1_START);
                            }
                        }
                    }
                }            
            }
        }
    }
 
    delete octets;
    delete lengthOctets;
    delete tagOctets;
    delete tag;

    if(((((ITS_UINT)acName) > CS1_MAX) && (((ITS_UINT)acName) < CS2_START)) || 
       (((ITS_UINT)acName) > CS2_MAX))
    {
        acName = UNKNOWN;  
    }

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
inap::EncodeApplicationContextVector(vector<long>& ac)
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
inap::DecodeApplicationContextVector(vector<byte>& ac)
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
