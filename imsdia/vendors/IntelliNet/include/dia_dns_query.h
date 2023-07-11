/*********************************-*-HPP-*-**********************************
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
 *  ID: $Id: dia_dns_query.h,v 1.4.44.1.4.1 2013/11/14 08:54:54 ncshivakumar Exp $
 *
 *  LOG: $Log: dia_dns_query.h,v $
 *  LOG: Revision 1.4.44.1.4.1  2013/11/14 08:54:54  ncshivakumar
 *  LOG: RFC6733 changes
 *  LOG:
 *  LOG: Revision 1.4.44.1  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 1.4  2011/10/14 10:41:08  rajeshak
 *  LOG: Removing OSS finding for DNS parsing
 *  LOG:
 *  LOG: Revision 1.3  2009/04/14 08:57:55  rajeshak
 *  LOG: Removed unwanted code
 *  LOG:
 *  LOG: Revision 1.2  2009/04/14 06:47:43  rajeshak
 *  LOG: Fixed Compilation Issue on Windriver.
 *  LOG:
 *  LOG: Revision 1.1  2009/04/13 14:08:42  rajeshak
 *  LOG: Introduced new files for peer discovery.
 *  LOG:
 *  
 ****************************************************************************/
#ident "$Id: dia_dns_query.h,v 1.4.44.1.4.1 2013/11/14 08:54:54 ncshivakumar Exp $"

#ifndef DNS_QUERY_H
#define DNS_QUERY_H

#include <stdlib.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <its_dia_config.h>

#define MAX_QUERY_SIZE                8192
#define ANS_SIZE                      8192
#define DNS_HDR_SIZE                  12
#define MAX_DNS_NAME                  256
#define MAX_DNS_STRING                255
#define MAX_DNS_MSG_SIZE              1024

#define NAPTR_PRIO(_naptr) \
        ((unsigned int)((((_naptr)->GetRecordOrder()) << 16) + ((_naptr)->GetRecordPref())))

#define GET_SRV_REC(x)      ((SrvRecord*)x->rdata)
#define GET_NAPTR_REC(x)    ((NaptrRecord*)x->rdata)
#define GET_A_REC(x)        ((A_RDATA*)x->rdata)
#define GET_AAAA_REC(x)     ((AAAA_RDATA*)x->rdata)

typedef enum _dns_query_type
{
    NAPTR_QUERY = ns_t_naptr,
    SRV_QUERY   = ns_t_srv,
    A_QUERY     = ns_t_a,
    AAAA_QUERY  = ns_t_aaaa
}
DNS_QUERY_TYPE;

/* Query union */
union dns_query
{
    HEADER hdr;
    unsigned char buff[MAX_QUERY_SIZE];
};

/* Resource Data struct */
typedef struct _rdata 
{
    unsigned short rtype;
    unsigned short rclass;
    unsigned int   rttl;
    void* rdata;
    struct _rdata* next;
}RDATA;

class NaptrRecord
{
public: 

    NaptrRecord() : _order(0), _pref(0),
                    _flagLen(0), _servLen(0),
                    _regExpLen(0), _rplcLen(0)
    {
       memset(_flags, 0, MAX_DNS_STRING);
       memset(_services, 0, MAX_DNS_STRING);
       memset(_regExp, 0, MAX_DNS_STRING);
       memset(_rplcmnt, 0, MAX_DNS_NAME);
    }

    ~NaptrRecord()
    {
    }

    void SetRecordOrder(ITS_USHORT val)
    {
        _order = val;
    }

    ITS_USHORT GetRecordOrder()
    {
        return _order;
    }

    void SetRecordPref(ITS_USHORT val)
    {
        _pref = val;
    }

    ITS_USHORT GetRecordPref()
    {
        return _pref;
    }

    void SetFlagLength(ITS_UINT val)
    {
        _flagLen = val;
    }

    ITS_UINT GetFlagLength()
    {
        return _flagLen;
    }

    void SetFlags(char* ptr, ITS_UINT len)
    {
        memcpy(_flags, ptr, len);
    }

    char* GetFlags()
    {
        return _flags;
    }

    void SetServiceLength(ITS_UINT val)
    {
        _servLen = val;
    }

    ITS_UINT GetServiceLength()
    {
        return _servLen;
    }

    void SetServices(char* ptr, ITS_UINT len)
    {
        memcpy(_services, ptr, len);
    }

    char* GetServices()
    {
        return _services;
    }

    void SetRegExpLength(ITS_UINT val)
    {
        _regExpLen = val;
    }

    ITS_UINT GetRegExpLength()
    {
        return _regExpLen;
    }

    void SetRegularExp(char* ptr, ITS_UINT len)
    {
        memcpy(_regExp, ptr, len);
    }

    char* GetRegularExp()
    {
        return _regExp;
    }

    void SetReplacementLength(ITS_UINT val)
    {
        _rplcLen = val;
    }

    ITS_UINT GetReplacementLength()
    {
        return _rplcLen;
    }

    void SetReplacement(char* ptr, ITS_UINT len)
    {
        memcpy(_rplcmnt, ptr, len);
    }

    char* GetReplacement()
    {
        return _rplcmnt;
    }

private:
    ITS_USHORT _order;
    ITS_USHORT _pref;
    ITS_UINT   _flagLen;
    char       _flags[MAX_DNS_STRING];
    ITS_UINT   _servLen;
    char       _services[MAX_DNS_STRING];
    ITS_UINT   _regExpLen;
    char       _regExp[MAX_DNS_STRING];
    ITS_UINT   _rplcLen;
    char       _rplcmnt[MAX_DNS_NAME];
};

class SrvRecord
{
public: 
    SrvRecord() : _priority(0), _weight(0),
                  _wghtSum(0), _port(0),
                  _nameLen(0)
    {
       memset(_name, 0, MAX_DNS_NAME);
    }

    ~ SrvRecord()
    {
    }

    void SetPriority(ITS_USHORT val)
    {
        _priority = val;
    }
    
    ITS_USHORT GetPriority()
    {
        return _priority;
    }
    
    void SetWeight(ITS_USHORT val)
    {
        _weight = val;
    }
    
    ITS_USHORT  GetWeight()
    {
        return _weight;
    }
    
    void SetWeightSum(ITS_USHORT val)
    {
        _wghtSum = val;
    }
    
    ITS_USHORT GetWeightSum()
    {
        return _wghtSum;
    }
    
    void SetPort(ITS_USHORT val)
    {
        _port = val;
    }

    ITS_USHORT GetPort()
    {
        return _port;
    }
    
    void SetNameLength(ITS_UINT val)
    {
        _nameLen = val;
    }
    
    ITS_UINT GetNameLength()
    {
        return _nameLen;
    }
    
    void SetName(char* ptr, ITS_UINT len)
    {
        memcpy(_name, ptr, len);
    }
    
    char* GetName()
    {
        return _name;
    }

private:
    ITS_USHORT  _priority;
    ITS_USHORT  _weight;
    ITS_USHORT  _wghtSum;
    ITS_USHORT  _port;
    ITS_UINT    _nameLen;
    char        _name[MAX_DNS_NAME];
};

/* A record struct */
typedef struct _a_rdata 
{
    unsigned char ip[4];
}A_RDATA;

/* AAAA record struct */
typedef struct _aaaa_rdata 
{
    unsigned char ip6[16];
}AAAA_RDATA;

typedef enum
{
    IPV4 = 0,
    IPV6

}IP_ADDR_TYPE;

typedef union
{
    unsigned char ip6[16];
    unsigned char ip[4];
}IP_ADDR;

typedef struct _host_data
{
    bool isTLSEnabled;
    unsigned short port;
    unsigned short securePort;
    DIA_TRANS_TYPE trType;  /* TCP-SCTP */
    IP_ADDR_TYPE ipType;
    unsigned int ttl;
    char name[MAX_DNS_NAME];
    IP_ADDR u;
} HOST_DATA;

static void FreeDnsRecords(RDATA* rec)
{
    while (rec != NULL)
    {
        RDATA* nxtRec = rec->next;
        int type = rec->rtype;

        if (rec->rdata != NULL)
        {
            switch(type)
            {
                case NAPTR_QUERY:
                {
                    NaptrRecord* nPtr = (NaptrRecord*) rec->rdata;
                    delete nPtr;
                }    
                break;
                case SRV_QUERY:
                {
                    SrvRecord* sPtr = (SrvRecord*) rec->rdata;
                    delete sPtr;
                }
                break;
                case A_QUERY:
                {
                    A_RDATA* addrPtr = (A_RDATA*) rec->rdata;
                    delete addrPtr;
                }
                break;
                case AAAA_QUERY:
                {
                    AAAA_RDATA* addrPtr = (AAAA_RDATA*) rec->rdata;
                    delete addrPtr;
                }
                break;
            }
            rec->rdata = NULL;
        }
        free(rec);
        rec = nxtRec;
    }
}   

class DnsQuery
{
public:
    static void ResInit()
    {
        res_init();
    }

    static int NaptrQuery(char* name, unsigned char*& respBuf);
    static int SrvQuery(char* name, unsigned char*& respBuf);
    static int AQuery(char* name, unsigned char*& respBuf);
    static int AAAAQuery(char* name, unsigned char*& respBuf);
    static int A6Query(char* name, unsigned char*& respBuf);
    static NaptrRecord* ParseNaptrRecord(unsigned char* startPtr,
                                         unsigned char* endPtr,
                                         unsigned char* data);
    static SrvRecord* ParseSrvRecord(unsigned char* startPtr,
                                     unsigned char* endPtr,
                                     unsigned char* data);
    static A_RDATA* ParseIpv4AddrRecord(unsigned char* startPtr,
                                        unsigned char* endPtr,
                                        unsigned char* data);
    static AAAA_RDATA* ParseIpv6AddrRecord(unsigned char* startPtr,
                                           unsigned char* endPtr,
                                           unsigned char* data);

    static int FindService(char* service);

    static int ResolveHostName(char* name, unsigned char*& respBuf);

private:
    static int ExecuteQuery(char* domainName, int classField, int type, unsigned char*& respBuf);

};

#endif
