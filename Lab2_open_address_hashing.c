//
// Created by hanstananda on 26/9/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int bsdChecksumFromstr(char *input) /* The file handle for input data */
{
    int checksum = 0;             /* The checksum mod 2^16. */
    int x;
    for (x=0;x<strlen(input);x++) {
        checksum = (checksum >> 1) + ((checksum & 1) << 15);
        checksum += input[x];
        checksum &= 0xffff;       /* Keep it within bounds. */
    }
    return checksum;
}

typedef struct node
{
    char name[100];
    int item;
} hashtable;


int hashtable_size = 1<<16;

//////////////////////// MAIN FUNCTION ///////////////////////////////////////////
char* outfilename;

int main() {
    freopen("Random_tc_generated_load75%.txt", "r", stdin);
    //freopen("out.txt","w",stdout);
    time_t rawtime;
    time(&rawtime);
    malloc(sizeof(ctime(&rawtime)));
    outfilename = ctime(&rawtime);
    int outfile_len = strlen(outfilename);
    while (!(outfilename[outfile_len] >= '0' && outfilename[outfile_len] <= '9')) {
        outfilename[outfile_len] = '\0';
        outfile_len--;
    }
    strcat(outfilename, ".txt");
    freopen(outfilename, "w", stdout);
    srand(time(NULL));
    int value;
    char in[100];
    char tmp1[50], tmp2[50];
    int n;
    scanf("%d", &n);
    int x;
    hashtable storage[100];
    for(x=0;x<hashtable_size;x++)
    {
        storage[x].item = 0;
    }
    clock_t start, end;
    double cpu_time_used;
    int debug = 0;
    start = clock();
    for (x = 0; x < n; x++) {
        scanf("%s %s %d", tmp1, tmp2, &value);
        strcat(tmp1, " ");
        strcat(tmp1, tmp2);
        strcpy(in, tmp1);
        int hashed_value = bsdChecksumFromstr(in);
    }
    return 0;
}