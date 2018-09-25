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

// COPIED FROM CZ1007

typedef struct _listnode
{
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
ListNode *search_name_in_Node(LinkedList *ll,char* name,int* num_of_comparison);
int insertNode(LinkedList *ll, int index, int value,char* name);
int removeNode(LinkedList *ll, int index);

int hashtable_size = 1<<16;

//////////////////////// MAIN FUNCTION ///////////////////////////////////////////

int main() {
	freopen("Random_tc_generated_load75%.txt","r",stdin); 
 	//freopen("out.txt","w",stdout);
	freopen("out1.txt","w",stdout);
	srand(time(NULL));
	int value;
    char in[100];
    char tmp1[50],tmp2[50];
    int n;
    scanf("%d",&n);
    LinkedList storage[hashtable_size];
    int x;
	for(x=0;x<hashtable_size;x++)
    {
        storage[x].head = NULL;
        storage[x].size = 0;
    }
    clock_t start,end;
    double cpu_time_used;
    int debug=0;
    int clash_check[hashtable_size],clash_max=0,clash_max_idx=0;
    start=clock();
    for(x=0;x<n;x++)
    {
        scanf("%s %s %d",tmp1,tmp2,&value);
        strcat(tmp1," ");
        strcat(tmp1,tmp2);
        strcpy(in,tmp1);
        int hashed_value=bsdChecksumFromstr(in);
        //printf("hashed into: %d\n",hashed_value);
        LinkedList *ll = &storage[hashed_value];
        //printf("\"%s\"",in);
        /*clash_check[hashed_value]=clash_check[hashed_value]+1;
        if(ll->size>0)
        {
        	//printf("clash %d!\n",ll->size);
        	if(clash_max<ll->size)
			{
				clash_max=ll->size;
				clash_max_idx=hashed_value;
			}
		}*/
        int insert_status=insertNode(ll,ll->size,value,&in[0]);
        if(insert_status==-1)
        {
        	printf("Insert Fail!\n");
		}
    }
	end=clock();
	cpu_time_used = ((double) (end - start)) /(double) CLOCKS_PER_SEC;
	//printList(&storage[clash_max_idx]);
	printf("Time used to map the value: %.8lf\n",cpu_time_used);
	
	// Query testing area
	freopen("Random_fail_query_generated.txt","r",stdin); 
	//freopen("Random_query_generated.txt","r",stdin); 
	scanf("%d",&n);
	start=clock();
	int cmp_total=0;
	for(x=0;x<n;x++)
    {
        scanf("%s %s",tmp1,tmp2);
        strcat(tmp1," ");
        strcat(tmp1,tmp2);
        strcpy(in,tmp1);
        int hashed_value=bsdChecksumFromstr(in);
        // Search dummy
        int cmp_num=0;
        LinkedList *ll = &storage[hashed_value];
		ListNode *tmp = search_name_in_Node(ll,in,&cmp_num);
        if(tmp!=NULL)
        {
        	printf("%s is found with value of %d\n",tmp->name,tmp->item);
        	printf("%d comparison performed\n",cmp_num);
		}
		else
		{
			printf("%s is not found!\n",in);
			printf("%d comparison performed\n",cmp_num);
		}
		cmp_total+=cmp_num;
		//printList(&storage[hashed_value]);
        
    }
	end=clock();
	cpu_time_used = ((double) (end - start)) /(double) CLOCKS_PER_SEC;
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

ListNode *search_name_in_Node(LinkedList *ll,char* name,int* num_of_comparison)
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
        if(strcmp(temp->name,name)==0)
        {
        	return temp;
		}
		temp = temp->next;
    }while(temp!=NULL );
    return temp;
}

int insertNode(LinkedList *ll, int index, int value,char* name){

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
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

