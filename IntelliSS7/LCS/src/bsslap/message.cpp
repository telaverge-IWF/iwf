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
//   ID: $Id: message.cpp,v 1.1.2.2 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG: $Log: message.cpp,v $
//  LOG: Revision 1.1.2.2  2010/09/03 10:21:12  rajeshak
//  LOG: Issue 3400 Codec changes
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4786)

#include <bsslap/message.h>
#include <bsslap/taresponse.h>
#include <bsslap/tarequest.h>
#include <bsslap/reject.h>
#include <bsslap/reset.h>
#include <bsslap/abort.h>
#include <bsslap/talayer3.h>
#include <bsslap/toarequest.h>
#include <bsslap/toaresponse.h>
//#include <bsslap/mspositioncommand.h>
//#include <bsslap/mspositionresponse.h>


namespace bsslap {

const int MAX_NO_MANDATORY =10;

Message::Message(const Message &msg)
{
    _msgType = msg._msgType;

    Message::InfoElementMap::const_iterator it;

    for (it = msg.ies.begin(); it != msg.ies.end(); ++it)
    {    
        AddIE((it->second)->Clone());
    }
}

Message::~Message()
{
    cleanup();
}

void
Message::AddIE(ie::InfoElement* ie_element, bool clone)
{
    ie::InfoElement *copy = clone ? ie_element->Clone() : ie_element;
    ies.insert(InfoElementMap::value_type(copy->GetID(), copy));
}

const ie::InfoElement*
Message::FindIE(ie::InfoElement::Type ieID) const
{
    InfoElementMap::const_iterator f = ies.find(ieID);

    if (f != ies.end())
    {
       return (*f).second; 
    }
    return 0;
}

/****************************************************************************
void
Message::Encode(ITS_OCTET* buf, int& len) const
{
    CheckForMandatoryParam();

    buf[0] = (ITS_OCTET)_msgType;
    int length = 1;
    int left = len - length;

    InfoElementMap::const_iterator it;
    for (it = ies.begin(); it != ies.end(); ++it)
    {
        int ielen = left;
        ((ie::InfoElement*)it->second)->Encode(&buf[length], ielen);
        length += ielen;
        left -= ielen;
    }
    len = length;
}
*****************************************************************************/
void
Message::Encode(ITS_OCTET* buf, int& len) const
{
    try 
    {
        CheckForMandatoryParam();

        buf[0] = (ITS_OCTET)_msgType;

        int size = 0;
        int length = 1;
        int left = len - length;

        ie::InfoElement::Type mandatory[MAX_NO_MANDATORY];

        GetMandatoryParams(mandatory, size);

        InfoElementMap::const_iterator it;

        for ( int i = 0; i < size; ++i )
        {
            int ielen = left;

            FindIE(mandatory[i])->Encode(&buf[length], ielen);

            length += ielen;
            left -= ielen;
        }

        for (it = ies.begin(); it != ies.end(); ++it)
        {
            bool flag   = false;
            int  ielen  = left;

            for (int j = 0; j < size; ++j)
            {
                if (it->first == mandatory[j])
                {
                    flag = true;
                    break;
                }
            }
        
            if ( flag ) continue;

            ((ie::InfoElement*)it->second)->Encode(&buf[length], ielen);       

            length += ielen;
            left -= ielen;
        }    // end for  

        len = length;

    }  //end try
    catch(Exception &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }

    
}

Message* 
Message::Decode( ITS_OCTET* buf, int& len)
{
    Message::Type type = static_cast<Message::Type>(buf[0]);
    Message *message = 0;
    --len;
    switch(type)
    {
    case TA_REQUEST:
        message = new TARequest(&buf[1], len);
        break;
    case TA_RESPONSE:
        message = new TAResponse(&buf[1], len);
        break;
    case TOA_REQUEST:
        message = new TOARequest(&buf[1], len);
        break;
    case TOA_RESPONSE:
        message = new TOAResponse(&buf[1], len);
        break;
    case RESET:
        message = new Reset(&buf[1], len);
        break;
    case REJECT:
        message = new Reject(&buf[1], len);
        break;
    case ABORT:
        message = new Abort(&buf[1], len);
        break;
    case TA_LAYER3:
        message = new TALayer3(&buf[1], len);
        break;
    //case MS_POSITION_COMMAND:
    //    break;
    //case MS_POSITION_RESPONSE:
    //    break;
    default:
        ITN_THROW(IllegalArgumentException, "Unrecognized IE id");
        break;
    }
    return message;
}

void Message::DecodeIEs(const ITS_OCTET* buf, int &len)
{
    int offset = 0;
    try
    {
        while (len > 0)
        {
            int ielen = len;
            ie::InfoElement* ie_element = 
                        ie::InfoElement::Decode(&buf[offset], ielen);
            if (ie_element != NULL)
            {
                //AddIE(ie::InfoElement::Decode(&buf[offset], ielen));
                AddIE(ie_element);
            }
            offset += ielen;
            len -= ielen;
        }
    } 
    catch(Exception &x)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(x)));
        cleanup();
        throw;
    }

}

std::ostream &operator<<(std::ostream &out, const Message& msg)
{
    Message::InfoElementMap::const_iterator it;

    switch(msg._msgType)
    {
    case Message::TA_REQUEST:
        out <<"TA Request {\n";
        break;
    case Message::TA_RESPONSE:
        out <<"TA Response {\n";
        break;
    case Message::RESET:
        out << "Reset {\n";
        break;
    case Message::REJECT:
        out << "Reject {\n";
        break;
    case Message::ABORT:
        out << "Abort {\n";
        break;
    case Message::TA_LAYER3:
        out << "TA Layer3 {\n";
        break;
    case Message::TOA_REQUEST:
        out <<"TOA Request {\n";
        break;
    }
    out << std::endl;
    for (it = msg.ies.begin(); it != msg.ies.end(); ++it)
    {
        std::cout << *(it->second) << std::endl;
    }
    out << "        }" << std::endl;
    return out;
}

} // end of bsslap namespace

