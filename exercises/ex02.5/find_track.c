/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

/*
  Searches a string for a given regex pattern
  string[]: an array of characters to be searched
  pattern[]: an array of characters that has a pattern to serach for (i.e. [A-X])

  returns: 1 for match found, 0 otherwise
*/
int searchString(char string[], char pattern[]){
  int error;
  regex_t reg; //

  if (regcomp(&reg, pattern, REG_EXTENDED|REG_NOSUB) != 0){

    // Using the flags, reg-extended (using extended reg expression)
    //    and reg_nosub (reporting error)
    // regcomp:  compiles the regex in pattern puts the results at reg
    return 0; // We got an error
  }
  error = regexec(&reg, string, 0, NULL, 0);  // compares value at reg with string to be matched
  // error = 0 => match
  // error = 1 => no match/error
  regfree(&reg); // Frees up the memeory
  if (error != 0){
    return 0;
  }
  return 1;
}

// Finds all tracks that match the given pattern.
// 
// Prints track number and title.
void find_track_regex(char pattern[])
{
  int i;
  for (i=0; i<NUM_TRACKS; i++) {
      if(searchString(tracks[i], pattern)){
        printf("Track %i: '%s'\n", i, tracks[i]);
      }
  }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
