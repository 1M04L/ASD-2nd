
#include "BSTree.h"

BinarySearchTree::BinarySearchTree(TreeNode* root) : BinaryTree(root) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : BinaryTree(other) {}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept : BinaryTree(std::move(other)) {}

BinarySearchTree::TreeNode* BinarySearchTree::insert(int key) {
    if (!getRoot()) {
        setRoot(new TreeNode(key));
        return getRoot();
    }
    return insertRecursive(getRoot(), key);
}

bool BinarySearchTree::remove(int key) {
    if (!find(key)) return false;
    setRoot(removeRecursive(getRoot(), key));
    return true;
}

BinarySearchTree::TreeNode* BinarySearchTree::find(int key) const {
    return findRecursive(getRoot(), key);
}

int BinarySearchTree::getNodeLevel(int key) const {
    return findNodeLevelRecursive(getRoot(), key, 0);
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this != &other) {
        BinaryTree::operator=(other);
    }
    return *this;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept {
    if (this != &other) {
        BinaryTree::operator=(std::move(other));
    }
    return *this;
}

BinarySearchTree::TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int key) {
    if (!node) return new TreeNode(key);

    if (key < node->getKey()) {
        node->setLeft(insertRecursive(node->getLeft(), key));
    } else {
        node->setRight(insertRecursive(node->getRight(), key));
    }
    return node;
}

BinarySearchTree::TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int key) {
    if (!node) return nullptr;

    if (key < node->getKey()) {
        node->setLeft(removeRecursive(node->getLeft(), key));
    } else if (key > node->getKey()) {
        node->setRight(removeRecursive(node->getRight(), key));
    } else {
        if (!node->getLeft()) {
            TreeNode* rightChild = node->getRight();
            delete node;
            return rightChild;
        } else if (!node->getRight()) {
            TreeNode* leftChild = node->getLeft();
            delete node;
            return leftChild;
        } else {
            TreeNode* minNode = findMin(node->getRight());
            node->setKey(minNode->getKey());
            node->setRight(removeRecursive(node->getRight(), minNode->getKey()));
        }
    }
    return node;
}

BinarySearchTree::TreeNode* BinarySearchTree::findMin(TreeNode* node) const {
    while (node && node->getLeft()) {
        node = node->getLeft();
    }
    return node;
}

BinarySearchTree::TreeNode* BinarySearchTree::findRecursive(TreeNode* node, int key) const {
    if (!node || node->getKey() == key) return node;
    if (key < node->getKey()) return findRecursive(node->getLeft(), key);
    return findRecursive(node->getRight(), key);
}

int BinarySearchTree::findNodeLevelRecursive(TreeNode* node, int key, int level) const {
    if (!node) return -1;
    if (node->getKey() == key) return level;
    if (key < node->getKey()) 
        return findNodeLevelRecursive(node->getLeft(), key, level + 1);
    return findNodeLevelRecursive(node->getRight(), key, level + 1);
}
