#include<iostream.h>
#define DEBUG1 0
#define DEBUG2 1
void main()
{
#if DEBUG1 == 0
	cout<<"debug1 = 0"<<endl;
#if DEBUG2 == 0
	cout<<"debug2 = 0 and debug1 = 0"<<endl;
#else
	cout<<"debug2 = 1 and debug1 = 0"<<endl;
#endif
#else
	cout<<"debug1 = 1"<<endl;
#if DEBUG2 == 0
	cout<<"debug2 = 0 and debug1 = 1"<<endl;
#else
	cout<<"debug2 = 1 and debug1 = 1"<<endl;
#endif
#endif
}