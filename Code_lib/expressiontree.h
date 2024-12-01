#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include<string>
#include<stack>

using namespace std;

class ExpressionTree
{
private:

    struct TreeNode {
        string value;
        TreeNode* left;
        TreeNode* right;
        TreeNode( string val) : value(val), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;

    //Helper Functions to be included in the Conversions
    bool isOperator(char ch);
    bool isOperator(string s);
    double applyOperation(double a, double b, char op);
    int precedence(char op);
    void processOperator(stack<TreeNode*>& nodeStack, stack<char>& operatorStack);

public:
    ExpressionTree();
    void clearTree(TreeNode* node);

    void reset();

    ~ExpressionTree();
    double evaluateExpression();
    void buildfromPostfix(const string & postfix); // building expression tree from postfix expression
    void buildfromPrefix(const string & prefix);
    void buildfromInfix(const string & infix);
    string ToInfix(TreeNode* Root);
    string ToPostfix(TreeNode* Root);
    string ToPrefix(TreeNode* Root);
    TreeNode * Root_Accesser ();// helper function for the main


};

#endif // EXPRESSIONTREE_H
