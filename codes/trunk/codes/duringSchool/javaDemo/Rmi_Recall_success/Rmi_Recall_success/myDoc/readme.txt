使用说明：
clear.bat 删除上次编译之后的所有文件
severMake.bat 编译然后运行服务端程序
clientMake.bat 运行客户端程序。



一、功能：计算3的阶乘
1)客户方调用服务方的一个对象成员函数计算3的阶乘.
2)服务器计算过程中返回中间结果给客户，并通知客户方再次调用本服务器计算中间结果阶乘.
3)递归上述过程直至计算结束
二、步骤：
step1:编译
1)用java命令编译所有的java源文件:
javac *.java
2)用rmic命令编译所有的接口实现类:
rmic LookSeverImpl
rmic FunctionImpl

step2:运行
1)运行注册rmi:
start rmiregistry
2)运行服务器程序:
java FSCSever
3)运行客户端程序:
java FSCClient



三、注意：
注意：
如果rmic编译提示找不到类，可以：
1)javac *.java
2)rmic -classpath . HelloImpl

注意如果不是在本机器需要
1)部署：
1.1)客户方：客户端程序，客户端接口 服务端接口 客户接口实现 服务接口skeleton 客户接口skeleton
FSCClient.java Function.java LookSever.java LookSeverImpl.java FunctionImpl_stub LookSeverImpl_skeleton 
1.2)服务方：服务端程序，服务端接口 客户端接口 服务接口实现 客户接口skeleton 服务接口skeleton
FSCSever.java Function.java FunctionImpl.java LookSever.java FuctionImpl_skeleton LookSeverImpl_stub
之后编译运行如下：
2)服务器和客户端同时运行start rmigistry
3)如果运行出错可能是策略问题需要编写如下策略文件然后用-Djava选项运行如下：

3.1)建立一个client.policy文件内容如下：
grant     
  {     permission   java.net.SocketPermission     
              "*:1024-65535",   "connect,accept";   
        permission   java.net.SocketPermission     
              "host:80",   "connect";   
  };
3.2)运行时服务接口实现类加-Djava.security.policy=client.policy选项:
java -Djava.security.policy=client.policy FSCClient






四、其他参考
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