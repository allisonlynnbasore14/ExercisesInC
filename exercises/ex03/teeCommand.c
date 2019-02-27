#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 200
#define MAX_ARG_SIZE 80


/*
Answers to Questions:

3) Reflect: what worked, what slowed you down?  What would you do differently next time?

To start I wrote down all the components I would need to make it the tee function. At first it seemed like a daunting task, but after writing down all the functionality, the job seemed more doable. Then I consulted Head First C regularly. The most recent chapter pretty much covered all the functionality I needed to know to make the tee command.

It worked really well for me to test incrementally, which is generally what I have been doing in this class. It also helped to find a couple good examples of reading the stdin and writing to files on stackoverflow. Overall nothing really took that long. I had to run the tee command a couple times to get a better understanding of what it dose and I could have done that sooner.

Next time, I wan't to spend less time googling examples and instead try to think through it myself first.


4) Compare your solution to professional code.

I see two major difference between the professional work and my code. They have tons more error checking. I am assuming almost every error case is covered with their code while you could easily break mine. Also the professional code set a lot more constants before jumping into the actual program as to not violate the DRY principle and to make their code more readable. This was necessary because they had a ton more options becuase of the error checking.

*/

/* Pips the stdin input to a specified file and to the standard output

   Command Line Arguments: files to write to

   Command Line Options:
      -a: append to files instead of overwritting

*/

int main(int argc, char *argv[]){
   int append = 0; //Defaults to overwritting
   char inputVal[MAX_ARG_SIZE];
   char totalVal[MAX_SIZE];

   char *value = "";
   int count;
   char ch;
   while ((ch = getopt(argc, argv, "a")) != EOF){
     printf("CH IS %c\n", ch);
     switch(ch){
       case 'a':
          append = 1;
          break;
       default:
          fprintf(stderr, "Unknown option: '%s'\n", optarg);
          return 1;
     }
   }

   argc -= optind;
   argv += optind;
   FILE *file;

   while (fgets(inputVal, sizeof(inputVal), stdin) != NULL) {
     printf("%s", inputVal);
     strcat(totalVal, inputVal);
   }


   for (count = 0; count< argc ; count++){
     // for all the files listed, print the value
     if(!append){
       file = fopen( argv[count], "w");
       fprintf(file, "%s\n", totalVal);
     }else{
       file = fopen( argv[count], "a");
       fprintf(file, "%s\n", totalVal);
     }
   }
    return 0;
}
