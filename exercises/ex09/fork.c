/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>



/*
The parents and children have their own versions of global variables. The same was true for local variables.
  I tested this by making a global variable and changing it in both the child and parent code.

They do not have the same stack or heap space.
  I tested this by modifing a pointer in both the child and parent and saw that a change in one did not change the other.


*/



// errno is an external global variable that contains
// error information
extern int errno;
int testVar;


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i, int*p)
{
    sleep(i);
    testVar = 1;
    printf("Hello from child %d.\n", i);
    *p = 25;//Write
    printf("Child %d: %d %p\n", getpid(), *p, p);//Read
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    int *p = (int*)malloc(sizeof(int));

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i, p);
            exit(i);
        }
    }

    /* parent continues */

    printf("Hello from the parent.\n");
    *p = 15;//write
    printf("Parent %d: %d %p\n", getpid(), *p, p);//read

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);
    printf("%d\n", testVar);
    exit(0);

}
