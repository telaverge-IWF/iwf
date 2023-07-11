#ifndef __IWF_PROT_UITLS_h__
#define __IWF_PROT_UITLS_h__

#include "iwf_prot_defines.h"
#include "iwf.h"
#ifdef GCC_LESS_THAN_4_3
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif
#include <stdexcept>
#include <diameter/Types.h>

#define IWF_FixedArraySize(_array) \
    (sizeof(_array) / sizeof(_array[0]))

#define IWF_FixedArrayToVector(_array) \
    std::vector<byte>(_array, _array + IWF_FixedArraySize(_array))

#define TIME_FROM_1900_TO_EPOCH 2208988800


struct TimeAndDate {
    ITS_UINT year;
    ITS_UINT month;
    ITS_UINT day;
    ITS_UINT hours;
    ITS_UINT minutes;
    ITS_UINT seconds;
    uint8_t tz[2];
};

#define KDF_String_concatenation(P0, L0, String, indx) \
    memcpy((unsigned char *)&String[indx], (unsigned char *)P0, L0); \
    indx+=L0; \
    String[indx++] = 0x00;\
    String[indx++] = L0;

#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32

#define UNPACK32(x, str)                      \
{                                             \
    *((str) + 3) = (unsigned char) ((x)      );       \
    *((str) + 2) = (unsigned char) ((x) >>  8);       \
    *((str) + 1) = (unsigned char) ((x) >> 16);       \
    *((str) + 0) = (unsigned char) ((x) >> 24);       \
}

#define PACK32(str, x)                        \
{                                             \
    *(x) =   ((unsigned int) *((str) + 3)      )    \
    | ((unsigned int) *((str) + 2) <<  8)    \
    | ((unsigned int) *((str) + 1) << 16)    \
    | ((unsigned int) *((str) + 0) << 24);   \
}

#define SHFR(x, n)    (x >> n)

static unsigned int sha256_h0[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

static unsigned int sha256_k[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define CH(x, y, z)  ((x & y) ^ (~x & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

/* Macros used for loops unrolling */
#define SHA256_SCR(i)                         \
{                                             \
    w[i] =  SHA256_F4(w[i -  2]) + w[i -  7]  \
    + SHA256_F3(w[i - 15]) + w[i - 16]; \
}

#define SHA512_SCR(i)                         \
{                                             \
    w[i] =  SHA512_F4(w[i -  2]) + w[i -  7]  \
    + SHA512_F3(w[i - 15]) + w[i - 16]; \
}

#define SHA256_F1(x) (ROTR(x,  2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SHA256_F2(x) (ROTR(x,  6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SHA256_F3(x) (ROTR(x,  7) ^ ROTR(x, 18) ^ SHFR(x,  3))
#define SHA256_F4(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHFR(x, 10))

struct Sha256Ctx_S
{
    unsigned int tot_len;

    unsigned int len;

    unsigned char block[2 * SHA256_BLOCK_SIZE];

    unsigned int h[8];
};

struct HmacSha256Ctx_S
{
    Sha256Ctx_S ctx_inside;

    Sha256Ctx_S ctx_outside;

    /* for hmac_reinit */
    Sha256Ctx_S ctx_inside_reinit;

    Sha256Ctx_S ctx_outside_reinit;

    unsigned char block_ipad[SHA256_BLOCK_SIZE];

    unsigned char block_opad[SHA256_BLOCK_SIZE];
};

class IWFUtils
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

        static std::string ReverseVectorToString(const std::vector<byte>& vec);

        // Works only with g++, not sure on other compilers
        static std::vector<bool> UnsignedToBitVector(unsigned long val, unsigned bits = 32)
        {
            return std::vector<bool>(std::_Bit_iterator(&val, 0),
                    std::_Bit_iterator(&val, bits));
        }

        static std::vector<byte> UnsignedToBytes(uint32_t paramInt, unsigned length = 4)
        {
            vector<byte> arrayOfByte(length);
            for (unsigned i = 0; i < length; i++)
                arrayOfByte[length - i - 1] = ((paramInt >> (i * 8)) & 0xff);
            return arrayOfByte;
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
            //return ntohl(*(unsigned*)(&vec[0]));
            uint8_t cVal[4] = {0};
            for (unsigned idx = 0; idx < vec.size() && idx < 4; idx++)
            {
                cVal[idx] = vec[idx];
            }
            return ntohl(*(unsigned*)(&cVal[0]));
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
                    IWF_MAX_E164_SZ, 0xF);
        }

        static void TBCDToString(const uint8_t *tbcd, int len, std::string &str, bool odd = false, bool rev = false, bool dontdiscard = false);

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

        static diameter::Address GSNAddressToDiaAddress(const std::vector<byte>& gsnAddr);

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
        static void ExtractMncMcc(const std::string& imsi, std::string& mcc, std::string& mnc);

        static bool CheckDateAndTime(struct TimeAndDate tm);

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

        static int ValidateIPString(const std::string &ipaddr, bool &isIPv4);

        static int CompareVplmnId(const uint8_t *plmn, std::string imsi, std::string ruleName);

        static void SetDestHost(DIA_BASE_CMD* cmd, const std::string& dhost);

        static void SetDestHostToBuf(DIA_BASE_CMD* cmd, const std::string& dhost, 
                          bool alreadyPresent = true);

        static void TrimAddrSignal(std::string &in_outStrAddrSignal,const unsigned int &oddEvenIndi);

        static void CreateVisitedPlmn(unsigned char* plmn, std::string& mcc, std::string& mnc);
        static int ValidateLocalHostIP(std::vector<string>& ipAddress, int port, bool isIPv6=false);

        static unsigned char Sha256 ( unsigned char * message_p, unsigned int len, unsigned char * digest );
        static void Sha256Init ( Sha256Ctx_S * ctx_p );
        static void Sha256Update ( Sha256Ctx_S * ctx_p, unsigned char * message_p, unsigned int len );
        static void Sha256Final ( Sha256Ctx_S * ctx_p, unsigned char * digest );
        static void Sha256Transf ( Sha256Ctx_S * ctx_p, unsigned char * message_p, unsigned int block_nb );
        static void HmacSha256Init ( HmacSha256Ctx_S * ctx_p, unsigned char * key, unsigned int key_size );
        static void HmacSha256Final ( HmacSha256Ctx_S * ctx_p, unsigned char * mac, unsigned int mac_size );
        static bool HmacSha256 ( unsigned char * key, unsigned int key_size, unsigned char * message, unsigned int len, unsigned char * mac, unsigned int mac_len );

        static bool GenerateKASMEKey(unsigned char * visited_plmn, unsigned char * autn, 
                unsigned char * ck, unsigned char * ik, unsigned char *kasme);
        static uint32_t MurmurHash32(std::string inString)
        {
            const char *key = inString.c_str();
            uint32_t len = inString.length();
            uint32_t seed = 0xdeadbeaf;
            static const uint32_t c1 = 0xcc9e2d51;
            static const uint32_t c2 = 0x1b873593;
            static const uint32_t r1 = 15;
            static const uint32_t r2 = 13;
            static const uint32_t m = 5;
            static const uint32_t n = 0xe6546b64;

            uint32_t hash = seed;

            const int nblocks = len / 4;
            const uint32_t *blocks = (const uint32_t *) key;
            int i;
            uint32_t k;
            for (i = 0; i < nblocks; i++) {
                k = blocks[i];
                k *= c1;
                k = (k << r1) | (k >> (32 - r1));
                k *= c2;

                hash ^= k;
                hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
            }

            const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
            uint32_t k1 = 0;

            switch (len & 3) {
                case 3:
                    k1 ^= tail[2] << 16;
                case 2:
                    k1 ^= tail[1] << 8;
                case 1:
                    k1 ^= tail[0];

                    k1 *= c1;
                    k1 = (k1 << r1) | (k1 >> (32 - r1));
                    k1 *= c2;
                    hash ^= k1;
            }

            hash ^= len;
            hash ^= (hash >> 16);
            hash *= 0x85ebca6b;
            hash ^= (hash >> 13);
            hash *= 0xc2b2ae35;
            hash ^= (hash >> 16);

            return hash;
        }

    protected:
        static const std::string sDigits;

#ifdef GCC_LESS_THAN_4_3
        typedef std::tr1::unordered_map<unsigned, unsigned> MccWith3DigitMnc;
        typedef std::tr1::unordered_map<unsigned, unsigned> MccWith2Or3DigitMnc;
#else
        typedef std::unordered_map<unsigned, unsigned> MccWith3DigitMnc;
        typedef std::unordered_map<unsigned, unsigned> MccWith2Or3DigitMnc;
#endif

        static const MccWith3DigitMnc sMccWith3DigitMnc;
        static const MccWith2Or3DigitMnc sMccWith2Or3DigitMnc;


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

        static MccWith2Or3DigitMnc InitMccWith2Or3DigitMnc()
        {
            MccWith2Or3DigitMnc TempMccWith2Or3DigitMnc;

            TempMccWith2Or3DigitMnc[37413] = 1;
            TempMccWith2Or3DigitMnc[37414] = 1;
            TempMccWith2Or3DigitMnc[40500] = 1;
            TempMccWith2Or3DigitMnc[40501] = 1;
            TempMccWith2Or3DigitMnc[40502] = 1;
            TempMccWith2Or3DigitMnc[40503] = 1;
            TempMccWith2Or3DigitMnc[40504] = 1;
            TempMccWith2Or3DigitMnc[40575] = 1;
            TempMccWith2Or3DigitMnc[40579] = 1;
            TempMccWith2Or3DigitMnc[40580] = 1;

            return TempMccWith2Or3DigitMnc;
        }



};

#endif // __IWF_PROT_UITLS_h__
