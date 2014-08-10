/*程序功能：
 * 这个程序定义了一个特殊的列表，
 * 1)列表的顶部是标题栏，
 * 2)列表的最右侧（标题栏的下面）是一个特殊的“翻页条”
 * 这个翻页条最上方是上一页（翻页条上的页），
 * 最下方是下一页（翻页条上的页），
 * 中间9个按钮分别对应主题区域相应的页数。
 * 选择相应的页数会给列表的主体区域发送翻页的消息。
 * 3)列表的主体区域是一个可以添加可点击标签项的itemContainer。
 *
 * */
#include <QApplication>
#include "esearchresult.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	ESearch searchResult;
	searchResult.show();
	app.exec();
	return 0;
}
