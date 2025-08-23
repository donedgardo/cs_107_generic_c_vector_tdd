#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
	v->logicalSize = 0;
	v->elemSize = elemSize;
	v->data = malloc(elemSize * initialAllocation);
}

void VectorDispose(vector *v)
{}

int VectorLength(const vector *v)
{ return v->logicalSize; }

void *VectorNth(const vector *v, int position)
{ 
  int vectorLength = VectorLength(v);
  if(vectorLength <= 0 || vectorLength - 1 < position) {
    assert(!"Vector Nth out of band.");
  }
  return v->data;
}

void VectorReplace(vector *v, const void *elemAddr, int position)
{}

void VectorInsert(vector *v, const void *elemAddr, int position)
{}

void VectorAppend(vector *v, const void *elemAddr)
{
	v->logicalSize += 1;
	memcpy(v->data, elemAddr, v->elemSize);
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
