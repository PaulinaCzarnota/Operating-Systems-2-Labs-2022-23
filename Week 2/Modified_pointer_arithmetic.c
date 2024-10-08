/* 
  Program to print each character of the string “this is a new message” on a new line using a pointer variable and to determine the length of a string.
*/

#include <stdio.h>

int string_ln(char*);

int  main()
{
    char str[20];
    int length;
    char *p = "this is a new message"; // p points to first character

    printf("Enter the string: ");
    scanf("%s",str);

    length = string_ln(str);
    printf("\nThe length of the given string [ %s ] is : %d\n", str, length);
  
    getchar();  

    return 0; 
}

int string_ln(char*p) /* p=&str[0] */
{
    int count = 0;

    // The next while loop is performed until p points to the null character ‘\0’ at the end of the string 
    while ( *p != '\0' )
    {
	    printf("%c\t The value of p: the variable pointer is %p \n", *p, p); 
        // print each character in string 
	    p++;  // p now points to next character 
        count++;
    }    
        
    return count;
}