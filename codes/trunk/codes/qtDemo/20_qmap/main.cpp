/*程序功能：
 * 对QMap的测试。
 * QMap是一种模板类映射集合，提供了许多key,value对之间的映射。
 * 这里演示的功能包括：
 * 1)插入一个key,value对（三种方法，使用[](ok),使用insert(ok),使用insertMulti(ok)）
 * 2)查找一个key(ok)
 * 3)获取指定key相应的value.(ok)
 * 4)判断一个key是否在集合中。(ok)
 * 5)使用iterator对map进行遍历.(ok)
 * 6)显示QMap的value item总数以及指定key的value item 数目(ok)
 * 7)删除某个元素(ok)或者清除整个QMap(ok).
 * */
#include <QMap>
#include <QDebug>
int main(int argc, char *argv[])
{
	QMap<QString,int> map;

	//一对一映射的插入,两种方法.
	//如果已经存在这个key会将原来key对应的value给替换。
	map["one"] = 1;
	map["two"] = 3;
	map["two"] = 2;
	map.insert("three",3);


	//获取指定key的value,两种方法.
	//建议使用value方法,因为[]有时候会隐式的插入，例如：
	//if (map[i] == okButton){cout << "Found button at index " << i << endl;}
	qDebug()<<"map[\"one\"] is:"<<map["one"];
	qDebug()<<"map[\"two\"] is:"<<map["two"];
	int v = map.value("three");
	qDebug()<<"map[\"three\"] is:"<<v;

	//一对多的映射插入
	//也可以用QMultiMap
	map["four"] = 4;
	map.insertMulti("four",44);
	map.insertMulti("four",444);
	
	//获取一对多映射的值
	qDebug()<<"map[\"four\"] is:"<<map["four"];//显示最后一个值444
	QList<int> values = map.values("four");
	qDebug()<<"map[\"four\"] are:"<<values;//显示(444,44,4)

	//判断一个key是否属于map:
	if(map.contains("three"))
	{
		qDebug()<<"map contains the key:"<<"\"three\"";
	}
	if(!map.contains("not"))
	{
		qDebug()<<"map not contain the key:"<<"\"not\"";
	}

	//查找
	qDebug()<<"begin to find";
	QMap<QString, int>::iterator i = map.find("four");
	while (i != map.end() && i.key() == "four") 
	{
		int v = i.value();
		qDebug()<<v;
		++i;
	}//444,44,4
	i = map.find("three");
	while (i != map.end() && i.key() == "three") 
	{//if key()=="four",have nothing
		int v = i.value();
		qDebug()<<v;
		++i;
	}//3
	
	//遍历
	QMapIterator<QString, int> it(map);
	while (it.hasNext())
	{
		it.next();
		qDebug()<<"key:value is:"<<it.key()<< ": " <<it.value();
	}
	
	//显示QMap的item总数以及指定key的value item 数目
	qDebug()<<"total count of qmap is:"<<map.count();//6
	qDebug()<<"count of value of key \"four\" is:"<<map.count("four");//3

	//删除一个key,value,注意如果是多value的key,那么只删除其中的一个。
	QMap<QString, int>::iterator i2 = map.find("four");
	map.erase(i2);
	i2 = map.find("four");
	while (i2 != map.end() && i2.key() == "four") 
	{
		int v = i2.value();
		qDebug()<<v;
		++i2;
	}//44,4

	qDebug()<<"total count of qmap is:"<<map.count();//5
	qDebug()<<"count of value of key \"four\" is:"<<map.count("four");//2

	//清除所有元素
	map.clear();
	qDebug()<<"total count of qmap is:"<<map.count();//0
	qDebug()<<"count of value of key \"four\" is:"<<map.count("four");//0

	return 0;
}
