#ifndef TREENODE_H
#define TREENODE_H
#include <string>
using namespace std;

class TreeNode {
public:
    string value;
    TreeNode* left;
    TreeNode* right;

    // Constructor for TreeNode
    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
    TreeNode() : value(""), left(nullptr), right(nullptr) {}
};
#endif //TREENODE_H
