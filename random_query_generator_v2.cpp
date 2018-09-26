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

void matric_randomizer(char* matric_num)
{
    // Considering all undergraduate student, so the first character will be 'U'
    matric_num[0]='U';
    for(int x=1;x<=7;x++)
    {
        // Randomize the integer value in matric card
        matric_num[x]=rand()%10+'0';
    }
    // last matric card is character
    matric_num[8]=rand()%26+'A';
    // end of string marking
    matric_num[9]='\0';
}
map<string,bool> double_check_matric;
char vocal[10]="aiueo";
char matric_num_list[100010][100];
char seed1[100010][100];
char seed2[100010][100];

int main()
{
    freopen("Random_tc_generated_load25%.txt","r",stdin);
    bool successful=1;
    if(successful)
    {
    	freopen("Random_success_query_generated_new.txt","w",stdout);
    }
    else
    {
    	freopen("Random_fail_query_generated_new.txt","w",stdout);
    }
    int x=1;
    int gen_needed=100000;
    
    int dummy;
    char matric_num[100];
    printf("%d\n",gen_needed);
    int n;
    scanf("%d",&n);
    for(x=1;x<=n;x++)
    {
        scanf("%s %s %s %d",matric_num_list[x],seed1[x],seed2[x],&dummy);
        double_check_matric[(string)matric_num_list[x]]=1;
        //printf("%s %s\n",seed1[x],seed2[x]);
    }
    //printf("%d\n",n);
    int y=0;
    for(y=0;y<gen_needed;y++)
    {
        int a=rand()%n+1;
        int b=a;
        if(successful)
        {
            //choose any ppl randomly in list
            printf("%s %s %s\n",matric_num_list[a],seed1[a],seed2[b]);
        }
        else
        {
            //randomly find ppl that is not available in the list
            matric_randomizer(matric_num);
            while(double_check_matric[(string)matric_num])
            {
                matric_randomizer(matric_num);
            }
            while(b==a)
            {
                b=rand()%x+1;
            }
            printf("%s %s %s%c\n",matric_num,seed1[a],seed2[b],vocal[rand()%5]);
        }
    }
    return 0;
}
