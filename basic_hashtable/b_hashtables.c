#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));
  ht->storage= calloc(capacity, sizeof(Pair *));
  ht->capacity = capacity;
  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // Create an index
  int index = hash(key, ht->capacity);
  // Create a pair
  Pair *pair = create_pair(key, value);
  // Assign storage index to pair(point the index to our array key-value)
  ht->storage[index] = pair;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // find index
  int index = hash(key, ht->capacity);
  // search storage for key, destroy! 
  if(ht->storage[index] !=NULL && strcmp(ht->storage[index]->key, key) == 0){
    // destroy 
    destroy_pair(ht->storage[index]);
    ht->storage[index] = NULL;
  }
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
  {
    // set new index to hash the key
  int index = hash(key, ht->capacity);
// look at ht->storage[index] != Null
  if (ht->storage[index] != NULL) {
    // strcmp -ht->storage->key and the stored key we then return the key.
    if (strcmp(ht->storage[index]->key, key) == 0 ) {
      return ht->storage[index]->value;
    }
    else{
      return NULL;
    }
  }else{
    return NULL;
  }
}
  

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
if (ht->storage != NULL) {
  //Free each pair in storage
    for (int i = 0; i < ht->capacity; i++) {
      if (ht->storage[i] != NULL ) {
        destroy_pair(ht->storage[i]);
      }
    }
    // Free Storage
    free(ht->storage);
  }
  // Free HT
  if(ht != NULL){
    free(ht);
  }
}


#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
