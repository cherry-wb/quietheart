rem 编译,之后运行服务端程序
echo off
echo 1.编译所有的java文件
echo javac *.java
PAUSE
javac mySrc\*.java -d .
echo 2.运行rmic编译接口实现文件
echo 2.1服务端接口实现:
echo rmic FunctionImpl
PAUSE
rmic FunctionImpl
echo 2.2客户端接口实现:
echo LookSeverImpl
PAUSE
rmic LookSeverImpl
echo 3.运行注册rmi
echo start rmiregistry
PAUSE
start rmiregistry
echo 4.运行服务端程序
echo java -Djava.security.policy=policy.policy FSCSever
PAUSE
echo 服务器方准备结束，结果如下。之后运行客户端程序
java -Djava.security.policy=mySrc\policy.policy FSCSever
PAUSE