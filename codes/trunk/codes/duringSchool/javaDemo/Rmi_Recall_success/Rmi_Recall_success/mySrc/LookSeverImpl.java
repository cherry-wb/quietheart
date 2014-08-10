//客户端实现类代码
//package myRmiRecall;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
public class LookSeverImpl extends UnicastRemoteObject implements LookSever{
	private String name;
	//构造函数
	public LookSeverImpl(String s)throws RemoteException{
		super();
		name = s;
	}
	//客户方接口实现函数
	public int lookandfunc(String name,int x)throws RemoteException{
		Function obj = null;
		try{
			//获得服务器提供回调方法的远程对象
			obj = (Function)Naming.lookup(name);
		}
		catch(Exception e){
			System.out.println(name+"LookSeverImpl: Error is:" + e);
		}
		System.out.println("This time calls x is:" + x);
		//客调服接口方法
		return obj.func(x);
	}
}
