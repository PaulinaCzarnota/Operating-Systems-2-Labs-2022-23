#include <stdio.h>

#define SIZE 3
 
int main()
{
    int m=SIZE, n=SIZE, p=SIZE, q=SIZE, c, d, k;
    int sum = 0;
    int first[SIZE][SIZE], second[SIZE][SIZE], addition[SIZE][SIZE], multiply[SIZE][SIZE];
  
 
    printf("Enter the elements of first matrix\n");
 
    for (c = 0; c < m; c++)
        for (d = 0; d < n; d++)
        {
            printf("Enter the value for row %d and col %d: ", c, d);	
            scanf("%d", & first[c][d]);
        }

    printf("Enter the elements of second matrix\n");
 
    for (c = 0; c < p; c++)
      for (d = 0; d < q; d++)
        {
            printf("Enter the value for row %d and col %d: ", c, d);
            scanf("%d", & second[c][d]);
        }

    for (c = 0; c < m; c++) 
    {
      for (d = 0; d < q; d++) 
      {
        addition[c][d] = first[c][d] + second[c][d];
      }
    }
	
	printf("The values of matrix 1:-\n");
 
    for (c = 0; c < m; c++) 
    {
      for (d = 0; d < q; d++)

        printf("%d\t", first[c][d]);
        printf("\n");
    }
	
	printf("The values of the matrix 2:-\n");
 
    for (c = 0; c < m; c++) 
    {
      for (d = 0; d < q; d++)
      
        printf("%d\t", second[c][d]);
        printf("\n");
    }

    for (c = 0; c < m; c++) 
    {
      for (d = 0; d < q; d++)
      {
        for (k = 0; k < p; k++)
        { 
        
          sum = sum + first[c][k] * second[k][d];
        }

        multiply[c][d] = sum;
        sum = 0;
      }
    }

    printf("The product of the 2 matrices:-\n");

    for (c = 0; c < m; c++) 
    {
        for (d = 0; d < q; d++)
        printf("%d\t", multiply[c][d]);
        printf("\n");
    }

  return 0;
}
