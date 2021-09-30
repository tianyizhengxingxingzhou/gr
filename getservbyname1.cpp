//Getservname()����ԭ��Ϊ��
//struct servent *getservbyname(const char *servname, const char *protoname)
//���ڸ��ݸ������ֲ�����Ӧ����
// getservbyname1.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>		// ��ͷ�ļ�����<winsock2.h>��<ws2tcpip.h>֮��
#pragma comment(lib, "ws2_32.lib") //���Ӿ�̬��

int main(int argc, char** argv)//argc:�������� argv:����ȡֵ
{//���� ��ʼ������
	WSADATA wsaData;		// ��������ΪWSADATA�Ķ��󣬴��socket�汾�ŵ���Ϣ
	int iResult;			// ����WSAStarup()�����ķ���ֵ

	char* serv_name;
	struct servent* remoteServ;//����server entry�ṹ��ָ�����

 // ע���׽���
 //��ʼ������winsock,����ʹ��WinSock2.2�汾 ����WSAStartup(),�����ݷ���ֵ�жϴ�����Ϣ
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//�����ϵͳȷ��֧�ֵ�WinSock�汾
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return -1;
	}

	char buff[128] = "";
	printf("�������������\n");
	while (~scanf("%s",buff))
	{
		serv_name = buff;
		printf("��ӡ %s �������ݣ�\n", serv_name);
 //��ȡ����������Ϣ�����servent�ṹ���С�getservbyname�������ڸ��ݸ������ֲ�����Ӧ����
		remoteServ = getservbyname(serv_name, NULL);
 //��ʾ�������ܹ���õ���Ϣ��
		printf("	������: %s \n", remoteServ->s_name);//��ʾ������
		printf("	�˿ں�: %d \n", ntohs((u_short)remoteServ->s_port));//��ʾ�˿ں�
		//ntohs()��һ�������������ǽ�һ��16λ���������ֽ�˳��ת��Ϊ�����ֽ�˳��	
		printf("	Э����: %s \n", remoteServ->s_proto);//��ʾЭ����
	}

 //�ͷ�Windows Sockets DLL
	iResult = WSACleanup();
	if (iResult != 0) {
		printf("WSACleanup failed: %d\n", iResult);
		return -1;
	}

	return 0;
}