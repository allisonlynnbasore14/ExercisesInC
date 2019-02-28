#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Write a function called get_int_part that takes as parameters an array of doubles and the
// integer number of elements in the array. It should allocate an array of doubles the same size
// as the input, and then use modf to compute the integer part of each element in the array,
// storing the result in the new array, and then returning the new array.
// For example, if the inputs are the array {2.718, 3.142} and the integer 2, the output
// should be the new array {2.0, 3.0}.
// Note: you must use modf even though you could do the same thing with a type cast.
//

double* get_int_part(double *array, int len){
  double* doubles = (double*)malloc(sizeof(double)*len);
  int pos;
  double fractpart, intpart;
  for(pos = 0; pos<len;pos++){
    fractpart = modf(array[pos], &intpart);
    doubles[pos] = intpart;
    printf("Integral part = %lf\n", intpart);
  }

  return doubles;
}

int main (int argc, char *argv[]){
  double array[] = {1.2, 2.718, 3.1412, 5.6};
  double expected[] = {1, 2, 3, 5};
  int length = sizeof(array) / sizeof(double);

  double *int_part = get_int_part(array, length);
}
