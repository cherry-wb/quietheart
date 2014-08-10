#include "lib/md5digest.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    //string digest usage:
    char *str = "abc";
    char strDigest[32 + 1];
    memset(strDigest, 0, sizeof(strDigest));
    Md5StringDigest(str, strDigest);
    printf("string %s 's digest is: %s\n", str, strDigest);

    //file digest usage:
    char *filename = "mytest.txt";
    char fileDigest[32 + 1];
    memset(fileDigest, 0, sizeof(fileDigest));
    Md5FileDigest(filename, fileDigest);
    printf("file %s 's digest is: %s\n", filename, fileDigest);

    //buffer digest usage:
    Byte buffer[5]={'h',    'e', 'l', 'l', 'o'};
    char bufferDigest[32 + 1];
    memset(bufferDigest, 0, sizeof(bufferDigest));
    Md5BufferDigest(buffer, sizeof(buffer), bufferDigest);
    printf("buffer 's digest is: %s\n", fileDigest);

    return EXIT_SUCCESS;
}
