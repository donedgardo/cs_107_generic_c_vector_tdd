#include "vector.h"
#include "vector_error.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
	v->logicalSize = 0;
	v->elemSize = elemSize;
	v->capacity = initialAllocation;
	v->data = malloc(elemSize * initialAllocation);
	v->freeFn = freeFn;
}

void VectorDispose(vector *v)
{
  if(v->freeFn != NULL) {
    for (int i = 0; i < VectorLength(v); i++) {
      v->freeFn(v->data + (v->elemSize * i));
    }
  }
}

int VectorLength(const vector *v)
{ return v->logicalSize; }


void *VectorNth(const vector *v, int position)
{ 
  AssertInBounds(v, position);
  return v->data + (position * v->elemSize);
}

void VectorReplace(vector *v, const void *elemAddr, int position)
{
  AssertInBounds(v, position);
  if(v->freeFn != NULL){
    v->freeFn(v->data + (v->logicalSize * v->elemSize));
  }
  memcpy(v->data + (position * v->elemSize), elemAddr, v->elemSize);
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{
  AssertInBounds(v, position);
  if(v->logicalSize >= v->capacity) {
    VectorReallocCapacity(v, 2);
  }
  void * insertPos = VectorNth(v, position);
  void * nextPos = insertPos + v->elemSize;
  size_t bytesToMove = (VectorLength(v) - position) * v->elemSize;
  memmove(nextPos, insertPos, bytesToMove);
  memcpy(v->data + (position * v->elemSize), elemAddr, v->elemSize);
  v->logicalSize++;
}


void VectorAppend(vector *v, const void *elemAddr)
{
  if(v->logicalSize >= v->capacity) {
    VectorReallocCapacity(v, 2);
  }
  memcpy(v->data + (v->logicalSize * v->elemSize), elemAddr, v->elemSize);
  v->logicalSize++;
}

void VectorDelete(vector *v, int position)
{}

void VectorSort(vector *v, VectorCompareFunction compare)
{}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, mybool isSorted)
{ return -1; } 

static void VectorReallocCapacity(vector *v, int factor) {
  void * ptr = realloc(v->data, v->logicalSize * factor * v->elemSize);
  vector_assert(ptr == NULL, "Couln't reallocate vector.");
  v->capacity = v->logicalSize * factor;
};

static void AssertInBounds(const vector *v, const int position) {
  int vectorLength = VectorLength(v);
  vector_assert((vectorLength <= 0 || vectorLength - 1 < position), "Index out of bounds.");
} 


