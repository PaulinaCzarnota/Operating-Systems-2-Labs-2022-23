/*
    Program that uses an array with function and subcript notation to display the sum of the contents of the array, he max value in the array and the max value in the array.
*/


#include <stdio.h>

int sumofarray(int a[], int n)
{
 	int min, max, i;

 	min = max = a[0];

    for(i = 1; i < n; i++)
    {
        if(min > a[i])
		min = a[i];

            if(max < a[i])
		    max = a[i];       
    }
    
    printf("Minimum of array is: %d\n", min);
    printf("Maximum of array is: %d", max);
}

int main()
{
    int a[10], i, n, sum;
   
    printf("Enter size of the array: ");
    scanf("%d", &n);
 
    printf("Enter elements in array: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    sumofarray(a, n);
}
