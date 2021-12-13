#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

#define BASE_SIZE 10

/**
 * @brief Creates a new "vector"
 * 
 * @param unitSize The size of each item
 * @return Vector* 
 */
Vector* create(int unitSize) {
  Vector* vector = malloc(sizeof(Vector));

  if (vector == NULL) {
    printf("malloc failed\n");
    exit(1);
  } 

  vector->unitSize = unitSize;
  vector->size = BASE_SIZE;
  vector->used = 0;
  vector->data = malloc(unitSize * BASE_SIZE);

  if (vector->data == NULL) {
    free(vector);
    vector = NULL;
    printf("malloc failed\n");
    exit(1);
  }

  return vector;
}

/**
 * @brief Pushes an item into the given vector, reallocating memory if necessary
 * 
 * @param vector 
 * @param data 
 * @return int 
 */
int push(Vector* vector, void *data) {
  if (vector->used == vector->size) {
   void* temp = realloc(vector->data, vector->unitSize * (vector->size * 2));

    if (vector->data != NULL) {
      printf("Realloc failed\n");
      exit(1);
    } else {
      // TODO: test
      vector->data=temp;
    }

    vector->size *= 2;
  }

  memcpy(vector->data + (vector->used) * (vector->unitSize), data, vector->unitSize);
  vector->used += 1;

  return 0;
}

/**
 * @brief Returns an item from the vector by index
 * Note: Cast the void* to the desired type
 * 
 * @param vector 
 * @param index 
 * @return void* 
 */
void* get(Vector* vector, int index) {
  assert(vector);
  if (index < 0 || index >= vector->size) {
    printf("Out of index\n");
    exit(1);
  }

  return vector->data + index * (vector->unitSize);
}

/**
 * @brief Clear the given vector and frees up the memory
 * 
 * @param vector 
 * @return Success/failure
 */
int clear(Vector* vector) {
  free(vector->data);
  vector->data = NULL;
  vector->used = vector->size = 0;
  free(vector);
  return 0;
}