#include "BinaryTree.h"
#include <climits>
#include <cstdlib>

BinaryTree::TreeNode::TreeNode() : key_(0), left_(nullptr), right_(nullptr) {}

BinaryTree::TreeNode::TreeNode(int key, TreeNode* left, TreeNode* right) 
    : key_(key), left_(left), right_(right) {}

int BinaryTree::TreeNode::getKey() const {
    return key_;
}

void BinaryTree::TreeNode::setKey(int key) {
    key_ = key;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::getLeft() const {
    return left_;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::getRight() const {
    return right_;
}

void BinaryTree::TreeNode::setLeft(TreeNode* left) {
    left_ = left;
}

void BinaryTree::TreeNode::setRight(TreeNode* right) {
    right_ = right;
}

BinaryTree::BinaryTree(TreeNode* root) : root_(root) {}

BinaryTree::BinaryTree(const BinaryTree& other) {
    root_ = copyTree(other.root_);
}

BinaryTree::BinaryTree(BinaryTree&& other) noexcept {
    root_ = other.root_;
    other.root_ = nullptr;
}

BinaryTree::~BinaryTree() {
    clearSubtree(root_);
}

BinaryTree::TreeNode* BinaryTree::getRoot() const {
    return root_;
}

void BinaryTree::setRoot(TreeNode* root) {
    root_ = root;
}

void BinaryTree::clear() {
    clearSubtree(root_);
    root_ = nullptr;
}

void BinaryTree::removeSubtrees() {
    removeChildSubtrees(root_);
}

bool BinaryTree::isEmpty() const {
    return root_ == nullptr;
}

int BinaryTree::getHeight() const {
    return calculateHeight(root_);
}

int BinaryTree::getNodeLevel(int key) const {
    return findNodeLevel(root_, key, 0);
}

int BinaryTree::getNodeIndex(int key) const {
    return findNodeIndex(root_, key);
}

int BinaryTree::getNodeCount() const {
    return countNodes(root_);
}

int BinaryTree::getMaxKey() const {
    return findMaxKey(root_);
}

int BinaryTree::getMinKey() const {
    return findMinKey(root_);
}

BinaryTree::TreeNode* BinaryTree::insert(int key) {
    return insertRandom(root_, key);
}

BinaryTree::TreeNode* BinaryTree::find(int key) const {
    return findNode(root_, key);
}

bool BinaryTree::remove(int key) {
    return removeNode(root_, key);
}

bool BinaryTree::contains(int key) const {
    return findNode(root_, key) != nullptr;
}

std::vector<int> BinaryTree::getKeysInOrder() const {
    std::vector<int> keys;
    collectKeysInOrder(root_, keys);
    std::sort(keys.begin(), keys.end());
    return keys;
}

void BinaryTree::printLevelOrder() const {
    printLevel(root_);
}

void BinaryTree::printHorizontal(int marginLeft, int levelSpacing) const {
    printHorizontal(root_, marginLeft, levelSpacing);
}

bool BinaryTree::isBalanced() const {
    return checkBalance(root_);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {
        clearSubtree(root_);
        root_ = copyTree(other.root_);
    }
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other) noexcept {
    if (this != &other) {
        clearSubtree(root_);
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

BinaryTree::TreeNode* BinaryTree::copyTree(TreeNode* node) {
    if (!node) return nullptr;

    TreeNode* newNode = new TreeNode(node->getKey());
    newNode->setLeft(copyTree(node->getLeft()));
    newNode->setRight(copyTree(node->getRight()));
    return newNode;
}

void BinaryTree::clearSubtree(TreeNode* node) {
    if (!node) return;

    clearSubtree(node->getLeft());
    clearSubtree(node->getRight());
    delete node;
}

void BinaryTree::removeChildSubtrees(TreeNode* node) {
    if (!node) return;

    clearSubtree(node->getLeft());
    clearSubtree(node->getRight());
    node->setLeft(nullptr);
    node->setRight(nullptr);
}

int BinaryTree::calculateHeight(TreeNode* node) const {
    if (!node) return 0;
    return 1 + std::max(calculateHeight(node->getLeft()), 
                     calculateHeight(node->getRight()));
}

int BinaryTree::findNodeLevel(TreeNode* node, int key, int level) const {
    if (!node) return -1;
    if (node->getKey() == key) return level;

    int left = findNodeLevel(node->getLeft(), key, level + 1);
    if (left != -1) return left;

    return findNodeLevel(node->getRight(), key, level + 1);
}

int BinaryTree::findNodeIndex(TreeNode* node, int key) const {
    if (!node) return -1;

    std::list<TreeNode*> queue{node};
    int index = 0;

    while (!queue.empty()) {
        int levelSize = queue.size();

        while (levelSize--) {
            TreeNode* current = queue.front();
            queue.pop_front();

            if (current->getKey() == key) return index;

            if (current->getLeft()) queue.push_back(current->getLeft());
            if (current->getRight()) queue.push_back(current->getRight());

            index++;
        }
    }
    return -1;
}

int BinaryTree::countNodes(TreeNode* node) const {
    return node ? 1 + countNodes(node->getLeft()) + countNodes(node->getRight()) : 0;
}

int BinaryTree::findMaxKey(TreeNode* node) const {
    if (!node) return INT_MIN;
    return std::max(node->getKey(), 
                   std::max(findMaxKey(node->getLeft()), 
                           findMaxKey(node->getRight())));
}

int BinaryTree::findMinKey(TreeNode* node) const {
    if (!node) return INT_MAX;
    return std::min(node->getKey(),
                   std::min(findMinKey(node->getLeft()),
                           findMinKey(node->getRight())));
}

BinaryTree::TreeNode* BinaryTree::insertRandom(TreeNode* node, int key) {
    if (!node) {
        node = new TreeNode(key);
        if (!root_) root_ = node;
        return node;
    }

    if (rand() % 2) {
        node->setLeft(insertRandom(node->getLeft(), key));
    } else {
        node->setRight(insertRandom(node->getRight(), key));
    }
    return node;
}

BinaryTree::TreeNode* BinaryTree::findNode(TreeNode* node, int key) const {
    if (!node || node->getKey() == key) return node;

    TreeNode* leftResult = findNode(node->getLeft(), key);
    return leftResult ? leftResult : findNode(node->getRight(), key);
}

bool BinaryTree::removeNode(TreeNode* root, int key) {
    TreeNode* node = findNode(root, key);
    if (!node) return false;

    TreeNode* parent = findParent(root, node);

    if (!node->getLeft() && !node->getRight()) {
        if (parent) {
            if (parent->getLeft() == node) parent->setLeft(nullptr);
            else parent->setRight(nullptr);
            delete node;
        } else {
            delete node;
            root_ = nullptr;
        }
    }
    else if (!node->getLeft() || !node->getRight()) {
        TreeNode* child = node->getLeft() ? node->getLeft() : node->getRight();
        if (parent) {
            if (parent->getLeft() == node) parent->setLeft(child);
            else parent->setRight(child);
            delete node;
        } else {
            root_ = child;
            delete node;
        }
    }
    else {
        TreeNode* successor = node->getRight();
        TreeNode* successorParent = node;

        while (successor->getLeft()) {
            successorParent = successor;
            successor = successor->getLeft();
        }

        if (successorParent != node) {
            successorParent->setLeft(successor->getRight());
            successor->setRight(node->getRight());
        }
        successor->setLeft(node->getLeft());

        if (parent) {
            if (parent->getLeft() == node) parent->setLeft(successor);
            else parent->setRight(successor);
        } else {
            root_ = successor;
        }
        delete node;
    }
    return true;
}

BinaryTree::TreeNode* BinaryTree::findParent(TreeNode* current, TreeNode* target) const {
    if (!current || current == target) return nullptr;
    if (current->getLeft() == target || current->getRight() == target) return current;

    TreeNode* leftResult = findParent(current->getLeft(), target);
    if (leftResult) return leftResult;

    return findParent(current->getRight(), target);
}

void BinaryTree::collectKeysInOrder(TreeNode* node, std::vector<int>& keys) const {
    if (!node) return;
    collectKeysInOrder(node->getLeft(), keys);
    keys.push_back(node->getKey());
    collectKeysInOrder(node->getRight(), keys);
}

void BinaryTree::printLevel(TreeNode* node) const {
    if (!node) return;

    std::list<TreeNode*> queue{node};
    while (!queue.empty()) {
        int levelSize = queue.size();
        while (levelSize--) {
            TreeNode* current = queue.front();
            queue.pop_front();
            std::cout << current->getKey() << " ";

            if (current->getLeft()) queue.push_back(current->getLeft());
            if (current->getRight()) queue.push_back(current->getRight());
        }
        std::cout << "\n";
    }
}

void BinaryTree::printHorizontal(TreeNode* node, int marginLeft, int levelSpacing) const {
    if (!node) return;
    printHorizontal(node->getRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << node->getKey() << "\n";
    printHorizontal(node->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

bool BinaryTree::checkBalance(TreeNode* node) const {
    if (!node) return true;
    int leftHeight = calculateHeight(node->getLeft());
    int rightHeight = calculateHeight(node->getRight());
    return abs(leftHeight - rightHeight) <= 1 && 
           checkBalance(node->getLeft()) && 
           checkBalance(node->getRight());
}
       
