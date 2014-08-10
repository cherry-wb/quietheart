//服务器程序代码
//package myRmiRecall;
import java.rmi.*;
public class FSCSever {
	public static void main(String args[]){
		//System.setSecurityManager(new RMISecurityManager());//建立安全管理对象
		try{
			//建立客户方调用服务器接口的接口实现类对象
			FunctionImpl obj = new FunctionImpl("functionsc");
			//用命名服务把服务器远程对象obj和名"functionsc"绑定
			Naming.rebind("functionsc",obj);
			System.out.println("functionsc bound in registry");
		}
		catch(Exception e){
			System.out.println("FSCSever Functionsc err:" + e.getLocalizedMessage());
			e.printStackTrace();
		}
	}

}
