/* Code from Head First C.

Modified by Allen Downey.

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

int listener_d = 0;


/* Print an error message and exit.
*/
void perror_exit(char *s)
{
    perror(s);
    exit(-1);
}


/* Call malloc and exit if it fails.
*/
void *check_malloc(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        perror_exit("malloc failed");
    }
    return p;
}

/* Print an error message and exit.
*/
void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/* Set up the signal catcher.
*/
int catch_signal(int sig, void (*handler)(int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

/* Signal handler for SHUTDOWN
*/
void handle_shutdown(int sig) {
    if (listener_d)
        close(listener_d);

    fprintf(stderr, "Bye!\n");
    exit(EXIT_SUCCESS);
}

/* Create the listener socket.
*/
int open_listener_socket(void) {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
    error("Can't open listener socket");
    return s;
}

/* Wait for clients to connect.
*/
int open_client_socket(void) {
    static struct sockaddr_storage client_address;
    static unsigned int address_size = sizeof(client_address);
    int s;

    if ((s = accept(listener_d, (struct sockaddr *)&client_address,
    &address_size)) == -1)
    error("Can't open client socket");

    return s;
}

/* Bind the socket to a port.
*/
void bind_to_port(int socket, int port) {
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;

    int res = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR,
                         (char *)&reuse, sizeof(int));
    if (res == -1)
        error("Can't set the 'reuse' option on the socket");

    res = bind(socket, (struct sockaddr *)&name, sizeof(name));
    if (res == -1)
        error("Can't bind to socket");
}

//
// /* Structure that contains variables shared between threads.
// */
// typedef struct {
//     int connect_d;
//     int listener_d;
//     char *buf;
// } Shared;
//
// /* Allocate the shared structure.
// */
// Shared *make_shared(char *buf, int listener_d)
// {
//     Shared *shared = check_malloc(sizeof(Shared));
//     shared->connect_d =  open_client_socket();
//     shared->listener_d = listener_d;
//     shared->buf = buf;
//     return shared;
// }


/* Send to the client.
*/
int say(int socket, char *s)
{
    int res = send(socket, s, strlen(s), 0);
    if (res == -1)
        error("Error talking to the client");
    raise(SIGSEGV);
    return res;
}


/* Read from the client.

Returns: number of characters read.
*/
int read_in(int socket, char *buf, int len)
{
    /* treat the socket stream as a regular IO stream,
    so we can do character IO */
    FILE *fp = fdopen(socket, "r");
    int i = 0, ch;

    /* eat any leading whitespace */
    while (isspace(ch = fgetc(fp)) && ch != EOF) {
        // do nothing
    }

    if (ferror(fp))
        error("fgetc");

    while (ch != '\n' && ch != EOF) {
        if (i < len)
        buf[i++] = ch;
        ch = fgetc(fp);
    }
    if (ferror(fp))
        error("fgetc");

    /* terminate the string, eating any trailing whitespace */
    while (isspace(buf[--i])) {
        buf[i] = '\0';
    }

    return strlen(buf);
}

char intro_msg[] = "Internet Knock-Knock Protocol Server\nKnock, knock.\n";


void *child_code(void*arg){
  char buf[255];

  int connect_d = (long) arg;

  // close(listener_d);
  printf("%d\n", connect_d);
  read_in(connect_d, buf, sizeof(buf));
  printf("%s\n", "AT CHILD");
  if (say(connect_d, "Surrealist giraffe.\n") == -1) {
      close(connect_d);
      return;
  }

  read_in(connect_d, buf, sizeof(buf));

  if (say(connect_d, "Bathtub full of brightly-colored machine tools.\n") == -1) {
      close(connect_d);
      return;
  }
  close(connect_d);

}

// void *entry(void *arg)
// {
//     child_code(arg);
//     pthread_exit(NULL);
// }

int main(int argc, char *argv[])
{
    // char buf[255];
    printf("%s\n", "AT 1");

    // set up the signal handler
    if (catch_signal(SIGINT, handle_shutdown) == -1)
        error("Setting interrupt handler");
    printf("%s\n", "AT 2");
    // create the listening socket
    int port = 30000;
    listener_d = open_listener_socket();
    bind_to_port(listener_d, port);

    if (listen(listener_d, 10) == -1)
        error("Can't listen");
    printf("%s\n", "AT 3  ");


    while (1) {
        printf("Waiting for connection on port %d\n", port);
        long connect_d = open_client_socket();

          //Shared *shared = make_shared(buf, listener_d);
        if (say(connect_d, intro_msg) == -1) {
            close(connect_d);
            continue;
        }

        int ret;
        pthread_t thread;

        printf("%s\n", "AT PARENT");
        ret = pthread_create(&thread, NULL, child_code, (void *) connect_d);
        if (ret != 0) {
            perror_exit("pthread_create failed");
        }
    }
    return 0;
}
