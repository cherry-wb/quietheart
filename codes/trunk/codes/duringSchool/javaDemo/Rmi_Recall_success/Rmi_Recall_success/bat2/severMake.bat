rem 编译,之后运行服务端程序
echo off
echo 1.编译所有的java文件
echo javac *.java
javac mySrc\*.java -d .
echo 2.运行rmic编译接口实现文件
echo 服务端接口实现:
echo rmic FunctionImpl
rmic FunctionImpl
echo 客户端接口实现:
echo LookSeverImpl
rmic LookSeverImpl
echo 3.运行注册rmi
echo start rmiregistry
start rmiregistry
echo 4.运行服务端程序
echo java -Djava.security.policy=policy.policy FSCSever
echo 然后运行客户端程序
java -Djava.security.policy=mySrc\policy.policy FSCSever
PAUSE