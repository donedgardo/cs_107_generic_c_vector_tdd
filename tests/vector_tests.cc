#include <cstddef>
#include <gtest/gtest.h>

extern "C" {
  #include "vector.h"
}

TEST(VectorTests, VectorNew_0_Length) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 10); 
	int actual = VectorLength(&myIntVector);
	EXPECT_EQ(actual, 0);
}

TEST(VectorTests, Throws_nth_with_0_Capacity) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 10); 
	EXPECT_DEATH(VectorNth(&myIntVector, 0), "Index out of bounds.");
}

TEST(VectorTests, VectorAppend_Add_element_to_end) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 10); 
	int n = 8;
	VectorAppend(&myIntVector, &n); 
	EXPECT_EQ(VectorLength(&myIntVector), 1);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 0), n);
}

TEST(VectorTests, Throws_nth_out_of_bounds) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 10); 
	int n = 8;
	VectorAppend(&myIntVector, &n); 
	EXPECT_DEATH(VectorNth(&myIntVector, 1), "Index out of bounds.");
}

TEST(VectorTests, ItReallocates_When_MaxCapacity_Reached) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 1); 
	int n = 3, y= 2;
	VectorAppend(&myIntVector, &n); 
	VectorAppend(&myIntVector, &y); 
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 0), n);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 1), y);
}

TEST(VectorTests, Throws_When_Replace_With0_Capacity) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int n = 2;
	EXPECT_DEATH(VectorReplace(&myIntVector, &n, 0), "Index out of bounds.");
}

TEST(VectorTests, Throws_When_Replace_Out_of_Bands) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int a = 3, b= 2;
	VectorAppend(&myIntVector, &a); 
	VectorAppend(&myIntVector, &b); 
	EXPECT_DEATH(VectorReplace(&myIntVector, &b, 2), "Index out of bounds.");
}

TEST(VectorTests, Replaces_Element) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int a = 3, b= 2;
	VectorAppend(&myIntVector, &a); 
	VectorAppend(&myIntVector, &b); 
	a = 4;
	VectorReplace(&myIntVector, &a, 0);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 0), a);
}

static int mock_free_called = 0;
static void * addressFreed;
void MockCharStringFree(void *elemAddr) {
    mock_free_called++;
    addressFreed = elemAddr;
}

TEST(VectorTests, Frees_replaced_element) {
	vector myStringVector;
	mock_free_called = 0;
	VectorNew(&myStringVector, sizeof(char*), MockCharStringFree, 4); 
	const char a[] = "Hello";
	const char b[] = "World";
	VectorAppend(&myStringVector, &a); 
	VectorAppend(&myStringVector, &a); 
	VectorReplace(&myStringVector, &b, 1);
	EXPECT_EQ(mock_free_called, 1);
}

TEST(VetorTests, Disposing_frees_elements) {
	vector myStringVector;
	mock_free_called = 0;
	VectorNew(&myStringVector, sizeof(char*), MockCharStringFree, 4); 
	const char a[] = "Hello";
	const char b[] = "World";
	VectorAppend(&myStringVector, &a); 
	VectorAppend(&myStringVector, &a); 
	VectorDispose(&myStringVector);
	EXPECT_EQ(mock_free_called, 2);
}

TEST(VectorTests, Throws_on_Insert_if_left_of_bounds) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int n = 2;
	EXPECT_DEATH(VectorInsert(&myIntVector, &n, 0), "Index out of bounds.");
}

TEST(VectorTests, Throws_on_Insert_if_right_of_bounds) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int n = 2;
	VectorAppend(&myIntVector, &n); 
	EXPECT_DEATH(VectorInsert(&myIntVector, &n, 4), "Index out of bounds.");
}

TEST(VectorTests, Inserts_element_in_correct_position) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int n = 2;
	VectorAppend(&myIntVector, &n); 
	n = 4;
	VectorInsert(&myIntVector, &n, 0);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 0), n);
}

TEST(VectorTests, Inserts_element_shifts_to_left) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 4); 
	int n = 2;
	VectorAppend(&myIntVector, &n); 
	int i = 4;
	VectorInsert(&myIntVector, &n, 0);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 1), n);
}


TEST(VectorTests, Inserts_grows_when_at_capacity) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 1); 
	int n = 2;
	VectorAppend(&myIntVector, &n); 
	int i = 4;
	VectorInsert(&myIntVector, &n, 0);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 1), n);
	EXPECT_EQ(myIntVector.capacity, 2);
}


TEST(VectorTests, Delete_throws_when_out_of_bands) {
	vector myStringVector;
	mock_free_called = 0;
	VectorNew(&myStringVector, sizeof(char*), MockCharStringFree, 0); 
	EXPECT_DEATH(VectorDelete(&myStringVector, 0), "Index out of bounds.");
}

TEST(VectorTests, Delete_decreases_length) {
	vector myStringVector;
	mock_free_called = 0;
	VectorNew(&myStringVector, sizeof(char*), MockCharStringFree, 0); 
	char n[] = "test";
	VectorAppend(&myStringVector, &n);
	VectorDelete(&myStringVector, 0);
	EXPECT_EQ(VectorLength(&myStringVector), 0);
}

TEST(VectorTests, Delete_frees_element) {
	vector myStringVector;
	mock_free_called = 0;
	addressFreed = NULL;
	VectorNew(&myStringVector, sizeof(char*), MockCharStringFree, 2); 
	char a[] = "test", b[] = "delete" ;
	VectorAppend(&myStringVector, &b);
	VectorAppend(&myStringVector, &a);
	void * elemForDeletion = VectorNth(&myStringVector, 0);
	VectorDelete(&myStringVector, 0);
	EXPECT_EQ(mock_free_called, 1);
	EXPECT_EQ(addressFreed, elemForDeletion);
}

TEST(VectorTests, Delete_shift_elements_to_left) {
	vector myStringVector;
	VectorNew(&myStringVector, sizeof(char*), NULL, 2); 
	char a[] = "a", b[] = "b" ;
	VectorAppend(&myStringVector, &a);
	VectorAppend(&myStringVector, &b);
	VectorDelete(&myStringVector, 0);
	EXPECT_STREQ((char *)VectorNth(&myStringVector, 0), b);
}


static int mapCounter = 0;
static int mapAddresses[3];
static int actualContext = 0;
void MockMapFn(void *elemAddr, void *auxData) {
  mapAddresses[mapCounter] = *(int *)elemAddr;	
  mapCounter++;
  if(auxData != NULL) {
    actualContext = *(int *)auxData;
  }
}

TEST(VectorTest, Map_throws_when_no_function) {
	vector myVector;
	VectorNew(&myVector, sizeof(int), NULL, 1);
	EXPECT_DEATH(VectorMap(&myVector, NULL, NULL), "Map function was not provided.");
}

TEST(VectorTest, Map_call_length_amount_of_time) {
	vector myVector;
	mapCounter = 0;
	VectorNew(&myVector, sizeof(int), NULL, 3);
	int numbers[] = { 1, 2, 3 };	
	for (int i = 0; i < 3; i++) {
	  VectorAppend(&myVector, &numbers[i]);
    	  mapAddresses[i] = 0;
	}
	VectorMap(&myVector, MockMapFn, NULL);
	EXPECT_EQ(VectorLength(&myVector), mapCounter);
}

TEST(VectorTest, Map_call_right_elements) {
	vector myVector;
	mapCounter = 0;
	VectorNew(&myVector, sizeof(int), NULL, 3);
	int numbers[] = { 1, 2, 3 };	
	for (int i = 0; i < 3; i++) {
	  VectorAppend(&myVector, &numbers[i]);
    	  mapAddresses[i] = 0;
	}
	VectorMap(&myVector, MockMapFn, NULL);
	for (int i = 0; i < 3; i++) {
	  EXPECT_EQ(numbers[i], mapAddresses[i]);
	}
}

TEST(VectorTest, Map_call_with_provided_aux_data) {
	vector myVector;
	VectorNew(&myVector, sizeof(int), NULL, 3);
	int n = 1;
        VectorAppend(&myVector, &n);
	actualContext = 0;
	int context = 42;
	VectorMap(&myVector, MockMapFn, &context);
        EXPECT_EQ(context, actualContext);
}

static int CompareInts(const void * lhs, const void * rhs) {
	int lh = *(int *)lhs;
	int rh = *(int *)rhs;
	if(lh == rh) return 0;
	return lh < rh ? -1 : 1;

}
TEST(VectorTest, Sort_throws_when_no_cpr_fn) {
	vector myVector;
	VectorNew(&myVector, sizeof(int), NULL, 3);
	EXPECT_DEATH(VectorSort(&myVector, NULL), "Failed sort, no compare function provided");
}

TEST(VectorTest, Sorts_a_generic_vector) {
	vector myVector;
	VectorNew(&myVector, sizeof(int), NULL, 4);
	int numbers[] = { 4, 3, 2, 1 };	
	for (int i = 0; i < 4; i++) {
	  VectorAppend(&myVector, &numbers[i]);
	}
	VectorSort(&myVector, CompareInts);
	int expectedNumbers[] = { 1, 2, 3, 4 };	
	for (int i = 0; i < 4; i++) {
	  EXPECT_EQ(expectedNumbers[i], *(int *)VectorNth(&myVector, i));
	}

}


