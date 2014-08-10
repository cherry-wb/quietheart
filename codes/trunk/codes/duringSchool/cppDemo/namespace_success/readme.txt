C++命名空间
C++中采用的是单一的全局变量命名空间。在这单一的空间中，如果有两个变量或函数的名字完全相同，就会出现冲突。当然，你也可以使用不同的名字，但有时我们并不知道另一个变量也使用完全相同的名字；有时为了程序的方便，必需使用同一名字。比如你定义了一个变量string user_name, 有可能在你调用的某个库文件或另外的程序代码中也定义了相同名字的变量，这就会出现冲突。命名空间就是为解决C++中的变量、函数的命名冲突而服务的。解决的办法就是将你的string user_name变量定义在一个不同名字的命名空间中。

#include <iostream>
#include <string>
using namespace std;

//两个在不同命名空间中定义的名字相同的变量
namespace myown1{
 string user_name = "myown1";
}


namespace myown2{
 string user_name = "myown2";
}

int main()
{
cout<< "\n"
 << "Hello, " 
 << myown1::user_name //用命名空间限制符myown1访问变量user_name
 << "... and goodbye!\n";

cout<< "\n"
 << "Hello, " 
 << myown2::user_name //用命名空间限制符myown2访问变量user_name
 << "... and goodbye!\n";

return 0;
}
也可以这样：

int main()
{
using namespace myown1;
cout<< "\n"
 << "Hello, " 
 << user_name 
 << "... and goodbye!\n";

// using namespace myown2;
cout<< "\n"
 << "Hello, " 
 << myown2::user_name //用命名空间限制符myown2访问变量user_name
 << "... and goodbye!\n";

return 0;
}
但第二个变量必需用命名空间限制符来访问，因为此时myown1空间中的变量已经可见，如果不加限制，编译器就会无法识别是那一个命名空间中的变量。
