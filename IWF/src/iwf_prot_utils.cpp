#include "iwf_prot_utils.h"
#include <boost/assign.hpp>
#include <ssg_trace.h>
#include <sstream>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/sctp.h>



const std::string IWFUtils::sDigits("0123456789ABCDEF");

#ifdef GCC_LESS_THAN_4_3
using namespace std::tr1;
const IWFUtils::MccWith3DigitMnc IWFUtils::sMccWith3DigitMnc = InitMccWith3DigitMnc();
const IWFUtils::MccWith2Or3DigitMnc IWFUtils::sMccWith2Or3DigitMnc = InitMccWith2Or3DigitMnc();
#else
// gcc flag -std=c++0x need for this type of initialization
const IWFUtils::MccWith3DigitMnc IWFUtils::sMccWith3DigitMnc = {
    // { 262, 2},       // Mixture of 2 and 3-digit MNCs
    { 302, 1},
    { 310, 1},
    { 311, 1},
    { 312, 1},
    { 313, 1},
    { 316, 1},
    { 334, 1},
    { 338, 1},
    { 342, 1},
    { 344, 1},
    { 346, 1},
    { 348, 1},
    { 350, 1},
    { 352, 1},
    { 354, 1},
    { 356, 1},
    { 358, 1},
    { 360, 1},
    { 365, 1},
    { 366, 1},
    { 374, 2},       // Mixture of 2 and 3-digit MNCs
    { 376, 1},
    { 405, 2},
    // { 502, 1},       // Mixture of 2 and 3-digit MNCs
    { 708, 1},
    // { 710, 1},       // Mixture of 2 and 3-digit MNCs
    { 722, 1},
    { 732, 1},
    { 750, 1},
};
const IWFUtils::MccWith2Or3DigitMnc IWFUtils::sMccWith2Or3DigitMnc = {
    {37413, 1},
    {37414, 1},
    {40500, 1},
    {40501, 1},
    {40502, 1},
    {40503, 1},
    {40504, 1},
    {40575, 1},
    {40579, 1},
    {40580, 1},
};
#endif

int IWFUtils::StringToTBCD(const std::string &str, uint8_t *tbcd, int len, unsigned pad, bool no_rev)
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
            tbcd[bIdx++] = (ToHex(str[sIdx]) << 4) | pad ;
        }   
        else
        {   
            tbcd[bIdx++] = ToHex(str[sIdx]) | (pad << 4); 
        }   
    }   
    return bIdx;
}

void IWFUtils::TBCDToString(const uint8_t *tbcd, int len, std::string &str, bool odd, bool rev, bool dontdiscard)
{
    int bIdx;


    if ((tbcd == NULL) || (len == 0))   
        return;

    if (!dontdiscard && ((tbcd[len-1] & 0xF0) == 0xF0)) 
        odd = true;
    if(rev)
    {
        for (bIdx = 0; bIdx < len; bIdx++)
        {
            str += ToChar(High4(tbcd[bIdx]));
            if (odd && (bIdx == len -1))
            {
                break;
            }
            str += ToChar(Low4(tbcd[bIdx]));
        }
    }
    else
    {
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
}

void IWFUtils::IpStringToGSNAddress(const std::string &ipStr, its::ByteArray &gsnAddr)
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

diameter::Address IWFUtils::GSNAddressToDiaAddress(
        const std::vector<byte>& gsnAddr)
{
    int gsnType = gsnAddr[0] >> 6;
    diameter::Address::Family family = diameter::Address::RESERVED;
    unsigned int len = 0;
    if (gsnType == 0)
    {
        family = diameter::Address::IPV4;
        len = 4;
        if(gsnAddr.size() < (len + 1))
        {
            throw std::out_of_range("vector size invalid");
        }
    }
    else if (gsnType == 1)
    {
        family = diameter::Address::IPV6;
        len = 16;
        if(gsnAddr.size() < (len + 1))
        {
            throw std::out_of_range("vector size invalid");
        }
    }
    else
    {
        // TODO throw an exception
    }

    return diameter::Address(family, (const char*)&gsnAddr[1], len);
}

std::string IWFUtils::ReverseVectorToString(const std::vector<byte>& vec)
{
    std::vector<byte> t1(vec.size()); 
    for(unsigned int i = 0, j = 0; i < vec.size(); i++, j++) 
    {
        t1[i] = (vec[j] >> 4);
        t1[i] |= (vec[j] << 4);
    }
    return IWFUtils::VectorToString(t1);
}

void IWFUtils::ByteArrayToHexString(const std::vector<byte>& arr, std::string& hexStr)
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


void IWFUtils::ExtractMncMcc(const std::vector<byte>& imsi, unsigned& mcc, unsigned& mnc)
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

void IWFUtils::ExtractMncMcc(const std::string& imsi, unsigned& mcc, unsigned& mnc)
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

void IWFUtils::ExtractMncMcc(const std::string& imsi, std::string& mcc, std::string& mnc)
{
    unsigned mncDigits = 2;

    mcc = imsi.substr(0, 3);
#ifdef GCC_LESS_THAN_4_3
    std::tr1::unordered_map<unsigned, unsigned>::const_iterator sMccWith3DigitMncIter = sMccWith3DigitMnc.find(atoi(mcc.c_str()));
#else
    std::unordered_map<unsigned, unsigned>::const_iterator sMccWith3DigitMncIter = sMccWith3DigitMnc.find(atoi(mcc.c_str()));
#endif
    if (sMccWith3DigitMncIter != sMccWith3DigitMnc.end())
    {
        if(sMccWith3DigitMncIter->second == 2)
        {
            std::string mccmncCombination = imsi.substr(0, 5);
            if(sMccWith2Or3DigitMnc.find(atoi(mccmncCombination.c_str())) != sMccWith2Or3DigitMnc.end())
            {
                mncDigits = 3;
                mnc = imsi.substr(3, 3);
            }
            else
            {
                mnc = imsi.substr(3, 2);
                mncDigits = 2;
            }
        }
        else
        {
            mncDigits = 3;
            mnc = imsi.substr(3, 3);
        }
    }
    else if (mncDigits == 2)
    {
        mnc = imsi.substr(3, 2);
    }
}

int IWFUtils::ValidateIPString(const std::string &ipaddr, bool &isIPv4)
{
    unsigned char buf[sizeof(struct in6_addr)];
    if(inet_pton(AF_INET, ipaddr.c_str(), buf))
    {
        isIPv4 = true;
        return ITS_SUCCESS;
    }
    else if(inet_pton(AF_INET6, ipaddr.c_str(), buf))
    {
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}

bool IWFUtils::CheckDateAndTime(struct TimeAndDate tm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    unsigned int year = 0; 
    int month = 0,day = 0;
    int hour = 0, minute = 0,second = 0;
    time_t systime;
    struct tm localtm;
    time(&systime);
    localtm = *localtime(&systime);

    year = localtm.tm_year + 1900;
    month = localtm.tm_mon + 1;
    day = localtm.tm_mday;
    hour = localtm.tm_hour;
    minute = localtm.tm_min;
    second = localtm.tm_sec;

    DLOG_DEBUG("%d",year);

    if(! (year >= tm.year) )
    {
        DLOG_ERROR("Invalid Year Value %d", tm.year);
        return false;
    }
    if (! ((1<= tm.month && tm.month<=12)) )
    {
        DLOG_ERROR("Invalid Month Value %d", tm.month);
        return false;
    }
    if (! (1<= tm.day && tm.day<=31) )
    {
        DLOG_ERROR("Invalid Day Value %d", tm.day);
        return false;
    }
    if ( (tm.day==31) && (tm.month==2 || tm.month==4 || tm.month==6 || tm.month==9 || tm.month==11) )
    {
        DLOG_ERROR("Month with Invalid days");
        return false;
    }
    if ( (tm.day==30) && (tm.month==2) )
    {
        DLOG_ERROR("Second Month with Invalid days");
        return false;
    }
    if ( (tm.month==2) && (tm.day==29) && (tm.year%4!=0) )
    {
        DLOG_ERROR("Second Month with Invalid LeapYear days");
        return false;
    }
    if ( (tm.month==2) && (tm.day==29) && (tm.year%400==0) )
    {
        DLOG_ERROR("Second Month with LeapYear days");
        return true;
    }
    if ( (tm.month==2) && (tm.day==29) && (tm.year%100==0) )
    {
        DLOG_ERROR("Second Month with Invalid LeapYear days");
        return false;
    }
    if ( (tm.month==2) && (tm.day==29) && (tm.year%4==0)  )
    {
        DLOG_ERROR("Second Month with LeapYear days");
        return true;
    }
    if ( !(tm.hours >=0 && tm.hours <=23) )
    {
        DLOG_ERROR("Invalid Value of Hours");
        return false;
    }
    if ( !(tm.minutes >=0 && tm.minutes <= 59) )
    {
        DLOG_ERROR("Invalid Value of Minutes");
        return false;
    }
    if ( !(tm.seconds >= 0 && tm.seconds <= 59) )
    {
        DLOG_ERROR("Invalid Value of Seconds");
        return false;
    }

    return true;
}

int IWFUtils::CompareVplmnId(const uint8_t *plmn, std::string imsi, std::string ruleName)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::CompareVplmnId Entry");
    std::string vplmn = "";
    IWFUtils::TBCDToString(&plmn[0], MAP_GR_REQUESTING_PLMN_ID_SZ, vplmn, 0, true);

    std::string mcc = "", mnc = "";
    std::string callingGtAddrDigits = "";
    IWFUtils::ExtractMncMcc(imsi, mcc, mnc);

    std::vector<std::string> l_vplmnId;
    std::vector<std::string>::iterator it;
    //l_vplmnId = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, DIAMETER_S6A_APPLICATION_ID, serviceKey, callingGtAddrDigits)->vplmnId();
    l_vplmnId = IwfController::Instance().Config().RoutingRules().Route(ruleName,callingGtAddrDigits)->vplmnId();

    DLOG_DEBUG("VplmnId Rcvd = %s", vplmn.c_str());
    int cmp_result = -1;
    for(unsigned int i = 0; i < l_vplmnId.size(); i++)
    {
        cmp_result = strcasecmp(l_vplmnId[i].c_str(), vplmn.c_str());
        if(!cmp_result)
        {
            break;
        }
    }
    DLOG_DEBUG("S6aToMAPHandler::CompareVplmnId Exit");
    return cmp_result;
}

void IWFUtils::SetDestHost(DIA_BASE_CMD* cmd, const std::string& dhost)
{
    bool dhostPresent = (cmd->getDestinationHost() != NULL);

    // Set the Destination Host in the Command
    diameter::AVPContainer& cont = const_cast<diameter::AVPContainer&>(
            cmd->GetBaseGenCommand()->getImpl().getContainer());
    cont.add(diameter::base::BaseAttributeName::DestinationHost,
            diameter::base::DestinationHost(dhost), true);
    cmd->ApplyFlags(diameter::DIA_REROUTE_REQ);

    // Set the Destination Host in the BaseCommand
    cmd->setDestinationHost(dhost);

    // Now set the Destination Host in the encoded buffer
    SetDestHostToBuf(cmd, dhost, dhostPresent);
}

static inline uint32_t PadSize(uint32_t len)
{
    return (4 - (len & 3)) & 3;
}
static inline uint32_t EncSize(uint32_t len)
{
    return len + PadSize(len);
}

// The caller needs to mention if the destination Host was present before in the
// original message or not. The msg passed will have the Destination-Host set
void IWFUtils::SetDestHostToBuf(DIA_BASE_CMD* msg, const std::string& dhost, 
        bool alreadyPresent)
{
    int buffLenDiff = 0;
    uint8_t* buf = (uint8_t*)msg->getEncodedBuf();
    unsigned bufLen = msg->getEncodedBufLen();

    if (alreadyPresent)
    {
        size_t oldDhostLen = msg->getDestinationHost()->value().size();
        buffLenDiff = EncSize(dhost.size()) - EncSize(oldDhostLen);
    }
    else
    {
        buffLenDiff = EncSize(dhost.size()) + AVP_HDR_SZ;
    }
    if (buffLenDiff > 0)
    {
        uint8_t* oldBuf = buf; // for freeing in case realloc fails
        // Realloc might be faster, it is possible that it might return
        // the same pointer (no copy)
        buf = (uint8_t*)realloc(buf, bufLen + buffLenDiff);

	if (!buf)
	{
	    if (oldBuf)
	    {
	        free(oldBuf);
	    }
	    return;
	}

        msg->setEncodedBuf(buf);
    }
    msg->setEncodedBufLen(bufLen + buffLenDiff);

    unsigned pos = CMD_HDR_SZ;
    unsigned avpCode = 0;
    unsigned avpLenFlags = 0;
    unsigned avpLen = 0;
    unsigned avpFlags = 0;
    while(pos < bufLen)
    {
        // Get AVP code
        avpCode = ntohl(*(unsigned*)(buf+pos));
        pos += 4;

        // Get AVP Flags and length
        avpLenFlags = ntohl(*(unsigned*)(buf+pos));
        pos += 4;
        avpLen = (avpLenFlags & 0xFFFFFF) - AVP_HDR_SZ;
        avpFlags = avpLenFlags >> 24;
        if (avpFlags & 0x80) // v-bit
        {
            pos += 4;
            avpLen -= 4;
        }
        if (alreadyPresent && avpCode == DEST_HOST_AVP_CODE)
        {
            if (buffLenDiff != 0)
            {
                uint32_t nextAvpOffset = pos + EncSize(avpLen);
                if (nextAvpOffset < bufLen)
                {
                    uint8_t* src = buf + nextAvpOffset;
                    memmove(src + buffLenDiff, src, bufLen - nextAvpOffset);
                }
            }

            // Change the AVP Len
            avpLen = AVP_HDR_SZ + dhost.size();
            *((unsigned*)(buf + pos - 4)) = htonl(MBIT_FULL | avpLen);

            memcpy(buf + pos, dhost.c_str(), dhost.size());
            pos += dhost.size();
            if (dhost.size() % 4)
            {
                memset(buf + pos, 0, PadSize(dhost.size()));
            }
            break;
        }
        else if (!alreadyPresent && avpCode == CC_REQUEST_NUMBER_AVP_CODE)
        {
            // Destination-Host not present in the original message
            // Include the destination host after the CC-Request-Type AVP
            uint32_t nextAvpOffset = pos + EncSize(avpLen);
            if (nextAvpOffset < bufLen)
            {
                uint8_t* src = buf + nextAvpOffset;
                memmove(src + buffLenDiff, src, bufLen - nextAvpOffset);
            }
            pos += avpLen; // Skip this AVP

            // Set AVP code
            *((unsigned*)(buf + pos)) = htonl(DEST_HOST_AVP_CODE);
            pos += 4;

            // Set the flag and avpLen
            avpLen = AVP_HDR_SZ + dhost.size();
            *((unsigned*)(buf + pos)) = htonl(MBIT_FULL | avpLen);
            pos += 4;

            // Set the contents
            memcpy(buf + pos, dhost.c_str(), dhost.size());
            pos += dhost.size();
            if (dhost.size() % 4)
            {
                memset(buf + pos, 0, PadSize(dhost.size()));
            }
            break;
        }
        pos += EncSize(avpLen); // Skip pad bytes too if any
    }

    // Set the modified length to the Diameter Message header
    *((unsigned*)buf) = htonl(DIA_VERSION_FULL | msg->getEncodedBufLen());
}

/* Based on OddEvenIndicator parameter, extracts either odd or even number of AddressSignals  */
void IWFUtils::TrimAddrSignal(std::string &in_outStrAddrSignal, const unsigned int &oddEvenIndi)
{
    size_t len = in_outStrAddrSignal.size();    
    
    if(oddEvenIndi)
    {   
         if(len % 2 == 0)
         {
          	in_outStrAddrSignal.erase(len-1,std::string::npos);
         }
    }

}

void IWFUtils::CreateVisitedPlmn(unsigned char* plmn, 
        std::string& mcc, std::string& mnc)
{
    const char* mcc_arr = mcc.c_str();
    const char* mnc_arr = mnc.c_str();
    plmn[0] = ((mcc_arr[1] - '0') << 4)| (mcc_arr[0] - '0');
    if (mnc.length() == 3)
    {
        plmn[1] = ((mnc_arr[2] - '0') << 4)| (mcc_arr[2] - '0');
    }
    else
    {
        plmn[1] = 0xf0 | (mcc_arr[2] - '0');
    }
    plmn[2] = ((mnc_arr[1] - '0') << 4)|(mnc_arr[0] - '0');
}

int IWFUtils::ValidateLocalHostIP(std::vector<string>& ipAddress, int port, bool isIPv6)
{
    int retVal = ITS_SUCCESS;
    int sockFd;
    DLOG_DEBUG("CMAPIIwfConfig::ValidateLocalHostIP entry");
    if((sockFd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)) < 0) 
    {
        DLOG_ERROR("Unable to create Socket");
        retVal = !ITS_SUCCESS;
    }
    else
    {
        if( isIPv6 )
        {
            struct sockaddr_in6 lSocket[MAX_IP_ADDRS];
            memset(lSocket, 0, sizeof(sockaddr_in)*MAX_IP_ADDRS);
            for( unsigned int currIp = 0 ; currIp < ipAddress.size(); currIp++ )
            {
                lSocket[currIp].sin6_family = AF_INET;
                lSocket[currIp].sin6_port = port;
                if ( inet_pton(AF_INET6, ipAddress[currIp].c_str(),
                            &(lSocket[currIp].sin6_addr)) == 0 )
                {
                    DLOG_ERROR("Convertion to IPv6 address failed ");
                    return !ITS_SUCCESS;
                }
            }
            if (sctp_bindx(sockFd, (sockaddr *)lSocket,
                        ipAddress.size(), SCTP_BINDX_ADD_ADDR) < 0)
            {
                DLOG_ERROR("local host Ip bind failed .errno = %d.",errno);
                retVal = !ITS_SUCCESS;
            }
            else
            {
                DLOG_DEBUG("Validation of local host ip successful");
            }
        }
        else
        {
            struct sockaddr_in lSocket[MAX_IP_ADDRS];
            memset(lSocket, 0, sizeof(sockaddr_in)*MAX_IP_ADDRS);
            for( unsigned int currIp = 0 ; currIp < ipAddress.size(); currIp++ )
            {
                lSocket[currIp].sin_family = AF_INET;
                lSocket[currIp].sin_port = port;
                lSocket[currIp].sin_addr.s_addr = inet_addr(ipAddress[currIp].c_str());
            }
            if (sctp_bindx(sockFd, (sockaddr *)lSocket,
                        ipAddress.size(), SCTP_BINDX_ADD_ADDR) < 0)
            {
                DLOG_ERROR("local host Ip bind failed.errno = %d.",errno);
                retVal = !ITS_SUCCESS;
            }
            else
            {
                DLOG_DEBUG("Validation of local host ip successful");
            }
        }
    }
    DLOG_DEBUG("CMAPIIwfConfig::ValidateLocalHostIP exit");
    return retVal;
}

bool IWFUtils::GenerateKASMEKey(unsigned char * visited_plmn, unsigned char * autn,
        unsigned char * ck, unsigned char * ik, unsigned char *kasme)
{
    unsigned char FC = 0x10;
    unsigned char String[14];
    unsigned char indx = 0;
    int AUC_CK_MAX_LENGTH = 16, AUC_IK_MAX_LENGTH = 16, AUC_MCC_MNC_LENGTH = 3, AUC_AUTH_TOK_LENGTH = 6;
    unsigned char ck_ik[AUC_CK_MAX_LENGTH + AUC_IK_MAX_LENGTH];

    /* MAke the string from the given inputs */
    memset ( String, 0, 14 );

    /* Copy the FC value */
    String[indx++] = FC;

    /* Copy the P0 and L0 values that is SNID and its length */
    /* Assuming that the given PLMN will in the same format as the SNID */
    KDF_String_concatenation ( visited_plmn, AUC_MCC_MNC_LENGTH, String, indx );

    /* Copy the P1 and L1 values that is SQN ^ AK  and its length to the string */
    /* Since the first six bytes of AUTN is SQN ^AK and already calculated taking that value */
    KDF_String_concatenation ( &autn[0], AUC_AUTH_TOK_LENGTH, String, indx );

    /* Generate the Key that is CK || IK */
    memset ( ck_ik, 0, sizeof ( ck_ik ) );

    memcpy ( ck_ik, ck, AUC_CK_MAX_LENGTH );

    memcpy ( ck_ik + AUC_CK_MAX_LENGTH, ik, AUC_IK_MAX_LENGTH );

    /* Call HMAC Sha for generating the KASME with ck_ik and String */
    HmacSha256 ( ck_ik, sizeof ( ck_ik ), String, indx, kasme, 32 );

    return true;
}

bool IWFUtils::HmacSha256 ( unsigned char * key, unsigned int key_size, unsigned char * message_p, unsigned int len, unsigned char * mac, unsigned   int mac_len ) 
{
    HmacSha256Ctx_S ctx; 

    HmacSha256Init ( &ctx, key, key_size );

    Sha256Update ( &ctx.ctx_inside, message_p, len );

    HmacSha256Final ( &ctx, mac, mac_len );

    return true;
}

void IWFUtils::HmacSha256Init ( HmacSha256Ctx_S * ctx_p, unsigned char * key, unsigned int key_size )
{
    unsigned int fill;

    unsigned int num;

    unsigned char *key_used;

    unsigned char key_temp[SHA256_DIGEST_SIZE];

    unsigned int i;

    if ( key_size == SHA256_BLOCK_SIZE )
    {
        key_used = key;

        num = SHA256_BLOCK_SIZE;
    }
    else
    {
        if ( key_size > SHA256_BLOCK_SIZE )
        {
            key_used = key_temp;

            num = SHA256_DIGEST_SIZE;

            Sha256 ( key, key_size, key_used );
        }
        else
        {                       /* key_size > SHA256_BLOCK_SIZE */
            key_used = key;

            num = key_size;
        }
        fill = SHA256_BLOCK_SIZE - num;

        memset ( ctx_p->block_ipad + num, 0x36, fill );

        memset ( ctx_p->block_opad + num, 0x5c, fill );
    }

    for ( i = 0; i < num; i++ )
    {
        ctx_p->block_ipad[i] = key_used[i] ^ 0x36;

        ctx_p->block_opad[i] = key_used[i] ^ 0x5c;
    }

    Sha256Init ( &ctx_p->ctx_inside );

    Sha256Update ( &ctx_p->ctx_inside, ctx_p->block_ipad, SHA256_BLOCK_SIZE );

    Sha256Init ( &ctx_p->ctx_outside );

    Sha256Update ( &ctx_p->ctx_outside, ctx_p->block_opad, SHA256_BLOCK_SIZE );

    /* for hmac_reinit */
    memcpy ( &ctx_p->ctx_inside_reinit, &ctx_p->ctx_inside, sizeof ( Sha256Ctx_S ) );

    memcpy ( &ctx_p->ctx_outside_reinit, &ctx_p->ctx_outside, sizeof ( Sha256Ctx_S ) );

    return;
}

void IWFUtils::HmacSha256Final ( HmacSha256Ctx_S * ctx_p, unsigned char * mac, unsigned int mac_size )
{
    unsigned char digest_inside[SHA256_DIGEST_SIZE];

    unsigned char mac_temp[SHA256_DIGEST_SIZE];

    Sha256Final ( &ctx_p->ctx_inside, digest_inside );

    Sha256Update ( &ctx_p->ctx_outside, digest_inside, SHA256_DIGEST_SIZE );

    Sha256Final ( &ctx_p->ctx_outside, mac_temp );

    memcpy ( mac, mac_temp, mac_size );

    return;
}

void IWFUtils::Sha256Transf ( Sha256Ctx_S * ctx_p, unsigned char * message_p, unsigned int block_nb )
{
    unsigned int w[64];

    unsigned int wv[8];

    unsigned int t1, t2;

    const unsigned char *sub_block;

    unsigned short i;

    unsigned short j;

    for ( i = 0; i < ( int ) block_nb; i++ )
    {
        sub_block = message_p + ( i << 6 );

        for ( j = 0; j < 16; j++ )
        {
            PACK32 ( &sub_block[j << 2], &w[j] );
        }

        for ( j = 16; j < 64; j++ )
        {
            SHA256_SCR ( j );
        }

        for ( j = 0; j < 8; j++ )
        {
            wv[j] = ctx_p->h[j];
        }

        for ( j = 0; j < 64; j++ )
        {
            t1 = wv[7] + SHA256_F2 ( wv[4] ) + CH ( wv[4], wv[5], wv[6] ) + sha256_k[j] + w[j];

            t2 = SHA256_F1 ( wv[0] ) + MAJ ( wv[0], wv[1], wv[2] );

            wv[7] = wv[6];

            wv[6] = wv[5];

            wv[5] = wv[4];

            wv[4] = wv[3] + t1;

            wv[3] = wv[2];
            wv[2] = wv[1];

            wv[1] = wv[0];

            wv[0] = t1 + t2;
        }


        for ( j = 0; j < 8; j++ )
        {
            ctx_p->h[j] += wv[j];
        }
    }

    return;
}

void IWFUtils::Sha256Update ( Sha256Ctx_S * ctx_p, unsigned char * message_p, unsigned int len )
{
    unsigned int block_nb;

    unsigned int new_len, rem_len, tmp_len;

    unsigned char *shifted_message_p;

    tmp_len = SHA256_BLOCK_SIZE - ctx_p->len;

    rem_len = len < tmp_len ? len : tmp_len;

    memcpy ( &ctx_p->block[ctx_p->len], message_p, rem_len );

    if ( ctx_p->len + len < SHA256_BLOCK_SIZE )
    {
        ctx_p->len += len;

        return;
    }

    new_len = len - rem_len;

    block_nb = new_len / SHA256_BLOCK_SIZE;

    shifted_message_p = message_p + rem_len;

    Sha256Transf ( ctx_p, ctx_p->block, 1 );

    Sha256Transf ( ctx_p, shifted_message_p, block_nb );

    rem_len = new_len % SHA256_BLOCK_SIZE;

    memcpy ( ctx_p->block, &shifted_message_p[block_nb << 6], rem_len );

    ctx_p->len = rem_len;

    ctx_p->tot_len += ( block_nb + 1 ) << 6;

    return;
}
void IWFUtils::Sha256Final ( Sha256Ctx_S * ctx_p, unsigned char * digest )
{
    unsigned int block_nb;

    unsigned int pm_len;

    unsigned int len_b;

    unsigned char i;

    block_nb = ( 1 + ( ( SHA256_BLOCK_SIZE - 9 ) < ( ctx_p->len % SHA256_BLOCK_SIZE ) ) );

    len_b = ( ctx_p->tot_len + ctx_p->len ) << 3;

    pm_len = block_nb << 6;

    memset ( ctx_p->block + ctx_p->len, 0, pm_len - ctx_p->len );

    ctx_p->block[ctx_p->len] = 0x80;

    UNPACK32 ( len_b, ctx_p->block + pm_len - 4 );

    Sha256Transf ( ctx_p, ctx_p->block, block_nb );

    for ( i = 0; i < 8; i++ )
    {
        UNPACK32 ( ctx_p->h[i], &digest[i << 2] );
    }

    return;
}

void IWFUtils::Sha256Init ( Sha256Ctx_S * ctx_p )
{
    unsigned char i;

    for ( i = 0; i < 8; i++ )
    {
        ctx_p->h[i] = sha256_h0[i];
    }
    ctx_p->len = 0;

    ctx_p->tot_len = 0;

    return;
}
unsigned char IWFUtils::Sha256 ( unsigned char * message_p, unsigned int len, unsigned char * digest )
{
    Sha256Ctx_S ctx;

    Sha256Init ( &ctx );

    Sha256Update ( &ctx, message_p, len );

    Sha256Final ( &ctx, digest );

    return true;
}
