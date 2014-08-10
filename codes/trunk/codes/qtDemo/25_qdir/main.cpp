/*程序功能：一个使用QDir获取目录信息的程序
 * 具体功能为：
 * 1）统计指定的目录的文件/子目录数目(ok)
 * 2）列出所有文件名/子目录名(ok)
 * 3) 打印当前目录路径和名称(ok)
 * 4) 判断某个目录是否存在(ok)
 * 5) 切换目录(ok)
 * 6) 返回用户家目录(ok)
 * 7) 列出特定名称的文件(ok)
 * */

//#include <QApplication>
#include <QDir>
//#include <QString>
//#include <QStringList>
#include <iostream>
using std::cout;
using std::endl;
//int main(int argc, char *argv[])
int main(void)
{
	QDir dir;
	QString path;
	//当前目录相对路径
	path = dir.path();//"."
	//path = dir.dirName();//注意这个也是"."
	cout<<"the relative current directory path is:"<<path.toLocal8Bit().data()<<endl;

	//当前目录的绝对路径
	path = dir.absolutePath();//"<目录的绝对路径>",注意这里目录不存在也没有错误
	cout<<"the absolute current directory path is:"<<path.toLocal8Bit().data()<<endl;

	//切换到另外目录
	dir.cd("testDir/subDir1");//切换到当前目录下的目录,如果正确返回true,这里也可绝对路径
	cout<<"the absolute current directory path is:"
		<<(dir.absolutePath()).toLocal8Bit().data()<<endl;
	
	//切换到父目录
	dir.cdUp();//上一层目录
	dir.cd("..");//这样也行
	cout<<"the absolute current directory path is:"
		<<(dir.absolutePath()).toLocal8Bit().data()<<endl;
	

	QDir dir2("/home/quietheart");
	QString dirName;
	//返回一个目录的名字
	dirName = dir2.dirName();//这里目录不存在也没有关系,只是字符串的处理。
	cout<<"the directory name is:"<<dirName.toLocal8Bit().data()<<endl;

	//测试一个目录是否存在，可读等等
	if(dir2.exists())
	{//是否存在
		cout<<"dir exists"<<endl;
		if(dir2.isReadable())
		{//是否可读
			cout<<"dir is readable"<<endl;
		}
		else
		{
			cout<<"dir isn't readable"<<endl;
		}
	}
	else
	{
		cout<<"dir not exists"<<endl;
	}


	int count = 0;
	//目录中的子目录和文件的总数目
	count = dir.count();//这里包括当前目录"."和父目录"..".
	cout<<"the entry count of current dir is:"<<count<<endl;

	QString home;
	//返回当前用户的家目录路径
	home = QDir::homePath();
	cout<<"the home path of current directory is:"<<home.toLocal8Bit().data()<<endl;


	cout<<"================================"<<endl;
	QStringList entries;
	//获得目录中所有的子项的名称
	entries = dir.entryList();//子项包括"."和"..".
	for(int i = 0; i < entries.count(); ++i)
	{
		cout<<"the "<<i<<"th entry is:"<<entries[i].toLocal8Bit().data()<<endl;
	}
	

	//获得目录中所有的子项的更多信息
	cout<<"================================"<<endl;
	QFileInfoList info;//a list of QFileInfo.
	QStringList nameFilters;
	//nameFilters<<"*";//没有内容或者是'*'就是列出全部的文件
	info = dir.entryInfoList(nameFilters);
	for(int i = 0; i < info.count(); ++i)
	{
		if(info[i].isDir())
		{
			cout<<"the "<<i<<"th entry is dir;";
			cout<<"the name is:"<<(info[i].baseName()).toLocal8Bit().data()<<endl;
		}
		else if(info[i].isFile())
		{
			cout<<"the "<<i<<"th entry is file;";
			cout<<"the name is:"<<(info[i].baseName()).toLocal8Bit().data()<<endl;
		}
	}

	//返回指定的规则的文件
	cout<<"================================"<<endl;
	nameFilters<<"*.cpp"<<"*.pro";
	info = dir.entryInfoList(nameFilters);//仅返回*.cpp和*.pro文件
	for(int i = 0; i < info.count(); ++i)
	{//返回的名称中将不包含.cpp和.pro字样了
		if(info[i].isDir())
		{
			cout<<"the "<<i<<"th entry is dir;";
			cout<<"the name is:"<<(info[i].baseName()).toLocal8Bit().data()<<endl;
		}
		else if(info[i].isFile())
		{
			cout<<"the "<<i<<"th entry is file;";
			cout<<"the name is:"<<(info[i].baseName()).toLocal8Bit().data()<<endl;
		}
	}

	return 0;
}
