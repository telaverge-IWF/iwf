/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * ID: $Id: dia_dns_query.cpp,v 1.3.58.1 2013/10/26 07:42:21 ncshivakumar Exp $
 *
 * LOG: $Log: dia_dns_query.cpp,v $
 * LOG: Revision 1.3.58.1  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 1.3  2011/10/14 10:40:45  rajeshak
 * LOG: Removing OSS finding for DNS parsing
 * LOG:
 * LOG: Revision 1.2  2009/05/12 08:42:31  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 1.1  2009/04/13 14:10:01  rajeshak
 * LOG: Introduced new files for peer discovery.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dia_dns_query.cpp,v 1.3.58.1 2013/10/26 07:42:21 ncshivakumar Exp $"

#include <netdb.h>
#include <string.h>

#include <dia_trace.h> 
#include <dia_utils.h>

#include <dia_dns_query.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;  
using namespace its;
using namespace engine;
using namespace diameter;
#endif


int DnsQuery::ExecuteQuery(char* domainName, int classField, int type, unsigned char*& respBuf)
{
    int rLen = 0;
    unsigned char buf[MAX_DNS_MSG_SIZE];

    respBuf = NULL;

    //DT_DBG(("DnsQuery::ExecuteQuery\n"));

    if ((rLen = res_query(domainName,
                          classField,
                          type,
                          buf,
                          sizeof(buf)))
                          < 0)
    {
        DT_ERR(("Error in res_query for domainName %s and errno is %d",domainName,errno));
        return -1;
    }

    if (rLen > 0)
    {
        respBuf = (unsigned char*) malloc(rLen);
        if (respBuf == NULL)
        {
            return 0;
        }
        
        if (rLen > MAX_DNS_MSG_SIZE)
        {
            if ((rLen = res_query(domainName,
                                  classField,
                                  type,
                                  respBuf,
                                  rLen))
                                  < 0)
            {
                return -1;
            }
        }
        else
        {
            memcpy(respBuf, buf, rLen);
        }
    }

    return rLen; 
}

int DnsQuery::NaptrQuery(char* name, unsigned char*& respBuf)
{
    return ExecuteQuery(name, ns_c_in, ns_t_naptr, respBuf); 
}

int DnsQuery::SrvQuery(char* name, unsigned char*& respBuf)
{
    return ExecuteQuery(name, ns_c_in, ns_t_srv, respBuf);
}

int DnsQuery::AQuery(char* name, unsigned char*& respBuf)
{
    return ExecuteQuery(name, ns_c_in, ns_t_a, respBuf);
}

int DnsQuery::AAAAQuery(char* name, unsigned char*& respBuf)
{
    return ExecuteQuery(name, ns_c_in, ns_t_aaaa, respBuf);
}

int DnsQuery::A6Query(char* name, unsigned char*& respBuf)
{
    return ExecuteQuery(name, ns_c_in, ns_t_a6, respBuf);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will parse the buffer and populate the NAPTR_RDATA 
 *  Input Parameters:
 *     starting buffer ptr
 *     ending buffer ptr
 *     pointer 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to RDATA :- if success
 *      NULL - in case of error
 *  Notes:  
 *
 *      Format of NAPTR Record Type:
 *       0123456789012345
 *      +------------------+
 *      |     Order        |
 *      |------------------|
 *      |     Preference   |
 *      |------------------|
 *      ~     Flags        ~
 *      |     (string)     |
 *      +------------------+
 *      ~     Services     ~
 *      |     (string)     |
 *      +------------------+
 *      ~     Regexp       ~
 *      |     (string)     |
 *      +------------------+
 *      ~     Replacement  ~
 *      |     (string)     |
 *      +------------------+
  *  See Also:
 *
 ****************************************************************************/
 NaptrRecord* DnsQuery::ParseNaptrRecord(unsigned char* startPtr,
                                        unsigned char* endPtr,
                                        unsigned char* data)
{
    ITS_USHORT sVal = 0;
    ITS_UINT   flagLen = 0, servLen = 0, regExpLen = 0;
    char  rplc[MAX_DNS_NAME];
    NaptrRecord* naptrRec = NULL;

    //DT_DBG(("DnsQuery::ParseNaptrRecord\n"));

    if ((data + 7) >= endPtr)
    {
       return NULL;
    }

    naptrRec = new NaptrRecord();
    if (naptrRec == NULL)
    {
        DT_ERR(("Memory allocation Failed\n"));
        return NULL;
    }

    /* Order */
    sVal =  (data[0] << 8) | data[1];
    naptrRec->SetRecordOrder(ntohs(sVal));

    /* move the data pointer by 2 byte (size of order) */
    data += 2;

    /* Preference */
    sVal =  (data[0] << 8) | data[1];
    naptrRec->SetRecordPref(ntohs(sVal));
    
    /* move the data pointer by 2 byte (size of preference) */
    data += 2;

    /* flags length*/
    flagLen = (int) data[0];
    if ((data + 7 +  flagLen) >= endPtr)
    {
       delete naptrRec;
       //DT_ERR("Error\n");
       return NULL;
    }

    /* move the data pointer by 1 byte (size of flag length) */
    data += 1;

    naptrRec->SetFlagLength(flagLen);

    /* flags */
    naptrRec->SetFlags((char*)data, flagLen);

    /* move the data pointer by flagLen byte (size of flag) */
    data += flagLen;

    /* services length */
    servLen = (int)data[0];
    if ((data + 7 + servLen) >= endPtr) 
    {
        delete naptrRec;
        //DT_ERR("Error\n");
        return NULL;
    }

    /* move the data pointer by 1 byte (size of service length) */
    data += 1;
    
    /* services */
    naptrRec->SetServices((char*)data, servLen);

    /* move the data pointer by servLen byte (size of services) */
    data += servLen;

    /* Regular Expression */
    regExpLen =  (int)data[0];

    if ((data + 7 + regExpLen) >= endPtr)
    {
       delete naptrRec;
       //DT_ERR("Error\n");
       return NULL;
    }

    /* move the data pointer by 1 byte (size of regular exp length) */

    data += 1;

    naptrRec->SetRegularExp((char*)data, regExpLen);

    /* move the data pointer by regExpLen byte (size of regular exp) */
    data += regExpLen;

    /* replacemnet - data */
    int rplcLen = dn_expand(startPtr, endPtr, data, (char*) rplc, MAX_DNS_NAME-1);

    if (rplcLen == (unsigned int)-1 )
    {
       delete naptrRec;
       //DT_ERR("Error\n");
       return NULL;
    }

    naptrRec->SetReplacementLength(rplcLen);
    naptrRec->SetReplacement(rplc, rplcLen);

    return naptrRec;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Parses the srv record into a SRV_RDATA structure
 *  Input Parameters:
 *      startPtr - pointer to the dns message.
 *      endPtr - pointer to the end of the message.
 *      data - pointer to the rdata part of the SRV answer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to SRV_RDATA :- if success
 *      (0) :- in case of error
 *  Notes:
 * 
 *      Format of SRV Record Type:
 *       0123456789012345
 *      +------------------+
 *      |     Priority     |
 *      |------------------|
 *      |     Weight       |
 *      |------------------|
 *      |     Port         |
 *      |------------------|
 *      ~     Target       ~
 *      |    (string)      |
 *      +------------------+
 *
 *  See Also:
 *
 ****************************************************************************/
SrvRecord* DnsQuery::ParseSrvRecord(unsigned char* startPtr,
                                    unsigned char* endPtr,
                                    unsigned char* data)
{
    SrvRecord* srvRec = NULL;
    ITS_USHORT prio = 0, wght = 0, port = 0;
    char name[MAX_DNS_NAME];
    int len;

    //DT_DBG(("DnsQuery::ParseSrvRecord\n"));

    if ((data+6)>=endPtr)
    {
       return NULL;
    }

    //srv=(SRV_RDATA*) calloc(1, sizeof(SRV_RDATA));
    srvRec = new SrvRecord();
    if (srvRec == NULL)
    {
        DT_ERR(("Memory allocation Failed\n"));
        return NULL;
    }

    prio =  (data[0] << 8) | data[1];
    data += 2;
    
    wght =  (data[0] << 8) | data[1];
    data += 2;

    port =  (data[0] << 8) | data[1];
    data += 2;

    srvRec->SetPriority(ntohs(prio));
    srvRec->SetWeight(ntohs(wght));
    srvRec->SetPort(ntohs(port));

    if ((len = dn_expand(startPtr, endPtr, data, name, MAX_DNS_NAME-1)) == -1)
    {
        delete srvRec;
        //DT_ERR("Error\n");
        return NULL;
    }

    srvRec->SetNameLength(len);
    srvRec->SetName(name, len);

    return srvRec;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Parses the IPV4 address record
 *  Input Parameters:
 *      startPtr - pointer to the dns message.
 *      endPtr - pointer to the end of the message.
 *      data - pointer to the rdata part of the SRV answer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to A_RDATA :- if success
 *      (0) :- in case of error
 *  Notes:
 *  See Also:
 *
 ****************************************************************************/
A_RDATA* DnsQuery::ParseIpv4AddrRecord(unsigned char* startPtr,
                                       unsigned char* endPtr,
                                       unsigned char* data)
{
    A_RDATA* addr;

    if (data+4 >= endPtr)
    {
        return NULL;
    }
    
    //addr = (A_RDATA*) calloc(1, sizeof(A_RDATA));
    addr = new A_RDATA;
    if (addr == NULL)
    {
        DT_ERR(("Memory allocation Failed\n"));
        return NULL;
    }
    
    memcpy(addr->ip, data, 4);

    return addr;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Parses the IPV6 address record
 *  Input Parameters:
 *      startPtr - pointer to the dns message.
 *      endPtr - pointer to the end of the message.
 *      data - pointer to the rdata part of the SRV answer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to A_RDATA :- if success
 *      (0) :- in case of error
 *  Notes:
 *  See Also:
 *
 ****************************************************************************/
AAAA_RDATA* DnsQuery::ParseIpv6AddrRecord(unsigned char* startPtr,
                                       unsigned char* endPtr,
                                       unsigned char* data)
{
    AAAA_RDATA* addr;
	
    if (data+16 >= endPtr)
    {
        return NULL;
    }
    
    //addr = (AAAA_RDATA*) calloc(1, sizeof(AAAA_RDATA));
    addr = new AAAA_RDATA;
    if (addr == NULL)
    {
        DT_ERR(("Memory allocation Failed\n"));
        return NULL;
    }
    
    memcpy(addr->ip6, data, 16);

    return addr;
}

int DnsQuery::ResolveHostName(char* name, unsigned char*& respBuf)
{
    int resLen = AQuery(name, respBuf);
    
    if (resLen == 0)
    {
        resLen = AAAAQuery(name, respBuf);
    }
    
    return resLen;
}

