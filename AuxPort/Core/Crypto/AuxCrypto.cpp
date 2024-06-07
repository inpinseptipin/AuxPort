#include "AuxCrypto.h"
#include <bitset>

uint32_t AuxPort::MD5::S[64] = { 
                               7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                               5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                               4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                               6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 
                             };

uint32_t AuxPort::MD5::K[64] = { 
                               0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                               0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                               0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                               0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                               0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                               0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                               0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                               0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                               0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                               0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                               0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                               0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                               0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                               0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                               0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                               0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 
                             };

uint32_t AuxPort::MD5::F(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & y) | (~x & z));
}

uint32_t AuxPort::MD5::G(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & z) | (y & ~z));
}

uint32_t AuxPort::MD5::H(uint32_t x, uint32_t y, uint32_t z)
{
    return (x ^ y ^ z);
}

uint32_t AuxPort::MD5::I(uint32_t x, uint32_t y, uint32_t z)
{
    return (y ^ (x | ~z));
}

uint32_t AuxPort::MD5::rotateLeft(uint32_t x, uint32_t n)
{
    return (x << n) | (x >> (32 - n));
}

std::vector<uint8_t> AuxPort::MD5::getPaddedData(const std::string& data)
{
    std::vector<uint8_t> paddedData(data.begin(), data.end());
    paddedData.push_back(0x80);
    while (paddedData.size() % 64 != 56)
        paddedData.push_back(0x00);

    // Padding with original data size
    size_t dataLengthInBits = data.size() * 8;
    for (int i = 0; i < 8; ++i)
    {
        paddedData.push_back(dataLengthInBits & 0xFF);
        dataLengthInBits >>= 8;
    }
    return paddedData;
}

std::string AuxPort::MD5::computeHash(const std::vector<uint8_t>& paddedData)
{
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    size_t blockCount = paddedData.size() / 64;
    for (size_t blockIndex = 0; blockIndex < blockCount; ++blockIndex)
    {
        uint32_t AA = a0;
        uint32_t BB = b0;
        uint32_t CC = c0;
        uint32_t DD = d0;

        uint32_t E;
        unsigned int j;
        for (unsigned int i = 0; i < 64; ++i)
        {
            switch (i / 16) 
            {
            case 0:
                E = F(BB, CC, DD);
                j = i;
                break;
            case 1:
                E = G(BB, CC, DD);
                j = ((i * 5) + 1) % 16;
                break;
            case 2:
                E = H(BB, CC, DD);
                j = ((i * 3) + 5) % 16;
                break;
            default:
                E = I(BB, CC, DD);
                j = (i * 7) % 16;
                break;
            }

            uint32_t temp = DD;
            DD = CC;
            CC = BB;
            BB = BB + rotateLeft(AA + E + K[i] + getWord(paddedData, blockIndex * 16 + j), S[i]);
            AA = temp;
        }

        a0 += AA;
        b0 += BB;
        c0 += CC;
        d0 += DD;
    }

    a0 = convertToBigEndian(a0);
    b0 = convertToBigEndian(b0);
    c0 = convertToBigEndian(c0);
    d0 = convertToBigEndian(d0);
    return getHexString(a0) + getHexString(b0) + getHexString(c0) + getHexString(d0);
}

std::string AuxPort::MD5::getHexString(uint32_t num)
{
    std::ostringstream oss;
    oss << std::hex << std::setw(8) << std::setfill('0') << num;
    return oss.str();
}

uint32_t AuxPort::MD5::getWord(const std::vector<uint8_t>& paddedData, size_t wordIndex)
{
    return 
        (static_cast<uint32_t>(paddedData[wordIndex * 4])) |
        ((static_cast<uint32_t>(paddedData[wordIndex * 4 + 1]) << 8)) |
        ((static_cast<uint32_t>(paddedData[wordIndex * 4 + 2]) << 16)) |
        ((static_cast<uint32_t>(paddedData[wordIndex * 4 + 3]) << 24));
}

uint32_t AuxPort::MD5::convertToBigEndian(uint32_t num)
{
    return ((num & 0x000000FF) << 24) | ((num & 0x0000FF00) << 8) | ((num & 0x00FF0000) >> 8) | ((num & 0xFF000000) >> 24);
}

std::string AuxPort::MD5::hash(const std::string& data)
{
    std::vector<uint8_t> paddedData = getPaddedData(data);
    return computeHash(paddedData);
}