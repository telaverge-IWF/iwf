#include "map_prot_utils.h"

const std::string MAPUtils::sDigits("0123456789ABCDEF");

#ifdef GCC_LESS_THAN_4_3
using namespace std::tr1;
const MAPUtils::MccWith3DigitMnc MAPUtils::sMccWith3DigitMnc = InitMccWith3DigitMnc();
#else
// gcc flag -std=c++0x need for this type of initialization
const MAPUtils::MccWith3DigitMnc MAPUtils::sMccWith3DigitMnc = {
    // { 262, 2},       // Mixture of 2 and 3-digit MNCs
    { 302, 1},
    { 310, 1},
    { 311, 1},
    { 316, 1},
    { 334, 1},
    { 338, 1},
    { 342, 1},
    { 344, 1},
    { 346, 1},
    { 348, 1},
    { 352, 1},
    { 354, 1},
    { 356, 1},
    { 358, 1},
    { 360, 1},
    { 365, 1},
    { 366, 1},
    // { 374, 1},       // Mixture of 2 and 3-digit MNCs
    { 376, 1},
    // { 405, 1},       // Mixture of 2 and 3-digit MNCs
    // { 502, 1},       // Mixture of 2 and 3-digit MNCs
    // { 710, 1},       // Mixture of 2 and 3-digit MNCs
    { 722, 1},
    { 732, 1},
};
#endif

int MAPUtils::StringToTBCD(const std::string &str, uint8_t *tbcd, int len, unsigned pad, bool no_rev)
{
    int slen = str.size();
    int shalf = slen >> 1;
    int bIdx, sIdx; 

    for (bIdx = 0, sIdx = 0; bIdx < shalf; bIdx++, sIdx++)
    {
        /* if 'no_rev' is true we will not reverse the digits configured in json */
        if (no_rev)
        {
            tbcd[bIdx] = (ToHex(str[sIdx]) << 4) | ToHex(str[sIdx+1]);
        }
        else
        {
            tbcd[bIdx] = ToHex(str[sIdx]) | ToHex(str[sIdx+1]) << 4;
        }
        sIdx++;
    }
    if (sIdx != slen)
    {
        // Odd digits
        if(no_rev)
        {
            tbcd[bIdx] = (ToHex(str[sIdx]) << 4) | pad ;
        }
        else
        {
            tbcd[bIdx++] = ToHex(str[sIdx]) | (pad << 4);
        }
    }
    return bIdx;
}

void MAPUtils::TBCDToString(const uint8_t *tbcd, int len, std::string &str, bool odd)
{
    int bIdx;

    if ((tbcd[len-1] & 0xF0) == 0xF0) 
        odd = true;
    for (bIdx = 0; bIdx < len; bIdx++)
    {
        str += ToChar(Low4(tbcd[bIdx]));
        if (odd && (bIdx == len -1))
        {
            break;
        }

        str += ToChar(High4(tbcd[bIdx]));
    }
}

void MAPUtils::IpStringToGSNAddress(const std::string &ipStr, its::ByteArray &gsnAddr)
{
    // GSN Address format 
    // 2 bits - IP Type (0 is IPv4 and 1 is IPv6)
    // 6 bits - Length  (Ipv4 4 and Ipv6 16)
    // 4-16 bytes - IP address value as in RFC 791 and 2373
    uint8_t ipAddr[sizeof(struct in6_addr)] = {0};
    int domain, type, len;
    if (ipStr.find(':') != std::string::npos)
    {
        domain = AF_INET6;
        type = 1;
        len = sizeof(struct in6_addr); // shoud be 16
    }
    else
    {
        domain = AF_INET;
        type = 0;
        len = sizeof(struct in_addr); // should be 4
    }

    int ret = inet_pton(domain, ipStr.c_str(), ipAddr);
    if (ret == 1)
    {
        uint8_t gsnBuf[sizeof(struct in6_addr) + 1];
        gsnBuf[0] = len | (type << 6);
        memcpy(&gsnBuf[1], ipAddr, len);

        gsnAddr.assign(gsnBuf, gsnBuf + len + 1);
    }
}

/*diameter::Address MAPUtils::GSNAddressToDiaAddress(
                        const std::vector<byte>& gsnAddr)
{
    int gsnType = gsnAddr[0] & 0x03;
    diameter::Address::Family family;
    int len;
    if (gsnType == 0)
    {
        family = diameter::Address::IPV4;
        len = 4;
    }
    else if (gsnType == 1)
    {
        family = diameter::Address::IPV6;
        len = 16;
    }
    else
    {
        // TODO throw an exception
    }

    return diameter::Address(family, (const char*)&gsnAddr[1], len);
}*/

void MAPUtils::ByteArrayToHexString(const std::vector<byte>& arr, std::string& hexStr)
{
    unsigned val = 0;
    for (std::vector<byte>::const_iterator it = arr.begin();
         it != arr.end(); it++)
    {
        val = *it;
        hexStr += ToChar(High4(val));
        hexStr += ToChar(Low4(val)); 
    }
}


void MAPUtils::ExtractMncMcc(const std::vector<byte>& imsi, unsigned& mcc, unsigned& mnc)
{
    unsigned mncDigits = 2;
    unsigned *val = &mcc;
    mcc = 0;
    mnc = 0;
    for (int i = 0; i < 6 ; i++)
    {
        *val *= 10;
        *val += Low4(imsi[i >> 1]);
        i++;
        if (i == 3)
        {
            if (sMccWith3DigitMnc.find(mcc) != sMccWith3DigitMnc.end())
            {
                mncDigits = 3;
            }
            val = &mnc;
        }
        else if (i == 5 && mncDigits == 2)
        {
            break;
        }

        *val *= 10;
        *val += High4(imsi[i >> 1]);
    }
}

void MAPUtils::ExtractMncMcc(const std::string& imsi, unsigned& mcc, unsigned& mnc)
{
    unsigned mncDigits = 2;
    unsigned *val = &mcc;
    mcc = 0;
    mnc = 0;
    for (int i = 0; i < 6 ; i++)
    {
        if (i == 3)
        {
            if (sMccWith3DigitMnc.find(mcc) != sMccWith3DigitMnc.end())
            {
                mncDigits = 3;
            }
            val = &mnc;
        }
        else if (i == 5 && mncDigits == 2)
        {
            break;
        }
        *val *= 10;
        *val += ToHex(imsi[i]);
    }
}


