#include <bits/stdc++.h>
// Define
#define mp make_pair
#define pii pair<int,int> 
#define ff first
#define pb push_back
#define ss second
#define ll long long 
#define ull unsigned long long
#define vi vector<int>
#define vii vector<pii>
#define vvi vector <vi>
#define rep(x,a,b,c) for(int x=a;x<=b;x+=c)
#define repp(x,a,b) rep(x,a,b,1)
#define rev(x,a,b,c) for(int x=a;x>=b;x-=c)
#define revv(x,a,b) rev(x,a,b,1)
#define OO (int)2e9
#define INF (ll)9e18
#define EPS (double)1e-6
#define MOD 1000000007

using namespace std;

char seed1[100000][50];
char seed2[100000][50];
char vocal[10]="aiueo";

int main()
{
	freopen("Random_tc_generated_load75%.txt","r",stdin); 
 	freopen("Random_fail_query_generated.txt","w",stdout);
 	int x=1;
 	int gen_needed=100000;
 	bool successful=0;
	int dummy;
	printf("%d\n",gen_needed);
	while(scanf("%s %s %d",seed1[x],seed2[x],&dummy)!=EOF)
 	{
 		//printf("%s %s\n",seed1[x],seed2[x]);
 		x++;
	}
	int y=0;
	for(y=0;y<=gen_needed;y++)
	{
		int a=rand()%x+1;
		int b=a;
		if(successful)
		{
			//choose any ppl randomly in list
			printf("%s %s\n",seed1[a],seed2[b]);
		}
		else
		{
			//randomly find ppl that is not available in the list
			
			while(b==a)
			{
				b=rand()%x+1;
			}
			printf("%s %s%c\n",seed1[a],seed2[b],vocal[rand()%5]);
		}
		
	}
	return 0;
}
