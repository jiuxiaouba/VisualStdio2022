#include<stdio.h>
#include<easyx.h>//图形库头文件
#include<mmsystem.h>//播放音乐头文件
#pragma comment(lib,"winmm.lib")//播放音乐库文件
/*
* 集成开发环境：vs2019 + easyx库 安装
*/

#define GRID_W 25			//每个线条之间的间隔
#define SPACE (3*GRID_W)	//上面和左边的间距
#define ROW 15
#define COL 15

bool judge(int r, int c);

enum Chess
{
	None,
	Black,
	White
};
//定义地图数组，用来存储棋子 0 没有棋子 1 黑棋 2 白棋
int map[ROW][COL];

struct Pos
{
	int row;
	int col;
	bool isShow;	//是否显示蓝色框
	int player;		//棋手
}pos = { -1,-1,false,Black };

//背景图片
IMAGE bk;
void loadResource()
{
	//加载图片 int a; a = 20;	//2 个重载中没有一个可以转换所有参数类型
	loadimage(&bk, "Res/bk.jpg");
	//播放音乐
	mciSendString("play Res/G弦之歌.mp3 repeat", 0, 0, 0);
}

void draw()
{
	//输出图片
	putimage(0, 0, &bk);

	//网格线 15*15
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	for (int i = 0; i < 15; i++)
	{
		line(SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE, i * GRID_W + SPACE);		//横线
		line(i * GRID_W + SPACE, SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE);		//竖线
	}
	//画边框(粗一点)
	setlinestyle(PS_SOLID, 2);
	rectangle(SPACE, SPACE, SPACE + 14 * GRID_W, SPACE + 14 * GRID_W);

	//设置填充颜色
	setfillcolor(BLACK);
	//画中间点
	solidcircle(SPACE + 7 * GRID_W, SPACE + 7 * GRID_W, 5);
	//左上
	solidcircle(SPACE + (7 - 4) * GRID_W, SPACE + (7 - 4) * GRID_W, 5);
	//左下
	solidcircle(SPACE + (7 - 4) * GRID_W, SPACE + (7 + 4) * GRID_W, 5);
	//右上
	solidcircle(SPACE + (7 + 4) * GRID_W, SPACE + (7 - 4) * GRID_W, 5);
	//右下
	solidcircle(SPACE + (7 + 4) * GRID_W, SPACE + (7 + 4) * GRID_W, 5);

	//绘制棋子：根据数组里面的数据绘制棋子
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			if (map[i][k] == Black)	//黑棋
			{
				setfillcolor(BLACK);
				solidcircle(k * GRID_W + SPACE, i * GRID_W + SPACE, 10);
			}
			else if (map[i][k] == White)	//白棋
			{
				setfillcolor(WHITE);
				solidcircle(k * GRID_W + SPACE, i * GRID_W + SPACE, 10);
			}
		}
	}

	//绘制蓝色的框
	setlinecolor(BLUE);
	//根据鼠标获得下标
	if (pos.isShow)
		rectangle(pos.col * GRID_W + SPACE - 12, pos.row * GRID_W + SPACE - 12, pos.col * GRID_W + SPACE + 12, pos.row * GRID_W + SPACE + 12);
}

//鼠标移动
void mouseMoveMsg(ExMessage* msg)
{
	printf("mouseMoveMsg\n");

	pos.isShow = false;
	//坐标校准
	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//获得每个格子左上角的坐标
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

//鼠标按下
void mousePressMsg(ExMessage* msg)
{
	//如果是鼠标左键，就下棋
	if (msg->message == WM_LBUTTONDOWN)
	{
		map[pos.row][pos.col] = pos.player;

		//判断输赢
		if (judge(pos.row, pos.col))
		{
			MessageBox(GetHWnd(), "你赢了", "hit", MB_OK);
			exit(666);
		}

		//切换棋手
		pos.player = (pos.player == Black ? White : Black);
	}
}

bool judge(int r, int c)
{
	
	//获取当前棋手	
	int who = pos.player;

	//横向:遍历列
	for (int i = c - 4; i < c; i++)
	{
		//注意下标不要越界了[0,15)
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
	//创建窗口
	initgraph(600, 500, EW_SHOWCONSOLE);
	loadResource();
	//循环
	while (true)
	{
		//解决闪屏问题,使用双缓冲绘图
		BeginBatchDraw();
		draw();
		EndBatchDraw();

		//处理消息
		ExMessage msg;
		//获取消息
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)	//消息类型
			{
			case WM_MOUSEMOVE:		//鼠标移动消息
				mouseMoveMsg(&msg);
				break;
			case WM_LBUTTONDOWN:	//鼠标左键按下
			case WM_RBUTTONDOWN:	//鼠标右键按下
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