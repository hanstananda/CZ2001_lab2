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
map<string,bool> double_check;
char matric_num_list[100010][100];

int main()
{
    freopen("Random_tc_generated_load75%.txt","r",stdin);
    //freopen("Random_fail_query_generated.txt","w",stdout);
    freopen("Random_success_query_generated.txt","w",stdout);
    int x=1;
    int gen_needed=100000;
    bool successful=0;
    int dummy;
    char seed1[100],seed2[100];
    char matric_num[100];
    printf("%d\n",gen_needed);
    while(scanf("%s %s %s %d",matric_num_list[x],seed1,seed2,&dummy)!=EOF)
    {
        double_check[(string)matric_num_list[x]]=1;
        //printf("%s %s\n",seed1[x],seed2[x]);
        x++;
    }
    int y=0;
    for(y=0;y<gen_needed;y++)
    {

        if(successful)
        {
            int a=rand()%x+1;
            //choose any ppl randomly in list
            printf("%s\n",matric_num_list[a]);
        }
        else
        {
            //randomly find ppl that is not available in the list
            matric_randomizer(matric_num);
            while(double_check[(string)matric_num])
            {
                matric_randomizer(matric_num);
            }
            printf("%s\n",matric_num);
        }
    }
    return 0;
}
