#include<stdio.h>
#include<easyx.h>  //图形库
#include<time.h>    //时间头文件
#include<mmsystem.h>     //音乐头文件
#pragma comment(lib,"winmm.lib")  //播放音乐库文件

IMAGE  img_meteor[2];


//绘制星星   移动的速度   颜色
struct Star
{
	int x;
	int y;
	int speed;
};

//初始化
void star_init(Star* star, int x, int y, int speed)
{
	star->x = x;
	star->y = y;
	star->speed = speed;
}

//绘制
void star_draw(Star* star)
{
	setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	solidcircle(star->x, star->y, 1);
}

void star_moveby(Star* star, int dx, int dy)
{
	star->x = dx;
	star->y = dy;
}
//流星
typedef Star Meteor;
//初始化流星
void meteor_init(Meteor* me, int x, int y, int speed)
{
	star_init(me,x, y, speed);
}

//绘制
void meteor_draw(Meteor* me)
{
	putimage(me->x, me->y, img_meteor + rand() % 2, SRCPAINT);
}

void meteor_moveby(Meteor* star, int dx, int dy)
{
	star_moveby(star, dx, dy);
}

//定义变量,初始化,绘制
#define STAR_NUM 500 //出现小星星的数量
#define METEOR_NUM 100
Star stars[STAR_NUM];
Meteor mes[METEOR_NUM];

void init()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		int x = rand() % getwidth();
		int y = rand() % getheight();
		int speed = rand()%5 + 1;//[1,5]
		meteor_init(mes + i, x, y, speed);
	}
}

void draw()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		star_draw(stars + i);
	}
	for (int i = 0; i < METEOR_NUM; i++)
	{
		meteor_draw(mes + i);
	}
}

void move()
{
	for (int i = 0; i < STAR_NUM; i++)
	{
		star_moveby(stars + i, stars[i].speed, 0);
		//判断流星是否移动超过了窗口边界
		if (stars[i].x > getwidth())
		{
			stars[i].x = 0;
		}
	}
	for (int i = 0; i < METEOR_NUM; i++)
	{
		meteor_moveby(mes + i, mes[i].speed, mes[i].speed);

		if (mes[i].x > getwidth())
		{
			mes[i].x = -img_meteor->getwidth();
		}
		else if (mes[i].y > getheight())
		{
			mes[i].y = -img_meteor->getheight(); 
		}
	}
}

int main()
{
	//窗口
	initgraph(1200, 800);
	//设置随机数种子
	srand(time(NULL));

	init();

	//打开文件夹中的音乐
	mciSendString("open./images/浪漫空气.mp3 alias bgm", NULL, 0, NULL);
	//播放文件中的音乐
	mciSendString("play bgm repeat", NULL, 0, NULL);

	//绘制背景图片
	IMAGE img_bk[2];
	loadimage(img_bk + 0, "./images/bk1.png", getwidth(), getheight());
	loadimage(img_bk + 1, "./images/bk1.png", getwidth(), getheight());

	loadimage(img_meteor + 0, "./images/bk1.png", 50,50);
	loadimage(img_meteor + 1, "./images/bk1.png", 50,50);
	loadimage(img_meteor + 1, "./images/heart/heart0_0.png", 30, 30);

	//输出图片
	//putimage(0, 0, img_bk + 0);
	//putimage(0, 0, img_bk + 1);

	//设置文字样式
	settextstyle(40, 0, "微软雅黑");
	//设置背景样式
	setbkmode(TRANSPARENT);
	//如果没有按键按下,那就一直循环,如果有按键按下,那就退出循环
	while (false)
	{
		putimage(0, 0, img_bk + 0);
		//设置文字颜色
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//绘制文字
		outtextxy(500, 20, "");
		outtextxy(200, 100, "");
		outtextxy(200, 150, "");
		outtextxy(200, 200, "");
		outtextxy(200, 250, "");
		outtextxy(200, 300, "");
		outtextxy(200, 350, "");
		outtextxy(200, 400, "");
		outtextxy(200, 450, "");
		outtextxy(200, 500, "");
		outtextxy(200, 550, "--------------------------");

		//绘制爱心
		for (int i = 0; i < 10; i++)
		{
			settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			outtextxy(rand() % getwidth(), rand() % getheight(), rand() % 2 ? "♥" : "♡");
		}

		Sleep(300);

	}

	//流星雨界面
	while (true)
	{
		BeginBatchDraw();//双缓冲绘图
		putimage(0, 0, img_bk + 1);
		draw();
		EndBatchDraw();
		move();

		Sleep(10);

	}
	getchar();//防止闪退
	getchar();//防止闪退
	getchar();//防止闪退
	//system("pause");
	return 0;

}