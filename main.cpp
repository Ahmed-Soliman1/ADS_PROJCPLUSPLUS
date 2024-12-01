#include <iostream>
#include <string>
#include "expressiontree.h"

using namespace std;


int main()
{


    // Testing the program
    ExpressionTree Tree;
    string PostfixExpression = "13 4 +";
    string InfixExpression= " 1+2*3/(6+7)";
    string PrefixExpression = "+ + * 3 4 - 5 2 7";
    cerr << "Building tree for: " << PostfixExpression << endl;

    Tree.buildfromPostfix(PostfixExpression);
    if (Tree.Root_Accesser()) {
        cerr << "Infix Expression: " << Tree.ToInfix(Tree.Root_Accesser()).toStdString() << endl;
    } else {
        cerr << "Error: Tree was not constructed!" << endl;
    }
    Tree.reset();
    cerr << "Building tree for: " << InfixExpression << endl;

    Tree.buildfromInfix(InfixExpression);
    if (Tree.Root_Accesser()) {
        cerr << "Postfix Expression: " << Tree.ToPostfix(Tree.Root_Accesser()).toStdString() << endl;
    } else {
        cerr << "Error: Tree was not constructed!" << endl;
    }
    Tree.reset();
    cerr << "Building tree for: " << PrefixExpression << endl;

    Tree.buildfromPrefix(PrefixExpression);
    if (Tree.Root_Accesser()) {
        cerr << "Postfix Expression: " << Tree.ToPostfix(Tree.Root_Accesser()).toStdString() << endl;
    } else {
        cerr << "Error: Tree was not constructed!" << endl;
    }



    return 0;

}
