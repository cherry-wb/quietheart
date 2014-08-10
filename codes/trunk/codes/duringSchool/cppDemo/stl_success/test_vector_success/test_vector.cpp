#include<iostream.h>
#include<math.h>//rand()
#include<ctype.h>
#include<vector>
#include<algorithm>
using namespace std;
void print(int i)
{
	cout<<i<<',';
}
int main(int argc, char** argv)
{
/////////定义
	vector<int> nums;//vector<int> nums(10);
	vector<int> nums2;
	vector<int> nums3(10);

//////////
	cout<<"nums3刚开始的初始值是："<<endl;
	int i = 0;
	for(i = 0; i < nums3.size(); i++)
	{//nums3.size() = 10,空间的大小
		cout<<nums3[i]<<',';//可以这样输出
	}
	cout<<'\b'<<endl;//为什么不能退格？
//////////与整数之间的赋值
	nums3[1] = 5;//可以这样赋值
	int test = nums3[1];//可以这样赋值
	cout<<"test:"<<test<<endl;
/////////插入与删除	
	int count;
	cout<<"请输入元素数目:"<<endl;
	cin>>count;

	for(i = 0; i < count; i++)
	{
		//nums.insert(nums.begin(),i);//行，但是头部线性
		nums.insert(nums.end(),i);//在数组末尾插入元素常数
		nums2.insert(nums2.begin());//插入空元素(注意此时为0)
		//nums.push_back(i);//行
	}
	nums2.erase(nums2.begin());//删除一个元素只能从头部，而不能直接从尾部
	nums2.erase(nums2.begin());
	nums.erase(nums.end()-1);//可以end()-1来删除最后一个元素
	cout<<nums2.size()<<endl;
//////////迭代显示函数
	cout<<"nums:"<<endl;
	for_each(nums.begin(),nums.end(),print);//循环现实数组的成员??<algorithm>
	cout<<endl;
	cout<<"nums2:"<<endl;
	for_each(nums2.begin(),nums2.end(),print);//循环现实数组的成员??<algorithm>
//////////列表之间的赋值	
	nums2 = nums;
	cout<<endl<<"赋值后nums2"<<endl;
	for_each(nums.begin(),nums.end(),print);//循环现实数组的成员,依次作为print的参数
	cout<<endl;
/////////迭代器的操作
	//vector<int>::iterator it;
	vector<int>::const_iterator cit;//如果不对数据修改用此迭代器
	cit = nums.begin();
	cout<<"nums:"<<endl;
	while(cit != nums.end())
	{
		cout<<*cit<<',';//读取内容
		cit++;//增1操作
	}
/////////stl算法
	reverse(nums.begin(),nums.end());//翻转函数
	cit = nums.begin();
	cout<<"reverse nums:"<<endl;
	while(cit != nums.end())
	{
		int a = *cit;//可以赋值
		//cout<<a<<',';//读取内容
		cout<<*cit<<',';//读取内容
		cit++;//增1操作
	}
	cout<<endl;
	sort(nums2.rbegin(),nums2.rend());//降序排序
	//sort(nums2.begin(),nums2.end());//升序排序
	cit = nums2.begin();
	cout<<"r sort nums2:"<<endl;
	while(cit != nums2.end())
	{
		cout<<*cit<<',';//读取内容
		cit++;//增1操作
	}
	generate(nums3.begin(),nums3.end(),rand);//随机生成数
	cout<<"nums3:"<<endl;
	for(i = 0; i < nums3.size(); i++)
	{
		cout<<nums3[i]<<',';
	}
	cout<<endl;
	//replace_if(nums2.begin(),nums2.end(),odd,5);//如果是奇数字则题为0不行
	cit = nums2.begin();
	cout<<"replace_if nums2:"<<endl;
	while(cit != nums2.end())
	{
		cout<<*cit<<',';//读取内容
		cit++;//增1操作
	}
	//system("PAUSE");
	//如何赋值
	return 0;
}





















