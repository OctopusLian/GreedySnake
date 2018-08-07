#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#define MAXSTAR 3200	// 星星总数

struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};

typedef struct SNAKE
{
	int x;
	int y;
	int toward;
	int act[4];
	SNAKE *next;
	SNAKE *last;

}SNAKE;
STAR star[MAXSTAR];

void PutSnake(SNAKE *first,IMAGE img3);
void Snakexy(SNAKE *final);
SNAKE *Move(SNAKE *first,SNAKE *previous,SNAKE *final);
void InitStar(int i);
void MoveStar(int i,int x,int y);
SNAKE *StartCreate(SNAKE *first);
SNAKE *Add(SNAKE *final);
int Judge(int x,int y, SNAKE *first);
int Diejudge(SNAKE *first,int x,int y);
void End();


void PutSnake(SNAKE *first,IMAGE img3)
{

		SNAKE *temp;
		temp=first;
	/*		putimage(5*(snake.x), snake.y,32, 32,&img3,32*snake.toward,32,SRCAND);
			putimage(5*(snake.x), snake.y,32, 32,&img3,32*snake.toward,0,SRCPAINT);*/
		while(temp!=NULL)
		{
			putimage(temp->x, temp->y,32, 32,&img3,32*(temp->toward),32,SRCAND);
			putimage(temp->x, temp->y,32, 32,&img3,32*(temp->toward),0,SRCPAINT);
			temp=temp->next;
		
		}
}
void Snakexy(SNAKE *final)
{
	switch(final->act[0])
	{
	case 1:final->x +=8;final->toward =0;break;
	case 2:final->x -=8;final->toward =4;break;
	case 3:final->y +=8;final->toward =3;break;
	case 4:final->y -=8;final->toward =1;break;
	default:break;

	}
}

SNAKE *Move(SNAKE *first,SNAKE *previous,SNAKE *final)
{
	SNAKE *ptemp=NULL;
	ptemp=(SNAKE *)malloc(sizeof(SNAKE));

	ptemp=final->last;
	
	while(ptemp!=NULL)
	{	

		Snakexy(final);
		final->act[0]=final->act[1];
		final->act[1]=final->act[2];
		final->act[2]=final->act[3];
		final->act[3]=ptemp->act[0];

		final=final->last ;
		ptemp=ptemp->last ;	
	}
	
		final->x = previous->x ;
		final->y =previous->y ;
		final->toward = previous->toward ;
	return first;
}


// 初始化星星
void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % 595;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i,int x,int y)
{

	int color[30]={0xff0000,0xff6600,0xffae00,0xffff00,0xccff00,
		           0xaaff00,0x30ff00,0x00ffcc,0x30eeff,0x0000ff,
				   0xf000ff,0xff0000,0xffc1ae,0xfff8ae,0xddff8b,
				   0x8bff8e,0x8bffe0,0x8bd5ff,0xa48bff,0xffa4ef,
				   0xffa4b3,0x55ff55,0xffff55,0x5555ff,0xff55ff,
				   0x55ffff,0x00aa00,0x0000,0x0055AA,0xffffff};

	// 擦掉原来的星星
	putpixel((int)star[i].x, star[i].y, 0);

	// 计算新位置
	star[i].x += star[i].step;
	if (star[i].x > 795)	InitStar(i);

	// 画新星星

	if(star[i].step<3)
	{
	star[i].color = RGB(star[i].color,star[i].color, star[i].color);
	putpixel((int)star[i].x, star[i].y, star[i].color);
	}
	else
	{
		putpixel((int)star[i].x, star[i].y, color[x%30]);
	}

}
SNAKE *StartCreate(SNAKE *first)
{
	SNAKE *ptemp=NULL;
	SNAKE *previous=NULL;
	SNAKE *final=NULL;
	previous = (SNAKE *)malloc(sizeof(SNAKE));
	ptemp = (SNAKE *)malloc(sizeof(SNAKE));

	first->next=ptemp;
	ptemp->x = 64;
	ptemp->y = 0;
	ptemp->toward =0;
	ptemp->act[0]=1;
	ptemp->act[1]=1;
	ptemp->act[2]=1;
	ptemp->act[3]=1;

	ptemp->last =first;
	previous=ptemp;

	ptemp=(SNAKE *)malloc(sizeof(SNAKE));
	previous->next = ptemp;
	ptemp->x = 32;
	ptemp->y = 0;
	ptemp->toward =0;
	ptemp->act[0]=1;
	ptemp->act[1]=1;
	ptemp->act[2]=1;
	ptemp->act[3]=1;

	ptemp->last =previous;
	previous=ptemp;

	ptemp=(SNAKE *)malloc(sizeof(SNAKE));
	previous->next = ptemp;
	ptemp->x = 0;
	ptemp->y = 0;
	ptemp->toward =0;
	ptemp->act[0]=1;
	ptemp->act[1]=1;
	ptemp->act[2]=1;
	ptemp->act[3]=1;

	ptemp->next = NULL;
	ptemp->last =previous;

	return ptemp;

}

SNAKE *Add(SNAKE *final)
{
	SNAKE *ptemp=NULL;
	ptemp=(SNAKE *)malloc(sizeof(SNAKE));
	ptemp->x=final->x;
	ptemp->y=final->y;
	ptemp->toward=final->toward;
	ptemp->last=final;
	final->next=ptemp;
	ptemp->next=NULL;
	ptemp->act[0]=0;
	ptemp->act[1]=0;
	ptemp->act[2]=0;
	ptemp->act[3]=0;
	return ptemp;
	
}


int Judge(int x,int y, SNAKE *first)
{
	int flag=0;
	if(fabs(first->x-x)<32 &&fabs(first->y-y)<32)
		flag=1;
	return flag;
}

int Diejudge(SNAKE *first,int x,int y)
{
	int flag;
	flag=0;

	if(x<0||x>768||y<0||y>568)
		flag=1;
	first=first->next;
	first=first->next;
	for( ;first->next!=NULL ; )
	{
		if(fabs(first->x-x)<32 && fabs(first->y-y)<32)
		{
			flag=1;
			break;
		}
		first=first->next;
		

	}
	return flag;
}
void End()
{	
	int i;
	setlinecolor(0x000000);
	for(i=0;i<600;i++)
	{
	line(0,i,800,i);
	Sleep(5);
	}

	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 72;                      // 设置字体高度
	_tcscpy(f.lfFaceName, _T("Snap ITC"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = PROOF_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	
	for(i=0;i<255;i++)
	{
		Sleep(20);
		settextcolor(RGB(i,i,i));
		outtextxy(100, 250, _T("TO BE CONTINUE"));
	}
	
}

void Start(IMAGE img1)
{
	putimage(0,0,&img1);

	int c=255;
	int flag=1;

	setfont(15, 0, "宋体");

	while(!kbhit())
	{
		setcolor(RGB(c, c, c));
			outtextxy(350, 520, "W、A、S、D操作");
		outtextxy(350, 550, " 按任意键继续");
		if(c<=0)
			flag=0;
		
		if(flag)
			c -= 5;
		
		else
		{
			c += 5;
			if(c>=255)
				flag=1;
		}
		Sleep(20);
	}
	getch();
	setfillcolor(BLACK);
	for(int i=0;i<600;i++)
	{
		solidcircle(400,300,i);
		Sleep(10);
	}


}
void main()
{	

	srand((unsigned)time(NULL));	// 随机种子
	int i,j,x,y;
	double level;
	level=20;
	x=100;
	y=100;
	char c='d',ctemp='d';
	SNAKE *first=NULL;	
	SNAKE *previous=NULL;
	SNAKE *final=NULL;
	previous=(SNAKE *)malloc(sizeof(SNAKE));
	first=(SNAKE *)malloc(sizeof(SNAKE));
	final=(SNAKE *)malloc(sizeof(SNAKE));
	first->x=96;
	first->y=0;
	first->toward=0;
	first->act[0]=0;
	first->act[1]=0;
	first->act[2]=0;
	first->act[3]=0;
	first->next=NULL;
	first->last = NULL;
	previous=first;
	final=StartCreate(first);


	// 绘图环境初始化
	initgraph(800, 600);

	setbkmode(TRANSPARENT);
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	// 读取图片至绘图窗口
	loadimage(&img1, _T("res\\start.jpg"));
	loadimage(&img2, _T("res\\dog.jpg"));
	loadimage(&img3, _T("res\\bird.jpg"));

	Start(img1);
	BeginBatchDraw();

		for(j = 0; j < MAXSTAR; j++)
	{
		InitStar(j);
		star[j].x = rand() % 600;
	}
	for(i=0;i<256;i++)
		{
	
			FlushBatchDraw();
			cleardevice();
			for(int j = 0; j < MAXSTAR; j++)
				MoveStar(j,x,y);
			Sleep(level>0?level:0);

			if(i==255)
				i=0;

			if(kbhit())
			{
				ctemp=getch();
				if(c=='d'&&ctemp!='a')
					c=ctemp;
				if(c=='a'&&ctemp!='d')
					c=ctemp;
				if(c=='s'&&ctemp!='w')
					c=ctemp;
				if(c=='w'&&ctemp!='s')
					c=ctemp;


			}	
			if(c=='d'||c=='D')
			{
				first->act[0]=1;
				first->toward=0;
			
			}
			if(c=='a'||c=='A')
			{	
				first->act[0]=2;
				first->toward=4;
			}
			if(c=='s'||c=='S')
			{
				first->act[0]=3;	
				first->toward=3;
			}
			if(c=='w'||c=='W')
			{
				first->act[0]=4;
				first->toward=1;
			}
			
		putimage(x, y,32, 32,&img2,0,32,SRCAND);
		putimage(x, y,32, 32,&img2,0,0,SRCPAINT);
		
		if(Judge(x,y,first))
		{
			level=level-0.5;
			final=Add(final);
			do
			{
			x=rand() %800;
			y=rand()%600;
			}while(Diejudge(first,x,y));
		}

		if(Diejudge(first,first->x,first->y ))
		{
			Sleep(1000);
			EndBatchDraw();
			End();
			break;
		}

		PutSnake(first,img3);
		Snakexy(first);
		previous=Move(first,previous,final);
		Sleep(15);
		BeginBatchDraw();

		}

	// 按任意键退出
	getch();
	closegraph();
}