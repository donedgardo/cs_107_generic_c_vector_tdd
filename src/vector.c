#include "vector.h"
#include <stdio.h>
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
{}

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
  memcpy(v->data + (position * v->elemSize), elemAddr, v->elemSize);
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{}


void VectorAppend(vector *v, const void *elemAddr)
{
	if(v->logicalSize >= v->capacity) {
	  VectorReallocCapacity(v, 2);
	}
	if(v->freeFn != NULL){
	  v->freeFn(v->data + (v->logicalSize * v->elemSize));
	}
	memcpy(v->data + (v->logicalSize * v->elemSize), elemAddr, v->elemSize);
	v->logicalSize += 1;
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
  if(ptr == NULL) {
   assert(!"Coudn't reallocate vector.");
  }
  v->capacity = v->logicalSize * factor;
};

static void AssertInBounds(const vector *v, const int position) {
  int vectorLength = VectorLength(v);
  if(vectorLength <= 0 || vectorLength - 1 < position) {
    assert(!"Index out of bounds.");
  }
} 


