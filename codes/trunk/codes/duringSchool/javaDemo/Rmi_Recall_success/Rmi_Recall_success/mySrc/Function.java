//服务端计算阶乘的接口
//package myRmiRecall;
import java.rmi.*;
public interface Function extends Remote{
	//计算阶乘的接口函数
	int func(int x)throws RemoteException;
}
