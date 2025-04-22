#include <iostream>
#include <ctime>

using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node() {
        key = 0;
        left = nullptr;
        right = nullptr;
    }

    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
    }

    Node(int k, Node* l, Node* r) {
        key = k;
        left = l;
        right = r;
    }
};

class BinaryTree {
private:
    Node* root;

    void clearTree(Node* node) {
        if (node == nullptr) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    int countNodes(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    Node* addNodeRandom(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (std::time(nullptr) % 2 == 0) {
            node->left = addNodeRandom(node->left, key);
        } else {
            node->right = addNodeRandom(node->right, key);
        }

        return node;
    }

    Node* findNode(Node* node, int key) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->key == key) {
            return node;
        }

        Node* found = findNode(node->left, key);
        if (found != nullptr) {
            return found;
        }

        return findNode(node->right, key);
    }

    bool removeNode(Node*& node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key < node->key) {
            return removeNode(node->left, key);
        }

        if (key > node->key) {
            return removeNode(node->right, key);
        }

        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* minRight = node->right;
            while (minRight->left != nullptr) {
                minRight = minRight->left;
            }
            node->key = minRight->key;
            removeNode(node->right, minRight->key);
        }
        return true;
    }

    void printTree(Node* node, int space) const {
        if (node == nullptr) {
            return;
        }

        space += 5;

        printTree(node->right, space);

        cout << endl;
        for (int i = 5; i < space; i++) {
            cout << " ";
        }
        cout << node->key << "\n";

        printTree(node->left, space);
    }

    Node* copyTree(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(node->key);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    BinaryTree(const BinaryTree& other) {
        root = copyTree(other.root);
    }

    ~BinaryTree() {
        clear();
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();
            root = copyTree(other.root);
        }
        return *this;
    }

    Node* getRoot() const {
        return root;
    }

    void clear() {
        clearTree(root);
        root = nullptr;
    }

    bool isEmpty() const {
        if (root == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    int getNodeCount() const {
        return countNodes(root);
    }

    void addNode(int key) {
        root = addNodeRandom(root, key);
    }

    bool remove(int key) {
        return removeNode(root, key);
    }

    Node* search(int key) const {
        return findNode(root, key);
    }

    void print() const {
        if (root == nullptr) {
            cout << "Дерево пустое" << endl;
        } else {
            printTree(root, 0);
        }
    }
};

int main() {
    BinaryTree tree;

    tree.addNode(10);
    tree.addNode(5);
    tree.addNode(15);
    tree.addNode(3);
    tree.addNode(7);
    tree.addNode(12);
    tree.addNode(17);

    cout << "Дерево:" << endl;
    tree.print();

    cout << "Количество узлов: ";
    cout << tree.getNodeCount() << endl;

    Node* found = tree.search(12);
    if (found != nullptr) {
        cout << "Узел 12 найден" << endl;
    } else {
        cout << "Узел 12 не найден" << endl;
    }

    if (tree.remove(5)) {
        cout << "Узел 5 удален" << endl;
    } else {
        cout << "Узел 5 не найден" << endl;
    }

    cout << "Дерево после удаления:" << endl;
    tree.print();

    cout << "Дерево пустое? ";
    if (tree.isEmpty()) {
        cout << "Да" << endl;
    } else {
        cout << "Нет" << endl;
    }

    tree.clear();
    cout << "Дерево после очистки:" << endl;
    tree.print();

    cout << "Дерево пустое? ";
    if (tree.isEmpty()) {
        cout << "Да" << endl;
    } else {
        cout << "Нет" << endl;
    }

    return 0;
}
