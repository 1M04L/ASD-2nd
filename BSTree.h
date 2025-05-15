
#pragma once
#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() = default;
    BinarySearchTree(TreeNode* root);
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    virtual ~BinarySearchTree() = default;

    virtual TreeNode* insert(int key) override;
    virtual bool remove(int key) override;
    virtual TreeNode* find(int key) const override;
    virtual int getNodeLevel(int key) const override;

    BinarySearchTree& operator=(const BinarySearchTree& other);
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

private:
    TreeNode* insertRecursive(TreeNode* node, int key);
    TreeNode* removeRecursive(TreeNode* node, int key);
    TreeNode* findMin(TreeNode* node) const;
    TreeNode* findRecursive(TreeNode* node, int key) const;
    int findNodeLevelRecursive(TreeNode* node, int key, int level) const;
};
