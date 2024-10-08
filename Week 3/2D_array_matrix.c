/*
    Program that uses a 2D array to display its contents and the addresses of its elements.
*/

#include <stdio.h>

int main()
{
    // 2D array declaration
    int display[4][3];

    // Counter variables for the loop
    int i, j;

    for(i = 0; i < 4; i++) 
    {
        for(j = 0; j < 3; j++) 
        {
            printf("\nEnter value for display [%d][%d]: ", i, j);
            scanf("%d", &display[i][j]);
        }
    }

    // Displaying array elements
    printf("\nTwo Dimensional array elements: \n\n");

    for(i = 0; i < 4; i++) 
    {
        for(j = 0; j < 3; j++) 
        {
            printf("%d ", display[i][j]);

            if(j == 2)
            {
                printf("\n\n");
            }

        }
    }

    return 0;
}
