//Getservname()函数原型为：
//struct servent *getservbyname(const char *servname, const char *protoname)
//用于根据给定名字查找相应服务
// getservbyname1.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>		// 此头文件放在<winsock2.h>或<ws2tcpip.h>之后
#pragma comment(lib, "ws2_32.lib") //连接静态库

int main(int argc, char** argv)//argc:参数个数 argv:参数取值
{//声明 初始化变量
	WSADATA wsaData;		// 创建类型为WSADATA的对象，存放socket版本号等信息
	int iResult;			// 接收WSAStarup()函数的返回值

	char* serv_name;
	struct servent* remoteServ;//定义server entry结构体指针变量

 // 注册套接字
 //初始化启动winsock,声明使用WinSock2.2版本 调用WSAStartup(),并根据返回值判断错误信息
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//与操作系统确认支持的WinSock版本
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return -1;
	}

	char buff[128] = "";
	printf("请输入服务名：\n");
	while (~scanf("%s",buff))
	{
		serv_name = buff;
		printf("打印 %s 服务内容：\n", serv_name);
 //获取服务器的信息存放在servent结构体中。getservbyname函数用于根据给定名字查找相应服务
		remoteServ = getservbyname(serv_name, NULL);
 //显示出函数能够获得的信息。
		printf("	服务名: %s \n", remoteServ->s_name);//显示服务名
		printf("	端口号: %d \n", ntohs((u_short)remoteServ->s_port));//显示端口号
		//ntohs()是一个函数名作用是将一个16位数由网络字节顺序转换为主机字节顺序	
		printf("	协议名: %s \n", remoteServ->s_proto);//显示协议名
	}

 //释放Windows Sockets DLL
	iResult = WSACleanup();
	if (iResult != 0) {
		printf("WSACleanup failed: %d\n", iResult);
		return -1;
	}

	return 0;
}