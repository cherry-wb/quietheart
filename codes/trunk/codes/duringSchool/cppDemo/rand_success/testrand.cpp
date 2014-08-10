//产生0，1间的随机数

#include<iostream.h>
#include<stdlib.h>//rand和srand
#include<math.h>
#include<time.h>
void main()
{
	//rand返回的是随机整数可以用%限定范围rand()%100指的是100以内的？？
	srand(time(NULL));//和rand配合使用是不是每次都要配合呢？
	double result = fabs (sin ((double)rand()));
	cout<<"result:"<<result<<endl;

	result = (double)rand()/RAND_MAX;
	cout<<"result:"<<result<<endl;
	result = fabs (sin ((double)rand()));
	cout<<"result:"<<result<<endl;
}

