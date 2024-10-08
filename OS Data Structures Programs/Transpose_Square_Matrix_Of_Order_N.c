#include<stdio.h>

int main()
{
 int i,j,n;
 float a[10][10], tmp;
 clrscr();
 printf("Enter order of matrix:\n");
 scanf("%d", &n);
 printf("Enter matrix elements:\n");
 for(i=0;i< n;i++)
 {
  for(j=0;j< n;j++)
  {
   printf("a[%d][%d]=",i,j);
   scanf("%f", &a[i][j]);
  }
 }
 for(i=0;i< n-1;i++)
 {
  for(j=i+1;j< n;j++)
  {
   tmp = a[i][j];
   a[i][j] = a[j][i];
   a[j][i] = tmp;
  }
 }
 printf("Transposed matrix is:\n");
 for(i=0;i< n;i++)
 {
  for(j=0;j< n;j++)
  {
   printf("%f\t", a[i][j]);
  }
  printf("\n");
 }
 return 0;
}