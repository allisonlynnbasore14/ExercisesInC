


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>


GHashTable* hash;

/* read_words: reads the words seperated by whitespaces in a passed in text file reference

  reads text file from argument reference
  checks if word is new and inserts word in hashtable or increments word count

*/

void read_words (FILE *f) {
    char x[1024];
    while (fscanf(f, " %1023s", x) == 1) {
        gpointer old_key;
        gpointer old_value;

        if (g_hash_table_lookup_extended (hash, strdup(x), &old_key, &old_value)){
            gpointer p = old_value;
            int val = GPOINTER_TO_INT(p) + 1;
            gpointer pNew = (void*) val;
            g_hash_table_insert (hash, strdup(x), pNew);
        }else{
            gpointer p = (void*) 1;
            g_hash_table_insert (hash,strdup(x), p);
        }
    }
}

/* printUniqueWords: function passed to foreach function to print each key pair value

  casts the key and value and prints pair

*/

void printUniqueWords(gpointer key, gpointer value, gpointer user_data){
  int realVal = GPOINTER_TO_INT( value );
  char* realKey = (char*)key;

  printf( "There are %d of the word: %s\n", realVal, realKey );
  return;
}



int main(int argc, char** argv) {

    hash = g_hash_table_new(g_str_hash, g_str_equal);
    FILE *file;
    file=fopen("CountFile.txt", "r");
    read_words(file);
    fclose(file);

    g_hash_table_foreach( hash, printUniqueWords, NULL );

    g_hash_table_destroy(hash);

    return 0;
}
