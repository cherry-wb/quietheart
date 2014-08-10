#include<iostream.h>
#include<fstream.h>
void test()
{
	char filename[256];
	cout<<"请输入文件名(包含扩展名的txt文件):"<<endl;
	cin>>filename;
	ifstream infile(filename,ios::nocreate);
	/*while(!infile)
	{
		cout<<"文件不存在！请重新输入！"<<endl;
		infile.close();//???此处不能循环处理
		cin>>filename;
		infile.open(filename,ios::nocreate);
	}*/
	//上面的代码不能实现，第一次错误了，就进入死循环了。下面的可以。 
	//infile.open(filename,ios::nocreate);
    while(!infile.is_open())
	//while(!infile)//不行
    {
        cout<<"文件不存在，请重新输入"<<endl;  
        infile.close();//进入死循环？                                  
        cin>>filename;  
        infile.open(filename,ios::nocreate); 
	}
}
void main()
{
	cout<<"hello world!"<<endl;
	test();
}