#include<stdio.h>

#include<winsock2.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	//1.确定网络协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion != 2 || HIBYTE(wsaData.wVersion) != 2) {
		print("确定网络版本协议失败:%d\n",
			GetLadtError());
			system("pause");
			return -1;
	}
	print("确定网络版本协议成功:")
}
	
