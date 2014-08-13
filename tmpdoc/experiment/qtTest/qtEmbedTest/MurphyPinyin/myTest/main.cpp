/*程序功能：
 * 测试引擎的功能，给出一个字符串，然后查找匹配的结果
 * 打印匹配的数目，然后输出结果到文件out.txt中。
 * */
using namespace std;

#include <qstring.h>
#include <qfile.h>
#include <q3textstream.h>
#include "PinyinEngine.h"


int main()
{
	char table_file[] = "./pinyin_table.txt";
	const char index_file[]="murphytalk_phrase_idx.txt";
	PinyinEngine ime(table_file,index_file);
	//获得匹配的数目
	unsigned int n = ime.search((const char*)"pi");
	cout<<n<<" matched"<<endl;
	
	QFile file("out.txt");
	if ( file.open( QIODevice::WriteOnly ) ) {
		Q3TextStream stream(&file);
		stream.setEncoding(Q3TextStream::UnicodeUTF8);

		QChar c;
		//依次获得匹配的字符串
		for(unsigned int i=0;i<n;i++){
			c=ime.get_char(i);
			stream<<c;
			
		}

		file.close();
	}

}
