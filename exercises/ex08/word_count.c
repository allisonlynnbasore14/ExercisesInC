


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>


GHashTable* hash;
// gpointer p = (void*) 1;
// gpointer p2 = (void*) 1;
// g_hash_table_insert(hash,"Jazzy",p);
// g_hash_table_insert(hash,"Mr Darcy",p2);


void read_words (FILE *f) {
    char x[1024];
    while (fscanf(f, " %1023s", x) == 1) {
        // puts(x);
        // char *old_key;
        // gpointer old_value;
        gpointer old_key;
        gpointer old_value;

        if (g_hash_table_lookup_extended (hash, strdup(x), &old_key, &old_value)){
            /* Insert the new value */
            gpointer p = old_value;
            int val = GPOINTER_TO_INT(p) + 1;
            gpointer pNew = (void*) val;
            g_hash_table_insert (hash, strdup(x), pNew);
            /* Just free the key and value */
        }else{
            /* Insert into our hash table it is not a duplicate. */
            gpointer p = (void*) 1;
            g_hash_table_insert (hash,strdup(x), p);
        }
    }
}


void readText(){
  // FILE *file;
  // file=fopen("test.txt", "r");
  //
  // if(NULL == file){
  //   printf("\n Error opening file");
  //   return;
  // }
  // int c;
  // while(1) {
  //    c = fgetc(file);
  //    if( feof(file) ) {
  //       break ;
  //    }
  //    // lineSplit(c);
  //
  // }
  // fclose(file);
}

void printUniqueWords(gpointer key, gpointer value, gpointer user_data){
  int realVal = GPOINTER_TO_INT( value );
  char* realKey = (char*)key;

  printf( "There are %d of the word: %s\n", realVal, realKey );
  return;
}



int main(int argc, char** argv) {

    // printf("There are %d keys in the hash table\n", g_hash_table_size(hash));
    //
    // printf("Jazzy likes %d\n", (int)g_hash_table_lookup(hash, "Jazzy"));


    // readText();
    hash = g_hash_table_new(g_str_hash, g_str_equal);
    FILE *file;
    file=fopen("CountFile.txt", "r");
    read_words(file);
    fclose(file);

    // void iterator(gpointer key, gpointer value, gpointer user_data) {
    g_hash_table_foreach( hash, printUniqueWords, NULL );
    // }


    g_hash_table_destroy(hash);
    // countFreq()
    return 0;
}
