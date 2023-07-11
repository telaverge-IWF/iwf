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
//   ID: $Id: dtapmessage.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: dtapmessage.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#include <bssaple/dtapmessage.h>
#include <bssaple/facility.h>
#include <bssaple/register.h>
#include <bssaple/releasecomplete.h>

namespace bssaple 
{

DTAPMessage *DTAPMessage::DecodeDTAPMessage(const ITS_OCTET *buf,int len)
{
    switch((DTAPMessage::Type)buf[3])
    {
    case DTAPMessage::FACILITY:
        return new Facility(buf,len);
        break;
    case DTAPMessage::REGISTER:
        return new Register(buf,len);
        break;
    case DTAPMessage::RELEASE_COMPLETE:
        //return new ReleaseComplete(buf,len);
        break;
    default:
        ITN_THROW(DecodeException, "Invalid DTAP-LE message type");
    }
}

void DTAPMessage::EncodeDTAPMessage(ITS_OCTET *buf,int& len) const
{
    buf[0] |= ((ITS_OCTET)channelId << 6) & 0xC0U;
    buf[0] |= (ITS_OCTET)sapi & 0x07U;
    buf[2] = tId_protDisc;
    buf[3] = msgType;

    int totLen =3;
    int ieLen =0;
    Message::IE_iterator iter;
    for(iter = ies.begin();iter != ies.end();++iter)
    {
        ((ie::InfoElement *)iter->second)->Encode(&buf[totLen +1],ieLen);
        totLen += ieLen;
        ieLen =0;
    }
    buf[1] = totLen -3;
    len = totLen;
}

void DTAPMessage::PrintMsg(std::ostream &out) const
{
    switch((DTAPMessage::Type)msgType)
    {
    case RELEASE_COMPLETE:
        out<<"ReleaseComplete"<<std::endl<<"{"<<std::endl;
        break;
    case FACILITY:
        out<<"Facility"<<std::endl<<"{"<<std::endl;
        break;
    case REGISTER:
        out<<"Register"<<std::endl<<"{"<<std::endl;
        break;
    default:
        out<<"Unknown Message Type ..."<<std::endl;
        break;
    }

    out<<"\tProtocolDiscriminator "<<std::hex
                            <<GetProtocolDiscriminator()<<std::endl;
    out<<"\tTransactionFlag "<<std::hex
                            <<GetTransactionFlag()<<std::endl;
    out<<"\tTransactionId "<<std::hex
                            <<GetTransactionId()<<std::endl;
    out<<"\tControlChannelId "<<std::hex
                            <<GetControlChannelId()<<std::endl;
    out<<"\tSAPI "<<std::hex
                            <<GetSAPI()<<std::endl;

    Message::IE_iterator iter;
    for(iter = ies.begin();iter != ies.end();++iter)
    {
        ((ie::InfoElement *)iter->second)->PrintIE(out);
    }
    out<<"}"<<std::endl<<std::endl;

    

}

}

