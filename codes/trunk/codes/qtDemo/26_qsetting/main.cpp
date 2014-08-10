/*功能：使用QSetting来保存程序的配置数据到磁盘中去。
 * 本程序包含的功能包括：
 * 1)设置一个key的键值（包含类型：）(ok)
 * 2)获取一个key的键值(ok)
 * 3)检查一个key是否存在(ok)
 * 4)列出所有的key(ok)
 * 5)插入一个key(ok)
 * 6)返回当前所在组(ok)
 * 7)查看当前配置文件的位置(ok)
 *
 * 8)删除一个key(用remove(keyname),未实践)
 * 9)删除所有的key(?)
 * 10)设置配置文件的位置?
 *
 * 注意：
 *  QStringList preStartApp;
 *  preStartApp<<"ereader"<<"qstardict";
 *  launchCfg.setValue("AppLoading/PreloadApps",preStartApp);//lvkaiadd
 *  设置之后PreloadApps=ereader, qstardict
 *  但是如果
 *  QString preStartApp="ereader,qstardict";
 *  launchCfg.setValue("AppLoading/PreloadApps",preStartApp);//lvkaiadd
 *  设置之后PreloadApps="ereader, qstardict"//多了一个冒号
 *
 *
 * */

#include <QSettings>
#include <QColor>
//用于打印qDebug()<<...;
#include <QDebug>
int main(int argc, char *argv[])
{
	QSettings cfg("MySoft", "MyApp");//两个参数分别是公司名字和程序名字
	
	//////关于配置路径
	//打印配置文件所在的路径
	//默认路径$HOME/.config/MySoft/MyApp.conf
	qDebug()<<"the default setting file is stored in:"<<cfg.fileName();
	qDebug()<<"=============";
	//设置配置文件所在的路径(不管用？),但可通过设XDG_CONFIG_HOME环境变量改变默认路径
	//cfg.setPath(QSettings::NativeFormat,QSettings::UserScope,"test");
	//qDebug()<<"after set, the setting file is stored in:"<<cfg.fileName();
	//qDebug()<<"=============";

	int size = 2;
	bool test = true;
	QColor color = QColor(255,0,0);
	QString appName("myapp");

	//////设置/插入,键值
	//没有指定层次那么就是默认的General组,例如name
	qDebug()<<"begin to set values";
	qDebug()<<"=============";
	qDebug()<<"setting the key 'name'";
	qDebug()<<"setting the key 'Main/size'";
	qDebug()<<"setting the key 'Special/isTest'";
	qDebug()<<"setting the key 'Special/color'";
	cfg.setValue("name", appName);//设置键值name为"myapp",这里没使用常量而使用变量appName
	cfg.setValue("Main/size",size);//设置层次的键值组Main下的 size键

	//////设置多个同一组的值
	//如果操作同一组的键值那么下面的方法可以自动加上组前缀，这样方便，组是可以嵌套的
	cfg.beginGroup("Special");//确定添加的前缀
	qDebug()<<"the current group (or prefix) is:"<<cfg.group();

	cfg.setValue("isTest", test);//这样会设置"Special/isTest"的值
	cfg.setValue("color", color);//这样会设置"Special/color"的值

	cfg.endGroup();//结束添加的最新前缀
	qDebug()<<"end the current group";

	//////列出所有键
	QStringList allKeys = cfg.allKeys();
	qDebug()<<"begin to print all the keys:";
	qDebug()<<"=============";
	for(int i = 0; i < allKeys.count(); ++i)
	{
		qDebug()<<allKeys[i];
	}
	////////获取键的值
	int getSize;
	int none1;//一个不存在的键值
	int none2;//一个不存在的键值
	QColor getColor;
	QString getName;

	getSize = cfg.value("Main/size").toInt();//获取一个整数值
	none1 = cfg.value("nothing").toInt();//获取一个不存在的值
	none2 = cfg.value("novalue",5).toInt();//对不存在的键值设置该键不存在时候的默认值
	getName = cfg.value("name").value<QString>();
	getColor = cfg.value("Special/color").value<QColor>();//特殊类型QColor值的获取

	qDebug()<<"print get key values";
	qDebug()<<"=============";
	qDebug()<<"'Main/size' of the config is:"<<getSize;
	qDebug()<<"'nothing' of the config is(this isn't exists):";
	qDebug()<<"'novalue' of the config(isn't exists,but with a default value):"<<none2;
	qDebug()<<"'name' of the config:"<<getName;
	qDebug()<<"'Special/color' of the config:"<<color;

	//////其他操作
	if(cfg.contains("Main/size"))
	{//判断键是否存在
		qDebug()<<"have the key 'Main/size'";
	}
	if(!cfg.contains("nothing"))
	{
		qDebug()<<"don't have the key 'nothing'";
	}

	cfg.sync();//确保文件被写到磁盘上面

	return 0;
}
