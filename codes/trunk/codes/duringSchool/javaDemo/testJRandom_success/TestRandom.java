//测试生成随机数的方法
import java.util.*;
public class TestRandom
{
	public static void main(String argv[])
	{
		System.out.println("测试生成随机数的函数：");
		double a = Math.random();
		System.out.println("Math.random()生成的0，1之间的随机数（不包括1）:"+a);
		int ia = new Random().nextInt(100);
		System.out.println("new Random().nextInt()生成的0,100(不包括100)间的随机整数:"+ia);
	}
}