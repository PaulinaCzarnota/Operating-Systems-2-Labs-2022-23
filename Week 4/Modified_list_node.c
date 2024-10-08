#include <stdio.h>
#include <stdlib.h>


// self-referential structure                       
struct listNode {                                      
   char data; 
   struct listNode *nextPtr; // pointer to next node
}; typedef struct listNode ListNode; // synonym for struct listNode


int main(void)
{ 
//   ListNode* startPtr = NULL; // initially there are no nodes
   
	char value;
	
   
   // create a node and add data to the node
   ListNode* newPtr = malloc(sizeof(ListNode)); // create node
   
   // enter a character
	printf("enter a character: ");
	scanf("%c",&value);
   
   
   // if nodes is created assign values to node
   
   if(newPtr != NULL)
   {
	   newPtr->data = value;	  
	   newPtr->nextPtr = NULL; // node does not link to another node
   }
	  

	// ***********************************print contents of node **********************************************
	  
	printf("the contents of the node: \n");
	printf("data ID is: %d\n",newPtr->data);
	printf("the pointer element points to %p", newPtr->nextPtr);
   
    printf("the address of the node is: %p\n", newPtr);
	printf("the address of newPtr (the variable that stores the location of the node is): %p\n", &newPtr); 
   
	return 0;
	
} 

