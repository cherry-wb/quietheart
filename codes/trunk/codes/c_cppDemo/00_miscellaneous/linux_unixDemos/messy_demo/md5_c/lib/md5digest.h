/** @file
* @author quietheart
* @version 1.0

This is the header for libmd5digest.a which is used for generate the digest for file or string.
Library : libmd5digest.a
Package : md5digest
Module  : md5digest

Copyright (c) 2013, md5.
All rights reserved.
*/
#ifndef MD5_H
#define MD5_H

#include <stdio.h>
#define DIGEST_LEN 128
/**If We use md5 algorithm define 'MD5' to 1.*/
#define MD5 0

/**Type define.*/
typedef unsigned char Byte;
typedef unsigned long ULong;

/**@addtogroup PublicFunction Public functions.*/
/**@{*/

/**@brief Function for get a string's digest.
@param str The string we want to get the digest for.
@param hexDigest The hex string of str's digest.
@return 0 for success or 1 for fail.
*/
size_t Md5StringDigest(const char* str, char* hexDigest);

/**@brief Function for get a file's digest.
@param filename The file we want to get the digest for.
@param hexDigest The hex string of file's digest.
@return 0 for success or 1 for fail.
*/
size_t Md5FileDigest(const char* filename, char* hexDigest);

/**@brief Function for get a buffer's digest.
@param buf The buffer contains the data we want to get the digest.
@param bufLen the length of the buffer.
@param hexDigest The hex string of file's digest.
@return 0 for success or 1 for fail.
*/
size_t Md5BufferDigest(const Byte* buf, size_t bufLen, char* hexDigest);
/**@}*/
#endif/*Md5Digest_H*/
