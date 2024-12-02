#include<iostream>
#include "expressiontree.h"
// #include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
ExpressionTree::ExpressionTree():root(nullptr) {

}
ExpressionTree& ExpressionTree::operator=(const ExpressionTree& other) {
    if (this == &other) {
        return *this;
    }
    reset();
    if (other.root != nullptr) {
        root = copyTree(other.root);
    }
    return *this;
}
ExpressionTree::ExpressionTree(const ExpressionTree& other) : root(nullptr) {
    if (other.root != nullptr) {
        root = copyTree(other.root);
    }
}
TreeNode* ExpressionTree::copyTree(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TreeNode* newNode = new TreeNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}


void ExpressionTree::clearTree(TreeNode *node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void ExpressionTree::reset() {
    clearTree(root);
    root = nullptr;
}

ExpressionTree::~ExpressionTree() {
    clearTree(root);
}
bool ExpressionTree::isOperator(char c){
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
bool ExpressionTree::isOperator(string s){
    return s == "+" || s == "-" || s == "*" || s == "/" || s =="%";
}
int ExpressionTree::precedence(char op) { // Helper Function for Build from Infix.(Yousef Elmenshawy)
    if(op=='+'||op=='-') {
        return 1;
    }
    else if(op=='*'||op=='/'||op=='%') {
        return 2;
    }
    else
        return 0;
    // Precedence rules:
    // - Return 1 for + and -
    // - Return 2 for *, /, and %
    // - Return 0 for any other character (default case)
}

double ExpressionTree::applyOperation(double a, double b, char op) {
    double result = 0;
    int A=static_cast<int>(a); int B=static_cast<int>(b);
    if (op == '+') {
        result = a + b;
    } else if (op == '-') {
        result = a - b;
    } else if (op == '*') {
        result = a * b;
    } else if (op == '/') {
        if (b == 0) {
            throw runtime_error("Error: Division by zero");
        } else {
            result = a / b;
        }
    } else if (op == '%') {
        result = A % B;
    }else {
        throw runtime_error("Error: Invalid Operation");
    }
    return result;

}

double ExpressionTree::evaluateExpression()
{
    string postfix = ToPostfix(root);
    double result = 0;
    Stackt<double> Store(postfix.size());
    stringstream ss(postfix);
    string token;
    while (ss >> token) {

        if(isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            Store.push(stod(token));
        }
        else{

            double a2 = Store.peek(); Store.pop();
            double a1=Store.peek(); Store.pop();
            result= applyOperation(a1,a2,token[0]);
            Store.push(result);
        }

    }

    return result;
}

void ExpressionTree::buildfromPostfix(const string &postfix) // Saif Sabry
{
    if (postfix.empty()) {
        throw std::invalid_argument("Error: Postfix expression is empty!");
    }

    Stackt<TreeNode*> s(postfix.size());
    string multi_digit;
    for (char ch : postfix) {
  if (isdigit(ch)) {
      multi_digit += ch;
  }
  else {
      if (!multi_digit.empty()) {
          s.push(new TreeNode(multi_digit));
          multi_digit.clear();
      }

      if (isOperator(ch)) {
          if (s.size() < 2) {
              throw std::invalid_argument("Invalid postfix expression: not enough operands for operator!");
          }
          TreeNode* rightChild = s.peek();
          s.pop();
          TreeNode* leftChild = s.peek();
          s.pop();

          TreeNode* newNode = new TreeNode(string(1, ch));
          newNode->left = leftChild;
          newNode->right = rightChild;
          s.push(newNode);
      }
      else if (ch!=' ') {
          throw std::invalid_argument("Invalid character in postfix expression!");
      }
  }
    }
    if (!multi_digit.empty()) {
        s.push(new TreeNode(multi_digit));
    }
    if (s.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression: too many operands!");
    }
    root = s.peek();
    s.pop();
}
void ExpressionTree::buildfromPrefix(const string & prefix) // Ahmed Amgad
{
    if (prefix.empty()) {
        throw std::invalid_argument("Error: Prefix expression is empty!");
    }

    Stackt<TreeNode*> s(prefix.size());
    vector<string> tokens;//vector of strings to store tokens

    string currentToken;
    for (char ch : prefix) {
        if (ch == ' ') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken += ch;
        }
    }

    // Add the last token if any
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);  // Add the final token to the QVector
    }

    for (int i = tokens.size() - 1; i >= 0; --i) {
        string token = tokens[i];

        if (isOperator(token)) {
            if (s.size() < 2) {
                throw std::invalid_argument("Invalid prefix expression: not enough operands for operator!");
            }

            TreeNode* node = new TreeNode(token);
            node->left = s.peek(); s.pop();
            node->right = s.peek(); s.pop();
            s.push(node);
        } else {
            s.push(new TreeNode(token));
        }
    }

    if (s.size() != 1) {
        throw std::invalid_argument("Invalid prefix expression: not enough operands for operator!");
    }

    root = s.peek();
}

void ExpressionTree::buildfromInfix(const string &infix) {// Yousef Elmenshawy
    if (infix.empty()) {
        throw std::invalid_argument("Error: Infix expression is empty!");
    }

    Stackt<TreeNode*> nodeStack(infix.size());       // Stack for operands/subtrees
    Stackt<char> operatorStack(infix.size());        // Stack for operators


    // Process the infix expression character by character
    int i = 0;
    while (i < infix.size()) {
        if (infix[i]==' ') {
            i++; // Skip whitespaces
            continue;
        }

        if (isdigit(infix[i])) {// Handling Multidigit
            string numStr;
            while (i < infix.size() && isdigit(infix[i])) {
                numStr += infix[i++];
            }
            nodeStack.push(new TreeNode(numStr));  // Push operand as a tree node
        }
        else if (infix[i] == '(') {
            operatorStack.push(infix[i]);

            i++;
        }
        else if (infix[i] == ')') {

            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                processOperator(nodeStack, operatorStack);
            }
            operatorStack.pop();  // Remove the '('
            i++;
        }
        else if (isOperator(infix[i])) {
            while (!operatorStack.isEmpty() && precedence(operatorStack.peek()) >= precedence(infix[i])) {
                processOperator(nodeStack, operatorStack);
            }
            operatorStack.push(infix[i]);  // Push the current operator
            i++;
        }
    }

    // Process remaining operators
    while (!operatorStack.isEmpty()) {
        processOperator(nodeStack, operatorStack);
    }

    // The root of the tree is the only node left in the stack
    if (!nodeStack.isEmpty()) {
        root = nodeStack.peek();
        nodeStack.pop();
    } else {
        cerr << "Error: Failed to build expression tree!" << endl;
    }
}


string ExpressionTree::ToInfix(TreeNode *Root)
{
    string InfixExp = "";
    if (Root == nullptr) {
        return InfixExp;  // Base case: If the node is null, return
    }

    // Traverse the left subtree
    InfixExp += ToInfix(Root->left);

    // Add the current node's value (operator)
    InfixExp += Root->value;
    InfixExp += " ";  // Space after the value for separation

    // Traverse the right subtree
    InfixExp += ToInfix(Root->right);

    return InfixExp;
}


void ExpressionTree::processOperator(Stackt<TreeNode*>& nodeStack, Stackt<char>& operatorStack) {// Helper function to avoid reptetion in Build from Infix code
    if (nodeStack.size() < 2) {
        throw std::invalid_argument ("Error: Insufficient operands for operator!");
        return;
    }

    // Pop operator
    char op = operatorStack.peek();
    operatorStack.pop();

    // Pop operands
    TreeNode* right = nodeStack.peek(); nodeStack.pop();
    TreeNode* left = nodeStack.peek(); nodeStack.pop();

    // Create operator node
    TreeNode* opNode = new TreeNode(string(1, op));
    opNode->left = left;
    opNode->right = right;

    // Push the new subtree
    nodeStack.push(opNode);
}

string ExpressionTree::ToPostfix(TreeNode* Root) //Koussay Jaballah
{
    string PostfixExp = "";
    if (Root == nullptr) {
        return PostfixExp;  // Base case: If the node is null, return
    }

    PostfixExp+= ToPostfix(Root->left); //Traverse left
     PostfixExp+=ToPostfix(Root->right); //Traverse right

    PostfixExp+= Root->value; // visit the node
    PostfixExp+=" ";
    return PostfixExp;
}

string ExpressionTree::ToPrefix(TreeNode* Root) //Koussay Jaballah
{
    string PrefixExp = "";
    if (Root == nullptr) {
        return PrefixExp;  // Base case: If the node is null, return
    }
    PrefixExp+= Root->value; // visit the node
    PrefixExp+=" ";

    PrefixExp= PrefixExp+ ToPrefix(Root->left); //Traverse left
   PrefixExp+= ToPrefix(Root->right); //Traverse right

    return PrefixExp;
}

TreeNode* ExpressionTree::Root_Accesser()
{
    return root;
}
