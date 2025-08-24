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
void MockCharStringFree(void *elemAddr) {
    mock_free_called++;
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






