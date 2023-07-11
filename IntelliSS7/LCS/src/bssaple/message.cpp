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
//   ID: $Id: message.cpp,v 1.1.2.3 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG: $Log: message.cpp,v $
//  LOG: Revision 1.1.2.3  2010/09/03 10:21:12  rajeshak
//  LOG: Issue 3400 Codec changes
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/23 05:41:53  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/message.h>
#include <bssaple/performlocationabort.h>
#include <bssaple/connectionorientedinformation.h> 
#include <bssaple/performlocationrequest.h>
#include <bssaple/performlocationinformation.h>
#include <bssaple/performlocationresponse.h>
#include <bssaple/reset.h>
#include <bssaple/resetacknowledge.h>
#include <bssaple/lmuconnectionaccept.h>
#include <bssaple/lmuconnectionreject.h>
#include <bssaple/lmuconnectionrelease.h>
#include <bssaple/lmuconnectionrequest.h>
#include <bssaple/connectionlessinformation.h>
#include <bssaple/dtapmessage.h>



namespace bssaple     {


int const IE_MAX_SIZE =240;
int const MAX_NO_MANDATORY =10;

Message::Message(const Message &right)
: msgType(right.msgType)
{
    IE_iterator iter;
    for(iter = right.ies.begin();iter != right.ies.end();++iter)
    {
        AddIE(iter->second,true);
    }
}
        
Message::~Message()
{
    Message::IE_iterator iter;
    for(iter = ies.begin();iter != ies.end();++iter)
    {
        if(iter->second != NULL)
        {
            delete iter->second;
        }
    }
    ies.clear();
}

Message * Message::Decode(const ITS_OCTET* buf, int len)
{
    if(buf[0] == DTAP_LE_ID)
    {
        return DTAPMessage::DecodeDTAPMessage(&buf[1],len -1);
    }

    Message *msg;
    switch((Message::Type)buf[2])
    {
    case Message::PERFORM_LOCATION_REQUEST:
        msg = new PerformLocationRequest(&buf[3], len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::PERFORM_LOCATION_RESPONSE:
        msg = new PerformLocationResponse(&buf[3], len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::PERFORM_LOCATION_ABORT:
        msg = new PerformLocationAbort(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::PERFORM_LOCATION_INFORMATION:
        msg = new PerformLocationInformation(&buf[3], len-(sizeof(ITS_OCTET)*3));
        break;    
    case Message::CONNECTION_ORIENTED_INFORMATION:
        msg = new ConnectionOrientedInformation(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::LMU_CONNECTION_REQUEST:
        msg = new LMUConnectionRequest(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::LMU_CONNECTION_ACCEPT:
        msg = new LMUConnectionAccept(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::LMU_CONNECTION_REJECT:
        msg = new LMUConnectionReject(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::LMU_CONNECTION_RELEASE:
        msg = new LMUConnectionRelease(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::CONNECTIONLESS_INFORMATION:
        msg = new ConnectionlessInformation(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::RESET:
        msg = new Reset(&buf[3],len-(sizeof(ITS_OCTET)*3));
        break;
    case Message::RESET_ACKNOWLEDGE:
        msg = new ResetAcknowledge();
        break;
    default:
        ITN_THROW(DecodeException, "Invalid BSSAP-LE message type indicator"); 
    }
    return msg;
}

const ie::InfoElement * Message::FindIE(ie::InfoElement::Type type) const
{
    Message::IE_iterator iter = ies.find(type);

    if(iter == ies.end())
    {
        return NULL;
    }
    return iter->second;
}

void Message::AddIE(const ie::InfoElement *ie, bool clone)
{
	if(ie != NULL)
    {
        if (clone)
        {
            ies.insert(ElementMap::value_type(ie->GetId(), ie->Clone()));
        }
        else
        {
            ies.insert(ElementMap::value_type(ie->GetId(), ie));
        }
    }
}

void Message::DecodeIE(const ITS_OCTET *buf, int len)
{
    try
    {
        int offset =0;
        while(offset < len)
        {
            AddIE(ie::InfoElement::Decode(&buf[offset], offset));
            if (offset > len)
            {
                std::cout << "HERE in DecodeIE " << std::endl;

                try
                {
                    CheckForMandatoryParams();
                } 
                catch(MissingParameterException & x)
                {
                    ITN_THROW(DecodeException,"Invalid IE length - Pointing beyond buffer");
                }
            }
        }

    }
    catch(DecodeException &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}

void Message::Encode(ITS_OCTET *buf,int &len) const
{
    try
    {
        int index =0;
        ie::InfoElement::Type manpar[MAX_NO_MANDATORY];
        GetMandatoryParams(manpar,index);
        
        int totLen =2;
        int ieLen=0;
        Message::IE_iterator iter;

        CheckForMandatoryParams();

        buf[0] = protocolId;
        if(protocolId == DTAP_LE_ID)
        {
             ((DTAPMessage *)this)->EncodeDTAPMessage(&buf[1],len); 
        }
        else
        {
            buf[2] = msgType;
            for(int i=0;i<index;++i)
            {
                FindIE(manpar[i])->Encode(&buf[totLen +1],ieLen);
                totLen += ieLen;
                ieLen =0;
            }

            for(iter = ies.begin();iter != ies.end();++iter)
            {
                bool flag =false;
                for(int i=0;i<index;++i)
                {
                    if(iter->first == manpar[i])
                    {
                        flag = true;
                        break;
                    }    
                }

                if(flag) continue;

                ((ie::InfoElement *)iter->second)->Encode(&buf[totLen +1],
                                                                    ieLen);
                totLen += ieLen;
                ieLen =0;
            }
            len = totLen + 1;
            buf[1] = len; 
        }
    }
    catch(Exception &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}

void Message::PrintMsg(std::ostream &out) const
{
    if(protocolId == DTAP_LE_ID)
    {
        ((DTAPMessage *)this)->PrintMsg(out);
        return;
    }

    switch ((Message::Type)msgType)
    {
    case Message::PERFORM_LOCATION_REQUEST:
        out<<"PerFormLocationRequest"<<std::endl;
        break;
    case Message::PERFORM_LOCATION_RESPONSE:
        out<<"PerFormLocationResponse"<<std::endl;
        break;
    case Message::PERFORM_LOCATION_ABORT:
        out<<"PerFormLocationAbort"<<std::endl;
        break;
    case Message::PERFORM_LOCATION_INFORMATION:
        out<<"PerformLocationInformation"<<std::endl;    
        break;
    case Message::CONNECTION_ORIENTED_INFORMATION:
        out<<"ConnectionOrientedInformation"<<std::endl;
        break;
    case Message::LMU_CONNECTION_REQUEST:
        out<<"LMUconnectionRequest"<<std::endl;
        break;
    case Message::LMU_CONNECTION_ACCEPT:
        out<<"LMUconnectionAccept"<<std::endl;
        break;
    case Message::LMU_CONNECTION_REJECT:
        out<<"LMUconnectionReject"<<std::endl;
        break;
    case Message::LMU_CONNECTION_RELEASE:
        out<<"LMUconnectionRelease"<<std::endl;
        break;
    case Message::RESET:
        out<<"Reset"<<std::endl;
        break;
    case Message::RESET_ACKNOWLEDGE:
        out<<"ResetAcknowledge"<<std::endl;
        break;
    case Message::CONNECTIONLESS_INFORMATION:
        out<<"ConnectionLessInformation"<<std::endl;
        break;
    default:
        out<<"Unknown Message"<<std::endl;
        return;
    }
    out<<"{"<<std::endl;
    Message::IE_iterator iter; 
    for(iter = ies.begin();iter != ies.end();++iter)
    {
        ((ie::InfoElement *)iter->second)->PrintIE(out);
    }
    out<<"}"<<std::endl<<std::endl;
}

} // namespace bssaple    

