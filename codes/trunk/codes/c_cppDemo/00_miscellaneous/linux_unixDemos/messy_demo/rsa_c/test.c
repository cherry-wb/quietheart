#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "lib/rsa.h"

#define BUFFER_SIZE 32
int main(int argc, char **argv)
{
    /*Generate public/private key pair.*/
    int idx;
    KeyPair pair;

    rsaInit(P, Q);/*TODO How to choose?*/
    rsaGetKeyPair(&pair);

    /*******1.buffer data for encrypt , and decrypt data.**********/
    Byte buffer[BUFFER_SIZE] = "hello, my world!";
    Byte encryptBuffer[rsaEncryptionLen(BUFFER_SIZE)];
    Byte decryptBuffer[BUFFER_SIZE];

    /*encrypt buffer data by public key.*/
    KeyPair pub;
    memset(&pub, 0, sizeof(pub));
    rsaGetPublicKey(&pub);
    rsaEncrypt(pub, buffer, sizeof(buffer), encryptBuffer);

    /*decrypt data by private key.*/
    KeyPair priv;
    memset(&priv, 0, sizeof(priv));
    rsaGetPrivateKey(&priv);
    rsaDecrypt(priv, encryptBuffer, sizeof(encryptBuffer), decryptBuffer);

    /*print result*/
    printf("input:%s\n", buffer);
    printf("encrypt:");
    for (idx = 0; idx < sizeof(encryptBuffer); ++idx)
    {
        printf("%c", encryptBuffer[idx]);
    }
    printf("\n");
    printf("output:%s\n", decryptBuffer);

    /*******2.string data for encrypt , and decrypt data.*********/
    char* mystr = "hello!";
    Byte encryptStrBuf[rsaEncryptionLen(strlen(mystr) + 1)];
    char decryptStr[strlen(mystr) + 1];
    memset(decryptStr, '\0', sizeof(decryptStr));

    /*encrypt buffer data by public key.*/
    memset(&pub, 0, sizeof(pub));
    rsaGetPublicKey(&pub);
    rsaEncrypt(pub, mystr, strlen(mystr) + 1, encryptStrBuf);

    memset(&priv, 0, sizeof(priv));
    rsaGetPrivateKey(&priv);
    rsaDecrypt(priv, encryptStrBuf, sizeof(encryptStrBuf), decryptStr);

    /*print result*/
    printf("input str:%s\n", mystr);
    printf("encrypt:");
    for (idx = 0; idx < sizeof(encryptStrBuf); ++idx)
    {
        printf("%c", encryptStrBuf[idx]);
    }
    printf("\n");
    printf("decrpyt str:%s\n", decryptStr);

    /*******3.int data for encrypt , and decrypt data.*********/
    int myInt[5] = {1,2,-3,4,11223344};
    Byte encryptIntBuf[rsaEncryptionLen(sizeof(myInt))];
    int decryptInt[sizeof(myInt) / sizeof(int)];
    memset(decryptInt, 0, sizeof(decryptInt));

    /*encrypt buffer data by public key.*/
    memset(&pub, 0, sizeof(pub));
    rsaGetPublicKey(&pub);
    rsaEncrypt(pub, myInt, sizeof(myInt), encryptIntBuf);

    memset(&priv, 0, sizeof(priv));
    rsaGetPrivateKey(&priv);
    rsaDecrypt(priv, encryptIntBuf, sizeof(encryptIntBuf), decryptInt);

    /*print result*/
    printf("input int:{");
    for(idx = 0; idx < sizeof(myInt) / sizeof(int); ++idx)
    {
        printf("%d,",myInt[idx]);
    }
    printf("\b}\n");

    printf("encrypt:");
    for (idx = 0; idx < sizeof(encryptIntBuf); ++idx)
    {
        printf("%c", encryptIntBuf[idx]);
    }
    printf("\n");

    printf("decrypt int:{");
    for(idx = 0; idx < sizeof(myInt) / sizeof(int); ++idx)
    {
        printf("%d,", decryptInt[idx]);
    }
    printf("\b}\n");

    /*******4.file for encrypt , and decrypt file.*********/
    char *inputFile = "rsa.jpg";
    char *encryptFile = "rsa.enc";
    char *decryptFile = "rsa.dec.jpg";

    memset(&pub, 0, sizeof(pub));
    rsaGetPublicKey(&pub);

    memset(&priv, 0, sizeof(priv));
    rsaGetPrivateKey(&priv);

    FILE *fp;
    FILE *encFp;
    FILE *decFp;
    size_t length;
    fp = fopen(inputFile, "r");
    encFp = fopen(encryptFile, "w");
    Byte inBuffer[1024];
    Byte encBuffer[rsaEncryptionLen(1024)];
    Byte decBuffer[1024];
    while (!feof(fp)) 
    {
        length = fread(inBuffer, sizeof(inBuffer[0]), 1024, fp);
        if (length > 0)
        {
            rsaEncrypt(pub, inBuffer, length, encBuffer);
            fwrite(encBuffer, sizeof(encBuffer[0]), sizeof(encBuffer), encFp);
        }
    }
    fclose(fp);
    fclose(encFp);

    encFp = fopen(encryptFile, "r");
    decFp = fopen(decryptFile, "w");
    bzero(encBuffer, sizeof(encBuffer));
    while (!feof(encFp)) 
    {
        length = fread(encBuffer, sizeof(encBuffer[0]), sizeof(encBuffer), encFp);
        if (length > 0)
        {
            rsaDecrypt(priv, encBuffer, sizeof(encBuffer), decBuffer);
            fwrite(decBuffer, sizeof(decBuffer[0]), sizeof(decBuffer), decFp);
        }
    }
    fclose(encFp);
    fclose(decFp);
    return 0;
}
