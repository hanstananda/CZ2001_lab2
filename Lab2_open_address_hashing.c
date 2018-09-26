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
    ////////// Start of I/O redirection for automation testing
    // Comment all these lines below if you want to test it manually
    freopen("Random_tc_generated_load75%.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    set_outfilename();
    freopen(outfilename,"w",stdout);
    ////////// End of I/O redirection for automation testing

    ////////// Start of Variables Initialization
    // for input
    int n,value,x;
    char in[100];
    char tmp1[50],tmp2[50];
    hashtable_init();
    // clock init
    srand(time(NULL));
    clock_t start,end;
    double cpu_time_used;
    ////////// End of Variables Initialization


    ////////// Start of Setting the initial hashtable
    scanf("%d",&n);
    start=clock();
    for(x=0;x<n;x++)
    {
        ////////// Start of input scanning and parsing
        scanf("%s %s %d",tmp1,tmp2,&value);
        strcat(tmp1," ");
        strcat(tmp1,tmp2);
        strcpy(in,tmp1);
        ////////// End of input scanning and parsing
        insert_into_hashtable(in,value);
    }
    end=clock();
    cpu_time_used = ((double) (end - start)) /(double) CLOCKS_PER_SEC;
    printf("Number of clashes: %d\n",num_clash);
    //printList(&storage[clash_max_idx]);
    printf("Time used to map the value: %.8lf\n",cpu_time_used);
    ////////// End of Setting the initial hashtable
    return 0;
}