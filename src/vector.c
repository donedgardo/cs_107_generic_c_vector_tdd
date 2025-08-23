#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
	v->size = 0;
}

void VectorDispose(vector *v)
{}

int VectorLength(const vector *v)
{ return v->size; }

void *VectorNth(const vector *v, int position)
{ 
	if(VectorLength(v) <= 0) {
		assert(!"Vector Nth out of band.");
	}

	return NULL; 
}

void VectorReplace(vector *v, const void *elemAddr, int position)
{}

void VectorInsert(vector *v, const void *elemAddr, int position)
{}

void VectorAppend(vector *v, const void *elemAddr)
{
	v->size += 1;
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
