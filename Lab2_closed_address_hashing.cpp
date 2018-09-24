#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bsdChecksumFromstr(char *input) /* The file handle for input data */
{
    int checksum = 0;             /* The checksum mod 2^16. */

    for (int x=0;x<strlen(input);x++) {
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
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

int hashtable_size = 1<<16;

int main() {
	int value;
    char in[100];
    int n;
    scanf("%d",&n);
    LinkedList storage[hashtable_size];
    for(int x=0;x<n;x++)
    {
        storage[x].head = NULL;
        storage[x].size = 0;
    }
    
    int len_input;
    for(int x=0;x<n;x++)
    {
        scanf("%s %d",in,value);
        len_input=strlen(in);
        int hashed_value=bsdChecksumFromstr(in);
        LinkedList ll = storage[hashed_value];
        insertNode(&ll,ll.size,value);
    }

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
        printf("%d ", cur->item);
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

int insertNode(LinkedList *ll, int index, int value){

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
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

