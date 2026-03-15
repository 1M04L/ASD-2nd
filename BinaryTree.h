#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class BinaryTree 
{
public:
    class TreeNode {
    public:
        TreeNode();
        TreeNode(int key, TreeNode* left = nullptr, TreeNode* right = nullptr);
        ~TreeNode() = default;

        int getKey() const;
        void setKey(int key);

        TreeNode* getLeft() const;
        TreeNode* getRight() const;

        void setLeft(TreeNode* left);
        void setRight(TreeNode* right);

    private:
        int key_;
        TreeNode* left_;
        TreeNode* right_;
    };

    BinaryTree() = default;
    BinaryTree(TreeNode* root);
    BinaryTree(const BinaryTree& other);
    BinaryTree(BinaryTree&& other) noexcept;
    virtual ~BinaryTree();

    TreeNode* getRoot() const;
    void setRoot(TreeNode* root);

    void clear();
    void removeSubtrees();
    bool isEmpty() const;

    int getHeight() const;
    int getNodeLevel(int key) const;
    int getNodeIndex(int key) const;
    int getNodeCount() const;
    int getMaxKey() const;
    int getMinKey() const;
    TreeNode* insert(int key);
    TreeNode* find(int key) const;
    bool remove(int key);
    bool contains(int key) const;
    std::vector<int> getKeysInOrder() const;
    void printLevelOrder() const;
    void printHorizontal(int marginLeft, int levelSpacing) const;

    bool isBalanced() const;

    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other) noexcept;

private:
    TreeNode* root_ = nullptr;
    TreeNode* copyTree(TreeNode* node);
    void clearSubtree(TreeNode* node);
    void removeChildSubtrees(TreeNode* node);

    int calculateHeight(TreeNode* node) const;
    int findNodeLevel(TreeNode* node, int key, int level) const;
    int findNodeIndex(TreeNode* node, int key) const;

    int countNodes(TreeNode* node) const;
    int findMaxKey(TreeNode* node) const;
    int findMinKey(TreeNode* node) const;

    TreeNode* insertRandom(TreeNode* node, int key);
    TreeNode* findNode(TreeNode* node, int key) const;
    TreeNode* findParent(TreeNode* current, TreeNode* target) const;

    bool removeNode(TreeNode* root, int key);
    void collectKeysInOrder(TreeNode* node, std::vector<int>& keys) const;

    void printLevel(TreeNode* node) const;
    void printHorizontal(TreeNode* node, int marginLeft, int levelSpacing) const;

    bool checkBalance(TreeNode* node) const;
};
