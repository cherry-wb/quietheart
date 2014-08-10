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

#ifndef __RSA_H__
#define __RSA_H__
#include <stdio.h>
#include <stdint.h>

/**addtogroup Type Type define*/
/**
  @{
 */
typedef unsigned char Byte;
typedef uint32_t ModuleType; /*TODO It's best that this is 1024 bit or more not uint32_t.*/

/*public/private key for encryption and decryption.*/
typedef struct KeyPair
{
    ModuleType n;
    ModuleType d;
    ModuleType e;
}KeyPair;
/**
  @}
 */

/**addtogroup Constant Constants.*/
/**
  @{
 */
/*Two Primer integer.*/
/*TODO It's best that P * Q is 1024 bit or more.*/
#define P 47
#define Q 59
/**
  @}
 */


/**@brief addtogroup publicFunction Public Functions*/
/**@{
 */
/**@brief Initialize and generate public key and private key pairs.
@param p One of two big prime number.
@param q One of two big prime number.
@return 1 if error, 0 if ok.
*/
int rsaInit(uint8_t p, uint8_t q);

/**@brief Get the encryption buffer length by the length of data to be encrypted.
@param dataLen The length of the data to be encrypted.
@return The length of the buffer needed for encrypted data.
*/
size_t rsaEncryptionLen(size_t dataLen);

/**@brief Get a pair of keys from generated key pair.
@param pair The public/private key.
*/
void rsaGetKeyPair(KeyPair* pair);

/**@brief Get a public key generated key pair.
@param pub The public key.
*/
/*TODO It's best choose specific key we want.*/
void rsaGetPublicKey(KeyPair* pub);

/**@brief Get private key from generated key pair.
@param priv The private key.
*/
/*TODO It's best choose specific key we want.*/
void rsaGetPrivateKey(KeyPair* priv);

/**@brief Encrypt the input buffer with public key.
@param pubKey Public key generated in 'rsaInit' for encryption.
@param input Data to be encrypted.
@param inputLen Length of Data to be encrypted.
@param output The encrypted data.
*/
void rsaEncrypt(KeyPair pubKey, const void* input, size_t inputLen, Byte* output);

/**@brief Decrypt the input buffer with private key.
@param privKey Private key generated in 'rsaInit' for decryption.
@param input Data to be decrypted.
@param inputLen Length of Data to be decrypted.
@param output The decrypted data.
*/
void rsaDecrypt(KeyPair privKey, const Byte* input, size_t inputLen, void* output);
/**@}
 */
#endif
