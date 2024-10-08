/* 
  Program to access the elements of an array using element addresses rather than subscripts.      
*/

#include <stdio.h>
#define NO_OF_ELS 5

int main()
{
  int a[NO_OF_ELS] = { 10, 13, 15, 11, 6 };
  int i;

  printf("\nThe contents of the array name is %p\n", a);
 
  for ( i = 0; i < NO_OF_ELS; i++ ) 
  { 	
    printf("Element %d is %d\n", i, *(a+i));
    printf("The address of the element is: %p\n\n", a+i);
  } 
  
  return 0; // to indicate the end of the program	
}
