/**************************-*-Dia-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *  
 *  ID: $Id: dia_codec.cpp,v 3.1 2008/03/31 10:33:25 nvijikumar Exp $
 *  
 *  LOG: $Log: dia_codec.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/03/13 16:32:21  yranade
 *  LOG: Bug Fixes. Code indentation and coding standards. Added traces.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/03 13:05:43  tpanda
 *  LOG: Code reorganisation:Codec part moved to separate file
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_codec.cpp,v 3.1 2008/03/31 10:33:25 nvijikumar Exp $"

#include <its++.h>
#include <dia_codec.h>

using namespace diameter;

//Encode to raw
int
diameter::Encode(diameter::Command& mesg, ITS_OCTET* buff, ITS_INT& length) 
{
    CommandAdapter& cmdAdp = (CommandAdapter&)mesg.getImpl();
    AAAMessage& msg = *((AAAMessage*)(cmdAdp.transfer()));
    AAAMessageBlock *aBuffer = NULL;

    for (int blockCnt = 1; 
            blockCnt <= 10; blockCnt ++)
    {
        aBuffer = AAAMessageBlock::Acquire(2048 * blockCnt);

        HeaderParser hp;
        hp.setRawData(aBuffer);
        hp.setAppData(&msg.hdr);
        hp.setDictData(PARSE_STRICT);
        
        try 
        {
            hp.parseAppToRaw();
        }
        catch (...) 
        {
            aBuffer->Release();
            return DIA_FAILURE;
        }

        PayloadParser pp;
        pp.setRawData(aBuffer);
        pp.setAppData(&msg.acl);
        pp.setDictData(msg.hdr.getDictHandle());

        try 
        { 
            pp.parseAppToRaw();
        }
        catch (...) 
        {
            aBuffer->Release();
            if (blockCnt < 10)
            {
                msg.acl.reset();
                continue;
            }
            return DIA_FAILURE;
        }

        msg.hdr.length = aBuffer->wr_ptr() - aBuffer->base();
        try 
        {
            hp.parseAppToRaw();
        }
        catch (...) 
        {
            aBuffer->Release();
            return DIA_FAILURE;
        }
        break;
    }

    aBuffer->length(msg.hdr.length);
    length = aBuffer->length();

    buff = new ITS_OCTET[length+1];
    memcpy(buff, aBuffer->base(), length);
    buff[length]='\0';

    aBuffer->Release();

    return DIA_SUCCESS;
}

//user should call CommandImpl::release to release the buffer
const CommandAdapter* 
diameter::Decode(void *data, size_t length) 
{
    const int MAX_MSG_LENGTH = 2048;
    const int MHEADER_SIZE = 20;
    unsigned int m_Offset=0;
    unsigned int m_BufSize=0;
    unsigned int m_MsgLength=0;

    char* m_Buffer = (char*)ACE_OS::malloc(MHEADER_SIZE + MAX_MSG_LENGTH);

    if (m_Buffer != NULL) 
    {
        m_BufSize = MHEADER_SIZE + MAX_MSG_LENGTH;
        ACE_OS::memset(m_Buffer, 0, m_BufSize);
    }

    int r_bytes = 0;

    while (length > 0) 
    {
        r_bytes = (length > size_t(m_BufSize - m_Offset)) ?
                  m_BufSize - m_Offset : length;
        ACE_OS::memcpy(m_Buffer + m_Offset, data, r_bytes);
          
        length -= r_bytes;

        data = (char*)data + r_bytes;
        m_Offset += (r_bytes > 0) ? r_bytes : 0;
    
        while (m_Offset > MHEADER_SIZE) 
        {
            if (m_MsgLength == 0) 
            {
                AAADiameterHeader hdr; 

                AAAMessageBlock *aBuffer = AAAMessageBlock::Acquire(m_Buffer, MHEADER_SIZE);

                HeaderParser hp;
                hp.setRawData(aBuffer);
                hp.setAppData(&hdr);
                hp.setDictData(PARSE_STRICT);

                try 
                {
                    hp.parseRawToApp();
                } 
                catch (...) 
                {
                    aBuffer->Release();
                    m_Offset -= HEADER_SIZE;
                    ACE_OS::memcpy(m_Buffer, m_Buffer + MHEADER_SIZE, m_Offset);
                    continue;
                }
                aBuffer->Release();
                m_MsgLength = hdr.length;
            }

            if (m_MsgLength > m_Offset) 
            {
                if (m_MsgLength > m_BufSize) 
                {
                    m_Buffer = (char*)ACE_OS::realloc(m_Buffer,m_MsgLength + 1);
                    if (m_Buffer) 
                    {
                        ACE_OS::memset(m_Buffer + m_BufSize, 0,m_MsgLength - m_BufSize + 1);
                        m_BufSize = m_MsgLength + 1;
                    }
                    else 
                    {
                        m_BufSize = 0; 
                        m_Offset = 0;
                        m_MsgLength = 0;
                        return NULL; 
                    }
                }
                else 
                {
                    break;
                }
            }
            else 
            {
                AAAMessageBlock *aBuffer = NULL; 
                AAAMessage* msg = new AAAMessage;
                try 
                { 
                    if (msg == NULL) 
                    {
                        return NULL; 
                    }
                    aBuffer = AAAMessageBlock::Acquire(m_Buffer, m_MsgLength);
                    HeaderParser hp;
                    hp.setRawData(aBuffer);
                    hp.setAppData(&msg->hdr);
                    hp.setDictData(PARSE_STRICT);

                    try 
                    {
                        hp.parseRawToApp();
                    }
                    catch (...) 
                    {
                        return NULL; 
                    }

                    PayloadParser pp;
                    pp.setRawData(aBuffer);
                    pp.setAppData(&msg->acl);
                    pp.setDictData(msg->hdr.getDictHandle());
                    aBuffer->rd_ptr(aBuffer->base() + MHEADER_SIZE);

                    try 
                    {
                        pp.parseRawToApp();
                    }
                    catch (...) 
                    {
                        return NULL;
                    }

                    aBuffer->Release();
                }
                catch (...) 
                {
                    if (msg == NULL) 
                    {
                        m_BufSize = 0; 
                        m_Offset = 0;
                        m_MsgLength = 0;
                        return NULL;
                    }
                    else
                    {
                        aBuffer->Release();
                        m_Offset -= m_MsgLength;
                        ACE_OS::memcpy(m_Buffer, m_Buffer + m_Offset, m_MsgLength);
                        continue;
                    }
                }
                if (m_MsgLength < m_Offset) 
                {                     
                    ACE_OS::memcpy(m_Buffer, m_Buffer + m_MsgLength, m_Offset - m_MsgLength);
                    m_Offset -= m_MsgLength;
                }
                else 
                {
                    m_Offset = 0;
                }

                ACE_OS::memset(m_Buffer + m_Offset, 0, m_BufSize - m_Offset);

                m_MsgLength = 0;

                return new CommandAdapter(msg);
            }
        }
    } 

    if (m_Buffer) 
    {
          ACE_OS::free(m_Buffer); 
    }

    return NULL;
}

