//服务端接口实现类
//package myRmiRecall;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
public class FunctionImpl extends UnicastRemoteObject implements Function{
	private String name;
	//构造函数
	public FunctionImpl(String s)throws RemoteException{
		super();
		name = s;
	}
	//接口实现函数
	public int func(int x)throws RemoteException{
		//建立客户方远程调用接口对象
		LookSever obj = null;
		if(x == 1){
			return 1;
		}
		else{
			try{
				//利用客户IP信息和远程对象名查找客户方服务对象
				//obj = (LookSever)Naming.lookup("//192.168.1.139/lxb");
				obj = (LookSever)Naming.lookup("rmi://127.0.0.1/lxb");			
			}
			catch(Exception e){
				System.out.println("FunctionImpl Error is:" + e);
			}
			System.out.println("This calls x is:" + x);
			//调用客户方接口服务函数，让客户方请求服务器方计算x-1的阶乘(递归过程)
			return x * (obj.lookandfunc("rmi://127.0.0.1/functionsc",x - 1));
			
		}
	}

}
