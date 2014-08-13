/*程序功能：编译连接自己的库(动态库，静态库)
 * 1)只编译myfile.cpp生成myfile.o
 * 生成并使用静态库：
 * 2）根据myfile.o生成库libmy.a
 * $ar r libmy.a myfile.o
 * 3)删除myfile.o和myfile.cpp
 * 4)编译连接libmy.a
 * g++ main.cpp -L./ -lmy
 * 这里改了libmy.a的名字为libmy2.a也行，相应用
 * g++ main.cpp -L./ -lmy2
 * 注意：这里面打包成了lib*.a文件，这是静态库。动态库是.so文件
 * 5)直接运行程序成功。
 *
 * 生成并使用动态库：
 * 2)根据myfile.o生成动态库libmy.so
 * $g++ -shared -fPCI -o libmy.so myfile.o 
 * 这里貌似gcc也行，实际用$g++ -shared -o libmy.so myfile.o就行
 * 3)删除myfile.o和myfile.cpp
 * 4)编译连接libmy.so
 * g++ main.cpp -L./ -lmy
 * 注意这里不要和libmy.a冲突了,如果同时存在libmy.a和libmy.so会优先选择libmy.so。
 * 5)将动态库移动到/usr/lib等标准路径：
 * $sudo cp libmy.so /usr/lib
 * 注意这里和静态库不同，还需要把库移动到特定的位置。
 * 实际三种方法：
 * a）拷贝到/usr/lib
 * b)或设置环境变量LD_LIBRARY_PATH加上你的路径
 * c) 或修改配置文件/etc/ld.so.conf加入你的路径，并刷新缓存ldconfig
 * 6)运行程序成功。
 *
 * 总结：
 * 1）生成.o文件用来生成库文件
 * 2）静态库：
 * ar r libmy.a *.o
 * 动态库：
 * g++ -shared -o libmy.so *.o
 * 3)连接
 * g++ *.c -L ./ -lmy
 * 4)运行：
 * 静态库直接运行，动态库需要把lib*.so拷贝到/usr/lib或者其他指定目录下才行。 
 * */
#include<iostream>
#include "myfile.h"
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	cout<<"begin test"<<endl;
	printInfo();
	return 0;
}
