/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

/*
  The function below illistrate what happens when you try to return a pointer
  to a stack allocated array.

  The functions themselfs are intended to fill an array in two different ways.
  The first function, foo, fills an array of size 5 with the number 42
  and returns a pointer to the array.

  The second function, bar, fills an array with each of its indices;
  i.e. array[3] = 3;

  The main function calls both and prints which ever successful changes the
  local array variable.

  However, running this file gives a warning message. The warning was that an
  address of stack memory associated with local variable array was being
  returned from a function.
  I believe this warning means that since "array" is part of the foo function
  stack. When the function exits that memory is released, so the memory pointer
  to "array" will probably point to something that we did not intend it to be
  pointing at.

  When I ran it and compiling it, it did not give me a Segmentation Error.
  Instead it printed stange output for the values in the array.

  The problem:
  The pointer the main function was referencing for "array" (which was returned
  by the foo function) was no longer pointing to anything we actually cared
  about. That memory was released from holding actual values when the foo
  function returned and the array pointer became useless. This is what the
  warning was referencing.s

  After printing out the addresses of the two function's "array" variables,
  it showed that both functions, foo and bar, are referencing the same address
  for "array" becuase the first function's memory had already been reallocated
  after it returned and the second function had used the same memory.

*/


#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
