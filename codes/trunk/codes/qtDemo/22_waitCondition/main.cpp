/*不同线程之间的串行化执行
 * QMutex是对资源互斥访问用到的，尽管有时候能够实现同步但是概念不同了。
 * QWaitCondition是确保线程之间同步的访问，和互斥是两个概念不要混淆。
 * 等待者等待同步条件，条件满足则发送这发送通知唤醒等待者。
 *
 * 尽管互斥和同步是两个概念，qt中却把两者代码进行了一些关联.
 * 即在等待之前，等待的是一个互斥锁，必须先将这个互斥锁加锁才能调用wait等待，
 * 等待的时候先解锁，然后阻塞等待有人用wake唤醒，唤醒之后再将互斥锁恢复为原来锁定的状态。
 * 具体需要参见QWaitCondition的文档。
 *
 * 这里仅实现同步，所以互斥锁不必要，但受限于Qt语法，唯一创建互斥锁的目的，是为了用同步wait
 *
 * 本程序功能是：
 * 点击窗口的时候：
 * 程序建立了t1,t2,两个线程。
 * t1启动之后，等待j的值大于等于5的时候就打印j。
 * t2启动之后，每隔1秒就把j的值增加1。
 *
 *
 * 期望的是,t1启动等待执行打印. t2执行到j=5的时候. t1执行打印,打印的j>=5.
 * 如果只有QMutex的控制，没有QWaitCondition那么将会在t1,t2执行打印的时候都打印3。
 * */
#include <QApplication>
#include "myCallback.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyCallback my;
	my.show();
	return app.exec();
}
