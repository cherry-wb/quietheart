#ifndef _X_DATA_H_ICODIC8E0C87S9C7_
#define _X_DATA_H_ICODIC8E0C87S9C7_


#define COUNTS_PER_PAGE 9


struct XData
{//存放用户输入于处理之后的输出
	//处理前的用户输入
    QString strPinyin;
	
	//处理后的输出字符（如果重码的画就有多个选择，所以是List）
    QStringList listHanzi;

	//每页的数目
    int counts_per_page;

    int first_visible;

    XData() :
        counts_per_page(COUNTS_PER_PAGE),
        first_visible(0)
    {}


    void reset()
    {
        strPinyin = "";
        listHanzi.clear();
        first_visible = 0;
    }
};

//------------------------------------------------------
#endif //_X_DATA_H_ICODIC8E0C87S9C7_
