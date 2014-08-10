/*程序功能：一个一对多的哈希表结构的使用，
 * 给定的映射关系：
 * key=first,values=1 2 3 
 * key=second,values=4 5 6
 * key=third,values=7 8 9
 * 这里的应用只给了最常用的功能，包含：
 * 1，建立哈希表
 * 2. 添加key和values(或者给某一个key追加值)

 * 3,根据key取出values序列
 * * */
#include <QApplication>
#include <QMultiHash>
#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QMultiHash<QString,int> myhash;
	QString s1("first");
	QString s2("second");
	QString s3("third");

	//添加(key,values)
	myhash.insert(s1,1);
	myhash.insert(s1,2);
	myhash.insert(s1,3);

	myhash.insert(s2,4);
	myhash.insert(s2,5);
	myhash.insert(s2,6);
	myhash.insert(s3,7);
	myhash.insert(s3,8);
	myhash.insert(s3,9);

	QList<int> values1;
	//获取键s1对应的值列表
	values1 = myhash.values(s1);
	cout<<"the values of the key \"first\" is :";
	for(int i = 0; i < values1.size(); ++i)
	{//注意这里打印的次序和添加的次序相反
		cout<<values1[i]<<' ';
	}
	cout<<endl;//这句话也起到刷新输出缓存的作用

	//app.exec();
	return 0;
}
