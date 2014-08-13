/*程序功能：使用gettext实现多语言支持的程序。
 * 该程序的适应多语言的相关文件存放在本程序的路径中而不是标准路径中了。
 *
 * 操作过程：
 * 1.编写源代码,源代码文件为：myhello.c
 *
 * 2.提取要翻译的字符生成模板：
 * xgettext -d hello -s -o myhello.pot myhello.c
 * 这样生成一个myhello.pot文件。
 *
 * 3.根据模板生成待翻译成目标语言的相应文件：
 * msginit -l zh_CN.UTF-8 -o mycn.po -i myhello.pot
 * 这里实际可以直接把模板myhello.pot拷贝一份mycn.po进行翻译，不过最好用这个工具来生成mycn.po。因为这样信息完整。
 * 注意：
 * 这里如果只用：msginit -l zh_CN -o mycn.po -i myhello.pot
 * 这样进行第5步的时候会出现错误说多字节次序有问题。后来发现需要将
 * "Content-Type: text/plain; charset=ASCII\n"
 * 改成"Content-Type: text/plain; charset=UTF-8\n"
 *
 * 4.翻译
 * 将上面生成的mycn.po文件中相应的字符串Hello, world!的翻译版本放填到相应位置(msgstr)。如下：
 * msgid "Hello, world!\n"
 * msgstr "你好，世界！\n"
 *
 * 5.将翻译好的文件编译成二进制文件让gettext可以加载：
 * msgfmt -c -v -o hello.mo mycn.po
 * -c选项进行具体PO文件格式得检查，-v给出一些程序得更多信息，输出文件通过-o选项指出。需要注意得是，文件得基本部分需要和消息域相匹配.
 *
 * 6.将生成的二进制拷贝到合适的位置：
 * mkdir -p ./po/zh_CN/LC_MESSAGES
 * cp hello.mo ./po/zh_CN/LC_MESSAGES
 *
 * 7.编译程序：
 * $gcc myhello.c -o myhello
 *
 * 8.使用程序的英文版本：
 *   $echo $LANG
 *   $export LANG=En_US
 *   $./myhello
 *   这样输出：
 *   hello world!
 * 9.使用程序的中文版本：
 *   $echo $LANG
 *   $export LANG=zh_CN.UTF-8
 *   $./myhello
 *   这样输出：
 *   你好！世界！
 * */
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	setlocale(LC_ALL, "");
	bindtextdomain("hello","./po");
	textdomain("hello");
	printf(gettext("hello world!\n"));
	return 0;
}
