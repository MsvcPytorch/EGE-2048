#define SHOW_CONSOLE
#include <graphics.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
int pawn[6][6]={0};
void setWindowTransparent(bool enable, int alpha = 0xFF) {
	HWND egeHwnd = getHWnd();
	LONG nRet = ::GetWindowLong(egeHwnd, GWL_EXSTYLE);
	nRet |= WS_EX_LAYERED;
	::SetWindowLong(egeHwnd, GWL_EXSTYLE, nRet);
	if (!enable)
		alpha = 0xFF;
	SetLayeredWindowAttributes(egeHwnd, 0, alpha, LWA_ALPHA);
}
void drawbar(int xpointx,int xpointy,int ypointx,int ypointy,int kind)
{   setfillcolor(BLUE);
setWindowTransparent(true, 0xc0);
    //setfont(-16,0,"宋体");
	bar(xpointx,xpointy,ypointx,ypointy);
	int xcentral=(ypointx+xpointx)/2-20;
	int ycentral=(ypointy+xpointy)/2-10;
	 kind=kind-1;
	switch(kind){
		case 0:
			{xyprintf(xcentral-10,ycentral,"2");break;}
		case 1:
			{xyprintf(xcentral,ycentral,"4");break;}
		case 2:
			{xyprintf(xcentral,ycentral,"8");break;}
		case 3:
			{xyprintf(xcentral,ycentral,"16");break;}
		case 4:
			{xyprintf(xcentral-10,ycentral,"32");break;}
		case 5:
			{xyprintf(xcentral,ycentral,"64");break;}
		case 6:
			{xyprintf(xcentral,ycentral,"128");break;}
		case 7:
			{xyprintf(xcentral,ycentral,"256");break;}
		case 8:
			{xyprintf(xcentral,ycentral,"512");break;}
		case 9:
			{xyprintf(xcentral,ycentral,"1024");break;}
		case 10:
			{xyprintf(xcentral,ycentral,"2048");;break;}
		case 11:
			{xyprintf(xcentral,ycentral,"4096");break;}
	    default:{}
	}
	
}
void printpawn()
{ int i,t;
for (i=1;i<=4;i++)
{
	for (t=1;t<=4;t++)
	{
		drawbar(250+90*(i-1),250+90*(t-1),250+90*(i-1)+70,250+90*(t-1)+70,pawn[i][t]);
		//cout<<pawn[i][t]<<endl;
	}
}
	
}
void generatenewblock()
{int d;
int y;
int temp,temp1;
int empty=0;
for (temp=1;temp<=4;temp++)
{for (temp1=1;temp1<=4;temp1++)
{if (pawn[temp][temp1]==0)
{empty++;
}
}
}
 
if (empty==0)
{
return ;
}
 d=rand()%empty+1;
 y=rand()%3+1;
 empty=0;
for (temp=1;temp<=4;temp++)
{for (temp1=1;temp1<=4;temp1++)
{if (pawn[temp][temp1]==0)
{empty++;
if (empty==d) 
{
pawn[temp][temp1]=y;return ;
}
}
}
 }
}


void keydown()
{int loc[5],temp;
loc[1]=4;loc[2]=4;loc[3]=4;loc[4]=4;
	for (int y=1;y<=4;y++)
	{for(int z=4;z>=1;z--)
	{if (pawn[y][z]>0)
	{
	    temp=pawn[y][z];
			pawn[y][z]=0;
			pawn[y][loc[y]]=temp;
		
		if (pawn[y][loc[y]]==pawn[y][loc[y]+1] && loc[y]!=4)
		{pawn[y][loc[y]+1]++;
		pawn[y][loc[y]]=0;
			loc[y]++;
		}
		loc[y]--;
	}
	}
	}
}
void keyup()
{int loc[5],temp;
loc[1]=1;loc[2]=1;loc[3]=1;loc[4]=1;
	for (int y=1;y<=4;y++)
	{for(int z=1;z<=4;z++)
	{if (pawn[y][z]>0)
	{
			temp=pawn[y][z];
			pawn[y][z]=0;
			pawn[y][loc[y]]=temp;
		
		if (pawn[y][loc[y]]==pawn[y][loc[y]-1] && loc[y]!=1)
		{pawn[y][loc[y]-1]++;
		pawn[y][loc[y]]=0;
			loc[y]--;
		}
		loc[y]++;
	}
	}
	}
	
}
void keyleft()
{int loc[5],temp;
loc[1]=1;loc[2]=1;loc[3]=1;loc[4]=1;
	for (int z=1;z<=4;z++)
	{for(int y=1;y<=4;y++)
	{if (pawn[y][z]>0)
	{
			temp=pawn[y][z];
			pawn[y][z]=0;
			pawn[loc[z]][z]=temp;
	
		if (pawn[loc[z]][z]==pawn[loc[z]-1][z] && loc[z]!=1)
		{pawn[loc[z]-1][z]++;
		pawn[loc[z]][z]=0;
			loc[z]--;
		}
			loc[z]++;
	}
	}
	}
	
}
void keyright()
{int loc[5],temp;
loc[1]=4;loc[2]=4;loc[3]=4;loc[4]=4;
	for (int z=1;z<=4;z++)
	{for(int y=4;y>=1;y--)
	{if (pawn[y][z]>0)
	{
		temp=pawn[y][z];
		pawn[y][z]=0;
		pawn[loc[z]][z]=temp;
		
		if (pawn[loc[z]][z]==pawn[loc[z]+1][z] && loc[z]!=4)
		{pawn[loc[z]+1][z]++;
		pawn[loc[z]][z]=0;
			loc[z]++;
		}
		loc[z]--;
	}
	}
	}
	
}
void play()
{  key_msg keyMsg = {0};
	printpawn();
//	generatenewblock();
	while(1)
	{
	generatenewblock();
	delay(200); 
	printpawn();

  	
  	for (; is_run(); delay_fps(10)) {
  		while (kbmsg()) {
  			keyMsg = getkey();
  			goto a;
  	}
  	}
  	a:	switch (keyMsg.key) {		
	  			case key_down:	keydown(); break;
	  			case key_up: 	keyup(); 	break;
	  			case key_left: 	keyleft(); break;
	  			case key_right: keyright(); break;
	  			case key_enter: printf("你输了\n"); closegraph();return ;break;
	  		//	default: generatenewblock();break;
	  			}
	  	printpawn();
	//delay(300);
	
	
}
}
int main()
{srand(time(NULL));
setWindowTransparent(true, 0xc0);
initgraph(720,960);
setcolor(GREEN);

drawbar(250,250,320,320,7);
drawbar(250,250,320,320,11);
play();
//xyprintf(300, 200, "暂停，按任意键继续 ");
    //ovewindow(-8, 0, true);
	//getch();
    
	closegraph();
	return 0;
	
}
