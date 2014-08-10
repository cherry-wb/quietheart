
//测试数组，特别是二维（多维）数组空间的分配
public class TestAllocate {
	public static void main(String args[])
	{
//		a2[][]={{1,2},{3,4,5}} 
		/*int a2[][];
		a2[][] = new int [2][]; //2行 这样报错*/
		int a2[][] = new int [2][]; //2行
		a2[0]=new int [2]; //第1行 2元素 
		a2[1]=new int [3];//第1行 3元素
		System.out.println("行数："+ a2.length);
		int value = 1;
		for(int i = 0; i < a2.length; ++i)
		{
			for(int j = 0; j < a2[i].length; ++j)
			{
				a2[i][j] = value++;
			}
		}
		
		System.out.println("元素内容如下：\n{");
		for(int i = 0; i < a2.length; ++i)
		{
			System.out.print("{");
			for(int j = 0; j < a2[i].length - 1; ++j)
			{
				System.out.print(a2[i][j]+",");			
			}
			System.out.println(a2[i][a2[i].length-1]+"}");
		}
		System.out.println("}");/**/
	}
}
