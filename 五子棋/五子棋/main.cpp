#include<stdio.h>
#include<easyx.h>//ͼ�ο�ͷ�ļ�
#include<mmsystem.h>//��������ͷ�ļ�
#pragma comment(lib,"winmm.lib")//�������ֿ��ļ�
/*
* ���ɿ���������vs2019 + easyx�� ��װ
*/

#define GRID_W 25			//ÿ������֮��ļ��
#define SPACE (3*GRID_W)	//�������ߵļ��
#define ROW 15
#define COL 15

bool judge(int r, int c);

enum Chess
{
	None,
	Black,
	White
};
//�����ͼ���飬�����洢���� 0 û������ 1 ���� 2 ����
int map[ROW][COL];

struct Pos
{
	int row;
	int col;
	bool isShow;	//�Ƿ���ʾ��ɫ��
	int player;		//����
}pos = { -1,-1,false,Black };

//����ͼƬ
IMAGE bk;
void loadResource()
{
	//����ͼƬ int a; a = 20;	//2 ��������û��һ������ת�����в�������
	loadimage(&bk, "Res/bk.jpg");
	//��������
	mciSendString("play Res/G��֮��.mp3 repeat", 0, 0, 0);
}

void draw()
{
	//���ͼƬ
	putimage(0, 0, &bk);

	//������ 15*15
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	for (int i = 0; i < 15; i++)
	{
		line(SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE, i * GRID_W + SPACE);		//����
		line(i * GRID_W + SPACE, SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE);		//����
	}
	//���߿�(��һ��)
	setlinestyle(PS_SOLID, 2);
	rectangle(SPACE, SPACE, SPACE + 14 * GRID_W, SPACE + 14 * GRID_W);

	//���������ɫ
	setfillcolor(BLACK);
	//���м��
	solidcircle(SPACE + 7 * GRID_W, SPACE + 7 * GRID_W, 5);
	//����
	solidcircle(SPACE + (7 - 4) * GRID_W, SPACE + (7 - 4) * GRID_W, 5);
	//����
	solidcircle(SPACE + (7 - 4) * GRID_W, SPACE + (7 + 4) * GRID_W, 5);
	//����
	solidcircle(SPACE + (7 + 4) * GRID_W, SPACE + (7 - 4) * GRID_W, 5);
	//����
	solidcircle(SPACE + (7 + 4) * GRID_W, SPACE + (7 + 4) * GRID_W, 5);

	//�������ӣ�����������������ݻ�������
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			if (map[i][k] == Black)	//����
			{
				setfillcolor(BLACK);
				solidcircle(k * GRID_W + SPACE, i * GRID_W + SPACE, 10);
			}
			else if (map[i][k] == White)	//����
			{
				setfillcolor(WHITE);
				solidcircle(k * GRID_W + SPACE, i * GRID_W + SPACE, 10);
			}
		}
	}

	//������ɫ�Ŀ�
	setlinecolor(BLUE);
	//����������±�
	if (pos.isShow)
		rectangle(pos.col * GRID_W + SPACE - 12, pos.row * GRID_W + SPACE - 12, pos.col * GRID_W + SPACE + 12, pos.row * GRID_W + SPACE + 12);
}

//����ƶ�
void mouseMoveMsg(ExMessage* msg)
{
	printf("mouseMoveMsg\n");

	pos.isShow = false;
	//����У׼
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//���ÿ���������Ͻǵ�����
			int gridx = k * GRID_W + SPACE;
			int gridy = i * GRID_W + SPACE;
			//msg->x msg->y
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
			{
				pos.isShow = true;
				pos.row = i;
				pos.col = k;
			}
		}
	}
}

//��갴��
void mousePressMsg(ExMessage* msg)
{
	//�������������������
	if (msg->message == WM_LBUTTONDOWN)
	{
		map[pos.row][pos.col] = pos.player;

		//�ж���Ӯ
		if (judge(pos.row, pos.col))
		{
			MessageBox(GetHWnd(), "��Ӯ��", "hit", MB_OK);
			exit(666);
		}

		//�л�����
		pos.player = (pos.player == Black ? White : Black);
	}
}

bool judge(int r, int c)
{
	
	//��ȡ��ǰ����	
	int who = pos.player;

	//����:������
	for (int i = c - 4; i < c; i++)
	{
		//ע���±겻ҪԽ����[0,15)
		if (i >= 0 && i < 15 &&
			map[r][i] == who && map[r][i + 1] == who && map[r][i + 2] == who
			&& map[r][i + 3] == who && map[r][i + 4] == who)
		{
			return true;
		}
	}


	return false;
}

int main()
{
	//��������
	initgraph(600, 500, EW_SHOWCONSOLE);
	loadResource();
	//ѭ��
	while (true)
	{
		//�����������,ʹ��˫�����ͼ
		BeginBatchDraw();
		draw();
		EndBatchDraw();

		//������Ϣ
		ExMessage msg;
		//��ȡ��Ϣ
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)	//��Ϣ����
			{
			case WM_MOUSEMOVE:		//����ƶ���Ϣ
				mouseMoveMsg(&msg);
				break;
			case WM_LBUTTONDOWN:	//����������
			case WM_RBUTTONDOWN:	//����Ҽ�����
				mousePressMsg(&msg);
				break;
			default:
				break;
			}
		}
	}


	getchar();
	return 0;
}