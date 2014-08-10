//package examples.hello; 
//import java.applet.Applet; 
//import java.awt.Graphics; 
import java.rmi.Naming; 
import java.rmi.RemoteException; 

public class HelloClient
{
	public static void main(String []args)
{ 
String message = "blank"; 
Hello obj = null ; 
try{
obj = (Hello)Naming.lookup("//192.168.1.139/HelloImpl");
message = obj.sayHello();
System.out.println(message);
}catch(Exception e){System.out.println("rmi exception:"+e.getMessage());
e.printStackTrace();}
 
} 
} 


