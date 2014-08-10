#include<iostream.h>
#include<fstream.h>

//对cin对象的测试
void testCin()
{
	//对cin>>的测试:
	cout<<"对cin>>的测试"<<endl;
	char a1,a2,a3;
	cin>>a1;
	cout<<"a1:"<<a1<<endl;//同上面cin>>
	cin>>a2;
	cout<<"a2:"<<a2<<endl;
	cin>>a3;
	cout<<"a3:"<<a3<<endl;
	//测试的结果是cin不会接受多余的回车把回车当作一个输入单元的分割结束符号,但是多余的字符会被后面的变量所接受或者丢失
	//但是cin还是回缓存回车符号的

	//cin.clear();//清空缓存，不管用？
	while(cin.get() != 10);//清空cin缓存好用
	//while(cin.get() != '\n');//清空cin缓存好用
	
	//对cin.get()的测试
	cout<<"对cin.get()的测试"<<endl;
	char b1,b2,b3;
	b1=cin.get();
	cout<<"b1:"<<b1<<endl;//同上面cin>>
	b2=cin.get();
	cout<<"b2:"<<b2<<endl;
	b3=cin.get();
	cout<<"b3:"<<b3<<endl;
	//测试的结果cin缓存的回车也会被读出来

	//总结论输入到cin的不只一个字符，但是每次get()只提取其中的一个字符
}
//实现输入的文字存放到文件当中
void inputToFile()
{//缺点是只能够用#作为输入的结束
	//对文件的合法性检查还不够严格
	cout<<"开始输入文件的内容，存放到文件中:"<<endl;
	char filename[256];//可以定义字符数组作为文件名
	cout<<"请输入文件名（包括扩展名且不得超过255字符）:"<<endl;
	cin>>filename;
	ofstream savfile(filename);
	if(savfile)
	{
		cout<<"文件已经打开,请输入文件内容："<<endl;
		char tmp;
		cin>>tmp;
		while(tmp != '#')
		{
			savfile<<tmp;//这样第一次不会多读入一个回车产生空行get就不行
			tmp = cin.get();//如果放到后面就会多一个回车,但是放到这里显示了#
		}
		savfile.close();
		cout<<"输入完毕，文件已经关闭!"<<endl;
	}
	else
	{
		cout<<"创建文件失败！"<<endl;
	}
}
void copyToFile()
{
	//拷贝之前的准备
	cout<<"准备拷贝文件..."<<endl;
	char source[256];
	char target[256];
	cout<<"请输入源文件名(包括扩展名不要超过255字符):"<<endl;
	cin>>source;
	ifstream file1(source,ios::nocreate);
	if(!file1)
	{
		cout<<"源文件不存在！"<<endl;
		return;
	}
	cout<<"请输入目标文件名(包括扩展名不要超过255字符):"<<endl;
	cin>>target;
	ofstream file2(target);
	cout<<"开始拷贝文件..."<<endl;
	//拷贝
	char tmp;
	tmp = file1.get();
	while(!file1.eof())
	{//如果不把循环前面的get写上，把循环内的get提前会使得最后多输出一个非法字符
		file2.put(tmp);
		tmp = file1.get();
	}
	file1.close();
	file2.close();
	cout<<"拷贝完毕！"<<endl;
}
void main()
{
	//testCin();
	cout<<"hello world!"<<endl;
	//inputToFile();
	copyToFile();
}