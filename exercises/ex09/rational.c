/* Example code for Exercises in C.

Copyright 2019 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num, den;
} Rational;

/* Make a rational.
*/
Rational *make_rational(int num, int den) {
    Rational *rational = malloc(sizeof(rational));
    rational->num = num;
    rational->den = den;
    return rational;
}


/* Print a rational.
*/
void print_rational(Rational *rational) {
    printf("%d/%d\n", rational->num, rational->den);
}


/* Sort rows in ascending order by floating-point approximation.
*/
// TODO: write this function
int compRat(const void*a, const void*b){
  return(-1 * *(int*)a - *(int*)b );
}

/* Comparator function for sorting rationals.
*/
// TODO: write this function
void sort_rationals(Rational *rat_array[], int n){

  qsort(rat_array, n, sizeof(Rational), compRat);
}




int main () {
    int n = 5;
    Rational *rat_array[n];

    rat_array[2] = make_rational(1, 2);
    rat_array[3] = make_rational(2, 3);
    rat_array[1] = make_rational(3, 4);
    rat_array[0] = make_rational(8, 9);
    rat_array[4] = make_rational(5, 9);

    for (int i=0; i<n; i++) {
        print_rational(rat_array[i]);
    }

    printf("sorting...\n");
    sort_rationals(rat_array, n);

    for (int i=0; i<n; i++) {
        print_rational(rat_array[i]);
    }

}
