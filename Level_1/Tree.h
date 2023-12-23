#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TreeNode {
public:
    string data;
    TreeNode* parent;
    vector<TreeNode*> children;
    TreeNode(const string& value, TreeNode* parent);
};

class Tree {
private:
    TreeNode* root;
    TreeNode* current;
    TreeNode* insertRecursive(TreeNode* current, const string& value, const string& parentValue);
    string preOrderTraversal(TreeNode* current);
    vector<TreeNode*> getChildrenRecursive(TreeNode* current, const string& value);

public:
    Tree();
    void insert(const string& value, const string& parentValue);
    string preOrder();
    vector<TreeNode*> getChildren(const string& value);
};
