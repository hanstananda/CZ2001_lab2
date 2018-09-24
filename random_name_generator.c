#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char seed1[100000][50];
char seed2[100000][50];
map<pii,bool> double_cek;

int main()
{
	freopen("input.in","r",stdin); 
 	freopen("output.out","w",stdout);
 	int x=0;
 	int gen_needed=100000;
	 while(scanf("%s %s",seed1[x],seed2[x])!=EOF)
 	{
 		printf("%s %s\n",seed1[x],seed2[x]);
 		x++;
	}
	int y=0;
	for(y=0;y<gen_needed;y++)
	{
		int a=rand()%x;
		int b=a;
		while(b==a)
		{
			b=rand()%x;
		}
		if(double_check[mp(a,b)]==1)
		continue;
		double_check[mp(a,b)]=1;
		printf("%s %s\n",seed1[x],seed2[x]);
	}
	return 0;
}
