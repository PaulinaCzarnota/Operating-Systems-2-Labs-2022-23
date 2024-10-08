/* 	
	A program to illustrate using an array of strings.
	The program that stores the months of the year in an array, then displays them to the user and displays the addresses stored in each element of the array. 

*/


#include <stdio.h>

void main()
{
	// Define an array of strings 
	char *months[12] = {"January", "February", "March", "April", "May", "June",
						"July", "August", "September", "October", "November",
						"December"};

	int i;

	// Display the months of the year using subscripts
	printf("\nThe months of the year are: \n\n");
	
	for(i = 0; i< 12; i++)
    {
	    printf("%s\n", months[i]);
    }
    
    // Display the months of the year using pointer arithmetic 
	printf("\nThe addresses of each element of the months array are: \n\n");
	
	for(i = 0; i< 12; i++)
    {
        printf("%p\n", *(months + i));
    }

    printf("\nThe address stored in each element of the year are: \n\n");

	for(i = 0; i< 12; i++)
    {
        printf("%p\n", i, months + i);
    }
}
