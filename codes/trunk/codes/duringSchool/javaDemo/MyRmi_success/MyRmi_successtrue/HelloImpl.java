/*?????HelloImpl.java????,????????? 6???: */
//package examples.hello; 
import java.rmi.Naming; 
import java.rmi.RemoteException; 
import java.rmi.RMISecurityManager; 
import java.rmi.server.UnicastRemoteObject; 
public class HelloImpl extends UnicastRemoteObject implements Hello 
{ 
public HelloImpl() throws RemoteException
{ 
super(); 
} 
public String sayHello () 
{
return "Hello World!";
} 

public static void main (String args [])
{ 
// Create and install a security manager 
//if (System.getSecurityManager() == null) 
//{ 
//System.setSecurityManager(new RMISecurityManager()); 
//} 

try 
{ 
HelloImpl obj = new HelloImpl() ; 
// Bind this object instance to the name "HelloServer" 
Naming.rebind("HelloImpl", obj); 
System.out.println("HelloServer bound in registry");
} catch (Exception e) 
{ 
System.out.println("HelloImpl err: " + e.getMessage()); 
e.printStackTrace(); 
} 
} 
} 