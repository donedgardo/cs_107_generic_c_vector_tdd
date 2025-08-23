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
	EXPECT_DEATH(VectorNth(&myIntVector, 0), "Vector Nth out of band.");
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
	EXPECT_DEATH(VectorNth(&myIntVector, 1), "Vector Nth out of band.");
}

TEST(VectorTests, ItReallocatesWhen_MaxCapacity_Reached) {
	vector myIntVector;
	VectorNew(&myIntVector, sizeof(int), NULL, 1); 
	int n = 3, y= 2;
	VectorAppend(&myIntVector, &n); 
	VectorAppend(&myIntVector, &y); 
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 0), n);
	EXPECT_EQ(*(int *)VectorNth(&myIntVector, 1), y);
}



