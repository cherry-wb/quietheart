/*获取加密的passwd中的密码。
root返回加密之后的密码。
其他用户返回NULL的ptr.
*/
#include <stdio.h>
#include <shadow.h>
int main(void)
{
	struct spwd *ptr;

	if ((ptr = getspnam("quietheart")) == NULL)
	{
		printf("passwd name is NULL!\n");
		return 1;
	}
	printf("sp_pwdp = %s\n", ptr->sp_pwdp == NULL ||
			ptr->sp_pwdp[0] == 0 ?  "(null)" : ptr->sp_pwdp);
	return 0;
}
