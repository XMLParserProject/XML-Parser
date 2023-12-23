#include "Tree.h"

TreeNode::TreeNode(const string& value, TreeNode* parent){
    this->data=value;
    this->parent=parent;
     }

Tree::Tree() : root(nullptr) {}

TreeNode* Tree::insertRecursive(TreeNode* current, const string& value, const string& parentValue) {
    if (current->data == parentValue) {
        current->children.push_back(new TreeNode(value, current));
        return current;
    }else{
    for (TreeNode* child : current->children) {
        if(child->data == parentValue){
        current->children.push_back(new TreeNode(value, current));
        return current;
    }
    }
    }
    return insertRecursive(current->parent, value, parentValue);
}

void Tree::insert(const string& value, const string& parentValue) {
    if (root == nullptr) {
        root = new TreeNode(value, root);
    } else {
        if(root->children.empty()){
            this->current=insertRecursive(root, value, parentValue);
        }
        else{
            this->current=insertRecursive(current, value, parentValue);
        }

    }
}

string Tree::preOrderTraversal(TreeNode* current) {
    string result;
    if (current != nullptr) {
        result += current->data + "<>";
        for (TreeNode* child : current->children) {
            result += preOrderTraversal(child);
        }
    }
    return result;
}

vector<TreeNode*> Tree::getChildrenRecursive(TreeNode* current, const string& value) {
    if (current->data == value) {
        return current->children;
    }

    for (TreeNode* child : current->children) {
        auto result = getChildrenRecursive(child, value);
        if (!result.empty()) {
            return result;
        }
    }

    return {}; // Return an empty vector if the node is not found
}

string Tree::preOrder() {
    return preOrderTraversal(root);
}

vector<TreeNode*> Tree::getChildren(const string& value) {
    return getChildrenRecursive(root, value);
}
