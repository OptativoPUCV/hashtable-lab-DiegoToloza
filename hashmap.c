#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

  for(long a = hash(key,map->capacity); a < map->capacity; a++){
      
      if(map->buckets[a] == NULL || map->buckets[a]->key == NULL){
        Pair* Par = createPair(key,value);
        map->buckets[a] = Par;
        map->size++;
        map->current = a;
    }
    if(is_equal(map->buckets[a]->key,key) ){
      break;
    }
    if(a == map -> capacity-1){
      a = 0;
    }
  }

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap * newM = (HashMap *)malloc(sizeof(HashMap));
  newM->buckets = malloc(capacity * sizeof(newM->buckets));
  for (long i = 0; i < capacity ; i++){
      newM->buckets[i] = NULL;
  }
  newM -> size = 0;
  newM -> capacity = capacity;
  newM -> current = -1;

    return newM;
}

void eraseMap(HashMap * map,  char * key) {    

for(long a = hash(key,map->capacity); a < map->capacity; a++){
      
    if(map->buckets[a] == NULL || map->buckets[a]->key == NULL){
        break;
    }
    if(is_equal(map->buckets[a]->key,key) ){
      map->buckets[a]->key = NULL; 
      map->size--;
      break;
    }
    if(a == map -> capacity-1){
      a = 0;
    }
  }
}

void * searchMap(HashMap * map,  char * key) {  
   
   for(long a = hash(key,map->capacity); a < map->capacity; a++){
      
    if(map->buckets[a] == NULL || map->buckets[a]->key == NULL){
       break;
    }
    if(is_equal(map->buckets[a]->key,key) ){
      map->current = a;
      return map->buckets[a]->value;
    }
    if(a == map -> capacity-1){
      a = 0;
    }
  }
  return NULL;
}

void * firstMap(HashMap * map) {
  for(long i = 0; i < map->capacity; i++){
    if(map->buckets[i] != NULL || map->buckets[i]->key != NULL){
      map->current =i;
      return map->buckets[i]->value;
    }
  }
    return NULL;
}

void * nextMap(HashMap * map) {
  for(long i = map->current + 1; i < map->capacity; i++){
    if(map->buckets[i] != NULL || map->buckets[i]->key != NULL){
      map->current = i;
      return map->buckets[i]->value;
    }
  }
    return NULL;
}
