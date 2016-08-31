#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fcntl.h>
#include <termios.h>

struct P{
	int x,y;
	P(int x,int y):x(x),y(y){}
} e(3,3); 
std::vector<P> p={P(6,4),P(5,4)};
char d='d';
int i,s=0,x=30,y=10,t=500000;
void pXY(int X,int Y,char c){printf("\033[%d;%dH%c",Y+1,X+1,c);}
P w(P g){
	if(d=='d')return P(g.x+1,g.y);
	if(d=='w')return P(g.x,g.y-1);
	if(d=='s')return P(g.x,g.y+1);
	if(d=='a')return P(g.x-1,g.y);
}
void r(){
	system("clear");
	for(auto a=p.begin();a!=p.end();a++)pXY(a->x,a->y,'o');
	pXY(e.x,e.y,'*');
	for(i=0;i<y;i++)pXY(x,i,'|');
	for(i=0;i<=x;i++)pXY(i,y,'-');
	puts("");
}
int k(){struct termios o,n;int c,q;tcgetattr(0,&o);n=o;n.c_lflag&=~(ICANON|ECHO);tcsetattr(0,TCSANOW,&n);q=fcntl(0,F_GETFL,0);fcntl(0,F_SETFL,q|O_NONBLOCK);c=getchar();tcsetattr(0,TCSANOW,&o);fcntl(0,F_SETFL,o);if(c!=EOF){ungetc(c,stdin);return 1;}return 0;}

int main(){
r();
while(1){
usleep(t);
if(k())d=getchar();
for(auto a=p.begin();a!=p.end();a++)
if(a->x>=x||a->x<0||a->y>=y||a->y<0){printf("Score: %d\n",s);exit(0);}
if(p.begin()->x==e.x&&p.begin()->y==e.y){s++;t-=10000;p.insert(p.begin(),w(e));e.x=rand()%x;e.y=rand()%y;}
p.erase(p.end()-1);
p.insert(p.begin(),w(*p.begin()));
r();
}}
