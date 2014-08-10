#ifndef __myEdge_h__
#define __myEdge_h__
class MyEdge
{
	public:
		// class constructor
		MyEdge();
		// class destructor
		~MyEdge();
		// 根据时间获取该边的代价的函数
		int getCost(int i,int j,int t);
		int getCost2(int i,int j,int t);//第二种权值函数
		// 判断是否是图中的一条边
		int isE;
		//记录该边被访问的次数
        int isVisited; 
};
#endif