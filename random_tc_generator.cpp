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
map<pii,bool> double_check;

int main()
{
	freopen("Random_names_2.txt","r",stdin); 
 	freopen("Random_tc_generated_load75%.txt","w",stdout);
 	int x=1;
 	int score;
 	int gen_needed=3<<14;
 	printf("%d\n",gen_needed);
	 while(scanf("%s %s",seed1[x],seed2[x])!=EOF)
 	{
 		score=rand()%100+1;
 		printf("%s %s %d\n",seed1[x],seed2[x],score);
 		x++;
	}
	int y=0;
	for(y=x;y<=gen_needed;y++)
	{
		int a=rand()%x+1;
		int b=a;
		while(b==a)
		{
			b=rand()%x+1;
		}
		if(double_check[mp(a,b)]==1||strcmp(seed1[a],"")==0||strcmp(seed2[b],"")==0)
		{
			y--;
			continue;
		}
		score=rand()%100+1;
		double_check[mp(a,b)]=1;
		printf("%s %s %d\n",seed1[a],seed2[b],score);
	}
	return 0;
}
