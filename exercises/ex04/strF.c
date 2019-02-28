
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* strf(char* string, char* letters){
  int len1 = sizeof(string);
  char* output = (char*)malloc(sizeof(char)*len1);
  int pos = 0;
  int i;
  char* pPosition;
  for(i = 0; i< len1;i++){
    pPosition = strchr(letters, string[i]);
    if(pPosition != NULL){
      output[pos] = string[i];
      pos++;
    }
  }
  return output;
}

int main (int argc, char *argv[]){
    char string[] = "equation";
    char letters[] = "aeiou";
    char* out;
    out = strf(string, letters);
    printf("%s\n", out);
    return 1;
}


// double array[] = {1.2, 2.718, 3.14159, 5.6};
// double expected_int[] = {1, 2, 3, 5};
// double expected_frac[] = {0.2, 0.718, 0.14159, 0.6};
// double *frac_part;
// int length = sizeof(array) / sizeof(double);
//
// double *int_part = get_both_parts(array, length, &frac_part);
//
// for (int i=0; i<length; i++) {
//     printf("%.18lf  %.18lf\n", int_part[i], expected_int[i]);
//     printf("%.18lf  %.18lf\n", frac_part[i], expected_frac[i]);
//     assert(int_part[i] == expected_int[i]);
//     assert(frac_part[i] == expected_frac[i]);
// }
