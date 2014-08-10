/*程序功能：这里通过对比，将static_cast和reinterpret_cast操作进行演示。
static_cast，dynamic_cast和reinterpret_cast之间的对比：
1)static_cast和dynamic_cast可以执行指针到指针的转换，或实例本身到实例本身的转换，但不能在实例和指针之间转换。static_cast只能提供编译时的类型安全，而dynamic_cast可以提供运行时类型安全。举个例子：
class a；class b:a；class c。
上面三个类a是基类，b继承a，c和a,b没有关系。假设有一个函数void function(a&a);现在有一个对象是b的实例b，一个c的实例c。function(static_cast<a&>(b)可以通过而function(static<a&>(c))不能通过编译，因为在编译的时候编译器已经知道c和a的类型不符，因此static_cast可以保证安全。
2)reinterpret_cast可以转换任意一个32bit整数，包括所有的指针和整数。可以把任何整数转成指针，也可以把任何指针转成整数，以及把指针转化为任意类型的指针，威力最为强大！但不能将非32bit的实例转成指针。总之，只要是32bit的东东，怎么转都行！对于刚刚说的例子，下面我们骗一下编译器，先把c转成类型a
b& ref_b = reinterpret_cast<b&>c;
这样，function(static_cast<a&>(ref_b))就通过了！因为从编译器的角度来看，在编译时并不能知道ref_b实际上是c！而function(dynamic_cast<a&>(ref_b))编译时也能过，但在运行时就失败了，因为dynamic_cast在运行时检查了ref_b的实际类型，这样怎么也骗不过去了。
在应用多态编程时，当我们无法确定传过来的对象的实际类型时使用dynamic_cast，如果能保证对象的实际类型，用static_cast就可以了。至于reinterpret_cast很象c语言那样的暴力转换。
这个例子中，需要注意的地方是:
*第63行中基类指针pY1被赋予子类指针pD后，pY1=pD+4而不是pD，因为pD是多继承，pD还要前移动以便也指向CBaseX.内存布局大致如下：
       +CDerived------------------+
       |   +CBase X--------+      |\
       |   |  int x        |      | 4 bytes
       |   +---------------+      |/
       |                          |
       |   +CBase Y--------+      |
       |   |  int y,*py    |      |
       |   +---------------+      |
       +--------------------------+
*第69行和70行的可以将父类指针用static_cast强制转换成子类指针，但是两个无关的类的指针之间却不能转换。
*第74行中使用reinterpret_cast将子类指针强制转换赋给父类指针后，却没有像static_cast那样将父类指针位置调整以指向正确的对象位置，这样导致虽然两者值是一样的，但是父指针所指向的内容却不是父对象了。
*第76行之后使用void将子类转换成父类再转回子类，却无法使用了。
因为任何指针可以被转换到void*，而void*可以被向后转换到任何指针（对于static_cast<> 和 reinterpret_cast<>转换都可以这样做），如果没有小心处理的话错误可能发生。一旦我们已经转换指针为void*，我们就不能轻易将其转换回原类所以使用void转换的时候一定要小心。在上面的例子中，从一个void* 返回CDerived*的唯一方法是将其转换为CBaseY*然后再转换为CDerived*。但是如果我们不能确定它是CBaseY* 还是 CDerived*，这时我们不得不用dynamic_cast<> 或typeid[2](dynamic_cast<>需要类成为多态，即包括“虚”函数，并因此而不能成为void*)。


*/
#include <iostream>
using std::cout;
using std::endl;
class CBaseX  
{  
	public:  
		int x;  
		CBaseX() { x = 10; }  
		void foo() { printf("CBaseX::foo() x=%d/n", x); }  
};  
class CBaseY  
{  
	public:  
		int y;  
		int* py;  
		CBaseY() { y = 20; py = &y; }  
		void bar() { printf("CBaseY::bar() y=%d, *py=%d/n", y, *py);}  
};  
class CDerived : public CBaseX, public CBaseY  
{  
	public:  
		int z;  
};

int main(int argc, char *argv[])
{
	float f = 12.3;  
	float* pf = &f;  

	//基本类型的转换
	cout<<"=================Basic Cast================="<<endl;
	//======static cast<>的使用:
	int n = static_cast<int>(f); //成功编译
	cout<<"n is :"<<n<<endl;//n = 12
	//int* pn = static_cast<int*>(pf);//编译错误，指向的类型是无关的,不能将指针指向无关的类型
	void* pv = static_cast<void*>(pf);//编译成功
	int* pn2 = static_cast<int*>(pv);//成功编译, 但是 *pn2是无意义的内存（rubbish）
	cout<<"pf is:"<<pf<<",pv is:"<<pv<<",pn2 is:"<<pn2<<endl;//三者值一样
	cout<<"*pf is:"<<*pf<<",*pn2 is:"<<*pn2<<endl;//pf=12.3,pn2是无用值，注意无法使用"*pv"因为编译错。

	//======reinterpret_cast<>的使用:
	//int i = reinterpret_cast<int>(f);//编译错误，类型‘float’到类型‘int’的转换无效.
	//成功编译, 但是 *pn 实际上是无意义的内存,和 *pn2一样  
	int* pi = reinterpret_cast<int*>(pf);
	cout<<"pf is:"<<pf<<",pi is:"<<pi<<endl;//值一样
	cout<<"*pf is:"<<*pf<<",*pi is:"<<*pi<<endl;//pi是无用值，和pn2一样。


	//对象类型的转换
	cout<<"=================Class Cast================="<<endl;
	CBaseX cx;
	CBaseY cy;
	CDerived cd;

	CDerived* pD = &cd;
	CBaseX *pX = &cx;
	CBaseY *pY = &cy;
	cout<<"CDerived* pD = "<<pD<<endl;  

	//======static_cast<>的使用:
	CBaseY* pY1 = pD;  //隐式static_cast转换
	//不一样是因为多继承，pD还要前移动以便也指向CBaseX.
	cout<<"CDerived* pD = "<<pD<<",CBaseY* pY1 = "<<pY1<<endl;//pY1=pD+4!!!!!!

	//CDerived* pD1 = pY1;//编译错误,类型 ‘CBaseY*’ 到类型 ‘CDerived*’ 的转换无效
	CDerived* pD1 = static_cast<CDerived*>(pY1);//成功编译
	cout<<"CDerived* pD1 = "<<pD1<<endl;//现在 pD1 = pD

	//pX = static_cast<CBaseX*>(pY);//编译错误，从类型 ‘CBaseY*’ 到类型 ‘CBaseX*’ 中的 static_cast 无效。
	pD1 = static_cast<CDerived*>(pY);//竟然可以编译通过!!!!!!
	cout<<"CDerived* pD1 = "<<pD1<<",CBaseY *pY = "<<pY<<endl;//现在 pD1 = pY-4
	//======reinterpret_cast<>的使用:  
	CBaseY* pY2 = reinterpret_cast<CBaseY*>(pD);// 成功编译, 但是 pY2 不是 CBaseY*  
	cout<<"CDerived* pD = "<<pD<<",CBaseY* pY2 = "<<pY2<<endl;//pY2=pD!!!!!!

	//======通过void的转换注意：
	CBaseY* ppY = pD;
	cout<<"CDerived* pD = "<<pD<<",CBaseY* ppY = "<<ppY<<endl;//ppY = pD + 4  

	void* ppV1 = ppY; //成功编译
	cout<<"CBaseY* ppY = "<<ppY<<",void* ppV1 = "<<ppV1<<endl;//ppV1 = ppY  

	//CDerived* ppD2 = ppV1;//编译错误,类型‘void*’ 到类型 ‘CDerived*’的转换无效
	CDerived* ppD2 = static_cast<CDerived*>(ppV1);  
	cout<<"CDerived* ppD2 = "<<ppD2<<endl;//ppD2 = ppY, 但是我们预期 ppD2 = ppY - 4 = pD
	//ppD2->bar();//系统崩溃,段错误 
	return 0;
}
