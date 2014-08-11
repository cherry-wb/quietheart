//#include "apue.h"
//为了测试exec中的第二个参数就是可执行程序中的arg[0]并且可以随意赋值为任意字符。
#include <unistd.h>
#include <sys/wait.h>

char    *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int
main(void)
{
    pid_t   pid;

    if ((pid = fork()) < 0) {
        //err_sys("fork error");
		exit(1);
    } else if (pid == 0) {  /* specify pathname, specify environment */
        if (execle("/mnt/myOwn_all/experiment/program/anyTest/exec/echoall", "eeeechoall", "myarg1",
                "MY ARG2", (char *)0, env_init) < 0)
            //err_sys("execle error");
			exit(1);
    }

    if (waitpid(pid, NULL, 0) < 0)
        //err_sys("wait error");
		exit(1);

    if ((pid = fork()) < 0) {
//        err_sys("fork error");
		exit(1);
    } else if (pid == 0) {  /* specify filename, inherit environment */
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
 //           err_sys("execlp error");
				exit(1);
    }

    exit(0);
}
