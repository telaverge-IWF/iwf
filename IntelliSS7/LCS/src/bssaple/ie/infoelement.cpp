//////////////////////////////////-*-C++-*-///////////////////////////////////
//                                                                          //
//     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    //
//             Manufactured in the United States of America.                //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                          //
//   This product and related documentation is protected by copyright and   //
//   distributed under licenses restricting its use, copying, distribution  //
//   and decompilation.  No part of this product or related documentation   //
//   may be reproduced in any form by any means without prior written       //
//   authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                          //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CONTRACT: INTERNAL                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
//   ID: $Id: infoelement.cpp,v 1.1.2.2 2010/03/23 05:43:46 rajeshak Exp $
//
//  LOG: $Log: infoelement.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/23 05:43:46  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#include <codec_trace.h>
#include <bssaple/ie/infoelement.h>

#include <bssaple/ie/imsi.h> 
#include <bssaple/ie/apdu.h>                    
#include <bssaple/ie/positioningdata.h>
#include <bssaple/ie/cause.h> 
#include <bssaple/ie/isdnaddress.h>            
#include <bssaple/ie/returnerrorcause.h>
#include <bssaple/ie/cellidentifier.h>          
#include <bssaple/ie/lcscause.h>                
#include <bssaple/ie/returnerrorrequest.h>
#include <bssaple/ie/chosenchannel.h>           
#include <bssaple/ie/lcsclienttype.h>           
#include <bssaple/ie/security.h>
#include <bssaple/ie/lcspriority.h>             
#include <bssaple/ie/segmentation.h>
#include <bssaple/ie/lcsqos.h>                  
#include <bssaple/ie/geographiclocation.h>      
#include <bssaple/ie/locationtype.h>
#include <bssaple/ie/networkelementidentity.h>
#include <bssaple/ie/decipheringkeys.h>
#include <bssaple/ie/gpsassistancedata.h>
#include <bssaple/ie/lmucause.h>
#include <bssaple/ie/signalingpointcode.h>
#include <bssaple/ie/releaseforbidden.h>
#include <bssaple/ie/releasecompletecause.h>
#include <bssaple/ie/facility.h>
#include <bssaple/ie/packetmeasurementreport.h>
#include <bssaple/ie/lcscapability.h>
#include <bssaple/ie/cellidentitylist.h>
#include <bssaple/ie/imei.h>
#include <bssaple/ie/velocitydata.h>
#include <bssaple/ie/ganssassistancedata.h>
#include <bssaple/ie/gansslocationtype.h>
#include <bssaple/ie/gansspositioningdata.h>


namespace bssaple
{

namespace ie
{

InfoElement *InfoElement::Decode(const ITS_OCTET *buf,int &offset)
{
    InfoElement *ptr = NULL;
    try
    {

        switch((InfoElement::Type)buf[0])
        {
        case InfoElement::LCS_QOS:
            ptr = new LCSQoS(&buf[1+1],buf[1]); 
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::LCS_PRIORITY:
            ptr = new LCSPriority(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::LOCATION_TYPE:
            ptr = new LocationType(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::GEOGRAPHIC_LOCATION:
            ptr = new GeographicLocation(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::POSITIONING_DATA:
            ptr = new PositioningData(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::LCS_CAUSE:
            ptr = new LCSCause(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::LCS_CLIENT_TYPE:
            ptr = new LCSClientType(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::APDU:
            {
            ITS_USHORT len = buf[1] << 8 | buf[1+1];
            ptr = new ie::APDU(&buf[1+1+1],len);
            offset += len + sizeof(ITS_OCTET)*3;//len =2 octets
            }
            break;
        case InfoElement::SRC_NETWORK_ELEMENT_ID:
        case InfoElement::DEST_NETWORK_ELEMENT_ID:
            ptr = new ie::NetworkElementIdentity(&buf[0],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::GPS_ASSISTANCE_DATA:
            ptr = new ie::GPSAssistanceData(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::DECIPHERING_KEYS:
            ptr = new ie::DecipheringKeys(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::RETURN_ERROR_REQUEST:
            ptr = new ReturnErrorRequest(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::RETURN_ERROR_CAUSE:
            ptr = new ReturnErrorCause(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::SEGMENTATION:
            ptr = new Segmentation(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::CLASSMARK_INFORMATION_TYPE3://This IE is not implemented so discard while decoding
            offset += buf[1] + sizeof(ITS_OCTET)*2;   //by throwing InvalidData Exception.
            ITN_THROW(InvalidData,
                  "Unsupported IE Classmark Infromation Type 3");
            break;
        case InfoElement::CAUSE:
            ptr = new Cause(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::CELL_IDENTIFIER:
            ptr = new CellIdentifier(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::CHOSEN_CHANNEL:
            ptr = new ChosenChannel(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::IMSI:
            ptr = new ie::IMSI(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::ISDN_ADDRESS:
            ptr = new ISDNAddress(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::SECURITY:
            ptr = new Security(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::SIGNALING_POINT_CODE:
            ptr = new SignalingPointCode(&buf[1+1],buf[1]);
            break;
        case InfoElement::FACILITY:
            ptr = new Facility(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::RELEASE_COMPLETE_CAUSE:
            ptr = new ReleaseCompleteCause(&buf[1+1],buf[1]);
            ++offset;
            break;
        case InfoElement::RELEASE_FORBIDDEN:
            ptr = new ReleaseForbidden(&buf[1+1],buf[1]);
            ++offset;
            break;
        case InfoElement::PACKET_MEASUREMENT_REPORT:
            ptr = new PacketMeasurementReport(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::LCS_CAPABILITY:
            ptr = new LcsCapability(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::IMEI:
            ptr = new ie::IMEI(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::CELL_IDENTITY_LIST:
            ptr = new CellIdentityList(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::VELOCITY_DATA:
            ptr = new VelocityData(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::REQ_GANSS_ASSIST_DATA:
            ptr = new GANSSAssistanceData(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::GANSS_LOCATION_TYPE:
            ptr = new GANSSLocationType(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;
        case InfoElement::GANSS_POSITIONING_DATA:
            ptr = new GANSSPositioningData(&buf[1+1],buf[1]);
            offset += buf[1] + sizeof(ITS_OCTET)*2;
            break;

        default:
            ITN_THROW(DecodeException,"Unknow Information Element");
        }
    }
    catch(InvalidData &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
    }
    return ptr;
}

} // namespace ie    
} // namespace bssaple    


