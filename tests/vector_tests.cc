#include <gtest/gtest.h>

extern "C" {
  #include "vector.h"
}

TEST(VectorTests, NewHas_0_Capacity) {
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
}

