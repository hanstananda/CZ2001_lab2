#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//////////////////////// hash function ///////////////////////////////////////////

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

//////////////////////// LinkedList, based on CZ1007 /////////////////////////////

typedef struct _listnode
{
    char key[100];
    char name[100];
    int item;
    struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You may use the following functions or you may write your own
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
ListNode *search_key_in_Node(LinkedList *ll, char *key, int *num_of_comparison);
int insertNode(LinkedList *ll, int index,char* key, int value,char* name);
int removeNode(LinkedList *ll, int index);

//////////////////////// HashTable FUNCTIONS ///////////////////////////////////////////

#define hashtable_size 1<<16

LinkedList storage[hashtable_size];
void hashtable_init()
{
    int x;
    for(x=0;x<hashtable_size;x++)
    {
        storage[x].head = NULL;
        storage[x].size = 0;
    }
}

// Clash checking init, use if needed
int clash_max=0,clash_max_idx=0,num_clash=0;

void insert_into_hashtable(char *key,int data1,char* data2)
{
    int hashed_value=bsdChecksumFromstr(key);
    //printf("hashed into: %d\n",hashed_value); // for debug only
    LinkedList *ll = &storage[hashed_value];
    //printf("\"%s\"",in); // for debug only


    ////////// Start of Clash checking, use if needed
    if(ll->size>0)
    {
        //printf("clash %d!\n",ll->size);
        num_clash++;
        if(clash_max<ll->size)
        {
            clash_max=ll->size;
            clash_max_idx=hashed_value;
        }
    }
    ////////// End of Clash checking


    int insert_status=insertNode(ll,ll->size,&key[0],data1,data2);
    // Error occured
    if(insert_status==-1)
    {
        printf("Caution: Insert Fail!\n");
    }
}

int cmp_total=0;
void search_in_hashtable(char * key)
{
    int hashed_value=bsdChecksumFromstr(key);
    int cmp_num=0;
    LinkedList *ll = &storage[hashed_value];
    ListNode *tmp = search_key_in_Node(ll, key, &cmp_num);
    if(tmp!=NULL)
    {
        printf("%s is found with value of %d\n",tmp->name,tmp->item);
        printf("%d comparison performed\n",cmp_num);
    }
    else
    {
        printf("not found!\n",key);
        printf("%d comparison performed\n",cmp_num);
    }
    cmp_total+=cmp_num;
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
    strcat(outfilename," closed address hashing output.txt");
}


//////////////////////// MAIN FUNCTION ///////////////////////////////////////////


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
    printf("Number of clashes: %d, no of items: %d\n",num_clash,n);
	//printList(&storage[clash_max_idx]);
	printf("Time used to map the value: %.8lf\n",cpu_time_used);
    ////////// End of Setting the initial hashtable


    ////////// Start of Query testing area

    ////////// Start of I/O redirection for automation testing
    // Comment all these lines below if you want to test it manually
	freopen("Random_fail_query_generated_new.txt","r",stdin);
	//freopen("Random_fail_query_generated_new.txt","r",stdin);
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


//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

    ListNode *cur;
    if (ll == NULL)
        return;
    cur = ll->head;
    if (cur == NULL)
        printf("Empty");
    while (cur != NULL)
    {
        printf("%d,%s\n", cur->item,cur->name);
        cur = cur->next;
    }
    printf("\n");
}


void removeAllItems(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL){
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ll->head = NULL;
    ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

    ListNode *temp;

    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;

    temp = ll->head;

    if (temp == NULL || index < 0)
        return NULL;

    while (index > 0){
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

ListNode *search_key_in_Node(LinkedList *ll, char *name, int *num_of_comparison)
{
	ListNode *temp;

    if (ll == NULL)
    {
    	(*num_of_comparison)++;
    	return NULL;
	}
    temp = ll->head;	
    do {
        (*num_of_comparison)++;
		if (temp == NULL)
            return NULL;
        if(strcmp(temp->key,name)==0)
        {
        	return temp;
		}
		temp = temp->next;
    }while(temp!=NULL );
    return temp;
}

int insertNode(LinkedList *ll, int index,char* key, int value,char* name){

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
        strcpy(ll->head->key,key);
        strcpy(ll->head->name,name);
        ll->head->next = cur;
        ll->size++;
        return 0;
    }

    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL){
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        strcpy(pre->next->key,key);
        strcpy(pre->next->name,name);
        pre->next->next = cur;
        ll->size++;
        return 0;
    }

    return -1;
}


int removeNode(LinkedList *ll, int index){

    ListNode *pre, *cur;

    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;

    // If removing first node, need to update head pointer
    if (index == 0){
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--;

        return 0;
    }

    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL){

        if (pre->next == NULL)
            return -1;

        cur = pre->next;
        pre->next = cur->next;
        free(cur);
        ll->size--;
        return 0;
    }

    return -1;
}

