#include<stdio.h>

#include<winsock2.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	//1.ȷ������Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion != 2 || HIBYTE(wsaData.wVersion) != 2) {
		print("ȷ������汾Э��ʧ��:%d\n",
			GetLadtError());
			system("pause");
			return -1;
	}
	print("ȷ������汾Э��ɹ�:")
}
	
