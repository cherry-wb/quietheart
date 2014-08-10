rem 运行客户端程序
echo off
echo 运行客户端程序
echo java -Djava.security.policy=policy.policy FSCClient
java -Djava.security.policy=mySrc\policy.policy FSCClient
PAUSE