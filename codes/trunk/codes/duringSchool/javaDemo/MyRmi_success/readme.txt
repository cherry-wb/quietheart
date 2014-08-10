功能：客户方可以实现调用服务方的一个对象成员函数。
运行步骤：
增加策略文件，假如保存为跟目录下client.policy   
  文件内容：   
  grant     
  {     permission   java.net.SocketPermission     
              "*:1024-65535",   "connect,accept";   
        permission   java.net.SocketPermission     
              "host:80",   "connect";   
  };
0/rmic 服务方接口实现类,javac 客户程序.java
1/start rmiregistry
2/运行服务方接口实现类(java -Djava.....  服务实现类)
  ****运行时加上参数：   
  -Djava.security.policy=client.policy
3/运行客户方程序 (java 客户程序)

注意：
如果编译提示找不到类，可以：
1)javac *.java
2)rmic -classpath . HelloImpl
这样一般可以了。