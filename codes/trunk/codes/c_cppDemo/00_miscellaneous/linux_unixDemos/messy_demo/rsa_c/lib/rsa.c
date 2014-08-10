/** @file
* @author quietheart
* @version 1.0

This is the header for librsa.a which is used for RSA algorithm.
Library : librsa.a
Package : rsa
Module  : rsa

Copyright (c) 2013, rsa.
All rights reserved.
*/

#include <string.h>
#include "rsa.h"

/**addtogroup Constant Constants.*/
/**
  @{
 */
#define MAX_KEY_NUM 10
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

/**addtogroup Type Type define*/
/**
  @{
 */
typedef struct KeySet
{
    ModuleType n;
    ModuleType e[MAX_KEY_NUM];
    ModuleType d[MAX_KEY_NUM];
} KeySet;
static KeySet s_keys;
/**
  @}
 */

/**@brief addtogroup privateFunction Inner Functions*/
/**@{
 */
/**@brief Whether m and p is prime against each other.*/
static uint8_t isPrime(ModuleType m, ModuleType n);

/**@brief Get a public key value by private key.*/
static ModuleType getPubPair(ModuleType priv, ModuleType eula);

/**@brief Encode ModuleType variable to hex character.*/
static void encryptToHexString(const ModuleType *input, char* output);

/**@brief Decode hex character to ModuleType variable.*/
static void hexStringToEncrypt(const char *input, ModuleType *output);

/**@brief Encrypt Byte array.*/
static void rsaEncryptByte(KeyPair pubKey, const Byte* input, size_t inputLen, Byte* output);

/**@brief Decrypt Byte array.*/
static void rsaDecryptByte(KeyPair privKey, const Byte* input, size_t inputLen, Byte* output);
/**@}
 */


/*Implementation*/
int rsaInit(uint8_t p, uint8_t q)
{
    ModuleType priv = 0;
    ModuleType pub = 0;
    uint32_t keyIdx = 0;

    s_keys.n = p * q;
    /*Get all the keys.*/
    ModuleType eula = (p - 1) * (q - 1);
    for(priv = 2; priv < eula; ++priv)
    {
        /*Private Key*/
        if(isPrime(priv, eula))
        {
            pub = getPubPair(priv, eula);
        }
        else
        {
            pub = 0;
        }

        /*Public Key*/
        if(pub > 0)
        {
            s_keys.e[keyIdx] = pub;
            s_keys.d[keyIdx] = priv;
            ++keyIdx;
        }

        if(keyIdx >= MAX_KEY_NUM)
        {
            break;
        }
    }

    if(0 == keyIdx)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*One byte encrypts to sizeof(ModuleType) << 1 bytes of hex.*/
size_t rsaEncryptionLen(size_t dataLen)
{
    return dataLen * (sizeof(ModuleType) << 1);
}

/**TODO how to choose?*/
void rsaGetKeyPair(KeyPair *pair)
{
    pair->n = s_keys.n;
    pair->d = s_keys.d[0];
    pair->e = s_keys.e[0];
}

void rsaGetPublicKey(KeyPair *pub)
{
    pub->n = s_keys.n;
    pub->e = s_keys.e[0];
}

void rsaGetPrivateKey(KeyPair *priv)
{
    priv->n = s_keys.n;
    priv->d = s_keys.d[0];
}

void rsaEncrypt(KeyPair pubKey, const void* input, size_t inputLen, Byte* output)
{
    Byte* byteInput = (Byte*)input;
    rsaEncryptByte(pubKey, byteInput, inputLen, output);
}

/*TODO It's best more bits not uint32_t.*/
static void rsaEncryptByte(KeyPair pubKey, const Byte* input, size_t inputLen, Byte* output)
{
    size_t idx=0;
    size_t hexIdx = 0;
    ModuleType modulo = pubKey.n;
    ModuleType factor=0;
    ModuleType encryptInt = 0;/*less than pubKey.n*/

    size_t encryptLen = sizeof(encryptInt)<<1;
    char encryptHexStr[encryptLen + 1];
    memset(&encryptHexStr, '\0', sizeof(encryptHexStr));

    for(idx=0; idx<inputLen; ++idx)
    {
        encryptInt = input[idx];
        for( factor=1; factor<pubKey.e; factor++ )
        {
            encryptInt = ( encryptInt * input[idx] ) % modulo;
        }
        encryptToHexString(&encryptInt, encryptHexStr);


        for(hexIdx = 0; hexIdx < encryptLen; ++hexIdx)
        {
            /*Assume a char size is 1 Byte.*/
            output[encryptLen * idx + hexIdx] = (Byte)encryptHexStr[hexIdx];
        }
    }
}

void rsaDecrypt(KeyPair privKey, const Byte* input, size_t inputLen, void* output)
{
    Byte *pByte = (Byte*)output;
    rsaDecryptByte(privKey, input, inputLen, output);
}

static void rsaDecryptByte(KeyPair privKey, const Byte* input, size_t inputLen, Byte* output)
{
    size_t idx = 0;
    size_t hexIdx = 0;
    ModuleType modulo = privKey.n;
    ModuleType factor=0;
    ModuleType encryptInt = 0;
    ModuleType decryptInt = 0;/*less than pubKey.n*/

    size_t decryptLen = sizeof(decryptInt)<<1;
    char decryptHexStr[decryptLen + 1];
    memset(&decryptHexStr, '\0', sizeof(decryptHexStr));

    for (idx = 0; idx < inputLen; idx += decryptLen)
    {
        memset(&decryptHexStr, '\0', sizeof(decryptHexStr));
        for(hexIdx = 0; hexIdx < decryptLen; ++hexIdx)
        {
            decryptHexStr[hexIdx] = (char)input[idx + hexIdx];
        }
        hexStringToEncrypt(decryptHexStr, &decryptInt);

        encryptInt = decryptInt;
        for( factor=1; factor<privKey.d; factor++ )
        {
            decryptInt = ( decryptInt * encryptInt ) % modulo;
        }
        output[idx / decryptLen] = decryptInt;
    }
}

/*TODO optimize*/
static uint8_t isPrime( ModuleType m, ModuleType n )
{
    unsigned int i=0;
    uint8_t flag = 1;

    if(m < 2 || n < 2)
        return 0;

    unsigned int tem = ( m > n ) ? n : m;
    for(i = 2; i <= tem && flag; ++i )
    {
        uint8_t mFlag = 1;
        uint8_t nFlag = 1;
        if( m % i == 0 )
            mFlag = 0;
        if( n % i == 0 )
            nFlag = 0;
        if( !mFlag && !nFlag )
            flag = 0;
    }

    return flag;
}

static ModuleType getPubPair(ModuleType priv, ModuleType eula)
{
    ModuleType retPub = 0;
    ModuleType pub = 0;
    for(pub = 2; pub < eula; ++pub)
    {
        if( (pub * priv) % eula == 1 )
        {
            retPub = pub;
            break;
        }
    }
    return retPub;
}

/*TODO It's best more bits not uint32_t.*/
static void hexStringToEncrypt(const char *input, ModuleType *output) 
{
    size_t moduloSize = sizeof(*output);
    size_t encryptLen = sizeof(output[0]) << 1;
    size_t hexBytes;

    memset(output, 0, moduloSize);
    for(hexBytes = 0; hexBytes < encryptLen; hexBytes+=2)
    {
        ModuleType byteI = 0;
        char byteStr[3] = {input[hexBytes], input[hexBytes + 1], '\0'};
        size_t shift =  ((moduloSize << 3 ) - 8 - ((hexBytes >> 1) << 3));

        sscanf(byteStr, "%x", &byteI);
        *output |= byteI << shift;
    }
}

/*TODO It's best more bits not uint32_t.*/
static void encryptToHexString(const ModuleType *input, char* output) 
{
    size_t moduloSize = sizeof(*input);
    size_t encryptLen = (moduloSize << 1);
    size_t hexBytes;

    memset(output, '\0', encryptLen + 1);
    for (hexBytes = 0; hexBytes < encryptLen; hexBytes += 2)
    {
        size_t shift =  ((moduloSize << 3 ) - 8 - ((hexBytes >> 1) << 3));
        ModuleType byte = 0;
        
        byte = (*input >> shift) & 0xff;
        sprintf(output, "%s%c%c", output, Hex[byte / 16], Hex[byte % 16]);
    }
}
