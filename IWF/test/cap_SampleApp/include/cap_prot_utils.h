#ifndef __CAP_PROT_UITLS_h__
#define __CAP_PROT_UITLS_h__

#include "cap_prot_defines.h"
#ifdef GCC_LESS_THAN_4_3
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif

//#include <diameter/Types.h>

#define CAP_FixedArraySize(_array) \
        (sizeof(_array) / sizeof(_array[0]))

#define CAP_FixedArrayToVector(_array) \
            std::vector<byte>(_array, _array + CAP_FixedArraySize(_array))


class CAPUtils
{
 public:
 
    static std::vector<byte> ByteArrayToVector(uint8_t *array, unsigned sz)
    {
        return std::vector<byte>(array, array + sz);
    }

    static std::vector<byte> StringToVector(const std::string& str)
    {
        return std::vector<byte>(str.begin(), str.end());
    }

    static std::string VectorToString(const std::vector<byte>& vec)
    {
        return std::string(vec.begin(), vec.end());
    }

    // Works only with g++, not sure on other compilers
    static std::vector<bool> UnsignedToBitVector(unsigned long val, unsigned bits = 32)
    {
        return std::vector<bool>(std::_Bit_iterator(&val, 0),
                std::_Bit_iterator(&val, bits));
    }

    static uint32_t BitVectorToUnsigned(const std::vector<bool> &vec)
    {
        std::vector<bool>::const_iterator it;
        int i;
        uint32_t res = 0;
        for(i = 0, it = vec.begin(); it != vec.end(); i++, it++)
        {
            res |= (((int)*it) << i);
        }
        return res;
    } 

    static uint32_t ByteArray4ToUInt32(const std::vector<uint8_t>& vec)
    {
        return ntohl(*(unsigned*)(&vec[0]));
    }

    template <typename T>
    static void VectorAppend(std::vector<T>& lhs, const std::vector<T>& rhs)
    {
       lhs.insert(lhs.end(), rhs.begin(), rhs.end());
    }

    static unsigned ToHex(char digit)
    {
        if(isalpha(digit))
        {
            return (tolower(digit) - 'a' + 10);
        }
        else
        {
            return digit - '0';
        }
    }

    static char ToChar(unsigned num)
    {
        return sDigits[num];
    }

    static uint8_t Low4(uint8_t octet)
    {
        return (octet & 0x0F);
    }
    static uint8_t High4(uint8_t octet)
    {
        return (octet >> 4);
    }

    static int StringToTBCD(const std::string &str, uint8_t *tbcd, int len, unsigned pad = 0, bool rev = false);

    static int ExtractIMSIFromUserName(const std::string &userName, uint8_t *imsi)
    {
        return StringToTBCD(userName.substr(0, userName.find('@')), imsi, 
                CAP_MAX_E164_SZ);
    }

    static void TBCDToString(const uint8_t *tbcd, int len, std::string &str, bool odd = false, bool rev = false);

    // Used by config
    static void IpStringToGSNAddress(const std::string &ipStr, its::ByteArray &gsnAddr);

    static void IPAddrToString(int family, const uint8_t *buf, std::string &str)
    {
        char ipStr[INET6_ADDRSTRLEN];
        const char* ret = inet_ntop(family, buf, ipStr, INET6_ADDRSTRLEN);
        if (ret != NULL)
        {
            str.assign(ret);
        }
    }

    //static diameter::Address GSNAddressToDiaAddress(const std::vector<byte>& gsnAddr);

    // static void DiaAddressToIPAddr(const diameter::base::Address& addr,
    //                std::vector<byte>& ipAddr);
    // this is not required, as this is a direct copy

    static void ByteArrayToHexString(const std::vector<byte>& arr, 
                                     std::string& hexStr);

    // DNS labels to displayable string
    template <typename T>
    static void LabelsToString(const T& dnsStr, std::string& res)
    {
        int totLen = dnsStr.size();
        int pos = 0, lLen;
        while (true)
        {
            lLen = dnsStr[pos];
            if (!lLen) break;

            // Similar to substring operation
            res += std::string(dnsStr.begin()+pos+1, dnsStr.begin()+pos+1+lLen);
            // res += dnsStr.substr(pos+1, lLen);
            pos += lLen + 1;
            if (pos + 1 >= totLen) break;
            res += '.';
        }
    }

    static void ExtractMncMcc(const std::vector<byte>& imsi, unsigned& mcc, unsigned& mnc);
    static void ExtractMncMcc(const std::string& imsi, unsigned& mcc, unsigned& mnc);

    template <typename T>
    static void ConstructPLMN(T& plmn, unsigned mcc, unsigned mnc)
    {
        uint8_t oct;

        // First Octet - mcc Digit 2 | mcc Digit 1
        oct = ((mcc / 10 ) % 10) | (mcc / 100);
        plmn.push_back(oct);

        // Second Octet - mnc Digit 3 | mcc Digit 3, for 2 digit mnc have F
        oct = (mnc < 100) ? (0xF | (mcc % 10)) :
                            ( (mnc % 10) | (mcc % 10) );
        plmn.push_back(oct);

        // Third octet - mnc digit 2 | mnc Digit 1
        oct = ((mnc / 10 ) % 10) | (mnc / 100);
        plmn.push_back(oct);
    }

 protected:
    static const std::string sDigits;

#ifdef GCC_LESS_THAN_4_3
    typedef std::tr1::unordered_map<unsigned, unsigned> MccWith3DigitMnc;
#else
    typedef std::unordered_map<unsigned, unsigned> MccWith3DigitMnc;
#endif 
    static const MccWith3DigitMnc sMccWith3DigitMnc;

    /* This methods will be ivoked to initialize the map for GCC less than 4.4 */
    static MccWith3DigitMnc InitMccWith3DigitMnc()
    {   
        MccWith3DigitMnc TempMccWith3DigitMnc;
        
        //TempMccWith3DigitMnc[262] = 2;    // Mixture of 2 and 3-digit MNCs
        TempMccWith3DigitMnc[302] = 1;
        TempMccWith3DigitMnc[310] = 1;
        TempMccWith3DigitMnc[311] = 1;
        TempMccWith3DigitMnc[312] = 1;
        TempMccWith3DigitMnc[313] = 1;
        TempMccWith3DigitMnc[316] = 1;
        TempMccWith3DigitMnc[334] = 1;
        TempMccWith3DigitMnc[338] = 1;
        TempMccWith3DigitMnc[342] = 1;
        TempMccWith3DigitMnc[344] = 1;
        TempMccWith3DigitMnc[346] = 1;
        TempMccWith3DigitMnc[348] = 1;
        TempMccWith3DigitMnc[350] = 1;
        TempMccWith3DigitMnc[352] = 1;
        TempMccWith3DigitMnc[354] = 1;
        TempMccWith3DigitMnc[356] = 1;
        TempMccWith3DigitMnc[358] = 1;
        TempMccWith3DigitMnc[360] = 1;
        TempMccWith3DigitMnc[365] = 1;
        TempMccWith3DigitMnc[366] = 1;
        TempMccWith3DigitMnc[374] = 2;     // Mixture of 2 and 3-digit MNCs
        TempMccWith3DigitMnc[376] = 1;
        TempMccWith3DigitMnc[405] = 2;
        //TempMccWith3DigitMnc[502] = 1;     // Mixture of 2 and 3-digit MNCs
        TempMccWith3DigitMnc[708] = 1;     // Mixture of 2 and 3-digit MNCs
        //TempMccWith3DigitMnc[710] = 1;     // Mixture of 2 and 3-digit MNCs
        TempMccWith3DigitMnc[722] = 1;
        TempMccWith3DigitMnc[732] = 1;
        TempMccWith3DigitMnc[750] = 1;

        return TempMccWith3DigitMnc;
    }
};

	
#endif // __CAP_PROT_UITLS_h__
