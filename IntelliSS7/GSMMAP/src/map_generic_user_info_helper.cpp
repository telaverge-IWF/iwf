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
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: map_generic_user_info_helper.cpp,v 9.2 2007/01/10 11:14:59 yranade Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  MAP Generic User Info helper class implementation (C++ API). 
//
//  Source file to be included by the following source files:
//
//  o map_v2_user_info_helper.cpp
//  o map_v3_user_info_helper.cpp
//  o map_v4_user_info_helper.cpp
//  o map_v5_user_info_helper.cpp
//  o map_v6_user_info_helper.cpp
//  
//  o map_common_user_info_helper.cpp
//

//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Source file MUST always be included in other source file. Cannot be compiled
//  directly.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  


MAP_UserInfoHelper::MAP_UserInfoHelper()    
     : hasDestinationReference(false),
       hasOriginationReference(false),
       isDecodeDone(false),
       isEncodeDone(false)
{
    std::vector<long> cptArray;    

    cptArray.push_back(OID_CPT_CCITT);
    cptArray.push_back(OID_CPT_IDEN_ORG);
    cptArray.push_back(OID_CPT_ETSI);
    cptArray.push_back(OID_CPT_MOBILE_DOMAIN);
    cptArray.push_back(OID_CPT_GSM_NETWORK);
    cptArray.push_back(OID_CPT_Q773);
    cptArray.push_back(OID_DLG);
    cptArray.push_back(OID_VERSION);

    oid = new AsnObjectIdentifier(cptArray);
}

std::vector<byte> 
MAP_UserInfoHelper::Encode()
{
    EXTERNAL *external = new EXTERNAL();
    MAP_DialoguePDU * map_dialoguePDU = new MAP_DialoguePDU();

    switch (mapDlgType)
    {
    case MAP_OPEN:
    { 
        MAP_OpenInfo* mapOpenInfo = new MAP_OpenInfo();

        if (hasDestinationReference)
        {
           AddressString *destString = new AddressString(destinationReference); 
           mapOpenInfo->SetDestinationReference(destString);
        }

        if (hasOriginationReference)
        {
            AddressString *origString = new AddressString(originationReference);
            mapOpenInfo->SetOriginationReference(origString);  
        }              

        map_dialoguePDU->SetChoiceMap_open(mapOpenInfo);     
        break;  
    }
    case MAP_ACCEPT:
    {
        MAP_AcceptInfo* mapAcceptInfo = new MAP_AcceptInfo();

        //Parameters if any

        map_dialoguePDU->SetChoiceMap_accept(mapAcceptInfo);       
        break;
    }
    case MAP_CLOSE:
    {
        MAP_CloseInfo* mapCloseInfo = new MAP_CloseInfo();

        //

        map_dialoguePDU->SetChoiceMap_close(mapCloseInfo);       
        break;
    }
    case MAP_REFUSE:
    {
        MAP_RefuseInfo* mapRefuseInfo = new MAP_RefuseInfo();

        //
        Reason reason(refuseReason);
        mapRefuseInfo->SetReason(reason);

        map_dialoguePDU->SetChoiceMap_refuse(mapRefuseInfo);       
        break;
    }
    case MAP_UABORT:
    {
        MAP_UserAbortInfo* mapUserAbortInfo = new MAP_UserAbortInfo();
       
        //
        MAP_UserAbortChoice abortChoice;
        
        switch (GetAbortReasonType())
        {
        case SPECIFIC_REASON:
        {
            MAP_UserAbortChoice::UserSpecificReason userSpecificReason;
            abortChoice.SetChoiceUserSpecificReason(userSpecificReason);
            break;
        }

        case RESOURCE_LIMIT:
        {
            MAP_UserAbortChoice::UserResourceLimitation userResourceLimitation;
            abortChoice.SetChoiceUserResourceLimitation(userResourceLimitation);
            break;
        }
        case RESOURCE_UNAVAIL:
        {
            ResourceUnavailableReason unavailReason(abortReason);
            abortChoice.SetChoiceResourceUnavailable(unavailReason);
            break;
        }

        case APP_PROC_CANCEL:
        {
            ProcedureCancellationReason cancelReason(abortReason);
            abortChoice.SetChoiceApplicationProcedureCancellation(cancelReason);
            break;
        }
        }

        mapUserAbortInfo->SetMap_UserAbortChoice(abortChoice);
        map_dialoguePDU->SetChoiceMap_userAbort(mapUserAbortInfo);       
        break;
    }
    case MAP_PABORT:
    {
        MAP_ProviderAbortInfo* mapProviderAbortInfo = 
                                                   new MAP_ProviderAbortInfo();
     
        map_dialoguePDU->SetChoiceMap_providerAbort(mapProviderAbortInfo);      
        break;
    }

    }

    Octets* oid_octets = oid->Encode();

    EXTERNAL::Direct_reference *dr = 
    new EXTERNAL::Direct_reference(*oid_octets);
    EXTERNAL::Encoding *encoding = 
    new EXTERNAL::Encoding();

    EXTERNAL::Encoding::Single_ASN1_type *sin_asn_type = 
    new EXTERNAL::Encoding::Single_ASN1_type(map_dialoguePDU);

    encoding->SetChoiceSingle_ASN1_type(sin_asn_type);
    
    external->SetDirect_reference(dr);
    external->SetEncoding(encoding);

    mui.AddElement(external);

    Octets* tmpOctets;

    try
    {
       tmpOctets = mui.Encode();    
    }
    catch(AsnEncodeError& exc)
    {        
       exc.Log();
    }

    std::vector<byte> vec;
    vec = tmpOctets->GetArray(); 

    std::vector<byte> vec1;
    //vec1 = tmpOctets->GetArray(); 

    for(int i=0,j=2; j < vec.size(); i++,j++)
        vec1.push_back(vec[j]);

    delete tmpOctets;    
    delete oid_octets;

    isEncodeDone = true;
    return vec1;
}

void 
MAP_UserInfoHelper::Decode(std::vector<byte>& userInfoOctets)
{
    std::vector<byte> userInfoOctets1;

    if(userInfoOctets[0] != 0x30)
    {
        userInfoOctets1.push_back(0x30);
        userInfoOctets1.push_back(userInfoOctets.size());
    }

    for(int i=0;i< userInfoOctets.size(); i++)
       userInfoOctets1.push_back(userInfoOctets[i]);

    Octets octets(userInfoOctets1);

    try
    {
        mui.Decode(octets);        
    }
    catch(AsnDecodeError& exc)
    {        
        exc.Log();
    }

    for (size_t i = 0; i < mui.GetSize(); i++)
    {
        const EXTERNAL& external = mui.ElementAt(i);

        if (!external.OptionDirect_reference())
        {
            continue;
        }

        const EXTERNAL::Direct_reference& dr = external.GetDirect_reference();
        
        if (!(dr.GetArray() == (*oid).GetArray()))
        {
            continue;
        }        
        
        const EXTERNAL::Encoding& encoding = external.GetEncoding();

        if (!encoding.ChoiceSingle_ASN1_type())
        {
            continue;
        }

        const EXTERNAL::Encoding::Single_ASN1_type& single_asn1_type =
                            encoding.GetChoiceSingle_ASN1_type();
        
        Octets anyOctets = single_asn1_type.GetDecodedOctets();

        MAP_DialoguePDU map_dialoguePDU(anyOctets);

        if(map_dialoguePDU.ChoiceMap_open())
            SetMapDlgType(MAP_OPEN);
        else if (map_dialoguePDU.ChoiceMap_accept())
            SetMapDlgType(MAP_ACCEPT);
        else if (map_dialoguePDU.ChoiceMap_close())
            SetMapDlgType(MAP_CLOSE);
        else if (map_dialoguePDU.ChoiceMap_refuse())
            SetMapDlgType(MAP_REFUSE);
        else if (map_dialoguePDU.ChoiceMap_userAbort())
            SetMapDlgType(MAP_UABORT);
        else if (map_dialoguePDU.ChoiceMap_providerAbort())
            SetMapDlgType(MAP_PABORT);

        switch (GetMapDlgType())
        {
        case MAP_OPEN:
        {
            const MAP_OpenInfo& map_openInfo = 
                                map_dialoguePDU.GetChoiceMap_open();
            if (map_openInfo.OptionDestinationReference())
            {
                const AddressString& destString = 
                     map_openInfo.GetDestinationReference();
            
                hasDestinationReference = true;

                destinationReference = destString.GetArray();
            }

            if (map_openInfo.OptionOriginationReference())
            {
                const AddressString& origString = 
                    map_openInfo.GetOriginationReference();

                hasOriginationReference = true;

                originationReference = origString.GetArray();
            }

            isDecodeDone = true;
            break;
        }
        case MAP_ACCEPT:
        {
             const MAP_AcceptInfo& mapAcceptInfo = 
                                   map_dialoguePDU.GetChoiceMap_accept();
            isDecodeDone = true;
             break;
        } 
        case MAP_CLOSE:
        {
             const MAP_CloseInfo& mapCloseInfo = 
                                   map_dialoguePDU.GetChoiceMap_close();
            isDecodeDone = true;
             break;
        } 
        case MAP_REFUSE:
        {
             const MAP_RefuseInfo& mapRefuseInfo = 
                                   map_dialoguePDU.GetChoiceMap_refuse();
    
             const Reason& reason = mapRefuseInfo.GetReason();
             SetRefuseReason(reason.GetValue()); 
            isDecodeDone = true;
             break;

        } 
        case MAP_UABORT:
        {
             const MAP_UserAbortInfo& mapUserAbortInfo = 
                                   map_dialoguePDU.GetChoiceMap_userAbort();
             const MAP_UserAbortChoice& userAbortChoice = 
                                      mapUserAbortInfo.GetMap_UserAbortChoice();

             if (userAbortChoice.ChoiceUserSpecificReason())
             {
                 SetAbortReasonType(SPECIFIC_REASON);
             }
             else if (userAbortChoice.ChoiceUserResourceLimitation())
             {
                 SetAbortReasonType (RESOURCE_LIMIT);
             }
             else if (userAbortChoice.ChoiceResourceUnavailable())
             {
                 SetAbortReasonType (RESOURCE_UNAVAIL);
             }
             else if (userAbortChoice.ChoiceApplicationProcedureCancellation())
             {
                 SetAbortReasonType (APP_PROC_CANCEL);
             }
             else
             {
                 SetAbortReasonType(SPECIFIC_REASON);
             }
             
            isDecodeDone = true;
             break;
        } 
        case MAP_PABORT:
        {
             const MAP_ProviderAbortInfo& mapProviderAbortInfo = 
                       map_dialoguePDU.GetChoiceMap_providerAbort();
             const MAP_ProviderAbortReason& mapProviderAbortReason = 
                       mapProviderAbortInfo.GetMap_ProviderAbortReason();
             SetAbortReason(mapProviderAbortReason.GetValue());
             
            isDecodeDone = true;
             break;
        } 
        } 
    }    
}


