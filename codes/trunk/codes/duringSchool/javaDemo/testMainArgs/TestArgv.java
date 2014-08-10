 /*Java中main函数的参数   
 * Filename：MainArgs.java
 * Task：Java中main函数的参数
 * Java中main方法的第一个参数是args[0]
 * 如果没有参数仍然建立一个空数组（args.length等于0）
 */
public class TestArgv {

 public static void main(String args[]) { 
 System.out.println(args.length);//没有参数是0
  if (args.length != 0) 
  {//有参数，长度不是0
	  for(int i = 0; i < args.length; ++i)
	  {
		  System.out.println(args[i]);
	  }
  }
  System.out.println(args.length);//没有参数是0
  } 
}
/*
 * 结果:
 * 1.输入java TestArgv,则:args.length = 0;
 * 2.输入java TestArgv first second，则:args.length = 2、args[0] = first、args[1] = second;
 * */


