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
//   ID: $Id: infoelement.cpp,v 1.1.2.4 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG: $Log: infoelement.cpp,v $
//  LOG: Revision 1.1.2.4  2010/09/03 10:21:12  rajeshak
//  LOG: Issue 3400 Codec changes
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/26 11:42:38  rajeshak
//  LOG: Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/23 05:44:52  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/infoelement.h>
#include <bsslap/ie/handovertype.h>
#include <bsslap/ie/timingadvance.h>
#include <bsslap/ie/handoverreference.h>
#include <bsslap/ie/cause.h>
#include <bsslap/ie/cellidentity.h>
#include <bsslap/ie/startingtime.h>
#include <bsslap/ie/neighborcellidentity.h>
#include <bsslap/ie/neighborstarttime.h>
#include <bsslap/ie/channeldescription.h>
#include <bsslap/ie/mspower.h>
#include <bsslap/ie/measurementreport.h>
#include <bsslap/ie/deltatimer.h>
#include <bsslap/ie/frequencylist.h>
#include <bsslap/ie/rrlpflag.h>
#include <bsslap/ie/locationareacode.h>
#include <bsslap/ie/cellidentitylist.h>

#include <bsslap/ie/frequencylistrel8.h>
#include <bsslap/ie/ciphermodesetting.h>
#include <bsslap/ie/encryptionkey.h>
#include <bsslap/ie/servingcellidentifier.h>
#include <bsslap/ie/mspowerrel8.h>
#include <bsslap/ie/deltatimerrel8.h>
#include <bsslap/ie/channelmode.h>
#include <bsslap/ie/multirateconfig.h>
#include <bsslap/ie/pollingrepetition.h>
#include <bsslap/ie/packetchanneldesc.h>
#include <bsslap/ie/tlli.h>
#include <bsslap/ie/tfi.h>
#include <bsslap/ie/powerupstartuptime.h>
#include <bsslap/ie/tbfstartingtime.h>
#include <bsslap/ie/enhancedmeasurementreport.h>


namespace bsslap {
namespace ie {

InfoElement* InfoElement::Decode(const ITS_OCTET *buf, int& len)
{
    InfoElement::Type type = static_cast<InfoElement::Type>(buf[0]);
    InfoElement *infoelement = 0;
    --len; 
    switch(type)
    {
    case ie::InfoElement::TIMING_ADVANCE:
        infoelement = new TimingAdvance(&buf[1], len);
        break;
//    case ie::InfoElement::TARGET_CELL_IDENTITY:
    case ie::InfoElement::CELL_IDENTITY:
    {
        infoelement  = new CellIdentity(&buf[0], len);
        break;
    }
    case ie::InfoElement::HANDOVER_TYPE:
        infoelement = new HandoverType(&buf[1], len);
        break;
    case ie::InfoElement::STARTING_TIME:
        infoelement = new StartingTime(&buf[1], len);
        break;
    case ie::InfoElement::NEIGHBOR_CELL_IDENTITY:
        infoelement = new NeighborCellIdentity(&buf[1], len);
        break;
    case ie::InfoElement::NEIGHBOR_STARTING_TIME:
        infoelement = new NeighborStartTime(&buf[1], len);
        break;
    case ie::InfoElement::CHANNEL_DESCRIPTION:
        infoelement = new ChannelDescription(&buf[1], len);
        break;
    case ie::InfoElement::HANDOVER_REFERENCE:
        infoelement = new HandoverReference(&buf[1], len);
        break;
    case ie::InfoElement::MS_POWER:
        infoelement = new MSPower(&buf[1], len);
        break;
    case ie::InfoElement::MEASUREMENT_REPORT:
        infoelement = new MeasurementReport(&buf[1], len);
        break;
    case ie::InfoElement::DELTA_TIMER:
        infoelement = new DeltaTimer(&buf[1], len);
        break;
    case ie::InfoElement::CAUSE:
        infoelement = new Cause(&buf[1], len);
        break;
    case ie::InfoElement::FREQUENCY_LIST:
        infoelement = new FrequencyList(&buf[1], len);
        break;
    case ie::InfoElement::LOCATION_AREA_CODE:
        infoelement = new LocationAreaCode(&buf[1], len);
        break;
    case ie::InfoElement::CELL_IDENTITY_LIST:
        infoelement = new CellIdentityList(&buf[1], len);
        break;
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
    case ie::InfoElement::RRLP_FLAG:
        infoelement = new RRLPFlag(&buf[1], len);
        break;
    case ie::InfoElement::RRLP_IE:
        infoelement = new RRLPIe(&buf[1], len);
        break;
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
    case ie::InfoElement::FREQUENCY_LIST_REL8:
        infoelement = new FrequencyListRel8(&buf[1], len);
        break;
    case ie::InfoElement::MS_POWER_REL8:
        infoelement = new MSPowerRel8(&buf[1], len);
        break;
    case ie::InfoElement::DELTA_TIMER_REL8:
        infoelement = new DeltaTimerRel8(&buf[1], len);
        break;
    case ie::InfoElement::SERVING_CELL_IDENTITY_REL8:
        infoelement = new ServingCellId(&buf[1], len);
        break;
    case ie::InfoElement::ENCRYPTION_KEY:
        infoelement = new EncryptionKey(&buf[1], len);
        break;
    case ie::InfoElement::CIPHER_MODE_SETTING:
        infoelement = new CipherModeSetting(&buf[1], len);
        break;
    case ie::InfoElement::CHANNEL_MODE:
        infoelement = new ChannelMode(&buf[1], len);
        break;
    case ie::InfoElement::MULTIRATE_CONFIG:
        infoelement = new MultiRateConfig(&buf[1], len);
        break;
    case ie::InfoElement::POLLING_REPETITION:
        infoelement = new PollingRepetition(&buf[1], len);
        break;
    case ie::InfoElement::PACKET_CHANNEL_DESC:
        infoelement = new PacketChannelDesc(&buf[1], len);
        break;
    case ie::InfoElement::TLLI:
        infoelement = new Tlli(&buf[1], len);
        break;
    case ie::InfoElement::TFI:
        infoelement = new Tfi(&buf[1], len);
        break;
    case ie::InfoElement::TFB_STARTING_TIME:
        infoelement = new TbfStartingTime(&buf[1], len);
        break;
    case ie::InfoElement::POWERUP_STARTING_TIME:
        infoelement = new PowerupStartupTime(&buf[1], len);
        break;
    case ie::InfoElement::ENHANCED_MEASUREMENT_REPORT:
        infoelement = new EnhancedMeasurementReport(&buf[1], len);
        break;

    default:
        /* unrecognised IEs are ignored */
        //ITN_THROW(IllegalArgumentException, "Illegal Type of IE");
        break;

    }
    ++len;
    // Upon return from IE constructor, len is set to the number of bytes
    // consumed by this IE less the byte for IEI.
    return infoelement;
}

std::ostream &operator<<(std::ostream &out, const InfoElement &info)
{
    info.Print(out);
    return out;
}

} //namespace ie
} //namespace bsslap

