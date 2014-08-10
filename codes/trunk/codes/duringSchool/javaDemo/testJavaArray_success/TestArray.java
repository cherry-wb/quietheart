import java.io.*;

class TEdge
{
	TEdge()
	{
		isE = 1;
	}
	int isE = 0;
}
public class TestArray
{
	public static void main(String argv[])
	{
		System.out.println("test Array:");
		//测试基本数据类型的数组
		int A[][];
		int n = 5;
		A = new int[n][n];
		int c = 0;
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				System.out.println(A[i][j]);
			}			
		}
		//基本类型数据测试成功，默认值是0
		
		//测试自定义类型的数组
		TEdge E = new TEdge();
		System.out.println(E.isE);//显示构造函数里的初始化1
		TEdge AT[][];
		AT = new TEdge[n][n];
		//这里非常重要，还要为它分配空间才能访问。如果没有这个循环那么最后一个循环有错。
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				//System.out.println(AT[i][j].isE);
				AT[i][j] = new TEdge();
			}			
		}
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				System.out.println(AT[i][j].isE);
				//AT[i][j] = new TEdge();
			}			
		}
		
		//自定义数据数组测试失败，空指针错误
	}
}
