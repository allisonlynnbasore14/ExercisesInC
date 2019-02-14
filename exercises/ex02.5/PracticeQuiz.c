#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int endsWith(char *str, char *suffix){
  int lenSuff = strlen(suffix);
  int lenStr = strlen(str);
  if(lenStr<lenSuff){
    return 0;
  }
  char *strEnd = (char*) malloc(sizeof(char)*lenSuff);
  strncpy(strEnd, str+(lenStr-lenSuff), lenSuff);//str+(lenStr-lenSuff-1), lenStr-1);
  int val = strcmp(strEnd, suffix);

  if(val == 0){
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]){
  char *a = "TH";
  char *b = "right";
  int val = endsWith(a, b);
  printf("%d\n", val);
  return 0;
}
