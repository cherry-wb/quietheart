#ifndef __myEdge_h__
#define __myEdge_h__
class MyEdge
{
	public:
		// class constructor
		MyEdge();
		// class destructor
		~MyEdge();
		// 判断是否是图中的一条边
		int isE;
		//记录该边被访问的次数
        int isVisited;
		//边的权值
		int cost;
};
#endif