#include "expressiontree.h"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Fixture for ExpressionTree testing
class ExpressionTreeTest : public ::testing::Test {
protected:
    ExpressionTree tree;

    // Initialize the tree with a default expression or other setup if needed
    ExpressionTreeTest() {
        cout << "Setting up ExpressionTree test..." << endl;
    }
};

// Test for building and evaluating from Postfix notation
TEST_F(ExpressionTreeTest, BuildFromPostfixAndEvaluate) {
    cout << "Running test for postfix expression..." << endl;
    string postfix = "3 4 + 5 *";  // This represents (3 + 4) * 5

    tree.buildfromPostfix(postfix);
    double result = tree.evaluateExpression();  // Expected result: 35.0

    cout << "Evaluating Postfix expression..." << endl;
    EXPECT_NEAR(result, 35.0, 1e-6) << "Expected result to be 35.0 from postfix evaluation.";

    // Test ToInfix conversion (should output ((3+4)*5))
    string infix = tree.ToInfix(tree.Root_Accesser());
    EXPECT_EQ(infix, "3 + 4 * 5 ") << "Expected infix expression to be '3 + 4 * 5'.";
}

// Test for building and evaluating from Prefix notation
TEST_F(ExpressionTreeTest, BuildFromPrefixAndEvaluate) {
    cout << "Running test for prefix expression..." << endl;
    string prefix = "* + 3 4 5";  // This represents (3 + 4) * 5

    tree.buildfromPrefix(prefix);
    double result = tree.evaluateExpression();  // Expected result: 35.0

    cout << "Evaluating Prefix expression..." << endl;
    EXPECT_NEAR(result, 35.0, 1e-6) << "Expected result to be 35.0 from prefix evaluation.";

    // Test ToInfix conversion (should output ((3+4)*5))
    string infix = tree.ToInfix(tree.Root_Accesser());
    cout<<infix<<"----------------------------"<<endl;
    EXPECT_EQ(infix, "3 + 4 * 5 ") << "Expected infix expression to be '3 + 4 * 5'.";
}

// Test for building and evaluating from Infix notation
TEST_F(ExpressionTreeTest, BuildFromInfixAndEvaluate) {
    cout << "Running test for infix expression..." << endl;
    string infix = "(3 + 4) * 5";  // This represents (3 + 4) * 5

    tree.buildfromInfix(infix);
    double result = tree.evaluateExpression();  // Expected result: 35.0

    cout << "Evaluating Infix expression..." << endl;
    EXPECT_NEAR(result, 35.0, 1e-6) << "Expected result to be 35.0 from infix evaluation.";

    // Test ToPostfix conversion (should output 3 4 + 5 *)
    string postfix = tree.ToPostfix(tree.Root_Accesser());
    EXPECT_EQ(postfix, "3 4 + 5 * ") << "Expected postfix expression to be '3 4 + 5 *'.";
}

// Test for invalid expressions
TEST_F(ExpressionTreeTest, InvalidPostfixExpression) {
    cout << "Running test for invalid postfix expression..." << endl;
    string invalidPostfix = "3 + * 5";  // Invalid postfix expression

    try {
        tree.buildfromPostfix(invalidPostfix);
        FAIL() << "Expected exception for invalid postfix expression.";
    } catch (const exception &e) {
        EXPECT_EQ(string(e.what()), "Invalid postfix expression: not enough operands for operator!")
            << "Expected exception for invalid postfix expression.";
    }
}

TEST_F(ExpressionTreeTest, InvalidPrefixExpression) {
    cout << "Running test for invalid prefix expression..." << endl;
    string invalidPrefix = "+ * 3 4 5 6";  // Invalid prefix expression

    try {
        tree.buildfromPrefix(invalidPrefix);
        string infix = tree.ToInfix(tree.Root_Accesser());
        cout<<infix<<"----------------------------"<<endl;
        FAIL() << "Expected exception for invalid prefix expression.";
    } catch (const exception &e) {
        EXPECT_EQ(string(e.what()), "Invalid prefix expression: not enough operands for operator!")
            << "Expected exception for invalid prefix expression.";
    }
}

TEST_F(ExpressionTreeTest, InvalidInfixExpression) {
    cout << "Running test for invalid infix expression..." << endl;
    string invalidInfix = "(3 + 4 * 5";  // Invalid infix expression (missing closing parenthesis)

    try {
        tree.buildfromInfix(invalidInfix);
        FAIL() << "Expected exception for invalid infix expression.";
    } catch (const exception &e) {
        EXPECT_EQ(string(e.what()), "Error: Insufficient operands for operator!")
            << "Expected exception for invalid infix expression.";
    }
}
TEST_F(ExpressionTreeTest, EmptyPrefixExpression) {
    try {
        tree.buildfromPrefix("");  // Passing an empty string to the method
        FAIL() << "Expected an exception for empty prefix expression!";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Error: Prefix expression is empty!", e.what());
    } catch (...) {
        FAIL() << "Expected std::invalid_argument exception for empty prefix expression!";
    }
}

// Test for empty infix expression handling (assuming `buildfromInfix` method exists)
TEST_F(ExpressionTreeTest, EmptyInfixExpression) {
    try {
        tree.buildfromInfix("");  // Passing an empty string to the method
        FAIL() << "Expected an exception for empty infix expression!";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Error: Infix expression is empty!", e.what());  // Assuming you throw this exception
    } catch (...) {
        FAIL() << "Expected std::invalid_argument exception for empty infix expression!";
    }
}

// Test for empty postfix expression handling (assuming `buildfromPostfix` method exists)
TEST_F(ExpressionTreeTest, EmptyPostfixExpression) {
    try {
        tree.buildfromPostfix("");  // Passing an empty string to the method
        FAIL() << "Expected an exception for empty postfix expression!";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Error: Postfix expression is empty!", e.what());  // Assuming you throw this exception
    } catch (...) {
        FAIL() << "Expected std::invalid_argument exception for empty postfix expression!";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
