#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strsplit(char *str, char sep, char*first, char*second){
  // char *ret;
  // ret = memchr(str, sep, strlen(str)); // location of seperation character

  char *ret;
  ret = strchr(str, sep);// pointer to first occerance of seperation character

  int si = 0;
  while(str[si]!=sep){
    first[si] = str[si];
    si++;
  }
  printf("%d\n", si);
  while(str[si]!='\0'){
    second[si] = str[si];
    si++;
  }

}



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
  char *a = "HellorWorld";
  char s = 'r';
  char *first =(char*)malloc(sizeof(char)*10);
  char *second =(char*)malloc(sizeof(char)*10);

  // int val = endsWith(a, b);
  strsplit(a, s,  first, second);
  printf("%s\n", first);
  printf("%s\n", second);
  return 0;
}
