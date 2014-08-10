/*程序功能：运行的时候动态加载库，并且执行其中的函数。
1. 概念
动态加载库(dynamically loaded (DL) libraries)是指在程序运行过程中可以加载的函数库。而不是像共享库一样在程序启动的时>候加载。DL对于实现插件和模块非常有用，因为他们可以让程序在允许时等待插件的加载。在Linux中，动态库的文件格式跟共享库>没有区别，主要区别在于共享库是程序启动时加载，而动态加载库是运行的过程中加载。
有专门的一组API用于完成打开动态库，查找符号，处理出错，关闭动态库等功能。
下面对这些接口函数逐一介绍: 
(1) dlopen   
函数原型：void *dlopen(const char *libname,int flag);
功能描述：dlopen必须在dlerror，dlsym和dlclose之前调用，表示要将库装载到内存，准备使用。
如果要装载的库依赖于其它库，必须首先装载依赖库。如果dlopen操作失败，返回NULL值；如果库已经被装载过，则dlopen会返回同
样的句柄。
参数中的libname一般是库的全路径，这样dlopen会直接装载该文件；如果只是指定了库名称，在dlopen会按照下面的机制去搜寻：
a.根据环境变量LD_LIBRARY_PATH查找
b.根据/etc/ld.so.cache查找
c.查找依次在/lib和/usr/lib目录查找。
flag参数表示处理未定义函数的方式，可以使用RTLD_LAZY或RTLD_NOW。RTLD_LAZY表示暂时不去处理未定义函数，先把库装载到内存
，等用到没定义的函数再说；RTLD_NOW表示马上检查是否存在未定义的函数，若存在，则dlopen以失败告终。
(2) dlerror 
函数原型：char *dlerror(void);
功能描述：dlerror可以获得最近一次dlopen,dlsym或dlclose操作的错误信息，返回NULL表示无错误。dlerror在返回错误信息的同>时，也会清除错误信息。 
(3) dlsym 
函数原型：void *dlsym(void *handle,const char *symbol);
功能描述：在dlopen之后，库被装载到内存。dlsym可以获得指定函数(symbol)在内存中的位置(指针)。
如果找不到指定函数，则dlsym会返回NULL值。但判断函数是否存在最好的方法是使用dlerror函数，
(4) dlclose 
函数原型：int dlclose(void *);
功能描述：将已经装载的库句柄减一，如果句柄减至零，则该库会被卸载。如果存在析构函数，则在dlclose之后，析构函数会被调>用。    


执行步骤：
 * 1)只编译myfile.cpp生成myfile.o
 * 2)根据myfile.o生成动态库libmy.so
 * $g++ -shared -fPCI -o libmy.so myfile.o 
 * 这里貌似gcc也行，实际用$g++ -shared -o libmy.so myfile.o就行
 * 3)删除myfile.o和myfile.cpp
 * 4)编译连接libmy.so
 * g++ main.cpp -ldl
 * 5)运行：
 * ./a.out
 * 注意：这里使用dlsym的时候，采用的标号不是库文件源代码中的printInfo，
 * 而是通过"nm libmy.so" 或者"readelf -s libmy.so"查询得知，标号名称为：_Z9printInfov
 * 通过这样的方式，加载，可以不用包含库的头文件而使用库的函数。
 * */
#include<iostream>
#include<dlfcn.h>
using std::cout;
using std::cerr;
using std::endl;
int main(int argc, char *argv[])
{
	//初始变量
	void *handle;
	void (*pPrint)(void);
	char *error;

	cout<<"Begin to call:"<<endl;
	//动态加载库，RTLD_LAZY表示如果遇到标号不存在的情况，不做处理，而是运行时候再说。
	handle = dlopen("./libmy.so", RTLD_LAZY);
	if(handle == NULL)
	{
		cerr<<dlerror()<<endl;
		exit(1);
	}

	//找到将要调用的函数标号,采用的标号不是库文件源代码中的printInfo，
	//而是通过"nm libmy.so" 或者"readelf -s libmy.so"查询得知，标号名称为：_Z9printInfov
	pPrint = (void(*)())dlsym(handle,"_Z9printInfov");
	error = dlerror();
	if( error != NULL )
	{
		cerr<<error<<endl;
		exit(1);
	}

	//调用函数
	pPrint();

	//关闭
	dlclose(handle);
	return 0;
}
