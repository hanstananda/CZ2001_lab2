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
map<pii,bool> double_check_name;
map<string,bool> double_check_matric;

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

int main()
{
    freopen("Random_names_2.txt","r",stdin);
    freopen("Random_tc_generated_load25%.txt","w",stdout);
    int x=1;
    int score;
    int gen_needed=1<<14;
    char matric_num[100];
    printf("%d\n",gen_needed);
    while(scanf("%s %s",seed1[x],seed2[x])!=EOF)
    {
        score=rand()%100+1;
        matric_randomizer(matric_num);
        printf("%s %s %s %d\n",matric_num,seed1[x],seed2[x],score);
        x++;
    }
    int y;
    for(y=x;y<=gen_needed;y++)
    {
        int a=rand()%x+1;
        int b=a;
        while(b==a)
        {
            b=rand()%x+1;
        }
        if(double_check_name[mp(a,b)]==1||strcmp(seed1[a],"")==0||strcmp(seed2[b],"")==0)
        {
            y--;
            continue;
        }
        score=rand()%100+1;
        double_check_name[mp(a,b)]=1;
        matric_randomizer(matric_num);
        while(double_check_matric[(string)matric_num])
        {
            matric_randomizer(matric_num);
        }
        double_check_matric[(string)matric_num]=1;
        printf("%s %s %s %d\n",matric_num,seed1[a],seed2[b],score);
    }
    return 0;
}
