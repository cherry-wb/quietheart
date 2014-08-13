/*测试用sbrk分配内存
 * #include <unistd.h>
 * int brk(void *addr);
 * void *sbrk(intptr_t increment);
 * brk和sbrk用来改变程序数据段的结尾地址。如果地址增加了表示为这个进程分配内存了，如果地址减少了表示给这个进程释放内存了。
 * sbrk把程序的结尾地址增加increment,如果increment的值为0会返回当前程序的结尾地址。返回先前的程序结尾，如果之前已经增加过那么返回上次的新的程序结尾(不是设置完了之后的)，失败了就返回-1,同时errno被设置为ENOMEM.
 *
 * 一个可能的输出结果是：
 * current break is:153415680
 * after add break is:153415680
 * after sub break is:153415690
 * current break is:153415680
 *
 * malloc就是用这个系统调用实现的。
 * */
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	void *cur = sbrk(0);
	printf("current break is:%d\n",(int)cur);//

	void *newadd1 = sbrk(10);
	printf("after add break is:%d\n",(int)newadd1);//
	void *newsub1 = sbrk(-10);
	printf("after sub break is:%d\n",(int)newsub1);//

	cur = sbrk(0);
	printf("current break is:%d\n",(int)cur);//

	return 0;
}
