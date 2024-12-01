#include "MaxHeap.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;

// Test fixture for setting up MaxHeap test cases
class MaxHeapTest : public ::testing::Test {
protected:
    MaxHeap maxHeap;

    // Set up function to initialize heap with common elements
    void SetUp() override {
        maxHeap.insert("2023-01-01", 1.2);
        maxHeap.insert("2023-01-02", 0.8);
        maxHeap.insert("2023-01-03", 1.5);
    }
};

// Test insertion and retrieval of the maximum element
TEST_F(MaxHeapTest, InsertAndGetMax) {
    EXPECT_EQ(maxHeap.getMax().first, "2023-01-03") << "Failure: Expected date for maximum element is '2023-01-03'. Check heap ordering.";
    EXPECT_DOUBLE_EQ(maxHeap.getMax().second, 1.5) << "Failure: Expected maximum value is 1.5. Ensure correct heap property maintenance.";

    cout << "Success: The maximum element was retrieved correctly after insertion!\n";
}

// Test insertion, extraction, and heap order maintenance
TEST_F(MaxHeapTest, ExtractMax) {
    // First extraction
    auto maxElement = maxHeap.extractMax();
    EXPECT_EQ(maxElement.first, "2023-01-03") << "Failure: Expected date for extracted maximum is '2023-01-03'.";
    EXPECT_DOUBLE_EQ(maxElement.second, 1.5) << "Failure: Expected maximum value for first extraction is 1.5.";

    // After extracting the maximum, next maximum should be "2023-01-01" with 1.2
    EXPECT_EQ(maxHeap.getMax().first, "2023-01-01") << "Failure: Expected next maximum date is '2023-01-01' after extraction.";
    EXPECT_DOUBLE_EQ(maxHeap.getMax().second, 1.2) << "Failure: Expected next maximum value after extraction is 1.2.";

    // Extract again to ensure ordering remains correct
    maxElement = maxHeap.extractMax();
    EXPECT_EQ(maxElement.first, "2023-01-01") << "Failure: Expected date for second extraction is '2023-01-01'.";
    EXPECT_DOUBLE_EQ(maxElement.second, 1.2) << "Failure: Expected second extracted value is 1.2.";

    // Verify last remaining element
    maxElement = maxHeap.extractMax();
    EXPECT_EQ(maxElement.first, "2023-01-02") << "Failure: Expected date for last remaining element is '2023-01-02'.";
    EXPECT_DOUBLE_EQ(maxElement.second, 0.8) << "Failure: Expected value for last remaining element is 0.8.";

    // Heap should now be empty, so extracting again should throw an error
    EXPECT_THROW(maxHeap.extractMax(), runtime_error) << "Failure: Expected runtime_error when extracting from an empty heap.";

    cout << "Success: All elements were extracted in the correct order, and the heap maintained the correct structure!\n";
}

// Test for correct exception handling when extracting from an empty heap
TEST_F(MaxHeapTest, ExtractMaxEmptyHeap) {
    // Clear the heap by extracting all elements
    maxHeap.extractMax();
    maxHeap.extractMax();
    maxHeap.extractMax();

    EXPECT_THROW(maxHeap.extractMax(), runtime_error) << "Failure: Expected runtime_error when extracting from an empty heap.";

    cout << "Success: Correctly handled extraction from an empty heap!\n";
}

// Test for correct exception handling when calling getMax on an empty heap
TEST_F(MaxHeapTest, GetMaxEmptyHeap) {
    MaxHeap emptyHeap;
    EXPECT_THROW(emptyHeap.getMax(), runtime_error) << "Failure: Expected runtime_error when calling getMax on an empty heap.";

    cout << "Success: Correctly handled getMax on an empty heap!\n";
}

// Test inserting elements with the same priority
TEST_F(MaxHeapTest, InsertDuplicateValues) {
    maxHeap.insert("2023-01-04", 1.5); // Insert duplicate value

    // Extract maximum elements one by one to check ordering of duplicates
    EXPECT_EQ(maxHeap.extractMax().first, "2023-01-03") << "Failure: Expected first maximum date '2023-01-03' for duplicate values test.";
    EXPECT_EQ(maxHeap.extractMax().first, "2023-01-04") << "Failure: Expected second maximum date '2023-01-04' for duplicate values test.";

    // Both elements with 1.2 should be present now
    auto maxElement = maxHeap.extractMax();
    EXPECT_DOUBLE_EQ(maxElement.second, 1.2) << "Failure: Expected third maximum value 1.2 with duplicates.";
    EXPECT_EQ(maxElement.first, "2023-01-01") << "Failure: Expected date for duplicate 1.2 value.";

    maxElement = maxHeap.extractMax();
    EXPECT_DOUBLE_EQ(maxElement.second, 0.8) << "Failure: Expected fourth maximum value 0.8 after duplicates.";
    EXPECT_EQ(maxElement.first, "2023-01-02") << "Failure: Expected date for last minimum value 0.8.";

    cout << "Success: Duplicate values were handled correctly!\n";
}

// Test inserting and extracting elements in a specific order
TEST(MaxHeapOrderTest, InsertOrder) {
    MaxHeap testHeap;
    testHeap.insert("2023-01-01", 2.0);
    testHeap.insert("2023-01-02", 3.0);
    testHeap.insert("2023-01-03", 1.0);

    EXPECT_EQ(testHeap.getMax().first, "2023-01-02") << "Failure: Expected maximum date '2023-01-02' in InsertOrder test.";
    EXPECT_DOUBLE_EQ(testHeap.getMax().second, 3.0) << "Failure: Expected maximum value 3.0 in InsertOrder test.";

    cout << "Success: Heap correctly maintained the maximum element at the top after various insertions!\n";
}