#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  char **data;
  int unitSize;
  int size;
  int used;
} Vector;

Vector* create(int unitSize);
int push(Vector* vector, void* data);
void* get(Vector* vector, int index);
int clear(Vector* vector);

#endif