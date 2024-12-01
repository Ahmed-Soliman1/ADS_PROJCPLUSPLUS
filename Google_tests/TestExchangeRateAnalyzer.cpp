#include "ExchangeRateAnalyzer.h"
#include "EuroDollarData.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

// Fixture for ExchangeRateAnalyzer testing
class ExchangeRateAnalyzerTest : public ::testing::Test {
protected:
    vector<vector<string>> data;
    EuroDollarData euroDollarData;
    int N;

    // Initialize data in the constructor
    ExchangeRateAnalyzerTest() : euroDollarData("../../Code_lib/euro-dollar.csv"), N(10) {
        cout << "Loading exchange rate data for testing..." << endl;
        data = euroDollarData.getData();
        cout << "Data loaded successfully. Total entries: " << data.size() << endl;
    }
};

// Test for finding top N positive changes
TEST_F(ExchangeRateAnalyzerTest, FindTopPositiveChanges) {
    cout << "Running test for top " << N << " positive changes..." << endl;
    ExchangeRateAnalyzer analyzer(euroDollarData, N);

    // Run the function to get the top positive changes
    auto topPositive = analyzer.findTopPositiveChanges();
    cout << "Top positive changes retrieved. Verifying results..." << endl;

    // Expected values for top 10 positive changes
    vector<pair<string, double>> expectedTopPositive = {
            {"2008-04-22", 0.416102},
            {"2008-04-16", 0.411302},
            {"2008-07-11", 0.410302},
            {"2008-07-21", 0.409102},
            {"2008-07-15", 0.408402},
            {"2008-04-21", 0.407302},
            {"2008-07-14", 0.407102},
            {"2008-04-17", 0.406402},
            {"2008-04-23", 0.405602},
            {"2008-07-02", 0.404602}
    };

    // Check that we get exactly N results
    EXPECT_EQ(topPositive.size(), N) << "Expected " << N << " results for top positive changes.";

    // Verify each result matches the expected value
    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(topPositive[i].first, "\""+expectedTopPositive[i].first)
                            << "Mismatch in date at index " << i << ": expected \""
                            << expectedTopPositive[i].first << "\", got \"" << topPositive[i].first << "\"";

        EXPECT_NEAR(topPositive[i].second, expectedTopPositive[i].second, 1e-6)
                            << "Mismatch in change at index " << i << ": expected "
                            << expectedTopPositive[i].second << ", got " << topPositive[i].second;
    }

    cout << "Top positive changes test passed successfully!" << endl;
}

// Test for finding top N negative changes
TEST_F(ExchangeRateAnalyzerTest, FindTopNegativeChanges) {
    cout << "Running test for top " << N << " negative changes..." << endl;
    ExchangeRateAnalyzer analyzer(euroDollarData, N);

    // Run the function to get the top negative changes
    auto topNegative = analyzer.findTopNegativeChanges();
    cout << "Top negative changes retrieved. Verifying results..." << endl;

    // Expected values for top 10 negative changes
    vector<pair<string, double>> expectedTopNegative = {
            {"2000-10-20", -0.341898},
            {"2000-10-30", -0.342798},
            {"2000-10-18", -0.344398},
            {"2000-10-27", -0.344398},
            {"2000-11-24", -0.344998},
            {"2001-07-05", -0.346398},
            {"2000-10-23", -0.347598},
            {"2000-10-24", -0.347798},
            {"2000-10-26", -0.353798},
            {"2000-10-25", -0.356198}
    };

    // Check that we get exactly N results
    EXPECT_EQ(topNegative.size(), N) << "Expected " << N << " results for top negative changes.";

    // Verify each result matches the expected value
    for (size_t i = 0; i < N; ++i) {
        EXPECT_EQ(topNegative[i].first, "\""+expectedTopNegative[i].first)
                            << "Mismatch in date at index " << i << ": expected \""
                            << expectedTopNegative[i].first << "\", got \"" << topNegative[i].first << "\"";

        EXPECT_NEAR(topNegative[i].second, expectedTopNegative[i].second, 1e-6)
                            << "Mismatch in change at index " << i << ": expected "
                            << expectedTopNegative[i].second << ", got " << topNegative[i].second;
    }

    cout << "Top negative changes test passed successfully!" << endl;
}