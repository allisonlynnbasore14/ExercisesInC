
/*
  Adding User Input Values

  The user inputs number values
  After the user is done inputing values, the sum of values is calculated

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 11


/*Sums the interger contents of the given array

  For each value in the given array refernce, the value of sum is totaled

  *array: a refernce to the array to be summed
*/

int sumArray(int *array){
  int sum = 0;
  int i;
  for(i=0;i<SIZE;i++){
    sum = sum + array[i];
  }
  return sum;
}

/*Prints an error of a given type

  For the errortype, prints a specific message for the user

  errorType: the type of error (1,2, or 3)
*/

void printError(int errorType){

  switch(errorType){
    case 1:
      printf("Sorry, that input is too large. Try something smaller.\n");
      break;
    case 2:
      printf("Sorry that input is invalid, please enter a non-zero integer.\n");
      break;
    case 3:
      printf("That is all the numbers we have space for!\n");
      break;
    default:
      printf("Sorry that dosen't work. Try again or press Control + D\n");
  }
}

/*Sums the values of user inputed numbers

  Stores user inputed values in an array
  prints errors if wrong type, too many inputs, or too large of an input
  Sums the array

*/


int main(){
  int arrIndex = 0;
  int arr[SIZE];
  char inBuffer[10];
  printf("Please enter your numbers to be added: \n");
  while(fgets(inBuffer, sizeof(inBuffer), stdin))
  {
    int val = atoi(inBuffer);
    if(strchr(inBuffer, '\n') == NULL){
      int c;
      while((c = getc(stdin)) != '\n' && c != EOF);
      printError(1);
    }else if(val == 0){
      printError(2);
    }else{
      arr[arrIndex] = val;
      arrIndex++;
    }
    if(arrIndex == (sizeof(arr)/sizeof(int))-1){
      printError(3);
      break;
    }

  }
  int sum = sumArray(arr);
  printf("Here is your sum: %d\n", sum);
  return 0;
}
