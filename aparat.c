#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

static char tab[4][4];
char keys[4][4] = {{'1','2','3','4'},{'q','w','e','r'},{'a','s','d','f'},{'z','x','c','v'}};
static int counter=0;
char g=0;

void timeout()
{
	printf("Czas upłynął. Twój wynik to: %d\n", counter);
	if(g==0) exit(0);
}

static void* start_tim(void *args)
{
	void (*fp)();
	int seconds = *((int*) args);
	fp = timeout;
	sleep(seconds);
	(*fp)();
	pthread_exit(NULL);
}

void print()
{
	int i, j;
	for(i = 0; i<4; i++)
	{
		printf("-----------------\n|");
		for(j=0; j<4;j++)
		{
			printf(" %c |", ((tab[i][j]==0) ? ' ' : 'x'));
		}
		printf("\n");
	}
	printf("-----------------\n");
}

int main()
{
	pthread_t th;
	int sec = 2;
	int i = 0, j = 0, x = 0, y = 0;
	while(1)
	{
		g = 0;
		system("clear");
		fflush(stdin);
		srand(time(NULL));
		int i = rand()%4;
		int j = rand()%4;
		for(y=0; y<4; y++)
		{
			for(x=0;x<4;x++)
			{
				tab[x][y] = 0;
			}
		}
		tab[i][j]=1;
		print();
		pthread_create(&th, NULL, start_tim, (void *) &sec);
		g=getchar();
		getchar();
		if(g != keys[i][j])
			break;
		counter++;
		pthread_join(th, NULL);
	}
	printf("Koniec gry. Twój wynik to: %d\n", counter);
	return 0;
}
