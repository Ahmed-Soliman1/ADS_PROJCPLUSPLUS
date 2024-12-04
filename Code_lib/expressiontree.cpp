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
        else if (isOperator(token)){
            if (Store.size() < 2) {
                throw runtime_error("Error: Insufficient operands for operator '" + token);
            }
            double a2 = Store.peek(); Store.pop();
            double a1=Store.peek(); Store.pop();
            result= applyOperation(a1,a2,token[0]);
            Store.push(result);
        }else
        {
            throw runtime_error("Error: Cannot Evaluate expression with non-numeric tokens!");
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
    vector<string> tokens;
    string currentToken;

    // Tokenize the postfix expression
    for (char ch : postfix) {
        if (ch == ' ') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken += ch;

        }
    }
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    // Iterate over the tokens
    for (int i = 0; i < tokens.size(); i++) {  // Fixed the loop condition to i < tokens.size()
        string token = tokens[i];

            if (isOperator(token)) {  // Check if the token is an operator
                if (s.size() < 2) {
                    throw std::invalid_argument("Invalid postfix expression: not enough operands for operator!");
                }
                TreeNode* rightChild = s.peek();
                s.pop();
                TreeNode* leftChild = s.peek();
                s.pop();

                TreeNode* newNode = new TreeNode(token);
                newNode->left = leftChild;
                newNode->right = rightChild;
                s.push(newNode);
            } else {  // Operand (number or variable)
                s.push(new TreeNode(token));
            }
        }

        if (s.size() != 1) {
            throw std::invalid_argument("Invalid postfix expression: too many operands!");
        }
        root = s.peek();  // Assign the root to the single remaining node in the stack
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
string ExpressionTree::removeSpaces(const std::string& str) {
    string result;
    for (char ch : str) {
        if (!isspace(ch)) {
            result += ch;
        }
    }
    return result;
}
void ExpressionTree::buildfromInfix( string& infix) {
    // Yousef Elmenshawy
    if (infix.empty()) {
        throw std::invalid_argument( "Error: Infix expression is empty!");
    }
    // Remove spaces
    infix=removeSpaces(infix);
    Stackt<TreeNode*> nodeStack(infix.size());       // Stack for operands/subtrees
    Stackt<char> operatorStack(infix.size());        // Stack for operators
    // Process the infix expression character by character
    int i = 0;
    while (i < infix.size()) {
        if (isspace(infix[i])) {
            i++; // Skip whitespaces
            continue;
        }


        if (isdigit(infix[i])||isalpha(infix[i])) {// Handling Multidigit
            string numStr;
            while (i < infix.size() && (isdigit(infix[i])||isalpha(infix[i]))) {
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
        else if (infix[i] == '-' &&
                   (i == 0 ||( infix[i - 1] == '(' && i>0) || (isOperator(infix[i - 1]) && i>0))) {
            // Unary minus case: Start a negative number
            i++; // Skip the '-'
            string numStr = "-";
            while (i < infix.size() &&isdigit(infix[i])) {
                numStr += infix[i++];
            }
            nodeStack.push(new TreeNode(numStr));  // Push negative operand as a tree node
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
void ExpressionTree::displayConversionMenu(ExpressionTree& tree) {
    string input;
    int choice;
    cout << "Welcome to our Tree of expressions!";
    while (true) {
        cout << "\nExpression Conversion Menu:\n";
        cout << "1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Postfix to Infix\n";
        cout << "4. Postfix to Prefix\n";
        cout << "5. Prefix to Infix\n";
        cout << "6. Prefix to Postfix\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7) {
            cout << "Exiting the menu. Goodbye!\n";
            break;
        }

        cout << "Enter the expression: ";
        cin.ignore(); // Clear newline from the input buffer
        getline(cin, input);

        try {
            switch (choice) {
                case 1: // Infix to Postfix
                    tree.buildfromInfix(input);
                cout << "Postfix Expression: " << tree.ToPostfix(tree.Root_Accesser()) << "\n";
                break;
                case 2: // Infix to Prefix
                    tree.buildfromInfix(input);
                cout << "Prefix Expression: " << tree.ToPrefix(tree.Root_Accesser()) << "\n";
                break;
                case 3: // Postfix to Infix
                    tree.buildfromPostfix(input);
                cout << "Infix Expression: " << tree.ToInfix(tree.Root_Accesser()) << "\n";
                break;
                case 4: // Postfix to Prefix
                    tree.buildfromPostfix(input);
                cout << "Prefix Expression: " << tree.ToPrefix(tree.Root_Accesser()) << "\n";
                break;
                case 5: // Prefix to Infix
                    tree.buildfromPrefix(input);
                cout << "Infix Expression: " << tree.ToInfix(tree.Root_Accesser()) << "\n";
                break;
                case 6: // Prefix to Postfix
                    tree.buildfromPrefix(input);
                cout << "Postfix Expression: " << tree.ToPostfix(tree.Root_Accesser()) << "\n";
                break;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    continue;
            }
            try
            {
                double result = tree.evaluateExpression();
                cout << "The evaluated value of the expression is: " << result << "\n";
            }catch (const std::exception& evalErr) {
                cout << "The expression could not be evaluated. Reason: " << evalErr.what() << "\n";
            }
        } catch (const std::exception& e) {
            cout << e.what() << "\n";// just in case if there were any errors inside the switch case but it should be fine
        }
    }
}