/** @file
* @author lvkai
* @version 1.0

This is the implementation for libmd5digest.a which is used for generate the digest for file or string.
Library : libmd5digest.a
Package : md5digest
Module  : md5digest

Copyright (c) 2013, md5.
All rights reserved.
*/

#include <string.h>
#include <stdio.h>
#include "md5digest.h"

/*F, G, H and I are basic Md5Digest functions for transformation round.*/
#define F_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define F_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define F_H(x, y, z) ((x) ^ (y) ^ (z))
#define F_I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* Transformations for rounds F, G, H, and I.
 Rotation is separate from addition to prevent recomputation.
 */
#define ROUND(op ,a, b, c, d, x, s, ac) { \
    (a) += F_##op ((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}


/**@addto group constant Cnstant and static members.
  @{
 */
/**Buffer size when read file.*/
static const size_t BUFFER_SIZE = 1024;

/**First bit is '1' and then many '0' bits until the original data lengh is 'K*512bits + 448'.*/
static const Byte Padding[64] = { 0x80 };

/**The Hex character is represented by lower letter.*/
static const char Hex[16] = 
{
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};
/**
  @}
*/


/**@addto group InnerVar private variables.
@{
 */
/**Like the state (ABCD) in md5 which used for construct the final digest.*/
static ULong ulState[4] = {0x67542301, 0xefcdab89, 0x98badcfe, 0x10325476};

/**Number of bits of the whole data processed, represented with 64bit(low-order word first).*/
static ULong ulCount[2];

/**Used for each loop compute which get 512bit(or 64byte) each time, and make the state (ABCD) changes.*/
static Byte byteBuffer[64];

/**Store the final digest we want.*/
static Byte byteDigest[16];

/**Whether we finished calculate?.*/
static int bFinished;
/**
  @}
*/


/**@addto group InnerFunction Private functions.*/
/**@{*/

/**@brief Reset state for new input data.*/
static void reset(void);

/**@brief Update state and record processed bit of input data (one time 512bit).*/
static void update(const Byte *input, size_t length) ;

/**@brief Used for update the state with each 512bit data block.*/
static void transform(const Byte block[64]) ;

/**@brief Transfer data represented with Byte to ULong type.*/
static void decode(const Byte *input, ULong *output, size_t length) ;

/**@brief Get the digest of the data we input for the result.*/
static void digest(char* hexDigest);

/**@brief Append extra data to make original data length modulo 2^512bit for compute.*/
static void final(void);

/**@brief Transfer data represented with ULong type to Byte.*/
static void encode(const ULong *input, Byte *output, size_t length) ;

/**@brief Convert byte array to hex string.*/
static void bytesToHexString(const Byte *input, size_t length, char* outPut); 
/**@}*/


size_t Md5StringDigest(const char* str, char* hexDigest)
{
    reset();
    memset(hexDigest, 0, DIGEST_LEN);

    update((const Byte*)str, strlen(str));
    digest(hexDigest);
    return 0; /*TODO*/
}

size_t Md5FileDigest(const char* filename, char* hexDigest)
{
    int length = 0;
    FILE *fp;

    reset();
    memset(hexDigest, 0, DIGEST_LEN);

    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        fprintf(stderr, "File :%s not exists!\n", filename);
        return -1;
    }

    Byte buffer[BUFFER_SIZE];
    while (!feof(fp)) 
    {
        length = fread(buffer, sizeof(buffer[0]), BUFFER_SIZE, fp);
        if (length > 0)
        {
            update((const Byte*)buffer, length);
        }
    }
    fclose(fp);

    digest(hexDigest);
    return 0; /*TODO*/
}

size_t Md5BufferDigest(const Byte* buf, size_t bufLen, char* hexDigest)
{
    reset();
    memset(hexDigest, 0, DIGEST_LEN);

    update((const Byte*)buf, bufLen);
    digest(hexDigest);
    return 0; /*TODO*/
}


static void reset(void) 
{
    bFinished = 0;
    /* reset number of bits. */
    ulCount[0] = ulCount[1] = 0;
    /* Load magic initialization constants.*/
    ulState[0] = 0x67452301;
    ulState[1] = 0xefcdab89;
    ulState[2] = 0x98badcfe;
    ulState[3] = 0x10325476;
    memset(byteDigest, 0, sizeof(byteDigest));
    memset(byteBuffer, 0, sizeof(byteBuffer));
}

/* @detail Md5Digest block update operation continued with an Md5Digest message-digest operation.
 * In each update, we add the processing data length(of 'length') to 'ulCount',
 * process K*512bit blocks and update the 'state' due to the blocks,
 * then remain the length % 512 bits to 'final' function.
 */
static void update(const Byte *input, size_t length) 
{

    ULong idx, index, partLen;

    bFinished = 0;

    /* Compute number of processed bytes mod 64, we will copy data to &byteBuffer[index]*/
    index = (ULong)((ulCount[0] >> 3) & 0x3f);

    /* update number of bits (convert length byte to length<<3 bits)*/
    if((ulCount[0] += ((ULong)length << 3)) < ((ULong)length << 3))
    {
        ulCount[1]++;
    }
    ulCount[1] += ((ULong)length >> 29);/*high 3 bit of length is 17,18,19 if (length << 3) so add to ulCount[1]*/

    partLen = 64 - index;
    /* transform as many times as possible.*/
    if(length >= partLen) 
    {

        memcpy(&byteBuffer[index], input, partLen);
        transform(byteBuffer);

        for(idx = partLen; idx + 63 < length; idx += 64)
        {
            transform(&input[idx]);
        }
        index = 0;

    } 
    else 
    {
        idx = 0;
    }

    /* Buffer remaining input*/
    memcpy(&byteBuffer[index], &input[idx], length-idx);
}

/** @detail Md5Digest basic transformation, transforms ulState based on each 512bit block.
 * We can change here to modify the algorithm result.
 */
static void transform(const Byte block[64])
{

    ULong a = ulState[0], b = ulState[1], c = ulState[2], d = ulState[3], x[16];

#if MD5 == 1
    int S[4][4] = 
    {
        { 7, 12, 17, 22},
        { 5,  9, 14, 20},
        { 4, 11, 16, 23},
        { 6, 10, 15, 21}
    };
#else
    int S[4][4] = 
    {
        { 1,  3,  5,  7},
        { 8, 10, 12, 14},
        {17, 19, 21, 23},
        {24, 26, 28, 30}
    };
#endif

    decode(block, x, 64);

    /* Round 1*/
    ROUND(F, a, b, c, d, x[ 0], S[0][0], 0xd76aa478); /*1*/
    ROUND(F, d, a, b, c, x[ 1], S[0][1], 0xe8c7b756); /*2*/
    ROUND(F, c, d, a, b, x[ 2], S[0][2], 0x242070db); /*3*/
    ROUND(F, b, c, d, a, x[ 3], S[0][3], 0xc1bdceee); /*4*/
    ROUND(F, a, b, c, d, x[ 4], S[0][0], 0xf57c0faf); /*5*/
    ROUND(F, d, a, b, c, x[ 5], S[0][1], 0x4787c62a); /*6*/
    ROUND(F, c, d, a, b, x[ 6], S[0][2], 0xa8304613); /*7*/
    ROUND(F, b, c, d, a, x[ 7], S[0][3], 0xfd469501); /*8*/
    ROUND(F, a, b, c, d, x[ 8], S[0][0], 0x698098d8); /*9*/
    ROUND(F, d, a, b, c, x[ 9], S[0][1], 0x8b44f7af); /*10*/
    ROUND(F, c, d, a, b, x[10], S[0][2], 0xffff5bb1); /*11*/
    ROUND(F, b, c, d, a, x[11], S[0][3], 0x895cd7be); /*12*/
    ROUND(F, a, b, c, d, x[12], S[0][0], 0x6b901122); /*13*/
    ROUND(F, d, a, b, c, x[13], S[0][1], 0xfd987193); /*14*/
    ROUND(F, c, d, a, b, x[14], S[0][2], 0xa679438e); /*15*/
    ROUND(F, b, c, d, a, x[15], S[0][3], 0x49b40821); /*16*/

    /* Round 2*/
    ROUND(G, a, b, c, d, x[ 1], S[1][0], 0xf61e2562); /*17*/
    ROUND(G, d, a, b, c, x[ 6], S[1][1], 0xc040b340); /*18*/
    ROUND(G, c, d, a, b, x[11], S[1][2], 0x265e5a51); /*19*/
    ROUND(G, b, c, d, a, x[ 0], S[1][3], 0xe9b6c7aa); /*20*/
    ROUND(G, a, b, c, d, x[ 5], S[1][0], 0xd62f105d); /*21*/
    ROUND(G, d, a, b, c, x[10], S[1][1],  0x2441453); /*22*/
    ROUND(G, c, d, a, b, x[15], S[1][2], 0xd8a1e681); /*23*/
    ROUND(G, b, c, d, a, x[ 4], S[1][3], 0xe7d3fbc8); /*24*/
    ROUND(G, a, b, c, d, x[ 9], S[1][0], 0x21e1cde6); /*25*/
    ROUND(G, d, a, b, c, x[14], S[1][1], 0xc33707d6); /*26*/
    ROUND(G, c, d, a, b, x[ 3], S[1][2], 0xf4d50d87); /*27*/
    ROUND(G, b, c, d, a, x[ 8], S[1][3], 0x455a14ed); /*28*/
    ROUND(G, a, b, c, d, x[13], S[1][0], 0xa9e3e905); /*29*/
    ROUND(G, d, a, b, c, x[ 2], S[1][1], 0xfcefa3f8); /*30*/
    ROUND(G, c, d, a, b, x[ 7], S[1][2], 0x676f02d9); /*31*/
    ROUND(G, b, c, d, a, x[12], S[1][3], 0x8d2a4c8a); /*32*/

    /* Round 3*/
    ROUND(H, a, b, c, d, x[ 5], S[2][0], 0xfffa3942); /*33*/
    ROUND(H, d, a, b, c, x[ 8], S[2][1], 0x8771f681); /*34*/
    ROUND(H, c, d, a, b, x[11], S[2][2], 0x6d9d6122); /*35*/
    ROUND(H, b, c, d, a, x[14], S[2][3], 0xfde5380c); /*36*/
    ROUND(H, a, b, c, d, x[ 1], S[2][0], 0xa4beea44); /*37*/
    ROUND(H, d, a, b, c, x[ 4], S[2][1], 0x4bdecfa9); /*38*/
    ROUND(H, c, d, a, b, x[ 7], S[2][2], 0xf6bb4b60); /*39*/
    ROUND(H, b, c, d, a, x[10], S[2][3], 0xbebfbc70); /*40*/
    ROUND(H, a, b, c, d, x[13], S[2][0], 0x289b7ec6); /*41*/
    ROUND(H, d, a, b, c, x[ 0], S[2][1], 0xeaa127fa); /*42*/
    ROUND(H, c, d, a, b, x[ 3], S[2][2], 0xd4ef3085); /*43*/
    ROUND(H, b, c, d, a, x[ 6], S[2][3],  0x4881d05); /*44*/
    ROUND(H, a, b, c, d, x[ 9], S[2][0], 0xd9d4d039); /*45*/
    ROUND(H, d, a, b, c, x[12], S[2][1], 0xe6db99e5); /*46*/
    ROUND(H, c, d, a, b, x[15], S[2][2], 0x1fa27cf8); /*47*/
    ROUND(H, b, c, d, a, x[ 2], S[2][3], 0xc4ac5665); /*48*/

    /* Round 4*/
    ROUND(I, a, b, c, d, x[ 0], S[3][0], 0xf4292244); /*49*/
    ROUND(I, d, a, b, c, x[ 7], S[3][1], 0x432aff97); /*50*/
    ROUND(I, c, d, a, b, x[14], S[3][2], 0xab9423a7); /*51*/
    ROUND(I, b, c, d, a, x[ 5], S[3][3], 0xfc93a039); /*52*/
    ROUND(I, a, b, c, d, x[12], S[3][0], 0x655b59c3); /*53*/
    ROUND(I, d, a, b, c, x[ 3], S[3][1], 0x8f0ccc92); /*54*/
    ROUND(I, c, d, a, b, x[10], S[3][2], 0xffeff47d); /*55*/
    ROUND(I, b, c, d, a, x[ 1], S[3][3], 0x85845dd1); /*56*/
    ROUND(I, a, b, c, d, x[ 8], S[3][0], 0x6fa87e4f); /*57*/
    ROUND(I, d, a, b, c, x[15], S[3][1], 0xfe2ce6e0); /*58*/
    ROUND(I, c, d, a, b, x[ 6], S[3][2], 0xa3014314); /*59*/
    ROUND(I, b, c, d, a, x[13], S[3][3], 0x4e0811a1); /*60*/
    ROUND(I, a, b, c, d, x[ 4], S[3][0], 0xf7537e82); /*61*/
    ROUND(I, d, a, b, c, x[11], S[3][1], 0xbd3af235); /*62*/
    ROUND(I, c, d, a, b, x[ 2], S[3][2], 0x2ad7d2bb); /*63*/
    ROUND(I, b, c, d, a, x[ 9], S[3][3], 0xeb86d391); /*64*/

    ulState[0] += a;
    ulState[1] += b;
    ulState[2] += c;
    ulState[3] += d;
}

/** @detail Decodes input (Byte) into output (ULong). Assumes length is
 * a multiple of 4.
 */
static void decode(const Byte *input, ULong *output, size_t length) 
{

    for(size_t iLong=0, iByte=0; iByte<length; iLong++, iByte+=4) 
    {	
        output[iLong] = ((ULong)input[iByte]) | (((ULong)input[iByte+1]) << 8) |
            (((ULong)input[iByte+2]) << 16) | (((ULong)input[iByte+3]) << 24);
    }
}

static void digest(char* hexDigest)
{
    if (!bFinished) 
    {
        bFinished = 1;
        final();
    }
    bytesToHexString(byteDigest, 16, hexDigest);
}


/** @detail Md5Digest finalization, ends an Md5Digest message-byteDigest operation, writing the message byteDigest and zeroizing the context.
 * This function extend the data to K*512bit or (K+1) *512 bit (length %512 == 0), and use update to process the last 512bit and generate digest.
 */
static void final(void) 
{

    Byte bits[8];
    ULong oldState[4];
    ULong oldCount[2];
    ULong index, padLen;

    /* Save current state and count. */
    memcpy(oldState, ulState, 16);
    memcpy(oldCount, ulCount, 8);

    /* Save number of bits */
    encode(ulCount, bits, 8);

    /* Pad out to 56 mod 64. */
    index = (ULong)((ulCount[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    update(Padding, padLen);

    /* Append length (before padding)*/
    update(bits, 8);

    /* Store state in digest*/
    encode(ulState, byteDigest, 16);

    /* Restore current state and count. */
    memcpy(ulState, oldState, 16);
    memcpy(ulCount, oldCount, 8);
}


/** @detail Encodes input (ULong) into output (Byte). Assumes length is
 * a multiple of 4.
 */
static void encode(const ULong *input, Byte *output, size_t length) 
{

    for(size_t iLong=0, iByte=0; iByte<length; iLong++, iByte+=4) 
    {
        output[iByte]= (Byte)(input[iLong] & 0xff);
        output[iByte+1] = (Byte)((input[iLong] >> 8) & 0xff);
        output[iByte+2] = (Byte)((input[iLong] >> 16) & 0xff);
        output[iByte+3] = (Byte)((input[iLong] >> 24) & 0xff);
    }
}

static void bytesToHexString(const Byte *input, size_t length, char* output) 
{
    for(size_t iByte = 0; iByte < length; iByte++) 
    {
        int t = input[iByte];
        int a = t / 16;
        int b = t % 16;
        sprintf(output, "%s%c%c", output, Hex[a], Hex[b]);
    }
}
