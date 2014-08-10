#include "stackNode.h"
//路径的长度限制是?
//#define L 100
class MyStack1
{//堆栈，20070314调试可用
	public:
		MyStack1(int l);
		MyStack1();
		MyStack1(MyStack1 &source);
		~MyStack1();
		//弹出栈顶元素 
		void pop();
		//压入栈顶元素 
		void push(StackNode &top);
		//获取栈顶元素 
		StackNode getTop();
		/*重载运算符*/
		MyStack1& operator=(MyStack1 &opnd2);
		//堆栈的数据指针
		StackNode *s;
		//指向堆栈的栈顶元素
		int top;
		//堆栈的长度
		int length;
		/*可能有待补充的
		没有seter,geter,
		没有getLength,setEmpty
		没有重新分配堆栈长度
		*/
};
