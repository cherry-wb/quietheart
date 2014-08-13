#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FIFOMODE (O_CREAT | O_RDWR | O_NONBLOCK)
#define OPENMODE (O_RDONLY | O_NONBLOCK)
#define FIFO_SERVER "myfifo"
