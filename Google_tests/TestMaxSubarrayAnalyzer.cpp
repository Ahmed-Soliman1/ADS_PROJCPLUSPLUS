#include "MaxSubarrayAnalyzer.h"
#include "EuroDollarData.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

class MaxSubarrayAnalyzerTest : public ::testing::Test {
protected:
    EuroDollarData euroDollarData;
    MaxSubarrayAnalyzer* analyzer;

    // Initialize data for testing
    MaxSubarrayAnalyzerTest() : euroDollarData("../../Code_lib/euro-dollar.csv") {
        analyzer = new MaxSubarrayAnalyzer(euroDollarData);
    }

    ~MaxSubarrayAnalyzerTest() override {
        delete analyzer;
    }
};

// Test for finding max subarray sum
TEST_F(MaxSubarrayAnalyzerTest, FindMaxSubarraySum) {
    cout << "Running test for contiguous period with maximum sum of changes..." << endl;

    // Run the findMaxSubarraySum function and get results
    auto result = analyzer->findMaxSubarraySum();

    // Expected values based on the provided output
    pair<string, string> expectedDates = {"2003-11-18", "2015-01-07"};
    double expectedMaxSum = 411.136;

    // Verify the start and end dates of the maximum subarray
    EXPECT_EQ(result.first.first, "\""+expectedDates.first)
                        << "Expected start date: " << expectedDates.first << ", got: " << result.first.first;
    EXPECT_EQ(result.first.second, "\""+expectedDates.second)
                        << "Expected end date: " << expectedDates.second << ", got: " << result.first.second;

    // Verify the maximum sum value
    EXPECT_NEAR(result.second, expectedMaxSum, 1e-3)
                        << "Expected max sum: " << expectedMaxSum << ", got: " << result.second;

    cout << "Contiguous period with maximum sum test passed successfully!" << endl;
}