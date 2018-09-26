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
    char key[100];
    char name[100];
    int item;
    int status; // not inserted =0, inserted = 1, deleted=2
} hashnode;

//////////////////////// HashTable FUNCTIONS ///////////////////////////////////////////

#define hashtable_size 1<<16

hashnode storage[hashtable_size];

void hashtable_init()
{
    int x;
    for(x=0;x<hashtable_size;x++)
    {
        storage[x].item = 0;
        storage[x].status = 0;
    }
}

int num_clash=0,num_shift=0;

void insert_into_hashtable(char *key,int data1,char* data2)
{
    int hashed_value=bsdChecksumFromstr(key);
    //printf("%s %d\n",key,hashed_value);
    //printf("hashed into: %d\n",hashed_value); // for debug only
    hashnode tmp = storage[hashed_value];
    int linear_probing_value = hashed_value;
    int full=0;
    if(storage[linear_probing_value].status!=0)
    {
        num_clash++;
    }
    while(storage[linear_probing_value].status!=0)
    {
        if(linear_probing_value==hashed_value&&full)
        {
            printf("Error! Table is full!");
            return;
        }
        full=1;
        linear_probing_value++;
        linear_probing_value &= 0xffff;       /* Keep it within bounds. */
        num_shift++;
    }
    ///////// Inserting value to hashtable
    storage[linear_probing_value].status=1;
    storage[linear_probing_value].item=data1;
    strcpy(storage[linear_probing_value].key,key);
    strcpy(storage[linear_probing_value].name,data2);
}

int cmp_total=0;
void search_in_hashtable(char * key)
{
    int hashed_value=bsdChecksumFromstr(key);
    int cmp_num=1;
    hashnode *tmp = &storage[hashed_value];
    int linear_probing_value = hashed_value;
    int full=0;
    while(tmp->status!=0)
    {
        if(linear_probing_value==hashed_value&&full)
        {
            break;
        }
        if(tmp->status==1&&strcmp(tmp->key,key)==0)
        {
            printf("%s is found with value of %d\n",tmp->name,tmp->item);
            printf("%d comparison performed\n",cmp_num);
            cmp_total+=cmp_num;
            return;
        }
        full=1;
        linear_probing_value++;
        linear_probing_value &= 0xffff;
        cmp_num++;
        tmp=&storage[linear_probing_value];
    }
    printf("not found!\n",key);
    printf("%d comparison performed\n",cmp_num);
    cmp_total+=cmp_num;
    return;
    //printList(&storage[hashed_value]);
}

//////////////////////// OTHER FUNCTIONS ///////////////////////////////////////////

// Set the output file name to contain current time timestamp
char* outfilename;
void set_outfilename()
{
    time_t rawtime;
    time (&rawtime);
    outfilename = malloc(sizeof(ctime(&rawtime)));
    outfilename=ctime(&rawtime);
    int outfile_len=strlen(outfilename);
    while(!(outfilename[outfile_len]>='0'&&outfilename[outfile_len]<='9'))
    {
        outfilename[outfile_len]='\0';
        outfile_len--;
    }
    strcat(outfilename," open address hashing output.txt");
}

//////////////////////// MAIN FUNCTION ///////////////////////////////////////////
char* outfilename;

int main() {
    ////////// Start of I/O redirection for automation testing
    // Comment all these lines below if you want to test it manually
    freopen("Random_tc_generated_load25%.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    set_outfilename();
    freopen(outfilename,"w",stdout);
    ////////// End of I/O redirection for automation testing

    ////////// Start of Variables Initialization
    // for input
    int n,value,x;
    char in[100],full_name[100];
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
        scanf("%s %s %s %d",in,tmp1,tmp2,&value);
        strcat(tmp1," ");
        strcat(tmp1,tmp2);
        strcpy(full_name,tmp1);
        strcat(in,full_name);
        ////////// End of input scanning and parsing
        insert_into_hashtable(in,value,full_name);
    }
    end=clock();
    cpu_time_used = ((double) (end - start)) /(double) CLOCKS_PER_SEC;
    printf("Number of clashes: %d, %d shifting performed\n",num_clash,num_shift);
    //printList(&storage[clash_max_idx]);
    printf("Time used to map the value: %.8lf\n",cpu_time_used);
    ////////// End of Setting the initial hashtable


    ////////// Start of Query testing area

    ////////// Start of I/O redirection for automation testing
    // Comment all these lines below if you want to test it manually
    freopen("Random_fail_query_generated_new.txt","r",stdin);
    //freopen("Random_success_query_generated_new.txt","r",stdin);
    ////////// End of I/O redirection for automation testing

    scanf("%d",&n);
    start=clock();
    for(x=0;x<n;x++)
    {
        scanf("%s %s %s",in,tmp1,tmp2);
        strcat(tmp1," ");
        strcat(tmp1,tmp2);
        strcpy(full_name,tmp1);
        strcat(in,full_name);
        search_in_hashtable(in);
    }
    end=clock();
    cpu_time_used = ((double) (end - start)) /(double) CLOCKS_PER_SEC;
    ////////// End of Query testing area


    ////////// Summary
    printf("%d queries performed and %d comparison performed in total\n",n,cmp_total);
    printf("Time used to finish all queries: %.8lf\n",cpu_time_used);
    return 0;
}