#include <stdio.h>
#include <easyx.h>  //graphics.h
#include <mmsystem.h> //系统多媒体头文件
#pragma comment(lib,"winmm.lib") //windows的多媒体库文件

int main()
{
	initgraph(800, 450);				//创建窗口
	char letter;			//定义字母
	int  x, y;			    //字母的坐标x 和 y
	int  speed = 2;         //字母移动的速度
	IMAGE bkimg;                   //定义图片
	loadimage(&bkimg, "111.jpg");  //加载图片
	IMAGE appimg0, appimg1;
	loadimage(&appimg0, "apple0.jpg");
	loadimage(&appimg1, "apple1.jpg");
	mciSendString("open 告白气球.mp3", 0, 0, 0);
	mciSendString("play 告白气球.mp3", 0, 0, 0);
	ExMessage m;  //定义一个消息

	int score = 100;//分数
	char scoreStr[10] = { 0 };
	setbkmode(0);

	while (1)
	{
		letter = rand() % 26 + 'A';  //随机的26个大写字母
		x = rand() % 781;            //随机的0-780
		for (y = 0; y < 450; y += speed) //字母下降
		{
			BeginBatchDraw();   //缓冲防止界面卡顿
			putimage(0, 0, &bkimg);        //输出图片
			putimage(x - 20, y - 20, &appimg0, SRCPAINT);
			putimage(x - 20, y - 20, &appimg1, SRCAND);
			settextcolor(WHITE);
			outtextxy(x, y, letter);  //输出字母
			sprintf(scoreStr, "分数：%d", score);
			settextcolor(BLACK);
			outtextxy(5, 5, scoreStr);  //输出分数
			EndBatchDraw();//结束缓冲
			peekmessage(&m, EM_MOUSE | EM_KEY); //接收消息
			if (m.message == WM_LBUTTONDOWN) {} //鼠标左键
			else if (m.message == WM_KEYDOWN) //按键
			{
				if (m.vkcode == letter)  //字母
				{
					score += 5;
					break;  //跳出for循环
				}
				else if (m.vkcode == '1')
				{
					speed = 2;
					mciSendString("close 本草纲目.mp3", 0, 0, 0);
					mciSendString("open 告白气球.mp3", 0, 0, 0);
					mciSendString("play 告白气球.mp3", 0, 0, 0);
				}
				else if (m.vkcode == '2')
				{
					speed = 5;
					mciSendString("close 告白气球.mp3", 0, 0, 0);
					mciSendString("open 本草纲目.mp3", 0, 0, 0);
					mciSendString("play 本草纲目.mp3", 0, 0, 0);
				}
			}
			Sleep(10);
		}
	}
	//VIP:
	//4.30号：
	// 1/3 

	//弟子：学什么东西。VIP所有的内容 + PYTHON + 手机游戏开发 + 逆向汇编与反汇编 
	//学多久： 九哥坟头不长草   8-9个月
	//怎么学： 
	// 1.直播 + 录播 + 课后1对1 8个老师
	// 2.3-4个月左右 顿开工作室 接外包
	// 学费：
		//正常价格：8280 分期  手续费 450
		//7280 分期 1000  800  600  500  400  300  200

	//怎么想：
	//1.时间的问题。 没时间：学这个东西 学好学会！效率吗？ 能磨出来！
	//大部分 少部分  
	// 上士闻道  勤而行之  中士闻道  若存若亡  下士闻道 大笑之

	//没时间。
	//没钱。
	//还年轻。
	//情况。
	//英语不好。
	//数学不好。
	//爸妈不同意。
	//不支持。


	//initgraph(800, 450);				//创建窗口
	//cleardevice();						//刷新
	//mciSendString("open 告白气球.mp3", 0, 0, 0);

	///*mciSendString("pause 告白气球.mp3", 0, 0, 0);
	//mciSendString("close 告白气球.mp3", 0, 0, 0);*/
	//settextcolor(RGB(255, 149, 240));    //set text color
	//settextstyle(72, 0, "华文彩云");      //set text style  字号(高72 宽-0自适应)
	//outtextxy(20, 100, "九夏真TMD帅");    //out text xy

	////7.图片
	////普通绘图
	//IMAGE bkimg;                   //定义图片
	//loadimage(&bkimg, "111.jpg");  //加载图片
	//putimage(0, 0, &bkimg);        //输出图片

	////透明绘图.
	////1.准备2张图片 黑底白面图  白底彩面图    (遮罩图 掩码图)
	////2.把2张图片绘制到同一个坐标
	////3.分别是用二进制操作 |-SRCPAINT  &-SRCAND
	//IMAGE appimg0, appimg1;
	//loadimage(&appimg0, "apple0.jpg");
	//loadimage(&appimg1, "apple1.jpg");
	//putimage(329, 184, &appimg0, SRCPAINT);
	//putimage(329, 184, &appimg1, SRCAND);

	////8.消息（键盘 鼠标）
	//ExMessage m;  //定义一个消息
	//while (1)
	//{
	//	peekmessage(&m, EM_MOUSE | EM_KEY); //接收消息
	//	if (m.message == WM_LBUTTONDOWN) //鼠标左键
	//	{
	//		mciSendString("play 告白气球.mp3", 0, 0, 0);
	//	}
	//	else if (m.message == WM_KEYDOWN) //按键
	//	{
	//		if (m.vkcode == 'F')
	//		{
	//			mciSendString("pause 告白气球.mp3", 0, 0, 0);
	//		}
	//	}
	//}
	return 0;
}