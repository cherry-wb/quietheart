//客户程序代码
//package myRmiRecall;
import java.rmi.*;
public class FSCClient {
	public static void main(String args[]){
		//System.setSecurityManager(new RMISecurityManager());
		Function obj = null;
		try{
			//建立服务器调用客户方接口的接口实现类对象
			LookSeverImpl obj1 = new LookSeverImpl("client");
			//为客户方绑定远程对象名字供服务器端调用客户方时使用
			Naming.rebind("lxb", obj1);
			//按服务器地址和远程对象名查远程服务器端对象
			obj = (Function)Naming.lookup("rmi://127.0.0.1/functionsc");
			//通过远程服务器提供的接口函数计算3的阶乘
			int results = obj.func(3);
			//System.out.println("到目前也都是正确的");
			System.out.println("RMI Result:" + results);
		}
		catch(Exception ex){
			System.out.println("FSCClient RMI exception:" + ex.getLocalizedMessage());
			ex.printStackTrace();
			
		}
	}

}
