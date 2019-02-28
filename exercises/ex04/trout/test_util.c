

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "util.h"
#include "../minunit.h"

int tests_run = 0;
#define TESTONE "First\0"


int compareS(char str1[], char str2[])
{
    int pos=0;
    while(str1[pos]==str2[pos]){
      if(str1[pos]=='\0'||str2[pos]=='\0'){
        break;
      }
      pos++;
    }
    if(str1[pos]=='\0' && str2[pos]=='\0'){
        return 1;
    }else{
        return 0;
    }
}

static char *test1() {
    int res;
    int fd;
    char buf[sizeof(char)*20];
    printf("%s %s\n", "Please type:", TESTONE);
    ssize_t y = Read(0, buf, 5);// 0 is for standand input
    res = compareS(buf, TESTONE);
    char *message = "test1 failed";
    mu_assert(message, res);
    return NULL;
}

static char *test2() {
    int res = 0;
    char buf[sizeof(char)*20];
    ssize_t y = Read(2, buf, 5);
    if(y != -1){
      res = 1;
    }
    char *message = "test2 failed";
    mu_assert(message, res);
    return NULL;
}

static char *test3() {
    // int res = endswith("endswith", "offendswith");
    // char *message = "test3 failed: endswith(\"offendswith\", \"swith\") should return 0";
    // mu_assert(message, res == 0);
    return NULL;
}

static char * testReadFunc() {
    mu_run_test(test1);
    mu_run_test(test2);
    return NULL;
}


int main(int argc, char **argv) {
    char *result =  testReadFunc();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
