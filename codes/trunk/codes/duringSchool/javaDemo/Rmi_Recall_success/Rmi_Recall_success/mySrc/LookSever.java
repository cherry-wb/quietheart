//客户端服务接口
//package myRmiRecall;
import java.rmi.Remote;
import java.rmi.RemoteException;
public interface LookSever extends Remote{
	//传入服务端对象标识ip和服务端反馈的新值
	int lookandfunc(String s,int x)throws RemoteException;
}
