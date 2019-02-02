/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);

    //Checking that malloc grows up
    void *k = malloc(20);
    printf ("k points to %p\n", k );

    //checking that a variable grows down
    int var3 = 100;
    printf("Address of var 3 is %p\n", &var3);

    //Allocating two memory chunch of: 10 and 22
    void *a = malloc(10);
    void *b = malloc(22);
    printf("Memory of 10 is at %p\n", a);
    printf("Memory of 22 is at %p\n", b);

    return 0;
}
