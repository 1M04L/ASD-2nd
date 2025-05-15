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
        virtual ~TreeNode() = default;

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

    virtual int getHeight() const;
    virtual int getNodeLevel(int key) const;
    virtual int getNodeIndex(int key) const;
    virtual int getNodeCount() const;
    virtual int getMaxKey() const;
    virtual int getMinKey() const;
    virtual TreeNode* insert(int key);
    virtual TreeNode* find(int key) const;
    virtual bool remove(int key);
    virtual bool contains(int key) const;
    virtual std::vector<int> getKeysInOrder() const;
    virtual void printLevelOrder() const;
    virtual void printHorizontal(int marginLeft, int levelSpacing) const;

    virtual bool isBalanced() const;

    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other) noexcept;

    TreeNode* root_ = nullptr;
    virtual TreeNode* copyTree(TreeNode* node);
    virtual void clearSubtree(TreeNode* node);
    virtual void removeChildSubtrees(TreeNode* node);

    virtual int calculateHeight(TreeNode* node) const;
    virtual int findNodeLevel(TreeNode* node, int key, int level) const;
    virtual int findNodeIndex(TreeNode* node, int key) const;

    virtual int countNodes(TreeNode* node) const;
    virtual int findMaxKey(TreeNode* node) const;
    virtual int findMinKey(TreeNode* node) const;

    virtual TreeNode* insertRandom(TreeNode* node, int key);
    virtual TreeNode* findNode(TreeNode* node, int key) const;
    virtual TreeNode* findParent(TreeNode* current, TreeNode* target) const;

    virtual bool removeNode(TreeNode* root, int key);
    virtual void collectKeysInOrder(TreeNode* node, std::vector<int>& keys) const;

    virtual void printLevel(TreeNode* node) const;
    virtual void printHorizontal(TreeNode* node, int marginLeft, int levelSpacing) const;

    virtual bool checkBalance(TreeNode* node) const;
};
