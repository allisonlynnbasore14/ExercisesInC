#include <stdio.h>


int newFunc(){
  return 3 + 4;
}

int main() {
    int x = 5;
    // int y = x + 1;
    // printf("%i\n",y);
    int a = 3;
    int b = 4;
    int c = a + b;
    printf("c is %d\n", c);

    if (c%2 == 0) {
        printf("c is even\n");
    } else {
        printf("c is odd\n");
    }

    int val = newFunc();

    return 0;
}



/*
  Optimization using -O2:
    In these experiments, the -O2 optimization was run with the main() function
    along with running th e main() function without any optimization. Using the
    -O2 optimization appeared to less of the 'movl' command than without
    optimization.
    Next, the main() function was run with the two lines shown uncommented.
    This causes the unoptimized function's assembly code to become more verbose
    with 'movl' commands. The increase to the O2 optimization did not increase
    significantly.
    I believe the O2 optimization combined the x, 1, and y without having to
<<<<<<< HEAD
    save them in seperate registers. Therefore, with the optimization it will
    take less space and time to calcuate and print y.
=======
    save them in separate registers. Therefore, with the optimization it will
    take less space and time to calculate and print y.

>>>>>>> d4654b4b0aa7310238c473a4eee41ee48766c4fb
*/
