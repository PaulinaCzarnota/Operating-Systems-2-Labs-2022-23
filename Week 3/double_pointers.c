/*
    Program that displays memory locations with double pointers.
*/

#include<stdio.h>

void main()
{
    
    int i = 3;
    int *j;   //pointer to integer
    int **k;  // pointer to pointer (double indirection)
    
    // assign value to pointer and double pointer
    j = &i;
    k = &j;
    
    // ouput results  
    
    printf("The value of i is %d\n", i);
    printf("The value of j is %p\n", j);
    printf ("The value of k is %p\n\n", k);
    
    // using indirection to get value of i;
    
    printf("The value of i is %d\n", i);
    printf("The value of *j is %d\n", *j);
    printf("The value of *k is %p\n", *k);
    printf("The value of *k is %d\n", *k);    
    printf("The value of **k is %d\n", **k); 
    
    // keep exec window open
    getchar();
}
      