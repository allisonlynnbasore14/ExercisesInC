#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumArray(int *array , int size){
  int sum = 0;
  int i;
  for(i=0;i<size;i++){
    sum = sum + array[i];
  }
  return sum;
}


int main(){
  int i;
  int size = 5;
  int array[size];
  for (i=0; i<size; i++) {
      array[i] = 3;
  }


  char *text = calloc(1,1), buffer[10];
  printf("Enter a message: \n");
  while( fgets(buffer, 10 , stdin) ) /* break with ^D or ^Z */
  {
    text = realloc( text, strlen(text)+1+strlen(buffer) );
    //if( !text ) ... /* error handling */
    strcat( text, buffer ); /* note a '\n' is appended here everytime */
    printf("%s\n", buffer);
  }
  printf("\ntext:\n%s",text);

  // char buf[10];
  // fgets(buf, 10, stdin);
  // printf("string is: %s\n", buf);
  int sum = sumArray(array, size);
  printf("%d\n", sum);
  return 0;
}
