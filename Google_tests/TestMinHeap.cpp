#include "MinHeap.h"
#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;

// Test fixture for setting up MinHeap test cases
class MinHeapTest : public ::testing::Test {
protected:
    MinHeap minHeap;

    // Set up function to initialize heap with common elements
    void SetUp() override {
        minHeap.insert("2023-01-01", 1.2);
        minHeap.insert("2023-01-02", 0.8);
        minHeap.insert("2023-01-03", 1.5);
    }
};

// Test insertion and retrieval of the minimum element
TEST_F(MinHeapTest, InsertAndGetMin) {
    EXPECT_EQ(minHeap.getMin().first, "2023-01-02") << "Failure: Expected date for minimum element is '2023-01-02'. Check heap ordering.";
    EXPECT_DOUBLE_EQ(minHeap.getMin().second, 0.8) << "Failure: Expected minimum value is 0.8. Ensure correct heap property maintenance.";

    cout << "Success: The minimum element was retrieved correctly after insertion!\n";
}

// Test insertion, extraction, and heap order maintenance
TEST_F(MinHeapTest, ExtractMin) {
    // First extraction
    auto minElement = minHeap.extractMin();
    EXPECT_EQ(minElement.first, "2023-01-02") << "Failure: Expected date for extracted minimum is '2023-01-02'.";
    EXPECT_DOUBLE_EQ(minElement.second, 0.8) << "Failure: Expected minimum value for first extraction is 0.8.";

    // After extracting the minimum, next minimum should be "2023-01-01" with 1.2
    EXPECT_EQ(minHeap.getMin().first, "2023-01-01") << "Failure: Expected next minimum date is '2023-01-01' after extraction.";
    EXPECT_DOUBLE_EQ(minHeap.getMin().second, 1.2) << "Failure: Expected next minimum value after extraction is 1.2.";

    // Extract again to ensure ordering remains correct
    minElement = minHeap.extractMin();
    EXPECT_EQ(minElement.first, "2023-01-01") << "Failure: Expected date for second extraction is '2023-01-01'.";
    EXPECT_DOUBLE_EQ(minElement.second, 1.2) << "Failure: Expected second extracted value is 1.2.";

    // Verify last remaining element
    minElement = minHeap.extractMin();
    EXPECT_EQ(minElement.first, "2023-01-03") << "Failure: Expected date for last remaining element is '2023-01-03'.";
    EXPECT_DOUBLE_EQ(minElement.second, 1.5) << "Failure: Expected value for last remaining element is 1.5.";

    // Heap should now be empty, so extracting again should throw an error
    EXPECT_THROW(minHeap.extractMin(), runtime_error) << "Failure: Expected runtime_error when extracting from an empty heap.";

    cout << "Success: All elements were extracted in the correct order, and the heap maintained the correct structure!\n";
}

// Test for correct exception handling when extracting from an empty heap
TEST_F(MinHeapTest, ExtractMinEmptyHeap) {
    // Clear the heap by extracting all elements
    minHeap.extractMin();
    minHeap.extractMin();
    minHeap.extractMin();

    EXPECT_THROW(minHeap.extractMin(), runtime_error) << "Failure: Expected runtime_error when extracting from an empty heap.";

    cout << "Success: Correctly handled extraction from an empty heap!\n";
}

// Test for correct exception handling when calling getMin on an empty heap
TEST_F(MinHeapTest, GetMinEmptyHeap) {
    MinHeap emptyHeap;
    EXPECT_THROW(emptyHeap.getMin(), runtime_error) << "Failure: Expected runtime_error when calling getMin on an empty heap.";

    cout << "Success: Correctly handled getMin on an empty heap!\n";
}

// Test inserting elements with the same priority
TEST_F(MinHeapTest, InsertDuplicateValues) {
    minHeap.insert("2023-01-04", 1.5); // Insert duplicate value

    // Extract minimum elements one by one to check ordering of duplicates
    EXPECT_EQ(minHeap.extractMin().first, "2023-01-02") << "Failure: Expected first minimum date '2023-01-02' for duplicate values test.";
    EXPECT_EQ(minHeap.extractMin().first, "2023-01-01") << "Failure: Expected second minimum date '2023-01-01' for duplicate values test.";

    // Both elements with 1.5 should be present now
    auto minElement = minHeap.extractMin();
    EXPECT_DOUBLE_EQ(minElement.second, 1.5) << "Failure: Expected third minimum value 1.5 with duplicates.";
    EXPECT_TRUE(minElement.first == "2023-01-03" || minElement.first == "2023-01-04") << "Failure: Expected date for duplicate 1.5 value.";

    minElement = minHeap.extractMin();
    EXPECT_DOUBLE_EQ(minElement.second, 1.5) << "Failure: Expected fourth minimum value 1.5 with duplicates.";
    EXPECT_TRUE(minElement.first == "2023-01-03" || minElement.first == "2023-01-04") << "Failure: Expected date for last duplicate 1.5 value.";

    cout << "Success: Duplicate values were handled correctly!\n";
}

// Test inserting and extracting elements in a specific order
TEST(MinHeapOrderTest, InsertOrder) {
    MinHeap testHeap;
    testHeap.insert("2023-01-01", 2.0);
    testHeap.insert("2023-01-02", 1.0);
    testHeap.insert("2023-01-03", 3.0);

    EXPECT_EQ(testHeap.getMin().first, "2023-01-02") << "Failure: Expected minimum date '2023-01-02' in InsertOrder test.";
    EXPECT_DOUBLE_EQ(testHeap.getMin().second, 1.0) << "Failure: Expected minimum value 1.0 in InsertOrder test.";

    cout << "Success: Heap correctly maintained the minimum element at the top after various insertions!\n";
}