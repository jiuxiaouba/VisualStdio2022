#include <stdio.h>
#include <easyx.h>  //graphics.h
#include <mmsystem.h> //ϵͳ��ý��ͷ�ļ�
#pragma comment(lib,"winmm.lib") //windows�Ķ�ý����ļ�

int main()
{
	initgraph(800, 450);				//��������
	char letter;			//������ĸ
	int  x, y;			    //��ĸ������x �� y
	int  speed = 2;         //��ĸ�ƶ����ٶ�
	IMAGE bkimg;                   //����ͼƬ
	loadimage(&bkimg, "111.jpg");  //����ͼƬ
	IMAGE appimg0, appimg1;
	loadimage(&appimg0, "apple0.jpg");
	loadimage(&appimg1, "apple1.jpg");
	mciSendString("open �������.mp3", 0, 0, 0);
	mciSendString("play �������.mp3", 0, 0, 0);
	ExMessage m;  //����һ����Ϣ

	int score = 100;//����
	char scoreStr[10] = { 0 };
	setbkmode(0);

	while (1)
	{
		letter = rand() % 26 + 'A';  //�����26����д��ĸ
		x = rand() % 781;            //�����0-780
		for (y = 0; y < 450; y += speed) //��ĸ�½�
		{
			BeginBatchDraw();   //�����ֹ���濨��
			putimage(0, 0, &bkimg);        //���ͼƬ
			putimage(x - 20, y - 20, &appimg0, SRCPAINT);
			putimage(x - 20, y - 20, &appimg1, SRCAND);
			settextcolor(WHITE);
			outtextxy(x, y, letter);  //�����ĸ
			sprintf(scoreStr, "������%d", score);
			settextcolor(BLACK);
			outtextxy(5, 5, scoreStr);  //�������
			EndBatchDraw();//��������
			peekmessage(&m, EM_MOUSE | EM_KEY); //������Ϣ
			if (m.message == WM_LBUTTONDOWN) {} //������
			else if (m.message == WM_KEYDOWN) //����
			{
				if (m.vkcode == letter)  //��ĸ
				{
					score += 5;
					break;  //����forѭ��
				}
				else if (m.vkcode == '1')
				{
					speed = 2;
					mciSendString("close ���ݸ�Ŀ.mp3", 0, 0, 0);
					mciSendString("open �������.mp3", 0, 0, 0);
					mciSendString("play �������.mp3", 0, 0, 0);
				}
				else if (m.vkcode == '2')
				{
					speed = 5;
					mciSendString("close �������.mp3", 0, 0, 0);
					mciSendString("open ���ݸ�Ŀ.mp3", 0, 0, 0);
					mciSendString("play ���ݸ�Ŀ.mp3", 0, 0, 0);
				}
			}
			Sleep(10);
		}
	}
	//VIP:
	//4.30�ţ�
	// 1/3 

	//���ӣ�ѧʲô������VIP���е����� + PYTHON + �ֻ���Ϸ���� + �������뷴��� 
	//ѧ��ã� �Ÿ��ͷ������   8-9����
	//��ôѧ�� 
	// 1.ֱ�� + ¼�� + �κ�1��1 8����ʦ
	// 2.3-4�������� �ٿ������� �����
	// ѧ�ѣ�
		//�����۸�8280 ����  ������ 450
		//7280 ���� 1000  800  600  500  400  300  200

	//��ô�룺
	//1.ʱ������⡣ ûʱ�䣺ѧ������� ѧ��ѧ�ᣡЧ���� ��ĥ������
	//�󲿷� �ٲ���  
	// ��ʿ�ŵ�  �ڶ���֮  ��ʿ�ŵ�  ��������  ��ʿ�ŵ� ��Ц֮

	//ûʱ�䡣
	//ûǮ��
	//�����ᡣ
	//�����
	//Ӣ�ﲻ�á�
	//��ѧ���á�
	//���費ͬ�⡣
	//��֧�֡�


	//initgraph(800, 450);				//��������
	//cleardevice();						//ˢ��
	//mciSendString("open �������.mp3", 0, 0, 0);

	///*mciSendString("pause �������.mp3", 0, 0, 0);
	//mciSendString("close �������.mp3", 0, 0, 0);*/
	//settextcolor(RGB(255, 149, 240));    //set text color
	//settextstyle(72, 0, "���Ĳ���");      //set text style  �ֺ�(��72 ��-0����Ӧ)
	//outtextxy(20, 100, "������TMD˧");    //out text xy

	////7.ͼƬ
	////��ͨ��ͼ
	//IMAGE bkimg;                   //����ͼƬ
	//loadimage(&bkimg, "111.jpg");  //����ͼƬ
	//putimage(0, 0, &bkimg);        //���ͼƬ

	////͸����ͼ.
	////1.׼��2��ͼƬ �ڵװ���ͼ  �׵ײ���ͼ    (����ͼ ����ͼ)
	////2.��2��ͼƬ���Ƶ�ͬһ������
	////3.�ֱ����ö����Ʋ��� |-SRCPAINT  &-SRCAND
	//IMAGE appimg0, appimg1;
	//loadimage(&appimg0, "apple0.jpg");
	//loadimage(&appimg1, "apple1.jpg");
	//putimage(329, 184, &appimg0, SRCPAINT);
	//putimage(329, 184, &appimg1, SRCAND);

	////8.��Ϣ������ ��꣩
	//ExMessage m;  //����һ����Ϣ
	//while (1)
	//{
	//	peekmessage(&m, EM_MOUSE | EM_KEY); //������Ϣ
	//	if (m.message == WM_LBUTTONDOWN) //������
	//	{
	//		mciSendString("play �������.mp3", 0, 0, 0);
	//	}
	//	else if (m.message == WM_KEYDOWN) //����
	//	{
	//		if (m.vkcode == 'F')
	//		{
	//			mciSendString("pause �������.mp3", 0, 0, 0);
	//		}
	//	}
	//}
	return 0;
}